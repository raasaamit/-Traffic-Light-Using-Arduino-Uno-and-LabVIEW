Traffic Light Control with Arduino Uno and LabVIEW
Overview
This project simulates a traffic light system using an Arduino Uno and LabVIEW. The Arduino controls three LEDs (Red, Green, Yellow) to replicate a traffic light sequence, while LabVIEW provides a graphical interface to manage the sequence and adjust timing parameters.
Features

LED Control: Arduino drives Red, Green, and Yellow LEDs for traffic light states.
LabVIEW GUI: Interface to start/stop the sequence and configure light durations.
Custom Timing: Adjust Red, Green, and Yellow state durations via LabVIEW.
Real-Time Feedback: Displays current light state on the LabVIEW front panel.
Serial Communication: Arduino and LabVIEW interact via serial protocol.

Hardware Requirements

Arduino Uno (or compatible microcontroller)
3 LEDs (Red, Green, Yellow)
3 resistors (220-330 ohms, depending on LED specifications)
Breadboard and jumper wires
USB cable (Type A to Type B)
Computer with LabVIEW and Arduino IDE installed

Software Requirements

Arduino IDE: For uploading the control sketch to the Arduino.
LabVIEW: Version 2018 or later, with NI-VISA and MakerHub LINX (or LIFA for older versions).
Drivers: Arduino USB drivers for serial communication.

Setup Instructions

Hardware Assembly:

Connect Red LED to Arduino pin 11, Green to pin 10, Yellow to pin 9 (each with a resistor in series).
Connect LED cathodes to Arduino GND.
Connect Arduino to the computer via USB.


Arduino Programming:

Open Arduino IDE and load TrafficLight.ino from the src folder.
Upload the sketch to the Arduino Uno.


LabVIEW Configuration:

Install LabVIEW, NI-VISA, and LINX (or LIFA).
Open Traffic Light with Arduino.vi from the labview folder in LabVIEW.
Select the correct COM port for the Arduino.


Running the System:

Launch Traffic Light with Arduino.vi in LabVIEW.
Use the GUI to start/stop the sequence and adjust light durations.
Verify LED behavior aligns with LabVIEW commands.



Project Structure

src/TrafficLight.ino: Arduino sketch for LED control via serial commands.
labview/Traffic Light with Arduino.vi: LabVIEW VI for GUI and serial communication.
docs/: Contains circuit diagrams and additional resources.

Usage

Open Traffic Light with Arduino.vi and select the Arduino’s COM port.
Set durations for Red, Green, and Yellow states using numeric controls.
Toggle the Start/Stop button to control the traffic light sequence.
Monitor the current state via the LabVIEW GUI and LED outputs.

Troubleshooting

Arduino Not Detected: Confirm the COM port and install Arduino drivers if needed.
LEDs Not Lighting: Check wiring, resistor values, and sketch upload.
LabVIEW Errors: Ensure NI-VISA and LINX/LIFA are properly installed.

Contributing
Contributions are welcome! Submit pull requests or issues for bugs, features, or improvements.
License
Licensed under the MIT License. See LICENSE for details.
Acknowledgments

Thanks to the Arduino and LabVIEW communities for their resources and support.
Inspired by educational projects on microcontroller-based automation.
