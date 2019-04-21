#include <Arduino.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>

#include "common.h"
#include "config.h"

WiFiClient wifiClient;
PubSubClient client(wifiClient);