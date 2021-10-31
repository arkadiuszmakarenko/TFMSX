#include "msx.h"


void InitMSXKeyboard()
{

	//Reset matrix state etc
	memset(&MSX_Matrix_data, 0, sizeof(MSX_Matrix_data));

}

void ProcessMSXKey(uint8_t usbkey)
{
	for (uint8_t idx=0; idx < MSX_KEYS_SIZE; idx++)
	{
		if (msxkeymap[idx][0]==usbkey)
		{
			MSX_Matrix_temp[msxkeymap[idx][1]] |= msxkeymap[idx][2];
		}
	}

}

void ProcessMSXKeyboard(){

	//Keyboard is not ready
	if(Appli_state!=APPLICATION_READY)
	{
		//turn off LED
		LL_GPIO_SetOutputPin(LED_GPIO_Port, LED_Pin);
		return;
	}
	//turn on LED to let know that USB is ready (still might turn on when mouse is inserted)
	LL_GPIO_ResetOutputPin(LED_GPIO_Port, LED_Pin);

	//Check if there is keyboard data waiting
	kb_data = USBH_HID_GetKeybdInfo(&hUsbHostFS);

	//keyboard hasn't return any data, so there was no change in state.
	if (kb_data==NULL) return;


	//reset temp array to zero
	memset(&MSX_Matrix_temp, 0, sizeof(MSX_Matrix_temp));

	//process special keys
	if (kb_data->lctrl || kb_data->rctrl)
	{
		//{KEY_LEFTCONTROL,								KB_ROW_6,		B_BIT_1},
		MSX_Matrix_temp[KB_ROW_6] |=KB_BIT_1;
	}


	if (kb_data->lshift|| kb_data->rshift)
	{
		//		{KEY_LEFTSHIFT,							KB_ROW_6,		KB_BIT_0},
		MSX_Matrix_temp[KB_ROW_6] |=KB_BIT_0;
	}

	if (kb_data->lgui)
	{
			//	{KEY_LEFT_GUI,							KB_ROW_6,		KB_BIT_4},
		MSX_Matrix_temp[KB_ROW_6] |=KB_BIT_4;
	}

	if (kb_data->rgui)
	{
		MSX_Matrix_temp[KB_ROW_6] |=KB_BIT_2;
			//{KEY_RIGHT_GUI,							KB_ROW_6,		KB_BIT_2},
	}

	//Interate over all keys - max 6 pressed keys at once
	for (int i = 0; i < 6; i++)
	{
		if(kb_data->keys[i]!=0x00) ProcessMSXKey(kb_data->keys[i]);
	}

	memcpy(MSX_Matrix_data,MSX_Matrix_temp,sizeof(MSX_Matrix_data));
}

void ProcessIRQ()
{
	uint8_t row = READ_MSX_ROW_VALUE(LL_GPIO_ReadInputPort(GPIOB));
	LL_GPIO_WriteOutputPort(GPIOA, MSX_Matrix_data[row]);
}

//System IRQ handler. It reset flag and executes ProcessIRQ
void EXTI0_IRQHandler(void)
{
  if (LL_EXTI_IsActiveFlag_0_31(LL_EXTI_LINE_0) != RESET)
  {

    ProcessIRQ();
    LL_EXTI_ClearFlag_0_31(LL_EXTI_LINE_0);
  }

}
