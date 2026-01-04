/*
 * PSP Software Development Kit - https://github.com/pspdev
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * pspkermit.h - Prototypes for the kermit related libraries.
 *
 * Copyright (c) 2025 Acid_Snake
 * Copyright (c) 2025 GrayJack
 *
 */

#ifndef __KERMIT_H__
#define __KERMIT_H__

#include <pspkerneltypes.h>

#define KERMIT_MAX_ARGC     (14)

/* KERMIT_PACKET address macros */
#define KERNEL(x)   ((x & 0x80000000)? 1:0)
#define KERMIT_PACKET(x)    (x | (2-KERNEL(x))*0x20000000)
#define ALIGN_64(x) ((x) & -64)
#define KERMIT_CALLBACK_DISABLE 0

typedef enum KermitModes {
    KERMIT_MODE_NONE,
    KERMIT_MODE_UNK_1,
    KERMIT_MODE_UNK_2,
    KERMIT_MODE_MSFS,
    KERMIT_MODE_FLASHFS,
    KERMIT_MODE_AUDIOOUT,
    KERMIT_MODE_ME,
    KERMIT_MODE_LOWIO,
    KERMIT_MODE_POCS_USBPSPCM,
    KERMIT_MODE_PERIPHERAL,
    KERMIT_MODE_WLAN,
    KERMIT_MODE_AUDIOIN,
    KERMIT_MODE_USB,
    KERMIT_MODE_UTILITY,
    KERMIT_MODE_EXTRA_1,
    KERMIT_MODE_EXTRA_2,
} KermitModes;

/* Kermit `KERMIT_MODE_PERIPHERAL` commands */
typedef enum KermitPeripheralCmd {
	KERMIT_CMD_RTC_GET_CURRENT_TICK = 0x0,
	KERMIT_CMD_ID_STORAGE_LOOKUP = 0x1,
	KERMIT_CMD_POWER_FREQUENCY = 0x2,
	KERMIT_CMD_AUDIO_ROUTING = 0x3,
	KERMIT_CMD_GET_CAMERA_DIRECTION = 0x5,
	KERMIT_CMD_GET_IDPSC_ENABLE = 0x6,
	KERMIT_CMD_DISABLE_MULTITASKING = 0x7,
	KERMIT_CMD_ERROR_EXIT = 0x8,
	KERMIT_CMD_ERROR_EXIT_2 = 0x422,
	KERMIT_CMD_ENABLE_MULTITASKING = 0x9,
	KERMIT_CMD_RESUME_DEVICE = 0xA,
	KERMIT_CMD_REQUEST_SUSPEND = 0xB,
	KERMIT_CMD_IS_FIRST_BOOT = 0xC,
	KERMIT_CMD_GET_PREFIX_SSID = 0xD,
	KERMIT_CMD_SET_PS_BUTTON_STATE = 0x10,
} KermitPeripheralCmd;

/* Kermit `KERMIT_MODE_MSFS` commands */
typedef enum KermitMsfsCmd {
	KERMIT_CMD_INIT_MS = 0x0,
	KERMIT_CMD_EXIT_MS = 0x1,
	KERMIT_CMD_OPEN_MS = 0x2,
	KERMIT_CMD_CLOSE_MS = 0x3,
	KERMIT_CMD_READ_MS = 0x4,
	KERMIT_CMD_WRITE_MS = 0x5,
	KERMIT_CMD_SEEK_MS = 0x6,
	KERMIT_CMD_IOCTL_MS = 0x7,
	KERMIT_CMD_REMOVE_MS = 0x8,
	KERMIT_CMD_MKDIR_MS = 0x9,
	KERMIT_CMD_RMDIR_MS = 0xA,
	KERMIT_CMD_DOPEN_MS = 0xB,
	KERMIT_CMD_DCLOSE_MS = 0xC,
	KERMIT_CMD_DREAD_MS = 0xD,
	KERMIT_CMD_GETSTAT_MS = 0xE,
	KERMIT_CMD_CHSTAT_MS = 0xF,
	KERMIT_CMD_RENAME_MS = 0x10,
	KERMIT_CMD_CHDIR_MS = 0x11,
	KERMIT_CMD_DEVCTL = 0x14,
} KermitMsfsCmd;

/* Kermit `KERMIT_MODE_AUDIO` commands */
typedef enum KermitAudioCmd {
	KERMIT_CMD_INIT_AUDIO_IN = 0x0,
	KERMIT_CMD_OUTPUT_1 = 0x1,
	KERMIT_CMD_OUTPUT_2 = 0x2,
	KERMIT_CMD_SUSPEND_AUDIO = 0x3,
	KERMIT_CMD_RESUME = 0x4,
} KermitAudioCmd;

