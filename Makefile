SOURCE=main.cpp
TARGET=fsat-grs

ifndef BUILD_DIR
	BUILD_DIR=build
endif

CXX=g++
CXXFLAGS=-std=c++14
GTKMM_FLAGS=`pkg-config --cflags --libs gtkmm-3.0`

all:
	mkdir -p $(BUILD_DIR)
	$(MAKE) BUILD_DIR=$(CURDIR)/$(BUILD_DIR) -C libs
	$(MAKE) BUILD_DIR=$(CURDIR)/$(BUILD_DIR) -C src
	$(CXX) $(CXXFLAGS) $(BUILD_DIR)/*.o $(BUILD_DIR)/*.a -o $(BUILD_DIR)/$(TARGET).x $(GTKMM_FLAGS)
	mkdir -p $(BUILD_DIR)/glade
	mkdir -p $(BUILD_DIR)/gnuradio
	mkdir -p $(BUILD_DIR)/matplotlib
	grcc gnuradio/gfsk_rx.grc -d $(BUILD_DIR)/gnuradio
	grcc gnuradio/gfsk_tx.grc -d $(BUILD_DIR)/gnuradio
	cp gui/fsat_grs_gui.glade $(BUILD_DIR)/glade/
	cp img/icon.png $(BUILD_DIR)/
	cp img/gpredict-icon.png $(BUILD_DIR)/
	cp img/gqrx-icon.png $(BUILD_DIR)/
	cp matplotlib/csv_plot.py $(BUILD_DIR)/matplotlib/
	cp src/*.csv $(BUILD_DIR)/

clean:
	rm $(BUILD_DIR)/*.o $(BUILD_DIR)/*.x $(BUILD_DIR)/*.a

