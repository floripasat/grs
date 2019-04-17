/*
 * payload_x_status.cpp
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
 * \brief Payload X status packet implementation.
 * 
 * \author Gabriel Mariano Marcelino <gabriel.mm8@gmail.com>
 * 
 * \version 0.4.5
 * 
 * \date 13/04/2019
 * 
 * \addtogroup payload_x_status
 * \{
 */

#include "payload_x_status.h"

using namespace std;
using namespace grs;

void PayloadXStatus::decode(Payload pl)
{
    Packet::decode(pl);

    // Sequence number
    this->sequence_number = (pl[PAYLOAD_X_STATUS_SEQUENCE_NUMBER_POS] << 8) | pl[PAYLOAD_X_STATUS_SEQUENCE_NUMBER_POS+1];

    // Status bytes
    this->status.assign(pl.begin() + PAYLOAD_X_STATUS_STATUS_POS, pl.end());
}

uint16_t PayloadXStatus::get_sequence_number()
{
    return this->sequence_number;
}

vector<uint8_t> PayloadXStatus::get_status()
{
    return this->status;
}

//! \} End of payload_x_status group
