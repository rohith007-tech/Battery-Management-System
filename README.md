# Battery Management System (BMS)

## Overview
This project presents the development of a microcontroller-based Battery Management System (BMS) for monitoring and protecting a Li-ion battery pack. The system continuously measures voltage, current, and temperature, and ensures safe operation using embedded control logic. If any parameter exceeds predefined safety limits, the system automatically disconnects the battery.

---

## Components & Technologies

### Microcontroller
- Arduino Uno / Nano

### Sensors
- ACS712 Current Sensor
- LM35 Temperature Sensor
- Voltage Divider Circuit (for battery voltage measurement)

### Output & Protection
- 16x2 LCD Display
- 5V Single Channel Relay
- Buzzer
- 5V Cooling Fan

### Software
- Embedded C using Arduino IDE

---

## Key Features
- Real-time monitoring of voltage, current, and temperature
- Automatic relay-based cutoff during unsafe conditions
- Live parameter display on LCD
- Audible alert using buzzer
- Basic thermal management support

---

## Working Principle
The battery voltage is measured using a voltage divider circuit and read through the Arduino’s analog input. The ACS712 sensor measures current flow, while the LM35 sensor provides temperature readings.

The embedded control logic continuously compares sensor values with predefined threshold limits:

- Voltage above maximum limit → Relay cutoff  
- Voltage below minimum limit → Relay cutoff  
- Current above safe limit → Relay cutoff  

When a fault condition is detected, the relay disconnects the battery and activates the buzzer. The LCD displays real-time system status and measured parameters.