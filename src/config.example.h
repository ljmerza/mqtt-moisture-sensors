#ifndef CONFIG_GUARD 
#define CONFIG_GUARD

#include <Arduino.h>
#include <ArduinoOTA.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>

#define STATE_TOPIC "moisture/bedroom"

#define HOSTNAME "esp8266-moistures"
#define MY_SSID ""
#define MY_PASSWORD ""
#define MQTT_SERVER ""
#define mqtt_username ""
#define mqtt_password ""

#define INITIAL_STATE false
#define OTA_PORT 8266

#endif