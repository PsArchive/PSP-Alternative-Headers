/*
 * PSP Software Development Kit - https://github.com/pspdev
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 *  pspchnnlsv.h - Include for the pspChnnlsv library.
 *
 * Copyright (c) 2005 Jim Paris <jim@jtan.com>
 * Copyright (c) 2005 psp123
 *
 */
#ifndef __PSPCHNNLSV_H__
#define __PSPCHNNLSV_H__

/* The descriptions are mostly speculation. */

/** @defgroup Chnnlsv Chnnlsv Library
 * Library imports for the vsh chnnlsv library.
 */

#include <psptypes.h>

/** @addtogroup Chnnlsv Chnnlsv Library */
/**@{*/

typedef struct _pspChnnlsvContext1 {
	/** Cipher mode */
	int mode;
	/** Context data */
	u8 data[16];
	/** Context key */
	u8 key[16];
	/** Data size */
	u32 size;
} SceSdContext1;

typedef struct _pspChnnlsvContext2 {
	/** Cipher mode */
	u32 mode;
	u32 unk4;
	u8 data[16];
} SceSdContext2;

// Backwards compat
typedef SceSdContext1 pspChnnlsvContext1;
typedef SceSdContext2 pspChnnlsvContext2;
#define sceChnnlsv_E7833020 sceSdSetIndex
#define sceChnnlsv_F21A1FCA sceSdRemoveValue
#define sceChnnlsv_C4C494F8 sceSdGetLastIndex
#define sceChnnlsv_ABFDFC8B sceSdCreateList
#define sceChnnlsv_850A7FA1 sceSdSetMember
#define sceChnnlsv_21BE78B4 sceSdCleanList

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
 * Initialize context.
 *
 * @param[inout] ctx A pointer to the context.
 * @param mode The cipher mode, whichs sets the scramble key for kirk.
 *
 * @return `0` on success, `< 0` on error.
 *
 * @attention Requires linking to `pspchnnlsv` or `pspchnnlsv_driver` stubs to be available.
 */
int sceSdSetIndex(SceSdContext1 *ctx, int mode);

/**
 * Process data
 *
 * @param[in] ctx A pointer to the context.
 * @param[in] data The pointer to the data used in hash generation (aligned to `0x10`).
 * @param size The size of data used for hash generation (aligned to `0x10`).
 *
 * @return `0` on success, `< 0` on error.
 */
int sceSdRemoveValue(SceSdContext1 *ctx, u8 *data, int len);

/**
 * Finalize hash
 *
 * @param[inout] ctx A pointer to the context.
 * @param[out] hash The hash output (aligned to `0x10`, `0x10` bytes long).
 * @param[in] crypt_key The crypt key or `NULL`. If provided, this key will also be used in the encryption process.
 *
 * @return `0` on success, `< 0` on error.
 *
 * @attention Requires linking to `pspchnnlsv` or `pspchnnlsv_driver` stubs to be available.
 */
int sceSdGetLastIndex(SceSdContext1 *ctx, u8 *hash, u8 *crypt_key);

/**
 * Prepare a key, and set up integrity check
 *
 * @param[inout] ctx A pointer to the context.
 * @param mode The cipher mode. Different public keys/kirk commands will be used depending on the mode specified.
 * @param encrypt_mode The encrypt mode (1 = encrypting, 2 = decrypting)
 * @param[out] data A pointer to some data used for encryption/decryption.
 * @param[in] priv_key The private key, or `NULL`. If specified, this key will be used as the private key for encryption/decryption.
 *
 * @return `0` on success, `< 0` on error.
 *
 * @attention Requires linking to `pspchnnlsv` or `pspchnnlsv_driver` stubs to be available.
 */
int sceSdCreateList(SceSdContext2 *ctx, int mode, int encrypt_mode, u8 *data, u8 *priv_key);

/**
 * Process data for integrity check
 *
 * @param[inout] ctx A pointer to the context.
 * @param data A pointer to the data used in the encryption/decryption process (aligned to `0x10`).
 * @param size The size of `data` (aligned to `0x10`).
 *
 * @return `0` on success, `< 0` on error.
 *
 * @attention Requires linking to `pspchnnlsv` or `pspchnnlsv_driver` stubs to be available.
 */
int sceSdSetMember(SceSdContext2 *ctx, u8 *data, int size);

/**
 * Check integrity
 *
 * @param[inout] ctx A pointer to the context.
 *
 * @return `0` on success, `< 0` on error.
 *
 * @attention Requires linking to `pspchnnlsv` or `pspchnnlsv_driver` stubs to be available.
 */
int sceSdCleanList(SceSdContext2 *ctx);

/**@}*/

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __PSPCHNNLSV_H__ */
