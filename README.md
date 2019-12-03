# MobileRoboticArm
## Mobile Robotic Arm Controlled Via Web Server

This project was completed for Dr. Roppel's ELEC 5530 Mobile Robotics course.
The goal of this project was to create a robotic arm on a mobile platform that is controlled wirelessly.

[Mobile Robotic Arm](https://github.com/NoahNedz/MobileRoboticArm/tree/master/pics/pic2.jpg "Mobile Robotic Arm")


---

* The NodeMCU was selected to handle all of the wireless communication handling and servo controlling. This MCU uses the ESP32 SoC which allows for easy setup of a web server.
* The arm design is mostly borrowed from [daGHIZmo](https://www.thingiverse.com/thing:1015238). I did, however, replace the claw design with a fork so that little pallets could be picked up.
* The base was borrowed from a SPARC sumo-bot competiton in which I printed and assembled my own base. I reused this base; the files for this can be found (here)[https://github.com/SPARC-Auburn/3D-Printed-Sumo-Bot]
* I used MG90S servos for this robot since the arm was designed around their implementation. I am running these off of a regulated 7.2V NiHM battery.
