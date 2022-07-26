#pragma once

#ifndef ESP8266
#error This library is made for ESP8266
#endif

#include <ArduinoJson.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClientSecure.h>
#include "DiscordEmbed.h"

class DiscordEmbed;

class DiscordWebhook {
private:
    String m_webhook_url;
public:
    void begin(const String &url);
    bool send(const String &text);
    bool send(const String &text, const bool& tts);
    bool send(const DiscordEmbed &embed);
    bool send(const String &text, const DiscordEmbed &embed);

private:
    bool checkWiFi();
    bool post(DynamicJsonDocument &json);
};