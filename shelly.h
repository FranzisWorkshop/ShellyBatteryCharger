/**
 *  Project:    Ladeschalter
 *  Author:     Franz Lorenz
 *  Copyright:  Franz Lorenz, Kelheim
 *
 *  Shelly EM3 handler. 
 */

//----------------------------------------------------------
//  SYSTEM
#include "ESP8266WiFi.h"
#include "ESP8266HTTPClient.h"
#include <WiFiClientSecure.h>

//----------------------------------------------------------
//  DEFINES
#define  SHELLY_DEBUG            0

//----------------------------------------------------------
//  TYPEDEFs

//----------------------------------------------------------
//  GLOBALS
WiFiClient  shellyWifiClient;
HTTPClient  shellyHttpClient;
String      shellyRequest = "http://192.168.178.39/emeter/2/current";
String      shellyData = "";
int         shellyState = 0;
int         shellySolarPower = 0;

//----------------------------------------------------------
//  LOCAL FUNCTIONS

//----------------------------------------------------------
//  API FUNCTIONS

/**
 *  This function initialize the meteo service.
 */
void shellyInit( void )
{
  #if defined SHELLY_DEBUG
    Serial.println( "shellyInit()" );
  #endif
  shellyState = 0;
}

/**
 *  This function triggers the update.
 */
void shellyTriggerUpdate( void )
{
  shellyState = 0;
}

int shellyIsQuery( void )
{
  int iRet = 0;
  if( shellyState < 6 )
    iRet = 1;
  return iRet;
}

/**
 *  This function returns the current solar power in Watt.
 *  @return   int     solar power in watt
 */
int shellyGetSolarPower( void )
{
  return shellySolarPower;
}

/**
 *  This function updates the power
 */
void shellyHandle( void )
{
  int     iPos1;
  int     iPos2;
  //
  #if defined SHELLY_DEBUG
    Serial.print( "shellyHandle() : state " );
    Serial.println( shellyState );
  #endif
  //
  switch( shellyState )  
  {
    case 0 :
      if( wifiIsConnected() )
      {
        shellyState++;
      }
      break;
      //
    case 1 :
      #if defined SHELLY_DEBUG
        Serial.print( "shelly request " );
        Serial.println( shellyRequest );
      #endif
      if( wifiIsConnected() )
      {
        shellyHttpClient.begin( shellyWifiClient, shellyRequest.c_str() );
        shellyState++;
      }
      else
      break;
      //
    case 2 :
      if( wifiIsConnected() )
      {
        if( shellyHttpClient.GET() > 0 )
        {
          shellyState++;
        }
      }
      break;
      //
    case 3 :
      shellyData = shellyHttpClient.getString();
      #if defined SHELLY_DEBUG
        Serial.println( shellyData );
      #endif
      shellyState++;
      break;
      //
    case 4 :
      shellyHttpClient.end();
      shellyState++;
      break;
      //
    case 5 :
      iPos1 = shellyData.indexOf( "power\":" );
      if( iPos1 >= 0 )
      {
        iPos1 += 7;
        iPos2 = shellyData.indexOf( ",", iPos1 );
        shellySolarPower = shellyData.substring( iPos1, iPos2 ).toInt();
        shellyState = 6;
      }
      else
      {
        shellyState = 0;
      }
      break;
      //
    case 6 :
      break;
      //
    default:
      shellyState = 0;
      break;
  }
}

