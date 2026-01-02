/*
 * PSP Software Development Kit - https://github.com/pspdev
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * pspaudio.h - Prototypes for the sceAudio and sceAudio_driver libraries.
 *
 * Copyright (c) 2005 Adresd
 * Copyright (c) 2005 Marcus R. Brown <mrbrown@ocgnet.org>
 * Copyright (c) 2007 cooleyes
 * Copyright (c) 2007 Alexander Berl <raphael@fx-world.org>
 * Copyright (c) 2008 David Perry <tias_dp@hotmail.com>
 *
 */
#ifndef PSPAUDIO_H
#define PSPAUDIO_H
// Protect from double definition of mixing our modified header with pspsdk header
#define PSPAUDIO_KERNEL_H

/** @defgroup Audio User Audio Library */

/** @addtogroup Audio */

/*@{*/

#include <psperror.h>

/** The maximum output volume. */
#define PSP_AUDIO_VOLUME_MAX    0x8000

/** The maximum number of hardware channels. */
#define PSP_AUDIO_CHANNEL_MAX   8

/** The minimum number of samples that can be allocated to a channel. */
#define PSP_AUDIO_SAMPLE_MIN    64

/** The maximum number of samples that can be allocated to a channel. */
#define PSP_AUDIO_SAMPLE_MAX    65472

/** Make the given sample count a multiple of 64. */
#define PSP_AUDIO_SAMPLE_ALIGN(s) (((s) + 63) & ~63)

/** Used to request the next available hardware channel. */
#define PSP_AUDIO_NEXT_CHANNEL  (-1)

/** Error codes used as return values for the Audio Driver. */
#define SCE_AUDIO_ERROR_NOT_INITIALIZED (0x80260001)
#define SCE_AUDIO_ERROR_OUTPUT_BUSY (0x80260002)
#define SCE_AUDIO_ERROR_INVALID_CH (0x80260003)
#define SCE_AUDIO_ERROR_PRIV_REQUIRED (0x80260004)
#define SCE_AUDIO_ERROR_NOT_FOUND (0x80260005)
#define SCE_AUDIO_ERROR_INVALID_SIZE (0x80260006)
#define SCE_AUDIO_ERROR_INVALID_FORMAT (0x80260007)
#define SCE_AUDIO_ERROR_NOT_RESERVED (0x80260008)
#define SCE_AUDIO_ERROR_NOT_OUTPUT (0x80260009)
#define SCE_AUDIO_ERROR_INVALID_FREQUENCY (0x8026000A)
#define SCE_AUDIO_ERROR_INVALID_VOLUME (0x8026000B)
#define SCE_AUDIO_ERROR_INPUT_BUSY (0x80260010)

typedef enum PspAudioFormats {
	/** Channel is set to stereo output. */
	PSP_AUDIO_FORMAT_STEREO = 0,
	/** Channel is set to mono output. */
	PSP_AUDIO_FORMAT_MONO   = 0x10
} PspAudioFormats;

typedef enum SceFrequencies {
	SCE_FREQ_48000 = 48000,
	SCE_FREQ_44100 = 44100,
	SCE_FREQ_32000 = 32000,
	SCE_FREQ_24000 = 24000,
	SCE_FREQ_22050 = 22050,
	SCE_FREQ_16000 = 16000,
	SCE_FREQ_12000 = 12000,
	SCE_FREQ_11050 = 11050,
	SCE_FREQ_8000 = 8000,
} SceFrequencies;

typedef struct {
	/** Unknown. Pass 0 */
	int unk1;
	int gain;
	/** Unknown. Pass 0 */
	int unk2;
	/** Unknown. Pass 0 */
	int unk3;
	/** Unknown. Pass 0 */
	int unk4;
	/** Unknown. Pass 0 */
	int unk5;
} SceAudioInputParams;

typedef SceAudioInputParams pspAudioInputParams;

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

/**
  * Allocate and initialize a hardware output channel.
  *
  * @param channel The channel to reserve. Use a value between 0 - 7 to reserve a specific channel.
  *                   Pass PSP_AUDIO_NEXT_CHANNEL to get the first available channel.
  * @param sample_count The number of samples that can be output on the channel per
  *                      output call.  It must be a value between ::PSP_AUDIO_SAMPLE_MIN
  *                      and ::PSP_AUDIO_SAMPLE_MAX, and it must be aligned to 64 bytes
  *                      (use the ::PSP_AUDIO_SAMPLE_ALIGN macro to align it).
  * @param format The output format to use for the channel.  One of ::PspAudioFormats.
  *
  * @return The channel number on success, an error code if less than `0`.
  *
  * @attention Requires linking to `pspaudio` or `pspaudio_driver` stubs to be available.
  */
int sceAudioChReserve(int channel, int sample_count, int format);

