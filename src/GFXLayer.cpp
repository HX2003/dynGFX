#ifndef _GFXLayer_
#include "GFXLayer.h"
#endif

#ifdef ADAFRUIT_GFX_LIB
Adafruit_GFX* _panel;
#endif

#ifdef TFT_eSPI_LIB
TFT_eSPI* _panel;
#endif

//GFXLayer
void GFXLayer::draw(){
	GFXLayer* GFXLayer;
	for(int i = 0; i < ElementList.size(); i++){
		GFXLayer = ElementList.get(i);
		GFXLayer->draw();
	}
}
void GFXLayer::clear(bool delete_me){
	GFXLayer* GFXLayer;
	for(int i = 0; i < ElementList.size(); i++){
		GFXLayer = ElementList.get(i);
		if(GFXLayer->isElement()){
			delete GFXLayer;
		}else{
			GFXLayer->clear(true);
		}
	}
	ElementList.clear();
	if(delete_me){
		delete this;
	}
}
bool GFXLayer::isElement(){
	return false;
}
void GFXLayer::setVisibility(bool visibility){
	GFXLayer* GFXLayer;
	for(int i = 0; i < ElementList.size(); i++){
		GFXLayer = ElementList.get(i);
		GFXLayer->setVisibility(visibility);
	}
}
void GFXLayer::setSimpleOpacity(uint8_t opacity){
	GFXLayer* GFXLayer;
	for(int i = 0; i < ElementList.size(); i++){
		GFXLayer = ElementList.get(i);
		GFXLayer->setSimpleOpacity(opacity);
	}
}
void GFXLayer::setZIndex(int8_t ZIndex){
	this->ZIndex = ZIndex;
}
uint8_t GFXLayer::getSimpleOpacityFirst(){
	GFXLayer* GFXLayer;
	GFXLayer = ElementList.get(0);
	return GFXLayer->getSimpleOpacityFirst();
	return GFXLayer->getSimpleOpacityFirst();
}
int8_t GFXLayer::getZIndex(){
	return ZIndex;
}
uint16_t GFXLayer::alphaBlendRGB565(uint32_t fg, uint32_t bg, uint8_t alpha){
	alpha = alpha >> 3;
	bg = (bg | (bg << 16)) & 0b00000111111000001111100000011111;
	fg = (fg | (fg << 16)) & 0b00000111111000001111100000011111;
	uint32_t result = ((((fg - bg) * alpha) >> 5) + bg) & 0b00000111111000001111100000011111;
	return (uint16_t)((result >> 16) | result);
}
//GFXLayerInterface
void GFXLayerInterface::add(GFXLayer *element){
	ElementList.add(element);
	this->sort();
}

int compare_zindex(GFXLayer*& lhs, GFXLayer*& rhs) {
	if(lhs->getZIndex()<rhs->getZIndex()){
		return -1;
	}
	if(lhs->getZIndex()==rhs->getZIndex()){
		return 0;
	}
	if(lhs->getZIndex()>rhs->getZIndex()){
		return 1;
	}
}

