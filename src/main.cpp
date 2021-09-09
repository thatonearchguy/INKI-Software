#include "Wire.h"
#include "lvgl.h"
#include "epd1in54.h"
#include "gpio.h"
#include "Adafruit_DRV2605.h"
#include "bluefruit.h"
#include "nrfx_rtc.h"
#include "RTClib.h"
#include <SEGGER_RTT.h>
#include <vector>
#include <string>
#include "max30102.h"
#include "algorithm_by_RF.h"
#include "Arduino-ICM20948.h"
#include <stack>

#define SCK        27
#define MISO       26
#define MOSI       40
#define EPD_CS     39
#define EPD_DC     38
#define SRAM_CS    37
#define EPD_RESET  36 // can set to -1 and share with microcontroller Reset!
#define EPD_BUSY   35 // can set to -1 to not use a pin (will wait a fixed delay)
#define GUI_RTC_CC 0
#define GUI_RTC 2
#define GUI_RTC_TICKS (RTC_US_TO_TICKS(500000ULL, RTC_DEFAULT_CONFIG_FREQUENCY))

/* B L U E T O O T H   P a r a m s */

uint8_t beaconUuid[16] =
{
  0x01, 0x12, 0x23, 0x34, 0x45, 0x56, 0x67, 0x78,
  0x89, 0x9a, 0xab, 0xbc, 0xcd, 0xde, 0xef, 0xf0
};

BLEDfu bledfu;
BLEUart bleuart;
BLEClientUart clientUart;
BLEBeacon beacon(beaconUuid, 0x0102, 0x0304, -54);

uint8_t batteryPercentage = 100;


TaskHandle_t Handle_maxData;
TaskHandle_t Handle_imuData;

float n_spo2,ratio,correl;  //SPO2 value
int8_t ch_spo2_valid;  //indicator to show if the SPO2 calculation is valid
int32_t n_heart_rate; //heart rate value
int8_t  ch_hr_valid;  //indicator to show if the heart rate calculation is valid
int32_t i;
uint32_t elapsedTime,timeStart;
const byte oxiInt = 10; // pin connected to MAX30102 INT

uint32_t aun_ir_buffer[BUFFER_SIZE]; //infrared LED sensor data
uint32_t aun_red_buffer[BUFFER_SIZE];  //red LED sensor data
float old_n_spo2;  // Previous SPO2 value
uint8_t uch_dummy,k;


Adafruit_DRV2605 drv;


RTC_DS1307 rtc;
char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

//static const nrf_drv_rtc_config_t m_rtc_config = NRF_DRV_RTC_DEFAULT_CONFIG;
static const nrfx_rtc_t m_rtc = NRFX_RTC_INSTANCE(2);

/* E P a p e r   D i s p l a y  <3  L V G L */
Epd epd;
void epd_flush( lv_disp_drv_t*, const lv_area_t*, lv_color_t* ); //Memory update function
void epd_set_px_cb(lv_disp_drv_t*, uint8_t*, lv_coord_t, lv_coord_t, lv_coord_t, lv_color_t, lv_opa_t); //Pixel painter
void epd_rounder( lv_disp_drv_t*, lv_area_t*); //Coordinate rounder
static void button_reader( lv_indev_drv_t*, lv_indev_data_t* ); //Reads button state
uint8_t button_interface(); //HW button interface
void button_feedback(lv_indev_drv_t*, uint8_t); //Buggy, implements DRV vibration behavior.
static uint8_t LV_TICK_INCREMENT_MS = 4;
static const uint8_t screenWidth  = 200;
static const uint8_t screenHeight = 200;

static lv_disp_draw_buf_t draw_buf;
static uint8_t buf_1[ screenWidth * screenHeight / 8 ];
//static uint8_t buf_2[ screenWidth * screenHeight / 8 ];

TaskHandle_t Handle_GUIUpdate;
SemaphoreHandle_t GuiSemaphore;

SemaphoreHandle_t I2CSemaphore;

#define MY_RUN_SYMBOL "\xEF\x9C\x8C"
#define MY_HEART_SYMBOL "\xEF\x88\x9E"
#define MY_PHONE_SYMBOL "\xEF\x8F\x8D"
#define MY_CALENDAR_SYMBOL "\xEF\x81\xB3"
#define MY_HOURGLASS_SYMBOL "\xEF\x89\x92"


ArduinoICM20948 icm20948;
ArduinoICM20948Settings icmSettings =
{
  .i2c_speed = 400000,                // i2c clock speed
  .is_SPI = false,                    // Enable SPI, if disable use i2c
  .cs_pin = 10,                       // SPI chip select pin
  .spi_speed = 7000000,               // SPI clock speed in Hz, max speed is 7MHz
  .mode = 1,                          // 0 = low power mode, 1 = high performance mode
  .enable_gyroscope = true,           // Enables gyroscope output
  .enable_accelerometer = true,       // Enables accelerometer output
  .enable_magnetometer = true,        // Enables magnetometer output // Enables quaternion output
  .enable_gravity = true,             // Enables gravity vector output
  .enable_linearAcceleration = true,  // Enables linear acceleration output
  .enable_quaternion6 = true,         // Enables quaternion 6DOF output
  .enable_quaternion9 = true,         // Enables quaternion 9DOF output
  .enable_har = true,                 // Enables activity recognition
  .enable_steps = true,               // Enables step counter
  .gyroscope_frequency = 1,           // Max frequency = 225, min frequency = 1
  .accelerometer_frequency = 1,       // Max frequency = 225, min frequency = 1
  .magnetometer_frequency = 1,        // Max frequency = 70, min frequency = 1 
  .gravity_frequency = 1,             // Max frequency = 225, min frequency = 1
  .linearAcceleration_frequency = 1,  // Max frequency = 225, min frequency = 1
  .quaternion6_frequency = 50,        // Max frequency = 225, min frequency = 50
  .quaternion9_frequency = 50,        // Max frequency = 225, min frequency = 50
  .har_frequency = 50,                // Max frequency = 225, min frequency = 50
  .steps_frequency = 50               // Max frequency = 225, min frequency = 50
};

