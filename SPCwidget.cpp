#include "SPCwidget.h"
#include "ui_SPCwidget.h"
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QDebug>
#include <QMessageBox>
#include "serialport_listener.h"

//---------------通信帧的关键字------------------
#define FRAMES_HEADER   "48"  //帧头
#define FRAMES_TAIL     "4d"    //帧尾
#define FACILITY_TYPE   "1a"  //设备类型
#define FACILITY_ID     "00"    //设备ID
#define STANDBY_OR_NOT  "01" //待机与否
#define PATTERN_CALL    "02"   //模式调用
#define PATTERN_SAVE    "03"   //模式保存
#define RELAY_ALL       "04"      //所有继电器全开/全关
#define RELAY_SINGAL    "05"   //单个继电器 开/关
#define BAUDRATE_SET    "06"   //波特率设置
#define LOCAL_ID        "07"       //本机ID设置
#define CASCADE_SWITCH  "08" //级联开关
#define INITIAL         "09"        //初始化
#define ON              "01"             //开
#define OFF             "00"            //关
#define BLANK           "00"          //0x00

#define RELAY_1 "00"        //继电器1~8
#define RELAY_2 "01"
#define RELAY_3 "02"
#define RELAY_4 "03"
#define RELAY_5 "04"
#define RELAY_6 "05"
#define RELAY_7 "06"
#define RELAY_8 "07"

#define GREEN 80,245,80
#define GRAY 240,240,240

#define SLEEP_DURATION 400

// #define RELAY_INDEX(value) \
//    ((value == 1) ? 0x00 : \
//     (value == 2) ? 0x01 : \
//     (value == 3) ? 0x02 : \
//     (value == 4) ? 0x03 : \
//     (value == 5) ? 0x04 : \
//     (value == 6) ? 0x05 : \
//     (value == 7) ? 0x06 : \
//     (value == 8) ? 0x07 : \
//     /*默认值*/      0xff)  //继电器1~8
// //控制命令
// #define OPEN_ALL_RELAY FRAMES_HEADER,FACILITY_TYPE,FACILITY_ID,RELAY_ALL,ON,BLANK,BLANK,FRAMES_TAIL
// #define CLOSE_ALL_RELAY FRAMES_HEADER,FACILITY_TYPE,FACILITY_ID,RELAY_ALL,OFF,BLANK,BLANK,FRAMES_TAIL
// #define OPEN_RELAY_1 FRAMES_HEADER,FACILITY_TYPE,FACILITY_ID,RELAY_SINGAL,RELAY_INDEX(1),ON,BLANK,FRAMES_TAIL

//---------------------------------------------

