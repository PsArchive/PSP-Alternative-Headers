/*
 * PSP Software Development Kit - https://github.com/pspdev
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * pspwlan.h - Prototypes for the sceWlanDrv and sceWlanDrv_lib library
 *
 * Copyright (c) 2005 John Kelley <ps2dev@kelley.ca>
 *
 */
#ifndef __PSPWLAN_H__
#define __PSPWLAN_H__

#include <psptypes.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#ifdef __USER__

/**
 * Determine if the wlan device is currently powered on.
 *
 * @return `0` if off, `1` if on.
 *
 * @attention Requires linking to `pspwlandrv` stub to be available.
 */
int sceWlanDevIsPowerOn(void);

/**
 * Determine the state of the Wlan power switch.
 *
 * @return `0` if off, `1` if on.
 *
 * @attention Requires linking to `pspwlandrv` stub to be available.
 */
int sceWlanGetSwitchState(void);

/**
 * Get the Ethernet Address of the wlan controller
 *
 * @param ether_addr A pointer to a buffer of bytes (NOTE: it only writes to `6` bytes, but
 * requests `8` so pass it `8` bytes just in case).
 *
 * @return `0` on success, `< 0` on error.
 *
 * @attention Requires linking to `pspwlandrv` stub to be available.
 */
int sceWlanGetEtherAddr(uint8_t *ether_addr);

/**
 * Attach to the wlan device.
 *
 * @return `0` on success, `< 0` on error.
 *
 * @attention Requires linking to `pspwlandrv_lib` stub to be available.
 */
int sceWlanDevAttach(void);

/**
 * Detach from the wlan device.
 *
 * @return `0` on success, `< 0` on error.
 *
 * @attention Requires linking to `pspwlandrv_lib` stub to be available.
 */
int sceWlanDevDetach(void);

/*
int sceWlanGPBindRegError();
*/


#endif /* __USER__ */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __PSPWLAN_H__ */
