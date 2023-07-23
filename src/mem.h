#ifndef _DOTLIBS_MEM
#define _DOTLIBS_MEM

#include "types.h"

#ifdef _WIN32

#include <windows.h>
#include <heapapi.h>

// TODO: see how this works
// static HANDLE __heap = GetProcessHeap();
#define __heap GetProcessHeap()

void* mem_alloc(u64 size) { return HeapAlloc(__heap, 0, size); }
void* mem_alloc0(u64 size) { return HeapAlloc(__heap, HEAP_ZERO_MEMORY, size); }
u64   mem_getsize(void* ptr) { return HeapSize(__heap, 0, ptr); }
void  mem_free(void* ptr) { HeapFree(__heap, 0, ptr); }
void* mem_realloc(void* ptr, u64 newsize) { return HeapReAlloc(__heap, 0, ptr, newsize); }
void* mem_realloc0(void* ptr, u64 newsize) { return HeapReAlloc(__heap, HEAP_ZERO_MEMORY, ptr, newsize); }
void* mem_expand(void* ptr, u64 inc) { return HeapReAlloc(__heap, 0, ptr, mem_getsize(ptr) + inc); }
void* mem_shrink(void* ptr, u64 dec) { return HeapReAlloc(__heap, 0, ptr, mem_getsize(ptr) - dec); }

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

void* mem_alloc(u64 size) {
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
void* mem_alloc0(u64 size) {
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
u64   mem_getsize(void* ptr) {
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
void  mem_free(void* ptr) {
	u64 s = mem_getsize(ptr);
	if (s != -1)
		munmap(mem - 8, s);
}
void* mem_realloc(void* ptr, u64 newsize) {
	u64 s = mem_getsize(ptr);
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
void* mem_realloc0(void* ptr, u64 newsize) {
	void* ret = mem_realloc(ptr, newsize);
	if (ret != nullptr) {
		for (u64 i=0; i < newsize; i++) ret[i] = 0;
	}
	return ret;
}
void* mem_expand(void* ptr, u64 inc) { return mem_realloc(ptr, mem_getsize(ptr) + inc); }
void* mem_shrink(void* ptr, u64 dec) { return mem_realloc(ptr, mem_getsize(ptr) - dec); }

#endif


void* mem_copy(void* src, u64 size) {
	void* ret = (void*)mem_alloc(size);
	for(u64 i=0; i<=size; i++)
		((u8*)ret)[i] = ((u8*)src)[i];

	return ret;
}

void mem_copy_to_buffer(void* src, void* dst, u64 size) {
	for(u64 i=0; i<=size; i++)
		((u8*)dst)[i] = ((u8*)src)[i];
}

void mem_fill(void* ptr, u64 length, u8 filler) {
	for(u64 i=0; i<=length; i++)
		((u8*)ptr)[i] = filler;
}

void mem_shift_to_tail(void* ptr, u64 length, u64 shift) {
	for(u64 start=0; shift <= length; start++, shift++)
		((u8*)ptr)[start] = ((u8*)ptr)[shift];
}

void mem_shift_to_head(void* ptr, u64 length, u64 shift) {
	for(u64 start=length-shift; start; start--, length--)
		((u8*)ptr)[length] = ((u8*)ptr)[start];
}


#ifndef malloc
#define malloc mem_alloc
#endif
#ifndef calloc
#define calloc mem_alloc0
#endif
#ifndef remalloc
#define remalloc mem_realloc
#endif
#ifndef free
#define free mem_free
#endif

// #define pri_alloc    mem_alloc
// #define pri_getsize  mem_getsize
// #define pri_free     mem_free
// #define pri_realloc  mem_realloc
// #define pri_expand   mem_expand
// #define pri_shrink   mem_shrink


// data
// state

#endif
