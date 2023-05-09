
#define TFT_BL 27


#include <Arduino.h>
#include <lvgl.h>
#include <TFT_eSPI.h>
#include "touch.h"
// #include "ui.h"
#include <Ticker.h>
#include <demos/lv_demos.h>
/*******************************************************************************"

  /*Change to your screen resolution*/
static const uint16_t screenWidth = 320;
static const uint16_t screenHeight = 240;

static lv_disp_draw_buf_t draw_buf;

//static lv_color_t *buf;

static lv_color_t *buf1;
static lv_color_t *buf2;


TFT_eSPI tft = TFT_eSPI(); /* TFT instance */

#if LV_USE_LOG != 0
/* Serial debugging */
void my_print(const char *buf)
{
  Serial.printf(buf);
  Serial.flush();
}
#endif

/* Display flushing */
void my_disp_flush(lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p)
{
  uint32_t w = (area->x2 - area->x1 + 1);
  uint32_t h = (area->y2 - area->y1 + 1);

  tft.startWrite();
  tft.setAddrWindow(area->x1, area->y1, w, h);
  tft.pushColors((uint16_t *)&color_p->full, w * h, true);
  tft.endWrite();

  lv_disp_flush_ready(disp);
}

/*Read the touchpad*/
void my_touchpad_read(lv_indev_drv_t *indev_driver, lv_indev_data_t *data)
{
  if (touch_has_signal())
  {

    // delay(20);

    if (touch_touched())
    {
      data->state = LV_INDEV_STATE_PR;

      /*Set the coordinates*/
      data->point.x = touch_last_x;
      data->point.y = touch_last_y;
    }
    else if (touch_released())
    {
      data->state = LV_INDEV_STATE_REL;
    }
  }
  else
  {
    data->state = LV_INDEV_STATE_REL;
  }
}

// lvgl -ui -------------------------------------------------------------------------------

static void event_handler(lv_event_t *e)
{
  lv_event_code_t code = lv_event_get_code(e);

  if (code == LV_EVENT_CLICKED)
  {
    LV_LOG_USER("Clicked");
    Serial.println("test");
  }
  else if (code == LV_EVENT_VALUE_CHANGED)
  {
    LV_LOG_USER("Toggled");
    Serial.println("test2");
  }
}

// lvgl -ui end-----------------------------------------------------------------------------

Ticker tickerRAM;

void tcr1RAM()
{
  Serial.printf("SRAM free size: %d\n", heap_caps_get_free_size(MALLOC_CAP_INTERNAL));
}

void setup()
{
  Serial.begin(115200);
  Serial.println("Starting...");
  tickerRAM.attach(1, tcr1RAM);

  // sdcard_init();

  touch_init();
  Serial.println("LVGL Widgets Demo");
  lv_init();
  tft.init();        /* TFT init */
  bool isDMA=tft.initDMA();      /* DMA init */
  Serial.printf("DMA init %d\n", isDMA);
  tft.setRotation(3); /* Landscape orientation, flipped */
  tft.fillScreen(TFT_BLACK);
  delay(50);

  ledcSetup(0, 600, 8);
  ledcAttachPin(TFT_BL, 0);
  ledcWrite(0, 200);
  
  tft.fillScreen(TFT_RED);
  delay(500);
  tft.fillScreen(TFT_GREEN);
  delay(500);
  tft.fillScreen(TFT_BLUE);
  delay(500);
  tft.fillScreen(TFT_BLACK);
  tft.drawRect(0, 0, 320, 240, TFT_RED);
  delay(500);
  
  /* Screen brightness can be modified by adjusting this parameter. (0-255) */
//
  buf1 = (lv_color_t *)heap_caps_malloc(sizeof(lv_color_t) * screenWidth * 170, MALLOC_CAP_DMA | MALLOC_CAP_INTERNAL);
  buf2 = (lv_color_t *)heap_caps_malloc(sizeof(lv_color_t) * screenWidth * 170, MALLOC_CAP_DMA | MALLOC_CAP_INTERNAL);

  lv_disp_draw_buf_init(&draw_buf, buf1, buf2, screenWidth * 170);


//buf = (lv_color_t *)heap_caps_malloc(sizeof(lv_color_t) * screenWidth * screenHeight/2, MALLOC_CAP_DMA | MALLOC_CAP_INTERNAL);
//lv_disp_draw_buf_init(&draw_buf, buf, NULL, screenWidth * screenHeight/2);




  /*Initialize the display*/
  static lv_disp_drv_t disp_drv;
  lv_disp_drv_init(&disp_drv);
  /*Change the following line to your display resolution*/
  disp_drv.hor_res = screenWidth;
  disp_drv.ver_res = screenHeight;
  disp_drv.flush_cb = my_disp_flush;
  disp_drv.draw_buf = &draw_buf;
  lv_disp_drv_register(&disp_drv);

  /*Initialize the (dummy) input device driver*/
  static lv_indev_drv_t indev_drv;
  lv_indev_drv_init(&indev_drv);
  indev_drv.type = LV_INDEV_TYPE_POINTER;
  indev_drv.read_cb = my_touchpad_read;
  lv_indev_drv_register(&indev_drv);
  //lv_log_register_print_cb(my_print);

#if 0
#else
  lv_demo_widgets();
  //  lv_demo_music();

  Serial.println("Setup done");

#endif
}

void loop()
{
  lv_timer_handler(); /* let the GUI do its work */
  delay(0);
}
