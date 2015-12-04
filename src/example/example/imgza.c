// utils.cpp
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <math.h>
#include "imgza.h"


int rgb_resize_nearest(unsigned char* src_data, int src_width, int src_height, unsigned char** dst_ptr, size_t* dst_size, int dst_width, int dst_height)
{
	int i, j;
	size_t srcLineSize = (src_width*3+3)/4*4;
	size_t dstLineSize = (dst_width*3+3)/4*4;
	size_t dstBufSize = dstLineSize*dst_height;
	unsigned char* dstBuf = (unsigned char*)malloc(dstBufSize);
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

int rgb_resize_double_linear(unsigned char* src_data, int src_width, int src_height, unsigned char** dst_ptr, size_t* dst_size, int dst_width, int dst_height)
{
	int i, j, k;
	size_t srcLineSize = (src_width*3+3)/4*4;
	size_t dstLineSize = (dst_width*3+3)/4*4;
	size_t dstBufSize = dstLineSize*dst_height;
	unsigned char* dstBuf = (unsigned char*)malloc(dstBufSize);
	float rateH = (float)src_height/(float)dst_height;
	float rateW = (float)src_width/(float)dst_width;
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
				dstBuf[i*dstLineSize + j*3 + k] = (unsigned char)
                    ((1-u)*(1-v)*src_data[tH*srcLineSize + tW*3 + k] +
					(1-u)*v*src_data[tH1*srcLineSize + tW*3 + k] +
					u*(1-v)*src_data[tH*srcLineSize + tW1*3 + k] +
					u*v*src_data[tH1*srcLineSize + tW1*3 + k]);
			}
		}
	}

	*dst_ptr = dstBuf;
	*dst_size = dstBufSize;
	return 0;
}

static float calc_S(float x)
{
    if (x < 0) {
        x = -x;
    }
    if (x < 1) {
        return 1-2*x*x+x*x*x;
    } else if (x < 2) {
        return 4-8*x+5*x*x-x*x*x;
    }
    return 0;
}

static void calc_A(float A[1][4], float u)
{
    A[0][0] = calc_S(u+1);
    A[0][1] = calc_S(u+0);
    A[0][2] = calc_S(u-1);
    A[0][3] = calc_S(u-2);
}

typedef struct tagPixel {
    float RGB[3];
} Pixel;
#define ZeroPixel(pixel) \
    pixel.RGB[0] = pixel.RGB[1] = pixel.RGB[2] = 0.0f
#define Copy2Pixel(pixel,f) { \
    (pixel).RGB[0] = (f)[0]; \
    (pixel).RGB[1] = (f)[1]; \
    (pixel).RGB[2] = (f)[2]; }
#define CopyFromPixel(f,pixel) { \
    (f)[0] = (unsigned char)(pixel).RGB[0]; \
    (f)[1] = (unsigned char)(pixel).RGB[1]; \
    (f)[2] = (unsigned char)(pixel).RGB[2]; }

static void calc_B(Pixel B[4][4], unsigned char* f, int w, int i, int j)
{
    int s, t;
    int x, y;
    for (s=0; s<4; s++) {
        x = (i+s-1)*w;
        for (t=0; t<4; t++) {
            y = (j+t-1)*3;
            Copy2Pixel(B[s][t], f+x+y);
        }
    }
}

static void calc_C(float C[4][1], float v)
{
    C[0][0] = calc_S(v+1);
    C[1][0] = calc_S(v+0);
    C[2][0] = calc_S(v-1);
    C[3][0] = calc_S(v-2);
}

static Pixel calc_ABC(float A[1][4], Pixel B[4][4], float C[4][1])
{
    int h, g, k;
    Pixel pixel;
    Pixel v[4];
    //V=A*B
    for (h=0; h<4; h++) {
        ZeroPixel(v[h]);
        for (g=0; g<4; g++) {
            for (k=0; k<3; k++) {
                v[h].RGB[k] += A[0][g]*B[g][h].RGB[k];
            }
        }
    }
    ZeroPixel(pixel);
    //V*C
    for (h=0; h<4; h++) {
        for (k=0; k<3; k++) {
            pixel.RGB[k] += v[h].RGB[k]*C[h][0];
        }
    }
    return pixel;
}

