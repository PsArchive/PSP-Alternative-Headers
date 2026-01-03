/*
 * PSP Software Development Kit - https://github.com/pspdev
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * pspsysevent.h - Prototypes for the sceSysEventForKernel library
 *
 * Copyright (c) 2007 Iaroslav Gaponenko <adrahil@gmail.com>
 *
 */
#ifndef __PSPSYSEVENT_H__
#define __PSPSYSEVENT_H__


typedef struct PspSysEventHandler _PspSysEventHandler;

typedef int (*PspSysEventHandlerFunc)(int ev_id, char* ev_name, void* param, int* result);

typedef struct PspSysEventHandler{
  int size;
  char* name;
  int type_mask;
  int (*handler)(int ev_id, char* ev_name, void* param, int* result);
  int r28;
  int busy;
  _PspSysEventHandler *next;
  int reserved[9];
} PspSysEventHandler;

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#ifdef __KERNEL__

/**
 * Dispatch a SysEvent event.
 *
 * @param ev_type_mask The event type mask.
 * @param ev_id The event id.
 * @param ev_name The event name.
 * @param param A pointer to the custom parameters.
 * @param result A pointer to the result.
 * @param break_nonzero Set to `1` to interrupt the calling chain after the first non-zero return.
 * @param break_handler The pointer to the event handler having interrupted.
 *
 * @return `0` on success, `< 0` on error.
 *
 * @attention Requires linking to `pspsysevent_kernel` stub to be available.
 */
int sceKernelSysEventDispatch(int ev_type_mask, int ev_id, char* ev_name, void* param, int* result, int break_nonzero, PspSysEventHandler* break_handler);


/**
 * Get the first SysEvent handler (the rest can be found with the linked list).
 *
 * @return `0` on error, handler on success.
 *
 * @attention Requires linking to `pspsysevent_kernel` stub to be available.
 */
PspSysEventHandler* sceKernelReferSysEventHandler(void);


/**
 * Check if a SysEvent handler is registered.
 *
 * @param handler The handler to check.
 *
 * @return `0` if the handler is not registered.
 *
 * @attention Requires linking to `pspsysevent_kernel` stub to be available.
 */
int sceKernelIsRegisterSysEventHandler(PspSysEventHandler* handler);


/**
 * Register a SysEvent handler.
 *
 * @param handler The handler to register.
 *
 * @return `0` on success, `< 0` on error.
 *
 * @attention Requires linking to `pspsysevent_kernel` stub to be available.
 */
int sceKernelRegisterSysEventHandler(PspSysEventHandler* handler);


/**
 * Unregister a SysEvent handler.
 *
 * @param handler The handler to unregister.
 *
 * @return `0` on success, `< 0` on error.
 *
 * @attention Requires linking to `pspsysevent_kernel` stub to be available.
 */
int sceKernelUnregisterSysEventHandler(PspSysEventHandler* handler);

#endif /* __KERNEL__ */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __PSPSYSEVENT_H__ */

