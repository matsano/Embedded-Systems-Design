/* ***************************************************************** */
/* File name:        util.c                                          */
/* File description: This file has a couple of useful functions to   */
/*                   make programming more productive                */
/*                                                                   */
/*                   Remarks: The soft delays consider               */
/*                   core clock @ 40MHz                              */
/*                   bus clock @ 20MHz                               */
/*                                                                   */
/* Author name:      dloubach                                        */
/*                   Igor B Teixeira                                 */
/*                   Matheus S Sano                                  */
/* Creation date:    09jan2015                                       */
/* Revision date:    24mai2022                                       */
/* ***************************************************************** */

#include <stdio.h>
#include "util.h"
#include "string.h"
/* system includes */
#include "fsl_clock_manager.h"
#include "fsl_device_registers.h"
#include "fsl_port_hal.h"
#include "fsl_smc_hal.h"
#include "fsl_debug_console.h"

/* ************************************************ */
/* Method name:        util_genDelay088us           */
/* Method description: generates ~ 088 micro sec    */
/* Input params:       n/a                          */
/* Output params:      n/a                          */
/* ************************************************ */
void util_genDelay088us(void)
{
    char i;
    for(i=0; i<120; i++)
    {
        __asm("NOP");
        __asm("NOP");
        __asm("NOP");
        __asm("NOP");
        __asm("NOP");
        __asm("NOP");
        __asm("NOP");
        __asm("NOP");
        __asm("NOP");
        __asm("NOP");
        __asm("NOP");
        __asm("NOP");
        __asm("NOP");
        __asm("NOP");
        __asm("NOP");
    }
}



/* ************************************************ */
/* Method name:        util_genDelay250us           */
/* Method description: generates ~   250 micro sec  */
/* Input params:       n/a                          */
/* Output params:      n/a                          */
/* ************************************************ */
void util_genDelay250us(void)
{
    char i;
    for(i=0; i<120; i++)
    {
        __asm("NOP");
        __asm("NOP");
        __asm("NOP");
        __asm("NOP");
        __asm("NOP");
        __asm("NOP");
        __asm("NOP");
        __asm("NOP");
        __asm("NOP");
        __asm("NOP");
    }
    util_genDelay088us();
    util_genDelay088us();
}



/* ************************************************ */
/* Method name:        util_genDelay1ms             */
/* Method description: generates ~   1 mili sec     */
/* Input params:       n/a                          */
/* Output params:      n/a                          */
/* ************************************************ */
void util_genDelay1ms(void)
{
    util_genDelay250us();
    util_genDelay250us();
    util_genDelay250us();
    util_genDelay250us();
}


/* ************************************************ */
/* Method name:        util_genDelay10ms            */
/* Method description: generates ~   10 mili sec    */
/* Input params:       n/a                          */
/* Output params:      n/a                          */
/* ************************************************ */
void util_genDelay10ms(void)
{
    util_genDelay1ms();
    util_genDelay1ms();
    util_genDelay1ms();
    util_genDelay1ms();
    util_genDelay1ms();
    util_genDelay1ms();
    util_genDelay1ms();
    util_genDelay1ms();
    util_genDelay1ms();
    util_genDelay1ms();
}



/* ************************************************ */
/* Method name:        util_genDelay100ms           */
/* Method description: generates ~   100 mili sec   */
/* Input params:       n/a                          */
/* Output params:      n/a                          */
/* ************************************************ */
void util_genDelay100ms(void)
{
    util_genDelay10ms();
    util_genDelay10ms();
    util_genDelay10ms();
    util_genDelay10ms();
    util_genDelay10ms();
    util_genDelay10ms();
    util_genDelay10ms();
    util_genDelay10ms();
    util_genDelay10ms();
    util_genDelay10ms();
}

/* ************************************************ */
/* Method name:        util_genDelay500ms           */
/* Method description: generates ~   500 mili sec   */
/* Input params:       n/a                          */
/* Output params:      n/a                          */
/* ************************************************ */
void util_genDelay500ms(void)
{
    util_genDelay100ms();
    util_genDelay100ms();
    util_genDelay100ms();
    util_genDelay100ms();
    util_genDelay100ms();
}

/* ************************************************ */
/* Method name:        util_genDelay1000ms          */
/* Method description: generates ~   1000 mili sec  */
/* Input params:       n/a                          */
/* Output params:      n/a                          */
/* ************************************************ */
void util_genDelay1000ms(void)
{
    util_genDelay100ms();
    util_genDelay100ms();
    util_genDelay100ms();
    util_genDelay100ms();
    util_genDelay100ms();
    util_genDelay100ms();
    util_genDelay100ms();
    util_genDelay100ms();
    util_genDelay100ms();
    util_genDelay100ms();
}




/* ****************************************************** */
/* Method name:        util_putStringSerial               */
/* Method description: Implementação de comunicação       */
/*                     por meio da transmissao            */
/*                     serial de dados                    */
/* Input params:       cString                            */
/*                     Caracter que deve ser transmitido  */
/*                     de forma serial                    */
/* Output params:      n/a                                */
/* ****************************************************** */
void util_putStringSerial(char* cString){

	for (int i=0; i<strlen(cString); i++){
		debug_putchar((int)*(cString+i));
	}
}



/* ************************************************ */
/* Method name:        util_putSerialLineFeed       */
/* Method description: Implementar uma quebra de    */
/*                     linha na transmissao serial  */
/*                     de dados                     */
/* Input params:       n/a                          */
/* Output params:      n/a                          */
/* ************************************************ */
void util_putSerialLineFeed(void){
	static char cLineFeed[2] = {10, 13};
	util_putStringSerial(cLineFeed);
}



