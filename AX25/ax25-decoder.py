#!/usr/bin/env python
# -*- coding: utf-8 -*-

#
# ax25-decoder.py
#
# Copyright (C) 2017, Universidade Federal de Santa Catarina
# 
# This file is part of FloripaSat-GRS.
# 
# FloripaSat-GRS is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
# 
# FloripaSat-GRS is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
# 
# You should have received a copy of the GNU General Public License
# along with FloripaSat-GRS.  If not, see <http://www.gnu.org/licenses/>.
# 
# 

__author__      = "Gabriel Mariano Marcelino"
__copyright__   = "gabriel.mm8@gmail.com"
__credits__     = ["Gabriel Mariano Marcelino"]
__license__     = "GPL3"
__version__     = "1.0-dev"
__maintaner__   = "Gabriel Mariano Marcelino"
__email__       = "gabriel.mm8@gmail.com"
__status__      = "Development"

import pickle


def crc16(poly, initial_value, data):
    table = list()
    for i in range(256):
        crc_t = 0
        c = i
        c = c << 8
        for j in range(8):
            if (crc_t ^ c) & 0x8000:
                crc_t = (crc_t << 1) ^ poly
            else:
                crc_t = crc_t << 1
            c = c << 1
        table.append(crc_t)
    
    crc = initial_value
    for c in data:
        if type(data) is str:
            c = ord(c)
        cc = 0xFF & c
        tmp = (crc >> 8) ^ cc
        crc = (crc << 8) ^ table[tmp & 0xFF]
        crc = crc & 0xFFFF
    return crc


def Bytes2String(f):
    bin_string = str()

    # Converts the binary file to a string of ones and zeros
    byte = f.read(1)
    while byte != "":
        if byte == '\x00':
            bin_string += '0'
        elif byte == '\x01':
            bin_string += '1'
        byte = f.read(1)
    return bin_string
    

def FindPackets(bin_stream, bin_sync_word):
    # Find packets in the binary string (using the sync. word as trigger)
    sync_word_buf   = str()
    get_pkt         = False
    byte_buf        = str()
    pkt_buf         = str()
    packets         = list()
    for b in bin_stream:
        if get_pkt:
            byte_buf += b
            pkt_buf += b
            if len(byte_buf) == 8:
                if byte_buf == "01111110":
                    if len(pkt_buf) >= 28*8:    # TODO: Implement Bit Stuffing <<<<<<<<<<<<<<<
                        packets.append(pkt_buf)
                        pkt_buf = ""
                        get_pkt = False
                byte_buf = byte_buf[1:]
        sync_word_buf += b
        if len(sync_word_buf) == len(bin_sync_word):
            if sync_word_buf == bin_sync_word:
                get_pkt = True
                pkt_buf = ""
                byte_buf = ""
            sync_word_buf = sync_word_buf[1:]
    return packets
    

def CheckPacket(packet):
    if len(packet) >= 29*8:
        pkt = packet[17*8:-24]
        pkt_bytes = list()
        for i in xrange(0, len(pkt), 8):
            pkt_bytes.append(int(pkt[i:i+8], 2))
        if packet[-24:-8] == str(bin(crc16(0x1021, 0x0000, pkt_bytes))[2:].zfill(16)):
            return True
        else:
            return False
    else:
        return False
    

def main(args):
    path = str()
    if len(args) == 1:
        path = "/code/gnuradio/bin_data.bin"
    else:
        path = args[1]
    
#****************************************************
#-- INPUTS ------------------------------------------
#****************************************************
    preamble_byte       = 0xAA
    preamble_size       = 4
    sync_bytes          = [0x04,0x08,0x0F,0x10]
    print_bin_str       = False
    print_packets       = False
    print_pkt_bytes     = True
    print_statistics    = True
    save_results        = False
#****************************************************

    preamble        = preamble_size*str(bin(preamble_byte))[2:]
    sync_word       = str()
    for i in sync_bytes:
        sync_word += str(bin(i)[2:].zfill(8))

    f = open(path, "rb")
    bin_stream = Bytes2String(f)
    f.close()
    
    # Prints the binary string
    if print_bin_str:
        print "\n###################################"
        print "-- Output -------------------------"
        print "###################################"
        print bin_stream
        print "###################################"
        if save_results:
            bin_file = open("bin_stream.txt", "w")
            bin_file.write(bin_stream)
            bin_file.close()

    packets = FindPackets(bin_stream, sync_word)

    # Prints the binary packets
    if print_packets:
        print "\n####################################"
        print "-- Packets -------------------------"
        print "####################################"
        print packets
        print "###################################"
        if save_results:
            bin_pkts_file = open("bin_pkts.txt", "w")
            pickle.dump(packets, bin_pkts_file)
            bin_pkts_file.close()
    
    # Split packets into bytes
    valid_packets = list()
    packet_counter = 0
    if print_pkt_bytes:
        print "\n###################################"
        print "-- Packets (Bytes) ----------------"
        print "###################################"
        for p in packets:
            print "\n----------------------------------"
            print " Packet " + str(packet_counter) + ":"
            print "----------------------------------"
            print "Binary\t\tHex.\tASCII"
            print "----------------------------------"
            i = 0
            j = 0
            byte = str()
            while j < len(p):
                byte += p[j]
                i += 1
                if i == 8:
                    hex_byte = hex(int(byte, 2))
                    ascii_char = str()
                    try:
                        ascii_char = str(hex(int(byte,2)))[2:].decode("hex")
                    except:
                        ascii_char = "Non char"
                    print byte + "\t" + str(hex_byte) + "\t" + ascii_char
                    byte = ""
                    i = 0
                j += 1
            print "----------------------------------"
            if CheckPacket(p):
                print "Result: Valid"
                valid_packets.append(packet_counter)
            else:
                print "Result: Invalid"
            
            packet_counter += 1
        print "###################################"
    
    if print_statistics:
        if not print_pkt_bytes:
            for p in packets:
                if CheckPacket(p):
                    valid_packets.append(packet_counter)
                packet_counter += 1
            
        print "\n###################################"
        print "-- Statistics ---------------------"
        print "###################################"
        print "Number of packets:\t\t" + str(packet_counter)
        print "Valid packets:\t\t\t" + str(valid_packets)
        print "Number of valid packets:\t" + str(len(valid_packets))
        print "Number of lost packets:\t\t" + str(packet_counter-len(valid_packets))
        print "Lost percentage:\t\t" + str(100.0 - 100.0*len(valid_packets)/packet_counter) if packet_counter > 0 else "0"
        print "###################################"
    
    return 0

if __name__ == '__main__':
    import sys
    sys.exit(main(sys.argv))
