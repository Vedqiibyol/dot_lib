# Documentation

As of, versnio `0`.

## `ansiclr.h` ANSI Terminal

This header contains only constants (in the form of `#define`ed macros), it
includes:

A `endl` macro for adding an end of line (`\n` for UNIX-like and `\r\n` for
Windows) which also resets all styles and colors. As well as the macro
`st_reset` which removes all styles and colors.

All the different styles `st_bold`, `st_grey`, `st_ital`, `st_uns`, `st_high`,
`st_strike`, which correspond respectively to **Bold**, Halfbright, *Italic*,
__Underlined__ or __Underscored__, ==Highligh== and ~~Strikethrough~~.

All the collors for background and foreground; with which `bg` is prefixes the
name for background and `fg` for foreground. The colors include Black, Red,
Green, Brown or Orange, Blue, Magenta otherwise Purple, Cyan and White. Which
respectively correspond to `bg_black`, `bg_red`, `bg_green`, `bg_brown`,
`bg_blue`, `bg_magen`, `bg_cyan`, `bg_white`. You will also find the macros
`bg_reset` and `fg_reset` which as the name suggests, reset the background
or foreground.

Also includes `vt_uns` for a slightly thicker underline, and `vt_blink` which
makes the text blink at a certain interval between fullbright and halfbright.

If you are not familiar with ANSI Terminal sequences, you should read the
manpage for `console_codes`, or online at
https://man7.org/linux/man-pages/man4/console_codes.4.html

## `defines.h` Handy constants and macros

This header contains a collection of simple and commonly used macros.

- `is_even(x)` `is_odd(x)` Do what their names suggest
- `max(a, b)` `min(a, b)` Do what their names suggest
- `bit_on(var, bit)` Allows to toggle a bit on, or set it to true, `var` is the
	variable to modify and `bit` indicates the bit to set on.
- `bit_off(var, bit)` Allows to toggle a bit off, or set it to false, `var` is
	the variable to modify and `bit` indicates the bit to set on.
- `toggle(var, bit)` Allows to toggle a bit on or off, true or false, `var` is
	the variable to modify and `bit` indicates the bit to toggle.
- `bool_str(var)` returns either "true" or "false" as a string.
- `bool_str2(var)` returns either "yes" or "no" as a string.
- `bool_str3(var)` returns either "on" or "off" as a string.
- `f32_mantissa(var)` returns only the part of the mantissa from a 32 bit
	floating point unit.
- `f32_sign(var)` returns only the part of the sign from a 32 bit floating point
	unit.
- `f32_exp(var)` returns only the part of the exponent from a 32 bit floating
	point unit.
- `f32_expshift(var)` returns only the part of the exponent, shifted to towards
	the LSB of 23 positions.
- `f32_pow(var)` returns the power of a 32 bit floating point unit
- `f64_mantissa(var)` returns only the part of the mantissa from a 64 bit
	floating point unit.
- `f64_sign(var)` returns only the part of the sign from a 64 bit floating point
	unit.
- `f64_exp(var)` returns only the part of the exponent from a 64 bit floating
	point unit.
- `f64_expshift(var)` returns only the part of the exponent, shifted to towards
	the LSB of 52 positions.
- `f64_pow(var)` returns the power of a 64 bit floating point unit

## `dfind.h` Dotlib's find algorithm

Provides basic search algorithm for linear search, reverse linear search and
binary search, respectively starting by `find_`, `rfind_` and `bfind_` and
suffixed by the type it works with, `str` for string, `s64`, `u64` and `f64` for
their corresponding types in `types.h`. Each functions take in parameter a list
of values of corresponding type, as well as a target, and finally an integer
representing the size of the list. The functions return the position of the
target in the given list, -1 if the targe is not present.

Here, a list of all functions:
- `find_str`, `rfind_str`, `bfind_str`
- `find_s64`, `rfind_s64`, `bfind_s64`
- `find_u64`, `rfind_u64`, `bfind_u64`
- `find_f64`, `rfind_f64`, `bfind_f64`

