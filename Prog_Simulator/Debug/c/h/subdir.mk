################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../c/h/card.c \
../c/h/list.c \
../c/h/search.c 

OBJS += \
./c/h/card.o \
./c/h/list.o \
./c/h/search.o 

C_DEPS += \
./c/h/card.d \
./c/h/list.d \
./c/h/search.d 


# Each subdirectory must supply rules for building sources it contributes
c/h/%.o: ../c/h/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -I/usr/include/python2.7 -I/home/mk/Dokumente/robo_prak/robolab15_g28/simulation/robo_sim/c/h -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


