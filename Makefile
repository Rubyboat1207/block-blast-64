V=1
SOURCE_DIR=src
BUILD_DIR=build
include $(N64_INST)/include/n64.mk

all: BlockBlast64.z64
.PHONY: all

SRCS := $(wildcard $(SOURCE_DIR)/*.cpp) \
        $(wildcard $(SOURCE_DIR)/*/*.cpp)

OBJS := $(patsubst $(SOURCE_DIR)/%.cpp, $(BUILD_DIR)/%.o, \
         $(patsubst $(SOURCE_DIR)/*/%.cpp, $(BUILD_DIR)/%.o, $(SRCS)))



BlockBlast64.z64: N64_ROM_TITLE="Block Blast 64"
BlockBlast64.z64: $(BUILD_DIR)/BlockBlast64.dfs

$(BUILD_DIR)/BlockBlast64.dfs: $(wildcard filesystem/*)
$(BUILD_DIR)/BlockBlast64.elf: $(OBJS)

clean:
	rm -Rf $(BUILD_DIR)/* *.z64
.PHONY: clean

-include $(wildcard $(BUILD_DIR)/*.d)