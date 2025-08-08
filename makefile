CC      = clang++

SRC     = src
BUILD   = build
TARGET  = $(BUILD)/libhtml++.so

PREFIX       ?= /usr/local
INCLUDEDIR   = $(DESTDIR)$(PREFIX)/include/html++
LIBDIR       = $(DESTDIR)$(PREFIX)/lib

ifeq ($(DEBUG),1)
  CFLAGS = -Wall -Wextra -O0 -g -fPIC -std=c++20 -MMD -MP
else
  CFLAGS = -Wall -Wextra -O2 -fPIC -std=c++20 -MMD -MP
endif

LDFLAGS = -shared -pthread -lm

CXX_SOURCES := $(shell find $(SRC) -name '*.cpp')
CXX_OBJS    := $(patsubst $(SRC)/%.cpp, $(BUILD)/%.o, $(CXX_SOURCES))
CXX_DEPS    := $(CXX_OBJS:.o=.d)
HEADERS     := $(shell find $(SRC) -name '*.hpp')

all: $(TARGET)

$(TARGET): $(CXX_OBJS)
	@mkdir -p $(dir $@)
	$(CC) -o $@ $^ $(LDFLAGS)

$(BUILD)/%.o: $(SRC)/%.cpp
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

install: $(TARGET)
	@echo "Installing libhtml++.so to $(LIBDIR)"
	install -d $(LIBDIR)
	install -m 0755 $(TARGET) $(LIBDIR)/libhtml++.so

	@echo "Installing headers to $(INCLUDEDIR)..."
	@find $(SRC) -name '*.hpp' | while read hdr; do \
		relpath=$${hdr#$(SRC)/}; \
		install -Dm 0644 "$$hdr" "$(INCLUDEDIR)/$$relpath"; \
	done

clean:
	rm -rf $(BUILD)

-include $(CXX_DEPS)
