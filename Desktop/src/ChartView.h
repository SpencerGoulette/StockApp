#ifndef CHARTVIEW_H
#define CHARTVIEW_H

#include <QtCharts>

#include <iostream>

class ChartView : public QChartView
{
    Q_OBJECT

public:
    ChartView(QChart* chart, QWidget *parent = 0);

protected:
    virtual void mouseMoveEvent(QMouseEvent *event) override;

private:
    QGraphicsLineItem * mMouseLine;
    QList<QGraphicsEllipseItem *> mMouseDots;
};

#endif // CHARTVIEW_H
