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
textElement notifyTextElement = textElement();
rectangleElement notifyBorderElement = rectangleElement();
void setup() {
  tft.begin();
  tft.setRotation(3);
  tft.fillScreen(0x000000);
  notifyTextElement.setCursor(100, 100);
  notifyTextElement.setTextSize(1);
  notifyTextElement.print("Hello. You have a message.");

  notifyBorderElement.drawRect(95, 95, 200, 20, 0xFFFF);

  NotifyLayer.addElement(&notifyTextElement);
  NotifyLayer.addElement(&notifyBorderElement);

  MainLayer.addElement(&NotifyLayer);
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