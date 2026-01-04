/*
 * PSP Software Development Kit - https://github.com/pspdev
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * pspopenpsid.h - Prototypes for the OpenPSID and sceOpenPSID_driver libraries
 *
 * Copyright (c) 2008 InsertWittyName (David Perry)
 *
 */

#ifndef __PSPOPENPSID_H__
#define __PSPOPENPSID_H__

#include <psptypes.h>

typedef struct PspOpenPSID {
	u8 data[16];
} SceOpenPSID;

typedef SceOpenPSID PspOpenPSID;

typedef struct {
	u8 unk[2];
} SceProductCode;

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Get the open PS ID.
 *
 * @param[out] openpsid A pointer to receive the `SceOpenPSID` data.
 *
 * @return `0` on success, `< 0` on error.
 *
 * @attention Requires linking to `pspopenpsid` or `pspopenpsid_driver` stubs to be available.
 */
int sceOpenPSIDGetOpenPSID(SceOpenPSID *openpsid);

#ifdef __USER__

/**
 * Get the product code.
 *
 * @param[out] prod_code A pointer to receive the `SceProductCode` data.
 *
 * @return `0` on success, `< 0` on error.
 *
 * @attention Requires linking to `pspopenpsid` (PSPSDK) or `pspopenpsid_user` (Adrenaline stubs) stubs to be available.
 */
int sceOpenPSIDGetProductCode(SceProductCode *prod_code);

#endif // __USER__

#ifdef __cplusplus
}
#endif

#endif	/* __PSPOPENPSID_H__ */
