EESchema Schematic File Version 4
LIBS:CameraMotor-cache
EELAYER 29 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title "Camera motor controll"
Date "2019-02-17"
Rev "2"
Comp "Cecilia Data AB"
Comment1 "lars.berntzon@cecilia-data.se"
Comment2 "Lars Berntzon"
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L CameraMotor-rescue:GNDD #PWR010
U 1 1 5C6997AC
P 10000 3700
F 0 "#PWR010" H 10000 3450 50  0001 C CNN
F 1 "GNDD" H 10000 3575 50  0000 C CNN
F 2 "" H 10000 3700 50  0001 C CNN
F 3 "" H 10000 3700 50  0001 C CNN
	1    10000 3700
	1    0    0    -1  
$EndComp
$Comp
L CameraMotor-rescue:+5VD #PWR011
U 1 1 5C6997CF
P 9400 2750
F 0 "#PWR011" H 9400 2600 50  0001 C CNN
F 1 "+5VD" H 9400 2890 50  0000 C CNN
F 2 "" H 9400 2750 50  0001 C CNN
F 3 "" H 9400 2750 50  0001 C CNN
	1    9400 2750
	1    0    0    -1  
$EndComp
Wire Wire Line
	9400 2750 9400 2900
Wire Wire Line
	10000 3550 10000 3700
$Comp
L CameraMotor-rescue:Polyfuse F1
U 1 1 5C699977
P 9750 2900
F 0 "F1" V 9650 2900 50  0000 C CNN
F 1 "Polyfuse" V 9850 2900 50  0000 C CNN
F 2 "lasse:Fuse_SMS-5.2x4.2mm" H 9800 2700 50  0001 L CNN
F 3 "" H 9750 2900 50  0001 C CNN
	1    9750 2900
	0    1    1    0   
$EndComp
Wire Wire Line
	9900 2900 9950 2900
$Comp
L CameraMotor-rescue:CP C1
U 1 1 5C699BB1
P 9400 3200
F 0 "C1" H 9425 3300 50  0000 L CNN
F 1 "100u" H 9425 3100 50  0000 L CNN
F 2 "Capacitor_SMD:CP_Elec_5x3.9" H 9438 3050 50  0001 C CNN
F 3 "" H 9400 3200 50  0001 C CNN
	1    9400 3200
	1    0    0    -1  
$EndComp
Wire Wire Line
	9400 3350 9400 3550
Wire Wire Line
	9400 3550 10000 3550
$Comp
L CameraMotor-rescue:USB_OTG J1
U 1 1 5C69A450
P 10350 3100
F 0 "J1" H 10150 3550 50  0000 L CNN
F 1 "USB_OTG" H 10150 3450 50  0000 L CNN
F 2 "lasse:USB_Micro-USB3135-30-A" H 10500 3050 50  0001 C CNN
F 3 "" H 10500 3050 50  0001 C CNN
	1    10350 3100
	-1   0    0    -1  
$EndComp
Wire Wire Line
	10350 3500 10350 3550
Connection ~ 10000 3550
Wire Wire Line
	9100 2700 9100 2900
Connection ~ 9400 2900
NoConn ~ 10050 3100
NoConn ~ 10050 3200
NoConn ~ 10050 3300
Wire Wire Line
	10450 3550 10450 3500
Connection ~ 10350 3550
$Comp
L CameraMotor-rescue:PWR_FLAG #FLG014
U 1 1 5C69C053
P 10350 3700
F 0 "#FLG014" H 10350 3775 50  0001 C CNN
F 1 "PWR_FLAG" H 10350 3850 50  0000 C CNN
F 2 "" H 10350 3700 50  0001 C CNN
F 3 "" H 10350 3700 50  0001 C CNN
	1    10350 3700
	-1   0    0    1   
$EndComp
$Comp
L CameraMotor-rescue:PWR_FLAG #FLG015
U 1 1 5C69C28E
P 9100 2700
F 0 "#FLG015" H 9100 2775 50  0001 C CNN
F 1 "PWR_FLAG" H 9100 2850 50  0000 C CNN
F 2 "" H 9100 2700 50  0001 C CNN
F 3 "" H 9100 2700 50  0001 C CNN
	1    9100 2700
	1    0    0    -1  
