#ifndef TICKERCHARTVIEW_H
#define TICKERCHARTVIEW_H

#include <QtCharts>

#include <iostream>

class TickerChartView : public QChartView
{
    Q_OBJECT

public:
    TickerChartView(QChart* chart, QWidget *parent = 0);

    void UpdateTicker(QMap<QString, QStringList> tmpTickerMap) {curTickerMap = tmpTickerMap;}

public Q_SLOTS:
    void UpdateRange(void);

protected:
    virtual void mouseMoveEvent(QMouseEvent *event) override;

private:
    QGraphicsLineItem * mMouseLine;
    QList<QGraphicsEllipseItem *> mMouseDots;

    QMap<QString, QStringList> curTickerMap;
};

#endif // CHARTVIEW_H
