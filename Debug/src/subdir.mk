################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/STLReader.cpp \
../src/draw.cpp \
../src/drawing.cpp \
../src/gcontext.cpp \
../src/image.cpp \
../src/line.cpp \
../src/matrix.cpp \
../src/point.cpp \
../src/shape.cpp \
../src/triangle.cpp \
../src/viewcontext.cpp \
../src/x11context.cpp 

OBJS += \
./src/STLReader.o \
./src/draw.o \
./src/drawing.o \
./src/gcontext.o \
./src/image.o \
./src/line.o \
./src/matrix.o \
./src/point.o \
./src/shape.o \
./src/triangle.o \
./src/viewcontext.o \
./src/x11context.o 

CPP_DEPS += \
./src/STLReader.d \
./src/draw.d \
./src/drawing.d \
./src/gcontext.d \
./src/image.d \
./src/line.d \
./src/matrix.d \
./src/point.d \
./src/shape.d \
./src/triangle.d \
./src/viewcontext.d \
./src/x11context.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


