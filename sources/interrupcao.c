/* *********************************************************************** */
/* File name:		 interrupcao.c							 		       */
/* File description: File dedicated to the configuration of the            */
/*                   interruptions to update the display7seg and read      */
/*                   the tacometer                                         */
/* Author name:      Igor B Teixeira                                       */
/*                   Matheus S Sano                                        */
/* Creation date:    05mai2022										       */
/* Revision date:    26jun2022										       */
/* *********************************************************************** */

#include "interrupcao.h"
#include "lptmr.h"
#include "display7seg.h"
#include "tacometro.h"
#include "adc.h"
#include "pid.h"
#include "screenControl.h"
#include "aquecedorECooler.h"
#include "ledrgb.h"

#define INTERRUPTION_TIME_US 2500
#define TACOMETRO_PERIODO 250
#define TACOMETRO_INTERRUPTION_COUNT 1000.0f * (float)((float)TACOMETRO_PERIODO / INTERRUPTION_TIME_US)
#define PID_INTERRUPTION_COUNT 40
#define ADC_INTERRUPTION_COUNT 8

unsigned int uiTacometroRpm = 0;
float fPidAquecedor;

extern float fLeituraTemperatura;
extern float fTemperaturaDesejada;
extern float fVelocidadeCoolerDesejada;

int iContadorRPM = 0;
int iContadorPID = 0;
int iContadorADC = 0;

/* *************************************************** */
/* Method name:        interruptionInit                */
/* Method description: Set up the interruption         */
/*                     parameters and treatment        */
/* Input params:       n/a                             */
/* Output params:      n/a                             */
/* *************************************************** */
void interruptionInit(void){

	/*
	 * ISR para tratamento da interrupcao gerada pelo LPTMR0
	 */
	void cyclicInterruption(void)
	{
		/* Le o valor do contador de pulsos do cooler a cada certo numero de interrupcoes*/
		if (TACOMETRO_INTERRUPTION_COUNT == iContadorRPM){
			uiTacometroRpm = tachometer_readSensor(TACOMETRO_PERIODO);
			TPM0_CNT=0;
			iContadorRPM = 0;
		}


		if (ADC_INTERRUPTION_COUNT == iContadorADC){
			armazenarValorAdc(); /* Armazena em uma var global a temperatura lida */
			adc_initConvertion(); /* Pede para o ADC ler a tensão do diodo */
			iContadorADC = 0;
		}


		if (PID_INTERRUPTION_COUNT == iContadorPID){
			/* Recalcula o duty cycle do aquecedor com o PID */
			fPidAquecedor = pidUpdateData(fLeituraTemperatura, fTemperaturaDesejada);

			/* O led muda a cor com base no duty cycle do heater */
			if ((25 > fPidAquecedor)){
				ledrgb_write(2);
			} else if (75 < fPidAquecedor){
				ledrgb_write(1);
			} else {
				ledrgb_write(4);
			}

			/* Ajuste dos duty cycle */
			heater_PWMDuty(fPidAquecedor/100.0);
			coolearfan_PWMDuty(fVelocidadeCoolerDesejada);
			iContadorPID = 0;
		}

		iContadorRPM ++;
		iContadorPID++;
		iContadorADC++;

	};


	/*
	 * Configuracao da interrupcao ativada por temporizador
	 * a cada 2.5ms chamando a funcao cyclicInterruption()
	 */
	tc_installLptmr0(INTERRUPTION_TIME_US, cyclicInterruption);
}
