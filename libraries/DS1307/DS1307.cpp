/*
* Maurice Ribble
* 4-17-2008
* http://www.glacialwanderer.com/hobbyrobotics
* This code tests the DS1307 Real Time clock on the Arduino board.
* The ds1307 works in binary coded decimal or BCD.  You can look up
* bcd in google if you aren't familior with it.  There can output
* a square wave, but I don't expose that in this code.  See the
* ds1307 for it's full capabilities.
*
* Add Wire.begin(); to main setup function when ready to use.
*
* Modified 9/12/2009 by Arclight for C library use.
* arclight@gmail.com 
*/

#include <DS1307.h>
#include <Wire.h>


DS1307::DS1307(){

}

DS1307::~DS1307(){
}


// Convert normal decimal numbers to binary coded decimal
uint8_t DS1307::decToBcd(uint8_t val)
{
  return ( (val/10*16) + (val%10) );
}

// Convert binary coded decimal to normal decimal numbers
uint8_t DS1307::bcdToDec(uint8_t val)
{
  return ( (val/16*10) + (val%16) );
}

// Stops the DS1307, but it has the side effect of setting seconds to 0
// Probably only want to use this for testing

/*
void DS1307::stopDs1307()
{
  Wire.beginTransmission(DS1307_I2C_ADDRESS);
  Wire.send(0);
  Wire.send(0x80);
  Wire.endTransmission();
}
*/

// 1) Sets the date and time on the ds1307
// 2) Starts the clock
// 3) Sets hour mode to 24 hour clock
// Assumes you're passing in valid numbers

void DS1307::setDateDs1307(uint8_t second,        // 0-59
                   uint8_t minute,        // 0-59
                   uint8_t hour,          // 1-23
                   uint8_t dayOfWeek,     // 1-7
                   uint8_t dayOfMonth,    // 1-28/29/30/31
                   uint8_t month,         // 1-12
                   uint8_t year)          // 0-99
{
   Wire.beginTransmission(DS1307_I2C_ADDRESS);
   Wire.send(0);
   Wire.send(decToBcd(second));    // 0 to bit 7 starts the clock
   Wire.send(decToBcd(minute));
   Wire.send(decToBcd(hour));      // If you want 12 hour am/pm you need to set
                                   // bit 6 (also need to change readDateDs1307)
   Wire.send(decToBcd(dayOfWeek));
   Wire.send(decToBcd(dayOfMonth));
   Wire.send(decToBcd(month));
   Wire.send(decToBcd(year));
   Wire.endTransmission();
}

// Gets the date and time from the ds1307
void DS1307::getDateDs1307(uint8_t *second,
          uint8_t *minute,
          uint8_t *hour,
          uint8_t *dayOfWeek,
          uint8_t *dayOfMonth,
          uint8_t *month,
          uint8_t *year)
{
  // Reset the register pointer
  Wire.beginTransmission(DS1307_I2C_ADDRESS);
  Wire.send(0);
  Wire.endTransmission();

  Wire.requestFrom(DS1307_I2C_ADDRESS, 7);

  // A few of these need masks because certain bits are control bits
  *second     = bcdToDec(Wire.receive() & 0x7f);
  *minute     = bcdToDec(Wire.receive());
  *hour       = bcdToDec(Wire.receive() & 0x3f);  // Need to change this if 12 hour am/pm
  *dayOfWeek  = bcdToDec(Wire.receive());
  *dayOfMonth = bcdToDec(Wire.receive());
  *month      = bcdToDec(Wire.receive());
  *year       = bcdToDec(Wire.receive());
}

/*
  // Change these values to what you want to set your clock to.
  // You probably only want to set your clock once and then remove
  // the setDateDs1307 call.
uint8_t   second = 20;
uint8_t   minute = 9;
uint8_t   hour = 19;
uint8_t   dayOfWeek = 6;
uint8_t   dayOfMonth = 12;
uint8_t   month = 9;
uint8_t   year = 9;
setDateDs1307(second, minute, hour, dayOfWeek, dayOfMonth, month, year);
*/