#include "mainwindow.h"
#include "tickerchartview.hpp"

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


void MainWindow::about(void)
{
    QMessageBox::about(this, tr("About"), tr("This example demonstrates the "
        "different features of the QCompleter class."));
}


void MainWindow::settings(void)
{

}


void MainWindow::createCentral(void)
{
    mainWidget      = new QWidget();
    mainLayout      = new QStackedLayout();

    mTickerDisplay  = new TickerDisplay();


    mainLayout->addWidget(mTickerDisplay);

    mainWidget->setLayout(mainLayout);

    setCentralWidget(mainWidget);
}
