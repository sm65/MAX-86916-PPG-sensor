#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QtWidgets>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
private slots:
    void closeSerialPort();
    void readData();
    void fillPortsInfo();
    void Mode_index_changed(int index);
    void PW_index_changed(int index);
    void handleError(QSerialPort::SerialPortError error);
    void on_Reset_COM_port_pushButton_clicked();
    void on_LogcheckBox_clicked(bool checked);
    void on_Command_Table_cellChanged(int row, int column);
    void on_Chart_table_cellChanged(int row, int column);

private:
    Ui::MainWindow *ui;
    typedef union{
    float tempfloat;
    char tempbyte[4];
    }Float2Byte;
    typedef union{
    uint16_t tempshort;
        uint8_t tempbyte[2];
    }ushort2byte;
    typedef union{
        uint8_t _bytes[20];
        struct{
        uint32_t RED;
        uint32_t IR;
        uint32_t GREEN;
        uint32_t BLUE;
        uint16_t Pulse;
        uint16_t SpO2;
        }sdata;
    }utopc_data;
    typedef enum{
     IR_MA=85,
     RED_MA,
     GREEN_MA,
     BLUE_MA,
     OP_MODE,
     LED_PW
    }ecommands;
    void initTables();
    void initChart();

    void version();
    void init_serial_port(QString com);
    QSerialPort *serial;
    QComboBox *Mode_Cmd;
    QComboBox *PW_Cmd;
    int link_status;
    double logfile_x=0;
    bool Table_Init=false;
};

#endif // MAINWINDOW_H
