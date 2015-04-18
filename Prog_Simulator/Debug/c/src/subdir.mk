################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../c/src/Communication.c \
../c/src/RobolabSimClient.c \
../c/src/RobotProxy.c \
../c/src/Urlcode.c 

OBJS += \
./c/src/Communication.o \
./c/src/RobolabSimClient.o \
./c/src/RobotProxy.o \
./c/src/Urlcode.o 

C_DEPS += \
./c/src/Communication.d \
./c/src/RobolabSimClient.d \
./c/src/RobotProxy.d \
./c/src/Urlcode.d 


# Each subdirectory must supply rules for building sources it contributes
c/src/%.o: ../c/src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -I/usr/include/python2.7 -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


