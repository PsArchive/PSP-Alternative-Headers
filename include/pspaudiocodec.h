/*
 * PSP Software Development Kit - https://github.com/pspdev
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * pspaudiocodec.h - Prototypes for the sceAudiocodec library.
 *
 * Copyright (c) 2006 hitchhikr
 *
 */

#ifndef PSPAUDIO_CODEC_H
#define PSPAUDIO_CODEC_H

typedef enum SceCodecKind {
	SCE_CODEC_AT3PLUS = 0x00001000,
	SCE_CODEC_AT3 = 0x00001001,
	SCE_CODEC_MP3 = 0x00001002,
	SCE_CODEC_AAC = 0x00001003,

	// COMPAT

	PSP_CODEC_AT3PLUS = SCE_CODEC_AT3PLUS,
	PSP_CODEC_AT3 = SCE_CODEC_AT3,
	PSP_CODEC_MP3 = SCE_CODEC_MP3,
	PSP_CODEC_AAC = SCE_CODEC_AAC,
} SceCodecKind;


#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#ifdef __USER__

/** @attention Requires linking to `pspaudiocodec` stub to be available. */
int sceAudiocodecCheckNeedMem(unsigned long *buffer, int kind);
/** @attention Requires linking to `pspaudiocodec` stub to be available. */
int sceAudiocodecInit(unsigned long *buffer, int kind);
/** @attention Requires linking to `pspaudiocodec` stub to be available. */
int sceAudiocodecDecode(unsigned long *buffer, int kind);
/** @attention Requires linking to `pspaudiocodec` stub to be available. */
int sceAudiocodecGetEDRAM(unsigned long *buffer, int kind);
/** @attention Requires linking to `pspaudiocodec` stub to be available. */
int sceAudiocodecReleaseEDRAM(unsigned long *buffer);

#endif // __USER__

#ifdef __cplusplus
}
#endif //__cplusplus


#endif // PSPAUDIO_CODEC_H