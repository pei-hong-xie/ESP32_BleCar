#include <Arduino.h>
#include <U8g2lib.h>
#include <WiFi.h> //wifi功能需要的库
#include "init.h"
#include "test.h"
#include "config.h"
#include <XboxSeriesXControllerESP32_asukiaaa.hpp>

XboxSeriesXControllerESP32_asukiaaa::Core
    xboxController("0c:35:26:cc:73:bd");
String xbox_string()
{
  String str = String(xboxController.xboxNotif.btnY) + "," +
               String(xboxController.xboxNotif.btnX) + "," +
               String(xboxController.xboxNotif.btnB) + "," +
               String(xboxController.xboxNotif.btnA) + "," +
               String(xboxController.xboxNotif.btnLB) + "," +
               String(xboxController.xboxNotif.btnRB) + "," +
               String(xboxController.xboxNotif.btnSelect) + "," +
               String(xboxController.xboxNotif.btnStart) + "," +
               String(xboxController.xboxNotif.btnXbox) + "," +
               String(xboxController.xboxNotif.btnShare) + "," +
               String(xboxController.xboxNotif.btnLS) + "," +
               String(xboxController.xboxNotif.btnRS) + "," +
               String(xboxController.xboxNotif.btnDirUp) + "," +
               String(xboxController.xboxNotif.btnDirRight) + "," +
               String(xboxController.xboxNotif.btnDirDown) + "," +
               String(xboxController.xboxNotif.btnDirLeft) + "," +
               String(xboxController.xboxNotif.joyLHori) + "," +//L水平
               String(xboxController.xboxNotif.joyLVert) + "," +
               String(xboxController.xboxNotif.joyRHori) + "," +
               String(xboxController.xboxNotif.joyRVert) + "," +
               String(xboxController.xboxNotif.trigLT) + "," +
               String(xboxController.xboxNotif.trigRT) + "\n";
  return str;
};



//需要启用哪些功能就取消掉对应的初始化与测试函数的注释
void setup()
{
  // Buzzer_Init();     //蜂鸣器测试初始化
  // LED_Init();        //LED测试初始化
  // Button_Init();     //按钮测试初始化
  // OLED_Init(&u8g2);  //OLED显示屏测试初始化
  // UART_Init();       //串口测试初始化
  //PWM_Init();        //PWM测试初始化
  //Motor_Init();     //电机测试初始化
  //UDP_Init();        //UDP通信测试初始化
  // ADC_Init();         //ADC红外循迹模块初始化
  //BLE_Init();           //蓝牙服务初始化：在手机端使用蓝牙调试器连接芯片创建的蓝牙服务，进行收发数据
  Serial.begin(115200);
  Serial.println("Starting NimBLE Client");
  xboxController.begin();
}

 void loop()
{
  // LED_Test();       //LED测试: 位于板中心的绿色LED闪烁
  // Buzzer_Test();    //蜂鸣器测试: 板子上的蜂鸣器反复响
  //  OLED_Test(&u8g2); //OLED测试: OLED显示屏上显示字母，数字，简单图形
  // Button_Test();    //按钮测试: 按压按钮控制LED闪烁
  // UART_Test();      //串口测试: 串口打印指定数据给电脑，需要配合串口助手完成
  //PWM_Test();       //PWM测试: 通过控制GPIO的PWM占空比来实现板上LED呼吸灯的效果
  //Motor_Test();     //电机测试: 控制PWM输出来控制小车的电机旋转，实现小车四个轮子前进，急刹，后退的效果
  // UDP_Test();       //UDP通信测试: 通过连接指定WIFI，在该WIFI下的局域网内实现UDP通信，电脑端的UDP网络调试助手发送数据给主控，主控将接收的数据通过自己的串口打印出来，再将数据回发给电脑
  // ADC_Test();        //ADC红外循迹模块读取测试：读取红外循迹模块的模拟电压值
  xboxController.onLoop();
  if (xboxController.isConnected())
  {
    if (xboxController.isWaitingForFirstNotification())
    {
      Serial.println("waiting for first notification");
    }
    else
    {
      Serial.print(xbox_string());
    }
      delay(500);
  }
  else
  {
    Serial.println("not connected");
    if (xboxController.getCountFailedConnection() > 2)
    {
      ESP.restart();
    }
    delay(500);
  }



 }



