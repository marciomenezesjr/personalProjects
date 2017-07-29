# **Internet of Things Challenge**

* Marcio Jose de Menezes

[//]: # (Image References)

[image1]: 06_Images/InternetOfThings.jpg "IoT Challenge Award"

## **1. Introduction: The SubSpy Project**
This project has been developed for the Internet of Things (IoT) contest and has been awarded the first place on the competition. The project has been dubbed SubSpy, since it is a device to capture network packets (spy) in a sub-GHz (sub) wireless sensor network.

 The competition goal was to design a USB wireless adapter to enable handheld devices to connect to an existing sub-GHz underground wireless sensor network used in a project which targets the monitoring of soil moisture in a reforestation project in Cameroon, but could also serve any other underground monitoring application.

Besides the construction of the wireless adapter, a graphical user interface (GUI) was also required, in order to log the sensor's data as well as graphically plot the sensor's readings. The following criteria ([IoT_Project_Evaluation.pdf](08_References/IoT_Project_Evaluation.pdf)) have been used to evaluate the projects:
* Implementation with least number of components
* Low power consumption
* Successful data reception and visualization
* User friendly graphical interface (voted by all students and professors)
* Cost effective solution

The SubSpy project has excelled in each of the evaluating points, being awarded the first place on the challenge.

![alt text][image1]
Image 1: IoT Challenge award

## **2. Content**
Below, the work developed along this project is listed, for further information, refer to the final project report [finalReportIOT.pdf](07_Final_Report/finalReportIOT_lowResolution.pdf)

* Hardware design of the wireless adapter using EAGLE
* Prototype assembly
* Arduino RFM69CW library ported to Texas Instruments MSP430F5529
* Wireless adapter (SubSpy) firmware development in C programming language
* Graphical User Interface developed in cpp using QT framework
* Power consumption profiling benchmarks using EnergyTrace
