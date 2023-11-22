#include "utils.h"
#include "usbh_hub.h"

uint8_t *USBH_Get_Device_Data(HUB_DEVICETypeDef deviceType)
{
	USBH_HandleTypeDef *phost = &hUsbHostFS;
	USBH_HandleTypeDef *phostHS = &hUsbHostHS;

	uint8_t *pnt = NULL;

	if(phost->gState == HOST_CLASS)
	{
		pnt = USBH_Get_Device_Data_Host(phost,deviceType,Appli_stateFS);
		if (pnt!=NULL) return pnt;
	}

	if(phostHS->gState == HOST_CLASS)
	{
		pnt = USBH_Get_Device_Data_Host(phostHS,deviceType,Appli_state);
		if (pnt!=NULL) return pnt;
	}

	return pnt;

}


uint8_t *USBH_Get_Device_Data_Host(USBH_HandleTypeDef *phost,HUB_DEVICETypeDef deviceType, ApplicationTypeDef Application_state)
{

  //handle device when connected to Hub
  if (phost->device.DevDesc.bDeviceClass == 9 && Application_state == APPLICATION_READY)
  {
    HUB_HandleTypeDef *HUB_Handle  = (HUB_HandleTypeDef *) phost->pActiveClass->pData[0];

    for (int port = 0; port <4; port++)
    {
      for (int interface = 0; interface <2; interface ++)
      {
        if (HUB_Handle->Port[port].Interface[interface].DeviceType == deviceType)
        {
            if (deviceType == HUB_KEYBOARD) return (uint8_t *)USBH_HUB_GetKeybdInfo(&HUB_Handle->Port[port].Interface[interface]);
            if (deviceType == HUB_MOUSE)    return (uint8_t *)USBH_HUB_GetMouseInfo(&HUB_Handle->Port[port].Interface[interface]);
            if (deviceType == HUB_GAMEPAD)  return (uint8_t *)USBH_HUB_GetGamepadInfo(&HUB_Handle->Port[port].Interface[interface]);
        }
      }


    }

  }
  else if (Application_state == APPLICATION_READY)
  {
      for (int interface = 0; interface <2; interface ++)
      {
        HID_HandleTypeDef *HID_Handle  = (HID_HandleTypeDef *) phost->pActiveClass->pData[interface];
        if (HID_Handle->HID_Desc.RptDesc.type == REPORT_TYPE_KEYBOARD)
        {
          if (deviceType == HUB_KEYBOARD)
          {
            return (uint8_t *)USBH_HID_GetKeybdInfo(phost);
          }

        }

        if (HID_Handle->HID_Desc.RptDesc.type == REPORT_TYPE_MOUSE)
        {
          if (deviceType == HUB_MOUSE)
          {
            return (uint8_t *)USBH_HID_GetMouseInfo(phost);
          }

        }

        if (HID_Handle->HID_Desc.RptDesc.type == REPORT_TYPE_JOYSTICK)
        {

          if (deviceType == HUB_GAMEPAD)
          {
            return (uint8_t *)USBH_HID_GetGamepadInfo(phost);
          }
        }



      }

  }

return NULL;
}



void SetupJoystick()
{

	uint8_t JoystickFound = 0;
	USBH_HandleTypeDef *phost = &hUsbHostFS;
	USBH_HandleTypeDef *phostHS = &hUsbHostHS;

	if(phost->gState == HOST_CLASS)
	{
		JoystickFound = SetupJoystick_Host(phost,Appli_stateFS);
	}

	if(phostHS->gState == HOST_CLASS)
	{
		JoystickFound = SetupJoystick_Host(phostHS,Appli_state);
	}

	if (JoystickFound == 1)
	{
		SetPinsOn();
	}
	else
	{
		SetPinsOff();
	}

}



