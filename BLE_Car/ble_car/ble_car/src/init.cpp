#include <Arduino.h>
#include <U8g2lib.h>
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>
#include <WiFi.h> //wifi功能需要的库
#include <init.h>
#include "config.h"
#define CHARACTERISTIC_UUID "beb5483e-36e1-4688-b7f5-ea07361b26a8"  //蓝牙服务下的特征UUID
#define SERVICE_UUID        "4fafc201-1fb5-459e-8fcc-c5c9c331914b"  //蓝牙服务UUID

U8G2_SSD1306_128X64_NONAME_F_SW_I2C u8g2(U8G2_R0, 22, 21, U8X8_PIN_NONE); 
WiFiUDP Udp; // 声明UDP对象

void Buzzer_Init(void)//蜂鸣器初始化
{
   pinMode(33,OUTPUT);
}

void LED_Init(void)//LED初始化
{
   pinMode(2,OUTPUT);
}

void Button_Init(void)
{
  pinMode(2,OUTPUT);
  pinMode(18,OUTPUT);
  pinMode(12,OUTPUT);
  digitalWrite(18,HIGH);
  digitalWrite(12,HIGH);
  pinMode(18,INPUT);
}


void OLED_Init(U8G2_SSD1306_128X64_NONAME_F_SW_I2C *u8g2)
{
  pinMode(21,OUTPUT);//SDA
  pinMode(22,OUTPUT);//SCL

  u8g2->begin();
} 


void UART_Init(void)
{
  Serial.begin(115200);//这个是esp32与电脑的串口波特率
}


void PWM_Init(void)
{
  ledcSetup(2, 10000, 12);//初始化PWM外设，参数：通道(第二通道)，频率(10000HZ)，位数(12位计量,范围0-4095)
  ledcAttachPin(2, 2);//将 第二通道 绑定到指定 IO 口（GPIO2）上以实现输出
}


void Motor_Init(void)
{
  ledcSetup(0, 10000, 12);//初始化PWM外设，使用通道1，0，10000HZ，12位
  ledcSetup(1, 10000, 12);
  
  ledcSetup(2, 10000, 12);//初始化PWM外设，使用通道2，3，10000HZ，12位
  ledcSetup(3, 10000, 12);

  ledcSetup(4, 10000, 12);//初始化PWM外设，使用通道4，5，10000HZ，12位
  ledcSetup(5, 10000, 12);

  ledcSetup(6, 10000, 12);//初始化PWM外设，使用通道6，7，10000HZ，12位
  ledcSetup(7, 10000, 12);

  ledcAttachPin(14, 0);//将通道0绑定到GPIO14上，也就是左前轮电机通道A输入对应的GPIO
  ledcAttachPin(13, 1);//将通道1绑定到GPIO13上，也就是左前轮电机通道B输入对应的GPIO

  ledcAttachPin(16, 2);//将通道2绑定到GPIO16上，也就是右后轮电机通道A输入对应的GPIO
  ledcAttachPin(17, 3);//将通道3绑定到GPIO17上，也就是右后轮电机通道B输入对应的GPIO

  ledcAttachPin(26, 4);//将通道2绑定到GPIO26上，也就是左后轮电机通道A输入对应的GPIO
  ledcAttachPin(27, 5);//将通道3绑定到GPIO27上，也就是左后轮电机通道B输入对应的GPIO

  ledcAttachPin(15, 6);//将通道6绑定到GPIO15上，也就是右前轮电机通道A输入对应的GPIO
  ledcAttachPin(4, 7);//将通道7绑定到GPIO4上，也就是右后前电机通道B输入对应的GPIO
}



void UDP_Init(void)
{
  const char *wifi_SSID = "0XFF";        // 存储所连接的WIFI的名字
  const char *wifi_Password = "XPHxph3505"; // 存储所连接的WIFI的密码

  uint16_t udp_port = 1122; // 存储需要监听的端口号

  Serial.begin(115200); // 开启串口，波特率为115200
  WiFi.begin(wifi_SSID, wifi_Password);
  while (WiFi.status() != WL_CONNECTED)
  { // 未连接上
    delay(500);
    Serial.println("conecting...");
  }
  Serial.println("conected"); //连接成功

  Serial.print("IP: ");
  Serial.println(WiFi.localIP()); // 串口输出模块IP地址

  Udp.begin(udp_port); // 启动UDP监听这个端口
}

void ADC_Init(void)
 {
  pinMode(32,OUTPUT);
  pinMode(35,OUTPUT);
  pinMode(34,OUTPUT);
  pinMode(39,OUTPUT);
  pinMode(36,OUTPUT);

  Serial.begin(115200);
}

//蓝牙功能的中断回调函数
class MyCallbacks: public BLECharacteristicCallbacks 
{
  
    void onWrite(BLECharacteristic *pCharacteristic) 
    {      //写方法
      std::string value = pCharacteristic->getValue();      //接收值
      if (value.length() > 0) 
      {
        Serial.printf("收到新信息: ");
        for (int i = 0; i < value.length(); i++)       //遍历输出字符串
          Serial.printf("%c",value[i]);
          Serial.print("\n");
      }
    }
};


void BLE_Init(void)
{
  Serial.begin(115200);
  delay(1000);
  BLEDevice::init("MyESP32");                      //设备初始化，名称MyESP32
  
  BLEServer *pServer = BLEDevice::createServer();            //BLEServer指针，创建Server

  BLEService *pService = pServer->createService(SERVICE_UUID);     //BLEService指针，创建Service

  BLECharacteristic *pCharacteristic = pService->createCharacteristic(     //BLECharacteristic指针，创建Characteristic
                                         CHARACTERISTIC_UUID,
                                         BLECharacteristic::PROPERTY_READ |
                                         BLECharacteristic::PROPERTY_WRITE
                                       );

  pCharacteristic->setCallbacks(new MyCallbacks());            //设置回调函数

  pCharacteristic->setValue("Hello World");    //发送信息，hello world
  pService->start();                      //开启服务

  BLEAdvertising *pAdvertising = pServer->getAdvertising();        //初始化广播
  pAdvertising->start();                    //开始广播
}

void UDP_Test(void)
{
  char incomingPacket[255];            // 存储UDP客户端发过来的数据
  /*接收发送过来的Udp数据*/
  int Data_length = Udp.parsePacket(); //读取接的UDP包的长度
  if (Data_length) // 如果有数据那么Data_length不为0，无数据Data_length为0
  {
    int len = Udp.read(incomingPacket, 255); // 读取数据，将数据保存在数组incomingPacket中
    if (len > 0)                             // 为了避免获取的数据后面乱码做的判断
    {
      incomingPacket[len] = 0;
    }

    /*将接受到的数据发送回去*/
    Udp.beginPacket(Udp.remoteIP(), Udp.remotePort()); // 准备发送数据到目标IP和目标端口
    Udp.print("receive data:");                        // 将数据receive data:放入发送的缓冲区
    Udp.println(incomingPacket);                                // 将接收到的数据放入发送的缓冲区
    for(int i = 0 ; i<Data_length;i++)
    {
      Serial.printf("receive data:%c\n",incomingPacket[i]);//串口打印接收的数据
    }
    Udp.endPacket(); // 向目标IP目标端口发送数据
  }
  delay(1);
}