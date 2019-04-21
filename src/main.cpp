#include <Arduino.h>
#include <ArduinoJson.h>

#include "config.h"
#include "common.h"
#include "wifi_common.h"

const int M1 = A0;

void setup() {
  Serial.begin(9600);
  setup_wifi();
  client.setServer(MQTT_SERVER, 1883);
  setupOTA();

  pinMode(D5, OUTPUT);
  pinMode(D0, OUTPUT);
  pinMode(D2, OUTPUT);
  pinMode(D1, OUTPUT);

  digitalWrite(D5, LOW);
  digitalWrite(D0, LOW);
  digitalWrite(D2, LOW);
  digitalWrite(D1, LOW);
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

  client.loop();
  ArduinoOTA.handle();

  delay(1000);
  sendState();
}