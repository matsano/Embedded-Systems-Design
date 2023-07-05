/* ***************************************************************** */
/* File name:		 screenControl.c				     			 */
/* File description: File dedicated to use the local interface       */
/* Author name:      Igor B Teixeira                                 */
/*                   Matheus S Sano                                  */
/* Creation date:    11jun2022										 */
/* Revision date:    26jun2022										 */
/* ***************************************************************** */

#include "screenControl.h"
#include "lcd.h"
#include "pid.h"

#define LIGADO 1
#define DESLIGADO 0
#define TEMP_MAX 90

extern float fPidAquecedor;
extern float fVelocidadeCoolerDesejada;
extern float fTemperaturaDesejada;
extern float fLeituraTemperatura;
extern unsigned int uiTacometroRpm;
extern int iEnableLedRGB;

int iCurrentScreen = 0; // Tela inicial sera mostrada quando o software for iniciado

void screenControl_nextScreen(){
	/* Se chegar na ultima tela volta para a primeira */
	if (SCREEN_FINAL == iCurrentScreen){
		iCurrentScreen = SCREEN_INITIAL;
	}
	else {
		iCurrentScreen += 1;
	}

	lcd_sendCommand(CMD_CLEAR);
	screenControl_updateScreen();
}

void screenControl_previousScreen(){
	/* Se chegar na primeira tela vai para a ultima */
	if (SCREEN_INITIAL == iCurrentScreen){
		iCurrentScreen = SCREEN_FINAL;
	}
	else {
		iCurrentScreen -= 1;
	}

	lcd_sendCommand(CMD_CLEAR);
	screenControl_updateScreen();
}

void screenControl_chooseScreen(int iScreenChoosed){
	/* Verifica se o numero da tela escolhida eh valido */
	if (SCREEN_INITIAL < iScreenChoosed && SCREEN_FINAL > iScreenChoosed){
		iCurrentScreen = iScreenChoosed;
	}

	lcd_sendCommand(CMD_CLEAR);
	screenControl_updateScreen();
}



void screenControl_adjustVariable(char cEscolha){
	switch(iCurrentScreen){
			case SCREEN_INITIAL:
				/* Nao faz nada */
				break;

			case SCREEN_SET_TEMP:
				if ('+' == cEscolha){
					if (TEMP_MAX > (fTemperaturaDesejada+0.5)){
						fTemperaturaDesejada += 0.5;
					}

				}
				else if ('-' == cEscolha){
					if (0 < (fTemperaturaDesejada-0.5)){
						fTemperaturaDesejada -= 0.5;
					}

				}
				break;

			case SCREEN_SET_COOLER:
				if ('+' == cEscolha){
					if (1 > (fVelocidadeCoolerDesejada+0.05)){
						fVelocidadeCoolerDesejada += 0.05;
					}

				}
				else if ('-' == cEscolha){
					if (0 < (fVelocidadeCoolerDesejada-0.05)){
						fVelocidadeCoolerDesejada -= 0.05;
					}

				}
				break;

			case SCREEN_ENABLE_LED_RGB:
				if ('+' == cEscolha){
					iEnableLedRGB = LIGADO;
				}
				else if ('-' == cEscolha){
					iEnableLedRGB = DESLIGADO;
				}
				break;

			case SCREEN_SET_KP:
				if ('+' == cEscolha){
					pid_setKp(pid_getKp() + 0.05);
				}
				else if ('-' == cEscolha){
					if (0 < (pid_getKp()-0.05)){
						pid_setKp(pid_getKp() - 0.05);
					}
					else {
						pid_setKp(0);
					}
				}
				break;

			case SCREEN_SET_KI:
				if ('+' == cEscolha){
					pid_setKi(pid_getKi() + 0.05);
				}
				else if ('-' == cEscolha){
					if (0 < (pid_getKi()-0.05)){
						pid_setKi(pid_getKi() - 0.05);
					}
					else {
						pid_setKi(0);
					}

				}
				break;

			case SCREEN_SET_KD:
				if ('+' == cEscolha){
					pid_setKd(pid_getKd() + 0.05);
				}
				else if ('-' == cEscolha){
					if (0 < (pid_getKd()-0.05)){
						pid_setKd(pid_getKd() - 0.05);
					}
					else {
						pid_setKd(0);
					}
				}
				break;

			default:
				/* Nao faz nada */
				break;
		}
}



void screenControl_updateScreen(){
	/* Linha inferior sempre mostra os mesmos valores */
	lcd_sendCommand(CMD_CLEAR);
	lcd_writeFloat("S:", fTemperaturaDesejada, 1, 1, 0);
	lcd_writeFloat("T:", fLeituraTemperatura, 1, 1, 8);
	switch(iCurrentScreen){
		case SCREEN_INITIAL:
			lcd_writeFloat("Aq:", fPidAquecedor, 0, 0, 0);
			lcd_writeFloat("Co:", (int)100*fVelocidadeCoolerDesejada, 0, 0, 8);
			if (100 == fPidAquecedor){
				lcd_setCursor(0,6);
			}
			else {
				lcd_setCursor(0,5);
			}
			lcd_writeString("% ");
			if (1 >= fVelocidadeCoolerDesejada){
				lcd_setCursor(0,14);
			}
			else {
				lcd_setCursor(0,13);
			}
			lcd_writeString("% ");
			break;
		case SCREEN_SET_TEMP:
			lcd_writeFloat("Setpoint: ", fTemperaturaDesejada, 1, 0, 0);
			break;
		case SCREEN_SET_COOLER:

			if (1 >= fVelocidadeCoolerDesejada){
				lcd_writeFloat("Cooler: ", (int)100*fVelocidadeCoolerDesejada, 0, 0, 0);
				lcd_setCursor(0,10);
			}
			else {
				lcd_writeFloat("Cooler: ", (int)100*fVelocidadeCoolerDesejada, 0, 0, 0);
				lcd_setCursor(0,11);
			}
			lcd_writeString("%");
			break;
		case SCREEN_ENABLE_LED_RGB:
			lcd_setCursor(0,0);
			lcd_writeString("LED:");
			lcd_setCursor(0,5);
			if(LIGADO == iEnableLedRGB){
				lcd_writeString("ON ");
			}
			else if(DESLIGADO == iEnableLedRGB){
				lcd_writeString("OFF");
			}
			break;
		case SCREEN_SET_KP:
			lcd_writeFloat("Kp: ", pid_getKp(), 2, 0, 0);
			break;
		case SCREEN_SET_KI:
			lcd_writeFloat("Ki: ", pid_getKi(), 2, 0, 0);
			break;
		case SCREEN_SET_KD:
			lcd_writeFloat("Kd: ", pid_getKd(), 2, 0, 0);
			break;
		default:
			lcd_dummyText();
	}

}

