#ifndef VG_SATURN_COMPAT_H
#define VG_SATURN_COMPAT_H

#include <ctype.h>
#include <stdarg.h>
#include <stdio.h>

#ifdef SATURN
#define VG_LOW_RAM_BSS __attribute__((section(".lowram_bss"), aligned(16)))
#else
#define VG_LOW_RAM_BSS
#endif

#ifdef __cplusplus
extern "C" {
#endif

#ifndef VG_SATURN_TIMESPEC_DEFINED
#define VG_SATURN_TIMESPEC_DEFINED
struct timespec {
    long tv_sec;
    long tv_nsec;
};
#endif

int fscanf(FILE *file, const char *format, ...);

double sin(double value);
double cos(double value);
float sinf(float value);
float cosf(float value);
double atan2(double y, double x);
double sqrt(double value);
double fabs(double value);
float logf(float value);

#ifdef __cplusplus
}
#endif

#endif
