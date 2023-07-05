/* *********************************************************************** */
/* File name:		 tacometro.c						 		           */
/* File description: File dedicated to the configuration and manipulation  */
/*                   of the encoder's cooler                               */
/* Author name:      Igor B Teixeira                                       */
/*                   Matheus S Sano                                        */
/* Creation date:    05mai2022										       */
/* Revision date:    10mai2022										       */
/* *********************************************************************** */

#include "board.h"
#include "regManager.h"
#include "tacometro.h"

/* *************************************************** */
/* Method name:        tachometer_init                 */
/* Method description: Initialize the tachometer and   */
/*                     configurate TPM0 as timer with  */
/*                     external clock                  */
/* Input params:       n/a                             */
/* Output params:      n/a                             */
/* *************************************************** */
void tachometer_init(void){
	/* Libera o clock para o contador TPM0 */
	writeRegister((int*)&SIM_SCGC6, CLOCK_TPM0, 1);

	/* Configura o divisor de clock do contador do modulo TPM0 para 1 */
	writeRegister((int*)&TPM0_SC, TPM_PS_2, 0);
	writeRegister((int*)&TPM0_SC, TPM_PS_1, 0);
	writeRegister((int*)&TPM0_SC, TPM_PS_0, 0);

	/* Libera o clock para a porta do pino de saida do encoder */
	writeRegister((int*)&SIM_SCGC5, CLOCK_PORTE_PIN, 1);

	/* Configura o pino PTE29 como external clock */
	writeRegister((int*)&PORTE_PCR29, PCR_MUX_2, 1);
	writeRegister((int*)&PORTE_PCR29, PCR_MUX_1, 0);
	writeRegister((int*)&PORTE_PCR29, PCR_MUX_0, 0);

	/* Selecionar o pino externo TPM_CLKIN0 como entrada do TPM0 */
	writeRegister((int*)&SIM_SOPT4, TPM0CLKSEL, 0);

	/* Configura contador para counter clock */
	writeRegister((int*)&TPM0_SC, TPM_CMOD_1, 1);
	writeRegister((int*)&TPM0_SC, TPM_CMOD_0, 0);

	/* Configura contador para contagem crescente */
	writeRegister((int*)&TPM0_SC, TPM_CPWMS, 0);

	TPM0_CONF = 0xC0;
}

/* ******************************************************** */
/* Method name:        tachometer_readSensor                */
/* Method description: Read the cooler's velocity in        */
/*                     revolutions per minute (RPM)         */
/* Input params:       uiPeriod                             */
/*                     Periodo da janela em microssegundos  */
/* Output params:      (unsigned int)                       */
/*                     Velocidade do cooler em rpm          */
/* ******************************************************** */
unsigned int tachometer_readSensor(unsigned int uiPeriod){

	float fPeriodo = (float)uiPeriod / 1000; /*periodo em segundos */

	return (unsigned int)((TPM0_CNT*60.0f) / (7.0f*fPeriodo));
}