const uint8_t number_i2c_addr = 2;
uint8_t poss_addresses[number_i2c_addr] = {0X69, 0X68};
uint8_t ICM_address;
bool ICM_found = false;

char icm_activity;
unsigned long icm_steps;





typedef enum
{
  INKWATCH_CLOCK_EVT_HFCLK_STARTED,
  INKWATCH_CLOCK_EVT_LFCLK_STARTED,
  INKWATCH_CLOCK_EVT_CAL_DONE,
  INKWATCH_CLOCK_EVT_CAL_ABORTED,
  INKWATCH_CLOCK_LFCLK_FAILURE,
} inkwatch_events_t;


static void gui_rtc_handler(nrfx_rtc_int_type_t int_type)
{
  if(int_type == NRFX_RTC_INT_TICK)
  {
    lv_tick_inc(LV_TICK_INCREMENT_MS);
  }
}

static void rtc_config(void)
{
    nrfx_err_t err_code;

    //Initialize RTC instance
    nrfx_rtc_config_t config = NRFX_RTC_DEFAULT_CONFIG;
    config.prescaler = (int)((32768*LV_TICK_INCREMENT_MS/1000)-1);
    err_code = nrfx_rtc_init(&m_rtc, &config, gui_rtc_handler);
    if(err_code!=NRFX_SUCCESS)
    {
      SEGGER_RTT_WriteString(0, "RTC Fail");
    }
    //Enable tick event & interrupt
    nrfx_rtc_tick_enable(&m_rtc,true);
    //Power on RTC instance
    nrfx_rtc_enable(&m_rtc);
}

static void event_handler(lv_event_t * e)
{
    lv_event_code_t code = lv_event_get_code(e);
    
    if(code == LV_EVENT_CLICKED) {
        LV_LOG_USER("Clicked");
    }
    else if(code == LV_EVENT_VALUE_CHANGED) {
        LV_LOG_USER("Toggled");
    }
}



static DateTime RTCTime;

struct Notification
{
  uint8_t* iconGlyph;
  char* title;
  char* body;
  char* action1;
  char* action2;
};

//stack< Notification > notif_stack;

/* Code Graveyard */
/*
class Screen {
  public:
    Screen(char* name, lv_indev_t* indev)
    {
      this->scr = lv_obj_create(NULL);
      this->scr_name = name;
      this->draw_scr(indev);
    }
    lv_obj_t* scr;
    virtual void draw_scr(lv_indev_t* indev);
    char* scr_name;

};
*/
/*
void lv_example_btn_1(lv_indev_t* indev)
{
    lv_group_t* g = lv_group_create();
    //lv_obj_t * label;
    lv_obj_t* currentScreen = lv_scr_act();

    lv_obj_t * btn1 = lv_btn_create(currentScreen);
    lv_obj_add_event_cb(btn1, event_handler, LV_EVENT_ALL, NULL);
    lv_obj_align(btn1, LV_ALIGN_CENTER, 0, -40);

    time_label = lv_label_create(btn1);
    lv_label_set_text(time_label, "");
    lv_obj_center(time_label);

    lv_obj_t * btn2 = lv_btn_create(lv_scr_act());
    lv_obj_add_event_cb(btn2, event_handler, LV_EVENT_ALL, NULL);
    lv_obj_align(btn2, LV_ALIGN_CENTER, 0, 40);
    lv_obj_add_flag(btn2, LV_OBJ_FLAG_CHECKABLE);
    lv_obj_set_height(btn2, LV_SIZE_CONTENT);

    date_label = lv_label_create(btn2);
    lv_label_set_text(date_label, "Toggle");
    lv_obj_center(date_label);
    lv_group_add_obj(g, btn1);
    lv_group_add_obj(g, btn2);
    lv_indev_set_group(indev, g);
    lv_scr_load(currentScreen);

}
*/


/*  H   O   M   E      S   C   R   E   N */
lv_obj_t* home_scr;
lv_obj_t* watchface_scr;
lv_indev_t* indev_lvgl;
lv_group_t* watchface_group;
lv_group_t* home_group;

static void load_watchface(lv_event_t* e)
{        
  
  LV_LOG_USER("Clicked on home");
  lv_scr_load(watchface_scr);
  lv_indev_set_group(indev_lvgl, watchface_group);

}
//const char* home_scr_btnm_map[] = {MY_HEART_SYMBOL,LV_SYMBOL_BELL, LV_SYMBOL_SETTINGS,"\n",MY_RUN_SYMBOL,LV_SYMBOL_HOME, LV_SYMBOL_AUDIO,"\n",MY_CALENDAR_SYMBOL,MY_HOURGLASS_SYMBOL,MY_PHONE_SYMBOL };

