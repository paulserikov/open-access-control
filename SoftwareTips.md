# Software Guide #
Once you have downloaded the software, you'll need to set up a few parameters to get started.

---

## Requirements ##
In order to install the software on your Arduino, the following is required.

  * The latest [Open Access Control software](http://code.google.com/p/open-access-control/downloads/list).

  * The latest [Arduino IDE](http://arduino.cc) for your Windows, Linux, or MAC system.

  * Some basic hardware to test with. At a minimum, you'll want to get at least one PIN or RFID reader and gook up some LEDs to the output pins to check their status. See the [hardware setup guide](HardwareTips.md) for more info on readers.


---

## Quick Start Guide ##
To get started right away, perform the following tasks:
  * Download and unzip the program files. Place the main .PDE file into a directory of your choice.
  * Extract the library files into your Arduino libraries directory. See the [getting started guide ](http://arduino.cc/en/Guide/HomePage) for more details.
  * Open the sketch and edit Open\_Access\_Control.pde. Change:
```
#define PRIVPASSWORD 0x1234
```
> to something less obvious.
    * Compile and upload the sketch.
    * Start up the Serial Monitor or another terminal. Attach to the Arduino and make sure the console comes up.
    * Scan a tag or enter a 7-digit PIN number at your reader and write down the result.
    * Edit your super static user list to put at least one of these tag values in permanently. You'll want this in case you lock yourself out later.
```
#define gonzo   0x1234                  
#define snake   0x1234                 
#define satan   0x1234
long  superUserList[] = { gonzo, snake, satan};  
```
    * Compile and upload the code again. You should now be able to swipe tags and have the corresponding door pins activate.


---

## Adding users ##
Once you have this working, you can log into the console again and add users.

  * You must enter the console password to enable user editing and all other functions other than locking up and setting the alarm
  * You can exit privileged mode by typing 'e' again.
  * Several usermasks (security levels) are defined in the code. A default of 254 will work for getting started.
  * You can store up to 200 users in eeprom on the Arduino. Users are numbered 0..199.
  * It's recommended that you create a spreadsheet of your users, as the software will replace the tage info with asteriks unless debugging is enabled.

# Version 1.40 Features #
## Add users at the reader ##
You can now add users to the system with a reader that has a key pad attached.  In order to do so you must be listed with an admin user mask, eg: a user that is hard coded as staff, or has a usermask of 5.

  1. Swipe key card that is to be provisioned (should have an invalid key read)
  1. Swipe staff key (usermask 5 or hard coded user)
  1. Press 666, Enter. This adds the fob to the user list from the last invalid fob read.
  1. Swipe new fob, and it should be added to the userlist.

## Side door emergency code ##
The side door reader (reader2) has a back door code in the event that someone gets completely locked out of the space- they can call us and we can give them the code over the phone.  This is done by using the user 199 as a code for the side door.  Just enter in a six digit number in the users "keyfob" code.  Then when the reader see this code it allows access.  Once this is used, you must change the number.

  1. At door2 reader press 666
  1. Enter the 6 digit number that is assigned to user 199
  1. Profit.

## Date / Time update ##
You can update the date/time from the serial port.

## Using the keypad as doorbell ##
As we made a loop for detecting card reads vs user button pushes, we setup the Enter key on the keypad to ring the bell inside the space.  We still need to put up a sign to tell the humans to push the button, but it's a start.

## Customization ##
  * You can customize the reader logic, keypad commands, timeout values and alarm functions as needed. Samples are included in the code. Be sure to make frequent backups.
  * There are about 20 bytes of unused eeprom space, 16KB of flash and about 650-700 bytes of free memory when an Atmega 328-based Arduino is used. Room for additional features does exist.
  * Please consider contributing anything that you think is useful back to the project.
## Sample Usage Instructions ##
You may want to post a set of directions near an inside keypad to remind users of system commands. Here is a sample:

  * 1# - Turns off front door chime.
  * 2# - Arms alarm and locks all doors.
  * 3# - Locks outside door, leaves inside unlocked.
  * 4# - Unlocks all doors and leaves unlocked.  Door chime on front door
  * 5# - Locks all doors.
  * 111111 - Locks all doors (no card or # needed)



---

Open Access Control by [23b Shop](http://shop.23b.org) is licensed under a [Commons Attribution 3.0 Unported License](http://creativecommons.org/licenses/by/3.0/Creative).

Based on a work at [code.google.com](http://code.google.com).