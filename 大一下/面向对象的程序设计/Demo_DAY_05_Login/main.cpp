#include "loginwindow.h"

#include <QApplication>
#include <QDesktopWidget>

int main(int argc, char *argv[])
{
    qputenv("QT_MAC_WANTS_LAYER", "1");
    QApplication a(argc, argv);
    LoginWindow w;
    w.show();
    w.move((QApplication::desktop()->width() - w.width())/2,
           (QApplication::desktop()->height() - w.height())/2);
    return a.exec();
}
