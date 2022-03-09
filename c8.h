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
	printf("%04x %02x %02x ", pc, code[0], code[1]);
	
	switch(first_nib)
	{
		case 0x00: 
			switch(code[1])
			{
				case 0xe0: printf("%-10s", "CLS"); break;
				case 0xee: printf("%-10s", "RTS"); break;
				default: printf("UKNOWN 0");break;

			}break;
		case 0x01: printf("%-10s $%01x%02x", "JUMP", code[0]&0xf, code[1]); break;
		case 0x02: printf("%-10s $%01x%02x", "CALL", code[0]&0xf, code[1]); break;
		case 0x03: printf("%-10s V%01x,#$%02x", "SKIP.EQ", code[0]&0xf, code[1]); break;
		case 0x04: printf("%-10s V%01x,#$%02x", "SKIP.NE", code[0]&0xf, code[1]); break;
		case 0x05: printf("%-10s V%01x,V%01x", "SKIP.EQ", code[0]&0xf, code[1] >> 4); break;
		case 0x06: printf("%-10s V%01x,#$%02x", "MVI", code[0]&0xf, code[1]); break;
		case 0x07: printf("%-10s V%01x,#$%02x", "ADDI", code[0]&0xf, code[1]); break;
		case 0x08: 
		{
			u8 lastnib = code[1] >> 4;
			switch (lastnib)
			{
				case 0: printf("%-10s V%01x,V%01x", "MOV.", code[0]&0xf, code[1] >> 4);break;
				case 1: printf("%-10s V%01x,V%01x", "OR.", code[0]&0xf, code[1] >> 4);break;
				case 2: printf("%-10s V%01x,V%01x", "AND.", code[0]&0xf, code[1] >> 4);break;
				case 3: printf("%-10s V%01x,V%01x", "XOR.", code[0]&0xf, code[1] >> 4);break;
				case 4: printf("%-10s V%01x,V%01x", "ADD.", code[0]&0xf, code[1] >> 4);break;
				case 5: printf("%-10s V%01x,V%01x,V%01x", "SUB.", code[0]&0xf,code[0]&0xf, code[1] >> 4);break;
				case 6: printf("%-10s V%01x,V%01x", "SHR.", code[0]&0xf, code[1] >> 4);break;
				case 7: printf("%-10s V%01x,V%01x,V%01x", "SUB.", code[0]&0xf,code[1]>>4, code[1] >> 4);break;
				case 0xe: printf("%-10s V%01x,V%01x", "SHL.", code[0]&0xf, code[1] >> 4);break;
				default: printf("UKNOWN 8");break;
			}
		}
		case 0x9: printf("%-10s V%01x,V%01x", "SKIP.NE", code[0]&0xf, code[1] >> 4);break;
		case 0xa: printf("%-10s I,#$%01x%02x", "MVI", code[0]&0xf, code[1]);break;
		case 0xb: printf("%-10s $%01x%02x(V0)", "JUMP", code[0]&0xf, code[1]);break;
		case 0xc: printf("%-10s V%01x,#$%02x", "RNDMSK", code[0]&0xf, code[1]);break;
		case 0xd: printf("%-10s V%01x,V%01x,#$%01x", "SPRITE", code[0]&0xf, code[1]>>4, code[1]&0xf);break;
		case 0xe:
			switch(code[1])
			{
				case 0x9E: printf("%-10s V%01x", "SKIPKEY.Y", code[0]&0xf);break;
				case 0xA1: printf("%-10s V%01x", "SKIPKEY.N", code[0]&0xf);break;
				default: printf("UKNOWN E");break;
			}break;
		case 0xf:
			switch(code[1])
			{
				case 0x07: printf("%-10s V%01x,DELAY", "MOV", code[0]&0xf);break;
				case 0x0a: printf("%-10s V%01x", "KEY", code[0]&0xf);break;
				case 0x15: printf("%-10s DELAY,V%01x", "MOV", code[0]&0xf);break;
				case 0x18: printf("%-10s SOUND,V%01x", "MOV", code[0]&0xf);break;
				case 0x1e: printf("%-10s I,V%01x", "ADI", code[0]&0xf);break;
				case 0x29: printf("%-10s I,V%01x", "SPRITECHAR", code[0]&0xf);break;
				case 0x33: printf("%-10s (I),V%01x", "MOVBCD", code[0]&0xf);break;
				case 0x55: printf("%-10s (I),V0-V%01x", "MOVM", code[0]&0xf);break;
				case 0x65: printf("%-10s V0-V%01x,(I)", "MOVM", code[0]&0xf);break;
				default: printf("UKNOWN F");break;

			}break;
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
		pc +=2; //2 chars per instruction
		printf("\n");
	}
}


typedef struct C8State
{
	u8 V[16]; //16 8-bit registers
	u16 I; //memory address register
	u16 SP; //stack pointer?
	u16 PC; //program counter
	u8 delay; //timer for delay
	u8 sound; //timer for sound
	u8 *mem; //RAM
	u8 *screen; //this is mem[0xF00] 
}C8State;

static C8State c8state;

void c8_init(void)
{
	memset(&c8state, 0, sizeof(c8state));
	c8state.mem = calloc(1024*4, 1);
	c8state.screen = &c8state.mem[0xF00];
	c8state.SP = 0xFA0;
	c8state.PC = 0x200;
}

#endif