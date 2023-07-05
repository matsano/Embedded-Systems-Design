/* *********************************************************************** */
/* File name:		 display7seg.c							 		       */
/* File description: File dedicated to the configuration and manipulation  */
/*                   of the 4 7-segment displays from the hardware kit     */
/* Author name:      Igor B Teixeira                                       */
/*                   Matheus S Sano                                        */
/* Creation date:    18abr2022										       */
/* Revision date:    10mai2022										       */
/* *********************************************************************** */

#include "board.h"
#include "regManager.h"
#include "display7seg.h"
#include "lptmr.h"
#include "util.h"

#define ALL_ON 22
#define ALL_OFF 21
#define ONLY_DOT 20

#define TRUE 1
#define FALSE 0

#define D7SEG_PINS_OUTPUT 0x3DFF

/* globais */
unsigned char ucDisplayData[4] = {ALL_OFF, ALL_OFF, ALL_OFF, ALL_OFF}; /* vetor que guarda os dados dos displays */
int iLastDisplayUpdated = 1; /* valor de referencia para a interrupcao atualizar 1 display por vez */
int iEnableDisplays;

/* ******************************************************* */
/* Method name:        display7seg_writeData               */
/* Method description: Escreve o caractere em um           */
/*                     dos displays                        */
/* Input params:       ucDisplay                           */
/*                     indica qual display que recebera    */
/*                     o valor:                            */
/*                     1 = display dos milhares,           */
/*                     2 = display das centenas,           */
/*                     3 = display das dezenas,            */
/*                     4 = display das unidades            */
/*                                                         */
/*                     ucValue                             */
/*                     indica qual caractere sera escrito  */
/*                     no display                          */
/*                     0-9 = numeros de 0 a 9              */
/*                           com ponto decimal apagado,    */
/*                     10-19 = numeros de 0 a 9            */
/*                             com ponto decimal aceso     */
/*                     20 = ponto decimal aceso            */
/*                     21 = todos os segmentos e           */
/*                          ponto decimal apagados         */
/*                     22 = todos os segmentos e           */
/*                          ponto decimal acesos)          */
/* Output params:      n/a                                 */
/* ******************************************************* */
void display7seg_writeData(unsigned char ucDisplay, unsigned char ucValue);


