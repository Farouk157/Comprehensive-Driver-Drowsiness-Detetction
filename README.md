# Comprehinesive Driver Drowsiness Detetction

## Project main goal and outcome
This project is primarily aimed at reducing the number of road accidents by focusing on the detection of driver drowsiness. It recognizes that drowsy driving is a major contributor to accidents and aims to mitigate this risk. By alerting the driver when they are in a drowsy state, the project seeks to raise awareness and prompt the driver to take necessary actions to prevent accidents. The impact of this project is significant as it directly addresses a leading cause of road accidents, potentially saving lives and reducing injuries on the road.

## Features 
    1- driver drowsy state detection through both:
          A- non-physical connection [Night Vision Camera]
          B- contact sensor:
              - FSR (Force Sensitive Resistor)
    2- Alerting the driver through:-
          - Vibrating disk
          - TFT display
          - Buzzer        
    3- communication with road emergency in worst case through:
          - GSM (Global System Mobile)
          - GPS (Global Position System)
    4- Interaction response from the Driver through:
          - Push Button

### For the Raspberry pi and Camera 
    - You will find here the code of raspberry pi and camera which is written and devoloped in python, with the model used and the Algorithm for the Camera was mainly depends on the (68-Face Landmarks),dlib, Convex Hull with computer vision to detect and predict the euclidean distance of the 6 points of each eye. 
### For The STM32F401CCU6  
    - You will also find here the drivers of the STM32F401CCU6 Microcontroller that are used in the project and the drivers for the electronics and components used.
#### For the Main Algorithm
    - It's a hyper Algorithm that means it's a combination of Event Triggering and Time Triggering alogrithm and that to make sure to get the highest Determinism and Responsiveness to the system. 
    - The Camera and RPi are connected to the STM32 through the UART communication protocol and if the camera detected any drowsiness the RPi will send data to the STM32 and once STM32 receives these data in its UART the interrupt of UART being fired and turnning on          the Alarm system.
    - On the other hand the STM32 is looping on the FSR which is attached to the steering wheel to detect the grip strength of the driver on the steering wheel if his pressure was lower than the THRESHOLD so the turning on warning system function will be executed.
    - Inside the warning system or alerting system we set the SYSTICK timer for 5 seconds if the driver didn't respond to the alerting system by pressing the push button after the 5 second the interrupt of the SYSTICK will be fired and inside its ISR it will               activate the GSM and GPS to send warning message and location of the vehicle to the emergency road and services.





          
