/* ***************************************************************** */
/* File name:        aquecedorECooler.h                              */
/* File description: Header file containing the functions/methods    */
/*                   interfaces for setting up and manipulating      */
/*                   the TPM modules to generate PWM signals for     */
/*                   heater and cooler control                       */
/* Author name:      Igor B Teixeira                                 */
/*                   Matheus S Sano                                  */
/* Creation date:    25abr2022                                       */
/* Revision date:    28abr2022                                       */
/* ***************************************************************** */


#ifndef SOURCES_AQUECEDORECOOLER_H_
#define SOURCES_AQUECEDORECOOLER_H_

/* *************************************************** */
/* Method name:        PWM_init                        */
/* Method description: Initialize the 0 and 1 channels */
/*                     of TPM1 as Edge-Aligned PWM and */
/*                     configure both signals PWM with */
/*                     frequency between 5 and 20 Hz   */
/* Input params:       n/a                             */
/* Output params:      n/a                             */
/* *************************************************** */
void PWM_init(void);



/* *************************************************** */
/* Method name:        coolerfan_init                  */
/* Method description: Initialize and release the PWM  */
/*                     signal on the cooler            */
/* Input params:       n/a                             */
/* Output params:      n/a                             */
/* *************************************************** */
void coolerfan_init(void);



/* *************************************************** */
/* Method name:        heater_init                     */
/* Method description: Initialize and release the PWM  */
/*                     signal on the heater            */
/* Input params:       n/a                             */
/* Output params:      n/a                             */
/* *************************************************** */
void heater_init(void);



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
void coolearfan_PWMDuty(float fCoolerDuty);



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
void heater_PWMDuty(float fHeaterDuty);



#endif /* SOURCES_AQUECEDORECOOLER_H_ */