You will also find other functions suffixed with `any`, these functions act as
templates for any kind of types, they take in parameter a pointer to a list of
void pointers, that are only pointers to the values, a target as `void*`, and a
size. Additionally there exists two derivates of functions, functions that use
a comparse function (ending in `_cmp`) and functions that use an equality
function (ending in `_equ`). For binary search, there are three derivates,
compare, equal and inferior operations (`_equinf`) and equal and superior
operations (`_equsup`). These functions take in parameter a compare function
that returns a signed integer and takes in parameter two pointers to void, or an
equality function that returns a boolean value. For equal and superior or
inferior, the function pointer template remain the same as the latter, but two
function pointers are passed, one for equality and the other for the associated
operation. The return value is the position of the target in the given list, or
-1 if the target is not present.

Here are the functions
- `find_any_cmp` and `rfind_any_cmp` that take a function pointer to a function
	performing a comparision (e.g a substraction) returning an integer value and
	two pointers to void.
- `find_any_equ` and `rfind_any_equ` that take a function pointer to a function
	performing an equality check (e.g a xor onto itself) returning a boolean
	value and two pointers to void.
- `bfind_any_cmp` that takes a function pointer to a function performing a
	comparision (e.g a substraction) returning an integer value and two pointers
	to void.
- `bfind_any_equinf` that takes a function pointer to a function performing an
	equality check (e.g a xor onto itself) and a function pointer to a function
	performing an inferiority check (e.g a comparision), returning an integer
	value and two pointers to void.
- `bfind_any_equsup` that takes a function pointer to a function performing an
	equality check (e.g a xor onto itself) and a function pointer to a function
	performing an superiority check (e.g a comparision), returning an integer
	value and two pointers to void.

Your compiler may annoy you by telling that conversion from your function is not
possible, in this case you may want to cast it to `int(*)(void*,void*)` or
`bool(*)(void*,void*)`, you can also use the built-in types provided by the
header, which are respectively `any_cmp_t` and `any_equ_t`.

## `mem.h` for memory allocation

This header provides different functions for memory management, and is an
alternative to the C standard library `malloc` and `free`.

- `mem_alloc` takes in parameter one 64 bit integer that indicates the size of
	the memory to allocate and return a pointer to that memory, or `nullptr` if
	the memory couldn't be allocated.
- `mem_alloc0` has the same behaviour as the previous function but also
	initializes the allocated memory to 0.
- `mem_getsize` takes in parameter the pointer to a memory allocation and
	returns the size of the allocation, -1 if it is not valid.
- `mem_free` takes in parameter the pointer to a memory allocation and frees the
	memory.
- `mem_realloc` takes in parameter the pointer to a memory allocation and a new
	size for the allocation, and reallocates the block of memory and returns the
	pointer to the newly reallocated block.
- `mem_realloc0`  has the same behaviour as the previous function but also
	(re)initializes the allocated memory to 0.
- `mem_expand` takes in parameter the pointer to a memory allocation and an
	increment to increment the allocation's size by. It reallocates the block of
	memory and returns the pointer to the newly reallocated block.
- `mem_shrink` offers the same behaviour as `mem_expand` but shrinks the
	allocation by the value of `dec` which is the opposite of `inc`.

The header also provides macro to redefines `malloc`, `free`, `realloc` and
`calloc` to their respective functions if they have not already been defined

The header also has five other functions for memory manipulation

- `mem_copy` takes in parameter one pointer to a buffer of the size precised by
	the second argument and allocates another buffer of same size and copies the
	content of the first into the new one.
- `mem_copy_to_buffer` is a routine that takes a source buffer, a destination
	buffer and a size (for both) and copies the content of the source to the
	destination
- `mem_fill` takes in parameter a pointer to a buffer, the size of the buffer
	and a filler value, and fills the buffer with given value.
