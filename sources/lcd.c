/* ***************************************************************** */
/* File name:		 lcd_hal.c							 			 */
/* File description: File dedicated to the hardware abstraction layer*/
/*                   related to the LCD HARDWARE based on the KS006U */
/*					 controller										 */
/* Author name:      dloubach										 */
/*                   Igor B Teixeira                                 */
/*                   Matheus S Sano                                  */
/* Creation date:    16out2015										 */
/* Revision date:    11abr2022										 */
/* ***************************************************************** */

#include "lcd.h"
#include "board.h"
#include "util.h"
#include "regManager.h"
#include "display7seg.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

/* line and columns */
#define LINE0		0U
#define COLUMN0		0U

#define L0C0_BASE	0x80 /* line 0, column 0 */
#define L1C0_BASE	0xC0 /* line 1, column 0 */
#define MAX_COLUMN  15U



/* ************************************************ */
/* Method name: 	   lcd_initLcd	         		*/
/* Method description: Initialize the LCD function  */
/* Input params:	   n/a                          */
/* Output params:	   n/a 							*/
/* ************************************************ */
void lcd_initLcd(void)
{
	/* pins configured as outputs */

	/* Libera o clock para o PORT C */
	writeRegister((int*)&SIM_SCGC5, CLOCK_PORTC_PIN, 1);

	/* set pin as gpio */
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

	writeRegister((int*)&PORTC_PCR8, PCR_MUX_2, 0);
	writeRegister((int*)&PORTC_PCR8, PCR_MUX_1, 0);
	writeRegister((int*)&PORTC_PCR8, PCR_MUX_0, 1);

	writeRegister((int*)&PORTC_PCR9, PCR_MUX_2, 0);
	writeRegister((int*)&PORTC_PCR9, PCR_MUX_1, 0);
	writeRegister((int*)&PORTC_PCR9, PCR_MUX_0, 1);


	/* set pin 0-9 as digital output */
	GPIOC_PDDR |= 0x3FF;

	// turn-on LCD, with no cursor and no blink
	lcd_sendCommand(CMD_NO_CUR_NO_BLINK);

	// init LCD
	lcd_sendCommand(CMD_INIT_LCD);

	// clear LCD
	lcd_sendCommand(CMD_CLEAR);

	// LCD with no cursor
	lcd_sendCommand(CMD_NO_CURSOR);

	// cursor shift to right
	lcd_sendCommand(CMD_CURSOR2R);

}



/* ************************************************ */
/* Method name: 	   lcd_write2Lcd         		*/
/* Method description: Send command or data to LCD  */
/* Input params:	   ucBuffer => char to be send  */
/*                   cDataType => command LCD_RS_CMD*/
/*                     or data LCD_RS_DATA          */
/* Output params:	   n/a 							*/
/* ************************************************ */
void lcd_write2Lcd(unsigned char ucBuffer,  unsigned char cDataType)
{
	/* writing data or command */
	writeRegister((int*)LCD_GPIO_BASE_PNT, LCD_RS_PIN, (!(LCD_RS_CMD == cDataType)));

	/* write in the LCD bus */
	writeRegister((int*)LCD_GPIO_BASE_PNT, LCD_DATA_DB0_PIN, ((ucBuffer & (1u << 0u)) >> 0u));
	writeRegister((int*)LCD_GPIO_BASE_PNT, LCD_DATA_DB1_PIN, ((ucBuffer & (1u << 1u)) >> 1u));
	writeRegister((int*)LCD_GPIO_BASE_PNT, LCD_DATA_DB2_PIN, ((ucBuffer & (1u << 2u)) >> 2u));
	writeRegister((int*)LCD_GPIO_BASE_PNT, LCD_DATA_DB3_PIN, ((ucBuffer & (1u << 3u)) >> 3u));
	writeRegister((int*)LCD_GPIO_BASE_PNT, LCD_DATA_DB4_PIN, ((ucBuffer & (1u << 4u)) >> 4u));
	writeRegister((int*)LCD_GPIO_BASE_PNT, LCD_DATA_DB5_PIN, ((ucBuffer & (1u << 5u)) >> 5u));
	writeRegister((int*)LCD_GPIO_BASE_PNT, LCD_DATA_DB6_PIN, ((ucBuffer & (1u << 6u)) >> 6u));
	writeRegister((int*)LCD_GPIO_BASE_PNT, LCD_DATA_DB7_PIN, ((ucBuffer & (1u << 7u)) >> 7u));

	/* enable, delay, disable LCD */
	/* this generates a pulse in the enable pin */
	writeRegister((int*)LCD_GPIO_BASE_PNT, LCD_ENABLE_PIN, LCD_ENABLED);
	util_genDelay1ms();
	writeRegister((int*)LCD_GPIO_BASE_PNT, LCD_ENABLE_PIN, LCD_DISABLED);
	util_genDelay1ms();
	util_genDelay1ms();
}



