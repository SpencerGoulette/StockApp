#ifndef TICKERINFOVIEW_H
#define TICKERINFOVIEW_H

#include <QtCharts>
#include <QLabel>

class TickerInfoView : public QWidget
{
    Q_OBJECT

public:
    TickerInfoView(QWidget *parent = 0);
    ~TickerInfoView();

    void updateTickerInfo(QString open, QString high, QString low, QString mktcap,
                          QString peratio, QString divyield, QString wkhigh, QString wklow);

private:
    void setup(void);

    void createGUI(void);

    QLabel * mOpenLbl;
    QLabel * mHighLbl;
    QLabel * mLowLbl;
    QLabel * mMktCapLbl;
    QLabel * mPERatio;
    QLabel * mDivYield;
    QLabel * m52WkHigh;
    QLabel * m52WkLow;

};

#endif // TICKERINFO_H
