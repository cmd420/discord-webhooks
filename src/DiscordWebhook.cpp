#include "DiscordWebhook.h"

void DiscordWebhook::begin(const String &url)
{
    this->m_webhook_url = url;
}

bool DiscordWebhook::send(const String &text)
{
    if (!this->checkWiFi())
        return false;

    if (text.length() > 2000)
        return false;

    DynamicJsonDocument json(2048);
    json["content"] = text;

    return this->post(json);
}

bool DiscordWebhook::send(const String &text, const bool& tts)
{
    if (!this->checkWiFi())
        return false;

    if (text.length() > 2000)
        return false;

    DynamicJsonDocument json(2048);
    json["content"] = text;
    json["tts"] = tts;

    return this->post(json);
}

bool DiscordWebhook::send(const DiscordEmbed &embed)
{
    if (!this->checkWiFi())
        return false;

    DynamicJsonDocument json(4096);
    JsonArray embeds_arr = json.createNestedArray("embeds");
    embeds_arr.add(embed.m_json);

    return this->post(json);
}

bool DiscordWebhook::send(const String &text, const DiscordEmbed &embed)
{
    if (!this->checkWiFi())
        return false;

    DynamicJsonDocument json(4096);
    json["content"] = text;
    JsonArray embeds_arr = json.createNestedArray("embeds");
    embeds_arr.add(embed.m_json);

    return this->post(json);
}

bool DiscordWebhook::checkWiFi()
{
    return WiFi.status() == WL_CONNECTED;
}

bool DiscordWebhook::post(DynamicJsonDocument &json) {
    WiFiClientSecure client;
    client.setInsecure();

    HTTPClient https;
    if (https.begin(client, this->m_webhook_url))
    {
        https.addHeader("Content-Type", "application/json");

        String payload;
        serializeJson(json, payload);
        int status_code = https.POST(payload);

        return status_code == 204;
    }

    return false;
}