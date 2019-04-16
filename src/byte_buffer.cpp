/*
 * byte_buffer.cpp
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
 * \brief Byte buffer implementation.
 * 
 * \author Gabriel Mariano Marcelino <gabriel.mm8@gmail.com>
 * 
 * \version 0.4.0
 * 
 * \date 06/04/2019
 * 
 * \defgroup byte_buffer Byte Buffer
 * \{
 */

#include "byte_buffer.h"

using namespace std;

ByteBuffer::ByteBuffer()
    : bitset<8>()
{
    this->clear();
}

bool ByteBuffer::is_full()
{
    if (this->pos > 7)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void ByteBuffer::push(bool bit)
{
    if (this->pos < 8)
    {
        this->set(this->pos--, bit);
    }
}

void ByteBuffer::clear()
{
    this->reset();

    this->pos = 7;
}

uint8_t ByteBuffer::to_byte()
{
    return this->to_ulong() & 0xFF;
}

//! \} End of byte_buffer group
