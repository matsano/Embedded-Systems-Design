/* ***************************************************************** */
/* File name:		 regManager.c					     			 */
/* File description: File dedicated to acess a register and perform  */
/*                   a write or a read to a pin.                     */
/* Author name:      Igor B Teixeira                                 */
/*                   Matheus S Sano                                  */
/* Creation date:    13abr2022										 */
/* Revision date:    13abr2022										 */
/* ***************************************************************** */

#include "board.h"
#include "regManager.h"

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
int acessRegister(int *iRegister,  int iEscolha, char cMode, int iValue){


	/* Se o pino iEscolha for saida (1), podemos realizar a escrita */
	if ( ((iRegister == (int*)&GPIOA_PDDR) || (1 == ((GPIOA_PDDR >> iEscolha) & 1))) && ('w' == cMode)){

		if (1 == iValue){
			*iRegister |= 1 << iEscolha;
		}
		else if (0 == iValue){
			*iRegister &= ~(1 << iEscolha);
		}
		return 0;
	}

	/* Se o pino iEscolha for entrada (0), podemos realizar a leitura */
	else if ((0 == ((GPIOA_PDDR >> iEscolha) & 1)) && ('r' == cMode)){

		return !(1 == ((*iRegister >> iEscolha) & 1));
	}

	return -1;
}



/* ********************************************************** */
/* Method name: 	   writeRegister	         	          */
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
int writeRegister(int *iRegister, int iPin, int iValue){

	if (1 == iValue){
		*iRegister |= 1 << iPin;
	}
	else if (0 == iValue){
		*iRegister &= ~(1 << iPin);
	}

	return 0;
}
