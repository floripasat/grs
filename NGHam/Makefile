TARGET = ngham_decoder.x

$(TARGET): main.o libngham.a
	g++ $^ -o $@
	rm *.o

main.o: main.cpp
	g++ -c $< -o $@

libngham.a: ccsds_scrambler.o crc_ccitt.o ngham.o ngham_extension.o ngham_packets.o decode_rs_char.o encode_rs_char.o init_rs_char.o platform.o
	ar rcs $@ $^

ccsds_scrambler.o: ngham/ccsds_scrambler.c ngham/ccsds_scrambler.h
	gcc -c -o $@ $<

crc_ccitt.o: ngham/crc_ccitt.c ngham/crc_ccitt.h
	gcc -c -o $@ $<

ngham.o: ngham/ngham.c ngham/ngham.h
	gcc -c -o $@ $<

ngham_extension.o: ngham/ngham_extension.c ngham/ngham_extension.h
	gcc -c -o $@ $<

ngham_packets.o: ngham/ngham_packets.c ngham/ngham_packets.h
	gcc -c -o $@ $<

decode_rs_char.o: ngham/fec-3.0.1/decode_rs_char.c
	gcc -c -o $@ $<

encode_rs_char.o: ngham/fec-3.0.1/encode_rs_char.c
	gcc -c -o $@ $<

init_rs_char.o: ngham/fec-3.0.1/init_rs_char.c
	gcc -c -o $@ $<

platform.o: ngham/platform/platform.c ngham/platform/platform.h
	gcc -c -o $@ $<

clean:
	rm -f *.o *.a $(TARGET)
