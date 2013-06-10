CC := clang
CXX := clang
BUILD := Debug
BUILD_DIR := build
PROJECT_DIR := $(realpath $(shell pwd)/..)

MAKEFLAGS += --no-print-directory

.PHONY: all run make configure clean cleanse

all: make

run:
	$(BUILD_DIR)/bin/dame

make: configure
	@$(MAKE) -C $(BUILD_DIR)

configure:
	@mkdir -p $(BUILD_DIR) && cd $(BUILD_DIR) && \
	  CC=$(CC) CXX=$(CXX) \
	  cmake -DCMAKE_BUILD_TYPE=$(BUILD) \
	        -DCMAKE_PREFIX_PATH=$(PROJECT_DIR) \
	        -DBUILD_DEMOS=OFF -DBUILD_SHARED=OFF -DINSTALL_STATIC=OFF \
		..

clean:
	@make -C $(BUILD_DIR) clean

cleanse: clean
	@rm -rf $(BUILD_DIR)/*

