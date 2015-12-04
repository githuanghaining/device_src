#ifndef __RTMP_COMMON_H__
#define __RTMP_COMMON_H__

typedef unsigned int DWORD;
typedef unsigned short WORD;
typedef unsigned long long DWORD64;

#define TOKEN_SIZE 128

typedef struct _RTMPMetaData
{
  double  duration;
  double  width;
  double  height;
  double  videodatarate;
  double  framerate;
  double  videocodecid;
  double  audiodatarate;
  double  audiosamplerate;
  double  audiosamplesize;
  double  stereo;			  //0 for false
  double  audiocodecid;  
}RTMPMetaData;


#endif

