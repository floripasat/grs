/*
 * packet_buffer.cpp
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
 * \brief Packet buffer implementation.
 * 
 * \author Gabriel Mariano Marcelino <gabriel.mm8@gmail.com>
 * 
 * \version 0.4.0
 * 
 * \date 06/04/2019
 * 
 * \defgroup packet_buffer Packet Buffer
 * \{
 */

#include "packet_buffer.h"

using namespace std;

PacketBuffer::PacketBuffer(unsigned int max)
{
    this->set_max_size(max);
}

void PacketBuffer::set_max_size(unsigned int max)
{
    this->max_size = max;
}

unsigned int PacketBuffer::get_max_size()
{
    return this->max_size;
}

bool PacketBuffer::is_full()
{
    return this->size() >= this->get_max_size();
}

void PacketBuffer::push(uint8_t byte)
{
    if (this->size() < this->get_max_size())
    {
        this->push_back(byte);
    }
}

void PacketBuffer::pop()
{
    this->erase(this->begin());
}

ostream& operator<<(ostream& os, const PacketBuffer& packet_buffer)
{
    for(unsigned int i=0; i<packet_buffer.size(); i++)
    {
        os << int(packet_buffer.at(i));

        if (i < packet_buffer.size()-1)
        {
            os << ",";
        }
    }

    return os;
}

//! \} End of packet_buffer group
