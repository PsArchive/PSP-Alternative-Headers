/*
 * PSP Software Development Kit - https://github.com/pspdev
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * psprtc.h - Prototypes for the sceRtc and sceRtc_driver libraries.
 *
 * Function returns marked with (?) have not been tested.
 *
 * Copyright (c) 2005 John Kelley <ps2dev@kelley.ca>
 * Copyright (c) 2025 GrayJack
 *
 */
#ifndef __PSPRTC_H__
#define __PSPRTC_H__

#include <time.h>
#include <psptypes.h>


enum SceRtcCheckValidErrors {
	PSP_TIME_INVALID_YEAR = -1,
	PSP_TIME_INVALID_MONTH = -2,
	PSP_TIME_INVALID_DAY = -3,
	PSP_TIME_INVALID_HOUR = -4,
	PSP_TIME_INVALID_MINUTES = -5,
	PSP_TIME_INVALID_SECONDS = -6,
	PSP_TIME_INVALID_MICROSECONDS = -7
};

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

/**
 * Get the resolution of the tick counter.
 *
 * @return The number of ticks per second.
 *
 * @attention Requires linking to `psprtc` (PSPSDK), `psprtc_user` (Adrenaline stubs)  or `psprtc_driver` stubs to be available.
 */
u32 sceRtcGetTickResolution();

/**
 * Get current tick count.
 *
 * @param tick_count A pointer to `u64` to receive the current tick count.
 *
 * @return `0` on success, `< 0` on error.
 *
 * @attention Requires linking to `psprtc` (PSPSDK), `psprtc_user` (Adrenaline stubs)  or `psprtc_driver` stubs to be available.
 */
int sceRtcGetCurrentTick(u64 *tick_count);

/**
 * Get current clock, adjusted for local time zone.
 *
 * @param[out] time A pointer to `ScePspDateTime` struct to receive clock time.
 * @param tz The time zone to adjust to (minutes from UTC).
 *
 * @return `0` on success, `< 0` on error.
 *
 * @attention Requires linking to `psprtc` (PSPSDK), `psprtc_user` (Adrenaline stubs)  or `psprtc_driver` stubs to be available.
 */
int sceRtcGetCurrentClock(ScePspDateTime *time, int tz);

/**
 * Get current local time.
 *
 * @param[out] time A pointer to ScePspDateTime struct to receive time.
 *
 * @return `0` on success, `< 0` on error.
 *
 * @attention Requires linking to `psprtc` (PSPSDK), `psprtc_user` (Adrenaline stubs)  or `psprtc_driver` stubs to be available.
 */
int sceRtcGetCurrentClockLocalTime(ScePspDateTime *time);

/**
 * Convert a UTC-based tick count into a local time tick count.
 *
 * @param[in] utc_tick A pointer to u64 tick in UTC time.
 * @param[out] local_tick A pointer to u64 to receive tick in local time.
 *
 * @return `0` on success, `< 0` on error.
 *
 * @attention Requires linking to `psprtc` (PSPSDK), `psprtc_user` (Adrenaline stubs)  or `psprtc_driver` stubs to be available.
 */
int sceRtcConvertUtcToLocalTime(const u64* utc_tick, u64* local_tick);

/**
 * Convert a local time based tickcount into a UTC-based tick count.
 *
 * @param[in] local_tick A pointer to u64 tick in local time.
 * @param[out] utc_tick A pointer to u64 to receive tick in UTC based time.
 *
 * @return `0` on success, `< 0` on error.
 *
 * @attention Requires linking to `psprtc` (PSPSDK), `psprtc_user` (Adrenaline stubs)  or `psprtc_driver` stubs to be available.
 */
int sceRtcConvertLocalTimeToUTC(const u64* local_tick, u64* utc_tick);

/**
 * Check if a year is a leap year.
 *
 * @param year The year to check if is a leap year.
 *
 * @return `1` on leapyear, `0` if not
 *
 * @attention Requires linking to `psprtc` (PSPSDK), `psprtc_user` (Adrenaline stubs)  or `psprtc_driver` stubs to be available.
 */
int sceRtcIsLeapYear(int year);

