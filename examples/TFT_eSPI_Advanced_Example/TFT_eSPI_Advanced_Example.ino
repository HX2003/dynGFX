//HX2003
#include <GFXLayer.h>
#include <TFT_eSPI.h>
#include <SPI.h>

TFT_eSPI tft = TFT_eSPI();

GFXText bgText;

class GFXPopUp : public GFXBaseElement {
  public:
    GFXPopUp(): GFXBaseElement() {};
    void
    drawAlert(uint16_t c),
              drawOverride();
  protected:
    int16_t w = 150;
    int16_t h = 50;
    int16_t r = 5;
};
void GFXPopUp::drawAlert(uint16_t c) {
  this->c = c;
}
void GFXPopUp::drawOverride() {
  _panel->fillRoundRect((_panel->width() - w) / 2, (_panel->height() - h) / 2, w, h, r, TFT_WHITE);
  _panel->setTextSize(3);
  _panel->setTextColor(c, TFT_WHITE);
  _panel->setTextDatum(MC_DATUM);
  _panel->drawString("ALERT", _panel->width()/ 2, _panel->height()/ 2);
}


GFXLayerInterface MainLayer(&tft);
GFXLayerInterface NotifyLayer(&tft);
GFXPopUp alert = GFXPopUp();
void setup() {
  tft.init();
  tft.setRotation(3);
  tft.fillScreen(0x000000);
  alert.drawAlert(TFT_RED);

  NotifyLayer.add(&alert);

  bgText.setTextWrap(true);
  bgText.print(F("Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Aliquet bibendum enim facilisis gravida neque convallis a cras. Convallis posuere morbi leo urna molestie at elementum eu facilisis. Tortor vitae purus faucibus ornare suspendisse. Arcu dictum varius duis at consectetur lorem donec massa. Iaculis eu non diam phasellus vestibulum lorem sed. Mauris augue neque gravida in fermentum et sollicitudin ac. Consectetur lorem donec massa sapien faucibus et molestie. Ac turpis egestas maecenas pharetra convallis posuere morbi leo. Nulla facilisi etiam dignissim diam. Eu turpis egestas pretium aenean pharetra magna. Nulla malesuada pellentesque elit eget gravida cum. Urna condimentum mattis pellentesque id nibh tortor id aliquet. Sapien pellentesque habitant morbi tristique senectus et. Orci dapibus ultrices in iaculis nunc. Duis convallis convallis tellus id interdum velit laoreet.Massa tincidunt dui ut ornare. Mauris a diam maecenas sed enim ut sem. Sodales ut eu sem integer vitae justo eget. Duis at tellus at urna condimentum. Velit laoreet id donec ultrices tincidunt arcu non. Bibendum est ultricies integer quis auctor elit sed vulputate. Sagittis vitae et leo duis ut diam. Gravida dictum fusce ut placerat orci nulla pellentesque dignissim. Eget magna fermentum iaculis eu non diam phasellus vestibulum lorem. Pulvinar elementum integer enim neque volutpat ac tincidunt vitae. Maecenas accumsan lacus vel facilisis volutpat. Venenatis a condimentum vitae sapien. Enim praesent elementum facilisis leo vel. Risus commodo viverra maecenas accumsan lacus vel facilisis volutpat. Non pulvinar neque laoreet suspendisse. Commodo nulla facilisi nullam vehicula ipsum a arcu cursus vitae. Imperdiet dui accumsan sit amet nulla facilisi. Dui ut ornare lectus sit amet est placerat in egestas.Amet cursus sit amet dictum sit. Amet aliquam id diam maecenas ultricies mi eget. Natoque penatibus et magnis dis parturient montes nascetur. Semper quis lectus nulla at volutpat. Pellentesque pulvinar pellentesque habitant morbi tristique senectus. Enim blandit volutpat maecenas volutpat blandit aliquam etiam. Pharetra sit amet aliquam id diam maecenas ultricies. Eu nisl nunc mi ipsum faucibus. Mattis molestie a iaculis at erat pellentesque adipiscing commodo elit. Nec feugiat nisl pretium fusce id velit ut tortor. Id leo in vitae turpis massa sed elementum. Faucibus et molestie ac feugiat. Etiam tempor orci eu lobortis elementum nibh. Aliquet risus feugiat in ante metus. Viverra justo nec ultrices dui sapien. Porta non pulvinar neque laoreet. Ultricies integer quis auctor elit sed vulputate mi sit amet. Arcu vitae elementum curabitur vitae nunc sed velit. Nisl tincidunt eget nullam non nisi est sit amet."));
  MainLayer.add(&bgText);
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