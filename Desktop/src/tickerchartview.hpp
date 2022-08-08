#ifndef TICKERCHARTVIEW_H
#define TICKERCHARTVIEW_H

#include <QtCharts>

#include <iostream>

class TickerChartView : public QChartView
{
    Q_OBJECT

public:
    TickerChartView(QChart* chart, QWidget *parent = 0);

protected:
    virtual void mouseMoveEvent(QMouseEvent *event) override;

private:
    QGraphicsLineItem * mMouseLine;
    QList<QGraphicsEllipseItem *> mMouseDots;
};

#endif // CHARTVIEW_H
