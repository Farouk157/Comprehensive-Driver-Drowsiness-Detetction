/******************************************************/
/*      Author  : Farouk Ehab Fouad                   */
/*      SWC     :   BIT_MATH.h                        */
/*      Date    :   1/10/2023                         */
/*      version :       1.00                          */
/******************************************************/

#ifndef UTILS_BIT_MATH_H_
#define UTILS_BIT_MATH_H_

#define   SET_BIT(VAR,BIT)  (VAR)|= ( 1<<(BIT))  // DDRA |=(1<<pin)
#define   TOG_BIT(VAR,BIT)  (VAR)^= ( 1<<(BIT))
#define   CLR_BIT(VAR,BIT)  (VAR)&= ~(1<< (BIT))
#define   GET_BIT(VAR,BIT)   ((VAR>>(BIT)) & 1)  // =  (( VAR &(1<<BIT))>>BIT)
#define   BIT_IS_CLEAR(VAR,BIT)  !(( VAR &(1<<BIT))>>BIT)

#endif /* UTILS_COMMON_MACROS_H_ */