/* ************************************************ */
/* Method name: 	   lcd_writeData				*/
/* Method description: Write data to be displayed   */
/* Input params:	   ucData => char to be writen  */
/* Output params:	   n/a 							*/
/* ************************************************ */
void lcd_writeData(unsigned char ucData)
{
	/* just a relay to send data */
	lcd_write2Lcd(ucData, LCD_RS_DATA);
}



/* ************************************************ */
/* Method name: 	   lcd_sendCommand				*/
/* Method description: Write command to LCD         */
/* Input params:	   ucCmd => command to be executed*/
/* Output params:	   n/a 							*/
/* ************************************************ */
void lcd_sendCommand(unsigned char ucCmd)
{
	/* just a relay to send command */
	lcd_write2Lcd(ucCmd, LCD_RS_CMD);
}



/* ************************************************ */
/* Method name: 	   lcd_setCursor         		*/
/* Method description: Set cursor line and column 	*/
/* Input params:	   cLine = LINE0..LINE1         */
/*					   cColumn = COLUMN0..MAX_COLUMN*/
/* Output params:	   n/a 							*/
/* ************************************************ */
void lcd_setCursor(unsigned char cLine, unsigned char cColumn)
{
	char cCommand;

	if(LINE0 == cLine)
		/* line 0 */
		cCommand = L0C0_BASE;
	else
		/* line 1 */
		cCommand = L1C0_BASE;

	/* maximum MAX_COLUMN columns */
	cCommand += (cColumn & MAX_COLUMN);

	// send the command to set the cursor
	lcd_sendCommand(cCommand);
}



/* ************************************************ */
/* Method name: 	   lcd_writeString				*/
/* Method description: Write string to be displayed */
/* Input params:	   cBuffer => string to be      */
/*					   written in LCD 				*/
/* Output params:	   n/a 							*/
/* ************************************************ */
void lcd_writeString(const char *cBuffer)
{
	while(*cBuffer)
	{
		lcd_writeData(*cBuffer++);
	};
}


/* ************************************************ */
/* Method name: 	   lcd_writeString				*/
/* Method description: Write string to be displayed */
/* Input params:	   cBuffer => string to be      */
/*					   written in LCD 				*/
/* Output params:	   n/a 							*/
/* ************************************************ */
void lcd_writeFloat(const char *cTextoDesejado, float fNumeroFloat, int iNumeroCasas, int iLinha, int iColuna)
{

	numero_float nfNumeroSeparado;
	nfNumeroSeparado.iParteInteiro = 0;
	nfNumeroSeparado.iParteDecimal = 0;
	char cStringedFloat[10];

	nfNumeroSeparado.iParteInteiro = (int) fNumeroFloat; /* parte inteira do valor*/

	if (0 == iNumeroCasas){
		sprintf(cStringedFloat, "%d", nfNumeroSeparado.iParteInteiro);
	}
	else if (1 == iNumeroCasas){
		nfNumeroSeparado.iParteDecimal = (fNumeroFloat - nfNumeroSeparado.iParteInteiro)*10; /* 1 casa decimal */
		sprintf(cStringedFloat, "%d.%d", nfNumeroSeparado.iParteInteiro, nfNumeroSeparado.iParteDecimal);
	}
	else if (2 == iNumeroCasas){
		nfNumeroSeparado.iParteDecimal = (fNumeroFloat - nfNumeroSeparado.iParteInteiro)*100; /* 2 casas decimais */
		sprintf(cStringedFloat, "%d.%d", nfNumeroSeparado.iParteInteiro, nfNumeroSeparado.iParteDecimal);
	}

	/*
	 * Desabilita o display7seg
	 * Posiciona o cursor, texto, variavel
	 * Habilita o display7seg
	 */
	display7seg_disable();
	lcd_setCursor(iLinha,iColuna);
	lcd_writeString(cTextoDesejado);
	lcd_writeString(cStringedFloat);
	display7seg_enable();

}



/* ************************************************ */
/* Method name: 	   lcd_dummyText				*/
/* Method description: Write a dummy hard coded text*/
/* Input params:	   n/a                          */
/* Output params:	   n/a 							*/
/* ************************************************ */
void lcd_dummyText(void)
{
	// clear LCD
	lcd_sendCommand(CMD_CLEAR);

	// set the cursor line 0, column 1
	lcd_setCursor(0,1);

	// send string
	lcd_writeString("*** ES670 ***");

	// set the cursor line 1, column 0
	lcd_setCursor(1,0);
	lcd_writeString("Prj Sis Embarcad");
}
