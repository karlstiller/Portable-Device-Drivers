/* Header for the ATMega 2560  *
 *  Author: Karl Stiller       *
 *  Date: 22/04/2014           */
#ifndef ATMEGA2560_H_
#define ATMEGA2560_H_

/* Timers */
#define WDTCSR			( 0x60 )	/* Watchdog Timer Control Register */
#define WDTCSR_WDIF		( 1 << 7 )	/* Watchdog Interrupt Flag */
#define WDTCSR_WDIE		( 1 << 6 )  /* Watchdog Interrupt Enable */
#define WDTCSR_WDP3		( 1 << 5 )  /* Watchdog Timer Prescaler 3 */
#define WDTCSR_WDCE		( 1 << 4 )  /* Watchdog Change Enable */
#define WDTCSR_WDE		( 1 << 3 )  /* Watchdog System Reset Enable */
#define WDTCSR_WDP2		( 1 << 2 )  /* Watchdog Timer Prescaler 2 */
#define WDTCSR_WDP1		( 1 << 1 )  /* Watchdog Timer Prescaler 1 */
#define WDTCSR_WDP0		( 1 << 0 )  /* Watchdog Timer Prescaler 0 */

#define TCCR0A			( 0x44 )	/* Timer/Counter Control Register 0 A */
#define TCCR0A_COM0A1	( 1 << 7 )	/* Compare Match Output A Mode */
#define TCCR0A_COM0A0	( 1 << 6 )	/* Compare Match Output A Mode */
#define TCCR0A_COM0B1	( 1 << 5 )	/* Compare Match Output B Mode */
#define TCCR0A_COM0B0	( 1 << 4 )	/* Compare Match Output B Mode */
#define TCCR0A_WGM01	( 1 << 1 )	/* Waveform Generation Mode */
#define TCCR0A_WGM00	( 1 << 0 )	/* Waveform Generation Mode */
#define TCCR0A_CTC      ( TCCR0A_WGM01 ) /* CTC Mode */

#define TCCR0B			( 0x45 )	/* Timer/Counter Control Register 0 B */
#define TCCR0B_FOC0A	( 1 << 7 )	/* Force Output Compare A */
#define TCCR0B_FOC0B	( 1 << 6 )	/* Force Output Compare B */
#define TCCR0B_WGM02	( 1 << 3 )	/* Waveform Generation Mode */
#define TCCR0B_CS02		( 1 << 2 )	/* Clock Select */
#define TCCR0B_CS01		( 1 << 1 )	/* Clock Select */
#define TCCR0B_CS00		( 1 << 0 )	/* Clock Select */
#define TCCR0B_NO_CLK   ( 0 )
#define TCCR0B_CLK_1	( TCCR0B_CS00 )
#define TCCR0B_CLK_8	( TCCR0B_CS01 )
#define TCCR0B_CLK_64	( TCCR0B_CS00 | TCCR0B_CS01 )
#define TCCR0B_CLK_256	( TCCR0B_CS02 )
#define TCCR0B_CLK_1024 ( TCCR0B_CS02 |  TCCR0B_CS00 )
#define TCCR0B_EXTCLK_F ( TCCR0B_CS02 |  TCCR0B_CS01 )
#define TCCR0B_EXTCLK_R ( TCCR0B_CS02 |  TCCR0B_CS01 |  TCCR0B_CS00 )

#define TCNT0			( 0x46 )	/* Timer/Counter Register 0 */
#define OCR0A			( 0x47 )	/* Output Compare Register 0 A */
#define OCR0B			( 0x48 )	/* Output Compare Register 0 B */

#define	TIMSK0			( 0x6E )	/* Timer/Counter 0 Interrupt Mask Register */
#define TIMSK0_OCIE0B	( 1 << 2 )	/* Timer/Counter 0 Output Compare Match B Interrupt Enable */
#define TIMSK0_OCIE0A	( 1 << 1 )	/* Timer/Counter 0 Output Compare Match A Interrupt Enable */
#define TIMSK0_TOIE0	( 1 << 0 )	/* Timer/Counter 0 Overflow Interrupt Enable */

#define TIFR0			( 0x35)		/* Timer/Counter 0 Interrupt Flag Register */
#define TIFR0_OCF0B		( 1 << 2 )	/* Timer/Counter 0 Output Compare B Match Flag */
#define TIFR0_OCF0A		( 1 << 1 )	/* Timer/Counter 0 Output Compare A Match Flag */
#define TIFR0_TOV0		( 1 << 0 )	/* Timer/Counter0 Overflow Flag */

#define TCCR1A			( 0x80 ) 	/* Timer/Counter 1 Control Register A */
#define TCCR1A_COM1A1	( 1 << 7 )	/* Compare Output Mode for Channel A */
#define TCCR1A_COM1A0	( 1 << 6 )	/* Compare Output Mode for Channel A */
#define TCCR1A_COM1B1	( 1 << 5 )	/* Compare Output Mode for Channel B */
#define TCCR1A_COM1B0	( 1 << 4 )	/* Compare Output Mode for Channel B */
#define TCCR1A_COM1C1	( 1 << 3 )	/* Compare Output Mode for Channel C */
#define TCCR1A_COM1C0	( 1 << 2 )	/* Compare Output Mode for Channel C */
#define TCCR1A_WGM11	( 1 << 1 )	/* Waveform Generation Mode */
#define TCCR1A_WGM10	( 1 << 0 )	/* Waveform Generation Mode */