/**
 * Get number of days in a specific month.
 *
 * @param year The year in which to check (accounts for leap year).
 * @param month The month to get number of days for.
 *
 * @return The number of days in month, `< 0` on error (?).
 *
 * @attention Requires linking to `psprtc` (PSPSDK), `psprtc_user` (Adrenaline stubs)  or `psprtc_driver` stubs to be available.
 */
int sceRtcGetDaysInMonth(int year, int month);

/**
 * Get day of the week for a date.
 *
 * @param year The year in which to check (accounts for leap year).
 * @param month The month that day is in.
 * @param day The day to get day of week for.
 *
 * @return The day of week with `0` representing Monday.
 *
 * @attention Requires linking to `psprtc` (PSPSDK), `psprtc_user` (Adrenaline stubs)  or `psprtc_driver` stubs to be available.
 */
int sceRtcGetDayOfWeek(int year, int month, int day);

/**
 * Validate the datetime component ranges.
 *
 * @param[in] date A pointer to `ScePspDateTime` struct to be checked.
 *
 * @return `0` on success, one of `SceRtcCheckValidErrors` on error.
 *
 * @attention Requires linking to `psprtc` (PSPSDK), `psprtc_user` (Adrenaline stubs)  or `psprtc_driver` stubs to be available.
 */
int sceRtcCheckValid(const ScePspDateTime* date);

/**
 * Set a `ScePspDateTime` struct based on ticks.
 *
 * @param[out] date A pointer to ScePspDateTime struct to set.
 * @param[in] tick A pointer to ticks to convert.
 *
 * @return `0` on success, `< 0` on error.
 *
 * @attention Requires linking to `psprtc` (PSPSDK), `psprtc_user` (Adrenaline stubs)  or `psprtc_driver` stubs to be available.
 */
int sceRtcSetTick(ScePspDateTime* date, const u64* tick);

/**
 * Set ticks based on a `ScePspDateTime` struct.
 *
 * @param[in] date A pointer to `ScePspDateTime` to convert.
 * @param[out] tick A pointer to tick to set.
 *
 * @return `0` on success, `< 0` on error.
 *
 * @attention Requires linking to `psprtc` (PSPSDK), `psprtc_user` (Adrenaline stubs)  or `psprtc_driver` stubs to be available.
 */
int sceRtcGetTick(const ScePspDateTime* date, u64 *tick);

/**
 * Compare two ticks.
 *
 * @param[in] tick1 A pointer to the first tick.
 * @param[in] tick2 A pinter to the second tick.
 *
 * @return `0` on equal, `< 0` when `tick1 < tick2`, `> 0` when `tick1 > tick2`.
 *
 * @attention Requires linking to `psprtc` (PSPSDK), `psprtc_user` (Adrenaline stubs)  or `psprtc_driver` stubs to be available.
 */
int sceRtcCompareTick(const u64* tick1, const u64* tick2);

/**
 * Add two ticks.
 *
 * @param[out] dest_tick A pointer to tick to hold the result.
 * @param[in] src_tick A pointer to source tick.
 * @param num_ticks The number of ticks to add.
 *
 * @return `0` on success, `< 0` on error.
 *
 * @attention Requires linking to `psprtc` (PSPSDK), `psprtc_user` (Adrenaline stubs)  or `psprtc_driver` stubs to be available.
 */
int sceRtcTickAddTicks(u64* dest_tick, const u64* src_tick, u64 num_ticks);

/**
 * Add an amount of ms to a tick.
 *
 * @param[out] dest_tick A pointer to tick to hold result.
 * @param[in] src_tick A pointer to source tick.
 * @param num_ms The number of ms to add.
 *
 * @return `0` on success, `< 0` on error.
 *
 * @attention Requires linking to `psprtc` (PSPSDK), `psprtc_user` (Adrenaline stubs)  or `psprtc_driver` stubs to be available.
 */
int sceRtcTickAddMicroseconds(u64* dest_tick, const u64* src_tick, u64 num_ms);

