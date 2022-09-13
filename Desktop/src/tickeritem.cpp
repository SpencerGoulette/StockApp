#include "tickeritem.hpp"

#include <QGridLayout>
#include <QString>

TickerItem::TickerItem(QWidget *parent)
        : QWidget(parent)
{
    setup();
}


TickerItem::TickerItem(QString ticker) : mTicker(ticker)
{
    setup();
}


TickerItem::~TickerItem()
{

}



void TickerItem::setup(void)
{
    createGUI();

    connect(mRemoveButton, SIGNAL(clicked()), this, SIGNAL(tickerRemoved()));

    setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Minimum);
}


void TickerItem::createGUI(void)
{
    mTickerLbl = new QLabel(mTicker);
    mRemoveButton = new QPushButton("-");

    QHBoxLayout * mainLayout = new QHBoxLayout();

    mainLayout->addWidget(mTickerLbl);
    mainLayout->addWidget(mRemoveButton);

    setLayout(mainLayout);
}


void TickerItem::mousePressEvent(QMouseEvent *event)
{
    Q_UNUSED(event);

    Q_EMIT tickerClicked(mTicker);

    QWidget::mousePressEvent(event);
}
