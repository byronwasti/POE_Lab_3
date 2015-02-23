#include <Adafruit_GFX.h>
#include <Adafruit_TFTLCD.h>
#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include <TouchScreen.h>

#define LCD_CS A3
#define LCD_CD A2
#define LCD_WR A1
#define LCD_RD A0

#define LCD_RESET A4

#define YP A3
#define XM A2
#define YM 9
#define XP 8

#define TS_MINX 150
#define TS_MINY 120
#define TS_MAXX 920
#define TS_MAXY 940

TouchScreen ts = TouchScreen(XP,YP,XM,YM, 300);
/*
#define LCD_CS 10
#define LCD_CD 11
#define LCD_WR 12
#define LCD_RD 13
*/

#define BLACK           0x0000
#define BLUE            0x001F
#define RED             0xF800
#define GREEN           0x07E0
#define CYAN            0x07FF
#define MAGENTA         0xF81F
#define YELLOW          0xFFE0
#define WHITE           0xFFFF
#define NAVY            0x000F      /*   0,   0, 128 */
#define DARKGREEN       0x03E0      /*   0, 128,   0 */
#define DARKCYAN        0x03EF      /*   0, 128, 128 */
#define MAROON          0x7800      /* 128,   0,   0 */
#define PURPLE          0x780F      /* 128,   0, 128 */
#define OLIVE           0x7BE0      /* 128, 128,   0 */
#define LIGHTGREY       0xC618      /* 192, 192, 192 */
#define DARKGREY        0x7BEF      /* 128, 128, 128 */
#define YELLOW          0xFFE0      /* 255, 255,   0 */
#define ORANGE          0xFD20      /* 255, 165,   0 */
#define GREENYELLOW     0xAFE5      /* 173, 255,  47 */
#define PINK            0xF81F

uint16_t getColor(uint8_t red, uint8_t green, uint8_t blue)
{
  red   >>= 3;
  green >>= 2;
  blue  >>= 3;
  return (red << 11) | (green << 5) | blue;
}

Adafruit_TFTLCD tft(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET);


void setup(){
    Serial.begin(9600);
    Serial.println(F("TFT LCD test"));

    #ifdef USE_ADAFRUIT_SHIELD_PINOUT
        Serial.println(F("Using Adafruit 2.8\" TFT Arduino Shield Pinout"));
    #else
        Serial.println(F("Using Adafruit 2.8\" TFT Breakout Board Pinout"));
    #endif

    Serial.print("TFT size is "); Serial.print(tft.width());
    Serial.print("x"); Serial.println(tft.height());

    tft.reset();

    uint16_t identifier = tft.readID();

    if(identifier == 0x9325) {
        Serial.println(F("Found ILI9325 LCD driver"));
    } else if(identifier == 0x9328) {
        Serial.println(F("Found ILI9328 LCD driver"));
    } else if(identifier == 0x7575) {
        Serial.println(F("Found HX8347G LCD driver"));
    } else if(identifier == 0x9341) {
        Serial.println(F("Found ILI9341 LCD driver"));
    } else if(identifier == 0x8357) {
        Serial.println(F("Found HX8357D LCD driver"));
    } else {
        Serial.print(F("Unknown LCD driver chip: "));
        Serial.println(identifier, HEX);
        Serial.println(F("If using the Adafruit 2.8\" TFT Arduino shield, the line:"));
        Serial.println(F("  #define USE_ADAFRUIT_SHIELD_PINOUT"));
        Serial.println(F("should appear in the library header (Adafruit_TFT.h)."));
        Serial.println(F("If using the breakout board, it should NOT be #defined!"));
        Serial.println(F("Also if using the breakout, double-check that all wiring"));
        Serial.println(F("matches the tutorial."));
        return;
    }

    tft.begin(identifier);

    tft.setRotation(1);
    tft.fillScreen(WHITE);
    tft.setTextColor(WHITE); tft.setTextSize(8);
    
    drawScreen(0);
}

#define MINPRESSURE 1
#define MAXPRESSURE 1000

void loop(void){
    // Should set the screen to be horizontal
    
    //testText();
    //tft.drawCircle(100,100,50,RED);

    /*    TOUCH SENSING
    TSPoint p = ts.getPoint();
    if (p.z > MINPRESSURE && p.z < MAXPRESSURE) {
        pinMode(XM, OUTPUT);
        pinMode(YP, OUTPUT);

        int x = map(p.x,TS_MINX,TS_MAXX,320,0);
        int y = map(p.y,TS_MINY,TS_MAXY,0,480);
        
        tft.fillCircle(y, x, 10,RED);
    }
    */
    delay(1000);
}
void drawScreen(int select){
    int length_long = 216;
    int length_short = 176;
    int l1 = length_short, l2 = length_short,
        l3 = length_short, l4 = length_short;

    switch(select){
        case 0: l1 = length_long; 
                tft.fillRect(20,0,95,223, BLACK);
                tft.fillCircle(63,58,60, BLACK);
                break;
        case 1: l2 = length_long; 
                break;
        case 2: l3 = length_long; 
                break;
        case 3: l4 = length_long; 
                break;
        default: break;
    }
    // 1
    tft.fillRect(22, 0, 90, l1, getColor(255,153,85));
    tft.fillCircle(63,58,55, getColor(128,0,0));
    tft.setCursor(45,35);
    tft.println("1");

    // 2
    tft.fillRect(135, 0, 90, l2, getColor(135,222,205));
    tft.fillCircle(181, 58,55, getColor(0,170,136));
    tft.setCursor(163,35);
    tft.println("2");

    // 3
    tft.fillRect(259, 0, 90, l3, getColor(141,211,95));
    tft.fillCircle(299, 58, 55, getColor(33,120,33));
    tft.setCursor(281,35);
    tft.println("3");

    // 4
    tft.fillRect(370, 0, 90, l4, getColor(153,85,255));
    tft.fillCircle(417, 58, 55, getColor(68,0,85));
    tft.setCursor(399,35);
    tft.println("4");

    // AUTO
    tft.fillRect(0,234, 480, 76, BLACK);
    tft.setCursor(160, 240);
    tft.println("AUTO");
}

void drawText(){
    //tft.fillScreen(BLACK);
    tft.setCursor(0, 0);
    tft.setTextColor(WHITE); tft.setTextSize(6);
    tft.println("Happy");
    tft.println("Birthday");
    tft.println("Bram");
}
