/*
 * PSP Software Development Kit - https://github.com/pspdev
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * psputils.h - Prototypes for the sceUtils library.
 *
 * Copyright (c) 2005 Marcus R. Brown <mrbrown@ocgnet.org>
 * Copyright (c) 2005 James Forshaw <tyranid@gmail.com>
 * Copyright (c) 2005 John Kelley <ps2dev@kelley.ca>
 *
 */
#ifndef __UTILS_H__
#define __UTILS_H__
// Protect from double definition of mixing our modified header with pspsdk header
#define __PSPUTILSFORKERNEL_H__

#include <time.h>
#include <sys/time.h>

#include <psptypes.h>

/* Some of the structures and definitions in this file were extracted from the japanese
   puzzle bobble main executable */

/** @defgroup Utils Utils Library */

/** @addtogroup Utils */

/**@{*/

/**
 *  This struct is needed because tv_sec size is different from what newlib expect
 * Newlib expects 64bits for seconds and PSP expects 32bits
 */
typedef struct SceKernelTimeval {
	uint32_t tv_sec;
	uint32_t tv_usec;
} SceKernelTimeval;

/** Structure for holding a mersenne twister context */
typedef struct _SceKernelUtilsMt19937Context {
	unsigned int 	count;
	unsigned int 	state[624];
} SceKernelUtilsMt19937Context;

/** Structure to hold the MD5 context */
typedef struct _SceKernelUtilsMd5Context {
	unsigned int 	h[4];
	unsigned int 	pad;
	SceUShort16 	usRemains;
	SceUShort16 	usComputed;
	SceULong64 	ullTotalLen;
	unsigned char 	buf[64];
} SceKernelUtilsMd5Context;

/** Type to hold a sha1 context */
typedef struct _SceKernelUtilsSha1Context {
	unsigned int 	h[5];
	SceUShort16 	usRemains;
	SceUShort16 	usComputed;
	SceULong64 	ullTotalLen;
	unsigned char 	buf[64];
} SceKernelUtilsSha1Context;

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
  * Get the time in seconds since the epoch (1st Jan 1970)
  *
  * @param[out] t A pointer to receive the data.
  *
  * @return The time in seconds.
  *
  * @attention Requires linking to `psputils_user` or `psputils_kernel` stubs to be available.
  */
time_t sceKernelLibcTime(time_t *t);

/**
  * Get the processor clock used since the start of the process.
  *
  * @return The processor clock.
  *
  * @attention Requires linking to `psputils_user` or `psputils_kernel` stubs to be available.
  */
clock_t sceKernelLibcClock(void);

/**
  * Get the current time of time and time zone information
  *
  * @param[out] tp A pointer to receive the timeval information.
  * @param[out] tzp A pointer to receive the timezone information.
  *
  * @attention Requires linking to `psputils_user` or `psputils_kernel` stubs to be available.
  */
int sceKernelLibcGettimeofday(struct SceKernelTimeval *tp, struct timezone *tzp);

/**
  * Write back the data cache to memory.
  *
  * @attention Requires linking to `psputils_user` or `psputils_kernel` stubs to be available.
  */
void sceKernelDcacheWritebackAll(void);

/**
  * Write back and invalidate the data cache.
  *
  * @attention Requires linking to `psputils_user` or `psputils_kernel` stubs to be available.
  */
void sceKernelDcacheWritebackInvalidateAll(void);

/**
  * Write back a range of addresses from the data cache to memory.
  *
  * @attention Requires linking to `psputils_user` or `psputils_kernel` stubs to be available.
  */
void sceKernelDcacheWritebackRange(const void *p, unsigned int size);

/**
  * Write back and invalidate a range of addresses in the data cache.
  *
  * @attention Requires linking to `psputils_user` or `psputils_kernel` stubs to be available.
  */
void sceKernelDcacheWritebackInvalidateRange(const void *p, unsigned int size);

/**
  * Invalidate a range of addresses in data cache.
  *
  * @attention Requires linking to `psputils_user` or `psputils_kernel` stubs to be available.
  */
void sceKernelDcacheInvalidateRange(const void *p, unsigned int size);

/**
  * Invalidate the instruction cache.
  *
  * @attention Requires linking to `psputils_user` or `psputils_kernel` stubs to be available.
  */
