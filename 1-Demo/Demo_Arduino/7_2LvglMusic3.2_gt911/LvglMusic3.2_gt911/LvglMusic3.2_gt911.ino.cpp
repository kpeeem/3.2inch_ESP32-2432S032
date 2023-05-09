# 1 "C:\\Users\\ADMINI~1\\AppData\\Local\\Temp\\1\\tmpu72lmug_"
#include <Arduino.h>
# 1 "L:/dev/project/jingcai/lvg_music_gt911_3.2/src/LvglMusic3.2_gt911.ino"
#include "HAL.h"
#define TFT_BL 27



Ticker ticker;
Audio audio(true, I2S_DAC_CHANNEL_LEFT_EN);

struct audioMessage {
  uint8_t cmd;
  const char* txt;
  uint32_t value;
  uint32_t ret;
} audioTxMessage, audioRxMessage;

enum : uint8_t { SET_VOLUME, GET_VOLUME, CONNECTTOHOST, CONNECTTOSD };

QueueHandle_t audioSetQueue = NULL;
QueueHandle_t audioGetQueue = NULL;




#include <lvgl.h>
#include "lv_demos.h"
#include <TFT_eSPI.h>
#include "touch.h"




static const uint16_t screenWidth = 320;
static const uint16_t screenHeight = 240;

static lv_disp_draw_buf_t draw_buf;
static lv_color_t buf[ screenWidth * 40 ];

TFT_eSPI tft = TFT_eSPI();


#if LV_USE_LOG != 0
void my_print(const char * buf);
void my_disp_flush( lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p );
void my_touchpad_read( lv_indev_drv_t * indev_driver, lv_indev_data_t * data );
void CreateQueues();
void audioTask(void *parameter);
void audioInit();
audioMessage transmitReceive(audioMessage msg);
void audioSetVolume(uint8_t vol);
uint8_t audioGetVolume();
bool audioConnecttohost(const char* host);
bool audioConnecttoSD(const char* filename);
void tcr1s();
static void event_handler(lv_event_t * e);
void lv_example_btn_1(void);
void setup();
void loop();
void audio_info(const char *info);
void audio_id3data(const char *info);
void audio_eof_mp3(const char *info);
void audio_showstation(const char *info);
void audio_showstreamtitle(const char *info);
void audio_bitrate(const char *info);
void audio_commercial(const char *info);
void audio_icyurl(const char *info);
void audio_lasthost(const char *info);
#line 43 "L:/dev/project/jingcai/lvg_music_gt911_3.2/src/LvglMusic3.2_gt911.ino"
void my_print(const char * buf)
{
  Serial.printf(buf);
  Serial.flush();
}
#endif


void my_disp_flush( lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p )
{
  uint32_t w = ( area->x2 - area->x1 + 1 );
  uint32_t h = ( area->y2 - area->y1 + 1 );

  tft.startWrite();
  tft.setAddrWindow( area->x1, area->y1, w, h );
  tft.pushColors( ( uint16_t * )&color_p->full, w * h, true );
  tft.endWrite();


  lv_disp_flush_ready( disp );
}






