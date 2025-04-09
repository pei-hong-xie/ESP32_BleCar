#include <init.h>
#include <Arduino.h>
#include <U8g2lib.h>
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>
#include <WiFi.h> //wifi功能需要的库
#include <test.h>
#include "config.h"
void LED_Test(void)
{
  static int Flag = 0 ;
  if(Flag==0)
  {
    digitalWrite(2,HIGH);
    Flag = 1 ;
  }
  else
  {
    digitalWrite(2,LOW);
    Flag = 0 ;
  }
}

void Buzzer_Test(void)
{
  static int Flag = 0 ;
  if(Flag==0)
  {
    digitalWrite(33,HIGH);
    Flag = 1 ;
  }
  else
  {
    digitalWrite(33,LOW);
    Flag = 0 ;
  }
}

void Button_Test(void)
{
  static int Flag = 0 ;
  if(digitalRead(18)==LOW)
  {
    delay(3);
    if(digitalRead(18)==LOW)
    {
      if(Flag==0) {digitalWrite(2,LOW);Flag = 1 ;}
      else if(Flag==1) {digitalWrite(2,HIGH);Flag = 0 ;}
    }
  }
}

void OLED_Test(U8G2_SSD1306_128X64_NONAME_F_SW_I2C *u8g2)
{
  // 清空显示屏内容
  u8g2->clearBuffer();

  // 添加文本
  u8g2->setFont(u8g2_font_ncenB08_tr);//设置字体
  u8g2->drawStr(0, 10, "Hello, world!");

  u8g2->setCursor(5, 30);//设置光标位置
  u8g2->enableUTF8Print();//使能UTF-8编码打印功能
  u8g2->setFont(u8g2_font_wqy12_t_gb2312b);//设置中文字符集
  u8g2->print("你好，世界！");//打印中文

  u8g2->setCursor(12, 60);
  u8g2->setFont(u8g2_font_ncenR18_tn);//设置字体
  int i = 2024 ;
  u8g2->print(i);

  u8g2->setCursor(80, 20);
  u8g2->drawRFrame(80,20,40,40,7);//绘制一个位于(80,20)，宽40像素，高40像素，圆角半径7像素的圆角矩形

  u8g2->setCursor(85, 25);
  u8g2->drawBox(85,25,30,30);//绘制一个位于(85,25)，宽30像素，高30像素的实心矩形
  //发送并刷新缓存
  u8g2->sendBuffer();
}

void UART_Test(void)
{
  int NowYear = 2024 ;
  int LastYear = 2023 ;

  Serial.println("hello,world!");//println函数会在每次打印之后自动加\n换行符
  Serial.print("goodbye,");       //print函数则是直接打印，不自动加\n
  Serial.print(LastYear);
  Serial.print('\n');
  Serial.printf("hello,%d!\n",NowYear);//printf函数的用法与C语言中的printf函数一致

  Serial.print('\n');
}

void PWM_Test(void)
{
  /*在for循环内不断改变输出的占空比，从而实现呼吸灯缓亮缓灭的效果*/
  for(int dutyCycle = 0; dutyCycle <= 2000; dutyCycle++)//dutyCycle为占空比，范围为 0-4095，这里为了更快显现效果将占空比范围设置为 0-2000
  {   
    ledcWrite(2, dutyCycle);//指定第二通道输出一定占空比波形
    delay(1);
  }
  delay(100);
    for(int dutyCycle = 2000; dutyCycle >= 0; dutyCycle--)
  {   
    ledcWrite(2, dutyCycle);//指定第二通道输出一定占空比波形
    delay(1);
  }
}

void Motor_Test(void)
{
  ledcWrite(0, 0);     //前进
  ledcWrite(1, 4095);
  ledcWrite(2, 0);  
  ledcWrite(3, 4095);
  ledcWrite(4, 0);  
  ledcWrite(5, 4095);
  ledcWrite(6, 0);  
  ledcWrite(7, 4095);
  delay(500);

  ledcWrite(0, 4095);  //急刹
  ledcWrite(1, 4095);
  ledcWrite(2, 4095);  
  ledcWrite(3, 4095);
  ledcWrite(4, 4095);  
  ledcWrite(5, 4095);
  ledcWrite(6, 4095);  
  ledcWrite(7, 4095);
  delay(500);

  ledcWrite(0, 4095);  //后退
  ledcWrite(1, 0);
  ledcWrite(2, 4095);  
  ledcWrite(3, 0);
  ledcWrite(4, 4095);  
  ledcWrite(5, 0);
  ledcWrite(6, 4095);  
  ledcWrite(7, 0);
  delay(500);
}


void ADC_Test(void)
{
  uint16_t value[5] ;
  value[0] = analogRead(32);//读取GPIO32的模拟电压
  value[1] = analogRead(35);
  value[2] = analogRead(34);
  value[3] = analogRead(39);
  value[4] = analogRead(36);

  Serial.printf("%d,%d,%d,%d,%d\n",value[0],value[1],value[2],value[3],value[4]);//使用串口打印出来
}
