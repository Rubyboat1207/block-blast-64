V=1
SOURCE_DIR=src
BUILD_DIR=build
RESOURCES_DIR=assets
AUDIO_DIR=$(RESOURCES_DIR)/audio
WAV_FILES=$(wildcard $(AUDIO_DIR)/*.wav)
XM_FILES=$(wildcard $(AUDIO_DIR)/*.xm)
YM_FILES=$(wildcard $(AUDIO_DIR)/*.ym)
AUDIO_FILES=$(WAV_FILES) $(XM_FILES) $(YM_FILES)

AUDIO_OUTPUT_FILES=$(subst resources/audio,filesystem,$(WAV_FILES:.wav=.wav64) $(XM_FILES:.xm=.xm64) $(YM_FILES:.ym=.ym64))

include $(N64_INST)/include/n64.mk

all: BlockBlast64.z64
.PHONY: all

SRCS := $(wildcard $(SOURCE_DIR)/*.cpp) \
        $(wildcard $(SOURCE_DIR)/*/*.cpp)

OBJS := $(patsubst $(SOURCE_DIR)/%.cpp, $(BUILD_DIR)/%.o, \
         $(patsubst $(SOURCE_DIR)/*/%.cpp, $(BUILD_DIR)/%.o, $(SRCS)))



BlockBlast64.z64: N64_ROM_TITLE="Block Blast 64"
BlockBlast64.z64: $(BUILD_DIR)/BlockBlast64.dfs
BlockBlast64.z64: N64_ED64ROMCONFIGFLAGS=-w eeprom4k

$(AUDIO_OUTPUT_FILES): $(AUDIO_FILES)
	audioconv64 -o filesystem/audio/ $(AUDIO_DIR)/$(subst .ym64,.ym,$(subst .xm64,.xm,$(subst .wav64,.wav,$(notdir $@))))


$(BUILD_DIR)/BlockBlast64.dfs: $(wildcard filesystem/*) $(AUDIO_OUTPUT_FILES)
$(BUILD_DIR)/BlockBlast64.elf: $(OBJS)

clean:
	rm -Rf $(BUILD_DIR)/* *.z64
.PHONY: clean

-include $(wildcard $(BUILD_DIR)/*.d)