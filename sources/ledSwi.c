/* ***************************************************************** */
/* File name:        ledSwi.c                                        */
/* File description: File dedicated to the hardware abstraction layer*/
/*                   related Buttons and LEDs from the FRDM-KL25Z    */
/*                   board.                                          */
/*                                                                   */
/* Author name:      Igor B Teixeira                                 */
/*                   Matheus S Sano                                  */
/*                                                                   */
/* Creation date:    28mar2022                                       */
/* Revision date:    04abr2022                                       */
/* ***************************************************************** */
#include <MKL25Z4.h>
#include "ledSwi.h"
#include "board.h"
#include "regManager.h"



/* *************************************************************** */
/* Method name: 	   initializeLedSwi	         	               */
/* Method description: Inicializa os pinos dos leds                */
/* 					   e botoes de acordo com a                    */
/* 					   escolha do usuario                          */
/* Input params:	   cPino1, cPino2, cPino3, cPino4 (b = botao   */
/*                     B = botao                                   */
/*                     l = LED                                     */
/*                     L = LED)                                    */
/*                                                                 */
/* Output params:	   n/a 							               */
/* *************************************************************** */
int initializeLedSwi(char cPino1, char cPino2, char cPino3, char cPino4){
	
	/* Libera o clock para o PORT A */
	writeRegister((int*)&SIM_SCGC5, CLOCK_PORTA_PIN, 1);

	/* Configura os MUX dos pinos do PORT A que serao GPIO */
	writeRegister((int*)&PORTA_PCR1, PCR_MUX_2, 0);
	writeRegister((int*)&PORTA_PCR1, PCR_MUX_1, 0);
	writeRegister((int*)&PORTA_PCR1, PCR_MUX_0, 1);

	writeRegister((int*)&PORTA_PCR2, PCR_MUX_2, 0);
	writeRegister((int*)&PORTA_PCR2, PCR_MUX_1, 0);
	writeRegister((int*)&PORTA_PCR2, PCR_MUX_0, 1);

	writeRegister((int*)&PORTA_PCR4, PCR_MUX_2, 0);
	writeRegister((int*)&PORTA_PCR4, PCR_MUX_1, 0);
	writeRegister((int*)&PORTA_PCR4, PCR_MUX_0, 1);

	writeRegister((int*)&PORTA_PCR5, PCR_MUX_2, 0);
	writeRegister((int*)&PORTA_PCR5, PCR_MUX_1, 0);
	writeRegister((int*)&PORTA_PCR5, PCR_MUX_0, 1);

	/* Limpa os registradores de dados */
	GPIOA_PDDR = 0;
	GPIOA_PDOR = 0;
	GPIOA_PSOR = 0;
	GPIOA_PCOR = 0;

	/* Configura cada pino como entrada ou saida */
	if ('l' == cPino1 || 'L' == cPino1){
		acessRegister((int*)&GPIOA_PDDR, 1, 'w', 1);
	}
	else if ('b' == cPino1 || 'B' == cPino1){
		acessRegister((int*)&GPIOA_PDDR, 1,'w',  0);
	}

	if ('l' == cPino2 || 'L' == cPino2){
		acessRegister((int*)&GPIOA_PDDR, 2,'w',  1);
	}
	else if ('b' == cPino2 || 'B' == cPino2){
		acessRegister((int*)&GPIOA_PDDR, 2,'w',  0);
	}

	if ('l' == cPino3 || 'L' == cPino3){
		acessRegister((int*)&GPIOA_PDDR, 4,'w',  1);
	}
	else if ('b' == cPino3 || 'B' == cPino3){
		acessRegister((int*)&GPIOA_PDDR, 4,'w',  0);
	}

	if ('l' == cPino4 || 'L' == cPino4){
		acessRegister((int*)&GPIOA_PDDR, 5,'w',  1);
	}
	else if ('b' == cPino4 || 'B' == cPino4){
		acessRegister((int*)&GPIOA_PDDR, 5,'w',  0);
	}

	return 0;
}

/* ************************************************ */
/* Method name: 	   readSwitch	         		*/
/* Method description: Adquiri o valor atual do pino */
/*                     escolhido                    */
/* Input params:	   iEscolha                     */
/*                     eh o numero do botao que     */
/*                     sera lido (1, 2, 3 ou 4)     */
/* Output params:	   n/a 							*/
/* ************************************************ */
int readSwitch(int iEscolha){

	// incrementa a posição do pino pois led3 = pino4 / led4 = pino5
	iEscolha += (3 <= iEscolha);

	return acessRegister((int*)&GPIOA_PDIR, iEscolha, 'r', 1);
	
}

/* ************************************************ */
/* Method name: 	   writeLed	         		    */
/* Method description: Escreve na saida o valor     */
/*                     desejado                     */
/* Input params:	   iEscolha                     */
/*                     eh o numero do LED que       */
/*                     sera escrito (1, 2, 3 ou 4)  */
/*                                                  */
/*                     iValor (0 = LED desligado    */
/*                     1 = LED ligado)              */
/* Output params:	   n/a 							*/
/* ************************************************ */
int writeLed(int iEscolha, int iValor){

	// incrementa a posição do pino pois led3 = pino4 / led4 = pino5
	iEscolha += (3 <= iEscolha);

	return acessRegister((int*)&GPIOA_PDOR, iEscolha, 'w', iValor);

}


/* ************************************************ */
/* Method name: 	   turnOnLed	         		*/
/* Method description: Ligar o LED                  */
/* Input params:	   iEscolha                     */
/*                     eh o numero do LED que       */
/*                     sera ligado (1, 2, 3 ou 4)   */
/* Output params:	   n/a 							*/
/* ************************************************ */
int turnOnLed(int iEscolha){

	// incrementa a posição do pino pois led3 = pino4 / led4 = pino5
	iEscolha += (3 <= iEscolha);

	return acessRegister((int*)&GPIOA_PSOR, iEscolha, 'w', 1);

}


/* ************************************************ */
/* Method name: 	   turnOffLed	         		*/
/* Method description: Desligar o LED               */
/* Input params:	   iEscolha                     */
/*                     eh o numero do LED que       */
/*                     sera desligado (1, 2, 3 ou 4)*/
/* Output params:	   n/a 							*/
/* ************************************************ */
int turnOffLed(int iEscolha){

	// incrementa a posição do pino pois led3 = pino4 / led4 = pino5
	iEscolha += (3 <= iEscolha);

	return acessRegister((int*)&GPIOA_PCOR, iEscolha, 'w', 1);

}


/* ********************************************************* */
/* Method name: 	   toggleLed	         		         */
/* Method description: Mudar status do LED: desligar caso    */
/*                     esteja ligado ou ligar caso esteja    */
/*                     desligado                             */
/* Input params:	   iEscolha                              */
/*                     eh o numero do LED que terá seu       */
/*                     status alterado (1, 2, 3 ou 4)        */
/* Output params:	   n/a 							         */
/* ********************************************************* */
int toggleLed(int iEscolha){

	// incrementa a posição do pino pois led3 = pino4 / led4 = pino5
	iEscolha += (3 <= iEscolha);

	return acessRegister((int*)&GPIOA_PTOR, iEscolha, 'w', 1);

}
