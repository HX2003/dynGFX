//HX2003
#include "SPI.h"
#include "Adafruit_GFX.h"
#include "Adafruit_ILI9341.h"
#include <GFXLayer.h>

//#define TFT_DC 9
//#define TFT_CS 10

#define TFT_DC D3
#define TFT_CS D2

Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC);
// If using the breakout, change pins as desired
//Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_MOSI, TFT_CLK, TFT_RST, TFT_MISO);
//Main Layer -|NotifyLayer -|notifyBorder
//            |            -|notifyText

GFXLayerInterface MainLayer(&tft);
GFXLayerInterface NotifyLayer(&tft);
GFXLayerInterface bgLayer(&tft);
GFXText notifyTextElement; 
GFXFilledRoundRectangle notifyBorderElement; 

GFXText bgTextElement; 
GFXFilledRectangle bgBorderElement; 
void setup() {
  Serial.begin(115200);
  tft.begin();
  tft.setRotation(3);
  tft.fillScreen(0x000000);
  notifyTextElement.setCursor(100, 100);
  notifyTextElement.setTextSize(1);
  notifyTextElement.print("Hello. You have a message.");
  notifyTextElement.setZIndex(1);
  
  notifyBorderElement.fillRoundRect(95, 95, 200, 20, 5, 0xFAFA);
  notifyBorderElement.setZIndex(0);
  NotifyLayer.add(&notifyTextElement);
  NotifyLayer.add(&notifyBorderElement);


  bgTextElement.setCursor(75, 75);
  bgTextElement.setTextSize(2);
  bgTextElement.print("BackgroundText");
  bgTextElement.setZIndex(1);
  
  bgBorderElement.fillRect(60, 60, 300, 100, 0x2222);
  bgBorderElement.setZIndex(0);
  bgLayer.add(&bgTextElement);
  bgLayer.add(&bgBorderElement);
  bgLayer.setZIndex(-1);
  MainLayer.add(&NotifyLayer);
  MainLayer.add(&bgLayer);
}

void loop() {
  tft.fillScreen(0x000000);
  NotifyLayer.setVisibility(true);
  MainLayer.draw();

  delay(1000);

  tft.fillScreen(0x000000);
  NotifyLayer.setVisibility(false);
  MainLayer.draw();
} 