/*
 * PSP Software Development Kit - https://github.com/pspdev
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * pspnand_driver.h - Definitions and interfaces to the NAND (flash) driver.
 *
 * Copyright (c) 2005 Marcus R. Brown <mrbrown@0xd6.org>
 *
 */

#ifndef PSPNAND_DRIVER_H
#define PSPNAND_DRIVER_H

#include <pspkerneltypes.h>
#include <psptypes.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/** @attention Requires linking to `pspnand_driver` stub to be available. */
int sceNandSetWriteProtect(int protectFlag);

/** @attention Requires linking to `pspnand_driver` stub to be available. */
int sceNandLock(int writeFlag);

/** @attention Requires linking to `pspnand_driver` stub to be available. */
void sceNandUnlock(void);

/** @attention Requires linking to `pspnand_driver` stub to be available. */
int sceNandReadStatus(void);

/** @attention Requires linking to `pspnand_driver` stub to be available. */
int sceNandReset(int flag);

/** @attention Requires linking to `pspnand_driver` stub to be available. */
int sceNandReadId(void *buf, SceSize size);

/** @attention Requires linking to `pspnand_driver` stub to be available. */
int sceNandReadPages(u32 ppn, void *buf, void *buf2, u32 count);

/** @attention Requires linking to `pspnand_driver` stub to be available. */
int sceNandReadPagesRawAll(u32 ppn, void* buf, void* spare, u32 count);

/*
// sceNandWritePages
// sceNandReadAccess
// sceNandCalcEcc
// sceNandVerifyEcc
// sceNandCollectEcc
*/

/** @attention Requires linking to `pspnand_driver` stub to be available. */
int sceNandEraseBlock(u32 ppn);

/** @attention Requires linking to `pspnand_driver` stub to be available. */
int sceNandWriteAccess(u32 ppn, void *buf, void *spare, int, unsigned int);

/** @attention Requires linking to `pspnand_driver` stub to be available. */
int sceNandReadExtraOnly(u32 ppn, void *buf, int);

/** @attention Requires linking to `pspnand_driver` stub to be available. */
int sceNandGetPageSize(void);

/** @attention Requires linking to `pspnand_driver` stub to be available. */
int sceNandGetPagesPerBlock(void);

/** @attention Requires linking to `pspnand_driver` stub to be available. */
int sceNandGetTotalBlocks(void);

/*
// sceNandWriteBlock
*/

/** @attention Requires linking to `pspnand_driver` stub to be available. */
int sceNandWriteBlockWithVerify(u32 ppn, void *buf, void *spare);

/** @attention Requires linking to `pspnand_driver` stub to be available. */
int sceNandReadBlockWithRetry(u32 ppn, void *buf, void *buf2);

/*
// sceNandVerifyBlockWithRetry
*/

/** @attention Requires linking to `pspnand_driver` stub to be available. */
int sceNandEraseBlockWithRetry(u32 ppn);

/** @attention Requires linking to `pspnand_driver` stub to be available. */
int sceNandIsBadBlock(u32 ppn);

/*
// sceNandEraseAllBlock
// sceNandTestBlock
*/

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* PSPNAND_DRIVER_H */
