#ifndef _DOTLIBS_FIND
#define _DOTLIBS_FIND

#include "types.h"
#include "str.h"


uint find_str(cc* strings, cc target, uint size) {
	for (uint i=0; i < size; i++) {
		if (str_equal(strings[i], target)) return i;
	}
	return -1;
}
uint rfind_str(cc* strings, cc target, uint size) {
	for (; size != -1; size--) {
		if (str_equal(strings[size], target)) return size;
	}
	return -1;
}

uint bfind_str(cc* strings, cc target, uint size) {
	int low  = 0;
	int high = size - 1;
	while (low <= high) {
		int mid = (low + high) / 2;
		int m = str_compare(strings[mid], target);
		if (m == 0) {
			return mid;
		} else if (m < 0) {
			low = mid + 1;
		} else {
			high = mid - 1;
		}
	}
	return -1; 
}

uint find_s64(const s64* array, s64 target, uint size) {
	for (uint i=0; i < size; i++) {
		if (array[i] == target) return i;
	}
	return -1;
}
uint rfind_s64(const s64* array, s64 target, uint size) {
	for (; size != -1; size--) {
		if (array[size] == target) return size;
	}
	return -1;
}
uint bfind_s64(const s64* array, s64 target, uint size) {
	int low  = 0;
	int high = size - 1;
	while (low <= high) {
		int mid = (low + high) / 2;
		int m = array[mid] - target;
		if (m == 0) {
			return mid;
		} else if (m < 0) {
			low = mid + 1;
		} else {
			high = mid - 1;
		}
	}
	return -1;
}

uint find_u64(const u64* array, u64 target, uint size) {
	for (uint i=0; i < size; i++) {
		if (array[i] == target) return i;
	}
	return -1;
}
uint rfind_u64(const u64* array, u64 target, uint size) {
	for (; size != -1; size--) {
		if (array[size] == target) return size;
	}
	return -1;
}
uint bfind_u64(const u64* array, u64 target, uint size) {
	int low  = 0;
	int high = size - 1;
	while (low <= high) {
		int mid = (low + high) / 2;
		int m = array[mid] - target;
		if (m == 0) {
			return mid;
		} else if (m < 0) {
			low = mid + 1;
		} else {
			high = mid - 1;
		}
	}
	return -1;
}

uint find_f64(const f64* array, f64 target, uint size) {
	for (uint i=0; i < size; i++) {
		if (array[i] == target) return i;
	}
	return -1;
}
uint rfind_f64(const f64* array, f64 target, uint size) {
	for (; size != -1; size--) {
		if (array[size] == target) return size;
	}
	return -1;
}

uint bfind_f64(const f64* array, f64 target, uint size) {
	int low  = 0;
	int high = size - 1;
	while (low <= high) {
		int mid = (low + high) / 2;
		int m = array[mid] - target;
		if (m == 0) {
			return mid;
		} else if (m < 0) {
			low = mid + 1;
		} else {
			high = mid - 1;
		}
	}
	return -1;
}




uint find_any_cmp(const void** array, void* target, uint size,
	int(*cmp_func)(void*, void*)) {
	for (uint i=0; i < size; i++) {
		if (cmp_func((void*)array[i], target) == 0) return i;
	}
	return -1;
}
uint find_any_equ(const void** array, void* target, uint size,
	bool(*equ_func)(void*, void*)) {
	for (uint i=0; i < size; i++) {
		if (equ_func((void*)array[i], target)) return i;
	}
	return -1;
}

uint rfind_any_cmp(const void** array, void* target, uint size,
	int(*cmp_func)(void*, void*)) {
	for (; size != -1; size--) {
		if (cmp_func((void*)array[size], target) == 0) return size;
	}
	return -1;
}
uint rfind_any_equ(const void** array, void* target, uint size,
	bool(*equ_func)(void*, void*)) {
	for (; size != -1; size--) {
		if (equ_func((void*)array[size], target)) return size;
	}
	return -1;
}

uint bfind_any_cmp(const void** array, void* target, uint size,
	int(*cmp_func)(void*, void*)) {
	int low  = 0;
	int high = size - 1;
	while (low <= high) {
		int mid = (low + high) / 2;
		int m = cmp_func((void*)array[mid], target);
		if (m == 0) {
			return mid;
		} else if (m < 0) {
			low = mid + 1;
		} else {
			high = mid - 1;
		}
	}
	return -1;
}

uint bfind_any_equinf(const void** array, void* target, uint size,
	bool(*equ_func)(void*, void*), bool(*inf_func)(void*, void*)) {
	int low  = 0;
	int high = size - 1;
	while (low <= high) {
		int mid = (low + high) / 2;
		if (equ_func((void*)array[mid], target)) {
			return mid;
		} else if (inf_func((void*)array[mid], target)) {
			low = mid + 1;
		} else {
			high = mid - 1;
		}
	}
	return -1;
}

uint bfind_any_equsup(const void** array, void* target, uint size,
	bool(*equ_func)(void*, void*), bool(*sup_func)(void*, void*)) {
	int low  = 0;
	int high = size - 1;
	while (low <= high) {
		int mid = (low + high) / 2;
		if (equ_func((void*)array[mid], target)) {
			return mid;
		} else if (sup_func((void*)array[mid], target)) {
			low = mid - 1;
		} else {
			high = mid + 1;
		}
	}
	return -1;
}

#define any_cmp_t int(*)(void*,void*)
#define any_equ_t bool(*)(void*,void*)

#endif