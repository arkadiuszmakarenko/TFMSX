################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Middlewares/ST/STM32_USB_Host_Library/Class/HUBHID/Src/usbh_hub.c \
../Middlewares/ST/STM32_USB_Host_Library/Class/HUBHID/Src/usbh_hub_gamepad.c \
../Middlewares/ST/STM32_USB_Host_Library/Class/HUBHID/Src/usbh_hub_keybd.c \
../Middlewares/ST/STM32_USB_Host_Library/Class/HUBHID/Src/usbh_hub_mouse.c \
../Middlewares/ST/STM32_USB_Host_Library/Class/HUBHID/Src/usbh_hubctrl.c \
../Middlewares/ST/STM32_USB_Host_Library/Class/HUBHID/Src/usbh_hubenum.c 

OBJS += \
./Middlewares/ST/STM32_USB_Host_Library/Class/HUBHID/Src/usbh_hub.o \
./Middlewares/ST/STM32_USB_Host_Library/Class/HUBHID/Src/usbh_hub_gamepad.o \
./Middlewares/ST/STM32_USB_Host_Library/Class/HUBHID/Src/usbh_hub_keybd.o \
./Middlewares/ST/STM32_USB_Host_Library/Class/HUBHID/Src/usbh_hub_mouse.o \
./Middlewares/ST/STM32_USB_Host_Library/Class/HUBHID/Src/usbh_hubctrl.o \
./Middlewares/ST/STM32_USB_Host_Library/Class/HUBHID/Src/usbh_hubenum.o 

C_DEPS += \
./Middlewares/ST/STM32_USB_Host_Library/Class/HUBHID/Src/usbh_hub.d \
./Middlewares/ST/STM32_USB_Host_Library/Class/HUBHID/Src/usbh_hub_gamepad.d \
./Middlewares/ST/STM32_USB_Host_Library/Class/HUBHID/Src/usbh_hub_keybd.d \
./Middlewares/ST/STM32_USB_Host_Library/Class/HUBHID/Src/usbh_hub_mouse.d \
./Middlewares/ST/STM32_USB_Host_Library/Class/HUBHID/Src/usbh_hubctrl.d \
./Middlewares/ST/STM32_USB_Host_Library/Class/HUBHID/Src/usbh_hubenum.d 


# Each subdirectory must supply rules for building sources it contributes
Middlewares/ST/STM32_USB_Host_Library/Class/HUBHID/Src/%.o Middlewares/ST/STM32_USB_Host_Library/Class/HUBHID/Src/%.su Middlewares/ST/STM32_USB_Host_Library/Class/HUBHID/Src/%.cyclo: ../Middlewares/ST/STM32_USB_Host_Library/Class/HUBHID/Src/%.c Middlewares/ST/STM32_USB_Host_Library/Class/HUBHID/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F730xx -c -I../Core/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../Drivers/CMSIS/Include -I../USB_HOST/App -I../USB_HOST/Target -I../Middlewares/ST/STM32_USB_Host_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Host_Library/Class/HID/Inc -I../Middlewares/ST/STM32_USB_Host_Library/Class/HUBHID/Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Middlewares-2f-ST-2f-STM32_USB_Host_Library-2f-Class-2f-HUBHID-2f-Src

clean-Middlewares-2f-ST-2f-STM32_USB_Host_Library-2f-Class-2f-HUBHID-2f-Src:
	-$(RM) ./Middlewares/ST/STM32_USB_Host_Library/Class/HUBHID/Src/usbh_hub.cyclo ./Middlewares/ST/STM32_USB_Host_Library/Class/HUBHID/Src/usbh_hub.d ./Middlewares/ST/STM32_USB_Host_Library/Class/HUBHID/Src/usbh_hub.o ./Middlewares/ST/STM32_USB_Host_Library/Class/HUBHID/Src/usbh_hub.su ./Middlewares/ST/STM32_USB_Host_Library/Class/HUBHID/Src/usbh_hub_gamepad.cyclo ./Middlewares/ST/STM32_USB_Host_Library/Class/HUBHID/Src/usbh_hub_gamepad.d ./Middlewares/ST/STM32_USB_Host_Library/Class/HUBHID/Src/usbh_hub_gamepad.o ./Middlewares/ST/STM32_USB_Host_Library/Class/HUBHID/Src/usbh_hub_gamepad.su ./Middlewares/ST/STM32_USB_Host_Library/Class/HUBHID/Src/usbh_hub_keybd.cyclo ./Middlewares/ST/STM32_USB_Host_Library/Class/HUBHID/Src/usbh_hub_keybd.d ./Middlewares/ST/STM32_USB_Host_Library/Class/HUBHID/Src/usbh_hub_keybd.o ./Middlewares/ST/STM32_USB_Host_Library/Class/HUBHID/Src/usbh_hub_keybd.su ./Middlewares/ST/STM32_USB_Host_Library/Class/HUBHID/Src/usbh_hub_mouse.cyclo ./Middlewares/ST/STM32_USB_Host_Library/Class/HUBHID/Src/usbh_hub_mouse.d ./Middlewares/ST/STM32_USB_Host_Library/Class/HUBHID/Src/usbh_hub_mouse.o ./Middlewares/ST/STM32_USB_Host_Library/Class/HUBHID/Src/usbh_hub_mouse.su ./Middlewares/ST/STM32_USB_Host_Library/Class/HUBHID/Src/usbh_hubctrl.cyclo ./Middlewares/ST/STM32_USB_Host_Library/Class/HUBHID/Src/usbh_hubctrl.d ./Middlewares/ST/STM32_USB_Host_Library/Class/HUBHID/Src/usbh_hubctrl.o ./Middlewares/ST/STM32_USB_Host_Library/Class/HUBHID/Src/usbh_hubctrl.su ./Middlewares/ST/STM32_USB_Host_Library/Class/HUBHID/Src/usbh_hubenum.cyclo ./Middlewares/ST/STM32_USB_Host_Library/Class/HUBHID/Src/usbh_hubenum.d ./Middlewares/ST/STM32_USB_Host_Library/Class/HUBHID/Src/usbh_hubenum.o ./Middlewares/ST/STM32_USB_Host_Library/Class/HUBHID/Src/usbh_hubenum.su

.PHONY: clean-Middlewares-2f-ST-2f-STM32_USB_Host_Library-2f-Class-2f-HUBHID-2f-Src

