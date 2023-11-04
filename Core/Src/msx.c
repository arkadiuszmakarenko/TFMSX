#include "msx.h"
#include "usbh_hub_keybd.h"
#include "utils.h"

uint32_t MSX_Matrix_data[12];
uint32_t MSX_Matrix_temp[12];

HID_KEYBD_Info_TypeDef *kb_data;

void InitMSXKeyboard()
{

	//Reset matrix state etc
	memset(&MSX_Matrix_data, 0, sizeof(MSX_Matrix_data));
	memset(&MSX_Matrix_temp, 0, sizeof(MSX_Matrix_data));
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

	HID_KEYBD_Info_TypeDef *kb_data = (HID_KEYBD_Info_TypeDef *)USBH_Get_Device_Data_Host(&hUsbHostFS, HUB_KEYBOARD);


	//keyboard hasn't return any data, so there was no change in state.
	if (kb_data==NULL) return;


	//reset temp array to zero
	memset(&MSX_Matrix_temp, 0, sizeof(MSX_Matrix_temp));

	//process special keys
	if (kb_data->lctrl)
	{
		//{KEY_LEFTCONTROL,								KB_ROW_6,		B_BIT_1},
		MSX_Matrix_temp[KB_ROW_6] |=KB_BIT_1;
	}

	if (kb_data->rctrl)
	{
		//{KEY_LEFTCONTROL,								KB_ROW_6,		B_BIT_1},
		MSX_Matrix_temp[KB_ROW_2] |=KB_BIT_5;
	}

	if (kb_data->lshift|| kb_data->rshift)
	{
		//{KEY_LEFTSHIFT,							KB_ROW_6,		KB_BIT_0},
		//{KEY_RIGHTSHIFT,					KB_ROW_6,		KB_BIT_0},
		MSX_Matrix_temp[KB_ROW_6] |=KB_BIT_0;
	}

	//{KEY_LEFTALT,						KB_ROW_6,		KB_BIT_4},
	//
	if (kb_data->ralt)
	{
		MSX_Matrix_temp[KB_ROW_6] |=KB_BIT_4;
	}

	if (kb_data->lalt)
	{
		MSX_Matrix_temp[KB_ROW_6] |=KB_BIT_2;
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
	uint8_t row = LL_GPIO_ReadInputPort(GPIOA)&0xF;
	uint16_t value = ~MSX_Matrix_data[row] & 0x00FF;
	uint16_t PortValue = LL_GPIO_ReadOutputPort(GPIOB)& 0xFF00;
	value = value | PortValue;
	LL_GPIO_WriteOutputPort(GPIOB, value);
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