void GFXLayerInterface::sort(){
	ElementList.sort(compare_zindex);
} 
void GFXLayerInterface::draw(){
	GFXLayer::draw();
}
void GFXLayerInterface::clear(){
	GFXLayer::clear(false);
}
void GFXLayerInterface::setSimpleOpacity(uint8_t opacity){
	GFXLayer::setSimpleOpacity(opacity);
}
void GFXLayerInterface::setVisibility(bool visibility){
	GFXLayer::setVisibility(visibility);
}
void GFXLayerInterface::setZIndex(int8_t ZIndex){
	return GFXLayer::setZIndex(ZIndex);
}
uint8_t GFXLayerInterface::getSimpleOpacityFirst(){
	return GFXLayer::getSimpleOpacityFirst();
}
int8_t GFXLayerInterface::getZIndex(){
	return GFXLayer::getZIndex();
}
//GFXBaseElement
void GFXBaseElement::drawOverride(){
}
void GFXBaseElement::draw(){
	if(simpleopacity >= 8){
		this->drawOverride();
	}
}
bool GFXBaseElement::isElement(){
	return true;
}
void GFXBaseElement::setBackgroundColor(uint16_t bgc){
	this->bgc = bgc;
}
void GFXBaseElement::setBackgroundColor888(uint8_t r, uint8_t g, uint8_t b){
	this->bgc = ((uint16_t)(r & 0xF8) << 8) | ((uint16_t)(g & 0xFC) << 3) | (b >> 3);
}
void GFXBaseElement::setCursor(int16_t x, int16_t y){
	this->x = x;
	this->y = y;
}
void GFXBaseElement::setVisibility(bool visibility){
	if(visibility){
		simpleopacity = 255;
	}else{
		simpleopacity = 0;
	}
}
void GFXBaseElement::setZIndex(int8_t zindex){
	this->zindex = zindex;
}
int8_t GFXBaseElement::getZIndex(){
	return zindex;
}
uint8_t GFXBaseElement::getSimpleOpacityFirst(){
	return simpleopacity;
}
//GFXRectangle
void GFXRectangle::drawRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t c){
	this->x = x;
	this->y = y;
	this->w = w;
	this->h = h;
	this->c = c;
}
void GFXRectangle::drawOverride(){
	_panel->drawRect(x, y, w, h, alphaBlendRGB565(c, bgc, simpleopacity));
}
//GFXFilledRectangle
void GFXFilledRectangle::fillRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t c){
	this->x = x;
	this->y = y;
	this->w = w;
	this->h = h;
	this->c = c;
}
void GFXFilledRectangle::drawOverride(){
	_panel->fillRect(x, y, w, h, alphaBlendRGB565(c, bgc, simpleopacity));
}
//GFXRoundRectangle
void GFXRoundRectangle::drawRoundRect(int16_t x, int16_t y, int16_t w, int16_t h, int16_t r, uint16_t c){
	this->x = x;
	this->y = y;
	this->w = w;
	this->h = h;
	this->r = r;
	this->c = c;
}
void GFXRoundRectangle::drawOverride(){
	_panel->drawRoundRect(x, y, w, h, r, alphaBlendRGB565(c, bgc, simpleopacity));
}
//GFXFilledRoundRectangle
void GFXFilledRoundRectangle::fillRoundRect(int16_t x, int16_t y, int16_t w, int16_t h, int16_t r, uint16_t c){
	this->x = x;
	this->y = y;
	this->w = w;
	this->h = h;
	this->r = r;
	this->c = c;
}
void GFXFilledRoundRectangle::drawOverride(){
	_panel->fillRoundRect(x, y, w, h, r, alphaBlendRGB565(c, bgc, simpleopacity));
}
//GFXTriangle
void GFXTriangle::drawTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint16_t c){
	this->x = x0;
	this->y = y0;
	this->x1 = x1;
	this->y1 = y1;
	this->x2 = x2;
	this->y2 = y2;
	this->c = c;
}
void GFXTriangle::drawOverride(){
	_panel->drawTriangle(x, y, x1, y1, x2, y2, alphaBlendRGB565(c, bgc, simpleopacity));
}
//GFXFilledTriangle
void GFXFilledTriangle::fillTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint16_t c){
	this->x = x0;
	this->y = y0;
	this->x1 = x1;
	this->y1 = y1;
	this->x2 = x2;
	this->y2 = y2;
	this->c = c;
}
void GFXFilledTriangle::drawOverride(){
	_panel->fillTriangle(x, y, x1, y1, x2, y2, alphaBlendRGB565(c, bgc, simpleopacity));
}
//GFXText
void GFXText::setFont(const GFXfont *font){
	this->font = font;
}
void GFXText::setTextWrap(bool textwrap){
	this->textwrap = textwrap;
}
void GFXText::setTextColor(uint16_t c){
	this->c = c;
}
void GFXText::setTextColor888(uint8_t r, uint8_t g, uint8_t b){
	this->c = ((uint16_t)(r & 0xF8) << 8) | ((uint16_t)(g & 0xFC) << 3) | (b >> 3);
}
void GFXText::setTextSize(uint8_t textsize){
	this->textsize = textsize;
}
void GFXText::setTextAlignment(uint8_t alignment){
	this->alignment = alignment;
}
void GFXText::print(String text){
	this->text = text;
}
void GFXText::drawOverride(){
	#ifdef ADAFRUIT_GFX_LIB
	_panel->setFont(font);
	#endif
	
	#ifdef TFT_eSPI_LIB
	_panel->setFreeFont(font);
	#endif
	_panel->setTextWrap(textwrap);
	_panel->setTextSize(textsize);
	_panel->setTextColor(alphaBlendRGB565(c, bgc, simpleopacity));
	//Take note alignment does not handle cases where text exceeds boundary
	int16_t x1, y1;
	uint16_t w1, h1;
	switch(alignment){
	case 0:
		_panel->setCursor(x, y);
		break;
	case TEXT_ALIGNMENT_CENTER:
		_panel->getTextBounds(text, 0, 0, &x1, &y1, &w1, &h1);
		_panel->setCursor((_panel->width() - w1) / 2, y);
		break;
	case TEXT_ALIGNMENT_2_LEFT:
		_panel->getTextBounds(text, 0, 0, &x1, &y1, &w1, &h1);
		_panel->setCursor((_panel->width()/2 - w1) / 2, y);
		break;
	case TEXT_ALIGNMENT_2_RIGHT:
		_panel->getTextBounds(text, 0, 0, &x1, &y1, &w1, &h1);
		_panel->setCursor(_panel->width()/2 + (_panel->width()/2 - w1) / 2, y);
		break;
	}
	_panel->print(text);
	//_panel->display(); use only for matrix
}
String GFXText::returnTextVal(){
	return text;
}
//GFXGrayscaleBitmap
void GFXGrayscaleBitmap::drawGrayscaleBitmap(int16_t x, int16_t y, const uint8_t *bitmap, int16_t w, int16_t h){
	this->x = x;
	this->y = y;
	this->w = w;
	this->h = h;
	this->bitmap = bitmap;
}
void GFXGrayscaleBitmap::drawOverride(){
	_panel->drawGrayscaleBitmap(x, y, bitmap, w, h);
}
#ifdef GFX_EXTENDED_FEATURES
//GFXTiled565RGBBitmap  
void GFXTiled565RGBBitmap::drawRGBBitmap(int16_t x, int16_t y, const uint16_t *bitmap, int16_t w, int16_t h){
	this->x = x;
	this->y = y;
	this->w = w;
	this->h = h;
	this->bitmap = bitmap;
};

