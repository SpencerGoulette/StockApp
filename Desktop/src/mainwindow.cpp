#include "mainwindow.h"
#include "tickerchartview.hpp"

#include <QHBoxLayout>
#include <QPainter>
#include <QComboBox>
#include <QAction>
#include <QUrl>

#define APP_NAME "Finette"

#define LOGO_SIZE 50

#define DONATE_URL "https://www.patreon.com/Finette/membership"

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
    createLayout();

    setMinimumSize(720, 480);

    // Include border
    //setWindowFlags(windowFlags() | Qt::WindowSystemMenuHint | Qt::WindowMinMaxButtonsHint);
    //setWindowState(Qt::WindowMaximized);
    //setWindowTitle(WINDOW_TITLE);

    // Make borderless
    setWindowFlags(windowFlags() | Qt::FramelessWindowHint);
    setWindowState(Qt::WindowMaximized);

    // Apply Stylesheet
    QFile file(":/style/style.qss");
    file.open(QFile::ReadOnly);
    QString styleSheet = QLatin1String(file.readAll());
    qApp->setStyleSheet(styleSheet);
}


void MainWindow::createLayout(void)
{
    // INSTANTIATE
    // Main Layout Widgets
    mMainWidget         = new QWidget();
    mMenuWidget         = new QWidget();
    mTabWidget          = new QWidget();

    // Main Layouts
    mMainLayout         = new QHBoxLayout();
    mMenuLayout         = new QVBoxLayout();
    mTabLayout          = new QStackedLayout();

    // Logo
    mLogo               = new QLabel();
    mLogoLbl            = new QLabel(tr(APP_NAME));

    // Menu Options
    mDashboardBtn       = new QPushButton(QIcon(":/img/dashboard.png"), tr("Dashboard"));
    mPortfoliosBtn      = new QPushButton(QIcon(":/img/portfolios.png"), tr("Portfolios"));
    mBudgettingBtn      = new QPushButton(QIcon(":/img/budget.png"), tr("Budgetting"));
    mTickersBtn         = new QPushButton(QIcon(":/img/ticker.png"), tr("Tickers"));
    mResourcesBtn       = new QPushButton(QIcon(":/img/resources.png"), tr("Resources"));
    mSettingsBtn        = new QPushButton(QIcon(":/img/settings.png"), tr("Settings"));

    // Displays
    mDashboardDisplay   = new DashboardDisplay();
    mPortfolioDisplay   = new PortfolioDisplay();
    mBudgettingDisplay  = new BudgettingDisplay();
    mTickerDisplay      = new TickerDisplay();
    mResourcesDisplay   = new ResourcesDisplay();
    mSettingsDisplay    = new SettingsDisplay();

    // Donate
    mDonateBtn          = new QPushButton(tr("Donate"));


    // SETUP
    // Set up Logo
    QHBoxLayout * logoLayout = new QHBoxLayout();
    QWidget * logo  = new QWidget();

    QFont logoFont = mLogoLbl->font();
    logoFont.setPointSize(LOGO_SIZE/2);
    logoFont.setBold(true);
    mLogoLbl->setFont(logoFont);
    QPixmap pixmap(":/img/logo.png");
    mLogo->setPixmap(pixmap.scaled(LOGO_SIZE, LOGO_SIZE));
    logo->setMaximumHeight(LOGO_SIZE*2);

    logoLayout->addWidget(mLogo);
    logoLayout->addWidget(mLogoLbl);

    logo->setLayout(logoLayout);

    // Setup Buttons
    mDashboardBtn->setObjectName("menuButton");
    mPortfoliosBtn->setObjectName("menuButton");
    mBudgettingBtn->setObjectName("menuButton");
    mTickersBtn->setObjectName("menuButton");
    mResourcesBtn->setObjectName("menuButton");
    mSettingsBtn->setObjectName("menuButton");
    mDonateBtn->setObjectName("donateButton");

    connect(mDashboardBtn,  &QPushButton::clicked, this, &MainWindow::selectMenuButton);
    connect(mPortfoliosBtn, &QPushButton::clicked, this, &MainWindow::selectMenuButton);
    connect(mBudgettingBtn, &QPushButton::clicked, this, &MainWindow::selectMenuButton);
    connect(mTickersBtn,    &QPushButton::clicked, this, &MainWindow::selectMenuButton);
    connect(mResourcesBtn,  &QPushButton::clicked, this, &MainWindow::selectMenuButton);
    connect(mSettingsBtn,   &QPushButton::clicked, this, &MainWindow::selectMenuButton);
    connect(mDonateBtn,     &QPushButton::clicked,
            this, [=]() {QDesktopServices::openUrl(QUrl(DONATE_URL, QUrl::TolerantMode));});

    mDashboardBtn->setIconSize(QSize(LOGO_SIZE/2, LOGO_SIZE/2));
    mPortfoliosBtn->setIconSize(QSize(LOGO_SIZE/2, LOGO_SIZE/2));
    mBudgettingBtn->setIconSize(QSize(LOGO_SIZE/2, LOGO_SIZE/2));
    mTickersBtn->setIconSize(QSize(LOGO_SIZE/2, LOGO_SIZE/2));
    mResourcesBtn->setIconSize(QSize(LOGO_SIZE/2, LOGO_SIZE/2));
    mSettingsBtn->setIconSize(QSize(LOGO_SIZE/2, LOGO_SIZE/2));

    mSelectedOption = mDashboardBtn;
    mDashboardBtn->setProperty("selected", "true");


    // LAYOUT
    // Menu Widget
    mMenuLayout->addWidget(logo, 0, Qt::AlignTop);

    mMenuLayout->addWidget(mDashboardBtn, 1);
    mMenuLayout->addWidget(mPortfoliosBtn, 1);
    mMenuLayout->addWidget(mBudgettingBtn, 1);
    mMenuLayout->addWidget(mTickersBtn, 1);
    mMenuLayout->addWidget(mResourcesBtn, 1);
    mMenuLayout->addWidget(mSettingsBtn, 1);

    mMenuLayout->addWidget(mDonateBtn);

    mMenuWidget->setLayout(mMenuLayout);

    // Tab Widget
    mTabLayout->addWidget(mDashboardDisplay);
    mTabLayout->addWidget(mPortfolioDisplay);
    mTabLayout->addWidget(mBudgettingDisplay);
    mTabLayout->addWidget(mTickerDisplay);
    mTabLayout->addWidget(mResourcesDisplay);
    mTabLayout->addWidget(mSettingsDisplay);

    mTabWidget->setLayout(mTabLayout);

    // Main Widget
    mMainLayout->addWidget(mMenuWidget);
    mMainLayout->addWidget(mTabWidget);

    mMainWidget->setLayout(mMainLayout);

    setCentralWidget(mMainWidget);
}


void MainWindow::selectMenuButton(void)
{
    QPushButton * button = qobject_cast<QPushButton *>(sender());

    int ofst = 1;

    mSelectedOption->setProperty("selected", "false");
    button->setProperty("selected", "true");

    style()->unpolish(mSelectedOption);
    style()->unpolish(button);
    style()->polish(mSelectedOption);
    style()->polish(button);

    mSelectedOption = button;
    mTabLayout->setCurrentIndex(mMenuLayout->indexOf(button) - ofst);
}


/*
void MainWindow::createCentral(void)
{
    mainWidget      = new QWidget();
    mainLayout      = new QStackedLayout();

    mTickerDisplay  = new TickerDisplay();

    QPushButton * button = new QPushButton(tr("FinEarn"));

    QPixmap pixmap(":/img/logo.jpg");
    QIcon ButtonIcon(pixmap);
    button->setIcon(ButtonIcon);
    button->setIconSize(pixmap.rect().size());

    mainLayout->addWidget(button);
    //mainLayout->addWidget(mTickerDisplay);

    mainWidget->setLayout(mainLayout);

    setCentralWidget(mainWidget);
}
*/
