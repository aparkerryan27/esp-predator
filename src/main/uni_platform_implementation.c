/****************************************************************************
http://retro.moe/unijoysticle2

Copyright 2019 Ricardo Quesada

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
****************************************************************************/

// Debug version

#include "uni_platform_implementation.h"

#include <stdio.h>
#include <string.h>
#include "uni_debug.h"
#include "uni_gamepad.h"
#include "uni_hid_device.h"

#include "driver/mcpwm.h"
#include "soc/mcpwm_periph.h"

// WHEELS
#define GPIO_PWM0A0_OUT 25   //Set GPIO 32 as PWM0A1 in unit 0
#define GPIO_PWM0B0_OUT 26   //Set GPIO 33 as PWM0B1 in unit 0
#define GPIO_PWM1A0_OUT 33   //Set GPIO 34 as PWM0A2 in unit 1
#define GPIO_PWM1B0_OUT 32   //Set GPIO 35 as PWM0B2 in unit 1

//#define GPIO_PWM0A0_OUT 33   //Set GPIO 32 as PWM0A1 in unit 0
//#define GPIO_PWM0B0_OUT 32   //Set GPIO 33 as PWM0B1 in unit 0
//#define GPIO_PWM1A0_OUT 26   //Set GPIO 34 as PWM0A2 in unit 1
//#define GPIO_PWM1B0_OUT 25   //Set GPIO 35 as PWM0B2 in unit 1

// LEDS
#define LED1 12      //Set GPIO 12 **
#define LED2 14
#define LED3 27

// PUFFER
//#define GPIO_PWM1A1_OUT 15
//#define GPIO_PWM1B1_OUT 16
#define GPIO_PWM1A1_OUT 18
#define GPIO_PWM1B1_OUT 19

//
// Globals
//
static int g_delete_keys = 0;

// PC Debug "instance"
typedef struct pc_debug_instance_s {
  uni_gamepad_seat_t gamepad_seat;  // which "seat" is being used
} pc_debug_instance_t;

// Declarations
static void trigger_event_on_gamepad(uni_hid_device_t* d);
static pc_debug_instance_t* get_pc_debug_instance(uni_hid_device_t* d);

