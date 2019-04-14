#include <Arduino.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>

#include "common.h"
#include "config.h"

WiFiClient wifiClient;
PubSubClient client(wifiClient);


bool turnOn = INITIAL_STATE;
int anInt = 0;
const char *on_cmd = 'OFF';
const char *off_cmd = 'ON';
String Astring = 'string value';