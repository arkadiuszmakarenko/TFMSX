#ifndef __UTILS_H
#define __UTILS_H

#include "main.h"
#include "usb_host.h"
#include "usbh_hid.h"
#include "usbh_hub_keybd.h"
#include "usbh_hub_mouse.h"
#include "usbh_hub_gamepad.h"



extern TIM_HandleTypeDef htim11;

typedef struct
{
  uint8_t  *buf;
  uint16_t  head;
  uint16_t tail;
  uint16_t size;
  uint8_t  lock;
} FIFO_Utils_TypeDef;

uint8_t *USBH_Get_Device_Data(HUB_DEVICETypeDef DeviceType);

void SetJoystickPins(USBH_HandleTypeDef pHost);

void SetPinsOn();
void SetPinsOff();

extern USBH_HandleTypeDef hUsbHostFS;
extern ApplicationTypeDef Appli_state;

#endif