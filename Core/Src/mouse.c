#include "mouse.h"

HID_MOUSE_Info_TypeDef* mouse_data;

uint8_t mouse_read_index = 0;


void ProcessMouse() {


			//SetupJoystick();
			HID_MOUSE_Info_TypeDef *mouse_data = (HID_MOUSE_Info_TypeDef *)USBH_Get_Device_Data(HUB_MOUSE);

			if (mouse_data == NULL) return;
			uint8_t a = 1;
			a++;





}

void MouseIRQ(void)
{
	switch(mouse_read_index) {
	  case 0:
	    // code block
		mouse_read_index++;
	    break;
	  case 1:


		mouse_data->x = 0;
		mouse_read_index++;
	    break;
	  case 2:

		mouse_read_index++;
	    break;
	  case 3:

		  mouse_data->y = 0;
		mouse_read_index = 0;
		break;
	  default:
		mouse_read_index = 0;

	}

}







void EXTI9_5_IRQHandler(void)
{

  if (LL_EXTI_IsActiveFlag_0_31(LL_EXTI_LINE_6) != RESET)
  {
	MouseIRQ();
    LL_EXTI_ClearFlag_0_31(LL_EXTI_LINE_6);

  }

}
