################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/mc/MarchingCubes.cpp \
../src/mc/mpVector.cpp 

OBJS += \
./src/mc/MarchingCubes.o \
./src/mc/mpVector.o 

CPP_DEPS += \
./src/mc/MarchingCubes.d \
./src/mc/mpVector.d 


# Each subdirectory must supply rules for building sources it contributes
src/mc/%.o: ../src/mc/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O2 -g -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


