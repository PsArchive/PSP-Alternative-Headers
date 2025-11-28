/*
 * PSP Software Development Kit - https://github.com/pspdev
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * psppower.h - Prototypes for the scePower and scePower_driver libraries.
 *
 * Copyright (c) 2005 Marcus R. Brown <mrbrown@ocgnet.org>
 * Copyright (c) 2005 James Forshaw <tyranid@gmail.com>
 * Copyright (c) 2005 John Kelley <ps2dev@kelley.ca>
 * Copyright (c) 2005 David Perry <tias_dp@hotmail.com>
 * Copyright (c) 2025 GrayJack <gr41.j4ck@gmail.com>
 *
 */
#ifndef __POWER_H__
#define __POWER_H__

#include <pspkerneltypes.h>

/**
 * Power callback flags
 */
typedef enum ScePowerCallbackFlags {
	/* Indicates the power switch it pushed, putting the unit into suspend mode */
	SCE_POWER_CB_POWER_SWITCH = 0x80000000,
	/* Indicates the hold switch is on */
	SCE_POWER_CB_HOLD_SWITCH = 0x40000000,
	/* What is standby mode? */
	SCE_POWER_CB_STANDBY  = 0x00080000,
	/* Indicates the resume process has been completed (only seems to be triggered when another event happens) */
	SCE_POWER_CB_RESUME_COMPLETE = 0x00040000,
	/* Indicates the unit is resuming from suspend mode */
	SCE_POWER_CB_RESUMING  = 0x00020000,
	/* Indicates the unit is suspending, seems to occur due to inactivity */
	SCE_POWER_CB_SUSPENDING  = 0x00010000,
	/* Indicates the unit is plugged into an AC outlet */
	SCE_POWER_CB_AC_POWER  = 0x00001000,
	/* Indicates the battery charge level is low */
	SCE_POWER_CB_BATTERY_LOW = 0x00000100,
	/* Indicates there is a battery present in the unit */
	SCE_POWER_CB_BATTERY_EXIST = 0x00000080,
	/*unknown*/
	SCE_POWER_CB_BATTPOWER  = 0x0000007F,


	/* Indicates the power switch it pushed, putting the unit into suspend mode */
	PSP_POWER_CB_POWER_SWITCH = SCE_POWER_CB_POWER_SWITCH,
	/* Indicates the hold switch is on */
	PSP_POWER_CB_HOLD_SWITCH = SCE_POWER_CB_HOLD_SWITCH,
	/* What is standby mode? */
	PSP_POWER_CB_STANDBY = SCE_POWER_CB_STANDBY,
	/* Indicates the resume process has been completed (only seems to be triggered when another event happens) */
	PSP_POWER_CB_RESUME_COMPLETE = SCE_POWER_CB_RESUME_COMPLETE,
	/* Indicates the unit is resuming from suspend mode */
	PSP_POWER_CB_RESUMING = SCE_POWER_CB_RESUMING,
	/* Indicates the unit is suspending, seems to occur due to inactivity */
	PSP_POWER_CB_SUSPENDING = SCE_POWER_CB_SUSPENDING,
	/* Indicates the unit is plugged into an AC outlet */
	PSP_POWER_CB_AC_POWER = SCE_POWER_CB_AC_POWER,
	/* Indicates the battery charge level is low */
	PSP_POWER_CB_BATTERY_LOW = SCE_POWER_CB_BATTERY_LOW,
	/* Indicates there is a battery present in the unit */
	PSP_POWER_CB_BATTERY_EXIST = SCE_POWER_CB_BATTERY_EXIST,
	/*unknown*/
	PSP_POWER_CB_BATTPOWER = SCE_POWER_CB_BATTPOWER,
} ScePowerCallbackFlags;


/**
 * Power tick flags
 */
typedef enum ScePowerTickFlags {
	/* All */
	SCE_POWER_TICK_ALL = 0,
	/* Suspend */
	SCE_POWER_TICK_SUSPEND = 1,
	/* Display */
	SCE_POWER_TICK_DISPLAY = 6,

	/* All */
	PSP_POWER_TICK_ALL = SCE_POWER_TICK_ALL,
	/* Suspend */
	PSP_POWER_TICK_SUSPEND = SCE_POWER_TICK_SUSPEND,
	/* Display */
	PSP_POWER_TICK_DISPLAY = SCE_POWER_TICK_DISPLAY,
} ScePowerTickFlags;

