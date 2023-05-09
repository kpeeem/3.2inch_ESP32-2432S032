![](Aspose.Words.98013f85-41cc-48b1-b32a-9b435e1418db.001.png) ![](Aspose.Words.98013f85-41cc-48b1-b32a-9b435e1418db.002.png)![](Aspose.Words.98013f85-41cc-48b1-b32a-9b435e1418db.003.png) ![](Aspose.Words.98013f85-41cc-48b1-b32a-9b435e1418db.004.png) ![](Aspose.Words.98013f85-41cc-48b1-b32a-9b435e1418db.005.png)

**Welcome to the JCZN Workshop!** ••••••••••••••••**Table of contents**•••••••••••••••• **一、Introduction**••••••••••••••••••••••••••••••••••••••2 **二、Installing using Arduino IDE**••••••••••••••••••••••••2 **三、sample program usage**••••••••••••••••••••••••••••11 **四、Function introduction**•••••••••••••••••••••••••••••20

**Getting Started**

**Introduction**

The objective of this post is to explain how to upload an Arduino program to the ESP32-2432S032 module, from JCZN .

http://www.jczn1688.com/zlxz

The ESP32 WiFi and Bluetooth chip is the latest generation of Espressif products. It has a dual-core 32-bit MCU, which integrates WiFi HT40 and Bluetooth/BLE4.2 technology inside.

ESP wroom 32 has a significant performance improvement. It is equipped with a high-performance dual-core Tensilica LX6 MCU. One core handles high speed connection and the other for standalone application development. The dual-core MCU has a 240 MHz frequency and a computing power of 600 DMIPS.

In addition, it supports Wi-Fi HT40, Classic Bluetooth/BLE4.2, and more GPIO resources.

**Installing using Arduino IDE**

Programming the ESP32

An easy way to get started is by using the familiar Arduino IDE. While this is not necessarily the best environment for working with the ESP32, it has the advantage of being a familiar application, so the learning curve is flattened.

We will be using the Arduino IDEfor our experiments.

1，Installing using Arduino IDE

we first need to install version 1.8.19 of the Arduino IDE (or greater),for example, the Arduino installation was in “C/Programs(x86)/Arduino”.

download release link:

https://downloads.arduino.cc/arduino-1.8.19-windows.exe

2，This is the way to install Arduino-ESP32 directly from the Arduino IDE.

Add Boards Manager Entry

Here is what you need to do to install the ESP32 boards into the Arduino IDE: （1） Open the Arduino IDE.

![](Aspose.Words.98013f85-41cc-48b1-b32a-9b435e1418db.006.jpeg)

（2）Click on the File menu on the top menu bar.

（3）Click on the Preferences menu item. This will open a Preferences dialog box.

![](Aspose.Words.98013f85-41cc-48b1-b32a-9b435e1418db.007.jpeg)

（4）You should be on the Settings tab in the Preferences dialog box by default.

（5）Look for the textbox labeled “Additional Boards Manager URLs”.

（6）If there is already text in this box add a coma at the end of it, then follow the next step. （7）Paste the following link into the text box ：

Stable release link: https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package\_esp32\_index.json Development release link:

https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package\_esp32\_dev\_index.json （8）Click the OKbutton to save the setting.

The textbox with the JSON link in it is illustrated here:

![](Aspose.Words.98013f85-41cc-48b1-b32a-9b435e1418db.008.jpeg)

9) In the Arduino IDEclick on the Tools menu on the top menu bar.
9) Scroll down to the Board: entry
9) Asubmenu will open when you highlight the Board: entry.
9) At the top of the submenu is Boards Manager. Click on it to open the Boards Manager dialog box. (13)In the search box in the Boards Manager enter “esp32”.

![](Aspose.Words.98013f85-41cc-48b1-b32a-9b435e1418db.009.jpeg)

(14) You should see an entry for “esp32 by Espressif Systems”. Highlight this entry and click on the Install button. This will install the ESP32 boards into your Arduino IDE

![](Aspose.Words.98013f85-41cc-48b1-b32a-9b435e1418db.010.jpeg)

Once the installation completes, we need to select the correct board options for the "ESP32 Arduino" board. In the board type, in the tools tab, we choose “ESP32 Dev Module”.

