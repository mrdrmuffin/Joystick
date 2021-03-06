//-----------------------------------------------------------------------------
// F342DC_USB0_Descriptor.c
//-----------------------------------------------------------------------------
// Copyright 2014 Silicon Laboratories, Inc.
// http://developer.silabs.com/legal/version/v11/Silicon_Labs_Software_License_Agreement.txt
//
// Program Description:
//
// Source file for USB firmware. Includes descriptor data.
//
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
#include "F34A_USB0_Register.h"
#include "F34A_USB0_InterruptServiceRoutine.h"
#include "JoystickDescriptor.h"

//-----------------------------------------------------------------------------
// Descriptor Declarations
//-----------------------------------------------------------------------------

const device_descriptor code XBOX360_DEVICEDESC =
{
   18,                                 // bLength
   0x01,                               // bDescriptorType
   0x1101,                             // bcdUSB
   0x03,                               // bDeviceClass
   0x03,                               // bDeviceSubClass
   0x00,                               // bDeviceProtocol
   EP0_PACKET_SIZE,                    // bMaxPacketSize0
   0x045E,                             // idVendor
   0x028E,                             // idProduct
   0x0000,                             // bcdDevice
   0x01,                               // iManufacturer
   0x02,                               // iProduct
   0x00,                               // iSerialNumber
   0x01                                // bNumConfigurations
}; //end of DEVICEDESC

const device_descriptor code SILABS_DEVICEDESC =
{
   18,                                 // bLength
   0x01,                               // bDescriptorType
   0x1101,                             // bcdUSB
   0x03,                               // bDeviceClass
   0x03,                               // bDeviceSubClass
   0x00,                               // bDeviceProtocol
   EP0_PACKET_SIZE,                    // bMaxPacketSize0
   0xC410,                             // idVendor
   0xB987,                             // idProduct
   0x0000,                             // bcdDevice
   0x01,                               // iManufacturer
   0x02,                               // iProduct
   0x00,                               // iSerialNumber
   0x01                                // bNumConfigurations
}; //end of DEVICEDESC

const device_descriptor code SFJS_DEVICEDESC =
{
   18,                                 // bLength
   0x01,                               // bDescriptorType
   0x1101,                             // bcdUSB
   0x03,                               // bDeviceClass
   0x03,                               // bDeviceSubClass
   0x00,                               // bDeviceProtocol
   EP0_PACKET_SIZE,                    // bMaxPacketSize0
   0x3807,                             // idVendor
   0x3847,                             // idProduct
   0x0000,                             // bcdDevice
   0x01,                               // iManufacturer
   0x02,                               // iProduct
   0x00,                               // iSerialNumber
   0x01                                // bNumConfigurations
}; //end of DEVICEDESC

const device_descriptor code USB20_DEVICEDESC =
{
   18,                                 // bLength
   0x01,                               // bDescriptorType
   0x0002,                             // bcdUSB
   0x00,                               // bDeviceClass
   0x00,                               // bDeviceSubClass
   0x00,                               // bDeviceProtocol
   EP0_PACKET_SIZE,                    // bMaxPacketSize0
   0x3807,                             // idVendor
   0x3847,                             // idProduct
   0x0001,                             // bcdDevice
   0x01,                               // iManufacturer
   0x02,                               // iProduct
   0x00,                               // iSerialNumber
   0x01                                // bNumConfigurations
}; //end of DEVICEDESC

