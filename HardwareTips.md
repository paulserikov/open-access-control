# Introduction #
This article is designed to help with the actual implementation of the Open Access Control system in a facility such as a hacker space or home.

<img src='http://open-access-control.googlecode.com/files/RFID_complete.jpg' width='300'>
<hr />
<h2>Disclaimer</h2>
This hardware/software project was designed by non-professionals and should be regarded as experimental. No warranties as to the safety, fitness for use or reliability of this project are expressed or implied.<br>
<hr />
<h2>Requirements</h2>
In order to implement this project at your space, the following items are recommended.<br>
<br>
<ul><li>The latest <a href='http://code.google.com/p/open-access-control/downloads/list'>Open Access Control hardware</a>. You can have the board fabricated or purchase one from the <a href='http://shop.23b.org'>23b Shop</a>. All of the parts listed in the Bill of Materials (available in the downloads folder) are available from <a href='http://www.digikey.com'>Digikey</a>, <a href='http://www.mouser.com'>Mouser</a>, and other common sources.</li></ul>

<ul><li>An <a href='http://arduino.cc'>Arduino</a> or compatible micro controller and the latest Arduino software. We have tested with the Duemillanove, Uno Seeeduino, and <a href='http://www.freeduino.org/'>FreeDuino</a>. You will need one with an Atmega 328 or higher for this project.</li></ul>

<ul><li>A power supply suitable for the peak current load of all of your door hardware as well as the access control itself. We use a 5A switching power supply and the UPS circuit. You will need a PS that can be adjusted up to 15V if you wish to use the UPS circuit provided. Fully operational, our system draws about 600ma with a door magnet, the access system, battery float charging, several alarm sensors, and an Arduino Ethernet module.</li></ul>

<ul><li>Some type of enclosure. Suggestions would be to either look for an old alarm panel to gut (call an installer and ask for the old ones) or a NEMA-format electrical box. These are available from electrical supply shops for a reasonable price.   A premade enclosure with power supply, UPS and battery hookup is available from <a href='http://www.securitypower.com/'>Electronic Security Devices</a>.</li></ul>

<ul><li>For mounting the Open Access Control into an enclosure, Will Bradley of <a href='http://www.heatsynclabs.org/'>Heatsync Labs</a> has created an excellent <a href='http://www.thingiverse.com/thing:12828'>Laser-cut template</a>.</li></ul>

<ul><li>Alarm sensors such as door magnets, motion detectors, glass-break sensors, etc if using the alarm or door chime feature set.</li></ul>

<ul><li>Door hardware, such as an <a href='http://shop.ebay.com/?_from=R40&_trksid=p5197.m570.l1313&_nkw=electric+strike'>electric strike</a>, mortise-style electric latch or <a href='http://shop.ebay.com/i.html?_nkw=magnetic+door+lock&_sacat=0&_odkw=door+magnet+lock'>door magnet</a>. <a href='http://hubpages.com/hub/Electrifying-an-Aluminum-Store-Front-Opening'>Glass front shop doors</a> are a bit more expensive to electrify but there is <a href='http://www.adamsrite.com/media/pdf/v2/sw32_4593.pdf'>drop-in</a> <a href='http://www.adamsrite.com/NewFiles/e-latch.pdf'>hardware</a> to do it.</li></ul>

<blockquote>A low-budget way to electrify a standard residential door is to hack a <a href='http://www.schlage.com/'>Schlage</a> or similar keyless door lock that uses batteries and a PIN code.</blockquote>

<blockquote>See the <a href='DoorInstallation.md'>Wiki Page</a> for more information on door hardware.</blockquote>

<ul><li>RFID, PIN pads or other access readers. Look for <a href='http://en.wikipedia.org/wiki/Wiegand_interface'>Wiegand</a> interface door readers. The HID brand is the most widely deployed for buildings, but is proprietary and expensive. The open-standards alternative is EM4100, which is available in abundance on <a href='http://shop.ebay.com/?_from=R40&_trksid=p5197.m570.l1313&_nkw=EM4100&_sacat=See-All-Categories'>eBay</a> or from Internet shops. Wiegand stuff is usually good for up to 500 feet of cable run  if you use shielded cable. You could also use RS232-based readers, but we have not tested this.</li></ul>

<blockquote>Note: The system is compatible with readers from <a href='http://www.hidglobal.com/'>HID Corporation</a>.  The Wiegand pulses sent from these readers may be too fast for the opto-isolation circuit in this hardware. If your HID readers will not work, solder a 0.15uF - 0.33uF capacitor between each READER input line and ground.</blockquote>

<ul><li>A key bypass. Since you will likely be tinkering with the code and "stuff" happens, it is advisable to have an alternate way into your space. Some suggestions including leaving a secondary door available for key access and/or installing electric hardware that includes a keyed cylinder.<br>
<hr />
<h2>Safety Considerations</h2>
When planning for your installation, you need to be aware of fire codes and safety issues. Our experience was basically the following:<br>
</li><li>You cannot lock the exit doors from people inside. Any door in the exit path must have a mechanical device to allow exit regardless of the electronics state. If your hardware can't do that (i.e. door magnets) then the fire codes typically require that your system have both a request-to-exit motion sensor and a button near the door which interrupts power and allows exit.</li></ul>

<ul><li>If you are installing access hardware on a fire-rated door, you cannot make any alterations to the door and you may need to buy specific hardware. Basically, these are solid doors that are rated to withstand a fire for a certain number of minutes. Drilling holes or removing material from them voids the rating and puts you on the hook for replacing the door. Look for a fire-rating sticker somewhere on the frame or hinges, and talk to the building owner if in doubt.</li></ul>