void init_home_scr(lv_indev_t* indev)
{
  home_group = lv_group_create();
  lv_obj_t* home_btnm_container = lv_obj_create(home_scr);
  
  static lv_style_t containerStyle;
  lv_style_init(&containerStyle);
  lv_style_set_bg_color(&containerStyle, lv_color_white());
  lv_style_set_bg_opa(&containerStyle, LV_OPA_0);
  lv_style_set_border_width(&containerStyle, 1);
  lv_style_set_outline_width(&containerStyle, 0);
  lv_style_set_border_opa(&containerStyle, LV_OPA_TRANSP);
  lv_style_set_outline_opa(&containerStyle, LV_OPA_TRANSP);

  lv_obj_set_size(home_btnm_container, 200, 190);
  lv_obj_align(home_btnm_container, LV_ALIGN_TOP_MID, 0, 0);
  lv_obj_add_style(home_btnm_container, &containerStyle, 0);
  
  /*Properties to transition*/
  static lv_style_prop_t props[] = {
          LV_STYLE_TRANSFORM_WIDTH, LV_STYLE_TRANSFORM_HEIGHT, LV_STYLE_TEXT_LETTER_SPACE, (lv_style_prop_t)0
  };

  /*Transition descriptor when going back to the default state.
    *Add some delay to be sure the press transition is visible even if the press was very short*/
  static lv_style_transition_dsc_t transition_dsc_def;
  lv_style_transition_dsc_init(&transition_dsc_def, props, lv_anim_path_overshoot, 140, 0, NULL);

  /*Transition descriptor when going to pressed state.
    *No delay, go to presses state immediately*/
  static lv_style_transition_dsc_t transition_dsc_pr;
  lv_style_transition_dsc_init(&transition_dsc_pr, props, lv_anim_path_ease_in_out, 140, 0, NULL);

  /*Add only the new transition to he default state*/
  static lv_style_t style_def;
  lv_style_init(&style_def);
  lv_style_set_transition(&style_def, &transition_dsc_def);
  lv_style_set_width(&style_def, 58);
  lv_style_set_height(&style_def, 58);
  lv_style_set_bg_color(&style_def, lv_color_black());
  lv_style_set_text_color(&style_def, lv_color_white());
  lv_style_set_text_font(&style_def, &lv_font_montserrat_40);
  /*Add the transition and some transformation to the presses state.*/
  static lv_style_t style_pr;
  lv_style_init(&style_pr);
  lv_style_set_transform_width(&style_pr, 5);
  lv_style_set_transform_height(&style_pr, -5);
  lv_style_set_text_letter_space(&style_pr, 5);
  lv_style_set_transition(&style_pr, &transition_dsc_pr);
  lv_style_set_bg_color(&style_pr, lv_color_black());
  lv_style_set_text_color(&style_pr, lv_color_white());
  lv_style_set_text_font(&style_pr, &lv_font_montserrat_40);

  static lv_style_t style_def_mysymbol;
  lv_style_init(&style_def_mysymbol);
  lv_style_set_transition(&style_def_mysymbol, &transition_dsc_def);
  lv_style_set_width(&style_def_mysymbol, 58);
  lv_style_set_height(&style_def_mysymbol, 58);
  lv_style_set_bg_color(&style_def_mysymbol, lv_color_black());
  lv_style_set_text_color(&style_def_mysymbol, lv_color_white());
  lv_style_set_text_font(&style_def_mysymbol, &extra_symbols_40);
  /*Add the transition and some transformation to the presses state.*/
  static lv_style_t style_pr_lv_mysymbol;
  lv_style_init(&style_pr_lv_mysymbol);
  lv_style_set_transform_width(&style_pr_lv_mysymbol, 5);
  lv_style_set_transform_height(&style_pr_lv_mysymbol, -5);
  lv_style_set_text_letter_space(&style_pr_lv_mysymbol, 5);
  lv_style_set_transition(&style_pr_lv_mysymbol, &transition_dsc_pr);
  lv_style_set_bg_color(&style_pr_lv_mysymbol, lv_color_black());
  lv_style_set_text_color(&style_pr_lv_mysymbol, lv_color_white());
  lv_style_set_text_font(&style_pr_lv_mysymbol, &extra_symbols_40);

  //LVGL BUILT-IN SYMBOL BUTTONS FIRST
  lv_obj_t * homebtn = lv_btn_create(home_btnm_container);
  lv_obj_align(homebtn, LV_ALIGN_CENTER, 0, 0);
  lv_obj_add_style(homebtn, &style_pr, LV_STATE_PRESSED);
  lv_obj_add_style(homebtn, &style_def, 0);
  lv_obj_t * label = lv_label_create(homebtn);
  lv_label_set_text(label, LV_SYMBOL_HOME);
  lv_obj_align(label, LV_ALIGN_CENTER, 0, 0);
  lv_obj_add_event_cb(homebtn, load_watchface, LV_EVENT_CLICKED, NULL);

  lv_obj_t * settingsbtn = lv_btn_create(home_btnm_container);
  lv_obj_align(settingsbtn, LV_ALIGN_TOP_RIGHT, 0, 0);
  lv_obj_add_style(settingsbtn, &style_pr, LV_STATE_PRESSED);
  lv_obj_add_style(settingsbtn, &style_def, 0);
  lv_obj_t * settingslabel = lv_label_create(settingsbtn);
  lv_label_set_text(settingslabel, LV_SYMBOL_SETTINGS);
  lv_obj_align(settingslabel, LV_ALIGN_CENTER, 0, 0);
  lv_obj_add_event_cb(settingsbtn, event_handler, LV_EVENT_CLICKED, NULL);

  lv_obj_t * audiobtn = lv_btn_create(home_btnm_container);
  lv_obj_align(audiobtn, LV_ALIGN_RIGHT_MID, 0, 0);
  lv_obj_add_style(audiobtn, &style_pr, LV_STATE_PRESSED);
  lv_obj_add_style(audiobtn, &style_def, 0);
  lv_obj_t * audiolabel = lv_label_create(audiobtn);
  lv_label_set_text(audiolabel, LV_SYMBOL_AUDIO);
  lv_obj_align(audiolabel, LV_ALIGN_CENTER, 0, 0);
  lv_obj_add_event_cb(audiobtn, event_handler, LV_EVENT_CLICKED, NULL);

  lv_obj_t * notifbtn = lv_btn_create(home_btnm_container);
  lv_obj_align(notifbtn, LV_ALIGN_TOP_MID, 0, 0);
  lv_obj_add_style(notifbtn, &style_pr, LV_STATE_PRESSED);
  lv_obj_add_style(notifbtn, &style_def, 0);
  lv_obj_t * notiflabel = lv_label_create(notifbtn);
  lv_label_set_text(notiflabel, LV_SYMBOL_BELL);
  lv_obj_align(notiflabel, LV_ALIGN_CENTER, 0, 0);
  lv_obj_add_event_cb(notifbtn, event_handler, LV_EVENT_CLICKED, NULL);

  //NON LVGL SYMBOL BUTTONS

  lv_obj_t * hrbtn = lv_btn_create(home_btnm_container);
  lv_obj_align(hrbtn, LV_ALIGN_TOP_LEFT, 0, 0);
  lv_obj_add_style(hrbtn, &style_pr_lv_mysymbol, LV_STATE_PRESSED);
  lv_obj_add_style(hrbtn, &style_def_mysymbol, 0);
  lv_obj_t * hrlabel = lv_label_create(hrbtn);
  lv_label_set_text(hrlabel, MY_HEART_SYMBOL);
  lv_obj_align(hrlabel, LV_ALIGN_CENTER, 0, 0);
  lv_obj_add_event_cb(hrbtn, event_handler, LV_EVENT_CLICKED, NULL);

  lv_obj_t * exercisebtn = lv_btn_create(home_btnm_container);
  lv_obj_align(exercisebtn, LV_ALIGN_LEFT_MID, 0, 0);
  lv_obj_add_style(exercisebtn, &style_pr_lv_mysymbol, LV_STATE_PRESSED);
  lv_obj_add_style(exercisebtn, &style_def_mysymbol, 0);
  lv_obj_t * exerciselabel = lv_label_create(exercisebtn);
  lv_label_set_text(exerciselabel, MY_RUN_SYMBOL);
  lv_obj_align(exerciselabel, LV_ALIGN_CENTER, 0, 0);
  lv_obj_add_event_cb(exercisebtn, event_handler, LV_EVENT_CLICKED, NULL);

  lv_obj_t * schedulebtn = lv_btn_create(home_btnm_container);
  lv_obj_align(schedulebtn, LV_ALIGN_BOTTOM_LEFT, 0, 0);
  lv_obj_add_style(schedulebtn, &style_pr_lv_mysymbol, LV_STATE_PRESSED);
  lv_obj_add_style(schedulebtn, &style_def_mysymbol, 0);
  lv_obj_t * schedulelabel = lv_label_create(schedulebtn);
  lv_label_set_text(schedulelabel, MY_CALENDAR_SYMBOL);
  lv_obj_align(schedulelabel, LV_ALIGN_CENTER, 0, 0);
  lv_obj_add_event_cb(schedulebtn, event_handler, LV_EVENT_CLICKED, NULL);

  lv_obj_t * timerbtn = lv_btn_create(home_btnm_container);
  lv_obj_align(timerbtn, LV_ALIGN_BOTTOM_MID, 0, 0);
  lv_obj_add_style(timerbtn, &style_pr_lv_mysymbol, LV_STATE_PRESSED);
  lv_obj_add_style(timerbtn, &style_def_mysymbol, 0);
  lv_obj_t * timerlabel = lv_label_create(timerbtn);
  lv_label_set_text(timerlabel, MY_HOURGLASS_SYMBOL);
  lv_obj_align(timerlabel, LV_ALIGN_CENTER, 0, 0);
  lv_obj_add_event_cb(timerbtn, event_handler, LV_EVENT_CLICKED, NULL);

  lv_obj_t * findmebtn = lv_btn_create(home_btnm_container);
  lv_obj_align(findmebtn, LV_ALIGN_BOTTOM_RIGHT, 0, 0);
  lv_obj_add_style(findmebtn, &style_pr_lv_mysymbol, LV_STATE_PRESSED);
  lv_obj_add_style(findmebtn, &style_def_mysymbol, 0);
  lv_obj_t * findmelabel = lv_label_create(findmebtn);
  lv_label_set_text(findmelabel, MY_PHONE_SYMBOL);
  lv_obj_align(findmelabel, LV_ALIGN_CENTER, 0, 0);
  lv_obj_add_event_cb(findmebtn, event_handler, LV_EVENT_CLICKED, NULL);

  lv_group_add_obj(home_group, hrbtn);
  lv_group_add_obj(home_group, notifbtn);
  lv_group_add_obj(home_group, settingsbtn);
  lv_group_add_obj(home_group, exercisebtn);
  lv_group_add_obj(home_group, homebtn);
  lv_group_add_obj(home_group, audiobtn);
  lv_group_add_obj(home_group, schedulebtn);
  lv_group_add_obj(home_group, timerbtn);
  lv_group_add_obj(home_group, findmebtn);

  lv_indev_set_group(indev, home_group);
}




