// Basic usage

// * If you use a compatible model in an environment other than Arduino IDE,
// If the compatible model is not in the board manager (TTGO T-Wristband, ESP-WROVER-KIT, etc.),
// Please describe the definition of define LGFX_ ～ before including in LovyanGFX.hpp.

// #define LGFX_M5STACK               // M5Stack (Basic / Gray / Go / Fire)
// #define LGFX_M5STACK_CORE2         // M5Stack Core2
// #define LGFX_M5STACK_COREINK       // M5Stack CoreInk
// #define LGFX_M5STICK_C             // M5Stick C / CPlus
// #define LGFX_M5PAPER // M5Paper
// #define LGFX_ODROID_GO             // ODROID-GO
// #define LGFX_TTGO_TS               // TTGO TS
// #define LGFX_TTGO_TWATCH           // TTGO T-Watch
// #define LGFX_TTGO_TWRISTBAND       // TTGO T-Wristband
// #define LGFX_DDUINO32_XS           // DSTIKE D-duino-32 XS
// #define LGFX_LOLIN_D32_PRO         // LoLin D32 Pro
// #define LGFX_ESP_WROVER_KIT        // ESP-WROVER-KIT
// #define LGFX_WIFIBOY_PRO           // WiFiBoy Pro
// #define LGFX_WIFIBOY_MINI          // WiFiBoy mini
// #define LGFX_MAKERFABS_TOUCHCAMERA // Makerfabs Touch with Camera
// #define LGFX_MAKERFABS_MAKEPYTHON  // Makerfabs MakePython
// #define LGFX_WIO_TERMINAL          // Wio Terminal

  #define LGFX_AUTODETECT // 自動認識 (M5Stack, M5StickC/CPlus, ODROID-GO, TTGO T-Watch, TTGO T-Wristband, LoLin D32 Pro, ESP-WROVER-KIT)

// By defining multiple models or defining LGFX_AUTODETECT, the board will be automatically recognized at runtime.


// Include the header.
#include <LovyanGFX.hpp>

static LGFX lcd;                  // Create an instance of LGFX.
static LGFX_Sprite sprite (& lcd); // Create an instance of LGFX_Sprite when using sprites.

// If you are currently using TFT_eSPI and don't want to change the source as much as possible, you can use this header.
// #include <LGFX_TFT_eSPI.hpp>
// static TFT_eSPI lcd; // TFT_eSPI is defined as an alias for LGFX.
// static TFT_eSprite sprite (& lcd); // TFT_eSprite is defined as an alias for LGFX_Sprite.


// See examples / HowToUse / 2_spi_setting.ino if you want to use it in a configuration that is not available on compatible models.
// Copy LGFX_Config_Custom.hpp in the config folder and edit it to suit your environment
// Include here or paste the contents of the file as it is and use it.


