#ifndef TICKERSELECTORVIEW_H
#define TICKERSELECTORVIEW_H

#include "tickeritem.hpp"

#include <QWidget>
#include <QtCharts>
#include <QLineEdit>
#include <QPushButton>
#include <QString>
#include <QList>

class TickerSelectorView : public QWidget
{
    Q_OBJECT

public:
    TickerSelectorView(QWidget *parent = 0);
    ~TickerSelectorView();

Q_SIGNALS:
    void tickerSelected(QString ticker);

public Q_SLOTS:
    void addTicker(void);
    void removeTicker(void);

private:
    void setup(void);

    void createGUI(void);
    void loadSettings(void);
    void loadRecommendations(void);

    QLineEdit *     mTickerSelector;
    QPushButton *   mTickerAdder;
    QScrollArea *   mTickerScrollArea;
    QVBoxLayout *   mTickerListLayout;

    QList<TickerItem *> mTickers;
    QList<TickerItem *> mRecommendations;

};

#endif // TICKERSELECTOR_H
