# Target specific settings
SOURCES = src/print.c \
src/strlen.c src/strtok.c src/strcmp.c src/strncpy.c \
src/memchr.c src/memcmp.c src/memcpy.c src/memmove.c src/memset.c \
src/strto.c \
src/ctypetable.c \
src/isspace.c src/isxdigit.c \
src/empty_stdio.c src/getchar.c  src/putchar.c src/puts.c \
src/fgetc.c src/fgets.c src/fputc.c src/fputs.c \
src/empty_logfs.c src/logfs.c \
src/cmdline.c src/cmdline_cmd.c src/cmdline_prompt.c \
src/queue_string.c \
src/parse_ansi.c \
src/assert.c
INCLUDES = -Iinc

# toolchain prefix
CXX_PREFIX = arm-none-eabi-

# Toolchain flags
COMPILE_FLAGS = -std=c11 -Wall -Wextra -Werror -mcpu=cortex-m0 -mthumb -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections
DEFINES = -DCORE_M0
RDEFINES = -DNDEBUG
DDEFINES = -DDEBUG
RCOMPILE_FLAGS = $(DEFINES) $(RDEFINES) -g -Os
DCOMPILE_FLAGS = $(DEFINES) $(DDEFINES) -g3 -O0

LINK_FLAGS =
RLINK_FLAGS =
DLINK_FLAGS =
