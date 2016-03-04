# Open Access v2.11 board assembly and testing #
The Open Access Control board is a pretty straightforward through-hole assembly job. The top silkscreen has all of the component layouts and their values. We recommend doing the assembly in the order listed however, as you can test each section of the board as you go.

The hardware kit supplied by [23B](http://shop.23b.org) comes with the PCB and all components listed in the hardware design docs. Estimated build time is 2-4hours.
For info on obtaining one of these kits, you can email arclight at gmail dot com.

For those that wish to go it alone, the bill of materials is provided with the hardware CAD files download. All parts can be sourced from Digikey, Mouser, Element 14, etc. The Arduino and Arduino pin headers
can be sourced from [Adafruit](http://www.adafruit.com), [Sparkfun](http://www.sparkfun.com), [NKC](http://www.nkcelectronics.com/) and other electronics hobby vendors.

---


## Step-by-step building and testing instructions ##

1. Locate the parts for the first module, "input protection." This should consist of screw terminals, (2) TVS diodes, a reverse protection diode, fuses, holders and an MOV.

Carefully observe the orientation of the diodes, and place the stripe side in the position indicated on the board.
The MOV has no polarity. The screw terminals snap together like Lego's, and they should be assembled prior to soldering. Install the holders on the fuses before soldering. This will make alignment easier.

Note that there are two TVS diodes. One part will end in "18" and is for the 12V rail. The other ends in "6.8" and protects the 5V rail. Do not mix these up or the 6.8 part will self-destruct when power is applied.

When finished soldering, attach a 12V power source to the terminals marked "12V IN." For each pair of power terminals, the left side is (-) and the terminal to the right is (+). Measure the voltage at each screw terminal. The 12V-IN, 12V-1 and 12V-2 rails should all read +12V.

2. Next, locate the second module, "power supply." This consists of the LM2575 switching regulator, inductor, Schottky diode, two electrolytic capacitors, a heatsink and screw, a green LED and a 330Ohm resistor.

Start by bending the leads of the 5-pin LM-2575 regulator into a staggered pattern that allows the regulator to allow the chip to lie flat in its mounting location. Align the hole in the board with the hole in the mounting  tab. If using the optional heatsink, install it and tighten the 4-40 screw supplied.  Using the needle-nose pliers, gently pull the leads tight and then solder them. Locate the 330uF and 100uF capacitors and install them, paying attention to polarity.

Install the Schottky barrier diode, again with the stripe oriented properly

The large, black cube is the 330uH inductor. Optionally, place a drop of hot glue under its footprint to make attachment more secure and then solder.  The LED is polarity-sensitive, and the flat edge should be oriented per the silkscreen.

When all components are installed, power up the system again. If the power supply is operating, the Green LED will light up. Check the +5V terminal next to the 5V fuse, and verify that voltage is between 4.9 and 5.1VDC.

3. The next modules is the output section. Solder the resistors and diodes to the board first. The socket for the ULN2003 driver array chip is installed next (line up the pin 1 notch with the board), and then the relays and screw terminals. Again, remember to snap the screw terminal modules together prior to soldering. Insert the ULN2003 last, paying attention to the "Pin 1" notch and corresponding dot or notch on the chip.

4. The input section comes next, and takes the most time.  Start by soldering all of the 2.2K and 4.7K resistors into place. Pay attention to which is which, The 2.2K's will have red,red as their first bands, while the 4.7k's will be yellow, blue. Next, install the 1N4004 blocking diodes, taking care to orient their stripes to the
silkscreen. Install the 8 or 16 pin DIP socks provided, aligning the "Pin 1" notch according to the board layout.

Install the screw terminals next, and lastly, install the PS2501 opto-isolator chips. These chips come in a 4,8, or 16 pin package (PS2501-1,-2,-4). Any of these parts will work in this system, but  their Pin 1 must face up towards the top of the board.

5. The last section we will install is the logic system. Install the two 4.7k resistors near the real-time clock chip. Install the 0.1uF capacitor (not polarized) and then the 32Khz crystal. This crystal is delicate. Bend its leads down and solder, taking care not to heat it any more than necessary. Install the battery holder with notch
according to diagram, install the DS1307 RTC socket and chip, and solder in the Arduino headers. Insert the battery (positive side up) and snap in your Arduino. Use the stand-offs and 4-40 screws provided to secure the Arduino.

6. Download a copy of the open Access Control firmware from the address above. Unzip it, and install the libraries in your Arduino libraries directory. Compile and upload.  You may test the hardware by un-commenting the following line:
```
hardwareTest(100);                         // IO Pin testing routine(use to check your inputs with hi/lo +(5-12V) sources)
                                           // Also checks relays
```

Upload this code, open a serial monitor and wait. You should see a date come across, the relays should cycle, and the system should show the status of each input port (digital 1..4 and analog 1..4).

Short each of these terminals to +5V using a jumper and check that the reading changes from 0 to 1 (digital) or 0 to ~1000 (analog).  You may also un-comment the routine to set the current date time at next startup.
```
ds1307.setDateDs1307(0,56,19,1,3,4,11);         
  /*  Sets the date/time (needed once at commissioning)
   
   byte second,        // 0-59
   byte minute,        // 0-59
   byte hour,          // 1-23
   byte dayOfWeek,     // 1-7
   byte dayOfMonth,    // 1-28/29/30/31
   byte month,         // 1-12
   byte year);          // 0-99
   */
```

Be sure to change this once the time has been set.

Congratulations, you're done!


---

## Notes ##

  * Version 2.00 and 2.10 of the hardware require that the LM-2575 regulator be installed with a mica insulator underneath the heat sink or mounting tab. Failing to install this part could result in a 5V short.
  * All parts on the v2.10 and 2.11 layouts have been tested with an actual build. If detachable screw terminals such as the Phoenix 5mm Fixed Terminal Block parts are to be used. the diameter of the holes needs to be increased to at least .055".
  * The design can be adapted for 24V use. The following parts must be changed if a 24V supply voltage is to be used:
    * 24V coil relays (G5LE-14 DC24 or Digikey part #Z1013-ND)
    * 30V TVS diode  (1.5KE30A)
    * 4.7K resistors for relay LEDs
    * 10K resistors on inputs in 24V signals are used.



---

Open Access Control by [23b Shop](http://shop.23b.org) is licensed under a [Commons Attribution 3.0 Unported License](http://creativecommons.org/licenses/by/3.0/Creative).

Based on a work at [code.google.com](http://code.google.com).