# 这是一个用于在windows系统上控制时序电源 iBanana SR-828 的上位机程序。  

开发环境： Qt 5.15.2 + Qt Creator 12.0.0 + MinGW 8.1.0 64-bit + qmake  

**iBanana SR-828** 好像没有读取当前状态的命令？但会把成功收到并执行的每条命令通过串口反馈回来（复读一遍）？？但但但是为什么单通道控制模式命令接收后，开启和关闭都回复同样的命令？？？  

欢迎对这款电源有了解的友友前来交流😀  

（SmartPowerController是工程文件夹；iBanana SR-828 Controller V1.0是打包发布的程序文件夹，双击exe即可运行）
