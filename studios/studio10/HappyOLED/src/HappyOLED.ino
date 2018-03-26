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
