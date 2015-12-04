//-----------------------------------------------------------------------------
// F3xx_USB0_Descriptor.h
//-----------------------------------------------------------------------------
// Copyright 2014 Silicon Laboratories, Inc.
// http://www.silabs.com
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
// Project Name:   F3xx_MouseExample
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

#ifndef  _USB_DESC_H_
#define  _USB_DESC_H_

#include "compiler_defs.h"

#define VENDOR 2    // 0 is default
                    // 1 is Street Fighter
                    // 2 is 360

// WORD type definition, for KEIL Compiler
#ifndef _WORD_DEF_                     // Compiler Specific, written for
                                       // Little Endian
#define _WORD_DEF_
typedef union {U16 i; U8 c[2];} WORD;
#define LSB 1                          // All words sent to and received
                                       // from the host are
#define MSB 0                          // little endian, this is switched
                                       // by software when neccessary.
                                       // These sections of code have been
                                       // marked with "Compiler Specific"
                                       // as above for easier modification
#endif   /* _WORD_DEF_ */

//------------------------------------------
// Standard Device Descriptor Type Defintion
//------------------------------------------
typedef /*code*/ struct
{
   U8 bLength;              // Size of this Descriptor in Bytes
   U8 bDescriptorType;      // Descriptor Type (=1)
   WORD bcdUSB;                        // USB Spec Release Number in BCD
   U8 bDeviceClass;         // Device Class Code
   U8 bDeviceSubClass;      // Device Subclass Code
   U8 bDeviceProtocol;      // Device Protocol Code
   U8 bMaxPacketSize0;      // Maximum Packet Size for EP0
   WORD idVendor;                      // Vendor ID
   WORD idProduct;                     // Product ID
   WORD bcdDevice;                     // Device Release Number in BCD
   U8 iManufacturer;        // Index of String Desc for Manufacturer
   U8 iProduct;             // Index of String Desc for Product
   U8 iSerialNumber;        // Index of String Desc for SerNo
   U8 bNumConfigurations;   // Number of possible Configurations
} device_descriptor;                   // End of Device Descriptor Type

//--------------------------------------------------
// Standard Configuration Descriptor Type Definition
//--------------------------------------------------
typedef /*code*/ struct
{
   U8 bLength;              // Size of this Descriptor in Bytes
   U8 bDescriptorType;      // Descriptor Type (=2)
   WORD wTotalLength;                  // Total Length of Data for this Conf
   U8 bNumInterfaces;       // No of Interfaces supported by this
                                       // Conf
   U8 bConfigurationValue;  // Designator Value for *this*
                                       // Configuration
   U8 iConfiguration;       // Index of String Desc for this Conf
   U8 bmAttributes;         // Configuration Characteristics (see below)
   U8 bMaxPower;            // Max. Power Consumption in this
                                       // Conf (*2mA)
} configuration_descriptor;            // End of Configuration Descriptor Type

//----------------------------------------------
// Standard Interface Descriptor Type Definition
//----------------------------------------------
typedef /*code*/ struct
{
   U8 bLength;              // Size of this Descriptor in Bytes
   U8 bDescriptorType;      // Descriptor Type (=4)
   U8 bInterfaceNumber;     // Number of *this* Interface (0..)
   U8 bAlternateSetting;    // Alternative for this Interface (if any)
   U8 bNumEndpoints;        // No of EPs used by this IF (excl. EP0)
   U8 bInterfaceClass;      // Interface Class Code
   U8 bInterfaceSubClass;   // Interface Subclass Code
   U8 bInterfaceProtocol;   // Interface Protocol Code
   U8 iInterface;           // Index of String Desc for this Interface
} interface_descriptor;                // End of Interface Descriptor Type

//------------------------------------------
// Standard Class Descriptor Type Definition
//------------------------------------------
typedef /*code */struct
{
   U8 bLength;              // Size of this Descriptor in Bytes (=9)
   U8 bDescriptorType;      // Descriptor Type (HID=0x21)
   WORD bcdHID;    				         // HID Class Specification
                                       // release number (=1.01)
   U8 bCountryCode;         // Localized country code
   U8 bNumDescriptors;	   // Number of class descriptors to follow
   U8 bReportDescriptorType;// Report descriptor type (HID=0x22)
   U16 wItemLength;			   // Total length of report descriptor table
} class_descriptor;                    // End of Class Descriptor Type

//---------------------------------------------
// Standard Endpoint Descriptor Type Definition
//---------------------------------------------
typedef /*code*/ struct
{
   U8 bLength;              // Size of this Descriptor in Bytes
   U8 bDescriptorType;      // Descriptor Type (=5)
   U8 bEndpointAddress;     // Endpoint Address (Number + Direction)
   U8 bmAttributes;         // Endpoint Attributes (Transfer Type)
   WORD wMaxPacketSize;	               // Max. Endpoint Packet Size
   U8 bInterval;            // Polling Interval (Interrupt) ms
} endpoint_descriptor;                 // End of Endpoint Descriptor Type

//---------------------------------------------
// HID Configuration Descriptor Type Definition
//---------------------------------------------
// From "USB Device Class Definition for Human Interface Devices (HID)".
// Section 7.1:
// "When a Get_Descriptor(Configuration) request is issued,
// it returns the Configuration descriptor, all Interface descriptors,
// all Endpoint descriptors, and the HID descriptor for each interface."
typedef code struct {
	configuration_descriptor 	hid_configuration_descriptor;
	interface_descriptor 		hid_interface_descriptor;
	class_descriptor 			hid_descriptor;
	endpoint_descriptor 		hid_endpoint_in_descriptor;
	endpoint_descriptor 		hid_endpoint_out_descriptor;
}
hid_configuration_descriptor;

#define HID_REPORT_DESCRIPTOR_SIZE 0x004A
#define HID_REPORT_DESCRIPTOR_SIZE_LE 0x4A00

typedef code U8 hid_report_descriptor[HID_REPORT_DESCRIPTOR_SIZE];

//-----------------------------
// SETUP Packet Type Definition
//-----------------------------
typedef struct
{
   U8 bmRequestType;        // Request recipient, type, and dir.
   U8 bRequest;             // Specific standard request number
   WORD wValue;                        // varies according to request
   WORD wIndex;                        // varies according to request
   WORD wLength;                       // Number of bytes to transfer
} setup_buffer;                        // End of SETUP Packet Type

#endif  /* _USB_DESC_H_ */
