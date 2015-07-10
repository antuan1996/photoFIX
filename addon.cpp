#include "addon.h"
void getfileList(const char *path){
    QDir mydir(path);
    mydir.setFilter(QDir::Files);
    QStringList filters;
    filters << "*.jpg";
    mydir.setNameFilters(filters);
    QStringList namelist = mydir.entryList();
    foreach (QString curs, namelist) {
        qDebug() << curs;
    }
    return ;
}
