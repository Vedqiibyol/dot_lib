#ifndef _DOTLIBS_STR
#define _DOTLIBS_STR

#include "types.h"
#include "mem.h"

#ifndef ALLOCATOR
#define ALLOCATOR mem_alloc
#endif
#ifndef FREEER
#define FREEER mem_free
#endif

u64 str_length(cc str) {
	char* p = (char*)str;
	while(*p) p++;
	return p - str;
}

char* str_copy(cc src) {
	char* dest = (char*)ALLOCATOR(str_length(src));
	uint i = 0;
	for(; src[i]; i++)
		dest[i] = src[i];
	dest[i] = 0;
	i++;
	return dest;
}

u64 str_copy_to_buffer(cc string, char* buffer, u64 size) {
	uint i = 0;
	for (; i < size && string[i]; i++) {
		buffer[i] = string[i];
	}
	return i;
}

bool str_equal(cc str1, cc str2) {
	for (; *str1 == *str2; str1++, str2++) {
		if (!*str1)
			return true;
	}

	return false;
}
bool str_inferior(cc str1, cc str2) {
	for (; ; str1++, str2++) { // // *str1 && *str2
		if (!*str1 && !*str2) return false;
		if (*str1 == *str2) continue;
		return (*str1 < *str2);
	}
	return false;
}
bool str_superior(cc str1, cc str2) {
	bool ret = false;
	for (; *str1 == *str2; str1++, str2++) { // // *str1 && *str2
		if (!*str1 && !*str2) return false;
		ret = *str1 > *str2;
	}
	return ret;
}

int str_compare(cc str1, cc str2) {
	int ret = 0;
	for (; *str1 && !ret; str1++, str2++) { //  && str2[i]
		ret = *str1 - *str2;
	}
	return ret;
}

uint char_is_in(char ch, cc str) {
	for (uint i=0; str[i]; i++)
		if (str[i] == ch) return i;
	return -1;
}

// uint str_upper(char* string);
// uint str_lower(char* string);

uint str_find(cc string, cc target) {
	for(uint i=0; string[i]; i++) {
		uint j=0;
		for (; target[j] && string[i]; j++, i++) {
			if (string[i] != target[j]) break;
		} if (!target[j]) return i-j;
	}
	return -1;
}
uint str_rfind(cc string, cc target) {
	char* p1 = (char*)string; char* p2 = (char*)target;
	while (*p1) p1++; while (*p2) p2++;
	p1--; p2 -= (u64)target+1;

	for(; string <= p1; p1--) {
		uint j = (u64)p2;
		for (; j && *p1; j--, p1--) {
			if (*p1 != target[j]) break;
		} if (!j) return p1 - string;
	}
	return -1;
}

bool str_starts_with(cc string, cc target) {
	for(; *target; string++, target++)
		if (!*string || *string != *target) return false;
	return true;
}

bool str_ends_with(cc string, cc target) {
	char* p1 = (char*)string; char* p2 = (char*)target;
	while (*p1) p1++; while (*p2) p2++;

	for(; target < p2; p1--, p2--)
		if (string >= p1 || *p1 != *p2) return false;
	return true;
}

uint str_count(cc string, cc target) {
	uint c = 0;
	for(; *string; string++)
		if (str_starts_with(string, target)) c++;
	return c;
}

