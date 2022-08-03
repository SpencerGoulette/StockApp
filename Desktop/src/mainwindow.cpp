#include "mainwindow.h"
#include "ChartView.h"

#include <QHBoxLayout>
#include <QPainter>
#include <QComboBox>
#include <QAction>

#define WINDOW_TITLE "Early Investor"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setup();
}


MainWindow::~MainWindow()
{
}


void MainWindow::setup(void)
{
    createMenu();
    //createToolBar();
    //createDock();
    createCentral();
    //createStatus();

    setMinimumSize(720, 480);
    setWindowFlags(windowFlags() | Qt::WindowSystemMenuHint | Qt::WindowMinMaxButtonsHint);
    setWindowState(Qt::WindowMaximized);
    setWindowTitle(WINDOW_TITLE);
}


void MainWindow::createMenu(void)
{
    QAction * exitAction        = new QAction(tr("Exit"), this);
    QAction * settingsAction    = new QAction(tr("Settings"), this);
    QAction * aboutAction       = new QAction(tr("About"), this);

    connect(exitAction,     SIGNAL(triggered()), qApp, SLOT(quit()));
    connect(settingsAction, SIGNAL(triggered()), this, SLOT(settings()));
    connect(aboutAction,    SIGNAL(triggered()), this, SLOT(about()));

    QMenu * fileMenu    = menuBar()->addMenu(tr("File"));
    QMenu * helpMenu    = menuBar()->addMenu(tr("About"));

    fileMenu->addAction(settingsAction);
    fileMenu->addAction(exitAction);

    helpMenu->addAction(aboutAction);
}


void MainWindow::createCentral(void)
{
    mMainWidget  = new QWidget();
    mMainChart   = new QChart();
    mStockPicker = new QComboBox();

    QVBoxLayout * mainLayout = new QVBoxLayout();

    mStockPicker->addItem("");
    mStockPicker->addItem("SPY");
    mStockPicker->addItem("TSLA");
    mStockPicker->addItem("BND");

    ChartView * chartView = new ChartView(mMainChart);
    chartView->setRubberBand(QChartView::RectangleRubberBand);
    chartView->setRenderHint(QPainter::Antialiasing);

    connect(mStockPicker, SIGNAL(currentIndexChanged(QString)), this, SLOT(UpdateChart(QString)));

    mainLayout->addWidget(mStockPicker);
    mainLayout->addWidget(chartView);

    mMainWidget->setLayout(mainLayout);

    setCentralWidget(mMainWidget);
}


void MainWindow::about(void)
{
    QMessageBox::about(this, tr("About"), tr("This example demonstrates the "
        "different features of the QCompleter class."));
}


void MainWindow::settings(void)
{

}


void MainWindow::UpdateChart(QString ticker)
{
    bool isLineSeries = true;

    mMainChart->removeAllSeries();

    if (ticker == "")
        return;

    QMap<QString, QStringList> tmpMap;

    std::time_t now = std::time(nullptr);

    tmpMap = mYFAPI.GetTickerData(ticker, "0", QString("%1").arg(now));

    //chartView->addSeriesMap(tmpMap);

    if (isLineSeries)
    {
        QLineSeries * series = new QLineSeries();

        for(int row = 0; row < tmpMap["Date"].size(); row++)
            series->append(QDateTime(QDate::fromString(tmpMap["Date"].at(row), "yyyy-MM-dd")).toMSecsSinceEpoch(), tmpMap["Close"].at(row).toDouble());

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

        for(int row = 0; row < tmpMap["Date"].size(); row++)
        {
            QCandlestickSet * candlestick = new QCandlestickSet(tmpMap["Open"].at(row).toDouble(),
                                    tmpMap["High"].at(row).toDouble(),
                                    tmpMap["Low"].at(row).toDouble(),
                                    tmpMap["Close"].at(row).toDouble(),
                                    QDateTime(QDate::fromString(tmpMap["Date"].at(row), "yyyy-MM-dd")).toMSecsSinceEpoch());
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
