#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>

#include "wifi_common.h"
#include "config.h"
#include "common.h"

const int BUFFER_SIZE_SEND = JSON_OBJECT_SIZE(10);

void setupOTA(){
    ArduinoOTA.setPort(OTA_PORT);
    ArduinoOTA.setHostname(HOSTNAME);

    ArduinoOTA.onStart([]() { Serial.println("Starting"); });
    ArduinoOTA.onEnd([]() { Serial.println("\nEnd"); });
    ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
        Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
    });

    ArduinoOTA.onError([](ota_error_t error) {
        Serial.printf("Error[%u]: ", error);
        if (error == OTA_AUTH_ERROR){
            Serial.println("Auth Failed");
        }else if (error == OTA_BEGIN_ERROR){
            Serial.println("Begin Failed");
        }else if (error == OTA_CONNECT_ERROR){
            Serial.println("Connect Failed");
        }else if (error == OTA_RECEIVE_ERROR){
            Serial.println("Receive Failed");
        }else if (error == OTA_END_ERROR){
            Serial.println("End Failed");
        }
    });
    ArduinoOTA.begin();
}

void setup_wifi(){

    delay(10);
    // We start by connecting to a WiFi network
    Serial.println();
    Serial.print("Connecting to ");
    Serial.println(MY_SSID);

    WiFi.mode(WIFI_STA);
    WiFi.begin(MY_SSID, MY_PASSWORD);

    while (WiFi.status() != WL_CONNECTED){
        delay(500);
        Serial.print(".");
    }

    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
}

void reconnect_mqtt(){
    // Loop until we're reconnected
    while (!client.connected()){

        // Attempt to connect
        if (client.connect(HOSTNAME, mqtt_username, mqtt_password)) {
            Serial.println("connected");
        } else {
            Serial.print("failed, rc=");
            Serial.print(client.state());
            Serial.println(" try again in 5 seconds");
            // Wait 5 seconds before retrying
            delay(5000);
        }
    }
}

void sendState(){
    
    // gather data
    StaticJsonBuffer<BUFFER_SIZE_SEND> jsonBuffer;
    JsonObject &object = jsonBuffer.createObject();

    digitalWrite(D5, LOW);
    digitalWrite(D0, LOW);
    digitalWrite(D2, LOW);
    digitalWrite(D1, HIGH);
    object["moisture_m1"] = analogRead(A0);
    delay(1000);

    digitalWrite(D5, HIGH);
    digitalWrite(D0, LOW);
    digitalWrite(D2, LOW);
    digitalWrite(D1, HIGH);
    object["moisture_m2"] = analogRead(A0);
    delay(1000);

    digitalWrite(D5, LOW);
    digitalWrite(D0, HIGH);
    digitalWrite(D2, LOW);
    digitalWrite(D1, HIGH);
    object["moisture_m3"] = analogRead(A0);
    delay(1000);

    // digitalWrite(D5, HIGH);
    // digitalWrite(D0, HIGH);
    // digitalWrite(D2, LOW);
    // digitalWrite(D1, HIGH);
    // object["moisture_m4"] = analogRead(A0);
    // delay(1000);

    char buffer[object.measureLength() + 1];
    object.printTo(buffer, sizeof(buffer));
    object.printTo(Serial);
    Serial.println("");
    client.publish(STATE_TOPIC, buffer, true);
}
