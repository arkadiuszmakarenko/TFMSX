# ============================================================================
#  TFMSX - STM32F730R8Tx firmware
#
#  Standalone GNU Make build. No STM32CubeIDE required.
#
#  Quick start:
#     make                 # build (debug by default) -> build/debug/*.elf/bin/hex
#     make release         # optimized build            -> build/release/*
#     make flash           # build + program via ST-Link
#     make help            # show all targets
#
#  Override the build configuration on any target, e.g.
#     make CONFIG=release flash
# ============================================================================

# ---- Project ---------------------------------------------------------------
TARGET      := TFMSXRev2F730
# Build configuration: "debug" (default) or "release"
CONFIG      ?= debug
CONFIG      := $(strip $(CONFIG))
DEBUG       ?= 0
DEBUG       := $(strip $(DEBUG))
LDSCRIPT    ?= STM32F730R8TX_FLASH.ld
BUILD_DIR   := build/$(CONFIG)
OBJ_DIR     := $(BUILD_DIR)/obj
DEBUG_STAMP := $(BUILD_DIR)/.printf-debug-$(DEBUG)

ELF         := $(BUILD_DIR)/$(TARGET).elf
BIN         := $(BUILD_DIR)/$(TARGET).bin
HEX         := $(BUILD_DIR)/$(TARGET).hex
MAP         := $(BUILD_DIR)/$(TARGET).map

# ---- Toolchain -------------------------------------------------------------
PREFIX      ?= arm-none-eabi-
CC          := $(PREFIX)gcc
AS          := $(PREFIX)gcc -x assembler-with-cpp
CP          := $(PREFIX)objcopy
OD          := $(PREFIX)objdump
SZ          := $(PREFIX)size
GDB         ?= $(PREFIX)gdb

# ---- Target CPU ------------------------------------------------------------
CPU_FLAGS   := -mcpu=cortex-m7 -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb

# ---- Defines / include paths ----------------------------------------------
DEFS        := -DUSE_HAL_DRIVER -DSTM32F730xx -DUSE_FULL_LL_DRIVER -DTFMSX_DEBUG=$(DEBUG)

INCLUDES    := \
  -ICore/Inc \
  -IUSB_HOST/App \
  -IUSB_HOST/Target \
  -IDrivers/STM32F7xx_HAL_Driver/Inc \
  -IDrivers/STM32F7xx_HAL_Driver/Inc/Legacy \
  -IDrivers/CMSIS/Device/ST/STM32F7xx/Include \
  -IDrivers/CMSIS/Include \
  -IMiddlewares/ST/STM32_USB_Host_Library/Core/Inc \
  -IMiddlewares/ST/STM32_USB_Host_Library/Class/HID/Inc \
  -IMiddlewares/ST/STM32_USB_Host_Library/Class/HUBHID/Inc