SerialPort_Listener *mySerialPort_Listener = Q_NULLPTR;


Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    //add begin


    connect(&mySerialPort, &QIODevice::readyRead, this, &Widget::do_com_readyRead);//连接串口的readRead信号和对应槽函数

    //初始化界面，除了串口选择，其他部分先禁用
    ui->btn_PowerDisconnect->setEnabled(false);
    ui->widget_2->setEnabled(false);
    ui->widget_3->setEnabled(false);

    //初始化通道串口
    ui->label_1->setStyleSheet("QLabel{border:1px solid #888888;}");
    ui->label_2->setStyleSheet("QLabel{border:1px solid #888888;}");
    ui->label_3->setStyleSheet("QLabel{border:1px solid #888888;}");
    ui->label_4->setStyleSheet("QLabel{border:1px solid #888888;}");
    ui->label_5->setStyleSheet("QLabel{border:1px solid #888888;}");
    ui->label_6->setStyleSheet("QLabel{border:1px solid #888888;}");
    ui->label_7->setStyleSheet("QLabel{border:1px solid #888888;}");
    ui->label_8->setStyleSheet("QLabel{border:1px solid #888888;}");

    // //初始化待机按钮
    // ui->btn_standby->setIcon(QIcon(":/ResourceFiles/switch_on.ico")); // 初始状态为开
    // ui->btn_standby->setIconSize(QSize(50, 50));// 设置图标大小
    // ui->btn_standby->setFixedSize(50,50);     // 设置按钮大小
    // ui->btn_standby->setStyleSheet("border:none;background-color: rgb(240, 240, 240);");


    //扫描计算机上的可用串口
    for (const QSerialPortInfo &info : QSerialPortInfo::availablePorts())
    {
        QSerialPort serial;
        serial.setPort(info);
        if (serial.open(QIODevice::ReadWrite))
        {
            ui->comboBox_powerLink->addItem(serial.portName());
            serial.close();
        }
    }
    //（通过检测WM_DEVICECHANGE信号实现USB热插拔，实时更新可用的COM口）
    mySerialPort_Listener = new SerialPort_Listener;
    qApp->installNativeEventFilter(mySerialPort_Listener);
    //串口新增信号连接到槽
    connect(mySerialPort_Listener, &SerialPort_Listener::DevicePlugIn, [=](){
        //先清除之前的所有项
        ui->comboBox_powerLink->clear();
        //扫描可用串口，并添加
        for (const QSerialPortInfo &info : QSerialPortInfo::availablePorts())
        {
            QSerialPort serial;
            serial.setPort(info);
            if (serial.open(QIODevice::ReadWrite))
            {
                ui->comboBox_powerLink->addItem(serial.portName());
                serial.close();
            }
        }
        qDebug() << "串口增加1个";
    });
    //串口减少信号连接到槽
    connect(mySerialPort_Listener, &SerialPort_Listener::DevicePlugOut, [=](){
        //先清除之前的所有项
        ui->comboBox_powerLink->clear();
        //扫描可用串口，并添加
        for (const QSerialPortInfo &info : QSerialPortInfo::availablePorts())
        {
            QSerialPort serial;
            serial.setPort(info);
            if (serial.open(QIODevice::ReadWrite))
            {
                ui->comboBox_powerLink->addItem(serial.portName());
                serial.close();
            }
        }
        qDebug() << "串口减少1个";
    });


    //add end
}

Widget::~Widget()
{
    delete ui;
}

//连接电源串口
void Widget::on_btn_PowerConnect_clicked()
{
    if(mySerialPort.isOpen())
    {
        QMessageBox::warning(this, "错误","此串口已被占用，无法连接！");
        return;
    }
    QList<QSerialPortInfo> comList = QSerialPortInfo::availablePorts();
    QSerialPortInfo portInfo = comList.at(ui->comboBox_powerLink->currentIndex());/////////////////////////////////////改成 用串口名，避免串口编号不连续时索引
    mySerialPort.setPort(portInfo); //设置使用当前下拉栏选中的串口
    mySerialPort.setBaudRate(QSerialPort::Baud57600); //波特率
    mySerialPort.setDataBits(QSerialPort::Data8);      //数据位8位
    mySerialPort.setStopBits(QSerialPort::OneStop);    //停止位1位
    mySerialPort.setParity(QSerialPort::NoParity);     //无奇偶校验
    if(mySerialPort.open(QIODevice::ReadWrite))
    {
        ui->btn_PowerConnect->setEnabled(false);
        ui->comboBox_powerLink->setEnabled(false);
        ui->btn_PowerDisconnect->setEnabled(true);
        ui->widget_2->setEnabled(true);
        ui->widget_3->setEnabled(true);
        ui->btn_off_all->setEnabled(false);

        //禁用8个“关”按钮
        ui->btn_off_1->setEnabled(false);
        ui->btn_off_2->setEnabled(false);
        ui->btn_off_3->setEnabled(false);
        ui->btn_off_4->setEnabled(false);
        ui->btn_off_5->setEnabled(false);
        ui->btn_off_6->setEnabled(false);
        ui->btn_off_7->setEnabled(false);
        ui->btn_off_8->setEnabled(false);
        //8个通道窗口变黑框
        ui->label_1->setStyleSheet("QLabel{border:1px solid #000000;}");
        ui->label_2->setStyleSheet("QLabel{border:1px solid #000000;}");
        ui->label_3->setStyleSheet("QLabel{border:1px solid #000000;}");
        ui->label_4->setStyleSheet("QLabel{border:1px solid #000000;}");
        ui->label_5->setStyleSheet("QLabel{border:1px solid #000000;}");
        ui->label_6->setStyleSheet("QLabel{border:1px solid #000000;}");
        ui->label_7->setStyleSheet("QLabel{border:1px solid #000000;}");
        ui->label_8->setStyleSheet("QLabel{border:1px solid #000000;}");

        //连接上以后，先关闭所有通道
        QByteArray frames = QByteArray::fromHex( FRAMES_HEADER FACILITY_TYPE FACILITY_ID RELAY_ALL OFF BLANK BLANK FRAMES_TAIL );
        mySerialPort.write(frames);  // "481A00040000004D" 帧类型04, 8通道继电器全关
        mySerialPort.waitForBytesWritten(); //等待写入信号，否则阻塞
        qDebug()<<"串口发送数据帧：继电器全关 "<<frames;
        Sleep(SLEEP_DURATION); //必须睡眠至少20ms，后一句指令才能被写入并执行
        relay_1_Open = false;
        relay_2_Open = false;
        relay_3_Open = false;
        relay_4_Open = false;
        relay_5_Open = false;
        relay_6_Open = false;
        relay_7_Open = false;
        relay_8_Open = false;
    }
}

