/**
 *  Project:    Ladeschalter
 *  Author:     Franz Lorenz
 *  Copyright:  Franz Lorenz, Kelheim
 */


#define   VERSION         "1.0"

//----------------------------------------------------------
//  INCLUDES
#include "config.h"                     //configuration for all following modules
#include "datetime.h"
#include "relais.h"
#include "wifi.h"
#include "shelly.h"
#include "led.h" 
#include "button.h"

//----------------------------------------------------------
//  DEFINES

//----------------------------------------------------------
//  LOCALS
int   iSec = -1;
int   iPower = 0;

//----------------------------------------------------------
//  ARDUINO FRAMEWORK

/**
 *  This function is called, when the system starts.
 */
void setup()
{
  ledInit();
  relaisInit();
  buttonInit();
  datetimeInit();
  wifiInit();
  //
  Serial.begin( 115200 );
  while( !Serial );
  delay( 300 );
  //
  shellyInit();
} //void setup()

/**
 *  This function is called, when the system starts.
 */
void loop()
{
  if( Serial.available() > 0 ) 
  {
    String sDebug = Serial.readString();
    sDebug.trim();
    if( sDebug == "shelly" )
    {
      shellyTriggerUpdate();
    }
  }  
  //
  datetimeHandle();
  ledHandle();
  wifiHandle();
  //
  if( iSec != datetimeSec() )
  {
    iSec = datetimeSec();
    shellyHandle();
    //
    Serial.println( datetimeGet() );
    Serial.print( " wifi:" );
    Serial.print( wifiIsEnabled() );
    Serial.print( " solarpwr:" );
    Serial.print( shellyGetSolarPower() );
    Serial.print( " relais:" );
    Serial.println( relaisGet() );

  }
} //void loop()