/**
  * Release a hardware output channel.
  *
  * @param channel The channel to release.
  *
  * @return `0` on success, an error if less than `0`.
  *
  * @attention Requires linking to `pspaudio` or `pspaudio_driver` stubs to be available.
  */
int sceAudioChRelease(int channel);

/**
  * Output audio of the specified channel
  *
  * @param channel The channel number.
  *
  * @param vol The volume.
  *
  * @param[out] buf A pointer to the PCM data to output.
  *
  * @return `0` on success, an error if less than `0`.
  *
  * @attention Requires linking to `pspaudio` or `pspaudio_driver` stubs to be available.
  */
int sceAudioOutput(int channel, int vol, void *buf);

/**
  * Output audio of the specified channel (blocking)
  *
  * @param channel The channel number.
  *
  * @param vol The volume.
  *
  * @param[out] buf A pointer to the PCM data to output.
  *
  * @return `0` on success, an error if less than `0`.
  *
  * @attention Requires linking to `pspaudio` or `pspaudio_driver` stubs to be available.
  */
int sceAudioOutputBlocking(int channel, int vol, void *buf);

/**
  * Output panned audio of the specified channel
  *
  * @param channel The channel number.
  *
  * @param left_vol The left volume.
  *
  * @param right_vol The right volume.
  *
  * @param[out] buf A pointer to the PCM data to output.
  *
  * @return `0` on success, an error if less than `0`.
  *
  * @attention Requires linking to `pspaudio` or `pspaudio_driver` stubs to be available.
  */
int sceAudioOutputPanned(int channel, int left_vol, int right_vol, void *buf);

/**
  * Output panned audio of the specified channel (blocking)
  *
  * @param channel The channel number.
  *
  * @param left_vol The left volume.
  *
  * @param right_vol The right volume.
  *
  * @param[out] buf A pointer to the PCM data to output.
  *
  * @return `0` on success, an error if less than `0`.
  *
  * @attention Requires linking to `pspaudio` or `pspaudio_driver` stubs to be available.
  */
int sceAudioOutputPannedBlocking(int channel, int left_vol, int right_vol, void *buf);

/**
  * Get count of unplayed samples remaining
  *
  * @param channel The channel number.
  *
  * @return Number of samples to be played, an error if less than `0`.
  *
  * @attention Requires linking to `pspaudio` or `pspaudio_driver` stubs to be available.
  */
int sceAudioGetChannelRestLen(int channel);

/**
  * Get count of unplayed samples remaining
  *
  * @param channel The channel number.
  *
  * @return Number of samples to be played, an error if less than `0`.
  *
  * @attention Requires linking to `pspaudio` or `pspaudio_driver` stubs to be available.
  */
int sceAudioGetChannelRestLength(int channel);

/**
  * Change the output sample count, after it's already been reserved
  *
  * @param channel The channel number.
  * @param sample_count The number of samples to output in one output call.
  *
  * @return `0` on success, an error if less than `0`.
  *
  * @attention Requires linking to `pspaudio` or `pspaudio_driver` stubs to be available.
  */
int sceAudioSetChannelDataLen(int channel, int sample_count);

/**
  * Change the format of a channel
  *
  * @param channel The channel number.
  *
  * @param format One of ::PspAudioFormats
  *
  * @return `0` on success, an error if less than `0`.
  *
  * @attention Requires linking to `pspaudio` or `pspaudio_driver` stubs to be available.
  */
int sceAudioChangeChannelConfig(int channel, int format);

/**
  * Change the volume of a channel
  *
  * @param channel The channel number.
  *
  * @param leftvol The left volume.
  *
  * @param right_vol The right volume.
  *
  * @return `0` on success, an error if less than `0`.
  *
  * @attention Requires linking to `pspaudio` or `pspaudio_driver` stubs to be available.
  */
int sceAudioChangeChannelVolume(int channel, int leftvol, int right_vol);

//sceAudioOneshotOutput ???

/**
  * Reserve the audio output
  *
  * @param sample_count The number of samples to output in one output call (min 17, max 4111).
  *
  * @param freq The frequency. One of `SceFrequencies`.
  *
  * @param channels Number of channels. Pass 2 (stereo).
  *
  * @return `0` on success, an error if less than `0`.
  *
  * @attention Requires linking to `pspaudio` or `pspaudio_driver` stubs to be available.
  */
int sceAudioSRCChReserve(int sample_count, int freq, int channels);

/**
  * Release the audio output
  *
  * @return `0` on success, an error if less than `0`.
  *
  * @attention Requires linking to `pspaudio` or `pspaudio_driver` stubs to be available.
  */
int sceAudioSRCChRelease(void);

