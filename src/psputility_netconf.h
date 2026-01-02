/*
 * PSP Software Development Kit - https://github.com/pspdev
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 *  psputility_netconf.h - Definitions and Functions for Network Configuration
 *                         section of the pspUtility library
 *
 * Copyright (c) 2005 John Kelley <ps2dev@kelley.ca>
 *
 */
#ifndef __PSPUTILITY_NETCONF_H__
#define __PSPUTILITY_NETCONF_H__

#include <psptypes.h>

enum pspUtilityNetconfActions {
	PSP_NETCONF_ACTION_CONNECTAP,
	PSP_NETCONF_ACTION_DISPLAYSTATUS,
	PSP_NETCONF_ACTION_CONNECT_ADHOC
};

struct pspUtilityNetconfAdhoc {
	u8 name[8];
	u32 timeout;
};

typedef struct _pspUtilityNetconfData {
	pspUtilityDialogCommon base;
	int action; /** One of pspUtilityNetconfActions */
	struct pspUtilityNetconfAdhoc *adhocparam; //* Adhoc connection params */
	int hotspot; /** Set to 1 to allow connections with the 'Internet Browser' option set to 'Start' (ie. hotspot connection) */
	int hotspot_connected; /** Will be set to 1 when connected to a hotspot style connection */
	int wifisp; /** Set to 1 to allow connections to Wifi service providers (WISP) */

} pspUtilityNetconfData;

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#ifdef __USER__

/**
 * Init the Network Configuration Dialog Utility
 *
 * @param data - pointer to pspUtilityNetconfData to be initialized
 * @return `0` on success, `< 0` on error.
 *
 * @attention Requires linking to `psputility` stub to be available.
 */
int sceUtilityNetconfInitStart (pspUtilityNetconfData *data);

/**
 * Shutdown the Network Configuration Dialog Utility
 *
 * @return `0` on success, `< 0` on error.
 *
 * @attention Requires linking to `psputility` stub to be available.
 */
int sceUtilityNetconfShutdownStart (void);

/**
 * Update the Network Configuration Dialog GUI
 *
 * @param unknown - unknown; set to 1
 * @return `0` on success, `< 0` on error.
 *
 * @attention Requires linking to `psputility` stub to be available.
 */
int sceUtilityNetconfUpdate (int unknown);

/**
 * Get the status of a running Network Configuration Dialog
 *
 * @return one of pspUtilityDialogState on success, < 0 on error
 *
 * @attention Requires linking to `psputility` stub to be available.
 */
int sceUtilityNetconfGetStatus (void);

#endif /* __USER__ */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __PSPUTILITY_NETCONF_H__ */
