# Discord Webhooks
A simple to use Discord webhooks wrapper made using Arduino C

## Library progress

- [x] Basic implementation
- [ ] Simple docs
- [ ] Send multiple embeds
- [ ] General optimization

## Use cases
- An easy notification system for IoT projects:

<br>

![notification](./images/wh_notifier.png "Simple Notifier")

- An easy way of sharing data with a community:

<br>

![data](./images/wh_share_data.png "Simple Data")

<hr/>

## Getting started

- Download and install the library
- Create a webhook:

    ### 1. Go to server settings > Integrations
    
    <br>

    ![server settings](./images/gs_server_settings.png "Server Settings")

    ### 2. Click on "Create Webhook"
    
    <br>
    
    ![create webhook](./images/gs_integrations_create_webhook.png "Create Webhook")

    ### 3. Customize your webhook and click on "Save Changes"
    
    <br>
    
    ![save changes](./images/gs_save_changes.png "Save Changes")

    ### 4. Copy your Webhook URL
    
    <br>
    
    ![copy url](./images/gs_copy_url.png "Copy Webhook URL")

- Now that you have your webhook URL, start coding!

<hr/>

## Examples
- ### Basic example:
    Include the needed libraries
    ```cpp
    #include <ESP8266WiFi.h>
    #include <ESP8266WiFiMulti.h>
    #include "DiscordWebhook.h"
    ```

    Set your credentails
    ```cpp
    #define SSID "<your ssid>"
    #define PASS "<your password>"
    #define DISCORD_WEBHOOK_URL "<your discord webhook url>"
    ```

    Define your variables and connect to WiFi
    ```cpp
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
    ```

    Run setup
    ```cpp
    void setup()
    {
        Serial.begin(115200);
        connect_to_wifi();

        discord_webhook.begin(DISCORD_WEBHOOK_URL);
    ...
    ```

    Start sending webhooks
    ```cpp
        bool success = discord_webhook.send("Hello World!");

        Serial.printf("Sending webhook %s\n", success ? "succeeded!" : "failed.");
    } // end of setup
    ```

    Full code:
    ```cpp
    #include <ESP8266WiFi.h>
    #include <ESP8266WiFiMulti.h>
    #include "DiscordWebhook.h"

    #define SSID "<your ssid>"
    #define PASS "<your password>"
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
        bool success = discord_webhook.send("Hello World!");

        Serial.printf("Sending webhook %s\n", success ? "succeeded!" : "failed.");
    }

    void loop()
    {
    }
    ```

- ### Using Embeds
    ```cpp
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
    ```
    #### or send an embed with a message
    ```cpp
        bool success = discord_webhook.send("Hey @everyone, check out the forecast!", embed);

        Serial.printf("Sending webhook %s\n", success ? "succeeded!" : "failed.");
    }
    ```

<hr/>