#define TCCR3A 			( 0x90 )	/* Timer/Counter 3 Control Register A */
#define TCCR3A_COM3A1	( 1 << 7 )	/* Compare Output Mode for Channel A */
#define TCCR3A_COM3A0	( 1 << 6 )	/* Compare Output Mode for Channel A */
#define TCCR3A_COM3B1	( 1 << 5 )	/* Compare Output Mode for Channel B */
#define TCCR3A_COM3B0	( 1 << 4 )	/* Compare Output Mode for Channel B */
#define TCCR3A_COM3C1	( 1 << 3 )	/* Compare Output Mode for Channel C */
#define TCCR3A_COM3C0	( 1 << 2 )	/* Compare Output Mode for Channel C */
#define TCCR3A_WGM31	( 1 << 1 )	/* Waveform Generation Mode */
#define TCCR3A_WGM30	( 1 << 0 )	/* Waveform Generation Mode */

#define TCCR4A			( 0xA0 )	/* Timer/Counter 4 Control Register A */
#define TCCR4A_COM4A1	( 1 << 7 )	/* Compare Output Mode for Channel A */
#define TCCR4A_COM4A0	( 1 << 6 )	/* Compare Output Mode for Channel A */
#define TCCR4A_COM4B1	( 1 << 5 )	/* Compare Output Mode for Channel B */
#define TCCR4A_COM4B0	( 1 << 4 )	/* Compare Output Mode for Channel B */
#define TCCR4A_COM4C1	( 1 << 3 )	/* Compare Output Mode for Channel C */
#define TCCR4A_COM4C0	( 1 << 2 )	/* Compare Output Mode for Channel C */
#define TCCR4A_WGM41	( 1 << 1 )	/* Waveform Generation Mode */
#define TCCR4A_WGM40	( 1 << 0 )	/* Waveform Generation Mode */

#define TCCR5A			( 0x120 )	/* Timer/Counter 5 Control Register A */
#define TCCR5A_COM5A1	( 1 << 7 )	/* Compare Output Mode for Channel A */
#define TCCR5A_COM5A0	( 1 << 6 )	/* Compare Output Mode for Channel A */
#define TCCR5A_COM5B1	( 1 << 5 )	/* Compare Output Mode for Channel B */
#define TCCR5A_COM5B0	( 1 << 4 )	/* Compare Output Mode for Channel B */
#define TCCR5A_COM5C1	( 1 << 3 )	/* Compare Output Mode for Channel C */
#define TCCR5A_COM5C0	( 1 << 2 )	/* Compare Output Mode for Channel C */
#define TCCR5A_WGM51	( 1 << 1 )	/* Waveform Generation Mode */
#define TCCR5A_WGM50	( 1 << 0 )	/* Waveform Generation Mode */

#define TCCR1B			( 0x81 )	/* Timer/Counter 1 Control Register B */
#define TCCR1B_ICNC1	( 1 << 7 )	/* Input Capture Noise Canceler */
#define TCCR1B_ICES1	( 1 << 6 )	/* Input Capture Edge Select */
#define TCCR1B_WGM13	( 1 << 4 )	/* Waveform Generation Mode */
#define TCCR1B_WGM12	( 1 << 3 )	/* Waveform Generation Mode */
#define TCCR1B_CS12		( 1 << 2 )	/* Clock Select */
#define TCCR1B_CS11		( 1 << 1 )	/* Clock Select */
#define TCCR1B_CS10		( 1 << 0 )	/* Clock Select */
#define TCCR1B_NO_CLK   ( 0 )
#define TCCR1B_CLK_1	( TCCR1B_CS10 )
#define TCCR1B_CLK_8	( TCCR1B_CS11 )
#define TCCR1B_CLK_64	( TCCR1B_CS10 | TCCR1B_CS11 )
#define TCCR1B_CLK_256	( TCCR1B_CS12 )
#define TCCR1B_CLK_1024 ( TCCR1B_CS12 |  TCCR1B_CS10 )
#define TCCR1B_EXTCLK_F ( TCCR1B_CS12 |  TCCR1B_CS11 )
#define TCCR1B_EXTCLK_R ( TCCR1B_CS12 |  TCCR1B_CS11 |  TCCR1B_CS10 )

#define TCCR3B			( 0x91 )	/* Timer/Counter 3 Control Register B */
#define TCCR3B_ICNC3	( 1 << 7 )	/* Input Capture Noise Canceler */
#define TCCR3B_ICES3	( 1 << 6 )	/* Input Capture Edge Select */
#define TCCR3B_WGM33	( 1 << 4 )	/* Waveform Generation Mode */
#define TCCR3B_WGM32	( 1 << 3 )	/* Waveform Generation Mode */
#define TCCR3B_CS32		( 1 << 2 )	/* Clock Select */
#define TCCR3B_CS31		( 1 << 1 )	/* Clock Select */
#define TCCR3B_CS30		( 1 << 0 )	/* Clock Select */

#define TCCR4B			( 0xA1 )	/* Timer/Counter 4 Control Register B */
#define TCCR4B_ICNC4	( 1 << 7 )	/* Input Capture Noise Canceler */
#define TCCR4B_ICES4	( 1 << 6 )	/* Input Capture Edge Select */
#define TCCR4B_WGM43	( 1 << 4 )	/* Waveform Generation Mode */
#define TCCR4B_WGM42	( 1 << 3 )	/* Waveform Generation Mode */
#define TCCR4B_CS42		( 1 << 2 )	/* Clock Select */
#define TCCR4B_CS41		( 1 << 1 )	/* Clock Select */
#define TCCR4B_CS40		( 1 << 0 )	/* Clock Select */

