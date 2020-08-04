PRJ_NAME   = Blink
CC         = arm-none-eabi-gcc
OBJCOPY    = arm-none-eabi-objcopy
OBJDUMP    = arm-none-eabi-objdump
SRCDIR     = src
SPL_DIR = ../STM32F10x_StdPeriph_Lib_V3.5.0/Libraries/STM32F10x_StdPeriph_Driver
# get a list of all the .c source file in this directory
SRC        = $(wildcard $(SRCDIR)/*.c)
# SPL source file, build all
SRC+=        $(wildcard $(SPL_DIR)/src/*.c)
ASRC       = $(wildcard $(SRCDIR)/*.s)
OBJ        = $(SRC:.c=.o) $(ASRC:.s=.o)
PROGRAMMER = openocd
PGFLAGS    = -f openocd.cfg -c "program ./bin/$(PRJ_NAME).elf verify reset" -c shutdown
#DEVICE     = STM32F103xB
# this is for `system_stm32f10x.c`
DEVICE     = STM32F10X_MD
OPT       ?= -Og
CFLAGS     = -fdata-sections -ffunction-sections -g3 -Wall -mcpu=cortex-m3 -mlittle-endian -mthumb -I./inc -D$(DEVICE) $(OPT)
CFLAGS     +=  -DUSE_STDPERIPH_DRIVER
CFLAGS     += -I$(SPL_DIR)/inc
CFLAGS     += -I../STM32F10x_StdPeriph_Lib_V3.5.0/Libraries/CMSIS/CM3/DeviceSupport/ST/STM32F10x
#CFLAGS +=-DSTM32F10X_MD
ASFLAGS    =  $(CFLAGS)
LDSCRIPT   = stm32f103c8tx.ld
LDFLAGS    = -T $(LDSCRIPT) -Wl,--gc-sections --specs=nano.specs --specs=nosys.specs

.PHONY: all clean flash burn hex bin

all: ./bin/$(PRJ_NAME).elf

./bin/$(PRJ_NAME).elf: $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $@ $(LDFLAGS)
	arm-none-eabi-size ./bin/$(PRJ_NAME).elf

%.o: %.c $(DEPS)
	$(CC) -MMD -c $(CFLAGS) $< -o $@

%.o: %.s $(DEPS)
	$(CC) -MMD -c $(ASFLAGS) $< -o $@

-include $(SRCDIR)/*.d

clean:
	rm -f $(OBJ) ./bin/$(PRJ_NAME).elf ./bin/$(PRJ_NAME).hex ./bin/$(PRJ_NAME).bin $(SRCDIR)/*.d
	rm -f ./bin/*
flash: ./bin/$(PRJ_NAME).elf
	$(PROGRAMMER) $(PGFLAGS)

burn: ./bin/$(PRJ_NAME).elf
	$(PROGRAMMER) $(PGFLAGS)

hex: ./bin/$(PRJ_NAME).elf
	$(OBJCOPY) -O ihex ./bin/$(PRJ_NAME).elf ./bin/$(PRJ_NAME).hex

bin: ./bin/$(PRJ_NAME).elf
	$(OBJCOPY) -O binary ./bin/$(PRJ_NAME).elf ./bin/$(PRJ_NAME).bin
