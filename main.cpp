#include "widget.h"
#include "color_change.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ImageFix myFix;
    myFix.readFile("photo.jpg");
    color_change mychanger(myFix.width,myFix.height,3);
    mychanger.loadMemory(myFix.pixmap);

    mychanger.RGB24toYUVplanar();
    mychanger.writeMemory(myFix.pixmap);
    //mychanger.writeFile("result.yuv");
    mychanger.clearMem();

    mychanger.loadMemory(myFix.pixmap);
    mychanger.fix_contrast();
    mychanger.writeMemory(myFix.pixmap);
    mychanger.clearMem();

    mychanger.loadMemory(myFix.pixmap);
    mychanger.YUVplanartoRGB24();
    mychanger.writeMemory(myFix.pixmap);
    mychanger.clearMem();


    myFix.writeFile("result.jpg");
    return a.exec();
}
