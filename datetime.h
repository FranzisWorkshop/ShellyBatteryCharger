/**
 *  Project:    Zeitschaltuhr
 *  Author:     Franz Lorenz
 *  Copyright:  Franz Lorenz, Kelheim
 */

//----------------------------------------------------------
//  INCLUDES
#include  <time.h>

//----------------------------------------------------------
//  SYSTEM
#if !defined( ESP8266 )
  #error This code is designed to run on ESP8266 and ESP8266-based boards! Please check your Tools->Board setting.
#endif

//----------------------------------------------------------
//  DEFINES
#define   DAYOFWEEK_SUNDAY            0
#define   DAYOFWEEK_MONDAY            1
#define   DAYOFWEEK_TUESDAY           2
#define   DAYOFWEEK_WEDNESDAY         3
#define   DAYOFWEEK_THURSDAY          4
#define   DAYOFWEEK_FRIDAY            5
#define   DAYOFWEEK_SATURDAY          6
#define   DAYOFWEEK_MAX               7

//----------------------------------------------------------
//  TYPEDEFs

//----------------------------------------------------------
//  GLOBALS
time_t        datetimeNow; 
tm            DateTime;
boolean       datetimeFirst = true;
boolean       datetimeUpdate = true;

//----------------------------------------------------------
//  LOCAL FUNCTIONS

//----------------------------------------------------------
//  API FUNCTIONS

/**
 *  This function initialize the clock, calendar
 *  and the timer 1 second interrupt function.
 */
void datetimeInit( void )
{
  DateTime.tm_hour  = 12;
  DateTime.tm_min   = 0;
  DateTime.tm_sec   = 0;
  DateTime.tm_wday  = 1;
  DateTime.tm_mon   = 1;
  DateTime.tm_year  = 2024-1900;
  DateTime.tm_wday  = 0;
  //
  datetimeFirst = true;
  datetimeUpdate = true;
  configTime( NTP_SERVER_URL, NTP_SERVER_CONFIG );
}

/**
 *  This function returns "true" if the time/date is set to ntp server.
 *  Otherwise "false".
 */
boolean datetimeIsSet( void )
{
  return ! datetimeFirst;
}

/**
 *  This function sets the update.
 *  @param  bUpdate   update flag
 */
void datetimeSetUpdate( boolean bUpdate )
{
  datetimeUpdate = bUpdate;
}

/**
 *  This function handles the time/date information.
 */
void datetimeHandle( void )
{
  tm  tmTemp;
  //
  if( datetimeUpdate )
  {
    time( &datetimeNow );
    if( datetimeFirst )
    {
      localtime_r( &datetimeNow, &tmTemp );  
      if( tmTemp.tm_hour != 0 )
        datetimeFirst = false;
    }
    else 
    {
      localtime_r( &datetimeNow, &DateTime );
    }
  }
}

/**
 *  This function returns the current day_of_week as string.
 *  @return   string    day_of_week
 */
String datetimeGetDayOfWeek( void )
{
  String sRet = "";
  switch( DateTime.tm_wday ) 
  {
    case 0: sRet = "SON";   break;
    case 1: sRet = "MON";   break;
    case 2: sRet = "DIE";   break;
    case 3: sRet = "MIT";   break;
    case 4: sRet = "DON";   break;
    case 5: sRet = "FRE";   break;
    case 6: sRet = "SAM";   break;
    default:                break;
  }
  return sRet;
}

/**
 *  This function sets the time
 *  @param  iHour     hour
 *  @param  iMin      minutes
 *  @param  iSec      seconds
 */
void datetimeSetTime( int iHour, int iMin, int iSec )
{
  iHour--;  if( iHour < 0 ) iHour = 23;
  DateTime.tm_hour  = iHour;
  DateTime.tm_min   = iMin;
  DateTime.tm_sec   = iSec;
}

/**
 *  This function sets the day-of-week number.
 *  @param  iDayOfWeek    day of week (see DAYOFWEEK defines)
 */
void datetimeSetDayOfWeek( int iDayOfWeek )
{
  DateTime.tm_wday = iDayOfWeek;
}

/**
 *  This function returns the current seconds.
 *  @return int   seconds [0..59]
 */
int datetimeSec( void )
{ return DateTime.tm_sec; }

/**
 *  This function returns the current minutes.
 *  @return int   minutes [0..59]
 */
int datetimeMin( void )
{ return DateTime.tm_min; }

/**
 *  This function returns the current hour.
 *  @return int   hour [0..23]
 */
int datetimeHour( void )
{ 
  int iHour = DateTime.tm_hour;
  iHour++;  if( iHour > 23 ) iHour = 0;
  return iHour;
}

/**
 *  This function returns a string with the current time.
 *  @return String
 */
String datetimeGet( void )
{
  char cBuf[20];
  sprintf( cBuf, "%s %02d:%02d:%02d", datetimeGetDayOfWeek(), datetimeHour(), datetimeMin(), datetimeSec() );
  String sRet( cBuf );
  return sRet;
}
