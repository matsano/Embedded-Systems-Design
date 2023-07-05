/* *********************************************************************** */
/* File name:		 tacometro.h						 		           */
/* File description: Header file containing the prototypes of the          */
/*                   functions used to configure and manipulate the        */
/*                   encoder's cooler                                      */
/* Author name:      Igor B Teixeira                                       */
/*                   Matheus S Sano                                        */
/* Creation date:    05mai2022										       */
/* Revision date:    10mai2022										       */
/* *********************************************************************** */

#ifndef SOURCES_TACOMETRO_H_
#define SOURCES_TACOMETRO_H_

/* *************************************************** */
/* Method name:        tachometer_init                 */
/* Method description: Initialize the tachometer and   */
/*                     configurate TPM0 as timer with  */
/*                     external clock                  */
/* Input params:       n/a                             */
/* Output params:      n/a                             */
/* *************************************************** */
void tachometer_init(void);


unsigned int tachometer_readSensor(unsigned int uiPeriod);

#endif /* SOURCES_TACOMETRO_H_ */
