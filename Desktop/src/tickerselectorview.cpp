#include "tickerselectorview.hpp"

TickerSelectorView::TickerSelectorView(QWidget *parent)
    : QWidget(parent)
{
    setup();
}


TickerSelectorView::~TickerSelectorView()
{

}



void TickerSelectorView::setup(void)
{
    createGUI();

    loadSettings();
    loadRecommendations();

    connect(mTickerAdder, SIGNAL(clicked()), this, SLOT(addTicker()));
    connect(mTickerSelector, SIGNAL(returnPressed()), this, SLOT(addTicker()));
}


void TickerSelectorView::createGUI(void)
{
    mTickerSelector     = new QLineEdit();
    mTickerAdder        = new QPushButton();
    mTickerScrollArea   = new QScrollArea();
    mTickerListLayout   = new QVBoxLayout();

    QWidget * selectorWidget        = new QWidget();
    QVBoxLayout * mainLayout        = new QVBoxLayout();
    QHBoxLayout * selectorLayout    = new QHBoxLayout();

    selectorLayout->addWidget(mTickerSelector);
    selectorLayout->addWidget(mTickerAdder);

    selectorWidget->setLayout(selectorLayout);

    QFrame * scrollWidget = new QFrame();

    scrollWidget->setLayout(mTickerListLayout);

    mTickerScrollArea->setWidgetResizable(true);
    mTickerScrollArea->setWidget(scrollWidget);
    mTickerScrollArea->show();

    mainLayout->addWidget(selectorWidget);
    mainLayout->addWidget(mTickerScrollArea);

    setLayout(mainLayout);
    setMaximumWidth(sizeHint().width());
}


void TickerSelectorView::loadSettings(void)
{

}


void TickerSelectorView::loadRecommendations(void)
{

}


void TickerSelectorView::addTicker(void)
{
    TickerItem * tickerItem = new TickerItem(mTickerSelector->text());
    mTickers.append(tickerItem);
    mTickerListLayout->addWidget(tickerItem, 0, Qt::AlignTop);

    connect(tickerItem, SIGNAL(tickerClicked(QString)), this, SIGNAL(tickerSelected(QString)));
    connect(tickerItem, SIGNAL(tickerRemoved()), this, SLOT(removeTicker()));

    tickerItem->show();
}


void TickerSelectorView::removeTicker(void)
{
    TickerItem * tickerItem = qobject_cast<TickerItem *>(sender());
    mTickers.removeAll(tickerItem);
    mTickerListLayout->removeWidget(tickerItem);
    delete tickerItem;

    mTickerScrollArea->update();
}

