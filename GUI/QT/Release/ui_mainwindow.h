/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.4.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCharts/QChartView>
#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QTableWidget *ADC_Data_Table;
    QChartView *myChart;
    QPushButton *Reset_COM_port_pushButton;
    QTableWidget *Command_Table;
    QTableWidget *Chart_table;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1691, 872);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName("centralWidget");
        ADC_Data_Table = new QTableWidget(centralWidget);
        if (ADC_Data_Table->columnCount() < 6)
            ADC_Data_Table->setColumnCount(6);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        ADC_Data_Table->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        ADC_Data_Table->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        ADC_Data_Table->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        ADC_Data_Table->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        ADC_Data_Table->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        ADC_Data_Table->setHorizontalHeaderItem(5, __qtablewidgetitem5);
        if (ADC_Data_Table->rowCount() < 1)
            ADC_Data_Table->setRowCount(1);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        ADC_Data_Table->setVerticalHeaderItem(0, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        __qtablewidgetitem7->setTextAlignment(Qt::AlignCenter);
        __qtablewidgetitem7->setFlags(Qt::ItemIsEnabled);
        ADC_Data_Table->setItem(0, 0, __qtablewidgetitem7);
        QTableWidgetItem *__qtablewidgetitem8 = new QTableWidgetItem();
        __qtablewidgetitem8->setTextAlignment(Qt::AlignCenter);
        __qtablewidgetitem8->setFlags(Qt::ItemIsEnabled);
        ADC_Data_Table->setItem(0, 1, __qtablewidgetitem8);
        QTableWidgetItem *__qtablewidgetitem9 = new QTableWidgetItem();
        __qtablewidgetitem9->setTextAlignment(Qt::AlignCenter);
        ADC_Data_Table->setItem(0, 2, __qtablewidgetitem9);
        QTableWidgetItem *__qtablewidgetitem10 = new QTableWidgetItem();
        __qtablewidgetitem10->setTextAlignment(Qt::AlignCenter);
        ADC_Data_Table->setItem(0, 3, __qtablewidgetitem10);
        QTableWidgetItem *__qtablewidgetitem11 = new QTableWidgetItem();
        __qtablewidgetitem11->setTextAlignment(Qt::AlignCenter);
        ADC_Data_Table->setItem(0, 4, __qtablewidgetitem11);
        QTableWidgetItem *__qtablewidgetitem12 = new QTableWidgetItem();
        __qtablewidgetitem12->setTextAlignment(Qt::AlignCenter);
        ADC_Data_Table->setItem(0, 5, __qtablewidgetitem12);
        ADC_Data_Table->setObjectName("ADC_Data_Table");
        ADC_Data_Table->setEnabled(true);
        ADC_Data_Table->setGeometry(QRect(470, 0, 411, 71));
        QPalette palette;
        QBrush brush(QColor(0, 0, 0, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::WindowText, brush);
        palette.setBrush(QPalette::Active, QPalette::Text, brush);
        palette.setBrush(QPalette::Active, QPalette::ButtonText, brush);
        QBrush brush1(QColor(0, 0, 0, 128));
        brush1.setStyle(Qt::NoBrush);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette.setBrush(QPalette::Active, QPalette::PlaceholderText, brush1);
#endif
        palette.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Text, brush);
        palette.setBrush(QPalette::Inactive, QPalette::ButtonText, brush);
        QBrush brush2(QColor(0, 0, 0, 128));
        brush2.setStyle(Qt::NoBrush);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette.setBrush(QPalette::Inactive, QPalette::PlaceholderText, brush2);
#endif
        palette.setBrush(QPalette::Disabled, QPalette::WindowText, brush);
        palette.setBrush(QPalette::Disabled, QPalette::Text, brush);
        palette.setBrush(QPalette::Disabled, QPalette::ButtonText, brush);
        QBrush brush3(QColor(0, 0, 0, 128));
        brush3.setStyle(Qt::NoBrush);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette.setBrush(QPalette::Disabled, QPalette::PlaceholderText, brush3);
#endif
        ADC_Data_Table->setPalette(palette);
        ADC_Data_Table->horizontalHeader()->setHighlightSections(false);
        ADC_Data_Table->verticalHeader()->setHighlightSections(false);
        myChart = new QChartView(centralWidget);
        myChart->setObjectName("myChart");
        myChart->setGeometry(QRect(20, 79, 1651, 761));
        Reset_COM_port_pushButton = new QPushButton(centralWidget);
        Reset_COM_port_pushButton->setObjectName("Reset_COM_port_pushButton");
        Reset_COM_port_pushButton->setGeometry(QRect(1470, 20, 91, 23));
        Command_Table = new QTableWidget(centralWidget);
        if (Command_Table->columnCount() < 6)
            Command_Table->setColumnCount(6);
        QTableWidgetItem *__qtablewidgetitem13 = new QTableWidgetItem();
        Command_Table->setHorizontalHeaderItem(0, __qtablewidgetitem13);
        QTableWidgetItem *__qtablewidgetitem14 = new QTableWidgetItem();
        Command_Table->setHorizontalHeaderItem(1, __qtablewidgetitem14);
        QTableWidgetItem *__qtablewidgetitem15 = new QTableWidgetItem();
        Command_Table->setHorizontalHeaderItem(2, __qtablewidgetitem15);
        QTableWidgetItem *__qtablewidgetitem16 = new QTableWidgetItem();
        Command_Table->setHorizontalHeaderItem(3, __qtablewidgetitem16);
        QTableWidgetItem *__qtablewidgetitem17 = new QTableWidgetItem();
        Command_Table->setHorizontalHeaderItem(4, __qtablewidgetitem17);
        QTableWidgetItem *__qtablewidgetitem18 = new QTableWidgetItem();
        Command_Table->setHorizontalHeaderItem(5, __qtablewidgetitem18);
        if (Command_Table->rowCount() < 1)
            Command_Table->setRowCount(1);
        QTableWidgetItem *__qtablewidgetitem19 = new QTableWidgetItem();
        Command_Table->setVerticalHeaderItem(0, __qtablewidgetitem19);
        QTableWidgetItem *__qtablewidgetitem20 = new QTableWidgetItem();
        __qtablewidgetitem20->setTextAlignment(Qt::AlignCenter);
        __qtablewidgetitem20->setFlags(Qt::ItemIsEditable|Qt::ItemIsEnabled);
        Command_Table->setItem(0, 0, __qtablewidgetitem20);
        QTableWidgetItem *__qtablewidgetitem21 = new QTableWidgetItem();
        __qtablewidgetitem21->setTextAlignment(Qt::AlignCenter);
        __qtablewidgetitem21->setFlags(Qt::ItemIsEditable|Qt::ItemIsEnabled);
        Command_Table->setItem(0, 1, __qtablewidgetitem21);
        QTableWidgetItem *__qtablewidgetitem22 = new QTableWidgetItem();
        __qtablewidgetitem22->setTextAlignment(Qt::AlignCenter);
        Command_Table->setItem(0, 2, __qtablewidgetitem22);
        QTableWidgetItem *__qtablewidgetitem23 = new QTableWidgetItem();
        __qtablewidgetitem23->setTextAlignment(Qt::AlignCenter);
        Command_Table->setItem(0, 3, __qtablewidgetitem23);
        QTableWidgetItem *__qtablewidgetitem24 = new QTableWidgetItem();
        Command_Table->setItem(0, 4, __qtablewidgetitem24);
        Command_Table->setObjectName("Command_Table");
        Command_Table->setEnabled(true);
        Command_Table->setGeometry(QRect(880, 0, 531, 71));
        QPalette palette1;
        palette1.setBrush(QPalette::Active, QPalette::WindowText, brush);
        palette1.setBrush(QPalette::Active, QPalette::Text, brush);
        palette1.setBrush(QPalette::Active, QPalette::ButtonText, brush);
        QBrush brush4(QColor(0, 0, 0, 128));
        brush4.setStyle(Qt::NoBrush);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette1.setBrush(QPalette::Active, QPalette::PlaceholderText, brush4);
#endif
        palette1.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette1.setBrush(QPalette::Inactive, QPalette::Text, brush);
        palette1.setBrush(QPalette::Inactive, QPalette::ButtonText, brush);
        QBrush brush5(QColor(0, 0, 0, 128));
        brush5.setStyle(Qt::NoBrush);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette1.setBrush(QPalette::Inactive, QPalette::PlaceholderText, brush5);
#endif
        palette1.setBrush(QPalette::Disabled, QPalette::WindowText, brush);
        palette1.setBrush(QPalette::Disabled, QPalette::Text, brush);
        palette1.setBrush(QPalette::Disabled, QPalette::ButtonText, brush);
        QBrush brush6(QColor(0, 0, 0, 128));
        brush6.setStyle(Qt::NoBrush);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette1.setBrush(QPalette::Disabled, QPalette::PlaceholderText, brush6);
#endif
        Command_Table->setPalette(palette1);
        Command_Table->horizontalHeader()->setHighlightSections(false);
        Command_Table->verticalHeader()->setHighlightSections(false);
        Chart_table = new QTableWidget(centralWidget);
        if (Chart_table->columnCount() < 6)
            Chart_table->setColumnCount(6);
        QTableWidgetItem *__qtablewidgetitem25 = new QTableWidgetItem();
        Chart_table->setHorizontalHeaderItem(0, __qtablewidgetitem25);
        QTableWidgetItem *__qtablewidgetitem26 = new QTableWidgetItem();
        Chart_table->setHorizontalHeaderItem(1, __qtablewidgetitem26);
        QTableWidgetItem *__qtablewidgetitem27 = new QTableWidgetItem();
        Chart_table->setHorizontalHeaderItem(2, __qtablewidgetitem27);
        QTableWidgetItem *__qtablewidgetitem28 = new QTableWidgetItem();
        Chart_table->setHorizontalHeaderItem(3, __qtablewidgetitem28);
        QTableWidgetItem *__qtablewidgetitem29 = new QTableWidgetItem();
        Chart_table->setHorizontalHeaderItem(4, __qtablewidgetitem29);
        QTableWidgetItem *__qtablewidgetitem30 = new QTableWidgetItem();
        Chart_table->setHorizontalHeaderItem(5, __qtablewidgetitem30);
        if (Chart_table->rowCount() < 1)
            Chart_table->setRowCount(1);
        QTableWidgetItem *__qtablewidgetitem31 = new QTableWidgetItem();
        Chart_table->setVerticalHeaderItem(0, __qtablewidgetitem31);
        QTableWidgetItem *__qtablewidgetitem32 = new QTableWidgetItem();
        Chart_table->setItem(0, 0, __qtablewidgetitem32);
        QTableWidgetItem *__qtablewidgetitem33 = new QTableWidgetItem();
        Chart_table->setItem(0, 1, __qtablewidgetitem33);
        QTableWidgetItem *__qtablewidgetitem34 = new QTableWidgetItem();
        Chart_table->setItem(0, 2, __qtablewidgetitem34);
        QTableWidgetItem *__qtablewidgetitem35 = new QTableWidgetItem();
        Chart_table->setItem(0, 3, __qtablewidgetitem35);
        QTableWidgetItem *__qtablewidgetitem36 = new QTableWidgetItem();
        Chart_table->setItem(0, 4, __qtablewidgetitem36);
        QTableWidgetItem *__qtablewidgetitem37 = new QTableWidgetItem();
        Chart_table->setItem(0, 5, __qtablewidgetitem37);
        Chart_table->setObjectName("Chart_table");
        Chart_table->setGeometry(QRect(20, 0, 451, 71));
        MainWindow->setCentralWidget(centralWidget);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName("mainToolBar");
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName("statusBar");
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "FPL Simulator", nullptr));
        QTableWidgetItem *___qtablewidgetitem = ADC_Data_Table->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("MainWindow", "IR ADC", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = ADC_Data_Table->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("MainWindow", "Red ADC", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = ADC_Data_Table->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("MainWindow", "Green ADC", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = ADC_Data_Table->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("MainWindow", "Blue ADC", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = ADC_Data_Table->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("MainWindow", "sPO2", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = ADC_Data_Table->horizontalHeaderItem(5);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("MainWindow", "Pulse", nullptr));

        const bool __sortingEnabled = ADC_Data_Table->isSortingEnabled();
        ADC_Data_Table->setSortingEnabled(false);
        ADC_Data_Table->setSortingEnabled(__sortingEnabled);

        Reset_COM_port_pushButton->setText(QCoreApplication::translate("MainWindow", "Reset COM port", nullptr));
        QTableWidgetItem *___qtablewidgetitem6 = Command_Table->horizontalHeaderItem(0);
        ___qtablewidgetitem6->setText(QCoreApplication::translate("MainWindow", "IR mA", nullptr));
        QTableWidgetItem *___qtablewidgetitem7 = Command_Table->horizontalHeaderItem(1);
        ___qtablewidgetitem7->setText(QCoreApplication::translate("MainWindow", "Red mA", nullptr));
        QTableWidgetItem *___qtablewidgetitem8 = Command_Table->horizontalHeaderItem(2);
        ___qtablewidgetitem8->setText(QCoreApplication::translate("MainWindow", "Green mA", nullptr));
        QTableWidgetItem *___qtablewidgetitem9 = Command_Table->horizontalHeaderItem(3);
        ___qtablewidgetitem9->setText(QCoreApplication::translate("MainWindow", "Blue mA", nullptr));
        QTableWidgetItem *___qtablewidgetitem10 = Command_Table->horizontalHeaderItem(4);
        ___qtablewidgetitem10->setText(QCoreApplication::translate("MainWindow", "Mode", nullptr));
        QTableWidgetItem *___qtablewidgetitem11 = Command_Table->horizontalHeaderItem(5);
        ___qtablewidgetitem11->setText(QCoreApplication::translate("MainWindow", "Pulse Width", nullptr));

        const bool __sortingEnabled1 = Command_Table->isSortingEnabled();
        Command_Table->setSortingEnabled(false);
        QTableWidgetItem *___qtablewidgetitem12 = Command_Table->item(0, 0);
        ___qtablewidgetitem12->setText(QCoreApplication::translate("MainWindow", "10", nullptr));
        QTableWidgetItem *___qtablewidgetitem13 = Command_Table->item(0, 1);
        ___qtablewidgetitem13->setText(QCoreApplication::translate("MainWindow", "10", nullptr));
        QTableWidgetItem *___qtablewidgetitem14 = Command_Table->item(0, 2);
        ___qtablewidgetitem14->setText(QCoreApplication::translate("MainWindow", "10", nullptr));
        QTableWidgetItem *___qtablewidgetitem15 = Command_Table->item(0, 3);
        ___qtablewidgetitem15->setText(QCoreApplication::translate("MainWindow", "10", nullptr));
        Command_Table->setSortingEnabled(__sortingEnabled1);

        QTableWidgetItem *___qtablewidgetitem16 = Chart_table->horizontalHeaderItem(0);
        ___qtablewidgetitem16->setText(QCoreApplication::translate("MainWindow", "Start/Reset", nullptr));
        QTableWidgetItem *___qtablewidgetitem17 = Chart_table->horizontalHeaderItem(1);
        ___qtablewidgetitem17->setText(QCoreApplication::translate("MainWindow", "Pause", nullptr));
        QTableWidgetItem *___qtablewidgetitem18 = Chart_table->horizontalHeaderItem(2);
        ___qtablewidgetitem18->setText(QCoreApplication::translate("MainWindow", "X Range", nullptr));
        QTableWidgetItem *___qtablewidgetitem19 = Chart_table->horizontalHeaderItem(3);
        ___qtablewidgetitem19->setText(QCoreApplication::translate("MainWindow", "X Tick", nullptr));
        QTableWidgetItem *___qtablewidgetitem20 = Chart_table->horizontalHeaderItem(4);
        ___qtablewidgetitem20->setText(QCoreApplication::translate("MainWindow", "Blue/Green", nullptr));
        QTableWidgetItem *___qtablewidgetitem21 = Chart_table->horizontalHeaderItem(5);
        ___qtablewidgetitem21->setText(QCoreApplication::translate("MainWindow", "Log File", nullptr));
        QTableWidgetItem *___qtablewidgetitem22 = Chart_table->verticalHeaderItem(0);
        ___qtablewidgetitem22->setText(QCoreApplication::translate("MainWindow", "Chart", nullptr));

        const bool __sortingEnabled2 = Chart_table->isSortingEnabled();
        Chart_table->setSortingEnabled(false);
        QTableWidgetItem *___qtablewidgetitem23 = Chart_table->item(0, 2);
        ___qtablewidgetitem23->setText(QCoreApplication::translate("MainWindow", "10", nullptr));
        QTableWidgetItem *___qtablewidgetitem24 = Chart_table->item(0, 3);
        ___qtablewidgetitem24->setText(QCoreApplication::translate("MainWindow", "10", nullptr));
        Chart_table->setSortingEnabled(__sortingEnabled2);

    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
