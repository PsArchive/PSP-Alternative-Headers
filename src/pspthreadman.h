/*
 * PSP Software Development Kit - https://github.com/pspdev
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * pspthreadman.h - Library imports for the kernel threading library.
 *
 * Copyright (c) 2005 Marcus R. Brown <mrbrown@ocgnet.org>
 * Copyright (c) 2005 James Forshaw <tyranid@gmail.com>
 * Copyright (c) 2005 John Kelley <ps2dev@kelley.ca>
 * Copyright (c) 2005 Florin Sasu
 *
 */
#ifndef __THREADMAN_H__
#define __THREADMAN_H__
// Protect from double definition of mixing our modified header with pspsdk header
#define PSPTHREADMANKERNEL_H

#include <psptypes.h>
#include <pspkerneltypes.h>
/* Include for profile register definitions */
#include <pspdebug.h>

/* Note: Some of the structures, types, and definitions in this file were
   extrapolated from symbolic debugging information found in the Japanese
   version of Puzzle Bobble. */

/** @defgroup ThreadMan Thread Manager Library
  * Library imports for the kernel threading library.
  */

/** @addtogroup ThreadMan */

/**@{*/

/** 64-bit system clock type. */
typedef struct SceKernelSysClock {
	SceUInt32   low;
	SceUInt32   hi;
} SceKernelSysClock;

/** Attribute for threads. */
enum PspThreadAttributes {
	/** Enable VFPU access for the thread. */
	PSP_THREAD_ATTR_VFPU = 0x00004000,
	/** Start the thread in user mode (done automatically
	  if the thread creating it is in user mode). */
	PSP_THREAD_ATTR_USER = 0x80000000,
	/** Thread is part of the USB/WLAN API. */
	PSP_THREAD_ATTR_USBWLAN = 0xa0000000,
	/** Thread is part of the VSH API. */
	PSP_THREAD_ATTR_VSH = 0xc0000000,
	/** Allow using scratchpad memory for a thread, NOT USABLE ON V1.0 */
	PSP_THREAD_ATTR_SCRATCH_SRAM = 0x00008000,
	/** Disables filling the stack with 0xFF on creation */
	PSP_THREAD_ATTR_NO_FILLSTACK = 0x00100000,
	/** Clear the stack when the thread is deleted */
	PSP_THREAD_ATTR_CLEAR_STACK = 0x00200000,
};

/* Maintained for compatibility with older versions of PSPSDK. */
#define THREAD_ATTR_VFPU PSP_THREAD_ATTR_VFPU
#define THREAD_ATTR_USER PSP_THREAD_ATTR_USER


/* Threads. */

/** Additional options used when creating threads. */
typedef struct SceKernelThreadOptParam {
	/** Size of the `SceKernelThreadOptParam` structure. */
	SceSize 	size;
	/** UID of the memory block (?) allocated for the thread's stack. */
	SceUID 		stackMpid;
} SceKernelThreadOptParam;

/** Structure to hold the status information for a thread
  * @see sceKernelReferThreadStatus
  */
typedef struct SceKernelThreadInfo {
	/** Size of the structure */
	SceSize     size;
	/** Nul terminated name of the thread */
	char    	name[32];
	/** Thread attributes */
	SceUInt     attr;
	/** Thread status */
	int     	status;
	/** Thread entry point */
	SceKernelThreadEntry    entry;
	/** Thread stack pointer */
	void *  	stack;
	/** Thread stack size */
	int     	stackSize;
	/** Pointer to the gp */
	void *  	gpReg;
	/** Initial priority */
	int     	initPriority;
	/** Current priority */
	int     	currentPriority;
	/** Wait type */
	int     	waitType;
	/** Wait id */
	SceUID  	waitId;
	/** Wakeup count */
	int     	wakeupCount;
	/** Exit status of the thread */
	int     	exitStatus;
	/** Number of clock cycles run */
	SceKernelSysClock   runClocks;
	/** Interrupt preemption count */
	SceUInt     intrPreemptCount;
	/** Thread preemption count */
	SceUInt     threadPreemptCount;
	/** Release count */
	SceUInt     releaseCount;
} SceKernelThreadInfo;

/** Statistics about a running thread.
 * @see sceKernelReferThreadRunStatus.
 */
typedef struct SceKernelThreadRunStatus {
	SceSize 	size;
	int 		status;
	int 		currentPriority;
	int 		waitType;
	int 		waitId;
	int 		wakeupCount;
	SceKernelSysClock runClocks;
	SceUInt 	intrPreemptCount;
	SceUInt 	threadPreemptCount;
	SceUInt 	releaseCount;
} SceKernelThreadRunStatus;

/* Sure there must be more than this, but haven't seen them */
enum PspThreadStatus {
	PSP_THREAD_RUNNING = 1,
	PSP_THREAD_READY   = 2,
	PSP_THREAD_WAITING = 4,
	PSP_THREAD_SUSPEND = 8,
	PSP_THREAD_STOPPED = 16,
	PSP_THREAD_KILLED  = 32, /* Thread manager has killed the thread (stack overflow) */
};

/** Additional options used when creating semaphores. */
typedef struct SceKernelSemaOptParam {
	/** Size of the ::SceKernelSemaOptParam structure. */
	SceSize 	size;
} SceKernelSemaOptParam;

/** Current state of a semaphore.
 * @see sceKernelReferSemaStatus.
 */
typedef struct SceKernelSemaInfo {
	/** Size of the ::SceKernelSemaInfo structure. */
	SceSize 	size;
	/** NUL-terminated name of the semaphore. */
	char 		name[32];
	/** Attributes. */
	SceUInt 	attr;
	/** The initial count the semaphore was created with. */
	int 		initCount;
	/** The current count. */
	int 		currentCount;
	/** The maximum count. */
	int 		maxCount;
	/** The number of threads waiting on the semaphore. */
	int 		num_wait_threads;
} SceKernelSemaInfo;

/** Attribute for lightweight mutex. */
enum PspLwMutexAttributes {
	/** The wait thread is queued using FIFO. */
	PSP_LW_MUTEX_ATTR_THFIFO = 0x0000U,
	/** The wait thread is queued by thread priority . */
	PSP_LW_MUTEX_ATTR_THPRI = 0x0100U,
	/** A recursive lock is allowed by the thread that acquired the lightweight mutex */
	PSP_LW_MUTEX_ATTR_RECURSIVE = 0x0200U
};

/** Struct as workarea for lightweight mutex */
typedef struct {
    /** Count */
    int lockLevel;
    /** Locking thread */
    SceUID lock_thread;
    /** Attribute */
    int attr;
    /** Number of waiting threads */
    int num_wait_threads;
    /** UID */
    SceUID uid;
    /** Padding */
    int pad[3];
} SceLwMutexWorkarea;

#define lockThread lock_thread

/** Structure to hold the event flag information */
typedef struct SceKernelEventFlagInfo {
	SceSize 	size;
	char 		name[32];
	SceUInt 	attr;
	SceUInt 	init_pattern;
	SceUInt 	current_pattern;
	int 		num_wait_threads;
} SceKernelEventFlagInfo;

#define initPattern init_pattern
#define currentPattern current_pattern

typedef struct SceKernelEventFlagOptParam {
	SceSize 	size;
} SceKernelEventFlagOptParam;


/** Event flag creation attributes */
enum PspEventFlagAttributes {
	/** Allow the event flag to be waited upon by a single thread */
	PSP_EVENT_WAITSINGLE = 0x00,
	/** Allow the event flag to be waited upon by multiple threads */
	PSP_EVENT_WAITMULTIPLE = 0x200
};

/** Event flag wait types */
enum PspEventFlagWaitTypes {
	/** Wait for all bits in the pattern to be set */
	PSP_EVENT_WAITAND = 0,
	/** Wait for one or more bits in the pattern to be set */
	PSP_EVENT_WAITOR  = 1,
	/** Clear the wait pattern when it matches */
	PSP_EVENT_WAITCLEAR = 0x20
};

/** Additional options used when creating messageboxes. */
typedef struct SceKernelMbxOptParam {
	/** Size of the ::SceKernelMbxOptParam structure. */
	SceSize 	size;
} SceKernelMbxOptParam;

/** Current state of a messagebox.
 * @see sceKernelReferMbxStatus.
 */
typedef struct SceKernelMbxInfo {
	/** Size of the ::SceKernelMbxInfo structure. */
	SceSize 	size;
	/** NUL-terminated name of the messagebox. */
	char 		name[32];
	/** Attributes. */
	SceUInt 	attr;
	/** The number of threads waiting on the messagebox. */
	int 		num_wait_threads;
	/** Number of messages currently in the messagebox. */
	int 		num_messages;
	/** The message currently at the head of the queue. */
	void		*first_message;
} SceKernelMbxInfo;

#define numMessages num_messages
#define firstMessage first_message

/**
 * Header for a message box packet
 */
typedef struct SceKernelMsgPacket {
	/** Pointer to next msg (used by the kernel) */
	struct SceKernelMsgPacket *next;
	/** Priority ? */
	SceUChar    msg_priority;
	SceUChar    dummy[3];
	/** After this can be any user defined data */
} SceKernelMsgPacket;

#define msgPriority msg_priority

/** Prototype for alarm handlers. */
typedef SceUInt (*SceKernelAlarmHandler)(void *common);

/** Struct containing alarm info */
typedef struct SceKernelAlarmInfo {
	/** Size of the structure (should be set before calling
	 * :: sceKernelReferAlarmStatus */
	SceSize		size;
	/* The current schedule */
	SceKernelSysClock schedule;
	/** Pointer to the alarm handler */
	SceKernelAlarmHandler handler;
	/** Common pointer argument */
	void *		common;
} SceKernelAlarmInfo;