$EndComp
$Comp
L CameraMotor-rescue:PWR_FLAG #FLG016
U 1 1 5C69C3E8
P 9950 2700
F 0 "#FLG016" H 9950 2775 50  0001 C CNN
F 1 "PWR_FLAG" H 9950 2850 50  0000 C CNN
F 2 "" H 9950 2700 50  0001 C CNN
F 3 "" H 9950 2700 50  0001 C CNN
	1    9950 2700
	1    0    0    -1  
$EndComp
Wire Wire Line
	9950 2700 9950 2900
Connection ~ 9950 2900
Wire Wire Line
	10000 3550 10350 3550
Wire Wire Line
	9400 2900 9400 3050
Wire Wire Line
	9400 2900 9600 2900
Wire Wire Line
	10350 3550 10350 3700
Wire Wire Line
	10350 3550 10450 3550
Wire Wire Line
	9950 2900 10050 2900
$Comp
L RF_Module:ESP-12E U1
U 1 1 5CD21681
P 5000 4400
F 0 "U1" V 5046 3656 50  0000 R CNN
F 1 "ESP-12E" V 4955 3656 50  0000 R CNN
F 2 "RF_Module:ESP-12E" H 5000 4400 50  0001 C CNN
F 3 "http://wiki.ai-thinker.com/_media/esp8266/esp8266_series_modules_user_manual_v1.1.pdf" H 4650 4500 50  0001 C CNN
	1    5000 4400
	0    -1   -1   0   
$EndComp
$Comp
L Connector:Conn_01x05_Male J2
U 1 1 5CD22440
P 5200 1450
F 0 "J2" V 5262 1162 50  0000 R CNN
F 1 "XH JST 800921" V 5353 1162 50  0000 R CNN
F 2 "Connector_JST:JST_XH_B5B-XH-A_1x05_P2.50mm_Vertical" H 5200 1450 50  0001 C CNN
F 3 "~" H 5200 1450 50  0001 C CNN
	1    5200 1450
	0    -1   1    0   
$EndComp
$Comp
L Transistor_Array:ULN2003 U2
U 1 1 5CD248CF
P 5200 2600
F 0 "U2" V 5246 3130 50  0000 L CNN
F 1 "ULN2003" V 5155 3130 50  0000 L CNN
F 2 "Package_SO:SOIC-16W_5.3x10.2mm_P1.27mm" H 5250 2050 50  0001 L CNN
F 3 "http://www.ti.com/lit/ds/symlink/uln2003a.pdf" H 5300 2400 50  0001 C CNN
	1    5200 2600
	0    -1   -1   0   
$EndComp
$Comp
L CameraMotor-rescue:+5VD #PWR013
U 1 1 5CD285B3
P 6300 1700
F 0 "#PWR013" H 6300 1550 50  0001 C CNN
F 1 "+5VD" H 6300 1840 50  0000 C CNN
F 2 "" H 6300 1700 50  0001 C CNN
F 3 "" H 6300 1700 50  0001 C CNN
	1    6300 1700
	1    0    0    -1  
$EndComp
Wire Wire Line
	5400 1650 5400 1700
Wire Wire Line
	5400 1700 6300 1700
Wire Wire Line
	5000 1650 5000 2200
Wire Wire Line
	5100 2900 5100 2200
Wire Wire Line
	5200 1650 5200 2200
Wire Wire Line
	5300 2900 5300 2200
$Comp
L CameraMotor-rescue:GNDD #PWR09
U 1 1 5CD2D448
P 6050 2700
F 0 "#PWR09" H 6050 2450 50  0001 C CNN
F 1 "GNDD" H 6050 2575 50  0000 C CNN
F 2 "" H 6050 2700 50  0001 C CNN
F 3 "" H 6050 2700 50  0001 C CNN
	1    6050 2700
	1    0    0    -1  
$EndComp
Wire Wire Line
	6050 2700 6050 2600
Wire Wire Line
	6050 2600 5800 2600
$Comp
L CameraMotor-rescue:+5VD #PWR07
U 1 1 5CD2E6E8
P 4800 2000
F 0 "#PWR07" H 4800 1850 50  0001 C CNN
F 1 "+5VD" H 4800 2140 50  0000 C CNN
F 2 "" H 4800 2000 50  0001 C CNN
F 3 "" H 4800 2000 50  0001 C CNN
	1    4800 2000
	1    0    0    -1  
