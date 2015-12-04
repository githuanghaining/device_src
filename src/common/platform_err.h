#ifndef __LY_ERR_H__
#define __LY_ERR_H__

typedef enum _lyerrno {
    LYR_OK = 0, /* 成功 */
    LYR_Unknown = 1, /* 未知错误 */
    LYR_MemoryRunOut = 2, /* 内存溢出 */
    LYR_InvalidParameter = 3, /* 非法参数 */
    LYR_LengthExceeded = 4, /* 参数内容过长 */
    LYR_OperationTimeout = 5, /* 操作超时 */
	LYR_DNSResolveFailed = 6, /* 域名解析失败 */

    LYR_InvalidAppID = 100, /* 错误的APPID */
    LYR_InvalidDevSN = 101, /* 错误的设备序列号 */
    LYR_InvalidCID = 102, /* 错误的CID */
    LYR_InvalidDataLevelPos = 103, /* 错误的数据层索引 */
    LYR_FrameTypeNotSupported = 104, /* 不支持的数据帧类型 */
    LYR_InvalidDevMode = 105, /* 错误的设备工作模式 */
    LYR_InvalidImageType = 106, /* 错误的截图类型 */
	LYR_InvalidToken = 107, /* 无效的token */
}lyerrno;

#endif //__LY_ERR_H__