/** Callback function prototype */
typedef int (*SceKernelCallbackFunction)(int arg1, int arg2, void *arg);

/** Structure to hold the status information for a callback */
typedef struct SceKernelCallbackInfo {
	/** Size of the structure (i.e. sizeof(SceKernelCallbackInfo)) */
	SceSize 	size;
	/** The name given to the callback */
	char 	name[32];
	/** The thread id associated with the callback */
	SceUID 	thread_id;
	/** Pointer to the callback function */
	SceKernelCallbackFunction 	callback;
	/** User supplied argument for the callback */
	void * 	common;
	/** Unknown */
	int 	notify_count;
	/** Unknown */
	int 	notify_arg;
} SceKernelCallbackInfo;

#define notifyCount notify_count
#define notifyArg notify_arg

/** Threadman types for ::sceKernelGetThreadmanIdList */
typedef enum SceKernelIdListType {
	SCE_KERNEL_TMID_Thread = 1,
	SCE_KERNEL_TMID_Semaphore = 2,
	SCE_KERNEL_TMID_EventFlag = 3,
	SCE_KERNEL_TMID_Mbox = 4,
	SCE_KERNEL_TMID_Vpl = 5,
	SCE_KERNEL_TMID_Fpl = 6,
	SCE_KERNEL_TMID_Mpipe = 7,
	SCE_KERNEL_TMID_Callback = 8,
	SCE_KERNEL_TMID_ThreadEventHandler = 9,
	SCE_KERNEL_TMID_Alarm = 10,
	SCE_KERNEL_TMID_VTimer = 11,
	SCE_KERNEL_TMID_SleepThread = 64,
	SCE_KERNEL_TMID_DelayThread = 65,
	SCE_KERNEL_TMID_SuspendThread = 66,
	SCE_KERNEL_TMID_DormantThread = 67,
} SceKernelIdListType;

/** Structure to contain the system status returned by ::sceKernelReferSystemStatus */
typedef struct SceKernelSystemStatus {
	/** Size of the structure (should be set prior to the call) */
	SceSize 	size;
	/** The status ? */
	SceUInt 	status;
	/** The number of cpu clocks in the idle thread */
	SceKernelSysClock 	idle_clocks;
	/** Number of times we resumed from idle */
	SceUInt 	comes_out_of_idle_count;
	/** Number of thread context switches */
	SceUInt 	thread_switch_count;
	/** Number of vfpu switches ? */
	SceUInt 	vfpu_switch_count;
} SceKernelSystemStatus;

#define idleClocks idle_clocks
#define comesOutOfIdleCount comes_out_of_idle_count
#define threadSwitchCount thread_switch_count
#define vfpuSwitchCount vfpu_switch_count

/** Message Pipe status info */
typedef struct SceKernelMppInfo {
	SceSize 	size;
	char 	name[32];
	SceUInt 	attr;
	int 	buf_size;
	int 	free_size;
	int 	num_send_wait_threads;
	int 	num_receive_wait_threads;
} SceKernelMppInfo;

#define bufSize buf_size
#define freeSize free_size
#define numSendWaitThreads num_send_wait_threads
#define numReceiveWaitThreads num_receive_wait_threads

struct SceKernelVplOptParam {
	SceSize 	size;
};

/** Variable pool status info */
typedef struct SceKernelVplInfo {
	SceSize 	size;
	char 	name[32];
	SceUInt 	attr;
	int 	pool_size;
	int 	free_size;
	int 	num_wait_threads;
} SceKernelVplInfo;

#define poolSize pool_size
#define numWaitThreads num_wait_threads

struct SceKernelFplOptParam {
	SceSize 	size;
};

/** Fixed pool status information */
typedef struct SceKernelFplInfo {
	SceSize 	size;
	char 	name[32];
	SceUInt 	attr;
	int 	block_size;
	int 	num_blocks;
	int 	free_blocks;
	int 	num_wait_threads;
} SceKernelFplInfo;

#define freeBlocks free_blocks
#define numBlocks num_blocks
#define blockSize block_size

typedef SceUInt (*SceKernelVTimerHandler)(SceUID uid, SceKernelSysClock *, SceKernelSysClock *, void *);
typedef SceUInt (*SceKernelVTimerHandlerWide)(SceUID uid, SceInt64, SceInt64, void *);

typedef struct SceKernelVTimerInfo {
	SceSize 	size;
	char 	name[32];
	int 	active;
	SceKernelSysClock 	base;
	SceKernelSysClock 	current;
	SceKernelSysClock 	schedule;
	SceKernelVTimerHandler 	handler;
	void * 	common;
} SceKernelVTimerInfo;

struct SceKernelVTimerOptParam {
	SceSize 	size;
};

typedef int (*SceKernelThreadEventHandler)(int mask, SceUID thid, void *common);

/** Struct for event handler info */
typedef struct SceKernelThreadEventHandlerInfo {
	SceSize 	size;
	char 	name[32];
	SceUID 	thread_id;
	int 	mask;
	SceKernelThreadEventHandler 	handler;
	void * 	common;
} SceKernelThreadEventHandlerInfo;

#define threadId thread_id

enum ThreadEventIds {
	THREADEVENT_ALL = 0xFFFFFFFF,
	THREADEVENT_KERN = 0xFFFFFFF8,
	THREADEVENT_USER = 0xFFFFFFF0,
	THREADEVENT_CURRENT = 0
};

enum ThreadEvents {
	THREAD_CREATE = 1,
	THREAD_START  = 2,
	THREAD_EXIT   = 4,
	THREAD_DELETE = 8,
};

/** Thread context
 * Structues for the thread context taken from florinsasu's post on the forums */
struct SceThreadContext {
	u32   type;
	u32   gpr[31];
	u32   fpr[32];
	u32   fc31;
	u32   hi;
	u32   lo;
	u32   SR;
	u32   EPC;
	u32   field_114;
	u32   field_118;
};

struct SceSCContext
{
	u32 status;
	u32 epc;
	u32 sp;
	u32 ra;
	u32 k1;
	u32 unk[3];
};

/** Structure to hold the status information for a thread (kernel form)
 * 1.5 form
  */
typedef struct SceKernelThreadKInfo {
	/** Size of the structure */
	SceSize     size;
	/** Nul terminated name of the thread */
	char    	name[32];
	/** Thread attributes */
	SceUInt     attr;
	/** Thread status */
	int     	status;
	/** Thread entry point */
	SceKernelThreadEntry    entry;
	/** Thread stack pointer */
	void *  	stack;
	/** Thread stack size */
	int     	stackSize;
	/** Kernel stack pointer */
	void *		kstack;
	/** Kernel stack size */
	void *		kstackSize;
	/** Pointer to the gp */
	void *  	gpReg;
	/** Size of args */
	SceSize     args;
	/** Pointer to args */
	void *      argp;
	/** Initial priority */
	int     	initPriority;
	/** Current priority */
	int     	currentPriority;
	/** Wait type */
	int     	waitType;
	/** Wait id */
	SceUID  	waitId;
	/** Wakeup count */
	int     	wakeupCount;
	/** Number of clock cycles run */
	SceKernelSysClock   runClocks;
#if defined(_PSP_FW_VERSION) && _PSP_FW_VERSION >= 200
	SceUInt unk3; /* Unknown extra field on later firmwares */
#endif
	/** Interrupt preemption count */
	SceUInt     intrPreemptCount;
	/** Thread preemption count */
	SceUInt     threadPreemptCount;
	/** Release count */
	SceUInt     releaseCount;
	/** Thread Context */
	struct SceThreadContext *thContext;
	/** VFPU Context */
	float *      vfpuContext;
	/** Return address from syscall */
	void  *      retAddr;
	/** Unknown, possibly size of SC context */
	SceUInt      unknown1;
	/** Syscall Context */
	struct SceSCContext *scContext;
} SceKernelThreadKInfo;


#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
 * Create a thread.
 *
 * @par Example:
 * @code
 * SceUID thid;
 * thid = sceKernelCreateThread("my_thread", threadFunc, 0x18, 0x10000, 0, NULL);
 * @endcode
 *
 * @param name An arbitrary thread name.
 * @param entry The thread function to run when started.
 * @param init_priority The initial priority of the thread. Less if higher priority.
 * @param stack_size The size of the initial stack.
 * @param attr The thread attributes, zero or more of `PspThreadAttributes`.
 * @param option An additional options specified by `SceKernelThreadOptParam`.
 *
 * @return UID of the created thread, or an error code.
 *
 * @attention Requires linking to `pspthreadman_user` or `pspthreadman_kernel` stubs to be available.
 */
SceUID sceKernelCreateThread(const char *name, SceKernelThreadEntry entry, int init_priority, int stack_size, SceUInt attr, SceKernelThreadOptParam *option);

/**
 * Delete a thread.
 *
 * @param thid The UID of the thread to be deleted.
 *
 * @return `< 0` on error.
 *
 * @attention Requires linking to `pspthreadman_user` or `pspthreadman_kernel` stubs to be available.
 */
int sceKernelDeleteThread(SceUID thid);

/**
 * Start a created thread.
 *
 * @param thid The thread ID from `sceKernelCreateThread()`
 * @param arglen The length of the data pointed to by argp, in bytes
 * @param argp A pointer to the arguments.
 *
 * @return `< 0` on error.
 *
 * @attention Requires linking to `pspthreadman_user` or `pspthreadman_kernel` stubs to be available.
 */
int sceKernelStartThread(SceUID thid, SceSize arglen, void *argp);

/**
 * Exit a thread.
 *
 * @param status The exit status.
 *
 * @return `< 0` on error.
 *
 * @attention Requires linking to `pspthreadman_user` or `pspthreadman_kernel` stubs to be available.
 */
int sceKernelExitThread(int status);

