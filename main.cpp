
#include "frontpanel.h"
#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    FrontPanel w;

    w.show();

    w.updateValue();




    return a.exec();
}