/**
 * Add an amount of seconds to a tick.
 *
 * @param[out] dest_tick A pointer to tick to hold result.
 * @param[in] src_tick A pointer to source tick.
 * @param num_secs The number of seconds to add.
 *
 * @return `0` on success, `< 0` on error.
 *
 * @attention Requires linking to `psprtc` (PSPSDK), `psprtc_user` (Adrenaline stubs)  or `psprtc_driver` stubs to be available.
 */
int sceRtcTickAddSeconds(u64* dest_tick, const u64* src_tick, u64 num_secs);

/**
 * Add an amount of minutes to a tick.
 *
 * @param[out] dest_tick A pointer to tick to hold result.
 * @param[in] src_tick A pointer to source tick.
 * @param num_mins The number of minutes to add.
 *
 * @return `0` on success, `< 0` on error.
 *
 * @attention Requires linking to `psprtc` (PSPSDK), `psprtc_user` (Adrenaline stubs)  or `psprtc_driver` stubs to be available.
 */
int sceRtcTickAddMinutes(u64* dest_tick, const u64* src_tick, u64 num_mins);

/**
 * Add an amount of hours to a tick.
 *
 * @param[out] dest_tick A pointer to tick to hold result.
 * @param[in] src_tick A pointer to source tick.
 * @param num_hours The number of hours to add.
 *
 * @return `0` on success, `< 0` on error.
 *
 * @attention Requires linking to `psprtc` (PSPSDK), `psprtc_user` (Adrenaline stubs)  or `psprtc_driver` stubs to be available.
 */
int sceRtcTickAddHours(u64* dest_tick, const u64* src_tick, int num_hours);

/**
 * Add an amount of days to a tick.
 *
 * @param[out] dest_tick A pointer to tick to hold result.
 * @param[in] src_tick A pointer to source tick.
 * @param num_days The number of days to add.
 *
 * @return `0` on success, `< 0` on error.
 *
 * @attention Requires linking to `psprtc` (PSPSDK), `psprtc_user` (Adrenaline stubs)  or `psprtc_driver` stubs to be available.
 */
int sceRtcTickAddDays(u64* dest_tick, const u64* src_tick, int num_days);

/**
 * Add an amount of weeks to a tick.
 *
 * @param[out] dest_tick A pointer to tick to hold result.
 * @param[in] src_tick A pointer to source tick.
 * @param num_weeks The number of weeks to add.
 *
 * @return `0` on success, `< 0` on error.
 *
 * @attention Requires linking to `psprtc` (PSPSDK), `psprtc_user` (Adrenaline stubs)  or `psprtc_driver` stubs to be available.
 */
int sceRtcTickAddWeeks(u64* dest_tick, const u64* src_tick, int num_weeks);


/**
 * Add an amount of months to a tick.
 *
 * @param[out] dest_tick A pointer to tick to hold result.
 * @param[in] src_tick A pointer to source tick.
 * @param num_months - number of months to add.
 *
 * @return `0` on success, `< 0` on error.
 *
 * @attention Requires linking to `psprtc` (PSPSDK), `psprtc_user` (Adrenaline stubs)  or `psprtc_driver` stubs to be available.
 */
int sceRtcTickAddMonths(u64* dest_tick, const u64* src_tick, int num_months);

/**
 * Add an amount of years to a tick.
 *
 * @param[out] dest_tick A pointer to tick to hold result.
 * @param[in] src_tick A pointer to source tick.
 * @param numYears The number of years to add.
 *
 * @return `0` on success, `< 0` on error.
 *
 * @attention Requires linking to `psprtc` (PSPSDK), `psprtc_user` (Adrenaline stubs)  or `psprtc_driver` stubs to be available.
 */
int sceRtcTickAddYears(u64* dest_tick, const u64* src_tick, int numYears);

