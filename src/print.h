#ifndef _DOTLIB_PRINT
#define _DOTLIB_PRINT

#include "./types.h"
#include "./buffer.h"
#include "./dfind.h"
#include "./str.h"
#include "./mem.h"
#include "./va_arg.h"

// Argument check for types
#pragma  varargck  argpos  print       1
#pragma  varargck  argpos  println     1
#pragma  varargck  argpos  printerr    1
#pragma  varargck  argpos  printlnerr  1
#pragma  varargck  argpos  xprint      2
#pragma  varargck  argpos  println     2
// #pragma varargck  argpos fprint       2
// #pragma varargck  argpos fprintln     2


// #pragma  varargck  type  "S"	Rune*
// #pragma  varargck  type  "Q"	Rune*

#pragma  varargck  type  "%"	void
#pragma  varargck  type  "c"    char
#pragma  varargck  type  "s"    cc
#pragma  varargck  type  "b"    bool // true false
#pragma  varargck  type  "B"    bool // yes no
#pragma  varargck  type  "p"    void*


// for integers only
// [bitsize]<flag>[:base,][+length,]
// [bitsize]<flag>[:base,][+length,][!]  -- prefix
// [bitsize]<flag>[:base,][+length,][#]  -- guide char (_)
// [bitsize]<flag>[:base,][+length,][$]  -- guide char ( )
// [bitsize]<flag>[:base,][+length,][~]  -- little endiant
// [bitsize]<flag>[:base,][+length,][.precision,]  -- for floating points
// :base or x for hexadecimal, o for octal and b for binary
// capital for prefix

#pragma  varargck  type  "u"    u32
#pragma  varargck  type  "d"    s32
#pragma  varargck  type  "i"    s32
#pragma  varargck  type  "hhu"  u8
#pragma  varargck  type  "hhd"  s8
#pragma  varargck  type  "hhi"  s8
#pragma  varargck  type  "hu"   u16
#pragma  varargck  type  "hd"   s16
#pragma  varargck  type  "hi"   s16
#pragma  varargck  type  "lu"   u64
#pragma  varargck  type  "ld"   u64
#pragma  varargck  type  "li"   s64
#pragma  varargck  type  "llu"  u128
#pragma  varargck  type  "lld"  s128
#pragma  varargck  type  "lli"  s128
#pragma  varargck  type  "f"    f32
#pragma  varargck  type  "lf"   f64
#pragma  varargck  type  "llf"  f128

#pragma  varargck  type  "e"    f32
#pragma  varargck  type  "le"   f64
#pragma  varargck  type  "lle"  f128



// Time
// <flag>[offset,][w]     -- weekday (xxx.)
// <flag>[offset,][W]     -- weekday
// <flag>[offset,][m]     -- month (xxx.)
// <flag>[offset,][M]     -- month
// <flag>[offset,][n]     -- week number
// <flag>[offset,][/]     -- AM/PM
// <flag>[offset,][/][?]  -- lap year (yes/no)
// <flag>[offset,][/][#]  -- lap year x/4

#pragma  varargck  type  "t"    time_t
#pragma  varargck  type  "ht"   hour_t
#pragma  varargck  type  "lt"   date_t
#pragma  varargck  type  "k"    u64
#pragma  varargck  type  "hk"   u64
#pragma  varargck  type  "lk"   u64

void dformat_ref(void(*_puts)(cc, uint), void* ref) {
	char buf[19] = "0x0000000000000000";
	u64  val = (u64)ref;
	uint i = 17;
	do {
		if(val % 16 > 9)
			buf[i] = val % 16 + 'a' - 10;
		else buf[i] = val % 16 + '0';
		i--;
	} while((val /= 16));
	_puts(buf, 19);
}
void dformat_uints(void(*_puts)(cc, uint), u64 value) {
	char buf[65] = {0};
	str_from_u64(value, buf, 65, 10, 0, 0);
	_puts(buf, -1);
}
void dformat_ints(void(*_puts)(cc, uint), s64 value) {
	char buf[66] = {0};
	str_from_s64(value, buf, 66, 10, '-', 0, 0, 0);
	_puts(buf, -1);
}
void dformat_floats(void(*_puts)(cc, uint), f64 value) {
	// char buf[512] = {0};
	char buf[512] = {0};
	str_from_f64(value, buf, 512, 10, '-', 0, '.', 0, 0);
	_puts(buf, -1);
}

