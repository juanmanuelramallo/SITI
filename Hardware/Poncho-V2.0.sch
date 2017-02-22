EESchema Schematic File Version 2
LIBS:Poncho_Esqueleto
LIBS:Misc_Poncho_Grande
LIBS:conn
LIBS:74xgxx
LIBS:74xx
LIBS:ac-dc
LIBS:actel
LIBS:adc-dac
LIBS:Altera
LIBS:analog_devices
LIBS:analog_switches
LIBS:atmel
LIBS:audio
LIBS:battery_management
LIBS:bbd
LIBS:brooktre
LIBS:cmos_ieee
LIBS:cmos4000
LIBS:contrib
LIBS:cypress
LIBS:dc-dc
LIBS:device
LIBS:digital-audio
LIBS:diode
LIBS:display
LIBS:dsp
LIBS:elec-unifil
LIBS:ESD_Protection
LIBS:ftdi
LIBS:gennum
LIBS:graphic
LIBS:hc11
LIBS:intel
LIBS:interface
LIBS:ir
LIBS:Lattice
LIBS:linear
LIBS:logo
LIBS:maxim
LIBS:memory
LIBS:microchip
LIBS:microchip_dspic33dsc
LIBS:microchip_pic10mcu
LIBS:microchip_pic12mcu
LIBS:microchip_pic16mcu
LIBS:microchip_pic18mcu
LIBS:microchip_pic32mcu
LIBS:microcontrollers
LIBS:motor_drivers
LIBS:motorola
LIBS:msp430
LIBS:nordicsemi
LIBS:nxp_armmcu
LIBS:onsemi
LIBS:opto
LIBS:Oscillators
LIBS:philips
LIBS:power
LIBS:Power_Management
LIBS:powerint
LIBS:pspice
LIBS:references
LIBS:regul
LIBS:relays
LIBS:rfcom
LIBS:sensors
LIBS:silabs
LIBS:siliconi
LIBS:stm8
LIBS:stm32
LIBS:supertex
LIBS:switches
LIBS:texas
LIBS:transf
LIBS:transistors
LIBS:ttl_ieee
LIBS:valves
LIBS:video
LIBS:Worldsemi
LIBS:Xicor
LIBS:xilinx
LIBS:Zilog
LIBS:Poncho-V2.0-cache
EELAYER 25 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title "Poncho Grande - Modelo - Ejemplo - Template"
Date "2015-10-06"
Rev "1.0"
Comp "Proyecto CIAA - COMPUTADORA INDUSTRIAL ABIERTA ARGENTINA"
Comment1 "https://github.com/ciaa/Ponchos/tree/master/modelos/doc"
Comment2 "Autores y Licencia del template (Diego Brengi - UNLaM)"
Comment3 "Autor del poncho (COMPLETAR NOMBRE Y APELLIDO). Ver directorio \"doc\""
Comment4 "CÓDIGO PONCHO:"
$EndDescr
$Comp
L OSHWA #G2
U 1 1 560A0A28
P 10800 6050
F 0 "#G2" H 10770 6450 60  0001 C CNN
F 1 "OSHWA" H 10800 6353 60  0001 C CNN
F 2 "mod:OSHWA" H 10800 6050 60  0001 C CNN
F 3 "" H 10800 6050 60  0000 C CNN
	1    10800 6050
	1    0    0    -1  
$EndComp
$Comp
L Logo_Poncho #G1
U 1 1 560CFFC0
P 10150 6000
F 0 "#G1" H 10100 5600 60  0001 C CNN
F 1 "Logo_Poncho" H 10350 5600 60  0001 C CNN
F 2 "" H 10150 6000 60  0000 C CNN
F 3 "" H 10150 6000 60  0000 C CNN
	1    10150 6000
	1    0    0    -1  
$EndComp
$Comp
L Conn_Poncho2P_2x_20x2 XA1
U 1 1 584D447D
P 9350 1700
F 0 "XA1" H 9650 2100 60  0000 C CNN
F 1 "Conn_Poncho2P_2x_20x2" H 9700 0   60  0000 C CNN
F 2 "Socket_Strips:Socket_Strip_Straight_2x20" H 9350 1700 60  0001 C CNN
F 3 "" H 9350 1700 60  0000 C CNN
	1    9350 1700
	1    0    0    -1  
