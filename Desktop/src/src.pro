#-------------------------------------------------
#
# Project created by QtCreator 2022-08-02T00:44:08
#
#-------------------------------------------------

QT       += core gui widgets charts

TARGET   = EarlyInvestor
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11 no_keywords

SOURCES += \
    main.cpp \
    GUI/mainwindow.cpp \
    APIs/yfapi.cpp \
    GUI/Tickers/tickerchartview.cpp \
    GUI/Tickers/tickerinfoview.cpp \
    GUI/Tickers/tickerselectorview.cpp \
    GUI/Tickers/tickerdisplay.cpp \
    GUI/Tickers/tickeritem.cpp \
    GUI/Dashboard/dashboarddisplay.cpp \
    GUI/Portfolios/portfoliodisplay.cpp \
    GUI/Budgetting/budgettingdisplay.cpp \
    GUI/Resources/resourcesdisplay.cpp \
    GUI/Settings/settingsdisplay.cpp

HEADERS += \
    mainwindow.h \
    APIs/yfapi.hpp \
    GUI/Tickers/tickerinfoview.hpp \
    GUI/Tickers/tickerselectorview.hpp \
    GUI/Tickers/tickerdisplay.hpp \
    GUI/Tickers/tickerchartview.hpp \
    GUI/Tickers/tickeritem.hpp \
    GUI/Tickers/tickerlist.hpp \
    GUI/Dashboard/dashboarddisplay.hpp \
    GUI/Portfolios/portfoliodisplay.hpp \
    GUI/Budgetting/budgettingdisplay.hpp \
    GUI/Resources/resourcesdisplay.hpp \
    GUI/Settings/settingsdisplay.hpp

LIBS += -L/tmp/curl/lib -lcurl

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Extras/resources.qrc
