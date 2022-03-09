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


void c8_disasm_op(u8 *code_buf, int pc)
{
	u8 *code = &code_buf[pc];
	u8 first_nib = (code[0] >> 4); //because we only want the first 4 bits out of the 8 of the first byte
	printf("%04x %02x %02x", pc, code[0], code[1]);
	
	switch(first_nib)
	{
		case 0x00: printf("0 not handled yet!");break;
		case 0x01: printf("1 not handled yet!");break;
		case 0x02: printf("2 not handled yet!");break;
		case 0x03: printf("3 not handled yet!");break;
		case 0x04: printf("4 not handled yet!");break;
		case 0x05: printf("5 not handled yet!");break;
		case 0x06:
		{
			u8 reg = code[0] & 0x0F;
			printf("%-10s V%01X,#$%02x", "MVI", reg, code[1]);
		}break;
		case 0x07: printf("7 not handled yet!");break;
		case 0x08: printf("8 not handled yet!");break;
		case 0x09: printf("9 not handled yet!");break;
		case 0x0a:
		{
			u8 addrhi = code[0] & 0x0F;
             printf("%-10s I,#$%01x%02x", "MVI", addrhi, code[1]);    
		}break;
		case 0x0b: printf("b not handled yet!");break;
		case 0x0c: printf("c not handled yet!");break;
		case 0x0d: printf("d not handled yet!");break;
		case 0x0e: printf("e not handled yet!");break;
		case 0x0f: printf("f not handled yet!");break;
	}
}


void parse_rom(char *filename)
{
	FILE *f = fopen(filename, "rb");
	if (f == NULL)
	{
		printf("C8 ERROR: Couldn't open rom %s!\n", filename);
		exit(1);
	}
	fseek(f, 0L, SEEK_END);
	int fsize = ftell(f);
	fseek(f, 0L, SEEK_SET);
	
	int pc = 0x200;
	//CHIP-8 puts programs at 0x200
	u8 *buffer = malloc(fsize + 0x200);
	fread(buffer + 0x200, fsize, 1, f);
	fclose(f);
	while (pc < (fsize + 0x200))
	{
		c8_disasm_op(buffer, pc);
		pc +=2;
		printf("\n");
	}
}

#endif