#ifndef _DOTLIB_STR_LONGTYPE
#define _DOTLIB_STR_LONGTYPE

#include "./types.h"
#include "./str.h"

uint s128_to_string(s128 value, char* buffer, uint buflen, uint base,
	char minus_sign, char plus_sign, char guide_char, uint guide_freq) {
	bool neg = (value < 0); if (neg) value = -value;
	s128 a = value; uint c = 0; uint len = 0;
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
uint u128_to_string(u128 value, char* buffer, uint buflen, uint base,
	char guide_char, uint guide_freq) {
	u128 a = value; uint c = 0; uint len = 0;
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



s128 str_to_s128(cc string, uint base, char minus_sign) {
	uint len = str_length(string);
	s128 value = 0;
	s128 m = 1;

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
u128 str_to_u128(cc string, uint base) {
	uint len = str_length(string);
	u128 value = 0;

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


uint s128_to_string_le(s128 value, char* buffer, uint buflen, uint base,
	char minus_sign, char plus_sign, char guide_char, uint guide_freq) {
	u128 i = 0; uint c = 0;
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
uint u128_to_string_le(u128 value, char* buffer, uint buflen, uint base,
	char guide_char, uint guide_freq) {
	u128 i = 0; uint c = 0;

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


s128 str_to_s128_le(cc string, uint base, char minus_sign) {
	s128 value = 0;
	s128 m = 1;

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

u128 str_to_u128_le(cc string, uint base) {
	u128 value = 0;

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



uint f128_to_string(f128 value, char* buffer, uint buflen, uint base, 
	char minus_sign, char plus_sign, char separator, char guide_char, uint guide_freq) {
	bool neg = (value < 0); if (neg) value = -value;
	f128 _ = value; uint c = 0; uint len = 0; uint a = 0; uint p = 0;
	while(_ - (u128)_) { _ *= base; p++; }
	u128 ival = _; u128 _val = ival;

	do len++; while (_val /= base);
	len += (guide_char && guide_freq) ? (len-1) / guide_freq : 0;
	len += (neg) ? !!minus_sign : !!plus_sign; len += !!separator;

	len--; buffer[len] = '\0'; len--;

	do {
		if(!p && separator) {
			buffer[len] = separator; len--; p--; a++; c = 0;
			continue;
		} else if (guide_char && guide_freq && c && !(c % guide_freq)) {
			buffer[len] = guide_char; len--; a++;
		}

		if(ival % base > 9)
			buffer[len] = ival % base + 'a' - 10;
		else buffer[len] = ival % base + '0';
		len--; c++; p--;
		ival /= base;
	} while(ival && a++ < buflen);


	if(neg) { if (minus_sign) buffer[len] = minus_sign; }
	else { if (plus_sign) buffer[len] = plus_sign; }

	return a;
}
uint f128_to_string_le(f128 value, char* buffer, uint buflen, uint base,
	char minus_sign, char plus_sign, char separator, char guide_char, uint guide_freq) {
	u128 i = 0; uint c = 0;
	if (value < 0) {
		if (minus_sign) { buffer[0] = minus_sign; i++;}
		value *= -1;
	} else if (plus_sign) {
		buffer[0] = plus_sign;
		i++;
	}

	u128 p = 0;
	while(value - (s128)value) {
		value *= base;
		p++;
	}
	u128 val = value;

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
f128 str_to_f128(cc string, uint base, char minus_sign, char separator) {
	uint len = str_length(string);
	f128 m = 1;
	f128 value = 0.0f;

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
f128 str_to_f128_le(cc string, uint base, char minus_sign, char plus_sign, char separator) {
	f128 m = 1;
	f128 value = 0.0f;

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
