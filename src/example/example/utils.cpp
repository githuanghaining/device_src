// utils.cpp
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "jpeg/jpeglib.h"

int decompress_jpeg_from_file(const char* file, char** data, size_t* size, int* width, int* height)
{
	FILE* fp;
	struct jpeg_error_mgr jerr;
	struct jpeg_decompress_struct cinfo;
	int imgwidth;
	int imgheight;
	int rowsize;
	int rgbsize;
	char* rgb;
	JSAMPROW rowptr[1];

	fp = fopen(file, "rb");
	if (fp == NULL)
	{
		fprintf(stderr, "Can't open file '%s' for reading: %d\n", file, errno);
		return -1;
	}

	cinfo.err = jpeg_std_error(&jerr);
	jpeg_create_decompress(&cinfo);
	jpeg_stdio_src(&cinfo, fp);
	jpeg_read_header(&cinfo, (boolean)1);

	imgwidth = cinfo.image_width;
	imgheight = cinfo.image_height;

	rowsize = imgwidth*cinfo.num_components;
	rgbsize = rowsize*imgheight;
	rgb = (char*)malloc(rgbsize);

	jpeg_start_decompress(&cinfo);
	while (cinfo.output_scanline < cinfo.output_height)
	{
		rowptr[0] = (JSAMPROW)(rgb + rowsize*cinfo.output_scanline);
		jpeg_read_scanlines(&cinfo, rowptr, 1);
	}

	jpeg_finish_decompress(&cinfo);
	jpeg_destroy_decompress(&cinfo);
	fclose(fp);

	*data = rgb;
	*size = rgbsize;
	*width = imgwidth;
	*height = imgheight;
	return 0;
}

int compress_rgb_to_jpeg_file(const char* file, char* rgb, int width, int height)
{
	FILE* fp;
	struct jpeg_compress_struct jcs;
	struct jpeg_error_mgr jerr;
	JSAMPROW rowptr[1];
	int rowstride;

	fp = fopen(file, "wb");
	if (fp == NULL)
	{
		fprintf(stderr, "Can't open file '%s' for writing: %d\n", file, errno);
		return -1;
	}

	jcs.err = jpeg_std_error(&jerr);
	jpeg_create_compress(&jcs);
	jpeg_stdio_dest(&jcs, fp);

	jcs.image_width = width;
	jcs.image_height = height;
	jcs.input_components = 3;
	jcs.in_color_space = JCS_RGB;

	jpeg_set_defaults(&jcs);
	jpeg_set_quality(&jcs, 80, (boolean)1);

	jpeg_start_compress(&jcs, (boolean)1);

	rowstride = (jcs.image_width*3+3)/4*4;
	while (jcs.next_scanline < jcs.image_height)
	{
		rowptr[0] = (JSAMPROW)(rgb + jcs.next_scanline*rowstride);
		jpeg_write_scanlines(&jcs, rowptr, 1);
	}

	jpeg_finish_compress(&jcs);
	jpeg_destroy_compress(&jcs);
	fclose(fp);
	return 0;
}

int decompress_jpeg_from_buffer(char* src, size_t src_size, char** data, size_t* size, int* width, int* height)
{
	struct jpeg_error_mgr jerr;
	struct jpeg_decompress_struct cinfo;
	int imgwidth;
	int imgheight;
	int rowsize;
	int rgbsize;
	char* rgb;
	JSAMPROW rowptr[1];

	cinfo.err = jpeg_std_error(&jerr);
	jpeg_create_decompress(&cinfo);
	jpeg_mem_src(&cinfo, (unsigned char*)src, (unsigned long)src_size);
	jpeg_read_header(&cinfo, (boolean)1);

	imgwidth = cinfo.image_width;
	imgheight = cinfo.image_height;

	rowsize = imgwidth*cinfo.num_components;
	rgbsize = rowsize*imgheight;
	rgb = (char*)malloc(rgbsize);

	jpeg_start_decompress(&cinfo);
	while (cinfo.output_scanline < cinfo.output_height)
	{
		rowptr[0] = (JSAMPROW)(rgb + rowsize*cinfo.output_scanline);
		jpeg_read_scanlines(&cinfo, rowptr, 1);
	}

	jpeg_finish_decompress(&cinfo);
	jpeg_destroy_decompress(&cinfo);

	*data = rgb;
	*size = rgbsize;
	*width = imgwidth;
	*height = imgheight;
	return 0;
}

