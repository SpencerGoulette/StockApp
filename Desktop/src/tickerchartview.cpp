#include "tickerchartview.hpp"

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
    //printf("%d", int(xVal));
    //printf("%s", asctime(gmtime(&val)));
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
            int expIdx = int((xVal - serie->at(0).x())/double(serie->at(1).x() - serie->at(0).x()));
            int pointX = int(pos.x());
            int pointY = int(chart()->mapToPosition(QPointF(0, serie->at(expIdx).y())).y());

            // Customize Point Highlighting
            QPen pen = serie->pen();
            pen.setColor(Qt::black);
            QRect highPoint = QRect(pointX, pointY, 2*serie->pen().width(), 2*serie->pen().width());

            // Add Highlights
            mMouseDots.append(chartScene->addEllipse(highPoint, pen, serie->brush()));

            // Add Point Info
            QToolTip::showText(mapToGlobal(curPos), QString("Date: %1\n Val: %2").arg(dateStr).arg(serie->at(expIdx).y()));
        }

        // Update Scene
        setScene(chartScene);
    }
    QChartView::mouseMoveEvent(event);

    update();
}
