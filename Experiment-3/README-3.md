# Experiment 3: Router-Based Communication between Two W5500 Ethernet Modules

## Aim

To verify communication between two W5500 Ethernet Modules connected to separate Arduino Uno boards through a router.

## Hardware Used

* Arduino Uno (2)
* W5500 Ethernet Modules (2)
* Router
* LAN Cables (2)
* Push Button
* LED
* Breadboard
* Jumper Wires

## Network Configuration

### Sender Node

IP Address: 192.168.0.201

### Receiver Node

IP Address: 192.168.0.200

Communication Port: 5000

## Working Principle

Each Arduino Uno is connected to a W5500 Ethernet Module using SPI communication. Both modules are connected to a router using LAN cables.

The sender node continuously monitors the state of a push button. When the button is pressed, an ON or OFF command is transmitted through the router to the receiver node.

The receiver node receives the command and controls the LED accordingly.

## Result

Successful communication was established between the two W5500 Ethernet Modules through the router. The LED responded correctly to button presses from the remote sender node.

## Observation

Direct communication between two W5500 modules using a straight-through LAN cable was found to be unreliable due to link establishment issues. However, communication through a router was successful because the router handled link negotiation and packet forwarding.

## Conclusion

The experiment successfully demonstrated Ethernet communication between two W5500 Ethernet Modules using TCP/IP networking through a router. The results confirmed that router-assisted communication provides reliable connectivity between embedded Ethernet nodes.
