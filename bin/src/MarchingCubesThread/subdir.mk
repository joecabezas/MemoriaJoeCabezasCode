################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/MarchingCubesThread/MarchingCubesThread.cpp 

OBJS += \
./src/MarchingCubesThread/MarchingCubesThread.o 

CPP_DEPS += \
./src/MarchingCubesThread/MarchingCubesThread.d 


# Each subdirectory must supply rules for building sources it contributes
src/MarchingCubesThread/%.o: ../src/MarchingCubesThread/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O2 -g -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


