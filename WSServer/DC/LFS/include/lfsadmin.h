/*******************************************************************************
 *                                                                             *
 * lfsadmin.h    LFS - Administration and Support functions                    *
 *                                                                             *
 *                     Version 1.00  -  (2020-02)                              *
 *                                                                             *
 *******************************************************************************/

#ifndef __INC_LFSADMIN__H
#define __INC_LFSADMIN__H

#ifdef __cplusplus
extern "C" {
#endif

#include "lfsapi.h"

/*   字节对齐设置为1   */
#pragma pack(push, 1)

/* LFMAllocateBuffer 中flags参数的取值 */

#define LFS_MEM_SHARE    0x00000001
#define LFS_MEM_ZEROINIT 0x00000002

/****** 支撑函数 *************************************************************/

HRESULT extern LFSAPI LFMAllocateBuffer(ULONG size, ULONG flags, LPVOID* data);

HRESULT extern LFSAPI LFMAllocateMore(ULONG size,
                                      LPVOID original,
                                      LPVOID* data);

HRESULT extern LFSAPI LFMFreeBuffer(LPVOID data);

HRESULT extern LFSAPI LFMGetTraceLevel(HSERVICE service, LPDWORD trace_level);

HRESULT extern LFSAPI LFMKillTimer(timer_t timer_id);

HRESULT extern LFSAPI LFMOutputTraceData(LPSTR data);

HRESULT extern LFSAPI LFMReleaseLib(HPROVIDER provider);

HRESULT extern LFSAPI LFMSetTimer(LPSTR object_name,
                                  LPVOID context,
                                  DWORD time_val,
                                  timer_t* timer_id);

/*   恢复字节对齐方式   */
#pragma pack(pop)

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif /* __INC_LFSADMIN__H */