//
// Platform Overrides
//
static void pc_debug_init(int argc, const char** argv){
  printf("initializing mcpwm gpio...\n");
  // WHEELS
  mcpwm_gpio_init(MCPWM_UNIT_0, MCPWM0A, GPIO_PWM0A0_OUT); // Unit (0 or 1), PWM output pair (0, 1, or 2), (MCPWM_UNIT_0 MCPWM0A) --> pin 25
  mcpwm_gpio_init(MCPWM_UNIT_0, MCPWM0B, GPIO_PWM0B0_OUT);
  mcpwm_gpio_init(MCPWM_UNIT_1, MCPWM0A, GPIO_PWM1A0_OUT);
  mcpwm_gpio_init(MCPWM_UNIT_1, MCPWM0B, GPIO_PWM1B0_OUT); 
  
  // LEDS
  mcpwm_gpio_init(MCPWM_UNIT_0, MCPWM1A, LED1); // intialize GPI0 pin
  mcpwm_gpio_init(MCPWM_UNIT_0, MCPWM1B, LED3);
  mcpwm_gpio_init(MCPWM_UNIT_0, MCPWM2A, LED2);

  // PUFFER
  mcpwm_gpio_init(MCPWM_UNIT_1, MCPWM1A, GPIO_PWM1A1_OUT);
  mcpwm_gpio_init(MCPWM_UNIT_1, MCPWM1B, GPIO_PWM1B1_OUT );
  
  //mcpwm_gpio_init(MCPWM_UNIT_0, MCPWM2B, GPIO_PWM2B_OUT);

  


  // MCPWM_GPIO_INIT
  // This function initializes one gpio at a time.
  // Parameters
  // mcpwm_num: set Mset MCPWM signals, 
  // io_signal: each MCPWM unit has 6 output(MCPWMXA, MCPWMXB) and 9 input(SYNC_X, FAULT_X, CAP_X) ‘X’ is timer_num(0-2) CPWM unit(0-1)
  // gpio_num: set this to configure gpio for MCPWM, if you want to use gpio16, gpio_num = 16




  //  MCPWM UNIT0_0 CONFIGURATION
  mcpwm_config_t pwm_config0;
  pwm_config0.frequency = 100000;    //frequency = 100Hz,
  pwm_config0.cmpr_a = 0;    //duty cycle of PWMxA = 0
  pwm_config0.cmpr_b = 0;    //duty cycle of PWMxb = 0
  pwm_config0.counter_mode = MCPWM_UP_COUNTER;
  pwm_config0.duty_mode = MCPWM_DUTY_MODE_0;
  mcpwm_init(MCPWM_UNIT_0, MCPWM_TIMER_0, &pwm_config0); // Configure PWM0A & PWM0B with above settings

  // MCPWM UNIT0_1 CONFIGURATION
  pwm_config0.frequency = 100000;     //frequency = 500Hz
  pwm_config0.cmpr_a = 0;       //duty cycle of PWMxA = 45.9%
  pwm_config0.cmpr_b = 0;    //duty cycle of PWMxb = 07.0%
  pwm_config0.counter_mode = MCPWM_UP_COUNTER;
  pwm_config0.duty_mode = MCPWM_DUTY_MODE_0;
  mcpwm_init(MCPWM_UNIT_0, MCPWM_TIMER_1, &pwm_config0);   //Configure PWM1A & PWM1B with above settings

  // MCPWM UNIT0_2 CONFIGURATION
  pwm_config0.frequency = 100000;     //frequency = 400Hz
  pwm_config0.cmpr_a = 0;       //duty cycle of PWMxA = 23.2%
  pwm_config0.cmpr_b = 0;       //duty cycle of PWMxb = 97.0%
  pwm_config0.counter_mode = MCPWM_UP_DOWN_COUNTER; //frequency is half when up down count mode is set i.e. SYMMETRIC PWM
  pwm_config0.duty_mode = MCPWM_DUTY_MODE_1;
  mcpwm_init(MCPWM_UNIT_0, MCPWM_TIMER_2, &pwm_config0);   //Configure PWM2A & PWM2B with above settings



  //  MCPWM UNIT1_0 CONFIGURATION
  mcpwm_config_t pwm_config1;
  pwm_config1.frequency = 100000;    //frequency = 100Hz,
  pwm_config1.cmpr_a = 0;    //duty cycle of PWMxA = 0
  pwm_config1.cmpr_b = 0;    //duty cycle of PWMxb = 0
  pwm_config1.counter_mode = MCPWM_UP_COUNTER;
  pwm_config1.duty_mode = MCPWM_DUTY_MODE_0;
  mcpwm_init(MCPWM_UNIT_1, MCPWM_TIMER_0, &pwm_config1);

  //  MCPWM UNIT1_1 CONFIGURATION
  pwm_config1.frequency = 100000;    //frequency = 100Hz,
  pwm_config1.cmpr_a = 0;    //duty cycle of PWMxA = 0
  pwm_config1.cmpr_b = 0;    //duty cycle of PWMxb = 0
  pwm_config1.counter_mode = MCPWM_UP_COUNTER;
  pwm_config1.duty_mode = MCPWM_DUTY_MODE_0;
  mcpwm_init(MCPWM_UNIT_1, MCPWM_TIMER_1, &pwm_config1);
}

static void pc_debug_on_init_complete(void) {
  logi("pc_debug: on_init_complete()\n");
}

static void pc_debug_on_device_connected(uni_hid_device_t* d) {
  logi("pc_debug: device connected: %p\n", d);
}

static void pc_debug_on_device_disconnected(uni_hid_device_t* d) {
  logi("pc_debug: device disconnected: %p\n", d);
}