$EndComp
$Comp
L Conn_Poncho2P_2x_20x2 XA1
U 2 1 584D4510
P 6500 1700
F 0 "XA1" H 6800 2100 60  0000 C CNN
F 1 "Conn_Poncho2P_2x_20x2" H 6850 0   60  0000 C CNN
F 2 "Socket_Strips:Socket_Strip_Straight_2x20" H 6500 1700 60  0001 C CNN
F 3 "" H 6500 1700 60  0000 C CNN
	2    6500 1700
	1    0    0    -1  
$EndComp
$Comp
L CONN_02X04 P1
U 1 1 584D49B5
P 1400 4450
F 0 "P1" H 1400 4700 50  0000 C CNN
F 1 "GPRS" H 1400 4200 50  0000 C CNN
F 2 "Socket_Strips:Socket_Strip_Straight_2x04" H 1400 3250 50  0001 C CNN
F 3 "" H 1400 3250 50  0000 C CNN
	1    1400 4450
	1    0    0    1   
$EndComp
$Comp
L CONN_01X04 P4
U 1 1 584D4A30
P 6175 4275
F 0 "P4" H 6175 4525 50  0000 C CNN
F 1 "Receptores" V 6275 4275 50  0000 C CNN
F 2 "Socket_Strips:Socket_Strip_Straight_1x04" H 6175 4275 50  0001 C CNN
F 3 "" H 6175 4275 50  0000 C CNN
	1    6175 4275
	1    0    0    -1  
$EndComp
$Comp
L CONN_01X04 P3
U 1 1 584D4A5F
P 4700 3450
F 0 "P3" H 4700 3700 50  0000 C CNN
F 1 "GPS" V 4800 3450 50  0000 C CNN
F 2 "Socket_Strips:Socket_Strip_Straight_1x04" H 4700 3450 50  0001 C CNN
F 3 "" H 4700 3450 50  0000 C CNN
	1    4700 3450
	1    0    0    -1  
$EndComp
Text GLabel 1650 4600 2    60   Input ~ 0
GND
Text GLabel 3625 1425 3    60   Input ~ 0
GND
$Comp
L CONN_01X03 P2
U 1 1 584D4FA4
P 4700 4225
F 0 "P2" H 4700 4425 50  0000 C CNN
F 1 "Emisores" V 4800 4225 50  0000 C CNN
F 2 "Socket_Strips:Socket_Strip_Straight_1x03" H 4700 4225 50  0001 C CNN
F 3 "" H 4700 4225 50  0000 C CNN
	1    4700 4225
	1    0    0    1   