int compress_rgb_to_jpeg_buffer(char** dst, size_t* dst_size, char* rgb, int width, int height)
{
	struct jpeg_compress_struct jcs;
	struct jpeg_error_mgr jerr;
	JSAMPROW rowptr[1];
	int rowstride;
	unsigned char* out_ptr = (unsigned char*)(*dst);
	unsigned long out_size = *dst_size;

	jcs.err = jpeg_std_error(&jerr);
	jpeg_create_compress(&jcs);
	jpeg_mem_dest(&jcs, &out_ptr, &out_size);

	jcs.image_width = width;
	jcs.image_height = height;
	jcs.input_components = 3;
	jcs.in_color_space = JCS_RGB;

	jpeg_set_defaults(&jcs);
	jpeg_set_quality(&jcs, 80, (boolean)1);

	jpeg_start_compress(&jcs, (boolean)1);

	rowstride = (jcs.image_width*3+3)/4*4;
	while (jcs.next_scanline < jcs.image_height)
	{
		rowptr[0] = (JSAMPROW)(rgb + jcs.next_scanline*rowstride);
		jpeg_write_scanlines(&jcs, rowptr, 1);
	}

	jpeg_finish_compress(&jcs);
	jpeg_destroy_compress(&jcs);
	
	*dst = (char*)out_ptr;
	*dst_size = (size_t)out_size;
	return 0;
}

//最临近插值算法
int resize_rgb_nearest(char* src_data, int src_width, int src_height, char** dst_ptr, size_t* dst_size, int dst_width, int dst_height)
{
	int i, j;
	size_t srcLineSize = (src_width*3+3)/4*4;
	size_t dstLineSize = (dst_width*3+3)/4*4;
	size_t dstBufSize = dstLineSize*dst_height;
	char* dstBuf = (char*)malloc(dstBufSize);
	float rateH = (float)src_height/dst_height;
	float rateW = (float)src_width/dst_width;
	int tSrcH, tSrcW;

	for (i=0; i<dst_height; ++i)
	{
		//选取最邻近的点
		tSrcH = (int)(rateH*i+0.5f);
		for (j=0; j<dst_width; ++j)
		{
			tSrcW = (int)(rateW*j+0.5);
			memcpy(&dstBuf[i*dstLineSize+j*3], &src_data[tSrcH*srcLineSize+tSrcW*3], 3);
		}
	}
	*dst_ptr = dstBuf;
	*dst_size = dstBufSize;
	return 0;
}

int resize_rgb_double_linear(char* src_data, int src_width, int src_height, char** dst_ptr, size_t* dst_size, int dst_width, int dst_height)
{
	int i, j, k;
	size_t srcLineSize = (src_width*3+3)/4*4;
	size_t dstLineSize = (dst_width*3+3)/4*4;
	size_t dstBufSize = dstLineSize*dst_height;
	char* dstBuf = (char*)malloc(dstBufSize);
	float rateH = (float)src_height/dst_height;
	float rateW = (float)src_width/dst_width;
	int tH, tH1;
	int tW, tW1;
	float u, v;

	for (i=0; i<dst_height; ++i)
	{
		tH = (int)(rateH*i);
		tH1 = (tH+1)>(src_height-1)?(src_height-1):(tH+1);
		u = (float)(rateH*i - tH);

		for (j=0; j<dst_width; ++j)
		{
			tW = (int)(rateW*j);
			tW1 = (tW+1)>(src_width-1)?(src_width-1):(tW+1);
			v = (float)(rateW*j - tW);

			//f(i+u,j+v) = (1-u)(1-v)f(i,j) + (1-u)vf(i,j+1) + u(1-v)f(i+1,j) + uvf(i+1,j+1)
			for (k=0; k<3; k++)
			{
				dstBuf[i*dstLineSize + j*3 + k] = 
					(1-u)*(1-v)*src_data[tH*srcLineSize + tW*3 + k] +
					(1-u)*v*src_data[tH1*srcLineSize + tW*3 + k] +
					u*(1-v)*src_data[tH*srcLineSize + tW1*3 + k] +
					u*v*src_data[tH1*srcLineSize + tW1*3 + k];
			}
		}
	}

	*dst_ptr = dstBuf;
	*dst_size = dstBufSize;
	return 0;
}
