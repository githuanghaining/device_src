#ifndef __UTILS_H__
#define __UTILS_H__

int decompress_jpeg_from_file(const char* file, char** data, size_t* size, int* width, int* height);
int compress_rgb_to_jpeg_file(const char* file, char* rgb, int width, int height);
int decompress_jpeg_from_buffer(char* src, size_t src_size, char** data, size_t* size, int* width, int* height);
int compress_rgb_to_jpeg_buffer(char** dst, size_t* dst_size, char* rgb, int width, int height);
int resize_rgb_nearest(char* src_data, int src_width, int src_height, char** dst_ptr, size_t* dst_size, int dst_width, int dst_height);
int resize_rgb_double_linear(char* src_data, int src_width, int src_height, char** dst_ptr, size_t* dst_size, int dst_width, int dst_height);

#endif //__UTILS_H__
