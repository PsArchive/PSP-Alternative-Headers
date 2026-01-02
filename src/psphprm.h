/*
 * PSP Software Development Kit - https://github.com/pspdev
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * pspaudio.h - Prototypes for the sceHprm and sceHprm_driver libraries.
 *
 * Copyright (c) 2005 Adresd
 *
 */

#ifndef __HPRM_H__
#define __HPRM_H__

#include <psptypes.h>

/** @defgroup Hprm Hprm Remote */

/** @addtogroup Hprm */

/**@{*/

/** Enumeration of the remote keys */
typedef enum SceHprmKeys {
	SCE_HPRM_PLAYPAUSE  = 0x1,
	SCE_HPRM_FORWARD    = 0x4,
	SCE_HPRM_BACK       = 0x8,
	SCE_HPRM_VOL_UP		= 0x10,
	SCE_HPRM_VOL_DOWN   = 0x20,
	SCE_HPRM_HOLD       = 0x80,

	PSP_HPRM_PLAYPAUSE  = SCE_HPRM_PLAYPAUSE,
	PSP_HPRM_FORWARD    = SCE_HPRM_FORWARD,
	PSP_HPRM_BACK       = SCE_HPRM_BACK,
	PSP_HPRM_VOL_UP		= SCE_HPRM_VOL_UP,
	PSP_HPRM_VOL_DOWN   = SCE_HPRM_VOL_DOWN,
	PSP_HPRM_HOLD       = SCE_HPRM_HOLD,
} SceHprmKeys;

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

/**
  * Peek at the current being pressed on the remote.
  *
  * @param[out] key A pointer to the u32 to receive the key bitmap, should be one or
  * more of `SceHprmKeys`
  *
  * @return `< 0` on error.
  *
  * @attention Requires linking to `psphprm` or `psphprm_driver` stubs to be available.
  */
int sceHprmPeekCurrentKey(u32 *key);

/**
  * Peek at the current latch data.
  *
  * @param[out] latch A pointer a to a 4 dword array to contain the latch data.
  *
  * @return `< 0` on error.
  *
  * @attention Requires linking to `psphprm` or `psphprm_driver` stubs to be available.
  */
int sceHprmPeekLatch(u32 *latch);

/**
  * Read the current latch data.
  *
  * @param[out] latch A pointer a to a 4 dword array to contain the latch data.
  *
  * @return `< 0` on error.
  *
  * @attention Requires linking to `psphprm` or `psphprm_driver` stubs to be available.
  */
int sceHprmReadLatch(u32 *latch);

/**
  * Determines whether the headphones are plugged in.
  *
  * @return `1` if the headphones are plugged in, else `0`.
  *
  * @attention Requires linking to `psphprm` or `psphprm_driver` stubs to be available.
  */
int sceHprmIsHeadphoneExist(void);

/**
  * Determines whether the remote is plugged in.
  *
  * @return `1` if the remote is plugged in, else `0`.
  *
  * @attention Requires linking to `psphprm` or `psphprm_driver` stubs to be available.
  */
int sceHprmIsRemoteExist(void);

/**
  * Determines whether the microphone is plugged in.
  *
  * @return `1` if the microphone is plugged in, else `0`.
  *
  * @attention Requires linking to `psphprm` or `psphprm_driver` stubs to be available.
  */
int sceHprmIsMicrophoneExist(void);


/**@}*/

#ifdef __cplusplus
}
#endif // __cplusplus

#endif
