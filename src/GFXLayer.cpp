#ifndef _GFXLayer_
	#include "GFXLayer.h"
#endif
Adafruit_GFX* _panel;

void GFXLayer::draw(){
	GFXLayer* GFXLayer;
	for(int i = 0; i < ElementList.size(); i++){
		GFXLayer = ElementList.get(i);
		GFXLayer->draw();
	}
};
void GFXLayer::setVisibility(bool visibility){
	GFXLayer* GFXLayer;
	for(int i = 0; i < ElementList.size(); i++){
		GFXLayer = ElementList.get(i);
		GFXLayer->setVisibility(visibility);
	}
};
void GFXLayer::setSimpleOpacity(uint8_t opacity){
	GFXLayer* GFXLayer;
	for(int i = 0; i < ElementList.size(); i++){
		GFXLayer = ElementList.get(i);
		GFXLayer->setSimpleOpacity(opacity);
	}
};
void GFXLayer::setSimpleOpacityAuto(uint8_t simpleopacity){
	GFXLayer* GFXLayer;
	for(int i = 0; i < ElementList.size(); i++){
		GFXLayer = ElementList.get(i);
		GFXLayer->setSimpleOpacityAuto(simpleopacity);
	}
};
uint8_t GFXLayer::getSimpleOpacityFirst(){
	GFXLayer* GFXLayer;
		GFXLayer = ElementList.get(0);
		return (GFXLayer->getSimpleOpacityFirst());
};
int8_t GFXLayer::getZIndex(){
	GFXLayer* GFXLayer;
		GFXLayer = ElementList.get(0);
		return (GFXLayer->getZIndex());
};
uint16_t GFXLayer::alphaBlendRGB565( uint32_t fg, uint32_t bg, uint8_t alpha){
    alpha = alpha >> 3;
    bg = (bg | (bg << 16)) & 0b00000111111000001111100000011111;
    fg = (fg | (fg << 16)) & 0b00000111111000001111100000011111;
    uint32_t result = ((((fg - bg) * alpha) >> 5) + bg) & 0b00000111111000001111100000011111;
    return (uint16_t)((result >> 16) | result);
}
//tiled565RGBBitmap Element 
void tiled565RGBBitmapElement::setZIndex(int8_t zindex){
	_zindex = zindex;
}
void tiled565RGBBitmapElement::setVisibility(bool visibility){
	_visibility=visibility;
}
void tiled565RGBBitmapElement::setSimpleOpacity(uint8_t simpleopacity){
	_simpleopacity=simpleopacity;
}
void tiled565RGBBitmapElement::setSimpleOpacityAuto(uint8_t simpleopacity){
	_simpleopacity=simpleopacity;
	if(_simpleopacity<=8){
		_visibility=false;
	}else if(_simpleopacity>8){
		_visibility=true;
	}
}
void tiled565RGBBitmapElement::setBackgroundColor(uint16_t backgroundcolor){
	_backgroundcolor=backgroundcolor;
}
void tiled565RGBBitmapElement::drawRGBBitmap(uint16_t x, uint16_t y, const uint16_t *bitmap, uint16_t w, uint16_t h){
	_x=x;
	_y=y;
	_bitmap=bitmap;
	_w=w;
	_h=h;
};
void tiled565RGBBitmapElement::setCursor(uint16_t cursorx, uint16_t cursory){
	_cursorx=cursorx;
	_cursory=cursory;
}
uint8_t tiled565RGBBitmapElement::getSimpleOpacityFirst(){
	return _simpleopacity;
}
void tiled565RGBBitmapElement::setTiling(uint16_t tilingx, uint16_t tilingy, uint16_t tilingxmargin, uint16_t tilingymargin){
	_tilingx=tilingx;
	_tilingy=tilingy;
	_tilingxmargin=tilingxmargin;
	_tilingymargin=tilingymargin;
}
void tiled565RGBBitmapElement::draw(){
	if(_visibility){
	for(int16_t a=0; a<_tilingx; a++){
		for(int16_t b=0; b<_tilingy; b++){ 
			for(int16_t j=0; j<_h; j++) {
				for(int16_t i=0; i<_w; i++ ) {
					_panel->writePixel(_x+i+a*(_w+_tilingxmargin)+_cursorx, _y+j+b*(_h+_tilingymargin)+_cursory, alphaBlendRGB565(pgm_read_word(&_bitmap[j * _w + i]),_backgroundcolor,_simpleopacity));
				}
			}
		}
	}
	}
}
int8_t tiled565RGBBitmapElement::getZIndex(){
	return _zindex;
}
//Rectangle Element
void rectangleElement::setZIndex(int8_t zindex){
	_zindex = zindex;
}
void rectangleElement::setVisibility(bool visibility){
	_visibility=visibility;
}
void rectangleElement::setSimpleOpacity(uint8_t simpleopacity){
	_simpleopacity=simpleopacity;
}
void rectangleElement::setSimpleOpacityAuto(uint8_t simpleopacity){
	_simpleopacity=simpleopacity;
	if(_simpleopacity<=8){
		_visibility=false;
	}else if(_simpleopacity>8){
		_visibility=true;
	}
}
void rectangleElement::setBackgroundColor(uint16_t backgroundcolor){
	_backgroundcolor=backgroundcolor;
}
void rectangleElement::drawRect(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t rectcolor){
	_x=x;
	_y=y;
	_w=w;
	_h=h;
	_rectcolor=rectcolor;
};
void rectangleElement::setCursor(uint16_t cursorx, uint16_t cursory){
	_cursorx=cursorx;
	_cursory=cursory;
}
uint8_t rectangleElement::getSimpleOpacityFirst(){
	return _simpleopacity;
}
void rectangleElement::draw(){
	if(_visibility){
	_panel->drawRect(_x,_y,_w,_h, alphaBlendRGB565(_rectcolor,_backgroundcolor,_simpleopacity));
	}
}
int8_t rectangleElement::getZIndex(){
	return _zindex;
}
//filledRectangleElement
void filledRectangleElement::setZIndex(int8_t zindex){
	_zindex = zindex;
}
void filledRectangleElement::setVisibility(bool visibility){
	_visibility=visibility;
}
void filledRectangleElement::setSimpleOpacity(uint8_t simpleopacity){
	_simpleopacity=simpleopacity;
}
void filledRectangleElement::setSimpleOpacityAuto(uint8_t simpleopacity){
	_simpleopacity=simpleopacity;
	if(_simpleopacity<=8){
		_visibility=false;
	}else if(_simpleopacity>8){
		_visibility=true;
	}
}
void filledRectangleElement::setBackgroundColor(uint16_t backgroundcolor){
	_backgroundcolor=backgroundcolor;
}
void filledRectangleElement::fillRect(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t rectcolor){
	_x=x;
	_y=y;
	_w=w;
	_h=h;
	_rectcolor=rectcolor;
};
void filledRectangleElement::setCursor(uint16_t cursorx, uint16_t cursory){
	_cursorx=cursorx;
	_cursory=cursory;
}
uint8_t filledRectangleElement::getSimpleOpacityFirst(){
	return _simpleopacity;
}
void filledRectangleElement::draw(){
	if(_visibility){
	_panel->fillRect(_x,_y,_w,_h, alphaBlendRGB565(_rectcolor,_backgroundcolor,_simpleopacity));
	}
}
int8_t filledRectangleElement::getZIndex(){
	return _zindex;
}
//textElement
void textElement::print(String text){
	_text=text;
}
String textElement::returnVal(){
	return _text;
}
void textElement::setZIndex(int8_t zindex){
	_zindex = zindex;
}
void textElement::setVisibility(bool visibility){
	_visibility=visibility;
}
void textElement::setSimpleOpacity(uint8_t simpleopacity){
	_simpleopacity=simpleopacity;
}
void textElement::setSimpleOpacityAuto(uint8_t simpleopacity){
	_simpleopacity=simpleopacity;
	if(_simpleopacity<=8){
		_visibility=false;
	}else if(_simpleopacity>8){
		_visibility=true;
	}
}
void textElement::setFont(const GFXfont *font){
    _font=font;
}

