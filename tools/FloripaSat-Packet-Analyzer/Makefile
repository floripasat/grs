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
	$(CXX) $(CXXFLAGS) $(BUILD_DIR)/*.o $(BUILD_DIR)/*.a -o $(BUILD_DIR)/$(TARGET).x $(GTKMM_FLAGS)
	mkdir -p $(BUILD_DIR)/glade
	mkdir -p $(BUILD_DIR)/gnuradio
	cp gui/MainWindow.glade $(BUILD_DIR)/glade/
	cp img/icon.png $(BUILD_DIR)/
	cp gnuradio/fsat_grs.py $(BUILD_DIR)/gnuradio/

clean:
	rm $(BUILD_DIR)/*.o $(BUILD_DIR)/*.x $(BUILD_DIR)/*.a

