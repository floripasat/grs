/*
 * payload.cpp
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
 * \brief Payload object implementation.
 * 
 * \author Gabriel Mariano Marcelino <gabriel.mm8@gmail.com>
 * 
 * \version 0.3.7
 * 
 * \date 08/04/2019
 * 
 * \addtogroup payload
 * \{
 */

#include "payload.h"

using namespace std;

Payload::Payload()
{
    this->id = 0xFF;
    this->source_callsign = "0000000";
}

Payload::Payload(std::vector<uint8_t> bytes)
{
    this->id = bytes.front();

    // The minimum length of a callsign is 4 characters, the maximum is 7
    if ((bytes[1] == '0') and (bytes[2] == '0') and ((bytes[3] == '0')))    // 4 characters ("000XXXX")
    {
        this->source_callsign.assign(bytes.begin()+4, bytes.begin()+8);
    }
    else if ((bytes[1] == '0') and (bytes[2] == '0'))                       // 5 characters ("00XXXXX")
    {
        this->source_callsign.assign(bytes.begin()+3, bytes.begin()+8);
    }
    else if (bytes[1] == '0')                                               // 6 characters ("0XXXXXX")
    {
        this->source_callsign.assign(bytes.begin()+2, bytes.begin()+8);
    }
    else                                                                    // 7 characters ("XXXXXXX")
    {
        this->source_callsign.assign(bytes.begin()+1, bytes.begin()+8);
    }

    this->assign(bytes.begin()+8, bytes.end());
}

Payload::Payload(uint8_t code, string callsign, vector<uint8_t> data)
{
    this->id = code;
    this->source_callsign = callsign;
    this->assign(data.begin(), data.end());
}

Payload::~Payload()
{

}

ostream& operator<<(ostream& os, const Payload& payload)
{
    os << "Packet type " << int(payload.id) << " from " << payload.source_callsign << ": ";

    for(unsigned int i=0; i<payload.size(); i++)
    {
        os << payload.at(i);

        if (i < payload.size()-1)
        {
            os << ",";
        }
    }

    return os;
}

//! \} End of payload group
