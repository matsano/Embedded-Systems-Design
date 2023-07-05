/* ***************************************************************** */
/* File name:        main.c                                          */
/* File description: File dedicated to the ES670 prototype projects  */
/*                   involving the FRDM-KL25Z board together with is */
/*                   daughter board containing more peripherals      */
/*                                                                   */
/*                   Processor MKL25Z128VLK4 characteristics         */
/*                   48 MHz ARM Cortex-M0+ core                      */
/*                   128 KB program flash memory                     */
/*                   16 KB SRAM                                      */
/*                   Voltage range: 1.71 to 3.6 V                    */
/*                                                                   */
/* Author name:      Rodrigo M Bacurau                               */
/*                   Igor B Teixeira                                 */
/*                   Matheus S Sano                                  */
/* Creation date:    26fev2020                                       */
/* Revision date:    30mai2022                                       */
/* ***************************************************************** */

/* our includes */
#include "util.h"
#include "mcg.h"
#include "ledrgb.h"
#include "board.h"
#include "ledSwi.h"
#include "lcd.h"
#include "lptmr.h"
#include "display7seg.h"
#include "aquecedorECooler.h"
#include "interrupcao.h"
#include "tacometro.h"
#include "print_scan.h"
#include "UART.h"
#include "communicationStateMachine.h"
#include <string.h>
#include "adc.h"
#include "pid.h"
#include "screenControl.h"


/* system includes */
#include "fsl_clock_manager.h"
#include "fsl_device_registers.h"
#include "fsl_port_hal.h"
#include "fsl_smc_hal.h"
#include "fsl_debug_console.h"
#include <stdio.h>
#include <stdlib.h>

#define LENGTH_STRING_SERIAL 50
#define RPM_MAX_COOLER 7131.0
#define TEMPERATURA_MAX 70.0
#define COUNTER_TIME_LCD 100000

#define TRUE 1
#define FALSE 0

/* globals */
int iEnableLedRGB = 1; /* LED RGB vem ligado por padrao */

int iCounterUpdateScreen = 0; /* Variavel para atualizar o LCD a cada periodo */

extern unsigned int uiTacometroRpm;
extern float fLeituraTemperatura;
extern float fTemperaturaDesejada;
char cLcdRpm[7];
char * cString[LENGTH_STRING_SERIAL];

/* variaveis do controlador */
extern float fPidAquecedor;
extern pid_data_type pidConfig;
char cLeituraGanhoKp[10];
char cLeituraGanhoKi[10];
char cLeituraGanhoKd[10];
char cDutyCycle[10];
char cTempDesajada[10];
char cLeituraTemperaturaLCD[10];

/* variaveis da maquina de estado */
extern int iHabilitarBotao; /* (= 0) se desabilitar botao, (= 1) habilitar botao */
extern float fVelocidadeCoolerDesejada;
extern float fTemperaturaDesejada;
extern char cLeituraTemperatura[10];

extern float fLeituraTemperatura;
numero_float temperaturaLcd;


/* ************************************************ */
/* Method name:        boardInit                    */
/* Method description: main board all needed        */
/*                     initializations              */
/* Input params:       n/a                          */
/* Output params:      n/a                          */
/* ************************************************ */
void boardInit(void)
{
	/* fist of all, clock configuration and initialization */
	mcg_clockInit();
	initializeLedSwi('L', 'L', 'B', 'B');
	lcd_initLcd();
	lcd_dummyText();
	PWM_init();
	coolerfan_init();
	heater_init();
	interruptionInit();
	tachometer_init();
	UART0_init();
	UART0_enableIRQ();
	adc_initADCModule();
	pid_init();
	ledrgb_init();
}



/* ************************************************ */
/* Method name:        main                         */
/* Method description: system entry point           */
/* Input params:       n/a                          */
/* Output params:      n/a                          */
/* ************************************************ */
int main(void)
{
	/* board initializations */
	boardInit();
	adc_initConvertion(); /* Pede para o ADC ler a tensão do diodo pela primeira vez */
	util_genDelay100ms();
	util_putSerialLineFeed();
	util_putStringSerial("Comunicacao Serial Inicializada");
	util_putSerialLineFeed();


	lcd_sendCommand(CMD_CLEAR);


	/****************************************************************************/
	/*                                LEGENDA                                   */
	/*                                                                          */
	/* BOTA 4 SOLTO:    TELA 1 - temperatura atual e ganhos do controlador      */
	/* BOTA 4 APERTADO: TELA 2 - temperatura desejada e duty cycle do aquecedor */
	/*                                                                          */
	/*                                                                          */
	/*                                                                          */
	/*                                                                          */
	/*                                                                          */
	/*                               SERIAL                                     */
	/* # - Inicia o comando                                                     */
	/* d - Desabilita interface local                                           */
	/* h - Habilita interface local                                             */
	/* s - Modo SET:                                                            */
	/*   |- t - Definir temperatura desejada                                    */
	/*   |- c - Definir velocidade do cooler desejada                           */
	/*   |- p - Definir ganho Kp do controlador                                 */
	/*   |- i - Definir ganho Ki do controlador                                 */
	/*   |- d - Definir ganho Kd do controlador                                 */
	/* g - Modo GET:                                                            */
	/*   |- t - Obter informacoes de temperatura                                */
	/*   |- c - Obter informacoes do cooler                                     */
	/* ; - Finaliza o comando                                                   */
	/****************************************************************************/

	/* main loop */
    while (1){

		if ((1 == readSwitch(3) || 1 == readSwitch(4)) && (TRUE == iHabilitarBotao)){
			util_genDelay100ms(); /* tempo de debounce dos botoes*/

			if (1 == readSwitch(3) && 1 == readSwitch(4)){
				/* Dois botoes juntos mudam de tela */
				util_genDelay500ms();
				screenControl_nextScreen();
				screenControl_updateScreen();
				util_genDelay1000ms();
			}

			else if (1 == readSwitch(3)){
				/* Botao esquerdo - */
				screenControl_adjustVariable('-');
				screenControl_updateScreen();

			}

			else if (1 == readSwitch(4)){
				/* Botao direito + */
				screenControl_adjustVariable('+');
				screenControl_updateScreen();
			}
		}

		iCounterUpdateScreen ++;

		if (COUNTER_TIME_LCD == iCounterUpdateScreen){
			screenControl_updateScreen();
			iCounterUpdateScreen = 0;
		}

    }
}