$EndComp
Wire Wire Line
	5000 3800 5000 3000
Wire Wire Line
	5100 3000 5100 3800
Wire Wire Line
	5200 3800 5200 3000
Wire Wire Line
	5300 3000 5300 3400
$Comp
L Regulator_Linear:LM1117-3.3 U3
U 1 1 5CD33089
P 8550 2900
F 0 "U3" H 8550 3142 50  0000 C CNN
F 1 "LM1117-3.3" H 8550 3051 50  0000 C CNN
F 2 "Package_TO_SOT_SMD:SOT-223-3_TabPin2" H 8550 2900 50  0001 C CNN
F 3 "http://www.ti.com/lit/ds/symlink/lm1117.pdf" H 8550 2900 50  0001 C CNN
	1    8550 2900
	-1   0    0    -1  
$EndComp
Wire Wire Line
	9400 2900 9100 2900
$Comp
L CameraMotor-rescue:GNDD #PWR017
U 1 1 5CD3916A
P 8550 3400
F 0 "#PWR017" H 8550 3150 50  0001 C CNN
F 1 "GNDD" H 8550 3275 50  0000 C CNN
F 2 "" H 8550 3400 50  0001 C CNN
F 3 "" H 8550 3400 50  0001 C CNN
	1    8550 3400
	1    0    0    -1  
$EndComp
Wire Wire Line
	8550 3200 8550 3350
Wire Wire Line
	9100 2900 8850 2900
Connection ~ 9100 2900
$Comp
L power:+3.3V #PWR016
U 1 1 5CD4102B
P 8000 2750
F 0 "#PWR016" H 8000 2600 50  0001 C CNN
F 1 "+3.3V" H 8015 2923 50  0000 C CNN
F 2 "" H 8000 2750 50  0001 C CNN
F 3 "" H 8000 2750 50  0001 C CNN
	1    8000 2750
	1    0    0    -1  
$EndComp
Wire Wire Line
	8000 2750 8000 2900
Wire Wire Line
	8000 2900 8250 2900
$Comp
L power:+3.3V #PWR05
U 1 1 5CD42ABF
P 3800 4250
F 0 "#PWR05" H 3800 4100 50  0001 C CNN
F 1 "+3.3V" H 3815 4423 50  0000 C CNN
F 2 "" H 3800 4250 50  0001 C CNN
F 3 "" H 3800 4250 50  0001 C CNN
	1    3800 4250
	1    0    0    -1  
$EndComp
Wire Wire Line
	3800 4250 3800 4400
Wire Wire Line
	3800 4400 4200 4400
$Comp
L CameraMotor-rescue:GNDD #PWR012
U 1 1 5CD43C66
P 6200 4650
F 0 "#PWR012" H 6200 4400 50  0001 C CNN
F 1 "GNDD" H 6200 4525 50  0000 C CNN
F 2 "" H 6200 4650 50  0001 C CNN
F 3 "" H 6200 4650 50  0001 C CNN
	1    6200 4650
	1    0    0    -1  
$EndComp
Wire Wire Line
	5700 4400 6200 4400
Wire Wire Line
	6200 4400 6200 4650
$Comp
L CameraMotor-rescue:R R2
U 1 1 5CD44B6E
P 3700 3250
F 0 "R2" V 3493 3250 50  0000 C CNN
F 1 "680" V 3584 3250 50  0000 C CNN
F 2 "Resistor_SMD:R_1206_3216Metric_Pad1.42x1.75mm_HandSolder" V 3630 3250 50  0001 C CNN
F 3 "" H 3700 3250 50  0001 C CNN
	1    3700 3250
	0    1    1    0   
$EndComp
$Comp
L CameraMotor-rescue:R R3
U 1 1 5CD45403
P 3700 3550
F 0 "R3" V 3493 3550 50  0000 C CNN
F 1 "680" V 3584 3550 50  0000 C CNN
F 2 "Resistor_SMD:R_1206_3216Metric_Pad1.42x1.75mm_HandSolder" V 3630 3550 50  0001 C CNN
F 3 "" H 3700 3550 50  0001 C CNN
	1    3700 3550
	0    1    1    0   
$EndComp
Wire Wire Line
	3850 3250 4700 3250
