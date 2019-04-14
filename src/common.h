#ifndef COMMON_GUARD
#define COMMON_GUARD

#include <Arduino.h>
#include <ArduinoOTA.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>

#include "config.h"

extern PubSubClient client;

extern bool turnOn;
extern int anInt;
extern const char *on_cmd;
extern const char *off_cmd;
extern String Astring;

#endif