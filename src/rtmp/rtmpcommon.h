#ifndef __RTMP_COMMON_H__
#define __RTMP_COMMON_H__

typedef unsigned int DWORD;
typedef unsigned short WORD;


#define MAX_CID_NUMER	8
#define TOKEN_SIZE		16


#pragma pack(1)
typedef struct cid_list
{
	DWORD cids[MAX_CID_NUMER];
}cid_list_t;
#pragma pack()

#pragma pack(1)
typedef struct mobile_token
{
	DWORD	cid;		//the camera id which want to look
	cid_list_t clt;
	DWORD	user_id;
	DWORD	deadline_time;
	unsigned char token[TOKEN_SIZE];
	
}mobile_token_t;
#pragma pack()

#pragma pack(1)
typedef struct camera_token
{
	DWORD	cid;		
	DWORD	deadline_time;
	unsigned char token[TOKEN_SIZE];
	
}camera_token_t;
#pragma pack()



#endif

