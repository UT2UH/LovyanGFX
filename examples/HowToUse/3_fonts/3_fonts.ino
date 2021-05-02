#include <LovyanGFX.hpp>

static LGFX lcd;

void drawGradation(void)
{
  // Draw a gradient on the background
  lcd. startWrite ();
  lcd.setAddrWindow(0, 0, lcd.width(), lcd.height());
  for (int y = 0; y < lcd.height(); ++y) {
    for (int x = 0; x < lcd.width(); ++x) {
      lcd.writeColor(lcd.color888(x>>1, (x + y) >> 2, y>>1), 1);
    }
  }
  lcd.endWrite();
}

void setup(void)
{
  lcd.init();

  drawGradation();

  // There are roughly two ways to draw characters, print type functions and drawString type functions.

  // In the drawString function, specify the character string in the first argument, specify the X coordinate in the second argument, and specify the Y coordinate in the third argument.
  lcd.drawString("string!", 10, 10);

  // In the drawNumber function, the first argument is a number.
  lcd.drawNumber(123, 100, 10);

  // In the drawFloat function, the first argument is a number, the second argument is the number of digits after the decimal point, the third argument is the X coordinate, and the fourth argument is the Y coordinate.
  lcd.drawFloat(3.14, 2, 150, 10);

  // The print function prints at the coordinates specified by the setCursor function (or the continuation of the last drawn character by the print function).
  lcd.setCursor(10, 20);
  lcd.print("print!");

  // You can draw the contents after the second argument with the printf function. (Since it is C language printf compliant, you can also draw character strings and floating point numbers)
  int value = 123;
  lcd.printf("test %d", value);

  // With the println function, you can start a new line after drawing a character string. It has the same effect as print ("\ n") ;.
  lcd.println("println");

  // To change the font, use the setFont function.
  // The same font as the setTextFont function of TFT_eSPI is Font0 to Font8.
  // * If you can use the input support of the editor, the font list will be displayed by inputting up to & fonts :: in the argument.
  lcd.setFont(&fonts::Font4);
  lcd.println("TestFont4");

  // For compatibility with TFT_eSPI, it is also possible to change the font by number with the setTextFont function.
  // The numbers that can be specified in the argument are 0, 2, 4, 6, 7, 8. (Compliant with TFT_eSPI)
  // * However, this method is not recommended because fonts with other numbers are forcibly included in the binary and the size increases.
  lcd.setTextFont(2);
  lcd.println("TestFont2");


  // You can change the color with setTextColor.
  // The first argument is the text color and the second argument is the background color.
  lcd.setTextColor(0x00FFFFU, 0xFF0000U);
  lcd.print("CyanText RedBack");
  // * If you want to redraw the characters repeatedly in the same place, it is recommended to specify the background color and overwrite.
  //     If you erase it with fillRect etc. and then rewrite it, flicker may occur.


  // If only the first argument is specified in setTextColor and the second argument is omitted,
  // Draw only the characters without filling the background.
  lcd.setTextColor(0xFFFF00U);
  lcd.print("YellowText ClearBack");


  // Font6 contains only clock characters.
  lcd.setFont(&fonts::Font6);
  lcd.print("apm.:-0369");

  // Font7 contains 7-segment LCD-like fonts.
  lcd.setFont(&fonts::Font7);
  lcd.print(".:-147");

  // Font8 contains only numbers.
  lcd.setFont(&fonts::Font8);
  lcd.print(".:-258");


  delay(3000);
  drawGradation();

// Japanese fonts converted from IPA fonts are preset in 4 types x 9 sizes = 36 ways.
// The number at the end indicates the size, and 8, 12, 16, 20, 24, 28, 32, 36, 40 are available.
// fonts :: lgfxJapanMincho_12 // Mincho size 12 fixed width font
// fonts :: lgfxJapanMinchoP_16 // Mincho size 16 proportional font
// fonts :: lgfxJapanGothic_20 // Gothic size 20 fixed width font
// fonts :: lgfxJapanGothicP_24 // Gothic size 24 proportional font

// Japanese / Korean / Chinese (simplified / traditional) fonts converted from efont are preset in 4 types x 5 sizes = 20 ways.
// Numbers represent sizes, available in 10, 12, 14, 16, 24.
// The last letter stands for b = bold / i = italic.
// fonts :: efontJA_10 // Japanese size 10
// fonts :: efontCN_12_b // Simplified Chinese size 12 bold
// fonts :: efontTW_14_bi // Traditional Chinese size 14 bold italics
// fonts :: efontKR_16_i // Korean size 16 italics

  lcd.setCursor(0, 0);
  lcd. setFont (& fonts :: lgfxJapanMincho_16); lcd. print ( " Mincho 16 Hello World \ nHello World \ n " );
// lcd.setFont (& fonts :: lgfxJapanMinchoP_16); lcd.print ("Mincho P 16 Hello World \ nHello World \ n");
  lcd. setFont (& fonts :: lgfxJapanGothic_16); lcd. print ( " Gothic 16 Hello World \ nHello World \ n " );
// lcd.setFont (& fonts :: lgfxJapanGothicP_16); lcd.print ("Gothic P 16 Hello World \ nHello World \ n");

// * Mr. Yamaneko's [Japanese Font Subset Generator] (https://github.com/yamamaya/lgfxFontSubsetGenerator)
// You can use // to create small font data that contains only the characters you need.


  delay(3000);
  drawGradation();


  // In LovyanGFX, AdafruitGFX fonts can also be used with the setFont function.
  // (A setFreeFont function is also provided for compatibility with TFT_eSPI)
  lcd.setFont(&fonts::FreeSerif9pt7b);


  // If you want to draw right-justified or center-justified, specify the reference position with the setTextDatum function.
  // There are 4 vertical directions, top, middle, baseline, and bottom, and 3 horizontal directions, left, center, and right.
  // Specify from 12 ways that combine vertical and horizontal specifications.
  lcd.setTextDatum( textdatum_t::top_left        );
  lcd.setTextDatum( textdatum_t::top_center      );
  lcd.setTextDatum( textdatum_t::top_right       );
  lcd.setTextDatum( textdatum_t::middle_left     );
  lcd.setTextDatum( textdatum_t::middle_center   );
  lcd.setTextDatum( textdatum_t::middle_right    );
  lcd.setTextDatum( textdatum_t::baseline_left   );
  lcd.setTextDatum( textdatum_t::baseline_center );
  lcd.setTextDatum( textdatum_t::baseline_right  );
  lcd.setTextDatum( textdatum_t::bottom_left     );
  lcd.setTextDatum( textdatum_t::bottom_center   );
  lcd.setTextDatum( textdatum_t::bottom_right    );
  // * "textdatum_t ::" can be omitted
  // * The print function has an effect only in the vertical direction, and has no effect in the horizontal direction.

  // Bottom right alignment
  lcd.setTextDatum( bottom_right );
  lcd.drawString("bottom_right",  lcd.width() / 2,  lcd.height() / 2);

  // Bottom left alignment
  lcd.setTextDatum( bottom_left );
  lcd.drawString("bottom_left",  lcd.width() / 2,  lcd.height() / 2);

  // Top right alignment
  lcd.setTextDatum( top_right );
  lcd.drawString("top_right",  lcd.width() / 2,  lcd.height() / 2);

  // Top left alignment
  lcd.setTextDatum( top_left );
  lcd.drawString("top_left",  lcd.width() / 2,  lcd.height() / 2);


  // Draw a centerline at the reference coordinates
  lcd.drawFastVLine(lcd.width() / 2, 0, lcd.height(), 0xFFFFFFU);
  lcd.drawFastHLine(0, lcd.height() / 2, lcd.width(), 0xFFFFFFU);


  delay(3000);
  drawGradation();

  lcd.setFont(&Font2);
  lcd.setCursor(0, 0);


  lcd.drawRect(8, 8, lcd.width() - 16, lcd.height() - 16, 0xFFFFFFU);

  // You can limit the drawing range with the setClipRect function. It will not be drawn outside the specified range.
  // * Affects all drawing functions, not just text.
  lcd.setClipRect(10, 10, lcd.width() - 20, lcd.height() - 20);


  // Specify the character enlargement ratio with the setTextSize function.
  // Specify the horizontal magnification with the first argument and the vertical magnification with the second argument.
  // If the second argument is omitted, the magnification of the first argument will be reflected both vertically and horizontally.
  lcd.setTextSize(2.7, 4);
  lcd.println("Size 2.7 x 4");

  lcd.setTextSize(2.5);
  lcd.println("Size 2.5 x 2.5");

  lcd.setTextSize(1.5, 2);
  lcd.println("Size 1.5 x 2");

  delay(1000);

  lcd.setTextColor(0xFFFFFFU, 0);
  for (float i = 0; i < 30; i += 0.01) {
    lcd.setTextSize(sin(i)+1.1, cos(i)+1.1);
    lcd.drawString("size test", 10, 10);
  }

  lcd.setTextSize(1);

  // With the setTextWrap function, specify the wrapping operation when the print function reaches the screen edge (drawing range edge).
  // If the first argument is set to true, it will move to the left end after reaching the right end.
  // If the second argument is set to true, it will move to the upper end after reaching the lower end. (Default: false)
  lcd.setTextWrap(false);
  lcd.println("setTextWrap(false) testing... long long long long string wrap test string ");
  // When false is specified, the position is not adjusted and the part outside the drawing range is not drawn.

  lcd.setTextWrap(true);
  lcd.setTextColor(0xFFFF00U, 0);
  lcd.println("setTextWrap(true) testing... long long long long string wrap test string ");
  // When true is specified, the coordinates are automatically adjusted so that they fit within the drawing range.

  delay(1000);

  // When true is specified in the second argument, when the bottom of the screen is reached, the continuation is drawn from the top.
  lcd.setTextColor(0xFFFFFFU, 0);
  lcd.setTextWrap(true, true);
  lcd.println("setTextWrap(true, true) testing...");
  for (int i = 0; i < 100; ++i) {
    lcd.printf("wrap test %03d ", i);
    delay(50);
  }


  drawGradation();

  // Use the setTextScroll function to specify the scrolling behavior when the bottom of the screen is reached.
  // Specify the rectangular range to scroll with the setScrollRect function. (If not specified, the entire screen will scroll)
  // * For the scroll function, the LCD must support pixel reading.
  lcd.setTextScroll(true);

  // Specify the rectangular range of XY Width Height with the 1st to 4th arguments, and specify the color after scrolling with the 5th argument. The 5th argument can be omitted (there is no change if omitted)
  lcd.setScrollRect(10, 10, lcd.width() - 20, lcd.height() - 20, 0x00001FU);

  for (int i = 0; i < 50; ++i) {
    lcd.printf("scroll test %d \n", i);
  }


  // Cancel the range specification of setClipRect.
  lcd.clearClipRect();

  // Cancel the range specification of setScrollRect.
  lcd.clearScrollRect();


  lcd.setTextSize(1);
  lcd.setTextColor(0xFFFFFFU, 0);


  // With the setTextPadding function, you can specify the minimum width when filling the background with drawString functions.
  lcd.setTextPadding(100);


  drawGradation();
}

