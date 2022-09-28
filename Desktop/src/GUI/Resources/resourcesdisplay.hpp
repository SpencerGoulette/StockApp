#ifndef RESOURCESDISPLAY_H
#define RESOURCESDISPLAY_H

#include <QWidget>

class ResourcesDisplay : public QWidget
{
    Q_OBJECT

public:
    ResourcesDisplay(QWidget *parent = 0);
    ~ResourcesDisplay();

private:
    void setup(void);

    void createGUI(void);
};

#endif // RESOURCESDISPLAY_H
