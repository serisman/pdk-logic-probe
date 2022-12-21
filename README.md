# pdk-logic-probe
A simple logic probe, based on the ultra-inexpensive (~$0.03) Padauk microcontrollers.
- LED is Green when Probe pin is LOW.
- LED is Red when Probe pin is HIGH.
- LED is Blue when Probe pin is Floating.

### Links
- [Firmware](firmware/)
- [PCB](pcb/)

![Top Side](https://github.com/serisman/pdk-logic-probe/blob/master/img/Top-Side.jpg?raw=true)
![Bottom Side](https://github.com/serisman/pdk-logic-probe/blob/master/img/Bottom-Side.jpg?raw=true)

### Schematic
(for 8-pin PFS154, PFS173, PMS150C/PMS15A, PMS152, PMS154C, PMS171B)
![Schematic](https://github.com/serisman/pdk-logic-probe/blob/master/pcb/output/Schematic.png?raw=true)

### Usage
Connect (-) to GND and (+) to VCC
- LED is Green when Probe pin is LOW.
- LED is Red when Probe pin is HIGH.
- LED is Blue when Probe pin is Floating.

![Green - LOW](https://github.com/serisman/pdk-logic-probe/blob/master/img/Green-LOW.jpg?raw=true)
![Red - HIGH](https://github.com/serisman/pdk-logic-probe/blob/master/img/Red-HIGH.jpg?raw=true)
![Blue - Floating](https://github.com/serisman/pdk-logic-probe/blob/master/img/Blue-Floating.jpg?raw=true)

### Compatibility
This project is currently intended to be run (without modifications) on the PFS154, PFS173, PMS150C/PMS15A, PMS152, PMS154C, and PMS171B Padauk microcontrollers,
but it should be able to be modified to run on just about every currently known Padauk microcontroller that is supported by SDCC and the Easy PDK Programmer.
