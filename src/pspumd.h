/*
 * PSP Software Development Kit - https://github.com/pspdev
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * pspumd.h - Prototypes for the sceUmd library.
 *
 * Copyright (c) 2005 Marcus R. Brown <mrbrown@ocgnet.org>
 * Copyright (c) 2005 James Forshaw <tyranid@gmail.com>
 * Copyright (c) 2005 John Kelley <ps2dev@kelley.ca>
 *
 */
#ifndef __UMD_H__
#define __UMD_H__

/** @defgroup UMD UMD Kernel Library
  * This module contains the imports for UMD drive.
  */

/** @addtogroup UMD UMD Kernel Library */
/**@{*/

#include <psptypes.h>

/** UMD Info struct */
typedef struct SceUmdInfo {
	/** Set to `sizeof(SceUmdInfo)` */
	u32 size;
	/** One or more of `SceUmdTypes` */
	u32 type;
} SceUmdInfo;

typedef SceUmdInfo pspUmdInfo;

/** Enumeration for UMD types */
typedef enum SceUmdTypes {
	SCE_UMD_TYPE_GAME =		0x10,
	SCE_UMD_TYPE_VIDEO =	0x20,
	SCE_UMD_TYPE_AUDIO =	0x40,

	PSP_UMD_TYPE_GAME =		SCE_UMD_TYPE_GAME,
	PSP_UMD_TYPE_VIDEO =	SCE_UMD_TYPE_VIDEO,
	PSP_UMD_TYPE_AUDIO =	SCE_UMD_TYPE_AUDIO,
} SceUmdTypes;

/** Enumeration for UMD drive state */
typedef enum SceUmdState {
	SCE_UMD_NOT_PRESENT =	0x01,
	SCE_UMD_PRESENT =		0x02,
	SCE_UMD_CHANGED =		0x04,
	SCE_UMD_INITING =		0x08,
	SCE_UMD_INITED =		0x10,
	SCE_UMD_READY =			0x20,

	PSP_UMD_NOT_PRESENT =	SCE_UMD_NOT_PRESENT,
	PSP_UMD_PRESENT =		SCE_UMD_PRESENT,
	PSP_UMD_CHANGED =		SCE_UMD_CHANGED,
	PSP_UMD_INITING =		SCE_UMD_INITING,
	PSP_UMD_INITED =		SCE_UMD_INITED,
	PSP_UMD_READY =			SCE_UMD_READY,
} SceUmdState;

/** Enumeration for UMD stats (legacy) */
enum UmdDriveStat {
	/** Wait for disc to be inserted */
	UMD_WAITFORDISC = PSP_UMD_PRESENT,
	/** Wait for the UMD to be initialised so it can be accessed from the mapped drive */
	UMD_WAITFORINIT	= PSP_UMD_READY
};

/** UMD Callback function */
typedef int (*UmdCallback)(int unknown, int event);

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

/**
  * Check whether there is a disc in the UMD drive.
  *
  * @return `0` if no disc present, anything else indicates a disc is inserted.
  *
  * @attention Requires linking to `pspumd` or `pspumd_driver` (PSPSDK), `pspumd_kernel` (Adrenaline stubs) stubs to be available.
  */
int sceUmdCheckMedium(void);

/**
  * Get the disc info.
  *
  * @param[out] info A pointer to a `SceUmdInfo` struct to receive the information.
  *
  * @return `0` on success, `< 0` on error.
  *
  * @attention Requires linking to `pspumd` or `pspumd_driver` (PSPSDK), `pspumd_kernel` (Adrenaline stubs) stubs to be available.
  */
int sceUmdGetDiscInfo(SceUmdInfo *info);

/**
  * Activates the UMD drive.
  *
  * @param unit The unit to initialise (probably). Should be set to `1`.
  * @param[in] drive A prefix string for the fs device to mount the UMD on (e.g. "disc0:").
  *
  * @return `0` on success, `< 0` on error.
  *
  * @attention Requires linking to `pspumd` or `pspumd_driver` (PSPSDK), `pspumd_kernel` (Adrenaline stubs) stubs to be available.
  *
  * @par Example:
  * @code
  * // Wait for disc and mount to filesystem
  * int i;
  * i = sceUmdCheckMedium();
  * if(i == 0)
  * {
  *    sceUmdWaitDriveStat(PSP_UMD_PRESENT);
  * }
  * sceUmdActivate(1, "disc0:"); // Mount UMD to disc0: file system
  * sceUmdWaitDriveStat(PSP_UMD_READY);
  * // Now you can access the UMD using standard sceIo functions
  * @endcode
  */
int sceUmdActivate(int unit, const char *drive);