## Docs
- ### DiscordEmbed
    ```cpp
    //example
    DiscordEmbed embed;
    ```

    #### Variables:
    - 
        ```cpp
        static const size_t embed_size = 4096;
        ```
        Determines the `DynamicJsonDocument` size which is a member variable used to store all json data related to the embed you're currently creating.
        
        **NOTE:** Discord embeds have predetermined limits and the default embed size in the program is way less than the limits (for memory purposes). You can find the embed limits [here](https://discord.com/developers/docs/resources/channel#embed-object-embed-limits).

    #### Methods:

    - 
        ```cpp
        DiscordEmbed *setTitle(const String &title)
        ```
        ```cpp
        const String embed_title = "Door Alarm";
        embed.setTitle(embed_title);
        ```
        Sets the embed title.
        
        params:

        - `title`: the embed title, ofc

        returns:

        - a pointer to the current object

    <br>

    - 
        ```cpp
        DiscordEmbed *setTitle(const String &title, const String &url)
        ```
        ```cpp
        const String embed_title = "Door Alarm";
        const String embed_url   = "https://my-website.com/door-alarm/status";

        embed.setTitle(embed_title, embed_url);
        ```
        Sets the embed title with url, hence making it a redirectable title link. For example:
        
        *(pretend this is an embed)*
        
        | [Door Alarm](https://my-website.com/door-alarm/status)|
        | ------------------|
        | embed description |
        | some embed fields |

        params:

        - `title`: the embed title

        - `url`: redirect url

        returns:

        - a pointer to the current object
    
    <br>

    -
        ```cpp
        DiscordEmbed *setDescription(const String &description)
        ```
        ```cpp
        //example
        const String embed_desc = "Alarm didn't get triggered in the past 3 hours";
        embed.setDescription(embed_desc)'
        ```
        Sets the embed description, the thing below the title.

        params:
        
        - `description`: whatever text you want to put here, but make sure it doesn't exceed `4096` characters. (You may have to edit the embed size)

        returns:

        - a pointer to the current object

    <br>

    -
        ```cpp
        DiscordEmbed *setColor(const int &color)
        ```
        ```cpp
        //example
        const int embed_color = 0xFFFF00;
        embed.setColor(embed_color);
        ```
        Sets the embed accent color.

        params:

        - `color`: embed accent color in hex

        returns:

        - a pointer to the current object

    <br>

    -
        ```cpp
        DiscordEmbed *setImage(const String &image_url)
        ```
        ```cpp
        //example
        const String embed_image = "https://picsum.photos/300/200";
        embed.setImage(embed_image);
        ```
        Sets the embed image url.

        params:

        - `image_url`: self explanatory, I guess?

        returns:

        - a pointer to the current object

    <br>

    - 
        ```cpp
        DiscordEmbed *setImage(const EmbedImage &embed_image)
        ```
        ```cpp
        //example
        EmbedImage embed_image;
        embed_image.url = "https://picsum.photos/300/200";
        embed_image.height = 100;
        embed_image.width = 150;

        embed.setImage(embed_image);
        ```
        Sets the embed image.

        params:

        - `embed_image`: an `EmbedImage` instance

        returns:

        - a pointer to the current object

    <br>

    -
        ```cpp
        DiscordEmbed *setAuthor(const EmbedAuthor & author)
        ```
        ```cpp
        //example
        EmbedAuthor author;
        author.name = "slacker";
        author.icon_url = "https://cdn.discordapp.com/avatars/738274800211984426/57b3da0b4df7cfbb616ef63941dd984d.webp";

        embed.setAuthor(author);
        ```
        Sets the embed author.

        params:

        - `author`: an `EmbedAuthor` instance

        returns:

        - a pointer to the current object

    <br>

    -
        ```cpp
        DiscordEmbed *setFooter(const EmbedFooter &footer)
        ```
        ```cpp
        //example
        EmbedFooter footer;
        footer.text = "footer text";

        embed.setFooter(footer);
        ```
        Sets the embed footer.

        params:

        - `footer`: an `EmbedFooter` instance

        returns:

        - a pointer to the current object

    <br>

    -
        ```cpp
        DiscordEmbed *setFooter(const String &text)
        ```
        ```cpp
        //example
        embed.setFooter("my footer text");
        ```
        Sets the embed footer text.

        params:

        - `text`: again, self explanatory

        returns:

        - a pointer to the current object

    <br>

    -
        ```cpp
        DiscordEmbed *addField(const EmbedField &field)
        ```
        ```cpp
        //example
        EmbedField field;
        field.name = "Status";
        field.value = "working 🟢";
        field.is_inline = false;
        
        embed.addField(field);
        ```
        Adds a field to the embed.

        params:

        - `field`: an `EmbedField` instance

        returns:

        - a pointer to the current object

    <br>

    -
        ```cpp
        DiscordEmbed *addField(const String &name, const String &value, cont bool &is_inline)
        ```
        ```cpp
        //example
        const String field_name = "Battery";
        const String field_value = "low 🔴";
        const bool field_is_inline = true;

        embed.addField(field_name, field_value, field_is_inline);
        ```
        Adds a field to the embed.

        params:

        - `name`: embed name (title)
        - `value`: embed value (content)
        - `is_inline`: `true` or `false` if the field is inline

        returns:

        - a pointer to the current object

    <br>

    -
        ```cpp
        String toString(bool pretty)
        ```
        ```cpp
        embed.setTitle("My Embed Title")
            ->setDescription("My embed description")
            ->setFooter("my footer text")
            ->setColor(0x333333);

        String my_embed = embed.toString(false);
        String my_pretty_embed = embed.toString(true);

        Serial.println(my_embed);
        Serial.println(my_pretty_embed);
        ```
        non-prettified
        ```
        {"title":"My Embed Title","description":"My embed description","footer":{"text":"my footer text"},"color":3355443}
        ```
        prettified
        ```
        {
            "title": "My Embed Title",
            "description": "My embed description",
            "footer": {
                "text": "my footer text"
        },
            "color": 3355443
        }
        ```

    <br>

    -
        ```cpp
        static int rgbToHex(const int &red, const int &green, const int &blue)
        ```
        ```cpp
        embed.setColor(DiscordEmbed::rgbToHex(151, 250, 148));
        ```
        Converts RGB value to HEX.

        params:

        - `red`: red color value
        - `green`: green color value
        - `blue`: blue color value

        returns:

        - HEX value of the given RGB
    
    <br>

<hr>

- ### DiscordWebhook

    ```cpp
    // example
    DiscordWebhook discord_webhook;
    ```

    #### Methods:
    - 
        ```cpp
        void begin(const String &url)
        ``` 
        ```cpp
        //example
        const String WEBHOOK_URL = "https://discord.com/api/webhooks/<webhook id>/<webhook token>";
        discord_webhook.begin(WEBHOOK_URL);
        ```
        Stores your webhook url for later use.

        params:

        - `url`: discord webhook URL

        returns:

        - nothing   
    
    <br/>

    - 
        ```cpp
        bool send(const String &text)
        ```
        ```cpp
        //example
        discord_webhook.send("Hello world!");
        ```
        Sends a POST request to the webhook url.

        params:

        - `text`: discord message content

        returns:

        - `true` if response status code == 204 else `false`

    <br/>

    - 
        ```cpp
        bool send(const String &text, const bool &tts)
        ```
        params:

        - `text`: discord message content
        - `tts`: `true` or `false` if the message is text to speech  

        returns:

        - `true` if response status code == 204 else `false`

    <br/>

    - 
        ```cpp
        bool send(const DiscordEmbed &embed)
        ```
        ```cpp
        //example
        DiscordEmbed embed;
        embed.setTitle("Sensor Readings")
            ->addField("10:00", "low - 23℃, high - 25℃", false)
            ->addField("11:00", "low - 24.7℃, high - 27℃", false)
            ->setColor(DiscordEmbed::rgbToHex(255, 255, 255));
        
        discord_webhook.send(embed);
        ```

        Send discord embed.

        params:

        - `embed`: a `DiscordEmbed` instance as the message embed

        returns:

        - `true` if response status code == 204 else `false`

    <br/>

    - 
        ```cpp
        bool send(const String &text, const DiscordEmbed &embed)
        ```
        ```cpp
        //example
        String content = "Reading from sensor every `1 hour`";
        DiscordEmbed embed;
        embed.setTitle("Sensor Readings")
            ->addField("10:00", "low - 23℃, high - 25℃", false)
            ->addField("11:00", "low - 24.7℃, high - 27℃", false)
            ->setColor(DiscordEmbed::rgbToHex(255, 255, 255));
        
        discord_webhook.send(content, embed);
        ```

        Send an embed with text above it as the message content.
        
        params:

        - `text`: discord message content
        - `embed`: a `DiscordEmbed` instance as the message embed

        returns:

        - `true` if response status code == 204 else `false`
