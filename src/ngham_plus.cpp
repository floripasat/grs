/*
 * ngham_plus.cpp
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
 * \brief NGHam wrapper implementation.
 * 
 * \author Gabriel Mariano Marcelino <gabriel.mm8@gmail.com>
 * 
 * \version 0.3.7
 * 
 * \date 07/04/2019
 * 
 * \addtogroup ngham_plus
 * \{
 */

extern "C"
{
#include <libs/ngham/ngham.h>
}

#include "ngham_plus.h"

using namespace std;

NGHamPlus::NGHamPlus()
{
    ngham_init();
}

NGHamPlus::~NGHamPlus()
{
}

vector<uint8_t> NGHamPlus::decode(vector<uint8_t> pkt)
{
    uint8_t buf[NGH_MAX_CODEWORD_SIZE];
    uint8_t buf_len;

    for(unsigned int i=0; i<pkt.size(); i++)
    {
        switch(ngham_decode(pkt[i], buf, &buf_len))
        {
            case PKT_CONDITION_OK:
                return vector<uint8_t>(buf, buf + buf_len/sizeof(uint8_t));
            case PKT_CONDITION_PREFAIL:
                continue;
            case PKT_CONDITION_FAIL:
                return vector<uint8_t>();
        }
    }
}

vector<uint8_t> NGHamPlus::encode(vector<uint8_t> data)
{
    if (data.size() > NGH_MAX_CODEWORD_SIZE)
    {
        return vector<uint8_t>();
    }

    ngham_tx_packet_t ngham_packet;

    ngham_tx_pkt_gen(&ngham_packet, &data[0], data.size());

    uint8_t pkt_str[NGH_MAX_TOT_SIZE];
    uint16_t pkt_str_len;

    ngham_encode(&ngham_packet, pkt_str, &pkt_str_len);

    return vector<uint8_t>(pkt_str, pkt_str + pkt_str_len/sizeof(uint8_t));
}

//! \} End of ngham_plus group
