# short makefile for me to be able to use :make from vim

CC := clang
CXX := clang
BUILD_DIR := build

.PHONY: all run make configure clean

all: make

run:
	$(BUILD_DIR)/bin/dame

make: configure
	$(MAKE) -C $(BUILD_DIR)

configure:
	@mkdir -p $(BUILD_DIR) && cd $(BUILD_DIR) && \
	  CC=$(CC) CXX=$(CXX) cmake ..

clean:
	@if   [ -a $(CMAKE_CACHE) ];        \
	 then make -C $(BUILD_DIR) clean && \
	      rm -rf $(BUILD_DIR)/* ;       \
	 fi

