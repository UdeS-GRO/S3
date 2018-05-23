#include "yourmainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    YourMainWindow w;
    w.show();
    return a.exec();

}
