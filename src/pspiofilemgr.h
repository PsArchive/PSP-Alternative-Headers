/*
 * PSP Software Development Kit - https://github.com/pspdev
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * pspiofilemgr.h - Prototypes for the sceIo library.
 *
 * Copyright (c) 2005 Marcus R. Brown <mrbrown@ocgnet.org>
 * Copyright (c) 2005 James Forshaw <tyranid@gmail.com>
 * Copyright (c) 2005 John Kelley <ps2dev@kelley.ca>
 *
 */
#ifndef __FILEIO_H__
#define __FILEIO_H__
// Protect from double definition of mixing our modified header with pspsdk header
#define PSPIOFILEMGR_KERNEL_H

#include <psptypes.h>
#include <pspkerneltypes.h>
#include <pspiofilemgr_stat.h>
#include <pspiofilemgr_fcntl.h>
#include <pspiofilemgr_dirent.h>
#include <pspiofilemgr_devctl.h>

/** @defgroup FileIO File IO Library
 *  This module contains the imports for the kernel's IO routines.
 */

/** @addtogroup FileIO File IO Library */
/**@{*/

/** Permission value for the sceIoAssign function */
enum IoAssignPerms {
	/** Assign the device read/write */
	IOASSIGN_RDWR = 0,
	/** Assign the device read only */
	IOASSIGN_RDONLY = 1
};

struct PspIoDrv;

/** Structure passed to the init and exit functions of the io driver system */
typedef struct PspIoDrvArg {
	/** Pointer to the original driver which was added */
	struct PspIoDrv *drv;
	/** Pointer to a user defined argument (if written by the driver will preseve across calls */
	void *arg;
} PspIoDrvArg;

/** Structure passed to the file functions of the io driver system */
typedef struct PspIoDrvFileArg {
	/** Unknown */
	u32 unk1;
	/** The file system number, e.g. if a file is opened as host5:/myfile.txt this field will be 5 */
	u32 fs_num;
	/** Pointer to the driver structure */
	PspIoDrvArg *drv;
	/** Unknown, again */
	u32 unk2;
	/** Pointer to a user defined argument, this is preserved on a per file basis */
	void *arg;
} PspIoDrvFileArg;

/** Structure to maintain the file driver pointers */
typedef struct PspIoDrvFuncs {
	int (*IoInit)(PspIoDrvArg* arg);
	int (*IoExit)(PspIoDrvArg* arg);
	int (*IoOpen)(PspIoDrvFileArg *arg, char *file, int flags, SceMode mode);
	int (*IoClose)(PspIoDrvFileArg *arg);
	int (*IoRead)(PspIoDrvFileArg *arg, char *data, int len);
	int (*IoWrite)(PspIoDrvFileArg *arg, const char *data, int len);
	SceOff (*IoLseek)(PspIoDrvFileArg *arg, SceOff ofs, int whence);
	int (*IoIoctl)(PspIoDrvFileArg *arg, unsigned int cmd, void *indata, int inlen, void *outdata, int outlen);
	int (*IoRemove)(PspIoDrvFileArg *arg, const char *name);
	int (*IoMkdir)(PspIoDrvFileArg *arg, const char *name, SceMode mode);
	int (*IoRmdir)(PspIoDrvFileArg *arg, const char *name);
	int (*IoDopen)(PspIoDrvFileArg *arg, const char *dirname);
	int (*IoDclose)(PspIoDrvFileArg *arg);
	int (*IoDread)(PspIoDrvFileArg *arg, SceIoDirent *dir);
	int (*IoGetstat)(PspIoDrvFileArg *arg, const char *file, SceIoStat *stat);
	int (*IoChstat)(PspIoDrvFileArg *arg, const char *file, SceIoStat *stat, int bits);
	int (*IoRename)(PspIoDrvFileArg *arg, const char *oldname, const char *newname);
	int (*IoChdir)(PspIoDrvFileArg *arg, const char *dir);
	int (*IoMount)(PspIoDrvFileArg *arg);
	int (*IoUmount)(PspIoDrvFileArg *arg);
	int (*IoDevctl)(PspIoDrvFileArg *arg, const char *devname, unsigned int cmd, void *indata, int inlen, void *outdata, int outlen);
	int (*IoUnk21)(PspIoDrvFileArg *arg);
} PspIoDrvFuncs;

