/*
 * PSP Software Development Kit - https://github.com/pspdev
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * pspstdio.h - Prototypes for the sceStdio library.
 *
 * Copyright (c) 2005 Marcus R. Brown <mrbrown@ocgnet.org>
 * Copyright (c) 2005 James Forshaw <tyranid@gmail.com>
 * Copyright (c) 2005 John Kelley <ps2dev@kelley.ca>
 *
 */
#ifndef __PSPSTDIO_H__
#define __PSPSTDIO_H__
// Protect from double definition of mixing our modified header with pspsdk header
#define PSPSTDIO_KERNEL_H

#include <pspkerneltypes.h>

/** @defgroup Stdio Stdio Library
 *  This module contains the imports for the kernel's stdio routines.
 */

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/** @addtogroup Stdio Stdio Library */
/**@{*/

/**
  * Function to get the current standard in file no.
  *
  * @return The stdin fileno.
  *
  * @attention Requires linking to `pspstdio_user` or `pspstdio_kernel` stubs to be available.
  */
SceUID sceKernelStdin(void);

/**
  * Function to get the current standard out file no.
  *
  * @return The stdout fileno.
  *
  * @attention Requires linking to `pspstdio_user` or `pspstdio_kernel` stubs to be available.
  */
SceUID sceKernelStdout(void);

/**
  * Function to get the current standard err file no.
  *
  * @return The stderr fileno.
  *
  * @attention Requires linking to `pspstdio_user` or `pspstdio_kernel` stubs to be available.
  */
SceUID sceKernelStderr(void);

/**@}*/

#ifdef __KERNEL__

/** @addtogroup Stdio_Kernel Driver interface to Stdio */
/**@{*/

/**
  * Function reopen the stdout file handle to a new file.
  *
  * @param[in] file The file to open.
  * @param flags The open flags .
  * @param mode The file mode.
  *
  * @return `< 0` on error.
  *
  * @attention Requires linking to `pspstdio_kernel` stub to be available.
  */
int sceKernelStdoutReopen(const char *file, int flags, SceMode mode);

/**
  * Function reopen the stderr file handle to a new file.
  *
  * @param[in] file The file to open.
  * @param flags The open flags.
  * @param mode The file mode.
  *
  * @return `< 0` on error.
  *
  * @attention Requires linking to `pspstdio_kernel` stub to be available.
  */
int sceKernelStderrReopen(const char *file, int flags, SceMode mode);


/**
  * fprintf but for file descriptors.
  *
  * @param fd The file descriptor from `sceIoOpen()`.
  * @param[in] format The format string.
  * @param[in] ... Variables.
  *
  * @return The number of characters printed, `< 0` on error.
  *
  * @attention Requires linking to `pspstdio_kernel` stub to be available.
  */
int fdprintf(int fd, const char *format, ...);
/**@}*/

#endif /* __KERNEL__ */


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __PSPSTDIO_H__ */
