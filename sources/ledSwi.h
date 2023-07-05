/* ***************************************************************** */
/* File name:        ledSwi.h                                        */
/* File description: Header file containing the prototypes of the    */
/*                   functions used to configure and use buttons     */
/*                   and leds                                        */
/*                                                                   */
/* Author name:      Igor B Teixeira                                 */
/*                   Matheus S Sano                                  */
/* Creation date:    28mar2022                                       */
/* Revision date:    04abr2022                                       */
/* ***************************************************************** */

#ifndef SOURCES_LEDSWI_H_
#define SOURCES_LEDSWI_H_

#define CLOCK_PORTA 0x200;


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
int initializeLedSwi(char cPino1, char cPino2, char cPino3, char cPino4);



/* ************************************************ */
/* Method name: 	   readSwitch	         		*/
/* Method description: Adquiri o valor atual do pino */
/*                     escolhido                    */
/* Input params:	   iEscolha                     */
/*                     eh o numero do botao que     */
/*                     sera lido (1, 2, 3 ou 4)     */
/* Output params:	   n/a 							*/
/* ************************************************ */
int readSwitch(int iEscolha);



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
int writeLed(int iEscolha, int iValor);



/* ************************************************ */
/* Method name: 	   turnOnLed	         		*/
/* Method description: Ligar o LED                  */
/* Input params:	   iEscolha                     */
/*                     eh o numero do LED que       */
/*                     sera ligado (1, 2, 3 ou 4)   */
/* Output params:	   n/a 							*/
/* ************************************************ */
int turnOnLed(int iEscolha);



/* ************************************************ */
/* Method name: 	   turnOffLed	         		*/
/* Method description: Desligar o LED               */
/* Input params:	   iEscolha                     */
/*                     eh o numero do LED que       */
/*                     sera desligado (1, 2, 3 ou 4)*/
/* Output params:	   n/a 							*/
/* ************************************************ */
int turnOffLed(int iEscolha);



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
int toggleLed(int iEscolha);



#endif /* SOURCES_LEDSWI_H_ */
