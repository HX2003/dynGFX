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
void GFXText::setTextCentered(bool centered){
	this->centered = centered;
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
	if(centered){
		int16_t x1, y1;
		uint16_t w1, h1;
		_panel->getTextBounds(text, 0, 0, &x1, &y1, &w1, &h1);
		_panel->setCursor((_panel->width() - w1) / 2, y);
	}else{
		_panel->setCursor(x, y);
	}
	_panel->print(text);
	//_panel->display(); use only for matrix
}
String GFXText::returnTextVal(){
	return text;
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