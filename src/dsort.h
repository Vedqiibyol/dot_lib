#ifndef _DOTLIBS_SORT
#define _DOTLIBS_SORT

#include "types.h"
#include "str.h"

uint dsort_str(char** array, uint size);
uint dsort_s64(s64* array, uint size);
uint dsort_u64(u64* array, uint size);
uint dsort_f64(f64* array, uint size);

uint rdsort_str(char** array, uint size);
uint rdsort_s64(s64* array, uint size);
uint rdsort_u64(u64* array, uint size);
uint rdsort_f64(f64* array, uint size);

uint dsort_any_cmp(void** array, uint size, int(*cmp_func)(void*, void*));
uint dsort_any_equinf(void** array, uint size,
	bool(*equ_func)(void*, void*), bool(*inf_func)(void*, void*));
uint dsort_any_equsup(void** array, uint size, int(*cmp_func)(void*, void*),
	bool(*equ_func)(void*, void*), bool(*sup_func)(void*, void*));

uint rdsort_any_cmp(void** array, uint size, int(*cmp_func)(void*, void*));
uint rdsort_any_equinf(void** array, uint size,
	bool(*equ_func)(void*, void*), bool(*inf_func)(void*, void*));
uint rdsort_any_equsup(void** array, uint size, int(*cmp_func)(void*, void*),
	bool(*equ_func)(void*, void*), bool(*sup_func)(void*, void*));

#endif
