SHELL=/bin/bash -o pipefail

### Build Options ###
VERSION      ?= proto
BASE_EXE     := hocus.$(VERSION).exe
TARGET       := hocus
COMPARE      ?= 1
VERBOSE      ?= 0
BUILD_DIR    ?= build/$(VERSION)

# Fail early if BASE_EXE does not exist
ifeq ($(wildcard $(BASE_EXE)),)
$(error BASE_EXE `$(BASE_EXE)' not found.)
endif

ifeq ($(VERBOSE),0)
V := @
endif

ifeq ($(OS),Windows_NT)
  DETECTED_OS=windows
else
  UNAME_S := $(shell uname -s)
  ifeq ($(UNAME_S),Linux)
    DETECTED_OS=linux
  endif
endif

### Output ###
VERSION_DIR  := versions/$(VERSION)
DOS_EXE      := $(BUILD_DIR)/$(TARGET).exe
LD_SCRIPT    := $(TARGET).rsp

### Tools ###
PYTHON     := python3
DIFF       := $(PYTHON) tools/diff.py
MKDIR      := mkdir -p
GREP       := grep -E
SED        := sed
DOSEMU	   := HOME="." dosemu -quiet -dumb -K . -E
AS         := %BCC31%\bin\tasm
LD         := %BCC31%\bin\tlink
CC         := %BCC31%\bin\bcc

PRINT := printf '
 ENDCOLOR := \033[0m
 WHITE     := \033[0m
 ENDWHITE  := $(ENDCOLOR)
 GREEN     := \033[0;32m
 ENDGREEN  := $(ENDCOLOR)
 BLUE      := \033[0;34m
 ENDBLUE   := $(ENDCOLOR)
 YELLOW    := \033[0;33m
 ENDYELLOW := $(ENDCOLOR)
 PURPLE    := \033[0;35m
 ENDPURPLE := $(ENDCOLOR)
ENDLINE := \n'

### Compiler Options ###
OPTFLAGS ?=
ASFLAGS  := /e /ml
CFLAGS   := -ml -y -a -K -Iinclude -I%BCC31%\include
LDFLAGS  := /m /s /c /l /v /L%BCC31%\lib

ifeq ($(VERSION),proto)
    CFLAGS += -DVERSION_PROTO=1
else ifeq ($(VERSION),v10)
    CFLAGS += -DVERSION_10=1
else ifeq ($(VERSION),v11)
    CFLAGS += -DVERSION_11=1
else ifeq ($(VERSION),demo10)
    CFLAGS += -DVERSION_DEMO10=1
else ifeq ($(VERSION),demo11)
    CFLAGS += -DVERSION_DEMO11=1
else
$(error Invalid VERSION variable detected. Please use either 'proto', 'v10', 'v11', 'demo10' or 'demo11')
endif

ifneq ($(VERSION),proto)
    CFLAGS += -2 -Iaudiolib
endif

### Sources ###

# Object files
OBJECTS := $(shell $(GREP) 'BUILD_PATH.+\.obj' $(VERSION_DIR)/$(LD_SCRIPT) -o | $(SED) 's/\\/\//g')
OBJECTS := $(OBJECTS:BUILD_PATH/%=$(BUILD_DIR)/%)
OBJDIRS = $(dir $(OBJECTS))
$(shell $(MKDIR) $(OBJDIRS))

### Targets ###

$(BUILD_DIR)/src/digisnd.obj: OPTFLAGS := -O2
$(BUILD_DIR)/src/digisnd.obj: CFLAGS := $(filter-out -a -K,$(CFLAGS))

$(BUILD_DIR)/audiolib/%.obj: OPTFLAGS := -O -G
$(BUILD_DIR)/audiolib/%.obj: CFLAGS := -ml -y -2 -Iaudiolib -I%BCC20%\include
$(BUILD_DIR)/audiolib/%.obj: CC := %BCC20%\bin\bcc

all: $(DOS_EXE)

clean:
	$(V)rm -rf $(BUILD_DIR)

$(BUILD_DIR)/%.obj: %.c
	@$(PRINT)$(GREEN)Compiling C file: $(ENDGREEN)$(BLUE)$<$(ENDBLUE)$(ENDLINE)
	$(V)$(DOSEMU) "$(CC) $(OPTFLAGS) $(CFLAGS) -c -o$(subst /,\,$@) $(subst /,\,$<)" | { $(GREP) "Warning|Error|Fatal" || true; }

$(BUILD_DIR)/%.obj: %.asm
	@$(PRINT)$(GREEN)Assembling asm file: $(ENDGREEN)$(BLUE)$<$(ENDBLUE)$(ENDLINE)
	$(V)$(DOSEMU) "$(AS) $(ASFLAGS) $(subst /,\,$<),$(subst /,\,$@)" | { $(GREP) "\*Warning\*|\*Error\*|\*Fatal\*" || true; }

$(BUILD_DIR)/$(LD_SCRIPT): $(VERSION_DIR)/$(LD_SCRIPT)
	@$(PRINT)$(GREEN)Preprocessing linker script: $(ENDGREEN)$(BLUE)$<$(ENDBLUE)$(ENDLINE)
	$(V)$(SED) 's/BUILD_PATH/$(subst /,\\,$(BUILD_DIR))/g' $< > $@

$(DOS_EXE): $(BUILD_DIR)/$(LD_SCRIPT) $(OBJECTS)
	@$(PRINT)$(GREEN)Linking DOS file: $(ENDGREEN)$(BLUE)$@$(ENDBLUE)$(ENDLINE)
	$(V)$(DOSEMU) "$(LD) $(LDFLAGS) @$(subst /,\\,$<)" | { $(GREP) "Warning|Error|Fatal" || true; }
ifeq ($(COMPARE),1)
	@$(DIFF) $(BASE_EXE) $(DOS_EXE)
endif

### Make Settings ###
.PHONY: all clean

# Remove built-in implicit rules to improve performance
MAKEFLAGS += --no-builtin-rules

# Print target for debugging
print-% : ; $(info $* is a $(flavor $*) variable set to [$($*)]) @true
