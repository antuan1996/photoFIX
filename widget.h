#ifndef WIDGET_H
#define WIDGET_H
#include <QImage>
#include <cstdint>
#include <cstdio>
class ImageFix
{

public:
    ImageFix();
    ~ImageFix();
    void readFile(char *);
    void writeFile(char *);
    u_int8_t * pixmap;
    int width;
    int height;
};

#endif // WIDGET_H
