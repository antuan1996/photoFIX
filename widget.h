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
    void readFile(const char *);
    void writeFile(const char *);
    u_int8_t * pixmap;
    int width;
    int height;
    int depth;
};

#endif // WIDGET_H
