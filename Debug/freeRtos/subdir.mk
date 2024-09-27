################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../freeRtos/heap_2.c \
../freeRtos/list.c \
../freeRtos/port.c \
../freeRtos/queue.c \
../freeRtos/tasks.c 

O_SRCS += \
../freeRtos/heap_2.o \
../freeRtos/list.o \
../freeRtos/port.o \
../freeRtos/queue.o \
../freeRtos/tasks.o 

OBJS += \
./freeRtos/heap_2.o \
./freeRtos/list.o \
./freeRtos/port.o \
./freeRtos/queue.o \
./freeRtos/tasks.o 

C_DEPS += \
./freeRtos/heap_2.d \
./freeRtos/list.d \
./freeRtos/port.d \
./freeRtos/queue.d \
./freeRtos/tasks.d 


# Each subdirectory must supply rules for building sources it contributes
freeRtos/%.o: ../freeRtos/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


