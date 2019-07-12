Honeywell HPMA115
===============

Taken from here: https://bitbucket.org/circuitdojo/particle-squared-code/src/master/


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


This connects through the Serial1 interface (TX/RX pins)

Documentation: https://docs.particle.io/reference/device-os/firmware/photon/#serial
Serial examples: 
* https://community.particle.io/t/serial-tutorial/26946
* https://community.particle.io/t/read-from-rx-tx-pins/26375/2