/*  W   A   T   C   H     F   A   C   E  */

lv_obj_t* time_label;
lv_obj_t* date_label;
lv_obj_t* steps_label;
lv_obj_t* battery_label;
lv_obj_t* status_above;
lv_obj_t* icon_bar;

const char* days[7] = {"SUNDAY", "MONDAY", "TUESDAY", "WEDNESDAY", "THURSDAY", "FRIDAY", "SATURDAY"};

void time_label_updater_timer(lv_timer_t* timer)
{
  RTCTime = rtc.now();
  char timeBuf[10];
  sprintf(timeBuf, "%02u\n%02u", RTCTime.hour(), RTCTime.minute());
  if(!(timeBuf==lv_label_get_text(time_label)))
  {
    lv_label_set_text(time_label, timeBuf);
  }
}
void date_label_update_timer(lv_timer_t* timer)
{
  RTCTime = rtc.now();
  char dateBuf[20];
  sprintf(dateBuf, "%.3s %02u", days[RTCTime.dayOfTheWeek()], RTCTime.day());
  lv_label_set_text(date_label, dateBuf);
  if(!(dateBuf==lv_label_get_text(date_label)))
  {
    lv_label_set_text(date_label, dateBuf);
  }
}
void steps_label_update_timer(lv_timer_t* timer)
{
  char stepsoutput[40];
  //icm20948.task();
  sprintf(stepsoutput, "%li", icm_steps);
  SEGGER_RTT_WriteString(0, stepsoutput);
  if(!(stepsoutput == lv_label_get_text(steps_label)))
  {
    lv_label_set_text(steps_label, stepsoutput);
  }
}
void battery_label_update_timer(lv_timer_t* timer)
{
  char bat[30];
  uint8_t snapshotbattery = batteryPercentage;
  sprintf(bat, "%u%% ", snapshotbattery);
  if(snapshotbattery<=5)
  {
    sprintf(bat, "%s%s", bat, LV_SYMBOL_BATTERY_EMPTY);
  }
  if(snapshotbattery<=20)
  {
    sprintf(bat, "%s%s", bat, LV_SYMBOL_BATTERY_1);
  }
  if(snapshotbattery<=40)
  {
    sprintf(bat, "%s%s", bat, LV_SYMBOL_BATTERY_2);
  }
  if(snapshotbattery<=80)
  {
    sprintf(bat, "%s%s", bat, LV_SYMBOL_BATTERY_3);
  }
  if(snapshotbattery<=100)
  {
    sprintf(bat, "%s%s", bat, LV_SYMBOL_BATTERY_FULL);
  }
  if(!(bat==lv_label_get_text(battery_label)))
  {
    lv_label_set_text(battery_label, bat);
  }
}

