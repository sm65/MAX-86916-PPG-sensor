#include "chart.h"
#include <QtCharts/QAbstractAxis>
#include <QtCharts/QSplineSeries>
#include <QtCharts/QValueAxis>
#include <QtCore/QRandomGenerator>
#include <QtCore/QDebug>


extern double IR_Data;
extern double RED_Data;
extern double GREEN_Data;
extern double BLUE_Data;
extern double X_Axis_Range;
extern int    X_Axis_Tick;
extern bool Pause;
extern bool BLUE_GREEN;

Chart::Chart(QGraphicsItem *parent, Qt::WindowFlags wFlags):
    QChart(QChart::ChartTypeCartesian, parent, wFlags),
    IR_series(0),
    x_axis(new QValueAxis),
    IR_axis(new QValueAxis),
    RED_axis(new QValueAxis),
    m_step(0),
    m_x(0),  
    y_IR(static_cast<qreal>(IR_Data)),
    y_RED(static_cast<qreal>(RED_Data)),
    y_GREEN(static_cast<qreal>(GREEN_Data)),
    y_BLUE(static_cast<qreal>(BLUE_Data))
{

    QObject::connect(&x_timer, &QTimer::timeout, this, &Chart::handleTimeout);
    x_timer.setInterval(100);
    IR_series = new QSplineSeries(this);
    RED_series = new QSplineSeries(this);
    if(!(BLUE_GREEN)){
    QPen dark_red(Qt::darkRed); 
    dark_red.setWidth(2);
    IR_series->setPen(dark_red);
    QPen red(Qt::red);
    red.setWidth(2);
    RED_series->setPen(red);
    }
    else{
    QPen dark_green(Qt::darkGreen);
    dark_green.setWidth(2);
    IR_series->setPen(dark_green);
    QPen blue(Qt::blue);
    blue.setWidth(2);
    RED_series->setPen(blue);
    }
    addSeries(IR_series);
    addSeries(RED_series);
    addAxis(x_axis,Qt::AlignBottom);

    IR_axis_max=y_IR+y_axis_max_offset;
    IR_axis_min=y_IR+y_axis_min_offset;
    RED_axis_max=y_RED+y_axis_max_offset;
    RED_axis_min=y_RED+y_axis_min_offset;
    addAxis(IR_axis, Qt::AlignLeft);
    IR_axis->setRange(IR_axis_min,IR_axis_max);
    addAxis(RED_axis, Qt::AlignRight);
    RED_axis->setRange(IR_axis_min,IR_axis_max);
    x_axis->setLabelFormat("%d");
    x_axis->setRange(0,X_Axis_Range);
    x_axis->setTickCount(X_Axis_Tick);
    IR_series->attachAxis(x_axis);
    IR_series->attachAxis(IR_axis);
    IR_series->append(m_x, y_IR);
    RED_series->attachAxis(x_axis);
    RED_series->attachAxis(RED_axis);
    RED_series->append(m_x, y_RED);
    x_timer.start();
}

Chart::~Chart()
{

}

void Chart::handleTimeout()
{
    if(!(Pause)){
    m_x += 0.1;
    if(!(BLUE_GREEN)){
    y_IR = static_cast<qreal>(IR_Data);
    y_RED = static_cast<qreal>(RED_Data);
    }
    else{
    y_IR = static_cast<qreal>(GREEN_Data);
    y_RED = static_cast<qreal>(BLUE_Data);
    }
    IR_series->append(m_x, y_IR);
    RED_series->append(m_x, y_RED);
    if (m_x > x_axis->max())
    {
        m_x=0;
        IR_series->clear();
        RED_series->clear();
        IR_axis_max=y_IR+y_axis_max_offset;
        IR_axis_min=y_IR+y_axis_min_offset;
        RED_axis_max=y_RED+y_axis_max_offset;
        RED_axis_min=y_RED+y_axis_min_offset;
        IR_axis->setRange( IR_axis_min, IR_axis_max);
        RED_axis->setRange( RED_axis_min,RED_axis_max);
    }

    if (y_IR>=IR_axis_max)
    {
          IR_axis_max=y_IR+y_axis_max_offset;
          IR_axis->setRange(IR_axis_min,IR_axis_max);
       }
    else if (y_IR<IR_axis_min)
      {
          IR_axis_min=y_IR+y_axis_min_offset;
          IR_axis->setRange(IR_axis_min,IR_axis_max);
       }

    if (y_RED>=RED_axis_max)
    {
          RED_axis_max=y_RED+y_axis_max_offset;
          RED_axis->setRange(RED_axis_min,RED_axis_max);
       }
    else if (y_RED<RED_axis_min)
      {
          RED_axis_min=y_RED+y_axis_min_offset;
          RED_axis->setRange(RED_axis_min,RED_axis_max);
       }
}}





