/* ***************************************************************** */
/* File name:        ledrgb.h                                        */
/* File description: Header file containing the functions/methods    */
/*                   interfaces to the hardware abstraction layer    */
/*                   related RGB LED from the FRDM-KL25Z board       */
/*                   controller.                                     */
/*                                                                   */
/* Author name:      Rodrigo M Bacurau                               */
/*                   Igor B Teixeira                                 */
/*                   Matheus S Sano                                  */
/* Creation date:    26fev2020                                       */
/* Revision date:    04abr2022                                       */
/* ***************************************************************** */

#ifndef SOURCES_LEDRGB_H_
#define SOURCES_LEDRGB_H_


/* ************************************************ */
/* Method name: 	   ledrgb_init	         		*/
/* Method description: Initialize the RGB LED device*/
/* Input params:	   n/a                          */
/* Output params:	   n/a 							*/
/* ************************************************ */
void ledrgb_init(void);

/* ************************************************ */
/* Method name: 	   ledrgb_write	         		*/
/* Method description: Write the color of the RGB   */
/*                     led.REMARKS LEDS are inverted*/
/* Input params:	   ucRGBColor 0..7 (0 = off     */
/*                     1 = red                      */
/*                     2 = green                    */
/*                     3 = red + green              */
/*                     4 = blue                     */
/*                     5 = blue + red               */
/*                     6 = blue + green             */
/*                     7 = blue + green + red)      */
/* Output params:	   n/a 							*/
/* ************************************************ */
void ledrgb_write(unsigned char ucRGBColor);

#endif /* SOURCES_LEDRGB_H_ */
