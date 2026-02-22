Overview-
This project presents the development of a microcontroller-based Battery Management System (BMS) for monitoring and protecting a Li-ion battery pack. The system continuously measures voltage, current, and temperature, and ensures safe operation using embedded control logic. If any parameter exceeds the predefined safety limits, the system automatically disconnects the battery.
Components & Technologies-
Microcontroller:
Arduino Uno / Nano
Sensors:
ACS712 Current Sensor
LM35 Temperature Sensor
Voltage Divider Circuit for battery voltage measurement
Output & Protection:
16x2 LCD Display
5V Single Channel Relay
Buzzer
5V Cooling Fan
Software:
Embedded C using Arduino IDE
Key Features=
Real-time monitoring of electrical and thermal parameters
Automatic relay-based cutoff during unsafe conditions
Live parameter display on LCD
Audible alert using buzzer
Basic thermal management support
Working Principle-
The battery voltage is measured through a voltage divider circuit and read using the Arduino’s analog input. The ACS712 sensor measures the current flowing through the circuit, while the LM35 sensor provides temperature readings.
The embedded logic continuously compares these values with predefined threshold limits:
Voltage above maximum limit → Relay cutoff
Voltage below minimum limit → Relay cutoff
Current above safe limit → Relay cutoff
When any fault condition is detected, the relay disconnects the battery and the buzzer is activated. The LCD displays real-time system status and measured values.
