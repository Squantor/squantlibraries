# Project settings
BIN_NAME = sqlibc_test
SOURCES = sqlibc_tests.c test_strlen.c test_strto.c test_strtok.c test_putchar.c test_getchar.c
INCLUDES = -I. -I../inc
RLIBDIR = -L"../bin/release"
RLIBS = -lsqlibc
DLIBDIR = -L"../bin/debug"
DLIBS = -lsqlibc

# Toolchain settings
MAKE = make
MKDIR = mkdir
RM = rm
CXX = gcc
CXX_PREFIX = 
SIZE = size
AR = ar
OBJDUMP = objdump

# Toolchain flags
COMPILE_FLAGS = -std=c99 -Wall -Wextra -lrt -lm
DEFINES = 
RDEFINES = -DNDEBUG
DDEFINES = -DDEBUG
RCOMPILE_FLAGS = $(DEFINES) $(RDEFINES) -O3
DCOMPILE_FLAGS = $(DEFINES) $(DDEFINES) -g3 -O0

LINK_FLAGS =
RLINK_FLAGS =
DLINK_FLAGS =

# other settings
SRC_EXT = c

# Clear built-in rules
.SUFFIXES:

# Function used to check variables. Use on the command line:
# make print-VARNAME
# Useful for debugging and adding features
print-%: ; @echo $*=$($*)

# Combine compiler and linker flags
release: export CXXFLAGS := $(CXXFLAGS) $(COMPILE_FLAGS) $(RCOMPILE_FLAGS)
release: export LDFLAGS := $(LINK_FLAGS) $(RLINK_FLAGS) $(RLIBDIR)
release: export LIBS := $(RLIBS)
debug: export CXXFLAGS := $(CXXFLAGS) $(COMPILE_FLAGS) $(DCOMPILE_FLAGS)
debug: export LDFLAGS := $(LINK_FLAGS) $(DLINK_FLAGS) $(DLIBDIR)
debug: export LIBS := $(DLIBS)

# Build and output paths
release: export BUILD_PATH := build/release
release: export BIN_PATH := bin/release
debug: export BUILD_PATH := build/debug
debug: export BIN_PATH := bin/debug

# Set the object file names, with the source directory stripped
# from the path, and the build path prepended in its place
OBJECTS = $(SOURCES:%.$(SRC_EXT)=$(BUILD_PATH)/%.o)
# Set the dependency files that will be used to add header dependencies
DEPS = $(OBJECTS:.o=.d)

# Standard, non-optimized release build
.PHONY: release
release: dirs
	$(MAKE) -C .. release
	$(MAKE) all --no-print-directory

# Debug build for gdb debugging
.PHONY: debug
debug: dirs
	$(MAKE) -C .. debug
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
all: $(BIN_PATH)/$(BIN_NAME)

# create the archive
$(BIN_PATH)/$(BIN_NAME): $(OBJECTS)
	$(CXX_PREFIX)$(CXX) $(LDFLAGS) $(OBJECTS) -Xlinker -Map="$(BIN_PATH)/$(BIN_NAME).map" -o $@ $(LIBS)
	# dump size and log to file
	$(CXX_PREFIX)$(SIZE) $(BIN_PATH)/$(BIN_NAME)
	date >> size$(BUILD_TARGET).log
	$(CXX_PREFIX)$(SIZE) $(BIN_PATH)/$(BIN_NAME) >> size$(BUILD_TARGET).log
	# create the various output files
	$(CXX_PREFIX)$(OBJDUMP) -h -S "$(BIN_PATH)/$(BIN_NAME)" > "$(BIN_PATH)/$(BIN_NAME).lss"

# Add dependency files, if they exist
-include $(DEPS)

# Source file rules
# After the first compilation they will be joined with the rules from the
# dependency files to provide header dependencies
# if the source file is in a subdir, create this subdir in the build dir
$(BUILD_PATH)/%.o: ./%.$(SRC_EXT)
	$(MKDIR) -p $(dir $@) 
	$(CXX_PREFIX)$(CXX) $(CXXFLAGS) $(INCLUDES) -MP -MMD -c $< -o $@