void drawNumberTest(const lgfx::IFont* font)
{
  lcd.setFont(font);

  lcd.fillScreen(0x0000FF);

  lcd.setColor(0xFFFF00U);
  lcd.drawFastVLine( 80, 0, 240);
  lcd.drawFastVLine(160, 0, 240);
  lcd.drawFastVLine(240, 0, 240);
  lcd. drawFastHLine ( 0 ,   45 , 320 );
  lcd. drawFastHLine ( 0 ,   95 , 320 );
  lcd. drawFastHLine ( 0 , 145 , 320 );
  lcd. drawFastHLine ( 0 , 195 , 320 );

  for (int i = 0; i < 200; ++i) {
    lcd.setTextDatum( textdatum_t::bottom_right    );     lcd.drawNumber(i,  80,  45);
    lcd.setTextDatum( textdatum_t::bottom_center   );     lcd.drawNumber(i, 160,  45);
    lcd.setTextDatum( textdatum_t::bottom_left     );     lcd.drawNumber(i, 240,  45);
    lcd.setTextDatum( textdatum_t::baseline_right  );     lcd.drawNumber(i,  80,  95);
    lcd.setTextDatum( textdatum_t::baseline_center );     lcd.drawNumber(i, 160,  95);
    lcd.setTextDatum( textdatum_t::baseline_left   );     lcd.drawNumber(i, 240,  95);
    lcd.setTextDatum( textdatum_t::middle_right    );     lcd.drawNumber(i,  80, 145);
    lcd.setTextDatum( textdatum_t::middle_center   );     lcd.drawNumber(i, 160, 145);
    lcd.setTextDatum( textdatum_t::middle_left     );     lcd.drawNumber(i, 240, 145);
    lcd.setTextDatum( textdatum_t::top_right       );     lcd.drawNumber(i,  80, 195);
    lcd.setTextDatum( textdatum_t::top_center      );     lcd.drawNumber(i, 160, 195);
    lcd.setTextDatum( textdatum_t::top_left        );     lcd.drawNumber(i, 240, 195);
  }
}

