#ifndef __C8__
#define __C8__


#if defined(_WIN32) || defined(__CYGWIN__)
#define BUILD_WIN
#elif defined(MACOSX)
#define BUILD_MACOSX
#else
#define BUILD_UNIX
#endif


#if defined(BUILD_WIN)
#include "windows.h"
#endif


//these are universal includes supported by all platforms
#include <stdint.h>
#include <time.h>
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stddef.h>

typedef uint8_t   u8;
typedef int8_t    s8;
typedef uint16_t  u16;
typedef int16_t   s16;
typedef uint32_t  u32;
typedef int32_t   s32;
typedef uint64_t  u64;
typedef int64_t   s64;
typedef float     f32;
typedef double    f64;
typedef int32_t   b32;
typedef char      b8;



#define INLINE static inline

#if !defined(TRUE)
#define TRUE 1
#endif
#if !defined(FALSE)
#define FALSE 0
#endif
#if !defined(FLT_MAX)
#define FLT_MAX 32767.F
#endif
#if !defined(NULL)
#define NULL 0
#endif


#define kilobytes(val) ((val)*1024LL)
#define megabytes(val) ((kilobytes(val))*1024LL)
#define gigabytes(val) ((megabytes(val))*1024LL)
#define terabytes(val) ((gigabytes(val))*1024LL)

#define PI 3.1415926535897f


#define align_pow2(val, align) (((val) + ((align) - 1)) & ~(((val) - (val)) + (align) - 1))
#define align4(val) (((val) + 3) & ~3)
#define align8(val) (((val) + 7) & ~7)
#define align16(val) (((val) + 15) & ~15)

#define equalf(a, b, epsilon) (fabs(b - a) <= epsilon)
#define maximum(a, b) ((a) > (b) ? (a) : (b))
#define minimum(a, b) ((a) < (b) ? (a) : (b))
#define step(threshold, value) ((value) < (threshold) ? 0 : 1) 
#define clamp(x, a, b)  (maximum(a, minimum(x, b)))
#define array_count(a) (sizeof(a) / sizeof((a)[0]))




INLINE b32 is_pow2(u32 val)
{
    b32 res = ((val & ~(val - 1)) == val);
    return(res);
}
static b32
char_is_alpha(s32 c)
{
    return ((c >='A' && c <= 'Z') || (c >= 'a' && c <= 'z'));
}
static b32 char_is_digit(s32 c)
{
    return c >= '0'&& c <= '9';
}

static s32 char_to_lower(s32 c)
{
    if (c >= 'A' && c <= 'z')
    {
        c += 32;
    }
    return c;
}

static u32 
str_size(char* str)
{
    u32 i = 0;
    while (str[i] != 0)++i;
    return i;
}


#endif