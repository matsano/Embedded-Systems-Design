/* ***************************************************************** */
/* File name:        pid.c                                           */
/* File description: This file has a couple of useful functions to   */
/*                   control the implemented PID controller          */
/* Author name:      julioalvesMS, IagoAF, rBacurau                  */
/* Creation date:    21jun2018                                       */
/* Revision date:    12jun2020                                       */
/* ***************************************************************** */

#include "pid.h"
#include "filaCircularTam50.h"

pid_data_type pidConfig;


/* ************************************************ */
/* Method name:        pid_init                     */
/* Method description: Initialize the PID controller*/
/*                     with default gains           */
/* Input params:       n/a                          */
/* Output params:      n/a                          */
/* ************************************************ */
void pid_init(void)
{

	/* Por tentativa e erro */
	pidConfig.fKp = 12.21;
	pidConfig.fKd = 0.08;
	pidConfig.fKi = 0.7;
	pidConfig.fSetValue_previous = 0;

	/* Por metodo */
	//pidConfig.fKp = 1233.323;
	//pidConfig.fKd = 0.26;
	//pidConfig.fKi = 0.065;

}

/* ************************************************ */
/* Method name:        pid_restoreDefaults          */
/* Method description: reinitialize gains as zero   */
/* Input params:       n/a                          */
/* Output params:      n/a                          */
/* ************************************************ */
void pid_zeroGains(void)
{
	pidConfig.fKp = 0.0;
	pidConfig.fKd = 0.0;
	pidConfig.fKi = 0.0;
	pidConfig.fSetValue_previous = 0;
}


/* ************************************************** */
/* Method name:        pid_setKp                      */
/* Method description: Set a new value for the PID    */
/*                     proportional constant          */
/* Input params:       fKp: New value                 */
/* Output params:      n/a                            */
/* ************************************************** */
void pid_setKp(float fKp)
{
	pidConfig.fKp = fKp;
}


/* ************************************************** */
/* Method name:        pid_getKp                      */
/* Method description: Get the value from the PID     */
/*                     proportional constant          */
/* Input params:       n/a                            */
/* Output params:      float: Value                   */
/* ************************************************** */
float pid_getKp(void)
{
	return pidConfig.fKp;
}


/* ************************************************** */
/* Method name:        pid_setKi                      */
/* Method description: Set a new value for the PID    */
/*                     integrative constant           */
/* Input params:       fKi: New value                 */
/* Output params:      n/a                            */
/* ************************************************** */
void pid_setKi(float fKi)
{
	pidConfig.fKi = fKi;
}


/* ************************************************** */
/* Method name:        pid_getKi                      */
/* Method description: Get the value from the PID     */
/*                     integrative constant           */
/* Input params:       n/a                            */
/* Output params:      float: Value                   */
/* ************************************************** */
float pid_getKi(void)
{
	return pidConfig.fKi;
}


/* ************************************************** */
/* Method name:        pid_setKd                      */
/* Method description: Set a new value for the PID    */
/*                     derivative constant            */
/* Input params:       fKd: New value                 */
/* Output params:      n/a                            */
/* ************************************************** */
void pid_setKd(float fKd)
{
	pidConfig.fKd = fKd;
}


/* ************************************************** */
/* Method name:        pid_getKd                      */
/* Method description: Get the value from the PID     */
/*                     derivative constant            */
/* Input params:       n/a                            */
/* Output params:      float: Value                   */
/* ************************************************** */
float pid_getKd(void)
{
	return pidConfig.fKd;
}


/* ************************************************** */
/* Method name:        pid_updateData                 */
/* Method description: Update the control output      */
/*                     using the reference and sensor */
/*                     value                          */
/* Input params:       fSensorValue: Value read from  */
/*                     the sensor                     */
/*                     fReferenceValue: Value used as */
/*                     control reference              */
/* Output params:      float: New Control effort     */
/* ************************************************** */
float pidUpdateData(float fSensorValue, float fSetValue)
{
	float fError, fDifference, fOut;

	/*
	 * Zera o erro integrativo quando o controlador receber
	 * uma nova temperatura de referencia
	*/
	if (fSetValue != pidConfig.fSetValue_previous){
		inicializarFilaTam50();
	}

	fError = fSetValue - fSensorValue;
	adicionarElementoFilaTam50(fError);
	fDifference = fError - obterElementoAnteriorTam50();

	fOut = pidConfig.fKp*fError
		 + pidConfig.fKi*obterSomatoriaElementosTam50()
		 + pidConfig.fKd*fDifference;

	pidConfig.fSetValue_previous = fSetValue;

	if (fOut>100.0)
		fOut = 100.0;

	else if (fOut<0.0)
		fOut = 0.0;

	return fOut;
}