void watchface_cb(lv_event_t* event)
{
  lv_scr_load(home_scr);
  lv_indev_set_group(indev_lvgl, home_group);
  SEGGER_RTT_WriteString(0, "Loaded home screen");
}

void init_watchface_scr(lv_indev_t* indev)
{
  watchface_group = lv_group_create();

  time_label = lv_label_create(watchface_scr);
  time_label_updater_timer(NULL);
  lv_obj_set_style_text_font(time_label, &hyperlegible_72, 0);
  lv_obj_align(time_label, LV_ALIGN_CENTER, 0, 0);

  static lv_style_t containerStyle2;
  lv_style_init(&containerStyle2);
  lv_style_set_bg_color(&containerStyle2, lv_color_white());
  lv_style_set_bg_opa(&containerStyle2, LV_OPA_TRANSP);
  lv_style_set_border_width(&containerStyle2, 0);
  lv_style_set_border_color(&containerStyle2, lv_color_white());

  lv_obj_t* centreContainer = lv_obj_create(watchface_scr);
  lv_obj_set_size(centreContainer, 185, 40);
  lv_obj_align(centreContainer, LV_ALIGN_CENTER, 0, -3);
  lv_obj_add_style(centreContainer, &containerStyle2, 0);

  status_above = lv_label_create(centreContainer);
  lv_label_set_text(status_above, "INKI");
  lv_obj_set_style_text_font(status_above, &hyperlegible_13, 0);
  lv_obj_align(status_above, LV_ALIGN_TOP_RIGHT, 0, 0);

  battery_label = lv_label_create(centreContainer);
  battery_label_update_timer(NULL);
  lv_obj_set_style_text_font(battery_label, &hyperlegible_13, 0);
  lv_obj_align(battery_label, LV_ALIGN_BOTTOM_RIGHT, 0, 0);

  date_label = lv_label_create(centreContainer);
  date_label_update_timer(NULL);
  lv_obj_set_style_text_font(date_label, &hyperlegible_13, 0);
  lv_obj_align(date_label, LV_ALIGN_BOTTOM_LEFT, 0, 0);

  steps_label = lv_label_create(centreContainer);
  steps_label_update_timer(NULL);
  lv_obj_set_style_text_font(steps_label, &hyperlegible_13, 0);
  lv_obj_align(steps_label, LV_ALIGN_TOP_LEFT, 0, 0);

  static lv_point_t line_points[] = { {5, 0}, {195, 0}};
  static lv_style_t middle_line;
  lv_style_init(&middle_line);
  lv_style_set_line_width(&middle_line, 3);
  lv_style_set_line_color(&middle_line, lv_color_black());
  lv_style_set_line_rounded(&middle_line, false);
  
  lv_obj_t* watch_line;
  SEGGER_RTT_WriteString(0, "Applying style\n");
  watch_line = lv_line_create(watchface_scr);
  lv_line_set_points(watch_line, line_points, 2);
  lv_obj_add_style(watch_line, &middle_line, 0);
  lv_obj_align(watch_line, LV_ALIGN_CENTER, 0, -3);


  lv_obj_t* btn_menu = lv_btn_create(watchface_scr);
  lv_obj_add_event_cb(btn_menu, watchface_cb, LV_EVENT_CLICKED, NULL);
  lv_obj_add_style(btn_menu, &containerStyle2, 0);
  lv_obj_align(btn_menu, LV_ALIGN_BOTTOM_MID, 0, 0);
  lv_group_add_obj(watchface_group, btn_menu);
  lv_indev_set_group(indev, watchface_group);

  
}


