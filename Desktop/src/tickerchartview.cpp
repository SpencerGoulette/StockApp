#include "tickerchartview.hpp"
#include "tickerdisplay.hpp"

TickerChartView::TickerChartView(QChart* chart, QWidget *parent)
    : QChartView(chart, parent)
{
    mMouseLine = new QGraphicsLineItem();
}


void TickerChartView::mouseMoveEvent(QMouseEvent *event)
{
    QPointF widgetPos = event->localPos();
    QPointF scenePos = mapToScene(QPoint(static_cast<int>(widgetPos.x()), static_cast<int>(widgetPos.y())));
    QPointF chartItemPos = chart()->mapFromScene(scenePos);
    QPointF valueGivenSeries = chart()->mapToValue(chartItemPos);

    QPoint curPos = QPoint(static_cast<int>(chartItemPos.x()) + x(), static_cast<int>(chartItemPos.y()) + y());

    qreal xVal = valueGivenSeries.x();
    qreal yVal = valueGivenSeries.y();

    time_t msEpoch = int(xVal / 1000);
    struct tm * date = gmtime(&msEpoch);
    QString dateStr = QString("%1-%2-%3").arg(date->tm_mon + 1).arg(date->tm_mday).arg(date->tm_year + 1900);

    // Remove Overlay Graphics
    QGraphicsScene * chartScene = scene();
    if (chartScene->items().contains(mMouseLine))
        chartScene->removeItem(mMouseLine);
    for (int dots = 0; dots < mMouseDots.size(); dots++)
        if (chartScene->items().contains(mMouseDots.at(dots)))
               chartScene->removeItem(mMouseDots.at(dots));

    QRectF rect = chart()->plotArea();
    QPointF pos = chart()->mapToPosition(QPointF(xVal, yVal));

    // Add Overlay Graphics
    if (pos.x() >= rect.left() && pos.x() <= rect.right() && pos.y() >= rect.top() && pos.y() <= rect.bottom())
    {
        // Add Line
        mMouseLine = chartScene->addLine(pos.x(), rect.top(), pos.x(), rect.bottom());

        QList<QAbstractSeries *> series = chart()->series();
        for (int idx = 0; idx < series.size(); idx++)
        {
            // Get Point
            QXYSeries * serie = qobject_cast<QXYSeries *>(series.at(idx));
            int pointX = int(pos.x());
            QString dateStr = QString("%1-%2-%3")
                    .arg(date->tm_year + 1900)
                    .arg(date->tm_mon + 1, 2, 10, QChar('0'))
                    .arg(date->tm_mday, 2, 10, QChar('0'));
            if (curTickerMap["Date"].indexOf(dateStr) >= 0)
            {
                yVal = curTickerMap["Close"].at(curTickerMap["Date"].indexOf(dateStr)).toDouble();
                int pointY = int(chart()->mapToPosition(QPointF(xVal, yVal)).y());

                // Customize Point Highlighting
                QPen pen = serie->pen();
                pen.setColor(Qt::black);
                QRect highPoint = QRect(pointX - serie->pen().width(), pointY, 2*serie->pen().width(), 2*serie->pen().width());

                // Add Highlights
                mMouseDots.append(chartScene->addEllipse(highPoint, pen, serie->brush()));

                // Add Point Info
                QToolTip::showText(mapToGlobal(curPos), QString("Date: %1\n Val: %2").arg(dateStr).arg(yVal));
            }
        }

        // Update Scene
        setScene(chartScene);
    }
    QChartView::mouseMoveEvent(event);

    update();
}


void TickerChartView::UpdateRange(void)
{
    QString range = "";
    if (qobject_cast<QPushButton *>(sender()) != nullptr)
        range = qobject_cast<QPushButton *>(sender())->text();

    if (range == "Week")
    {
        chart()->axisY()->setMin(0);
        chart()->axisX()->setRange(curTickerMap["Date"].at(curTickerMap["Date"].size() - 7),
                                    curTickerMap["Date"].at(curTickerMap["Date"].size() - 1));
    }
    else if (range == "Month")
    {
        chart()->axisY()->setMin(0);
        chart()->axisX()->setRange(curTickerMap["Date"].at(curTickerMap["Date"].size() - 31),
                                    curTickerMap["Date"].at(curTickerMap["Date"].size() - 1));
    }
    else if (range == "YTD")
    {
        chart()->axisY()->setMin(0);
        chart()->axisX()->setRange(curTickerMap["Date"].at(curTickerMap["Date"].size() - 365),
                                    curTickerMap["Date"].at(curTickerMap["Date"].size() - 1));
    }
    else
    {
        chart()->axisY()->setMin(0);
        chart()->axisX()->setRange(curTickerMap["Date"].at(0),
                                    curTickerMap["Date"].at(curTickerMap["Date"].size() - 1));
    }
    update();
}
