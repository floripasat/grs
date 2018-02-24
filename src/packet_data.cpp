/*
 * packet_data.cpp
 * 
 * Copyright (C) 2017, Federal University of Santa Catarina.
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
 * \file packet_data.cpp
 * 
 * \brief Packet data class implementation.
 * 
 * \author Gabriel Mariano Marcelino <gabriel.mm8@gmail.com>
 * 
 * \version 1.0-dev
 * 
 * \date 08/10/2017
 * 
 * \addtogroup packet_data
 * \{
 */

#include "packet_data.h"

using namespace std;

PacketData::PacketData()
{
    
}

PacketData::~PacketData()
{
    
}

void PacketData::Display()
{
    
}

void PacketData::Display(uint8_t pkt_type)
{
    
}

void PacketData::Display(bool no_data)
{
    
}

void PacketData::Update(uint8_t *data, uint8_t len)
{
    
}

void PacketData::Clear()
{
    
}

string PacketData::Log()
{
    return string("");
}

const char* PacketData::getLabel()
{
    return "GENERIC";
}

void PacketData::ForceDisplay(vector<string> data)
{

}

//! \} End of packet_data