Wire Wire Line
	4700 3250 4700 3800
Wire Wire Line
	3850 3550 4500 3550
Wire Wire Line
	4500 3550 4500 3800
$Comp
L Connector_Generic:Conn_01x03 J3
U 1 1 5CD47018
P 2700 3350
F 0 "J3" H 2618 3025 50  0000 C CNN
F 1 "Conn_01x03" H 2618 3116 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x03_P2.54mm_Vertical" H 2700 3350 50  0001 C CNN
F 3 "~" H 2700 3350 50  0001 C CNN
	1    2700 3350
	-1   0    0    1   
$EndComp
Wire Wire Line
	2900 3250 3550 3250
Wire Wire Line
	2900 3350 3300 3350
Wire Wire Line
	3300 3350 3300 3550
Wire Wire Line
	3300 3550 3550 3550
$Comp
L CameraMotor-rescue:GNDD #PWR02
U 1 1 5CD4DD3A
P 3000 3550
F 0 "#PWR02" H 3000 3300 50  0001 C CNN
F 1 "GNDD" H 3000 3425 50  0000 C CNN
F 2 "" H 3000 3550 50  0001 C CNN
F 3 "" H 3000 3550 50  0001 C CNN
	1    3000 3550
	1    0    0    -1  
$EndComp
Wire Wire Line
	2900 3450 3000 3450
Wire Wire Line
	3000 3450 3000 3550
Wire Wire Line
	5400 3800 5400 3000
$Comp
L CameraMotor-rescue:R R7
U 1 1 5CD500B5
P 6050 3400
F 0 "R7" V 5843 3400 50  0000 C CNN
F 1 "4K7" V 5934 3400 50  0000 C CNN
F 2 "Resistor_SMD:R_1206_3216Metric_Pad1.42x1.75mm_HandSolder" V 5980 3400 50  0001 C CNN
F 3 "" H 6050 3400 50  0001 C CNN
	1    6050 3400
	0    1    1    0   
$EndComp
Wire Wire Line
	5900 3400 5300 3400
Connection ~ 5300 3400
Wire Wire Line
	5300 3400 5300 3800
$Comp
L CameraMotor-rescue:GNDD #PWR014
U 1 1 5CD51826
P 6350 3500
F 0 "#PWR014" H 6350 3250 50  0001 C CNN
F 1 "GNDD" H 6350 3375 50  0000 C CNN
F 2 "" H 6350 3500 50  0001 C CNN
F 3 "" H 6350 3500 50  0001 C CNN
	1    6350 3500
	1    0    0    -1  
$EndComp
Wire Wire Line
	6200 3400 6350 3400
Wire Wire Line
	6350 3400 6350 3500
$Comp
L CameraMotor-rescue:C C2
U 1 1 5CD57150
P 3800 4700
F 0 "C2" H 3915 4746 50  0000 L CNN
F 1 "100n" H 3915 4655 50  0000 L CNN
F 2 "Capacitor_SMD:C_1206_3216Metric" H 3838 4550 50  0001 C CNN
F 3 "" H 3800 4700 50  0001 C CNN
	1    3800 4700
	1    0    0    -1  
$EndComp
$Comp
L CameraMotor-rescue:GNDD #PWR06
U 1 1 5CD57C23
P 3800 4950
F 0 "#PWR06" H 3800 4700 50  0001 C CNN
F 1 "GNDD" H 3800 4825 50  0000 C CNN
F 2 "" H 3800 4950 50  0001 C CNN
F 3 "" H 3800 4950 50  0001 C CNN
	1    3800 4950
	1    0    0    -1  
$EndComp
Wire Wire Line
	3800 4400 3800 4550
Connection ~ 3800 4400
Wire Wire Line
	3800 4850 3800 4950
$Comp
L CameraMotor-rescue:R R5
U 1 1 5CD5AB06
P 4050 5900
F 0 "R5" V 3843 5900 50  0000 C CNN
F 1 "4K7" V 3934 5900 50  0000 C CNN
F 2 "Resistor_SMD:R_1206_3216Metric_Pad1.42x1.75mm_HandSolder" V 3980 5900 50  0001 C CNN
F 3 "" H 4050 5900 50  0001 C CNN
	1    4050 5900
	0    1    1    0   