uint s64_to_string(s64 value, char* buffer, uint buflen, uint base,
	char minus_sign, char plus_sign, char guide_char, uint guide_freq) {
	bool neg = (value < 0); if (neg) value = -value;
	s64 a = value; uint c = 0; uint len = 0;
	do len++; while (a /= base);
	len += (guide_char && guide_freq) ? (len-1) / guide_freq : 0;
	len += (neg) ? !!minus_sign : !!plus_sign;

	buffer[len] = '\0'; len--; a = 0;

	do {
		if (guide_char && guide_freq && c && !(c % guide_freq)) {
			buffer[len] = guide_char; len--; a++;
		}

		if(value % base > 9)
			buffer[len] = value % base + 'a' - 10;
		else buffer[len] = value % base + '0';
		len--; c++;
	} while((value /= base) && a++ < buflen);

	if(neg) { if (minus_sign) buffer[len] = minus_sign; }
	else { if (plus_sign) buffer[len] = plus_sign; }

	return a;
}
uint u64_to_string(u64 value, char* buffer, uint buflen, uint base,
	char guide_char, uint guide_freq) {
	u64 a = value; uint c = 0; uint len = 0;
	do len++; while (a /= base);
	len += (guide_char && guide_freq) ? (len-1) / guide_freq : 0;

	buffer[len] = '\0'; len--; a = 0;

	do {
		if (guide_char && guide_freq && c && !(c % guide_freq)) {
			buffer[len] = guide_char; len--; a++; 
		}

		if(value % base > 9)
			buffer[len] = value % base + 'a' - 10;
		else buffer[len] = value % base + '0';
		len--; c++;
	} while((value /= base) && a++ < buflen);

	return a;
}
uint f64_to_string(f64 value, char* buffer, uint buflen, uint base, 
	char minus_sign, char plus_sign, char separator, char guide_char, uint guide_freq) {
	bool neg = (value < 0); if (neg) value = -value;
	f64 _ = value; uint c = 0; uint len = 0; uint a = 0; uint p = 0;

	while(_ - (u64)_ > 0.000000000000000000000000001) { _ *= base; p++; }
	u64 ival = _; u64 _val = ival;

	do { buffer[len] = '0'; len++; } while ((_val /= base));
	len += (guide_char && guide_freq) ? (len-1) / guide_freq : 0;
	len += (neg) ? !!minus_sign : !!plus_sign;
	// len += !!separator;
	len += separator != 0;

	buffer[len] = '\0'; len--;

	do {
		if (!p && separator) {
			buffer[len] = separator; len--; p--; a++; c = 0;
			continue;
		} else if (guide_char && guide_freq && c && !(c % guide_freq)) {
			buffer[len] = guide_char; len--; a++;
		}

		if (ival % base > 9)
			buffer[len] = ival % base + 'a' - 10;
		else buffer[len] = ival % base + '0';
		len--; c++; p--;
		ival /= base;
	} while(a++ < buflen && len != -1);

	if(neg) { if (minus_sign) buffer[len] = minus_sign; }
	else { if (plus_sign) buffer[len] = plus_sign; }

	return a;
}


s64 str_to_s64(cc string, uint base, char minus_sign) {
	uint len = str_length(string);
	s64 value = 0;
	s64 m = 1;

	uint p = 1;
	for(; len != -1; len--) {
		if (string[len] >= '0' && string[len] <= '9') {
			value += p * (string[len] - '0');
			p *= base; m = 1;
		} else if (string[len] >= 'A' && string[len] <= 'Z') {
			value += p * (string[len] - 'A' + 10);
			p *= base; m = 1;
		} else if (string[len] >= 'a' && string[len] <= 'z') {
			value += p * (string[len] - 'a' + 10);
			p *= base; m = 1;
		}

		if(string[len] == minus_sign) m = -1;
	}

	return value * m;
}
u64 str_to_u64(cc string, uint base) {
	uint len = str_length(string);
	u64 value = 0;

	uint p = 1;
	for(; len != -1; len--) {
		if (string[len] >= '0' && string[len] <= '9') {
			value += p * (string[len] - '0');
			p *= base;
		} else if (string[len] >= 'A' && string[len] <= 'Z') {
			value += p * (string[len] - 'A' + 10);
			p *= base;
		} else if (string[len] >= 'a' && string[len] <= 'z') {
			value += p * (string[len] - 'a' + 10);
			p *= base;
		}
	}

	return value;
}
f64 str_to_f64(cc string, uint base, char minus_sign, char separator) {
	uint len = str_length(string);
	f64 m = 1;
	f64 value = 0.0f;

	uint p = 1; uint dec = 0;
	for(; len != -1; len--) {
		if (string[len] >= '0' && string[len] <= '9') {
			value += p * (string[len] - '0');
			p *= base; m = 1;
		} else if (string[len] >= 'A' && string[len] <= 'Z') {
			value += p * (string[len] - 'A' + 10);
			p *= base; m = 1;
		} else if (string[len] >= 'a' && string[len] <= 'z') {
			value += p * (string[len] - 'a' + 10);
			p *= base; m = 1;
		}

		if(string[len] == separator) dec = p;
		if(string[len] == minus_sign) m = -1;
	}

	return (value / dec) * m;
}

