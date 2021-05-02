#include <LovyanGFX.hpp>

extern const uint8_t rgb888[];
extern const uint8_t bgr888[];
extern const uint16_t swap565[];
extern const uint16_t rgb565[];
extern const uint8_t rgb332[];

static constexpr int image_width = 33;
static constexpr int image_height = 31;
//----------------------------------------------------------------------------

static LGFX lcd;

void setup(void)
{
  lcd.init();
  lcd. startWrite ();
}

void loop(void)
{

/*
  There are several types of functions that draw image data.
Method 1. How to set the drawing range in advance and then specify the length of the data to draw
Method 2. How to draw data by specifying the coordinates to draw and the width and height
Method 1. How to set the drawing range in advance and then specify the length of the data to draw
In this method, after setting the drawing range with the setWindow / setAddrWindow function,
Use the writePixels / pushPixels function to specify the length of the image data and draw it.
  setWindow (x0, y0, x1, y1); // Specify the drawing range. Specify the upper left and lower right coordinates.
  setAddrWindow (x, y, w, h); // Specify the drawing range. Specify the upper left coordinates, width and height.
The operation of setWindow is not guaranteed when the coordinates outside the screen are specified.
setAddrWindow is adjusted within the range if it is specified outside the drawing range.
 * However, as a result of automatic adjustment, the width and height that are actually set may be smaller than the specified values, so be careful.
  writePixels (* data, len, swap); // Draw the image. (StartWrite is required in advance and endWrite is required after the fact)
  pushPixels (* data, len, swap); // Draw the image. (No need for startWrite / endWrite)
 * WritePixels is a function derived from AdafruitGFX, and pushPixels is a function derived from TFT_eSPI.
    The drawing contents are the same, but whether or not startWrite / endWrite is performed automatically is different.
First argument: Pointer of image data (The color format is determined according to the data type and conversion is performed.)
Second argument: Number of pixels in image data (Note that it is not the number of bytes.)
Third argument: Byte order conversion flag (If omitted, the value set in advance by the setSwapBytes function is used.)
Color format conversion is performed based on the data type of the first argument.
  In the case of uint8_t *, it is treated as 8-bit color RGB332.
  In case of uint16_t *, it is treated as 16bit color RGB565.
  If it is void *, it is treated as 24-bit color RGB888.
 * (Since there is no 3-byte primitive type, void * type is treated as 24-bit color)
 * When drawing on the LCD, the color format is automatically converted according to the color mode of the LCD.
*/
  lcd.clear(TFT_DARKGREY);
  lcd. setColorDepth ( 16 );   // Set the LCD to 16bit color mode.
  lcd. setSwapBytes ( true ); // Enable byte order conversion.
  int len = image_width * image_height;

  // Set the width and height of the image in advance with setAddrWindow and draw with writePixels.
  lcd. setAddrWindow ( 0 , 0 , image_width, image_height);          // Set the drawing range.
  lcd. writePixels (( uint16_t *) rgb565, len); // Draw 16bit image data of RGB565.

  // If the data and byte order conversion specifications do not match, the color will be garbled.
  lcd.setAddrWindow(0, 40, image_width, image_height);
  // You can specify the presence or absence of byte order conversion by specifying false in the third argument.
  lcd. writePixels (( uint16_t *) rgb565, len, false ); // Colors are garbled when drawing an RGB565 image without byte order conversion.

  // If the drawing range does not match the width and height of the image, such as outside the screen, the drawing result will be corrupted.
  lcd. setAddrWindow ( -1 , 80 , image_width, image_height); // The X coordinate is -1 (outside the screen), so it cannot be set correctly.
  lcd. writePixels (( uint16_t *) rgb565, len); // The drawing content is corrupted because the width of the drawing destination and the width of the image do not match.

  // Even if the data and type do not match, the drawing result will be corrupted.
  lcd.setAddrWindow(0, 120, image_width, image_height);
  // Cast RGB565 data to uint8_t on purpose and treat it as RGB332 8-bit color.
  lcd. writePixels (( uint8_t *) rgb565, len);   // The drawing is disturbed because the image format and type do not match.

  // If the data and type match, the appropriate format conversion will be performed according to the number of colors of the drawing destination.
  lcd.setAddrWindow(0, 160, image_width, image_height);
  lcd. writePixels (( uint8_t *) rgb332, len);   // Even RGB332 data can be drawn correctly on a 16-bit color LCD.


// * Image data is sent to the LCD in 1-byte units in order from the data at the youngest address in the memory.
//     For this reason, for example, if RGB565 16-bit type data is prepared in an array of uint16_t obediently, the byte order will be changed for convenience of transmission.
// In     this case, by using setSwapBytes (true) in advance or specifying true in the 3rd argument, byte order conversion is performed and drawing can be performed normally.
// If     the image data to be prepared is created with the upper and lower bytes replaced in advance, this conversion becomes unnecessary and it is advantageous in terms of speed.

  lcd.setAddrWindow(40,  0, image_width, image_height);
  lcd. writePixels (( uint16_t *) swap565, len, false ); // Disable byte order conversion for 16-bit data with the upper and lower levels swapped in advance.

  lcd.setAddrWindow(40, 40, image_width, image_height);
  lcd. writePixels (( uint16_t *) swap565, len, true );   // On the contrary, the color is garbled when byte order conversion is performed on the data in which the upper and lower parts are exchanged in advance.

  lcd.setAddrWindow(40, 80, image_width, image_height);
  lcd. writePixels (( void *) rgb888, len, true );   // Similarly for 24-bit data, byte order conversion is required for data with RGB888 blue on the lower side.

  lcd.setAddrWindow(40, 120, image_width, image_height);
  lcd. writePixels (( void *) bgr888, len, false );   // Similarly, data with red on the lower side of BGR888 does not need byte order conversion.

  lcd.setAddrWindow(40, 160, image_width, image_height);
  lcd. writePixels (( void *) bgr888, len, true );   // If the setting is wrong, the color will be garbled . (Red and blue switch)

  lcd.display();
  delay(4000);
  lcd.clear(TFT_DARKGREY);

/*
Method 2. How to draw data by specifying the coordinates to draw and the width and height
In this method, the pushImage function is used to specify the drawing range and drawing data for drawing.
  pushImage (x, y, w, h, * data); // Draw an image at the specified coordinates.
Unlike method 1, the drawing will not be disturbed even if you specify the coordinates that extend off the screen. (The protruding part is not drawn.)
Unlike method 1, there is no argument to specify the conversion in byte order, so it is necessary to set by setSwapBytes in advance.
As with method 1, color conversion is performed according to the data type.
*/

  lcd. setSwapBytes ( true ); // Enable byte order conversion.

  // Draw the image data by specifying the coordinates of the drawing destination and the width / height of the image.
  lcd. pushImage (    0 , 0 , image_width, image_height, ( uint16_t *) rgb565); // Draw 16bit image data of RGB565.

  // If the data and byte order conversion specifications do not match, the color will be garbled.
  lcd. pushImage (    0 , 40 , image_width, image_height, ( uint16_t *) swap565); // NG. Byte order converted data is garbled when byte order conversion is performed.

  // Even if the drawing range goes off the screen, the drawing result will not be corrupted.
  lcd. pushImage ( -1 , 80 , image_width, image_height, ( uint16_t *) rgb565); // Drawing is not disturbed even if X coordinate -1 (outside the screen) is specified.

  // If the data and type do not match, the drawing result will be corrupted.
  lcd. pushImage ( 0 , 120 , image_width, image_height, ( uint8_t *) rgb565); // Casting RGB565 data to uint8_t and treating it as RGB332 will disturb the drawing.

  // If the data and type match, the format conversion will be done properly.
  lcd. pushImage ( 0 , 160 , image_width, image_height, ( uint8_t *) rgb332); // Even RGB332 data can be drawn correctly.


  lcd. setSwapBytes ( false );    // Disable byte order conversion.
  lcd. pushImage ( 40 ,    0 , image_width, image_height, ( uint8_t *) rgb332);   // good. RGB332 data is not affected by byte order conversion.
  lcd. pushImage ( 40 ,   40 , image_width, image_height, ( uint16_t *) rgb565);   // NG. RGB565 data requires byte order conversion.
  lcd. pushImage ( 40 ,   80 , image_width, image_height, ( void *) rgb888);   // NG. RGB888 data requires byte order conversion.
  lcd. pushImage ( 40 , 120 , image_width, image_height, ( uint16_t *) swap565); // good. Byte order converted RGB565 data is not garbled.
  lcd. pushImage ( 40 , 160 , image_width, image_height, ( void *) bgr888);   // good. Byte order converted RGB888 data is not garbled.

  lcd. setSwapBytes ( true );    // Enable byte order conversion.
  lcd. pushImage ( 80 ,    0 , image_width, image_height, ( uint8_t *) rgb332);   // good. RGB332 data is not affected by byte order conversion.
  lcd. pushImage ( 80 ,   40 , image_width, image_height, ( uint16_t *) rgb565);   // good. RGB565 data will not be garbled if byte order conversion is enabled.
  lcd. pushImage ( 80 ,   80 , image_width, image_height, ( void *) rgb888);   // good. RGB888 data will not be garbled if byte order conversion is enabled.
  lcd. pushImage ( 80 , 120 , image_width, image_height, ( uint16_t *) swap565); // NG. Byte order converted data is garbled when byte order conversion is performed.
  lcd. pushImage ( 80 , 160 , image_width, image_height, ( void *) bgr888);   // NG. Byte order converted data is garbled when byte order conversion is performed.

// You can also use the type defined in the lgfx :: namespace as the data type.
// When casting to these types, the setSwapBytes setting is ignored.
  lcd.pushImage(120,   0, image_width, image_height, (lgfx:: rgb332_t*) rgb332); // good  8bitデータ
  lcd.pushImage(120,  40, image_width, image_height, (lgfx:: rgb565_t*) rgb565); // good 16bitデータ
  lcd.pushImage(120,  80, image_width, image_height, (lgfx:: rgb888_t*) rgb888); // good 24bitデータ
  lcd. pushImage ( 120 , 120 , image_width, image_height, (lgfx :: swap565_t *) swap565); // good Byte order converted 16bit data
  lcd. pushImage ( 120 , 160 , image_width, image_height, (lgfx :: bgr888_t *) bgr888); // good byte-order converted 24-bit data

// You can specify the transparent color with the 6th argument. The part with the color specified as transparent is not drawn.
  lcd. pushImage ( 160 ,    0 , image_width, image_height, (lgfx :: rgb332_t *) rgb332, 0 );                    // Specify black transparent
  lcd. pushImage ( 160 ,   40 , image_width, image_height, (lgfx :: rgb565_t *) rgb565, ( uint8_t ) 0xE0 );        // Red is transparent
  lcd. pushImage ( 160 ,   80 , image_width, image_height, (lgfx :: rgb888_t *) rgb888, ( uint16_t ) 0x07E0 );     // Green transparent
  lcd. pushImage ( 160 , 120 , image_width, image_height, (lgfx :: swap565_t *) swap565, ( uint32_t ) 0x0000FFU ); // Blue transparent
  lcd. pushImage ( 160 , 160 , image_width, image_height, (lgfx :: bgr888_t *) bgr888, TFT_WHITE);            // White is transparent

  lcd.display();
  delay(4000);
  lcd.clear(TFT_DARKGREY);

// You can use the pushImageRotateZoom function to rotate and scale the image for drawing.
  for (int angle = 0; angle <= 360; ++angle) {
    lcd. pushImageRotateZoom
      (lcd. width () >> 2   // Center coordinates of drawing destination X
      , lcd. height () >> 1   // Center coordinates of drawing destination Y
      , image_width >> 1   // Image center coordinates X
      , image_height >> 1   // Image center coordinates Y
      , angle               // Rotation angle
      , 3.0                 // Magnification in X direction (can be inverted by specifying minus)
      , 3.0                 // Magnification in Y direction (can be reversed by specifying minus)
      , image_width         // Image data width
      , image_height        // Height of image data
      , rgb332              // Pointer of image data
      );

// Use the pushImageRotateZoomWithAA function to enable antialiasing.
    lcd. pushImageRotateZoomWithAA
      ( lcd.width()*3>> 2
      , lcd.height() >> 1
      , image_width  >> 1
      , image_height >> 1
      , angle
      , 3.0
      , 3.0
      , image_width
      , image_height
      , rgb332
      );

    if ((angle % 36) == 0) { lcd.display(); }
  }

  lcd.clear(TFT_DARKGREY);

// You can use the pushImageAffine function to transform an image with affine transformation and draw it.
// Specify the affine transformation parameters as a float type array.
  {
    float matrix[ 6 ] = // equal multiple representation
      { 1.0,  0.0,  (float)lcd.width()  / 2
      , 0.0,  1.0,  (float)lcd.height() / 2 };
    lcd.pushImageAffine(matrix, image_width, image_height, rgb332);
  }

  lcd.display();
  delay(1000);
  lcd.clear(TFT_DARKGREY);

  {
    float matrix[ 6 ] = // Horizontal 2 times representation
      { 2.0,  0.0,  (float)lcd.width()  / 2
      , 0.0,  1.0,  (float)lcd.height() / 2 };
    lcd.pushImageAffine(matrix, image_width, image_height, rgb332);
  }

  lcd.display();
  delay(1000);
  lcd.clear(TFT_DARKGREY);

  {
    float matrix [ 6 ] = // Double vertical display
      { 1.0,  0.0,  (float)lcd.width()  / 2
      , 0.0,  2.0,  (float)lcd.height() / 2 };
    lcd.pushImageAffine(matrix, image_width, image_height, rgb332);
  }

  lcd.display();
  delay(1000);
  lcd.clear(TFT_DARKGREY);

  {
    float matrix [ 6 ] = // Diagonal deformation
      { 1.0, -0.4,  (float)lcd.width()  / 2
      , 0.0,  1.0,  (float)lcd.height() / 2 };
    lcd.pushImageAffine(matrix, image_width, image_height, rgb332);
  }

  lcd.display();
  delay(1000);
  lcd.clear(TFT_DARKGREY);

  // Use the pushImageAffineWithAA function to enable antialiasing.
  {
    float matrix[6] =
      { 1.0,  0.0,  (float)lcd.width()  / 2
      , 0.0,  1.0,  (float)lcd.height() / 2 };
    for (int i = -300; i < 300; i++) {
      float f = (float)i / 100;
      matrix[1] = f;
      matrix[3] = f;
      lcd.pushImageAffineWithAA(matrix, image_width, image_height, rgb332);

      if ((i % 30) == 0) { lcd.display(); }
    }
  }
}


