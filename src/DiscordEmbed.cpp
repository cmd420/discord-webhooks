#include "DiscordEmbed.h"

DiscordEmbed *DiscordEmbed::setTitle(const String &title)
{
    this->m_json["title"] = title;

    return this;
}

DiscordEmbed *DiscordEmbed::setTitle(const String &title, const String &url)
{
    this->m_json["title"] = title;
    this->m_json["url"] = url;

    return this;
}

DiscordEmbed *DiscordEmbed::setDescription(const String &description)
{
    this->m_json["description"] = description;

    return this;
}

DiscordEmbed *DiscordEmbed::setColor(const int &color)
{
    this->m_json["color"] = color;

    return this;
}

DiscordEmbed *DiscordEmbed::setImage(const String &image_url)
{
    this->m_json["image"]["url"] = image_url;

    return this;
}

DiscordEmbed *DiscordEmbed::setImage(const EmbedImage &embed_image)
{
    if (!embed_image.url.isEmpty())
        this->m_json["image"]["url"] = embed_image.url;
    if (!embed_image.proxy_url.isEmpty())
        this->m_json["image"]["proxy_url"] = embed_image.proxy_url;
    if (embed_image.height)
        this->m_json["image"]["height"] = embed_image.height;
    if (embed_image.width)
        this->m_json["image"]["width"] = embed_image.width;

    return this;
}

DiscordEmbed *DiscordEmbed::setAuthor(const EmbedAuthor &author)
{
    if (!author.name.isEmpty())
        this->m_json["author"]["name"] = author.name;
    if (!author.url.isEmpty())
        this->m_json["author"]["url"] = author.url;
    if (!author.icon_url.isEmpty())
        this->m_json["author"]["icon_url"] = author.icon_url;

    return this;
}

DiscordEmbed *DiscordEmbed::setFooter(const EmbedFooter &footer)
{
    if (!footer.text.isEmpty())
        this->m_json["footer"]["text"] = footer.text;
    if (!footer.icon_url.isEmpty())
        this->m_json["footer"]["icon_url"] = footer.icon_url;

    return this;
}

DiscordEmbed *DiscordEmbed::setFooter(const String &text)
{
    if(this->m_json["footer"].containsKey("icon_url"))
        this->m_json["footer"].remove("icon_url");
        
    this->m_json["footer"]["text"] = text;

    return this;
}

DiscordEmbed *DiscordEmbed::addField(const EmbedField &field)
{
    if (!this->m_json["fields"])
    {
        this->m_json.createNestedArray("fields");
    }

    JsonArray field_arr = this->m_json["fields"].as<JsonArray>();
    JsonObject new_field = field_arr.createNestedObject();

    new_field["name"] = field.name;
    new_field["value"] = field.value;
    new_field["inline"] = field.is_inline;

    return this;
}

DiscordEmbed *DiscordEmbed::addField(const String &name, const String &value, const bool &is_inline)
{
    EmbedField field;
    field.name = name;
    field.value = value;
    field.is_inline = is_inline;

    return this->addField(field);
}

int DiscordEmbed::rgbToHex(const int &red, const int &green, const int &blue)
{
    return ((red << 16) | (green << 8) | (blue << 0));
}

String DiscordEmbed::toString(bool pretty)
{
    String stringified;

    if (pretty)
        serializeJsonPretty(this->m_json, stringified);
    else
        serializeJson(this->m_json, stringified);

    return stringified;
}