// void dformat_u128(void(*_puts)(cc, uint), u128 value) {
// 	char buf[129] = {0};
// 	u128_to_string(value, buf, 21, 10,  0, 0);
// 	_puts(buf, -1);
// }
// void dformat_s128(void(*_puts)(cc, uint), s128 value) {
// 	char buf[130] = {0};
// 	s128_to_string(value, buf, 21, 10, '-', 0, 0, 0);
// 	_puts(buf, -1);
// }


// void dformat_u8(void(*_puts)(cc, uint), u8 val);
// void dformat_u16(void(*_puts)(cc, uint), u16 val);
// void dformat_u32(void(*_puts)(cc, uint), u32 val);
// void dformat_u64(void(*_puts)(cc, uint), u64 val);
// void dformat_u128(void(*_puts)(cc, uint), u128 val);
// void dformat_s8(void(*_puts)(cc, uint), s8 val);
// void dformat_s16(void(*_puts)(cc, uint), s16 val);
// void dformat_s32(void(*_puts)(cc, uint), s32 val);
// void dformat_s64(void(*_puts)(cc, uint), s64 val);
// void dformat_s128(void(*_puts)(cc, uint), s128 val);
// void dformat_f32(void(*_puts)(cc, uint), f32 val);
// void dformat_f64(void(*_puts)(cc, uint), f64 val);
// void dformat_f128(void(*_puts)(cc, uint), f128 val);

