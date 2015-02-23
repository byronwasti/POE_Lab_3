#include <Adafruit_GFX.h>
#include <Adafruit_TFTLCD.h>
#include <TouchScreen.h>

#if defined(__SAM3X8E__)
    #undef __FlashStringHelper::F(string_literal)
    #define F(string_literal) string_literal
#endif

#define YP A3
#define XM A2
#define YM 9
#define XP 8

#define TS_MINX 150
#define TS_MINY 120
#define TS_MAXX 920
#define TS_MAXY 940

TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300); 
#define LCD_CS A3
#define LCD_CD A2
#define LCD_WR A1
#define LCD_RD A0
#define LCD_RESET A4

#define BLACK   0x0000
#define BLUE    0x001F
#define RED     0xF800
#define GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF
#define BLUEISH 0xaa88

Adafruit_TFTLCD tft(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET);

void setup(void){
    Serial.begin(9600);
    Serial.println("It Works!");

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
    pinMode(13,OUTPUT);
}

#define MINPRESSURE 4
#define MAXPRESSURE 1000
int prev_x;
int prev_y;

void loop()
{
    //tft.setRotation(0);
    //tft.fillScreen(BLACK);
    TSPoint p = ts.getPoint();
    //tft.setCursor(0,0);
    //tft.setTextColor(WHITE); tft.setTextSize(3);
    //tft.println("Hey Patrick");
    //delay(2000);

    if (p.z > MINPRESSURE && p.z < MAXPRESSURE) {
        pinMode(XM, OUTPUT);
        pinMode(YP, OUTPUT);
        
        tft.fillCircle(map(p.x,TS_MINX,TS_MAXX,0,320) , map(p.y,TS_MINY,TS_MAXY,0,480) ,5,BLUEISH);
        //tft.fillCircle(map(prev_x,TS_MINX,TS_MAXX,0,320) , map(prev_y,TS_MINY,TS_MAXY,0,480) ,50,BLACK);

        prev_x = p.x;
        prev_y = p.y;
    }
}
