V=1
SOURCE_DIR=src
BUILD_DIR=build
include $(N64_INST)/include/n64.mk

all: hello.z64
.PHONY: all

SRCS := $(wildcard $(SOURCE_DIR)/*.cpp) \
        $(wildcard $(SOURCE_DIR)/*/*.cpp)

OBJS := $(patsubst $(SOURCE_DIR)/%.cpp, $(BUILD_DIR)/%.o, \
         $(patsubst $(SOURCE_DIR)/*/%.cpp, $(BUILD_DIR)/%.o, $(SRCS)))



hello.z64: N64_ROM_TITLE="Hello World"
hello.z64: $(BUILD_DIR)/hello.dfs

$(BUILD_DIR)/hello.dfs: $(wildcard filesystem/*)
$(BUILD_DIR)/hello.elf: $(OBJS)

clean:
	rm -f $(BUILD_DIR)/* *.z64
.PHONY: clean

-include $(wildcard $(BUILD_DIR)/*.d)