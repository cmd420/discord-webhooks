#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include "DiscordWebhook.h"

#define SSID "<your ssid>"
#define PASS "<your pass>"
#define DISCORD_WEBHOOK_URL "<your discord webhook url>"

ESP8266WiFiMulti wifi_multi;

DiscordWebhook discord_webhook;
const size_t NUMBER_OF_EMBEDS = 3;
DiscordEmbed embeds[NUMBER_OF_EMBEDS];

bool success = false;

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
    
    for(size_t i = 0; i < NUMBER_OF_EMBEDS; ++i)
        embeds[i].setTitle(String(i));

}

void loop()
{
    if(success)
        return;

    // NOTE: for some reason calling send in setup while sending 
    // multiple embeds doesn't work. No idea if this problem happens
    // only with me.
    success = discord_webhook.send(embeds, NUMBER_OF_EMBEDS);
    Serial.printf("Sending webhook %s\n", success ? "succeeded!" : "failed.");
    delay(15000);
}