- `mem_shift_to_tail` takes in parameter a pointer to a buffer, the size of the
	buffer and a shifting value, and shifts the content of the buffer from the
	given shift value towards the end of the buffer (the tail).
- `mem_shift_to_head` offers the same behaviour as the function above but
	shofts the data towards the start of the buffer (the head).

## `str.h` String manipulatin

This header contains functions dedicated to manipulate strings, here are the
following functions

- `str_length` which takes into paramter a single string (`cc` or `char*`) and
	returns the length of the string
- `str_copy` takes one string as argument (`cc` or `char*`) returns a heap
	allocated string
- `str_copy_to_buffer` takes in parameter a string, a buffer (as `char*`) and an
	integer representing the size of the given buffer. The function copies the
	content of the given string into the buffer for as much as it can hold and
	returns the number of copied bytes.
- `str_equal` return true if both given strings are equal, false otherwise.
- `str_inferior` returns true if the first string given is inferior to the
	second one, false otherwise.
- `str_superior` returns true if the first string given is superior to the
	second one, false otherwise.
- `str_compare` returns the difference between the first string and the second;
	0 if the two strings are equal, a value inferior to 0 if the first string
	is inferior, a value above 0 otherwise.
- `char_is_in` takes in parameter one character and a string, and returns the
	position of the character in the string.
<!-- - `str_upper` takes in parameter a single string of character, and puts all
	characters to their uppercase variant if any.
- `str_lower` takes in parameter a single string of character, and puts all
	characters to their lowercase variant if any. -->
- `str_find` takes in parameter two strings, and attempts to find the second
	in the first and returns its first encountered position.
- `str_rfind` takes in parameter two strings, and attempts to find the second
	in the first and returns its last encountered position, or its first
	position starting from its end.
- `str_starts_with` returns true if the first string starts with the second,
	note that the second string must not be of a superior length otherwise it
	cannot be contained in the first, thus returning false.
- `str_ends_with` returns true if the first string end with the second, note
	that the second string must not be of a superior length otherwise it
	cannot be contained in the first, thus returning false.
- `str_count` returns the number of occurence of the second string given in the
	first one

### String converstion

`s64_to_string`, `u64_to_string` and `f64_to_string` all take a value as
indicated by the first word of their name, and take the minus sign and positive
sign (only for `s64_to_string` and `f64_to_string`) which can both be ommited if
they are not wanted, a character that may be used as a reading guide and the
frequency at which given guide is suppose to appear. If the guide not provided,
or the frequency is 0, it will not be added. The function fills the buffer with
the string representation of the given value and returns its length.

`str_to_s64` ,`str_to_u64` and `str_to_f64` all take in parameter a string, a
numerical base, a character for the minus sign (exept `str_to_u64`),
`str_to_f64` also takes in parameter a character for the decimal separator, the
functions return as respective types their name suggests. Non-alpha numerical
characters are ignored, which in effects, soft-limits the available decimal
bases from 2 to 36.

These functions will respectively provide a string represented, and process
strings in Big-endiant, if you wish to use little-endiant, then you can add
`_le` at the end of the function name.

## `types.h` Alternative to `stdint.h`

This header provides more convinient type names, the pattern is the same as
TypeScript, for integers, a letter indicates the signature, `s` for signed
integers and `u` for unsigned integers. `f` for all floating points values.
Then the number of bit follows. Some compilers also provide 128 bit integers,
if this is the case for you, you can presise the `DOTLIBS_WITH_128BITS_INTS`.

The header also includes `typedef`s for unsigned 32 bit integers, `uint`, signed
64 bit integers, `rel` and `urel` for the unsigned variant. The name `cc` for
`const char*`

For pure C, the header also has a type definition for booleans, named as `bool`.
As well as a macro for `nullptr`.

Here are all the types, indicated above, in order.

```
s8 s16 s32 s64 s128
u8 u16 u32 u64 u128
f32 f64 f128
uint rel urel cc
bool
```
