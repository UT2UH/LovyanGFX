// How to set up the SPI with LovyanGFX

#include <LovyanGFX.hpp>

// Create a structure for SPI configuration

// for ESP32 SPI
struct LGFX_Config
{
// You can change the name of the structure from "LGFX_Config"
// But do not change the name and type of the members.

  // Select the type of SPI  (VSPI_HOST or HSPI_HOST)
  static constexpr spi_host_device_t spi_host = VSPI_HOST;

  // Set the DMA channel number (1 or 2)
  // If you don't want to use DMA, omit it or set it to 0.
  static constexpr int dma_channel = 1;

  // Set the SPI SCLK pin number
  static constexpr int spi_sclk = 18;

  // Set the SPI MOSI pin number
  static constexpr int spi_mosi = 23;

  // Set the SPI MISO pin number
  // If you share the SPI bus with an SD card, be sure to set up MISO as well.
  // If you don't want to use MISO, omit it or set it to -1.
  static constexpr int spi_miso = 19;

  // Set the data length of SPI communication.
  // If you want to use the LCD for RPi, set it to 16.
  static constexpr int spi_dlen = 8;
};


// Create an LGFX_SPI instance with the configuration structure you just created as a template argument.
static lgfx::LGFX_SPI<LGFX_Config> lcd;


// Create an instance of the Panel class. Comment out the description of the panel you want to use.
//static lgfx::Panel_HX8357B panel;
//static lgfx::Panel_HX8357D panel;
//static lgfx::Panel_ILI9163 panel;
//static lgfx::Panel_ILI9341 panel;
//static lgfx::Panel_ILI9342 panel;
//static lgfx::Panel_ILI9486 panel;
//static lgfx::Panel_ILI9486L panel;
static lgfx::Panel_ILI9488 panel;
//static lgfx::Panel_SSD1351 panel;
//static lgfx::Panel_ST7735  panel;
//static lgfx::Panel_ST7735S panel;
//static lgfx::Panel_ST7789 panel;
//static lgfx::Panel_ST7796 panel;

// If you want to use a touch panel, create an instance of the Touch class.
//static lgfx::Touch_SPI_STMPE610 touch;
static lgfx::Touch_FT5x06 touch;
//static lgfx::Touch_XPT2046 touch;


void setup(void)
{
// Assign various setting values to the panel class.

  // Set the SPI clock for normal write operation.
  panel.freq_write = 80000000;

  // Set the SPI clock for fill write operation.
  // It may work even if you set the clock higher than freq_write.
  panel.freq_fill  = 40000000;

  // Set the SPI clock for read operation.
  panel.freq_read  = 16000000;

  // Set the SPI mode. (0~3)
  panel.spi_mode = 0;

  // Set the SPI mode when read operation. (0~3)
  panel.spi_mode_read = 0;

  // Sets the number of dummy bits for pixel readout.
  panel.len_dummy_read_pixel = 8;

  // Set the readability of the data. If reading of the data is not possible, set false.
  panel.spi_read = true;

  // Set to "true" for a panel that uses MOSI pins to read data.
  panel.spi_3wire = false;

  // Set the pin number for connecting the CS pins of the LCD.
  panel.spi_cs = 5;

  // Set the pin number for connecting the D/C pins of the LCD.
  panel.spi_dc = 32;

  // Set the pin number for connecting the RST pins of the LCD.
  panel.gpio_rst = -1;

  // Set the backlight pin number.
  panel.gpio_bl  = -1;

  // Set the backlight control PWM channel number.
  panel.pwm_ch_bl = -1;

  // Set the backlight level (rue=turns on HIGH / false=turns on LOW)
  panel.backlight_level = true;

  // Set the panel color inversion.
  panel.reverse_invert = false;

  // Set the RGB/BGR color order.
  panel.rgb_order = false;

  // Set the internal memory size of the LCD driver.
  // （例：ST7735は 132x162 / 128x160 / 132x132 の３通りが存在します）
  panel.memory_width  = 320;
  panel.memory_height = 480;

  // Set the size of the pixels that can be displayed on the LCD panel.
  panel.panel_width  = 320;
  panel.panel_height = 480;

  // Set the number of offset pixels.
  panel.offset_x = 0;
  panel.offset_y = 0;

  // Set the default rotation number.
  panel.rotation = 2;

  // Set the number of rotation offset number.
  // setRotationを使用した時の向きを変更したい場合、offset_rotationを設定します。
  // setRotation(0)での向きを 1の時の向きにしたい場合、 1を設定します。
  panel.offset_rotation = 0;

  // After setting up, you can pass the panel pointer to the lcd.setPanel function.
  lcd.setPanel(&panel);


/*
  // If you use a touch panel, you will assign various setting values to the touch class.

  // for SPI setting.  (XPT2046 / STMPE610)
  touch.spi_host = VSPI_HOST;  // VSPI_HOST or HSPI_HOST
  touch.spi_sclk = 18;
  touch.spi_mosi = 23;
  touch.spi_miso = 19;
  touch.spi_cs   =  5;
  touch.freq = 1000000;
  touch.bus_shared = true;  // If the LCD and touch share SPI, set to true.

  // for I2C setting. (FT5x06)
  touch.i2c_port = I2C_NUM_1;
  touch.i2c_sda  = 21;
  touch.i2c_scl  = 22;
  touch.i2c_addr = 0x38;
  touch.freq = 400000;

  // (This can be omitted if calibration is performed.)
  touch.x_min = 0;
  touch.x_max = 319;
  touch.y_min = 0;
  touch.y_max = 319;

  // After setting up, you can pass the touch pointer to the lcd.setTouch function.
  lcd.setTouch(&touch);
*/

  // for I2C setting. (FT5x06)
  touch.i2c_port = I2C_NUM_1;
  touch.i2c_sda  = 21;
  touch.i2c_scl  = 22;
  touch.i2c_addr = 0x38;
  touch.freq = 400000;
  
  // After setting up, you can pass the touch pointer to the lcd.setTouch function.
  lcd.setTouch(&touch);

  // Initializing the SPI bus and panel will make it available.
  lcd.init();

  if (lcd.width() > 240 || lcd.height() > 240) lcd.setTextSize(2);

  if (lcd.touch())
  {
    if (lcd.width() < lcd.height()) lcd.setRotation(3 & (lcd.getRotation() + 1));

    // Draw the information text.
    lcd.drawString("touch the arrow marker.", 0, lcd.height()>>1);

    // If the touch is enabled, perform calibration. Touch the arrow tips that appear in the four corners of the screen in order.
    lcd.calibrateTouch(nullptr, 0xFFFFFFU, 0x000000U, 30);

    lcd.clear();
  }
}

uint32_t count = ~0;
void loop(void)
{
  delay(10);
  lcd.startWrite();
  lcd.setRotation(++count & 7);
  lcd.setColorDepth((count & 8) ? 16 : 24);

  lcd.setTextColor(random(65536));
  lcd.drawNumber(lcd.getRotation(), 16, 0);

  lcd.setTextColor(0xFF0000U);
  lcd.drawString("R", 30, 16);
  lcd.setTextColor(0x00FF00U);
  lcd.drawString("G", 40, 16);
  lcd.setTextColor(0x0000FFU);
  lcd.drawString("B", 50, 16);

  lcd.drawRect(30,30,lcd.width()-60,lcd.height()-60,random(65536));

  lcd.endWrite();

  int32_t x, y;
  if (lcd.getTouch(&x, &y)) {
    lcd.fillRect(x-2, y-2, 5, 5, random(65536));
  }
}
