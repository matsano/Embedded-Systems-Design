/* ***************************************************************** */
/* File name:		 screenControl.h				     			 */
/* File description: Header file containing the functions/methods    */
/*                   interfaces for using the local interface        */
/* Author name:      Igor B Teixeira                                 */
/*                   Matheus S Sano                                  */
/* Creation date:    11jun2022										 */
/* Revision date:    26jun2022										 */
/* ***************************************************************** */

#ifndef SOURCES_SCREENCONTROL_H_
#define SOURCES_SCREENCONTROL_H_

#define SCREEN_INITIAL 0
#define SCREEN_SET_TEMP 1
#define SCREEN_SET_COOLER 2
#define SCREEN_ENABLE_LED_RGB 3
#define SCREEN_SET_KP 4
#define SCREEN_SET_KI 5
#define SCREEN_SET_KD 6
#define SCREEN_FINAL 6

void screenControl_nextScreen(void);

void screenControl_previousScreen(void);

void screenControl_chooseScreen(int iScreenChoosed);

void screenControl_adjustVariable(char cEscolha);

void screenControl_updateScreen(void);


#endif /* SOURCES_SCREENCONTROL_H_ */