![](Aspose.Words.98013f85-41cc-48b1-b32a-9b435e1418db.011.jpeg)

![](Aspose.Words.98013f85-41cc-48b1-b32a-9b435e1418db.012.jpeg)

Set and In the programmer entry of the same tab, we choose “esptool”.

![](Aspose.Words.98013f85-41cc-48b1-b32a-9b435e1418db.013.jpeg)

It’s important to note that after the code is uploaded, the device will start to run it. So, if we want to upload a new program, wee need to reset the power of the device, in order to guarantee that it enters flashing mode again.

First program

Since this platform is based on Arduino, we can use many of the usual functions. As an example for the first program, the code bellow starts the Serial port and prints “hello from ESP32”every second.

void setup() {

Serial.begin(115200); }

void loop() {

Serial.println("hello from ESP32"); delay(1000);

}

If everything is working fine, we will see the output in the serial console shown.

![](Aspose.Words.98013f85-41cc-48b1-b32a-9b435e1418db.014.jpeg)

Again thank you for so much concern.. Hopefully, it's the beginning of a wonderful relationship!

**Sample program usage**

At present, only a preliminary explanation and introductory use are given to the samples displayed on the screen, and the corresponding examples in the data center are found, as shown in the figure：

![](Aspose.Words.98013f85-41cc-48b1-b32a-9b435e1418db.015.jpeg)

The examples in the red circle are all based on the Arduino\_GFXlibrary as the basic application. This library supports various commonly used driver chips, such as ST7735, ST7789, ILI9341, etc., and has good compatibility.

Arduino\_GFXlibrary file installation:

Open the librarymanagerin Arduino,search forArduino\_GFX,and clickinstal.

![](Aspose.Words.98013f85-41cc-48b1-b32a-9b435e1418db.016.jpeg)

![](Aspose.Words.98013f85-41cc-48b1-b32a-9b435e1418db.017.jpeg)

Although the Arduino\_GFXI library has many advantages, it may also have a troublesome place for ordinary users, that is, after the installation

![](Aspose.Words.98013f85-41cc-48b1-b32a-9b435e1418db.018.png)![](Aspose.Words.98013f85-41cc-48b1-b32a-9b435e1418db.019.png) ![](Aspose.Words.98013f85-41cc-48b1-b32a-9b435e1418db.020.png) ![](Aspose.Words.98013f85-41cc-48b1-b32a-9b435e1418db.021.png)![](Aspose.Words.98013f85-41cc-48b1-b32a-9b435e1418db.022.png) ![](Aspose.Words.98013f85-41cc-48b1-b32a-9b435e1418db.023.png) ![](Aspose.Words.98013f85-41cc-48b1-b32a-9b435e1418db.024.png)

Find the data center 3\_3-5\_TFT-LVGL-Widgets\_Capacitive touch-gt911As shown：

![](Aspose.Words.98013f85-41cc-48b1-b32a-9b435e1418db.025.jpeg)

Download two library files . One -Arduino\_GFX

![](Aspose.Words.98013f85-41cc-48b1-b32a-9b435e1418db.017.jpeg)

Two -Lvgl

![](Aspose.Words.98013f85-41cc-48b1-b32a-9b435e1418db.026.jpeg)

Copy the User\_Setup.h of the data center . As-shown

![](Aspose.Words.98013f85-41cc-48b1-b32a-9b435e1418db.027.png)

Put this file under the arduino library file, it must be in the same root directory as the library TFT\_eSPI. As shown：

![](Aspose.Words.98013f85-41cc-48b1-b32a-9b435e1418db.028.jpeg)

After compiling, you can run LVGLand touch normally.

![](Aspose.Words.98013f85-41cc-48b1-b32a-9b435e1418db.029.png) ![](Aspose.Words.98013f85-41cc-48b1-b32a-9b435e1418db.030.png)

