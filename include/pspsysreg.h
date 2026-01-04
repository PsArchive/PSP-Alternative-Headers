/*
 * PSP Software Development Kit - https://github.com/pspdev
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * pspsysreg.h - Interface to sceSysreg_driver.
 *
 * Copyright (c) 2005 Marcus R. Brown <mrbrown@ocgnet.org>
 * Copyright (c) 2005 James Forshaw <tyranid@gmail.com>
 * Copyright (c) 2005 John Kelley <ps2dev@kelley.ca>
 *
 */

#ifndef PSPSYSREG_H
#define PSPSYSREG_H

#include <pspkerneltypes.h>

/** @defgroup Sysreg Interface to the sceSysreg_driver library.
 */

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/** @addtogroup Sysreg Interface to the sceSysreg_driver library. */
/**@{*/

#ifdef __KERNEL__

/**
  * Enable the ME reset.
  *
  * @return `< 0` on error.
  *
  * @attention Requires linking to `pspsysreg_driver` stub to be available.
  */
int sceSysregMeResetEnable(void);

/**
  * Disable the ME reset.
  *
  * @return `< 0` on error.
  *
  * @attention Requires linking to `pspsysreg_driver` stub to be available.
  */
int sceSysregMeResetDisable(void);

/**
  * Enable the VME reset.
  *
  * @return `< 0` on error.
  *
  * @attention Requires linking to `pspsysreg_driver` stub to be available.
  */
int sceSysregVmeResetEnable(void);

/**
  * Disable the VME reset.
  *
  * @return `< 0` on error.
  *
  * @attention Requires linking to `pspsysreg_driver` stub to be available.
  */
int sceSysregVmeResetDisable(void);

/**
  * Enable the ME bus clock.
  *
  * @return `< 0` on error.
  *
  * @attention Requires linking to `pspsysreg_driver` stub to be available.
  */
int sceSysregMeBusClockEnable(void);

/**
  * Disable the ME bus clock.
  *
  * @return `< 0` on error.
  *
  * @attention Requires linking to `pspsysreg_driver` stub to be available.
  */
int sceSysregMeBusClockDisable(void);

/**
 * Get the PSP's Tachyon version.
 *
 * @return The Tachyon version.
 *
 * @attention Requires linking to `pspsysreg_driver` stub to be available.
 */
int sceSysregGetTachyonVersion(void);

/** @attention Requires linking to `pspsysreg_driver` stub to be available. */
int sceSysregKirkBusClockEnable(void);

/** @attention Requires linking to `pspsysreg_driver` stub to be available. */
int sceSysregAtaBusClockEnable(void);

#endif /* __KERNEL__ */

/**@}*/

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* PSPLOADCORE_H */
