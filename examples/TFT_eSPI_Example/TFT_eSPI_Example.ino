//HX2003
#include <GFXLayer.h>
#include <TFT_eSPI.h> 
#include <SPI.h>

TFT_eSPI tft = TFT_eSPI();      

//Main Layer -|NotifyLayer -|notifyBorder
//            |            -|notifyText

GFXLayerInterface MainLayer(&tft);
GFXLayerInterface NotifyLayer(&tft);
GFXText notifyTextElement = GFXText();
GFXRectangle notifyBorderElement = GFXRectangle();
void setup() {
  tft.init();
  tft.setRotation(3);
  tft.fillScreen(0x000000);
  notifyTextElement.setCursor(100, 100);
  notifyTextElement.setTextSize(1);
  notifyTextElement.print("Hello. You have a message.");

  notifyBorderElement.drawRect(95, 95, 200, 20, 0xFFFF);

  NotifyLayer.add(&notifyTextElement);
  NotifyLayer.add(&notifyBorderElement);

  MainLayer.add(&NotifyLayer);
}

void loop() {
  tft.fillScreen(0x000000);
  NotifyLayer.setVisibility(true);
  MainLayer.draw();

  delay(1000);

  tft.fillScreen(0x000000);
  NotifyLayer.setVisibility(false);
  MainLayer.draw();

  
  delay(1000);
}