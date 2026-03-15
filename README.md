# Seat Belt System
This is an **Embedded System** Project designed to improve an passenger safety during vehicle accidents.The system detects potential accidents using the sensors,
then automatically tightens the seat belt to reduce the injury. It also sends a emergency message to a desired contact through bluetooth when an accident is detected.

### This project demonstrates the use of sensors, microcontrollers, motor control, and communication for an automotive safety application

# Components Used
- #### Arduino Uno - Main microcontroller controlling the system
- #### Ultrasonic Sensor - Detect nearby objects
- #### Bluetooth Module - Low power communication b/w electronic devices
- #### Vibration Sensor - Detects abnormal vibrations
- #### IR Sensor - Detect Infrared radiation to sense the aspects of the surroundings
- #### Stepper Motor - Electric motor, converts physical pluse into mechanical motion
- #### Motor Driver - Acts as an interface b/w the microcontroller and electric motor

# Working Principle 
- ## Environment Monitoring
The ultrasonic sensor continuously measures the distance between the vehicle and nearby objects.
- ## Collision Detection
If an vehicle is detected within a dangerous distance threshold, the system enters into alert mode.
- ## Impact Detection
The Vibration sensor detects sudden shock or impact, which indicats the collision.
- ## Seat Belt Tightening
#### When an accident is confirmed:
     - Arduino sends signal to motor driver,
     - The stepper motor rotats,
     - The seat belt tightens to reduce the injury risk for the passenger.
- ## Emergency Notification
The Bluetooth module sends an alert message, includes the location, indicating that an accident occured.

# Project Structure
```
Seat Belt System/
│
├──Codes/
     └──GPS_Tracking.ino
     └──Project_code_1st.ino (Initial code)
     └──Project_code.ino
     └──Bluetooth_ultrasonic_stepper_Vibration.ino (Final Code)
     └──Speed and Distance.ino (tried to calculate distance and speed)
│
├──images/         <──(contains high resolution of the setup)
├──docs/           <──(Presentation)
├──media/          <──(demo video)
│
└──Readme.md
```

# Challenges Faced
- #### Difficulty in developing the physical prototype structure of the system
- #### Ultrasonic sensor limitation in measuring velocity and distance simultaneously
- #### Calibration of seat belt tightening mechanism
- #### Bluetooth communication reliability issues:
      Location sending success rate:
      - 7/10 times successful
      - 3/10 times failed
- #### Delay in seat belt tightening response

# Future Improvements
### Prototype can be Improved further by,
- #### Integrate vehicle speed sensors
- #### Machine learning models for accident prediction
- #### Improving mechanical design for real automotive deployment

# License
- This project is developed for **Academic purposes** as part of an **Embedded system** course project.
