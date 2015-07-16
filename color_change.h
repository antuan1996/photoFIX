#ifndef COLOR_CHANGE_H
#define COLOR_CHANGE_H
#include <algorithm>
#include <iostream>
#include <string>
#include <cmath>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <QDebug>
using namespace std;
class color_change
{
  public:
    color_change(int w, int h, int len);
    virtual ~color_change();
    bool loadFile(char *);
    void loadMemory(u_int8_t *);
    bool writeFile(char *);
    void writeMemory(u_int8_t *);
    void RGB24toYUVplanar();
    void RGB24toRGBplanar();
    void RGBplanartoRGB24();
    void YUVplanartoRGB24();
    void fix_contrast();
    void fix_light();
    void clearMem();
  protected:
    int pointSize;
    int dstSize;
    int width;
    int height;
    u_int8_t * src_matrix;
    u_int8_t * dst_matrix;
    void fix_contrast_engine(u_int8_t *src, u_int8_t *dst, int w , int h);
    void fix_light_engine(u_int8_t *src, u_int8_t *dst,int w, int h);
    void RGB24toYUVplanar_engine(int w, int h, u_int8_t* src, u_int8_t* dst);
    void RGB24toRGBplanar_engine(int w, int h, u_int8_t* src, u_int8_t* dst);
    void RGBplanartoRGB24_engine(int w, int h, u_int8_t* src, u_int8_t* dst);
    void YUVplanartoRGB24_engine(int w, int h, u_int8_t* src, u_int8_t* dst);
  private:
};

#endif // COLOR_CHANGE_H