/* *************************************************** */
/* Method name:        display7seg_init                */
/* Method description: Set up the pins used to control */
/*                     the 7-segment displays          */
/* Input params:       n/a                             */
/* Output params:      n/a                             */
/* *************************************************** */
void display7seg_init(void){
	
	/* Libera o clock para o PORT C */
	writeRegister((int*)&SIM_SCGC5, CLOCK_PORTC_PIN, 1);

	/* Configura pinos dos segmentos dos diplays como GPIO */
	writeRegister((int*)&PORTC_PCR0, PCR_MUX_2, 0);
	writeRegister((int*)&PORTC_PCR0, PCR_MUX_1, 0);
	writeRegister((int*)&PORTC_PCR0, PCR_MUX_0, 1);

	writeRegister((int*)&PORTC_PCR1, PCR_MUX_2, 0);
	writeRegister((int*)&PORTC_PCR1, PCR_MUX_1, 0);
	writeRegister((int*)&PORTC_PCR1, PCR_MUX_0, 1);

	writeRegister((int*)&PORTC_PCR2, PCR_MUX_2, 0);
	writeRegister((int*)&PORTC_PCR2, PCR_MUX_1, 0);
	writeRegister((int*)&PORTC_PCR2, PCR_MUX_0, 1);

	writeRegister((int*)&PORTC_PCR3, PCR_MUX_2, 0);
	writeRegister((int*)&PORTC_PCR3, PCR_MUX_1, 0);
	writeRegister((int*)&PORTC_PCR3, PCR_MUX_0, 1);

	writeRegister((int*)&PORTC_PCR4, PCR_MUX_2, 0);
	writeRegister((int*)&PORTC_PCR4, PCR_MUX_1, 0);
	writeRegister((int*)&PORTC_PCR4, PCR_MUX_0, 1);

	writeRegister((int*)&PORTC_PCR5, PCR_MUX_2, 0);
	writeRegister((int*)&PORTC_PCR5, PCR_MUX_1, 0);
	writeRegister((int*)&PORTC_PCR5, PCR_MUX_0, 1);

	writeRegister((int*)&PORTC_PCR6, PCR_MUX_2, 0);
	writeRegister((int*)&PORTC_PCR6, PCR_MUX_1, 0);
	writeRegister((int*)&PORTC_PCR6, PCR_MUX_0, 1);

	writeRegister((int*)&PORTC_PCR7, PCR_MUX_2, 0);
	writeRegister((int*)&PORTC_PCR7, PCR_MUX_1, 0);
	writeRegister((int*)&PORTC_PCR7, PCR_MUX_0, 1);

	/* Configura pinos de enable dos diplays como GPIO */
	writeRegister((int*)&PORTC_PCR10, PCR_MUX_2, 0);
	writeRegister((int*)&PORTC_PCR10, PCR_MUX_1, 0);
	writeRegister((int*)&PORTC_PCR10, PCR_MUX_0, 1);

	writeRegister((int*)&PORTC_PCR11, PCR_MUX_2, 0);
	writeRegister((int*)&PORTC_PCR11, PCR_MUX_1, 0);
	writeRegister((int*)&PORTC_PCR11, PCR_MUX_0, 1);

	writeRegister((int*)&PORTC_PCR12, PCR_MUX_2, 0);
	writeRegister((int*)&PORTC_PCR12, PCR_MUX_1, 0);
	writeRegister((int*)&PORTC_PCR12, PCR_MUX_0, 1);

	writeRegister((int*)&PORTC_PCR13, PCR_MUX_2, 0);
	writeRegister((int*)&PORTC_PCR13, PCR_MUX_1, 0);
	writeRegister((int*)&PORTC_PCR13, PCR_MUX_0, 1);

	/* Configura pinos 0-7 (segmentos) e 10-13 (enables) como saida digital (valor 1) */
	GPIOC_PDDR |= D7SEG_PINS_OUTPUT;

	iEnableDisplays = TRUE;
}