#define TCCR5B			( 0x121 )	/* Timer/Counter 5 Control Register B */
#define TCCR5B_ICNC5	( 1 << 7 )	/* Input Capture Noise Canceler */
#define TCCR5B_ICES5	( 1 << 6 )	/* Input Capture Edge Select */
#define TCCR5B_WGM53	( 1 << 4 )	/* Waveform Generation Mode */
#define TCCR5B_WGM52	( 1 << 3 )	/* Waveform Generation Mode */
#define TCCR5B_CS52		( 1 << 2 )	/* Clock Select */
#define TCCR5B_CS51		( 1 << 1 )	/* Clock Select */
#define TCCR5B_CS50		( 1 << 0 )	/* Clock Select */

#define TCCR1C			( 0x82 )	/* Timer/Counter 1 Control Register C */
#define TCCR1C_FOC1A	( 1 << 7 )	/* Force Output Compare for Channel A */
#define TCCR1C_FOC1B	( 1 << 6 )	/* Force Output Compare for Channel B */
#define TCCR1C_FOC1C	( 1 << 5 )	/* Force Output Compare for Channel C */

#define TCCR3C			( 0x92 )	/* Timer/Counter 3 Control Register C */
#define TCCR3C_FOC3A	( 1 << 7 )	/* Force Output Compare for Channel A */
#define TCCR3C_FOC3B	( 1 << 6 )	/* Force Output Compare for Channel B */
#define TCCR3C_FOC3C	( 1 << 5 )	/* Force Output Compare for Channel C */

#define TCCR4C			( 0xA2 )	/* Timer/Counter 4 Control Register C */
#define TCCR3C_FOC4A	( 1 << 7 )	/* Force Output Compare for Channel A */
#define TCCR3C_FOC4B	( 1 << 6 )	/* Force Output Compare for Channel B */
#define TCCR3C_FOC4C	( 1 << 5 )	/* Force Output Compare for Channel C */

#define TCCR5C			( 0x122 )	/* Timer/Counter 5 Control Register C */
#define TCCR5C_FOC5A	( 1 << 7 )	/* Force Output Compare for Channel A */
#define TCCR5C_FOC5B	( 1 << 6 )	/* Force Output Compare for Channel B */
#define TCCR5C_FOC5C	( 1 << 5 )	/* Force Output Compare for Channel C */

#define TCNT1H			( 0x85 )	/* Timer/Counter 1 H */
#define TCNT1L			( 0x84 )	/* Timer/Counter 1 L */
#define TCNT1			( 0x84 )	/* Timer/Counter 1 */

#define TCNT3H			( 0x95 )	/* Timer/Counter 3 H */
#define TCNT3L			( 0x94 )	/* Timer/Counter 3 L */

#define TCNT4H			( 0xA5 )	/* Timer/Counter 4 H */
#define TCNT4L			( 0xA4 )	/* Timer/Counter 4 L */

#define TCNT5H			( 0x125 )	/* Timer/Counter 5 H */
#define TCNT5L			( 0x124 )	/* Timer/Counter 5 L */

#define OCR1AH			( 0x89 )	/* Output Compare Register 1 A H */
#define OCR1AL			( 0x88 )	/* Output Compare Register 1 A L */
#define OCR1A			( 0x88 )	/* Output Compare Register 1 A   */

#define OCR1BH			( 0x8B )	/* Output Compare Register 1 B H */
#define OCR1BL			( 0x8A )	/* Output Compare Register 1 B L */

#define OCR1CH			( 0x8D )	/* Output Compare Register 1 C H */
#define OCR1CL			( 0x8C )	/* Output Compare Register 1 C L */

#define OCR3AH			( 0x99 )	/* Output Compare Register 3 A H */
#define OCR3AL			( 0x98 )	/* Output Compare Register 3 A L */

#define OCR3BH			( 0x9B )	/* Output Compare Register 3 B H */
#define OCR3BL			( 0x9A )	/* Output Compare Register 3 B L */

#define OCR3CH			( 0x9D )	/* Output Compare Register 3 C H */
#define OCR3CL			( 0x9C )	/* Output Compare Register 3 C L */

#define OCR4AH			( 0xA9 )	/* Output Compare Register 4 A H */
#define OCR4AL			( 0xA8 )	/* Output Compare Register 4 A L */

#define OCR4BH			( 0xAA )	/* Output Compare Register 4 B H */
#define OCR4BL			( 0xAB )	/* Output Compare Register 4 B L */

#define OCR4CH			( 0xAD )	/* Output Compare Register 4 C H */
#define OCR4CL			( 0xAC )	/* Output Compare Register 4 C L */

#define OCR5AH			( 0x129 )	/* Output Compare Register 5 A H */
#define OCR5AL			( 0x128 )	/* Output Compare Register 5 A L */

#define OCR5BH			( 0x12B )	/* Output Compare Register 5 B H */
#define OCR5BL			( 0x12A )	/* Output Compare Register 5 B L */

#define OCR5CH			( 0x12D )	/* Output Compare Register 5 C H */
#define OCR5CL			( 0x12C )	/* Output Compare Register 5 C L */

#define ICR1H			( 0x87 )	/* Input Capture Register 1 H */
#define ICR1L			( 0x86 )	/* Input Capture Register 1 L */

#define ICR3H			( 0x97 )	/* Input Capture Register 3 H */
#define ICR3L			( 0x96 )	/* Input Capture Register 3 L */

#define ICR4H			( 0xA7 )	/* Input Capture Register 4 H */
#define ICR4L			( 0xA6 )	/* Input Capture Register 4 L */

#define ICR5H			( 0x127 )	/* Input Capture Register 5 H */
#define ICR5L			( 0x126 )	/* Input Capture Register 5 L */