void sceKernelIcacheInvalidateAll(void);

/**
  * Invalidate a range of addresses in the instruction cache.
  *
  * @attention Requires linking to `psputils_user` or `psputils_kernel` stubs to be available.
  */
void sceKernelIcacheInvalidateRange(const void *p, unsigned int size);

/**
  * Function to initialise a mersenne twister context.
  *
  * @param ctx A pointer to a context
  * @param seed - A seed for the random function.
  *
  * @par Example:
  * @code
  * SceKernelUtilsMt19937Context ctx;
  * sceKernelUtilsMt19937Init(&ctx, time(NULL));
  * u23 rand_val = sceKernelUtilsMt19937UInt(&ctx);
  * @endcode
  *
  * @return `< 0` on error.
  *
  * @attention Requires linking to `psputils_user` or `psputils_kernel` stubs to be available.
  */
int sceKernelUtilsMt19937Init(SceKernelUtilsMt19937Context *ctx, u32 seed);

/**
  * Function to return a new psuedo random number.
  *
  * @param ctx A pointer to a pre-initialised context.
  *
  * @return A pseudo random number (between `0` and `MAX_INT`).
  *
  * @attention Requires linking to `psputils_user` or `psputils_kernel` stubs to be available.
  */
u32 sceKernelUtilsMt19937UInt(SceKernelUtilsMt19937Context *ctx);

/**
  * Function to perform an MD5 digest of a data block.
  *
  * @param data A pointer to a data block to make a digest of.
  * @param size - Size of the data block.
  * @param digest A pointer to a 16byte buffer to store the resulting digest
  *
  * @return `< 0` on error.
  *
  * @attention Requires linking to `psputils_user` or `psputils_kernel` stubs to be available.
  */
int sceKernelUtilsMd5Digest(u8 *data, u32 size, u8 *digest);

/**
  * Function to initialise a MD5 digest context
  *
  * @param ctx A context block to initialise.
  *
  * @return `< 0` on error.
  * @par Example:
  * @code
  * SceKernelUtilsMd5Context ctx;
  * u8 digest[16];
  * sceKernelUtilsMd5BlockInit(&ctx);
  * sceKernelUtilsMd5BlockUpdate(&ctx, (u8*) "Hello", 5);
  * sceKernelUtilsMd5BlockResult(&ctx, digest);
  * @endcode
  *
  * @attention Requires linking to `psputils_user` or `psputils_kernel` stubs to be available.
  */
int sceKernelUtilsMd5BlockInit(SceKernelUtilsMd5Context *ctx);

/**
  * Function to update the MD5 digest with a block of data.
  *
  * @param ctx A filled in context block.
  * @param data The data block to hash.
  * @param size The size of the data to hash.
  *
  * @return `< 0` on error.
  *
  * @attention Requires linking to `psputils_user` or `psputils_kernel` stubs to be available.
  */
int sceKernelUtilsMd5BlockUpdate(SceKernelUtilsMd5Context *ctx, u8 *data, u32 size);

/**
  * Function to get the digest result of the MD5 hash.
  *
  * @param ctx A filled in context block.
  * @param digest A 16 byte array to hold the digest.
  *
  * @return `< 0` on error.
  *
  * @attention Requires linking to `psputils_user` or `psputils_kernel` stubs to be available.
  */
int sceKernelUtilsMd5BlockResult(SceKernelUtilsMd5Context *ctx, u8 *digest);


/**
  * Function to SHA1 hash a data block.
  *
  * @param data The data to hash.
  * @param size The size of the data.
  * @param digest A pointer to a 20 byte array for storing the digest.
  *
  * @return `< 0` on error.
  *
  * @attention Requires linking to `psputils_user` or `psputils_kernel` stubs to be available.
  */
int sceKernelUtilsSha1Digest(u8 *data, u32 size, u8 *digest);

/**
  * Function to initialise a context for SHA1 hashing.
  *
  * @param ctx A pointer to a context.
  *
  * @return `< 0` on error.
  *
  * @par Example:
  * @code
  * SceKernelUtilsSha1Context ctx;
  * u8 digest[20];
  * sceKernelUtilsSha1BlockInit(&ctx);
  * sceKernelUtilsSha1BlockUpdate(&ctx, (u8*) "Hello", 5);
  * sceKernelUtilsSha1BlockResult(&ctx, digest);
  * @endcode
  *
  * @attention Requires linking to `psputils_user` or `psputils_kernel` stubs to be available.
  */
