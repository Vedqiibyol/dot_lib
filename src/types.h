#ifndef _DOTLIBS_TYPES
#define _DOTLIBS_TYPES

typedef unsigned int uint;
typedef signed long long rel;
typedef unsigned long long urel;

typedef signed char s8;
typedef signed short s16;
typedef signed long s32;
typedef signed long long s64;


typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long u32;
typedef unsigned long long u64;

	// #ifdef DOTLIBS_WITH_128BITS_INTS
	#ifndef DOTLIBS_WITHOUT_128BITS_INTS
	typedef __int128 s128;
	typedef unsigned __int128 u128;
	#endif

typedef float f32;
typedef double f64;
typedef long double f128;

typedef const char* cc;
typedef const void* _vp;
typedef const void** _vpp;

#ifndef __cplusplus
	typedef enum bool {
		false,
		true
	} bool;
	#define nullptr (void*)0
#endif

#endif


