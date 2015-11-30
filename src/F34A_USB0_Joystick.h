//-----------------------------------------------------------------------------
// F3xx_USB0_Mouse.h
//-----------------------------------------------------------------------------
// Copyright 2014 Silicon Laboratories, Inc.
// http://www.silabs.com
//
// Program Description:
//
// Header file for mouse routines.
//
//
// How To Test:    See Readme.txt
//
//
// Target:         ToolStick342DC
// Tool chain:     Simplicity Studio / Keil C51 9.51
// Project Name:   F3xx_MouseExample
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
#ifndef  _MOUSE_H_
#define  _MOUSE_H_

extern signed char MOUSE_VECTOR;
extern U8 MOUSE_AXIS;
extern U8 MOUSE_BUTTON;
extern U8 IN_PACKET[7];
extern U8 REPORT_STYLE;
extern U8 DESCRIPTOR_STYLE;

#define X_Axis 0
#define Y_Axis 1

void System_Init(void);
void USB0_Init(void);

#endif  /* _MOUSE_H_ */
