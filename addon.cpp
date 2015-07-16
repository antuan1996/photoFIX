#include "addon.h"
std::mutex mbef;
void picture_cycle(const char * src_name){

    //mbef.lock();
    std::cout << "step 1"<<std::endl;
    ImageFix myFix;
    std::cout<< src_name<<endl;
    //std::cout<< src_name2<<endl;
    myFix.readFile(src_name);
    color_change mychanger(myFix.width,myFix.height,myFix.depth/8);
    //mbef.unlock();

    //mbef.lock();
    std::cout << "step 2"<<std::endl;
    mychanger.loadMemory(myFix.pixmap);
    mychanger.RGB24toYUVplanar();
    mychanger.writeMemory(myFix.pixmap);
    //mychanger.writeFile("result.yuv");
    mychanger.clearMem();
    mbef.unlock();

    std::cout << "step 2.5"<<std::endl;
    mychanger.loadMemory(myFix.pixmap);
    mychanger.fix_light();
    mychanger.writeMemory(myFix.pixmap);
    //mychanger.writeFile("result.rgb");
    mychanger.clearMem();


    // mbef.lock();
    std::cout << "step 3"<<std::endl;
    mychanger.loadMemory(myFix.pixmap);
    mychanger.fix_contrast();
    mychanger.writeMemory(myFix.pixmap);
    //mychanger.writeFile("result.rgb");
    mychanger.clearMem();
    //mbef.unlock();

    //mbef.lock();
    std::cout << "step 4"<<std::endl;
    mychanger.loadMemory(myFix.pixmap);
    mychanger.YUVplanartoRGB24();
    mychanger.writeMemory(myFix.pixmap);
    mychanger.clearMem();
    //mbef.unlock();

    //mbef.lock();
    std::cout << "step 5" <<std::endl;
    //std::cout <<src_name1<<endl;
    //std::cout <<src_name2<<endl;

    QString dst_name = src_name;
    dst_name = dst_name.insert(dst_name.size()-3-1,"res");
    //dst_name = "resultX"+dst_name;
    myFix.writeFile(dst_name.toStdString().c_str());
    //mbef.unlock();
}

void getfileList(const char *path){
    QDir mydir(path);
    mydir.setFilter(QDir::Files);
    QStringList filters;
    filters << "*.jpg";
    mydir.setNameFilters(filters);
    QStringList namelist = mydir.entryList();
    std::cout <<namelist.count()<<"count\n";
    int i;
    for(i=0; i+1 < namelist.count() ;i+=2) {
        std::cout << i<< endl;
        std::string src_name1 = namelist.at(i).toStdString();
        std::string src_name2 = namelist.at(i+1).toStdString();
        //std::cout << namelist.at(i).toStdString().c_str() <<" " <<namelist.at(i+1).toStdString().c_str()<<std::endl;
        //std::cout << src_name1 << " " << src_name2 << std::endl;
        std::thread pic_thread1(picture_cycle,src_name1.c_str());
        std::thread pic_thread2(picture_cycle,src_name2.c_str());
        pic_thread1.join();
        pic_thread2.join();
    }
    std :: string lastr = namelist.at(namelist.size()-1).toStdString().c_str();
    if(i == namelist.size()-1) picture_cycle(lastr.c_str());
    return ;
}