void my_print(const char *);

void my_print(const char* buf)
{
  SEGGER_RTT_WriteString(0, buf);
  SEGGER_RTT_WriteString(0, "\n");
}

static void guiTask(void *pvParameter)
{
  (void) pvParameter;
  GuiSemaphore = xSemaphoreCreateMutex();
  I2CSemaphore = xSemaphoreCreateMutex();
  lv_init();
  if (epd.Init(lut_full_update) != 0) {
    SEGGER_RTT_WriteString(0, "e-Paper init failure");
    return;
  }
  SEGGER_RTT_WriteString(0, "e-Paper init");
  epd.ClearFrameMemory(0xFF);
  epd.DisplayFrame();
  epd.ClearFrameMemory(0xFF);
  epd.DisplayFrame();
  epd.SetLut(lut_partial_update);
  digitalWrite(PIN_LED1, LOW);
  
  
  lv_init();

#if LV_USE_LOG != 0
  lv_log_register_print_cb( my_print ); /* register print function for debugging */
#endif

  lv_disp_draw_buf_init( &draw_buf, buf_1, NULL, screenWidth * screenHeight / 8 );

  /*Initialising display*/
  static lv_disp_drv_t disp_drv;
  lv_disp_drv_init( &disp_drv );
  disp_drv.draw_buf = &draw_buf;
  disp_drv.flush_cb = epd_flush;
  disp_drv.set_px_cb = epd_set_px_cb;
  disp_drv.rounder_cb = epd_rounder;
  disp_drv.hor_res = screenWidth;
  disp_drv.ver_res = screenHeight;

  lv_disp_t* disp;
  disp = lv_disp_drv_register( &disp_drv );
  //KEYPAD Initialisation. ToDo - refactor into nice methods once eInk operational.
  static lv_indev_drv_t indev_drv;
  lv_indev_drv_init( &indev_drv );
  indev_drv.type = LV_INDEV_TYPE_KEYPAD;
  indev_drv.read_cb = button_reader;
  indev_drv.feedback_cb = button_feedback;
  indev_lvgl = lv_indev_drv_register( &indev_drv );

  watchface_scr = lv_obj_create(NULL);
  home_scr = lv_obj_create(NULL);
  lv_theme_t* theme = lv_theme_mono_init(disp, false, &lv_font_montserrat_30);
  lv_disp_set_theme(disp, theme);

  //lv_example_btn_1(indev);

  DateTime now = rtc.now();
  char date[100];
  sprintf(date, "%d:%d:%d\n", now.hour(), now.minute(), now.second());
  SEGGER_RTT_WriteString(0, date);
  SEGGER_RTT_WriteString(0,  "Setup done" );
  rtc_config();
  init_watchface_scr(indev_lvgl);
  lv_timer_create(time_label_updater_timer, 20000, NULL);
  lv_timer_create(date_label_update_timer, 2.88e7, NULL);
  lv_timer_create(steps_label_update_timer, 10000, NULL);
  lv_timer_create(battery_label_update_timer, 600000, NULL);
  init_home_scr(indev_lvgl);
  load_watchface(NULL);

  SEGGER_RTT_WriteString(0, "Reached while\n");
  while(1) {
    delay(5);
    if(pdTRUE==xSemaphoreTake(GuiSemaphore, portMAX_DELAY)){
      lv_timer_handler();
      xSemaphoreGive(GuiSemaphore);
    }
  }
  SEGGER_RTT_WriteString(0, "Bruh exited\n");

  vTaskDelete(NULL);
}


