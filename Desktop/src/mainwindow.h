#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedLayout>

#include "dashboarddisplay.hpp"
#include "portfoliodisplay.hpp"
#include "budgettingdisplay.hpp"
#include "tickerdisplay.hpp"
#include "resourcesdisplay.hpp"
#include "settingsdisplay.hpp"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    void setup(void);
    void createLayout(void);
    void selectMenuButton(void);

    // Main Layout Widgets
    QWidget *           mMainWidget;
    QWidget *           mMenuWidget;
    QWidget *           mTabWidget;

    // Main Layouts
    QHBoxLayout *       mMainLayout;
    QVBoxLayout *       mMenuLayout;
    QStackedLayout *    mTabLayout;

    // Logo
    QLabel *            mLogo;
    QLabel *            mLogoLbl;

    // Menu Options
    QPushButton *       mDashboardBtn;
    QPushButton *       mPortfoliosBtn;
    QPushButton *       mBudgettingBtn;
    QPushButton *       mTickersBtn;
    QPushButton *       mResourcesBtn;
    QPushButton *       mSettingsBtn;

    // Displays
    DashboardDisplay *  mDashboardDisplay;
    PortfolioDisplay *  mPortfolioDisplay;
    BudgettingDisplay * mBudgettingDisplay;
    TickerDisplay *     mTickerDisplay;
    ResourcesDisplay *  mResourcesDisplay;
    SettingsDisplay *   mSettingsDisplay;

    // Donate
    QWidget *           mDonateWidget;
    QPushButton *       mDonateBtn;


    // Record Current Menu Selection
    QPushButton *       mSelectedOption;
};

#endif // MAINWINDOW_H