#define TIMSK1			( 0x6F )	/* Timer/Counter 1 Interrupt Mask Register */
#define TIMSK1_ICIE1	( 1 << 5 )	/* Timer/Counter 1, Input Capture Interrupt Enable */
#define TIMSK1_OCIE1C	( 1 << 3 )	/* Timer/Counter 1, Output Compare C Match Interrupt Enable */
#define TIMSK1_OCIE1B	( 1 << 2 )	/* Timer/Counter 1, Output Compare B Match Interrupt Enable */
#define TIMSK1_OCIE1A	( 1 << 1 )	/* Timer/Counter 1, Output Compare A Match Interrupt Enable */
#define TIMSK1_TOIE1	( 1 << 0 )	/* Timer/Counter 1, Overflow Interrupt Enable */


#define TIMSK3			( 0x71 )	/* Timer/Counter 3 Interrupt Mask Register */
#define TIMSK3_ICIE3	( 1 << 5 )	/* Timer/Counter 3, Input Capture Interrupt Enable */
#define TIMSK3_OCIE3C	( 1 << 3 )	/* Timer/Counter 3, Output Compare C Match Interrupt Enable */
#define TIMSK3_OCIE3B	( 1 << 2 )	/* Timer/Counter 3, Output Compare B Match Interrupt Enable */
#define TIMSK3_OCIE3A	( 1 << 1 )	/* Timer/Counter 3, Output Compare A Match Interrupt Enable */
#define TIMSK3_TOIE3	( 1 << 0 )	/* Timer/Counter 3, Overflow Interrupt Enable */

#define TIMSK4			( 0x72 )	/* Timer/Counter 4 Interrupt Mask Register */
#define TIMSK4_ICIE4	( 1 << 5 )	/* Timer/Counter 4, Input Capture Interrupt Enable */
#define TIMSK4_OCIE4C	( 1 << 3 )	/* Timer/Counter 4, Output Compare C Match Interrupt Enable */
#define TIMSK4_OCIE4B	( 1 << 2 )	/* Timer/Counter 4, Output Compare B Match Interrupt Enable */
#define TIMSK4_OCIE4A	( 1 << 1 )	/* Timer/Counter 4, Output Compare A Match Interrupt Enable */
#define TIMSK4_TOIE4	( 1 << 0 )	/* Timer/Counter 4, Overflow Interrupt Enable */

#define TIMSK5			( 0x73 )	/* Timer/Counter 5 Interrupt Mask Register */
#define TIMSK5_ICIE5	( 1 << 5 )	/* Timer/Counter 5, Input Capture Interrupt Enable */
#define TIMSK5_OCIE5C	( 1 << 3 )	/* Timer/Counter 5, Output Compare C Match Interrupt Enable */
#define TIMSK5_OCIE5B	( 1 << 2 )	/* Timer/Counter 5, Output Compare B Match Interrupt Enable */
#define TIMSK5_OCIE5A	( 1 << 1 )	/* Timer/Counter 5, Output Compare A Match Interrupt Enable */
#define TIMSK5_TOIE5	( 1 << 0 )	/* Timer/Counter 5, Overflow Interrupt Enable */

#define TIFR1			( 0x36 )	/* Timer/Counter 1 Interrupt Flag Register */
#define TIFR1_ICF1		( 1 << 5 )	/* Timer/Counter 1, Input Capture Flag */
#define TIFR1_OCF1C		( 1 << 3 )	/* Timer/Counter 1, Output Compare C Match Flag */
#define TIFR1_OCF1B		( 1 << 2 )	/* Timer/Counter 1, Output Compare B Match Flag */
#define TIFR1_OCF1A		( 1 << 1 )	/* Timer/Counter 1, Output Compare A Match Flag */
#define TIFR1_TOV1		( 1 << 0 )	/* Timer/Counter 1, Overflow Interrupt Enable */

#define TIFR3			( 0x38 )	/* Timer/Counter 3 Interrupt Flag Register */
#define TIFR3_ICF3		( 1 << 5 )	/* Timer/Counter 3, Input Capture Flag */
#define TIFR3_OCF3C		( 1 << 3 )	/* Timer/Counter 3, Output Compare C Match Flag */
#define TIFR3_OCF3B		( 1 << 2 )	/* Timer/Counter 3, Output Compare B Match Flag */
#define TIFR3_OCF3A		( 1 << 1 )	/* Timer/Counter 3, Output Compare A Match Flag */
#define TIFR3_TOV3		( 1 << 0 )	/* Timer/Counter 3, Overflow Interrupt Enable */

#define TIFR4			( 0x39 )	/* Timer/Counter 4 Interrupt Flag Register */
#define TIFR4_ICF4		( 1 << 5 )	/* Timer/Counter 4, Input Capture Flag */
#define TIFR4_OCF4C		( 1 << 3 )	/* Timer/Counter 4, Output Compare C Match Flag */
#define TIFR4_OCF4B		( 1 << 2 )	/* Timer/Counter 4, Output Compare B Match Flag */
#define TIFR4_OCF4A		( 1 << 1 )	/* Timer/Counter 4, Output Compare A Match Flag */
#define TIFR4_TOV4		( 1 << 0 )	/* Timer/Counter 4, Overflow Interrupt Enable */

#define TIFR5			( 0x3A )	/* Timer/Counter 5 Interrupt Flag Register */
#define TIFR5_ICF5		( 1 << 5 )	/* Timer/Counter 5, Input Capture Flag */
#define TIFR5_OCF5C		( 1 << 3 )	/* Timer/Counter 5, Output Compare C Match Flag */
#define TIFR5_OCF5B		( 1 << 2 )	/* Timer/Counter 5, Output Compare B Match Flag */
#define TIFR5_OCF5A		( 1 << 1 )	/* Timer/Counter 5, Output Compare A Match Flag */
#define TIFR5_TOV5		( 1 << 0 )	/* Timer/Counter 5, Overflow Interrupt Enable */


