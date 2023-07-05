/* *********************************************************************** */
/* File name:		 communicationStateMachine.c    		 		       */
/* File description: Arquivo dedicado a implementar a maquina de estados   */
/*                   com o uso de transmissao serial de dados              */
/* Author name:      Igor B Teixeira                                       */
/*                   Matheus S Sano                                        */
/* Creation date:    19mai2022										       */
/* Revision date:    30mai2022										       */
/* *********************************************************************** */

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "util.h"
#include "pid.h"
#include "screenControl.h"

#define IDDLE '0'
#define READY '1'
#define HABILITAR_BOTOES '2'
#define DESABILITAR_BOTOES '3'
#define GET '4'
#define SET '5'
#define GET_TEMPERATURA '6'
#define GET_COOLER '7'
#define SET_TEMPERATURA '8'
#define SET_COOLER '9'
#define SET_KP 'A'
#define SET_KI 'B'
#define SET_KD 'C'

#define BOTAO_HABILITADO 1
#define BOTAO_DESABILITADO 0

#define DUTY_CYCLE_MAXIMO 1
#define DUTY_CYCLE_MINIMO 0
#define TEMPERATURA_MAXIMA 90
#define TEMPERATURA_MINIMA 0

/* struct do duty cycle do aquecedor e do cooler */
typedef struct duty_cycle_heater_cooler
{
	int iDutyCycleHCInteiro;
	int iDutyCycleHCDecimal;
} duty_cycle_hc;

/* struct da temperatura do aquecedor */
typedef struct temperatura_aquecedor
{
	int iTemperaturaHInteiro;
	int iTemperaturaHDecimal;
} temperatura_aquecedor;

/* globals */
unsigned char ucEstadoAtual = IDDLE;
int iHabilitarBotao = 0; /* (= 0) se desabilitar botao, (= 1) habilitar botao */


float fTemperaturaDesejada = 0.0;
float fTemperaturaDesejadaTemporaria = 0.0;
float fVelocidadeCoolerDesejada = 0.0;
float fVelocidadeCoolerDesejadaTemporaria = 0.0;


char cLeituraTemperatura[10];
char cVelocidadeCooler[10];

float fDutyCoolerMaquinaEstados;
float fDutyHeaterMaquinaEstados;
duty_cycle_hc dutyCycleHC;
temperatura_aquecedor temperaturaH;

extern unsigned int uiTacometroRpm;
extern float fLeituraTemperatura;
extern float fPidAquecedor;
extern pid_data_type pidConfig;

