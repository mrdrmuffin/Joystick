//-----------------------------------------------------------------------------
// F342DC_USB_Main.c
//-----------------------------------------------------------------------------
// Copyright 2014 Silicon Laboratories, Inc.
// http://developer.silabs.com/legal/version/v11/Silicon_Labs_Software_License_Agreement.txt
//
// Program Description:
//
// This application will communicate with a PC across the USB interface.
// The device will appear to be a mouse, and will manipulate the cursor
// on screen.
//
// How To Test:    See Readme.txt
//
//
// Target:         ToolStick342DC
// Tool chain:     Simplicity Studio / Keil C51 9.51
// Project Name:   F342DC_MouseExample
//
//
// Release 1.2 (BL)
//    - Updated Description / How to Test
//    - 21 MAR 2014
//
// Release 1.1
//    -Minor code comment changes
//    -16 NOV 2006
// Release 1.0
//    -Initial Revision (PD)
//    -07 DEC 2005
//

//-----------------------------------------------------------------------------
// Includes
//-----------------------------------------------------------------------------

#include "SI_C8051F340_Register_Enums.h"
#include "F34A_USB0_InterruptServiceRoutine.h"
#include "F34A_USB0_Joystick.h"

//-----------------------------------------------------------------------------
// Main Routine
//-----------------------------------------------------------------------------
void main(void)
{
   System_Init ();
   JOYSTICK_STYLE = P1;
   USB0_Init ();

   IE_EA = 1;
   while (1)
   {
      SendPacket (0);
   }
}
