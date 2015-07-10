#include "widget.h"
#include "color_change.h"
#include "addon.h"
#include <QDebug>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //qDebug() << a.applicationDirPath();
    getfileList((a.applicationDirPath().toStdString().c_str()));

    for(int i=0; i<100; ++i){
    ImageFix myFix;
    myFix.readFile("photo.jpg");
    color_change mychanger(myFix.width,myFix.height,3);
    mychanger.loadMemory(myFix.pixmap);

    mychanger.RGB24toYUVplanar();
    mychanger.writeMemory(myFix.pixmap);
    //mychanger.writeFile("result.yuv");
    mychanger.clearMem();

     /*
    mychanger.loadMemory(myFix.pixmap);
    mychanger.fix_contrast();
    mychanger.writeMemory(myFix.pixmap);
    mychanger.clearMem();
    */
    mychanger.loadMemory(myFix.pixmap);
    mychanger.YUVplanartoRGB24();
    mychanger.writeMemory(myFix.pixmap);
    mychanger.clearMem();


    myFix.writeFile("photo.jpg");
    }
    qDebug() << "finish";
    return a.exec();
}
