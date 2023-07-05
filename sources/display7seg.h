/* ***************************************************************** */
/* File name:        display7seg.h                                   */
/* File description: Header file containing the functions/methods    */
/*                   interfaces for setting up and manipulating      */
/*                   the 4 7-segment displays from the hardware kit  */
/* Author name:      Igor B Teixeira                                 */
/*                   Matheus S Sano                                  */
/* Creation date:    18abr2022                                       */
/* Revision date:    10mai2022                                       */
/* ***************************************************************** */

#ifndef SOURCES_DISPLAY7SEG_H_
#define SOURCES_DISPLAY7SEG_H_


/* *************************************************** */
/* Method name:        display7seg_init                */
/* Method description: Initialize the pins used to     */
/*                     control the 7-segment displays  */
/* Input params:       n/a                             */
/* Output params:      n/a                             */
/* *************************************************** */
void display7seg_init(void);



/* ******************************************************* */
/* Method name:        display7seg_writeSymbol             */
/* Method description: Write a character on one of         */
/*                     the displays.                       */
/* Input params:       ucDisplay                           */
/*                     indica qual display que recebera    */
/*                     o valor (1 = display dos milhares,  */
/*                     2 = display das centenas,           */
/*                     3 = display das dezenas,            */
/*                     4 = display das unidades)           */
/*                                                         */
/*                     ucValue                             */
/*                     indica qual caractere sera escrito  */
/*                     no display (0-9 = numeros de 0 a 9  */
/*                     com ponto decimal apagado,          */
/*                     10-19 = numeros de 0 a 9 com ponto  */
/*                     decimal aceso, 20 = ponto decimal   */
/*                     aceso, 21 = todos os segmentos e    */
/*                     ponto decimal apagados, 22 = todos  */
/*                     os segmentos e ponto decimal acesos)*/
/* Output params:      n/a                                 */
/* ******************************************************* */
void display7seg_writeSymbol(unsigned char ucDisplay, unsigned char ucValue);



/* ****************************************************** */
/* Method name: 	   display7seg_slideDummy		      */
/* Method description: Write a dummy hard coded text with */
/*                     a slide movement                   */
/* Input params:	   n/a                                */
/* Output params:	   n/a 							      */
/* ****************************************************** */
void display7seg_slideDummy(void);




/* ****************************************************** */
/* Method name: 	   display7seg_circleWaiting		  */
/* Method description: Make a circular movement with      */
/*                     a light trace at the displays      */
/* Input params:	   int iDurationTimeInS:              */
/*                     Duration time (in sec) of the      */
/*                     animation                          */
/* Output params:	   n/a 							      */
/* ****************************************************** */
void display7seg_circleWaiting(int iDurationTimeInS);

/* ******************************************************* */
/* Method name:        display7seg_interruption            */
/* Method description: A cada interrupcao um display eh    */
/*                     atualizado na ordem do 1 ao 4.      */
/* Input params:       void                                */
/* Output params:      n/a                                 */
/* ******************************************************* */
void display7seg_interruption(void);

/* ****************************************************** */
/* Method name: 	   display7seg_clear		          */
/* Method description: Clear all displays 7 seg           */
/*                                                        */
/* Input params:	   n/a                                */
/* Output params:	   n/a 							      */
/* ****************************************************** */
void display7seg_clear(void);



/* ****************************************************** */
/* Method name: 	   display7seg_test		              */
/* Method description: Turn on all displays 7 seg         */
/*                     for 2 sec                          */
/*                                                        */
/* Input params:	   n/a                                */
/* Output params:	   n/a 							      */
/* ****************************************************** */
void display7seg_test(void);


/* ****************************************************** */
/* Method name: 	   display7seg_enable		          */
/* Method description: enable write on the displays       */
/*                                                        */
/* Input params:	   n/a                                */
/* Output params:	   n/a 							      */
/* ****************************************************** */
void display7seg_enable(void);


/* ****************************************************** */
/* Method name: 	   display7seg_disable		          */
/* Method description: disable write on the displays      */
/*                                                        */
/* Input params:	   n/a                                */
/* Output params:	   n/a 							      */
/* ****************************************************** */
void display7seg_disable(void);


#endif /* SOURCES_DISPLAY7SEG_H_ */
