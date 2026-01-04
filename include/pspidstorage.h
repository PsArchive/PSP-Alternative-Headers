/*
 * PSP Software Development Kit - https://github.com/pspdev
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * pspidstorage.h - Interface to sceIdstorage_driver.
 *
 * Copyright (c) 2006 Harley G. <harleyg@0x89.org>
 *
 */

#ifndef PSPIDSTORAGE_H
#define PSPIDSTORAGE_H

#include <psptypes.h>

/** @defgroup IdStorage Interface to the sceIdStorage_driver library.
 */

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/** @addtogroup IdStorage Interface to the sceIdStorage_driver library.*/
/**@{*/

/**
 * Retrieves the value associated with a key.
 *
 * @param key    The idstorage key
 * @param offset The offset within the 512 byte leaf
 * @param buf    The buffer with enough storage
 * @param len    The amount of data to retrieve (`offset + len` must be <= `512` bytes)
 *
 * @return `0` on success, `< 0` on error.
 */
int sceIdStorageLookup(u16 key, u32 offset, void *buf, u32 len);

/**
 * Retrieves the whole 512 byte container for the key.
 *
 * @param key    The idstorage key
 * @param buf    The buffer with at last 512 bytes of storage
 *
 * @return `0` on success, `< 0` on error.
 */
int sceIdStorageReadLeaf(u16 key, void *buf);

/**
 * Writes 512-bytes to idstorage key.
 *
 * @param key    The idstorage key
 * @param buf    The buffer with 512 bytes of data
 *
 * @return `0` on success, `< 0` on error.
 */
int sceIdStorageWriteLeaf(u16 key, void *buf);

/** Checks idstorage for readonly status
 *
 * @return `1` is read-only, `0` otherwise.
*/
int sceIdStorageIsReadOnly(void);

/** Finalizes a write
 *
 * @return `0` on success, `< 0` on error.
*/
int sceIdStorageFlush(void);

int sceIdStorageCreateLeaf(unsigned int leafid);

int sceIdStorageCreateAtomicLeaves(u16 *leaves, int n);

int sceIdStorageFormat();

int sceIdStorageUnformat();

/**@}*/

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* PSPIDSTORAGE_H */