void setup(void)
{
// First call the initialization function.
  lcd.init();


// Set the rotation direction from 4 directions from 0 to 3. (If you use 4 to 7, it will be upside down.)
  lcd.setRotation(1);


// Set the backlight brightness in the range 0-255.
  lcd.setBrightness(128);


// Set the color mode as needed. (Initial value is 16)
// 16 has less SPI traffic and operates faster, but the red and blue tones are 5 bits.
// 24 has more SPI traffic, but the gradation expression is cleaner.
// lcd.setColorDepth (16); // Set to 16-bit RGB565
  lcd. setColorDepth ( 24 );   // Set to 24 bits for RGB888 (The number of colors displayed will be 18 bits for RGB666 depending on the panel performance)


// The basic figure drawing function is as follows.
/*
  fillScreen (color); // Fill the entire screen
  drawPixel     ( x, y         , color);  // 点
  drawFastVLine (x, y, h, color); // vertical line
  drawFastHLine (x, y, w, color); // horizontal line
  drawRect (x, y, w, h, color); // outer circumference of the rectangle
  fillRect (x, y, w, h, color); // Rectangle fill
  drawRoundRect (x, y, w, h, r, color); // Outer circumference of a rounded rectangle
  fillRoundRect (x, y, w, h, r, color); // Fill rectangle with rounded corners
  drawCircle (x, y, r, color); // Circle circumference
  fillCircle (x, y, r, color); // Fill the circle
  drawEllipse (x, y, rx, ry, color); // Outer circumference of the ellipse
  fillEllipse (x, y, rx, ry, color); // Fill the ellipse
  drawLine (x0, y0, x1, y1, color); // Straight line between two points
  drawTriangle (x0, y0, x1, y1, x2, y2, color); // The outer circumference of the triangle between the three points
  fillTriangle (x0, y0, x1, y1, x2, y2, color); // Fill the triangle between 3 points
  drawBezier (x0, y0, x1, y1, x2, y2, color); // Bezier curve between 3 points
  drawBezier (x0, y0, x1, y1, x2, y2, x3, y3, color); // Bezier curve between 4 points
  drawArc (x, y, r0, r1, angle0, angle1, color); // Outer circumference of the arc
  fillArc (x, y, r0, r1, angle0, angle1, color); // Fill the arc
*/


// For example, when drawing a point with drawPixel, there are three arguments: X coordinate, Y coordinate, and color.
  lcd. drawPixel ( 0 , 0 , 0xFFFF ); // draw a white dot at coordinates 0: 0


// A function to generate a color code is provided and can be used to specify a color.
// For the argument, specify red, green, and blue from 0 to 255, respectively.
// It is recommended to use color888 to prevent missing color information.
  lcd. drawFastVLine ( 2 , 0 , 100 , lcd. color888 ( 255 ,    0 ,    0 )); // Draw a vertical line in red
  lcd. drawFastVLine ( 4 , 0 , 100 , lcd. color565 (   0 , 255 ,    0 )); // Draw a vertical line in green
  lcd. drawFastVLine ( 6 , 0 , 100 , lcd. color332 (   0 ,    0 , 255 )); // Draw a vertical line in blue


// If the color code generation function is not used, it will be as follows.
// RGB888 24-bit specified uint32_t type
// RGB565 16-bit specification uint16_t type, int32_t type
// RGB332 Specify with 8 bits uint8_t type

// If you use uint32_t type, it will be treated as 24-bit RGB888.
// You can write in the order of red, green, and blue with 2 hexadecimal digits.
// Use a uint32_t type variable, add a U at the end, or cast it to a uint32_t type.
  uint32_t red = 0xFF0000;
  lcd. drawFastHLine ( 0 , 2 , 100 , red);             // Draw a horizontal line in red
  lcd. drawFastHLine ( 0 , 4 , 100 , 0x00FF00U );       // Draw a horizontal line in green
  lcd. drawFastHLine ( 0 , 6 , 100 , ( uint32_t ) 0xFF ); // Draw a horizontal line in blue


// If you use uint16_t type and int32_t type, it will be treated as 16 bits of RGB565.
// If you do not write it in a special way, it will be treated as int32_t type, so this method will be used.
// (This is done for compatibility with AdafruitGFX and TFT_eSPI.)
  uint16_t green = 0x07E0;
  lcd. drawRect ( 10 , 10 , 50 , 50 , 0xF800 );          // Draw the outer circumference of the rectangle in red
  lcd. drawRect ( 12 , 12 , 50 , 50 , green);           // Draw the outer circumference of the rectangle in green
  lcd. drawRect ( 14 , 14 , 50 , 50 , ( uint16_t ) 0x1F ); // Draw the outer circumference of the rectangle in blue


// If you use int8_t type and uint8_t type, it will be treated as 8 bits of RGB332.
  uint8_t blue = 0x03;
  lcd. fillRect ( 20 , 20 , 20 , 20 , ( uint8_t ) 0xE0 );   // Draw a rectangular fill in red
  lcd. fillRect ( 30 , 30 , 20 , 20 , ( uint8_t ) 0x1C );   // Draw a rectangular fill in green
  lcd. fillRect ( 40 , 40 , 20 , 20 , blue);            // Draw a rectangular fill in blue


// The color of the drawing function argument can be omitted.
// If omitted, the color set by the setColor function or the last used color will be used as the foreground color.
// If you draw repeatedly in the same color, omitting it will work slightly faster.
  lcd. setColor ( 0xFF0000U );                         // Specify red for drawing color
  lcd. fillCircle ( 40 , 80 , 20     );                // Fill a circle in red
  lcd. fillEllipse ( 80 , 40 , 10 , 20 );                // Fill red oval
  lcd. fillArc     ( 80 , 80 , 20 , 10 , 0 , 90 );         // Fill the arc in red
  lcd. fillTriangle ( 80 , 80 , 60 , 80 , 80 , 60 );        // Triangular paint in red
  lcd. setColor ( 0x0000FFU );                         // Specify blue as the drawing color
  lcd. drawCircle ( 40 , 80 , 20     );                // Blue circle circumference
  lcd. drawEllipse ( 80 , 40 , 10 , 20 );                // Blue and outer circumference of the ellipse
  lcd. drawArc     ( 80 , 80 , 20 , 10 , 0 , 90 );         // Blue color around the arc
  lcd. drawTriangle ( 60 , 80 , 80 , 80 , 80 , 60 );        // Blue triangle outer circumference
  lcd. setColor ( 0x00FF00U );                         // Specify green as the drawing color
  lcd. drawBezier ( 60 , 80 , 80 , 80 , 80 , 60 );         // Green quadratic Bezier curve
  lcd. drawBezier ( 60 , 80 , 80 , 20 , 20 , 80 , 80 , 60 ); // Green and cubic Bezier curve

// Draw Gradient Line drawGradientLine cannot omit the color specification.
  lcd. drawGradientLine ( 0 , 80 , 80 , 0 , 0xFF0000U , 0x0000FFU ); // Gradient straight line from red to blue

  delay(1000);

// You can fill the entire screen with clear or fillScreen.
// fillScreen is the same as specifying the entire screen of fillRect, and the color specification is treated as the drawing color.
  lcd. fillScreen ( 0xFFFFFFu );   // Fill with white
  lcd. setColor ( 0x00FF00u );     // Specify green as the drawing color
  lcd. fillScreen ();            // fill with green

// clear is different from the drawing function and holds the color as a background color.
// The background color is rarely used, but it is also used as a color to fill the gap when using the scroll function.
  lcd. clear ( 0xFFFFFFu );        // Fill with white as the background color
  lcd. setBaseColor ( 0x000000u ); // Specify black as the background color
  lcd. clear ();                 // fill with black


// The SPI bus is allocated and released automatically when the drawing function is called,
// If drawing speed is important, use startWrite and endWrite before and after the drawing process.
// Suppresses securing and releasing the SPI bus, improving speed.
// In the case of electronic paper (EPD), the drawing after startWrite () is reflected on the screen by calling endWrite ().
  lcd. drawLine ( 0 , 1 , 39 , 40 , red);        // Secure SPI bus, draw line, release SPI bus
  lcd. drawLine ( 1 , 0 , 40 , 39 , blue);       // Secure SPI bus, draw line, release SPI bus
  lcd. startWrite ();                       // Secure SPI bus
  lcd. drawLine ( 38 , 0 , 0 , 38 , 0xFFFF00U ); // Draw a line
  lcd. drawLine ( 39 , 1 , 1 , 39 , 0xFF00FFU ); // Draw a line
  lcd. drawLine ( 40 , 2 , 2 , 40 , 0x00FFFFU ); // Draw a line
  lcd. endWrite ();                         // Release SPI bus


// startWrite and endWrite internally count the number of calls and
// If called repeatedly, it will only work at the beginning and end.
// Be sure to use startWrite and endWrite so that they are paired.
// (If you don't mind occupying the SPI bus, you can call startWrite once first and not endWrite.)
  lcd. startWrite ();      // Count +1, secure SPI bus
  lcd. startWrite ();      // count +1
  lcd. startWrite ();      // count +1
  lcd. endWrite ();        // Count-1
  lcd. endWrite ();        // Count-1
  lcd. endWrite ();        // Count-1, SPI bus release
  lcd. endWrite ();        // do nothing
// If you call endWrite excessively, nothing will be done and the count will not be negative.


// If you want to forcibly release / secure the SPI bus regardless of the count status of startWrite,
// use endTransaction · beginTransaction.
// The count will not be cleared, so be careful not to make the Tsuji match.
  lcd. startWrite ();        // Count +1, secure SPI bus
  lcd. startWrite ();        // count +1
  lcd. drawPixel ( 0 , 0 );     // draw
  lcd. endTransaction ();    // Release SPI bus
  // Other SPI devices can be used here
  // When using another device (SD card, etc.) on the same SPI bus
  // Make sure the SPI bus is free.
  lcd. beginTransaction (); // Secure SPI bus
  lcd. drawPixel ( 0 , 0 );     // draw
  lcd. endWrite ();          // Count-1
  lcd. endWrite ();          // Count-1, SPI bus release



// Apart from drawPixel, there is a function that draws a point called writePixel.
// drawPixel reserves the SPI bus as needed, while
// writePixel does not check the status of the SPI bus.
  lcd. startWrite ();   // Secure SPI bus
  for (uint32_t x = 0; x < 128; ++x) {
    for ( uint32_t y = 0 ; y < 128 ; ++ y) {
      lcd.writePixel(x, y, lcd.color888( x*2, x + y, y*2));
    }
  }
  lcd. endWrite ();     // Release SPI bus
// All functions whose names start with write must explicitly call startWrite.
// writePixel, writeFastVLine, writeFastHLine, writeFillRect are applicable.

  delay(1000);

// Similar drawing functions can be used for drawing on sprites (offscreen).
// First, specify the color depth of the sprite with setColorDepth. (If omitted, it will be treated as 16.)
// sprite.setColorDepth (1); // Set to 1-bit (2 colors) palette mode
// sprite.setColorDepth (2); // Set to 2-bit (4 colors) palette mode
// sprite.setColorDepth (4); // Set to 4-bit (16 colors) palette mode
// sprite.setColorDepth (8); // Set to 8-bit RGB332
// sprite.setColorDepth (16); // Set to 16 bits in RGB565
  sprite. setColorDepth ( 24 );   // Set to 24-bit RGB888


// * By calling createPalette () after setting setColorDepth (8) ;, it will be in 256 color palette mode.
// sprite.createPalette();


// Use createSprite to specify the width and height to allocate memory.
// Memory consumption is proportional to color depth and area. Please note that if it is too large, memory allocation will fail.
  sprite. createSprite ( 65 , 65 ); // Create a sprite with a width of 65 and a height of 65.

  for (uint32_t x = 0; x < 64; ++x) {
    for ( uint32_t y = 0 ; y < 64 ; ++ y) {
      sprite. drawPixel (x, y, lcd. color888 ( 3 + x * 4 , (x + y) * 2 , 3 + y * 4 ));   // Draw on sprite
    }
  }
  sprite.drawRect(0, 0, 65, 65, 0xFFFF);

// The created sprite can be output to any coordinates with pushSprite.
// The output destination will be the LGFX passed as an argument when creating the instance.
  sprite. pushSprite ( 64 , 0 );         // Draw a sprite at coordinates 64,0 on the lcd

// If you did not pass the pointer of the drawing destination when creating the instance of sprite, or
// If there are multiple LGFX, you can also pushSprite by specifying the output destination as the first argument.
  sprite. pushSprite (& lcd, 0 , 64 );   // Draw a sprite at coordinates 0,64 on the lcd

  delay(1000);

  // You can rotate, scale, and draw sprites with pushRotateZoom.
  // The coordinates set by setPivot are treated as the center of rotation, and the center of rotation is drawn so that it is located at the coordinates of the drawing destination.
  sprite. setPivot ( 32 , 32 );     // Handle coordinates 32, 32 as the center
  int32_t center_x = lcd.width()/2;
  int32_t center_y = lcd.height()/2;
  lcd. startWrite ();
  for (int angle = 0; angle <= 360; ++angle) {
    sprite. pushRotateZoom (center_x, center_y, angle, 2.5 , 3 ); // Draw at angle angle, width 2.5 times, height 3 times in the center of the screen

    if ((angle% 36 ) == 0 ) lcd. display (); // Update the display for electronic paper once every 36 times.
  }
  lcd.endWrite();

  delay(1000);

  // Use deleteSprite to free memory for sprites that are no longer in use.
  sprite.deleteSprite();

  // The same instance can be reused after deleteSprite.
  sprite. setColorDepth ( 4 );      // Set to 4-bit (16 colors) palette mode
  sprite.createSprite(65, 65);

  // In the palette mode sprite, the color of the argument of the drawing function is treated as the palette number.
  // When drawing with pushSprite etc., the actual drawing color is determined by referring to the palette.

  // In 4-bit (16 colors) palette mode, palette numbers 0 to 15 can be used.
  // The initial color of the palette is black for 0, white for the palette at the end, and a gradation from 0 to the end.
  // Use setPaletteColor to set the palette color.
  sprite. setPaletteColor ( 1 , 0x0000FFU );     // Set palette 1 to blue
  sprite. setPaletteColor ( 2 , 0x00FF00U );     // Set palette 2 to green
  sprite. setPaletteColor ( 3 , 0xFF0000U );     // Set palette 3 to red

  sprite. fillRect ( 10 , 10 , 45 , 45 , 1 );              // Fill a rectangle with palette # 1.
  sprite. fillCircle ( 32 , 32 , 22 , 2 );                // Fill the circle with palette # 2.
  sprite. fillTriangle ( 32 , 12 , 15 , 43 , 49 , 43 , 3 ); // Triangular fill with palette 3

  // The last argument of pushSprite allows you to specify a color that you don't want to draw.
  sprite. pushSprite ( 0 ,   0 , 0 );   // Draw sprites with palette 0 treated as transparent
  sprite. pushSprite ( 65 ,   0 , 1 );   // Draw sprites on palette 1 as transparent
  sprite. pushSprite ( 0 , 65 , 2 );   // Draw sprites on palette 2 as transparent
  sprite. pushSprite ( 65 , 65 , 3 );   // Draw sprites on palette 3 as transparent

  delay(5000);

  lcd. startWrite (); // Keep the SPI bus occupied by doing startWrite () here.
}

void loop(void)
{
  static int count = 0;
  static int a = 0;
  static int x = 0;
  static int y = 0;
  static float zoom = 3;
  ++count;
  if ((a += 1) >= 360) a -= 360;
  if ((x += 2) >= lcd.width()) x -= lcd.width();
  if ((y += 1) >= lcd.height()) y -= lcd.height();
  sprite.setPaletteColor(1, lcd.color888( 0, 0, count & 0xFF));
  sprite.setPaletteColor(2, lcd.color888( 0,~count & 0xFF, 0));
  sprite.setPaletteColor(3, lcd.color888( count & 0xFF, 0, 0));

  sprite.pushRotateZoom(x, y, a, zoom, zoom, 0);

  if ((count% 100 ) == 0 ) lcd. display (); // Update the display for electronic paper once every 100 times.
}