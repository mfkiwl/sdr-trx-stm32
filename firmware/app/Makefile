#****************************************************************************
#*
#*  (C) 2020 Andrii Bilynskyi <andriy.bilynskyy@gmail.com>
#*
#*  This code is licensed under the GPLv3.
#*
#****************************************************************************


TOOLCHAIN_PATH := /opt/gcc-arm-none-eabi-10-2020-q4-major


CC     := ${TOOLCHAIN_PATH}/bin/arm-none-eabi-gcc
CXX    := ${TOOLCHAIN_PATH}/bin/arm-none-eabi-g++
AS     := ${TOOLCHAIN_PATH}/bin/arm-none-eabi-gcc
LD     := ${TOOLCHAIN_PATH}/bin/arm-none-eabi-ld
OBJCPY := ${TOOLCHAIN_PATH}/bin/arm-none-eabi-objcopy
SIZE   := ${TOOLCHAIN_PATH}/bin/arm-none-eabi-size
GDB    := ${TOOLCHAIN_PATH}/bin/arm-none-eabi-gdb
OCD    := openocd
DDD    := ddd
STYLE  := astyle
CHECK  := cppcheck


PROJECT ?= sdr-trx-app


PROJECT_SRC := \
  ${wildcard src/*.c} ${wildcard src/*.cpp} \
  ${wildcard src/widgets/*.c} ${wildcard src/widgets/*.cpp} \
  ${wildcard src/rtos_ext/*.c} ${wildcard src/rtos_ext/*.cpp} \
  ${wildcard src/tasks/*.c} ${wildcard src/tasks/*.cpp} \
  ${wildcard src/dsp_proc/*.c} ${wildcard src/dsp_proc/*.cpp} \
  ${wildcard src/app_hal/*.c} ${wildcard src/app_hal/*.cpp} \
  ${wildcard src/bitmaps/*.c} \

PROJECT_INC := \
  config \
  src \
  src/widgets \
  src/tasks \
  src/dsp_proc \
  src/app_hal \
  src/bitmaps \

PROJECT_LIB := \

PROJECT_STYLE := \
  ${wildcard src/*.[hc]} ${wildcard src/*.cpp} \
  ${wildcard src/widgets/*.[hc]} ${wildcard src/widgets/*.cpp} \
  ${wildcard src/rtos_ext/*.[hc]} ${wildcard src/rtos_ext/*.cpp} \
  ${wildcard src/tasks/*.[hc]} ${wildcard src/tasks/*.cpp} \
  ${wildcard src/dsp_proc/*.[hc]} ${wildcard src/dsp_proc/*.cpp} \
  ${wildcard src/app_hal/*.[hc]} ${wildcard src/app_hal/*.cpp} \
  ${wildcard config/*.h} \
  ${wildcard src/bitmaps/*.[hc]} \


include ../free_rtos/unit.mk
include ../bsp/codec/unit.mk
include ../bsp/dco/unit.mk
include ../bsp/mem24/unit.mk
include ../bsp/rf_amp/unit.mk
include ../bsp/i2c_master/unit.mk
include ../bsp/adc/unit.mk
include ../bsp/rtc/unit.mk
include ../bsp/ui_engine/unit.mk
include ../bsp/trxctl/unit.mk
include ../bsp/hwctl/unit.mk
include ../bsp/led/unit.mk
include ../bsp/critical_err/unit.mk
include ../bsp/misc/unit.mk
include ../bsp/system/unit.mk
include ../common/misc/unit.mk
include ../common/dbg/unit.mk
include ../stm/unit.mk
include ../cm/unit.mk
include ../sw_version/unit.mk


LD_SCRIPT := STM32F413ZH_FLASH.ld

OBJECTS := ${addsuffix .o, ${PROJECT_SRC}}

CFLAGS  := -Wall -Wdouble-promotion -std=c99 -fdata-sections -ffunction-sections
CFLAGS  += -mlittle-endian -mthumb -mcpu=cortex-m4 -mfloat-abi=hard -mfpu=fpv4-sp-d16
CFLAGS  += -DSTM32F413_423xx -DHSE_VALUE=24000000u -DUSE_STDPERIPH_DRIVER -DUSE_FULL_ASSERT
CFLAGS  += -DARM_MATH_CM4=1 -D__FPU_PRESENT=1 -D__FPU_USED=1U -D__VFP_FP__

ASFLAGS  := -Wall -Wdouble-promotion -std=c99 -fdata-sections -ffunction-sections
ASFLAGS  += -mlittle-endian -mthumb -mcpu=cortex-m4 -mfloat-abi=hard -mfpu=fpv4-sp-d16
ASFLAGS  += -DSTM32F413_423xx -DHSE_VALUE=24000000u -DUSE_STDPERIPH_DRIVER -DUSE_FULL_ASSERT
ASFLAGS  += -DARM_MATH_CM4=1 -D__FPU_PRESENT=1 -D__FPU_USED=1U -D__VFP_FP__

CXXFLAGS  := -Wall -Wdouble-promotion -fno-exceptions -fdata-sections -ffunction-sections
CXXFLAGS  += -mlittle-endian -mthumb -mcpu=cortex-m4 -mfloat-abi=hard -mfpu=fpv4-sp-d16
CXXFLAGS  += -DSTM32F413_423xx -DHSE_VALUE=24000000u -DUSE_STDPERIPH_DRIVER -DUSE_FULL_ASSERT
CXXFLAGS  += -DARM_MATH_CM4=1 -D__FPU_PRESENT=1 -D__FPU_USED=1U -D__VFP_FP__

LDFLAGS := -T${LD_SCRIPT}
LDFLAGS += -mlittle-endian -mthumb -mcpu=cortex-m4 -mfloat-abi=hard -mfpu=fpv4-sp-d16
LDFLAGS += -Wl,--gc-sections
LDFLAGS += -Xlinker -Map=${PROJECT}.map
LDFLAGS += ${addprefix -l, ${PROJECT_LIB}}

BINFLAGS := -r -b binary


ifndef BUILD
  BUILD := RELEASE
endif

ifeq (${BUILD},DEBUG)
  CFLAGS  += -g3 -O1 -DDEBUG
  ASFLAGS += -g3 -O1 -DDEBUG
  CXXFLAGS += -g3 -O1 -DDEBUG
  LDFLAGS += --specs=rdimon.specs
else ifeq (${BUILD},RELEASE)
  CFLAGS  += -g0 -O3
  ASFLAGS += -g0 -O3
  CXXFLAGS += -g0 -O3
  LDFLAGS += --specs=nosys.specs
else
  ${error Wrong BUILD '${BUILD}'! Should be: DEBUG or RELEASE}
endif

CFLAGS  += ${addprefix -I, ${PROJECT_INC}}
CXXFLAGS  += ${addprefix -I, ${PROJECT_INC}}

.PHONY: all build clean flash erase debug style help force

all: ${PROJECT}.elf

build: ${PROJECT}.elf

${PROJECT}.elf: ${OBJECTS} ${LD_SCRIPT}
	${info ${BUILD} BUILD}
	${CXX} ${OBJECTS} -o $@ ${LDFLAGS}
	${OBJCPY} -O ihex $@ ${PROJECT}.hex
	${SIZE} --format=berkeley $@

%.c.o: %.c
	${CC} ${CFLAGS} -MD -c $< -o $@

%.s.o: %.s
	${CC} ${ASFLAGS} -MD -c $< -o $@

%.S.o: %.S
	${CC} ${ASFLAGS} -MD -c $< -o $@

%.cpp.o: %.cpp
	${CXX} ${CXXFLAGS} -MD -c $< -o $@

%.bin.o: %.bin
	${LD} ${BINFLAGS} $< -o $@

clean:
	rm -f ${OBJECTS} ${PROJECT_UNIT_GEN} ${OBJECTS:.o=.d} ${PROJECT}.elf ${PROJECT}.hex ${PROJECT}.map

flash:
	@if [ -f "${PROJECT}.hex" ] ;                                               \
  then                                                                          \
    ${OCD} -f ../openocd/jlink.cfg -f ../openocd/stm32f4x.cfg                   \
            -c "init"                                                           \
            -c "reset init"                                                     \
            -c "flash write_image erase ${PROJECT}.hex"                         \
            -c "reset"                                                          \
            -c "shutdown";                                                      \
  else                                                                          \
    echo "Output .hex file doesn't exist. Run 'make all' before!";              \
  fi

erase:
	${OCD} -f ../openocd/jlink.cfg -f ../openocd/stm32f4x.cfg                   \
            -c "init"                                                           \
            -c "reset init"                                                     \
            -c "flash protect 0 0 last off"                                     \
            -c "stm32f4x unlock 0"                                              \
            -c "reset halt"                                                     \
            -c "reset init"                                                     \
            -c "stm32f4x mass_erase 0"                                          \
            -c "reset"                                                          \
            -c "shutdown";                                                      \

debug:
	@if [ -f "${PROJECT}.elf" ] ;                                               \
  then                                                                          \
    ${OCD} -f ../openocd/jlink.cfg -f ../openocd/stm32f4x.cfg &                 \
    ${DDD} "${PROJECT}.elf" --debugger "${GDB}                                  \
                                            -ex 'target extended-remote :3333'  \
                                            -ex 'monitor arm semihosting enable'\
                                            -ex 'monitor reset halt'            \
                                            -ex 'load'                          \
                                            -ex 'monitor reset halt'";          \
    kill -9 $$!;                                                                \
  else                                                                          \
    echo "Output .elf file doesn't exist. Run 'make all' before!";              \
  fi

style:
	${STYLE} --style=google --convert-tabs --lineend=linux --suffix=none ${PROJECT_STYLE}

check:
	${CHECK} -q --enable=style,performance,portability,information              \
                --suppress=missingInclude                                       \
                --force --inconclusive --inline-suppr ${PROJECT_STYLE}          \

help:
	@:
	${info Help}
	${info ---------------------------------------------------------------------}
	${info make help                     - this help text}
	${info make BUILD=<build_type> build - create binary files (.elf, .hex)}
	${info make BUILD=<build_type> all   - create binary files (.elf, .hex). same as build}
	${info make clean                    - remove generated files}
	${info make flash                    - flash target}
	${info make erase                    - flash erase}
	${info make debug                    - start debugging session DDD(gdb)}
	${info make style                    - perform user sources formatting}
	${info make check                    - perform user sources static analysis}
	${info ---------------------------------------------------------------------}
	${info Available build_type [DEBUG RELEASE], eg: make BUILD=RELEASE ...}
	${info Default build_type RELEASE}

-include ${OBJECTS:.o=.d}
