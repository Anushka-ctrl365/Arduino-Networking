# Experiment 4: Ethernet-Based Star Topology Implementation Using Ethernet Shields and W5500 Modules

## Aim

To implement a bus topology using Arduino Uno boards, Ethernet Shields and W5500 Ethernet Modules and verify end-to-end communication between distributed nodes.

## Hardware Used

* Arduino Uno Boards (3)
* Ethernet Shields (2)
* W5500 Ethernet Modules (2)
* LAN Cables
* Push Button Switch
* LED
* Breadboard
* Jumper Wires

## Network Architecture

### Sender Node

* Arduino Uno
* Ethernet Shield
* Push Button Switch

IP Address: 192.168.2.30

### Bridge Node

* Arduino Uno
* W5500 Module A
* W5500 Module B

Module A IP Address: 192.168.1.20

Module B IP Address: 192.168.2.20

### Receiver Node

* Arduino Uno
* Ethernet Shield
* LED

IP Address: 192.168.1.10

## Working Principle

The sender node monitors the state of a push button. When the button is pressed, an ON or OFF command is generated and transmitted through Ethernet.

The bridge node receives the command through one W5500 Ethernet Module and attempts to forward the message through the second W5500 Ethernet Module towards the receiver node.

The receiver node processes the received command and controls the LED accordingly.

## Experimental Observations

* Ethernet Shields were successfully detected and initialized.
* W5500 Ethernet Modules were successfully detected through SPI communication.
* Static IP configuration was verified.
* Individual communication between shield and module nodes was successfully established.
* Router-assisted communication was successfully demonstrated.
* Both W5500 modules could be detected simultaneously on a single Arduino Uno.
* End-to-end communication through the complete bridge architecture presented challenges due to dual Ethernet interface management on a single Arduino Uno.

## Result

Individual communication links were successfully established and verified. The complete bus topology architecture was implemented and tested through multiple iterations.

## Conclusion

The experiment provided practical understanding of Ethernet networking, SPI communication, client-server architecture, and multi-node embedded system design. The implementation highlighted both the capabilities and limitations of using multiple Ethernet interfaces on a resource-constrained microcontroller platform.
