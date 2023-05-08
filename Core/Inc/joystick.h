#ifndef __JOYSTICK_H
#define __JOYSTICK_H

#include "stdint.h"
#include "usb_host.h"
#include "usbh_hid.h"
#include "usbh_hid_mouse.h"
#include "utils.h"

extern USBH_HandleTypeDef hUsbHostFS;
extern USBH_HandleTypeDef hUsbHostHS;

void ProcessJoystick();

#endif