This <a href='http://www.securitymagazine.com/articles/requirements-for-card-to-exit-1'>article</a> explains more.<br>
<hr />
<h2>Installing the controller and wiring</h2>

This is one of those times where physical security is needed for there to be any security. We recommend placing the controller, UPS and other electronics in a sturdy enclosure that is located away from the entry points and public area. Locking it up is also a good idea.<br>
<br>
<ul><li>All wiring should be run inside walls or conduits and not accessible from outside your perimeter. Consider placing your readers behind glass or at least securing the mounting screws with a drop of Epoxy.  A tamper switch is also an option. Wiegand and serial readers have no protocol security and are vulnerable to skimming, replay and MITM attacks.</li></ul>

<ul><li>Document your wiring as you go. Use some cable tags or a labeling machine, and also document the wire pairs that you use for power, signals, etc. While the Open Access Control has protection on data and other lines, you don't really want to keep blowing fuses.</li></ul>

<ul><li>Consider installing some terminal blocks to distribute power and ground connections. This results in less mess inside the enclosure.</li></ul>

<ul><li>Be mindful of what power circuit each device is plugged into. For instance, putting the door magnet and an outside reader on the 12V 'A' rail could make it possible for the door to open if the reader wires were shorted out. You are warned.</li></ul>

<ul><li>Use solder and heatshrink tubing or quality crimp connectors and a proper crimper for all terminations. Bad connections are the source of 90% of system problems.</li></ul>

<ul><li>If using the alarm zones on the unit, wire up the sensors in series and use "normally closed" sensors for any security-sensitive application. Also place a 3-5K resistor at the end of each sensor loop. Once you wire up a zone and "train" the alarm, the software will sense a fault if the zone is ever shorted out. This is called a "supervised" zone on commercial alarms.</li></ul>

Sample wiring diagram:<br>
<br>
<img src='http://open-access-control.googlecode.com/files/openaccess_v211_wiring.png' width='600'>
<hr />
<h2>Security considerations</h2>
Once the system is in production, it would be a good idea to prevent unauthorized users from updating the code or tampering with the hardware. Here are some tips:<br>
<br>
<ul><li>On most Arduino models, you can connect a 120ohm resistor between "+5V" and "RST" to prevent the controller from being reset by the serial port. This will effectively prevent the boot loader from being activated and thus prevent updates to your code. If you solder a 1/4w resistor between the two outer pins of a 3-pin .100 header, you can make a handy little "remove for programming" dongle.<br>
</li><li>The controller itself should be locked in an enclosure or other secure location. There is no software security without physical security.<br>
</li><li>Alarm sensors are a topic unto themselves. At a minimum, you'll want to have door sensor on the doors controlled by the access system. The simplest variety is a small magnet that screws to the door and a reed switch that mounts above it. Motion sensors, glass break sensors, and a plethora of other sensors are available. Think about protecting your perimeter and then protecting the control panel when designing your zones.<br>
<hr />
<h2>Remote Monitoring and Administration</h2>
A quick way to get the system to log events and report on them is to attach a Linux PC via USB or serial, open a session, and log it to a file. The syntax looks like this:</li></ul>

<pre><code>~/logs$minicom -L /home/access/scripts/access.log<br>
</code></pre>

Use the "screen" command to run this, and you'll be able to reattach to the serial session any time you need to perform administration. The system does not echo commands, so your enable password should not end up in the logs.<br>
<br>
To monitor the system and send alerts, create one or more shell scripts like this:<br>
<br>
<pre><code>#!/bin/bash<br>
tail -0f access_log.txt | egrep --line-buffered -i "triggered" | while read line<br>
        do<br>
                msmtp -t &lt; /home/access/scripts/alert_msg.txt<br>
        done<br>
</code></pre>

You'll need to run these scripts all time, so run them with the '&' option like this:<br>
<br>
<pre><code>~/script$log_access_alert.sh &amp;<br>
</code></pre>

A fancier version that tails the the last 5 lines of the log so that you can get more information about what user logged in, etc:<br>
<br>
<pre><code>#!/bin/bash<br>
tail -0f access_log.txt | egrep --line-buffered -i "authenticated" | while read<br>
line<br>
        do<br>
            rm message_tmp.txt<br>
            cp log_msg.txt message_tmp.txt<br>
            sleep 1<br>
            tail -5 access_log.txt &gt;&gt; message_tmp.txt<br>
            msmtp -t &lt; message_tmp.txt<br>
        done<br>
<br>
</code></pre>

The "msmtp" package is a great way to send alerting messages out via SMTP without having to run a mail server locally. You can configure it to use gmail, Yahoo, etc or your own private SMTP server on another system.<br>
<hr />
<h2>Third Party Software</h2>
Below are add-in software projects for the Open Access Control.<br>
<br>
<h3>Zyphlar</h3>
<a href='http://heatsynclabs.org'>Heatsync Labs</a> has created a simple <a href='https://github.com/zyphlar/Open-Source-Access-Control---Web-Interface'>Web Interface</a> to our system.<br>
<br>
<hr />
Open Access Control by <a href='http://shop.23b.org'>23b Shop</a> is licensed under a <a href='http://creativecommons.org/licenses/by/3.0/Creative'>Commons Attribution 3.0 Unported License</a>.<br>
<br>
Based on a work at <a href='http://code.google.com'>code.google.com</a>.