//断开电源串口
void Widget::on_btn_PowerDisconnect_clicked()
{
    if(mySerialPort.isOpen())
    {
        mySerialPort.close();
        ui->btn_PowerConnect->setEnabled(true);
        ui->comboBox_powerLink->setEnabled(true);
        ui->btn_PowerDisconnect->setEnabled(false);
        ui->widget_2->setEnabled(false);
        ui->widget_3->setEnabled(false);
        //8个通道窗口框变灰
        ui->label_1->setStyleSheet("QLabel{border:2px solid #888888;}");
        ui->label_2->setStyleSheet("QLabel{border:2px solid #888888;}");
        ui->label_3->setStyleSheet("QLabel{border:2px solid #888888;}");
        ui->label_4->setStyleSheet("QLabel{border:2px solid #888888;}");
        ui->label_5->setStyleSheet("QLabel{border:2px solid #888888;}");
        ui->label_6->setStyleSheet("QLabel{border:2px solid #888888;}");
        ui->label_7->setStyleSheet("QLabel{border:2px solid #888888;}");
        ui->label_8->setStyleSheet("QLabel{border:2px solid #888888;}");
    }
    else
    {
        QMessageBox::warning(this, "提示", "此串口已关闭，请勿重复操作！");
    }
}


//发送继电器全开指令
void Widget::on_btn_on_all_clicked()
{
    QByteArray frames = QByteArray::fromHex( FRAMES_HEADER FACILITY_TYPE FACILITY_ID RELAY_ALL ON BLANK BLANK FRAMES_TAIL );
    mySerialPort.write(frames);
    mySerialPort.waitForBytesWritten();
    qDebug()<<"串口发送数据帧：继电器全开 "<<frames;
    Sleep(SLEEP_DURATION);
    relay_1_Open = true;
    relay_2_Open = true;
    relay_3_Open = true;
    relay_4_Open = true;
    relay_5_Open = true;
    relay_6_Open = true;
    relay_7_Open = true;
    relay_8_Open = true;
}

//发送继电器全关指令
void Widget::on_btn_off_all_clicked()
{
    QByteArray frames = QByteArray::fromHex( FRAMES_HEADER FACILITY_TYPE FACILITY_ID RELAY_ALL OFF BLANK BLANK FRAMES_TAIL );
    mySerialPort.write(frames);  // "481A00040000004D" 帧类型04, 8通道继电器全关
    mySerialPort.waitForBytesWritten(); //等待写入信号，否则阻塞
    qDebug()<<"串口发送数据帧：继电器全关 "<<frames;
    Sleep(SLEEP_DURATION); //必须睡眠至少20ms，后一句指令才能被写入并执行
    relay_1_Open = false;
    relay_2_Open = false;
    relay_3_Open = false;
    relay_4_Open = false;
    relay_5_Open = false;
    relay_6_Open = false;
    relay_7_Open = false;
    relay_8_Open = false;
}


