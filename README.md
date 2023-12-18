# EH5IoT-semester-project
The IoT semester project - Return Temperature Regulation for Fjernvarme
## Table of Contents
- [General Info](#general-info)
- [Technologies](#technologies)
- [Requirements](#requirements)
  - [Functional Requirements](#functional-requirements)
  - [Non-functional Requirements](#non-functional-requirements)

## General Info
This project focuses on optimizing the return temperature in Heating System District ( Fjernvarme ) to enhance energy efficiency and promote environmental sustainability. In collaboration with Kredsløb A/S, we strive to maintain return temperatures below 30°C, which qualifies for a bonus.

"Få styr på din fjernvarme og spar penge på din varme

Vidste du, at du kan spare penge på din varmeregning og samtidig bidrage til mere klimavenlig fjernvarme? Hemmeligheden ligger i det, der hedder returtemperatur og god udnyttelse af energien.
Det er temperaturen på det fjernvarmevand, der bliver sendt retur fra dit hjem til varmeværket.
Og er returtemperatur fra din bolig under 30°C, får du en bonus." (www.kredslob.dk)

### About Fjernvarme
Fjernvarme is a district heating system that supplies heat to multiple households from a centralized source. The return temperature refers to the temperature of the water sent back from homes to the heating plant.

### Project Implementation
This system will be implemented using Particle Photon2 boards, leveraging IoT technology to gather data from weather forecasts and change setpoint after that. 
Logic for setpoint is dynamic depending on the outside temperature.

| Temperature Condition   | Set Point  |
|-------------------------|------------|
| Extreme low temperature (< -3°C) | 40°C       |
| Low temperature (-2°C to 2°C)    | 35°C       |
| Normal temperature (> 3°C)       | 30°C       |

The system will collect data from a temperature sensor RTD PT500 Kamstrup mounted on return pipe .
Data collected from the temperature sensor will by used in an PID controller (Proportional, Integral, Derivative ) able to control the dynamic system. 
- P = Proportional - Kp = Proportional constant (adjust current error)
- I = Integral - Ki = Integral constant ( adjust past error)
- D = Derivative - Kd = Derivative constant (adjust future error)

## Technologies
The following technologies are used in this project:
- Particle Photon2 for data acquisition and actuator control
- Temperature Sensor: PT500 Kamstrup
- Actuator: 24V Electric Valve M3P 46825-30
- IoT: Webhooks for weather forecast data

## Requirements
### Functional Requirements
The device must meet the following functional requirements:
- Establish an internet connection via Wi-Fi
- Read data from the connected PT500 temperature sensor
- Control the electric valve actuator
- Utilize data from a web service, such as weather forecast data to help in controlling the system.

### Non-functional Requirements

- Create a public GitHub account and upload relevant project files.
- Upload hardware documentation, schematics, datasheets, and optional PCB layouts in PDF format.
- Upload software files in raw source code format, such as .C, .CPP, .h, .py, etc.
