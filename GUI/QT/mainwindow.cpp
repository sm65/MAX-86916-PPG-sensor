#include "chart.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtCharts/QChartView>

double IR_Data;
double RED_Data;
double GREEN_Data;
double BLUE_Data;
double X_Axis_Range;
int    X_Axis_Tick;
bool Pause;
bool BLUE_GREEN;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->version();
    serial = new QSerialPort(this);
    this->fillPortsInfo();
    this->initTables();
    Table_Init=true;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::init_serial_port(QString com){
serial->setPortName(com);
serial->setBaudRate(QSerialPort::Baud115200);
serial->setDataBits(QSerialPort::Data8);
serial->setParity(QSerialPort::NoParity);
serial->setStopBits(QSerialPort::OneStop);
serial->setFlowControl(QSerialPort::NoFlowControl);/**/
if (serial->open(QIODevice::ReadWrite)){
    serial->clear();
connect(serial, &QSerialPort::readyRead, this, &MainWindow::readData);
connect(serial, &QSerialPort::errorOccurred, this, &MainWindow::handleError);
}}

void MainWindow::initChart()
{
X_Axis_Range=ui->Chart_table->item(0,2)->text().toDouble();
X_Axis_Tick=ui->Chart_table->item(0,3)->text().toInt();
Chart *chart = new Chart;
chart->setTitle("MAX 86916 ADC");
chart->legend()->hide();
chart->setAnimationOptions(QChart::AllAnimations);
ui->myChart->setChart(chart);
}

void MainWindow::version()
{
QString app_version = APP_VERSION;
this->setWindowTitle("MAX 86916 I/F V" + app_version);
}

void MainWindow::initTables()
{
    int i;
    for(i=0;i<6;i++){
    ui->ADC_Data_Table->setColumnWidth(i,65);
    ui->Chart_table->setColumnWidth(i,65);
    ui->Chart_table->item(0,i)->setFlags(Qt::ItemIsEnabled | Qt::ItemIsUserCheckable | Qt::ItemIsEditable);
   }
    ui->ADC_Data_Table->setRowHeight(0,20);
    ui->ADC_Data_Table->item(0,0)->setForeground(Qt::darkRed);
    ui->ADC_Data_Table->item(0,1)->setForeground(Qt::red);
    ui->ADC_Data_Table->item(0,2)->setForeground(Qt::darkGreen);
    ui->ADC_Data_Table->item(0,3)->setForeground(Qt::blue);

    ui->Chart_table->setRowHeight(0,20);
    ui->Chart_table->item(0,0)->setCheckState(Qt::Unchecked);
    ui->Chart_table->item(0,1)->setCheckState(Qt::Unchecked);
    ui->Chart_table->item(0,2)->setTextAlignment(Qt::AlignCenter);
    ui->Chart_table->item(0,3)->setTextAlignment(Qt::AlignCenter);
    ui->Chart_table->item(0,4)->setCheckState(Qt::Unchecked);
    ui->Chart_table->item(0,5)->setCheckState(Qt::Unchecked);
    for(i=0;i<4;i++){
    ui->Command_Table->setColumnWidth(i,70);
   }
    ui->Command_Table->setColumnWidth(4,80);
    ui->Command_Table->setColumnWidth(5,80);
    ui->Command_Table->setRowHeight(0,20);
    ui->Command_Table->item(0,0)->setForeground(Qt::darkRed);
    ui->Command_Table->item(0,1)->setForeground(Qt::red);
    ui->Command_Table->item(0,2)->setForeground(Qt::darkGreen);
    ui->Command_Table->item(0,3)->setForeground(Qt::blue);
    QString temp_string = "Pulse\nWidth (";
    temp_string.append(QChar(0xb5,0x00));//micro symbol
    temp_string.append("s)");
    ui->Command_Table->setHorizontalHeaderLabels(QStringList()<<"IR (mA)"<<"RED (mA)"<<"Green (mA)"<<"Blue (mA)"<<"Mode"<<temp_string);
    Mode_Cmd=new QComboBox(this);
    Mode_Cmd->addItems(QStringList()<<"Disabled"<<"LED 1"<<"LED 1 & 2"<<"Flex");
    Mode_Cmd->setCurrentIndex(2);
    ui->Command_Table->setCellWidget(0,4,Mode_Cmd);
    connect(Mode_Cmd, QOverload<int>::of(&QComboBox::currentIndexChanged),
        [=](int index){Mode_index_changed(index);});
    PW_Cmd=new QComboBox(this);
    PW_Cmd->addItems(QStringList()<<"70"<<"120"<<"220"<<"420");
    PW_Cmd->setCurrentIndex(2);
    ui->Command_Table->setCellWidget(0,5,PW_Cmd);
    connect(PW_Cmd, QOverload<int>::of(&QComboBox::currentIndexChanged),
        [=](int index){PW_index_changed(index);});
}

