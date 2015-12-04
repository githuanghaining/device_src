#ifndef __IMGZA_H__
#define __IMGZA_H__
#include <stdio.h>

//最临近元法
int rgb_resize_nearest(unsigned char* src_data, int src_width, int src_height, unsigned char** dst_ptr, size_t* dst_size, int dst_width, int dst_height);
//双线性内插法
int rgb_resize_double_linear(unsigned char* src_data, int src_width, int src_height, unsigned char** dst_ptr, size_t* dst_size, int dst_width, int dst_height);
//三次卷积插值法
int rgb_resize_three_convolution(unsigned char* src_data, int src_width, int src_height, unsigned char** dst_ptr, size_t* dst_size, int dst_width, int dst_height);
////////////////////////////////////////////////////////////////////////////////
/**
 * Resizes the image. mode can be 0 for slow (bilinear) method ,
 * 1 for fast (nearest pixel) method, or 2 for accurate (bicubic spline interpolation) method.
 * The function is faster with 24 and 1 bpp images, slow for 4 bpp images and slowest for 8 bpp images.
 */
int rgb_resample(unsigned char* src, int x, int y, unsigned char** dst, size_t* dstsize, int newx, int newy, int mode);

#endif //__IMGZA_H__