#define SCE_POWER_SLOT_AUTO (-1)

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Power Callback Function Definition.
 *
 * @param unknown Unknown function, appears to cycle between 1,2 and 3
 * @param power_info A combination of `ScePowerCallbackFlags` flags
 */
typedef void (*powerCallback_t)(int unknown, int power_info);

/**
 * Register Power Callback Function.
 *
 * @param slot The slot of the callback in the list (`0` to `15`). Pass `SCE_POWER_SLOT_AUTO` to get an auto assignment.
 * @param cb_id The callback ID from calling `sceKernelCreateCallback()`.
 *
 * @return `0` on success, the slot number if `SCE_POWER_SLOT_AUTO` is passed, `< 0` on error.
 *
 * @attention Requires linking to `psppower` (PSPSDK), `psppower_user` (Adrenaline stubs)  or `psppower_driver` stubs to be available.
 */
int scePowerRegisterCallback(int slot, SceUID cb_id);

/**
 * Unregister Power Callback Function.
 *
 * @param slot The slot of the callback
 *
 * @return `0` on success, `< 0` on error.
 *
 * @attention Requires linking to `psppower` (PSPSDK), `psppower_user` (Adrenaline stubs)  or `psppower_driver` stubs to be available.
 */
int scePowerUnregisterCallback(int slot);

/**
 * Check if unit is plugged in.
 *
 * @return `1` if plugged in, `0` if not plugged in, `< 0` on error.
 *
 * @attention Requires linking to `psppower` (PSPSDK), `psppower_user` (Adrenaline stubs)  or `psppower_driver` stubs to be available.
 */
int scePowerIsPowerOnline(void);

/**
 * Check if a battery is present.
 *
 * @return `1` if battery present, `0` if battery not present, `< 0` on error.
 *
 * @attention Requires linking to `psppower` (PSPSDK), `psppower_user` (Adrenaline stubs)  or `psppower_driver` stubs to be available.
 */
int scePowerIsBatteryExist(void);

/**
 * Check if the battery is charging.
 *
 * @return `1` if battery charging, `0` if battery not charging, `< 0` on error.
 *
 * @attention Requires linking to `psppower` (PSPSDK), `psppower_user` (Adrenaline stubs)  or `psppower_driver` stubs to be available.
 */
int scePowerIsBatteryCharging(void);

/**
 * Get the status of the battery charging.
 *
 * @return The battery charging status, `< 0` on error.
 *
 * @attention Requires linking to `psppower` (PSPSDK), `psppower_user` (Adrenaline stubs)  or `psppower_driver` stubs to be available.
 */
int scePowerGetBatteryChargingStatus(void);

/**
 * Check if the battery is low.
 *
 * @return `1` if the battery is low, `0` if the battery is not low, `< 0` on error.
 *
 * @attention Requires linking to `psppower` (PSPSDK), `psppower_user` (Adrenaline stubs)  or `psppower_driver` stubs to be available.
 */
int scePowerIsLowBattery(void);

/**
 * Check if a suspend is required.
 *
 * @return `1` if suspend is required, `0` otherwise.
 *
 * @attention Requires linking to `psppower` (PSPSDK), `psppower_user` (Adrenaline stubs)  or `psppower_driver` stubs to be available.
 */
int scePowerIsSuspendRequired(void);

/**
 * Returns battery remaining capacity
 *
 * @return The battery remaining capacity in mAh (milliampere hour)
 *
 * @attention Requires linking to `psppower` (PSPSDK), `psppower_user` (Adrenaline stubs)  or `psppower_driver` stubs to be available.
 */
int scePowerGetBatteryRemainCapacity(void);

/**
 * Returns battery full capacity
 *
 * @return The battery full capacity in mAh (milliampere hour)
 *
 * @attention Requires linking to `psppower` (PSPSDK), `psppower_user` (Adrenaline stubs)  or `psppower_driver` stubs to be available.
 */
int scePowerGetBatteryFullCapacity(void);

/**
 * Get battery life as integer percent.
 *
 * @return The battery charge percentage (`0`-`100`), `< 0` on error.
 *
 * @attention Requires linking to `psppower` (PSPSDK), `psppower_user` (Adrenaline stubs)  or `psppower_driver` stubs to be available.
 */
int scePowerGetBatteryLifePercent(void);

