//-----------------------------------------------------------------------------
// USB0_ReportHandler.c
//-----------------------------------------------------------------------------
// Copyright 2014 Silicon Laboratories, Inc.
// http://developer.silabs.com/legal/version/v11/Silicon_Labs_Software_License_Agreement.txt
//
// Program Description:
//
// Contains functions and variables dealing with Input and Output
// HID reports.
//
// How To Test:    See Readme.txt
//
//
// Target:         ToolStick342DC
// Tool chain:     Simplicity Studio / Keil C51 9.51
// Project Name:   F342DC_MouseExample
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

// ----------------------------------------------------------------------------
// Header files
// ----------------------------------------------------------------------------

#include "SI_C8051F340_Register_Enums.h"
#include "F34A_USB0_ReportHandler.h"
#include "F34A_USB0_InterruptServiceRoutine.h"
#include "F34A_USB0_Joystick.h"

// ----------------------------------------------------------------------------
// Local Function Prototypes
// ----------------------------------------------------------------------------

// ****************************************************************************
// Add custom Report Handler Prototypes Here
// ****************************************************************************

void IN_Report(void);
void OUT_Report(void);

// ----------------------------------------------------------------------------
// Local Definitions
// ----------------------------------------------------------------------------

// ****************************************************************************
// Set Definitions to sizes corresponding to the number of reports
// ****************************************************************************

#define IN_VECTORTABLESize 1
#define OUT_VECTORTABLESize 1

// ----------------------------------------------------------------------------
// Global Constant Declaration
// ----------------------------------------------------------------------------

// ****************************************************************************
// Link all Report Handler functions to corresponding Report IDs
// ****************************************************************************

const VectorTableEntry code IN_VECTORTABLE[IN_VECTORTABLESize] = {
// FORMAT: Report ID, Report Handler
		0, IN_Report };

// ****************************************************************************
// Link all Report Handler functions to corresponding Report IDs
// ****************************************************************************
const VectorTableEntry code OUT_VECTORTABLE[OUT_VECTORTABLESize] = {
// FORMAT: Report ID, Report Handler
		0, OUT_Report };

// ----------------------------------------------------------------------------
// Global Variable Declaration
// ----------------------------------------------------------------------------

BufferStructure IN_BUFFER, OUT_BUFFER;

// ----------------------------------------------------------------------------
// Local Functions
// ----------------------------------------------------------------------------

// ****************************************************************************
// Add all Report Handler routines here
// ****************************************************************************

// ****************************************************************************
// For Input Reports:
// Point IN_BUFFER.Ptr to the buffer containing the report
// Set IN_BUFFER.Length to the number of bytes that will be
// transmitted.
//
// REMINDER:
// Systems using more than one report must define Report IDs
// for each report.  These Report IDs must be included as the first
// byte of an IN report.
// Systems with Report IDs should set the FIRST byte of their buffer
// to the value for the Report ID
// AND
// must transmit Report Size + 1 to include the full report PLUS
// the Report ID.
//
// ****************************************************************************

static const U8 DPAD_MAPPING[] = {
        0,  // [0] Not pressed
        1,  // [1] Up
        5,  // [2] Down
        0,  // [3] Up and Down - Invalid
        3,  // [4] Left
        2,  // [5] Left and up
        4,  // [6] Left and down
        1,  // [7] Left, down, up - Left
        7,  // [8] Right
        8,  // [9] Right, up
        6,  // [A] Right, Down
        7,  // [B] Right, down, up - Right
        4,  // [C] Right, Left - Invalid
        1,  // [D] Right, Left, Up - Up
        5,  // [E] Right, Left, Down - Down
        0  //  [F] Right, Left, Down, Up - Invalid
    };

void IN_Report(void) {

    static unsigned char pack = 0x01;
	pack = pack << 1;
	if (pack == 0) {
		pack = 0x01;
	}

	BuildDInputReport();

	// point IN_BUFFER pointer to data packet and set
	// IN_BUFFER length to transmit correct report size
	IN_BUFFER.Ptr = IN_PACKET;
	IN_BUFFER.Length = 4;

}

void BuildXInputReport()
{
    U8 btnkey = ~P2 & 0x1; //(~P2 & 0xF) | (~P1<<4);

    btnkey |= (~P1 & 0x40) >> 5; // Button B,  2
    btnkey |= (~P2 & 0x02) << 1; // Button X,  3
    btnkey |= (~P1 & 0x80) >> 4; // Button Y,  4
    btnkey |= (~P1 & 0x04) << 2; // Button LB, 5
    btnkey |= (~P1 & 0x20);      // Button RB, 6
    btnkey |= (~P2 & 0x08) << 3; // Button BK, 7
    btnkey |= (~P2 & 0x04) << 5; // Button ST, 8

    // save left mouse button stat to bit 0 of first data byte
    IN_PACKET[0] = btnkey;
    IN_PACKET[1] = (~P1 & 0x18)>>3;
    IN_PACKET[2] = DPAD_MAPPING[~P2>>4];
}

