# How to configure a Raspberry Pi for monitoring #

## This page explains how to set up a Raspberry Pi embedded PC for monitoring the Open Access Control. ##

Created 10/19/2012
Updated 02/20/2013

### Raspberry Pi Device Setup ###
#### Download the software ####
Download the software from [Raspberry Pi](http://www.raspberrypi.org/downloads) site.

Please follow their [setup instructions](http://elinux.org/RPi_Easy_SD_Card_Setup) before beginning on this. We recommend an >8GB SD card (High speed recommended) at a minimum.

#### After boot ####
Make sure you run _raspi-config_, and expand your file system to fill the entire SD card.  Also, unless your are running with a head, configure your system to have less video memory via the _raspi-config_ tool.

Make sure to run the update process from within the raspi-config tool as well.

<a href='Hidden comment: Once your setup, grab [https://github.com/Hexxeh/rpi-update rpi-update] and run _rpi-update_ to make sure the firmware is up-to-date.

To install _rpi-update_:
```
sudo wget http://goo.gl/1BOfJ -O /usr/bin/rpi-update && sudo chmod +x /usr/bin/rpi-update
```
'></a>

#### Install all the software packages ####
SSH into the Pi, and issue the following commands:

```
sudo apt-get update
sudo apt-get install minicom screen msmtp arduino
# arduino is optional - but it allows you to program the arduino from the Linux host
```

#### Connect the Pi to the Arduino ####
Once connected, the Arduino will power the Raspberry Pi via the USB port (tested with version B and 512Mb of memory).  Unknown if this is outside of spec, but if it burns up we will post a fix.

Upon boot, you will see a /dev/ttyUSB0, which can be used to talk with the Arduino.

### Setup the monitoring system ###
a. Create a normal user to run your monitoring scripts under. We'll call this user "access" for the tutorial.

```
sudo useradd -g users -m access
```

b. In the "access" users home directory create a directory called "scripts". Place the following files in this directory and modify the e-mail addresses, messages, etc as needed.

start\_screen\_logging.sh
```
cat > start_screen_logging.sh << EOF
#!/bin/bash
# Start logging functions in a screen
/bin/su - access -c "screen -dmS MINICOM /home/access/scripts/start_logging.sh"
EOF

```

log\_notify.sh
```
cat > log_notify.sh << EOF
#!/bin/bash
tail -0f /home/access/scripts/access_log.txt | egrep --line-buffered -i "authenticated" | while read line
        do
                rm /home/access/scripts/message_tmp.txt
                cp /home/access/scripts/log_msg.txt /home/access/scripts/message_tmp.txt
                sleep 1
                tail -6 /home/access/scripts/access_log.txt >> /home/access/scripts/message_tmp.txt
                msmtp -t < /home/access/scripts/message_tmp.txt
        done
EOF

```

log\_alert.sh
```
cat > log_alert.sh << EOF
#!/bin/bash
cd /home/access/scripts
tail -0f /home/access/scripts/access_log.txt | egrep --line-buffered -i "triggered" |
while read line
        do
                msmtp -t < /home/access/scripts/alert_msg.txt
        done
EOF

```

log\_msg.txt
```
cat > log_msg.txt << EOF
From:hackerspace_notifier@yourdomain.com
To:somebody@domain.com, somebody_else@anotherdomain.com
Subject:User at the Hacker Space
EOF
```

log\_alert.txt
```
cat > log_alert.txt << EOF
From:hackerspace_notifier@yourdomain.com
To:somebody@domain.com, somebody_else@anotherdomain.com
Subject: Alert: Alarm triggered at shop

Please log in to the webcame at http://www.somedomain.com/cameras to check status.

-The Hacker Space
EOF

```

start\_logging.sh
```
cat > start_logging.sh << EOF
#!/bin/bash
/usr/bin/minicom -C /home/access/scripts/access_log.txt
EOF

```

c. Secure the scripts directory:
```
chmod -r 700 /home/access/scripts
```

d. Secure the USB serial port:

```
chown root:dialout /dev/ttyACM0  
chmod 770 /dev/ttyACM0
ls -al /dev/ttyA*

crw-rw---T 1 root dialout 166,  0 Feb 20 21:37 /dev/ttyACM0
```

Add the user "access" to the group dialout:
```
gpasswd -a access dialout
```

Check to see if the dialout user has been created:
```
grep dialout /etc/group
```
Should produce:   "dialout:x:20:pi,access"

e. configure the com parameters for minicom.

Either edit /etc/minicom/minirc.dfl or paste the following:
```
cat > /etc/minicom/minirc.dfl << EOF
pr port             /dev/ttyACM0
pr lock             /var/lock
pu baudrate         57600
pu minit
pu mreset
pu mdialpre
pu mdialsuf
pu mdialpre2
pu mdialsuf2
pu mdialpre3
pu mdialsuf3
pu mconnect
pu mnocon1
pu mnocon2
pu mnocon3
pu mnocon4
pu mhangup
pu mdialcan
pu rtscts           No
EOF
```

f.  Configure _iptables_ with some basic rules to protect the monitoring system. Tutorial here:

[Iptables rules](http://www.howtoforge.com/linux_iptables_sarge)

g. Add the following file to /home/access. Modify as needed for your outgoing e-mail account.

.msmtprc
```
#Gmail account
account gmail
host smtp.gmail.com
from myuser@gmail.com
auth on
tls on
tls
tls_trust_file /etc/ssl/certs/ca-certificates.crt
user xxxx@gmail.com
password xxxx
port 587
#tls_certcheck off

#ATT Account
account att
host smtp.att.yahoo.com
tls on
auth on
tls_trust_file /etc/ssl/certs/ca-certificates.crt
tls_starttls off
from xxx@att.net
user xxx@att.net
password xxxx

account default : att
```

h. Add the following lines to _/etc/rc.d/rc.local_:
```
/bin/su - access -c "/home/access/scripts/log_notify.sh &"
/bin/su - access -c "/home/access/scripts/log_alert.sh &"
/home/access/scripts/start_screen_logging.sh
```

i. With the Arduino connected, reboot everything and verify that it all comes up automatically. You should be able to log in via ssh, type "screen -rd" and be connected to an interactive session on the Arduino. Please secure the ssh system with certificates and/or good passwords.


---

Open Access Control by [23b Shop](http://shop.23b.org) is licensed under a [Commons Attribution 3.0 Unported License](http://creativecommons.org/licenses/by/3.0/Creative).

Based on a work at [code.google.com](http://code.google.com).