static int pc_debug_on_device_ready(uni_hid_device_t* d) {
  logi("pc_debug: device ready: %p\n", d);
  pc_debug_instance_t* ins = get_pc_debug_instance(d);
  ins->gamepad_seat = GAMEPAD_SEAT_A;

  trigger_event_on_gamepad(d);
  return 0;
}

float f_abs(float n){
  if (n>=0) return n;
  return -n;
}

// OPERATE
// mcpwm_set_signal_low(MCPWM_UNIT_0, MCPWM_TIMER_0,MCPWM_OPR_B); // makes motor turn with max speed

void set_pwm0(int32_t motor){
  float duty = f_abs((float) motor / 5.12)/4;
  //float duty = f_abs((float) motor / 5.12)/4; // duty value
  //float led_duty = 50.0;
  if (motor>=0){
    mcpwm_set_signal_low(MCPWM_UNIT_0, MCPWM_TIMER_0,MCPWM_OPR_B); // makes motorB stop
    mcpwm_set_duty(MCPWM_UNIT_0, MCPWM_TIMER_0, MCPWM_OPR_A, duty); // used to vary PWM's duty cycle
    mcpwm_set_duty_type(MCPWM_UNIT_0, MCPWM_TIMER_0, MCPWM_OPR_A, MCPWM_DUTY_MODE_0); // used to alter phase of PWM signal of motorA
  } else {
    mcpwm_set_signal_low(MCPWM_UNIT_0, MCPWM_TIMER_0, MCPWM_OPR_A); 
    mcpwm_set_duty(MCPWM_UNIT_0, MCPWM_TIMER_0, MCPWM_OPR_B, duty);
    mcpwm_set_duty_type(MCPWM_UNIT_0, MCPWM_TIMER_0, MCPWM_OPR_B, MCPWM_DUTY_MODE_0);
  }

  // LED //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  // 1
  //mcpwm_set_signal_low(MCPWM_UNIT_0, MCPWM_TIMER_1,MCPWM_OPR_A);
  //mcpwm_set_duty(MCPWM_UNIT_0, MCPWM_TIMER_1, MCPWM_OPR_A, led_duty); // used to vary PWM's duty cycle
  //mcpwm_set_duty_type(MCPWM_UNIT_0, MCPWM_TIMER_1, MCPWM_OPR_A, MCPWM_DUTY_MODE_0); // used to alter phase of PWM signal
  
  // 2
  //mcpwm_set_signal_low(MCPWM_UNIT_0, MCPWM_TIMER_2, MCPWM_OPR_A);
  //mcpwm_set_duty(MCPWM_UNIT_0, MCPWM_TIMER_2, MCPWM_OPR_A, led_duty);
  //mcpwm_set_duty_type(MCPWM_UNIT_0, MCPWM_TIMER_2, MCPWM_OPR_A, MCPWM_DUTY_MODE_0);

  // 3
  //mcpwm_set_signal_low(MCPWM_UNIT_0, MCPWM_TIMER_1, MCPWM_OPR_B);
  //mcpwm_set_duty(MCPWM_UNIT_0, MCPWM_TIMER_1, MCPWM_OPR_B, led_duty);
  //mcpwm_set_duty_type(MCPWM_UNIT_0, MCPWM_TIMER_1, MCPWM_OPR_B, MCPWM_DUTY_MODE_0);
}

void set_pwm1(int32_t motor){
  float duty = f_abs((float) motor / 5.12)/4;
  //float duty = f_abs((float) motor / 5.12)/4;
  if (motor>=0){
    mcpwm_set_signal_low(MCPWM_UNIT_1, MCPWM_TIMER_0, MCPWM_OPR_B);
    mcpwm_set_duty(MCPWM_UNIT_1, MCPWM_TIMER_0, MCPWM_OPR_A, duty);
    mcpwm_set_duty_type(MCPWM_UNIT_1, MCPWM_TIMER_0, MCPWM_OPR_A, MCPWM_DUTY_MODE_0);
  }else {
    mcpwm_set_signal_low(MCPWM_UNIT_1, MCPWM_TIMER_0, MCPWM_OPR_A);
    mcpwm_set_duty(MCPWM_UNIT_1, MCPWM_TIMER_0, MCPWM_OPR_B, duty);
    mcpwm_set_duty_type(MCPWM_UNIT_1, MCPWM_TIMER_0, MCPWM_OPR_B, MCPWM_DUTY_MODE_0);
  }
}


