/*
 * App.h
 *
 * Created: 20/05/2014 23:16:15
 *  Author: Karl
 */ 

#ifndef APP_H_
#define APP_H_

#define BACKSPACE (0x7F) /* On my keyboard it is 'DEL' and not 0x08 'BS' */

/* Note that I am deliberately defining different variable types for the
 * application space
 */
#define U32 unsigned long
#define S32 signed long
#define U16 unsigned short
#define S16 signed short
#define U8 unsigned char
#define S8 signed char

/* vectors in AVR are hard coded to a function by name */
/* USART0 Rx Complete */
extern void ISR_USART0_RX (void) __attribute__ ((signal));
/* USART0 Data Register Empty */
extern void ISR_USART0_UDRE (void) __attribute__ ((signal));
/* USART0 Tx Complete */
extern void ISR_USART0_TX (void) __attribute__ ((signal));


#endif /* APP_H_ */