/**
  * Exit a thread and delete itself.
  *
  * @param status The exit status
  *
 * @attention Requires linking to `pspthreadman_user` or `pspthreadman_kernel` stubs to be available.
  */
int sceKernelExitDeleteThread(int status);

/**
 * Terminate a thread.
 *
 * @param thid The UID of the thread to terminate.
 *
 * @return Success if `>= 0`, an error if `< 0`.
 *
 * @attention Requires linking to `pspthreadman_user` or `pspthreadman_kernel` stubs to be available.
 */
int sceKernelTerminateThread(SceUID thid);

/**
 * Terminate and delete a thread.
 *
 * @param thid The UID of the thread to terminate and delete.
 *
 * @return Success if `>= 0`, an error if `< 0`.
 *
 * @attention Requires linking to `pspthreadman_user` or `pspthreadman_kernel` stubs to be available.
 */
int sceKernelTerminateDeleteThread(SceUID thid);

/**
 * Suspend the dispatch thread.
 *
 * @return The current state of the dispatch thread, `< 0` on error.
 *
 * @attention Requires linking to `pspthreadman_user` or `pspthreadman_kernel` stubs to be available.
 */
int sceKernelSuspendDispatchThread(void);

/**
 * Resume the dispatch thread
 *
 * @param state The state of the dispatch thread.
 * (from ::sceKernelSuspendDispatchThread)
 *
 * @return `0` on success, `< 0` on error.
 *
 * @attention Requires linking to `pspthreadman_user` or `pspthreadman_kernel` stubs to be available.
 */
int sceKernelResumeDispatchThread(int state);

/**
 * Sleep thread
 *
 * @return `< 0` on error.
 *
 * @attention Requires linking to `pspthreadman_user` or `pspthreadman_kernel` stubs to be available.
 */
int sceKernelSleepThread(void);

/**
 * Sleep thread but service any callbacks as necessary.
 *
 * @par Example:
 * @code
 * // Once all callbacks have been setup call this function
 * sceKernelSleepThreadCB();
 * @endcode
 *
 * @attention Requires linking to `pspthreadman_user` or `pspthreadman_kernel` stubs to be available.
 */
int sceKernelSleepThreadCB(void);

/**
 * Wake a thread previously put into the sleep state.
 *
 * @param thid The UID of the thread to wake.
 *
 * @return Success if `>= 0`, an error if `< 0`.
 *
 * @attention Requires linking to `pspthreadman_user` or `pspthreadman_kernel` stubs to be available.
 */
int sceKernelWakeupThread(SceUID thid);

/**
 * Cancel a thread that was to be woken with `sceKernelWakeupThread`.
 *
 * @param thid The UID of the thread to cancel.
 *
 * @return Success if `>= 0`, an error if `< 0`.
 *
 * @attention Requires linking to `pspthreadman_user` or `pspthreadman_kernel` stubs to be available.
 */
int sceKernelCancelWakeupThread(SceUID thid);

/**
 * Suspend a thread.
 *
 * @param thid The UID of the thread to suspend.
 *
 * @return Success if `>= 0`, an error if `< 0`.
 *
 * @attention Requires linking to `pspthreadman_user` or `pspthreadman_kernel` stubs to be available.
 */
int sceKernelSuspendThread(SceUID thid);

/**
 * Resume a thread previously put into a suspended state with `sceKernelSuspendThread`.
 *
 * @param thid The UID of the thread to resume.
 *
 * @return Success if `>= 0`, an error if `< 0`.
 *
 * @attention Requires linking to `pspthreadman_user` or `pspthreadman_kernel` stubs to be available.
 */
int sceKernelResumeThread(SceUID thid);

/**
  * Wait until a thread has ended.
  *
  * @param thid The ID of the thread to wait for.
  * @param timeout The timeout in microseconds (assumed).
  *
  * @return `< 0` on error.
 *
 * @attention Requires linking to `pspthreadman_user` or `pspthreadman_kernel` stubs to be available.
  */
int sceKernelWaitThreadEnd(SceUID thid, SceUInt *timeout);

/**
  * Wait until a thread has ended and handle callbacks if necessary.
  *
  * @param thid The ID of the thread to wait for.
  * @param timeout The timeout in microseconds (assumed).
  *
  * @return `< 0` on error.
 *
 * @attention Requires linking to `pspthreadman_user` or `pspthreadman_kernel` stubs to be available.
  */
int sceKernelWaitThreadEndCB(SceUID thid, SceUInt *timeout);

/**
  * Delay the current thread by a specified number of microseconds
  *
  * @param delay The delay in microseconds.
  *
  * @par Example:
  * @code
  * sceKernelDelayThread(1000000); // Delay for a second
  * @endcode
 *
 * @attention Requires linking to `pspthreadman_user` or `pspthreadman_kernel` stubs to be available.
  */
int sceKernelDelayThread(SceUInt delay);

/**
  * Delay the current thread by a specified number of microseconds and handle any callbacks.
  *
  * @param delay The delay in microseconds.
  *
  * @par Example:
  * @code
  * sceKernelDelayThread(1000000); // Delay for a second
  * @endcode
 *
 * @attention Requires linking to `pspthreadman_user` or `pspthreadman_kernel` stubs to be available.
  */
int sceKernelDelayThreadCB(SceUInt delay);

/**
  * Delay the current thread by a specified number of sysclocks
  *
  * @param delay The delay in sysclocks
  *
  * @return `0` on success, `< 0` on error.
 *
 * @attention Requires linking to `pspthreadman_user` or `pspthreadman_kernel` stubs to be available.
  */
int sceKernelDelaySysClockThread(SceKernelSysClock *delay);

/**
  * Delay the current thread by a specified number of sysclocks handling callbacks
  *
  * @param delay The delay in sysclocks
  *
  * @return `0` on success, `< 0` on error.
 *
 * @attention Requires linking to `pspthreadman_user` or `pspthreadman_kernel` stubs to be available.
  */
int sceKernelDelaySysClockThreadCB(SceKernelSysClock *delay);

/**
 * Modify the attributes of the current thread.
 *
 * @param unk Unknown. Set to 0.
 * @param attr The thread attributes to modify. One of `PspThreadAttributes`.
 *
 * @return `< 0` on error.
 *
 * @attention Requires linking to `pspthreadman_user` or `pspthreadman_kernel` stubs to be available.
 */
int sceKernelChangeCurrentThreadAttr(int unknown, SceUInt attr);

/**
  * Change the threads current priority.
  *
  * @param thid The ID of the thread (from `sceKernelCreateThread` or `sceKernelGetThreadId`).
  * @param priority The new priority (the lower the number the higher the priority).
  *
  * @par Example:
  * @code
  * int thid = sceKernelGetThreadId();
  * // Change priority of current thread to 16
  * sceKernelChangeThreadPriority(thid, 16);
  * @endcode
  *
  * @return 0 if successful, otherwise the error code.
 *
 * @attention Requires linking to `pspthreadman_user` or `pspthreadman_kernel` stubs to be available.
  */
int sceKernelChangeThreadPriority(SceUID thid, int priority);

/**
 * Rotate thread ready queue at a set priority.
 *
 * @param priority The priority of the queue.
 *
 * @return `0` on success, `< 0` on error.
 *
 * @attention Requires linking to `pspthreadman_user` or `pspthreadman_kernel` stubs to be available.
 */
int sceKernelRotateThreadReadyQueue(int priority);

/**
 * Release a thread in the wait state.
 *
 * @param thid The UID of the thread.
 *
 * @return `0` on success, `< 0` on error.
 *
 * @attention Requires linking to `pspthreadman_user` or `pspthreadman_kernel` stubs to be available.
 */
int sceKernelReleaseWaitThread(SceUID thid);

/**
  * Get the current thread ID.
  *
  * @return The thread id of the calling thread.
 *
 * @attention Requires linking to `pspthreadman_user` or `pspthreadman_kernel` stubs to be available.
  */
int sceKernelGetThreadId(void);

/**
 * Get the current priority of the thread you are in.
 *
 * @return The current thread priority.
 *
 * @attention Requires linking to `pspthreadman_user` or `pspthreadman_kernel` stubs to be available.
 */
int sceKernelGetThreadCurrentPriority(void);

/**
 * Get the exit status of a thread.
 *
 * @param thid The UID of the thread to check.
 *
 * @return The exit status.
 *
 * @attention Requires linking to `pspthreadman_user` or `pspthreadman_kernel` stubs to be available.
 */
int sceKernelGetThreadExitStatus(SceUID thid);

/**
 * Check the thread stack?
 *
 * @return Unknown.
 *
 * @attention Requires linking to `pspthreadman_user` or `pspthreadman_kernel` stubs to be available.
 */
int sceKernelCheckThreadStack(void);

/**
 * Get the free stack size for a thread.
 *
 * @param thid The thread ID. Seem to take current thread if set to `0`.
 *
 * @return The free size.
 *
 * @attention Requires linking to `pspthreadman_user` or `pspthreadman_kernel` stubs to be available.
 */
int sceKernelGetThreadStackFreeSize(SceUID thid);

/**
  * Get the status information for the specified thread.
  *
  * @param thid The ID of the thread to get status
  * @param info A pointer to the info structure to receive the data.
  *
  * @note The structures size field should be set to
  * `sizeof(SceKernelThreadInfo)` before calling this function.
  *
  * @par Example:
  * @code
  * SceKernelThreadInfo status;
  * status.size = sizeof(SceKernelThreadInfo);
  * if(sceKernelReferThreadStatus(thid, &status) == 0)
  * { Do something... }
  * @endcode
  *
  * @return `0` if successful, otherwise the error code.
 *
 * @attention Requires linking to `pspthreadman_user` or `pspthreadman_kernel` stubs to be available.
  */
