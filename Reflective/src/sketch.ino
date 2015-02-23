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
#define Navy            0x000F      /*   0,   0, 128 */
#define DarkGreen       0x03E0      /*   0, 128,   0 */
#define DarkCyan        0x03EF      /*   0, 128, 128 */
#define Maroon          0x7800      /* 128,   0,   0 */
#define Purple          0x780F      /* 128,   0, 128 */
#define Olive           0x7BE0      /* 128, 128,   0 */
#define LightGrey       0xC618      /* 192, 192, 192 */
#define DarkGrey        0x7BEF      /* 128, 128, 128 */
#define Yellow          0xFFE0      /* 255, 255,   0 */
#define Orange          0xFD20      /* 255, 165,   0 */
#define GreenYellow     0xAFE5      /* 173, 255,  47 */
#define Pink            0xF81F

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
    tft.fillScreen(BLACK);
}

#define MINPRESSURE 1
#define MAXPRESSURE 1000

void loop(void){
    // Should set the screen to be horizontal
    tft.setRotation(1);
    
    testText();
    //tft.drawCircle(100,100,50,RED);

    TSPoint p = ts.getPoint();
    if (p.z > MINPRESSURE && p.z < MAXPRESSURE) {
        pinMode(XM, OUTPUT);
        pinMode(YP, OUTPUT);

        int x = map(p.x,TS_MINX,TS_MAXX,320,0);
        int y = map(p.y,TS_MINY,TS_MAXY,0,480);
        
        tft.fillCircle(y, x, 10,RED);
    }
}

void testText(){
    //tft.fillScreen(BLACK);
    tft.setCursor(0, 0);
    tft.setTextColor(WHITE); tft.setTextSize(6);
    tft.println("Happy");
    tft.println("Birthday");
    tft.println("Bram");
}

/*
void Circle_Draw(uint8_t radius, uint16_t color, n){
    int w = tft.width(), h = tft.height();
    //x, y, r2 = radius * 2;
    
    tft.drawCircle(x, y, radius, color);
}
*/