void dformat_match(cc string, va_list list, void(*_puts)(cc, uint)) {
	const char* patterns[] = {
	//  0      1      2      3      4      5      6      7     8     9     10
		"%",   "c",   "s",   "b",   "B",   "p",   "hhu", "hu", "u",  "lu", "llu",
	//  11     12     13     14     15     16     17     18    19    20
		"hhd", "hd",  "d",   "ld",  "lld", "hhi", "hi",  "i",  "li", "lli",
	//  21     22     23     24     25     26     27     28    29    30     31  32
		"f",   "lf",  "llf", "e",   "le",  "lle", "ht",  "t",  "lt", "hk",  "k","lk"
	}; // 33

	uint type      = -1;
	// uint base      = 0;
	// uint length    = 0;
	// uint precision = -1;
	// bool prefix    = false;
	// char guide     = 0;
	// bool le        = false;
	// uint offset    = 0;
	// uint weekday   = 0;
	// uint month     = 0;
	// bool weeknbr   = 0;
	// bool ampm      = false;
	// uint lapyear   = 0;

	uint last = 0;
	uint i    = 0;
	for (; string[i]; i++) {
		if (string[i] == '%') {
			char target[4] = {0,0,0,0};
			uint j = 0;
			for (; j<3 && string[i+1+j]; j++) {
				target[j] = string[i+1+j];
				type = find_str(patterns, target, 33);
				if (type != -1)
					break;
			}

			if (type == 6) { // hhu
				_puts(string+last, i-last);
				// C wants throws a warning to promote the type of va_arg to
				// int when it's size (-> sizeof) is smaller than an int.
				// using int and casting to u8 works just as well and
				// doesn't throw an error at least.
				u8 val = va_arg(list, int);
				dformat_uints(_puts, val);
				i    += j+2;
				last  = i;
			} else if (type == 7) {
				_puts(string+last, i-last);
				u16 val = va_arg(list, int);
				dformat_uints(_puts, val);
				i    += j+2;
				last  = i;
			} else if (type == 8) {
				_puts(string+last, i-last);
				u32 val = va_arg(list, u32);
				dformat_uints(_puts, val);
				i    += j+2;
				last  = i;
			} else if (type == 9) {
				_puts(string+last, i-last);
				u64 val = va_arg(list, u64);
				dformat_uints(_puts, val);
				i    += j+2;
				last  = i;
			} /* else if (type == 10) {
				_puts(string+last, i-last);
				u128 val = va_arg(list, u128);
				dformat_u128(_puts, val);
				i    += j+2;
				last  = i;

			} */ else if (type == 11) { // hhd
				_puts(string+last, i-last);
				s8 val = va_arg(list, int);
				dformat_ints(_puts, val);
				i    += j+2;
				last  = i;
			} else if (type == 12) {
				_puts(string+last, i-last);
				s16 val = va_arg(list, int);
				dformat_ints(_puts, val);
				i    += j+2;
				last  = i;
			} else if (type == 13) {
				_puts(string+last, i-last);
				s32 val = va_arg(list, s32);
				dformat_ints(_puts, val);
				i    += j+2;
				last  = i;
			} else if (type == 14) {
				_puts(string+last, i-last);
				s64 val = va_arg(list, s64);
				dformat_ints(_puts, val);
				i    += j+2;
				last  = i;
			} /* else if (type == 15) {
				_puts(string+last, i-last);
				s128 val = va_arg(list, s128);
				dformat_s128(_puts, val);
				i    += j+2;
				last  = i;
			} */ else if (type == 16) { // hhi
				_puts(string+last, i-last);
				s8 val = va_arg(list, int);
				dformat_ints(_puts, val);
				i    += j+2;
				last  = i;
			} else if (type == 17) {
				_puts(string+last, i-last);
				s16 val = va_arg(list, int);
				dformat_ints(_puts, val);
				i    += j+2;
				last  = i;
			} else if (type == 18) {
				_puts(string+last, i-last);
				s32 val = va_arg(list, s32);
				dformat_ints(_puts, val);
				i    += j+2;
				last  = i;
			} else if (type == 19) {
				_puts(string+last, i-last);
				s64 val = va_arg(list, s64);
				dformat_ints(_puts, val);
				i    += j+2;
				last  = i;
			} /* else if (type == 20) {
				_puts(string+last, i-last);
				s128 val = va_arg(list, s128);
				dformat_s128(_puts, val);
				i    += j+2;
				last  = i;

			} */ else if (type == 21) { // f
				_puts(string+last, i-last);
				// Same here. (look at definition for hhu hint)
				f32 val = va_arg(list, double);
				dformat_floats(_puts, val);
				i    += j+2;
				last  = i;
			} else if (type == 22) {
				_puts(string+last, i-last);
				f64 val = va_arg(list, f64);
				dformat_floats(_puts, val);
				i    += j+2;
				last  = i;
			} /* else if (type == 23) {
				_puts(string+last, i-last);
				f128 val = va_arg(list, f128);
				dformat_f128(_puts, val);
				i    += j+2;
				last  = i;
			} */
			// } else if (type == 24)// e
			// case 25:
			// case 26:

			// case 27: // ht
			// case 28:
			// case 29:
			// case 30: // hk
			// case 31:
			// case 32:

			/*for (; string[i+j]; j++)
			if (string[i+j] == ',') {}

			if (string[i+j] == ':' && !base) {}
			if (string[i+j] == '+') {}
			if (string[i+j] == '.') {}

			if (string[i+j] == '!') {}
			if (string[i+j] == '#') {}
			if (string[i+j] == '$') {}
			if (string[i+j] == '~') {}
			if (string[i+j] == '?') {}
			if (string[i+j] == '/') {}

			if (string[i+j] == 'x' && !base) {}
			if (string[i+j] == 'o' && !base) {}
			if (string[i+j] == 'b' && !base) {}
			if (string[i+j] == 'X' && !base) {}
			if (string[i+j] == 'O' && !base) {}
			if (string[i+j] == 'B' && !base) {}

			if (string[i+j] == 'w') {}
			if (string[i+j] == 'W') {}
			if (string[i+j] == 'm') {}
			if (string[i+j] == 'M') {}
			if (string[i+j] == 'n') {} */

			else if (type == 0) {
				_puts(string+last, i-last);
				i++;
				last  = i;
			} else if (type == 1) {
				_puts(string+last, i-last);
				// Same here.
				char ch = va_arg(list, int);
				_puts(&ch, 1);
				i += 2;
				last  = i;
			} else if (type == 2) {
				_puts(string+last, i-last);
				cc str = va_arg(list, cc);
				_puts(str, -1);
				i += 2;
				last  = i;
			} else if (type == 3) {
				_puts(string+last, i-last);
				bool bl = va_arg(list, int);
				_puts(bl ? "true" : "false", -1);
				i += 2;
				last  = i;
			} else if (type == 4) {
				_puts(string+last, i-last);
				bool bl = va_arg(list, int);
				_puts(bl ? "yes" : "no", -1);
				i += 2;
				last  = i;
			} else if (type == 5) {
				_puts(string+last, i-last);
				void* ref = va_arg(list, void*);
				dformat_ref(_puts, ref);
				i += 2;
				last  = i;
			}
		}
		if (!string[i]) break;
	}
	if (string[last]) _puts(string+last, i-last);
}


#ifdef _WIN32

#include <windows.h>

// static void* __stdout_handle = GetStdHandle(STD_OUTPUT_HANDLE);
// static void* __stderr_handle = GetStdHandle(STD_ERROR_HANDLE);

