/* ***************************************************************** */
/* File name:		 regManager.h					     			 */
/* File description: Header file containing the functions/methods    */
/*                   interfaces for acessing a register from the     */
/*                   hardware kit                                    */
/* File description: File dedicated to acess a register and perform  */
/*                   a write or a read to a pin.                     */
/* Author name:      Igor B Teixeira                                 */
/*                   Matheus S Sano                                  */
/* Creation date:    13abr2022										 */
/* Revision date:    13abr2022										 */
/* ***************************************************************** */

#ifndef SOURCES_REGMANAGER_H_
#define SOURCES_REGMANAGER_H_

/* ********************************************************** */
/* Method name: 	   acessRegister	         	          */
/* Method description: Acessar o registrador, e realizar a    */
/*                     escrita caso o pino seja uma saida     */
/*                     ou realizar a leitura caso o pino      */
/*                     seja uma entrada.                      */
/* Input params:	   *iRegister                             */
/*                     eh o registrador do modulo GPIO        */
/*                                                            */
/*                     iEscolha                               */
/*                     eh o numero do LED que                 */
/*                     sera escrito (1, 2, 4 ou 5)            */
/*                                                            */
/*                     cMode (w = escrita                     */
/*                     r = leitura)                           */
/*                                                            */
/*                     iValor (0 = LED desligado              */
/*                     1 = LED ligado)                        */
/*                                                            */
/* Output params:	   n/a 							          */
/* ********************************************************** */
int acessRegister(int *iRegister,  int iEscolha, char cMode, int iValue);



/* ********************************************************** */
/* Method name: 	   writeRegisterLcd	         	          */
/* Method description: Acessar o registrador e realizar a    */
/*                     escrita no pino.                      */
/* Input params:	   *iRegister                             */
/*                     eh o registrador do modulo GPIO        */
/*                                                            */
/*                     iPin                                  */
/*                     eh o numero do pino que                */
/*                     sera escrito                           */
/*                                                            */
/*                     iValue                                 */
/*                     valor a ser escrito no pino            */
/*                                                            */
/* Output params:	   n/a 							          */
/* ********************************************************** */
int writeRegister(int *iRegister, int iPin, int iValue);

#endif /* SOURCES_REGMANAGER_H_ */
