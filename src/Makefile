TARGET=src

ifndef BUILD_DIR
	BUILD_DIR=.
endif

CXX=g++
LIBS=../
FLAGS=-std=c++11 -I$(LIBS)
GTKMM_FLAGS=`pkg-config --cflags --libs gtkmm-3.0`

all: $(BUILD_DIR)/main.o $(BUILD_DIR)/aux.o $(BUILD_DIR)/fsat-grs.o $(BUILD_DIR)/log.o $(BUILD_DIR)/uart.o $(BUILD_DIR)/protocol_statistic.o $(BUILD_DIR)/packet_data.o $(BUILD_DIR)/beacon_data.o $(BUILD_DIR)/telemetry_data.o $(BUILD_DIR)/event_log.o $(BUILD_DIR)/packets.o $(BUILD_DIR)/ngham_pkts.o $(BUILD_DIR)/data_processing.o $(BUILD_DIR)/ax25_pkts.o $(BUILD_DIR)/sha256.o $(BUILD_DIR)/read_log.o $(BUILD_DIR)/uplink_event.o

$(BUILD_DIR)/main.o: main.cpp
	$(CXX) $(GTKMM_FLAGS) $(FLAGS) -c $< -o $@

$(BUILD_DIR)/aux.o: aux.cpp aux.hpp
	$(CXX) $(GTKMM_FLAGS) $(FLAGS) -c $< -o $@

$(BUILD_DIR)/fsat-grs.o: fsat-grs.cpp fsat-grs.h
	$(CXX) $(GTKMM_FLAGS) $(FLAGS) -c $< -o $@

$(BUILD_DIR)/log.o: log.cpp log.h
	$(CXX) $(GTKMM_FLAGS) $(FLAGS) -c $< -o $@

$(BUILD_DIR)/uart.o: uart.cpp uart.h
	$(CXX) $(GTKMM_FLAGS) $(FLAGS) -c $< -o $@

$(BUILD_DIR)/protocol_statistic.o: protocol_statistic.cpp protocol_statistic.h
	$(CXX) $(GTKMM_FLAGS) $(FLAGS) -c $< -o $@

$(BUILD_DIR)/packet_data.o: packet_data.cpp packet_data.h
	$(CXX) $(GTKMM_FLAGS) $(FLAGS) -c $< -o $@

$(BUILD_DIR)/beacon_data.o: beacon_data.cpp beacon_data.h
	$(CXX) $(GTKMM_FLAGS) $(FLAGS) -c $< -o $@

$(BUILD_DIR)/telemetry_data.o: telemetry_data.cpp telemetry_data.h
	$(CXX) $(GTKMM_FLAGS) $(FLAGS) -c $< -o $@

$(BUILD_DIR)/event_log.o: event_log.cpp event_log.h
	$(CXX) $(GTKMM_FLAGS) $(FLAGS) -c $< -o $@

$(BUILD_DIR)/packets.o: packets.cpp packets.h
	$(CXX) $(GTKMM_FLAGS) $(FLAGS) -c $< -o $@

$(BUILD_DIR)/ngham_pkts.o: ngham_pkts.cpp ngham_pkts.h
	$(CXX) $(GTKMM_FLAGS) $(FLAGS) -c $< -o $@

$(BUILD_DIR)/data_processing.o: data_processing.cpp data_processing.hpp
	$(CXX) $(GTKMM_FLAGS) $(FLAGS) -c $< -o $@

$(BUILD_DIR)/ax25_pkts.o: ax25_pkts.cpp ax25_pkts.h
	$(CXX) $(GTKMM_FLAGS) $(FLAGS) -c $< -o $@

$(BUILD_DIR)/sha256.o: sha256.cpp sha256.h
	$(CXX) $(GTKMM_FLAGS) $(FLAGS) -c $< -o $@

$(BUILD_DIR)/read_log.o: read_log.cpp read_log.h
	$(CXX) $(GTKMM_FLAGS) $(FLAGS) -c $< -o $@

$(BUILD_DIR)/uplink_event.o: uplink_event.cpp uplink_event.h
	$(CXX) $(GTKMM_FLAGS) $(FLAGS) -c $< -o $@

clean:
	rm $(BUILD_DIR)/*.o

