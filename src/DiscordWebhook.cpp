#include "DiscordWebhook.h"

void DiscordWebhook::begin(const String &url)
{
    this->m_webhook_url = url;
    this->m_is_valid = this->get();
}

bool DiscordWebhook::get()
{
    if (!this->checkWiFi() || this->m_is_valid)
        return false;

    WiFiClientSecure client;
    client.setInsecure();

    HTTPClient https;
    if (https.begin(client, this->m_webhook_url))
    {
        const int status_code = https.GET();
        if (status_code != 200)
            return false;

        const String &response = https.getString();
        DynamicJsonDocument doc(1024);
        if (deserializeJson(doc, response) != DeserializationError::Ok)
            return false;

        this->type = doc["type"];
        this->id = doc["id"].as<String>();
        this->name = doc["name"].as<String>();
        this->avatar = doc["avatar"].as<String>();
        this->channel_id = doc["channel_id"].as<String>();
        this->guild_id = doc["guild_id"].as<String>();
        this->application_id = doc["application_id"].as<String>();
        this->token = doc["token"].as<String>();

        this->m_is_valid = true;
        return true;
    }

    return false;
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

bool DiscordWebhook::send(const String &text, const bool &tts)
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

bool DiscordWebhook::send(const DiscordEmbed *embeds, const size_t &size) {
    if (!this->checkWiFi())
        return false;

    DynamicJsonDocument json(4096);
    JsonArray embeds_arr = json.createNestedArray("embeds");
    for(size_t i = 0; i < size; ++i)
        embeds_arr.add(embeds[i].m_json);

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

bool &DiscordWebhook::isValid()
{
    return this->m_is_valid;
}

bool DiscordWebhook::checkWiFi()
{
    return WiFi.status() == WL_CONNECTED;
}

bool DiscordWebhook::post(DynamicJsonDocument &json)
{
    WiFiClientSecure client;
    client.setInsecure();

    HTTPClient https;
    if (https.begin(client, this->m_webhook_url))
    {
        https.addHeader("Content-Type", "application/json");

        String payload;
        serializeJson(json, payload);
        int status_code = https.POST(payload);
        
        https.end();
        return status_code == 204;
    }

    return false;
}