/**
  * Output audio
  *
  * @param vol The volume.
  *
  * @param[out] buf A pointer to the PCM data to output.
  *
  * @return `0` on success, an error if less than `0`.
  *
  * @attention Requires linking to `pspaudio` or `pspaudio_driver` stubs to be available.
  */
int sceAudioSRCOutputBlocking(int vol, void *buf);

/**
  * Init audio input
  *
  * @param unk1 Unknown. Pass 0.
  *
  * @param gain Gain.
  *
  * @param unk2 Unknown. Pass 0.
  *
  * @return `0` on success, an error if less than `0`.
  *
  * @attention Requires linking to `pspaudio` or `pspaudio_driver` stubs to be available.
  */
int sceAudioInputInit(int unk1, int gain, int unk2);

/**
  * Init audio input (with extra arguments)
  *
  * @param params A pointer to a `SceAudioInputParams` struct.
  *
  * @return `0` on success, an error if less than `0`.
  *
  * @attention Requires linking to `pspaudio` or `pspaudio_driver` stubs to be available.
  */
int sceAudioInputInitEx(SceAudioInputParams *params);

/**
  * Perform audio input (blocking)
  *
  * @param sample_count The number of samples.
  *
  * @param freq The frequency. Either 44100, 22050 or 11025.
  *
  * @param[out] buf A pointer to where the audio data will be stored.
  *
  * @return `0` on success, an error if less than `0`.
  *
  * @attention Requires linking to `pspaudio` or `pspaudio_driver` stubs to be available.
  */
int sceAudioInputBlocking(int sample_count, int freq, void *buf);

/**
  * Perform audio input
  *
  * @param sample_count The number of samples.
  *
  * @param freq The frequency. Either 44100, 22050 or 11025.
  *
  * @param[out] buf A pointer to where the audio data will be stored.
  *
  * @return `0` on success, an error if less than `0`.
  *
  * @attention Requires linking to `pspaudio` or `pspaudio_driver` stubs to be available.
  */
int sceAudioInput(int sample_count, int freq, void *buf);

/**
  * Get the number of samples that were acquired
  *
  * @return Number of samples acquired, an error if less than `0`.
  *
  * @attention Requires linking to `pspaudio` or `pspaudio_driver` stubs to be available.
  */
int sceAudioGetInputLength(void);

/**
  * Wait for non-blocking audio input to complete
  *
  * @return `0` on success, an error if less than `0`.
  *
  * @attention Requires linking to `pspaudio` or `pspaudio_driver` stubs to be available.
  */
int sceAudioWaitInputEnd(void);

/**
  * Poll for non-blocking audio input status
  *
  * @return `0` if input has completed, `1` if not completed, or an error if less than `0`.
  *
  * @attention Requires linking to `pspaudio` or `pspaudio_driver` stubs to be available.
  */
int sceAudioPollInputEnd(void);

/**
  * Get count of unplayed samples remaining
  *
  * @return Number of samples to be played, an error if less than `0`.
  *
  * @attention Requires linking to `pspaudio` or `pspaudio_driver` stubs to be available.
  */
int sceAudioOutput2GetRestSample(void);

#ifdef __USER__

/**
  * Reserve the audio output and set the output sample count
  *
  * @param sample_count The number of samples to output in one output call (min 17, max 4111).
  *
  * @return `0` on success, an error if less than `0`.
  *
  * @attention Requires linking to `pspaudio` stub to be available.
  */
int sceAudioOutput2Reserve(int sample_count);

/**
  * Release the audio output
  *
  * @return `0` on success, an error if less than `0`.
  *
  * @attention Requires linking to `pspaudio` stub to be available.
  */
int sceAudioOutput2Release(void);

/**
  * Change the output sample count, after it's already been reserved
  *
  * @param sample_count The number of samples to output in one output call (min 17, max 4111).
  *
  * @return `0` on success, an error if less than `0`.
  *
  * @attention Requires linking to `pspaudio` stub to be available.
  */
int sceAudioOutput2ChangeLength(int sample_count);

/**
  * Output audio (blocking)
  *
  * @param vol The volume.
  *
  * @param[out] buf Pointer to the PCM data.
  *
  * @return `0` on success, an error if less than `0`.
  *
  * @attention Requires linking to `pspaudio` stub to be available.
  */
int sceAudioOutput2OutputBlocking(int vol, void *buf);

#endif // __USER__


#ifdef __KERNEL__

/**
  * Set audio sampling frequency
  *
  * @param frequency - Sampling frequency to set the audio output. Either 44100 or 48000.
  *
  * @return `0` on success, an error if less than `0`.
  *
  * @attention Requires linking to `pspaudio_driver` stub to be available.
  */
int sceAudioSetFrequency(int frequency);

#endif __KERNEL__


/*@}*/

#ifdef __cplusplus
}
#endif

#endif /* PSPAUDIO_H */
