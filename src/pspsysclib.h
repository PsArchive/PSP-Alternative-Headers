/*
 * PSP Software Development Kit - https://github.com/pspdev
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * pspsysclib.h - Interface to sysclib library.
 *
 * Copyright (c) 2007 James F
 *
 */

#ifndef PSPSYSCLIB_H
#define PSPSYSCLIB_H

#include <pspkerneltypes.h>
#include <stdarg.h>

/** Callback type, ch is 0x200 on start of string, 0x201 on end */
typedef void (*prnt_callback)(void *ctx, int ch);

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#ifdef __KERNEL__

/**
 * Generic print routine
 *
 * @param[in] cb The callback, called for every character printed
 * @param[in] ctx The context parameter passed to the callback
 * @param[in] fmt The format data
 * @param[in] args The arguments for format
 *
 * @attention Requires linking to `pspsysclib_kernel` stub to be available.
 */
void prnt(prnt_callback cb, void *ctx, const char *fmt, va_list args);

#endif /* __KERNEL__ */

/*@}*/

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif
