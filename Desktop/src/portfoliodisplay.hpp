#ifndef PORTFOLIODISPLAY_H
#define PORTFOLIODISPLAY_H

#include <QWidget>

class PortfolioDisplay : public QWidget
{
    Q_OBJECT

public:
    PortfolioDisplay(QWidget *parent = 0);
    ~PortfolioDisplay();

private:
    void setup(void);

    void createGUI(void);
};

#endif // PORTFOLIODISPLAY_H
