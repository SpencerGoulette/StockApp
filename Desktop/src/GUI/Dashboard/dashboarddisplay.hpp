#ifndef DASHBOARDDISPLAY_H
#define DASHBOARDDISPLAY_H

#include <QWidget>

class DashboardDisplay : public QWidget
{
    Q_OBJECT

public:
    DashboardDisplay(QWidget *parent = 0);
    ~DashboardDisplay();

private:
    void setup(void);

    void createGUI(void);
};

#endif // DASHBOARDDISPLAY_H