int sceKernelReferThreadStatus(SceUID thid, SceKernelThreadInfo *info);

/**
 * Retrive the runtime status of a thread.
 *
 * @param thid The UID of the thread to retrive status.
 * @param status A pointer to a `SceKernelThreadRunStatus` struct to receive the runtime status.
 *
 * @return `0` if successful, otherwise the error code.
 *
 * @attention Requires linking to `pspthreadman_user` or `pspthreadman_kernel` stubs to be available.
 */
int sceKernelReferThreadRunStatus(SceUID thid, SceKernelThreadRunStatus *status);


/**
 * Creates a new semaphore.
 *
 * @par Example:
 * @code
 * int semaid;
 * semaid = sceKernelCreateSema("MyMutex", 0, 1, 1, 0);
 * @endcode
 *
 * @param name An arbitrary name for the sema.
 * @param attr The sema attribute flags (normally set to `0`)
 * @param initVal The sema initial value.
 * @param maxVal The sema maximum value.
 * @param option The sema options (normally set to `0`).
 *
 * @return A semaphore ID.
 *
 * @attention Requires linking to `pspthreadman_user` or `pspthreadman_kernel` stubs to be available.
 */
SceUID sceKernelCreateSema(const char *name, SceUInt attr, int initVal, int maxVal, SceKernelSemaOptParam *option);

/**
 * Destroy a semaphore.
 *
 * @param semaid The semaid returned from a previous create call.
 *
 * @return Returns the value `0` if its successful, otherwise `-1`.
 *
 * @attention Requires linking to `pspthreadman_user` or `pspthreadman_kernel` stubs to be available.
 */
int sceKernelDeleteSema(SceUID semaid);

/**
 * Send a signal to a semaphore.
 *
 * @par Example:
 * @code
 * // Signal the sema
 * sceKernelSignalSema(semaid, 1);
 * @endcode
 *
 * @param semaid The sema ID returned from sceKernelCreateSema
 * @param signal The amount to signal the sema (i.e. if 2 then increment the sema by 2)
 *
 * @return `< 0` on error.
 *
 * @attention Requires linking to `pspthreadman_user` or `pspthreadman_kernel` stubs to be available.
 */
int sceKernelSignalSema(SceUID semaid, int signal);

/**
 * Lock a semaphore
 *
 * @par Example:
 * @code
 * sceKernelWaitSema(semaid, 1, 0);
 * @endcode
 *
 * @param semaid The sema id returned from sceKernelCreateSema
 * @param signal The value to wait for (i.e. if 1 then wait till reaches a signal state of 1)
 * @param timeout The timeout in microseconds (assumed).
 *
 * @return `< 0` on error.
 *
 * @attention Requires linking to `pspthreadman_user` or `pspthreadman_kernel` stubs to be available.
 */
int sceKernelWaitSema(SceUID semaid, int signal, SceUInt *timeout);

/**
 * Lock a semaphore a handle callbacks if necessary.
 *
 * @par Example:
 * @code
 * sceKernelWaitSemaCB(semaid, 1, 0);
 * @endcode
 *
 * @param semaid The sema id returned from `sceKernelCreateSema`.
 * @param signal The value to wait for (i.e. if 1 then wait till reaches a signal state of 1).
 * @param timeout The timeout in microseconds (assumed).
 *
 * @return `< 0` on error.
 *
 * @attention Requires linking to `pspthreadman_user` or `pspthreadman_kernel` stubs to be available.
 */
int sceKernelWaitSemaCB(SceUID semaid, int signal, SceUInt *timeout);

/**
 * Poll a sempahore.
 *
 * @param semaid The UID of the semaphore to poll.
 * @param signal The value to test for.
 *
 * @return `< 0` on error.
 *
 * @attention Requires linking to `pspthreadman_user` or `pspthreadman_kernel` stubs to be available.
 */
int sceKernelPollSema(SceUID semaid, int signal);

/**
 * Retrieve information about a semaphore.
 *
 * @param semaid The UID of the semaphore to retrieve info for.
 * @param[out] info A pointer to a `SceKernelSemaInfo` struct to receive the info.
 *
 * @return `< 0` on error.
 *
 * @attention Requires linking to `pspthreadman_user` or `pspthreadman_kernel` stubs to be available.
 */
int sceKernelReferSemaStatus(SceUID semaid, SceKernelSemaInfo *info);

/**
 * Create a lightweight mutex
 *
 * @param workarea The pointer to the workarea.
 * @param name The name of the lightweight mutex.
 * @param attr The LwMutex attributes, zero or more of `PspLwMutexAttributes`.
 * @param initialCount The inital value of the mutex.
 * @param optionsPtr - Other options for mutex.
 *
 * @return 0 on success, otherwise one of `PspKernelErrorCodes`.
 *
 * @attention Requires linking to `pspthreadman_user` or `pspthreadman_kernel` stubs to be available.
 */
int sceKernelCreateLwMutex(SceLwMutexWorkarea *workarea, const char *name, SceUInt32 attr, int initialCount, u32 *optionsPtr);

/**
 * Delete a lightweight mutex.
 *
 * @param workarea The pointer to the workarea.
 *
 * @return 0 on success, otherwise one of `PspKernelErrorCodes`.
 *
 * @attention Requires linking to `pspthreadman_user` or `pspthreadman_kernel` stubs to be available.
 */
int sceKernelDeleteLwMutex(SceLwMutexWorkarea *workarea);

/**
 * Try to lock a lightweight mutex.
 *
 * @param workarea The pointer to the workarea.
 * @param lockCount - value of increase the lock counter.
 *
 * @return 0 on success, otherwise one of `PspKernelErrorCodes`.
 *
 * @attention Requires linking to `pspthreadman_user` or `pspthreadman_kernel` stubs to be available.
 */
int sceKernelTryLockLwMutex(SceLwMutexWorkarea *workarea, int lockCount);

/**
 * Lock a lightweight mutex.
 *
 * @param workarea The pointer to the workarea.
 * @param lockCount - value of increase the lock counter.
 * @param pTimeout The pointer for timeout waiting.
 *
 * @return 0 on success, otherwise one of `PspKernelErrorCodes`.
 *
 * @attention Requires linking to `pspthreadman_user` or `pspthreadman_kernel` stubs to be available.
 */
int sceKernelLockLwMutex(SceLwMutexWorkarea *workarea, int lockCount, u32 *pTimeout);

/**
 * Lock a lightweight mutex.
 *
 * @param workarea The pointer to the workarea.
 * @param lockCount - value of decrease the lock counter.
 *
 * @return 0 on success, otherwise one of `PspKernelErrorCodes`.
 *
 * @attention Requires linking to `pspthreadman_user` or `pspthreadman_kernel` stubs to be available.
 */
int sceKernelUnlockLwMutex(SceLwMutexWorkarea *workarea, int lockCount);

/* Event flags. */

/**
  * Create an event flag.
  *
  * @param name The name of the event flag.
  * @param attr The event flag attributes. A set of `PspEventFlagAttributes`.
  * @param bits The initial bit pattern.
  * @param opt  The options, set to `NULL`.
  *
  * @return `< 0` on error. `>= 0` event flag id.
  *
  * @par Example:
  * @code
  * int evid;
  * evid = sceKernelCreateEventFlag("wait_event", 0, 0, 0);
  * @endcode
 *
 * @attention Requires linking to `pspthreadman_user` or `pspthreadman_kernel` stubs to be available.
  */
SceUID sceKernelCreateEventFlag(const char *name, int attr, int bits, SceKernelEventFlagOptParam *opt);

/**
  * Set an event flag bit pattern.
  *
  * @param evid The event id returned by sceKernelCreateEventFlag.
  * @param bits The bit pattern to set.
  *
  * @return `< 0` on error.
 *
 * @attention Requires linking to `pspthreadman_user` or `pspthreadman_kernel` stubs to be available.
  */
int sceKernelSetEventFlag(SceUID evid, u32 bits);

/**
 * Clear a event flag bit pattern
 *
 * @param evid The event id returned by ::sceKernelCreateEventFlag
 * @param bits The bits to clean
 *
 * @return `< 0` on error.
 *
 * @attention Requires linking to `pspthreadman_user` or `pspthreadman_kernel` stubs to be available.
 */
int sceKernelClearEventFlag(SceUID evid, u32 bits);

/**
  * Poll an event flag for a given bit pattern.
  *
  * @param evid The event id returned by sceKernelCreateEventFlag.
  * @param bits The bit pattern to poll for.
  * @param wait The wait type. One or more of `PspEventFlagWaitTypes` or'ed together.
  * @param[out] out_bits The bit pattern that was matched.
  *
  * @return `< 0` on error.
 *
 * @attention Requires linking to `pspthreadman_user` or `pspthreadman_kernel` stubs to be available.
  */
int sceKernelPollEventFlag(int evid, u32 bits, u32 wait, u32 *out_bits);

/**
  * Wait for an event flag for a given bit pattern.
  *
  * @param evid The event id returned by `sceKernelCreateEventFlag`.
  * @param bits The bit pattern to poll for.
  * @param wait The wait type. One or more of `PspEventFlagWaitTypes` or'ed together.
  * @param[out] out_bits The bit pattern that was matched.
  * @param[in] timeout  The timeout in microseconds.
  *
  * @return `< 0` on error.
 *
 * @attention Requires linking to `pspthreadman_user` or `pspthreadman_kernel` stubs to be available.
  */
int sceKernelWaitEventFlag(int evid, u32 bits, u32 wait, u32 *out_bits, SceUInt *timeout);

