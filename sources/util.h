/* ***************************************************************** */
/* File name:        util.h                                          */
/* File description: Header file containing the function/methods     */
/*                   prototypes of util.c                            */
/*                   Those delays were tested under the following:   */
/*                   core clock @ 40MHz                              */
/*                   bus clock @ 20MHz                               */
/* Author name:      dloubach                                        */
/*                   Igor B Teixeira                                 */
/*                   Matheus S Sano                                  */
/* Creation date:    09jan2015                                       */
/* Revision date:    31mar2022                                       */
/* ***************************************************************** */

#ifndef UTIL_H
#define UTIL_H

/* ************************************************ */
/* Method name:        util_genDelay088us           */
/* Method description: generates ~ 088 micro sec    */
/* Input params:       n/a                          */
/* Output params:      n/a                          */
/* ************************************************ */
void util_genDelay088us(void);


/* ************************************************ */
/* Method name:        util_genDelay250us           */
/* Method description: generates ~   250 micro sec  */
/* Input params:       n/a                          */
/* Output params:      n/a                          */
/* ************************************************ */
void util_genDelay250us(void);


/* ************************************************ */
/* Method name:        util_genDelay1ms             */
/* Method description: generates ~   1 mili sec     */
/* Input params:       n/a                          */
/* Output params:      n/a                          */
/* ************************************************ */
void util_genDelay1ms(void);


/* ************************************************ */
/* Method name:        util_genDelay10ms            */
/* Method description: generates ~   10 mili sec    */
/* Input params:       n/a                          */
/* Output params:      n/a                          */
/* ************************************************ */
void util_genDelay10ms(void);

/* ************************************************ */
/* Method name:        util_genDelay100ms           */
/* Method description: generates ~   100 mili sec   */
/* Input params:       n/a                          */
/* Output params:      n/a                          */
/* ************************************************ */
void util_genDelay100ms(void);

/* ************************************************ */
/* Method name:        util_genDelay500ms           */
/* Method description: generates ~   500 mili sec   */
/* Input params:       n/a                          */
/* Output params:      n/a                          */
/* ************************************************ */
void util_genDelay500ms(void);

/* ************************************************ */
/* Method name:        util_genDelay1000ms          */
/* Method description: generates ~   1000 mili sec  */
/* Input params:       n/a                          */
/* Output params:      n/a                          */
/* ************************************************ */
void util_genDelay1000ms(void);

/* ****************************************************** */
/* Method name:        util_putStringSerial               */
/* Method description: Implementação de comunicação       */
/*                     por meio da transmissao            */
/*                     serial de dados                    */
/* Input params:       cString                            */
/*                     Caracter que deve ser transmitido  */
/*                     de forma serial                    */
/* Output params:      n/a                                */
/* ****************************************************** */
void util_putStringSerial(char* cString);

/* ************************************************ */
/* Method name:        util_putSerialLineFeed       */
/* Method description: Implementar uma quebra de    */
/*                     linha na transmissao serial  */
/*                     de dados                     */
/* Input params:       n/a                          */
/* Output params:      n/a                          */
/* ************************************************ */
void util_putSerialLineFeed(void);


#endif /* UTIL_H */
