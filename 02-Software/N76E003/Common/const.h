#ifndef CONST_H
#define CONST_H

#define ON		1
#define OFF		0

//#define	FALSE	0
//#define TRUE	1

#define YES		TRUE
#define NO		FALSE

#define FAILED	FALSE
//#define SUCCESS	TRUE

#define LB_UINT8	0x0F
#define UB_UINT8	0xF0

#ifdef N76E003
/*!< Signed integer types  */
typedef   signed char     int8_t;
typedef   signed short    int16_t;
typedef   signed long     int32_t;

/*!< STM8 Standard Peripheral Library old types (maintained for legacy purpose) */

#define     __I     volatile const   /*!< defines 'read only' permissions     */
#define     __O     volatile         /*!< defines 'write only' permissions    */
#define     __IO    volatile         /*!< defines 'read / write' permissions  */

//typedef int32_t  s32;
//typedef int16_t s16;
//typedef int8_t  s8;


typedef enum {FALSE = 0, TRUE = !FALSE} Bool;

typedef enum {RESET = 0, SET = !RESET} FlagStatus, ITStatus, BitStatus, BitAction;

typedef enum {DISABLE = 0, ENABLE = !DISABLE} FunctionalState;

typedef enum {ERROR = 0, SUCCESS = !ERROR} ErrorStatus;

#define U8_MAX     (255)
#define S8_MAX     (127)
#define S8_MIN     (-128)
#define U16_MAX    (65535u)
#define S16_MAX    (32767)
#define S16_MIN    (-32768)
#define U32_MAX    (4294967295uL)
#define S32_MAX    (2147483647)
#define S32_MIN    (-2147483648uL)

#endif

#endif //CONST_H