// From "USB Device Class Definition for Human Interface Devices (HID)".
// Section 7.1:
// "When a Get_Descriptor(Configuration) request is issued,
// it returns the Configuration descriptor, all Interface descriptors,
// all Endpoint descriptors, and the HID descriptor for each interface."
const hid_configuration_descriptor code HIDCONFIGDESC =
{

{ // configuration_descriptor hid_configuration_descriptor
   0x09,                               // Length
   0x02,                               // Type
   0x2200,                             // Totallength (= 9+9+9+7)
   0x01,                               // NumInterfaces
   0x01,                               // bConfigurationValue
   0x00,                               // iConfiguration
   0x80,                               // bmAttributes
   0xFA                                // MaxPower (in 2mA units)
},

{ // interface_descriptor hid_interface_descriptor
   0x09,                               // bLength
   0x04,                               // bDescriptorType
   0x00,                               // bInterfaceNumber
   0x00,                               // bAlternateSetting
   0x01,                               // bNumEndpoints
   0x03,                               // bInterfaceClass (3 = HID)
   0x00,                               // bInterfaceSubClass
   0x00,                               // bInterfaceProcotol
   0x00                                // iInterface
},

{ // class_descriptor hid_descriptor
	0x09,	                              // bLength
	0x21,	                              // bDescriptorType
	0x1101,	                           // bcdHID
	0x00,	                              // bCountryCode
	0x01,	                              // bNumDescriptors
	0x22,                               // bDescriptorType
	HID_REPORT_DESCRIPTOR_SIZE_LE       // wItemLength (tot. len. of report
                                       // descriptor)
},

// IN endpoint (mandatory for HID)
{ // endpoint_descriptor hid_endpoint_in_descriptor
   0x07,                               // bLength
   0x05,                               // bDescriptorType
   0x81,                               // bEndpointAddress
   0x03,                               // bmAttributes
   EP1_PACKET_SIZE_LE,                 // MaxPacketSize (LITTLE ENDIAN)
   10                                  // bInterval
},

// OUT endpoint (optional for HID)
{ // endpoint_descriptor hid_endpoint_out_descriptor
   0x07,                               // bLength
   0x05,                               // bDescriptorType
   0x01,                               // bEndpointAddress
   0x03,                               // bmAttributes
   EP2_PACKET_SIZE_LE,                 // MaxPacketSize (LITTLE ENDIAN)
   10                                  // bInterval
}

};

const hid_report_descriptor code HIDREPORTDESC =
{
    /*0x05, 0x01,                        // Usage Page (Generic Desktop)
    0x09, 0x04,                        // Usage (Joystick)
    0xA1, 0x01,                        // Collection (Application)
    0xA1, 0x00,                        //   Collection (Physical)
    0x05, 0x09,                        //     Usage Page (Buttons)
    0x19, 0x01,                        //     Usage Minimum (01)
    0x29, 0x0E,                        //     Usage Maximum (01)
    0x15, 0x00,                        //     Logical Minimum (0)
    0x25, 0x01,                        //     Logical Maximum (1)
    0x95, 0x10,                        //     Report Count (16)
    0x75, 0x01,                        //     Report Size (1)
    0x81, 0x02,                        //     Input (Data, Variable, Absolute)
    0x95, 0x01,                        //     Report Count (1)
    0x75, 0x00,                        //     Report Size (7)
    0x81, 0x01,                        //     Input (Constant) for padding
    0xC0,                              //   End Collection (Physical)
    0xC0                               // End Collection (Application)*/

	/*0x05, 0x01, // Usage Page, Generic Desktop
    	0x09, 0x05, // Usage, Gamepad
        	0xA1, 0x01, // Collection Application
        		// Left and right joysticks. We use X and Y for the left joystick
        		// and Z and Rz for the right joystick by traditional convention.
        		// Each value is 1 byte, 0 - 255. We have 4 reports, one for each
        		// axis on each joystick.
        		0x09, 0x30, // Usage, JS direction X
        		0x09, 0x31, // Usage, JS direction Y
        		0x09, 0x32, // Usage, JS direction Z
        		0x09, 0x35, // Usage, JS direction Rz (Rotate-Z)
        		0x15, 0x00, // Logical Min (0)
        		0x26, 0xFF, 0x00, // Logical Max (255) [2-byte logical max]
        		0x75, 0x08,  // Report Size (8)
        		0x95, 0x04,  // Report Count (4)
        		// Padding or something? Look this up, copied from HORI FC4
        		// report descriptor
        		0x81, 0x02, // Input, Variable
        		// DPAD
				0x09, 0x39, // Usage, Hat Switch (DPAD)
				0x15, 0x00, // Logical Min (0)
				0x25, 0x07, // Logical Max (7)
				0x35, 0x00, // Physical Min (0)
				0x46, 0x3B, 0x01, // Physical Max (315)
				0x65, 0x14,  // Unit
				0x75, 0x04,  // Report Size (4)
				0x95, 0x01,  // Report Count (1)
				0x81, 0x42,  // Input (Variable, Null)
				0x65, 0x00,  // Unit
        		// Buttons (0A)
				0x05, 0x09, // Usage page button
				0x19, 0x01, // Usage Min, Button 1 (10 digital Buttons)
				0x29, 0x0A, // Usage Max, Button 10
				0x15, 0x00, // Logical Min (0)
				0x25, 0x01, // Logical Max (1)
				0x75, 0x01, // Report Size, 1
				0x95, 0x0A, // Report Count, 10
				0x81, 0x02, // Input, Variable
				// Padding or something? Look this up, copied from HORI FC4
				// report descriptor
				0x06, 0x00, 0xFF, // Usage page
				0x09, 0x20, // Usage data
				// Button Padding
				0x75, 0x02, // Report Size 2
				0x95, 0x01, // Report Count 1
				0x81, 0x02, // Input (constant)
				// 3rd joystick? This one doesn't seem to be used on the FC4
				0x05, 0x01, // Usage page button
				0x09, 0x33, // Usage, JS direction Rx (Rotate-X)
				0x09, 0x34, // Usage, JS direction Ry (Rotate-Y)
				0x15, 0x00, // Logical Min (0)
				0x26, 0xFF, 0x00, // Logical Max (255) [2-byte logical max]
				0x75, 0x08, // Report Size 8
				0x95, 0x02, // Report Count 1
				// Alignment padding (DWORD alignment)
				0x81, 0x02, // Input data
				0x06, 0x00, 0xFF, // Usage page
				0x09, 0x21, // Usage data
				0x95, 0x36,  // Report Count (1)

			0xC0 // End Collection*/

		0x05, 0x01, // Usage Page, Generic Desktop
		    	0x09, 0x05, // Usage, Gamepad
		        	0xA1, 0x01, // Collection Application
		        		// Buttons (0A)
						0x05, 0x09, // Usage page button
						0x19, 0x01, // Usage Min, Button 1 (10 digital Buttons)
						0x29, 0x0A, // Usage Max, Button 10
						0x15, 0x00, // Logical Min (0)
						0x25, 0x01, // Logical Max (1)
						0x75, 0x01, // Report Size, 1
						0x95, 0x0A, // Report Count, 10
						0x81, 0x02, // Input, Variable
						// Button Padding
						0x95, 0x06, // Report Count 6
						0x81, 0x01, // Input (constant)
						// DPAD
						0x05, 0x01, // Usage Page, Generic Desktop
						0x15, 0x01, // Logical Min (1)
						0x25, 0x08, // Logical Max (8)
						0x35, 0x00, // Physical Min (0)
						0x46, 0x3B, 0x01, // Physical Max (315)
						0x75, 0x04,  // Report Size (4)
						0x95, 0x01,  // Report Count (1)
						0x65, 0x14,  // Unit
						0x09, 0x39,  // Usage, Hat Switch (DPAD)
						0x81, 0x42,  // Input (Variable, Null)
						// Padding
						0x65, 0x00,  // Unit
						0x95, 0x01, // Report Count 1
						0x81, 0x01, // Input (constant)
		        		// Left and right joysticks. We use X and Y for the left joystick
		        		// and Z and Rz for the right joystick by traditional convention.
		        		// Each value is 1 byte, 0 - 255. We have 4 reports, one for each
		        		// axis on each joystick.
		        		0x09, 0x30, // Usage, JS direction X
		        		0x09, 0x31, // Usage, JS direction Y
		        		0x09, 0x33, // Usage, JS direction Rx
		        		0x09, 0x34, // Usage, JS direction Ry (Rotate-Z)
		        		0x15, 0x00, // Logical Min (0)
		        		0x25, 0xFF, // Logical Max (255)
						0x45, 0xFF, // Physical Max (255)
		        		0x75, 0x08,  // Report Size (8)
		        		0x95, 0x04,  // Report Count (4)
						0x81, 0x02, // Input, Variable

					0xC0 // End Collection
};

