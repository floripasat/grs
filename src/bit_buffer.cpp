/*
 * bit_buffer.cpp
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
 * \brief Bit buffer implementation.
 * 
 * \author Gabriel Mariano Marcelino <gabriel.mm8@gmail.com>
 * 
 * \version 0.3.7
 * 
 * \date 06/04/2019
 * 
 * \defgroup bit_buffer Bit Buffer
 * \{
 */

#include "bit_buffer.h"

using namespace std;

BitBuffer::BitBuffer()
{

}

BitBuffer::BitBuffer(unsigned int max_size)
{
    this->set_max_size(max_size);
}

void BitBuffer::set_max_size(unsigned int max)
{
    this->max_size = max;
}

unsigned int BitBuffer::get_max_size()
{
    return this->max_size;
}

void BitBuffer::push(bool bit)
{
    if (this->size() == this->get_max_size())
    {
        this->erase(this->begin());
    }

    this->push_back(bit);
}

ostream& operator<<(ostream& os, const BitBuffer& bit_buffer)
{
    for(unsigned int i=0; i<bit_buffer.size(); i++)
    {
        os << bit_buffer.at(i);
    }

    return os;
}

//! \} End of bit_buffer group
