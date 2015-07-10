#include "addon.h"
void picture_cycle(const char * src_name){
    ImageFix myFix;

    myFix.readFile(src_name);
    color_change mychanger(myFix.width,myFix.height,myFix.depth/8);

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

    QString dst_name = src_name;
    dst_name = "resultX"+dst_name;
    myFix.writeFile(dst_name.toStdString().c_str());
}
void getfileList(const char *path){
    QDir mydir(path);
    mydir.setFilter(QDir::Files);
    QStringList filters;
    filters << "*.jpg";
    mydir.setNameFilters(filters);
    QStringList namelist = mydir.entryList();
    foreach (QString curs, namelist) {
       picture_cycle(curs.toStdString().c_str());
    }
    return ;
}
