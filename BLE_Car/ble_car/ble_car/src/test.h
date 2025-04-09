#ifndef __TEST_H
#define __TEST_H
#include <U8g2lib.h>
#include "config.h"
void  LED_Test(void);       //LED测试: 位于板中心的绿色LED闪烁
void  Buzzer_Test();    //蜂鸣器测试: 板子上的蜂鸣器反复响
void  OLED_Test(U8G2_SSD1306_128X64_NONAME_F_SW_I2C *u8g2); //OLED测试: OLED显示屏上显示字母，数字，简单图形
void  Button_Test();    //按钮测试: 按压按钮控制LED闪烁
void  UART_Test();      //串口测试: 串口打印指定数据给电脑，需要配合串口助手完成
void  PWM_Test();       //PWM测试: 通过控制GPIO的PWM占空比来实现板上LED呼吸灯的效果
void  Motor_Test();     //电机测试: 控制PWM输出来控制小车的电机旋转，实现小车四个轮子前进，急刹，后退的效果
void  UDP_Test();       //UDP通信测试: 通过连接指定WIFI，在该WIFI下的局域网内实现UDP通信，电脑端的UDP网络调试助手发送数据给主控，主控将接收的数据通过自己的串口打印出来，再将数据回发给电脑
void  ADC_Test();        //ADC红外循迹模块读取测试：读取红外循迹模块的模拟电压值

//  void LED_Test(void);
//  void Buzzer_Test(void);
//  void OLED_Test(U8G2_SSD1306_128X64_NONAME_F_SW_I2C *u8g2);
//  void Button_Test(void);
//  void UART_Test(void);
//  void PWM_Test(void);
//  void Motor_Test(void);
//  void UDP_Test(void);
//  void ADC_Test(void);
#endif