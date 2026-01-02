/*
 * PSP Software Development Kit - https://github.com/pspdev
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * pspjpeg.h - Prototypes for the sceJpeg library
 *
 * Copyright (c) 2007 dot_blank
 *
 */
#ifndef __PSPJPEG_H__
#define __PSPJPEG_H__

#include <psptypes.h>
#include <psperror.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#ifdef __USER__

/**
 * Inits the MJpeg library.
 *
 * @return `0` on success, `< 0` on error.
 *
 * @attention Requires linking to `pspjpeg` stub to be available.
*/
int sceJpegInitMJpeg(void);

/**
 * Finishes the MJpeg library.
 *
 * @return `0` on success, `< 0` on error.
 *
 * @attention Requires linking to `pspjpeg` stub to be available.
*/
int sceJpegFinishMJpeg(void);

/**
 * Creates the decoder context.
 *
 * @param width The width of the frame.
 * @param height The height of the frame.
 *
 * @return `0` on success, `< 0` on error.
 *
 * @attention Requires linking to `pspjpeg` stub to be available.
*/
int sceJpegCreateMJpeg(int width, int height);

/**
 * Deletes the current decoder context.
 *
 * @return `0` on success, `< 0` on error.
 *
 * @attention Requires linking to `pspjpeg` stub to be available.
*/
int sceJpegDeleteMJpeg(void);

/**
 * Decodes a mjpeg frame to RGBA encoding.
 *
 * @note Input frame should be encoded as either yuv420p or yuvj420p, returns `SCE_JPEG_ERROR_UNSUPPORT_SAMPLING` otherwise.
 *
 * @param[in] jpeg_buf The buffer with the mjpeg frame.
 * @param size The size of the buffer pointed by `jpeg_buf`.
 * @param[out] rgba The buffer where the decoded data in RGBA format will be stored. It should have a size of (`width * height * 4`).
 * @param unk - Unknown, pass `0`.
 *
 * @return `(width * 65536) + height` on success, `< 0` on error.
 *
 * @attention Requires linking to `pspjpeg` stub to be available.
*/
int sceJpegDecodeMJpeg(u8 *jpeg_buf,	SceSize size, u8 *rgba, u32 unk);

/**
 * Reads information from mjpeg frame.
 *
 * @param[in] jpeg_buf The buffer with the mjpeg frame.
 * @param size The size of the mjpeg frame.
 * @param[out] color_info The address where the mjpeg chroma information will be stored.
 * @param unk Unknown, pass `0`.
 *
 * @return number of bytes needed in the buffer that will be used for YCbCr decoding, `<= 0` on error.
 *
 * @attention Requires linking to `pspjpeg` stub to be available.
*/
int sceJpegGetOutputInfo(u8 *jpeg_buf, SceSize size, int *color_info, int unk);

/**
 * Decodes a mjpeg frame to YCbCr encoding.
 *
 * @note Input frame should be encoded as either yuv420p or yuvj420p, returns `SCE_JPEG_ERROR_UNSUPPORT_SAMPLING` otherwise
 *
 * @param[in] jpeg_buf The buffer with the mjpeg frame.
 * @param size The size of the buffer pointed by `jpeg_buf`.
 * @param[out] ycbcr_buf The buffer where the decoded data in YCbCr format will be stored.
 * @param ycbcr_size The size of the buffer pointed by yCbCr (see `sceJpegGetOutputInfo()`).
 * @param unk Unknown, pass `0`.
 *
 * @return `(width * 65536) + height` on success, `< 0` on error.
 *
 * @attention Requires linking to `pspjpeg` stub to be available.
*/
int sceJpegDecodeMJpegYCbCr(u8 *jpeg_buf, SceSize size, u8 *ycbcr_buf, SceSize ycbcr_size, u32 unk);

/**
 * Converts a frame from YCbCr to RGBA
 *
 * @param[out] rgba_buf The buffer where the converted data in RGBA format will be stored.
 * @param[in] ycbcr_buf The buffer with the YCbCr data.
 * @param width_height The width and height of the frame `(width * 65536) + height`,
 *                          as returned by `sceJpegDecodeMJpegYCbCr()` or `sceJpegDecodeMJpeg()`.
 * @param buf_width The number of pixels per row of the buffer.
 * @param colour_info The chroma subsampling mode, as provided by `sceJpegGetOutputInfo()`.
 *
 * @return `0` on success, `< 0` on error.
 *
 * @attention Requires linking to `pspjpeg` stub to be available.
*/
int sceJpegCsc(u8 *rgba_buf, u8 *ycbcr_buf, int width_height, int buf_width, int colour_info);

#endif /* __USER__ */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __PSPJPEG_H__ */
