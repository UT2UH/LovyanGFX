/*\
 *

 LovyanGFX SharpLCD demo

 Author: tobozo - https://github.com/tobozo
 Library requirement: https://github.com/lovyan03/LovyanGFX/tree/develop

 *
\*/

#include <LovyanGFX.h>
#include <lgfx_user/SharpLCD.hpp>

// any pins can be used
#define SHARP_SCK     16
#define SHARP_MOSI    17
#define SHARP_SS      47
#define SHARP_DISPON  48
#define SHARP_EXTMODE -1
#define SHARP_EXTCOM   0
//static SharpDisplay lcd(SHARP_SCK, SHARP_MOSI, SHARP_SS, 400, 240);
static K52SharpLCD lcd;
//static SharpDisplay lcd(SHARP_SCK, SHARP_MOSI, SHARP_SS, 230, 303);
//static SharpDisplay lcd(SHARP_SCK, SHARP_MOSI, SHARP_SS, 128, 128);

// fps counter
uint32_t sec, psec;
size_t fps = 0, frame_count = 0;

// frequency changer
uint32_t freqs[] = { 1000000, 2000000, 4000000, 8000000, 10000000 };
uint32_t freqs_count = sizeof(freqs)/sizeof(uint32_t);
uint32_t freq_idx = 0;
char status[16];

// text (fps/mhz) cliprect
uint32_t l8, tw, centerX, centerY;
uint32_t clipw, clipw8, cliph;
uint32_t clipx8, clipx, clipy;
// cliprect buffer (to capture background)
uint8_t* rect = nullptr;


LGFX_Sprite sprite1bit(&lcd);


void drawGrid(LGFX_Sprite *dst, uint8_t w )
{
  for(uint8_t y=0;y<dst->height();y++)
  {
    bool ystate = y%w == 1;
    for(uint8_t x=0;x<dst->width();x++)
    {
      bool xstate = x%w == 1;
      bool state = !(ystate ? xstate : !xstate);
      dst->drawPixel(x, y, state);
    }
  }
}


void setup(void)
{
  Serial.begin(115200);
  Serial.println("Hello!");

  pinMode(SHARP_EXTCOM, OUTPUT);
  digitalWrite(SHARP_EXTCOM, LOW);

  lcd.begin();
  //lcd.setRotation(2);
  lcd.setAutoDisplay(false);
  lcd.setDithering(false);

  sprite1bit.setColorDepth(1);
  if(! sprite1bit.createSprite(64, 64) )
  {
    Serial.println("Failed to create 1bit sprite");
    while(1);
  }

  drawGrid(&sprite1bit, 4);
  sprite1bit.pushRotateZoom(&lcd, lcd.width()>>1, (lcd.height()>>1), 0.0, 24, 24);

  lcd.setTextSize(3);
  lcd.setTextColor(0xFFFFFFU);
  lcd.setTextDatum(MC_DATUM);

  snprintf(status, sizeof(status)-1, "%02dfps %02dMHz", 100, 100);

  auto spibus = (lgfx::Bus_SPI*)lcd.getPanel()->getBus();
  spibus->setClock(freqs[freq_idx]);

  l8      = lcd.width()/8;
  tw      = lcd.textWidth(status)+4;
  centerX = lcd.width()/2;
  centerY = lcd.height()/2;

  clipw  = 8+ceil(tw/8)*8;
  clipw8 = clipw/8;
  cliph  = ceil((lcd.fontHeight()+4)/2)*2;

  clipx8 = (centerX-clipw/2)/8;
  clipx  = clipx8*8;
  clipy  = centerY-cliph/2;

  rect = (uint8_t*)malloc(cliph*clipw8);
}


void loop(void)
{
  auto buf = lcd.getBuffer();
  static bool restore = false;

  if( restore ) // clear text and restore background
  {
    for(int y=0;y<cliph;y++)
    {
      uint32_t addr = clipx8+((y+clipy)*l8);
      memcpy(&buf[addr], &rect[y*clipw8], clipw8);
    }
  }

  auto _freq_idx = (sec/5)%freqs_count;
  if( _freq_idx != freq_idx )
  {
    freq_idx = _freq_idx;
    auto spibus = (lgfx::Bus_SPI*)lcd.getPanel()->getBus();
    spibus->setClock(freqs[freq_idx]);
    drawGrid(&sprite1bit, 2+rand()%4);
    sprite1bit.pushRotateZoom(&lcd, lcd.width()>>1, (lcd.height()>>1), 0, 24, 24);
  }


  { // scroll by 8 horizontal pixels and 1 vertical pixel
    uint8_t firstline[l8];
    memcpy(firstline, &buf[0], l8);
    uint8_t* lastline = &buf[(lcd.height()-1)*l8];

    for(int y=1;y<lcd.height();y++)
    {
      uint8_t* linebufdst = &buf[(y-1)*l8];
      uint8_t* linebufsrc = &buf[ y   *l8];
      uint8_t firstbyte = linebufsrc[0];
      for(int x8=1;x8<l8;x8++)
      {
        linebufdst[x8-1] = linebufsrc[x8];
      }
      linebufdst[l8-1] = firstbyte;
    }

    uint8_t firstbyte = firstline[0];
    for(int x8=1;x8<l8;x8++)
    {
      lastline[x8-1] = firstline[x8];
    }
    lastline[l8-1] = firstbyte;
  }

  // backup background before writing text
  for(int y=0;y<cliph;y++)
  {
    uint32_t addr = clipx8+((y+clipy)*l8);
    memcpy(&rect[y*clipw8], &buf[addr], clipw8);
    restore = true;
  }

  snprintf(status, sizeof(status)-1, "%2dfps %2dMHz", fps, int(freqs[freq_idx]/1000000));
  lcd.setTextColor(TFT_BLACK);
  lcd.drawString(status, centerX+1, centerY+1);
  lcd.setTextColor(TFT_WHITE);
  lcd.drawString(status, centerX, centerY);

  lcd.display();

  ++frame_count;
  sec = lgfx::millis() / 1000;
  if (psec != sec)
  {
    psec = sec;
    fps = frame_count;
    frame_count = 0;
  }
}