# ---- Sources (auto-discovered) --------------------------------------------
C_SOURCES   := \
  $(wildcard Core/Src/*.c) \
  $(wildcard USB_HOST/App/*.c) \
  $(wildcard USB_HOST/Target/*.c) \
  $(wildcard Drivers/STM32F7xx_HAL_Driver/Src/*.c) \
  $(wildcard Middlewares/ST/STM32_USB_Host_Library/Core/Src/*.c) \
  $(wildcard Middlewares/ST/STM32_USB_Host_Library/Class/HID/Src/*.c) \
  $(wildcard Middlewares/ST/STM32_USB_Host_Library/Class/HUBHID/Src/*.c)

ASM_SOURCES := $(wildcard Core/Startup/*.s)

# ---- Per-configuration flags ----------------------------------------------
SPECS       := --specs=nano.specs

ifeq ($(CONFIG),debug)
  OPT       := -Og
  DEBUG_DEF := -DDEBUG
  DBG_FLAGS := -g3
else ifeq ($(CONFIG),release)
  OPT       := -Os
  DEBUG_DEF :=
  DBG_FLAGS := -g
else
  $(error Unknown CONFIG '$(CONFIG)': expected 'debug' or 'release')
endif

CFLAGS      := $(CPU_FLAGS) $(DEFS) $(INCLUDES) $(SPECS) $(DEBUG_DEF) $(OPT) $(DBG_FLAGS) \
               -std=gnu11 -Wall -ffunction-sections -fdata-sections -MMD -MP
ASFLAGS     := $(CPU_FLAGS) $(OPT) $(DBG_FLAGS) -MMD -MP
LDFLAGS     := $(CPU_FLAGS) -T$(LDSCRIPT) $(SPECS) --specs=nosys.specs \
               -Wl,-Map=$(MAP) -Wl,--gc-sections -static \
               -Wl,--start-group -lc -lm -Wl,--end-group

# ---- Object / dependency lists --------------------------------------------
OBJS        := $(addprefix $(OBJ_DIR)/,$(C_SOURCES:.c=.o)) \
               $(addprefix $(OBJ_DIR)/,$(ASM_SOURCES:.s=.o))
DEPS        := $(OBJS:.o=.d)

# ============================================================================
#  Build rules
# ============================================================================
.PHONY: all release debug flash erase reset server gdb stflash size clean distclean help check-toolchain

all: check-toolchain $(ELF) $(BIN) $(HEX) size

# Convenience wrappers
release:
	@$(MAKE) --no-print-directory CONFIG=release all
debug:
	@$(MAKE) --no-print-directory CONFIG=debug all

# ---- Toolchain presence check ---------------------------------------------
check-toolchain:
	@command -v $(CC) >/dev/null 2>&1 || { \
	  echo "ERROR: '$(CC)' not found in PATH."; \
	  echo "Install the toolchain first, e.g.:"; \
	  echo "    sudo apt install gcc-arm-none-eabi"; \
	  exit 1; }

# ---- Link ------------------------------------------------------------------
$(ELF): $(OBJS) $(LDSCRIPT) Makefile
	@echo "  LD      $@"
	@$(CC) $(OBJS) $(LDFLAGS) -o $@

# ---- Binary / hex generation ----------------------------------------------
$(BIN): $(ELF)
	@echo "  OBJCOPY $@"
	@$(CP) -O binary $< $@

$(HEX): $(ELF)
	@echo "  OBJCOPY $@"
	@$(CP) -O ihex $< $@

$(BUILD_DIR)/$(TARGET).map: $(ELF)

$(BUILD_DIR)/$(TARGET).list: $(ELF)
	@echo "  OBJDUMP $@"
	@$(OD) -h -S $< > $@

# ---- Compile / assemble ----------------------------------------------------
$(OBJ_DIR)/%.o: %.c Makefile $(DEBUG_STAMP)
	@mkdir -p $(dir $@)
	@echo "  CC      $<"
	@$(CC) $(CFLAGS) -MF $(@:.o=.d) -c $< -o $@

$(OBJ_DIR)/%.o: %.s Makefile $(DEBUG_STAMP)
	@mkdir -p $(dir $@)
	@echo "  AS      $<"
	@$(AS) $(ASFLAGS) -MF $(@:.o=.d) -c $< -o $@

$(DEBUG_STAMP):
	@mkdir -p $(BUILD_DIR)
	@touch $@

# ============================================================================
#  Programming / debugging (ST-Link via OpenOCD by default)
# ============================================================================
OPENOCD      ?= openocd
OPENOCD_IF   ?= interface/stlink.cfg
OPENOCD_TGT  ?= target/stm32f7x.cfg
OPENOCD_ARGS := -f $(OPENOCD_IF) -f $(OPENOCD_TGT)
STFLASH      ?= st-flash

# Flash the built ELF (verify + reset + exit)
flash: check-toolchain $(ELF)
	@command -v $(OPENOCD) >/dev/null 2>&1 || { \
	  echo "ERROR: '$(OPENOCD)' not found. Install with: sudo apt install openocd"; exit 1; }
	$(OPENOCD) $(OPENOCD_ARGS) -c "program $(ELF) verify reset exit"

# Alternative flasher (stlink-tools)
stflash: $(BIN)
	@command -v $(STFLASH) >/dev/null 2>&1 || { \
	  echo "ERROR: '$(STFLASH)' not found. Install with: sudo apt install stlink-tools"; exit 1; }
	$(STFLASH) --reset write $(BIN) 0x08000000

# Full chip erase
erase:
	$(OPENOCD) $(OPENOCD_ARGS) -c "init; reset halt; stm32f2x mass_erase 0; shutdown"

# Reset the target
reset:
	$(OPENOCD) $(OPENOCD_ARGS) -c "init; reset; shutdown"

# Start the GDB server (leave running, then use 'make gdb' in another shell)
server:
	$(OPENOCD) $(OPENOCD_ARGS)

# Attach GDB, load the image and halt at main
gdb: check-toolchain $(ELF)
	$(GDB) $(ELF) \
	  -ex "target extended-remote localhost:3333" \
	  -ex "monitor reset halt" \
	  -ex "load" \
	  -ex "monitor reset init" \
	  -ex "break main" \
	  -ex "continue"

# ============================================================================
#  Utility targets
# ============================================================================
size: $(ELF)
	@echo "  SIZE    $<"
	@$(SZ) $<

clean:
	@echo "  CLEAN   $(BUILD_DIR)"
	@rm -rf $(BUILD_DIR)

distclean:
	@echo "  CLEAN   build/"
	@rm -rf build

help:
	@echo "TFMSX build system"
	@echo ""
	@echo "  make [CONFIG=debug|release]   Build ELF/BIN/HEX (default: debug)"
	@echo "  make flash DEBUG=1             Enable USB/data printf diagnostics"
	@echo "  make release                  Optimized build (-Os)"
	@echo "  make debug                    Debug build (-O0 -g3)"
	@echo "  make flash                    Program via ST-Link/OpenOCD"
	@echo "  make stflash                  Program via st-flash (stlink-tools)"
	@echo "  make erase                    Erase whole flash"
	@echo "  make reset                    Reset target"
	@echo "  make server                   Start OpenOCD GDB server (:3333)"
	@echo "  make gdb                      Attach GDB (after 'make server')"
	@echo "  make size                     Show ELF section sizes"
	@echo "  make clean                    Remove build/$(CONFIG)"
	@echo "  make distclean                Remove entire build/"
	@echo ""
	@echo "  Variables: CONFIG, LDSCRIPT, PREFIX, OPENOCD, OPENOCD_IF, OPENOCD_TGT"
	@echo "  Output:    build/<config>/$(TARGET).{elf,bin,hex,map}"

-include $(DEPS)
