################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Middlewares/ST/STM32_USB_Host_Library/Class/HID/Src/usbh_hid.c \
../Middlewares/ST/STM32_USB_Host_Library/Class/HID/Src/usbh_hid_gamepad.c \
../Middlewares/ST/STM32_USB_Host_Library/Class/HID/Src/usbh_hid_keybd.c \
../Middlewares/ST/STM32_USB_Host_Library/Class/HID/Src/usbh_hid_mouse.c \
../Middlewares/ST/STM32_USB_Host_Library/Class/HID/Src/usbh_hid_parser.c \
../Middlewares/ST/STM32_USB_Host_Library/Class/HID/Src/usbh_hid_reportparser.c 

OBJS += \
./Middlewares/ST/STM32_USB_Host_Library/Class/HID/Src/usbh_hid.o \
./Middlewares/ST/STM32_USB_Host_Library/Class/HID/Src/usbh_hid_gamepad.o \
./Middlewares/ST/STM32_USB_Host_Library/Class/HID/Src/usbh_hid_keybd.o \
./Middlewares/ST/STM32_USB_Host_Library/Class/HID/Src/usbh_hid_mouse.o \
./Middlewares/ST/STM32_USB_Host_Library/Class/HID/Src/usbh_hid_parser.o \
./Middlewares/ST/STM32_USB_Host_Library/Class/HID/Src/usbh_hid_reportparser.o 

C_DEPS += \
./Middlewares/ST/STM32_USB_Host_Library/Class/HID/Src/usbh_hid.d \
./Middlewares/ST/STM32_USB_Host_Library/Class/HID/Src/usbh_hid_gamepad.d \
./Middlewares/ST/STM32_USB_Host_Library/Class/HID/Src/usbh_hid_keybd.d \
./Middlewares/ST/STM32_USB_Host_Library/Class/HID/Src/usbh_hid_mouse.d \
./Middlewares/ST/STM32_USB_Host_Library/Class/HID/Src/usbh_hid_parser.d \
./Middlewares/ST/STM32_USB_Host_Library/Class/HID/Src/usbh_hid_reportparser.d 


# Each subdirectory must supply rules for building sources it contributes
Middlewares/ST/STM32_USB_Host_Library/Class/HID/Src/%.o Middlewares/ST/STM32_USB_Host_Library/Class/HID/Src/%.su Middlewares/ST/STM32_USB_Host_Library/Class/HID/Src/%.cyclo: ../Middlewares/ST/STM32_USB_Host_Library/Class/HID/Src/%.c Middlewares/ST/STM32_USB_Host_Library/Class/HID/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F730xx -DUSE_FULL_LL_DRIVER -c -I../Core/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../Drivers/CMSIS/Include -I../USB_HOST/App -I../USB_HOST/Target -I../Middlewares/ST/STM32_USB_Host_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Host_Library/Class/HID/Inc -I../Middlewares/ST/STM32_USB_Host_Library/Class/HUBHID/Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Middlewares-2f-ST-2f-STM32_USB_Host_Library-2f-Class-2f-HID-2f-Src

clean-Middlewares-2f-ST-2f-STM32_USB_Host_Library-2f-Class-2f-HID-2f-Src:
	-$(RM) ./Middlewares/ST/STM32_USB_Host_Library/Class/HID/Src/usbh_hid.cyclo ./Middlewares/ST/STM32_USB_Host_Library/Class/HID/Src/usbh_hid.d ./Middlewares/ST/STM32_USB_Host_Library/Class/HID/Src/usbh_hid.o ./Middlewares/ST/STM32_USB_Host_Library/Class/HID/Src/usbh_hid.su ./Middlewares/ST/STM32_USB_Host_Library/Class/HID/Src/usbh_hid_gamepad.cyclo ./Middlewares/ST/STM32_USB_Host_Library/Class/HID/Src/usbh_hid_gamepad.d ./Middlewares/ST/STM32_USB_Host_Library/Class/HID/Src/usbh_hid_gamepad.o ./Middlewares/ST/STM32_USB_Host_Library/Class/HID/Src/usbh_hid_gamepad.su ./Middlewares/ST/STM32_USB_Host_Library/Class/HID/Src/usbh_hid_keybd.cyclo ./Middlewares/ST/STM32_USB_Host_Library/Class/HID/Src/usbh_hid_keybd.d ./Middlewares/ST/STM32_USB_Host_Library/Class/HID/Src/usbh_hid_keybd.o ./Middlewares/ST/STM32_USB_Host_Library/Class/HID/Src/usbh_hid_keybd.su ./Middlewares/ST/STM32_USB_Host_Library/Class/HID/Src/usbh_hid_mouse.cyclo ./Middlewares/ST/STM32_USB_Host_Library/Class/HID/Src/usbh_hid_mouse.d ./Middlewares/ST/STM32_USB_Host_Library/Class/HID/Src/usbh_hid_mouse.o ./Middlewares/ST/STM32_USB_Host_Library/Class/HID/Src/usbh_hid_mouse.su ./Middlewares/ST/STM32_USB_Host_Library/Class/HID/Src/usbh_hid_parser.cyclo ./Middlewares/ST/STM32_USB_Host_Library/Class/HID/Src/usbh_hid_parser.d ./Middlewares/ST/STM32_USB_Host_Library/Class/HID/Src/usbh_hid_parser.o ./Middlewares/ST/STM32_USB_Host_Library/Class/HID/Src/usbh_hid_parser.su ./Middlewares/ST/STM32_USB_Host_Library/Class/HID/Src/usbh_hid_reportparser.cyclo ./Middlewares/ST/STM32_USB_Host_Library/Class/HID/Src/usbh_hid_reportparser.d ./Middlewares/ST/STM32_USB_Host_Library/Class/HID/Src/usbh_hid_reportparser.o ./Middlewares/ST/STM32_USB_Host_Library/Class/HID/Src/usbh_hid_reportparser.su

.PHONY: clean-Middlewares-2f-ST-2f-STM32_USB_Host_Library-2f-Class-2f-HID-2f-Src
