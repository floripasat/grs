SOURCE=main.cpp
TARGET=fsat-grs.x
BUILD_FOLDER=build

CPP=g++
CC=gcc
CPPFLAGS=-std=c++11 -c -o
CFLAGS=-c -o
GTKMM_FLAGS=`pkg-config --cflags --libs gtkmm-3.0`

$(TARGET): main.o uart.o aux.o signals.o global_var.o pkt_handler.o error.o log.o libngham.a
	$(CPP) $^ -o $@ $(GTKMM_FLAGS)
#	rm *.o

main.o: main.cpp
	$(CPP) $(CPPFLAGS) $@ $< $(GTKMM_FLAGS)

uart.o: src/uart.cpp inc/uart.h
	$(CPP) -c $< -o $@

aux.o: src/aux.cpp inc/aux.hpp
	$(CPP) $(CPPFLAGS) $@ $< $(GTKMM_FLAGS)

signals.o: src/signals.cpp inc/signals.h
	$(CPP) $(CPPFLAGS) $@ $< $(GTKMM_FLAGS)

global_var.o: src/global_var.cpp inc/global_var.h
	$(CPP) $(CPPFLAGS) $@ $< $(GTKMM_FLAGS)

pkt_handler.o: src/pkt_handler.cpp inc/pkt_handler.h
	$(CPP) $(CPPFLAGS) $@ $< $(GTKMM_FLAGS)

error.o: src/error.cpp inc/error.h
	$(CPP) $(CPPFLAGS) $@ $< $(GTKMM_FLAGS)

log.o: src/log.cpp inc/log.h
	$(CPP) $(CPPFLAGS) $@ $< $(GTKMM_FLAGS)

libngham.a: ccsds_scrambler.o crc_ccitt.o fec.o ngham.o ngham_extension.o ngham_packets.o platform.o
	ar rcs $@ $^

ccsds_scrambler.o: ngham/ccsds_scrambler.c ngham/ccsds_scrambler.h
	$(CC) $(CFLAGS) $@ $<

crc_ccitt.o: ngham/crc_ccitt.c ngham/crc_ccitt.h
	$(CC) $(CFLAGS) $@ $<

fec.o: ngham/fec.c ngham/fec.h
	$(CC) $(CFLAGS) $@ $<

ngham.o: ngham/ngham.c ngham/ngham.h
	$(CC) $(CFLAGS) $@ $<

ngham_extension.o: ngham/ngham_extension.c ngham/ngham_extension.h
	$(CC) $(CFLAGS) $@ $<

ngham_packets.o: ngham/ngham_packets.c ngham/ngham_packets.h
	$(CC) $(CFLAGS) $@ $<

platform.o: ngham/platform/platform.c ngham/platform/platform.h
	$(CC) $(CFLAGS) $@ $<

clean:
	rm -f *.x *.o *.a $(TARGET) $(BUILD_FOLDER)/*.o $(BUILD_FOLDER)/*.a