#define STR0LEN 4

code const U8 String0Desc [STR0LEN] =
{
   STR0LEN, 0x03, 0x09, 0x05
}; //end of String0Desc

#define STR1LEN sizeof ("MrDrMuffin Inc.") * 2

code const U8 String1Desc [STR1LEN] =
{
   STR1LEN, 0x03,
   'M', 0,
   'r', 0,
   'D', 0,
   'r', 0,
   'M', 0,
   'u', 0,
   'f', 0,
   'f', 0,
   'i', 0,
   'n', 0,
   ' ', 0,
   'I', 0,
   'n', 0,
   'c', 0,
   '.', 0
}; //end of String1Desc

#define STR2LEN sizeof ("Jewelry Box Joystick") * 2

code const U8 String2Desc [STR2LEN] =
{
   STR2LEN, 0x03,
   'J', 0,
   'e', 0,
   'w', 0,
   'e', 0,
   'l', 0,
   'r', 0,
   'y', 0,
   ' ', 0,
   'B', 0,
   'o', 0,
   'x', 0,
   ' ', 0,
   'J', 0,
   'o', 0,
   'y', 0,
   's', 0,
   't', 0,
   'i', 0,
   'c', 0,
   'k', 0
}; //end of String2Desc

U8* const STRINGDESCTABLE [] =
{
   String0Desc,
   String1Desc,
   String2Desc
};
