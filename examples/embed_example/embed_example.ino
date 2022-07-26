#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include "DiscordWebhook.h"

#define SSID "<your ssid>"
#define PASS "<your pass>"
#define DISCORD_WEBHOOK_URL "<your discord webhook url>"

ESP8266WiFiMulti wifi_multi;
DiscordWebhook discord_webhook;

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

    DiscordEmbed embed;
    embed.setTitle("Weather Forecast")
        ->setColor(DiscordEmbed::rgbToHex(225, 232, 237))
        ->addField("Now", "Clear 🌙", false)
        ->addField("6:00", "Sunny ☀", true)
        ->addField("7:00", "Cloudy ☁", true);

    EmbedField field1;
    field1.name = "8:00";
    field1.value = "Rainy 🌧";
    field1.is_inline = true;

    embed.addField(field1);

    EmbedFooter footer;
    footer.text = "Watch out for a possible snowfall";

    embed.setFooter(footer);

    bool success = discord_webhook.send(embed);
    // or send an embed with a message!
    // bool success = discord_webhook.send("Hey @everyone, check out the forecast!", embed);

    Serial.printf("Sending webhook %s\n", success ? "succeeded!" : "failed.");
}

void loop()
{
}