![](Aspose.Words.98013f85-41cc-48b1-b32a-9b435e1418db.031.png) ![](Aspose.Words.98013f85-41cc-48b1-b32a-9b435e1418db.032.png) ![](Aspose.Words.98013f85-41cc-48b1-b32a-9b435e1418db.033.png)       ![](Aspose.Words.98013f85-41cc-48b1-b32a-9b435e1418db.034.png) ![](Aspose.Words.98013f85-41cc-48b1-b32a-9b435e1418db.035.png)![](Aspose.Words.98013f85-41cc-48b1-b32a-9b435e1418db.036.png)![](Aspose.Words.98013f85-41cc-48b1-b32a-9b435e1418db.037.png)![](Aspose.Words.98013f85-41cc-48b1-b32a-9b435e1418db.038.png)![](Aspose.Words.98013f85-41cc-48b1-b32a-9b435e1418db.039.png)![](Aspose.Words.98013f85-41cc-48b1-b32a-9b435e1418db.040.png)![](Aspose.Words.98013f85-41cc-48b1-b32a-9b435e1418db.041.png)

**一、Basic settings**

1. tft.init(); //Initialization

Initialize the screen, if it is ST7735, you can pass a parameter to it, and see when it is used .

2. tft.fillScreen(TFT\_BLACK); //fill full screen fill full screen, followed by color values. tft.fillScreen(uint32\_t color);
2. Screen rotation

// Set the rotation angle of the screen display, the parameters are: 0, 1, 2, 3

// Represent 0°, 90°, 180°, 270°

void setRotation(uint8\_t r);

4. Screen inversion

//Invert display colors i = 1 invert, i = 0 normal

tft.invertDisplay(bool i);

**二、Text related API**

1. tft.setCursor(20, 10, 4); //Set the starting coordinate position and font size of typing

// Set the text display coordinates. By default, the upper left corner of the text is used as the reference point. The reference point can be changed.

void setCursor(int16\_t x, int16\_t y);

// Set the text display coordinates, and the font of the text

void setCursor(int16\_t x, int16\_t y, uint8\_t font);

2. tft.setTextColor(2); //Set font color

// Set text color

void setTextColor(uint16\_t color);

// Set text color and background color

void setTextColor(uint16\_t fgcolor, uint16\_t bgcolor);

//Setting the background color can effectively prevent numbers from overlapping

3. tft.setTextSize(2); //Set font size

Setting the text size can enlarge the display of the font, but the "resolution" of the font will not change // Set the text size, the text size range is an integer from 1 to 7

void setTextSize(uint8\_t size);

4. tft.print("Hello World!");

// Display font

tft.print("Hello World!");

5. tft.printf, tft.println //Display font

Special Note: Font 7 is an imitation of a 7-segment digital screen

**三、APIs related to drawing text**

1. Draw the string (left)

int16\_t drawString(const String &string, int32\_t x, int32\_t y)

int16\_t drawString(const char \*string, int32\_t x, int32\_t y)

int16\_t drawString(const String &string, int32\_t x, int32\_t y, uint8\_t font) int16\_t drawString(const char \*string, int32\_t x, int32\_t y, uint8\_t font)

2. Draw the string (centered)

int16\_t drawCentreString(const char \*string, int32\_t x, int32\_t y, uint8\_t font) int16\_t drawCentreString(const String &string, int32\_t x, int32\_t y, uint8\_t font)

3. Draw the string (right)

int16\_t drawRightString(const char \*string, int32\_t x, int32\_t y, uint8\_t font) int16\_t drawRightString(const String &string, int32\_t x, int32\_t y, uint8\_t font)

4. Drawing characters

int16\_t drawChar(uint16\_t uniCode, int32\_t x, int32\_t y)

int16\_t drawChar(uint16\_t uniCode, int32\_t x, int32\_t y, uint8\_t font)

void drawChar(int32\_t x, int32\_t y, uint16\_t c, uint32\_t color, uint32\_t bg, uint8\_t size)

5. Plot floating point numbers

int16\_t TFT\_eSPI::drawFloat(float floatNumber, uint8\_t decimal, int32\_t x, int32\_t y)

int16\_t TFT\_eSPI::drawFloat(float floatNumber, uint8\_t decimal, int32\_t x, int32\_t y, uint8\_t font)

tft.drawFloat(3.124, 4, 0,0,4);

6. Draw the numbers

int16\_t drawNumber(long intNumber, int32\_t x, int32\_t y)

int16\_t drawNumber(long intNumber, int32\_t x, int32\_t y, uint8\_t font)

**四、Drawing geometric figures**

1. Draw the dots

void drawPixel(int32\_t x, int32\_t y, uint32\_t color)

