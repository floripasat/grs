TARGET=src

ifndef BUILD_DIR
	BUILD_DIR=.
endif

CXX=g++
LIBS=../
FLAGS=-std=c++11 -I$(LIBS)
GTKMM_FLAGS=`pkg-config --cflags --libs gtkmm-3.0`

all: $(BUILD_DIR)/main.o $(BUILD_DIR)/aux.o $(BUILD_DIR)/fsat-pkt-ana.o $(BUILD_DIR)/log.o $(BUILD_DIR)/uart.o $(BUILD_DIR)/protocol_statistic.o
	

$(BUILD_DIR)/main.o: main.cpp
	$(CXX) $(GTKMM_FLAGS) $(FLAGS) -c $< -o $@

$(BUILD_DIR)/aux.o: aux.cpp aux.hpp
	$(CXX) $(GTKMM_FLAGS) $(FLAGS) -c $< -o $@

$(BUILD_DIR)/fsat-pkt-ana.o: fsat-pkt-ana.cpp fsat-pkt-ana.h
	$(CXX) $(GTKMM_FLAGS) $(FLAGS) -c $< -o $@

$(BUILD_DIR)/log.o: log.cpp log.h
	$(CXX) $(GTKMM_FLAGS) $(FLAGS) -c $< -o $@

$(BUILD_DIR)/uart.o: uart.cpp uart.h
	$(CXX) $(GTKMM_FLAGS) $(FLAGS) -c $< -o $@

$(BUILD_DIR)/protocol_statistic.o: protocol_statistic.cpp protocol_statistic.h
	$(CXX) $(GTKMM_FLAGS) $(FLAGS) -c $< -o $@

#$(BUILD_DIR)/beacon_data.o: beacon_data.cpp beacon_data.h
#	$(CXX) $(GTKMM_FLAGS) $(FLAGS) -c $< -o $@

clean:
	rm $(BUILD_DIR)/*.o

