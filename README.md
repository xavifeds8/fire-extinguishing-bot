## Fire Extinguishing robot
We aim to design a robot capable of detecting and suppressing fires. This robot model works in such a way that it tries to detect fire and extinguishes the fire. The robot model consists of an ultrasonic sensor HC-SR04 and IR based thermal sensor. Based on the intensity reading of the thermal sensor the fire bot sets its goal position and the ultrasonic module helps in obstacle avoidance. The bot is equipped with the fire extinguishing system which consists of a water pump. After the fire is being extinguished the bot looks for any other presence of fire. 

### Features Of the robot
* Autonomous differential drive robot
* Searches for the fire even in the narrow areas
* PD controller for smooth movement of the bot with reduced errors
* counter and a count based implementation to improve the accuracy of the reading of the sensor
* optimised water pumping system to avoid wastage of water

### Architectural design of the bot


