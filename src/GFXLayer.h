#ifndef _GFXLayer_
#define _GFXLayer_

#include <Adafruit_GFX.h>
#include <LinkedList.h>

extern Adafruit_GFX* _panel;

class GFXLayer{
  public:
    LinkedList<GFXLayer*> ElementList = LinkedList<GFXLayer*>();
    GFXLayer(){};
    ~GFXLayer(){};
  virtual void 
   draw(),
   setVisibility(bool value),
   setSimpleOpacity(uint8_t opacity),
   setSimpleOpacityAuto(uint8_t opacity);
  virtual uint8_t getSimpleOpacityFirst();
  protected:  
  uint16_t 
	alphaBlendRGB565( uint32_t fg, uint32_t bg, uint8_t alpha);
};
class tiled565RGBBitmapElement : public GFXLayer{ 
public:
	tiled565RGBBitmapElement():GFXLayer(){
		_bitmap=NULL;
		_backgroundcolor=0;
		_cursorx=0;
		_cursory=0;
		_x=0;
		_y=0;
		_w=0;
		_h=0;
		_tilingx=1;
	    _tilingy=1;
	    _tilingxmargin=0;
	    _tilingymargin=0;
		_visibility=true;
		_simpleopacity=255;
	};
void 
	drawRGBBitmap(uint16_t x, uint16_t y, const uint16_t *bitmap, uint16_t w, uint16_t h),
	draw(),
	setBackgroundColor(uint16_t backgroundcolor),
	setVisibility(bool value),
    setSimpleOpacity(uint8_t opacity),
    setSimpleOpacityAuto(uint8_t opacity),
	setTiling(uint16_t tilingx, uint16_t tilingy, uint16_t tilingxmargin, uint16_t tilingymargin),
	setCursor(uint16_t cursorx, uint16_t cursory);
uint8_t getSimpleOpacityFirst();
protected:
	uint8_t  
	 _simpleopacity;
    const uint16_t *_bitmap;
	uint16_t
	 _backgroundcolor,
	 _cursorx,
	 _cursory,
	 _x,
	 _y,
	 _w,
	 _h,
	 _tilingx,
	 _tilingy,
	 _tilingxmargin,
	 _tilingymargin;
	bool
	 _visibility;
};
class rectangleElement : public GFXLayer{ 
public:
	rectangleElement():GFXLayer(){
		_rectcolor=0xFFFF;
		_backgroundcolor=0;
		_cursorx=0;
		_cursory=0;
		_x=0;
		_y=0;
		_w=0;
		_h=0;
		_visibility=true;
		_simpleopacity=255;
	};
void 
	drawRect(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t rectcolor),
	draw(),
	setBackgroundColor(uint16_t backgroundcolor),
	setVisibility(bool value),
    setSimpleOpacity(uint8_t opacity),
    setSimpleOpacityAuto(uint8_t opacity),
	setCursor(uint16_t cursorx, uint16_t cursory);
uint8_t getSimpleOpacityFirst();
protected:
	uint8_t  
	 _simpleopacity;
	uint16_t
	 _rectcolor,
	 _backgroundcolor,
	 _cursorx,
	 _cursory,
	 _x,
	 _y,
	 _w,
	 _h;
	bool
	 _visibility;
};
class filledRectangleElement : public GFXLayer{ 
public:
	filledRectangleElement():GFXLayer(){
		_rectcolor=0xFFFF;
		_backgroundcolor=0;
		_cursorx=0;
		_cursory=0;
		_x=0;
		_y=0;
		_w=0;
		_h=0;
		_visibility=true;
		_simpleopacity=255;
	};
void 
	fillRect(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t rectcolor),
	draw(),
	setBackgroundColor(uint16_t backgroundcolor),
	setVisibility(bool value),
    setSimpleOpacity(uint8_t opacity),
    setSimpleOpacityAuto(uint8_t opacity),
	setCursor(uint16_t cursorx, uint16_t cursory);
uint8_t getSimpleOpacityFirst();
protected:
	uint8_t  
	 _simpleopacity;
	uint16_t
	 _rectcolor,
	 _backgroundcolor,
	 _cursorx,
	 _cursory,
	 _x,
	 _y,
	 _w,
	 _h;
	bool
	 _visibility;
};
class textElement : public GFXLayer{ 
public:
	textElement():GFXLayer(){
		_font=NULL;
		_textwrap=false;
		_textsize=1;
		_textcolor=0xFFFF;
		_backgroundcolor=0;
		_cursorx=0;
		_cursory=0;
		_visibility=true;
		_simpleopacity=255;
	};
	//~textElement();
void
	setVisibility(bool value),
	setSimpleOpacity(uint8_t opacity),
	setSimpleOpacityAuto(uint8_t opacity),
	setFont(const GFXfont *font),
	setTextWrap(bool textwrap),
	setCursor(uint16_t cursorx, uint16_t cursory),
	setTextColor(uint16_t textcolor),
	setTextColor888(uint8_t r, uint8_t g, uint8_t b),
	setBackgroundColor(uint16_t backgroundcolor),
	setBackgroundColor888(uint8_t r, uint8_t g, uint8_t b),
	setTextSize(uint8_t textcolor),
	print(String text),
	draw();
uint8_t getSimpleOpacityFirst();
String returnVal();
protected:
	const GFXfont *_font;
	uint8_t 
	 _textsize,
	 _simpleopacity;
	uint16_t
	 _textcolor,
	 _backgroundcolor,
	 _cursorx,
	 _cursory;
    bool
	 _textwrap,
     _visibility;
	String
     _text;
	
};
class GFXLayerInterface : public GFXLayer{ 
  public:
  GFXLayerInterface(Adafruit_GFX *panel):GFXLayer(){_panel=panel;};
  //~GFXLayerInterface();
  void
	addElement(GFXLayer* element),
	draw(),
	setSimpleOpacity(uint8_t opacity),
	setSimpleOpacityAuto(uint8_t opacity),
	setVisibility(bool value);
  uint8_t getSimpleOpacityFirst();
  protected:
};
#endif
