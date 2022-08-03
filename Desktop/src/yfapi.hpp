#include <string.h>
#include <curl/curl.h>
#include <ctime>
#include <iomanip>
#include <sstream>
#include <iostream>
#include <stdio.h>

#include <QFile>
#include <QStringList>
#include <QMap>
#include <QVariant>
#include <QDateTime>

class YahooFinanceAPI
{
    public:
        YahooFinanceAPI();
        ~YahooFinanceAPI();

        QMap<QString, QStringList> GetTickerData(QString ticker, QString start, QString end, QString interval = "1d");
        QString downloadTickerData(QString ticker, QString start, QString end, QString interval = "1d");

        void    removeTicker(QString filename);
        void    clearTickers(void);

    private:
        QString buildURL(QString ticker, QString start, QString end, QString interval = "1d");
        QString downloadFile(QString url, QString filename);

        QString mBaseURL;
        QStringList mTickers;

        // Storage for data
        QMap<QString, QMap<QString, QStringList>> mDataMap;
};