/* Kermit `KERMIT_MODE_ME` commands */
typedef enum KermitMeCmd {
	KERMIT_CMD_UNK0= 0x0,
	KERMIT_CMD_SETAVC_TIMESTAMPINTERNAL= 0x1,
	KERMIT_CMD_BOOT_START= 0x2,
} KermitMeCmd;

/* Kermit `KERMIT_MODE_LOWIO` commands */
typedef enum KermitLowIoCmd {
	KERMIT_CMD_UNK9 = 0x9,
	KERMIT_CMD_UNKA = 0xA,
	KERMIT_CMD_UNKB = 0xB,
	KERMIT_CMD_UNKC = 0xC,
} KermitLowIoCmd;

/* Kermit `KERMIT_MODE_WLAN` commands */
typedef enum KermitWlanCmd {
	KERMIT_CMD_INIT = 0x0,
	KERMIT_CMD_GET_SWITCH_INTERNAL_STATE = 0x2,
	KERMIT_CMD_GET_ETHER_ADDR = 0x3,
	KERMIT_CMD_ADHOC_CTL_INIT = 0x6,
	KERMIT_CMD_ADHOC_CTL_TERM = 0x7,
	KERMIT_CMD_ADHOC_SCAN = 0x8,
	KERMIT_CMD_ADHOC_JOIN = 0x9,
	KERMIT_CMD_ADHOC_CREATE = 0xA,
	KERMIT_CMD_ADHOC_LEAVE = 0xB,
	KERMIT_CMD_ADHOC_TX_DATA = 0xC,
	KERMIT_CMD_ADHOC_RX_DATA = 0xD,
	KERMIT_CMD_INET_INIT = 0xE,
	KERMIT_CMD_INET_START = 0xF,
	KERMIT_CMD_INET_TERM = 0x10,
	KERMIT_CMD_INET_SOCKET = 0x11,
	KERMIT_CMD_INET_CLOSE = 0x12,
	KERMIT_CMD_INET_BIND = 0x13,
	KERMIT_CMD_INET_LISTEN = 0x14,
	KERMIT_CMD_INET_CONNECT = 0x15,
	KERMIT_CMD_INET_SHUTDOWN = 0x16,
	KERMIT_CMD_INET_POLL = 0x17,
	KERMIT_CMD_INET_ACCEPT = 0x18,
	KERMIT_CMD_INET_GET_PEER_NAME = 0x19,
	KERMIT_CMD_INET_GET_SOCK_NAME = 0x1A,
	KERMIT_CMD_INET_GET_OPT = 0x1B,
	KERMIT_CMD_INET_SET_OPT = 0x1C,
	KERMIT_CMD_INET_RECV_FROM = 0x1D,
	KERMIT_CMD_INET_SENDTO_INTERNAL = 0x1E,
	KERMIT_CMD_INET_SOIOCTL = 0x1F,
	KERMIT_CMD_SUSPEND_WLAN = 0x20,
	KERMIT_CMD_SET_WOL_PARAM = 0x22,
	KERMIT_CMD_GET_WOL_INFO = 0x23,
	KERMIT_CMD_SET_HOST_DISCOVER = 0x24,
} KermitWlanCmd;

/* Kermit `KERMIT_MODE_UTILITY` commands */
typedef enum KermitUtilityCmd {
	KERMIT_CMD_OSK_START = 0x0,
	KERMIT_CMD_OSK_SHUTDOWN = 0x1,
	KERMIT_CMD_OSK_UPDATE = 0x3,
} KermitUtilityCmd;

/* Kermit `KERMIT_MODE_USB` commands */
typedef enum KermitUsbCmd {
	KERMIT_CMD_INIT = 0x0,
	KERMIT_CMD_ACTIVATE = 0x15,
	KERMIT_CMD_DEACTIVATE = 0x16,
	KERMIT_CMD_SET_OP = 0x19,
	KERMIT_CMD_SET_OP_BIS = 0x1A,
	KERMIT_CMD_UNK1B = 0x1B,
} KermitUsbCmd;


typedef enum KermitVirtualInterrupts {
    KERMIT_VIRTUAL_INTR_NONE,
    KERMIT_VIRTUAL_INTR_AUDIO_CH1,
    KERMIT_VIRTUAL_INTR_AUDIO_CH2,
    KERMIT_VIRTUAL_INTR_AUDIO_CH3,
    KERMIT_VIRTUAL_INTR_ME_DMA_CH1,
    KERMIT_VIRTUAL_INTR_ME_DMA_CH2,
    KERMIT_VIRTUAL_INTR_ME_DMA_CH3,
    KERMIT_VIRTUAL_INTR_WLAN_CH1,
    KERMIT_VIRTUAL_INTR_WLAN_CH2,
    KERMIT_VIRTUAL_INTR_IMPOSE_CH1,
    KERMIT_VIRTUAL_INTR_POWER_CH1,
    KERMIT_VIRTUAL_INTR_UNKNOWN_CH1,    // <- used after settings
    KERMIT_VIRTUAL_INTR_USBGPS_CH1,
    KERMIT_VIRTUAL_INTR_USBPSPCM_CH1,
} KermitVirtualInterrupts;

