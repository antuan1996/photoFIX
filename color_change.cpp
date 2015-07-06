#include "color_change.h"

color_change::color_change(int w, int h, int len)
{
  width = w;
  height = h;
  pointSize = len;
  src_matrix = 0;
  dst_matrix = 0;
}

color_change::~color_change()
{
  if(src_matrix != 0) free(src_matrix);
  if(dst_matrix != 0) free(dst_matrix);
}
void color_change::clearMem(){
  if(src_matrix != 0) free(src_matrix);
  if(dst_matrix != 0) free(dst_matrix);
  src_matrix = 0;
  dst_matrix = 0;
}
void color_change::RGB24toYUVplanar(){
  const int len = 3;
  dstSize = width*height*len;
  dst_matrix = (u_int8_t *) malloc(dstSize);
  if(src_matrix != 0)
    RGB24toYUVplanar_engine(width, height, src_matrix, dst_matrix);
}
void color_change::YUVplanartoRGB24(){
  const int len = 3;
  dstSize = width*height*len;
  dst_matrix = (u_int8_t *) malloc(dstSize);
  if(src_matrix != 0)
    YUVplanartoRGB24_engine(width, height, src_matrix, dst_matrix);
}
bool color_change::loadFile(char * src_file){
  FILE * f1 = fopen(src_file,"rb");
  if(f1 == 0) return false;
  src_matrix = (u_int8_t *)malloc(width*height*pointSize);
  fread(src_matrix, pointSize, width*height,f1);
  fclose(f1);
  return true;
}
bool color_change::writeFile(char * dst_file){
  FILE * f1 = fopen(dst_file,"wb");
  if(f1 == 0 || dst_matrix == 0) return false;
  fwrite(dst_matrix, 1, dstSize,f1);
  fclose(f1);
  return true;
}
void color_change::loadMemory(u_int8_t *mem_pos){
  src_matrix = (u_int8_t *)malloc(width*height*pointSize);
  memcpy(src_matrix, mem_pos,width*height*pointSize);
}
void color_change::writeMemory(u_int8_t *mem_pos){
  memcpy( mem_pos,dst_matrix, dstSize);
}
void color_change::RGB24toYUVplanar_engine(int w, int h, u_int8_t *src, u_int8_t *dst){
  const int len = 3;

  const int YKR = 66;
  const int YKG = 129;
  const int YKB = 25;

  const int VKR = 112;
  const int VKG = -94;
  const int VKB = -18;

  const int UKR = -38;
  const int UKG = -74;
  const int UKB = 112;

  const int shift = 8;
  u_int8_t * y = dst;
  u_int8_t * u = dst + w*h;
  u_int8_t * v = dst + w*h + w*h ;
  for(int i = 0; i < h; ++i)
    for(int j = 0; j < w; ++j){
      u_int32_t r = src[(i*w + j)*len +0];
      u_int32_t g = src[(i*w + j)*len +1];
      u_int32_t b = src[(i*w + j)*len +2];
      u_int32_t cury = ((r*YKR + g*YKG + b*YKB) >> shift) + 16;
      u_int32_t curu = ((r*UKR + g*UKG + b*UKB) >> shift) + 128;
      u_int32_t curv = ((r*VKR + g*VKG + b*VKB) >> shift) + 128;
      //cury = max(0,min(255, cury));
      //curu = max(0,min(255, curu));
      //curv = max(0,min(255, curv));
      y[i*w + j] = cury;
      u[i*w + j] = curu;
      v[i*w + j] = curv;
    }
}
void color_change::fix_contrast(){
    dstSize = width*height*3;
    dst_matrix = (u_int8_t*)(malloc(dstSize));
    fix_contrast_engine(src_matrix, dst_matrix , width, height);
}

void color_change::fix_contrast_engine(u_int8_t *src, u_int8_t *dst,int w, int h){
 int low = 256 ,high = -1;
    for(int i = 0; i < h; ++i)
        for(int j = 0; j < w; ++j){
            int cur = src[i * w + j];
            low = min(low, cur);
            high = max(high, cur);
        }
    int range = high -  low + 1;
    for(int i = 0; i < h; ++i)
        for(int j = 0; j < w; ++j){
            u_int8_t cur = src[i * w + j];
            cur = 1. * (cur - low) / range *  256;
            dst[i * w + j] = cur;
        }
}
void color_change::YUVplanartoRGB24_engine(int w, int h,u_int8_t *src, u_int8_t *dst){
  const int len = 3;

const int RKY = 298; // Koeff of  Y for red  processing
const int RKU = 0;		//  Koeff of  U for red processing
const int RKV = 409;	//  Koeff of 	V for red processing

const int GKY = 298; // Koeff of Y for green processing
const int GKU = -100; // Koeff of U for green processing
const int GKV = -208;// Koeff of V for green processing

const int BKY = 298;// Koeff of Y for blue processing
const int BKU = 516;// Koeff of U for blue processing
const int BKV = 0;// Koeff of V for blue processing

  const int shift = 8;
  u_int8_t * chy = src;
  u_int8_t * chu = src + w*h;
  u_int8_t * chv = src + w*h + w*h ;
  for(int i = 0; i < h; ++i)
    for(int j = 0; j < w; ++j){
      int32_t y = chy[(i*w + j)];
      int32_t u = chu[(i*w + j)];
      int32_t v = chv[(i*w + j)];
      y -= 16;
      u -= 128;
      v -= 128;
      int curr = (y*RKY + u*RKU + v*RKV) >> shift;
      int curg = (y*GKY + u*GKU + v*GKV) >> shift;
      int curb = (y*BKY + u*BKU + v*BKV) >> shift;
      curr = max(0,min(255, curr));
      curg = max(0,min(255, curg));
      curb = max(0,min(255, curb));
      dst[(i*w + j)*len + 0] = curr;
      dst[(i*w + j)*len + 1] = curg;
      dst[(i*w + j)*len + 2] = curb;
    }
}
