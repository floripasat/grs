/*
 * packet.cpp
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
 * \brief Packet object implementation.
 * 
 * \author Gabriel Mariano Marcelino <gabriel.mm8@gmail.com>
 * 
 * \version 0.4.0
 * 
 * \date 09/04/2019
 * 
 * \addtogroup packet
 * \{
 */

#include "packet.h"

using namespace grs;

Packet::Packet()
{
    this->id = 0xFF;
    this->src_callsign = "0000000";
}

Packet::Packet(Payload pl)
{
    this->decode(pl);
}

Packet::~Packet()
{
}

void Packet::decode(Payload pl)
{
    this->id = pl.id;
    this->src_callsign = pl.source_callsign;
}

//! \} End of packet group