$EndComp
$Comp
L Switch:SW_DIP_x01 RES1
U 1 1 5CD5B5DD
P 4400 6300
F 0 "RES1" V 4354 6430 50  0000 L CNN
F 1 "SW_DIP_x01" V 4445 6430 50  0000 L CNN
F 2 "Button_Switch_SMD:SW_Push_1P1T_NO_6x6mm_H9.5mm" H 4400 6300 50  0001 C CNN
F 3 "~" H 4400 6300 50  0001 C CNN
	1    4400 6300
	0    1    1    0   
$EndComp
$Comp
L power:+3.3V #PWR04
U 1 1 5CD5C211
P 3750 5500
F 0 "#PWR04" H 3750 5350 50  0001 C CNN
F 1 "+3.3V" H 3765 5673 50  0000 C CNN
F 2 "" H 3750 5500 50  0001 C CNN
F 3 "" H 3750 5500 50  0001 C CNN
	1    3750 5500
	1    0    0    -1  
$EndComp
Wire Wire Line
	3750 5500 3750 5550
Wire Wire Line
	4200 5900 4400 5900
Wire Wire Line
	4400 5900 4400 5000
Wire Wire Line
	4400 5900 4400 6000
Connection ~ 4400 5900
$Comp
L CameraMotor-rescue:GNDD #PWR08
U 1 1 5CD606E3
P 4400 6700
F 0 "#PWR08" H 4400 6450 50  0001 C CNN
F 1 "GNDD" H 4400 6575 50  0000 C CNN
F 2 "" H 4400 6700 50  0001 C CNN
F 3 "" H 4400 6700 50  0001 C CNN
	1    4400 6700
	1    0    0    -1  
$EndComp
Wire Wire Line
	4400 6700 4400 6600
$Comp
L CameraMotor-rescue:R R4
U 1 1 5CD62317
P 4050 5550
F 0 "R4" V 3843 5550 50  0000 C CNN
F 1 "4K7" V 3934 5550 50  0000 C CNN
F 2 "Resistor_SMD:R_1206_3216Metric_Pad1.42x1.75mm_HandSolder" V 3980 5550 50  0001 C CNN
F 3 "" H 4050 5550 50  0001 C CNN
	1    4050 5550
	0    1    1    0   
$EndComp
Wire Wire Line
	4200 5550 4600 5550
Wire Wire Line
	4600 5550 4600 5000
Wire Wire Line
	3900 5900 3750 5900
Wire Wire Line
	3900 5550 3750 5550
Connection ~ 3750 5550
Wire Wire Line
	3750 5550 3750 5900
Connection ~ 5000 2200
Wire Wire Line
	5000 2200 5000 2900
Connection ~ 5100 2200
Wire Wire Line
	5100 2200 5100 1650
Connection ~ 5200 2200
Wire Wire Line
	5200 2200 5200 2900
Connection ~ 5300 2200
Wire Wire Line
	5300 2200 5300 1650
$Comp
L CameraMotor-rescue:R R6
U 1 1 5CD75288
P 5650 1950
F 0 "R6" V 5443 1950 50  0000 C CNN
F 1 "39" V 5534 1950 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0617_L17.0mm_D6.0mm_P7.62mm_Vertical" V 5580 1950 50  0001 C CNN
F 3 "" H 5650 1950 50  0001 C CNN
	1    5650 1950
	0    1    1    0   
$EndComp
Wire Wire Line
	5500 1950 5400 1950
Wire Wire Line
	5400 1950 5400 2200
Wire Wire Line
	5800 1950 6300 1950
Wire Wire Line
	6300 1950 6300 1700
Connection ~ 6300 1700
Wire Wire Line
	5300 5000 5300 5200
Wire Wire Line
	5300 5200 6650 5200
Wire Wire Line
	6650 5200 6650 3750
Wire Wire Line
	6650 3750 5500 3750
Wire Wire Line
	5500 3750 5500 3000
$Comp
L Connector:Conn_01x02_Male J4
U 1 1 5CD82EE7
P 6900 1450
F 0 "J4" V 6962 1494 50  0000 L CNN
F 1 "Conn_01x02_Male" V 7053 1494 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x02_P2.54mm_Vertical" H 6900 1450 50  0001 C CNN
F 3 "~" H 6900 1450 50  0001 C CNN
	1    6900 1450
	0    1    1    0   
