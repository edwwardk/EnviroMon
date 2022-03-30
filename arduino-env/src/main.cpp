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

RH_RF95 rf95(RFM95_CS, RFM95_INT); // instance of radio driver

int16_t rx_count = 0;
uint8_t rx_buf[RH_RF95_MAX_MESSAGE_LEN];
uint8_t rx_recv_len;

char print_buf[32] = "\0";


// mqtt and ethernet
//byte mac[] = {0x00, 0xAA, 0xBB, 0xCC, 0xDE, 0x02}; // home mac
byte mac[] = {0x90, 0xA2, 0xDA, 0x10, 0x02, 0x0B}; // school mac
//IPAddress iotIP (192, 168, 0, 105); // home ip address
//IPAddress iotIP (10, 1, 74, 5); // school ip?

#define AIO_SERVER "io.adafruit.com"
#define AIO_SERVERPORT 1883
#define AIO_USERNAME "edwward"
#define AIO_KEY "aio_Rgmw87fzyaUj4rX2qVDL5s9yhEDL"

EthernetClient client;

Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME, AIO_KEY);

Adafruit_MQTT_Publish temp = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/enviromon.temperature");
Adafruit_MQTT_Publish humidity = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/enviromon.humidity");
Adafruit_MQTT_Publish battery = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/enviromon.battery");

// sample variables
uint8_t sampleid;
uint8_t year, month, day, hour, minute, second;
uint32_t temperature_value, humidity_value, battery_value;

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

  // check for init
  while (!rf95.init()) {
    Serial.println("radio init failed :(");
    while (1);
  }
  Serial.println("radio init success!");

  // set frequency
  if (!rf95.setFrequency(RF95_FREQ)) {
    Serial.println("cannot set frequency");
    while (1);
  }
  Serial.print("frequency set to: "); Serial.println(RF95_FREQ);

  // set to receive all frames
  rf95.setPromiscuous(true);

  Serial.println("aaaaaaaaaaaaaa");

  // init ethernet
  Ethernet.begin(mac);
  delay(1000);

  // print ip address
  Serial.println(Ethernet.localIP());
}

// main program loop
void loop() {
  rx_recv_len = sizeof(rx_buf);

  if (rf95.available()) {
    if (rf95.recv(rx_buf, &rx_recv_len)) {
      char is_ack[4] = {""};
      if (rf95.headerFlags() & RH_FLAGS_ACK) {
        memcpy(is_ack, "Ack\0", 3);
      }
      rx_buf[rx_recv_len] = '\0';

      Serial.println();

      snprintf(print_buf, sizeof(print_buf), "msg: %s \r", rx_buf);
      Serial.println(print_buf);

      // process and send data
      process_data(rx_buf);
    }
    
  }
  // uncomment if spamming
  delay(1500);
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

  Serial.println("mqtt connected!");
}

// publish temperature
void MQTT_publish_temperature() {
  // ensure connection to mqtt server
  MQTT_connect();

  // try to send temp
  Serial.println("sending temp...");
  if (!temp.publish(temperature_value)) {
    Serial.println("temp failed!");
  } else {
    Serial.println("temp sent!");
  }

  // ping server to keep connection alive
  if(!mqtt.ping()) {
    mqtt.disconnect();
  }
}

// publish humidity
void MQTT_publish_humidity() {
  // ensure connection to mqtt server
  MQTT_connect();

  // try to send humidity
  Serial.println("sending humidity...");
  if (!humidity.publish(humidity_value)) {
    Serial.println("humidity failed!");
  } else {
    Serial.println("humidity sent!");
  }

  // ping server to keep connection alive
  if(!mqtt.ping()) {
    mqtt.disconnect();
  }
}

// publish battery
void MQTT_publish_battery() {
  // ensure connection to mqtt server
  MQTT_connect();

  // try to send temp
  Serial.println("sending battery...");
  if (!battery.publish(battery_value)) {
    Serial.println("battery failed!");
  } else {
    Serial.println("battery sent!");
  }

  // ping server to keep connection alive
  if(!mqtt.ping()) {
    mqtt.disconnect();
  }
}

// process received data
void process_data(uint8_t data[]) {
  year = data[5];
  month = data[6];
  day = data[7];
  hour = data[8];
  minute = data[9];

  for (int i = 0; i < 12; i++) {
    Serial.println(data[i]);
  }

  switch (data[4]) {
    case 1: // temp id = 0
      temperature_value = data[11];
      Serial.println(temperature_value);
      MQTT_publish_temperature();
    break;
    case 2: // humidity id = 1
      humidity_value = data[11];
      MQTT_publish_humidity();
    break;
    case 3: // vbat id = 2
      battery_value = data[11];
      MQTT_publish_battery();
    break;
    default:
      Serial.println("invalid data!");
  }
}