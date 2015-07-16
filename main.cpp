#include "addon.h"
#include <QApplication>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    getfileList((a.applicationDirPath().toStdString().c_str()));
    qDebug() << "finish-it";
    return 0;
    //return a.exec();
}
