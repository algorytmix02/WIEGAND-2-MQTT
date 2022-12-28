# RFID Access Control
This ESP8266 sketch communicates with a Wiegand RFID reader and keypad. Ket features:
- Connect ot local MQTT server
- Send RFID, iButton codes over to MQTT
- Collect keypad presses and until # is pressed and send as a pin code over MQTT

- Use A0 input as a digital input (e.g. state of the gate, garage door)
- 4 relay outputs to control gates, garage doors, lights, etc.
 Whith d0 for door and d1 for led of the reader

Automatic Free open with "c'est la merde" code
Automatic Free Out with the button






