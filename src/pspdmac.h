/*
 * PSP Software Development Kit - http://www.pspdev.org
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * dmac.c - A DMAC function
 *
 * Copyright (c) 2016 173210 <root.3.173210@live.com>
 */

#ifndef __DMAC_H__
#define __DMAC_H__

#include <psptypes.h>

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#ifdef __USER__

/**
 * Copy data in memory using DMAC
 *
 * @param dst A pointer to the destination
 * @param src A pointer to the source
 * @param size The size of data
 *
 * @return `0` on success; otherwise an error code
 *
 * @attention Requires linking to `pspdmac` stub to be available.
 */
int sceDmacMemcpy(void *dst, const void *src, SceSize size);

/**
 * Tries tp copy data in memory using DMAC
 *
 * @param dst A pointer to the destination
 * @param src A pointer to the source
 * @param size The size of data
 *
 * @return `0` on success; otherwise an error code
 *
 * @attention Requires linking to `pspdmac` stub to be available.
 */
int sceDmacTryMemcpy(void *dst, const void *src, SceSize size);

#endif // __USER__

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // __DMAC_H__
