# ==============================================================================
# rules.mk — Build Rules and Targets
#
# Defines pattern rules for compiling C and assembly sources, linking the
# final ELF binary, and generating HEX/BIN output files.
#
# Provides the following targets:
#   all   — Build the firmware (default)
#   clean — Remove all build artifacts
#   flash — Program the target via OpenOCD
#   debug — Start OpenOCD GDB server for debugging
#   size  — Print firmware size summary
#
# Included by the top-level Makefile.
# ==============================================================================

# --------------------------------------------------------------------------
# Object file lists
# --------------------------------------------------------------------------

OBJECTS  = $(addprefix $(BUILD_DIR)/,$(notdir $(C_SOURCES:.c=.o)))
vpath %.c $(sort $(dir $(C_SOURCES)))

OBJECTS += $(addprefix $(BUILD_DIR)/,$(notdir $(ASM_SOURCES:.s=.o)))
vpath %.s $(sort $(dir $(ASM_SOURCES)))

# Dependency files for automatic header tracking
DEPS = $(OBJECTS:.o=.d)

# --------------------------------------------------------------------------
# Output files
# --------------------------------------------------------------------------

ELF = $(BUILD_DIR)/$(PROJECT).elf
HEX = $(BUILD_DIR)/$(PROJECT).hex
BIN = $(BUILD_DIR)/$(PROJECT).bin
MAP = $(BUILD_DIR)/$(PROJECT).map

# --------------------------------------------------------------------------
# Default target
# --------------------------------------------------------------------------

all: $(ELF) $(HEX) $(BIN) size

# --------------------------------------------------------------------------
# Pattern rules
# --------------------------------------------------------------------------

# Compile C sources
$(BUILD_DIR)/%.o: %.c | $(BUILD_DIR)
	@echo "  CC    $<"
	@$(CC) -c $(CFLAGS) $< -o $@

# Assemble startup file
$(BUILD_DIR)/%.o: %.s | $(BUILD_DIR)
	@echo "  AS    $<"
	@$(AS) -c $(ASFLAGS) $< -o $@

# --------------------------------------------------------------------------
# Link
# --------------------------------------------------------------------------

$(ELF): $(OBJECTS)
	@echo "  LD    $@"
	@$(LD) $(OBJECTS) $(LDFLAGS) -o $@

# --------------------------------------------------------------------------
# Binary output
# --------------------------------------------------------------------------

$(HEX): $(ELF)
	@echo "  HEX   $@"
	@$(OBJCOPY) -O ihex $< $@

$(BIN): $(ELF)
	@echo "  BIN   $@"
	@$(OBJCOPY) -O binary -S $< $@

# --------------------------------------------------------------------------
# Create build directory
# --------------------------------------------------------------------------

$(BUILD_DIR):
	@mkdir -p $(BUILD_DIR)

# --------------------------------------------------------------------------
# Utility targets
# --------------------------------------------------------------------------

.PHONY: all clean flash debug size

size: $(ELF)
	@echo ""
	@$(SIZE) $<
	@echo ""

clean:
	@echo "  CLEAN $(BUILD_DIR)/"
	@rm -rf $(BUILD_DIR)

flash: $(BIN)
	@echo "  FLASH $(BIN)"
	openocd -f config/openocd.cfg \
	  -c "program $(ELF) verify reset exit"

debug:
	@echo "  DEBUG Starting OpenOCD GDB server..."
	openocd -f config/openocd.cfg

# --------------------------------------------------------------------------
# Include auto-generated dependency files
# --------------------------------------------------------------------------

-include $(DEPS)
