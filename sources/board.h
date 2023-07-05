/* ************************************************************************ */
/* File name:        board.h                                                */
/* File description: Header file containing the peripherals mapping         */
/*                     of the peripheral board for the ES670 hardware       */
/*                                                                          */
/* Author name:      Rodrigo M Bacurau                                      */
/*                   Igor B Teixeira                                        */
/*                   Matheus S Sano                                         */
/* Creation date:    26fev2020                                              */
/* Revision date:    05mai2022                                              */
/* ************************************************************************ */

#ifndef SOURCES_BOARD_H_
#define SOURCES_BOARD_H_

/* system includes */
#include <MKL25Z4.h>

/* FDRMKL25Z RGB LED pins defintions */
#define RED_LED_PORT_BASE_PNT    PORTB /* peripheral port base pointer */
#define RED_LED_GPIO_BASE_PNT    PTB   /* peripheral gpio base pointer */
#define RED_LED_PIN		         (uint32_t) 18u
#define GREEN_LED_PORT_BASE_PNT  PORTB /* peripheral port base pointer */
#define GREEN_LED_GPIO_BASE_PNT  PTB   /* peripheral gpio base pointer */
#define GREEN_LED_PIN	         (uint32_t) 19u
#define BLUE_LED_PORT_BASE_PNT   PORTD /* peripheral port base pointer */
#define BLUE_LED_GPIO_BASE_PNT   PTD   /* peripheral gpio base pointer */
#define BLUE_LED_PIN	         (uint32_t) 1u

#define S1_LED1_PORT_BASE_PNT    PORTA /* peripheral port base pointer */
#define S1_LED1_GPIO_BASE_PNT    PTA   /* peripheral gpio base pointer */
#define S1_LED1_PIN	             (uint32_t) 1u

#define S2_LED2_PORT_BASE_PNT    PORTA /* peripheral port base pointer */
#define S2_LED2_GPIO_BASE_PNT    PTA   /* peripheral gpio base pointer */
#define S2_LED2_PIN	             (uint32_t) 2u

#define S3_LED3_PORT_BASE_PNT    PORTA /* peripheral port base pointer */
#define S3_LED3_GPIO_BASE_PNT    PTA   /* peripheral gpio base pointer */
#define S3_LED3_PIN	             (uint32_t) 4u

#define S4_LED4_PORT_BASE_PNT    PORTA /* peripheral port base pointer */
#define S4_LED4_GPIO_BASE_PNT    PTA   /* peripheral gpio base pointer */
#define S4_LED4_PIN	             (uint32_t) 5u

#define CLOCK_PORTA_PIN			 (uint32_t) 9u  /* bits do registrador que libera os clocks */
#define CLOCK_PORTB_PIN			 (uint32_t) 10u
#define CLOCK_PORTC_PIN			 (uint32_t) 11u
#define CLOCK_PORTD_PIN			 (uint32_t) 12u
#define CLOCK_PORTE_PIN			 (uint32_t) 13u

#define PCR_MUX_0				 (uint32_t) 8u /* bits do registrador que configura o MUX do pino */
#define PCR_MUX_1				 (uint32_t) 9u
#define PCR_MUX_2				 (uint32_t) 10u

/* TPM pins defintions */
#define CLOCK_TPM0               (uint32_t) 24u /* bits do registrador que libera os clocks */
#define CLOCK_TPM1               (uint32_t) 25u

#define TPM_PS_0                 (uint32_t) 0u /* bits do registrador que configura o divisor de clock do contador */
#define TPM_PS_1                 (uint32_t) 1u
#define TPM_PS_2                 (uint32_t) 2u

#define TPM_SOURCE_0             (uint32_t) 24u /* bits do registrador que configura a fonte do clock do contador */
#define TPM_SOURCE_1             (uint32_t) 25u

#define TPM_CMOD_0               (uint32_t) 3u /* bits do registrador que configura o CMOD do contador */
#define TPM_CMOD_1               (uint32_t) 4u

#define TPM_CPWMS                (uint32_t) 5u /* bits do registrador que configura o CPWMS do contador */

#define TPM_MSB                  (uint32_t) 5u /* bits do registrador que configura o modo do canal (Edge e Level) */
#define TPM_MSA                  (uint32_t) 4u
#define TPM_ELSB                 (uint32_t) 3u
#define TPM_ELSA                 (uint32_t) 2u

#define TPM0CLKSEL               (uint32_t) 24u /* bit do registrador que escolhe o pino de entrada de clock do TPM0 */



/* 				LCD definitions 				*/

/* LCD Register Selector
 * Used as register selector input
 * When (LCD_RS = LCD_RS_HIGH) => DATA register is selected
 * When (LCD_RS = LCD_RS_LOW)  => INSTRUCTION register is selected
*/
#define LCD_PORT_BASE_PNT		PORTC							/* peripheral port base pointer */
#define LCD_GPIO_BASE_PNT		PTC								/* peripheral gpio base pointer */

#define LCD_RS_PIN				8U								/* register selector */
#define LCD_RS_DIR				kGpioDigitalOutput
#define LCD_RS_ALT				kPortMuxAsGpio

#define LCD_ENABLE_PIN			9U								/* enable pin */
#define LCD_ENABLE_DIR			kGpioDigitalOutput
#define LCD_ENABLE_ALT			kPortMuxAsGpio

#define LCD_RS_HIGH				1U
#define LCD_RS_DATA				LCD_RS_HIGH

#define LCD_RS_LOW 				0U
#define LCD_RS_CMD   			LCD_RS_LOW

#define LCD_ENABLED				1U
#define LCD_DISABLED			0U

#define LCD_DATA_DIR			kGpioDigitalOutput				/* LCD data pins */
#define LCD_DATA_ALT			kPortMuxAsGpio

#define LCD_DATA_DB0_PIN		0U
#define LCD_DATA_DB1_PIN	    1u
#define LCD_DATA_DB2_PIN	    2u
#define LCD_DATA_DB3_PIN		3U
#define LCD_DATA_DB4_PIN		4U
#define LCD_DATA_DB5_PIN		5U
#define LCD_DATA_DB6_PIN		6U
#define LCD_DATA_DB7_PIN		7U
/* 				END OF LCD definitions 				*/



/*                 TEMPERATURE SENSOR DIODE DEFINITIONS           */
#define  THERMOMETER_PORT_BASE_PNT  PORTE                         /* peripheral port base pointer */
#define  THERMOMETER_GPIO_BASE_PNT  PTE                           /* peripheral gpio base pointer */
#define  THERMOMETER_PIN            21U                           /* thermometer pin */
#define  THERMOMETER_DIR            (GPIO_INPUT << TERMOMETER_PIN)
#define  THERMOMETER_ALT            0x00u
#define  CGC_CLOCK_ENABLED          0x1U
/*                 END OF TEMPERATURE SENSOR DIODE DEFINITIONS    */



#endif /* SOURCES_BOARD_H_ */