/**
 * Get battery life as time.
 *
 * @return The battery life in minutes, `< 0` on error.
 *
 * @attention Requires linking to `psppower` (PSPSDK), `psppower_user` (Adrenaline stubs)  or `psppower_driver` stubs to be available.
 */
int scePowerGetBatteryLifeTime(void);

/**
 * Get temperature of the battery.
 *
 * @return The battery temperature, `< 0` on error.
 *
 * @attention Requires linking to `psppower` (PSPSDK), `psppower_user` (Adrenaline stubs)  or `psppower_driver` stubs to be available.
 */
int scePowerGetBatteryTemp(void);

/**
 * unknown? - crashes PSP in usermode
 *
 * @attention Requires linking to `psppower` (PSPSDK), `psppower_user` (Adrenaline stubs)  or `psppower_driver` stubs to be available.
 */
int scePowerGetBatteryElec(void);

/**
 * Get battery volt level.
 *
 * @return The battery volt level, `< 0` on error.
 *
 * @attention Requires linking to `psppower` (PSPSDK), `psppower_user` (Adrenaline stubs)  or `psppower_driver` stubs to be available.
 */
int scePowerGetBatteryVolt(void);

/**
 * Set the CPU frequency.
 *
 * @param cpu_freq The new CPU frequency, valid values are `1 - 333`
 *
 * @return `0` on success, `< 0` on error.
 *
 * @attention Requires linking to `psppower` (PSPSDK), `psppower_user` (Adrenaline stubs)  or `psppower_driver` stubs to be available.
 */
int scePowerSetCpuClockFrequency(int cpu_freq);

/**
 * Set the BUS frequency.
 *
 * @param bus_freq - new BUS frequency, valid values are 1 - 167
 *
 * @return `0` on success, `< 0` on error.
 *
 * @attention Requires linking to `psppower` (PSPSDK), `psppower_user` (Adrenaline stubs)  or `psppower_driver` stubs to be available.
 */
int scePowerSetBusClockFrequency(int bus_freq);

/**
 * Get the CPU Frequency as integer.
 *
 * @return The CPU frequency as integer.
 *
 * @attention Requires linking to `psppower` (PSPSDK), `psppower_user` (Adrenaline stubs)  or `psppower_driver` stubs to be available.
 */
int scePowerGetCpuClockFrequencyInt(void);

/**
 * Get the CPU frequency as float.
 *
 * @return The CPU frequency as float point.
 *
 * @attention Requires linking to `psppower` (PSPSDK), `psppower_user` (Adrenaline stubs)  or `psppower_driver` stubs to be available.
 */
float scePowerGetCpuClockFrequencyFloat(void);

/**
 * Get the BUS frequency as integer.
 *
 * @return The BUS frequency as integer.
 *
 * @attention Requires linking to `psppower` (PSPSDK), `psppower_user` (Adrenaline stubs)  or `psppower_driver` stubs to be available.
 */
int scePowerGetBusClockFrequencyInt(void);

/**
 * Get the BUS frequency as float.
 *
 * @return The BUS frequency as float.
 *
 * @attention Requires linking to `psppower` (PSPSDK), `psppower_user` (Adrenaline stubs)  or `psppower_driver` stubs to be available.
 */
float scePowerGetBusClockFrequencyFloat(void);

/**
 * Set clock frequencies.
 *
 * @param pll_freq The PLL frequency. Valid from `19-333`.
 * @param cpu_freq The CPU frequency, valid from `1-333`.
 * @param bus_freq The BUS frequency, valid from `1-167`.
 *
 * and:
 *
 * cpu_freq <= pll_freq
 * bus_freq*2 <= pll_freq
 *
 * @return `0` on success, `< 0` on error.
 *
 * @attention Requires linking to `psppower` (PSPSDK), `psppower_user` (Adrenaline stubs)  or `psppower_driver` stubs to be available.
 */
int scePowerSetClockFrequency(int pll_freq, int cpu_freq, int busfreq);

/**
 * Lock the power switch.
 *
 * Note: if the power switch is toggled while locked
 * it will fire immediately after being unlocked.
 *
 * @param unk Unknown. Pass `0`.
 *
 * @return `0` on success, `< 0` on error.
 *
 * @attention Requires linking to `psppower` (PSPSDK), `psppower_user` (Adrenaline stubs)  or `psppower_driver` stubs to be available.
 */