// cam ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void set_pwm2(int32_t motor){
  //float duty = f_abs((float) motor / 5.12)/8;
  float duty = f_abs((float) motor / 5.12);
  //float duty = 1;
  if (motor>=0){
    mcpwm_set_signal_low(MCPWM_UNIT_1, MCPWM_TIMER_1, MCPWM_OPR_B);
    mcpwm_set_duty(MCPWM_UNIT_1, MCPWM_TIMER_1, MCPWM_OPR_A, duty);
    mcpwm_set_duty_type(MCPWM_UNIT_1, MCPWM_TIMER_1, MCPWM_OPR_A, MCPWM_DUTY_MODE_0);
  }else {
    mcpwm_set_signal_low(MCPWM_UNIT_1, MCPWM_TIMER_1, MCPWM_OPR_A);
    mcpwm_set_duty(MCPWM_UNIT_1, MCPWM_TIMER_1, MCPWM_OPR_B, duty);
    mcpwm_set_duty_type(MCPWM_UNIT_1, MCPWM_TIMER_1, MCPWM_OPR_B, MCPWM_DUTY_MODE_0);
  }
}





// CONTROLLER BOOLEANS
static void pc_debug_on_gamepad_data(uni_hid_device_t* d, uni_gamepad_t* gp) {
  UNUSED(d);
  static uni_gamepad_t prev = {0};
  static int32_t motor_0 = {0};
  static int32_t motor_1 = {0};
  static int32_t ccw = 512;
  static int32_t cw = -508;
  float led_duty = 100.0;
  


  if (memcmp(&prev, gp, sizeof(*gp)) == 0) {
    return;
  }
  prev = *gp;
  if (motor_0 != prev.axis_y) {
    //set_motor 0
    motor_0 = prev.axis_y;
    set_pwm0(motor_0);
  }
  if (motor_1 != prev.axis_ry) {
    //set_motor 1
    motor_1 = prev.axis_ry;
    set_pwm1(motor_1);
    //set_pwm2(motor_1);
  }

  // turn cam motor cw
  if (prev.buttons == BUTTON_A){
    logi("A pressed \n");
    set_pwm2(cw);
  }
  // turn cam motor ccw
  if (prev.buttons == BUTTON_B){
    logi("B pressed \n");
    set_pwm2(ccw);
  }
  // turn cam motor off
  if (prev.buttons == 0){
    logi("motor off \n");
    set_pwm2(0);
  } 

  // TURN ON LEDS
  if (prev.dpad == 1){
    // 1
    //mcpwm_set_signal_low(MCPWM_UNIT_0, MCPWM_TIMER_1,MCPWM_OPR_A);
    mcpwm_set_duty(MCPWM_UNIT_0, MCPWM_TIMER_1, MCPWM_OPR_A, led_duty); // used to vary PWM's duty cycle
    mcpwm_set_duty_type(MCPWM_UNIT_0, MCPWM_TIMER_1, MCPWM_OPR_A, MCPWM_DUTY_MODE_0); // used to alter phase of PWM signal
  
    // 2
    //mcpwm_set_signal_low(MCPWM_UNIT_0, MCPWM_TIMER_2, MCPWM_OPR_A);
    mcpwm_set_duty(MCPWM_UNIT_0, MCPWM_TIMER_2, MCPWM_OPR_A, led_duty);
    mcpwm_set_duty_type(MCPWM_UNIT_0, MCPWM_TIMER_2, MCPWM_OPR_A, MCPWM_DUTY_MODE_0);

    // 3
    //mcpwm_set_signal_low(MCPWM_UNIT_0, MCPWM_TIMER_1, MCPWM_OPR_B);
    mcpwm_set_duty(MCPWM_UNIT_0, MCPWM_TIMER_1, MCPWM_OPR_B, led_duty);
    mcpwm_set_duty_type(MCPWM_UNIT_0, MCPWM_TIMER_1, MCPWM_OPR_B, MCPWM_DUTY_MODE_0);

  }
  if (prev.dpad == 2){
    // 1
    mcpwm_set_signal_low(MCPWM_UNIT_0, MCPWM_TIMER_1,MCPWM_OPR_B);
  
    // 2
    mcpwm_set_signal_low(MCPWM_UNIT_0, MCPWM_TIMER_2, MCPWM_OPR_A);

    // 3
    mcpwm_set_signal_low(MCPWM_UNIT_0, MCPWM_TIMER_1, MCPWM_OPR_A);

  }





  // turn on leds
  //if (prev.buttons == BUTTON_A){
    //set_pwm2(motor_2);
  //}
  ////////////////////////////////////////////if (BUTTON_A == )
  
  
  //uni_gamepad_dump(gp);
  logi("%d , %d \n", motor_0, motor_1); // print joystick axis commands
  
  logi("dpad %d \n", prev.dpad);
  logi("previous buttton %d \n", prev.buttons);


}


