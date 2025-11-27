/*
 * PSP Software Development Kit - http://www.pspdev.org
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * pspcrypt.h - Native encrypt/decrypt prototypes.
 *
 * Copyright (c) 2025 GrayJack <gr41.j4ck@gmail.com>
 */

#ifndef PSP_CRYPT_H
#define PSP_CRYPT_H

#include <psptypes.h>

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#ifdef __KERNEL__

/**
 * Sends a command to the KIRK encryption/decryption engine.
 *
 * @param[in] in_buf The input buffer
 * @param[out] out_buf The output buffer
 * @param cmd The commands to send to KIRK engine.
 *
 * @returns `< 0` on error
 *
 * @attention Requires linking to `pspsemaphore` stub to be available.
 */
int sceUtilsBufferCopy(u8 *in_buf, u8* out_buf, int cmd);

/**
 * Sends a command to the KIRK encryption/decryption engine, by polling.
 *
 * @param[in] in_buf The input buffer
 * @param[out] out_buf The output buffer
 * @param cmd The commands to send to KIRK engine.
 *
 * @returns `< 0` on error
 *
 * @attention Requires linking to `pspsemaphore` stub to be available.
 */
int sceUtilsBufferCopyByPolling(u8 *in_buf, u8* out_buf, int cmd);

/**
 * Sends a command to the KIRK encryption/decryption engine.
 *
 * @param[in] in_buf The input buffer
 * @param in_size The size of input buffer
 * @param[out] out_buf The output buffer
 * @param out_size The size of output buffer
 * @param cmd The commands to send to KIRK engine.
 *
 * @returns `< 0` on error
 *
 * @attention Requires linking to `pspsemaphore` stub to be available.
 */
int sceUtilsBufferCopyWithRange(void *in_buf, SceSize in_size, void *out_buf, int out_size, int cmd);

/**
 * Sends a command to the KIRK encryption/decryption engine, by polling
 *
 * @param[in] in_buf The input buffer
 * @param in_size The size of input buffer
 * @param[out] out_buf The output buffer
 * @param out_size The size of output buffer
 * @param cmd The commands to send to KIRK engine.
 *
 * @returns `< 0` on error
 *
 * @attention Requires linking to `pspsemaphore` stub to be available.
 */
int sceUtilsBufferCopyByPollingWithRange(void *in_buf, SceSize in_size, void *out_buf, int out_size, int cmd);

/**
 * Used for PSAR decoding (1.00 bogus)
 *
 * @param[inout] buf The in/out buffer to decode.
 * @param buf_size The size of the buffer pointed by buf
 * @param[out] ret_size A pointer to an integer that receives the size of
 * the decoded data.
 *
 * @returns `< 0` on error
 *
 * @attention Requires linking to `pspnwman_driver` stub to be available.
*/
int sceNwman_driver_9555D68D(void* buf, SceSize buf_size, int* ret_size);

/**
 * Used for PSAR decoding
 *
 * @param[inout] buf - The in/out buffer to decode.
 * @param buf_size - The size of the buffer pointed by buf
 * @param[out]  ret_size - Pointer to an integer that receives the size of
 * the decoded data.
 *
 * @returns `< 0` on error
 *
 * @attention Requires linking to `pspmesgd_driver` stub to be available.
*/
int sceMesgd_driver_102DC8AF(void* buf, SceSize buf_size, int* ret_size);

#endif // __KERNEL__

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // PSP_CRYPT_H