int scePowerLock(int unk);

/**
 * Unlock the power switch.
 *
 * @param unk Unknown. Pass `0`.
 *
 * @return `0` on success, `< 0` on error.
 *
 * @attention Requires linking to `psppower` (PSPSDK), `psppower_user` (Adrenaline stubs)  or `psppower_driver` stubs to be available.
 */
int scePowerUnlock(int unk);

/**
 * Generate a power tick, preventing unit from powering off and turning off display.
 *
 * @param type The type of the tick. One of `ScePowerTickFlags`.
 *
 * @return `0` on success, `< 0` on error.
 *
 * @attention Requires linking to `psppower` (PSPSDK), `psppower_user` (Adrenaline stubs)  or `psppower_driver` stubs to be available.
 */
int scePowerTick(int type);

/**
 * Get the power idle timer.
 *
 * @return The idle timer, `< 0` on error.
 *
 * @attention Requires linking to `psppower` (PSPSDK), `psppower_user` (Adrenaline stubs)  or `psppower_driver` stubs to be available.
 */
int scePowerGetIdleTimer(void);

/**
 * Enable the power idle timer.
 *
 * @param unk Unknown. Pass `0`.
 *
 * @return `< 0` on error.
 *
 * @attention Requires linking to `psppower` (PSPSDK), `psppower_user` (Adrenaline stubs)  or `psppower_driver` stubs to be available.
 */
int scePowerIdleTimerEnable(int unk);

/**
 * Disable Idle timer
 *
 * @param unk Unknown. Pass `0`.
 *
 * @return `< 0` on error.
 *
 * @attention Requires linking to `psppower` (PSPSDK), `psppower_user` (Adrenaline stubs)  or `psppower_driver` stubs to be available.
 */
int scePowerIdleTimerDisable(int unk);

/**
 * Request the PSP to go into standby
 *
 * @return `0` always.
 *
 * @attention Requires linking to `psppower` (PSPSDK), `psppower_user` (Adrenaline stubs)  or `psppower_driver` stubs to be available.
 */
int scePowerRequestStandby(void);

/**
 * Request the PSP to go into suspend
 *
 * @return `0` always.
 *
 * @attention Requires linking to `psppower` (PSPSDK), `psppower_user` (Adrenaline stubs)  or `psppower_driver` stubs to be available.
 */
int scePowerRequestSuspend(void);

/**
 * Request the PSP to do a cold reset.
 *
 * @param a0 - Unknown
 *
 * @return `< 0` on error.
 *
 * @attention Requires linking to `psppower` (PSPSDK), `psppower_user` (Adrenaline stubs)  or `psppower_driver` stubs to be available.
 */
int scePowerRequestColdReset(int a0);

#ifdef __USER__
/**
 * Alias for scePowerGetBusClockFrequencyInt.
 *
 * @return The BUS frequency as integer.
 *
 * @attention Requires linking to `psppower` (PSPSDK) or `psppower_user` (Adrenaline stubs) stubs to be available.
 */
int scePowerGetBusClockFrequency(void);

/**
 * Alias for scePowerGetCpuClockFrequencyInt.
 *
 * @return The CPU frequency as integer.
 *
 * @attention Requires linking to `psppower` (PSPSDK) or `psppower_user` (Adrenaline stubs) stubs to be available.
 */
int scePowerGetCpuClockFrequency(void);

#endif // __USER__

#ifdef __KERNEL__

/**
 * Initialize the power module.
 *
 * @return `0` always.
 *
 * @attention Requires linking to `psppower_driver` stub to be available.
 */
int scePowerInit(void);

/**
 * Deinitialize the power module.
 *
 * @return `0` always.
 *
 * @attention Requires linking to `psppower_driver` stub to be available.
 */
int scePowerEnd(void);

/**
 * Set the idle callback.
 *
 * @param slot The slot of the callback in the list (`0` to `8`).
 * @param flags The flags of the callback.
 * @param callback The function pointer to the callback.
 * @param arg Unknown.
 *
 * @return `0` on success, `< 0` on error.
 *
 * @attention Requires linking to `psppower_driver` stub to be available.
 */
int scePowerSetIdleCallback(int slot, int flags, u64 time, int (* callback)(int slot, u32 diff, int arg, int *unk), int arg);

#endif // __KERNEL__


#ifdef __cplusplus
}
#endif

#endif