/**
  * Wait for an event flag for a given bit pattern with callback.
  *
  * @param evid The event id returned by sceKernelCreateEventFlag.
  * @param bits The bit pattern to poll for.
  * @param wait The wait type. One or more of `PspEventFlagWaitTypes` or'ed together.
  * @param[out] out_bits The bit pattern that was matched.
  * @param timeout  The timeout in microseconds
  * @return `< 0` on error.
 *
 * @attention Requires linking to `pspthreadman_user` or `pspthreadman_kernel` stubs to be available.
  */
int sceKernelWaitEventFlagCB(int evid, u32 bits, u32 wait, u32 *out_bits, SceUInt *timeout);

/**
  * Delete an event flag
  *
  * @param evid The event id returned by sceKernelCreateEventFlag.
  *
  * @return `< 0` on error.
 *
 * @attention Requires linking to `pspthreadman_user` or `pspthreadman_kernel` stubs to be available.
  */
int sceKernelDeleteEventFlag(int evid);

/**
  * Get the status of an event flag.
  *
  * @param event The UID of the event.
  * @param status A pointer to a 1SceKernelEventFlagInfo1 structure.
  *
  * @return `< 0` on error.
 *
 * @attention Requires linking to `pspthreadman_user` or `pspthreadman_kernel` stubs to be available.
  */
int sceKernelReferEventFlagStatus(SceUID event, SceKernelEventFlagInfo *status);


/* Message boxes. */

/**
 * Creates a new messagebox.
 *
 * @par Example:
 * @code
 * int mbxid;
 * mbxid = sceKernelCreateMbx("MyMessagebox", 0, NULL);
 * @endcode
 *
 * @param name An arbitrary name for the mbx.
 * @param attr The mbx attribute flags (normally set to `0`).
 * @param option The mbx options (normally set to `NULL`).
 *
 * @return A messagebox ID.
 *
 * @attention Requires linking to `pspthreadman_user` or `pspthreadman_kernel` stubs to be available.
 */
SceUID sceKernelCreateMbx(const char *name, SceUInt attr, SceKernelMbxOptParam *option);

/**
 * Destroy a messagebox.
 *
 * @param mbxid The mbxid returned from a previous create call.
 *
 * @return Returns the value `0` if its succesful otherwise an error code.
 *
 * @attention Requires linking to `pspthreadman_user` or `pspthreadman_kernel` stubs to be available.
 */
int sceKernelDeleteMbx(SceUID mbxid);

/**
 * Send a message to a messagebox
 *
 * @par Example:
 * @code
 * struct MyMessage {
 * 	SceKernelMsgPacket header;
 * 	char text[8];
 * };
 *
 * struct MyMessage msg = { {0}, "Hello" };
 * // Send the message
 * sceKernelSendMbx(mbxid, (void*) &msg);
 * @endcode
 *
 * @param mbxid The mbx id returned from sceKernelCreateMbx
 * @param[in] message A message to be forwarded to the receiver.
 * 					The start of the message should be the
 * 					::SceKernelMsgPacket structure, the rest
 *
 * @return `< 0` on error.
 *
 * @attention Requires linking to `pspthreadman_user` or `pspthreadman_kernel` stubs to be available.
 */
int sceKernelSendMbx(SceUID mbxid, void *message);

/**
 * Wait for a message to arrive in a messagebox
 *
 * @par Example:
 * @code
 * void *msg;
 * sceKernelReceiveMbx(mbxid, &msg, NULL);
 * @endcode
 *
 * @param mbxid The mbx id returned from sceKernelCreateMbx
 * @param[out] pmessage A pointer to where a pointer to the
 *                   received message should be stored
 * @param[in] timeout The timeout in microseconds
 *
 * @return `< 0` on error.
 *
 * @attention Requires linking to `pspthreadman_user` or `pspthreadman_kernel` stubs to be available.
 */
int sceKernelReceiveMbx(SceUID mbxid, void **pmessage, SceUInt *timeout);

/**
 * Wait for a message to arrive in a messagebox and handle callbacks if necessary.
 *
 * @par Example:
 * @code
 * void *msg;
 * sceKernelReceiveMbxCB(mbxid, &msg, NULL);
 * @endcode
 *
 * @param mbxid The mbx id returned from sceKernelCreateMbx
 * @param[out] pmessage A pointer to where a pointer to the received message should be stored
 * @param[in] timeout The timeout in microseconds
 *
 * @return `< 0` on error.
 *
 * @attention Requires linking to `pspthreadman_user` or `pspthreadman_kernel` stubs to be available.
 */
int sceKernelReceiveMbxCB(SceUID mbxid, void **pmessage, SceUInt *timeout);

/**
 * Check if a message has arrived in a messagebox
 *
 * @par Example:
 * @code
 * void *msg;
 * sceKernelPollMbx(mbxid, &msg);
 * @endcode
 *
 * @param mbxid The mbx id returned from sceKernelCreateMbx
 * @param pmessage - A pointer to where a pointer to the
 *                   received message should be stored
 *
 * @return `< 0` on error (`SCE_KERNEL_ERROR_MBOX_NOMSG` if the mbx is empty).
 *
 * @attention Requires linking to `pspthreadman_user` or `pspthreadman_kernel` stubs to be available.
 */
int sceKernelPollMbx(SceUID mbxid, void **pmessage);

/**
 * Abort all wait operations on a messagebox.
 *
 * @par Example:
 * @code
 * sceKernelCancelReceiveMbx(mbxid, NULL);
 * @endcode
 *
 * @param mbxid The mbx id returned from sceKernelCreateMbx
 * @param pnum  - A pointer to where the number of threads which
 *                were waiting on the mbx should be stored (NULL
 *                if you don't care)
 *
 * @return `< 0` on error.
 *
 * @attention Requires linking to `pspthreadman_user` or `pspthreadman_kernel` stubs to be available.
 */
int sceKernelCancelReceiveMbx(SceUID mbxid, int *pnum);

/**
 * Retrieve information about a messagebox.
 *
 * @param mbxid The UID of the messagebox to retrieve info for.
 * @param info A pointer to a ::SceKernelMbxInfo struct to receive the info.
 *
 * @return `< 0` on error.
 *
 * @attention Requires linking to `pspthreadman_user` or `pspthreadman_kernel` stubs to be available.
 */
int sceKernelReferMbxStatus(SceUID mbxid, SceKernelMbxInfo *info);


/* Alarms. */

/**
 * Set an alarm.
 *
 * @param clock The number of micro seconds till the alarm occurrs.
 * @param handler A pointer to a ::SceKernelAlarmHandler.
 * @param common A common pointer for the alarm handler.
 *
 * @return A UID representing the created alarm, `< 0` on error.
 *
 * @attention Requires linking to `pspthreadman_user` or `pspthreadman_kernel` stubs to be available.
 */
SceUID sceKernelSetAlarm(SceUInt clock, SceKernelAlarmHandler handler, void *common);

/**
 * Set an alarm using a `SceKernelSysClock` structure for the time.
 *
 * @param clock A pointer to a `SceKernelSysClock` structure.
 * @param handler A pointer to a ::SceKernelAlarmHandler.
 * @param common A common pointer for the alarm handler.
 *
 * @return A UID representing the created alarm, `< 0` on error.
 *
 * @attention Requires linking to `pspthreadman_user` or `pspthreadman_kernel` stubs to be available.
 */
SceUID sceKernelSetSysClockAlarm(SceKernelSysClock *clock, SceKernelAlarmHandler handler, void *common);

/**
 * Cancel a pending alarm.
 *
 * @param alarmid The UID of the alarm to cancel.
 *
 * @return `0` on success, `< 0` on error.
 *
 * @attention Requires linking to `pspthreadman_user` or `pspthreadman_kernel` stubs to be available.
 */
int sceKernelCancelAlarm(SceUID alarmid);

/**
 * Refer the status of a created alarm.
 *
 * @param alarmid The UID of the alarm to get the info of
 * @param[out] info A pointer to a `SceKernelAlarmInfo` structure
 *
 * @return `0` on success, `< 0` on error.
 *
 * @attention Requires linking to `pspthreadman_user` or `pspthreadman_kernel` stubs to be available.
 */
int sceKernelReferAlarmStatus(SceUID alarmid, SceKernelAlarmInfo *info);

/* Callbacks. */

/**
 * Create callback
 *
 * @par Example:
 * @code
 * int cbid;
 * cbid = sceKernelCreateCallback("Exit Callback", exit_cb, NULL);
 * @endcode
 *
 * @param[in] name A textual name for the callback
 * @param[in] func A pointer to a function that will be called as the callback
 * @param[in] arg  An rgument for the callback ?
 *
 * @return `>= 0` A callback id which can be used in subsequent functions, `< 0` an error.
 *
 * @attention Requires linking to `pspthreadman_user` or `pspthreadman_kernel` stubs to be available.
 */
int sceKernelCreateCallback(const char *name, SceKernelCallbackFunction func, void *arg);

/**
  * Gets the status of a specified callback.
  *
  * @param cb The UID of the callback to refer.
  * @param[in] status A pointer to a status structure. The size parameter should be
  * initialised before calling.
  *
  * @return `< 0` on error.
 *
 * @attention Requires linking to `pspthreadman_user` or `pspthreadman_kernel` stubs to be available.
  */
int sceKernelReferCallbackStatus(SceUID cb, SceKernelCallbackInfo *status);

/**
 * Delete a callback
 *
 * @param cb The UID of the specified callback
 *
 * @return `0` on success, `< 0` on error.
 *
 * @attention Requires linking to `pspthreadman_user` or `pspthreadman_kernel` stubs to be available.
 */
int sceKernelDeleteCallback(SceUID cb);

/**
 * Notify a callback
 *
 * @param cb The UID of the specified callback.
 * @param arg2 Unknown. Passed as arg2 into the callback function.
 *
 * @return `0` on success, `< 0` on error.
 *
 * @attention Requires linking to `pspthreadman_user` or `pspthreadman_kernel` stubs to be available.
 */
