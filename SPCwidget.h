#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QSerialPort>

QT_BEGIN_NAMESPACE
namespace Ui {
class Widget;
}
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void on_btn_PowerConnect_clicked();

    void on_btn_PowerDisconnect_clicked();

    void on_btn_on_all_clicked();

    void on_btn_off_all_clicked();

    void do_com_readyRead(); //当串口缓冲区有数据时，处理

    void on_btn_on_1_clicked();

    void on_btn_off_1_clicked();

    void on_btn_on_2_clicked();

    void on_btn_on_3_clicked();

    void on_btn_on_4_clicked();

    void on_btn_on_5_clicked();

    void on_btn_on_6_clicked();

    void on_btn_on_7_clicked();

    void on_btn_on_8_clicked();

    void on_btn_off_2_clicked();

    void on_btn_off_3_clicked();

    void on_btn_off_4_clicked();

    void on_btn_off_5_clicked();

    void on_btn_off_6_clicked();

    void on_btn_off_7_clicked();

    void on_btn_off_8_clicked();

    //void on_btn_standby_clicked();

private:
    Ui::Widget *ui;
    QSerialPort mySerialPort; //串口对象
    bool relay_1_Open = false; //继电器1~8是否开启的标志
    bool relay_2_Open = false;
    bool relay_3_Open = false;
    bool relay_4_Open = false;
    bool relay_5_Open = false;
    bool relay_6_Open = false;
    bool relay_7_Open = false;
    bool relay_8_Open = false;
    bool standbyOrNot = false;//默认初始为开机状态
};
#endif // WIDGET_H
