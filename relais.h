/**
 *  Project:    Ladeschalter
 *  Author:     Franz Lorenz
 *  Copyright:  Franz Lorenz, Kelheim
 */

//----------------------------------------------------------
//  SYSTEM

//----------------------------------------------------------
//  DEFINES

//----------------------------------------------------------
//  TYPEDEFs

//----------------------------------------------------------
//  GLOBALS

boolean   bRelaisState = false;


//----------------------------------------------------------
//  API FUNCTIONS

/**
 *  This function initialize the relais interface.
 */
void relaisInit( void )
{
  pinMode( RELAIS_GPIO, OUTPUT );
  digitalWrite( RELAIS_GPIO, LOW );
  bRelaisState = false;
}

/**
 *  This function sets the relais state.
 *  @param  bOn     on
 */
void relaisSet( boolean bOn )
{
  bRelaisState = bOn;
  if( bOn )
    digitalWrite( RELAIS_GPIO, HIGH );
  else
    digitalWrite( RELAIS_GPIO, LOW );
}

/**
 *  This function returns the current state.
 *  @return   boolean   state
 */
boolean relaisGet( void )
{
  return bRelaisState;
}