/* TIMER 2 */
#define TCCR2A			( 0xB0 )	/* Timer/Counter 2 Control Register A */
#define TCCR2A_COM2A1	( 1 << 7 )	/* Compare Match Output A Mode */
#define TCCR2A_COM2A0	( 1 << 6 )	/* Compare Match Output A Mode */
#define TCCR2A_COM2B1	( 1 << 5 )	/* Compare Match Output B Mode */
#define TCCR2A_COM2B0	( 1 << 4 )	/* Compare Match Output B Mode */
#define TCCR2A_WGM21	( 1 << 1 )	/* Waveform Generation Mode */
#define TCCR2A_WGM20	( 1 << 0 )	/* Waveform Generation Mode */

#define TCCR2B			( 0xB1 )	/* Timer/Counter 2 Control Register B */
#define TCCR2B_FOC2A	( 1 << 7 )	/* Force Output Compare A */
#define TCCR2B_FOC2B	( 1 << 6 )	/* Force Output Compare B */
#define TCCR2B_WGM22	( 1 << 3 )	/* Waveform Generation Mode */
#define TCCR2B_CS22		( 1 << 2 )	/* Clock Select */
#define TCCR2B_CS21		( 1 << 1 )	/* Clock Select */
#define TCCR2B_CS20		( 1 << 0 )	/* Clock Select */

#define TCNT2			( 0xB2 )	/* Timer/Counter 2 */

#define OCR2A			( 0xB3 )	/* Output Compare Register 2 A */
#define OCR2B			( 0xB4 )	/* Output Compare Register 2 B */

#define ASSR			( 0xB6 )	/* Asynchronous Status Register */
#define ASSR_EXCLK		( 1 << 6 )	/* Enable External Clock Input */
#define ASSR_AS2		( 1 << 5 )	/* Asynchronous Timer/Counter 2 */
#define ASSR_OCR2AUB	( 1 << 4 )	/* Output Compare Register 2 Update Busy */
#define ASSR_OCR2BUB	( 1 << 3 )	/* Output Compare Register 2 Update Busy */
#define ASSR_TCR2AUB	( 1 << 2 )	/* Timer/Counter Control Register 2 Update Busy */
#define ASSR_TCR2BUB	( 1 << 1 )	/* Timer/Counter Control Register 2 Update Busy */

#define TIMSK2			( 0x70 )	/* Timer/Counter 2 Interrupt Mask Register */
#define TIMSK2_OCIE2B	( 1 << 2 )	/* Timer/Counter 2 Output Compare Match B Interrupt Enable */
#define TIMSK2_OCIE2A	( 1 << 1 )	/* Timer/Counter 2 Output Compare Match A Interrupt Enable */
#define TIMSK2_TOIE2	( 1 << 0 )	/* Timer/Counter 2 Overflow Interrupt Enable */

#define TIFR2			( 0x37 )	/* Timer/Counter 2 Interrupt Flag Register */
#define TIFR2_OCF2B		( 1 << 2 )	/* Output Compare Flag 2 B */
#define TIFR2_OCF2A		( 1 << 1 )	/* Output Compare Flag 2 A */
#define TIFR2_TOV2		( 1 << 0 )	/* Timer/Counter 2 Overflow Flag */

#define GTCCR			( 0x43 )	/* General Timer/Counter Control Register */
#define GTCCR_TSM		( 1 << 7 )	/* Timer/Counter Synchronization Mode */ 
#define GTCCR_PSRASY	( 1 << 1 )	/* Prescaler Reset Timer/Counter 2 */
#define GTCCR_PSRSYNC	( 1 << 0 )	/* Prescaler Reset for Synchronous Timer/Counters */

/* UART */
#define UDR0			( 0xC6 )	/* USART I/O Data Register 0 */
#define UDR1			( 0xCE )	/* USART I/O Data Register 1 */
#define UDR2			( 0xD6 )	/* USART I/O Data Register 2 */
#define UDR3			( 0x136 )	/* USART I/O Data Register 3 */

#define UCSR0A			( 0xC0 )	/* USART Control and Status Register 0 A */
#define UCSR0A_RXC0		( 1 << 7 )	/* USART Receive Complete */
#define UCSR0A_TXC0		( 1 << 6 )	/* USART Transmit Complete */
#define UCSR0A_UDRE0	( 1 << 5 )	/* USART Data Register Empty */
#define UCSR0A_FE0		( 1 << 4 )	/* Frame Error */
#define UCSR0A_DOR0		( 1 << 3 )	/* Data OverRun */
#define UCSR0A_UPE0		( 1 << 2 )	/* USART Parity Error */
#define UCSR0A_U2X0		( 1 << 1 )	/* Double the USART Transmission Speed */
#define UCSR0A_MPCM0	( 1 << 0 )	/* Multi-processor Communication Mode */

#define UCSR1A			( 0xC8 )	/* USART Control and Status Register 1 A */
#define UCSR1A_RXC1		( 1 << 7 )	/* USART Receive Complete */
#define UCSR1A_TXC1		( 1 << 6 )	/* USART Transmit Complete */
#define UCSR1A_UDRE1	( 1 << 5 )	/* USART Data Register Empty */
#define UCSR1A_FE1		( 1 << 4 )	/* Frame Error */
#define UCSR1A_DOR1		( 1 << 3 )	/* Data OverRun */
#define UCSR1A_UPE1		( 1 << 2 )	/* USART Parity Error */
#define UCSR1A_U2X1		( 1 << 1 )	/* Double the USART Transmission Speed */
#define UCSR1A_MPCM1	( 1 << 0 )	/* Multi-processor Communication Mode */

