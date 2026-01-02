/*
 * PSP Software Development Kit - https://github.com/pspdev
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * pspmpeg.h - Prototypes for the sceMpeg library
 *
 * Copyright (c) 2006 Sorin P. C. <magik@hypermagik.com>
 * Copyright (c) 2007 Alexander Berl <raphael@fx-world.org>
 *
 */

#ifndef __SCELIBMPEG_H__
#define __SCELIBMPEG_H__

#include <psptypes.h>

/** points to "LIBMPEG" */
typedef ScePVoid SceMpeg;

/** some structure */
typedef SceVoid  SceMpegStream;

/** Ringbuffer callback */
typedef int (*sceMpegRingbufferCB)(void *data, int num_packets, void *param);

typedef struct SceMpegRingbuffer {
    /** packets */
	s32			packets;
    /** unknown */
	u32			unk0;
    /** unknown */
	u32			unk1;
    /** unknown */
	u32			unk2;
    /** unknown */
	u32			unk3;
    /** pointer to data */
	void *data;
    /** ringbuffer callback */
	sceMpegRingbufferCB	callback;
    /** callback param */
	void *cp_param;
    /** unknown */
	u32			unk4;
    /** unknown */
	u32			unk5;
    /** mpeg id */
	SceMpeg				mpeg_handler;
} SceMpegRingbuffer;

typedef struct SceMpegAu {
    /** presentation timestamp MSB */
	u32			pts_MSB;
    /** presentation timestamp LSB */
	u32			pts;
    /** decode timestamp MSB */
	u32			dts_MSB;
    /** decode timestamp LSB */
	u32			dts;
    /** Es buffer handle */
	u32			es_buffer;
    /** Au size */
	u32			au_size;
} SceMpegAu;

typedef enum {
	SCE_MPEG_AVC_FORMAT_DEFAULT = -1,
	SCE_MPEG_AVC_FORMAT_5650 = 0,
	SCE_MPEG_AVC_FORMAT_5551 = 1,
	SCE_MPEG_AVC_FORMAT_4444 = 2,
	SCE_MPEG_AVC_FORMAT_8888 = 3,
} SceMpegFormatKind;

typedef struct SceMpegAvcMode {
	/** unknown, set to -1 */
	s32			unk0;
	/** Decode pixelformat */
	s32			pixel_format;
} SceMpegAvcMode;

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#ifdef __USER__

/**
 * Initialize the Mpeg library.
 *
 * @return `0` if success.
 */
int sceMpegInit();

/**
 * Finishes the Mpeg library.
 */
void sceMpegFinish();

/**
 * sceMpegRingbufferQueryMemSize
 *
 * @param num_packets The number of packets in the ringbuffer.
 *
 * @return `< 0` if error else ringbuffer data size.
 */
int sceMpegRingbufferQueryMemSize(u32 num_packets);

/**
 * sceMpegRingbufferConstruct
 *
 * @param[inout] ringbuffer A pointer to a `sceMpegRingbuffer` struct.
 * @param packets The number of packets in the ringbuffer.
 * @param[out] data A pointer to allocated memory.
 * @param data_size The size of allocated memory, shoud be `sceMpegRingbufferQueryMemSize(iPackets)`.
 * @param[in] callback The ringbuffer callback.
 * @param[in] cb_param The param passed to callback.
 *
 * @return `0` if success.
 */
int sceMpegRingbufferConstruct(SceMpegRingbuffer* ringbuffer, u32 packets, void *data, u32 data_size, sceMpegRingbufferCB callback, void *cb_param);

/**
 * sceMpegRingbufferDestruct
 *
 * @param[inout] ringbuffer - pointer to a `sceMpegRingbuffer` struct
 */
void sceMpegRingbufferDestruct(SceMpegRingbuffer* ringbuffer);

/**
 * sceMpegQueryMemSize
 *
 * @param[in] ringbuffer A pointer to a `sceMpegRingbuffer` struct.
 *
 * @return `< 0` if error else number of free packets in the ringbuffer.
 */
int sceMpegRingbufferAvailableSize(SceMpegRingbuffer* ringbuffer);

/**
 * sceMpegRingbufferPut
 *
 * @param[inout] ringbuffer A pointer to a `sceMpegRingbuffer` struct.
 * @param num_packets The num packets to put into the ringbuffer.
 * @param available_packets The free packets in the ringbuffer. It should be `sceMpegRingbufferAvailableSize()`.
 *
 * @return `< 0` if error, else number of packets.
 */
int sceMpegRingbufferPut(SceMpegRingbuffer* ringbuffer, u32 num_packets, u32 available_packets);

/**
 * sceMpegQueryMemSize
 *
 * @param unk Unknown, set to `0`
 *
 * @return `< 0` if error else decoder data size.
 */
int sceMpegQueryMemSize(int unk);

/**
 * sceMpegCreate
 *
 * @param[inout] mpeg A pointer to a mpeg handler.
 * @param[in] data A pointer to allocated memory of size equal to `sceMpegQueryMemSize()`.
 * @param data_size The size of data, should be equal to `sceMpegQueryMemSize()`.
 * @param[in] ringbuffer A pointer to a ringbuffer.
 * @param frame_width The display buffer width. Set to `512` if writing to framebuffer.
 * @param unk1 Unknown, set to `0`.
 * @param unk2 Unknown, set to `0`.
 *
 * @return `0` if success.
 */
int sceMpegCreate(SceMpeg* mpeg, void *data, u32 data_size, SceMpegRingbuffer* ringbuffer, u32 frame_width, int unk1, int unk2);

/**
 * sceMpegDelete
 *
 * @param[inout] mpeg A pointer to a mpeg handler.
 */
