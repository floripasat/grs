/*
 * byte_buffer.hpp
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
 * \brief Byte buffer object.
 * 
 * \author Gabriel Mariano Marcelino <gabriel.mm8@gmail.com>
 * 
 * \version 0.3.7
 * 
 * \date 06/04/2019
 * 
 * \defgroup byte_buffer Byte Buffer
 * \{
 */

#ifndef BYTE_BUFFER_HPP_
#define BYTE_BUFFER_HPP_

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
        ByteBuffer()
            : std::bitset<8>()
        {
            this->clear();
        }

        /**
         * \brief Checks if the buffer is full or not (1 byte = 8 bits).
         *
         * \return TRUE/FALSE if the buffer is full or not.
         */
        bool is_full()
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

        /**
         * \brief Push a new bit to the buffer.
         *
         * \param[in] bit is the new bit to insert into the buffer.
         *
         * \return None.
         */
        void push(bool bit)
        {
            if (this->pos < 8)
            {
                this->set(this->pos--, bit);
            }
        }

        /**
         * \brief Clears the contents of buffer.
         *
         * \return None.
         */
        void clear()
        {
            this->reset();

            this->pos = 7;
        }

        /**
         * \brief Converts the buffer elements to a byte.
         *
         * \return The equivalent byte of the bitset sequence.
         */
        uint8_t to_byte()
        {
            return this->to_ulong() & 0xFF;
        }

    private:

        /**
         * \brief The current position of the buffer.
         */
        unsigned int pos;
};

#endif // BYTE_BUFFER_HPP_

//! \} End of byte_buffer group
