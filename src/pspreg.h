/*
 * PSP Software Development Kit - https://github.com/pspdev
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * pspreg.h - Prototypes for the sceReg and sceReg_driver libraries.
 *
 * Copyright (c) 2005 James F
 * Copyright (c) 2025 GrayJack
 *
 */

#ifndef __REG_H__
#define __REG_H__

#include <psptypes.h>

/** @addtogroup Reg Registry Kernel Library */
/**@{*/

/** System registry path */
#define SYSTEM_REGISTRY "/system"

/** Size of a keyname, used in ::sceRegGetKeys */
#define REG_KEYNAME_SIZE 27

/** Key types */
enum RegKeyTypes {
	/** Key is a directory */
	REG_TYPE_DIR = 1,
	/** Key is an integer (4 bytes) */
	REG_TYPE_INT = 2,
	/** Key is a string */
	REG_TYPE_STR = 3,
	/** Key is a binary string */
	REG_TYPE_BIN = 4,
};

/** Typedef for a registry handle */
typedef u32 REGHANDLE;

/** Typedef for a registry handle */
typedef u32 RegisterHandle;

/** Struct used to open a registry */
typedef struct RegParam {
	u32 regtype;     /* 0x0, set to 1 only for system */
	/** Seemingly never used, set to `SYSTEM_REGISTRY` */
	char name[256];        /* 0x4-0x104 */
	/** Length of the name */
	u32 namelen;     /* 0x104 */
	/** Unknown, set to 1 */
	u32 unk2;     /* 0x108 */
	/** Unknown, set to 1 */
	u32 unk3;     /* 0x10C */
} SceRegParam;

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

/**
 * Open the registry
 *
 * @param[in] reg_param A pointer to a `SceRegParam` structure
 * @param mode The open mode (set to 1)
 * @param[out] handle A pointer to a `RegisterHandle` to receive the handle.
 *
 * @return `0` on success, `< 0` on error.
 *
 * @attention Requires linking to `pspreg` (PSPSDK), `pspreg_user` (Adrenaline stubs)  or `pspreg_driver` stubs to be available.
 */
int sceRegOpenRegistry(SceRegParam *reg_param, int mode, RegisterHandle *handle);

/**
 * Flush the registry to disk.
 *
 * @param handle The open registry handle.
 *
 * @return `0` on success, `< 0` on error.
 *
 * @attention Requires linking to `pspreg` (PSPSDK), `pspreg_user` (Adrenaline stubs)  or `pspreg_driver` stubs to be available.
 */
int sceRegFlushRegistry(RegisterHandle handle);

/**
 * Close the registry.
 *
 * @param handle The open registry handle.
 *
 * @return `0` on success, `< 0` on error.
 *
 * @attention Requires linking to `pspreg` (PSPSDK), `pspreg_user` (Adrenaline stubs)  or `pspreg_driver` stubs to be available.
 */
int sceRegCloseRegistry(RegisterHandle handle);

/**
 * Open a registry directory.
 *
 * @param handle The open registry handle.
 * @param[in] name The path to the dir to open (e.g. /CONFIG/SYSTEM).
 * @param mode The open mode (can be 1 or 2, probably read or read/write).
 * @param[out] dir_handle A pointer to a RegisterHandle to receive the registry dir handle.
 *
 * @return `0` on success, `< 0` on error.
 *
 * @attention Requires linking to `pspreg` (PSPSDK), `pspreg_user` (Adrenaline stubs)  or `pspreg_driver` stubs to be available.
 */
int sceRegOpenCategory(RegisterHandle handle, const char *name, int mode, RegisterHandle *dir_handle);

/**
 * Remove a registry dir.
 *
 * @param dir_handle The open registry dir handle.
 * @param[in] name The name of the key.
 *
 * @return `0` on success, `< 0` on error.
 *
 * @attention Requires linking to `pspreg` (PSPSDK), `pspreg_user` (Adrenaline stubs)  or `pspreg_driver` stubs to be available.
 */
int sceRegRemoveCategory(RegisterHandle dir_handle, const char *name);

/**
 * Close the registry directory.
 *
 * @param dir_handle The open registry dir handle.
 *
 * @return `0` on success, `< 0` on error.
 *
 * @attention Requires linking to `pspreg` (PSPSDK), `pspreg_user` (Adrenaline stubs)  or `pspreg_driver` stubs to be available.
 */
int sceRegCloseCategory(RegisterHandle dir_handle);

/**
 * Flush the registry directory to disk.
 *
 * @param dir_handle The open registry dir handle.
 *
 * @return `0` on success, `< 0` on error.
 *
 * @attention Requires linking to `pspreg` (PSPSDK), `pspreg_user` (Adrenaline stubs)  or `pspreg_driver` stubs to be available.
 */
int sceRegFlushCategory(RegisterHandle dir_handle);

