/*
 * PSP Software Development Kit - https://github.com/pspdev
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * pspmp3.h - Prototypes for the sceMp3 library
 *
 * Copyright (c) 2008 David Perry <tias_dp@hotmail.com>
 * Copyright (c) 2008 Alexander Berl <raphael@fx-world.org>
 *
 */

#ifndef __SCELIBMP3_H__
#define __SCELIBMP3_H__

#include <psptypes.h>
#include <pspkerneltypes.h>

typedef struct SceMp3InitArg {
	/** Stream start position */
	SceOff		mp3_stream_start;
	/** Stream end position */
	SceOff		mp3_stream_end;
	/** Pointer to a buffer to contain raw mp3 stream data (+1472 bytes workspace) */
	SceUChar8*	mp3_buf;
	/** Size of mp3Buf buffer (must be >= 8192) */
	SceInt32	mp3_buf_size;
	/** Pointer to decoded pcm samples buffer */
	SceUChar8*	pcm_buf;
	/** Size of pcmBuf buffer (must be >= 9216) */
	SceInt32	pcm_buf_size;
} SceMp3InitArg;

// Compat with old field names.

#define mp3StreamStart mp3_stream_start
#define mp3StreamEnd mp3_stream_end
#define mp3Buf mp3_buf
#define mp3BufSize mp3_buf_size
#define pcmBuf pcm_buf
#define pcmBufSize pcm_buf_size

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#ifdef __USER__

/**
 * Initialize and reserve an sceMp3 handle.
 *
 * @param[in] args A pointer to `SceMp3InitArg` structure.
 *
 * @return sceMp3 handle ID on success, `< 0` on error.
 *
 * @attention Requires linking to `pspmp3` stub to be available.
 */
SceInt32 sceMp3ReserveMp3Handle(SceMp3InitArg* args);

/**
 * Release an sceMp3 handle.
 *
 * @param handle_id The sceMp3 handle ID.
 *
 * @return `0` if success, `< 0` on error.
 *
 * @attention Requires linking to `pspmp3` stub to be available.
 */
SceInt32 sceMp3ReleaseMp3Handle(SceInt32 handle_id);

/**
 * Initialize the sceMp3 internal values.
 *
 * This should be called before any other `sceMp3*` function.
 *
 * @return `0` if success, `< 0` on error.
 *
 * @attention Requires linking to `pspmp3` stub to be available.
 */
SceInt32 sceMp3InitResource();

/**
 * Deinitialize the sceMp3 internal values.
 *
 * @return `0` if success, `< 0` on error.
 *
 * @attention Requires linking to `pspmp3` stub to be available.
 */
SceInt32 sceMp3TermResource();

/**
 * Initialize a handle based.
 *
 * @param handle_id The sceMp3 handle ID to initialize.
 *
 * @return `0` if success, `< 0` on error.
 *
 * @attention Requires linking to `pspmp3` stub to be available.
 */
SceInt32 sceMp3Init(SceInt32 handle_id);

/**
 * Decode a sceMp3 handle.
 *
 * @param handle_id The sceMp3 handle ID to decode.
 * @param[out] pcm_buf A pointer to destination pcm samples buffer.
 *
 * @return number of bytes in decoded pcm buffer, `< 0` on error.
 *
 * @attention Requires linking to `pspmp3` stub to be available.
 */
SceInt32 sceMp3Decode(SceInt32 handle_id, SceShort16** pcm_buf);

/**
 * Get the information of the stream of a given handle ID.
 *
 * @param handle_id The sceMp3 handle ID.
 * @param[out] stream_buf A pointer to stream data buffer.
 * @param[out] to_write The Space remaining in stream data buffer
 * @param[out] src_pos - Position in source stream to start reading from
 *
 * @return `0` if success, `< 0` on error.
 *
 * @attention Requires linking to `pspmp3` stub to be available.
 */
SceInt32 sceMp3GetInfoToAddStreamData(SceInt32 handle_id, SceUChar8** stream_buf, SceInt32* to_write, SceInt32* src_pos);

/**
 * sceMp3NotifyAddStreamData
 *
 * @param handle_id The sceMp3 handle ID.
 * @param size The number of bytes added to the stream data buffer.
 *
 * @return `0` if success, `< 0` on error.
 *
 * @attention Requires linking to `pspmp3` stub to be available.
 */
SceInt32 sceMp3NotifyAddStreamData(SceInt32 handle_id, SceInt32 size);

/**
 * Checks if a given sceMp3 handle needs more stream data.
 *
 * @param handle_id The sceMp3 handle ID.
 *
 * @return `1` if more stream data is needed, `< 0` on error.
 *
 * @attention Requires linking to `pspmp3` stub to be available.
 */
SceInt32 sceMp3CheckStreamDataNeeded(SceInt32 handle_id);

/**
 * Set the loop number for a given sceMp3 handle ID.
 *
 * @param handle_id The sceMp3 handle ID.
 * @param loop The number of loops. Set to `0` to not loop.
 *
 * @return `0` if success, `< 0` on error.
 *
 * @attention Requires linking to `pspmp3` stub to be available.
 */
