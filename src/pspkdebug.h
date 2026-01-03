/*
 * PSP Software Development Kit - https://github.com/pspdev
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * pspkdebug.h - Interface to KDebugForKernel.
 *
 * Copyright (c) 2005 James Forshaw <tyranid@gmail.com>
 *
 */

#ifndef PSPKDEBUG_H
#define PSPKDEBUG_H

#include <pspkerneltypes.h>

/** @defgroup Kdebug Interface to the KDebugForKernel library.
 */

/** @addtogroup Kdebug Interface to the KDebugForKernel library. */
/**@{*/

/** Typedef for the debug putcharacter handler */
typedef void (*PspDebugPutChar)(unsigned short* args, unsigned int ch);

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#ifdef __KERNEL__

/**
 * Register a debug put character handler.
 *
 * @param func The put character function to register.
 *
 * @attention Requires linking to `pspkdebug_kernel` stub to be available.
 */
void sceKernelRegisterDebugPutchar(PspDebugPutChar func);

/**
 * Get the debug put character handler.
 *
 * @return The current debug putchar handler.
 *
 * @attention Requires linking to `pspkdebug_kernel` stub to be available.
 */
PspDebugPutChar sceKernelGetDebugPutchar(void);

/**
 * Kernel printf function.
 *
 * @param format The format string.
 * @param ... The arguments for the format string.
 *
 * @attention Requires linking to `pspkdebug_kernel` stub to be available.
 */
void Kprintf(const char *format, ...) __attribute__((format(printf, 1, 2)));

#endif /* __KERNEL__ */

/**@}*/

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* PSPKDEBUG_H */
