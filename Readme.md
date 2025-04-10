ESP32 Xbox 手柄小车项目
#项目简介
----
本项目利用 ESP32 开发板和 Xbox Series X 手柄，通过 BLE（蓝牙低功耗）通信实现对小车的远程控制。项目主要功能包括：
- 使用 BLE 技术接收 Xbox 手柄信号（摇杆、触发器、按键）；
- 对手柄输入进行死区处理与缩放，保证输入的准确性；
- 通过 LEDC 模块生成 PWM 信号，实现电机控制、差速转向及各种驾驶模式（前进、后退、转向、手刹）；
- 采用差速转向算法，实现车辆平稳转弯及原地调向。
- 该项目既适用于娱乐控制，又可以作为智能机器人、自动驾驶基础平台的原型验证。

硬件要求:
ESP32 开发板，电机及驱动模块，电源模块，Xbox Series X 手柄(支持BLE连接)
软件要求
PlatformIO
推荐使用 PlatformIO 开发环境，方便管理依赖和编译设置
Arduino 框架（ESP32 Arduino Core）

依赖库：

	NimBLE-Arduino
	XboxSeriesXControllerESP32_asukiaaa


在 platformio.ini 中示例配置如下：
	
	[env:esp-wrover-kit]
	platform = espressif32
	board = esp-wrover-kit
	framework = arduino
	lib_deps =
    NimBLE-Arduino
    asukiaaa/XboxSeriesXControllerESP32
    olikraus/U8g2@^2.35.19
	build_flags = -Iinclude
	lib_extra_dirs = lib
	monitor_speed = 115200


未来改进
算法优化：
加入 PID 控制或其他闭环控制算法，以获得更平稳的车辆运动。

界面优化：
增加显示模块或手机 APP，用于实时监控和调整车辆状态。

功能扩展：
增加传感器输入（如陀螺仪、距离传感器），实现自动避障及路径规划等功能。