/* ******************************************************* */
/* Method name:        display7seg_writeData               */
/* Method description: Escreve o caractere em um           */
/*                     dos displays                        */
/* Input params:       ucDisplay                           */
/*                     indica qual display que recebera    */
/*                     o valor:                            */
/*                     1 = display dos milhares,           */
/*                     2 = display das centenas,           */
/*                     3 = display das dezenas,            */
/*                     4 = display das unidades            */
/*                                                         */
/*                     ucValue                             */
/*                     indica qual caractere sera escrito  */
/*                     no display                          */
/*                     0-9 = numeros de 0 a 9              */
/*                           com ponto decimal apagado,    */
/*                     10-19 = numeros de 0 a 9            */
/*                             com ponto decimal aceso     */
/*                     20 = ponto decimal aceso            */
/*                     21 = todos os segmentos e           */
/*                          ponto decimal apagados         */
/*                     22 = todos os segmentos e           */
/*                          ponto decimal acesos)          */
/* Output params:      n/a                                 */
/* ******************************************************* */
void display7seg_writeData(unsigned char ucDisplay, unsigned char ucValue){

	/*
	 * Determinar qual display sera ligado
	 * 1 == ucDisplay so sera 1 para o display escolhido e eles estiverem habilitados
	 */
	writeRegister((int*)&GPIOC_PDOR, 13, (1 == ucDisplay) && (TRUE == iEnableDisplays));
	writeRegister((int*)&GPIOC_PDOR, 12, (2 == ucDisplay) && (TRUE == iEnableDisplays));
	writeRegister((int*)&GPIOC_PDOR, 11, (3 == ucDisplay) && (TRUE == iEnableDisplays));
	writeRegister((int*)&GPIOC_PDOR, 10, (4 == ucDisplay) && (TRUE == iEnableDisplays));


	if (TRUE == iEnableDisplays){
		/* Casos especiais e escolha do ponto */

		if (ALL_ON == ucValue){ /* Tudo ligado */
			GPIOC_PSOR |= 0xFF;
		}

		else if (ALL_OFF == ucValue){ /* Tudo ligado sem o ponto */
			GPIOC_PCOR |= 0xFF;
		}

		else if (ONLY_DOT == ucValue){ /* So o ponto ligado */
			GPIOC_PSOR |= 0x80;
			GPIOC_PCOR |= 0x7F;
		}

		else if (10 <= ucValue && 20 >= ucValue){ /* Liga o ponto e subtrai 10 para facilitar as condicoes*/
			GPIOC_PSOR |= 0x80;
			ucValue -= 10;
		}

		else { /* Desliga o ponto */
			GPIOC_PCOR |= 0x80;
		}


		/* Casos comuns, liga apenas os segmentos de acordo com o numero/letra/segmento escolhida */

		if (0 == ucValue){
			GPIOC_PSOR |= 0x3F;
			GPIOC_PCOR |= 0x40;
		}

		else if (1 == ucValue){
			GPIOC_PSOR |= 0x6;
			GPIOC_PCOR |= 0x79;
		}

		else if (2 == ucValue){
			GPIOC_PSOR |= 0x5B;
			GPIOC_PCOR |= 0x24;
		}

		else if (3 == ucValue){
			GPIOC_PSOR |= 0x4F;
			GPIOC_PCOR |= 0x30;
		}

		else if (4 == ucValue){
			GPIOC_PSOR |= 0x66;
			GPIOC_PCOR |= 0x19;
		}

		else if (5 == ucValue){
			GPIOC_PSOR |= 0x6D;
			GPIOC_PCOR |= 0x12;
		}

		else if (6 == ucValue){
			GPIOC_PSOR |= 0x7D;
			GPIOC_PCOR |= 0x2;
		}

		else if (7 == ucValue){
			GPIOC_PSOR |= 0x7;
			GPIOC_PCOR |= 0x78;
		}

		else if (8 == ucValue){
			GPIOC_PSOR |= 0x7F;
		}

		else if (9 == ucValue){
			GPIOC_PSOR |= 0x6F;
			GPIOC_PCOR |= 0x10;
		}

		else if ('A' == ucValue){ /* Letras maiusculas escrevem uma letra no display */
			GPIOC_PSOR |= 0x77;
			GPIOC_PCOR |= 0x8;
		}

		else if ('B' == ucValue){
			GPIOC_PSOR |= 0x7C;
			GPIOC_PCOR |= 0x3;
		}

		else if ('C' == ucValue){
			GPIOC_PSOR |= 0x39;
			GPIOC_PCOR |= 0x46;
		}

		else if ('D' == ucValue){
			GPIOC_PSOR |= 0x5E;
			GPIOC_PCOR |= 0x21;
		}

		else if ('E' == ucValue){
			GPIOC_PSOR |= 0x79;
			GPIOC_PCOR |= 0x6;
		}

		else if ('F' == ucValue){
			GPIOC_PSOR |= 0x71;
			GPIOC_PCOR |= 0xE;
		}

		else if ('L' == ucValue){
			GPIOC_PSOR |= 0x38;
			GPIOC_PCOR |= 0x47;
		}

		else if ('O' == ucValue){
			GPIOC_PSOR |= 0x3F;
			GPIOC_PCOR |= 0x40;
		}

		else if ('P' == ucValue){
			GPIOC_PSOR |= 0x73;
			GPIOC_PCOR |= 0xC;
		}

		else if ('S' == ucValue){
			GPIOC_PSOR |= 0x6D;
			GPIOC_PCOR |= 0x12;
		}

		else if ('T' == ucValue){
			GPIOC_PSOR |= 0x78;
			GPIOC_PCOR |= 0x7;
		}

		else if ('U' == ucValue){
			GPIOC_PSOR |= 0x2E;
			GPIOC_PCOR |= 0x41;
		}

		else if ('W' == ucValue){
			GPIOC_PSOR |= 0x1C;
			GPIOC_PCOR |= 0x63;
		}


		else if ('a' == ucValue){ /* Letras minusculas escrevem no referido segmento do display */
			GPIOC_PSOR |= 0x1;
			GPIOC_PCOR |= 0x7E;
		}

		else if ('b' == ucValue){
			GPIOC_PSOR |= 0x2;
			GPIOC_PCOR |= 0x7D;
		}

		else if ('c' == ucValue){
			GPIOC_PSOR |= 0x4;
			GPIOC_PCOR |= 0x7B;
		}

		else if ('d' == ucValue){
			GPIOC_PSOR |= 0x8;
			GPIOC_PCOR |= 0x77;
		}

		else if ('e' == ucValue){
			GPIOC_PSOR |= 0x10;
			GPIOC_PCOR |= 0x6F;
		}

		else if ('f' == ucValue){
			GPIOC_PSOR |= 0x20;
			GPIOC_PCOR |= 0x5F;
		}

		else if ('g' == ucValue){
			GPIOC_PSOR |= 0x40;
			GPIOC_PCOR |= 0x3F;
		}
	}
}