void BuildDInputReport()
{
    U8 btnkey = 0;
    U8 packet1 = 0;

    btnkey |= (~P2 & 0x02) << 2; // Button X,  4

    btnkey |= (~P1 & 0x80) >> 7; // Button Y,  1

    btnkey |= (~P1 & 0x40) >> 5; // Button B,  2
    btnkey |= (~P2 & 0x01) << 2; // Button A,  3

    btnkey |= (~P1 & 0x04) << 2; // Button LB, 5
    btnkey |= (~P1 & 0x20);      // Button RB, 6


    btnkey |= (~P1 & 0x08) << 3; // Button LT, 8
    btnkey |= (~P1 & 0x10) << 3; // Button RT, 7

    packet1 |= (~P2 & 0x08) >> 3; // Button Select, 9
    packet1 |= (~P2 & 0x04) >> 1; // Button Start, 10

    // save left mouse button stat to bit 0 of first data byte
    IN_PACKET[0] = btnkey;
    IN_PACKET[1] = packet1;
    IN_PACKET[2] = DPAD_MAPPING[~P2>>4];
}

// ****************************************************************************
// For Output Reports:
// Data contained in the buffer OUT_BUFFER.Ptr will not be
// preserved after the Report Handler exits.
// Any data that needs to be preserved should be copyed from
// the OUT_BUFFER.Ptr and into other user-defined memory.
//
// ****************************************************************************

void OUT_Report(void) {
}

// ----------------------------------------------------------------------------
// Global Functions
// ----------------------------------------------------------------------------

// ****************************************************************************
// Configure Setup_OUT_BUFFER
//
// Reminder:
// This function should set OUT_BUFFER.Ptr so that it
// points to an array in data space big enough to store
// any output report.
// It should also set OUT_BUFFER.Length to the size of
// this buffer.
//
// ****************************************************************************

void Setup_OUT_BUFFER(void) {
}

// ----------------------------------------------------------------------------
// Vector Routines
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// ReportHandler_IN...
// ----------------------------------------------------------------------------
//
// Return Value - None
// Parameters - Report ID
//
// These functions match the Report ID passed as a parameter
// to an Input Report Handler.
// the ...FG function is called in the SendPacket foreground routine,
// while the ...ISR function is called inside the USB ISR.  A lock
// is set whenever one function is called to prevent a call from the
// other from disrupting the routine.
// However, this should never occur, as interrupts are disabled by SendPacket
// before USB operation begins.
// ----------------------------------------------------------------------------
void ReportHandler_IN_ISR(U8 R_ID) {
	U8 index;

	index = 0;

	while (index <= IN_VECTORTABLESize) {
		// check to see if Report ID passed into function
		// matches the Report ID for this entry in the Vector Table
		if (IN_VECTORTABLE[index].ReportID == R_ID) {
			IN_VECTORTABLE[index].hdlr();
			break;
		}

		// if Report IDs didn't match, increment the index pointer
		index++;
	}

}
void ReportHandler_IN_Foreground(U8 R_ID) {
	U8 index;

	index = 0;

	while (index <= IN_VECTORTABLESize) {
		// check to see if Report ID passed into function
		// matches the Report ID for this entry in the Vector Table
		if (IN_VECTORTABLE[index].ReportID == R_ID) {
			IN_VECTORTABLE[index].hdlr();
			break;
		}

		// if Report IDs didn't match, increment the index pointer
		index++;
	}

}

// ----------------------------------------------------------------------------
// ReportHandler_OUT
// ----------------------------------------------------------------------------
//
// Return Value - None
// Parameters - None
//
// This function matches the Report ID passed as a parameter
// to an Output Report Handler.
//
// ----------------------------------------------------------------------------
void ReportHandler_OUT(U8 R_ID) {

	U8 index;

	index = 0;

	while (index <= OUT_VECTORTABLESize) {
		// check to see if Report ID passed into function
		// matches the Report ID for this entry in the Vector Table
		if (OUT_VECTORTABLE[index].ReportID == R_ID) {
			OUT_VECTORTABLE[index].hdlr();
			break;
		}

		// if Report IDs didn't match, increment the index pointer
		index++;
	}
}