/* *************************************************** */
/* Method name:        communicationStateMachineStart  */
/* Method description: Implementacao da maquina de     */
/*                     estados com comunicacao de      */
/*                     transmissao serial              */
/* Input params:       cReceivedChar                   */
/*                     Caracter para indicar o comando */
/*                     que a maquina de estado deve    */
/*                     realizar                        */
/* Output params:      n/a                             */
void communicationStateMachineStart(char cReceivedChar){

	static char cVelocidadeCooler[10];
	static char cTemperatura[10];
	static char cGanhoKp[10];
	static char cGanhoKi[10];
	static char cGanhoKd[10];
	static char cDutyCycleHeater[10];
	static char cDutyCycleCooler[10];
	static int iArrayPosition = 0; /* contador para gravar cada numero no vetor de char */

	if ('#' == cReceivedChar){
		ucEstadoAtual = READY;
		util_putStringSerial("Comando Inicializado");
		util_putSerialLineFeed(); // line feed e carriage return

	} else {
		if (IDDLE != ucEstadoAtual){
			switch(ucEstadoAtual){
				case READY:
					switch(cReceivedChar){
						//////////////////////////////////////////////// APENAS PARA TESTE REMOTO ///////////////////////////////
						case '=':
							screenControl_nextScreen();
							util_putStringSerial("Comando Finalizado");
							util_putSerialLineFeed();
							ucEstadoAtual = IDDLE;
							break;
						case 'h':
							util_putStringSerial("Modo HABILITAR INTERFACE LOCAL selecionado. Aguardando fim de comando (;)");
							util_putSerialLineFeed();
							ucEstadoAtual = HABILITAR_BOTOES;
							break;
						case 'd':
							util_putStringSerial("Modo DESABILITAR INTERFACE LOCAL selecionado. Aguardando fim de comando (;)");
							util_putSerialLineFeed();
							ucEstadoAtual = DESABILITAR_BOTOES;
							break;
						case 'g':
							util_putStringSerial("Modo GET selecionado, escolha o dispositivo a ser lido: ");
							ucEstadoAtual = GET;
							break;
						case 's':
							util_putStringSerial("Modo SET selecionado, escolha o dispositivo a ser configurado: ");
							ucEstadoAtual = SET;
							break;
						default:
							util_putStringSerial("Comando Finalizado");
							util_putSerialLineFeed();
							ucEstadoAtual = IDDLE;
					}
					break;

				case HABILITAR_BOTOES:
					switch(cReceivedChar){
						case ';':
							iHabilitarBotao = BOTAO_HABILITADO;
							util_putStringSerial("Interface local HABILITADA");
							util_putSerialLineFeed();
							ucEstadoAtual = IDDLE;
							break;
						default:
							util_putStringSerial("Comando Finalizado");
							util_putSerialLineFeed();
							ucEstadoAtual = IDDLE;
					}
					break;

				case DESABILITAR_BOTOES:
					switch(cReceivedChar){
						case ';':
							iHabilitarBotao = BOTAO_DESABILITADO;
							util_putStringSerial("Interface local DESABILITADA");
							util_putSerialLineFeed();
							ucEstadoAtual = IDDLE;
							break;
						default:
							util_putStringSerial("Comando Finalizado");
							util_putSerialLineFeed();
							ucEstadoAtual = IDDLE;
					}
					break;

				case GET:
					switch(cReceivedChar){
						case 't':
							util_putSerialLineFeed();
							util_putStringSerial("Dispositivo AQUECEDOR selecionado. Aguardando fim de comando (;)");
							util_putSerialLineFeed();
							ucEstadoAtual = GET_TEMPERATURA;
							break;
						case 'c':
							util_putSerialLineFeed();
							util_putStringSerial("Dispositivo COOLER selecionado. Aguardando fim de comando (;)");
							util_putSerialLineFeed();
							ucEstadoAtual = GET_COOLER;
							break;
						default:
							util_putStringSerial("Comando Finalizado");
							util_putSerialLineFeed();
							ucEstadoAtual = IDDLE;
					}
					break;

				case SET:
					switch(cReceivedChar){
						case 't':
							util_putSerialLineFeed();
							util_putStringSerial("Digite a TEMPERATURA desejada (MAX: 90): ");
							ucEstadoAtual = SET_TEMPERATURA;
							break;
						case 'c':
							util_putSerialLineFeed();
							util_putStringSerial("Digite o DUTY CYCLE do cooler desejado (MAX: 1): ");
							ucEstadoAtual = SET_COOLER;
							break;
						case 'p':
							util_putSerialLineFeed();
							util_putStringSerial("Digite a ganho Kp desejado: ");
							ucEstadoAtual = SET_KP;
							break;
						case 'i':
							util_putSerialLineFeed();
							util_putStringSerial("Digite a ganho Ki desejado: ");
							ucEstadoAtual = SET_KI;
							break;
						case 'd':
							util_putSerialLineFeed();
							util_putStringSerial("Digite a ganho Kd desejado: ");
							ucEstadoAtual = SET_KD;
							break;
						default:
							util_putSerialLineFeed();
							util_putStringSerial("Comando Finalizado");
							util_putSerialLineFeed();
							ucEstadoAtual = IDDLE;
					}
					break;

				case GET_TEMPERATURA:
					switch(cReceivedChar){
						case ';':
							util_putStringSerial("Temperatura: ");
							temperaturaH.iTemperaturaHInteiro = (int) fLeituraTemperatura;
							temperaturaH.iTemperaturaHDecimal = (fLeituraTemperatura - temperaturaH.iTemperaturaHInteiro)*100;
							sprintf(cLeituraTemperatura, "%d.%d", temperaturaH.iTemperaturaHInteiro, temperaturaH.iTemperaturaHDecimal);
							util_putStringSerial(cLeituraTemperatura);
							util_putSerialLineFeed();


							util_putStringSerial("Duty Cycle Aquecedor: ");
							dutyCycleHC.iDutyCycleHCInteiro = (int) fPidAquecedor; /* parte inteira do valor do duty cycle do aquecedor */
							dutyCycleHC.iDutyCycleHCDecimal = (fPidAquecedor - dutyCycleHC.iDutyCycleHCInteiro)*10; /* 1 casa decimal do duty cycle do aquecedor */
							sprintf(cDutyCycleHeater, "%d.%d", dutyCycleHC.iDutyCycleHCInteiro, dutyCycleHC.iDutyCycleHCDecimal);
							util_putStringSerial(cDutyCycleHeater);
							util_putSerialLineFeed();
							ucEstadoAtual = IDDLE;
							break;
						default:
							util_putStringSerial("Comando Finalizado");
							util_putSerialLineFeed();
							ucEstadoAtual = IDDLE;
					}
					break;

				case GET_COOLER:
					switch(cReceivedChar){
						case ';':
							sprintf(cVelocidadeCooler, "%d", uiTacometroRpm);
							util_putStringSerial("RPM: ");
							util_putStringSerial(cVelocidadeCooler);
							util_putSerialLineFeed();


							util_putStringSerial("Duty Cycle Cooler: ");
							dutyCycleHC.iDutyCycleHCInteiro = (int) (fVelocidadeCoolerDesejada*100); /* parte inteira do valor do duty cycle do aquecedor */
							sprintf(cDutyCycleCooler, "%d", dutyCycleHC.iDutyCycleHCInteiro);
							util_putStringSerial(cDutyCycleCooler);
							util_putStringSerial("%");
							util_putSerialLineFeed();


							ucEstadoAtual = IDDLE;
							break;
						default:
							util_putStringSerial("Comando Finalizado");
							util_putSerialLineFeed();
							ucEstadoAtual = IDDLE;
					}
					break;



				case SET_TEMPERATURA:
					if ('-' == cReceivedChar){
						util_putSerialLineFeed();
						util_putStringSerial("Comando invalido. Aguardando novo comando.");
						util_putSerialLineFeed();
						for(int i=0;i<10;i++){cTemperatura[i]=0;}
						iArrayPosition = 0;
						ucEstadoAtual = IDDLE;
						break;
					}
					if ((cReceivedChar >= '0' && cReceivedChar <= '9') || '.' == cReceivedChar || '-' == cReceivedChar){
						cTemperatura[iArrayPosition++] = cReceivedChar;
						break;
					}
					switch(cReceivedChar){
						case ';':
							fTemperaturaDesejadaTemporaria = (float)atof(cTemperatura);
							if ((TEMPERATURA_MAXIMA >= fTemperaturaDesejadaTemporaria) && (TEMPERATURA_MINIMA <= fTemperaturaDesejadaTemporaria)){
								fTemperaturaDesejada = (float)atof(cTemperatura);
								util_putSerialLineFeed();
								util_putStringSerial("Nova temperatura foi configurada.");
								util_putSerialLineFeed();
							} else if (TEMPERATURA_MAXIMA < fTemperaturaDesejadaTemporaria){
								fVelocidadeCoolerDesejada = 1; /* Se a temperatura eh maior do que a maxima, o cooler eh ligado ao maximo e o aquecedor desligado */
								fTemperaturaDesejada = 0;
								util_putSerialLineFeed();
								util_putStringSerial("A temperatura nao pode ser superior a 90.");
								util_putSerialLineFeed();
							} else{
								util_putSerialLineFeed();
								util_putStringSerial("A temperatura nao pode ser negativa.");
								util_putSerialLineFeed();
							}
							for(int i=0;i<10;i++){cTemperatura[i]=0;}
							iArrayPosition = 0;
							ucEstadoAtual = IDDLE;
							break;
						default:
							for(int i=0;i<10;i++){cTemperatura[i]=0;}
							iArrayPosition = 0;
							util_putSerialLineFeed();
							util_putStringSerial("Comando invalido. Aguardando novo comando.");
							util_putSerialLineFeed();
							ucEstadoAtual = IDDLE;
					}
					break;

				case SET_COOLER:
					if ('-' == cReceivedChar){
						util_putSerialLineFeed();
						util_putStringSerial("Comando invalido. Aguardando novo comando.");
						util_putSerialLineFeed();
						for(int i=0;i<10;i++){cVelocidadeCooler[i]=0;}
						iArrayPosition = 0;
						ucEstadoAtual = IDDLE;
						break;
					}
					if ((cReceivedChar >= '0' && cReceivedChar <= '9') || '.' == cReceivedChar){
						cVelocidadeCooler[iArrayPosition++] = cReceivedChar;
						break;
					}
					switch(cReceivedChar){
						case ';':
							fVelocidadeCoolerDesejadaTemporaria = (float)atof(cVelocidadeCooler);
							if ((DUTY_CYCLE_MAXIMO >= fVelocidadeCoolerDesejadaTemporaria) && (DUTY_CYCLE_MINIMO <= fVelocidadeCoolerDesejadaTemporaria)){
								fVelocidadeCoolerDesejada = (float)atof(cVelocidadeCooler);
								util_putSerialLineFeed();
								util_putStringSerial("Novo duty cycle do cooler foi configurado.");
								util_putSerialLineFeed();
							} else{
								util_putSerialLineFeed();
								util_putStringSerial("O duty cycle do cooler nao pode ser maior do que 1. Apenas valores entre 0 e 1 sao validos.");
								util_putSerialLineFeed();
							}
							for(int i=0;i<10;i++){cVelocidadeCooler[i]=0;}
							iArrayPosition = 0;
							ucEstadoAtual = IDDLE;
							break;
					}
					break;

				case SET_KP:
					if ((cReceivedChar >= '0' && cReceivedChar <= '9') || '.' == cReceivedChar){
						cGanhoKp[iArrayPosition++] = cReceivedChar;
						break;
					}
					switch(cReceivedChar){
						case ';':
							pidConfig.fKp = (float)atof(cGanhoKp);
							for(int i=0;i<10;i++){cGanhoKp[i]=0;}
							iArrayPosition = 0;
							util_putSerialLineFeed();
							util_putStringSerial("Novo ganho Kp foi configurado.");
							util_putSerialLineFeed();
							ucEstadoAtual = IDDLE;
							break;
						default:
							for(int i=0;i<10;i++){cGanhoKp[i]=0;}
							iArrayPosition = 0;
							util_putSerialLineFeed();
							util_putStringSerial("Comando invalido. Aguardando novo comando.");
							util_putSerialLineFeed();
							ucEstadoAtual = IDDLE;
					}
					break;

				case SET_KI:
					if ((cReceivedChar >= '0' && cReceivedChar <= '9') || '.' == cReceivedChar){
						cGanhoKi[iArrayPosition++] = cReceivedChar;
						break;
					}
					switch(cReceivedChar){
						case ';':
							pidConfig.fKi = (float)atof(cGanhoKi);
							for(int i=0;i<10;i++){cGanhoKi[i]=0;}
							iArrayPosition = 0;
							util_putSerialLineFeed();
							util_putStringSerial("Novo ganho Ki foi configurado.");
							util_putSerialLineFeed();
							ucEstadoAtual = IDDLE;
							break;
						default:
							for(int i=0;i<10;i++){cGanhoKi[i]=0;}
							iArrayPosition = 0;
							util_putSerialLineFeed();
							util_putStringSerial("Comando invalido. Aguardando novo comando.");
							util_putSerialLineFeed();
							ucEstadoAtual = IDDLE;
					}
					break;

				case SET_KD:
					if ((cReceivedChar >= '0' && cReceivedChar <= '9') || '.' == cReceivedChar){
						cGanhoKd[iArrayPosition++] = cReceivedChar;
						break;
					}
					switch(cReceivedChar){
						case ';':
							pidConfig.fKd = (float)atof(cGanhoKd);
							for(int i=0;i<10;i++){cGanhoKd[i]=0;}
							iArrayPosition = 0;
							util_putSerialLineFeed();
							util_putStringSerial("Novo ganho Kd foi configurado.");
							util_putSerialLineFeed();
							ucEstadoAtual = IDDLE;
							break;
						default:
							for(int i=0;i<10;i++){cGanhoKd[i]=0;}
							iArrayPosition = 0;
							util_putSerialLineFeed();
							util_putStringSerial("Comando invalido. Aguardando novo comando.");
							util_putSerialLineFeed();
							ucEstadoAtual = IDDLE;
					}
					break;
			}
		}
	}

}
