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

enum DiscordWebhookType {
    INCOMING = 1,
    CHANNEL_FOLLOWER,
    APPLICATION
};

class DiscordEmbed;

class DiscordWebhook {
private:
    String m_webhook_url;
    bool m_is_valid;
public:
    void begin(const String &url);
    bool get();
    bool send(const String &text);
    bool send(const String &text, const bool& tts);
    bool send(const DiscordEmbed &embed);
    bool send(const String &text, const DiscordEmbed &embed);

    bool &isValid();

    int type;
    String id;
    String name;
    String avatar;
    String channel_id;
    String guild_id;
    String application_id;
    String token;

private:
    bool checkWiFi();
    bool post(DynamicJsonDocument &json);
};