SceInt32 sceMp3SetLoopNum(SceInt32 handle_id, SceInt32 loop);

/**
 * Get the loop number for a sceMp3 handle.
 *
 * @param handle_id The sceMp3 handle ID.
 *
 * @return Number of loops, `< 0` on error.
 *
 * @attention Requires linking to `pspmp3` stub to be available.
 */
SceInt32 sceMp3GetLoopNum(SceInt32 handle_id);

/**
 * Get the number of decoded samples of a sceMp3 handle.
 *
 * @param handle_id The sceMp3 handle ID.
 *
 * @return Number of decoded samples, `< 0` on error.
 *
 * @attention Requires linking to `pspmp3` stub to be available.
 */
SceInt32 sceMp3GetSumDecodedSample(SceInt32 handle_id);

/**
 * Get the maximum samples to output of a sceMp3 handle.
 *
 * @param handle_id The sceMp3 handle ID.
 *
 * @return Number of max samples to output, `< 0` on error.
 *
 * @attention Requires linking to `pspmp3` stub to be available.
 */
SceInt32 sceMp3GetMaxOutputSample(SceInt32 handle_id);

/**
 * Get the sample rate of a sceMp3 handle.
 *
 * @param handle_id The sceMp3 handle ID.
 *
 * @return Sampling rate of the mp3, `< 0` on error.
 *
 * @attention Requires linking to `pspmp3` stub to be available.
 */
SceInt32 sceMp3GetSamplingRate(SceInt32 handle_id);

/**
 * Get the bitrate of a sceMp3 handle.
 *
 * @param handle_id The sceMp3 handle ID.
 *
 * @return Bitrate of the mp3, `< 0` on error.
 *
 * @attention Requires linking to `pspmp3` stub to be available.
 */
SceInt32 sceMp3GetBitRate(SceInt32 handle_id);

/**
 * Get the number of channels of a sceMp3 handle.
 *
 * @param handle_id The sceMp3 handle ID.
 *
 * @return Number of channels of the mp3, `< 0` on error.
 *
 * @attention Requires linking to `pspmp3` stub to be available.
 */
SceInt32 sceMp3GetMp3ChannelNum(SceInt32 handle_id);

/**
 * Reset the play position of a sceMp3 handle.
 *
 * @param handle_id The sceMp3 handle ID.
 *
 * @return `0` if success, `< 0` on error.
 *
 * @attention Requires linking to `pspmp3` stub to be available.
 */
SceInt32 sceMp3ResetPlayPosition(SceInt32 handle_id);

/**
 * Get the number of audio frames of a sceMp3 handle.
 *
 * @param handle_id The sceMp3 handle ID.
 *
 * @return Number of audio frames, `< 0` on error
 *
 * @attention Requires linking to `pspmp3` stub to be available.
 */
SceInt32 sceMp3GetFrameNum(SceInt32 handle_id);

/**
 * Reset tje play position of a specific frame of a sceMp3 handle.
 *
 * @param handle_id The sceMp3 handle ID.
 * @param frame The frame to reset play position.
 *
 * @return `0` if success, `< 0` on error.
 *
 * @attention Requires linking to `pspmp3` stub to be available.
 */
SceInt32 sceMp3ResetPlayPositionByFrame(SceInt32 handle_id, SceUInt32 frame);

/**
 * Get the MPEG version of a sceMp3 handle.
 *
 * @param handle_id The sceMp3 handle ID.
 *
 * @return MPEG Version, `< 0` on error
 *
 * @attention Requires linking to `pspmp3` stub to be available.
 */
SceInt32 sceMp3GetMPEGVersion(SceInt32 handle_id);

/**
 * sceMp3LowLevelInit
 *
 * @param handle_id The sceMp3 handle ID.
 * @param[in] raw_buf A pointer to a buffer to contain raw mp3 stream data
 *
 * @return `0` if success, `< 0` on error.
 *
 * @attention Requires linking to `pspmp3` stub to be available.
 */
SceInt32 sceMp3LowLevelInit(SceInt32 handle_id, SceUChar8* raw_buf);

/**
 * sceMp3LowLevelDecode
 *
 * @param handle_id The sceMp3 handle ID.
 * @param[in] mp3_src A pointer to a buffer to contain raw mp3 stream data.
 * @param[out] mp3_src_used A pointer to hold the mp3 data size consumed by decoding.
 * @param[out] pcm_dst A pointer to destination pcm samples buffer.
 * @param[out] pcm_dst_size A pointer to hold the size of pcm data output by decoding.
 *
 * @return `0` if success, `< 0` on error.
 *
 * @attention Requires linking to `pspmp3` stub to be available.
 */
SceInt32 sceMp3LowLevelDecode(SceInt32 handle_id, SceUChar8* mp3_src, SceUInt32* mp3_src_used, SceShort16* pcm_dst, SceUInt32* pcm_dst_size);

#endif // __USER__

#ifdef __cplusplus
}
#endif // __cplusplus

#endif
