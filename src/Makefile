TARGET=src

ifndef BUILD_DIR
	BUILD_DIR=.
endif

CXX=g++
LIBS=../
FLAGS=-std=c++14 -I$(LIBS)
GTKMM_FLAGS=`pkg-config --cflags --libs gtkmm-3.0`

all: $(BUILD_DIR)/main.o $(BUILD_DIR)/aux.o $(BUILD_DIR)/fsat-grs.o $(BUILD_DIR)/log.o $(BUILD_DIR)/uart.o $(BUILD_DIR)/protocol_statistic.o $(BUILD_DIR)/packet_data.o $(BUILD_DIR)/beacon_data_old.o $(BUILD_DIR)/telemetry_data.o $(BUILD_DIR)/event_log.o $(BUILD_DIR)/packets.o $(BUILD_DIR)/ngham_pkts.o $(BUILD_DIR)/ax25_pkts.o $(BUILD_DIR)/sha256.o $(BUILD_DIR)/read_log.o $(BUILD_DIR)/uplink_event.o $(BUILD_DIR)/payload_x_upload.o $(BUILD_DIR)/udp_decoder.o $(BUILD_DIR)/udp_server.o $(BUILD_DIR)/bit_buffer.o $(BUILD_DIR)/byte_buffer.o $(BUILD_DIR)/ngham_plus.o $(BUILD_DIR)/packet_buffer.o $(BUILD_DIR)/packet_sniffer.o $(BUILD_DIR)/sync_word.o $(BUILD_DIR)/payload.o $(BUILD_DIR)/ax25.o $(BUILD_DIR)/beacon.o
	$(MAKE) BUILD_DIR=$(BUILD_DIR) -C packets

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

$(BUILD_DIR)/beacon_data_old.o: beacon_data_old.cpp beacon_data_old.h
	$(CXX) $(GTKMM_FLAGS) $(FLAGS) -c $< -o $@

$(BUILD_DIR)/telemetry_data.o: telemetry_data.cpp telemetry_data.h
	$(CXX) $(GTKMM_FLAGS) $(FLAGS) -c $< -o $@

$(BUILD_DIR)/event_log.o: event_log.cpp event_log.h
	$(CXX) $(GTKMM_FLAGS) $(FLAGS) -c $< -o $@

$(BUILD_DIR)/packets.o: packets.cpp packets.h
	$(CXX) $(GTKMM_FLAGS) $(FLAGS) -c $< -o $@

$(BUILD_DIR)/ngham_pkts.o: ngham_pkts.cpp ngham_pkts.h
	$(CXX) $(GTKMM_FLAGS) $(FLAGS) -c $< -o $@

$(BUILD_DIR)/ax25_pkts.o: ax25_pkts.cpp ax25_pkts.h
	$(CXX) $(GTKMM_FLAGS) $(FLAGS) -c $< -o $@

$(BUILD_DIR)/sha256.o: sha256.cpp sha256.h
	$(CXX) $(GTKMM_FLAGS) $(FLAGS) -c $< -o $@

$(BUILD_DIR)/read_log.o: read_log.cpp read_log.h
	$(CXX) $(GTKMM_FLAGS) $(FLAGS) -c $< -o $@

$(BUILD_DIR)/uplink_event.o: uplink_event.cpp uplink_event.h
	$(CXX) $(GTKMM_FLAGS) $(FLAGS) -c $< -o $@

$(BUILD_DIR)/payload_x_upload.o: payload_x_upload.cpp payload_x_upload.h
	$(CXX) $(GTKMM_FLAGS) $(FLAGS) -c $< -o $@

$(BUILD_DIR)/udp_decoder.o: udp_decoder.cpp udp_decoder.h
	$(CXX) $(GTKMM_FLAGS) $(FLAGS) -c $< -o $@

$(BUILD_DIR)/udp_server.o: udp_server.cpp udp_server.h
	$(CXX) $(GTKMM_FLAGS) $(FLAGS) -c $< -o $@

$(BUILD_DIR)/bit_buffer.o: bit_buffer.cpp bit_buffer.h
	$(CXX) $(GTKMM_FLAGS) $(FLAGS) -c $< -o $@

$(BUILD_DIR)/byte_buffer.o: byte_buffer.cpp byte_buffer.h
	$(CXX) $(GTKMM_FLAGS) $(FLAGS) -c $< -o $@

$(BUILD_DIR)/ngham_plus.o: ngham_plus.cpp ngham_plus.h
	$(CXX) $(GTKMM_FLAGS) $(FLAGS) -c $< -o $@

$(BUILD_DIR)/packet_sniffer.o: packet_sniffer.cpp packet_sniffer.h
	$(CXX) $(GTKMM_FLAGS) $(FLAGS) -c $< -o $@

$(BUILD_DIR)/packet_buffer.o: packet_buffer.cpp packet_buffer.h
	$(CXX) $(GTKMM_FLAGS) $(FLAGS) -c $< -o $@

$(BUILD_DIR)/sync_word.o: sync_word.cpp sync_word.h
	$(CXX) $(GTKMM_FLAGS) $(FLAGS) -c $< -o $@

$(BUILD_DIR)/payload.o: payload.cpp payload.h
	$(CXX) $(GTKMM_FLAGS) $(FLAGS) -c $< -o $@

$(BUILD_DIR)/ax25.o: ax25.cpp ax25.h
	$(CXX) $(GTKMM_FLAGS) $(FLAGS) -c $< -o $@

$(BUILD_DIR)/beacon.o: beacon.cpp beacon.h
	$(CXX) $(GTKMM_FLAGS) $(FLAGS) -c $< -o $@

clean:
	rm $(BUILD_DIR)/*.o