#if LV_USE_LOG != 0
/* Serial debugging */
void my_print( lv_log_level_t level, const char * file, uint32_t line, const char * fn_name, const char * dsc )
{
   Serial.printf( "%s(%s)@%d->%s\r\n", file, fn_name, line, dsc );
   Serial.flush();
}
#endif

static void getMAXData(void* pvParameters)
{
  while(1)
  {
    char out[75];
    //read the first 100 samples, and determine the signal range
    if(pdTRUE==xSemaphoreTake(GuiSemaphore, portMAX_DELAY))
    {
      for(i=0;i<BUFFER_SIZE;i++)
      {
        while(digitalRead(oxiInt)==1);  //wait until the interrupt pin asserts
        maxim_max30102_read_fifo((aun_ir_buffer+i), (aun_red_buffer+i));  //read from MAX30102 FIFO
        //sprintf(out, "red:%li, ir:%li\n", aun_red_buffer[i], aun_ir_buffer[i]);
        //SEGGER_RTT_WriteString(0, out);
      }
      xSemaphoreGive(I2CSemaphore);
    }
    //calculate heart rate and SpO2 after BUFFER_SIZE samples (ST seconds of samples) using Robert's method
    rf_heart_rate_and_oxygen_saturation(aun_ir_buffer, BUFFER_SIZE, aun_red_buffer, &n_spo2, &ch_spo2_valid, &n_heart_rate, &ch_hr_valid, &ratio, &correl); 
    sprintf(out, "spo2:%f, hr:%ld\n", n_spo2, n_heart_rate);
    SEGGER_RTT_WriteString(0, out);
    delay(20);
  }
}

static void getIMUData(void* pvParameters)
{
  while(1)
  {
    char out[50];
    if(pdTRUE==xSemaphoreTake(GuiSemaphore, portMAX_DELAY))
    {
      icm20948.task();
      if(icm20948.stepsDataIsReady())
      {
        icm20948.readStepsData(&icm_steps);
      }
      xSemaphoreGive(I2CSemaphore);
    }
    sprintf(out, "Steps: %li\n", icm_steps);
    SEGGER_RTT_WriteString(0, out);
    delay(20);
  }
}

//TODO - debug & fix for better performance
void epd_flush( lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p )
{
  uint8_t *buf = (uint8_t*) color_p;
  epd.SetFrameMemory(buf, area->x1, area->y1, area->x2 - area->x1+1, area->y2-area->y1+1);
  if(lv_disp_flush_is_last(disp))
  {
    epd.MixedRefresh(10);
    //epd.WaitUntilIdle();
  }
  lv_disp_flush_ready(disp);
}

void epd_set_px_cb(lv_disp_drv_t *disp, uint8_t *buf, lv_coord_t buf_w, lv_coord_t x, lv_coord_t y, lv_color_t color, lv_opa_t opa) 
{
  unsigned char bitIndex, a;
  uint16_t byteIndex = (y*(buf_w/8))+((x&0xF8)/8);
  bitIndex = x-(x&0xF8);
  a = 1;
  if(lv_color_brightness(color) > 128)
  {
    buf[byteIndex] |= a << (7-bitIndex);
  }
  else{
    buf[byteIndex] &= ~(a << (7-bitIndex));
  }
}




//DEBUG AND FIX
void epd_rounder( lv_disp_drv_t *disp, lv_area_t *area)
{
  
  //area->x1 = area->x1 & ~(0x7);
  //area->x2 = (area->x2 | 0x7)+1;
  
 area->x1 = 0;
 area->x2 = 200;
 
}

uint8_t button_interface()
{
  if(READ_ENTER==LOW)
  {
    return ENTER_PRESSED;
  } 
  if(READ_ESC==LOW)
  {
    return ESC_PRESSED;
  } 
  if(READ_NEXT==LOW)
  {
    return NEXT_PRESSED;
  } 
  if(READ_PREVIOUS==LOW)
  {
    return PREVIOUS_PRESSED;
  } 
  else
  {
    return 0;
  } 
}

static uint8_t lastKey = 0;

void button_reader(lv_indev_drv_t* drv, lv_indev_data_t* data)
{
  //This is quickly coded as touchscreen will likely be implemented, so this code may be thrown away.
  uint8_t receivedKey = button_interface();
  if(receivedKey!=0)
  {
    data->state = LV_INDEV_STATE_PR;
    switch(receivedKey)
    {
      case ENTER_PRESSED:
        receivedKey = LV_KEY_ENTER;
        break;
      case ESC_PRESSED:
        receivedKey = LV_KEY_ESC;
        break;
      case NEXT_PRESSED:
        receivedKey = LV_KEY_NEXT;
        break;
      case PREVIOUS_PRESSED:
        receivedKey = LV_KEY_PREV;
        break;
    }
    lastKey = receivedKey;
    SEGGER_RTT_WriteString(0, "KEY PRESSED:");
    SEGGER_RTT_PutChar(0, lastKey);
    SEGGER_RTT_WriteString(0, "\n");
  }
  else
  {
    data->state = LV_INDEV_STATE_REL;
  }
  data->key = lastKey;
}