$EndComp
$Comp
L CameraMotor-rescue:GNDD #PWR015
U 1 1 5CD83F7D
P 6900 2150
F 0 "#PWR015" H 6900 1900 50  0001 C CNN
F 1 "GNDD" H 6900 2025 50  0000 C CNN
F 2 "" H 6900 2150 50  0001 C CNN
F 3 "" H 6900 2150 50  0001 C CNN
	1    6900 2150
	1    0    0    -1  
$EndComp
Wire Wire Line
	6900 1650 6900 2150
Wire Wire Line
	5500 2200 5500 2100
Wire Wire Line
	5500 2100 6800 2100
Wire Wire Line
	6800 2100 6800 1650
$Comp
L Switch:SW_DIP_x01 PROG1
U 1 1 5CD8B671
P 3150 4450
F 0 "PROG1" V 3104 4580 50  0000 L CNN
F 1 "SW_DIP_x01" V 3195 4580 50  0000 L CNN
F 2 "Button_Switch_SMD:SW_Push_1P1T_NO_6x6mm_H9.5mm" H 3150 4450 50  0001 C CNN
F 3 "~" H 3150 4450 50  0001 C CNN
	1    3150 4450
	0    1    1    0   
$EndComp
Wire Wire Line
	4400 3800 3150 3800
$Comp
L CameraMotor-rescue:GNDD #PWR03
U 1 1 5CD8EBDB
P 3150 4900
F 0 "#PWR03" H 3150 4650 50  0001 C CNN
F 1 "GNDD" H 3150 4775 50  0000 C CNN
F 2 "" H 3150 4900 50  0001 C CNN
F 3 "" H 3150 4900 50  0001 C CNN
	1    3150 4900
	1    0    0    -1  
$EndComp
Wire Wire Line
	3150 4750 3150 4900
$Comp
L CameraMotor-rescue:R R1
U 1 1 5CD91698
P 2700 4050
F 0 "R1" V 2493 4050 50  0000 C CNN
F 1 "4K7" V 2584 4050 50  0000 C CNN
F 2 "Resistor_SMD:R_1206_3216Metric_Pad1.42x1.75mm_HandSolder" V 2630 4050 50  0001 C CNN
F 3 "" H 2700 4050 50  0001 C CNN
	1    2700 4050
	0    1    1    0   
$EndComp
$Comp
L power:+3.3V #PWR01
U 1 1 5CD91DA5
P 2300 3950
F 0 "#PWR01" H 2300 3800 50  0001 C CNN
F 1 "+3.3V" H 2315 4123 50  0000 C CNN
F 2 "" H 2300 3950 50  0001 C CNN
F 3 "" H 2300 3950 50  0001 C CNN
	1    2300 3950
	1    0    0    -1  
$EndComp
Wire Wire Line
	2300 3950 2300 4050
Wire Wire Line
	2300 4050 2550 4050
Wire Wire Line
	2850 4050 3150 4050
Wire Wire Line
	3150 3800 3150 4050
Connection ~ 3150 4050
Wire Wire Line
	3150 4050 3150 4150
NoConn ~ 4800 5000
NoConn ~ 5000 5000
NoConn ~ 5100 5000
NoConn ~ 5200 5000
NoConn ~ 5400 5000
NoConn ~ 5500 5000
NoConn ~ 5600 3000
NoConn ~ 5600 2200
NoConn ~ 4900 3800
NoConn ~ 4800 3800
NoConn ~ 4600 3800
$Comp
L CameraMotor-rescue:CP C3
U 1 1 5CDC011D
P 8000 3200
F 0 "C3" H 8025 3300 50  0000 L CNN
F 1 "100u" H 8025 3100 50  0000 L CNN
F 2 "Capacitor_SMD:CP_Elec_5x3.9" H 8038 3050 50  0001 C CNN
F 3 "" H 8000 3200 50  0001 C CNN
	1    8000 3200
	1    0    0    -1  
$EndComp
Wire Wire Line
	8000 3350 8550 3350
Wire Wire Line
	4800 2000 4800 2200
Connection ~ 8550 3350
Wire Wire Line
	8550 3350 8550 3400
Wire Wire Line
	8000 3050 8000 2900
Connection ~ 8000 2900
$EndSCHEMATC
