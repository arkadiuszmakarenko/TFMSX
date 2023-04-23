#include "joystick.h"

HID_gamepad_Info_TypeDef* joymap;

void ProcessJoystick() {

			
			SetupJoystick();
			HID_gamepad_Info_TypeDef *joymap = (HID_gamepad_Info_TypeDef *)USBH_Get_Device_Data(HUB_GAMEPAD);


			if (joymap == NULL) return;
			if ((joymap->gamepad_data & 0x1)) LL_GPIO_SetOutputPin(GPIOC, LL_GPIO_PIN_10); else LL_GPIO_ResetOutputPin(GPIOC, LL_GPIO_PIN_10); //RIGHT - PC7
			if ((joymap->gamepad_data >> 1 & 0x1)) LL_GPIO_SetOutputPin(GPIOC, LL_GPIO_PIN_7); else LL_GPIO_ResetOutputPin(GPIOC, LL_GPIO_PIN_7); //LEFT - PC10
			if ((joymap->gamepad_data >> 2 & 0x1)) LL_GPIO_SetOutputPin(GPIOC, LL_GPIO_PIN_13); else LL_GPIO_ResetOutputPin(GPIOC, LL_GPIO_PIN_13); //BACK - PC11
			if ((joymap->gamepad_data >> 3 & 0x1)) LL_GPIO_SetOutputPin(GPIOC, LL_GPIO_PIN_11); else LL_GPIO_ResetOutputPin(GPIOC, LL_GPIO_PIN_11); //FORWARD - PC13
			if ((joymap->gamepad_data >> 4 & 0x1)) LL_GPIO_ResetOutputPin(GPIOC, LL_GPIO_PIN_15); else LL_GPIO_SetOutputPin(GPIOC, LL_GPIO_PIN_15); //TR1 - PC15
			if ((joymap->gamepad_data >> 5 & 0x1)) LL_GPIO_ResetOutputPin(GPIOC, LL_GPIO_PIN_14); else LL_GPIO_SetOutputPin(GPIOC, LL_GPIO_PIN_14); //TR2 - PC14





		//		HAL_GPIO_WritePin(MB_GPIO_Port, RB_Pin, !(joymap->gamepad_data >> 5 & 0x1));
		//		HAL_GPIO_WritePin(RB_GPIO_Port, MB_Pin, !(joymap->gamepad_data >> 6 & 0x1));
	
}

