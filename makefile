# short makefile for me to be able to use :make from vim

CC := clang
BUILD_DIR := build
CMAKE_CACHE := $(BUILD_DIR)/CMakeCache.txt

all: make

run:
	$(BUILD_DIR)/bin/dame

make: configure
	$(MAKE) -C $(BUILD_DIR)

configure: $(CMAKE_CACHE)

$(CMAKE_CACHE):
	@mkdir -p $(BUILD_DIR) && cd $(BUILD_DIR) && CC=$(CC) cmake ..

clean:
	@if   [ -a $(CMAKE_CACHE) ];        \
	 then make -C $(BUILD_DIR) clean && \
	      rm -rf $(BUILD_DIR)/* ;       \
	 fi

