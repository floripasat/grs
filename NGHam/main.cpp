/*
 * main.cpp
 * 
 * Copyright (C) 2017, Universidade Federal de Santa Catarina
 * 
 * This file is part of FloripaSat-GRS.
 * 
 * FloripaSat-GRS is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * FloripaSat-GRS is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with FloripaSat-GRS.  If not, see <http://www.gnu.org/licenses/>.
 * 
 */

#include <iostream>
#include <fstream>
#include <vector>
#include <stdint.h>

extern "C"
{
    #include "ngham/ngham.h"
}

#define DEFAULT_INPUT_FILE "/code/gnuradio/bin_data.bin"

#define SYNC_BYTES {0x5D, 0xE6, 0x2A, 0x7E}

using namespace std;

int main(int argc, char **argv)
{
    cout << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << endl;
    cout << "------------- NGHAM DECODER -------------" << endl;
    cout << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << endl;
    cout << endl;
    
    fstream fin;
    
    if (argc > 1)
        fin.open(argv[1], fstream::in);
    else
        fin.open(DEFAULT_INPUT_FILE, fstream::in);
    
    if (!fin.is_open())
    {
        cout << "Error opening the input file!" << endl;
        return -1;
    }
    
    unsigned int pkt_counter    = 0;
    unsigned int lost_pkts      = 0;
    
    // Generate a vector with the sync. bytes
    uint8_t sync_bytes_array[] = SYNC_BYTES;
    vector<uint8_t> sync_bytes(sync_bytes_array, sync_bytes_array + sizeof(sync_bytes_array)/sizeof(uint8_t));
    
    cout << "#########################################" << endl;
    cout << "-- Received data ------------------------" << endl;
    cout << "#########################################" << endl;
    
    cout << endl;
    
    cout << "------------------------------------" << endl;
    cout << "Packet\tPayload" << endl;
    cout << "------------------------------------" << endl;
    
    bool receive_pkt = false;
    vector<uint8_t> sync_bits_buffer;
    vector<uint8_t> byte_buffer;
    
    while(!fin.eof())
    {
        uint8_t byte;
        fin >> byte;
        if (!receive_pkt)
        {
            sync_bits_buffer.push_back(byte);
            if (sync_bits_buffer.size() == sync_bytes.size()*8)  // 1 byte = 8 bits
            {
                vector<uint8_t> sync_bytes_buffer(sync_bytes.size(), 0x00);
                unsigned int j = 7;
                unsigned int k = 0;
                for(unsigned int l=0;l<sync_bits_buffer.size();l++)
                {
                    sync_bytes_buffer[k] |= (uint8_t)(sync_bits_buffer[l] << j);
                    if (j == 0)
                    {
                        j = 7;
                        k++;
                    }
                    else
                    {
                        j--;
                    }
                }
                
                if (sync_bytes_buffer == sync_bytes)
                {
                    receive_pkt = true;
                    pkt_counter++;
                }
                
                sync_bits_buffer.erase(sync_bits_buffer.begin());
            }
        }
        else
        {
            byte_buffer.push_back(byte);
            if (byte_buffer.size() == 8)
            {
                uint8_t byte = 0x00;
                unsigned int k = 8-1;
                for(unsigned int j=0;j<byte_buffer.size();j++)
                {
                    byte |= (uint8_t)(byte_buffer[j] << k);
                    k--;
                }
                
                uint8_t data[256];
                uint8_t data_len;
                switch(ngham_decode(byte, data, &data_len))
                {
                    case PKT_CONDITION_OK:
                        receive_pkt = false;
                        cout << pkt_counter << "\t";
                        for(unsigned int j=0;j<data_len;j++)
                        {
                            cout << data[j];
                        }
                        cout << endl;
                        receive_pkt = false;
                        break;
                    case PKT_CONDITION_PREFAIL:
                        break;
                    case PKT_CONDITION_FAIL:
                        cout << pkt_counter << "\t";
                        cout << "ERROR!" << endl;
                        receive_pkt = false;
                        lost_pkts++;
                        break;
                }
                
                byte_buffer.clear();
            }
        }
    }
    
    fin.close();
    
    cout << "------------------------------------" << endl;
    
    cout << endl;
    cout << "#########################################" << endl;
    cout << "-- Results ------------------------------" << endl;
    cout << "#########################################" << endl;
    
    cout << "Number of packets:\t\t" << pkt_counter << endl;
    cout << "Number of valid packets:\t" << pkt_counter-lost_pkts << endl;
    cout << "Number of lost packets:\t\t" << lost_pkts << endl;
    float lost_percentage = 0;
    if (pkt_counter > 0)
        lost_percentage = lost_pkts*100.0/pkt_counter;
    cout << "Lost percentage:\t\t" << lost_percentage << endl;
    
    return 0;
}