#define UCSR2A			( 0xD0 )	/* USART Control and Status Register 2 A */
#define UCSR2A_RXC2		( 1 << 7 )	/* USART Receive Complete */
#define UCSR2A_TXC2		( 1 << 6 )	/* USART Transmit Complete */
#define UCSR2A_UDRE2	( 1 << 5 )	/* USART Data Register Empty */
#define UCSR2A_FE2		( 1 << 4 )	/* Frame Error */
#define UCSR2A_DOR2		( 1 << 3 )	/* Data OverRun */
#define UCSR2A_UPE2		( 1 << 2 )	/* USART Parity Error */
#define UCSR2A_U2X2		( 1 << 1 )	/* Double the USART Transmission Speed */
#define UCSR2A_MPCM2	( 1 << 0 )	/* Multi-processor Communication Mode */

#define UCSR3A			( 0x130 )	/* USART Control and Status Register 3 A */
#define UCSR3A_RXC3		( 1 << 7 )	/* USART Receive Complete */
#define UCSR3A_TXC3		( 1 << 6 )	/* USART Transmit Complete */
#define UCSR3A_UDRE3	( 1 << 5 )	/* USART Data Register Empty */
#define UCSR3A_FE3		( 1 << 4 )	/* Frame Error */
#define UCSR3A_DOR3		( 1 << 3 )	/* Data OverRun */
#define UCSR3A_UPE3		( 1 << 2 )	/* USART Parity Error */
#define UCSR3A_U2X3		( 1 << 1 )	/* Double the USART Transmission Speed */
#define UCSR3A_MPCM3	( 1 << 0 )	/* Multi-processor Communication Mode */

#define UCSR0B			( 0xC1 )	/* USART Control and Status Register 0 B */
#define UCSR0B_RXCIE0	( 1 << 7 )	/* RX Complete Interrupt Enable 0 */
#define UCSR0B_TXCIE0	( 1 << 6 )	/* TX Complete Interrupt Enable 0 */
#define UCSR0B_UDRIE0	( 1 << 5 )	/* USART Data Register Empty Interrupt Enable 0 */
#define UCSR0B_RXEN0	( 1 << 4 )	/* Receiver Enable 0 */
#define UCSR0B_TXEN0	( 1 << 3 )	/* Transmitter Enable 0 */
#define UCSR0B_UCSZ02	( 1 << 2 )	/* Character Size 0 */
#define UCSR0B_RXB80	( 1 << 1 )	/* Receive Data Bit 8 0 */
#define UCSR0B_TXB80	( 1 << 0 )	/* Transmit Data Bit 8 0 */

#define UCSR1B			( 0xC9 )	/* USART Control and Status Register 1 B */
#define UCSR1B_RXCIE1	( 1 << 7 )	/* RX Complete Interrupt Enable 1 */
#define UCSR1B_TXCIE1	( 1 << 6 )	/* TX Complete Interrupt Enable 1 */
#define UCSR1B_UDRIE1	( 1 << 5 )	/* USART Data Register Empty Interrupt Enable 1 */
#define UCSR1B_RXEN1	( 1 << 4 )	/* Receiver Enable 1 */
#define UCSR1B_TXEN1	( 1 << 3 )	/* Transmitter Enable 1 */
#define UCSR1B_UCSZ12	( 1 << 2 )	/* Character Size 1 */
#define UCSR1B_RXB81	( 1 << 1 )	/* Receive Data Bit 8 1 */
#define UCSR1B_TXB81	( 1 << 0 )	/* Transmit Data Bit 8 1 */

#define UCSR2B			( 0xD1 )	/* USART Control and Status Register 2 B */
#define UCSR2B_RXCIE2	( 1 << 7 )	/* RX Complete Interrupt Enable 2 */
#define UCSR2B_TXCIE2	( 1 << 6 )	/* TX Complete Interrupt Enable 2 */
#define UCSR2B_UDRIE2	( 1 << 5 )	/* USART Data Register Empty Interrupt Enable 2 */
#define UCSR2B_RXEN2	( 1 << 4 )	/* Receiver Enable 2 */
#define UCSR2B_TXEN2	( 1 << 3 )	/* Transmitter Enable 2 */
#define UCSR2B_UCSZ22	( 1 << 2 )	/* Character Size 2 */
#define UCSR2B_RXB82	( 1 << 1 )	/* Receive Data Bit 8 2 */
#define UCSR2B_TXB82	( 1 << 0 )	/* Transmit Data Bit 8 2 */

#define UCSR3B			( 0x131 )	/* USART Control and Status Register 3 B */
#define UCSR3B_RXCIE3	( 1 << 7 )	/* RX Complete Interrupt Enable 3 */
#define UCSR3B_TXCIE3	( 1 << 6 )	/* TX Complete Interrupt Enable 3 */
#define UCSR3B_UDRIE3	( 1 << 5 )	/* USART Data Register Empty Interrupt Enable 3 */
#define UCSR3B_RXEN3	( 1 << 4 )	/* Receiver Enable 3 */
#define UCSR3B_TXEN3	( 1 << 3 )	/* Transmitter Enable 3 */
#define UCSR3B_UCSZ32	( 1 << 2 )	/* Character Size 3 */
#define UCSR3B_RXB83	( 1 << 1 )	/* Receive Data Bit 8 3 */
#define UCSR3B_TXB83	( 1 << 0 )	/* Transmit Data Bit 8 3 */

