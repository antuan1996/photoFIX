#include "widget.h"

ImageFix::ImageFix()
{
    pixmap = 0;
}

ImageFix::~ImageFix()
{

}
void ImageFix::readFile(const char *file_name){
    QImage checkimage;
    checkimage.load(QString(file_name));
    checkimage = checkimage.convertToFormat(QImage::Format_RGB888);
    //checkimage = checkimage.scaledToWidth(640);
    //checkimage = checkimage.scaledToHeight(480);
    width = checkimage.width();
    height = checkimage.height();
    depth = checkimage.depth();
    if(pixmap != 0) free(pixmap);
    pixmap = (u_int8_t *)malloc(width*height*3);
    int line_len = checkimage.bytesPerLine();
    for(int i = 0 ; i< height; ++i){
        u_int8_t * line = checkimage.scanLine(i);
        memcpy(pixmap+i*line_len,line,line_len);
    }

}
void ImageFix::writeFile(const char *file_name){
    QImage checkimage(pixmap,width,height,QImage::Format_RGB888);
    checkimage.save(QString(file_name));

}
