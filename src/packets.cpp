/*
 * packets.cpp
 * 
 * Copyright (C) 2017-2019, Universidade Federal de Santa Catarina.
 * 
 * This file is part of FloripaSat-GRS.
 * 
 * FloripaSat-GRS is free software: you can redistribute it
 * and/or modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation, either version 3 of the
 * License, or (at your option) any later version.
 * 
 * FloripaSat-GRS is distributed in the hope that it will be
 * useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with FloripaSat-GRS. If not, see <http://www.gnu.org/licenses/>.
 * 
 */

/**
 * \brief Packets class implementation.
 * 
 * \author Gabriel Mariano Marcelino <gabriel.mm8@gmail.com>
 * 
 * \version 0.6.8
 * 
 * \date 06/10/2017
 * 
 * \addtogroup packets
 * \{
 */

#include "packets.h"

using namespace std;

Packets::Packets()
{
    make_log = false;
    
    this->InitPkts();
}

Packets::~Packets()
{
    if (make_log)
    {
        delete log_pkts;
    }
    
    if (make_data_log)
    {
        delete log_data_pkts;
    }
    
    if (this->is_open())
    {
        this->close();
    }
}

void Packets::InitPkts()
{
    receive_pkt = false;
    
    prev_fin_byte_counter = 0;
    fin_byte_counter = 0;
    
    this->SetSyncBytes(PACKETS_SYNC_BYTE_S0_DEFAULT, PACKETS_SYNC_BYTE_S1_DEFAULT, PACKETS_SYNC_BYTE_S2_DEFAULT, PACKETS_SYNC_BYTE_S3_DEFAULT);
}

void Packets::SetPreamble(uint8_t byte, uint8_t quant)
{
    preamble.clear();
    
    for(unsigned int i=0; i<quant; i++)
    {
        preamble.push_back(byte);
    }
}

void Packets::SetSyncBytes(uint8_t s0, uint8_t s1, uint8_t s2, uint8_t s3)
{
    sync_bytes.clear();
    
    sync_bytes.push_back(s3);
    sync_bytes.push_back(s2);
    sync_bytes.push_back(s1);
    sync_bytes.push_back(s0);
}

bool Packets::ProcessByte(uint8_t b)
{    
    return false;
}

void Packets::Search(const char *file)
{
    if (!this->is_open())
    {
        this->open(file, ifstream::in);
    }
    
    vector<uint8_t> sync_bits_buffer;
    
    uint32_t byte_counter = 0;
    
    char d;
    while(this->get(d))
    {
        uint8_t byte = d;
        fin_byte_counter++;
        
        if (fin_byte_counter <= prev_fin_byte_counter)
        {                
            continue;
        }
        else
        {
            prev_fin_byte_counter = fin_byte_counter;
        }
        
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
                
                if ((byte == 125) and (byte_counter == 0))
                {
                    receive_pkt = false;
                }
                else
                {
                    byte_counter++;
                    
                    if (this->ProcessByte(byte))
                    {
                        byte_counter = 0;
                    }
                }
                
                byte_buffer.clear();
            }
        }
    }
    
    fin_byte_counter = 0;
    
    this->close();
}

string Packets::LogPayload()
{
    return string();
}

void Packets::reset()
{
    this->prev_fin_byte_counter = 0;
    this->fin_byte_counter = 0;
}

//! \} End of packets group
