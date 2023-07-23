#ifndef _DOTLIB_VA_ARG
#define _DOTLIB_VA_ARG

// va_list

#define va_start(list, arg) __builtin_va_start(list, arg)
#define va_arg(list, type)  __builtin_va_arg(list, type)
#define va_end(list)        __builtin_va_end(list)

#endif
