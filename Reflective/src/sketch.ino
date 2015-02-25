#include <Adafruit_GFX.h>
#include <Adafruit_TFTLCD.h>
#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include <TouchScreen.h>

#define LCD_CS A3
#define LCD_CD A2
/*
#define LCD_WR A1
#define LCD_RD A0
*/
#define LCD_WR 10
#define LCD_RD 11

#define LCD_RESET A4

#define YP A3
#define XM A2
#define YM 9
#define XP 8

#define TS_MINX 150
#define TS_MINY 120
#define TS_MAXX 920
#define TS_MAXY 940

#define BLACK           0x0000
#define WHITE           0xFFFF

// Defining lengths
#define BOX_SHORT    176
#define BOX_LONG     216
#define BOX_DIFF     40
#define NUMB_H       30
#define MEASURE_H    55
#define CIRCLE_H     60

#define MINPRESSURE 1
#define MAXPRESSURE 1000

#define Y_LOW       110
#define Y_HIGH      0

uint8_t selector = 4;
TouchScreen ts = TouchScreen(XP,YP,XM,YM, 300);
Adafruit_TFTLCD tft(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET);

uint16_t getColor(uint8_t red, uint8_t green, uint8_t blue)
{
  red   >>= 3;
  green >>= 2;
  blue  >>= 3;
  return (red << 11) | (green << 5) | blue;
}

void setup(){
    Serial.begin(9600);

    tft.reset();

    uint16_t identifier = tft.readID();

    tft.begin(identifier);

    // Begins drawing the screen
    tft.setRotation(1);
    tft.fillScreen(WHITE);
    tft.setTextColor(WHITE); tft.setTextSize(8);

    // 1
    tft.fillRect(23, 0, 80, BOX_SHORT, getColor(255,153,85));
    tft.fillCircle(63,CIRCLE_H,55, getColor(128,0,0));
    tft.setCursor(45,NUMB_H);
    tft.println("1");

    // 2
    tft.fillRect(141, 0, 80, BOX_SHORT, getColor(135,222,205));
    tft.fillCircle(181, CIRCLE_H,55, getColor(0,170,136));
    tft.setCursor(163,NUMB_H);
    tft.println("2");

    // 3
    tft.fillRect(259, 0, 80, BOX_SHORT, getColor(141,211,95));
    tft.fillCircle(299, CIRCLE_H, 55, getColor(33,120,33));
    tft.setCursor(281,NUMB_H);
    tft.println("3");

    // 4
    tft.fillRect(377, 0, 80, BOX_SHORT, getColor(153,85,255));
    tft.fillCircle(417, CIRCLE_H, 55, getColor(68,0,85));
    tft.setCursor(393,NUMB_H);
    tft.println("4");

    // AUTO
    tft.fillRect(0,230, 480, 75, BLACK);
    tft.setCursor(160, 240);
    tft.println("AUTO");
}


void loop(void){
    
    TSPoint p = ts.getPoint();
    if (p.z > MINPRESSURE && p.z < MAXPRESSURE) {
        pinMode(XM, OUTPUT);
        pinMode(YP, OUTPUT);

        uint8_t y = map(p.x,TS_MINX,TS_MAXX,320,0);
        uint8_t x = map(p.y,TS_MINY,TS_MAXY,0,480);
        
        if ( y < Y_LOW && y > Y_HIGH ){
            if ( x > 0 && x < 120 && selector != 0 ){
                selector = 0;
                Select(selector);
            }
            if ( x > 120 && x < 240 && selector != 1){
                selector = 1;
                Select(selector);
            }
            if (x > 240 && x < 360 && selector != 2){
                selector = 2;
                Select(selector);
            }
            if ( x > 360 && x < 480 && selector != 3){
                selector = 3;
                Select(selector);
            }
        }
        if ( y > 230 ){
            selector = 4;
            Select(4);
        }
    }
}
void Select(uint8_t select){
    tft.fillRect(0, BOX_SHORT, 480, BOX_DIFF, WHITE);
    switch(select){
        case 0: 
            tft.fillRect(23, BOX_SHORT, 80, BOX_DIFF, getColor(255,153,85));
            break;
        case 1:  
            tft.fillRect(141, BOX_SHORT, 80, BOX_DIFF, getColor(135,222,205));
            break;
        case 2:  
            tft.fillRect(259, BOX_SHORT, 80, BOX_DIFF, getColor(141,211,95));
            break;
        case 3: 
            tft.fillRect(377, BOX_SHORT, 80, BOX_DIFF, getColor(153,85,255));
            break;
        default: break;
    }
}