typedef struct PspIoDrv {
	/** The name of the device to add */
	const char *name;
	/** Device type, this 0x10 is for a filesystem driver */
	u32 dev_type;
	/** Unknown, set to 0x800 */
	u32 unk2;
	/** This seems to be the same as name but capitalised :/ */
	const char *name2;
	/** Pointer to a filled out functions table */
	PspIoDrvFuncs *funcs;
} PspIoDrv;

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
 * Open or create a file for reading or writing.
 *
 * @par Example1: Open a file for reading
 * @code
 * if(!(fd = sceIoOpen("device:/path/to/file", O_RDONLY, 0777)) {
 *	// error
 * }
 * @endcode
 * @par Example2: Open a file for writing, creating it if it doesnt exist
 * @code
 * if(!(fd = sceIoOpen("device:/path/to/file", O_WRONLY|O_CREAT, 0777)) {
 *	// error
 * }
 * @endcode
 *
 * @param file A pointer to a string holding the name of the file to open.
 * @param flags A libc styled flags that are or'ed together.
 * @param mode The file access mode.
 *
 * @return A non-negative integer is a valid fd, anything else an error.
 *
 * @attention Requires linking to `pspiofilemgr_user` or `pspiofilemgr_kernel` stubs to be available.
 */
SceUID sceIoOpen(const char *file, int flags, SceMode mode);

/**
 * Open or create a file for reading or writing (asynchronous).
 *
 * @param file A pointer to a string holding the name of the file to open.
 * @param flags A libc styled flags that are or'ed together.
 * @param mode The file access mode.
 *
 * @return A non-negative integer is a valid fd, anything else an error.
 *
 * @attention Requires linking to `pspiofilemgr_user` or `pspiofilemgr_kernel` stubs to be available.
 */
SceUID sceIoOpenAsync(const char *file, int flags, SceMode mode);

/**
 * Delete a descriptor.
 *
 * @code
 * sceIoClose(fd);
 * @endcode
 *
 * @param fd A file descriptor to close.
 *
 * @return `< 0` on error.
 *
 * @attention Requires linking to `pspiofilemgr_user` or `pspiofilemgr_kernel` stubs to be available.
 */
int sceIoClose(SceUID fd);

/**
 * Delete a descriptor (asynchronous).
 *
 * @param fd A file descriptor to close.
 *
 * @return `< 0` on error.
 *
 * @attention Requires linking to `pspiofilemgr_user` or `pspiofilemgr_kernel` stubs to be available.
 */
int sceIoCloseAsync(SceUID fd);

/**
 * Read input.
 *
 * @par Example:
 * @code
 * bytes_read = sceIoRead(fd, data, 100);
 * @endcode
 *
 * @param fd A opened file descriptor to read from.
 * @param data A pointer to the buffer where the read data will be placed.
 * @param size The size of the read in bytes.
 *
 * @return The number of bytes read.
 *
 * @attention Requires linking to `pspiofilemgr_user` or `pspiofilemgr_kernel` stubs to be available.
 */
int sceIoRead(SceUID fd, void *data, SceSize size);

/**
 * Read input (asynchronous).
 *
 * @par Example:
 * @code
 * bytes_read = sceIoRead(fd, data, 100);
 * @endcode
 *
 * @param fd A opened file descriptor to read from.
 * @param data A pointer to the buffer where the read data will be placed.
 * @param size The size of the read in bytes.
 *
 * @return `< 0` on error.
 *
 * @attention Requires linking to `pspiofilemgr_user` or `pspiofilemgr_kernel` stubs to be available.
 */
int sceIoReadAsync(SceUID fd, void *data, SceSize size);

/**
 * Write output.
 *
 * @par Example:
 * @code
 * bytes_written = sceIoWrite(fd, data, 100);
 * @endcode
 *
 * @param fd A opened file descriptor to write to.
 * @param data A pointer to the data to write.
 * @param size The size of data to write.
 *
 * @return The number of bytes written.
 *
 * @attention Requires linking to `pspiofilemgr_user` or `pspiofilemgr_kernel` stubs to be available.
 */
int sceIoWrite(SceUID fd, const void *data, SceSize size);

/**
 * Write output (asynchronous).
 *
 * @param fd A opened file descriptor to write to.
 * @param data A pointer to the data to write.
 * @param size The size of data to write.
 *
 * @return `< 0` on error.
 *
 * @attention Requires linking to `pspiofilemgr_user` or `pspiofilemgr_kernel` stubs to be available.
 */
int sceIoWriteAsync(SceUID fd, const void *data, SceSize size);

/**
 * Reposition read/write file descriptor offset.
 *
 * @par Example:
 * @code
 * pos = sceIoLseek(fd, -10, SEEK_END);
 * @endcode
 *
 * @param fd A opened file descriptor with which to seek
 * @param offset The relative offset from the start position given by whence
 * @param whence The set to SEEK_SET to seek from the start of the file, SEEK_CUR
 * seek from the current position and SEEK_END to seek from the end.
 *
 * @return The position in the file after the seek.
 *
 * @attention Requires linking to `pspiofilemgr_user` or `pspiofilemgr_kernel` stubs to be available.
 */
SceOff sceIoLseek(SceUID fd, SceOff offset, int whence);

/**
 * Reposition read/write file descriptor offset (asynchronous).
 *
 * @param fd A opened file descriptor with which to seek.
 * @param offset The relative offset from the start position given by whence.
 * @param whence A set to SEEK_SET to seek from the start of the file, SEEK_CUR
 * seek from the current position and SEEK_END to seek from the end.
 *
 * @return `< 0` on error. Actual value should be passed returned by the `sceIoWaitAsync` call.
 *
 * @attention Requires linking to `pspiofilemgr_user` or `pspiofilemgr_kernel` stubs to be available.
 */
int sceIoLseekAsync(SceUID fd, SceOff offset, int whence);

/**
 * Reposition read/write file descriptor offset (32bit mode).
 *
 * @par Example:
 * @code
 * pos = sceIoLseek32(fd, -10, SEEK_END);
 * @endcode
 *
 * @param fd A opened file descriptor with which to seek.
 * @param offset The relative offset from the start position given by whence.
 * @param whence The set to SEEK_SET to seek from the start of the file, SEEK_CUR
 * seek from the current position and SEEK_END to seek from the end.
 *
 * @return The position in the file after the seek.
 *
 * @attention Requires linking to `pspiofilemgr_user` or `pspiofilemgr_kernel` stubs to be available.
 */
int sceIoLseek32(SceUID fd, int offset, int whence);

/**
 * Reposition read/write file descriptor offset (32bit mode, asynchronous).
 *
 * @param fd A opened file descriptor with which to seek.
 * @param offset The relative offset from the start position given by whence.
 * @param whence The set to SEEK_SET to seek from the start of the file, SEEK_CUR
 * seek from the current position and SEEK_END to seek from the end.
 *
 * @return `< 0` on error.
 *
 * @attention Requires linking to `pspiofilemgr_user` or `pspiofilemgr_kernel` stubs to be available.
 */
int sceIoLseek32Async(SceUID fd, int offset, int whence);

/**
 * Remove directory entry.
 *
 * @param file The path to the file to remove.
 *
 * @return `< 0` on error.
 *
 * @attention Requires linking to `pspiofilemgr_user` or `pspiofilemgr_kernel` stubs to be available.
 */
int sceIoRemove(const char *file);

/**
 * Make a directory file.
 *
 * @param dir The directory path to create.
 * @param mode The access mode.
 *
 * @return Returns the value `0` if its successful otherwise `-1`.
 *
 * @attention Requires linking to `pspiofilemgr_user` or `pspiofilemgr_kernel` stubs to be available.
 */
int sceIoMkdir(const char *dir, SceMode mode);

/**
 * Remove a directory file.
 *
 * @param path The directory path to remove.
 *
 * @return Returns the value `0` if its succesful otherwise `-1`.
 *
 * @attention Requires linking to `pspiofilemgr_user` or `pspiofilemgr_kernel` stubs to be available.
 */
int sceIoRmdir(const char *path);

/**
  * Change the current directory.
  *
  * @param path The path to change to.
  *
  * @return `< 0` on error.
  *
  * @attention Requires linking to `pspiofilemgr_user` or `pspiofilemgr_kernel` stubs to be available.
  */
int sceIoChdir(const char *path);

/**
 * Change the name of a file.
 *
 * @param oldname The old filename.
 * @param newname The new filename.
 *
 * @return `< 0` on error.
 *
 * @attention Requires linking to `pspiofilemgr_user` or `pspiofilemgr_kernel` stubs to be available.
 */
int sceIoRename(const char *oldname, const char *newname);

/**
  * Open a directory.
  *
  * @par Example:
  * @code
  * int dfd;
  * dfd = sceIoDopen("device:/");
  * if(dfd >= 0)
  * { Do something with the file descriptor }
  * @endcode
  *
  * @param dirname The directory to open for reading.
  *
  * @return If `>= 0` then a valid file descriptor, otherwise a Sony error code.
  *
  * @attention Requires linking to `pspiofilemgr_user` or `pspiofilemgr_kernel` stubs to be available.
  */
SceUID sceIoDopen(const char *dirname);

/**
  * Reads an entry from an opened file descriptor.
  *
  * @param fd An already opened file descriptor (using sceIoDopen).
  * @param dir A pointer to an io_dirent_t structure to hold the file information.
  *
  * @return Read status
  * -   `0` - No more directory entries left
  * - `> 0` - More directory entired to go
  * - `< 0` - Error
  *
  * @attention Requires linking to `pspiofilemgr_user` or `pspiofilemgr_kernel` stubs to be available.
  */
int sceIoDread(SceUID fd, SceIoDirent *dir);

/**
  * Close an opened directory file descriptor.
  *
  * @param fd An already opened file descriptor (using sceIoDopen).
  *
  * @return `< 0` on error.
  *
  * @attention Requires linking to `pspiofilemgr_user` or `pspiofilemgr_kernel` stubs to be available.
  */
int sceIoDclose(SceUID fd);

/**
  * Send a devctl command to a device.
  *
  * @par Example: Sending a simple command to a device (not a real devctl)
  * @code
  * sceIoDevctl("ms0:", 0x200000, indata, 4, NULL, NULL);
  * @endcode
  *
  * @param dev String for the device to send the devctl to (e.g. "ms0:").
  * @param cmd The command to send to the device.
  * @param indata A data block to send to the device, if `NULL` sends no data.
  * @param inlen Length of indata, if `0` sends no data.
  * @param outdata A data block to receive the result of a command, if `NULL` receives no data.
  * @param outlen Length of outdata, if `0` receives no data.
  *
  * @return `0` on success, `< 0` on error.
  *
  * @attention Requires linking to `pspiofilemgr_user` or `pspiofilemgr_kernel` stubs to be available.
  */
int sceIoDevctl(const char *dev, unsigned int cmd, void *indata, int inlen, void *outdata, int outlen);

/**
  * Assigns one IO device to another (I guess).
  *
  * @param dev1 The device name to assign.
  * @param dev2 The block device to assign from.
  * @param dev3 The filesystem device to map the block device to `dev1`.
  * @param mode Read/Write mode. One of IoAssignPerms.
  * @param unk1 Unknown, set to `NULL`.
  * @param unk2 Unknown, set to `0`.
  *
  * @return `< 0` on error.
  *
  * @par Example: Reassign flash0 in read/write mode.
  * @code
  *	sceIoUnassign("flash0");
  * sceIoAssign("flash0", "lflash0:0,0", "flashfat0:", IOASSIGN_RDWR, NULL, 0);
  * @endcode
  *
  * @attention Requires linking to `pspiofilemgr_user` or `pspiofilemgr_kernel` stubs to be available.
  */
int sceIoAssign(const char *dev1, const char *dev2, const char *dev3, int mode, void* unk1, long unk2);

/**
  * Unassign an IO device.
  *
  * @param dev The device to unassign.
  *
  * @return `< 0` on error.
  *
  * @par Example: See `sceIoAssign`
  *
  * @attention Requires linking to `pspiofilemgr_user` or `pspiofilemgr_kernel` stubs to be available.
  */
int sceIoUnassign(const char *dev);

/**
  * Get the status of a file.
  *
  * @param file The path to the file.
  * @param stat A pointer to an io_stat_t structure.
  *
  * @return `< 0` on error.
  *
  * @attention Requires linking to `pspiofilemgr_user` or `pspiofilemgr_kernel` stubs to be available.
  */
int sceIoGetstat(const char *file, SceIoStat *stat);

/**
  * Change the status of a file.
  *
  * @param file The path to the file.
  * @param stat A pointer to an io_stat_t structure.
  * @param bits Bitmask defining which bits to change.
  *
  * @return `< 0` on error.
  *
  * @attention Requires linking to `pspiofilemgr_user` or `pspiofilemgr_kernel` stubs to be available.
  */
int sceIoChstat(const char *file, SceIoStat *stat, int bits);

/**
  * Perform an ioctl on a device.
  *
  * @param fd Opened file descriptor to ioctl to.
  * @param cmd The command to send to the device.
  * @param indata A data block to send to the device, if `NULL` sends no data.
  * @param inlen Length of indata, if `0` sends no data.
  * @param outdata A data block to receive the result of a command, if `NULL` receives no data.
  * @param outlen Length of outdata, if `0` receives no data.
  *
  * @return `0` on success, `< 0` on error.
  *
  * @attention Requires linking to `pspiofilemgr_user` or `pspiofilemgr_kernel` stubs to be available.
  */
int sceIoIoctl(SceUID fd, unsigned int cmd, void *indata, int inlen, void *outdata, int outlen);

/**
  * Perform an ioctl on a device. (asynchronous)
  *
  * @param fd An opened file descriptor to ioctl to.
  * @param cmd The command to send to the device.
  * @param indata A data block to send to the device, if NULL sends no data.
  * @param inlen Length of indata, if 0 sends no data.
  * @param outdata A data block to receive the result of a command, if NULL receives no data.
  * @param outlen Length of outdata, if 0 receives no data.
  *
  * @return `0` on success, `< 0` on error.
  *
  * @attention Requires linking to `pspiofilemgr_user` or `pspiofilemgr_kernel` stubs to be available.
  */
int sceIoIoctlAsync(SceUID fd, unsigned int cmd, void *indata, int inlen, void *outdata, int outlen);

/**
  * Synchronize the file data on the device.
  *
  * @param device The device to synchronize (e.g. "msfat0:").
  * @param unk Unknown.
  *
  * @attention Requires linking to `pspiofilemgr_user` or `pspiofilemgr_kernel` stubs to be available.
  */
int sceIoSync(const char *device, unsigned int unk);

/**
  * Wait for asynchronous completion.
  *
  * @param fd The file descriptor which is current performing an asynchronous action.
  * @param res The result of the async action.
  *
  * @return `< 0` on error.
  *
  * @attention Requires linking to `pspiofilemgr_user` or `pspiofilemgr_kernel` stubs to be available.
  */
int sceIoWaitAsync(SceUID fd, SceInt64 *res);

/**
  * Wait for asynchronous completion (with callbacks).
  *
  * @param fd The file descriptor which is current performing an asynchronous action.
  * @param res The result of the async action.
  *
  * @return `< 0` on error.
  *
  * @attention Requires linking to `pspiofilemgr_user` or `pspiofilemgr_kernel` stubs to be available.
  */
int sceIoWaitAsyncCB(SceUID fd, SceInt64 *res);

/**
  * Poll for asyncronous completion.
  *
  * @param fd The file descriptor which is current performing an asynchronous action.
  * @param res The result of the async action.
  *
  * @return `< 0` on error.
  *
  * @attention Requires linking to `pspiofilemgr_user` or `pspiofilemgr_kernel` stubs to be available.
  */
int sceIoPollAsync(SceUID fd, SceInt64 *res);

/**
  * Get the asynchronous completion status.
  *
  * @param fd The file descriptor which is current performing an asynchronous action.
  * @param poll If `0` then waits for the status, otherwise it polls the fd.
  * @param res The result of the async action.
  *
  * @return `< 0` on error.
  *
  * @attention Requires linking to `pspiofilemgr_user` or `pspiofilemgr_kernel` stubs to be available.
  */
int sceIoGetAsyncStat(SceUID fd, int poll, SceInt64 *res);

/**
  * Cancel an asynchronous operation on a file descriptor.
  *
  * @param fd The file descriptor to perform cancel on.
  *
  * @return `< 0` on error.
  *
  * @attention Requires linking to `pspiofilemgr_user` or `pspiofilemgr_kernel` stubs to be available.
  */
int sceIoCancel(SceUID fd);

/**
  * Get the device type of the currently opened file descriptor.
  *
  * @param fd The opened file descriptor.
  *
  * @return `< 0` on error. Otherwise the device type?
  *
  * @attention Requires linking to `pspiofilemgr_user` or `pspiofilemgr_kernel` stubs to be available.
  */
int sceIoGetDevType(SceUID fd);

/**
  * Change the priority of the asynchronous thread.
  *
  * @param fd The opened fd on which the priority should be changed.
  * @param pri The priority of the thread.
  *
  * @return `< 0` on error.
  *
  * @attention Requires linking to `pspiofilemgr_user` or `pspiofilemgr_kernel` stubs to be available.
  */
int sceIoChangeAsyncPriority(SceUID fd, int pri);

/**
  * Sets a callback for the asynchronous action.
  *
  * @param fd The filedescriptor currently performing an asynchronous action.
  * @param cb The UID of the callback created with ::sceKernelCreateCallback
  * @param argp A pointer to an argument to pass to the callback.
  *
  * @return `< 0` on error.
  *
  * @attention Requires linking to `pspiofilemgr_user` or `pspiofilemgr_kernel` stubs to be available.
  */
int sceIoSetAsyncCallback(SceUID fd, SceUID cb, void *argp);


#ifdef __KERNEL__

/**
  * Adds a new IO driver to the system.
  *
  * @param drv A pointer to a filled out driver structure.
  *
  * @return `< 0` on error.
  *
  * @par Example:
  * @code
  * PspIoDrvFuncs host_funcs = { ... };
  * PspIoDrv host_driver = { "host", 0x10, 0x800, "HOST", &host_funcs };
  * sceIoDelDrv("host");
  * sceIoAddDrv(&host_driver);
  * @endcode
  *
  * @attention Requires linking to `pspiofilemgr_kernel` stub to be available.
  */
int sceIoAddDrv(PspIoDrv *drv);

/**
  * Deletes a IO driver from the system.
  *
  * @param drv_name The name of the driver to delete.
  *
  * @return `< 0` on error.
  *
  * @attention Requires linking to `pspiofilemgr_kernel` stub to be available.
  */
int sceIoDelDrv(const char *drv_name);

/**
  * Reopens an existing file descriptor.
  *
  * @param file The new file to open.
  * @param flags The open flags.
  * @param mode The open mode.
  * @param fd The old filedescriptor to reopen.
  *
  * @return `< 0` on error, otherwise the reopened fd.
  *
  * @attention Requires linking to `pspiofilemgr_kernel` stub to be available.
  */
int sceIoReopen(const char *file, int flags, SceMode mode, SceUID fd);

/**
 * Get the current working directory for a thread.
 *
 * @param uid The UID of the thread.
 * @param dir A character buffer in which to store the cwd.
 * @param len The length of the buffer.
 *
 * @return Number of characters written to buf, if no cwd then `0` is
 * returned.
 *
 * @attention Requires linking to `pspiofilemgr_kernel` stub to be available.
 */
int sceIoGetThreadCwd(SceUID uid, char *dir, int len);

/**
 * Set the current working directory for a thread.
 *
 * @param uid The UID of the thread.
 * @param dir The directory to set.
 *
 * @return `0` on success, `< 0` on error.
 *
 * @attention Requires linking to `pspiofilemgr_kernel` stub to be available.
 */
int sceIoChangeThreadCwd(SceUID uid, char *dir);

#endif /* __KERNEL__ */



/**@}*/

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif
