#pragma once

#include <ArduinoJson.h>
#include "DiscordWebhook.h"

struct EmbedAuthor
{
    String name;
    String url;
    String icon_url;
};

struct EmbedFooter
{
    String text;
    String icon_url;
};

struct EmbedField
{
    String name;
    String value;
    bool is_inline;
};

struct EmbedImage
{
    String url;
    String proxy_url;
    unsigned int height;
    unsigned int width;
};

class DiscordEmbed
{
private:
    DynamicJsonDocument m_json = DynamicJsonDocument(DiscordEmbed::embed_size);

public:
    friend class DiscordWebhook;
    DiscordEmbed *setTitle(const String &title);
    DiscordEmbed *setTitle(const String &title, const String &url);
    DiscordEmbed *setDescription(const String &description);
    DiscordEmbed *setColor(const int &color);
    DiscordEmbed *setImage(const String &image_url);
    DiscordEmbed *setImage(const EmbedImage &embed_image);
    DiscordEmbed *setAuthor(const EmbedAuthor &author);
    DiscordEmbed *setFooter(const EmbedFooter &footer);
    DiscordEmbed *setFooter(const String &text);
    DiscordEmbed *addField(const EmbedField &field);
    DiscordEmbed *addField(const String &name, const String &value, const bool &is_inline);
    String toString(bool pretty);
    static const size_t embed_size = 4096;
    static int rgbToHex(const int &red, const int &green, const int &blue);
};