void textElement::setTextWrap(bool textwrap){
	_textwrap=textwrap;
}
void textElement::setTextSize(uint8_t textsize){
	_textsize=textsize;
}
void textElement::setBackgroundColor(uint16_t backgroundcolor){
	_backgroundcolor=backgroundcolor;
}
void textElement::setBackgroundColor888(uint8_t r, uint8_t g, uint8_t b){
	_backgroundcolor=((uint16_t)(r & 0xF8) << 8) | ((uint16_t)(g & 0xFC) << 3) | (b >> 3);
}
void textElement::setTextColor(uint16_t textcolor){
	_textcolor=textcolor;
}
void textElement::setTextColor888(uint8_t r, uint8_t g, uint8_t b){
	_textcolor=((uint16_t)(r & 0xF8) << 8) | ((uint16_t)(g & 0xFC) << 3) | (b >> 3);
}

void textElement::setCursor(uint16_t cursorx, uint16_t cursory){
	_cursorx=cursorx;
	_cursory=cursory;
}
int8_t textElement::getZIndex(){
	return _zindex;
}
uint8_t textElement::getSimpleOpacityFirst(){
	return _simpleopacity;
}
void textElement::draw(void){
	if(_visibility){
		char _buf[_text.length()+2];
		_text.toCharArray(_buf,_text.length()+1);
		_panel->setFont(_font);
		_panel->setTextWrap(_textwrap);
		_panel->setTextSize(_textsize);
		_panel->setTextColor(alphaBlendRGB565(_textcolor,_backgroundcolor,_simpleopacity));
		_panel->setCursor(_cursorx,_cursory);
		_panel->print(_buf);
		//_panel->display(); use only for matrix
	}	 
}
void GFXLayerInterface::addElement(GFXLayer *element){
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
  if(lhs->getZIndex()<rhs->getZIndex()){
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
};
void GFXLayerInterface::setSimpleOpacityAuto(uint8_t opacity){
	GFXLayer::setSimpleOpacityAuto(opacity);	
};
void GFXLayerInterface::setVisibility(bool visibility){
	GFXLayer::setVisibility(visibility);
}

uint8_t GFXLayerInterface::getSimpleOpacityFirst(){
	return GFXLayer::getSimpleOpacityFirst();
}