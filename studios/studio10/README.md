# Studio Questions / Replies

***Q1.1. How often does the schedule update and what "starts" the process of updating the displayed data?***
The schedule updates every minute. The update starts when the nextbus webhook comes in. This is parsed by the gotnextbusdata fucntion.

***Q1.2. What is the full URL used for the WebHook (to get bus 2115's arrival at the Lincoln Memorial)?***

[This](http://webservices.nextbus.com/service/publicXMLFeed?command=predictions&a=dc-circulator&r=mall&s=lincmemo)

***Q1.3. Provide a sequence diagram that shows the complete process used to get data from the NextBus service.  Actors (timelines) should include the Photon (use [websequencediagrams](https://www.websequencediagrams.com/). Be sure to include messages being exchanged by the event names.***

```
# Complete Code Below:
title Update Sequence
participant Photon
participant Particle.io
participant NextBus

Photon -> Particle.io: "get_nextbus"
Particle.io -> NextBus: get the data for next bus
NextBus -> Particle.io: send back data for next bus

Particle.io -> Photon : hook-response/get_nextbus/0


```

***Q2.1. Subscribing to just `events` is sometimes called the firehose.  Explain what data you are seeing and why it may be given this nickname.***

Subscribing to events gives you all possible information. It's called the firehose because this information is raw and unparsed and a lot of it does not pertain to what you need.


***Q2.2. The `get_nextbus` events seem to end with numbers (like `/0`, `/1`, etc.).  Why?***

The hook responses contain different information. These are split into objects and we differentiate these objects with number endings.

***Q2.3.  Paste the entire response, including headers here:***

```
# Full Result Here:
HEADERS
Access-Control-Allow-Origin: *

Connection: keep-alive

Content-Length: 11

Content-Type: application/json; charset=utf-8

Date: Mon, 26 Mar 2018 20:25:30 GMT

Server: nginx

X-Request-Id: 05e95b98-6d56-4f93-94da-d8974e5e809d

BODY
{
"ok": true
}
```

***Q3. Paste the code for your solution here:***

```
// Code here
#include "Adafruit_SSD1306/Adafruit_SSD1306.h"
// use hardware SPI
#define OLED_DC     D3
#define OLED_CS     D4
#define OLED_RESET  D5
Adafruit_SSD1306 display(OLED_DC, OLED_RESET, OLED_CS);

/*
#define	BLACK           0x0000
#define	BLUE            0x001F
#define	RED             0xF800
#define	GREEN           0x07E0
#define CYAN            0x07FF
#define MAGENTA         0xF81F
#define YELLOW          0xFFE0
#define WHITE           0xFFFF
*/

// variables for scrolling code
int  x, minX;

void setup()   {
    Serial.begin(9600);
    // initializes the interface to the LCD screen
    // uses Adafruit code!
    display.begin(SSD1306_SWITCHCAPVCC);
    // set text formatting
    display.setTextSize(5);
    display.setTextColor(WHITE);
}

void loop() {
    display.clearDisplay();
    display.setCursor(0, 32); // coordinates
    display.fillCircle(64, 42, 16, WHITE);
    display.fillRect(0, 0, 128, 42, BLACK);
    display.drawCircle(display.width()/2, display.height()/2, display.height()/2, WHITE);
    display.drawCircle(54, 23, 4, WHITE);
    display.drawCircle(72, 23, 4, WHITE);
    display.display();
    delay(500);
}
```
