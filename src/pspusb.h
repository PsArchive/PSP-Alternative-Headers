/*
 * PSP Software Development Kit - https://github.com/pspdev
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * pspusb.h - Prototypes for the sceUsb library
 *
 * Copyright (c) 2005 John Kelley <ps2dev@kelley.ca>
 *
 */
#ifndef __PSPUSB_H__
#define __PSPUSB_H__

#include <psptypes.h>


#define PSP_USBBUS_DRIVERNAME "USBBusDriver"

//Defines for use with status function return values
enum SceUsbStatus {
	SCE_USB_ACTIVATED = 0x200,
	SCE_USB_CABLE_CONNECTED = 0x020 ,
	SCE_USB_CONNECTION_ESTABLISHED = 0x002,

	PSP_USB_ACTIVATED = SCE_USB_ACTIVATED,
	PSP_USB_CABLE_CONNECTED = SCE_USB_CABLE_CONNECTED,
	PSP_USB_CONNECTION_ESTABLISHED = SCE_USB_CONNECTION_ESTABLISHED,
};

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

/**
  * Start a USB driver.
  *
  * @param[in] driver_name The name of the USB driver to start.
  * @param size The size of arguments to pass to USB driver start.
  * @param[in] args The arguments to pass to USB driver start.
  *
  * @return `0` on success
  *
  * @attention Requires linking to `pspusb` or `pspusb_driver` stubs to be available.
  */
int sceUsbStart(const char* driver_name, int size, void *args);

/**
  * Stop a USB driver.
  *
  * @param[in] driver_name The name of the USB driver to stop.
  * @param size The size of arguments to pass to USB driver stop.
  * @param[in] args The arguments to pass to USB driver stop.
  *
  * @return `0` on success.
  *
  * @attention Requires linking to `pspusb` or `pspusb_driver` stubs to be available.
  */
int sceUsbStop(const char* driver_name, int size, void *args);

/**
  * Activate a USB driver.
  *
  * @param pid The product ID for the default USB Driver.
  *
  * @return `0` on success.
  *
  * @attention Requires linking to `pspusb` or `pspusb_driver` stubs to be available.
  */
int sceUsbActivate(u32 pid);

/**
  * Deactivate USB driver.
  *
  * @param pid The product ID for the default USB driver.
  *
  * @return `0` on success.
  *
  * @attention Requires linking to `pspusb` or `pspusb_driver` stubs to be available.
  */
int sceUsbDeactivate(u32 pid);

/**
  * Get USB state.
  *
  * @return OR'd `SceUsbStatus` constants.
  *
  * @attention Requires linking to `pspusb` or `pspusb_driver` stubs to be available.
  */
int sceUsbGetState(void);

/**
  * Get state of a specific USB driver.
  *
  * @param[in] driver_name The name of USB driver to get status.
  *
  * @return `1` if the driver has been started, `2` if it is stopped.
  *
  * @attention Requires linking to `pspusb` or `pspusb_driver` stubs to be available.
  */
int sceUsbGetDrvState(const char* driver_name);

#if 0
int sceUsbGetDrvList(u32 r4one, u32* r5ret, u32 r6one);
int sceUsbWaitState(u32 state, s32 waitmode, u32 *timeout);
int sceUsbWaitCancel(void);
#endif

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // __PSPUSB_H__