void loop(void)
{
// * There are four types of fonts whose names start with "Free": 9pt 12pt 18pt 24pt.
  drawNumberTest( &fonts::Font0                   );
  drawNumberTest( &fonts::Font2                   );
  drawNumberTest( &fonts::Font4                   );
  drawNumberTest( &fonts::Font6                   );
  drawNumberTest( &fonts::Font7                   );
  drawNumberTest( &fonts::Font8                   );
  drawNumberTest( &fonts::TomThumb                );
  drawNumberTest( &fonts::FreeMono9pt7b           );
  drawNumberTest( &fonts::FreeMonoBold9pt7b       );
  drawNumberTest( &fonts::FreeMonoOblique9pt7b    );
  drawNumberTest( &fonts::FreeMonoBoldOblique9pt7b);
  drawNumberTest( &fonts::FreeSans9pt7b           );
  drawNumberTest( &fonts::FreeSansBold9pt7b       );
  drawNumberTest( &fonts::FreeSansOblique9pt7b    );
  drawNumberTest( &fonts::FreeSansBoldOblique9pt7b);
  drawNumberTest( &fonts::FreeSerif9pt7b          );
  drawNumberTest( &fonts::FreeSerifBold9pt7b      );
  drawNumberTest( &fonts::FreeSerifItalic9pt7b    );
  drawNumberTest( &fonts::FreeSerifBoldItalic9pt7b);
  drawNumberTest( &fonts::Orbitron_Light_24       );
  drawNumberTest( &fonts::Roboto_Thin_24          );
  drawNumberTest( &fonts::Satisfy_24              );
  drawNumberTest( &fonts::Yellowtail_32           );
}