static int32_t pc_debug_get_property(uni_platform_property_t key) {
  logi("pc_debug: get_property(): %d\n", key);
  if (key != UNI_PLATFORM_PROPERTY_DELETE_STORED_KEYS) return -1;
  return g_delete_keys;
}

static void pc_debug_on_device_oob_event(uni_hid_device_t* d,
                                         uni_platform_oob_event_t event) {
  if (d == NULL) {
    loge("ERROR: pc_debug_on_device_gamepad_event: Invalid NULL device\n");
    return;
  }
  logi("pc_debug: on_device_oob_event(): %d\n", event);

  if (event != UNI_PLATFORM_OOB_GAMEPAD_SYSTEM_BUTTON) {
    loge("ERROR: pc_debug_on_device_gamepad_event: unsupported event: 0x%04x\n",
         event);
    return;
  }

  pc_debug_instance_t* ins = get_pc_debug_instance(d);
  ins->gamepad_seat =
      ins->gamepad_seat == GAMEPAD_SEAT_A ? GAMEPAD_SEAT_B : GAMEPAD_SEAT_A;

  trigger_event_on_gamepad(d);
}

//
// Helpers
//
static pc_debug_instance_t* get_pc_debug_instance(uni_hid_device_t* d) {
  return (pc_debug_instance_t*)&d->platform_data[0];
}

static void trigger_event_on_gamepad(uni_hid_device_t* d) {
  pc_debug_instance_t* ins = get_pc_debug_instance(d);

  if (d->report_parser.set_rumble != NULL) {
    d->report_parser.set_rumble(d, 0x80 /* value */, 15 /* duration */);
  }

  if (d->report_parser.set_player_leds != NULL) {
    d->report_parser.set_player_leds(d, ins->gamepad_seat);
  }

  if (d->report_parser.set_lightbar_color != NULL) {
    uint8_t red = (ins->gamepad_seat & 0x01) ? 0xff : 0;
    uint8_t green = (ins->gamepad_seat & 0x02) ? 0xff : 0;
    uint8_t blue = (ins->gamepad_seat & 0x04) ? 0xff : 0;
    d->report_parser.set_lightbar_color(d, red, green, blue);
  }
}

//
// Entry Point
//
struct uni_platform* uni_platform_pc_debug_create(void) {
  static struct uni_platform plat;

  plat.name = "PC Debug";
  plat.init = pc_debug_init;
  plat.on_init_complete = pc_debug_on_init_complete;
  plat.on_device_connected = pc_debug_on_device_connected;
  plat.on_device_disconnected = pc_debug_on_device_disconnected;
  plat.on_device_ready = pc_debug_on_device_ready;
  plat.on_device_oob_event = pc_debug_on_device_oob_event;
  plat.on_gamepad_data = pc_debug_on_gamepad_data;
  plat.get_property = pc_debug_get_property;

  return &plat;
}