/** @attention Requires linking to `psprtc` (PSPSDK), `psprtc_user` (Adrenaline stubs)  or `psprtc_driver` stubs to be available. */
int sceRtcSetTime_t(ScePspDateTime* date, const time_t time);
/** @attention Requires linking to `psprtc` (PSPSDK), `psprtc_user` (Adrenaline stubs)  or `psprtc_driver` stubs to be available. */
int sceRtcGetTime_t(const ScePspDateTime* date, time_t *time);
/** @attention Requires linking to `psprtc` (PSPSDK), `psprtc_user` (Adrenaline stubs)  or `psprtc_driver` stubs to be available. */
int sceRtcSetDosTime(ScePspDateTime* date, u32 dosTime);
/** @attention Requires linking to `psprtc` (PSPSDK), `psprtc_user` (Adrenaline stubs)  or `psprtc_driver` stubs to be available. */
int sceRtcGetDosTime(ScePspDateTime* date, u32 dosTime);
/** @attention Requires linking to `psprtc` (PSPSDK), `psprtc_user` (Adrenaline stubs)  or `psprtc_driver` stubs to be available. */
int sceRtcSetWin32FileTime(ScePspDateTime* date, u64* win32Time);
/** @attention Requires linking to `psprtc` (PSPSDK), `psprtc_user` (Adrenaline stubs)  or `psprtc_driver` stubs to be available. */
int sceRtcGetWin32FileTime(ScePspDateTime* date, u64* win32Time);

/** @attention Requires linking to `psprtc` (PSPSDK), `psprtc_user` (Adrenaline stubs)  or `psprtc_driver` stubs to be available. */
int sceRtcParseDateTime(u64 *dest_tick, const char *dateString);

/**
 * Format Tick-representation UTC time in RFC2822 format.
 *
 * @param[out] datetime_fmt A pointer as buffer to receive the representation in RFC2822 format.
 * @param[in] utc_tick A pointer to a UTC tick time.
 * @param timezone_minutes The time zone to adjust to (minutes from UTC).
 *
 * @return `0` on success, `< 0` on error.
 *
 * @attention Requires linking to `psprtc` (PSPSDK), `psprtc_user` (Adrenaline stubs)  or `psprtc_driver` stubs to be available.
 */
int sceRtcFormatRFC2822(char *datetime_fmt, const u64 *utc_tick, int timezone_minutes);

/**
 * Format Tick-representation local time in RFC2822 format.
 *
 * @param[out] datetime_fmt A pointer as buffer to receive the representation in RFC2822 format.
 * @param[in] local_tick A pointer local tick time.
 *
 * @return `0` on success, `< 0` on error.
 *
 * @attention Requires linking to `psprtc` (PSPSDK), `psprtc_user` (Adrenaline stubs)  or `psprtc_driver` stubs to be available.
 */
int sceRtcFormatRFC2822LocalTime(char *datetime_fmt, const u64 *local_tick);

/**
 * Format Tick-representation UTC time in RFC3339(ISO8601) format.
 *
 * @param[out] datetime_fmt A pointer as buffer to receive the representation in RFC3339 format.
 * @param[in] utc_tick A pointer UTC tick time.
 * @param timezone_minutes The time zone to adjust to (minutes from UTC).
 *
 * @return `0` on success, `< 0` on error.
 *
 * @attention Requires linking to `psprtc` (PSPSDK), `psprtc_user` (Adrenaline stubs)  or `psprtc_driver` stubs to be available.
 */
int sceRtcFormatRFC3339(char *datetime_fmt, const u64 *utc_tick, int timezone_minutes);

/**
 * Format Tick-representation local time in RFC3339(ISO8601) format.
 *
 * @param[out] datetime_fmt A pointer as buffer to receive the representation in RFC3339 format.
 * @param[in] local_tick A pointer local tick time.
 *
 * @return `0` on success, `< 0` on error.
 *
 * @attention Requires linking to `psprtc` (PSPSDK), `psprtc_user` (Adrenaline stubs)  or `psprtc_driver` stubs to be available.
 */
int sceRtcFormatRFC3339LocalTime(char *datetime_fmt, const u64 *local_tick);

/**
 * Parse time information represented in RFC3339 format.
 *
 * @param[out] tick A pointer to hold the tick time.
 * @param[in] datetime_fmt A pointer as buffer as input to the representation in RFC3339 format.
 *
 * @return `0` on success, `< 0` on error.
 *
 * @attention Requires linking to `psprtc` (PSPSDK), `psprtc_user` (Adrenaline stubs)  or `psprtc_driver` stubs to be available.
 */
int sceRtcParseRFC3339(u64 *tick, const char *datetime_fmt);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif
