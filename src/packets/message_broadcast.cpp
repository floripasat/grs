/*
 * message_broadcast.cpp
 * 
 * Copyright (C) 2019, Universidade Federal de Santa Catarina.
 * 
 * This file is part of FloripaSat-GRS.
 * 
 * FloripaSat-GRS is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * FloripaSat-GRS is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public License
 * along with FloripaSat-GRS. If not, see <http://www.gnu.org/licenses/>.
 * 
 */

/**
 * \brief Message broadcast packet implementation.
 * 
 * \author Gabriel Mariano Marcelino <gabriel.mm8@gmail.com>
 * 
 * \version 0.4.3
 * 
 * \date 15/04/2019
 * 
 * \addtogroup message_broadcast
 * \{
 */

#include "message_broadcast.h"

using namespace std;
using namespace grs;

void MessageBroadcast::decode(Payload pl)
{
    // ID, source callsign and requester callsign
    DownlinkData::decode(pl);

    // Destination callsign
    this->destination_callsign = Packet::substr_to_callsign(string(pl.begin() + MESSAGE_BROADCAST_DST_CALLSIGN_POS,
                                                                   pl.begin() + MESSAGE_BROADCAST_MESSAGE_POS));

    // Received message
    this->message.assign(pl.begin() + MESSAGE_BROADCAST_MESSAGE_POS, pl.end());
}

string MessageBroadcast::get_destination_callsign()
{
    return this->destination_callsign;
}

string MessageBroadcast::get_message()
{
    return this->message;
}

//! \} End of message_broadcast group