$EndComp
Text GLabel 1650 4300 2    60   Input ~ 0
GPIO1
Text GLabel 1150 4300 0    60   Input ~ 0
GPIO2
Text GLabel 1150 4600 0    60   Input ~ 0
GND
Text GLabel 1150 4500 0    60   Input ~ 0
3.3V
Text GLabel 6250 1400 0    60   Input ~ 0
3.3V
NoConn ~ 1650 4400
NoConn ~ 1150 4400
Text GLabel 4500 4225 0    60   Input ~ 0
GND
Text GLabel 4500 4325 0    60   Input ~ 0
GPIO8
Text GLabel 7450 2900 2    60   Input ~ 0
GPIO1
Text GLabel 6250 2900 0    60   Input ~ 0
GPIO2
Text GLabel 4500 3600 0    60   Input ~ 0
GND
Text GLabel 4500 3500 0    60   Input ~ 0
RX232
Text GLabel 4500 3400 0    60   Input ~ 0
TX232
Text GLabel 5975 4425 0    60   Input ~ 0
GND
Text GLabel 5975 4225 0    60   Input ~ 0
ADC_CH2
Text GLabel 5975 4125 0    60   Input ~ 0
ADC_CH1
Text GLabel 9100 2500 0    60   Input ~ 0
RX232
Text GLabel 9100 2600 0    60   Input ~ 0
TX232
Text GLabel 9100 2000 0    60   Input ~ 0
ADC_CH1
Text GLabel 9100 1900 0    60   Input ~ 0
ADC_CH2
NoConn ~ 6250 1600
NoConn ~ 6250 1700
NoConn ~ 6250 1800
NoConn ~ 6250 1900
NoConn ~ 6250 2000
NoConn ~ 6250 2100
NoConn ~ 6250 2200
NoConn ~ 6250 2300
NoConn ~ 6250 2400
NoConn ~ 6250 2500
NoConn ~ 6250 2600
NoConn ~ 6250 2700
NoConn ~ 6250 2800
NoConn ~ 7450 2800
NoConn ~ 7450 2700
NoConn ~ 7450 2600
NoConn ~ 7450 2500
NoConn ~ 7450 2400
NoConn ~ 7450 2300
NoConn ~ 7450 2200
NoConn ~ 7450 2100
NoConn ~ 7450 2000
NoConn ~ 7450 1900
NoConn ~ 7450 1800
NoConn ~ 7450 1700
NoConn ~ 7450 1600
NoConn ~ 7450 1500
NoConn ~ 7450 3200
NoConn ~ 7450 3100
NoConn ~ 7450 3000
NoConn ~ 6250 3200
NoConn ~ 6250 3100
NoConn ~ 6250 3000
NoConn ~ 9100 1500
NoConn ~ 9100 1600
NoConn ~ 9100 1700
NoConn ~ 9100 1800
NoConn ~ 9100 2100
NoConn ~ 9100 2200
NoConn ~ 9100 2300
NoConn ~ 9100 2400
NoConn ~ 9100 2700
NoConn ~ 9100 2800
NoConn ~ 9100 2900
NoConn ~ 9100 3100
NoConn ~ 9100 3200
NoConn ~ 9100 3300
NoConn ~ 10300 3300
NoConn ~ 10300 3200
NoConn ~ 10300 3100
NoConn ~ 10300 3000
NoConn ~ 10300 2900
NoConn ~ 10300 2800
NoConn ~ 10300 2700
NoConn ~ 10300 2600
NoConn ~ 10300 2500
NoConn ~ 10300 2400
NoConn ~ 10300 2300
NoConn ~ 10300 2200
NoConn ~ 10300 2100
NoConn ~ 10300 2000
NoConn ~ 10300 1900
NoConn ~ 10300 1800
NoConn ~ 10300 1700
NoConn ~ 10300 1600
Text GLabel 10300 1400 2    60   Input ~ 0
5V
Text GLabel 5975 4325 0    60   Input ~ 0
+3.3V
Text GLabel 6250 3300 0    60   Input ~ 0
GND
NoConn ~ 6250 1500
$Comp
L CONN_01X02 P6
U 1 1 5853EEAA
P 3575 1225
F 0 "P6" H 3575 1375 50  0000 C CNN
F 1 "Fuente" V 3675 1225 50  0000 C CNN
F 2 "Socket_Strips:Socket_Strip_Straight_1x02" H 3575 1225 50  0001 C CNN
F 3 "" H 3575 1225 50  0000 C CNN
	1    3575 1225
	0    -1   -1   0   
$EndComp
$Comp
L CONN_01X02 P5
U 1 1 5853F531
P 1325 3525
F 0 "P5" H 1325 3675 50  0000 C CNN
F 1 "AlimentacionCIAA" V 1425 3525 50  0000 C CNN
F 2 "Socket_Strips:Socket_Strip_Straight_1x02" H 1325 3525 50  0001 C CNN
F 3 "" H 1325 3525 50  0000 C CNN
	1    1325 3525
	-1   0    0    1   
$EndComp
Wire Wire Line
	2200 3475 1525 3475
Text GLabel 1525 3575 2    60   Input ~ 0
GND
NoConn ~ 7450 1400
NoConn ~ 9100 3000
Text GLabel 7450 3300 2    60   Input ~ 0
GPIO8
Wire Wire Line
	3525 1425 2200 1425
Wire Wire Line
	2200 1425 2200 4500
Wire Wire Line
	2200 4500 1650 4500
Connection ~ 2200 3475
Text GLabel 10300 1500 2    60   Input ~ 0
GND
Text GLabel 4500 3300 0    60   Input ~ 0
+3.3V
Text GLabel 4500 4125 0    60   Input ~ 0
5V
Text GLabel 9100 1400 0    60   Input ~ 0
+3.3V
$EndSCHEMATC
