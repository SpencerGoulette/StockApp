#ifndef TICKERDISPLAY_H
#define TICKERDISPLAY_H

#include <QtCharts>
#include <QLabel>

#include "yfapi.hpp"
#include "tickerchartview.hpp"
#include "tickerinfoview.hpp"
#include "tickerselectorview.hpp"

class TickerDisplay : public QWidget
{
    Q_OBJECT

public:
    TickerDisplay(QWidget *parent = 0);
    ~TickerDisplay();

    QChart *    mMainChart;

public Q_SLOTS:
    void UpdateTicker(QString ticker);

private:
    void setup(void);

    void createGUI(void);

    TickerChartView *       mTickerChartView;
    TickerInfoView *        mTickerInfoView;
    TickerSelectorView *    mTickerSelectorView;
    YahooFinanceAPI         mYFAPI;
};

#endif // TICKERDISPLAY_H
