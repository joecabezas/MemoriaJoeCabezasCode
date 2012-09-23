################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/filehandlers/OffFile.cpp 

OBJS += \
./src/filehandlers/OffFile.o 

CPP_DEPS += \
./src/filehandlers/OffFile.d 


# Each subdirectory must supply rules for building sources it contributes
src/filehandlers/%.o: ../src/filehandlers/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O2 -g -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


