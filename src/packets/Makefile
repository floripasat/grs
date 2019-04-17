ifndef BUILD_DIR
	BUILD_DIR=.
endif

CXX=g++
LIBS=../
FLAGS=-std=c++14 -I$(LIBS)

all: $(BUILD_DIR)/packet.o $(BUILD_DIR)/beacon_data.o $(BUILD_DIR)/obdh_data.o $(BUILD_DIR)/eps_data.o $(BUILD_DIR)/ttc_data.o $(BUILD_DIR)/downlink_data.o $(BUILD_DIR)/ping_reply.h $(BUILD_DIR)/hibernation_feedback.o $(BUILD_DIR)/message_broadcast.o $(BUILD_DIR)/payload_x_status.o

$(BUILD_DIR)/packet.o: packet.cpp packet.h
	$(CXX) $(FLAGS) -c $< -o $@

$(BUILD_DIR)/beacon_data.o: beacon_data.cpp beacon_data.h
	$(CXX) $(FLAGS) -c $< -o $@

$(BUILD_DIR)/obdh_data.o: obdh_data.cpp obdh_data.h
	$(CXX) $(FLAGS) -c $< -o $@

$(BUILD_DIR)/eps_data.o: eps_data.cpp eps_data.h
	$(CXX) $(FLAGS) -c $< -o $@

$(BUILD_DIR)/ttc_data.o: ttc_data.cpp ttc_data.h
	$(CXX) $(FLAGS) -c $< -o $@

$(BUILD_DIR)/downlink_data.o: downlink_data.cpp downlink_data.h
	$(CXX) $(FLAGS) -c $< -o $@

$(BUILD_DIR)/ping_reply.o: ping_reply.cpp ping_reply.h
	$(CXX) $(FLAGS) -c $< -o $@

$(BUILD_DIR)/hibernation_feedback.o: hibernation_feedback.cpp hibernation_feedback.h
	$(CXX) $(FLAGS) -c $< -o $@

$(BUILD_DIR)/message_broadcast.o: message_broadcast.cpp message_broadcast.h
	$(CXX) $(FLAGS) -c $< -o $@

$(BUILD_DIR)/payload_x_status.o: payload_x_status.cpp payload_x_status.h
	$(CXX) $(FLAGS) -c $< -o $@

clean:
	rm $(BUILD_DIR)/*.o