/* ******************************************************* */
/* Method name:        display7seg_writeSymbol             */
/* Method description:                                     */
/*                     the displays.                       */
/* Input params:       ucDisplay                           */
/*                     indica qual display que recebera    */
/*                     o valor:                            */
/*                     1 = display dos milhares,           */
/*                     2 = display das centenas,           */
/*                     3 = display das dezenas,            */
/*                     4 = display das unidades            */
/*                                                         */
/*                     ucValue                             */
/*                     indica qual caractere sera escrito  */
/*                     no display                          */
/*                     0-9 = numeros de 0 a 9              */
/*                           com ponto decimal apagado,    */
/*                     10-19 = numeros de 0 a 9            */
/*                             com ponto decimal aceso     */
/*                     20 = ponto decimal aceso            */
/*                     21 = todos os segmentos e           */
/*                          ponto decimal apagados         */
/*                     22 = todos os segmentos e           */
/*                          ponto decimal acesos)          */
/* Output params:      n/a                                 */
/* ******************************************************* */
void display7seg_writeSymbol(unsigned char ucDisplay, unsigned char ucValue){

	if (1 <= ucDisplay && 4 >= ucDisplay){
		ucDisplayData[ucDisplay-1] = ucValue;
	}

}



/* ****************************************************** */
/* Method name: 	   display7seg_slideDummy		      */
/* Method description: Write a dummy hard coded text with */
/*                     a slide movement                   */
/* Input params:	   n/a                                */
/* Output params:	   n/a 							      */
/* ****************************************************** */
void display7seg_slideDummy(void){

	ucDisplayData[0] = ALL_OFF;
	ucDisplayData[1] = ALL_OFF;
	ucDisplayData[2] = ALL_OFF;
	ucDisplayData[3] = 'E';
	util_genDelay100ms();
	util_genDelay100ms();
	util_genDelay100ms();
	

	ucDisplayData[0] = ALL_OFF;
	ucDisplayData[1] = ALL_OFF;
	ucDisplayData[2] = 'E';
	ucDisplayData[3] = 5;
	util_genDelay100ms();
	util_genDelay100ms();
	util_genDelay100ms();


	ucDisplayData[0] = ALL_OFF;
	ucDisplayData[1] = 'E';
	ucDisplayData[2] = 5;
	ucDisplayData[3] = ONLY_DOT;
	util_genDelay100ms();
	util_genDelay100ms();
	util_genDelay100ms();


	ucDisplayData[0] = 'E';
	ucDisplayData[1] = 5;
	ucDisplayData[2] = ONLY_DOT;
	ucDisplayData[3] = 6;
	util_genDelay100ms();
	util_genDelay100ms();
	util_genDelay100ms();


	ucDisplayData[0] = 5;
	ucDisplayData[1] = ONLY_DOT;
	ucDisplayData[2] = 6;
	ucDisplayData[3] = 7;
	util_genDelay100ms();
	util_genDelay100ms();
	util_genDelay100ms();


	ucDisplayData[0] = ONLY_DOT;
	ucDisplayData[1] = 6;
	ucDisplayData[2] = 7;
	ucDisplayData[3] = 0;
	util_genDelay100ms();
	util_genDelay100ms();
	util_genDelay100ms();


	ucDisplayData[0] = 6;
	ucDisplayData[1] = 7;
	ucDisplayData[2] = 0;
	ucDisplayData[3] = ALL_OFF;
	util_genDelay100ms();
	util_genDelay100ms();
	util_genDelay100ms();


	ucDisplayData[0] = 7;
	ucDisplayData[1] = 0;
	ucDisplayData[2] = ALL_OFF;
	ucDisplayData[3] = ALL_OFF;
	util_genDelay100ms();
	util_genDelay100ms();
	util_genDelay100ms();


	ucDisplayData[0] = 0;
	ucDisplayData[1] = ALL_OFF;
	ucDisplayData[2] = ALL_OFF;
	ucDisplayData[3] = ALL_OFF;
	util_genDelay100ms();
	util_genDelay100ms();
	util_genDelay100ms();


	/* Limpa todos os displays 7seg */
	display7seg_clear();
}



