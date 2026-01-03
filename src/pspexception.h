/*
 * PSP Software Development Kit - https://github.com/pspdev
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * pspexception.h - Interface to the kernel side of ExceptionMan
 *
 * Copyright (c) 2006 James F.
 *
 */

#ifndef PSPEXCEPTION_H
#define PSPEXCEPTION_H

#include <pspkerneltypes.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#ifdef __KERNEL__

/**
 * Register a default exception handler.
 *
 * @param func A pointer to the exception handler function.
 * @note The exception handler function must start with a `NOP` instructions.
 *
 * @return `0` on success, `< 0` on error.
 *
 * @attention Requires linking to `pspexceptionmanager_kernel` stub to be available.
 */
int sceKernelRegisterDefaultExceptionHandler(void *func);

/**
 * Register a exception handler.
 *
 * @param exno The exception number.
 * @param func A pointer to the exception handler function.
 *
 * @return `0` on success, `< 0` on error.
 *
 * @attention Requires linking to `pspexceptionmanager_kernel` stub to be available.
 */
int sceKernelRegisterExceptionHandler(int exno, void *func);

/**
 * Register a exception handler with a priority.
 *
 * @param exno The exception number.
 * @param priority The priority of the exception.
 * @param func A pointer to the exception handler function.
 *
 * @return `0` on success, `< 0` on error.
 *
 * @attention Requires linking to `pspexceptionmanager_kernel` stub to be available.
 */
int sceKernelRegisterPriorityExceptionHandler(int exno, int priority, void *func);

#endif /* __KERNEL__ */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* PSPEXCEPTION_H */
