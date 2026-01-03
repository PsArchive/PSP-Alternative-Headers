/*
 * PSP Software Development Kit - https://github.com/pspdev
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * pspimpose.h - Prototypes for the sceImpose and sceImpose_driver libraries.
 *
 * Copyright (c) 2007 Iaroslav Gaponenko <adrahil@gmail.com>
 * Copyright (c) 2025 GrayJack
 *
 */

#ifndef __IMPOSE_H__
#define __IMPOSE_H__
// Protect from double definition of mixing our modified header with pspsdk header
#define __IMPOSE_DRIVER_H__

#include <psptypes.h>

typedef enum SceImposeParam {
	SCE_IMPOSE_MAIN_VOLUME = 0x1,
	SCE_IMPOSE_BACKLIGHT_BRIGHTNESS = 0x2,
	SCE_IMPOSE_EQUALIZER_MODE = 0x4,
	SCE_IMPOSE_MUTE = 0x8,
	SCE_IMPOSE_AVLS = 0x10,
	SCE_IMPOSE_TIME_FORMAT = 0x20,
	SCE_IMPOSE_DATE_FORMAT = 0x40,
	SCE_IMPOSE_LANGUAGE = 0x80,
	SCE_IMPOSE_BACKLIGHT_OFF_INTERVAL = 0x200,
	SCE_IMPOSE_SOUND_REDUCTION = 0x400,

	// Compat

	PSP_IMPOSE_MAIN_VOLUME = SCE_IMPOSE_MAIN_VOLUME,
	PSP_IMPOSE_BACKLIGHT_BRIGHTNESS = SCE_IMPOSE_BACKLIGHT_BRIGHTNESS,
	PSP_IMPOSE_EQUALIZER_MODE = SCE_IMPOSE_EQUALIZER_MODE,
	PSP_IMPOSE_MUTE = SCE_IMPOSE_MUTE,
	PSP_IMPOSE_AVLS = SCE_IMPOSE_AVLS,
	PSP_IMPOSE_TIME_FORMAT = SCE_IMPOSE_TIME_FORMAT,
	PSP_IMPOSE_DATE_FORMAT = SCE_IMPOSE_DATE_FORMAT,
	PSP_IMPOSE_LANGUAGE = SCE_IMPOSE_LANGUAGE,
	PSP_IMPOSE_BACKLIGHT_OFF_INTERVAL = SCE_IMPOSE_BACKLIGHT_OFF_INTERVAL,
	PSP_IMPOSE_SOUND_REDUCTION = SCE_IMPOSE_SOUND_REDUCTION,
} SceImposeParam;

/**
 * These values have been found in the 3.52 kernel.
 * Therefore, they might not be supported by previous ones.
 */

typedef enum SceImposeUmdStatus {
	SCE_IMPOSE_UMD_POPUP_DISABLED = 0,
	SCE_IMPOSE_UMD_POPUP_ENABLED = 1,

	// Compat

	PSP_IMPOSE_UMD_POPUP_DISABLED = SCE_IMPOSE_UMD_POPUP_DISABLED,
	PSP_IMPOSE_UMD_POPUP_ENABLED = SCE_IMPOSE_UMD_POPUP_ENABLED,
} SceImposeUmdStatus;

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
 * Get the value of the backlight timer.
 *
 * @return backlight timer in seconds or `< 0` on error.
 *
 * @attention Requires linking to `pspimpose` or `pspimpose_driver` stubs to be available.
 */
int sceImposeGetBacklightOffTime(void);

/**
 * Set the value of the backlight timer.
 *
 * @param value - The backlight timer. (30 to a lot of seconds).
 *
 * @return `< 0` on error.
 *
 * @attention Requires linking to `pspimpose` or `pspimpose_driver` stubs to be available.
 */
int sceImposeSetBacklightOffTime(int value);

/**
 * Get the language and button assignment parameters.
 *
 * @return `< 0` on error.
 *
 * @attention Requires linking to `pspimpose` or `pspimpose_driver` stubs to be available.
 */
int sceImposeGetLanguageMode(int* lang, int* button);

/**
 * Set the language and button assignment parameters.
 *
 * @attention Parameter values are not known.
 *
 * @param lang The language.
 * @param button The button assignment.
 *
 * @return `< 0` on error.
 *
 * @attention Requires linking to `pspimpose` or `pspimpose_driver` stubs to be available.
 */
int sceImposeSetLanguageMode(int lang, int button);

/**
 * Get the value of the UMD popup.
 *
 * @return umd popup state, or `< 0` on error
 *
 *
 * @attention Requires linking to `pspimpose` or `pspimpose_driver` stubs to be available.
 */
int sceImposeGetUMDPopup(void);

/**
 * Set the value of the UMD popup.
 *
 * @param value The popup mode.
 *
 * @return `< 0` on error.
 *
 * @attention Requires linking to `pspimpose` or `pspimpose_driver` stubs to be available.
 */
int sceImposeSetUMDPopup(int value);

/**
 * Get the value of the Home popup.
 *
 * @return home popup state or `< 0` on error
 *
 * @attention Requires linking to `pspimpose` or `pspimpose_driver` stubs to be available.
 */
int sceImposeGetHomePopup(void);

/**
 * Set the value of the Home popup.
 *
 * @param value - The popup mode.
 *
 * @return `< 0` on error.
 *
 * @attention Requires linking to `pspimpose` or `pspimpose_driver` stubs to be available.
 */
int sceImposeSetHomePopup(int value);


#ifdef __KERNEL__

/**
 * Fetch the value of an Impose parameter.
 *
 * @param param The impose parameter. One of `SceImposeParam`.
 *
 * @return value of the parameter on success, `< 0` on error.
 *
 * @attention Requires linking to `pspimpose_driver` stub to be available.
 */
int sceImposeGetParam(SceImposeParam param);

/**
 * Change the value of an Impose parameter.
 *
 * @param param The impose parameter to change. One of `SceImposeParam`.
 * @param value The value to set the parameter to.
 *
 * @return `< 0` on error.
 *
 * @attention Requires linking to `pspimpose_driver` stub to be available.
 */
int sceImposeSetParam(SceImposeParam param, int value);

/**
 * Check the video out. (for psp slim?)
 *
 * @param value The video out mode/status(?).
 *
 * @return `< 0` on error.
 *
 * @attention Requires linking to `pspimpose_driver` stub to be available.
 */
int sceImposeCheckVideoOut(int* value);

#endif /* __KERNEL__ */


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __IMPOSE_H__ */