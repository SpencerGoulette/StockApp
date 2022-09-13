#ifndef SETTINGSDISPLAY_H
#define SETTINGSDISPLAY_H

#include <QWidget>

class SettingsDisplay : public QWidget
{
    Q_OBJECT

public:
    SettingsDisplay(QWidget *parent = 0);
    ~SettingsDisplay();

private:
    void setup(void);

    void createGUI(void);
};

#endif // SETTINGSDISPLAY_H
