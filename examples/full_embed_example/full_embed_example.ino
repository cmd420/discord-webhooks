#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include "DiscordWebhook.h"

#define SSID "<your ssid>"
#define PASS "<your pass>"
#define DISCORD_WEBHOOK_URL "<your discord webhook url>"

ESP8266WiFiMulti wifi_multi;
DiscordWebhook discord_webhook;
DiscordEmbed embed;

void connect_to_wifi()
{
    WiFi.mode(WIFI_STA);
    wifi_multi.addAP(SSID, PASS);

    Serial.printf("Connecting to %s\n", SSID);
    while (wifi_multi.run() != WL_CONNECTED)
        delay(50);
    Serial.println("Connected to WiFi");
}

void setup()
{
    Serial.begin(115200);
    connect_to_wifi();

    discord_webhook.begin(DISCORD_WEBHOOK_URL);

    // Author
    EmbedAuthor author;
    author.name = "slacker"; // my username lmao;
    author.icon_url = "https://cdn.discordapp.com/avatars/738274800211984426/57b3da0b4df7cfbb616ef63941dd984d.webp";

    // Field
    EmbedField field1;
    field1.name = "8:00";
    field1.value = "Rainy 🌧";
    field1.is_inline = true;

    // Image
    EmbedImage image;
    // couldn't think of something else to put here
    image.url = "https://opengraph.githubassets.com/361b23d6a4805ab67d808dda456c38270b5dc055f770c21129e04d2075e2ff0d/ahmedo-o/discord-webhooks";

    // Footer
    EmbedFooter footer;
    footer.text = "Watch out for a possible snowfall";
    footer.icon_url = "https://cdn.iconscout.com/icon/free/png-256/snowfall-203-1123570.png";

    embed.setTitle("Weather Forecast")
        .setColor(DiscordEmbed::rgbToHex(225, 232, 237))
        .addField("Now", "Clear 🌙", false)
        .addField("6:00", "Sunny ☀", true)
        .addField("7:00", "Cloudy ☁", true)
        .addField(field1)
        .setImage(image)
        .setFooter(footer);

    bool success = discord_webhook.send(embed);

    Serial.printf("Sending webhook %s\n", success ? "succeeded!" : "failed.");
}

void loop()
{
}