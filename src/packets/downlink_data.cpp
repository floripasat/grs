/*
 * downlink_data.cpp
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
 * \brief Downlink data packet implementation.
 * 
 * \author Gabriel Mariano Marcelino <gabriel.mm8@gmail.com>
 * 
 * \version 0.4.3
 * 
 * \date 13/04/2019
 * 
 * \addtogroup downlink_data
 * \{
 */

#include <cmath>

#include "downlink_data.h"

using namespace std;
using namespace grs;

void DownlinkData::decode(Payload pl)
{
    // ID and source callsign
    Packet::decode(pl);

    // Requester callsign
    DownlinkData::requester_callsign = Packet::substr_to_callsign(string(pl.begin(), pl.begin()+7));
}

string DownlinkData::get_requester_callsign()
{
    return this->requester_callsign;
}

//! \} End of downlink_data group