//通道1，开
void Widget::on_btn_on_1_clicked()
{
    QByteArray frames = QByteArray::fromHex( FRAMES_HEADER FACILITY_TYPE FACILITY_ID RELAY_SINGAL RELAY_1 ON BLANK FRAMES_TAIL );
    mySerialPort.write(frames);
    mySerialPort.waitForBytesWritten();
    Sleep(SLEEP_DURATION);
    relay_1_Open = true;
    qDebug()<<"串口发送数据帧：通道1，开 "<<frames;
}


void Widget::on_btn_on_2_clicked()
{
    QByteArray frames = QByteArray::fromHex( FRAMES_HEADER FACILITY_TYPE FACILITY_ID RELAY_SINGAL RELAY_2 ON BLANK FRAMES_TAIL );
    mySerialPort.write(frames);
    mySerialPort.waitForBytesWritten();
    Sleep(SLEEP_DURATION);
    relay_2_Open = true;
    qDebug()<<"串口发送数据帧：通道2，开 "<<frames;
}


void Widget::on_btn_on_3_clicked()
{
    QByteArray frames = QByteArray::fromHex( FRAMES_HEADER FACILITY_TYPE FACILITY_ID RELAY_SINGAL RELAY_3 ON BLANK FRAMES_TAIL );
    mySerialPort.write(frames);
    mySerialPort.waitForBytesWritten();
    Sleep(SLEEP_DURATION);
    relay_3_Open = true;
    qDebug()<<"串口发送数据帧：通道3，开 "<<frames;
}


void Widget::on_btn_on_4_clicked()
{
    QByteArray frames = QByteArray::fromHex( FRAMES_HEADER FACILITY_TYPE FACILITY_ID RELAY_SINGAL RELAY_4 ON BLANK FRAMES_TAIL );
    mySerialPort.write(frames);
    mySerialPort.waitForBytesWritten();
    Sleep(SLEEP_DURATION);
    relay_4_Open = true;
    qDebug()<<"串口发送数据帧：通道4，开 "<<frames;
}


void Widget::on_btn_on_5_clicked()
{
    QByteArray frames = QByteArray::fromHex( FRAMES_HEADER FACILITY_TYPE FACILITY_ID RELAY_SINGAL RELAY_5 ON BLANK FRAMES_TAIL );
    mySerialPort.write(frames);
    mySerialPort.waitForBytesWritten();
    Sleep(SLEEP_DURATION);
    relay_5_Open = true;
    qDebug()<<"串口发送数据帧：通道5，开 "<<frames;
}


void Widget::on_btn_on_6_clicked()
{
    QByteArray frames = QByteArray::fromHex( FRAMES_HEADER FACILITY_TYPE FACILITY_ID RELAY_SINGAL RELAY_6 ON BLANK FRAMES_TAIL );
    mySerialPort.write(frames);
    mySerialPort.waitForBytesWritten();
    Sleep(SLEEP_DURATION);
    relay_6_Open = true;
    qDebug()<<"串口发送数据帧：通道6，开 "<<frames;
}


void Widget::on_btn_on_7_clicked()
{
    QByteArray frames = QByteArray::fromHex( FRAMES_HEADER FACILITY_TYPE FACILITY_ID RELAY_SINGAL RELAY_7 ON BLANK FRAMES_TAIL );
    mySerialPort.write(frames);
    mySerialPort.waitForBytesWritten();
    Sleep(SLEEP_DURATION);
    relay_7_Open = true;
    qDebug()<<"串口发送数据帧：通道7，开 "<<frames;
}