#define UCSR0C			( 0xC2 )	/* USART Control and Status Register 0 C */
#define UCSR0C_UMSEL01	( 1 << 7 )	/* USART Mode Select */
#define UCSR0C_UMSEL00	( 1 << 6 )	/* USART Mode Select */
#define UCSR0C_UPM01	( 1 << 5 )	/* Parity Mode */
#define UCSR0C_UPM00	( 1 << 4 )	/* Parity Mode */
#define UCSR0C_USBS0	( 1 << 3 )	/* Stop Bit Select */
#define UCSR0C_UCSZ01	( 1 << 2 )	/* Character Size */
#define UCSR0C_UCSZ00	( 1 << 1 )	/* Character Size */
#define UCSR0C_UCPOL0	( 1 << 0 )	/* Clock Polarity */

#define UCSR1C			( 0xCA )	/* USART Control and Status Register 1 C */
#define UCSR1C_UMSEL11	( 1 << 7 )	/* USART Mode Select */
#define UCSR1C_UMSEL10	( 1 << 6 )	/* USART Mode Select */
#define UCSR1C_UPM11	( 1 << 5 )	/* Parity Mode */
#define UCSR1C_UPM10	( 1 << 4 )	/* Parity Mode */
#define UCSR1C_USBS1	( 1 << 3 )	/* Stop Bit Select */
#define UCSR1C_UCSZ11	( 1 << 2 )	/* Character Size */
#define UCSR1C_UCSZ10	( 1 << 1 )	/* Character Size */
#define UCSR1C_UCPOL1	( 1 << 0 )	/* Clock Polarity */

#define UCSR2C			( 0xD2 )	/* USART Control and Status Register 2 C */
#define UCSR2C_UMSEL21	( 1 << 7 )	/* USART Mode Select */
#define UCSR2C_UMSEL20	( 1 << 6 )	/* USART Mode Select */
#define UCSR2C_UPM21	( 1 << 5 )	/* Parity Mode */
#define UCSR2C_UPM20	( 1 << 4 )	/* Parity Mode */
#define UCSR2C_USBS2	( 1 << 3 )	/* Stop Bit Select */
#define UCSR2C_UCSZ21	( 1 << 2 )	/* Character Size */
#define UCSR2C_UCSZ20	( 1 << 1 )	/* Character Size */
#define UCSR2C_UCPOL2	( 1 << 0 )	/* Clock Polarity */

#define UCSR3C			( 0x132 )	/* USART Control and Status Register 3 C */
#define UCSR3C_UMSEL31	( 1 << 7 )	/* USART Mode Select */
#define UCSR3C_UMSEL30	( 1 << 6 )	/* USART Mode Select */
#define UCSR3C_UPM31	( 1 << 5 )	/* Parity Mode */
#define UCSR3C_UPM30	( 1 << 4 )	/* Parity Mode */
#define UCSR3C_USBS3	( 1 << 3 )	/* Stop Bit Select */
#define UCSR3C_UCSZ31	( 1 << 2 )	/* Character Size */
#define UCSR3C_UCSZ30	( 1 << 1 )	/* Character Size */
#define UCSR3C_UCPOL3	( 1 << 0 )	/* Clock Polarity */

#define UBRR0H			( 0xC5 )	/* USART Baud Rate Registers 0 H */
#define UBRR0L			( 0xC4 )	/* USART Baud Rate Registers 0 L*/
#define UBRR1H			( 0xCD )	/* USART Baud Rate Registers 1 H */
#define UBRR1L			( 0xCC )	/* USART Baud Rate Registers 1 L*/
#define UBRR2H			( 0xD5 )	/* USART Baud Rate Registers 2 H */
#define UBRR2L			( 0xD4 )	/* USART Baud Rate Registers 2 L*/
#define UBRR3H			( 0x135 )	/* USART Baud Rate Registers 3 H */
#define UBRR3L			( 0x134 )	/* USART Baud Rate Registers 3 L*/


/* EEPROM */

/* Use 16 bit access to this register */
/* #define EEARH 		( 0x42 )	 * EEPROM Address Register H */
#define EEAR			( 0x41 )	/* EEPROM Address Register */
#define EEAR_EEAR11		( 1 << 11 )	/* Address Bit 11 */
#define EEAR_EEAR10		( 1 << 10 )	/* Address Bit 10 */
#define EEAR_EEAR9		( 1 << 9 )	/* Address Bit 9 */
#define EEAR_EEAR8		( 1 << 8 )	/* Address Bit 8 */
#define EEAR_EEAR7		( 1 << 7 )	/* Address Bit 7 */
#define EEAR_EEAR6		( 1 << 6 )	/* Address Bit 6 */
#define EEAR_EEAR5		( 1 << 5 )	/* Address Bit 5 */
#define EEAR_EEAR4		( 1 << 4 )	/* Address Bit 4 */
#define EEAR_EEAR3		( 1 << 3 )	/* Address Bit 3 */
#define EEAR_EEAR2		( 1 << 2 )	/* Address Bit 2 */
#define EEAR_EEAR1		( 1 << 1 )	/* Address Bit 1 */
#define EEAR_EEAR0		( 1 << 0 )	/* Address Bit 0 */

#define EEDR  			( 0x40 )	/* EEPROM Data Register */

#define EECR			( 0x3F )	/* EEPROM Control Register */
#define EECR_EEPM1		( 1 << 5 )	/* EEPROM Programming Mode Bits */
#define EECR_EEPM0		( 1 << 4 )	/* EEPROM Programming Mode Bits */
#define EECR_EERIE		( 1 << 3 )	/* EEPROM Ready Interrupt Enable */
#define EECR_EEMPE		( 1 << 2 )	/* EEPROM Master Programming Enable */
#define EECR_EEPE		( 1 << 1 )	/* EEPROM Programming Enable */
#define EECR_EERE		( 1 << 0 )	/* EEPROM Read Enable */

