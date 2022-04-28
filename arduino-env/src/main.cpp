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

#define MESSAGE_LENGTH 5 // fixed message length

#define LORA_ARDUINO_ADDRESS 69
#define LORA_MONITOR_ADDRESS 70

RH_RF95 rf95(RFM95_CS, RFM95_INT); // instance of radio driver

uint8_t rx_buf[MESSAGE_LENGTH];
uint8_t rx_recv_len = MESSAGE_LENGTH;

// rssi holding variable
int16_t rssi_val;

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

// sample unions
union {
  float ufloat;
  uint8_t ubytes[4];
} union_temp, union_humidity, union_battery;


// ethernet
byte mac[] = {0x00, 0xAA, 0xBB, 0xCC, 0xDE, 0x02}; // school mac

EthernetClient client;


// mqtt
#define AIO_SERVER "mqtt.elen.ca"
#define AIO_SERVERPORT 1883

Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT);

Adafruit_MQTT_Publish temp = Adafruit_MQTT_Publish(&mqtt, "edward/temperature");
Adafruit_MQTT_Publish humidity = Adafruit_MQTT_Publish(&mqtt, "edward/humidity");
Adafruit_MQTT_Publish battery = Adafruit_MQTT_Publish(&mqtt, "edward/battery");
Adafruit_MQTT_Publish rssi = Adafruit_MQTT_Publish(&mqtt, "edward/rssi");


// using serial?
bool using_serial = 1;


// process received data
void process_data() {
  // connect to broker
  while (!mqtt.connected()) {
    if (!mqtt.connect()) {
      Serial.println("retrying mqtt connection in 5 seconds...");
      delay(5000);
    }
  }

  if (using_serial) {
    Serial.print("rssi: "); Serial.println(rssi_val);
  }
  if (!rssi.publish((double)rssi_val)) {
    if (using_serial) Serial.println("rssi failed!");
  } else {
    if (using_serial) Serial.println("rssi sent!");
  }

  // determine data type
  int i;
  switch (rx_buf[lora_sampleid]) {

    // temperature sample handle
    case temperature_id:
      for (i = 0; i < (uint8_t)sizeof(union_temp.ubytes); i++) {
        union_temp.ubytes[i] = rx_buf[i+1];
      }

      if (using_serial) {
        Serial.print("temp: "); Serial.println(union_temp.ufloat);
      }
      if (!temp.publish(union_temp.ufloat)) {
        if (using_serial) Serial.println("temp failed!");
      } else {
        if (using_serial) Serial.println("temp sent!");
      }
    break;

    // humidity sample handle
    case humidity_id:
      for (i = 0; i < (uint8_t)sizeof(union_humidity.ubytes); i++) {
        union_humidity.ubytes[i] = rx_buf[i+1];
      }


      if (using_serial) {
        Serial.print("humidity: "); Serial.println(union_humidity.ufloat);
      }
      if (!humidity.publish(union_humidity.ufloat)) {
        if (using_serial) Serial.println("humidity failed!");
      } else {
        if (using_serial) Serial.println("humidity sent!");
      }
    break;

    // battery sample handle
    case battery_id:
      for (i = 0; i < (uint8_t)sizeof(union_battery.ubytes); i++) {
        union_battery.ubytes[i] = rx_buf[i+1];
      }

      if (using_serial) {
        Serial.print("battery: "); Serial.println(union_battery.ufloat);
      }
      if (!battery.publish(union_battery.ufloat)) {
        if (using_serial) Serial.println("battery failed!");
      } else {
        if (using_serial) Serial.println("battery sent!");
      }
    break;

    // invalid id
    default:
      if (using_serial) Serial.println("invalid data!");
  }

  // ping server to keep connection alive
  if(!mqtt.ping()) {
    mqtt.disconnect();
  }
}


// initialize lora module
void lora_init() {
  // reset rfm95 
  pinMode(RFM95_RST, OUTPUT);
  digitalWrite(RFM95_RST, LOW);
  delay(10);
  digitalWrite(RFM95_RST, HIGH);
  delay(10);

  // check for lora init
  while (!rf95.init()) {
    if (using_serial) Serial.println("radio init failed :(");
    while (1);
  }
  if (using_serial) Serial.println("radio init success!");
  
  // set lora frequency
  if (!rf95.setFrequency(RF95_FREQ)) {
    if (using_serial) Serial.println("cannot set frequency");
    while (1);
  }
  if (using_serial) {
    Serial.print("frequency set to: "); Serial.println(RF95_FREQ);
  }

  // set address to arduino address
  rf95.setThisAddress(LORA_ARDUINO_ADDRESS);
  if (using_serial) Serial.println("lora address set!");
}


// run setup routine
void setup() {
  // init serial
  if (using_serial) while(!Serial);
  if (using_serial) Serial.begin(9600);
  delay(100);

  // init ethernet
  Ethernet.begin(mac);
  delay(1000);

  // print ip address
  if (using_serial) {
    Serial.print("ip: "); Serial.println(Ethernet.localIP());
  }

  lora_init();
}


// main program loop
void loop() {
  rf95.waitAvailable(50); // wait for message, check 50ms

  if (rf95.recv(rx_buf, &rx_recv_len)) { // receive message
    if (using_serial) Serial.println(); // seperate debug messages with newline

    uint8_t i;
    for (i = 0; i < sizeof(rx_buf); i++) {
      if (using_serial) Serial.println(rx_buf[i]);
    }
    
    rssi_val = rf95.lastRssi(); // capture rssi

    process_data(); // process and send data
  }
}