# html++ Makefile

# Tools
CC      = clang++

# Project Structure
SRC     = src
BUILD   = build
TARGET  = $(BUILD)/libhtml++.so

# Install locations
PREFIX       ?= /usr/local
INCLUDEDIR   = $(PREFIX)/include/html++
LIBDIR       = $(PREFIX)/lib

# Compiler flags
ifeq ($(DEBUG),1)
  CFLAGS = -Wall -Wextra -O0 -fPIC -std=c++20 -MMD -MP
else
  CFLAGS = -Wall -Wextra -O2 -fPIC -std=c++20 -MMD -MP
endif

LDFLAGS = -shared -pthread -lm

# Source & object files
CXX_SOURCES := $(shell find $(SRC) -name '*.cpp')
CXX_OBJS    := $(patsubst $(SRC)/%.cpp, $(BUILD)/%.o, $(CXX_SOURCES))
CXX_DEPS    := $(CXX_OBJS:.o=.d)

# Public headers
HEADERS := $(shell find $(SRC) -name '*.hpp')

# Default target: build the shared library
all: $(TARGET)

# Link the shared library
$(TARGET): $(CXX_OBJS)
	@mkdir -p $(dir $@)
	$(CC) -o $@ $^ $(LDFLAGS)

# Compile .cpp into .o
$(BUILD)/%.o: $(SRC)/%.cpp
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# Install library and headers
install: $(TARGET)
	@echo "Installing libhtml++.so to $(DESTDIR)$(LIBDIR)"
	install -d $(DESTDIR)$(LIBDIR)
	install -m 0755 $(TARGET) $(DESTDIR)$(LIBDIR)/libhtml++.so

	@echo "Installing headers to $(DESTDIR)$(INCLUDEDIR)..."
	install -d $(DESTDIR)$(INCLUDEDIR)
	find $(SRC) -name '*.hpp' -exec install -Dm 0644 {} $(DESTDIR)$(INCLUDEDIR)/{} \;

# Clean build artifacts
clean:
	rm -rf $(BUILD)

# Include auto-generated dependency files
-include $(CXX_DEPS)
