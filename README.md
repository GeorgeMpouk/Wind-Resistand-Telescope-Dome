<h1>Welcome to our github page</h1>

# Wind-Resistand-Telescope-Dome
<i>A 3d printed telescope dome that rotates based on the wind direction and wind speed to protect the telescope from harsh winds</i>
<h2>Introduction </h2>

<p>This reposotiry hosts the code and the 3d files needed to replicate the project.</p>
<p> The incentive to create this project started as part of the final project for the Robotics course at Leiden University in the Spring of 2023.
  The goal of our system is to simulate a novel idea concerning the automation of the rotation of a telescope dome based on weather conditions.
  Our system focuses on the behaviour of the wind (wind direction & wind speed) and basically adjusts the telescopes observational position based the sensed input
from the two sensor that we use (Wind vane & Anemometer). That input gets processed from the microprossesor (Arduino Uno) who in turn sends the command to the motor (ULN-2003) to rotate the dome. </p>

<h2> Gear used </h2>
The gear that was used can be divided in two main categories, mechanical and electronic

<h3> Electronics </h3>
<p>Below is the list of electronics that were used</p>
  <ul>
    <li> 1x Arduino Uno</li>
    <li>5x KY-003 Hall Effect Sensor </li>
<li>1x ULN2003 Stepper Motor</li>
<li>1x Breadboard</li>
<li>Jumper Wires</li>
<li>Several Magnets</li>
    </ul>
<p> In the section instruction we will talk about how to create the schematic</p>

<h3> Mechanical </h3>
<p>Below is the list of mechanical parts that were used</p>

  <ul>
    <li> 4x M6 allen bolts</li>
    <li>4x M6  End Nuts</li>
    <li>4x M6 Nuts</li>
    <li>Several  M6 Washers</li>
    <li>Hot glue</li>
 </ul>
 
 
 
 
 <h2> Instrunctions </h2>
 <h3> 3D printed parts </h3>
<p>All the 3d files are located in the folder 3d files. In order to replicate them you will need a standard FDM 3d printer, CAD software and a slicing software. This project used the  Ender3 V2, Fusion 360 and Cura Ultimaker.</p>
<br>
<h3>Electronics</h3>
<p>As mentioned and before this project was implemented with an Arduino Uno. The connections are clear and can be desciphered from the code also but here is a brief breakdown.
The motor is connected to 8,9,10,11 digital pins as it needs four digital pins to work correctly, in the code they are assigned in confused manner for most but that is for the sake of the magnetic polarity of the motor. Next we connected one of the hall effect hall sensors to digital pin 2 because of its added capabillity with interuppting the code flow and that is needed for the measurement of the wind speed. Lastly we connect the last four hall effect sensors to the digital pins 4,5,6,7 to complete the wind vane system. The system uses a breadboard to distribute power to the sensors. The whole system can be powered by the 5v usb port but it is reccomended for the motor to be powered by the DC input. </p>

<p> Please dont hesitate to contact us for any question regarding the implementation</p>