void button_feedback(lv_indev_drv_t* indev, uint8_t e)
{
  if(pdTRUE==xSemaphoreTake(GuiSemaphore, portMAX_DELAY))
  {
    switch(e)
    {
      case LV_EVENT_CLICKED:
        drv.setWaveform(0, 24);
        drv.setWaveform(1, 0);
        drv.go();
        break;
      case LV_EVENT_FOCUSED:
        drv.setWaveform(0, 26);
        drv.setWaveform(1, 0);
        drv.go();
        break;
      case LV_EVENT_LONG_PRESSED:
        drv.setWaveform(0, 34);
        drv.setWaveform(1, 0);
        drv.go();
        break;
    }
  }
  xSemaphoreGive(I2CSemaphore);
}



/*  G U I  */

void startAdv(void)
{  
  // Advertising packet
  // Set the beacon payload using the BLEBeacon class populated
  // earlier in this example
  Bluefruit.Advertising.setBeacon(beacon);

  // Secondary Scan Response packet (optional)
  // Since there is no room for 'Name' in Advertising packet
  Bluefruit.ScanResponse.addName();
  
  /* Start Advertising
   * - Enable auto advertising if disconnected
   * - Timeout for fast mode is 30 seconds
   * - Start(timeout) with timeout = 0 will advertise forever (until connected)
   * 
   * Apple Beacon specs
   * - Type: Non connectable, undirected
   * - Fixed interval: 100 ms -> fast = slow = 100 ms
   */
  //Bluefruit.Advertising.setType(BLE_GAP_ADV_TYPE_ADV_NONCONN_IND);
  Bluefruit.Advertising.restartOnDisconnect(true);
  Bluefruit.Advertising.setInterval(160, 160);    // in unit of 0.625 ms
  Bluefruit.Advertising.setFastTimeout(30);      // number of seconds in fast mode
  Bluefruit.Advertising.start(0);                // 0 = Don't stop advertising after n seconds  
}

void i2c_scan(){
    uint8_t error;
    for(uint8_t add_int = 0; add_int < number_i2c_addr; add_int++ ){
        Serial.printf("Scanning 0x%02X for slave...", poss_addresses[add_int]);
        Wire.beginTransmission(poss_addresses[add_int]);
        error = Wire.endTransmission();
        if (error == 0){
            Serial.println("found.");
            if(poss_addresses[add_int] == 0x69 || poss_addresses[add_int] == 0x68){
                Serial.println("\t- address is ICM.");
                ICM_address = poss_addresses[add_int];
                ICM_found = true;
            }
        }
    }
}

void setup()
{
  pinMode(PIN_BUTTON1, INPUT_PULLUP);
  pinMode(PIN_BUTTON2, INPUT_PULLUP);
  pinMode(PIN_BUTTON3, INPUT_PULLUP);
  pinMode(PIN_BUTTON4, INPUT_PULLUP);
  pinMode(PIN_LED1, OUTPUT);
  //Serial.begin( 9600 ); /* prepare for possible serial debug */
  //while ( !Serial ) delay(10);
  Wire.begin();
  delay(1000);
  SEGGER_RTT_WriteString(0, "Welcome to InkWatchOS\n" );
  SEGGER_RTT_WriteString(0,  "LVGL V8.0.X\n" );
  rtc.begin();
  SEGGER_RTT_WriteString(0,  "Init rtc \n");
  if(!rtc.isrunning())
  {
    SEGGER_RTT_WriteString(0, "Setting time to build date:\n");
    SEGGER_RTT_WriteString(0, __DATE__);
    SEGGER_RTT_WriteString(0, " ");
    SEGGER_RTT_WriteString(0, __TIME__);
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }
  rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  drv.begin();
  //SEGGER_RTT_WriteString(0, "Init drv\n");
  drv.selectLibrary(1);
  drv.setMode(DRV2605_MODE_INTTRIG);

  maxim_max30102_reset();
  delay(1000);
  maxim_max30102_read_reg(REG_INTR_STATUS_1, &uch_dummy);
  maxim_max30102_init();
  old_n_spo2=0.0; 

  SEGGER_RTT_WriteString(0, "Init MAX30105\n");
  
  i2c_scan();
  if(ICM_found)
  {
    icm20948.init(icmSettings);
  }
  SEGGER_RTT_WriteString(0, "Init ICM-20948");

  Bluefruit.begin(1, 1);
  Bluefruit.setTxPower(0);
  startAdv();
  beacon.setManufacturer(0x0059);
  xTaskCreate(guiTask, "gui", 4096*2, NULL, tskIDLE_PRIORITY+2, &Handle_GUIUpdate);
  /* Scheduling MAX Data collection so it doesn't just suck up all the CPU cycles lmao */
  delay(8000);
  //xTaskCreate(getMAXData, "max30105", 4096*2, NULL, tskIDLE_PRIORITY+1, &Handle_maxData);
  xTaskCreate(getIMUData, "icm20948", 4096*2, NULL, tskIDLE_PRIORITY+1, &Handle_imuData);
}




void loop()
{
  char taskReport[300];
  char memReport[50];
  vTaskList(taskReport);
  SEGGER_RTT_SetTerminal(1);
  SEGGER_RTT_WriteString(0, "**********************************\n");
  SEGGER_RTT_WriteString(0, "Task          State Prio Stack Num\n"); 
  SEGGER_RTT_WriteString(0, "**********************************\n");
  SEGGER_RTT_WriteString(0, taskReport);
  SEGGER_RTT_WriteString(0, "\n**********************************\n\n");
  SEGGER_RTT_SetTerminal(0);
  delay(500); 
}