void Widget::on_btn_on_8_clicked()
{
    QByteArray frames = QByteArray::fromHex( FRAMES_HEADER FACILITY_TYPE FACILITY_ID RELAY_SINGAL RELAY_8 ON BLANK FRAMES_TAIL );
    mySerialPort.write(frames);
    mySerialPort.waitForBytesWritten();
    Sleep(SLEEP_DURATION);
    relay_8_Open = true;
    qDebug()<<"串口发送数据帧：通道8，开 "<<frames;
}

//通道1，关
void Widget::on_btn_off_1_clicked()
{
    QByteArray frames = QByteArray::fromHex( FRAMES_HEADER FACILITY_TYPE FACILITY_ID RELAY_SINGAL RELAY_1 OFF BLANK FRAMES_TAIL );
    mySerialPort.write(frames);
    mySerialPort.waitForBytesWritten();
    Sleep(SLEEP_DURATION);
    relay_1_Open = false;
    qDebug()<<"串口发送数据帧：通道1，关 "<<frames;
}
void Widget::on_btn_off_2_clicked()
{
    QByteArray frames = QByteArray::fromHex( FRAMES_HEADER FACILITY_TYPE FACILITY_ID RELAY_SINGAL RELAY_2 OFF BLANK FRAMES_TAIL );
    mySerialPort.write(frames);
    mySerialPort.waitForBytesWritten();
    Sleep(SLEEP_DURATION);
    relay_2_Open = false;
    qDebug()<<"串口发送数据帧：通道2，关 "<<frames;
}


void Widget::on_btn_off_3_clicked()
{
    QByteArray frames = QByteArray::fromHex( FRAMES_HEADER FACILITY_TYPE FACILITY_ID RELAY_SINGAL RELAY_3 OFF BLANK FRAMES_TAIL );
    mySerialPort.write(frames);
    mySerialPort.waitForBytesWritten();
    Sleep(SLEEP_DURATION);
    relay_3_Open = false;
    qDebug()<<"串口发送数据帧：通道3，关 "<<frames;
}


void Widget::on_btn_off_4_clicked()
{
    QByteArray frames = QByteArray::fromHex( FRAMES_HEADER FACILITY_TYPE FACILITY_ID RELAY_SINGAL RELAY_4 OFF BLANK FRAMES_TAIL );
    mySerialPort.write(frames);
    mySerialPort.waitForBytesWritten();
    Sleep(SLEEP_DURATION);
    relay_4_Open = false;
    qDebug()<<"串口发送数据帧：通道4，关 "<<frames;
}


void Widget::on_btn_off_5_clicked()
{
    QByteArray frames = QByteArray::fromHex( FRAMES_HEADER FACILITY_TYPE FACILITY_ID RELAY_SINGAL RELAY_5 OFF BLANK FRAMES_TAIL );
    mySerialPort.write(frames);
    mySerialPort.waitForBytesWritten();
    Sleep(SLEEP_DURATION);
    relay_5_Open = false;
    qDebug()<<"串口发送数据帧：通道5，关 "<<frames;
}


void Widget::on_btn_off_6_clicked()
{
    QByteArray frames = QByteArray::fromHex( FRAMES_HEADER FACILITY_TYPE FACILITY_ID RELAY_SINGAL RELAY_6 OFF BLANK FRAMES_TAIL );
    mySerialPort.write(frames);
    mySerialPort.waitForBytesWritten();
    Sleep(SLEEP_DURATION);
    relay_6_Open = false;
    qDebug()<<"串口发送数据帧：通道6，关 "<<frames;
}


void Widget::on_btn_off_7_clicked()
{
    QByteArray frames = QByteArray::fromHex( FRAMES_HEADER FACILITY_TYPE FACILITY_ID RELAY_SINGAL RELAY_7 OFF BLANK FRAMES_TAIL );
    mySerialPort.write(frames);
    mySerialPort.waitForBytesWritten();
    Sleep(SLEEP_DURATION);
    relay_7_Open = false;
    qDebug()<<"串口发送数据帧：通道7，关 "<<frames;
}