typedef enum KermitArgumentModes {
	KERMIT_INPUT_MODE = 0x1,
	KERMIT_OUTPUT_MODE = 0x2,
} KermitArgumentModes;

typedef struct {
    u32 cmd; //0x0
    SceUID sema_id; //0x4
    u64 *response; //0x8
    u32 padding; //0xC
    u64 args[14]; // 0x10
} SceKermitRequest; //0x80

typedef struct {
    u32 cmd; //0x00
    SceKermitRequest *request; //0x04
} SceKermitCommand; //0x8

// 0xBFC00840
typedef struct {
    u64 result; //0x0
    SceUID sema_id; //0x8
    s32 unk_C; //0xC
    u64 *response; //0x10
    u64 unk_1C; //0x1C
} SceKermitResponse; //0x24 or 0x30????

// 0xBFC008C0
typedef struct {
    s32 unk_0; //0x0
    s32 unk_4; //0x4
} SceKermitInterrupt; //0x8

typedef struct KermitPacket_
{
    u32 cmd;            //0x0
    SceUID sema;        //0x4
    struct KermitPacket_ *self; //0x8
    u32 unk_C;          //0xC
} KermitPacket;

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#ifdef __KERNEL__

/**
 * Register handler for a kermit virtual interrupt.
 *
 * @param interrupt_id The ID of the virtual interrupt.
 * @param[in] handler A pointer to the handler function to register.
 *
 * @return `0` on success, else `< 0` on error.
 *
 * @attention Requires linking to `pspkermit_driver` stub to be available.
 */
int sceKermitRegisterVirtualIntrHandler(u32 interrupt_id, void* handler);

/**
 * Send a request to kermit.
 *
 * @param[in] request A pointer to the request information.
 * @param mode The command mode. One of `KermitModes`.
 * @param cmd The command subtype for the specified `mode`.
 * @param argc The number of 64 bit arguments following the header. Max 13 arguments.
 * @param allow_callback Set non-zero to use callback, permitting semaphore wait.
 * @param[out] resp A pointer to receive a 64 bit word returned by the kermit call.
 *
 * @return `0` on success, else `< 0` on error.
 *
 * @attention Requires linking to `pspkermit_driver` stub to be available.
 */
int sceKermitSendRequest(SceKermitRequest* request, u32 mode, u32 cmd, int argc, u32 allow_callback, u64* response);

/**
 * Apply IO to kermit packet.
 *
 * @param[in] packet A pointer to a kermit packet. Header followed by 64 bit words (LE) as arguments.
 * @param argc The number of 64 bit arguments following the header. Max 13 arguments.
 * @param[inout] buffer A pointer to a input buffer containing the data to be sent or the output buffer to store data.
 * @param buffer_size The size of the the `buffer`.
 * @param io_mode The I/O mode of the buffer. One of `KermitArgumentModes`.
 *
 * @attention Requires linking to `pspkermitmemory_driver` stub to be available.
 */
void sceKermitMemorySetArgument(KermitPacket *packet, u32 argc, const void *buffer, u32 buffer_size, u32 io_mode);

#ifndef _USE_PSPSDK_STUB

/**
 * Send data to VITA host.
 *
 * @param[in] data A pointer to the data to be sent to the host.
 * @param len The size of the data to be sent.
 *
 * @attention Requires linking to `pspkermitmemory_driver` stub to be available.
 */
void sceKermitMemorySendData(const void *data, u32 len);

/**
 * Receive data from VITA host.
 *
 * @param[out] data A pointer to buffer to store output data.
 * @param len The size of the expected output data.
 *
 * @attention Requires linking to `pspkermitmemory_driver` stub to be available.
 */
void sceKermitMemoryReceiveData(u8 *data, u32 data_size);

#else

/**
 * Send data to VITA host.
 *
 * @param[in] data A pointer to the data to be sent to the host.
 * @param len The size of the data to be sent.
 *
 * @attention Requires linking to `pspkermitmemory_driver` stub to be available.
 */
void sceKermitMemory_driver_80E1240A(const void *data, u32 len);

/**
 * Receive data from VITA host.
 *
 * @param[out] data A pointer to buffer to store output data.
 * @param len The size of the expected output data.
 *
 * @attention Requires linking to `pspkermitmemory_driver` stub to be available.
 */
void sceKermitMemory_driver_90B662D0(u8 *data, u32 data_size);

#endif // _USE_PSPSDK_STUB

#endif // __KERNEL__

#ifdef __cplusplus
}
#endif // __cplusplus

#endif /* __KERMIT_H__ */
