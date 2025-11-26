/*
 * PSP Software Development Kit - https://github.com/pspdev
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * pspatrac3.h - Prototypes for the sceAtrac3plus library
 *
 * Copyright (c) 2006 moonlight
 *
 */
#ifndef __LIBATRAC3_H__
#define __LIBATRAC3_H__

#include <psptypes.h>
#include <psperror.h>

/* Error code definition */
#define PSP_ATRAC_SUCCESS                       SCE_OK

#define PSP_ATRAC_ERROR_PARAM_FAIL              (0x80630001)
#define PSP_ATRAC_ERROR_API_FAIL                (0x80630002)
#define PSP_ATRAC_ERROR_NO_ATRACID              (0x80630003)
#define PSP_ATRAC_ERROR_BAD_CODECTYPE           (0x80630004)
#define PSP_ATRAC_ERROR_BAD_ATRACID             (0x80630005)
#define PSP_ATRAC_ERROR_UNKNOWN_FORMAT          (0x80630006)
#define PSP_ATRAC_ERROR_UNMATCH_FORMAT          (0x80630007)
#define PSP_ATRAC_ERROR_BAD_DATA                (0x80630008)
#define PSP_ATRAC_ERROR_ALLDATA_IS_ONMEMORY     (0x80630009)
#define PSP_ATRAC_ERROR_UNSET_DATA              (0x80630010)

#define PSP_ATRAC_ERROR_READSIZE_IS_TOO_SMALL   (0x80630011)
#define PSP_ATRAC_ERROR_NEED_SECOND_BUFFER      (0x80630012)
#define PSP_ATRAC_ERROR_READSIZE_OVER_BUFFER    (0x80630013)
#define PSP_ATRAC_ERROR_NOT_4BYTE_ALIGNMENT     (0x80630014)
#define PSP_ATRAC_ERROR_BAD_SAMPLE              (0x80630015)
#define PSP_ATRAC_ERROR_WRITEBYTE_FIRST_BUFFER  (0x80630016)
#define PSP_ATRAC_ERROR_WRITEBYTE_SECOND_BUFFER (0x80630017)
#define PSP_ATRAC_ERROR_ADD_DATA_IS_TOO_BIG     (0x80630018)

#define PSP_ATRAC_ERROR_UNSET_PARAM             (0x80630021)
#define PSP_ATRAC_ERROR_NONEED_SECOND_BUFFER    (0x80630022)
#define PSP_ATRAC_ERROR_NODATA_IN_BUFFER        (0x80630023)
#define PSP_ATRAC_ERROR_ALLDATA_WAS_DECODED     (0x80630024)

/* Audio Codec Types */
enum SceAtracCodecType {
	// Compat

	PSP_ATRAC_AT3PLUS = SCE_CODEC_AT3PLUS,
	PSP_ATRAC_AT3 = SCE_CODEC_AT3,
};

/* Remain Frame typical Status */
enum SceAtracRemainFrameStatus {
	SCE_ATRAC_ALLDATA_IS_ON_MEMORY = -1,
	SCE_ATRAC_NONLOOP_STREAM_DATA_IS_ON_MEMORY = -2,
	SCE_ATRAC_LOOP_STREAM_DATA_IS_ON_MEMORY = -3,

	// Compat

	PSP_ATRAC_ALLDATA_IS_ON_MEMORY = SCE_ATRAC_ALLDATA_IS_ON_MEMORY,
	PSP_ATRAC_NONLOOP_STREAM_DATA_IS_ON_MEMORY = SCE_ATRAC_NONLOOP_STREAM_DATA_IS_ON_MEMORY,
	PSP_ATRAC_LOOP_STREAM_DATA_IS_ON_MEMORY = SCE_ATRAC_LOOP_STREAM_DATA_IS_ON_MEMORY,
};