int sceKernelUtilsSha1BlockInit(SceKernelUtilsSha1Context *ctx);

/**
  * Function to update the current hash.
  *
  * @param ctx A pointer to a prefilled context.
  * @param data The data block to hash.
  * @param size The size of the data block.
  *
  * @return `< 0` on error.
  *
  * @attention Requires linking to `psputils_user` or `psputils_kernel` stubs to be available.
  */
int sceKernelUtilsSha1BlockUpdate(SceKernelUtilsSha1Context *ctx, u8 *data, u32 size);

/**
  * Function to get the result of the SHA1 hash.
  *
  * @param ctx A pointer to a prefilled context.
  * @param digest A pointer to a 20 byte array to contain the digest.
  *
  * @return `< 0` on error.
  *
  * @attention Requires linking to `psputils_user` or `psputils_kernel` stubs to be available.
  */
int sceKernelUtilsSha1BlockResult(SceKernelUtilsSha1Context *ctx, u8 *digest);

/**@}*/

#ifdef __KERNEL__

/**
 * Decompress gzip'd data (requires kernel mode).
 *
 * @param[out] dest A pointer to destination buffer.
 * @param dest_size The size of destination buffer.
 * @param[in] src A pointer to source (compressed) data.
 * @param[in] unknown Unknown, pass `NULL`.
 *
 * @return The decompressed size on success, `< 0` on error.
 *
 * @attention Requires linking to `psputils_kernel` stub to be available.
 */
int sceKernelGzipDecompress(u8 *dest, u32 dest_size, const u8 *src, void *unknown);

/**
 * Decompress RLZ data (requires kernel mode)
 *
 * @param dest A pointer to destination buffer
 * @param dest_size The size of destination buffer
 * @param[in] src A pointer to source (compressed) data
 * @param[in] unknown Unknown, pass `NULL`
 *
 * @return The decompressed size on success, `< 0` on error.
 *
 * @attention Requires linking to `psputils_kernel` stub to be available.
 */
int sceKernelLzrcDecode(u8 *dest, u32 dest_size, const u8 *src, void *unknown);

/**
 * Decompress inflate data (requires kernel mode)
 *
 * @param dest A pointer to destination buffer
 * @param dest_size The size of destination buffer
 * @param[in] src A pointer to source (compressed) data
 * @param[in] unknown Unknown, pass `NULL`.
 *
 * @return The decompressed size on success, `< 0` on error.
 *
 * @attention Requires linking to `psputils_kernel` stub to be available.
 */
int sceKernelDeflateDecompress(u8 *dest, u32 dest_size, const u8 *src, void *unknown);

/**
 * Invalidate the entire data cache.
 *
 * @attention Requires linking to `psputils_kernel` stub to be available.
 */
void sceKernelDcacheInvalidateAll(void);

/**
 * Check whether the specified address is in the data cache.
 *
 * @param[in] addr The address to check.
 *
 * @return `0` = not cached, `1` = cached.
 *
 * @attention Requires linking to `psputils_kernel` stub to be available.
 */
int  sceKernelDcacheProbe(void *addr);

/**
 * Invalidate the entire instruction cache.
 *
 * @attention Requires linking to `psputils_kernel` stub to be available.
 */
void sceKernelIcacheInvalidateAll(void);

/**
 * Invalidate a instruction cache range.
 *
 * @param[in] addr The start address of the range.
 * @param size The size in bytes.
 *
 * @attention Requires linking to `psputils_kernel` stub to be available.
 */
void sceKernelIcacheInvalidateRange(const void *addr, unsigned int size);

/**
 * Check whether the specified address is in the instruction cache.
 *
 * @param[in] addr The address to check.
 *
 * @return `0` = not cached, `1` = cached.
 *
 * @attention Requires linking to `psputils_kernel` stub to be available.
 */
int  sceKernelIcacheProbe(const void *addr);

#endif /* __KERNEL__ */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __UTILS_H__ */
