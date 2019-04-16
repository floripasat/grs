/*
 * bit_buffer.h
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
 * \brief Bit buffer definition.
 * 
 * \author Gabriel Mariano Marcelino <gabriel.mm8@gmail.com>
 * 
 * \version 0.4.0
 * 
 * \date 06/04/2019
 * 
 * \defgroup bit_buffer Bit Buffer
 * \{
 */

#ifndef BIT_BUFFER_H_
#define BIT_BUFFER_H_

#include <vector>
#include <iostream>

/**
 * \brief BitBuffer object.
 */
class BitBuffer: public std::vector<bool>
{
    public:

        /**
         * \brief .
         *
         * \return None.
         */
        BitBuffer();

        /**
         * \brief .
         *
         * \param[in] max_size is the maximum size of the buffer in bits.
         *
         * \return None.
         */
        BitBuffer(unsigned int max_size);

        /**
         * \brief Sets the maximum size of the buffer.
         *
         * \param[in] max is the maximum size of the buffer in bits.
         *
         * \return None.
         */
        void set_max_size(unsigned int max);

        /**
         * \brief Gets the maximum size of the buffer.
         *
         * \return The maximum size of the buffer in bits.
         */
        unsigned int get_max_size();

        /**
         * \brief Push a new bit to the buffer.
         *
         * \param[in] bit is the new bit to insert into the buffer.
         *
         * \return None.
         */
        void push(bool bit);

        /**
         * \brief cout overload.
         *
         * \param[in] os is the ostream object.
         * \param[in] bit_buffer is the BitBuffer object.
         *
         * \return An ostream object.
         */
        friend std::ostream& operator<<(std::ostream& os, const BitBuffer& bit_buffer);

    private:

        /**
         * \brief Max size in bits.
         */
        unsigned int max_size;
};

#endif // BIT_BUFFER_H_

//! \} End of bit_buffer group
