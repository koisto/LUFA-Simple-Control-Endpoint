/*
             LUFA Library
     Copyright (C) Dean Camera, 2017.

  dean [at] fourwalledcubicle [dot] com
           www.lufa-lib.org
*/

/*
  Copyright 2017  Dean Camera (dean [at] fourwalledcubicle [dot] com)

  Permission to use, copy, modify, distribute, and sell this
  software and its documentation for any purpose is hereby granted
  without fee, provided that the above copyright notice appear in
  all copies and that both that the copyright notice and this
  permission notice and warranty disclaimer appear in supporting
  documentation, and that the name of the author not be used in
  advertising or publicity pertaining to distribution of the
  software without specific, written prior permission.

  The author disclaims all warranties with regard to this
  software, including all implied warranties of merchantability
  and fitness.  In no event shall the author be liable for any
  special, indirect or consequential damages or any damages
  whatsoever resulting from loss of use, data or profits, whether
  in an action of contract, negligence or other tortious action,
  arising out of or in connection with the use or performance of
  this software.
*/

/** \file
 *
 *  Main source file for the Bulk Vendor demo. This file contains the main tasks of the demo and
 *  is responsible for the initial application hardware configuration.
 */

#define  INCLUDE_FROM_BULKVENDOR_C
#include "ControlEnd.h"


/** Main program entry point. This routine configures the hardware required by the application, then
 *  enters a loop to run the application tasks in sequence.
 */
int main(void)
{
	SetupHardware();

	LEDs_SetAllLEDs(LEDMASK_USB_NOTREADY);
	GlobalInterruptEnable();

	for (;;)
	{
		USB_USBTask();

/*		uint8_t ReceivedData[VENDOR_IO_EPSIZE];
		memset(ReceivedData, 0x00, sizeof(ReceivedData));

		Endpoint_SelectEndpoint(VENDOR_OUT_EPADDR);
		if (Endpoint_IsOUTReceived())
		{
			Endpoint_Read_Stream_LE(ReceivedData, VENDOR_IO_EPSIZE, NULL);
			Endpoint_ClearOUT();

			Endpoint_SelectEndpoint(VENDOR_IN_EPADDR);
			Endpoint_Write_Stream_LE(ReceivedData, VENDOR_IO_EPSIZE, NULL);
			Endpoint_ClearIN();
		}
*/	}
}

/** Configures the board hardware and chip peripherals for the demo's functionality. */
void SetupHardware(void)
{
	/* Disable watchdog if enabled by bootloader/fuses */
	MCUSR &= ~(1 << WDRF);
	wdt_disable();

	/* Disable clock division */
	clock_prescale_set(clock_div_1);

	/* Hardware Initialization */
	LEDs_Init();
	USB_Init();
}

/** Event handler for the USB_Connect event. This indicates that the device is enumerating via the status LEDs. */
void EVENT_USB_Device_Connect(void)
{
	/* Indicate USB enumerating */
	LEDs_SetAllLEDs(LEDMASK_USB_ENUMERATING);
}

/** Event handler for the USB_Disconnect event. This indicates that the device is no longer connected to a host via
 *  the status LEDs.
 */
void EVENT_USB_Device_Disconnect(void)
{
	/* Indicate USB not ready */
	LEDs_SetAllLEDs(LEDMASK_USB_NOTREADY);
}

/** Event handler for the USB_ConfigurationChanged event. This is fired when the host set the current configuration
 *  of the USB device after enumeration - the device endpoints are configured.
 */
void EVENT_USB_Device_ConfigurationChanged(void)
{
	bool ConfigSuccess = true;

	/* Setup Vendor Data Endpoints */
/*	ConfigSuccess &= Endpoint_ConfigureEndpoint(VENDOR_IN_EPADDR,  EP_TYPE_BULK, VENDOR_IO_EPSIZE, 1);
	ConfigSuccess &= Endpoint_ConfigureEndpoint(VENDOR_OUT_EPADDR, EP_TYPE_BULK, VENDOR_IO_EPSIZE, 1);
*/
	/* Indicate endpoint configuration success or failure */
	LEDs_SetAllLEDs(ConfigSuccess ? LEDMASK_USB_READY : LEDMASK_USB_ERROR);
}

void process_LED_CMD_SET(void)
{
	/* marks the command as "accepted" by the
	application, so that LUFA does not process it: */
	Endpoint_ClearSETUP();
	/* mark the whole request as successful: */
	Endpoint_ClearStatusStage();
	/* process command parameters: */
	LEDs_ToggleLEDs(LEDS_LED1 | LEDS_LED2);
}


#define LED_CMD_SET 0

/** Event handler for the USB_ControlRequest event. This is used to catch and process control requests sent to
 *  the device from the USB host before passing along unhandled control requests to the library for processing
 *  internally.
 */
void EVENT_USB_Device_ControlRequest(void)
{
	if(USB_ControlRequest.bmRequestType & (REQTYPE_CLASS | REQREC_DEVICE))
	{
		
		if ((USB_ControlRequest.bmRequestType & CONTROL_REQTYPE_DIRECTION) == REQDIR_HOSTTODEVICE)
		{
			
			switch(USB_ControlRequest.bRequest)
			{
				case LED_CMD_SET:
					process_LED_CMD_SET();
					break;
				default: 
					break;
			}
		}
		else
		{
			switch(USB_ControlRequest.bRequest)
			{
				default:
					break;
			}
		}
	}
}
