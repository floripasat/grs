TARGET=libngham
TARGET_DIR=ngham

CC=gcc
CFLAGS=-c -o

ifndef BUILD_DIR
	OUTPUT_DIR=.
else
	OUTPUT_DIR=$(BUILD_DIR)/$(TARGET_DIR)
endif

$(TARGET).a: $(OUTPUT_DIR)/ccsds_scrambler.o $(OUTPUT_DIR)/crc_ccitt.o $(OUTPUT_DIR)/fec.o $(OUTPUT_DIR)/ngham.o $(OUTPUT_DIR)/ngham_extension.o $(OUTPUT_DIR)/ngham_packets.o $(OUTPUT_DIR)/platform.o
	ar rcs $(OUTPUT_DIR)/$@ $^

$(OUTPUT_DIR)/ccsds_scrambler.o: ccsds_scrambler.c ccsds_scrambler.h
	mkdir -p $(OUTPUT_DIR)
	$(CC) $(CFLAGS) $@ $<

$(OUTPUT_DIR)/crc_ccitt.o: crc_ccitt.c crc_ccitt.h
	$(CC) $(CFLAGS) $@ $<

$(OUTPUT_DIR)/fec.o: fec.c fec.h
	$(CC) $(CFLAGS) $@ $<

$(OUTPUT_DIR)/ngham.o: ngham.c ngham.h
	$(CC) $(CFLAGS) $@ $<

$(OUTPUT_DIR)/ngham_extension.o: ngham_extension.c ngham_extension.h
	$(CC) $(CFLAGS) $@ $<

$(OUTPUT_DIR)/ngham_packets.o: ngham_packets.c ngham_packets.h
	$(CC) $(CFLAGS) $@ $<

$(OUTPUT_DIR)/platform.o: platform/platform.c platform/platform.h
	$(CC) $(CFLAGS) $@ $<

clean:
	rm $(OUTPUT_DIR)/*.o $(OUTPUT_DIR)/*.a
