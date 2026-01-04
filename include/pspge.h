/*
 * PSP Software Development Kit - https://github.com/pspdev
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * pspge.h - Prototypes for the sceGe library.
 *
 * Copyright (c) 2005 Marcus R. Brown <mrbrown@ocgnet.org>
 * Copyright (c) 2005 James Forshaw <tyranid@gmail.com>
 * Copyright (c) 2005 John Kelley <ps2dev@kelley.ca>
 *
 */
#ifndef __GE_H__
#define __GE_H__

#include <psptypes.h>

/** Stores the state of the GE. */
typedef struct PspGeContext {
	u32 context[512];
} PspGeContext;

/** Structure storing a stack (for CALL/RET) */
typedef struct {
	/** The stack buffer */
	u32 stack[8];
} SceGeStack;

/** Typedef for a GE callback */
typedef void (*PspGeCallback)(int id, void *arg);

/** Structure to hold the callback data */
typedef struct PspGeCallbackData {
	/** GE callback for the signal interrupt */
	PspGeCallback signal_func;
	/** GE callback argument for signal interrupt */
	void *signal_arg;
	/** GE callback for the finish interrupt */
	PspGeCallback finish_func;
	/** GE callback argument for finish interrupt */
	void *finish_arg;
} PspGeCallbackData;

typedef struct PspGeListArgs {
	/** Size of the structure (16) */
	u32	size;
	/** Pointer to a context */
	PspGeContext*	context;
	/** Number of stacks to use */
	u32 numStacks;
	/** Pointer to the stacks (unused) */
	SceGeStack *stacks;
} PspGeListArgs;

/**
 * Drawing queue interruption parameter
 */
typedef struct PspGeBreakParam {
	u32 buf[4];
} PspGeBreakParam;

/** GE matrix types. */
typedef enum PspGeMatrixTypes {
	/** Bone matrices. */
	PSP_GE_MATRIX_BONE0 = 0,
	PSP_GE_MATRIX_BONE1,
	PSP_GE_MATRIX_BONE2,
	PSP_GE_MATRIX_BONE3,
	PSP_GE_MATRIX_BONE4,
	PSP_GE_MATRIX_BONE5,
	PSP_GE_MATRIX_BONE6,
	PSP_GE_MATRIX_BONE7,
	/** World matrix. */
	PSP_GE_MATRIX_WORLD,
	/** View matrix. */
	PSP_GE_MATRIX_VIEW,
	/** Projection matrix. */
	PSP_GE_MATRIX_PROJECTION,
	PSP_GE_MATRIX_TEXGEN
} PspGeMatrixTypes;

/** List status for `sceGeListSync()` and `sceGeDrawSync()`. */
typedef enum PspGeListState {
	PSP_GE_LIST_DONE = 0,
	PSP_GE_LIST_QUEUED,
	PSP_GE_LIST_DRAWING_DONE,
	PSP_GE_LIST_STALL_REACHED,
	PSP_GE_LIST_CANCEL_DONE
} PspGeListState;

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

/**
 * Get the size of VRAM.
 *
 * @return The size of VRAM (in bytes).
 *
 * @attention Requires linking to `pspge_user`  or `pspge_driver` stubs to be available.
 */
u32 sceGeEdramGetSize(void);

/**
 * Sets the EDRAM size to be enabled.
 *
 * @param size The size (0x200000 or 0x400000). Will return an error if 0x400000 is specified for the PSP FAT.
 *
 * @return Zero on success, otherwise less than zero.
 *
 * @attention Requires linking to `pspge_user`  or `pspge_driver` stubs to be available.
 */
int sceGeEdramSetSize(int size);

/**
  * Get the eDRAM address.
  *
  * @return A pointer to the base of the eDRAM.
  */
void * sceGeEdramGetAddr(void);

/**
 * Retrieve the current value of a GE command.
 *
 * @param cmd The GE command register to retrieve (0 to 0xFF, both included).
 *
 * @return The value of the GE command, < 0 on error.
 *
 * @attention Requires linking to `pspge_user`  or `pspge_driver` stubs to be available.
 */
u32 sceGeGetCmd(int cmd);

/**
 * Retrieve a matrix of the given type.
 *
 * @param type - One of ::PspGeMatrixTypes.
 * @param matrix - Pointer to a variable to store the matrix.
 *
 * @return < 0 on error.
 *
 * @attention Requires linking to `pspge_user`  or `pspge_driver` stubs to be available.
 */
int sceGeGetMtx(int type, void *matrix);

/** Structure storing a stack (for CALL/RET). */
typedef struct{
	/** The stack buffer. */
	u32 stack[8];
} PspGeStack;

/**
 * Retrieve the stack of the display list currently being executed.
 *
 * @param stackId The ID of the stack to retrieve.
 * @param stack A pointer to a structure to store the stack, or NULL to not store it.
 *
 * @return The number of stacks of the current display list, `< 0` on error.
 *
 * @attention Requires linking to `pspge_user`  or `pspge_driver` stubs to be available.
 */
int sceGeGetStack(int stackId, PspGeStack *stack);

