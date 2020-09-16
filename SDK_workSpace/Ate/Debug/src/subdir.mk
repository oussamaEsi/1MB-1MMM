################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/frob.c \
../src/main.c \
../src/miller.c \
../src/montgomeyIP.c \
../src/opPoint.c \
../src/operFp.c \
../src/operFp12.c \
../src/operFp2.c \
../src/operFp6.c \
../src/outil.c 

LD_SRCS += \
../src/lscript.ld 

OBJS += \
./src/frob.o \
./src/main.o \
./src/miller.o \
./src/montgomeyIP.o \
./src/opPoint.o \
./src/operFp.o \
./src/operFp12.o \
./src/operFp2.o \
./src/operFp6.o \
./src/outil.o 

C_DEPS += \
./src/frob.d \
./src/main.d \
./src/miller.d \
./src/montgomeyIP.d \
./src/opPoint.d \
./src/operFp.d \
./src/operFp12.d \
./src/operFp2.d \
./src/operFp6.d \
./src/outil.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo Building file: $<
	@echo Invoking: MicroBlaze gcc compiler
	mb-gcc -Wall -O3 -g3 -c -fmessage-length=0 -I../../Ate_bsp/microblaze_0/include -mxl-barrel-shift -mxl-pattern-compare -mcpu=v8.20.a -mno-xl-soft-mul -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo Finished building: $<
	@echo ' '


