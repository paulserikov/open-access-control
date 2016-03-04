# Open Access Control for Hacker Spaces #


![http://open-access-control.googlecode.com/files/open_access_ft_sm.jpg](http://open-access-control.googlecode.com/files/open_access_ft_sm.jpg)


**Uses the Arduino open-source hardware to build a robust access control and alarm system.**



It attaches to a standard Arduino as a shield and provides:
  * Wiegand26 reader support (Two readers in v2.x hardware, up to 3 possible in software)
  * Real-time clock (DS1307 RTC in v2.x hardware)
  * On-board 5V switching power supply (1A rating)
  * Alarm monitoring with multiple zones (4 in current hardware, uses analog inputs)
  * Syslog-like serial logging
  * 200 user local database stored in eeprom memory.
  * Extensible and easy to modify.

Update: Kits and assembled units are now available [here](http://www.accxproducts.com).

Update: The latest software release (v1.3x) has a serial terminal for administration, security improvements, and greatly reduced memory footprint.

Version 2.11 of the hardware features:
  * On-board 5V switching power supply
  * Robust circuit protection with MOV and TVS diodes
  * Opto-isolation on all inputs using the NEC PS2501 series parts
  * Full 5A continuous trace rating on all relays, 10A contact rating

_Open Access Control hardware design by Arclight is licensed under a Creative Commons Attribution 3.0 Unported License. Based on a work at code.google.com._