int sceKernelNotifyCallback(SceUID cb, int arg2);

/**
 * Cancel a callback ?
 *
 * @param cb The UID of the specified callback.
 *
 * @return `0` on success, `< 0` on error.
 *
 * @attention Requires linking to `pspthreadman_user` or `pspthreadman_kernel` stubs to be available.
 */
int sceKernelCancelCallback(SceUID cb);

/**
 * Get the callback count.
 *
 * @param cb The UID of the specified callback.
 *
 * @return The callback count, `< 0` on error.
 *
 * @attention Requires linking to `pspthreadman_user` or `pspthreadman_kernel` stubs to be available.
 */
int sceKernelGetCallbackCount(SceUID cb);

/**
 * Check callback ?.
 *
 * @return Something or another
 *
 * @attention Requires linking to `pspthreadman_user` or `pspthreadman_kernel` stubs to be available.
 */
int sceKernelCheckCallback(void);

/* Misc. */

/**
  * Get a list of UIDs from threadman. Allows you to enumerate
  * resources such as threads or semaphores.
  *
  * @param type The type of resource to list, one of `SceKernelIdListType`.
  * @param[out] readbuf A pointer to a buffer to store the list.
  * @param readbufsize The size of the buffer in SceUID units.
  * @param[out] idcount A pointer to an integer in which to return the number of ids in the list.
  *
  * @return `< 0` on error. Either 0 or the same as idcount on success.
 *
 * @attention Requires linking to `pspthreadman_user` or `pspthreadman_kernel` stubs to be available.
  */
int sceKernelGetThreadmanIdList(enum SceKernelIdListType type, SceUID *readbuf, int readbufsize, int *idcount);

/**
  * Get the current system status.
  *
  * @param[out] status A pointer to a `SceKernelSystemStatus` structure.
  *
  * @return `< 0` on error.
 *
 * @attention Requires linking to `pspthreadman_user` or `pspthreadman_kernel` stubs to be available.
  */
int sceKernelReferSystemStatus(SceKernelSystemStatus *status);


/**
 * Create a message pipe.
 *
 * @param name An arbitrary name for the pipe.
 * @param part The ID of the memory partition.
 * @param attr Unknown. Set to `0`?
 * @param unk1 Unknown.
 * @param opt  The message pipe options (set to `NULL`).
 *
 * @return The UID of the created pipe, `< 0` on error.
 *
 * @attention Requires linking to `pspthreadman_user` or `pspthreadman_kernel` stubs to be available.
 */
SceUID sceKernelCreateMsgPipe(const char *name, int part, int attr, void *unk1, void *opt);

/**
 * Delete a message pipe.
 *
 * @param uid The UID of the pipe
 *
 * @return `0` on success, `< 0` on error.
 *
 * @attention Requires linking to `pspthreadman_user` or `pspthreadman_kernel` stubs to be available.
 */
int sceKernelDeleteMsgPipe(SceUID uid);

/**
 * Send a message to a pipe.
 *
 * @param uid The UID of the pipe.
 * @param message A pointer to the message.
 * @param size The size of the message.
 * @param unk1 Unknown.
 * @param unk2 Unknown.
 * @param timeout The timeout for send.
 *
 * @return `0` on success, `< 0` on error.
 *
 * @attention Requires linking to `pspthreadman_user` or `pspthreadman_kernel` stubs to be available.
 */
int sceKernelSendMsgPipe(SceUID uid, void *message, u32 size, int unk1, void *unk2, u32 *timeout);

/**
 * Send a message to a pipe (with callback).
 *
 * @param uid The UID of the pipe.
 * @param message A pointer to the message.
 * @param size The size of the message.
 * @param unk1 Unknown.
 * @param unk2 Unknown.
 * @param timeout The timeout for send.
 *
 * @return `0` on success, `< 0` on error.
 *
 * @attention Requires linking to `pspthreadman_user` or `pspthreadman_kernel` stubs to be available.
 */
int sceKernelSendMsgPipeCB(SceUID uid, void *message, u32 size, int unk1, void *unk2, u32 *timeout);

/**
 * Try to send a message to a pipe.
 *
 * @param uid The UID of the pipe.
 * @param message A pointer to the message.
 * @param size The size of the message.
 * @param unk1 Unknown.
 * @param unk2 Unknown.
 *
 * @return `0` on success, `< 0` on error.
 *
 * @attention Requires linking to `pspthreadman_user` or `pspthreadman_kernel` stubs to be available.
 */
int sceKernelTrySendMsgPipe(SceUID uid, void *message, u32 size, int unk1, void *unk2);

/**
 * Receive a message from a pipe.
 *
 * @param uid The UID of the pipe.
 * @param message A pointer to the message.
 * @param size The size of the message.
 * @param unk1 Unknown.
 * @param unk2 Unknown.
 * @param timeout The timeout for receive.
 *
 * @return `0` on success, `< 0` on error.
 *
 * @attention Requires linking to `pspthreadman_user` or `pspthreadman_kernel` stubs to be available.
 */
int sceKernelReceiveMsgPipe(SceUID uid, void *message, u32 size, int unk1, void *unk2, u32 *timeout);

/**
 * Receive a message from a pipe (with callback).
 *
 * @param uid The UID of the pipe.
 * @param message A pointer to the message.
 * @param size The size of the message.
 * @param unk1 Unknown.
 * @param unk2 Unknown.
 * @param timeout The timeout for receive.
 *
 * @return `0` on success, `< 0` on error.
 *
 * @attention Requires linking to `pspthreadman_user` or `pspthreadman_kernel` stubs to be available.
 */
int sceKernelReceiveMsgPipeCB(SceUID uid, void *message, u32 size, int unk1, void *unk2, u32 *timeout);

/**
 * Receive a message from a pipe.
 *
 * @param uid The UID of the pipe.
 * @param message A pointer to the message.
 * @param size The size of the message.
 * @param unk1 Unknown.
 * @param unk2 Unknown.
 *
 * @return `0` on success, `< 0` on error.
 *
 * @attention Requires linking to `pspthreadman_user` or `pspthreadman_kernel` stubs to be available.
 */
int sceKernelTryReceiveMsgPipe(SceUID uid, void *message, u32 size, int unk1, void *unk2);

/**
 * Cancel a message pipe.
 *
 * @param uid The UID of the pipe to cancel.
 * @param[out] psend Receive the number of sending threads?
 * @param[out] precv Receive the number of receiving threads?
 *
 * @return `0` on success, `< 0` on error.
 *
 * @attention Requires linking to `pspthreadman_user` or `pspthreadman_kernel` stubs to be available.
 */
int sceKernelCancelMsgPipe(SceUID uid, int *psend, int *precv);

/**
 * Get the status of a Message Pipe.
 *
 * @param uid The uid of the Message Pipe.
 * @param info A pointer to a `SceKernelMppInfo` structure.
 *
 * @return `0` on success, `< 0` on error.
 *
 * @attention Requires linking to `pspthreadman_user` or `pspthreadman_kernel` stubs to be available.
 */
int sceKernelReferMsgPipeStatus(SceUID uid, SceKernelMppInfo *info);

/* VPL Functions */

/**
 * Create a variable pool
 *
 * @param name An arbitrary name for the pool.
 * @param part The memory partition ID.
 * @param attr The attributes.
 * @param size The size of pool.
 * @param opt  The options (set to `NULL`).
 *
 * @return The UID of the created pool, `< 0` on error.
 *
 * @attention Requires linking to `pspthreadman_user` or `pspthreadman_kernel` stubs to be available.
 */
SceUID sceKernelCreateVpl(const char *name, int part, int attr, u32 size, struct SceKernelVplOptParam *opt);

/**
 * Delete a variable pool.
 *
 * @param uid The UID of the pool.
 *
 * @return `0` on success, `< 0` on error.
 *
 * @attention Requires linking to `pspthreadman_user` or `pspthreadman_kernel` stubs to be available.
 */
int sceKernelDeleteVpl(SceUID uid);

/**
 * Allocate from the pool.
 *
 * @param uid The UID of the pool.
 * @param size The size to allocate.
 * @param[out] data Receives the address of the allocated data.
 * @param[in] timeout The timeout. The amount of time to wait for allocation?
 *
 * @return `0` on success, `< 0` on error.
 *
 * @attention Requires linking to `pspthreadman_user` or `pspthreadman_kernel` stubs to be available.
 */
int sceKernelAllocateVpl(SceUID uid, u32 size, void **data, u32 *timeout);

/**
 * Allocate from the pool (with callback).
 *
 * @param uid The UID of the pool.
 * @param size The size to allocate.
 * @param[out] data Receives the address of the allocated data.
 * @param[in] timeout The timeout. The amount of time to wait for allocation?
 *
 * @return `0` on success, `< 0` on error.
 *
 * @attention Requires linking to `pspthreadman_user` or `pspthreadman_kernel` stubs to be available.
 */
int sceKernelAllocateVplCB(SceUID uid, u32 size, void **data, u32 *timeout);

/**
 * Try to allocate from the pool.
 *
 * @param uid The UID of the pool.
 * @param size The size to allocate.
 * @param[out] data Receives the address of the allocated data.
 *
 * @return `0` on success, `< 0` on error.
 *
 * @attention Requires linking to `pspthreadman_user` or `pspthreadman_kernel` stubs to be available.
 */
int sceKernelTryAllocateVpl(SceUID uid, u32 size, void **data);

/**
 * Free a block.
 *
 * @param uid The UID of the pool.
 * @param[in] data The data block to deallocate.
 *
 * @return `0` on success, `< 0` on error.
 *
 * @attention Requires linking to `pspthreadman_user` or `pspthreadman_kernel` stubs to be available.
 */