typedef struct {
	u8 *pucWritePositionFirstBuf;
	u32 uiWritableByteFirstBuf;
	u32 uiMinWriteByteFirstBuf;
	u32 uiReadPositionFirstBuf;

	u8 *pucWritePositionSecondBuf;
	u32 uiWritableByteSecondBuf;
	u32 uiMinWriteByteSecondBuf;
	u32 uiReadPositionSecondBuf;
} PspBufferInfo;

typedef struct {
	u8 *write_pos_first_buf;
	u32 writable_size_first_buf;
	u32 min_write_size_first_buf;
	u32 read_pos_first_buf;

	u8 *write_pos_second_buf;
	u32 writable_size_second_buf;
	u32 min_write_size_second_buf;
	u32 read_pos_second_buf;
} SceBufferInfo;

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#ifdef __USER__

/**
 * Get the current Atrac ID of the given codec type.
 *
 * @param codec_type The codec type to get the current Atrac ID. One of `SceCodecType` related to Atrac.
 *
 * @return The current atrac ID on success, or `< 0` on error.
 *
 * @attention Requires linking to `pspatrac3plus` stub to be available.
 */
int sceAtracGetAtracID(u32 codec_type);

/**
 * Creates a new Atrac ID from the specified data.
 *
 * @param buf The buffer holding the atrac3 data, including the RIFF/WAVE header.
 * @param buf_size The size of the buffer pointed by `buf`.
 *
 * @return The new atrac ID, or `< 0` on error.
 *
 * @attention Requires linking to `pspatrac3plus` stub to be available.
*/
int sceAtracSetDataAndGetID(void *buf, SceSize buf_size);

/**
 * Decode a frame of data.
 *
 * @param atrac_id The atrac ID.
 * @param[out] samples_buf A pointer to a buffer that receives the decoded data of the current frame.
 * @param[out] num_samples A pointer to a integer that receives the number of audio samples of the decoded frame.
 * @param[out] is_last_frame A pointer to a integer that receives a boolean value indicating if the decoded frame is the last one
 * @param[out] remain_frame A pointer to a integer that receives either -1 if all at3 data is already on memory,
 *  or the remaining (not decoded yet) frames at memory if not all at3 data is on memory. See `SceAtracRemainFrameStatus`.
 *
 *
 * @return `< 0` on error, otherwise `0`.
 *
 * @attention Requires linking to `pspatrac3plus` stub to be available.
*/
int sceAtracDecodeData(int atrac_id, u16 *samples_buf, int [out]*num_samples, int *is_last_frame, int *remain_frame);

/**
 * Gets the remaining (not decoded) number of frames.
 *
 * @param atrac_id The atrac ID.
 * @param[out] remain_frame A pointer to a integer that receives either -1 if all at3 data is already on memory,
 *  or the remaining (not decoded yet) frames at memory if not all at3 data is on memory.
 *
 * @return `< 0` on error, otherwise `0`.
 *
 * @attention Requires linking to `pspatrac3plus` stub to be available.
*/
int sceAtracGetRemainFrame(int atrac_id, int *remain_frame);

/**
 *
 * @param atrac_id The atrac ID.
 * @param[out] write_ptr A pointer to where to read the atrac data.
 * @param[out] writable_bytes The number of bytes available at the `write_ptr` location.
 * @param[out] read_offset A offset where to seek into the atrac file before reading.
 *
 * @return `< 0` on error, otherwise `0`.
 *
 * @attention Requires linking to `pspatrac3plus` stub to be available.
*/
int sceAtracGetStreamDataInfo(int atrac_id, u8** write_ptr, u32* writable_bytes, u32* read_offset);

/**
 *
 * @param atrac_id The atrac ID.
 * @param bytes_to_add The number of bytes read into location given by `sceAtracGetStreamDataInfo()`.
 *
 * @return `< 0` on error, otherwise `0`.
 *
 * @attention Requires linking to `pspatrac3plus` stub to be available.
*/
int sceAtracAddStreamData(int atrac_id, u32 bytes_to_add);