/**
 * Get a key's information
 *
 * @param dir_handle The open registry dir handle.
 * @param[in] name The name of the key.
 * @param[out] key_handle A pointer to a RegisterHandle to get registry key handle.
 * @param type The type of the key. One of `RegKeyTypes`.
 * @param size The size of the key's value in bytes.
 *
 * @return `0` on success, `< 0` on error.
 *
 * @attention Requires linking to `pspreg` (PSPSDK), `pspreg_user` (Adrenaline stubs)  or `pspreg_driver` stubs to be available.
 */
int sceRegGetKeyInfo(RegisterHandle dir_handle, const char *name, RegisterHandle *key_handle,u32 *type, SceSize *size);

/**
 * Get a key's information by name.
 *
 * @param dir_handle The open registry dir handle.
 * @param[out] name The name of the key.
 * @param[out] type The type of the key. One of `RegKeyTypes`.
 * @param[out] size The size of the key's value in bytes.
 *
 * @return `0` on success, `< 0` on error.
 *
 * @attention Requires linking to `pspreg` (PSPSDK), `pspreg_user` (Adrenaline stubs)  or `pspreg_driver` stubs to be available.
 */
int sceRegGetKeyInfoByName(RegisterHandle dir_handle, const char *name, u32 *type, SceSize *size);

/**
 * Get a key's value.
 *
 * @param dir_handle The open registry dir handle.
 * @param key_handle The open registry key handle (from `sceRegGetKeyInfo()`).
 * @param[out] buf The buffer to hold the value.
 * @param size The size of the buffer.
 *
 * @return `0` on success, `< 0` on error.
 *
 * @attention Requires linking to `pspreg` (PSPSDK), `pspreg_user` (Adrenaline stubs)  or `pspreg_driver` stubs to be available.
 */
int sceRegGetKeyValue(RegisterHandle dir_handle, RegisterHandle key_handle, void *buf, SceSize size);

/**
 * Get a key's value by name.
 *
 * @param dir_handle The open registry dir handle.
 * @param[in] name The key name.
 * @param[out] buf The buffer to hold the value.
 * @param size The size of the buffer.
 *
 * @return `0` on success, `< 0` on error.
 *
 * @attention Requires linking to `pspreg` (PSPSDK), `pspreg_user` (Adrenaline stubs)  or `pspreg_driver` stubs to be available.
 */
int sceRegGetKeyValueByName(RegisterHandle dir_handle, const char *name, void *buf, SceSize size);

/**
 * Set a key's value.
 *
 * @param dir_handle The open registry dir handle.
 * @param[in] name The key name.
 * @param[in] buf The buffer to hold the value.
 * @param size The size of the buffer.
 *
 * @return `0` on success, `< 0` on error.
 *
 * @attention Requires linking to `pspreg` (PSPSDK), `pspreg_user` (Adrenaline stubs)  or `pspreg_driver` stubs to be available.
 */
int sceRegSetKeyValue(RegisterHandle dir_handle, const char *name, const void *buf, SceSize size);

/**
 * Get number of subkeys in the current dir.
 *
 * @param dir_handle The open registry dir handle.
 * @param num A pointer to an integer to receive the number.
 *
 * @return `0` on success, `< 0` on error.
 *
 * @attention Requires linking to `pspreg` (PSPSDK), `pspreg_user` (Adrenaline stubs)  or `pspreg_driver` stubs to be available.
 */
int sceRegGetKeysNum(RegisterHandle dir_handle, int *num);

/**
 * Get the key names in the current directory.
 *
 * @param dir_handle The open registry dir handle.
 * @param[out] buf A buffer to hold the NUL terminated strings. It should be `num*REG_KEYNAME_SIZE`.
 * @param num - Number of elements in `buf`.
 *
 * @return `0` on success, `< 0` on error.
 *
 * @attention Requires linking to `pspreg` (PSPSDK), `pspreg_user` (Adrenaline stubs)  or `pspreg_driver` stubs to be available.
 */
int sceRegGetKeys(RegisterHandle hd, char *buf, int num);

/**
 * Create a key.
 *
 * @param dir_handle The open registry dir handle.
 * @param[in] name The name of the key to create.
 * @param type The type of key (note cannot be a directory type).
 * @param size The size of the allocated value space.
 *
 * @return `0` on success, `< 0` on error.
 *
 * @attention Requires linking to `pspreg` (PSPSDK), `pspreg_user` (Adrenaline stubs)  or `pspreg_driver` stubs to be available.
 */
int sceRegCreateKey(RegisterHandle dir_handle, const char *name, int type, SceSize size);

/**
 * Remove a registry (HONESTLY, DO NOT USE).
 *
 * @param reg The filled out registry parameter.
 *
 * @return `0` on success, `< 0` on error.
 *
 * @attention Requires linking to `pspreg` (PSPSDK), `pspreg_user` (Adrenaline stubs)  or `pspreg_driver` stubs to be available.
 */
int sceRegRemoveRegistry(SceRegParam *reg);

/**@}*/

#ifdef __cplusplus
}
#endif // __cplusplus

#endif
