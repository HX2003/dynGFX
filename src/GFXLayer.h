#ifndef _GFXLayer_
#define _GFXLayer_

//-------------CONFIGURATION-------------------//
#define ADAFRUIT_GFX_LIB //Comment to disable
//#define TFT_eSPI_LIB //Uncomment to enable
#define GFX_EXTENDED_FEATURES //Comment to disable
#define GFX_USE_JSON_LOADER
#define GFX_USE_SPIFFS
/////////////////////////////////////////////////
#ifdef ADAFRUIT_GFX_LIB
#include <Adafruit_GFX.h>
#endif

#ifdef TFT_eSPI_LIB
#include <TFT_eSPI.h>
#endif

#ifdef GFX_USE_JSON_LOADER
#include <ArduinoJson.h>
#endif

#ifdef GFX_USE_SPIFFS
#include <SPIFFS.h>
#endif
 
#include <LinkedList.h>

#ifdef ADAFRUIT_GFX_LIB
extern Adafruit_GFX* _panel;
#endif

#ifdef TFT_eSPI_LIB
extern TFT_eSPI* _panel;
#endif

#define TEXT_ALIGNMENT_CENTER 1
#define TEXT_ALIGNMENT_2_LEFT 2
#define TEXT_ALIGNMENT_2_RIGHT 3

class GFXLayer{
public:
	LinkedList<GFXLayer*> ElementList = LinkedList<GFXLayer*>();
	GFXLayer(){};
	virtual ~GFXLayer(){};
	virtual void 
	draw(),
	clear(bool delete_me),
	setVisibility(bool value),
	setSimpleOpacity(uint8_t opacity),
	setZIndex(int8_t ZIndex);
	virtual bool isElement();
	virtual uint8_t getSimpleOpacityFirst();
	virtual int8_t getZIndex();
protected: 
	int8_t ZIndex = 0;  
	uint16_t alphaBlendRGB565(uint32_t fg, uint32_t bg, uint8_t alpha);
};

class GFXLayerInterface : public GFXLayer{ 
public:
	#ifdef ADAFRUIT_GFX_LIB
	GFXLayerInterface(Adafruit_GFX *panel):GFXLayer(){_panel=panel;};
	#endif

	#ifdef TFT_eSPI_LIB
	GFXLayerInterface(TFT_eSPI *panel):GFXLayer(){_panel=panel;};
	#endif
	//~GFXLayerInterface();
	void
	add(GFXLayer* element),
	draw(),
	clear(),
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
	virtual ~GFXBaseElement(){};
	virtual void drawOverride();
	void 
	draw(),
	setBackgroundColor(uint16_t backgroundcolor),
	setBackgroundColor888(uint8_t r, uint8_t g, uint8_t b),
	setCursor(int16_t x, int16_t y),
	setVisibility(bool visibility),
	setZIndex(int8_t zindex);
	bool isElement();
	int8_t getZIndex();
	uint8_t getSimpleOpacityFirst();
	uint8_t zindex = 0;
	int16_t x = 0;
	int16_t y = 0;
	uint16_t c = 0xFFFF;
	uint16_t bgc = 0x0000;
	uint8_t simpleopacity = 255;
protected:
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
	int16_t w = 0;
	int16_t h = 0;
protected:
};
//GFXFilledRectangle
class GFXFilledRectangle : public GFXBaseElement{ 
public:
	GFXFilledRectangle():GFXBaseElement(){};
	void 
	fillRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t c),
	drawOverride();
	int16_t w = 0;
	int16_t h = 0;
protected:
};
//GFXRoundRectangle
class GFXRoundRectangle : public GFXBaseElement{ 
public:
	GFXRoundRectangle():GFXBaseElement(){};
	void 
	drawRoundRect(int16_t x, int16_t y, int16_t w, int16_t h, int16_t r, uint16_t c),
	drawOverride();
	int16_t w = 0;
	int16_t h = 0;
	int16_t r = 0;
protected:
};
//GFXFilledRoundRectangle
class GFXFilledRoundRectangle : public GFXBaseElement{ 
public:
	GFXFilledRoundRectangle():GFXBaseElement(){};
	void 
	fillRoundRect(int16_t x, int16_t y, int16_t w, int16_t h, int16_t r, uint16_t c),
	drawOverride();
	int16_t w = 0;
	int16_t h = 0;
	int16_t r = 0;
protected:
};
//GFXTriangle
class GFXTriangle : public GFXBaseElement{ 
public:
	GFXTriangle():GFXBaseElement(){};
	void 
	drawTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint16_t c),
	drawOverride();
	int16_t x1 = 0;
	int16_t y1 = 0;
	int16_t x2 = 0;
    int16_t y2 = 0;
