# Binary Utilities
CC = arm-none-eabi-gcc
AS = arm-none-eabi-as
LD = arm-none-eabi-ld
BIN = arm-none-eabi-objcopy

# Flags to compiler
OPT = -O0
DEPFLAGS = -MP -MD
CFLAGS = -c -mthumb -mcpu=cortex-m4 -std=gnu11 -Wall $(foreach D,$(INC_DIR),-I$(D)) $(OPT) $(DEPFLAGS)

# Flags to linker
LDFLAGS = -nostdlib -T linker_script.ld -Wl,-Map=out.map

# Flags to programmer
OPENOCD_FLAGS = -f st_nucleo_f4.cfg -c "program $(BINARY) verify reset exit"

# Directories paths
INC_DIR = App/Inc Lib $(wildcard Src/*/Inc) $(wildcard Mcal/*/Inc) $(wildcard Hal/*/Inc) $(wildcard Service/*/Inc)
SRC_DIR = App/Src $(wildcard Mcal/*/Src) $(wildcard Hal/*/Src) $(wildcard Service/*/Src)

# File paths within the directories
SRCS = $(foreach D,$(SRC_DIR),$(wildcard $(D)/*.c))
OBJS = $(patsubst %.c,%.o,$(SRCS))
DEPS = $(patsubst %.c,%.d,$(SRCS))
BINARY = out.elf

all : $(BINARY)

$(BINARY) : $(OBJS)
	$(info ==================== GENERATING Binary =======================)
	$(CC) $(LDFLAGS) $^ -o $@

%.o : %.c 
	$(info ================= GENERATING OBJECT FILES ====================)
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf $(OBJS) $(BINARY) $(DEPS) *.map

flash:
	openocd $(OPENOCD_FLAGS)

# include the dependencies
-include $(DEPS)