void GFXTiled565RGBBitmap::setTiling(uint16_t tilingx, uint16_t tilingy, uint16_t tilingxspacing, uint16_t tilingyspacing){
	this->tilingx = tilingx;
	this->tilingy = tilingy;
	this->tilingxspacing = tilingxspacing;
	this->tilingyspacing = tilingyspacing;
}
void GFXTiled565RGBBitmap::drawOverride(){
	for(uint16_t a=0; a<tilingx; a++){
		for(uint16_t b=0; b<tilingy; b++){ 
			for(int16_t j=0; j<h; j++) {
				for(int16_t i=0; i<w; i++ ) {
					_panel->drawPixel(x+i+a*(w+tilingxspacing)+x, y+j+b*(h+tilingyspacing)+y, alphaBlendRGB565(pgm_read_word(&bitmap[j * w + i]), bgc , simpleopacity));
				}
			}
		}
	}
	//_panel->display(); use only for matrix
}
//GFXDotsIndicator
void GFXDotsIndicator::drawDotsIndicator(int16_t x, int16_t y, int16_t h, uint16_t tilingx, uint16_t tilingxspacing, uint16_t c, bool centered){
	this->x = x;
	this->y = y;
	this->h = h;
	this->tilingx = tilingx;
	this->tilingxspacing = tilingxspacing;
	this->c = c;
	this->centered = centered;
}
void GFXDotsIndicator::setDotPosition(uint16_t pos){
	this->pos = pos;
}
void GFXDotsIndicator::drawOverride(){
	uint16_t offsetx = 0;
	uint16_t offsety = 0;
	//Convert top left to center point
	offsety = y + h/2;
	offsetx = x + h/2;
	if(centered){
		uint16_t totalw;

		totalw = tilingxspacing*(tilingx - 1);
		totalw = totalw + h;
		
		offsetx = offsetx + (_panel->width() - totalw)/2;
	} 
	for(uint16_t i=0; i<tilingx; i++){
		if(i == pos){
			_panel->fillCircle(offsetx + tilingxspacing*i, offsety, h/2, alphaBlendRGB565(c, bgc, simpleopacity));
		}else{
			_panel->drawCircle(offsetx + tilingxspacing*i, offsety, h/2, alphaBlendRGB565(c, bgc, simpleopacity));
			_panel->drawCircle(offsetx + tilingxspacing*i, offsety, h/2 - 1, alphaBlendRGB565(c, bgc, simpleopacity)); //Temporary! Thicker circles without additional functions!
		}
	}
}
#endif

