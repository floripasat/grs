/*
 * packet_sniffer.cpp
 * 
 * Copyright (C) 2019, Universidade Federal de Santa Catarina.
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
 * along with FloripaSat-GRS. If not, see <http://www.gnu.org/licenses/>.
 * 
 */

/**
 * \brief Packet sniffer implementation.
 * 
 * \author Gabriel Mariano Marcelino <gabriel.mm8@gmail.com>
 * 
 * \version 0.3.7
 * 
 * \date 05/04/2019
 * 
 * \addtogroup packet_sniffer
 * \{
 */

#include "packet_sniffer.h"

using namespace std;

PacketSniffer::PacketSniffer()
{

}

PacketSniffer::PacketSniffer(vector<uint8_t> sw, unsigned int len)
    : PacketSniffer()
{
    this->set_sync_word(sw);
    this->set_packet_buffer_size(len);
}

PacketSniffer::PacketSniffer(SyncWord sw, unsigned int len)
    : PacketSniffer()
{
    this->set_sync_word(sw);
    this->set_packet_buffer_size(len);
}

PacketSniffer::~PacketSniffer()
{

}

void PacketSniffer::set_sync_word(std::vector<uint8_t> bytes)
{
    this->sync_word.set_sync_word(bytes);

    this->sync_word_buffer.set_max_size(this->sync_word.size());
}

void PacketSniffer::set_sync_word(SyncWord sw)
{
    this->sync_word = sw;

    this->sync_word_buffer.set_max_size(this->sync_word.size());
}

void PacketSniffer::set_packet_buffer_size(unsigned int max)
{
    this->packet_buffer.set_max_size(max);
}

void PacketSniffer::sniff(bool bit)
{
    this->sync_word_buffer.push(bit);

    if (this->sync_word_buffer == this->sync_word)
    {
        this->byte_buffer.clear();

        this->packet_buffer.clear();

        auto sync_word_bytes = this->sync_word.get_bytes();

        for(unsigned int i=0; i<sync_word_bytes.size(); i++)
        {
            this->packet_buffer.push(sync_word_bytes[i]);
        }

        return;
    }

    this->byte_buffer.push(bit);

    if (this->byte_buffer.is_full())
    {
        this->packet_buffer.push(this->byte_buffer.to_byte());

        this->byte_buffer.clear();
    }
}

PacketBuffer PacketSniffer::get_packet_bytes(unsigned int n)
{
    if (this->packet_buffer.size() < n)
    {
        n = this->packet_buffer.size();
    }

    PacketBuffer buffer_bytes;

    while(n--)
    {
        buffer_bytes.push(this->packet_buffer.front());
        this->packet_buffer.pop();
    }

    return buffer_bytes;
}

unsigned int PacketSniffer::available_bytes()
{
    auto sync_word_bytes = this->sync_word.get_bytes();

    for(unsigned int i=0; i<sync_word_bytes.size(); i++)
    {
        if (sync_word_bytes[i] != this->packet_buffer[i])
        {
            return 0;
        }
    }

    return this->packet_buffer.size();
}

//! \} End of packet_sniffer group
