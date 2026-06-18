# Experiment 1: Communication Between Two Ethernet Shields

## Aim

To verify communication between two Arduino Uno boards equipped with Ethernet Shields using Ethernet-based TCP/IP communication.

## Hardware Used

* Arduino Uno Boards (2)
* Ethernet Shields (2)
* LAN Cable
* Push Button Switch
* Green LED
* Jumper Wires

## Network Configuration

### Server Node (LED Node)

IP Address: 192.168.1.10

Port Number: 80

### Client Node (Switch Node)

IP Address: 192.168.1.11

## Working Principle

The Ethernet Shield attached to the first Arduino Uno acts as a client node. A push button connected to Digital Pin 6 is used to generate ON and OFF commands.

The second Arduino Uno equipped with an Ethernet Shield acts as a server node. A green LED connected to Digital Pin 5 responds to the commands received from the client node.

When the button is pressed, the client sends an ON command to the server, causing the LED to glow. Pressing the button again sends an OFF command, turning the LED off.

## Procedure

1. Stack Ethernet Shields on both Arduino Uno boards.
2. Connect a push button to Digital Pin 6 of the client node.
3. Connect an LED to Digital Pin 5 of the server node.
4. Connect both Ethernet Shields using a LAN cable.
5. Upload the client and server programs through Arduino IDE.
6. Power both Arduino Uno boards and observe communication.

## Result

Successful communication was established between the two Ethernet Shields. The LED responded correctly to ON and OFF commands transmitted from the client node.

## Conclusion

The experiment successfully demonstrated Ethernet-based communication between two Arduino Uno boards using Ethernet Shields. Data packets were transmitted using TCP/IP communication and executed correctly by the receiving node.