/* PORTS */
#define MCUCR			( 0x55 )	/* MCU Control Register */
#define MCUCR_JTD		( 1 << 7 )	/* JTAG Disable bit */
#define MCUCR_PUD		( 1 << 4 )	/* Pull-up Disable */
#define MCUCR_IVSEL		( 1 << 1 )	/* Interrupt Vector Select */
#define MCUCR_IVCE		( 1 << 0 )	/* Interrupt Vector Change Enable */

/* General defines for all Port registers */
#define BIT(n)			( 1 << n )

#define PORTA			( 0x22 )	/* Port A Data Register */
#define DDRA			( 0x21 )	/* Port A Data Direction Register */
#define PINA			( 0x20 )	/* Port A Input Pins Address */

#define PORTB			( 0x25 )	/* Port B Data Register */
#define DDRB			( 0x24 )	/* Port B Data Direction Register */
#define PINB			( 0x23 )	/* Port B Input Pins Address */

#define PORTC			( 0x28 )	/* Port C Data Register */
#define DDRC			( 0x27 )	/* Port C Data Direction Register */
#define PINC			( 0x26 )	/* Port C Input Pins Address */

#define PORTD			( 0x2B )	/* Port D Data Register */
#define DDRD			( 0x2A )	/* Port D Data Direction Register */
#define PIND			( 0x29 )	/* Port D Input Pins Address */

#define PORTE			( 0x2E )	/* Port E Data Register */
#define DDRE			( 0x2D )	/* Port E Data Direction Register */
#define PINE			( 0x2C )	/* Port E Input Pins Address */

#define PORTF			( 0x31 )	/* Port F Data Register */
#define DDRF			( 0x30 )	/* Port F Data Direction Register */
#define PINF			( 0x2F )	/* Port F Input Pins Address */

#define PORTG			( 0x34 )	/* Port G Data Register */
#define DDRG			( 0x33 )	/* Port G Data Direction Register */
#define PING			( 0x32 )	/* Port G Input Pins Address */

#define PORTH			( 0x102 )	/* Port H Data Register */
#define DDRH			( 0x101 )	/* Port H Data Direction Register */
#define PINH			( 0x100 )	/* Port H Input Pins Address */

#define PORTJ			( 0x105 )	/* Port J Data Register */
#define DDRJ			( 0x104 )	/* Port J Data Direction Register */
#define PINJ			( 0x103 )	/* Port J Input Pins Address */

#define PORTK			( 0x108 )	/* Port K Data Register */
#define DDRK			( 0x107 )	/* Port K Data Direction Register */
#define PINK			( 0x106 )	/* Port K Input Pins Address */

#define PORTL			( 0x10B )	/* Port L Data Register */
#define DDRL			( 0x10A )	/* Port L Data Direction Register */
#define PINL			( 0x109 )	/* Port L Input Pins Address */

/* Interrupts */
#define ISR_RESET			__vector_0
#define ISR_INT0			__vector_1
#define ISR_INT1			__vector_2
#define ISR_INT2			__vector_3
#define ISR_INT3			__vector_4
#define ISR_INT4			__vector_5
#define ISR_INT5			__vector_6
#define ISR_INT6			__vector_7
#define ISR_INT7			__vector_8
#define ISR_PCINT0			__vector_9
#define ISR_PCINT1			__vector_10
#define ISR_PCINT2			__vector_11
#define ISR_WDT				__vector_12
#define ISR_TIMER2_COMPA	__vector_13
#define ISR_TIMER2_COMPB	__vector_14
#define ISR_TIMER2_OVF		__vector_15
#define ISR_TIMER1_CAPT		__vector_16
#define ISR_TIMER1_COMPA	__vector_17
#define ISR_TIMER1_COMPB	__vector_18
#define ISR_TIMER1_COMPC	__vector_19
#define ISR_TIMER1_OVF		__vector_20
#define ISR_TIMER0_COMPA	__vector_21
#define ISR_TIMER0_COMPB	__vector_22
#define ISR_TIMER0_OVF		__vector_23
#define ISR_SPI_STC			__vector_24
#define ISR_USART0_RX		__vector_25
#define ISR_USART0_UDRE		__vector_26
#define ISR_USART0_TX		__vector_27
#define ISR_ANALOG_COMP		__vector_28
#define ISR_ADC				__vector_29
#define ISR_EE_READY		__vector_30
#define ISR_TIMER3_CAPT		__vector_31
#define ISR_TIMER3_COMPA	__vector_32
#define ISR_TIMER3_COMPB	__vector_33
#define ISR_TIMER3_COMPC	__vector_34
#define ISR_TIMER3_OVF		__vector_35
#define ISR_USART1_RX		__vector_36
#define ISR_USART1_UDRE		__vector_37
#define ISR_USART1_TX		__vector_38
#define ISR_TWI				__vector_39
#define ISR_SPM_READY		__vector_40
#define ISR_TIMER4_CAPT		__vector_41
#define ISR_TIMER4_COMPA	__vector_42
#define ISR_TIMER4_COMPB	__vector_43
#define ISR_TIMER4_COMPC	__vector_44
#define ISR_TIMER4_OVF		__vector_45
#define ISR_TIMER5_CAPT		__vector_46
#define ISR_TIMER5_COMPA	__vector_47
#define ISR_TIMER5_COMPB	__vector_48
#define ISR_TIMER5_COMPC	__vector_49
#define ISR_TIMER5_OVF		__vector_50
#define ISR_USART2_RX		__vector_51
#define ISR_USART2_UDRE		__vector_52
#define ISR_USART2_TX		__vector_53
#define ISR_USART3_RX		__vector_54
#define ISR_USART3_UDRE		__vector_55
#define ISR_USART3_TX		__vector_56

#endif /* ATMEGA2560_H_ */