/**
 * Gets the bitrate.
 *
 * @param atrac_id The atrac ID.
 * @param[out] outBitrate A pointer to a integer that receives the bitrate in kbps.
 *
 * @return `< 0` on error, otherwise `0`.
 *
 * @attention Requires linking to `pspatrac3plus` stub to be available.
*/
int sceAtracGetBitrate(int atrac_id, int *outBitrate);

/**
 * Sets the number of loops for this atrac ID
 *
 * @param atrac_id The atrac ID.
 * @param num_loops The number of loops to set.
 *
 * @return `< 0` on error, otherwise `0`.
 *
 * @attention Requires linking to `pspatrac3plus` stub to be available.
*/
int sceAtracSetLoopNum(int atrac_id, int num_loops);

/**
 * It releases an atrac ID
 *
 * @param atrac_id The atrac ID to release
 *
 * @return `< 0` on error
 *
 * @attention Requires linking to `pspatrac3plus` stub to be available.
*/
int sceAtracReleaseAtracID(int atrac_id);

/**
 * Gets the number of samples of the next frame to be decoded.
 *
 * @param atrac_id The atrac ID.
 * @param[out] num_samples A pointer to receives the number of samples of the next frame.
 *
 * @return `< 0` on error, otherwise `0`
 *
 * @attention Requires linking to `pspatrac3plus` stub to be available.
 */
int sceAtracGetNextSample(int atrac_id, int *num_samples);

/**
 * Gets the maximum number of samples of the atrac3 stream.
 *
 * @param atrac_id The atrac ID.
 * @param[out] max_samples A pointer to a integer that receives the maximum number of samples.
 *
 * @return `< 0` on error, otherwise `0`
 *
 * @attention Requires linking to `pspatrac3plus` stub to be available.
 */
int sceAtracGetMaxSample(int atrac_id, int *max_samples);

/** @attention Requires linking to `pspatrac3plus` stub to be available. */
int sceAtracGetBufferInfoForReseting(int atrac_id, u32 sample, SceBufferInfo *buffer_info);

/** @attention Requires linking to `pspatrac3plus` stub to be available. */
int sceAtracGetChannel(int atrac_id, u32 *channel);

/** @attention Requires linking to `pspatrac3plus` stub to be available. */
int sceAtracGetInternalErrorInfo(int atrac_id, int *result);

/** @attention Requires linking to `pspatrac3plus` stub to be available. */
int sceAtracGetLoopStatus(int atrac_id, int *loop_num, u32 *loop_status);

/** @attention Requires linking to `pspatrac3plus` stub to be available. */
int sceAtracGetNextDecodePosition(int atrac_id, u32 *sample_position);

/** @attention Requires linking to `pspatrac3plus` stub to be available. */
int sceAtracGetSecondBufferInfo(int atrac_id, u32 *position, u32 *data_byte);

/** @attention Requires linking to `pspatrac3plus` stub to be available. */
int sceAtracGetSoundSample(int atrac_id, int *end_sample, int *loop_start_sample, int *loop_end_sample);

/** @attention Requires linking to `pspatrac3plus` stub to be available. */
int sceAtracResetPlayPosition(int atrac_id, u32 sample, u32 write_byte_first_buf, u32 write_byte_second_buf);

/** @attention Requires linking to `pspatrac3plus` stub to be available. */
int sceAtracSetData(int atrac_id, u8 *buffer_addr, u32 buffer_byte);

/** @attention Requires linking to `pspatrac3plus` stub to be available. */
int sceAtracSetHalfwayBuffer(int atrac_id, u8 *buffer_addr, u32 read_byte, u32 buffer_byte);

/** @attention Requires linking to `pspatrac3plus` stub to be available. */
int sceAtracSetHalfwayBufferAndGetID(u8 *buffer_addr, u32 read_byte, u32 buffer_byte);

/** @attention Requires linking to `pspatrac3plus` stub to be available. */
int sceAtracSetSecondBuffer(int atrac_id, u8 *second_buff_addr, u32 second_buff_byte);

#endif // __USER__


#ifdef __cplusplus
}
#endif // __cplusplus


#endif // __LIBATRAC3_H__
