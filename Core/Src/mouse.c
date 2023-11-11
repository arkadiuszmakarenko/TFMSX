#include "joystick.h"

HID_MOUSE_Info_TypeDef* mouse_data;

void ProcessMouse() {


			SetupJoystick();
			HID_MOUSE_Info_TypeDef *mouse_data = (HID_MOUSE_Info_TypeDef *)USBH_Get_Device_Data_Host(&hUsbHostHS,HUB_MOUSE);



}

