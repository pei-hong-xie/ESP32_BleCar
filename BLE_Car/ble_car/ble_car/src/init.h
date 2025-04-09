#ifndef __INIT_H
#define __INIT_H
#include "config.h"
#include <U8g2lib.h>
extern U8G2_SSD1306_128X64_NONAME_F_SW_I2C u8g2; 

 void Buzzer_Init(void);
 void LED_Init(void);
 void Button_Init(void);
 void OLED_Init(U8G2_SSD1306_128X64_NONAME_F_SW_I2C *u8g2);
 void UART_Init(void);
 void PWM_Init(void);
 void Motor_Init(void);
 void UDP_Init(void);
 void ADC_Init(void);
 void BLE_Init(void);

 #endif




 