#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtCharts>
#include <QComboBox>
#include <QString>
#include <QToolTip>

#include "yfapi.hpp"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

    QChart      * mMainChart;

public Q_SLOTS:
    void UpdateChart(QString ticker);

private:
    void setup(void);

    void createMenu(void);
    void createToolBar(void);
    void createDock(void);
    void createCentral(void);
    void createStatus(void);

    QWidget * mMainWidget;

    QComboBox * mStockPicker;
    YahooFinanceAPI mYFAPI;

private Q_SLOTS:
    void about(void);
    void settings(void);
};

#endif // MAINWINDOW_H
