SOURCE=main.cpp
TARGET=fsat-grs
IMG_SRC=img/
GLADE_SRC=glade/

BUILD_DIR=build

CPP=g++
CC=gcc
CPPFLAGS=-std=c++11 -c -o
CFLAGS=-c -o
GTKMM_FLAGS=`pkg-config --cflags --libs gtkmm-3.0`

$(TARGET): $(BUILD_DIR)/main.o $(BUILD_DIR)/uart.o $(BUILD_DIR)/error.o $(BUILD_DIR)/log.o $(BUILD_DIR)/ngham/libngham.a
	$(CPP) $^ -o $(BUILD_DIR)/$@ $(GTKMM_FLAGS)
	cp -r $(IMG_SRC) $(BUILD_DIR)
	cp -r $(GLADE_SRC) $(BUILD_DIR)

$(BUILD_DIR)/main.o: src/main.cpp
	mkdir -p $(BUILD_DIR)
	$(CPP) $(CPPFLAGS) $@ $< $(GTKMM_FLAGS)

$(BUILD_DIR)/uart.o: src/uart.cpp src/uart.h
	$(CPP) -c $< -o $@

$(BUILD_DIR)/error.o: src/error.cpp src/error.h
	$(CPP) $(CPPFLAGS) $@ $< $(GTKMM_FLAGS)

$(BUILD_DIR)/log.o: src/log.cpp src/log.h
	$(CPP) $(CPPFLAGS) $@ $< $(GTKMM_FLAGS)

$(BUILD_DIR)/ngham/libngham.a:
	$(MAKE) BUILD_DIR=$(CURDIR)/$(BUILD_DIR) -C lib/ngham

clean:
	rm -r $(BUILD_DIR)