protected:
};
//GFXFilledTriangle
class GFXFilledTriangle : public GFXBaseElement{ 
public:
	GFXFilledTriangle():GFXBaseElement(){};
	void 
    fillTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint16_t c),
	drawOverride();
	int16_t x1 = 0;
	int16_t y1 = 0;
	int16_t x2 = 0;
    int16_t y2 = 0;
protected:
}; 
//GFXText
class GFXText : public GFXBaseElement{ 
public:
	GFXText():GFXBaseElement(){};
	//~GFXText();
	void
	setFont(const GFXfont *font),
	setTextWrap(bool textwrap),
	setTextColor(uint16_t c),
	setTextColor888(uint8_t r, uint8_t g, uint8_t b),
	setTextSize(uint8_t textcolor),
	setTextAlignment(uint8_t alignment),
	print(String text),
	drawOverride();
	String returnTextVal();
protected:
	const GFXfont *font = NULL;
	uint8_t textsize = 1;
	uint8_t alignment = 0;
	bool textwrap = false;
	String text;
};
//GFXGrayscaleBitmap
class GFXGrayscaleBitmap : public GFXBaseElement{ 
public:
	GFXGrayscaleBitmap():GFXBaseElement(){};
	void 
	drawGrayscaleBitmap(int16_t x, int16_t y, const uint8_t *bitmap, int16_t w, int16_t h),
	drawOverride();
protected:
	const uint8_t *bitmap = NULL;
	int16_t w = 0;
	int16_t h = 0;
};
#ifdef GFX_EXTENDED_FEATURES
//GFXTiled565RGBBitmap
class GFXTiled565RGBBitmap : public GFXBaseElement{ 
public:
	GFXTiled565RGBBitmap():GFXBaseElement(){};
	void 
	drawRGBBitmap(int16_t x, int16_t y, const uint16_t *bitmap, int16_t w, int16_t h),
	setTiling(uint16_t tilingx, uint16_t tilingy, uint16_t tilingxspacing, uint16_t tilingyspacing),
	drawOverride();
protected:
	const uint16_t *bitmap = NULL;
	int16_t w = 0;
	int16_t h = 0;
	uint16_t tilingx = 1;
	uint16_t tilingy = 1;
	uint16_t tilingxspacing = 0;
	uint16_t tilingyspacing = 0;
};
//GFXDOTSINDICATOR
class GFXDotsIndicator : public GFXBaseElement{
public:
	GFXDotsIndicator():GFXBaseElement(){}
	void
	drawDotsIndicator(int16_t x, int16_t y, int16_t h, uint16_t tilingx, uint16_t tilingxspacing, uint16_t c, bool centered),
	setDotPosition(uint16_t pos),
	drawOverride();
protected:
	int16_t h = 0;
	uint16_t pos = 0;
    uint16_t tilingx = 1;
	uint16_t tilingxspacing = 0;
	bool centered = false;
};
#endif

#ifdef GFX_USE_JSON_LOADER
class GFXJson{
public:
	#ifdef ADAFRUIT_GFX_LIB
	GFXJson(Adafruit_GFX *panel){_panel=panel;};
	#endif
	
	#ifdef TFT_eSPI_LIB
	GFXJson(TFT_eSPI *panel){_panel=panel;};
	#endif
	
	void 
	load(const __FlashStringHelper* src, GFXLayerInterface* element), //Load from progmem
	load(const String& src, GFXLayerInterface* element), //Load from SPIFFS
	setFontSlot(uint8_t id, const GFXfont *font),
	setTypeHandler(void(*handler)(const char*, GFXLayerInterface*, GFXLayer**)),
	setCharHandler(void(*handler)(const char*, const char*, const char*, GFXLayer**));

	const GFXfont* getFontFromId(uint8_t id);
protected:
	template<typename T>
	void parseJson(T src, GFXLayerInterface* layer);
	void _load(JsonVariant& json, GFXLayerInterface* element);
	const GFXfont *fonts[10];
	void (*typeHandler)(const char*, GFXLayerInterface*, GFXLayer**);
	void (*charHandler)(const char*, const char*, const char*, GFXLayer**);
};
#endif
#endif