int sceKernelFreeVpl(SceUID uid, void *data);

/**
 * Cancel a pool.
 *
 * @param uid The UID of the pool.
 * @param[out] pnum Receives the number of waiting threads.
 *
 * @return `0` on success, `< 0` on error.
 *
 * @attention Requires linking to `pspthreadman_user` or `pspthreadman_kernel` stubs to be available.
 */
int sceKernelCancelVpl(SceUID uid, int *pnum);

/**
 * Get the status of an VPL.
 *
 * @param uid The uid of the VPL.
 * @param[out] info A pointer to a `SceKernelVplInfo` structure.
 *
 * @return `0` on success, `< 0` on error.
 *
 * @attention Requires linking to `pspthreadman_user` or `pspthreadman_kernel` stubs to be available.
 */
int sceKernelReferVplStatus(SceUID uid, SceKernelVplInfo *info);

/* FPL Functions */

/**
 * Create a fixed pool.
 *
 * @param name An arbitrary name for the pool.
 * @param part The memory partition ID.
 * @param attr The attributes.
 * @param size The size of pool block.
 * @param blocks The number of blocks to allocate.
 * @param opt  The options (set to `NULL`).
 *
 * @return The UID of the created pool, `< 0` on error.
 *
 * @attention Requires linking to `pspthreadman_user` or `pspthreadman_kernel` stubs to be available.
 */
int sceKernelCreateFpl(const char *name, int part, int attr, u32 size, u32 blocks, struct SceKernelFplOptParam *opt);

/**
 * Delete a fixed pool.
 *
 * @param uid The UID of the pool.
 *
 * @return `0` on success, `< 0` on error.
 *
 * @attention Requires linking to `pspthreadman_user` or `pspthreadman_kernel` stubs to be available.
 */
int sceKernelDeleteFpl(SceUID uid);

/**
 * Allocate from the pool.
 *
 * @param uid The UID of the pool.
 * @param data Receives the address of the allocated data.
 * @param timeout The timeout. The amount of time to wait for allocation?
 *
 * @return `0` on success, `< 0` on error.
 *
 * @attention Requires linking to `pspthreadman_user` or `pspthreadman_kernel` stubs to be available.
 */
int sceKernelAllocateFpl(SceUID uid, void **data, u32 *timeout);

/**
 * Allocate from the pool (with callback).
 *
 * @param uid The UID of the pool.
 * @param data Receives the address of the allocated data.
 * @param timeout The timeout. The amount of time to wait for allocation?
 *
 * @return `0` on success, `< 0` on error.
 *
 * @attention Requires linking to `pspthreadman_user` or `pspthreadman_kernel` stubs to be available.
 */
int sceKernelAllocateFplCB(SceUID uid, void **data, u32 *timeout);

/**
 * Try to allocate from the pool.
 *
 * @param uid The UID of the pool.
 * @param data Receives the address of the allocated data.
 *
 * @return `0` on success, `< 0` on error.
 *
 * @attention Requires linking to `pspthreadman_user` or `pspthreadman_kernel` stubs to be available.
 */
int sceKernelTryAllocateFpl(SceUID uid, void **data);

/**
 * Free a block.
 *
 * @param uid The UID of the pool.
 * @param data The data block to deallocate.
 *
 * @return `0` on success, `< 0` on error.
 *
 * @attention Requires linking to `pspthreadman_user` or `pspthreadman_kernel` stubs to be available.
 */
int sceKernelFreeFpl(SceUID uid, void *data);

/**
 * Cancel a pool.
 *
 * @param uid The UID of the pool.
 * @param pnum Receives the number of waiting threads.
 *
 * @return `0` on success, `< 0` on error.
 *
 * @attention Requires linking to `pspthreadman_user` or `pspthreadman_kernel` stubs to be available.
 */
int sceKernelCancelFpl(SceUID uid, int *pnum);

/**
 * Get the status of an FPL.
 *
 * @param uid The uid of the FPL.
 * @param info A pointer to a `SceKernelFplInfo` structure.
 *
 * @return `0` on success, `< 0` on error.
 *
 * @attention Requires linking to `pspthreadman_user` or `pspthreadman_kernel` stubs to be available.
 */
int sceKernelReferFplStatus(SceUID uid, SceKernelFplInfo *info);

/**
 * Return from a timer handler (doesn't seem to do alot).
 *
 * @attention Requires linking to `pspthreadman_user` or `pspthreadman_kernel` stubs to be available.
 */
void _sceKernelReturnFromTimerHandler(void);

/**
 * Return from a callback (used as a syscall for the return
 * of the callback function).
 *
 * @attention Requires linking to `pspthreadman_user` or `pspthreadman_kernel` stubs to be available.
 */
void _sceKernelReturnFromCallback(void);

/**
 * Convert a number of microseconds to a `SceKernelSysClock` structure.
 *
 * @param usec The number of microseconds.
 * @param[out] clock A pointer to a `SceKernelSysClock` structure.
 *
 * @return `0` on success, `< 0` on error.
 *
 * @attention Requires linking to `pspthreadman_user` or `pspthreadman_kernel` stubs to be available.
 */
int sceKernelUSec2SysClock(u32 usec, SceKernelSysClock *clock);

/**
 * Convert a number of microseconds to a wide time
 *
 * @param usec The number of microseconds.
 *
 * @return The time.
 *
 * @attention Requires linking to `pspthreadman_user` or `pspthreadman_kernel` stubs to be available.
 */
SceInt64 sceKernelUSec2SysClockWide(u32 usec);

/**
 * Convert a `SceKernelSysClock` structure to microseconds.
 *
 * @param[in] clock A pointer to a `SceKernelSysClock` structure.
 * @param[out] low A pointer to the low part of the time.
 * @param[out] high A pointer to the high part of the time.
 *
 * @return `0` on success, `< 0` on error.
 *
 * @attention Requires linking to `pspthreadman_user` or `pspthreadman_kernel` stubs to be available.
 */
int sceKernelSysClock2USec(SceKernelSysClock *clock, u32 *low, u32 *high);

/**
 * Convert a wide time to microseconds.
 *
 * @param clock The wide time.
 * @param[out] low A pointer to the low part of the time.
 * @param[out] high A pointer to the high part of the time.
 *
 * @return `0` on success, `< 0` on error.
 *
 * @attention Requires linking to `pspthreadman_user` or `pspthreadman_kernel` stubs to be available.
 */
int sceKernelSysClock2USecWide(SceInt64 clock, unsigned *low, u32 *high);

/**
 * Get the system time.
 *
 * @param time A pointer to a `SceKernelSysClock` structure.
 *
 * @return `0` on success, `< 0` on error.
 *
 * @attention Requires linking to `pspthreadman_user` or `pspthreadman_kernel` stubs to be available.
 */
int sceKernelGetSystemTime(SceKernelSysClock *time);

/**
 * Get the system time (wide version).
 *
 * @return The system time.
 *
 * @attention Requires linking to `pspthreadman_user` or `pspthreadman_kernel` stubs to be available.
 */
SceInt64 sceKernelGetSystemTimeWide(void);

/**
 * Get the low 32bits of the current system time.
 *
 * @return The low 32bits of the system time.
 *
 * @attention Requires linking to `pspthreadman_user` or `pspthreadman_kernel` stubs to be available.
 */
u32 sceKernelGetSystemTimeLow(void);

/**
 * Create a virtual timer.
 *
 * @param name A name for the timer.
 * @param opt  A pointer to an `SceKernelVTimerOptParam` (pass `NULL`).
 *
 * @return The VTimer's UID or `< 0` on error.
 *
 * @attention Requires linking to `pspthreadman_user` or `pspthreadman_kernel` stubs to be available.
 */
SceUID sceKernelCreateVTimer(const char *name, struct SceKernelVTimerOptParam *opt);

/**
 * Delete a virtual timer.
 *
 * @param uid The UID of the timer.
 *
 * @return `< 0` on error.
 *
 * @attention Requires linking to `pspthreadman_user` or `pspthreadman_kernel` stubs to be available.
 */
int sceKernelDeleteVTimer(SceUID uid);

/**
 * Get the timer base.
 *
 * @param uid The UID of the vtimer.
 * @param base A pointer to a `SceKernelSysClock` structure.
 *
 * @return `0` on success, `< 0` on error.
 *
 * @attention Requires linking to `pspthreadman_user` or `pspthreadman_kernel` stubs to be available.
 */
int sceKernelGetVTimerBase(SceUID uid, SceKernelSysClock *base);

/**
 * Get the timer base (wide format).
 *
 * @param uid The UID of the vtimer.
 *
 * @return The 64bit timer base.
 *
 * @attention Requires linking to `pspthreadman_user` or `pspthreadman_kernel` stubs to be available.
 */
SceInt64 sceKernelGetVTimerBaseWide(SceUID uid);

/**
 * Get the timer time.
 *
 * @param uid The UID of the vtimer.
 * @param[out] time A pointer to a `SceKernelSysClock` structure.
 *
 * @return `0` on success, `< 0` on error.
 *
 * @attention Requires linking to `pspthreadman_user` or `pspthreadman_kernel` stubs to be available.
 */
int sceKernelGetVTimerTime(SceUID uid, SceKernelSysClock *time);

/**
 * Get the timer time (wide format).
 *
 * @param uid The UID of the vtimer.
 *
 * @return The 64bit timer time.
 *
 * @attention Requires linking to `pspthreadman_user` or `pspthreadman_kernel` stubs to be available.
 */
SceInt64 sceKernelGetVTimerTimeWide(SceUID uid);

/**
 * Set the timer time.
 *
 * @param uid The UID of the vtimer.
 * @param[in] time A pointer to a `SceKernelSysClock` structure.
 *
 * @return `0` on success, `< 0` on error.
 *
 * @attention Requires linking to `pspthreadman_user` or `pspthreadman_kernel` stubs to be available.
 */
