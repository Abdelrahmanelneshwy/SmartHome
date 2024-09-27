################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../freerRTOS/heap_2.c \
../freerRTOS/list.c \
../freerRTOS/port.c \
../freerRTOS/queue.c \
../freerRTOS/tasks.c 

O_SRCS += \
../freerRTOS/heap_2.o \
../freerRTOS/list.o \
../freerRTOS/port.o \
../freerRTOS/queue.o \
../freerRTOS/tasks.o 

OBJS += \
./freerRTOS/heap_2.o \
./freerRTOS/list.o \
./freerRTOS/port.o \
./freerRTOS/queue.o \
./freerRTOS/tasks.o 

C_DEPS += \
./freerRTOS/heap_2.d \
./freerRTOS/list.d \
./freerRTOS/port.d \
./freerRTOS/queue.d \
./freerRTOS/tasks.d 


# Each subdirectory must supply rules for building sources it contributes
freerRTOS/%.o: ../freerRTOS/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


