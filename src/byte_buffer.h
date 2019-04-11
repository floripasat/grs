/*
 * byte_buffer.h
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
 * \brief Byte buffer definition.
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

#ifndef BYTE_BUFFER_H_
#define BYTE_BUFFER_H_

#include <bitset>

/**
 * \brief Byte buffer object.
 */
class ByteBuffer: public std::bitset<8>
{
    public:

        /**
         * \brief Constructor.
         *
         * \return None.
         */
        ByteBuffer();

        /**
         * \brief Checks if the buffer is full or not (1 byte = 8 bits).
         *
         * \return TRUE/FALSE if the buffer is full or not.
         */
        bool is_full();

        /**
         * \brief Push a new bit to the buffer.
         *
         * \param[in] bit is the new bit to insert into the buffer.
         *
         * \return None.
         */
        void push(bool bit);

        /**
         * \brief Clears the contents of buffer.
         *
         * \return None.
         */
        void clear();

        /**
         * \brief Converts the buffer elements to a byte.
         *
         * \return The equivalent byte of the bitset sequence.
         */
        uint8_t to_byte();

    private:

        /**
         * \brief The current position of the buffer.
         */
        unsigned int pos;
};

#endif // BYTE_BUFFER_H_

//! \} End of byte_buffer group