#define __puts_stdout(data, size) WriteConsole(GetStdHandle(STD_OUTPUT_HANDLE), data, size, NULL, NULL);
#define __puts_stderr(data, size) WriteConsole(GetStdHandle(STD_ERROR_HANDLE), data, size, NULL, NULL);

#else // __unix

#include <unistd.h>

#define __puts_stdout(data, size) write(1, data, size);
#define __puts_stderr(data, size) write(0, data, size);

#endif

#ifndef _DOTLIB_IO_BUFLEN
#define _DOTLIB_IO_BUFLEN 2048
#endif
static char __dotlib_io_buffer[_DOTLIB_IO_BUFLEN] = {0};
static uint __dotlib_io_index = 0;
void __dotlib_io_append(cc text, uint size) {
	for (uint i=0; __dotlib_io_index <= _DOTLIB_IO_BUFLEN &&
		i < size && text[i]; __dotlib_io_index++, i++) {
		if (__dotlib_io_index >= _DOTLIB_IO_BUFLEN) {
			__puts_stdout(__dotlib_io_buffer, _DOTLIB_IO_BUFLEN);
			__dotlib_io_buffer[0] = 0;
			__dotlib_io_index = 0;
		}
		__dotlib_io_buffer[__dotlib_io_index] = text[i];
	}
}
void __dotlib_io_flush() {
	__puts_stdout(__dotlib_io_buffer, __dotlib_io_index);
	__dotlib_io_buffer[0] = 0;
	__dotlib_io_index = 0;
}



#ifndef _DOTLIB_ERR_BUFLEN
#define _DOTLIB_ERR_BUFLEN 2048
#endif
static char __dotlib_err_buffer[_DOTLIB_ERR_BUFLEN] = {0};
static uint __dotlib_err_index = 0;
void __dotlib_err_append(cc text, uint size) {
	for (uint i=0; __dotlib_err_index <= _DOTLIB_ERR_BUFLEN &&
		i < size && text[i]; __dotlib_err_index++, i++) {
		if (__dotlib_err_index >= _DOTLIB_ERR_BUFLEN) {
			__puts_stdout(__dotlib_err_buffer, _DOTLIB_ERR_BUFLEN);
			__dotlib_err_buffer[0] = 0;
			__dotlib_err_index = 0;
		}
		__dotlib_err_buffer[__dotlib_err_index] = text[i];
	}
}
void __dotlib_err_flush() {
	__puts_stdout(__dotlib_err_buffer, __dotlib_err_index);
	__dotlib_err_buffer[0] = 0;
	__dotlib_err_index = 0;
}

// // https://github.com/Bhalut/printf
// typedef struct {
// 	cc fmt;
// 	int (*func)(va_list list);
// } _dotlib_fmt;




void print(cc string, ...) {
	va_list list;
	va_start(list, string);

	dformat_match(string, list, __dotlib_io_append);
	__dotlib_io_flush();

	va_end(list);
}
void println(cc string, ...) {
	va_list list;
	va_start(list, string);

	dformat_match(string, list, __dotlib_io_append);
	__dotlib_io_append("\n", 1);
	__dotlib_io_flush();

	va_end(list);
}

void printerr(cc string, ...) {
	va_list list;
	va_start(list, string);

	dformat_match(string, list, __dotlib_err_append);
	__dotlib_err_flush();

	va_end(list);
}
void printlnerr(cc string, ...) {
	va_list list;
	va_start(list, string);

	dformat_match(string, list, __dotlib_err_append);
	__dotlib_err_append("\n", 1);
	__dotlib_err_flush();

	va_end(list);
}

/*
typedef struct {
	uint  buflen;
	char* buffer;
	void(*puts)(char* data, uint size);
	void(*flush)(uint size);
} xio;

void xprint_init(xio* impl) { impl->buffer = (char*)mem_alloc(impl->buflen); }
xio  xprint_init2(uint buflen, void(*puts)(char*, uint), void(*flush)(char*)) {
	xio impl;
	impl.buflen = buflen;
	impl.buffer = (char*)mem_alloc(buflen);
	impl.puts   = puts;
	impl.flush  = flush;
	return impl;
}
void xprint_destroy(xio* impl) { free(impl->buffer); }

void xprint(xio* impl, cc string, ...) {
	va_list list;
	va_start(list, string);

	dformat_match(string, list, impl->puts);
	impl->flush();

	va_end(list);
}
void xprintln(xio* impl, cc string, ...); */


#endif




















