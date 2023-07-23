#ifndef _DOTLIBS_MEM
#define _DOTLIBS_MEM

#if defined (__kohr_compatibility)
#define mem(n) n
#else
#define mem(n) mem_ ## n
#endif


#include "types.h"

#ifdef _WIN32

#include <windows.h>
#include <heapapi.h>

// TODO: see how this works
// static HANDLE __heap = GetProcessHeap();
#define __heap GetProcessHeap()

void* mem(alloc)(u64 size) { return HeapAlloc(__heap, 0, size); }
void* mem(alloc0)(u64 size) { return HeapAlloc(__heap, HEAP_ZERO_MEMORY, size); }
u64   mem(getsize)(void* ptr) { return HeapSize(__heap, 0, ptr); }
void  mem(free)(void* ptr) { HeapFree(__heap, 0, ptr); }
void* mem(realloc)(void* ptr, u64 newsize) { return HeapReAlloc(__heap, 0, ptr, newsize); }
void* mem(realloc0)(void* ptr, u64 newsize) { return HeapReAlloc(__heap, HEAP_ZERO_MEMORY, ptr, newsize); }
void* mem(expand)(void* ptr, u64 inc) { return HeapReAlloc(__heap, 0, ptr, mem_getsize(ptr) + inc); }
void* mem(shrink)(void* ptr, u64 dec) { return HeapReAlloc(__heap, 0, ptr, mem_getsize(ptr) - dec); }

// void* pub_alloc(u64 size) { return HeapAlloc(__heap, 0, size); }
// u64   pub_getsize(void* ptr) { return HeapSize(__heap, 0, ptr); }
// void  pub_free(void* ptr) { HeapFree(__heap, 0, ptr); }
// void* pub_realloc(void* ptr, u64 newsize) { return HeapReAlloc(__heap, 0, ptr, newsize); }
// void* pub_expand(void* ptr, u64 inc) { return HeapReAlloc(__heap, 0, ptr, mem_getsize(ptr) + inc); }
// void* pub_shrink(void* ptr, u64 dec) { return HeapReAlloc(__heap, 0, ptr, mem_getsize(ptr) - dec); }

// void* exec_alloc(u64 size) { return HeapAlloc(__heap, 0, size); }
// u64   exec_getsize(void* ptr) { return HeapSize(__heap, 0, ptr); }
// void  exec_free(void* ptr) { HeapFree(__heap, 0, ptr); }
// void* exec_realloc(void* ptr, u64 newsize) { return HeapReAlloc(__heap, 0, ptr, newsize); }
// void* exec_expand(void* ptr, u64 inc) { return HeapReAlloc(__heap, 0, ptr, mem_getsize(ptr) + inc); }
// void* exec_shrink(void* ptr, u64 dec) { return HeapReAlloc(__heap, 0, ptr, mem_getsize(ptr) - dec); }

// void* vir_alloc(u64 size) { return HeapAlloc(__heap, 0, size); }
// u64   vir_getsize(void* ptr) { return HeapSize(__heap, 0, ptr); }
// void  vir_free(void* ptr) { HeapFree(__heap, 0, ptr); }
// void* vir_realloc(void* ptr, u64 newsize) { return HeapReAlloc(__heap, 0, ptr, newsize); }
// void* vir_expand(void* ptr, u64 inc) { return HeapReAlloc(__heap, 0, ptr, mem_getsize(ptr) + inc); }
// void* vir_shrink(void* ptr, u64 dec) { return HeapReAlloc(__heap, 0, ptr, mem_getsize(ptr) - dec); }

#else // __unix__

#include <sys/mman.h>

