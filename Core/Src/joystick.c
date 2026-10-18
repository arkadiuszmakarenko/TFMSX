#include "joystick.h"
#include <stdio.h>

HID_gamepad_Info_TypeDef* joymap;
static HID_gamepad_Info_TypeDef last_joystick_report;
static uint8_t have_joystick_report;

void ProcessJoystick() {
			
			SetupJoystick();
			HID_gamepad_Info_TypeDef *joymap = (HID_gamepad_Info_TypeDef *)USBH_Get_Device_Data(HUB_GAMEPAD);

			if (joymap == NULL) return;
			if ((have_joystick_report == 0U) ||
				(memcmp(joymap, &last_joystick_report, sizeof(last_joystick_report)) != 0))
			{
				TFMSX_DEBUG_PRINTF("HID gamepad report: data=%02X extra=%02X\r\n",
				       joymap->gamepad_data, joymap->gamepad_extraBtn);
				memcpy(&last_joystick_report, joymap, sizeof(last_joystick_report));
				have_joystick_report = 1U;
			}
			if ((joymap->gamepad_data & 0x1)) LL_GPIO_ResetOutputPin(GPIOC, LL_GPIO_PIN_7); else LL_GPIO_SetOutputPin(GPIOC, LL_GPIO_PIN_7); //RIGHT - PC7
			if ((joymap->gamepad_data >> 1 & 0x1)) LL_GPIO_ResetOutputPin(GPIOC, LL_GPIO_PIN_10); else LL_GPIO_SetOutputPin(GPIOC, LL_GPIO_PIN_10); //LEFT - PC10
			if ((joymap->gamepad_data >> 2 & 0x1)) LL_GPIO_ResetOutputPin(GPIOC, LL_GPIO_PIN_11); else LL_GPIO_SetOutputPin(GPIOC, LL_GPIO_PIN_11); //BACK - PC11
			if ((joymap->gamepad_data >> 3 & 0x1)) LL_GPIO_ResetOutputPin(GPIOC, LL_GPIO_PIN_13); else LL_GPIO_SetOutputPin(GPIOC, LL_GPIO_PIN_13); //FORWARD - PC13
			if ((joymap->gamepad_data >> 4 & 0x1)) LL_GPIO_ResetOutputPin(GPIOC, LL_GPIO_PIN_15); else LL_GPIO_SetOutputPin(GPIOC, LL_GPIO_PIN_15); //TR1 - PC15
			if ((joymap->gamepad_data >> 5 & 0x1)) LL_GPIO_ResetOutputPin(GPIOC, LL_GPIO_PIN_14); else LL_GPIO_SetOutputPin(GPIOC, LL_GPIO_PIN_14); //TR2 - PC14
}
