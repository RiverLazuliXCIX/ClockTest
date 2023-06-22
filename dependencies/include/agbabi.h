/*
===============================================================================

 C header file for agbabi

 Copyright (C) 2021-2023 agbabi contributors
 For conditions of distribution and use, see copyright notice in LICENSE.md

===============================================================================
*/

#ifndef AGBABI_H
#define AGBABI_H
#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>

/**
 * Initialize GPIO pins for RTC
 * @return 0 for success
 */
int __agbabi_rtc_init(void);

/**
 * Get the current, raw time from the RTC
 * @return Raw time in BCD
 */
unsigned int __agbabi_rtc_time(void);

/**
 * Set the Hour, Minute, Second
 * @param time raw BCD (second, minute, hour)
 */
void __agbabi_rtc_settime(unsigned int time);

/**
 * [raw time in BCD, raw date in BCD]
 */
typedef unsigned int __attribute__((vector_size(sizeof(unsigned int) * 2))) __agbabi_datetime_t;

/**
 * Get the current, raw date & time from the RTC
 * @return [raw time in BCD, raw date in BCD]
 */
__agbabi_datetime_t __agbabi_rtc_datetime(void);

/**
 * Set the time and date
 * @param datetime [raw BCD time, raw BCD date]
 */
void __agbabi_rtc_setdatetime(__agbabi_datetime_t datetime);

#ifdef __cplusplus
}
#endif
#endif /* define AGBABI_H */
