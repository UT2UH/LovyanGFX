
// Arduino-misaki UTF16 is required to run this sample.
// need misakifont to run this example.
//
// URL : https://github.com/Tamakichi/Arduino-misakiUTF16
//

// Include Arduino-misaki UTF16 font data.
// Include the font data of Arduino-misakiUTF16.
#include "misakiUTF16FontData.h"

#include <LovyanGFX.hpp>

static LGFX lcd;

// Use the lgfx :: BDFfont class to configure Arduino-misakiUTF16 to be available.
static constexpr lgfx::BDFfont misaki_font = 
  {fdata              // Bitmap data of the first argument font
  , ftable             // 2nd argument unicode font table
  , sizeof (ftable) >> 1  // 3rd argument font table size
  , 8                  // 4th argument font width
  , 4                  // 5th argument font width (half-width)
  , 7                  // 6th argument font height
  , 6                  // 7th argument Baseline height
  , 8                  // 8th argument Vertical cursor movement amount at line feed
  };


void setup()
{
  lcd.init();

  // By specifying the misaki_font created earlier as an argument of the setFont function, it can be used in print, drawString, etc.
  lcd.setFont(&misaki_font);

  lcd.setTextWrap(true, true);
}

void loop()
{
  lcd.setTextColor(0x808080U|random(0xFFFFFF), 0x7F7F7FU&random(0x10000));

  lcd.print("美さきフォントは8x8のコンパクトなフォントです。");
  lcd.print("Arduino-misakiUTF16は、教育漢字1,006字(小学校で習う漢字）＋ひらがな・カタカナ・記号・半角等の1,710字にしぼって収録されています。");
  lcd.print("Hello");
  lcd.print("ＨＥＬＬＯ");
  lcd.print("こんにちは");
  delay(1000);
}