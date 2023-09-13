# EH5IoT-semester-project
The IoT semester project - Retur Temperature Regulation for Fjernvarme
## Table of Contents
- [General Info](#general-info)
- [Technologies](#technologies)
- [Requirements](#requirements)
  - [Functional Requirements](#functional-requirements)
  - [Non-functional Requirements](#non-functional-requirements)

## General Info
This project aims to optimize the return temperature in Fjernvarme systems, allowing for energy savings and contributing to more environmentally friendly district heating. In collaboration with Kredsløb A/S, we strive to maintain return temperatures below 30°C, which qualifies for a bonus.

"Få styr på din fjernvarme og spar penge på din varme

Vidste du, at du kan spare penge på din varmeregning og samtidig bidrage til mere klimavenlig fjernvarme? Hemmeligheden ligger i det, der hedder returtemperatur og god udnyttelse af energien.
Det er temperaturen på det fjernvarmevand, der bliver sendt retur fra dit hjem til varmeværket.
Og er returtemperatur fra din bolig under 30°C, får du en bonus." (www.kredslob.dk)

### About Fjernvarme
Fjernvarme is a district heating system that supplies heat to multiple households from a centralized source. The return temperature refers to the temperature of the water sent back from homes to the heating plant.

### Project Implementation
This system will be implemented using Particle Argon boards, leveraging IoT technology to gather data from weather forecasts.

## Technologies
The following technologies are used in this project:
- Particle Argon for data acquisition and actuator control
- Temperature Sensor: PT500 Kamstrup
- Actuator: 24V Electric Valve
- IoT: Webhooks for weather forecast data

## Requirements
### Functional Requirements
The device must meet the following functional requirements:
- Establish an internet connection via Wi-Fi
- Read data from the connected PT500 temperature sensor
- Control the electric valve actuator
- Utilize data from a web service, such as weather forecast data

### Non-functional Requirements

- Create a public GitHub account and upload relevant project files.
- Upload hardware documentation, schematics, datasheets, and optional PCB layouts in PDF format.
- Upload software files in raw source code format, such as .C, .CPP, .h, .py, etc.
