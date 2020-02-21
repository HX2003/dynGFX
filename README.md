# dynGFX
This library is very much in its alpha stage. Best used with a library that supports double buffering or it will be very slow. Make sure you have lots of ram to spare.

# Getting started

You'll need to install the [LinkedList library](https://github.com/ivanseidel/LinkedList).

Configure for either Adafruit GFX or TFT_eSPI Library in GFXLayer.h

In your sketch include this library.

`#include <GFXLayer.h>`

Pass your pointer of an instance of the display you're using. This creates a main layer.

`GFXLayerInterface MainLayer(&tft);`

Add to your main loop.

`MainLayer.draw();`

Create more layers.

```
GFXLayerInterface AnotherLayer(&tft);
```
|Supported GFX Elements | 
|-----------------------| 
|      GFXRectangle     | 
|   GFXFilledRectangle  |
|   GFXRoundRectangle   |
|GFXFilledRoundRectangle|
|      GFXTriangle      |
|   GFXFilledTriangle   |
|        GFXText        |
|   GFXGrayscaleBitmap* |

| Extended GFX Elements | 
|-----------------------| 
|  GFXTiled565RGBBitmap |
|    GFXDotsIndicator   |

Create elements.
```
GFXText notifyTextElement = GFXText();
GFXRectangle myRectElement = GFXRectangle();
```
or
```
GFXText notifyTextElement;
GFXRectangle myRectElement;
```
Add layer to a layer.

` MainLayer.add(&AnotherLayer); `

Add element to a layer.

`AnotherLayer.add(&notifyTextElement);`

Set visibility.

`notifyTextElement.setVisibility(true);`

Set ZIndex.

`notifyTextElement.setZIndex(1);`

# Demo sketch output

(This is running on esp8266)

![ILI9341 Example](data/ILI9341Layers.gif)

# Experimental

Loading from a json file.

# Limitations
× True alpha blending not yet supported.
