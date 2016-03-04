# How to configure a Sheevaplug PC for monitoring #

## This page explains how to set up a Sheevaplug embedded PC for monitoring the Open Access Control. ##

Updated 10/19/2012

### Plug Computer Device Setup ###
Tutorial based on the [Sheevaplug PC](http://www.plugcomputer.org/) from [Globalscale Technologies](http://www.globalscaletechnologies.com) and [ArmedSlack Linux v13.37](http://www.armedslack.org).

1. Download [ArmedSlack 13.37](http://www.armedslack.org/doku.php?id=getslack).

```
mkdir armedslack
cd armedslack
rsync -Pavv --delete ftp.armedslack.org::armedslack/armedslack-current .
```

2. Install an 8GB MMC card. We used high-speed model from Sandisk, no problems.

3. Attach to the plug PC with a mini USB to USB A cable. Linux terminal instructions are in the Slackware install doc here:
[ftp://ftp.armedslack.org/armedslack/armedslack13.3/INSTALL_KIRKWOOD.TXT](ftp://ftp.armedslack.org/armedslack/armedslack13.3/INSTALL_KIRKWOOD.TXT)

Windows USB serial drivers are here, also more Linux help:

http://www.plugcomputer.org/plugwiki/index.php/Serial_terminal_program

4. Follow installation instructions at:

[ftp://ftp.armedslack.org/armedslack/armedslack/3.37/INSTALL_KIRKWOOD.TXT](ftp://ftp.armedslack.org/armedslack/armedslack/3.37/INSTALL_KIRKWOOD.TXT)

5. Set up a TFTP and NFS server. Instructions for Ubuntu are below.

[TFTP](http://www.davidsudjiman.info/2006/03/27/installing-and-setting-tftpd-in-ubuntu/)

[NFS](https://help.ubuntu.com/community/SettingUpNFSHowTo)

a. If you get a CRC error on the boot or root image, re-download it from the mirror site and try again. This seems to be a common problem. Also, be sure you did not download and of the packages
in ASCII mode.

b. You need to run _mmcinit_ twice on the boot loader to get it to recognize the card.

c. Use an ext2 file system for the /boot volume. The / volume can be ext4 (recommended for journaling)

d. The device names should be as follows:
```
/dev/mmcblk0p1            2048      206847      102400   83  Linux 
/dev/mmcblk0p2          206848     1845247      819200   82  Linux swap 
/dev/mmcblk0p3         1845248    15646719     6900736   83  Linux 
```

Using _/dev/sda1,sda2,sda3_ does not work! These file system sizes are good for the 8GB card.

e. Use these boot arguments:
```
Marvell>>   setenv bootargs_console console=ttyS0,115200 
# note changed device file: 
Marvell>>   setenv bootargs_root 'root=/dev/mmcblk0p3 waitforroot=10 rootfs=ext4' 
Marvell>>   setenv bootcmd 'setenv bootargs $(bootargs_console) $(bootargs_root); run bootcmd_slk ; reset' 
# for MMC: 
Marvell>>   setenv bootcmd_slk 'mmcinit;ext2load mmc 0:1 0x01100000 /uinitrd-kirkwood;ext2load mmc 0:1 0x00800000 /uImage-kirkwood;bootm 0x00800000 0x01100000' 
# save 
Marvell>>   saveenv 
Marvell>>   reset 
```

f. Additional help is available [here.](http://think-deep.com/wiki/becki/linux/sheevaplug)

6. Install these packages:
-All dev/make/gcc/binutils/glibc/kernel headers/etc for building sources. This is much easier to do from the inititial installation script. pkgtool does not let you see the "everything" and "all dev" type options later. You'll get stuck having to manually add missing libraries/etc like I did, so watch out!

-_iptables_ (Needed for securing the system later)

-All networking, openssl, basic required packages.
-All Marvell utilities in the Slackware distribution

-These specific packages we need for the Security Monitoring scripts:

a. _msmtp_ (Command-line mail sending client. Will work with SMTP/Gmail/Yahoo/etc)
> Download and build from:
> http://msmtp.sourceforge.net
> Must also install openSSL for TLS/SSL support!
> Also, install a root CA file from Firefox or similar in:
> _/etc/ssl/certs/ca-certificates.crt_

b. _minicom_ (Terminal program, we use this to communicate with the Arduino.)
> Use the built-in Slackware package, but be aware that it will just hang and seg-fault
> unless you first modify this file:
> > /etc/minirc.dfl -> Open this file in vi and add a carriage return/line feed at the bottom and save.

c. _screen_ (We use screen to run minicom interactively)


**Note:**

A complete installation of everything will fit on the 8GB flash card. You can also pull the
flash card out and copy the complete set of package files from your host PC to a directory once the
basic install is completed. This will leave you with abotu 2GB free on the / file system.

7. Configure networking and plug in your Arduino to the large USB 'A' port. The stock kernel seems
to have no problem recognizing the built-in network devices and the FTDI chip on the Arduino is
recognized as :

_/dev/ttyUSB0_

8. Now it's time to configure our monitoring stuff. Follow these instructions:

### Setup the monitoring system ###
a. Create a normal user to run your monitoring scripts under. We'll call this user "access" for the tutorial.

b. Create a directory called "scripts" in their home directory. Place the following files in this directory and modify the e-mail addresses, messages, etc as needed.

start\_screen\_logging.sh
```
#!/bin/bash
# Start logging functions in a screen
/bin/su - access -c "screen -dmS MINICOM /home/access/scripts/start_logging.sh"
```


log\_notify.sh
```
#!/bin/bash
tail -0f /home/access/scripts/access_log.txt | egrep --line-buffered -i "authenticated" | while read line
        do
                rm /home/access/scripts/message_tmp.txt
                cp /home/access/scripts/log_msg.txt /home/access/scripts/message_tmp.txt
                sleep 1
                tail -6 /home/access/scripts/access_log.txt >> /home/access/scripts/message_tmp.txt
                msmtp -t < /home/access/scripts/message_tmp.txt
        done
```

log\_alert.sh
```
#!/bin/bash
cd /home/access/scripts
tail -0f /home/access/scripts/access_log.txt | egrep --line-buffered -i "triggered" |
while read line
        do
                msmtp -t < /home/access/scripts/alert_msg.txt
        done
```

log\_msg.txt
```
From:hackerspace_notifier@yourdomain.com
To:somebody@domain.com, somebody_else@anotherdomain.com
Subject:User at the Hacker Space
```


&lt;BR&gt;


log\_alert.txt
```
From:hackerspace_notifier@yourdomain.com
To:somebody@domain.com, somebody_else@anotherdomain.com
Subject: Alert: Alarm triggered at shop

Please log in to the webcame at http://www.somedomain.com/cameras to check status.

-The Hacker Space
```

start\_logging.sh
```
#!/bin/bash
/usr/bin/minicom -C /home/access/scripts/access_log.txt
```

c. Secure the scripts directory:
_chmod -r 700 /home/access/scripts_

d. Secure the USB serial port:

```
chown root:dialout /dev/ttyUSB0

chmod 770 /dev/ttyUSB0

ls -al /dev/ttyU*

crw-rw---- 1 root dialout 188, 0 2011-09-25 16:36 /dev/ttyUSB0
```

Add the user "access" to the group dialout:
_gpasswd -a access dialout_
_dialout:x:16:access_

e. run _minicom -s_ and configure the comm parameters. The defaults for Open Access are:

/etc/minirc.dfl
```
pr port             /dev/ttyUSB0
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
/etc/sysconfig/iptables
/bin/su - access -c "/home/access/scripts/log_notify.sh &"
/bin/su - access -c "/home/access/scripts/log_alert.sh &"
/home/access/scripts/start_screen_logging.sh
```

i. With the Arduino connected, reboot everything and verify that it all comes up automatically. You should be able to log in via ssh, type "screen -rd" and be connected to an interactive session on the Arduino. Please secure the ssh system with certificates and/or good passwords.


---

Open Access Control by [23b Shop](http://shop.23b.org) is licensed under a [Commons Attribution 3.0 Unported License](http://creativecommons.org/licenses/by/3.0/Creative).

Based on a work at [code.google.com](http://code.google.com).