/* ****************************************************** */
/* Method name: 	   display7seg_circleWaiting		  */
/* Method description: Make a circular movement with      */
/*                     a light trace at the displays      */
/* Input params:	   int iDurationTimeInS:              */
/*                     Duration time (in sec) of the      */
/*                     animation                          */
/* Output params:	   n/a 							      */
/* ****************************************************** */
void display7seg_circleWaiting(int iDurationTimeInS){

	int iCount;

	/*
	 * Liga cada segmento por vez para produzir uma ilusao de que
	 * o traço luminoso esta percorrento os diplays de forma circular
	 */

	for (iCount = 0; iCount <= iDurationTimeInS; iCount++){

		ucDisplayData[0] = 'a';
		ucDisplayData[1] = ALL_OFF;
		ucDisplayData[2] = ALL_OFF;
		ucDisplayData[3] = ALL_OFF;
		util_genDelay100ms();

		ucDisplayData[0] = ALL_OFF;
		ucDisplayData[1] = 'a';
		ucDisplayData[2] = ALL_OFF;
		ucDisplayData[3] = ALL_OFF;
		util_genDelay100ms();

		ucDisplayData[0] = ALL_OFF;
		ucDisplayData[1] = ALL_OFF;
		ucDisplayData[2] = 'a';
		ucDisplayData[3] = ALL_OFF;
		util_genDelay100ms();

		ucDisplayData[0] = ALL_OFF;
		ucDisplayData[1] = ALL_OFF;
		ucDisplayData[2] = ALL_OFF;
		ucDisplayData[3] = 'a';
		util_genDelay100ms();

		ucDisplayData[0] = ALL_OFF;
		ucDisplayData[1] = ALL_OFF;
		ucDisplayData[2] = ALL_OFF;
		ucDisplayData[3] = 'b';
		util_genDelay100ms();

		ucDisplayData[0] = ALL_OFF;
		ucDisplayData[1] = ALL_OFF;
		ucDisplayData[2] = ALL_OFF;
		ucDisplayData[3] = 'c';
		util_genDelay100ms();

		ucDisplayData[0] = ALL_OFF;
		ucDisplayData[1] = ALL_OFF;
		ucDisplayData[2] = ALL_OFF;
		ucDisplayData[3] = 'd';
		util_genDelay100ms();

		ucDisplayData[0] = ALL_OFF;
		ucDisplayData[1] = ALL_OFF;
		ucDisplayData[2] = 'd';
		ucDisplayData[3] = ALL_OFF;
		util_genDelay100ms();

		ucDisplayData[0] = ALL_OFF;
		ucDisplayData[1] = 'd';
		ucDisplayData[2] = ALL_OFF;
		ucDisplayData[3] = ALL_OFF;
		util_genDelay100ms();

		ucDisplayData[0] = 'd';
		ucDisplayData[1] = ALL_OFF;
		ucDisplayData[2] = ALL_OFF;
		ucDisplayData[3] = ALL_OFF;
		util_genDelay100ms();

		ucDisplayData[0] = 'e';
		ucDisplayData[1] = ALL_OFF;
		ucDisplayData[2] = ALL_OFF;
		ucDisplayData[3] = ALL_OFF;
		util_genDelay100ms();

		ucDisplayData[0] = 'f';
		ucDisplayData[1] = ALL_OFF;
		ucDisplayData[2] = ALL_OFF;
		ucDisplayData[3] = ALL_OFF;
		util_genDelay100ms();
	}

	/* Limpa todos os displays 7seg */
	display7seg_clear();

}

