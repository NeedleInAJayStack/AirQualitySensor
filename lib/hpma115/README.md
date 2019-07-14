Honeywell HPMA115
===============

HPMA Datasheet
https://sensing.honeywell.com/honeywell-sensing-particulate-hpm-series-datasheet-32322550

Pins (from right to left):
1. Vout: power output (+3.3 V/100 mA)
2. Vcc: power input (5 V)
3. N/A
4. N/A
5. RES: reserved for future use
6. TX: UART TX output (0 V - 3.3 V)
7. RX: UART RX input (0 V - 3.3 V)
8. GND: ground

HPMA <-> Particle Pins
* Vcc (2) <-> USB
* TX (6) <-> RX
* RX (7) <-> TX
* GND (8) <-> GND


This connects through the Serial1 interface (TX/RX pins). As such, long delays in the loop should be avoided, since it must monitor Serial 
for the expected starting characters.

Documentation: https://docs.particle.io/reference/device-os/firmware/photon/#serial
Serial examples: 
* https://community.particle.io/t/serial-tutorial/26946
* https://community.particle.io/t/read-from-rx-tx-pins/26375/2

Example of firmware:
* https://bitbucket.org/circuitdojo/particle-squared-code/src/master/