void Widget::on_btn_off_8_clicked()
{
    QByteArray frames = QByteArray::fromHex( FRAMES_HEADER FACILITY_TYPE FACILITY_ID RELAY_SINGAL RELAY_8 OFF BLANK FRAMES_TAIL );
    mySerialPort.write(frames);
    mySerialPort.waitForBytesWritten();
    Sleep(SLEEP_DURATION);
    relay_8_Open = false;
    qDebug()<<"串口发送数据帧：通道8，关 "<<frames;
}

//如果串口收到反馈，就改变窗口颜色
//ui->label_1->setStyleSheet("QLabel{background-color:rgb(50,255,0);}");
//3.30安排
//1.串口接收信号的槽函数，连接，根据收到反馈 开/关 通道灯
//2.从全开/全关 到 单个通道

//根据串口接收到的数据，作出反应 槽函数
void Widget::do_com_readyRead()
{
    QByteArray alldata = mySerialPort.readAll();
    qDebug()<<"电源串口收到：alldata= "<< alldata;

    // 检查 alldata 中的特定字节来确定串口数据的内容
    const char* dataPtr = alldata.constData();

    if(alldata.size() == 8 && dataPtr[0] == 'H' && dataPtr[1] == '\x1A' && dataPtr[2] == '\x00' && dataPtr[7] == 'M')
    {
        //待机功能存在缺陷，暂时去除，不影响使用
        // if(dataPtr[3] == '\x01')  //帧类型01：待机与否
        // {
        //     switch (dataPtr[4]) {
        //     case '\x00':
        //         standbyOrNot = true;
        //         ui->btn_standby->setIcon(QIcon(":/ResourceFiles/switch_off.ico"));
        //         ui->btn_standby->setIconSize(QSize(50, 50));// 设置图标大小
        //         ui->btn_standby->setFixedSize(50,50);     // 设置按钮大小
        //         ui->btn_standby->setStyleSheet("border:none;background-color: rgb(240, 240, 240);");

        //         break;
        //     case '\x01':
        //         standbyOrNot = false;
        //         ui->btn_standby->setIcon(QIcon(":/ResourceFiles/switch_on.ico"));
        //         ui->btn_standby->setIconSize(QSize(50, 50));// 设置图标大小
        //         ui->btn_standby->setFixedSize(50,50);     // 设置按钮大小
        //         ui->btn_standby->setStyleSheet("border:none;background-color: rgb(240, 240, 240);");
        //         break;
        //     default:
        //         QMessageBox::warning(this, "错误","返回的数据帧01后格式错误！");
        //         break;
        //     }
        // }
        if(dataPtr[3] == '\x04' ) //帧类型04：继电器全开/全关
        {
            switch (dataPtr[4]) {
            case '\x00':
                ui->label_1->setStyleSheet("QLabel{border:1px solid #000000;background-color:rgb(240,240,240);}");
                ui->label_2->setStyleSheet("QLabel{border:1px solid #000000;background-color:rgb(240,240,240);}");
                ui->label_3->setStyleSheet("QLabel{border:1px solid #000000;background-color:rgb(240,240,240);}");
                ui->label_4->setStyleSheet("QLabel{border:1px solid #000000;background-color:rgb(240,240,240);}");
                ui->label_5->setStyleSheet("QLabel{border:1px solid #000000;background-color:rgb(240,240,240);}");
                ui->label_6->setStyleSheet("QLabel{border:1px solid #000000;background-color:rgb(240,240,240);}");
                ui->label_7->setStyleSheet("QLabel{border:1px solid #000000;background-color:rgb(240,240,240);}");
                ui->label_8->setStyleSheet("QLabel{border:1px solid #000000;background-color:rgb(240,240,240);}");
                ui->btn_off_all->setEnabled(false);
                ui->btn_on_all->setEnabled(true);
                ui->btn_off_1->setEnabled(false);
                ui->btn_off_2->setEnabled(false);
                ui->btn_off_3->setEnabled(false);
                ui->btn_off_4->setEnabled(false);
                ui->btn_off_5->setEnabled(false);
                ui->btn_off_6->setEnabled(false);
                ui->btn_off_7->setEnabled(false);
                ui->btn_off_8->setEnabled(false);
                ui->btn_on_1->setEnabled(true);
                ui->btn_on_2->setEnabled(true);
                ui->btn_on_3->setEnabled(true);
                ui->btn_on_4->setEnabled(true);
                ui->btn_on_5->setEnabled(true);
                ui->btn_on_6->setEnabled(true);
                ui->btn_on_7->setEnabled(true);
                ui->btn_on_8->setEnabled(true);
                break;
            case '\x01':
                ui->label_1->setStyleSheet("QLabel{border:1px solid #000000;background-color:rgb(80,245,80);}");
                ui->label_2->setStyleSheet("QLabel{border:1px solid #000000;background-color:rgb(80,245,80);}");
                ui->label_3->setStyleSheet("QLabel{border:1px solid #000000;background-color:rgb(80,245,80);}");
                ui->label_4->setStyleSheet("QLabel{border:1px solid #000000;background-color:rgb(80,245,80);}");
                ui->label_5->setStyleSheet("QLabel{border:1px solid #000000;background-color:rgb(80,245,80);}");
                ui->label_6->setStyleSheet("QLabel{border:1px solid #000000;background-color:rgb(80,245,80);}");
                ui->label_7->setStyleSheet("QLabel{border:1px solid #000000;background-color:rgb(80,245,80);}");
                ui->label_8->setStyleSheet("QLabel{border:1px solid #000000;background-color:rgb(80,245,80);}");
                ui->btn_off_all->setEnabled(true);
                ui->btn_on_all->setEnabled(false);
                ui->btn_off_1->setEnabled(true);
                ui->btn_off_2->setEnabled(true);
                ui->btn_off_3->setEnabled(true);
                ui->btn_off_4->setEnabled(true);
                ui->btn_off_5->setEnabled(true);
                ui->btn_off_6->setEnabled(true);
                ui->btn_off_7->setEnabled(true);
                ui->btn_off_8->setEnabled(true);
                ui->btn_on_1->setEnabled(false);
                ui->btn_on_2->setEnabled(false);
                ui->btn_on_3->setEnabled(false);
                ui->btn_on_4->setEnabled(false);
                ui->btn_on_5->setEnabled(false);
                ui->btn_on_6->setEnabled(false);
                ui->btn_on_7->setEnabled(false);
                ui->btn_on_8->setEnabled(false);
                break;
            default:
                QMessageBox::warning(this, "错误","返回的数据帧04后格式错误！");
                break;
            }
        }
        if(dataPtr[3] == '\x05'  ) //帧类型05：单个继电器开/关
        {
            switch (dataPtr[4]) {
            case '\x00':
                if(relay_1_Open==false)
                    ui->label_1->setStyleSheet("QLabel{border:1px solid #000000;background-color:rgb(240,240,240);}") , ui->btn_off_1->setEnabled(false), ui->btn_on_1->setEnabled(true);
                else
                    ui->label_1->setStyleSheet("QLabel{border:1px solid #000000;background-color:rgb(80,245,80);}"), ui->btn_off_1->setEnabled(true), ui->btn_on_1->setEnabled(false);
                break;
            case '\x01':
                if(relay_2_Open==false)
                    ui->label_2->setStyleSheet("QLabel{border:1px solid #000000;background-color:rgb(240,240,240);}"), ui->btn_off_2->setEnabled(false), ui->btn_on_2->setEnabled(true);
                else
                    ui->label_2->setStyleSheet("QLabel{border:1px solid #000000;background-color:rgb(80,245,80);}"), ui->btn_off_2->setEnabled(true), ui->btn_on_2->setEnabled(false);
                break;
            case '\x02':
                if(relay_3_Open==false)
                    ui->label_3->setStyleSheet("QLabel{border:1px solid #000000;background-color:rgb(240,240,240);}"), ui->btn_off_3->setEnabled(false), ui->btn_on_3->setEnabled(true);
                else
                    ui->label_3->setStyleSheet("QLabel{border:1px solid #000000;background-color:rgb(80,245,80);}"), ui->btn_off_3->setEnabled(true), ui->btn_on_3->setEnabled(false);
                break;
            case '\x03':
                if(relay_4_Open==false)
                    ui->label_4->setStyleSheet("QLabel{border:1px solid #000000;background-color:rgb(240,240,240);}"), ui->btn_off_4->setEnabled(false), ui->btn_on_4->setEnabled(true);
                else
                    ui->label_4->setStyleSheet("QLabel{border:1px solid #000000;background-color:rgb(80,245,80);}"), ui->btn_off_4->setEnabled(true), ui->btn_on_4->setEnabled(false);
                break;
            case '\x04':
                if(relay_5_Open==false)
                    ui->label_5->setStyleSheet("QLabel{border:1px solid #000000;background-color:rgb(240,240,240);}"), ui->btn_off_5->setEnabled(false), ui->btn_on_5->setEnabled(true);
                else
                    ui->label_5->setStyleSheet("QLabel{border:1px solid #000000;background-color:rgb(80,245,80);}"), ui->btn_off_5->setEnabled(true), ui->btn_on_5->setEnabled(false);
                break;
            case '\x05':
                if(relay_6_Open==false)
                    ui->label_6->setStyleSheet("QLabel{border:1px solid #000000;background-color:rgb(240,240,240);}"), ui->btn_off_6->setEnabled(false), ui->btn_on_6->setEnabled(true);
                else
                    ui->label_6->setStyleSheet("QLabel{border:1px solid #000000;background-color:rgb(80,245,80);}"), ui->btn_off_6->setEnabled(true), ui->btn_on_6->setEnabled(false);
                break;
            case '\x06':
                if(relay_7_Open==false)
                    ui->label_7->setStyleSheet("QLabel{border:1px solid #000000;background-color:rgb(240,240,240);}"), ui->btn_off_7->setEnabled(false), ui->btn_on_7->setEnabled(true);
                else
                    ui->label_7->setStyleSheet("QLabel{border:1px solid #000000;background-color:rgb(80,245,80);}"), ui->btn_off_7->setEnabled(true), ui->btn_on_7->setEnabled(false);
                break;
            case '\x07':
                if(relay_8_Open==false)
                    ui->label_8->setStyleSheet("QLabel{border:1px solid #000000;background-color:rgb(240,240,240);}"), ui->btn_off_8->setEnabled(false), ui->btn_on_8->setEnabled(true);
                else
                    ui->label_8->setStyleSheet("QLabel{border:1px solid #000000;background-color:rgb(80,245,80);}"), ui->btn_off_8->setEnabled(true), ui->btn_on_8->setEnabled(false);
                break;
            default:
                QMessageBox::warning(this, "错误","返回的数据帧05后格式错误！");
                break;
            }
        }
    }
    else
    {
        //QMessageBox::warning(this, "错误", "返回的数据帧长度或格式错误！");  //有时会连续弹出多个提示框，省去
    }

}


//发送待机/工作 信号
// void Widget::on_btn_standby_clicked()
// {
//     if(!standbyOrNot) //如果当前为开机状态
//     {
//         QByteArray frames = QByteArray::fromHex( FRAMES_HEADER FACILITY_TYPE FACILITY_ID STANDBY_OR_NOT OFF BLANK BLANK FRAMES_TAIL );
//         mySerialPort.write(frames);
//         mySerialPort.waitForBytesWritten();
//         Sleep(50);
//         qDebug()<<"串口发送数据帧：待机 "<<frames;
//     }
//     else //当前为待机状态
//     {
//         QByteArray frames = QByteArray::fromHex( FRAMES_HEADER FACILITY_TYPE FACILITY_ID STANDBY_OR_NOT ON BLANK BLANK FRAMES_TAIL );
//         mySerialPort.write(frames);
//         mySerialPort.waitForBytesWritten();
//         Sleep(50);
//         qDebug()<<"串口发送数据帧：开机 "<<frames;
//     }

// }

