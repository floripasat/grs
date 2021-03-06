/*
 * aux.cpp
 * 
 * Copyright (C) 2017, Federal University of Santa Catarina
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
 * \file aux.cpp
 * 
 * \brief Auxiliary functions implementation.
 * 
 * \author Gabriel Mariano Marcelino <gabriel.mm8@gmail.com>
 * 
 * \version 1.0-dev
 * 
 * \date 07/05/2017
 * 
 * \addtogroup aux
 * \{
 */

#include "aux.hpp"

using namespace std;

uint8_t EntryToHex(Glib::ustring byte_str)
{
    int byte = int(byte_str[byte_str.size()-2]);
    int b1 = (byte >= 65)? byte-55 : byte-48;

    byte = int(byte_str[byte_str.size()-1]);
    int b0 = (byte >= 65)? byte-55 : byte-48;

    return ((uint8_t)b1 << 4) + (uint8_t)b0;
}

string HexToStr(uint8_t byte)
{
    string output = "0x";
    
    uint8_t digit = (uint8_t)(byte >> 4);
    
    if (digit < 0x0A)
    {
        output += (char)(digit + 0x30);     // 0x30 = ascii 0
    }
    else if (digit <= 0x0F)
    {
        output += (char)(digit + 0x37);     // 0x37 = ascii 7
    }
    else
    {
        output += 'N';
    }
    
    digit = (uint8_t)(byte & 0x0F);
    
    if (digit < 0x0A)
    {
        output += (char)(digit + 0x30);     // 0x30 = ascii 0
    }
    else if (digit <= 0x0F)
    {
        output += (char)(digit + 0x37);     // 0x37 = ascii 7
    }
    else
    {
        output += 'N';
    }
    
    return output;
}

//! \} End of aux group implementation
