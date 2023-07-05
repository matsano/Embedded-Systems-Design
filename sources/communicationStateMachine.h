/* ***************************************************************** */
/* File name:        communicationStateMachine.h                     */
/* File description: Header file containing the functions/methods    */
/*                   interfaces for setting up and manipulating      */
/*                   the 4 7-segment displays from the hardware kit  */
/* Author name:      Igor B Teixeira                                 */
/*                   Matheus S Sano                                  */
/* Creation date:    19mai2022                                       */
/* Revision date:    24mai2022                                       */
/* ***************************************************************** */

#ifndef SOURCES_COMMUNICATIONSTATEMACHINE_H_
#define SOURCES_COMMUNICATIONSTATEMACHINE_H_

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
/* *************************************************** */
void communicationStateMachineStart(char cReceivedChar);


#endif /* SOURCES_COMMUNICATIONSTATEMACHINE_H_ */

