#include <Arduino.h>
#include <SPI.h>
#include <RH_RF95.h>
#include <stdio.h>

#include <Adafruit_MQTT.h>
#include <Adafruit_MQTT_Client.h>

#include <Ethernet.h>
#include <EthernetClient.h>
#include <Dns.h>
#include <Dhcp.h>


// rfm95
#define RH_FLAGS_ACK 0x80
#define RFM95_CS 9 // chip select
#define RFM95_RST 3 // reset
#define RFM95_INT 2 // interrupt
#define RF95_FREQ 915.0 // center frequency

#define MESSAGE_LENGTH 2 // fixed message length

#define LORA_ARDUINO_ADDRESS 69
#define LORA_MONITOR_ADDRESS 70

RH_RF95 rf95(RFM95_CS, RFM95_INT); // instance of radio driver

uint8_t rx_buf[MESSAGE_LENGTH];
uint8_t rx_recv_len = MESSAGE_LENGTH;


// ethernet
byte mac[] = {0x90, 0xA2, 0xDA, 0x10, 0x02, 0x0B}; // school mac

EthernetClient client;


// mqtt
#define AIO_SERVER "io.adafruit.com"
#define AIO_SERVERPORT 1883
#define AIO_USERNAME "edwward"
#define AIO_KEY "aio_Rgmw87fzyaUj4rX2qVDL5s9yhEDL"

Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME, AIO_KEY);

Adafruit_MQTT_Publish temp = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/enviromon.temperature");
Adafruit_MQTT_Publish humidity = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/enviromon.humidity");
Adafruit_MQTT_Publish battery = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/enviromon.battery");


// lora message bytes
enum {
  lora_sampleid, // sample type id
  lora_value // sample value
};

// sample type ids
enum {
  temperature_id = 1,
  humidity_id,
  battery_id
};


// function declarations
void process_data(uint8_t[]);


// run setup routine
void setup() {
  // reset rfm95 
  pinMode(RFM95_RST, OUTPUT);
  digitalWrite(RFM95_RST, LOW);
  delay(10);
  digitalWrite(RFM95_RST, HIGH);
  delay(10);

  // init serial
  while(!Serial);
  Serial.begin(9600);
  delay(100);

  // check for lora init
  while (!rf95.init()) {
    Serial.println("radio init failed :(");
    while (1);
  }
  Serial.println("radio init success!");

  // set lora frequency
  if (!rf95.setFrequency(RF95_FREQ)) {
    Serial.println("cannot set frequency");
    while (1);
  }
  Serial.print("frequency set to: "); Serial.println(RF95_FREQ);

  // set address to arduino address
  rf95.setThisAddress(LORA_ARDUINO_ADDRESS);

  // init ethernet
  Ethernet.begin(mac);
  delay(1000);

  // print ip address
  Serial.print("ip: "); Serial.println(Ethernet.localIP());
}


// main program loop
void loop() {
  rf95.waitAvailable(50); // wait for message, check 50ms

  if (rf95.recv(rx_buf, &rx_recv_len)) { // receive message
    Serial.println(); // seperate debug messages with newline

    uint8_t i;
    for (i = 0; i < sizeof(rx_buf); i++) {
      Serial.println(rx_buf[i]);
    }

    process_data(rx_buf); // process and send data
  }

  // uncomment if spamming
  // delay(3000);
}


// connect and reconnect to mqtt server as necessary
void MQTT_connect() {
  int8_t ret;

  // stop if already connected
  if (mqtt.connected()) {
    return;
  }

  Serial.println("connecting to mqtt...");
  
  while ((ret = mqtt.connect()) != 0) {
    Serial.println(mqtt.connectErrorString(ret));
    Serial.println("retrying mqtt connection in 5 seconds...");
    mqtt.disconnect();
    delay(5000);
  }

  Serial.println("mqtt connected!"); Serial.println("");
}


// process received data
void process_data(uint8_t data[]) {
  // ensure connection to broker
  MQTT_connect();

  // determine data type
  switch (data[lora_sampleid]) {

    // temperature sample handle
    case temperature_id:
      Serial.print("temp: "); Serial.println(data[lora_value]);
      if (!temp.publish((int32_t) data[lora_value])) {
        Serial.println("temp failed!");
      } else {
        Serial.println("temp sent!");
      }
    break;

    // humidity sample handle
    case humidity_id:
      Serial.print("humidity: "); Serial.println(data[lora_value]);
      if (!humidity.publish((int32_t) data[lora_value])) {
        Serial.println("humidity failed!");
      } else {
        Serial.println("humidity sent!");
      }
    break;

    // battery sample handle
    case battery_id:
      Serial.print("battery: "); Serial.println(data[lora_value]);
      if (!battery.publish((int32_t) data[lora_value])) {
        Serial.println("battery failed!");
      } else {
        Serial.println("battery sent!");
      }
    break;

    // invalid id
    default:
      Serial.println("invalid data!");
  }

  // ping server to keep connection alive
  if(!mqtt.ping()) {
    mqtt.disconnect();
  }
}