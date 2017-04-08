#ifndef FRONTPANEL_H
#define FRONTPANEL_H

#include <QMainWindow>

namespace Ui {
class FrontPanel;
}

class FrontPanel : public QMainWindow
{
    Q_OBJECT

public:
    explicit FrontPanel(QWidget *parent = 0);
    ~FrontPanel();

private:
    Ui::FrontPanel *ui;
};

#endif // FRONTPANEL_H
