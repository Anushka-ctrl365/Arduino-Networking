# Experiment 2: Ethernet Shield to W5500 Module Communication

## Aim

To verify communication between an Arduino Uno equipped with an Ethernet Shield and another Arduino Uno connected to a W5500 Ethernet Module.

## Hardware Used

* Arduino Uno (2)
* Ethernet Shield
* W5500 Ethernet Module
* LAN Cable
* Push Button
* LED
* Jumper Wires

## Network Configuration

### Shield Node (Client)

IP Address: 192.168.1.10

### W5500 Module Node (Server)

IP Address: 192.168.1.20

Port Number: 5000

## Working

The Shield Node continuously monitors the push button state. Whenever the button is pressed, ON/OFF commands are transmitted over Ethernet. The W5500 Module Node receives these commands and controls the LED accordingly.

## Result

Successful communication was established between the Ethernet Shield and W5500 Ethernet Module. The LED responded correctly to button presses from the remote node.

## Conclusion

The experiment verified interoperability between Ethernet Shields and W5500 Ethernet Modules using TCP/IP communication over Ethernet.