int sceKernelSetVTimerTime(SceUID uid, SceKernelSysClock *time);

/**
 * Set the timer time (wide format)
 *
 * @param uid The UID of the vtimer
 * @param time A wide time.
 *
 * @return Possibly the last time.
 *
 * @attention Requires linking to `pspthreadman_user` or `pspthreadman_kernel` stubs to be available.
 */
SceInt64 sceKernelSetVTimerTimeWide(SceUID uid, SceInt64 time);

/**
 * Start a virtual timer.
 *
 * @param uid The UID of the timer.
 *
 * @return `< 0` on error.
 *
 * @attention Requires linking to `pspthreadman_user` or `pspthreadman_kernel` stubs to be available.
 */
int sceKernelStartVTimer(SceUID uid);

/**
 * Stop a virtual timer
 *
 * @param uid The UID of the timer
 *
 * @return `< 0` on error.
 *
 * @attention Requires linking to `pspthreadman_user` or `pspthreadman_kernel` stubs to be available.
 */
int sceKernelStopVTimer(SceUID uid);

/**
 * Set the timer handler.
 *
 * @param uid The UID of the vtimer.
 * @param[in] time A time to call the handler?
 * @param[in] handler The timer handler.
 * @param[in] common  A common pointer.
 *
 * @return `0` on success, `< 0` on error.
 *
 * @attention Requires linking to `pspthreadman_user` or `pspthreadman_kernel` stubs to be available.
 */
int sceKernelSetVTimerHandler(SceUID uid, SceKernelSysClock *time, SceKernelVTimerHandler handler, void *common);

/**
 * Set the timer handler (wide mode).
 *
 * @param uid The UID of the vtimer.
 * @param[in] time A time to call the handler?
 * @param[in] handler The timer handler.
 * @param[in] common  A common pointer.
 *
 * @return `0` on success, `< 0` on error.
 *
 * @attention Requires linking to `pspthreadman_user` or `pspthreadman_kernel` stubs to be available.
 */
int sceKernelSetVTimerHandlerWide(SceUID uid, SceInt64 time, SceKernelVTimerHandlerWide handler, void *common);

/**
 * Cancel the timer handler.
 *
 * @param uid The UID of the vtimer.
 *
 * @return `0` on success, `< 0` on error.
 *
 * @attention Requires linking to `pspthreadman_user` or `pspthreadman_kernel` stubs to be available.
 */
int sceKernelCancelVTimerHandler(SceUID uid);

/**
 * Get the status of a VTimer.
 *
 * @param uid The uid of the VTimer.
 * @param[out] info A pointer to a `SceKernelVTimerInfo` structure.
 *
 * @return `0` on success, `< 0` on error.
 *
 * @attention Requires linking to `pspthreadman_user` or `pspthreadman_kernel` stubs to be available.
 */
int sceKernelReferVTimerStatus(SceUID uid, SceKernelVTimerInfo *info);

/**
 * Exit the thread (probably used as the syscall when the main thread
 * returns.
 *
 * @attention Requires linking to `pspthreadman_user` or `pspthreadman_kernel` stubs to be available.
 */
void _sceKernelExitThread(void);

/**
 * Get the type of a threadman UID.
 *
 * @param uid The UID to get the type from.
 *
 * @return The type, `< 0` on error.
 *
 * @attention Requires linking to `pspthreadman_user` or `pspthreadman_kernel` stubs to be available.
 */
SceKernelIdListType sceKernelGetThreadmanIdType(SceUID uid);

/**
 * Register a thread event handler
 *
 * @param[in] name A name for the thread event handler.
 * @param threadID The thread ID to monitor.
 * @param mask The bit mask for what events to handle (only lowest 4 bits valid).
 * @param[in] handler A pointer to a `SceKernelThreadEventHandler` function.
 * @param[in] common A common pointer.
 *
 * @return The UID of the create event handler, `< 0` on error.
 *
 * @attention Requires linking to `pspthreadman_user` or `pspthreadman_kernel` stubs to be available.
 */
SceUID sceKernelRegisterThreadEventHandler(const char *name, SceUID threadID, int mask, SceKernelThreadEventHandler handler, void *common);

/**
 * Release a thread event handler.
 *
 * @param uid The UID of the event handler
 *
 * @return `0` on success, `< 0` on error.
 *
 * @attention Requires linking to `pspthreadman_user` or `pspthreadman_kernel` stubs to be available.
 */
int sceKernelReleaseThreadEventHandler(SceUID uid);

/**
 * Refer the status of an thread event handler.
 *
 * @param uid The UID of the event handler.
 * @param[out] info A pointer to a `SceKernelThreadEventHandlerInfo` structure.
 *
 * @return `0` on success, `< 0` on error.
 *
 * @attention Requires linking to `pspthreadman_user` or `pspthreadman_kernel` stubs to be available.
 */
int sceKernelReferThreadEventHandlerStatus(SceUID uid, struct SceKernelThreadEventHandlerInfo *info);

/**
 * Get the thread profiler registers.
 *
 * @return Pointer to the registers, `NULL` on error.
 *
 * @attention Requires linking to `pspthreadman_user` or `pspthreadman_kernel` stubs to be available.
 */
PspDebugProfilerRegs *sceKernelReferThreadProfiler(void);

/**
 * Get the globile profiler registers.
 * @return Pointer to the registers, `NULL` on error.
 *
 * @attention Requires linking to `pspthreadman_user` or `pspthreadman_kernel` stubs to be available.
 */
PspDebugProfilerRegs *sceKernelReferGlobalProfiler(void);

/**@}*/

#ifdef __KERNEL__

/**
 * Suspend all user mode threads in the system.
 *
 * @return `0` on success, `< 0` on error.
 *
 * @attention Requires linking to `pspthreadman_kernel` stub to be available.
 */
int sceKernelSuspendAllUserThreads(void);

/**
 * Checks if the current thread is a usermode thread.
 *
 * @return `0` if kernel, `1` if user, `< 0` on error.
 *
 * @attention Requires linking to `pspthreadman_kernel` stub to be available.
 */
int sceKernelIsUserModeThread(void);

/**
 * Get the user level of the current thread.
 *
 * @return The user level, `< 0` on error.
 *
 * @attention Requires linking to `pspthreadman_kernel` stub to be available.
 */
int sceKernelGetUserLevel(void);

/**
 * Get the return address of the current thread's syscall.
 *
 * @return The RA, `0` on error.
 *
 * @attention Requires linking to `pspthreadman_kernel` stub to be available.
 */
u32 sceKernelGetSyscallRA(void);

/**
 * Get the free stack space on the kernel thread.
 *
 * @param thid The UID of the thread.
 *
 * @return The free stack space, `< 0` on error.
 *
 * @attention Requires linking to `pspthreadman_kernel` stub to be available.
 */
int sceKernelGetThreadKernelStackFreeSize(SceUID thid);

/**
 * Check the thread kernel stack.
 *
 * @return Unknown.
 *
 * @attention Requires linking to `pspthreadman_kernel` stub to be available.
 */
int sceKernelCheckThreadKernelStack(void);

/**
 * Extend the kernel thread stack.
 *
 * @param type The type of block allocation. One of `PspSysMemBlockTypes`.
 * @param[in] cb A pointer to a callback function.
 * @param[in] arg A pointer to a user specified argument.
 *
 * @return `< 0` on error.
 *
 * @attention Requires linking to `pspthreadman_kernel` stub to be available.
 */
int sceKernelExtendKernelStack(int type, void (*cb)(void*), void *arg);

/**
 * Get the system status flag.
 *
 * @return The system status flag.
 *
 * @attention Requires linking to `pspthreadman_kernel` stub to be available.
 */
u32 sceKernelGetSystemStatusFlag(void);

/**
 * Setup the KTLS allocator.
 *
 * @param id The ID of the allocator.
 * @param[in] cb The allocator callback.
 * @param[in] arg A user specified arg passed to the callback.
 *
 * @return `< 0` on error., allocation ID on success.
 *
 * @attention Requires linking to `pspthreadman_kernel` stub to be available.
 */
int sceKernelAllocateKTLS(int id, int (*cb)(u32 *size, void *arg), void *arg);

/**
 * Free the KTLS allocator.
 *
 * @param id The allocation id returned from AllocateKTLS.
 *
 * @return `< 0` on error.
 *
 * @attention Requires linking to `pspthreadman_kernel` stub to be available.
 */
int sceKernelFreeKTLS(int id);

/**
 * Get the KTLS of the current thread.
 *
 * @param id The allocation id returned from AllocateKTLS.
 *
 * @return The current KTLS, `NULL` on error.
 *
 * @attention Requires linking to `pspthreadman_kernel` stub to be available.
 */
void *sceKernelGetKTLS(int id);

/**
 * Get the KTLS of a thread.
 *
 * @param id The allocation id returned from AllocateKTLS.
 * @param thid The thread ID, `0` for current thread.
 * @param mode Perhaps? Sees to be set to `0` or `1`.
 *
 * @return The current KTLS, `NULL` on error.
 *
 * @attention Requires linking to `pspthreadman_kernel` stub to be available.
 */
void *sceKernelGetThreadKTLS(int id, SceUID thid, int mode);

/**
 * Refer kernel version of thread information.
 *
 * @param uid The UID to find.
 * @param[out] info A pointer to info structure, ensure size is set before calling.
 *
 * @return `0` on success.
 *
 * @attention Requires linking to `pspthreadman_kernel` stub to be available.
 */
int sceKernelReferThreadDebugStatus(SceUID uid, SceKernelThreadKInfo *info);

#endif /* __KERNEL__ */


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __THREADMAN_H__ */
