# CodeVoid basic (CPP) Makefile

# Tools
ASM     = nasm
CC      = clang++

# Project Structure
SRC     = src
BUILD   = build
TARGET  = $(BUILD)/main

# Compiler flags (switch -O0 for DEBUG=1)
ifeq ($(DEBUG),1)
  CFLAGS = -Wall -Wextra -O0 -std=c++20 -MMD -MP
else
  CFLAGS = -Wall -Wextra -O2 -std=c++20 -MMD -MP
endif

LDFLAGS = -pthread -lm

# Find all .cpp files
CXX_SOURCES := $(shell find $(SRC) -name '*.cpp')
# Convert .cpp files to .o files in build folder
CXX_OBJS    := $(patsubst $(SRC)/%.cpp, $(BUILD)/%.o, $(CXX_SOURCES))
# Corresponding dependency files (.d)
CXX_DEPS    := $(CXX_OBJS:.o=.d)

# Find all header files (for info only)
HEADERS := $(shell find $(SRC) -name '*.hpp' -o -name '*.h')

# Default target
all: $(TARGET)

# Link the executable
$(TARGET): $(CXX_OBJS)
	@mkdir -p $(dir $@)
	$(CC) -o $@ $^ $(LDFLAGS)

# Compile each .cpp to .o, generate dependency info
$(BUILD)/%.o: $(SRC)/%.cpp
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# Include the dependency files (if exist)
-include $(CXX_DEPS)

# Run the built program
run: $(TARGET)
	./$(TARGET)

# Clean build artifacts
clean:
	rm -rf $(BUILD)