SceVoid sceMpegDelete(SceMpeg* mpeg);

/**
 * sceMpegQueryStreamOffset
 *
 * @param[inout] mpeg A pointer to a mpeg handler.
 * @param[in] buffer A pointer to file header.
 * @param[in] offset The stream offset in bytes. Usually `2048`.
 *
 * @return `0` if success.
 */
int sceMpegQueryStreamOffset(SceMpeg* mpeg, void *buffer, s32 *offset);

/**
 * sceMpegQueryStreamSize
 *
 * @param[in] buffer A pointer to file header.
 * @param size The stream size in bytes.
 *
 * @return `0` if success.
 */
int sceMpegQueryStreamSize(void *buffer, u32 *size);

/**
 * sceMpegRegistStream
 *
 * @param[inout] mpeg A pointer to a mpeg handler.
 * @param stream_id The stream id. `0` for video, `1` for audio.
 * @param unk Unknown, set to `0`.
 *
 * @return `NULL` if error.
 */
SceMpegStream* sceMpegRegistStream(SceMpeg* mpeg, s32 stream_id, s32 unk);

/**
 * sceMpegUnRegistStream
 *
 * @param[inout] mpeg A pointer to a mpeg handler.
 * @param stream A pointer to stream.
 */
void sceMpegUnRegistStream(SceMpeg mpeg, SceMpegStream* stream);

/**
 * sceMpegFlushAllStreams
 *
 * @param[inout] mpeg A pointer to a mpeg handler.
 *
 * @return `0` if success.
 */
int sceMpegFlushAllStream(SceMpeg* mpeg);

/**
 * sceMpegMallocAvcEsBuf
 *
 * @param[inout] mpeg A pointer to a mpeg handler.
 *
 * @return `0` if error, else, a pointer to buffer.
 */
void *sceMpegMallocAvcEsBuf(SceMpeg* mpeg);

/**
 * sceMpegFreeAvcEsBuf
 *
 * @param[inout] mpeg A pointer to a mpeg handler.
 * @param[in] buf A pointer to a buffer.
 */
void sceMpegFreeAvcEsBuf(SceMpeg* mpeg, void *buf);

/**
 * sceMpegQueryAtracEsSize
 *
 * @param[inout] mpeg A pointer to a mpeg handler.
 * @param[out] es_size - will contain size of Es
 * @param[out] out_size - will contain size of decoded data
 *
 * @return `0` if success.
 */
int sceMpegQueryAtracEsSize(SceMpeg* mpeg, u32 *es_size, u32 *out_size);

/**
 * sceMpegInitAu
 *
 * @param[inout] mpeg A pointer to a mpeg handler.
 * @param[in] es_buffer A pointer to a previously allocated Es buffer.
 * @param[out] au A pointer to receive Au value.
 *
 * @return `0` if success.
 */
int sceMpegInitAu(SceMpeg* mpeg, void *es_buffer, SceMpegAu* au);

/**
 * sceMpegGetAvcAu
 *
 * @param[inout] mpeg A pointer to a mpeg handler.
 * @param[in] stream A pointer to an associated stream.
 * @param[out] au A pointer to receive Au value.
 * @param unk Unknown
 *
 * @return 0 if success.
 */
int sceMpegGetAvcAu(SceMpeg* mpeg, SceMpegStream* stream, SceMpegAu* au, int* unk);

/**
 * sceMpegAvcDecodeMode
 *
 * @param[inout] mpeg A pointer to a mpeg handler.
 * @param[in] mode A pointer to `SceMpegAvcMode` struct defining the decode mode (pixelformat).
 *
 * @return `0` if success.
 */
int sceMpegAvcDecodeMode(SceMpeg* mpeg, SceMpegAvcMode* mode);

/**
 * sceMpegAvcDecode
 *
 * @param[inout] mpeg A pointer to a mpeg handler.
 * @param[in] au The video Au.
 * @param frame_width The output buffer width. Set to `512` if writing to framebuffer.
 * @param[out] buffer The buffer that will contain the decoded frame.
 * @param[out] is_init The initialization state. It will be set to `0` on first call, then `1`.
 *
 * @return `0` if success.
 */
int sceMpegAvcDecode(SceMpeg* mpeg, SceMpegAu* au, u32 frame_width, void *buffer, u32 *is_init);

/**
 * sceMpegAvcDecodeStop
 *
 * @param[inout] mpeg A pointer to a mpeg handler.
 * @param frame_width The output buffer width. Set to `512` if writing to framebuffer.
 * @param[out] buffer - buffer that will contain the decoded frame
 * @param[out] status The frame number.
 *
 * @return `0` if success.
 */
int sceMpegAvcDecodeStop(SceMpeg* mpeg, int frame_width, ScePVoid buffer, int* status);

/**
 * sceMpegGetAtracAu
 *
 * @param[inout] mpeg A pointer to a mpeg handler.
 * @param[in] stream A pointer to the associated stream.
 * @param[out] au Aointer to Au.
 * @param unk - unknown
 *
 * @return 0 if success.
 */
int sceMpegGetAtracAu(SceMpeg* mpeg, SceMpegStream* stream, SceMpegAu* au, void *unk);

/**
 * sceMpegAtracDecode
 *
 * @param[inout] mpeg A pointer to a mpeg handler.
 * @param[in] au The video Au.
 * @param[out] buffer The buffer that will contain the decoded frame
 * @param[out] is_init The initialization state. It will be set to `0` on first call, then `1`.
 *
 * @return `0` if success.
 */
int sceMpegAtracDecode(SceMpeg* mpeg, SceMpegAu* au, void *buffer, int is_init);

#endif /* __USER__ */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __SCELIBMPEG_H__ */
