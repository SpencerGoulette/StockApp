#include "yfapi.hpp"

YahooFinanceAPI::YahooFinanceAPI()
{
    mBaseURL = "https://query1.finance.yahoo.com/v7/finance/download/{ticker}?period1={start_time}&period2={end_time}&interval={interval}&events=history";
}


YahooFinanceAPI::~YahooFinanceAPI()
{
    clearTickers();
}


QMap<QString, QStringList> YahooFinanceAPI::GetTickerData(QString ticker, QString start, QString end, QString interval)
{
    // Download Ticker Data Into File
    QString filename = downloadTickerData(ticker, start, end, interval);

    // Open File
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly))
    {
        std::cout << "Error: " << filename.toStdString() << " failed to open!" << std::endl;
        return QMap<QString, QStringList>();
    }

    std::cout << "Downloaded File" << std::endl;

    // Read File
    // Headers
    QMap<QString, QStringList> tmpMap;
    QStringList headers;
    QByteArray line = file.readLine();
    QString tmpStr = QString(line.toStdString().c_str());
    headers.append(tmpStr.split(","));

    for(int header = 0; header < headers.size(); header++)
        tmpMap[headers.at(header)] = QStringList();
    mDataMap[ticker] = tmpMap;

    // Data
    unsigned long i = 0;
    while (!file.atEnd())
    {
        i++;
        QStringList dataList;
        line = file.readLine();
        tmpStr = QString(line.toStdString().c_str());
        dataList.append(tmpStr.split(","));
        std::cout << i << std::endl;
        for (int header = 0; header < headers.size(); header++)
            mDataMap[ticker][headers.at(header)].append(dataList.at(header));
    }

    std::cout << "Read File" << std::endl;

    //clearTickers();

    return mDataMap[ticker];
}


QString YahooFinanceAPI::downloadTickerData(QString ticker, QString start, QString end, QString interval)
{
    // Create url
    QString url = buildURL(ticker, start, end, interval);

    std::time_t now = std::time(nullptr);
    QString filename = QString("%1_%2.csv").arg(ticker).arg(std::to_string(now).c_str());

    filename = downloadFile(url, filename);

    return filename;
}


void YahooFinanceAPI::removeTicker(QString filename)
{
    // Delete File
    if(remove(filename.toStdString().c_str()))
    {
        std::cout << "Error: " << filename.toStdString() << " failed to be deleted!" << std::endl;
        return;
    }

    // Remove From List
    mTickers.removeAll(filename);
}


void YahooFinanceAPI::clearTickers(void)
{
    for (int fileNum = mTickers.size(); fileNum >= 0; fileNum++)
        removeTicker(mTickers.at(fileNum));
}


QString YahooFinanceAPI::buildURL(QString ticker, QString start, QString end, QString interval)
{
    // Build String
    QString buildURL = mBaseURL;
    buildURL.replace("{ticker}", ticker);
    buildURL.replace("{start_time}", start);
    buildURL.replace("{end_time}", end);
    buildURL.replace("{interval}", interval);
    return buildURL;
}


QString YahooFinanceAPI::downloadFile(QString url, QString filename)
{
    // Initialize
    CURL *curl;
    FILE *fp;
    CURLcode res;

    curl = curl_easy_init();

    // Download File
    if (curl)
    {
        fp = fopen(filename.toStdString().c_str(), "wb");
        curl_easy_setopt(curl, CURLOPT_URL, url.toStdString().c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, NULL);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
        res = curl_easy_perform(curl);

        // Cleanup
        curl_easy_cleanup(curl);
        fclose(fp);
    }

    mTickers.append(filename);

    return filename;
}