uint s64_to_string_le(s64 value, char* buffer, uint buflen, uint base,
	char minus_sign, char plus_sign, char guide_char, uint guide_freq) {
	u64 i = 0; uint c = 0;
	if (value < 0) {
		if (minus_sign) { buffer[0] = minus_sign; i++;}
		value *= -1;
	} else if (plus_sign) {
		buffer[0] = plus_sign;
		i++;
	}

	do {
		if (guide_char && guide_freq && c && !(c % guide_freq)) {
			buffer[i] = guide_char; i++;
		}

		if(value % base > 9)
			buffer[i] = value % base + 'a' - 10;
		else buffer[i] = value % base + '0';
		i++; c++;
	} while((value /= base) && i < buflen);

	buffer[i++] = 0;
	return i;
}
uint u64_to_string_le(u64 value, char* buffer, uint buflen, uint base,
	char guide_char, uint guide_freq) {
	u64 i = 0; uint c = 0;

	do {
		if (guide_char && guide_freq && c && !(c % guide_freq)) {
			buffer[i] = guide_char; i++;
		}

		if(value % base > 9)
			buffer[i] = value % base + 'a' - 10;
		else buffer[i] = value % base + '0';
		i++; c++;
	} while((value /= base) && i < buflen);

	buffer[i++] = 0;
	return i;
}
uint f64_to_string_le(f64 value, char* buffer, uint buflen, uint base,
	char minus_sign, char plus_sign, char separator, char guide_char, uint guide_freq) {
	u64 i = 0; uint c = 0;
	if (value < 0) {
		if (minus_sign) { buffer[0] = minus_sign; i++;}
		value *= -1;
	} else if (plus_sign) {
		buffer[0] = plus_sign;
		i++;
	}

	u64 p = 0;
	while(value - (s64)value) {
		value *= base;
		p++;
	}
	u64 val = value;

	do {
		if(!p && separator) {
			buffer[i] = separator; i++; p--; c = 0;
			continue;
		} else if (guide_char && guide_freq && c && !(c % guide_freq)) {
			buffer[i] = guide_char; i++;
		}

		if(val % base > 9)
			buffer[i] = val % base + 'a' - 10;
		else buffer[i] = val % base + '0';
		i++; c++; p--;
		val /= base;
	} while(val && i < buflen);

	buffer[i++] = 0;
	return i;
}

s64 str_to_s64_le(cc string, uint base, char minus_sign) {
	s64 value = 0;
	s64 m = 1;

	uint p = 1;
	for(uint i=0; string[i]; i++) {
		if (string[i] >= '0' && string[i] <= '9') {
			value += p * (string[i] - '0');
			p *= base; m = 1;
		} else if (string[i] >= 'A' && string[i] <= 'Z') {
			value += p * (string[i] - 'A' + 10);
			p *= base; m = 1;
		} else if (string[i] >= 'a' && string[i] <= 'z') {
			value += p * (string[i] - 'a' + 10);
			p *= base; m = 1;
		}

		if(string[i] == minus_sign) m = -1;
	}

	return value * m;
}

u64 str_to_u64_le(cc string, uint base) {
	u64 value = 0;

	uint p = 1;
	for(uint i=0; string[i]; i++) {
		if (string[i] >= '0' && string[i] <= '9') {
			value += p * (string[i] - '0');
			p *= base;
		} else if (string[i] >= 'A' && string[i] <= 'Z') {
			value += p * (string[i] - 'A' + 10);
			p *= base;
		} else if (string[i] >= 'a' && string[i] <= 'z') {
			value += p * (string[i] - 'a' + 10);
			p *= base;
		}
	}

	return value;
}
f64 str_to_f64_le(cc string, uint base, char minus_sign, char plus_sign, char separator) {
	f64 m = 1;
	f64 value = 0.0f;

	uint p = 1; uint dec = 0;
	for(uint i=0; string[i]; i++) {
		if (string[i] >= '0' && string[i] <= '9') {
			value += p * (string[i] - '0');
			p *= base; m = 1;
		} else if (string[i] >= 'A' && string[i] <= 'Z') {
			value += p * (string[i] - 'A' + 10);
			p *= base; m = 1;
		} else if (string[i] >= 'a' && string[i] <= 'z') {
			value += p * (string[i] - 'a' + 10);
			p *= base; m = 1;
		}

		if(string[i] == separator) dec = p;
		if(string[i] == minus_sign) m = -1;
	}

	return (value / dec) * m;
}



#endif
