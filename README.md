# Embedded-Systems-Design
Embedded Systems Design Course Project

## 📋 Description
The developed project consists of a temperature controller using the FRDM KL25 development kit coupled to the MCLAB2 peripheral board.

The main objective is to control the peripheral board heater temperature, implementing remote communication via UART and local communication via interface. A state machine was implemented to control the temperature, allowing the user to adjust parameters such as the cooler's speed, the desired temperature and the PID controller gains.

Communication with the system is done through serial communication via UART, using the Putty terminal, and also through a local interface with buttons and an LCD board. The state machine is also used to manage user interaction with the local interface.

The system has a PID controller with predefined gains, but the user can change these values either through remote communication or through the local interface. An interrupt is used to update the controller with the current temperature, set point, and to obtain cooler's and heater's information such as the cooler's speed in RPM and the average of the last 5 heater's temperatures.

Some additional features have been implemented, such as turning off the heater and turning on the cooler at maximum if the set point is greater than 90°C, and the use of the FRDM-KL25Z's RGB LED to indicate the duty cycle of the heater through the color of the LED.

## 🛠️ Software used

This project was implemented in C on the [Kinetis Design Studio IDE](https://www.nxp.com/design/designs/design-studio-integrated-development-environment-ide:KDS_IDE).

## ✒️ Authors

- Igor BARROS TEIXEIRA:
    - [![GitHub](https://i.stack.imgur.com/tskMh.png) GitHub](https://github.com/igor-bt)
- Matheus SANTOS SANO:
    - [![GitHub](https://i.stack.imgur.com/tskMh.png) GitHub](https://github.com/matsano)

We would like to thank our professor Mr. Rodrigo Moreira Bacurau for the knowledge taught in Embedded Systems Design Course at [UNICAMP](https://www.unicamp.br/unicamp/) which were essential for the realization of this project.
