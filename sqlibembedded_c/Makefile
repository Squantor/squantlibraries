# generic makefile template
# valid options PLATFORM, defines the platform to compile for (pc, cortexM0, RV32I etc)

# Target settings
PLATFORM ?= pc
PROJECT = libsqlibembedded_c

# Tool settings
MAKE = make
MKDIR = mkdir
RM = rm
CXX = gcc
SIZE = size
AR = ar
OBJDUMP = objdump

# other settings
SRC_EXT = c

# include settings pertaining to the platform
include platforms/$(PLATFORM)/Makefile.inc

# Clear built-in rules
.SUFFIXES:

# Function used to check variables. Use on the command line:
# make print-VARNAME
# Useful for debugging and adding features
print-%: ; @echo $*=$($*)

# Combine compiler and linker flags
release: export CXXFLAGS := $(CXXFLAGS) $(COMPILE_FLAGS) $(RCOMPILE_FLAGS)
release: export LDFLAGS := $(LINK_FLAGS) $(RLINK_FLAGS)
debug: export CXXFLAGS := $(CXXFLAGS) $(COMPILE_FLAGS) $(DCOMPILE_FLAGS)
debug: export LDFLAGS := $(LINK_FLAGS) $(DLINK_FLAGS)

# Build and output paths
release: export BUILD_PATH := build/$(PLATFORM)/release
release: export BIN_PATH := bin/$(PLATFORM)/release
debug: export BUILD_PATH := build/$(PLATFORM)/debug
debug: export BIN_PATH := bin/$(PLATFORM)/debug

# export what target we are building, used for size logs
release: export BUILD_TARGET := release
debug: export BUILD_TARGET := debug

# Set the object file names, with the source directory stripped
# from the path, and the build path prepended in its place
OBJECTS = $(SOURCES:%.$(SRC_EXT)=$(BUILD_PATH)/%.o)
# Set the dependency files that will be used to add header dependencies
DEPS = $(OBJECTS:.o=.d)

# Standard, non-optimized release build
.PHONY: release
release: dirs
	$(MAKE) all --no-print-directory

# Debug build for gdb debugging
.PHONY: debug
debug: dirs
	$(MAKE) all --no-print-directory

# Create the directories used in the build
.PHONY: dirs
dirs:
	$(MKDIR) -p $(BUILD_PATH)
	$(MKDIR) -p $(BIN_PATH)

# Removes all build files
.PHONY: clean clean_debug clean_release
clean_debug:
clean_release:
clean:
	$(RM) -r build
	$(RM) -r bin

# Main rule, checks the executable and symlinks to the output
all: $(BIN_PATH)/$(PROJECT).a

# create the archive
$(BIN_PATH)/$(PROJECT).a: $(OBJECTS)
	$(CXX_PREFIX)$(AR) -r $@ $(OBJECTS)
	$(CXX_PREFIX)$(SIZE) $@
	date >> size$(BUILD_TARGET).log
	$(CXX_PREFIX)$(SIZE) $@ >> size$(BUILD_TARGET).log
	$(CXX_PREFIX)$(OBJDUMP) -h -S "$@" > "$(BIN_PATH)/$(PROJECT).lss"

# Add dependency files, if they exist
-include $(DEPS)

# Source file rules
# After the first compilation they will be joined with the rules from the
# dependency files to provide header dependencies
# if the source file is in a subdir, create this subdir in the build dir
$(BUILD_PATH)/%.o: ./%.$(SRC_EXT)
	$(MKDIR) -p $(dir $@) 
	$(CXX_PREFIX)$(CXX) $(CXXFLAGS) $(INCLUDES) -MP -MMD -c $< -o $@
