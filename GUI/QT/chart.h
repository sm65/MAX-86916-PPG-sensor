#include <QtCharts/QChart>
#include <QtCore/QTimer>

class QSplineSeries;
class QValueAxis;


class Chart: public QChart
{
    Q_OBJECT
public:
    Chart(QGraphicsItem *parent = nullptr, Qt::WindowFlags wFlags = Qt::Widget);
    virtual ~Chart();
public slots:
    void handleTimeout();

private:
    QTimer x_timer;
    QSplineSeries *IR_series;
    QSplineSeries *RED_series;
    QStringList m_titles;
    QValueAxis *x_axis;
    QValueAxis *IR_axis;
    QValueAxis *RED_axis;
    qreal m_step;
    qreal m_x;
    qreal y_IR;
    qreal y_RED;
    qreal y_GREEN;
    qreal y_BLUE;
    qreal IR_axis_min;
    qreal IR_axis_max;
    qreal RED_axis_min;
    qreal RED_axis_max;
    qreal y_axis_min_offset=-2000;
    qreal y_axis_max_offset=2000;
};

