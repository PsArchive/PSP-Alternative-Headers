/*
 * PSP Software Development Kit - https://github.com/pspdev
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * pspmpegbase.h - Prototypes for the sceMpegbase library
 *
 * Copyright (c) 2006 Sorin P. C. <magik@hypermagik.com>
 * Copyright (c) 2007 cooleyes
 * Copyright (c) 2007 Alexander Berl <raphael@fx-world.org>
 *
 */

#ifndef __SCELIBMPEGBASE_H__
#define __SCELIBMPEGBASE_H__

#include <psptypes.h>


typedef struct SceMpegLLI {
	void * src;
	void * dst;
	void * next;
	u32 size;
} __attribute__((aligned(64))) SceMpegLLI;

typedef struct SceMpegYCrCbBuffer {
	s32	frame_buf_height16;
	s32	frame_buf_width16;
	s32	unk1;			// Set to `0`
	s32	unk2;			// Set to `1`
	void *	y_buf;			// pointer to YBuffer (in VME EDRAM?)
	void *	y_buf2;			// pointer to YBuffer + framebufferwidth*(frameheight/32)
	void *	cr_buf;			// pointer to CrBuffer (in VME EDRAM?)
	void *	cb_buf;			// pointer to CbBuffer (in VME EDRAM?)
	void *	cr_buf2;			// pointer to CrBuffer + (framebufferwidth/2)*(frameheight/64)
	void *	cb_buf2;			// pointer to CbBuffer + (framebufferwidth/2)*(frameheight/64)
	s32	frame_height;
	s32	frame_width;
	s32	frame_buf_width;
	s32	unk3[11];
} __attribute__((aligned(64))) SceMpegYCrCbBuffer;

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */


/**  @attention Requires linking to `pspmpegbase` or `pspmpegbase_driver` stubs to be available. */
int sceMpegBaseYCrCbCopyVme(void * yuv_buffer, int *buffer, int type);
/**  @attention Requires linking to `pspmpegbase` or `pspmpegbase_driver` stubs to be available. */
int sceMpegBaseCscInit(int width);
/**  @attention Requires linking to `pspmpegbase` or `pspmpegbase_driver` stubs to be available. */
int sceMpegBaseCscVme(void *rgb_buffer, void *rgb_buffer2, u32 width, SceMpegYCrCbBuffer* YCrCb_buffer);
/**  @attention Requires linking to `pspmpegbase` or `pspmpegbase_driver` stubs to be available. */
int sceMpegBasePESpacketCopy(SceMpegLLI *lli);


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __SCELIBMPEGBASE_H__ */
