#include <Arduino.h>
#include <ArduinoJson.h>

#include "config.h"
#include "common.h"
#include "wifi_common.h"

const int M1 = A0;
const int BUFFER_SIZE_SEND = JSON_OBJECT_SIZE(10);

void setup() {
  Serial.begin(9600);

  setup_wifi();

  client.setServer(MQTT_SERVER, 1883);

  setupOTA();
}

void loop() {

  if (!client.connected()){
    delay(1);
    Serial.println("Attempting MQTT connection...");
    reconnect_mqtt();
    return;
  }

  if (WiFi.status() != WL_CONNECTED){
    delay(1);
    Serial.println("Attempting WIFI connection...");
    setup_wifi();
    return;
  }

  // Process MQTT tasks
  client.loop();

  // Handle OTA
  ArduinoOTA.handle();

  // only send state every 1 second
  delay(1000);

  // gather data
  StaticJsonBuffer<BUFFER_SIZE_SEND> jsonBuffer;
  JsonObject &object = jsonBuffer.createObject();
  JsonObject &sub_json = object.createNestedObject("sub_json");
  sub_json["name"] = 'M1';
  sub_json["moisture"] = 'M1';

  // send data
  sendState(object);
}