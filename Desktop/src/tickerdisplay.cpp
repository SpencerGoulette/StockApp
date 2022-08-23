#include "tickerdisplay.hpp"

#include <QGridLayout>
#include <QString>

TickerDisplay::TickerDisplay(QWidget *parent)
    : QWidget(parent)
{
    setup();
}


TickerDisplay::~TickerDisplay()
{

}



void TickerDisplay::setup(void)
{
    createGUI();

    connect(mTickerSelectorView, SIGNAL(tickerSelected(QString)), this, SLOT(UpdateTicker(QString)));
}


void TickerDisplay::createGUI(void)
{
    mMainChart              = new QChart();
    mTickerSelectorView     = new TickerSelectorView();
    mTickerInfoView         = new TickerInfoView();
    mTickerChartView        = new TickerChartView(mMainChart);

    QHBoxLayout * mainLayout    = new QHBoxLayout();
    QVBoxLayout * tickerLayout  = new QVBoxLayout();

    mTickerChartView->setRubberBand(QChartView::RectangleRubberBand);
    mTickerChartView->setRenderHint(QPainter::Antialiasing);

    QWidget * tickerHWidget = new QWidget();

    tickerLayout->addWidget(mTickerChartView);
    tickerLayout->addWidget(mTickerInfoView);

    tickerHWidget->setLayout(tickerLayout);

    mainLayout->addWidget(mTickerSelectorView);
    mainLayout->addWidget(tickerHWidget);

    setLayout(mainLayout);
}


void TickerDisplay::UpdateTicker(QString ticker)
{
    bool isLineSeries = true;

    mMainChart->removeAllSeries();

    if (ticker == "")
        return;

    std::time_t now = std::time(nullptr);

    QMap<QString, QStringList>  tmpTickerMap;

    tmpTickerMap = mYFAPI.GetTickerData(ticker, "0", QString("%1").arg(now));

    mTickerChartView->UpdateTicker(tmpTickerMap);

    //chartView->addSeriesMap(tmpTickerMap);

    // Update Chart
    if (isLineSeries)
    {
        QLineSeries * series = new QLineSeries();

        for(int row = 0; row < tmpTickerMap["Date"].size(); row++)
            series->append(QDateTime(QDate::fromString(tmpTickerMap["Date"].at(row), "yyyy-MM-dd")).toMSecsSinceEpoch(), tmpTickerMap["Close"].at(row).toDouble());

        mMainChart->legend()->hide();
        mMainChart->addSeries(series);
        mMainChart->setTitle(QString("%1 Stock").arg(ticker));

        QDateTimeAxis * axisX = new QDateTimeAxis;
        axisX->setTickCount(10);
        axisX->setFormat("MM-dd-yyyy");
        axisX->setTitleText("Date");
        mMainChart->setAxisX(axisX);
        series->attachAxis(axisX);

        QValueAxis * axisY = new QValueAxis();
        axisY->setTickCount(10);
        axisY->setTitleText("Value ($)");
        mMainChart->setAxisY(axisY);
        series->attachAxis(axisY);
    }
    else
    {
        QCandlestickSeries * series = new QCandlestickSeries();
        series->setIncreasingColor(QColor(Qt::green));
        series->setDecreasingColor(QColor(Qt::red));

        for(int row = 0; row < tmpTickerMap["Date"].size(); row++)
        {
            QCandlestickSet * candlestick = new QCandlestickSet(tmpTickerMap["Open"].at(row).toDouble(),
                                    tmpTickerMap["High"].at(row).toDouble(),
                                    tmpTickerMap["Low"].at(row).toDouble(),
                                    tmpTickerMap["Close"].at(row).toDouble(),
                                    QDateTime(QDate::fromString(tmpTickerMap["Date"].at(row), "yyyy-MM-dd")).toMSecsSinceEpoch());
            series->append(candlestick);
        }

        mMainChart->legend()->hide();
        mMainChart->addSeries(series);
        mMainChart->setTitle(QString("%1 Stock").arg(ticker));

        QDateTimeAxis * axisX = new QDateTimeAxis;
        axisX->setTickCount(10);
        axisX->setFormat("MM-dd-yyyy");
        axisX->setTitleText("Date");
        mMainChart->setAxisX(axisX);
        series->attachAxis(axisX);

        QValueAxis * axisY = new QValueAxis();
        axisY->setTickCount(10);
        axisY->setTitleText("Value ($)");
        mMainChart->setAxisY(axisY);
        series->attachAxis(axisY);
    }

    mMainChart->update();


    // Update Ticker Info
    QString open = "";
    QString high = "";
    QString low = "";
    QString mktcap = "";
    QString peratio = "";
    QString divyield = "";
    QString wkhigh = "";
    QString wklow = "";

    open = tmpTickerMap["Open"].last();
    high = tmpTickerMap["High"].last();
    low = tmpTickerMap["Low"].last();

    mTickerInfoView->updateTickerInfo(open, high, low, mktcap, peratio, divyield, wkhigh, wklow);

/*    for(unsigned long asset = 0; asset < assetClasses.size(); asset++)
    {
        for()
        {

        }
    }

    X1*return1 + X2*return2 + X3*return3

    X1^2*var(return1) + X1^2*var(return1) + X1^2*var(return1) + 2*X1*X2*covar(return1, return2)
            + 2*X1*X3*covar(return1, return3) + 2*X2*X3*covar(return2, return3)

    for (unsigned long idx = 0; idx < ; idx++)
        series->append(xData.at(idx), yData.at(idx));
*/
}