//----------------------------------------------------------------------------
#define R 0x00,0x00,0xFF,
#define G 0x00,0xFF,0x00,
#define B 0xFF,0x00,0x00,
#define C 0xFF,0xFF,0x00,
#define M 0xFF,0x00,0xFF,
#define Y 0x00,0xFF,0xFF,
#define W 0xFF,0xFF,0xFF,
#define _ 0x00,0x00,0x00,
constexpr uint8_t rgb888[] = {
#include "image.h"
};
#undef R
#undef G
#undef B
#undef C
#undef M
#undef Y
#undef W
#undef _
//----------------------------------------------------------------------------
#define R 0xFF,0x00,0x00,
#define G 0x00,0xFF,0x00,
#define B 0x00,0x00,0xFF,
#define C 0x00,0xFF,0xFF,
#define M 0xFF,0x00,0xFF,
#define Y 0xFF,0xFF,0x00,
#define W 0xFF,0xFF,0xFF,
#define _ 0x00,0x00,0x00,
constexpr uint8_t bgr888[] = {
#include "image.h"
};
#undef R
#undef G
#undef B
#undef C
#undef M
#undef Y
#undef W
#undef _
//----------------------------------------------------------------------------
#define R 0x00F8,
#define G 0xE007,
#define B 0x1F00,
#define C 0xFF07,
#define M 0x1FF8,
#define Y 0xE0FF,
#define W 0xFFFF,
#define _ 0x0000,
constexpr uint16_t swap565[] = {
#include "image.h"
};
#undef R
#undef G
#undef B
#undef C
#undef M
#undef Y
#undef W
#undef _
//----------------------------------------------------------------------------
#define R 0xF800,
#define G 0x07E0,
#define B 0x001F,
#define C 0x07FF,
#define M 0xF81F,
#define Y 0xFFE0,
#define W 0xFFFF,
#define _ 0x0000,
constexpr uint16_t rgb565[] = {
#include "image.h"
};
#undef R
#undef G
#undef B
#undef C
#undef M
#undef Y
#undef W
#undef _
//----------------------------------------------------------------------------
#define R 0xE0,
#define G 0x1C,
#define B 0x03,
#define C 0x1F,
#define M 0xE3,
#define Y 0xFC,
#define W 0xFF,
#define _ 0x00,
constexpr uint8_t rgb332[] = {
#include "image.h"
};
#undef R
#undef G
#undef B
#undef C
#undef M
#undef Y
#undef W
#undef _