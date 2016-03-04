# Introduction #
If you pick up a lock catalog, there are a huge number of choices for electric strikes, door magnets, and locks. This article is designed to help you choose appropriate hardware for your home or commercial door.

---

## Disclaimer ##
This page was not written by locksmiths. Modifying a fire-rated door may void its rating, and installing your hardware incorrectly may lock you out. No warranties as to the safety, fitness for use or reliability of this project are expressed or implied.

---

## Intro to Electrified Door Locks ##
The basic requirement for any electronic access control system is that you be able to close a relay, energize (or de-energize) some piece of physical hardware, and thus unlock the door. There are several types of doors that we will cover:

  * Garage doors - These are trivial to electrify, provided that you have an electric garage door opener installed. Electrifying one of these simply involves tapping the "door open" button on the wall and running it to one of your relays. Be sure to check with a multimeter to see if the button is normally open (NO) or normally closed (NC) and connect the appropriate terminals.

  * Residential deadbolts. This would be your typical Kwikset or Schlage lock set as found in most homes in North America. They usually mount in a 2.25" hole. Options for electrifying these include special door strikes that will push in and release the latch, surface-mounted hardware that does not use the installed lock, and modified ["keyless entry"](http://www.google.com/search?q=schlage+keyless) sets available from hardware stores. Modifying one of these consists of opening it up, finding the solenoid, and soldering wires to it. You can run the wires through the door or via a piece of flex cable to your panel. A 3-6V power source (to match the battery supply) will be needed.

  * Commercial doors with mortise locks. These can be identified as the type of door where most of the hardware is embedded in a large pocket in the door edge. The only bits you may see from the outside are a small round lock cylinder and some type of handle. Common brands are Sargent, Adams Rite, and the professional lines from Schlage.  A commercial lock catalog will have many variations of electric hardware for these.

  * Glass store front doors. The majority of retail and office space in the U.S. comes equipped with an Aluminum-frame door containing an Adams-Rite mortise deadbolt or dead latch. There is specific hardware available from the manufacturer for this.

  * Other types of doors. A common way to electrify anything else (interior doors, doors where you do not have access to the door frame to run a strike or wires) is a door magnet. These are large electromagnets that are typically bolted into the top of the door and are rated for 1000-2500lbs holding force. When energized, they keep the door shut. They are also "fail secure," meaning that the door will open when power is interrupted. This can be a good thing for a fire exit, but may not be a good thing for a secure area.

## How to Measure your Door ##
There are a few key parameters that you must know in order to order lock hardware. These measurements mostly apply to mortise locks, but may be asked for when ordering for other types.


1. Handing - This refers to what direction the door opens, with respect to the hinges and interior.

The way this is specified is really confusing. There are only two types of locks Adams Rite sells for these doors. "LH" or "Left Hand" is the same as "RRH" or "Reverse Right Hand" for purposes of  ordering parts. We have the LH/RRH, as our door opens out, with thedoorknob on the left if you are standing outside looking at it. Here is a good description:

[Door handing guide](http://www.directdoorhardware.com/door_handing.htm)

[Convenient chart](http://www.doorwaysplus.com/helpful-information/doorway-handing-chart)

2. Backset - This is the distance between the center of the keyhole
and the front edge of the lock. Ours was 1 1/8", which is pretty
common for glass store front doors. Your door edge might be tapered or rounded, so measure the front edge first.

3. Door edge - If you open the door and look at the edge, it could be
square, rounded or beveled. The trim plate that covers the locking
mechanism might be available in more than one contour. If it is, get
it. If not, the rounded one will fit anyway. Ours came with both a
square and rounded one.

## How to take apart a mortise lock ##
Taking apart most mortise locks pretty easy. The steps for an Adams Rite are as follows:

1. Open the door and unscrew the trim plate that covers the locking mechanism on the door edge. There should be two Allen head or flat-head screws visible. Unscrew them about 10 turns, then grasp the lock cylinder (use the key partially inserted or a screwdriver) unscrew the lock cylinder from the door front. Remove the lock cylinder or exit device from the inside using the same procedure.

2. There may also be a "locked/unlocked" status indicator on the inside. Remove this as well.

3. Looking at the door edge, you should see two long bolts securing the deadbolt mechanism to the door frame. Remove these, and the whole mortise assembly will come out.

## How to run the wiring ##
Most metal doors are hollow, and all Aluminum frame glass doors have hollow edges. You can use a fish tape to run a 2-pair wire from the lock, through the frame, and up to a corner by the hinge. There are a couple of options for getting power to the door:

  * Electrified hinges - These are sexy, but may require professional installation. This is a good option to ask for if you are ordering a new door.
  * Armored security cable. This is a 1/4" diameter metal cable that looks like the outside of a payphone handset cord. They typically come with hardware that lets you terminate them into the door frame and door, and they are hollow. We used a "Securitron" brand cable, which is pretty standard. You can mount the end of this to the door frame (if it's hollow and you have access to the attic to fish it) or to a junction box like you would use for a network cable drop.

## Voltage and amperage considerations ##
Many of the newer strikes and door locks use a low-current solenoid that simply moves a pin out of the way, allowing the user to pull or push the door open. These usually use 200ma - 1A of current.

Some systems have very powerful solenoids, and will require a 5A or larger power supply and wiring.

  * Most of the newer device mentioned above will work with 18-22ga wire, depending on the length of the run. You can often get away with CAT5 cable if you solder some of the pairs together. Always check the manufacturer's data sheet to be sure.
  * Watch out for continuous vs. intermittent duty cycles. Some hardware cannot be left in an unlocked state indefinitely, while other models can.
  * AC vs. DC. The voltage rating for AC current is often different than DC, as some of these devices rely on inductance to present the proper load to the power supply. Running a 12VAC rated device at 12VDC may cause it to overheat.
  * Door supervision - Some hardware comes with an open/closed sensor inside the lock. This is a nice, clean way to run the door sensor lines, but be sure to check before ordering. Many manufacturers make several variants of their hardware, and you may get one that is wired up for it but does not have the feature installed.
  * It probably goes without saying, but you MUST protect the wiring to these devices if you want to have any security at all. Unlike the reader inputs, tampering with the door hardware can lead to immediate access being granted.


---

Open Access Control by [23b Shop](http://shop.23b.org) is licensed under a [Commons Attribution 3.0 Unported License](http://creativecommons.org/licenses/by/3.0/Creative).

Based on a work at [code.google.com](http://code.google.com).