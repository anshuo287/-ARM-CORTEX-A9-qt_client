#include "log_reg.h"

#include <QApplication>
#include <QFile>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QFile file(":/rsc/style.qss");
    file.open(QIODevice::ReadOnly);
    a.setStyleSheet(file.readAll());
    file.close();

    log_reg w;
    w.show();
    return a.exec();
}