/* ******************************************************* */
/* Method name:        display7seg_interruption            */
/* Method description: A cada interrupcao um display eh    */
/*                     atualizado na ordem do 1 ao 4.      */
/* Input params:       void                                */
/* Output params:      n/a                                 */
/* ******************************************************* */
void display7seg_interruption(void) {
	/* Volta a atualizar a partir do display 1 apos chegar no 4*/
	if (4 < iLastDisplayUpdated){
		iLastDisplayUpdated = 1;
	}
	display7seg_writeData(iLastDisplayUpdated,ucDisplayData[iLastDisplayUpdated-1]);
	iLastDisplayUpdated += 1;
}



/* ****************************************************** */
/* Method name: 	   display7seg_clear		          */
/* Method description: Clear all displays 7 seg           */
/*                                                        */
/* Input params:	   n/a                                */
/* Output params:	   n/a 							      */
/* ****************************************************** */
void display7seg_clear(void){

	/* Limpa todos os displays 7seg */
	ucDisplayData[0] = ALL_OFF;
	ucDisplayData[1] = ALL_OFF;
	ucDisplayData[2] = ALL_OFF;
	ucDisplayData[3] = ALL_OFF;

}


/* ****************************************************** */
/* Method name: 	   display7seg_test		              */
/* Method description: Turn on all displays 7 seg         */
/*                     for 2 sec                          */
/*                                                        */
/* Input params:	   n/a                                */
/* Output params:	   n/a 							      */
/* ****************************************************** */
void display7seg_test(void){

	/* Limpa todos os displays 7seg */
	ucDisplayData[0] = ALL_ON;
	ucDisplayData[1] = ALL_ON;
	ucDisplayData[2] = ALL_ON;
	ucDisplayData[3] = ALL_ON;
	util_genDelay1000ms();
	util_genDelay1000ms();
	display7seg_clear();

}



/* ****************************************************** */
/* Method name: 	   display7seg_enable		          */
/* Method description: enable write on the displays       */
/*                                                        */
/* Input params:	   n/a                                */
/* Output params:	   n/a 							      */
/* ****************************************************** */
void display7seg_enable(void){

	/* Habilita os displays */
	iEnableDisplays = TRUE;
}

/* ****************************************************** */
/* Method name: 	   display7seg_disable		          */
/* Method description: disable write on the displays      */
/*                                                        */
/* Input params:	   n/a                                */
/* Output params:	   n/a 							      */
/* ****************************************************** */
void display7seg_disable(void){

	/* Desabilita os displays */
	iEnableDisplays = FALSE;
}





