/******************************************************/
/*      Author  : Farouk Ehab Fouad                   */
/*      SWC     :   STD_TYPES.h                       */
/*      Date    :   1/10/2023                         */
/*      version :       1.00                          */
/******************************************************/

#ifndef UTILS_STD_TYPES_H_
#define UTILS_STD_TYPES_H_

typedef  unsigned  char          u8;
typedef  signed    char          s8;

typedef  unsigned  short int     u16;
typedef  signed    short int     s16;

typedef  unsigned long int       u32;
typedef  signed   long int       s32;

typedef  float                   f32;
typedef  double                  f64;

typedef  unsigned long long      u64;
typedef  signed   long long      s64;

//#define  NuLL                    '\0'
#ifndef NULL
#define NULL	((void*)0)

#define E_OK 					  1;
#define E_NOK					  0;

#endif

#endif /* UTILS_STD_TYPES_H_ */