int rgb_resize_three_convolution(unsigned char* src_data, int src_width, int src_height, unsigned char** dst_ptr, size_t* dst_size, int dst_width, int dst_height)
{
    //f(i+u,j+v)=[A]*[B]*[C]
    float A[1][4];
    Pixel B[4][4];
    float C[4][1];
	int i, j;
	size_t srcLineSize = (src_width*3+3)/4*4;
	size_t dstLineSize = (dst_width*3+3)/4*4;
	size_t dstBufSize = dstLineSize*dst_height;
	unsigned char* dstBuf = (unsigned char*)malloc(dstBufSize);
	float rateH = (float)src_height/(float)dst_height;
	float rateW = (float)src_width/(float)dst_width;
    int x, y;
	float u, v;
    Pixel pixel;

	for (i=0; i<dst_height; ++i) {
		u = rateH * i;
        x = (int)u;
		u -= x;
        //边界判断
        if (x < 1) x++;
        else if (x+2 >= src_height) x = src_height-1;
        calc_A(A, u);

		for (j=0; j<dst_width; ++j) {
			v = rateW * j;
            y = (int)v;
			v -= y;

            //边界判断
            if (y < 1) y++;
            else if (y+2 >= src_width) y = src_width-1;
            calc_B(B, src_data, srcLineSize, x, y);

            calc_C(C, v);

            pixel = calc_ABC(A, B, C);

            CopyFromPixel(dstBuf+i*dstLineSize+j*3, pixel);
		}
	}

	*dst_ptr = dstBuf;
	*dst_size = dstBufSize;
	return 0;
}

static float KernelBSpline(const float x)
{
	if (x>2.0f) return 0.0f;
	// thanks to Kristian Kratzenstein
	float a, b, c, d;
	float xm1 = x - 1.0f; // Was calculatet anyway cause the "if((x-1.0f) < 0)"
	float xp1 = x + 1.0f;
	float xp2 = x + 2.0f;

	if ((xp2) <= 0.0f) a = 0.0f; else a = xp2*xp2*xp2; // Only float, not float -> double -> float
	if ((xp1) <= 0.0f) b = 0.0f; else b = xp1*xp1*xp1;
	if (x <= 0) c = 0.0f; else c = x*x*x;  
	if ((xm1) <= 0.0f) d = 0.0f; else d = xm1*xm1*xm1;

	return (0.16666666666666666667f * (a - (4.0f * b) + (6.0f * c) - (4.0f * d)));

	/* equivalent <Vladim韗 Kloucek>
	if (x < -2.0)
		return(0.0f);
	if (x < -1.0)
		return((2.0f+x)*(2.0f+x)*(2.0f+x)*0.16666666666666666667f);
	if (x < 0.0)
		return((4.0f+x*x*(-6.0f-3.0f*x))*0.16666666666666666667f);
	if (x < 1.0)
		return((4.0f+x*x*(-6.0f+3.0f*x))*0.16666666666666666667f);
	if (x < 2.0)
		return((2.0f-x)*(2.0f-x)*(2.0f-x)*0.16666666666666666667f);
	return(0.0f);
	*/
}

