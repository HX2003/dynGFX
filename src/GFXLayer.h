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
	setZIndex(int8_t ZIndex);
	virtual uint8_t getSimpleOpacityFirst();
	virtual int8_t getZIndex();
protected: 
	int8_t ZIndex = 0;  
	uint16_t alphaBlendRGB565(uint32_t fg, uint32_t bg, uint8_t alpha);
};

class GFXLayerInterface : public GFXLayer{ 
public:
	GFXLayerInterface(Adafruit_GFX *panel):GFXLayer(){_panel=panel;};
	//~GFXLayerInterface();
	void
	add(GFXLayer* element),
	draw(),
	setSimpleOpacity(uint8_t opacity),
	setVisibility(bool value),
	setZIndex(int8_t ZIndex);
	uint8_t getSimpleOpacityFirst();
	int8_t getZIndex();
protected:
	void sort();
};
class GFXBaseElement : public GFXLayer{ 
public:
	GFXBaseElement():GFXLayer(){};
	virtual void drawOverride();
	void 
	draw(),
	setBackgroundColor(uint16_t backgroundcolor),
	setBackgroundColor888(uint8_t r, uint8_t g, uint8_t b),
	setCursor(int16_t x, int16_t y),
	setVisibility(bool visibility),
	setZIndex(int8_t zindex);
	int8_t getZIndex();
	uint8_t getSimpleOpacityFirst();
protected:
	uint8_t zindex = 0;
	int16_t x = 0;
	int16_t y = 0;
	uint16_t c = 0xFFFFF;
	uint16_t bgc = 0x0000;
	uint8_t simpleopacity = 255;
};
	//template <typename T>
	//void print(T text){
	//	ZIndex = GFX_TYPE_TEXT;
	//};
//GFXRectangle
class GFXRectangle : public GFXBaseElement{ 
public:
	GFXRectangle():GFXBaseElement(){};
	void 
	drawRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t c),
	drawOverride();
protected:
	int16_t w = 0;
	int16_t h = 0;
};
//GFXFilledRectangle
class GFXFilledRectangle : public GFXBaseElement{ 
public:
	GFXFilledRectangle():GFXBaseElement(){};
	void 
	fillRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t c),
	drawOverride();
protected:
	int16_t w = 0;
	int16_t h = 0;
};
//GFXRoundRectangle
class GFXRoundRectangle : public GFXBaseElement{ 
public:
	GFXRoundRectangle():GFXBaseElement(){};
	void 
	drawRoundRect(int16_t x, int16_t y, int16_t w, int16_t h, int16_t r, uint16_t c),
	drawOverride();
protected:
	int16_t w = 0;
	int16_t h = 0;
	int16_t r = 0;
};
//GFXFilledRoundRectangle
class GFXFilledRoundRectangle : public GFXBaseElement{ 
public:
	GFXFilledRoundRectangle():GFXBaseElement(){};
	void 
	fillRoundRect(int16_t x, int16_t y, int16_t w, int16_t h, int16_t r, uint16_t c),
	drawOverride();
protected:
	int16_t w = 0;
	int16_t h = 0;
	int16_t r = 0;
};
//GFXTriangle
class GFXTriangle : public GFXBaseElement{ 
public:
	GFXTriangle():GFXBaseElement(){};
	void 
	drawTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint16_t c),
	drawOverride();
protected:
	int16_t x1 = 0;
	int16_t y1 = 0;
	int16_t x2 = 0;
    int16_t y2 = 0;
};
//GFXFilledTriangle
class GFXFilledTriangle : public GFXBaseElement{ 
public:
	GFXFilledTriangle():GFXBaseElement(){};
	void 
    fillTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint16_t c),
	drawOverride();
protected:
	int16_t x1 = 0;
	int16_t y1 = 0;
	int16_t x2 = 0;
    int16_t y2 = 0;
}; 
//GFXText
class GFXText : public GFXBaseElement{ 
public:
	GFXText():GFXBaseElement(){};
	//~GFXText();
	void
	setFont(const GFXfont *font),
	setTextWrap(bool textwrap),
	setTextColor(uint16_t textcolor),
	setTextColor888(uint8_t r, uint8_t g, uint8_t b),
	setTextSize(uint8_t textcolor),
	print(String text),
	drawOverride();
	String returnTextVal();
protected:
	const GFXfont *font = NULL;
	uint8_t textsize = 1;
	bool textwrap = false;
	String text;
};
//GFXTiled565RGBBitmap
class GFXTiled565RGBBitmap : public GFXBaseElement{ 
public:
	GFXTiled565RGBBitmap():GFXBaseElement(){};
	void 
	drawRGBBitmap(int16_t x, int16_t y, const uint16_t *bitmap, int16_t w, int16_t h),
	setTiling(uint16_t tilingx, uint16_t tilingy, uint16_t tilingxmargin, uint16_t tilingymargin),
	drawOverride();
protected:
	const uint16_t *bitmap = NULL;
	int16_t w = 0;
	int16_t h = 0;
	uint16_t tilingx = 1;
	uint16_t tilingy = 1;
	uint16_t tilingxmargin = 0;
	uint16_t tilingymargin = 0;
};
#endif