void MainWindow::readData()
{
       QByteArray serial_data;
       utopc_data data;
       int i;
       if (serial->bytesAvailable()>19){
       serial_data = serial->read(20);
       serial->clear();
       for(i=0;i<20;i++){
           data._bytes[i]=serial_data[i];
       }

       i=Mode_Cmd->currentIndex();
       if(i>0){
       IR_Data=data.sdata.IR;
       ui->ADC_Data_Table->item(0,0)->setText(QString::number(data.sdata.IR));
       if(i>1){
       RED_Data=data.sdata.RED;
       ui->ADC_Data_Table->item(0,1)->setText(QString::number(data.sdata.RED));
       ui->ADC_Data_Table->item(0,4)->setText(QString::number(data.sdata.SpO2));
       }
       else{
           ui->ADC_Data_Table->item(0,1)->setText("N/A");
           ui->ADC_Data_Table->item(0,4)->setText("N/A");
       }
       if(i==3){
         GREEN_Data=data.sdata.GREEN;
         BLUE_Data=data.sdata.BLUE;
         ui->ADC_Data_Table->item(0,2)->setText(QString::number(data.sdata.GREEN));
         ui->ADC_Data_Table->item(0,3)->setText(QString::number(data.sdata.BLUE));
       }
       else{
           ui->ADC_Data_Table->item(0,2)->setText("N/A");
           ui->ADC_Data_Table->item(0,3)->setText("N/A");
       }
       ui->ADC_Data_Table->item(0,5)->setText(QString::number(data.sdata.Pulse));
       }
       else{
          for(i=0;i<6;i++){
           ui->ADC_Data_Table->item(0,i)->setText("N/A");
          }
       }

       if(ui->Chart_table->item(0,5)->checkState()){
           QFile file_data("ppg_logdata.csv");
           logfile_x+=0.05;
           if (file_data.open(QIODevice::ReadWrite| QIODevice::Append)){
              QTextStream out(&file_data);
               out << logfile_x<<","<<IR_Data<<","<<RED_Data<<","<<GREEN_Data<<","<<BLUE_Data<< '\n';
}}}}

void MainWindow::closeSerialPort()
{
    if (serial->isOpen())
        serial->close();
}

void MainWindow::handleError(QSerialPort::SerialPortError error)
{
    if (error == QSerialPort::ResourceError) {
        closeSerialPort();
    }
}

void MainWindow::fillPortsInfo()
{
    //ui->serialPortInfoListBox->clear();
    QString description;
    QString manufacturer;
    QString serialNumber;
    const auto infos = QSerialPortInfo::availablePorts();
    for (const QSerialPortInfo &info : infos) {
        if(info.productIdentifier()==0x5740){//TI
        this->init_serial_port(info.portName());
        }/*
        QStringList list;
        description = info.description();
        manufacturer = info.manufacturer();
        serialNumber = info.serialNumber();
        list << info.portName();
        ui->serialPortInfoListBox->addItem(list.first(), list);
    }*/
}}

void MainWindow::on_Reset_COM_port_pushButton_clicked()
{
    closeSerialPort();
    this->fillPortsInfo();
}

void MainWindow::on_LogcheckBox_clicked(bool checked)
{
    QFile file_data("ppg_logdata.csv");
    if(checked){     
        if(file_data.open(QIODevice::ReadWrite| QIODevice::Truncate)){
            QTextStream out(&file_data);
             out <<" ,IR ADC,RED ADC,GREEN ADC,BLUE ADC"<<'\n';
        }}
        else{
            file_data.close();
            logfile_x=0;
        }
}

void MainWindow::on_Command_Table_cellChanged(int row, int column)
{
    if(Table_Init){
    if(row==0){
       bool ok=true;
       QByteArray send;
       uint8_t milliamps=ui->Command_Table->item(row,column)->text().toDouble()/0.2;
       send.append(milliamps);
       switch(column){
       case 0:
       send.prepend(IR_MA);
       break;
       case 1:
       send.prepend(RED_MA);     
       break;
       case 2:
       send.prepend(GREEN_MA);
       break;
       case 3:
       send.prepend(BLUE_MA);
       break;
       default:
       ok=false;
       break;
       }
       if(ok){
       serial->write(send,2);
       }
}}}

void MainWindow::Mode_index_changed(int index)
{
    QByteArray send;
    send.prepend(OP_MODE);
    send.append(index);
    serial->write(send,2);
}

void MainWindow::PW_index_changed(int index)
{
    QByteArray send;
    send.prepend(LED_PW);
    send.append(index);
    serial->write(send,2);
}

void MainWindow::on_Chart_table_cellChanged(int row, int column)
{
    if(Table_Init){
    if(row==0){
        switch (column){
           case 0:
            if(ui->Chart_table->item(row,column)->checkState()){
               this->initChart();
               ui->Chart_table->item(row,column)->setCheckState(Qt::Unchecked);
            }
            break;
           case 1:
            if(ui->Chart_table->item(row,column)->checkState()){
              Pause=true;
            }
            else{
              Pause=false;
            }
            break;
           case 2:
           case 3:
            break;
           case 4:
            if(ui->Chart_table->item(row,column)->checkState()){
              BLUE_GREEN=true;
            }
            else{
              BLUE_GREEN=false;
            }
            this->initChart();
            break;
            case 5:
            QFile file_data("ppg_logdata.csv");
            if(ui->Chart_table->item(row,column)->checkState()){
                    if(file_data.open(QIODevice::ReadWrite| QIODevice::Truncate)){
                        QTextStream out(&file_data);
                         out <<" ,IR ADC,RED ADC,GREEN ADC,BLUE ADC"<<'\n';
                    }
                    else{
                        file_data.close();
                        logfile_x=0;
                    }
            }
        }
    }}
}

