/*
 * payload_x_upload.cpp
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
 * \brief Payload X upload command implementation.
 * 
 * \author Gabriel Mariano Marcelino <gabriel.mm8@gmail.com>
 * 
 * \version 0.2.12
 * 
 * \date 23/02/2019
 * 
 * \addtogroup payload_x_upload
 * \{
 */

#include "payload_x_upload.h"

using namespace std;

PayloadXUpload::PayloadXUpload()
{
    this->block_counter = 0;
}

PayloadXUpload::PayloadXUpload(string filename, unsigned int blk_size)
    : PayloadXUpload()
{
    this->open(filename, ifstream::in);

    this->set_block_size(blk_size);

    this->split_bitfile();
}

PayloadXUpload::~PayloadXUpload()
{
}

void PayloadXUpload::set_block_size(unsigned int size)
{
    this->block_size = size;
}

unsigned int PayloadXUpload::get_block_size()
{
    return this->block_size;
}

unsigned int PayloadXUpload::get_number_of_required_blocks()
{
    if (!this->is_open())
    {
        return 0;
    }

    return blocks.size();
}

unsigned int PayloadXUpload::get_number_of_transmitted_blocks()
{
    return block_counter;
}

unsigned int PayloadXUpload::get_number_of_remaining_blocks()
{
    return this->get_number_of_required_blocks()-this->block_counter;
}

void PayloadXUpload::split_bitfile()
{
    if (!this->is_open())
    {
        return;
    }

    blocks.clear();

    vector<uint8_t> block;

    char d;
    while(this->get(d))
    {
        block.push_back(d);

        if (block.size() == this->get_block_size())
        {
            blocks.push_back(block);
            block.clear();
        }
    }

    // Filling the last block with zeros
    for(unsigned int i=block.size(); i<this->get_block_size(); i++)
    {
        block.push_back(0);
    }

    if (!block.empty())
    {
        blocks.push_back(block);
    }
}

vector<uint8_t> PayloadXUpload::get_next_block()
{
    if (!this->is_open())
    {
        return vector<uint8_t>();
    }

    return blocks[this->block_counter++];
}

double PayloadXUpload::get_progress()
{
    return 100-(this->get_number_of_remaining_blocks()*100/this->get_number_of_required_blocks());
}

//! \} End of payload_x_upload group
