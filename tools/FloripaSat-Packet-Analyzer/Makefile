SOURCE=main.cpp
TARGET=fsat-grs

ifndef BUILD_DIR
	BUILD_DIR=build
endif

CXX=g++
CXXFLAGS=-std=c++11
GTKMM_FLAGS=`pkg-config --cflags --libs gtkmm-3.0`

all:
	mkdir -p $(BUILD_DIR)
	$(MAKE) BUILD_DIR=$(CURDIR)/$(BUILD_DIR) -C libs
	$(MAKE) BUILD_DIR=$(CURDIR)/$(BUILD_DIR) -C src
	$(CXX) $(CXXFLAGS) $(BUILD_DIR)/main.o $(BUILD_DIR)/aux.o $(BUILD_DIR)/fsat-pkt-ana.o $(BUILD_DIR)/log.o $(BUILD_DIR)/uart.o $(BUILD_DIR)/protocol_statistic.o $(BUILD_DIR)/libngham.a -o $(BUILD_DIR)/$(TARGET).x $(GTKMM_FLAGS)
	mkdir -p $(BUILD_DIR)/glade
	cp gui/MainWindow.glade $(BUILD_DIR)/glade/
	cp img/icon.png $(BUILD_DIR)/

clean:
	rm -r $(BUILD_DIR)