////////////////////////////////////////////////////////////////////////////////
//mode: 0_bilinear  双线性;1-nearest  最邻近;2-bicubic-spline 双三次
#define min(a,b) ((a)<(b)?(a):(b))
int rgb_resample(unsigned char* src, int w, int h, unsigned char** dst, size_t* dstsize, int newx, int newy, int mode)
{
	float xScale, yScale, fX, fY;
    uint32_t srcEffWidth = (w*3+3)/4*4;
    uint32_t dstEffWidth = (newx*3+3)/4*4;
    size_t dstBufSize = dstEffWidth*newy; 
    float f_x, f_y, f_a, f_b, rr, gg, bb, r1, r2;
    int32_t i_x, i_y, xx, yy;
    int32_t i, j, x, y, m, n;
    unsigned char* iDst, *iSrc;
    unsigned char* dst_buf;
    int32_t ifX, ifY, ifX1, ifY1, xmax, ymax;
    float ir1, ir2, ig1, ig2, ib1, ib2, dx, dy;
    uint8_t r,g,b;
    uint8_t rgbBlue1,rgbGreen1,rgbRed1;
    uint8_t rgbBlue2,rgbGreen2,rgbRed2;
    uint8_t rgbBlue3,rgbGreen3,rgbRed3;
    uint8_t rgbBlue4,rgbGreen4,rgbRed4;
    const int32_t ACCURACY = 1000;
    uint8_t* pSource;
    uint8_t* pDest;
    int32_t* naAccu;
    int32_t* naCarry;
    int32_t* naTemp;
    int32_t  nWeightX,nWeightY;
    float fEndX;
    int32_t nScale;
    int32_t u, v = 0; // coordinates in dest image
    float fEndY;

	if (newx==0 || newy==0) return -1;
    dst_buf = (unsigned char*)malloc(dstBufSize);
    if (dst_buf == NULL) {
        return -1;
    }
	if (x==newx && y==newy){
        memcpy(dst_buf, src, dstBufSize);
        if (dst) *dst = dst_buf;
        if (dstsize) *dstsize = dstBufSize;
		return 0;
	}

    xScale = (float)w/(float)newx;
    yScale = (float)h/(float)newy;

	switch (mode) {
	case 1: // nearest pixel
	{ 
		for(y=0; y<newy; y++){
            yy = (int)(y * yScale + 0.5f);
			for(x=0; x<newx; x++){
                xx = (int)(x * xScale + 0.5f);
                iDst = dst_buf + y*dstEffWidth + x*3;
                iSrc = src + yy*srcEffWidth + xx*3;
                memcpy(iDst, iSrc, 3);
			}
		}
		break;
	}
	case 2: // bicubic interpolation by Blake L. Carlson <blake-carlson(at)uiowa(dot)edu
	{
		for(y=0; y<newy; y++){
			f_y = (float) y * yScale - 0.5f;
			i_y = (int32_t) floor(f_y);
			f_a = f_y - (float)floor(f_y);
			for(x=0; x<newx; x++){
				f_x = (float) x * xScale - 0.5f;
				i_x = (int32_t) floor(f_x);
				f_b = f_x - (float)floor(f_x);

				rr = gg = bb = 0.0f;
				for(m=-1; m<3; m++) {
					r1 = KernelBSpline((float) m - f_a);
					yy = i_y+m;
					if (yy<0) yy=0;
					if (yy>=h) yy = h-1;
					for(n=-1; n<3; n++) {
						r2 = r1 * KernelBSpline(f_b - (float)n);
						xx = i_x+n;
						if (xx<0) xx=0;
						if (xx>=w) xx=w-1;

                        iSrc  = src + yy*srcEffWidth + xx*3;
						bb += *iSrc++ * r2;
						gg += *iSrc++ * r2;
						rr += *iSrc * r2;
					}
				}

                iDst = dst_buf + y*dstEffWidth + x*3;
                *iDst++ = (uint8_t)bb;
                *iDst++ = (uint8_t)gg;
                *iDst   = (uint8_t)rr;
			}
		}
		break;
	}
	default: // bilinear interpolation
		if (!(w>newx && h>newy /*&& head.biBitCount==24*/)) {
			// (c) 1999 Steve McMahon (steve@dogma.demon.co.uk)
			xmax = w-1;
			ymax = h-1;
			for(y=0; y<newy; y++){
				fY = y * yScale;
				ifY = (int32_t)fY;
				ifY1 = min(ymax, ifY+1);
				dy = fY - ifY;
				for(x=0; x<newx; x++){
					fX = x * xScale;
					ifX = (int32_t)fX;
					ifX1 = min(xmax, ifX+1);
					dx = fX - ifX;
					// Interpolate using the four nearest pixels in the source
                    iSrc = src + ifY*srcEffWidth + ifX*3;
                    rgbBlue1 = *iSrc++;	rgbGreen1 = *iSrc++;	rgbRed1 =*iSrc;
                    iSrc = src + ifY*srcEffWidth + ifX1*3;
                    rgbBlue2 = *iSrc++;	rgbGreen2 = *iSrc++;	rgbRed2 =*iSrc;
                    iSrc = src + ifY1*srcEffWidth + ifX*3;
                    rgbBlue3 = *iSrc++;	rgbGreen3 = *iSrc++;	rgbRed3 =*iSrc;
                    iSrc = src + ifY1*srcEffWidth + ifX1*3;
                    rgbBlue4 = *iSrc++;	rgbGreen4 = *iSrc++;	rgbRed4 =*iSrc;
					// Interplate in x direction:
					ir1 = rgbRed1   + (rgbRed3   - rgbRed1)   * dy;
					ig1 = rgbGreen1 + (rgbGreen3 - rgbGreen1) * dy;
					ib1 = rgbBlue1  + (rgbBlue3  - rgbBlue1)  * dy;
					ir2 = rgbRed2   + (rgbRed4   - rgbRed2)   * dy;
					ig2 = rgbGreen2 + (rgbGreen4 - rgbGreen2) * dy;
					ib2 = rgbBlue2  + (rgbBlue4  - rgbBlue2)  * dy;
					// Interpolate in y:
					r = (uint8_t)(ir1 + (ir2-ir1) * dx);
					g = (uint8_t)(ig1 + (ig2-ig1) * dx);
					b = (uint8_t)(ib1 + (ib2-ib1) * dx);
					// Set output
                    iDst = dst_buf + y*dstEffWidth + x;
                    *iDst++ = b;
                    *iDst++ = g;
                    *iDst = r;
				}
			} 
		} else {
			//high resolution shrink, thanks to Henrik Stellmann <henrik.stellmann@volleynet.de>
			pDest = dst_buf;
			naAccu  = (int32_t*)malloc((3*newx + 3)*4);
			naCarry = (int32_t*)malloc((3*newx + 3)*4);
			nScale = (int32_t)(ACCURACY * xScale * yScale);

			memset(naAccu,  0, sizeof(int32_t) * 3 * newx);
			memset(naCarry, 0, sizeof(int32_t) * 3 * newx);

			u = v = 0; // coordinates in dest image
			fEndY = yScale - 1.0f;
			for (y = 0; y < h; y++){
				pSource = src + y * srcEffWidth;
				u = i = 0;
				fEndX = xScale - 1.0f;
				if ((float)y < fEndY) {       // complete source row goes into dest row
					for (x = 0; x < w; x++){
						if ((float)x < fEndX){       // complete source pixel goes into dest pixel
							for (j = 0; j < 3; j++)	naAccu[i + j] += (*pSource++) * ACCURACY;
						} else {       // source pixel is splitted for 2 dest pixels
							nWeightX = (int32_t)(((float)x - fEndX) * ACCURACY);
							for (j = 0; j < 3; j++){
								naAccu[i] += (ACCURACY - nWeightX) * (*pSource);
								naAccu[3 + i++] += nWeightX * (*pSource++);
							}
							fEndX += xScale;
							u++;
						}
					}
				} else {       // source row is splitted for 2 dest rows       
					nWeightY = (int32_t)(((float)y - fEndY) * ACCURACY);
					for (x = 0; x < w; x++){
						if ((float)x < fEndX){       // complete source pixel goes into 2 pixel
							for (j = 0; j < 3; j++){
								naAccu[i + j] += ((ACCURACY - nWeightY) * (*pSource));
								naCarry[i + j] += nWeightY * (*pSource++);
							}
						} else {       // source pixel is splitted for 4 dest pixels
							nWeightX = (int32_t)(((float)x - fEndX) * ACCURACY);
							for (j = 0; j < 3; j++) {
								naAccu[i] += ((ACCURACY - nWeightY) * (ACCURACY - nWeightX)) * (*pSource) / ACCURACY;
								*pDest++ = (uint8_t)(naAccu[i] / nScale);
								naCarry[i] += (nWeightY * (ACCURACY - nWeightX) * (*pSource)) / ACCURACY;
								naAccu[i + 3] += ((ACCURACY - nWeightY) * nWeightX * (*pSource)) / ACCURACY;
								naCarry[i + 3] = (nWeightY * nWeightX * (*pSource)) / ACCURACY;
								i++;
								pSource++;
							}
							fEndX += xScale;
							u++;
						}
					}
					if (u < newx){ // possibly not completed due to rounding errors
						for (j = 0; j < 3; j++) *pDest++ = (uint8_t)(naAccu[i++] / nScale);
					}
					naTemp = naCarry;
					naCarry = naAccu;
					naAccu = naTemp;
					memset(naCarry, 0, sizeof(int32_t) * 3);    // need only to set first pixel zero
					pDest = dst_buf + (++v * dstEffWidth);
					fEndY += yScale;
				}
			}
			if (v < newy){	// possibly not completed due to rounding errors
				for (i = 0; i < 3 * newx; i++) *pDest++ = (uint8_t)(naAccu[i] / nScale);
			}
			free(naAccu);
			free(naCarry);
		}
	}

    if (dst) *dst = dst_buf;
    if (dstsize) *dstsize = dstBufSize;
    return 0;
}