uint8_t SetupJoystick_Host(USBH_HandleTypeDef *phost,ApplicationTypeDef Application_state)
{
  uint8_t JoystickFound = 0;
  //handle device when connected to Hub
  if (phost->device.DevDesc.bDeviceClass == 9 && Application_state == APPLICATION_READY)
  {
    HUB_HandleTypeDef *HUB_Handle  = (HUB_HandleTypeDef *) phost->pActiveClass->pData[0]; 

    for (int port = 0; port <4; port++)
    {
      for (int interface = 0; interface <2; interface ++)
      {
        if (HUB_Handle->Port[port].Interface[interface].DeviceType == HUB_GAMEPAD)
        {
        	JoystickFound = 1;
            return JoystickFound;
        }
      }


    }
    
  }
  else if (Application_state == APPLICATION_READY)
  {
      for (int interface = 0; interface <2; interface ++)
      {
        HID_HandleTypeDef *HID_Handle  = (HID_HandleTypeDef *) phost->pActiveClass->pData[interface]; 


        if (HID_Handle->HID_Desc.RptDesc.type == REPORT_TYPE_JOYSTICK)
        {

            //TURN ON PINS and return
        	JoystickFound = 1;
            return JoystickFound;
        }
      }

  }

  //If we are here, no joystick detected change pins back to Input
  return JoystickFound;


}


void SetPinsOn()
{
  LL_GPIO_InitTypeDef GPIO_InitStruct = {0};
    /**/

  LL_GPIO_SetOutputPin(GPIOC, LL_GPIO_PIN_6);

  GPIO_InitStruct.Pin = LL_GPIO_PIN_7;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  LL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  GPIO_InitStruct.Pin = LL_GPIO_PIN_6;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  LL_GPIO_Init(GPIOC, &GPIO_InitStruct);


    /**/
  GPIO_InitStruct.Pin = LL_GPIO_PIN_10;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  LL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  GPIO_InitStruct.Pin = LL_GPIO_PIN_11;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  LL_GPIO_Init(GPIOC, &GPIO_InitStruct);
  /**/
  GPIO_InitStruct.Pin = LL_GPIO_PIN_13;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  LL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /**/
  GPIO_InitStruct.Pin = LL_GPIO_PIN_14;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  LL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /**/
  GPIO_InitStruct.Pin = LL_GPIO_PIN_15;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  LL_GPIO_Init(GPIOC, &GPIO_InitStruct);


}


void SetPinsOff()
{
	  LL_GPIO_SetOutputPin(GPIOC, LL_GPIO_PIN_7);
	  LL_GPIO_SetOutputPin(GPIOC, LL_GPIO_PIN_10);
	  LL_GPIO_SetOutputPin(GPIOC, LL_GPIO_PIN_11);
	  LL_GPIO_SetOutputPin(GPIOC, LL_GPIO_PIN_13);
	  LL_GPIO_SetOutputPin(GPIOC, LL_GPIO_PIN_14);
	  LL_GPIO_SetOutputPin(GPIOC, LL_GPIO_PIN_15);

 //GPIOC->MODER = 0x0;

  LL_GPIO_InitTypeDef GPIO_InitStruct = {0};
    /**/
  GPIO_InitStruct.Pin = LL_GPIO_PIN_7;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  LL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  GPIO_InitStruct.Pin = LL_GPIO_PIN_6;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  LL_GPIO_Init(GPIOC, &GPIO_InitStruct);

    /**/
  GPIO_InitStruct.Pin = LL_GPIO_PIN_10;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  LL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  GPIO_InitStruct.Pin = LL_GPIO_PIN_11;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  LL_GPIO_Init(GPIOC, &GPIO_InitStruct);
  /**/
  GPIO_InitStruct.Pin = LL_GPIO_PIN_13;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  LL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /**/
  GPIO_InitStruct.Pin = LL_GPIO_PIN_14;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  LL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /**/
  GPIO_InitStruct.Pin = LL_GPIO_PIN_15;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  LL_GPIO_Init(GPIOC, &GPIO_InitStruct);
}

void SetLEDs()
{
	USBH_HandleTypeDef *phost = &hUsbHostFS;
	USBH_HandleTypeDef *phostHS = &hUsbHostHS;

	if(phost->gState == HOST_CLASS || phostHS->gState == HOST_CLASS)
	{
		if (Appli_stateFS == APPLICATION_READY || Appli_state == APPLICATION_READY)
		{
			LL_GPIO_ResetOutputPin(GPIOB, LL_GPIO_PIN_13);
			return;
		}

	}

	 LL_GPIO_SetOutputPin(GPIOB, LL_GPIO_PIN_13);
}