/**
 * Save the GE's current state.
 *
 * @param context A pointer to a ::PspGeContext.
 *
 * @return `< 0` on error.
 *
 * @attention Requires linking to `pspge_user`  or `pspge_driver` stubs to be available.
 */
int sceGeSaveContext(PspGeContext *context);

/**
 * Restore a previously saved GE context.
 *
 * @param context A pointer to a ::PspGeContext.
 *
 * @return `< 0` on error.
 *
 * @attention Requires linking to `pspge_user`  or `pspge_driver` stubs to be available.
 */
int sceGeRestoreContext(const PspGeContext *context);

/**
  * Enqueue a display list at the tail of the GE display list queue.
  *
  * @param[in] list The head of the list to queue.
  * @param[in] stall The stall address. If `NULL` then no stall address is set and the list is transferred immediately.
  * @param cb_id The ID of the callback set by calling `sceGeSetCallback()`
  * @param[in] arg The structure containing GE context buffer address
  *
  * @return The ID of the queue, `< 0` on error.
  *
  * @attention Requires linking to `pspge_user`  or `pspge_driver` stubs to be available.
  */
int sceGeListEnQueue(const void *list, void *stall, int cb_id, PspGeListArgs *arg);

/**
  * Enqueue a display list at the head of the GE display list queue.
  *
  * @param list The head of the list to queue.
  * @param stall The stall address. If `NULL` then no stall address is set and the list is transferred immediately.
  * @param cb_id The ID of the callback set by calling sceGeSetCallback
  * @param arg The structure containing GE context buffer address
  *
  * @return The ID of the queue, `< 0` on error.
  *
  * @attention Requires linking to `pspge_user`  or `pspge_driver` stubs to be available.
  */
int sceGeListEnQueueHead(const void *list, void *stall, int cb_id, PspGeListArgs *arg);

/**
 * Cancel a queued or running list.
 *
 * @param queue_id The ID of the queue.
 *
 * @return `< 0` on error.
 *
 * @attention Requires linking to `pspge_user`  or `pspge_driver` stubs to be available.
 */
int sceGeListDeQueue(int queue_id);

/**
  * Update the stall address for the specified queue.
  *
  * @param queue_id The ID of the queue.
  * @param[in] stall The new stall address.
  *
  * @return `< 0` on error.
  *
  * @attention Requires linking to `pspge_user`  or `pspge_driver` stubs to be available.
  */
int sceGeListUpdateStallAddr(int queue_id, void *stall);

/**
  * Wait for syncronization of a list.
  *
  * @param queue_id - The queue ID of the list to sync.
  * @param sync_kind - 0 if you want to wait for the list to be completed, or 1 if you just want to peek the actual state.
  *
  * @return The specified queue status, one of `PspGeListState`.
  *
  * @attention Requires linking to `pspge_user`  or `pspge_driver` stubs to be available.
  */
int sceGeListSync(int queue_id, int sync_kind);

/**
  * Wait for drawing to complete.
  *
  * @param sync_kind - 0 if you want to wait for the drawing to be completed, or 1 if you just want to peek the state of the display list currently being executed.
  *
  * @return The current queue status, one of `PspGeListState`.
  *
  * @attention Requires linking to `pspge_user`  or `pspge_driver` stubs to be available.
  */
int sceGeDrawSync(int sync_kind);

/**
  * Register callback handlers for the the GE.
  *
  * @param[in] callback A pointer to a configured callback data structure.
  *
  * @return The callback ID, `< 0` on error.
  *
  * @attention Requires linking to `pspge_user`  or `pspge_driver` stubs to be available.
  */
int sceGeSetCallback(PspGeCallbackData *callback);

/**
  * Unregister the callback handlers.
  *
  * @param cb_id The ID of the callbacks, returned by `sceGeSetCallback()`.
  *
  * @return `< 0` on error
  */
int sceGeUnsetCallback(int cb_id);

/**
 * Interrupt drawing queue.
 *
 * @param mode If set to 1, reset all the queues.
 * @param[inout] param Unused (just K1-checked).
 *
 * @return The stopped queue ID if mode isn't set to `0`, otherwise `0`, and `< 0` on error.
 *
 * @attention Requires linking to `pspge_user`  or `pspge_driver` stubs to be available.
 */
int sceGeBreak(int mode, PspGeBreakParam *param);

/**
 * Restart drawing queue.
 *
 * @return `< 0` on error.
 *
 * @attention Requires linking to `pspge_user`  or `pspge_driver` stubs to be available.
 */
int sceGeContinue(void);

/**
 * Set the eDRAM address translation mode.
 *
 * @param width The translation width. 0 to not set the translation width, otherwise 512, 1024, 2048 or 4096.
 *
 * @return The previous width if it was set, otherwise `0`, `< 0` on error.
 *
 * @attention Requires linking to `pspge_user`  or `pspge_driver` stubs to be available.
 */
int sceGeEdramSetAddrTranslation(int width);


#ifdef __cplusplus
}
#endif

#endif /* __GE_H__ */
