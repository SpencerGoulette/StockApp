#include "tickerinfoview.hpp"

#include <QGridLayout>
#include <QString>

TickerInfoView::TickerInfoView(QWidget *parent)
    : QWidget(parent)
{
    setup();
}


TickerInfoView::~TickerInfoView()
{

}



void TickerInfoView::setup(void)
{
    createGUI();
}


void TickerInfoView::createGUI(void)
{
    QGridLayout * mainLayout = new QGridLayout();

    mOpenLbl    = new QLabel("Open          ");
    mHighLbl    = new QLabel("High          ");
    mLowLbl     = new QLabel("Low           ");
    mMktCapLbl  = new QLabel("Mkt Cap       ");
    mPERatio    = new QLabel("P/E Ratio     ");
    mDivYield   = new QLabel("Div Yield     ");
    m52WkHigh   = new QLabel("52-Wk High    ");
    m52WkLow    = new QLabel("52-Wk Low     ");

    mainLayout->addWidget(mOpenLbl,   0, 0, 1, 1, Qt::AlignLeft);
    mainLayout->addWidget(mHighLbl,   1, 0, 1, 1, Qt::AlignLeft);
    mainLayout->addWidget(mLowLbl,    2, 0, 1, 1, Qt::AlignLeft);
    mainLayout->addWidget(mMktCapLbl, 0, 1, 1, 1, Qt::AlignLeft);
    mainLayout->addWidget(mPERatio,   1, 1, 1, 1, Qt::AlignLeft);
    mainLayout->addWidget(mDivYield,  2, 1, 1, 1, Qt::AlignLeft);
    mainLayout->addWidget(m52WkHigh,  0, 2, 1, 1, Qt::AlignLeft);
    mainLayout->addWidget(m52WkLow,   1, 2, 1, 1, Qt::AlignLeft);

    setLayout(mainLayout);
}


void TickerInfoView::updateTickerInfo(QString open, QString high, QString low, QString mktcap,
                                  QString peratio, QString divyield, QString wkhigh, QString wklow)
{
    mOpenLbl->setText(mOpenLbl->text().append(open));
    mHighLbl->setText(mHighLbl->text().append(high));
    mLowLbl->setText(mLowLbl->text().append(low));
    mMktCapLbl->setText(mMktCapLbl->text().append(mktcap));
    mPERatio->setText(mPERatio->text().append(peratio));
    mDivYield->setText(mDivYield->text().append(divyield));
    m52WkHigh->setText(m52WkHigh->text().append(wkhigh));
    m52WkLow->setText(m52WkLow->text().append(wklow));
}