void* mem(alloc)(u64 size) {
	void* ptr = (void*)mmap(0, size+8, PROT_READ | PROT_WRITE,
		MAP_ANONYMOUS | MAP_PRIVATE | MAP_UNINITIALIZED, -1, 0);

	if(ptr) {
		u8*  p =  (u8*)ptr;
		u64* s = (u64*)ptr;
		s[0]   =       size;

		mlock(ptr, 1);

		return p + 8;
	}

	return nullptr;

	// Tunrs out, doing something like `p - 1` is actually p minus sizeof(type(p)).
	// Not **1** byte, like any normal being would think of that.
	// Thanks Clang, thanks GCC.
	// *We love it!*
}
void* mem(alloc0)(u64 size) {
	void* ptr = (void*)mmap(0, size+8, PROT_READ | PROT_WRITE,
		MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);

	if(ptr) {
		u8*  p =  (u8*)ptr;
		u64* s = (u64*)ptr;
		s[0]   =       size;

		mlock(ptr, 1);

		return p + 8;
	}

	return nullptr;

	// Tunrs out, doing something like `p - 1` is actually p minus sizeof(type(p)).
	// Not **1** byte, like any normal being would think of that.
	// Thanks Clang, thanks GCC.
	// *We love it!*
}
u64   mem(getsize)(void* ptr) {
	u8*  p  =  (u8*)ptr;
	     p -=       8;
	u64* s  = (u64*)p;

	if(munlock(p, 1) == -1) {
		return -1;
	} else if(mem != nullptr) {
		return s[0];
	}

	// return false;
}
void  mem(free)(void* ptr) {
	u64 s = mem(getsize)(ptr);
	if (s != -1)
		munmap(mem - 8, s);
}
void* mem(realloc)(void* ptr, u64 newsize) {
	u64 s = mem(getsize)(ptr);
	if (s != -1) {
		// u64* pp = (u64*)mremap(mem.realptr, mem.realsize, size+9, MREMAP_MAYMOVE);
		u64* pp = (u64*)mremap(ptr-8, s+8, newsize +8, MREMAP_MAYMOVE);

		u8*  p =  (u8*)pp;
		u64* s = (u64*)pp;
		s[8]   =       size;

		mlock(ptr, 1);

		return p + 8;
	}

	return nullptr;
}
void* mem(realloc0)(void* ptr, u64 newsize) {
	void* ret = mem(realloc)(ptr, newsize);
	if (ret != nullptr) {
		for (u64 i=0; i < newsize; i++) ret[i] = 0;
	}
	return ret;
}
void* mem(expand)(void* ptr, u64 inc) { return mem(realloc)(ptr, mem(getsize)(ptr) + inc); }
void* mem(shrink)(void* ptr, u64 dec) { return mem(realloc)(ptr, mem(getsize)(ptr) - dec); }

#endif


void* mem(copy)(void* src, u64 size) {
	void* ret = (void*)mem(alloc)(size);
	for(u64 i=0; i<=size; i++)
		((u8*)ret)[i] = ((u8*)src)[i];

	return ret;
}

void mem(copy_to_buffer)(void* src, void* dst, u64 size) {
	for(u64 i=0; i<=size; i++)
		((u8*)dst)[i] = ((u8*)src)[i];
}

void mem(fill)(void* ptr, u64 length, u8 filler) {
	for(u64 i=0; i<=length; i++)
		((u8*)ptr)[i] = filler;
}

void mem(shift_to_tail)(void* ptr, u64 length, u64 shift) {
	for(u64 start=0; shift <= length; start++, shift++)
		((u8*)ptr)[start] = ((u8*)ptr)[shift];
}

void mem(shift_to_head)(void* ptr, u64 length, u64 shift) {
	for(u64 start=length-shift; start; start--, length--)
		((u8*)ptr)[length] = ((u8*)ptr)[start];
}


#ifndef malloc
#define malloc mem(alloc)
#endif
#ifndef calloc
#define calloc mem(alloc0)
#endif
#ifndef remalloc
#define remalloc mem(realloc)
#endif
#ifndef free
#define free mem(free)
#endif

// #define pri_alloc    mem(alloc)
// #define pri_getsize  mem(getsize)
// #define pri_free     mem(free)
// #define pri_realloc  mem(realloc)
// #define pri_expand   mem(expand)
// #define pri_shrink   mem(shrink)


// data
// state

#endif
