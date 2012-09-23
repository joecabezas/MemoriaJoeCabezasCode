################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Dataset/Dataset.cpp \
../src/Dataset/DatasetImage.cpp 

OBJS += \
./src/Dataset/Dataset.o \
./src/Dataset/DatasetImage.o 

CPP_DEPS += \
./src/Dataset/Dataset.d \
./src/Dataset/DatasetImage.d 


# Each subdirectory must supply rules for building sources it contributes
src/Dataset/%.o: ../src/Dataset/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O2 -g -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