void my_touchpad_read( lv_indev_drv_t * indev_driver, lv_indev_data_t * data )
{
    if (touch_has_signal())
    {



        if (touch_touched())
        {
            data->state = LV_INDEV_STATE_PR;


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


void CreateQueues() {
  audioSetQueue = xQueueCreate(10, sizeof(struct audioMessage));
  audioGetQueue = xQueueCreate(10, sizeof(struct audioMessage));
}

void audioTask(void *parameter) {
  CreateQueues();
  if (!audioSetQueue || !audioGetQueue) {
    log_e("queues are not initialized");
    while (true) {
      ;
    }
  }

  struct audioMessage audioRxTaskMessage;
  struct audioMessage audioTxTaskMessage;


  while (true) {
    if (xQueueReceive(audioSetQueue, &audioRxTaskMessage, 1) == pdPASS) {
      if (audioRxTaskMessage.cmd == SET_VOLUME) {
        audioTxTaskMessage.cmd = SET_VOLUME;
        audio.setVolume(audioRxTaskMessage.value);
        audioTxTaskMessage.ret = 1;
        xQueueSend(audioGetQueue, &audioTxTaskMessage, portMAX_DELAY);
      }
      else if (audioRxTaskMessage.cmd == CONNECTTOHOST) {
        audioTxTaskMessage.cmd = CONNECTTOHOST;
        audioTxTaskMessage.ret = audio.connecttohost(audioRxTaskMessage.txt);
        xQueueSend(audioGetQueue, &audioTxTaskMessage, portMAX_DELAY);
      }
      else if (audioRxTaskMessage.cmd == CONNECTTOSD) {
        audioTxTaskMessage.cmd = CONNECTTOSD;
        audioTxTaskMessage.ret = audio.connecttoSD(audioRxTaskMessage.txt);
        xQueueSend(audioGetQueue, &audioTxTaskMessage, portMAX_DELAY);
      }
      else if (audioRxTaskMessage.cmd == GET_VOLUME) {
        audioTxTaskMessage.cmd = GET_VOLUME;
        audioTxTaskMessage.ret = audio.getVolume();
        xQueueSend(audioGetQueue, &audioTxTaskMessage, portMAX_DELAY);
      }
      else {
        log_i("error");
      }
    }
    audio.loop();
  }
}

void audioInit() {
  xTaskCreatePinnedToCore(
    audioTask,
    "audioplay",
    5000,
    NULL,
    2 | portPRIVILEGE_BIT,
    NULL,
    0
  );
}

audioMessage transmitReceive(audioMessage msg) {
  xQueueSend(audioSetQueue, &msg, portMAX_DELAY);
  if (xQueueReceive(audioGetQueue, &audioRxMessage, portMAX_DELAY) == pdPASS) {
    if (msg.cmd != audioRxMessage.cmd) {
      log_e("wrong reply from message queue");
    }
  }
  return audioRxMessage;
}

void audioSetVolume(uint8_t vol) {
  audioTxMessage.cmd = SET_VOLUME;
  audioTxMessage.value = vol;
  audioMessage RX = transmitReceive(audioTxMessage);
}

uint8_t audioGetVolume() {
  audioTxMessage.cmd = GET_VOLUME;
  audioMessage RX = transmitReceive(audioTxMessage);
  return RX.ret;
}

bool audioConnecttohost(const char* host) {
  audioTxMessage.cmd = CONNECTTOHOST;
  audioTxMessage.txt = host;
  audioMessage RX = transmitReceive(audioTxMessage);
  return RX.ret;
}

bool audioConnecttoSD(const char* filename) {
  audioTxMessage.cmd = CONNECTTOSD;
  audioTxMessage.txt = filename;
  audioMessage RX = transmitReceive(audioTxMessage);
  return RX.ret;
}



void tcr1s() {
  uint32_t act = audio.getAudioCurrentTime();
  uint32_t afd = audio.getAudioFileDuration();
  uint32_t pos = audio.getFilePos();
  Serial.println(act);
  Serial.println(afd);

}





static void event_handler(lv_event_t * e)
{
  lv_event_code_t code = lv_event_get_code(e);



  if (code == LV_EVENT_CLICKED ) {
    LV_LOG_USER("Clicked");
    Serial.println("test");

  }
  else if (code == LV_EVENT_VALUE_CHANGED) {
    LV_LOG_USER("Toggled");
    Serial.println("test2");
  }
}

void lv_example_btn_1(void)
{
  lv_obj_t * label;

  lv_obj_t * btn1 = lv_btn_create(lv_scr_act());
  lv_obj_add_event_cb(btn1, event_handler, LV_EVENT_ALL, NULL);
  lv_obj_align(btn1, LV_ALIGN_CENTER, 0, 0);

  label = lv_label_create(btn1);
  lv_label_set_text(label, "test");
  lv_obj_center(label);
# 247 "L:/dev/project/jingcai/lvg_music_gt911_3.2/src/LvglMusic3.2_gt911.ino"
}







void setup()
{

  Serial.begin(115200);

  ledcSetup(0, 600, 8);
  ledcAttachPin(TFT_BL, 0);
  ledcWrite(0, 255);

  sdcard_init();
  delay(200);
  audioInit();
  touch_init();



  audio.setVolume(15);

  log_i("current volume is: %d", audioGetVolume());

  ticker.attach(1, tcr1s);

  Serial.println("LVGL music Demo");
  lv_init();

  tft.begin();
  tft.setRotation( 3 );
  tft.fillScreen( TFT_BLACK );

  lv_disp_draw_buf_init( &draw_buf, buf, NULL, screenWidth * 40 );


  static lv_disp_drv_t disp_drv;
  lv_disp_drv_init( &disp_drv );

  disp_drv.hor_res = screenWidth;
  disp_drv.ver_res = screenHeight;
  disp_drv.flush_cb = my_disp_flush;
  disp_drv.draw_buf = &draw_buf;
  lv_disp_drv_register( &disp_drv );


  static lv_indev_drv_t indev_drv;
  lv_indev_drv_init( &indev_drv );
  indev_drv.type = LV_INDEV_TYPE_POINTER;
  indev_drv.read_cb = my_touchpad_read;
  lv_indev_drv_register( &indev_drv );

#if 0
  lv_example_btn_1();
#else

  lv_demo_music();

  Serial.println("Setup done");
#endif
}


void loop()
{
  lv_timer_handler();
}
# 326 "L:/dev/project/jingcai/lvg_music_gt911_3.2/src/LvglMusic3.2_gt911.ino"
void audio_info(const char *info) {
  Serial.print("info        "); Serial.println(info);
}
void audio_id3data(const char *info) {
  Serial.print("id3data     "); Serial.println(info);
}
void audio_eof_mp3(const char *info) {
  Serial.print("eof_mp3     "); Serial.println(info);
}
void audio_showstation(const char *info) {
  Serial.print("station     "); Serial.println(info);
}
void audio_showstreamtitle(const char *info) {
  Serial.print("streamtitle "); Serial.println(info);
}
void audio_bitrate(const char *info) {
  Serial.print("bitrate     "); Serial.println(info);
}
void audio_commercial(const char *info) {
  Serial.print("commercial  "); Serial.println(info);
}
void audio_icyurl(const char *info) {
  Serial.print("icyurl      "); Serial.println(info);
}
void audio_lasthost(const char *info) {
  Serial.print("lasthost    "); Serial.println(info);
}