#ifdef GFX_USE_JSON_LOADER
void GFXJson::load(const __FlashStringHelper* src, GFXLayerInterface* layer){
	parseJson<const __FlashStringHelper*>(src, layer);
}

void GFXJson::load(const String& src, GFXLayerInterface* layer){ 
	#ifdef GFX_USE_SPIFFS
	if (SPIFFS.exists(src))
	{
		File jsonFile = SPIFFS.open(src, "r");
		parseJson<File>(jsonFile, layer);
		jsonFile.close();
	}
	#endif
}
template<typename T>
void GFXJson::parseJson(T src, GFXLayerInterface* layer){
	DynamicJsonDocument doc(4096);
	JsonVariant json;
	auto error = deserializeJson(doc, src);
	if (error) {
		Serial.print(F("deserializeJson() failed with code "));
		Serial.println(error.c_str());
		return;
	}
	json = doc.as<JsonVariant>();
	_load(json, layer);
}


void GFXJson::_load(JsonVariant& json, GFXLayerInterface* element) {
	if(json.is<JsonArray>()){
		JsonArray array = json.as<JsonArray>();
		for(JsonVariant variant : array) {
			if (variant.is<JsonArray>()){
				_load(variant, element);
			} else if (variant.is<JsonObject>()){
				_load(variant, element);
			} else {
				Serial.println("   " + String(variant.as<char*>()));
			}
		}
	}else if(json.is<JsonObject>()){
		JsonObject object = json.as<JsonObject>();
		GFXLayerInterface* newLayer;  
		const char* type = nullptr;
		GFXLayer* newElement;
		for(JsonPair p : object) {
			JsonString key = p.key(); // is a JsonString
			JsonVariant variant = p.value(); // is a JsonVariant
			if (variant.is<JsonArray>()){
				_load(variant, newLayer);
			}else if(variant.is<JsonObject>()) {
				_load(variant, newLayer);
			}else if(variant.is<char*>()){
				const char* k = key.c_str();
				const char* v = variant;
				Serial.print("key: ");
				Serial.print(k);
				Serial.print(", val: ");
				Serial.println(v);
				//Type handling
				if(strcmp_P(k, PSTR("type"))==0){
					type = v;
					if(strcmp_P(v, PSTR("GFXLayer"))==0){
						GFXLayerInterface* layer = new GFXLayerInterface(_panel);
						newLayer = layer;
						element->add(newLayer);
					}
					if(strcmp_P(v, PSTR("GFXText"))==0){
						GFXText* tempElement = new GFXText;
						newElement = (GFXLayer*)tempElement;
						element->add(newElement);
					}
					if(strcmp_P(v, PSTR("GFXRectangle"))==0){
						GFXRectangle* tempElement = new GFXRectangle;
						newElement = (GFXLayer*)tempElement;
						element->add(newElement);
					}
					if(strcmp_P(v, PSTR("GFXFilledRectangle"))==0){
						GFXFilledRectangle* tempElement = new GFXFilledRectangle;
						newElement = (GFXLayer*)tempElement;
						element->add(newElement);
					}
					if(strcmp_P(v, PSTR("GFXRoundRectangle"))==0){
						GFXRoundRectangle* tempElement = new GFXRoundRectangle;
						newElement = (GFXLayer*)tempElement;
						element->add(newElement);
					}
					if(strcmp_P(v, PSTR("GFXFilledRoundRectangle"))==0){
						GFXFilledRoundRectangle* tempElement = new GFXFilledRoundRectangle;
						newElement = (GFXLayer*)tempElement;
						element->add(newElement);
					}
					if(strcmp_P(v, PSTR("GFXTriangle"))==0){
						GFXTriangle* tempElement = new GFXTriangle;
						newElement = (GFXLayer*)tempElement;
						element->add(newElement);
					}
					if(strcmp_P(v, PSTR("GFXFilledTriangle"))==0){
						GFXFilledTriangle* tempElement = new GFXFilledTriangle;
						newElement = (GFXLayer*)tempElement;
						element->add(newElement);
					}
					if(typeHandler != NULL){
						typeHandler(v, element, &newElement);
					}
					
				}
				//Extensions
				if(type != NULL){
					if(strcmp_P(type, PSTR("GFXText"))==0){
						if(strcmp_P(k, PSTR("text"))==0){
							GFXText* tempElement = (GFXText*)newElement;
							tempElement->print(v);
						}
					}
					if(charHandler != NULL){
					charHandler(type, k, v, &newElement);
					}
				}
				
			}else if(variant.is<int>()){
				const char* k = key.c_str();
				int v = variant;
				//GFXBaseElement
				if(strcmp_P(k, PSTR("zindex"))==0){
					GFXBaseElement* tempElement = (GFXBaseElement*)newElement;
					tempElement->zindex = v;
				}
				if(strcmp_P(k, PSTR("x"))==0||strcmp_P(k, PSTR("x0"))==0){
					GFXBaseElement* tempElement = (GFXBaseElement*)newElement;
					tempElement->x = v;
				}
				if(strcmp_P(k, PSTR("y"))==0){
					GFXBaseElement* tempElement = (GFXBaseElement*)newElement;
					tempElement->y = v;
				}
				if(strcmp_P(k, PSTR("c"))==0){
					GFXBaseElement* tempElement = (GFXBaseElement*)newElement;
					tempElement->c = v;
				}
				if(strcmp_P(k, PSTR("bgc"))==0){
					GFXBaseElement* tempElement = (GFXBaseElement*)newElement;
					tempElement->bgc = v;
				}
				//Extensions
				//For GFXRectangle
				if(strcmp_P(type, PSTR("GFXRectangle"))==0){
					if(strcmp_P(k, PSTR("w"))==0){
						GFXRectangle* tempElement = (GFXRectangle*)newElement;
						tempElement->w = v;
					}
					if(strcmp_P(k, PSTR("h"))==0){
						GFXRectangle* tempElement = (GFXRectangle*)newElement;
						tempElement->h = v;
					}
				}
				//For GFXFilledRectangle
				if(strcmp_P(type, PSTR("GFXFilledRectangle"))==0){
					if(strcmp_P(k, PSTR("w"))==0){
						GFXFilledRectangle* tempElement = (GFXFilledRectangle*)newElement;
						tempElement->w = v;
					}
					if(strcmp_P(k, PSTR("h"))==0){
						GFXFilledRectangle* tempElement = (GFXFilledRectangle*)newElement;
						tempElement->h = v;
					}
				}
				//For GFXRoundRectangle
				if(strcmp_P(type, PSTR("GFXRoundRectangle"))==0){
					if(strcmp_P(k, PSTR("w"))==0){
						GFXRoundRectangle* tempElement = (GFXRoundRectangle*)newElement;
						tempElement->w = v;
					}
					if(strcmp_P(k, PSTR("h"))==0){
						GFXRoundRectangle* tempElement = (GFXRoundRectangle*)newElement;
						tempElement->h = v;
					}
					if(strcmp_P(k, PSTR("r"))==0){
						GFXRoundRectangle* tempElement = (GFXRoundRectangle*)newElement;
						tempElement->r = v;
					}
				}
				//For GFXFilledRectangle
				if(strcmp_P(type, PSTR("GFXFilledRoundRectangle"))==0){
					if(strcmp_P(k, PSTR("w"))==0){
						GFXFilledRoundRectangle* tempElement = (GFXFilledRoundRectangle*)newElement;
						tempElement->w = v;
					}
					if(strcmp_P(k, PSTR("h"))==0){
						GFXFilledRoundRectangle* tempElement = (GFXFilledRoundRectangle*)newElement;
						tempElement->h = v;
					}
					if(strcmp_P(k, PSTR("r"))==0){
						GFXFilledRoundRectangle* tempElement = (GFXFilledRoundRectangle*)newElement;
						tempElement->r = v;
					}
				}
				//For GFXTriangle
				if(strcmp_P(type, PSTR("GFXTriangle"))==0){
					if(strcmp_P(k, PSTR("x1"))==0){
						GFXTriangle* tempElement = (GFXTriangle*)newElement;
						tempElement->x1 = v;
					}
					if(strcmp_P(k, PSTR("y1"))==0){
						GFXTriangle* tempElement = (GFXTriangle*)newElement;
						tempElement->y1 = v;
					}
					if(strcmp_P(k, PSTR("x2"))==0){
						GFXTriangle* tempElement = (GFXTriangle*)newElement;
						tempElement->x2 = v;
					}
					if(strcmp_P(k, PSTR("y2"))==0){
						GFXTriangle* tempElement = (GFXTriangle*)newElement;
						tempElement->y2 = v;
					}
				}
				//For GFXFilledTriangle
				if(strcmp_P(type, PSTR("GFXFilledTriangle"))==0){
					if(strcmp_P(k, PSTR("x1"))==0){
						GFXFilledTriangle* tempElement = (GFXFilledTriangle*)newElement;
						tempElement->x1 = v;
					}
					if(strcmp_P(k, PSTR("y1"))==0){
						GFXFilledTriangle* tempElement = (GFXFilledTriangle*)newElement;
						tempElement->y1 = v;
					}
					if(strcmp_P(k, PSTR("x2"))==0){
						GFXFilledTriangle* tempElement = (GFXFilledTriangle*)newElement;
						tempElement->x2 = v;
					}
					if(strcmp_P(k, PSTR("y2"))==0){
						GFXFilledTriangle* tempElement = (GFXFilledTriangle*)newElement;
						tempElement->y2 = v;
					}
				}
				//For GFXText
				if(strcmp_P(type, PSTR("GFXText"))==0){
					if(strcmp_P(k, PSTR("alignment"))==0){
						GFXText* tempElement = (GFXText*)newElement;
						tempElement->setTextAlignment(v);
					}
					if(strcmp_P(k, PSTR("textsize"))==0){
						GFXText* tempElement = (GFXText*)newElement;
						tempElement->setTextSize(v);
					}
					if(strcmp_P(k, PSTR("font"))==0){
						GFXText* tempElement = (GFXText*)newElement;
						tempElement->setFont(getFontFromId(v));
					}
				}
			}else if(variant.is<bool>()){
				const char* k = key.c_str();
				bool v = variant;
				//Extensions
				//For GFXText
				if(strcmp_P(type, PSTR("GFXText"))==0){
					if(strcmp_P(k, PSTR("textwrap"))==0){
						GFXText* tempElement = (GFXText*)newElement;
						tempElement->setTextWrap(v);
					}
				}
			}
		} 
	}
}
void GFXJson::setFontSlot(uint8_t id, const GFXfont *font){
	this->fonts[id] = font;
}
const GFXfont* GFXJson::getFontFromId(uint8_t id){
	return this->fonts[id];
}
void GFXJson::setTypeHandler(void(*handler)(const char*, GFXLayerInterface*, GFXLayer**)){
	typeHandler = handler;
}
void GFXJson::setCharHandler(void(*handler)(const char*, const char*, const char*, GFXLayer**)){
	charHandler = handler;
}
#endif