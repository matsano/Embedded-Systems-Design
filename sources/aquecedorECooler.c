/* *********************************************************************** */
/* File name:		 aquecedorECooler.c						 		       */
/* File description: File dedicated to the configuration and manipulation  */
/*                   of TPM modules to generate PWM signals for heater and */
/*                   cooler control                                        */
/* Author name:      Igor B Teixeira                                       */
/*                   Matheus S Sano                                        */
/* Creation date:    25abr2022										       */
/* Revision date:    28abr2022										       */
/* *********************************************************************** */

#include "board.h"
#include "regManager.h"
#include "aquecedorECooler.h"
#include "util.h"

#define COUNTER_VALUE_TPM1 50000; /* um valor de contagem de 50000 */
#define TPM_EDGEALIGN_HIGHTRUE 0b101000

/* variaveis da maquina de estado */
extern float fDutyCoolerMaquinaEstados;
extern float fDutyHeaterMaquinaEstados;

/* *************************************************** */
/* Method name:        PWM_init                        */
/* Method description: Initialize the 0 and 1 channels */
/*                     of TPM1 as Edge-Aligned PWM and */
/*                     configure both signals PWM with */
/*                     frequency between 5 and 20 Hz   */
/* Input params:       n/a                             */
/* Output params:      n/a                             */
/* *************************************************** */
void PWM_init(void){

	/* Libera o clock para o contador TPM1 */
	writeRegister((int*)&SIM_SCGC6, CLOCK_TPM1, 1);

	/* Configura o divisor de clock do contador do modulo TPM para 32 */
	writeRegister((int*)&TPM1_SC, TPM_PS_2, 1);
	writeRegister((int*)&TPM1_SC, TPM_PS_1, 0);
	writeRegister((int*)&TPM1_SC, TPM_PS_0, 1);

	/* Configurar a fonte de clock do contador do modulo TPM para 8 MHz */
	writeRegister((int*)&SIM_SOPT2, TPM_SOURCE_1, 1);
	writeRegister((int*)&SIM_SOPT2, TPM_SOURCE_0, 0);

	/* Configura contador para counter clock */
	writeRegister((int*)&TPM1_SC, TPM_CMOD_1, 0);
	writeRegister((int*)&TPM1_SC, TPM_CMOD_0, 1);

	/* Configura contador para contagem crescente */
	writeRegister((int*)&TPM1_SC, TPM_CPWMS, 0);

	/* Configura o valor maximo de contagem do TPM1 */
	TPM1_MOD = COUNTER_VALUE_TPM1;

	/* Configura o modo do canal 0 como Edge-Aligned PWM com High-true pulses */
	TPM1_C0SC = TPM_EDGEALIGN_HIGHTRUE;

	/* Configura o modo do canal 1 como Edge-Aligned PWM com High-true pulses */
	TPM1_C1SC = TPM_EDGEALIGN_HIGHTRUE;

	/* Configura o duty cycle em 0% para comecar com nivel baixo por seguranca */
	util_genDelay1000ms();
	TPM1_C0V = 0;
	TPM1_C1V = 0;


	TPM1_CONF = 0xC0;
}



/* *************************************************** */
/* Method name:        coolerfan_init                  */
/* Method description: Initialize and release the PWM  */
/*                     signal on the cooler            */
/* Input params:       n/a                             */
/* Output params:      n/a                             */
/* *************************************************** */
void coolerfan_init(void){

	/* Libera o clock para o PORTA */
	writeRegister((int*)&SIM_SCGC5, CLOCK_PORTA_PIN, 1);

	/* Configura o pino do ventilador como PWM */
	writeRegister((int*)&PORTA_PCR13, PCR_MUX_2, 0);
	writeRegister((int*)&PORTA_PCR13, PCR_MUX_1, 1);
	writeRegister((int*)&PORTA_PCR13, PCR_MUX_0, 1);
}



/* *************************************************** */
/* Method name:        heater_init                     */
/* Method description: Initialize and release the PWM  */
/*                     signal on the heater            */
/* Input params:       n/a                             */
/* Output params:      n/a                             */
/* *************************************************** */
void heater_init(void){

	/* Libera o clock para o PORTA */
	writeRegister((int*)&SIM_SCGC5, CLOCK_PORTA_PIN, 1);

	/* Configura o pino do aquecedor como PWM */
	writeRegister((int*)&PORTA_PCR12, PCR_MUX_2, 0);
	writeRegister((int*)&PORTA_PCR12, PCR_MUX_1, 1);
	writeRegister((int*)&PORTA_PCR12, PCR_MUX_0, 1);
}



/* *************************************************** */
/* Method name:        coolearfan_PWMDuty              */
/* Method description: Configure the duty cycles of    */
/*                     the PWM signal on the cooler    */
/* Input params:       fCoolerDuty                     */
/*                     duty cicle of the PWM signal on */
/*                     the cooler (0 = duty cicle 0%   */
/*                     1 = duty cicle 100%             */
/* Output params:      n/a                             */
/* *************************************************** */
void coolearfan_PWMDuty (float fCoolerDuty){

	/* Multiplica o duty cycle pelo valor de comparacao do contador */
	float fComparador = COUNTER_VALUE_TPM1;
	fDutyCoolerMaquinaEstados = fCoolerDuty;
	TPM1_C1V = (int)(fComparador * fCoolerDuty);
}



/* *************************************************** */
/* Method name:        heater_PWMDuty                  */
/* Method description: Configure the duty cycles of    */
/*                     the PWM signal on the heater    */
/* Input params:       fHeaterDuty                     */
/*                     duty cicle of the PWM signal on */
/*                     the cooler (0 = duty cicle 0%   */
/*                     1 = duty cicle 100%             */
/* Output params:      n/a                             */
/* *************************************************** */
void heater_PWMDuty (float fHeaterDuty){

	/* Multiplica o duty cycle pelo valor de comparacao do contador */
	float fComparador = COUNTER_VALUE_TPM1;
	fDutyHeaterMaquinaEstados = fHeaterDuty;
	TPM1_C0V = (int)(fComparador * fHeaterDuty);
}
