#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedLayout>

#include "tickerdisplay.hpp"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    void setup(void);

    void createMenu(void);
    void createToolBar(void);
    void createDock(void);
    void createCentral(void);
    void createStatus(void);

    QWidget * mainWidget;
    QStackedLayout * mainLayout;
    TickerDisplay * mTickerDisplay;

private Q_SLOTS:
    void about(void);
    void settings(void);
};

#endif // MAINWINDOW_H
