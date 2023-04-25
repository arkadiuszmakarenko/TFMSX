#include "utils.h"
#include "usbh_hub.h"

uint8_t *USBH_Get_Device_Data(HUB_DEVICETypeDef deviceType)
{
	USBH_HandleTypeDef *phost = &hUsbHostFS;
	USBH_HandleTypeDef *phostHS = &hUsbHostHS;

	if(phost->gState == HOST_CLASS)
	{
		return USBH_Get_Device_Data_Host(phost,deviceType);
	}

	if(phostHS->gState == HOST_CLASS)
	{
		return USBH_Get_Device_Data_Host(phostHS,deviceType);
	}

	return NULL;


}

uint8_t *USBH_Get_Device_Data_Host(USBH_HandleTypeDef *phost,HUB_DEVICETypeDef deviceType)
{

  //handle device when connected to Hub
  if (phost->device.DevDesc.bDeviceClass == 9 && Appli_state == APPLICATION_READY)
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
  else if (Appli_state == APPLICATION_READY)
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
	USBH_HandleTypeDef *phost = &hUsbHostFS;
		USBH_HandleTypeDef *phostHS = &hUsbHostHS;

		if(phost->gState == HOST_CLASS)
		{
			SetupJoystick_Host(phost);
		}

		if(phostHS->gState == HOST_CLASS)
		{
			SetupJoystick_Host(phostHS);
		}

}



void SetupJoystick_Host(USBH_HandleTypeDef *phost)
{
  
  //handle device when connected to Hub
  if (phost->device.DevDesc.bDeviceClass == 9 && Appli_state == APPLICATION_READY)
  {
    HUB_HandleTypeDef *HUB_Handle  = (HUB_HandleTypeDef *) phost->pActiveClass->pData[0]; 

    for (int port = 0; port <4; port++)
    {
      for (int interface = 0; interface <2; interface ++)
      {
        if (HUB_Handle->Port[port].Interface[interface].DeviceType == HUB_GAMEPAD)
        {
            //TURN ON PINS and return;
            SetPinsOn();
            return;
        }
      }


    }
    
  }
  else if (Appli_state == APPLICATION_READY)
  {
      for (int interface = 0; interface <2; interface ++)
      {
        HID_HandleTypeDef *HID_Handle  = (HID_HandleTypeDef *) phost->pActiveClass->pData[interface]; 


        if (HID_Handle->HID_Desc.RptDesc.type == REPORT_TYPE_JOYSTICK)
        {

            //TURN ON PINS and return
            SetPinsOn();
            return;
        }
        


      }

  }

  //If we are here, no joystick detected change pins back to Input
  SetPinsOff();


}


void SetPinsOn()
{
  LL_GPIO_InitTypeDef GPIO_InitStruct = {0};
    /**/
  GPIO_InitStruct.Pin = LL_GPIO_PIN_7;
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
  LL_GPIO_InitTypeDef GPIO_InitStruct = {0};
    /**/
  GPIO_InitStruct.Pin = LL_GPIO_PIN_7;
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

