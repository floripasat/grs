TARGET=libngham.a

ifndef BUILD_DIR
	BUILD_DIR=.
endif

CC=gcc
CFLAGS=-c -o

$(BUILD_DIR)/$(TARGET): $(BUILD_DIR)/ccsds_scrambler.o $(BUILD_DIR)/crc_ccitt.o $(BUILD_DIR)/fec.o $(BUILD_DIR)/ngham.o $(BUILD_DIR)/ngham_extension.o $(BUILD_DIR)/ngham_packets.o $(BUILD_DIR)/platform.o
	ar rcs $@ $^

$(BUILD_DIR)/ccsds_scrambler.o: ngham/ccsds_scrambler.c ngham/ccsds_scrambler.h
	$(CC) $(CFLAGS) $@ $<

$(BUILD_DIR)/crc_ccitt.o: ngham/crc_ccitt.c ngham/crc_ccitt.h
	$(CC) $(CFLAGS) $@ $<

$(BUILD_DIR)/fec.o: ngham/fec.c ngham/fec.h
	$(CC) $(CFLAGS) $@ $<

$(BUILD_DIR)/ngham.o: ngham/ngham.c ngham/ngham.h
	$(CC) $(CFLAGS) $@ $<

$(BUILD_DIR)/ngham_extension.o: ngham/ngham_extension.c ngham/ngham_extension.h
	$(CC) $(CFLAGS) $@ $<

$(BUILD_DIR)/ngham_packets.o: ngham/ngham_packets.c ngham/ngham_packets.h
	$(CC) $(CFLAGS) $@ $<

$(BUILD_DIR)/platform.o: ngham/platform/platform.c ngham/platform/platform.h
	$(CC) $(CFLAGS) $@ $<

clean:
	rm $(BUILD_DIR)/*.o

