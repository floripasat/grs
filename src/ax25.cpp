/*
 * ax25.cpp
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
 * \brief AX25 encoder and decoder implementation.
 * 
 * \author Gabriel Mariano Marcelino <gabriel.mm8@gmail.com>
 * 
 * \version 0.3.7
 * 
 * \date 10/04/2019
 * 
 * \addtogroup ax25
 * \{
 */

#include "ax25.h"

using namespace std;

AX25::AX25()
{
}

AX25::~AX25()
{
}

vector<uint8_t> AX25::decode(vector<uint8_t> pkt)
{
    return vector<uint8_t>();
}

vector<uint8_t> AX25::encode(vector<uint8_t> data)
{
    return vector<uint8_t>();
}

//! \} End of ax25 group
