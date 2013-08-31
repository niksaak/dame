BUILD := Debug
BUILD_DIR := build
PROJECT_DIR := $(realpath $(shell pwd)/..)

MAKEFLAGS += --no-print-directory

.PHONY: all run make configure test check clean cleanse

all: make

run:
	$(BUILD_DIR)/dame

make: configure
	@$(MAKE) -C $(BUILD_DIR)

configure:
	@mkdir -p $(BUILD_DIR) && cd $(BUILD_DIR) && \
	  CC=clang cmake -DCMAKE_BUILD_TYPE=$(BUILD) ..

test:
	@$(BUILD_DIR)/checkall

check: test

clean:
	@make -C $(BUILD_DIR) clean

cleanse:
	@rm -rf $(BUILD_DIR)/*

