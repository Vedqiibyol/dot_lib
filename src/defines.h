#ifndef _DOTLIBS_DEFINES
#define _DOTLIBS_DEFINES

#define is_even(x) !(x & 1)
#define is_odd(x)   (x & 1)

#define max(a, b) (a > b) ? a : b
#define min(a, b) (a < b) ? a : b

#define bit_on(var, bit)  var |=  bit
#define bit_off(var, bit) var &= ~bit
#define toggle(var, bit)  var ^=  bit

#define bool_str(var) var ? "true" : "false"
#define bool_str2(var) var ? "yes" : "no"
#define bool_str3(var) var ? "on" : "off"

#define f32_mantissa(var) *(int)var & ~0xff800000
#define f32_sign(var) *(int)var & 0x80000000
#define f32_exp(var) *(int)var & 0x7f800000
#define f32_expshift(var) f32_exp(var) >> 23
#define f32_pow(var) f32_expshift(var) - 127

#define f64_mantissa(var) *(long long)var & ~0xfff0000000000000
#define f64_sign(var) *(long long)var & 0x8000000000000000
#define f64_exp(var) *(long long)var & 0x7ff0000000000000
#define f64_expshift(var) f64_exp(var) >> 52
#define f64_pow(var) f64_expshift(var) - 1023

#define rounddown(val) (u64)val
#define roundup(val) (u64)val + !!(val - (u64)val)
#define roundmid(val) (val - (u64)val < 0.5 ? rounddown(val) : val - (u64)val == 0.5 ? val : (u64)val ++)
#define round(val) (u64)val + (val - (u64)val <= 0.5)
#define xround(val) (u64)val + (val - (u64)val < 0.5)

// #define f32_decimal(var)
// #define f32_int(var)

// #define f64_decimal(var)
// #define f64_int(var)


#endif