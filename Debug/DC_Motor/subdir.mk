################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../DC_Motor/DC_Motor_config.c \
../DC_Motor/DC_Motor_program.c 

OBJS += \
./DC_Motor/DC_Motor_config.o \
./DC_Motor/DC_Motor_program.o 

C_DEPS += \
./DC_Motor/DC_Motor_config.d \
./DC_Motor/DC_Motor_program.d 


# Each subdirectory must supply rules for building sources it contributes
DC_Motor/%.o: ../DC_Motor/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


