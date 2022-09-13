#ifndef BUDGETTINGDISPLAY_H
#define BUDGETTINGDISPLAY_H

#include <QWidget>

class BudgettingDisplay : public QWidget
{
    Q_OBJECT

public:
    BudgettingDisplay(QWidget *parent = 0);
    ~BudgettingDisplay();

private:
    void setup(void);

    void createGUI(void);
};

#endif // BUDGETTINGDISPLAY_H