2. Draw lines

void drawLine(int32\_t xs, int32\_t ys, int32\_t xe, int32\_t ye, uint32\_t color)

3. Draw a horizontal line (quick)

void drawFastHLine(int32\_t x, int32\_t y, int32\_t w, uint32\_t color)

4. Draw a vertical line (quick)

void drawFastVLine(int32\_t x, int32\_t y, int32\_t h, uint32\_t color)

5. Draw the hollow circle

tft.drawCircle(100, 100,50,TFT\_RED);

6. Draw a filled circle

void fillCircle(int32\_t x, int32\_t y, int32\_t r, uint32\_t color)

7. Draw a hollow ellipse

tft.drawEllipse(100, 100, 100,60,TFT\_GREENYELLOW);

8. Draw a solid ellipse

void drawRect(int32\_t x, int32\_t y, int32\_t w, int32\_t h, uint32\_t color)

9. Draw a hollow rectangle

void drawRect(int32\_t x, int32\_t y, int32\_t w, int32\_t h, uint32\_t color)

10. Draw a solid rectangle

void fillRect(int32\_t x, int32\_t y, int32\_t w, int32\_t h, uint32\_t color)

11. Draw a hollow rounded rectangle

void drawRoundRect(int32\_t x, int32\_t y, int32\_t w, int32\_t h, int32\_t radius, uint32\_t color)

12. Draw a solid rounded rectangle

void fillRoundRect(int32\_t x, int32\_t y, int32\_t w, int32\_t h, int32\_t radius, uint32\_t color)

13. Draw Hollow Triangles

void drawTriangle(int32\_t x1, int32\_t y1, int32\_t x2, int32\_t y2, int32\_t x3, int32\_t y3, uint32\_t color)

14. Draw Solid Triangles

void fillTriangle(int32\_t x1, int32\_t y1, int32\_t x2, int32\_t y2, int32\_t x3, int32\_t y3, uint32\_t color)

**五、Image display related**

1. Display BMP picture

void drawBitmap(int16\_t x, int16\_t y, const uint8\_t \*bitmap, int16\_t w, int16\_t h, uint16\_t fgcolor)

void drawBitmap(int16\_t x, int16\_t y, const uint8\_t \*bitmap, int16\_t w, int16\_t h, uint16\_t fgcolor, uint16\_t bgcolor)

2. XBM

xbm is a simple two-color image bitmap format, which was widely used in early cgi and is currently used in counters. Here TFT\_eSPI recommends an online XBM production toolxbm is a simple two-color image bitmap format, which was widely used in early cgi and is currently used in counters. Here TFT\_eSPIrecommends an online XBM production tool [https://www.online-utility.org/image/convert/to/XBM](https://links.jianshu.com/go?to=https%3A%2F%2Fwww.online-utility.org%2Fimage%2Fconvert%2Fto%2FXBM)

3. Test is very useful

void drawXBitmap(int16\_t x, int16\_t y, const uint8\_t \*bitmap, int16\_t w, int16\_t h, uint16\_t fgcolor)

void drawXBitmap(int16\_t x, int16\_t y, const uint8\_t \*bitmap, int16\_t w, int16\_t h, uint16\_t fgcolor, uint16\_t bgcolor)

Display pictures

void pushImage(int32\_t x, int32\_t y, int32\_t w, int32\_t h, const uint16\_t \*data) void pushImage(int32\_t x, int32\_t y, int32\_t w, int32\_t h, uint16\_t \*data)

void pushImage(int32\_t x, int32\_t y, int32\_t w, int32\_t h, const uint16\_t \*data, uint16\_t transparent)

void pushImage(int32\_t x, int32\_t y, int32\_t w, int32\_t h, uint16\_t \*data, uint16\_t transparent)

void pushImage(int32\_t x, int32\_t y, int32\_t w, int32\_t h, uint8\_t \*data, bool bpp8 = true, uint16\_t \*cmap = (uint16\_t \*)nullptr)

void pushImage(int32\_t x, int32\_t y, int32\_t w, int32\_t h, uint8\_t \*data, uint8\_t transparent, bool bpp8 = true, uint16\_t \*cmap = (uint16\_t \*)nullptr)
**http://www.jczn1688.com/** 第 19 页 共 19 页
