#ifndef TICKERITEM_H
#define TICKERITEM_H

#include <QtCharts>
#include <QLabel>

class TickerItem : public QWidget
{
    Q_OBJECT

public:
    TickerItem(QWidget *parent = 0);
    TickerItem(QString ticker);
    ~TickerItem();

    virtual void mousePressEvent(QMouseEvent *event) override;

Q_SIGNALS:
    void tickerClicked(QString ticker);
    void tickerRemoved(void);

private:
    void setup(void);

    void createGUI(void);

    QPushButton *   mRemoveButton;
    QLabel *        mTickerLbl;
    QString         mTicker;
};

#endif // TICKERITEM_H