/**
  * Deactivates the UMD drive.
  *
  * @param unit The unit to initialise (probably). Should be set to `1`.
  * @param[in] drive A prefix string for the fs device to mount the UMD on (e.g. "disc0:").
  *
  * @return `0` on success, `< 0` on error.
  *
  * @attention Requires linking to `pspumd` or `pspumd_driver` (PSPSDK), `pspumd_kernel` (Adrenaline stubs) stubs to be available.
  */
int sceUmdDeactivate(int unit, const char *drive);

/**
  * Wait for the UMD drive to reach a certain state.
  *
  * @param stat The drive stat to wait. One or more of `SceUmdState`.
  *
  * @return `0` on success, `< 0` on error.
  *
  * @attention Requires linking to `pspumd` or `pspumd_driver` (PSPSDK), `pspumd_kernel` (Adrenaline stubs) stubs to be available.
  */
int sceUmdWaitDriveStat(int stat);

/**
  * Wait for the UMD drive to reach a certain state during a specified timeout.
  *
  * @param stat The drive stat to wait. One or more of `SceUmdState`.
  * @param timeout The timeout value in microseconds.
  *
  * @return `0` on success, `< 0` on error.
  *
  * @attention Requires linking to `pspumd` or `pspumd_driver` (PSPSDK), `pspumd_kernel` (Adrenaline stubs) stubs to be available.
  */
int sceUmdWaitDriveStatWithTimer(int stat, u32 timeout);

/**
  * Wait for the UMD drive to reach a certain state (plus callback).
  *
  * @param stat The drive stat to wait. One or more of `SceUmdState`.
  * @param timeout The timeout value in microseconds.
  *
  * @return `0` on success, `< 0` on error.
  *
  * @attention Requires linking to `pspumd` or `pspumd_driver` (PSPSDK), `pspumd_kernel` (Adrenaline stubs) stubs to be available.
  */
int sceUmdWaitDriveStatCB(int stat, u32 timeout);

/**
  * Cancel a sceUmdWait* call.
  *
  * @return `0` on success, `< 0` on error.
  *
  * @attention Requires linking to `pspumd` or `pspumd_driver` (PSPSDK), `pspumd_kernel` (Adrenaline stubs) stubs to be available.
  */
int sceUmdCancelWaitDriveStat(void);

/**
  * Get (poll) the current state of the UMD drive.
  *
  * @return `0` on success, `< 0` on error., one or more of ::SceUmdState on success
  *
  * @attention Requires linking to `pspumd` or `pspumd_driver` (PSPSDK), `pspumd_kernel` (Adrenaline stubs) stubs to be available.
  */
int sceUmdGetDriveStat(void);

/**
  * Get the error code associated with a failed event.
  *
  * @return `0` on success, `< 0` on error., the error code on success
  *
  * @attention Requires linking to `pspumd` or `pspumd_driver` (PSPSDK), `pspumd_kernel` (Adrenaline stubs) stubs to be available.
  */
int sceUmdGetErrorStat(void);

/**
  * Register a callback for the UMD drive.
  *
  * @note Callback is of type `UmdCallback`.
  *
  * @param cb_id - A callback ID created from `sceKernelCreateCallback()`.
  *
  * @return `0` on success, `< 0` on error.
  *
  * @attention Requires linking to `pspumd` or `pspumd_driver` (PSPSDK), `pspumd_kernel` (Adrenaline stubs) stubs to be available.
  *
  * @par Example:
  * @code
  * int umd_callback(int unknown, int event)
  * {
  *      //do something
  * }
  * int cb_id = sceKernelCreateCallback("UMD Callback", umd_callback, NULL);
  * sceUmdRegisterUMDCallBack(cb_id);
  * @endcode
  */
int sceUmdRegisterUMDCallBack(int cb_id);

/**
  * Un-register a callback for the UMD drive.
  *
  * @param cbid - A callback ID created from `sceKernelCreateCallback()`.
  *
  * @return `0` on success, `< 0` on error.
  *
  * @attention Requires linking to `pspumd` or `pspumd_driver` (PSPSDK), `pspumd_kernel` (Adrenaline stubs) stubs to be available.
  */
int sceUmdUnRegisterUMDCallBack(int cbid);

/**
  * Permit UMD disc being replaced.
  *
  * @return `0` on success, `< 0` on error.
  *
  * @attention Requires linking to `pspumd` or `pspumd_driver` (PSPSDK), `pspumd_kernel` (Adrenaline stubs) stubs to be available.
  */
int sceUmdReplacePermit(void);

/**
  * Prohibit UMD disc being replaced.
  *
  * @return `0` on success, `< 0` on error.
  *
  * @attention Requires linking to `pspumd` or `pspumd_driver` (PSPSDK), `pspumd_kernel` (Adrenaline stubs) stubs to be available.
  */
int sceUmdReplaceProhibit(void);

/**@}*/

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // __UMD_H__
