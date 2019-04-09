/*
 * packet_buffer.hpp
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
 * \brief Packet buffer object.
 * 
 * \author Gabriel Mariano Marcelino <gabriel.mm8@gmail.com>
 * 
 * \version 0.3.7
 * 
 * \date 06/04/2019
 * 
 * \defgroup packet_buffer Packet Buffer
 * \{
 */

#ifndef PACKET_BUFFER_HPP_
#define PACKET_BUFFER_HPP_

#include <stdint.h>

#include <vector>
#include <iostream>

/**
 * \brief Packet buffer object.
 */
class PacketBuffer: public std::vector<uint8_t>
{
    public:

        /**
         * \brief Constructor.
         *
         * \param[in] max is the maximum number of bytes of the buffer.
         *
         * \return None.
         */
        PacketBuffer(unsigned int max=256)
        {
            this->set_max_size(max);
        }

        /**
         * \brief Sets the maximum number of bytes of the buffer.
         *
         * \param[in] max is the maximum number of bytes.
         *
         * \return None.
         */
        void set_max_size(unsigned int max)
        {
            this->max_size = max;
        }

        /**
         * \brief Gets the maximum number of bytes of the buffer.
         *
         * \return The maximum number of bytes.
         */
        unsigned int get_max_size()
        {
            return this->max_size;
        }

        /**
         * \brief Verifies if the buffer is full or not.
         *
         * \return TRUE/FALSE if the buffer is full or not.
         */
        bool is_full()
        {
            return this->size() >= this->get_max_size();
        }

        /**
         * \brief Pushes a new byte to the buffer.
         *
         * \param[in] byte is an element to store into the buffer
         *
         * \return None.
         */
        void push(uint8_t byte)
        {
            if (this->size() < this->get_max_size())
            {
                this->push_back(byte);
            }
        }

        /**
         * \brief Pops the first byte of the buffer.
         *
         * \return None.
         */
        void pop()
        {
            this->erase(this->begin());
        }

        /**
         * \brief cout overload.
         *
         * \param[in] os is the ostream object.
         * \param[in] packet_buffer is the PacketBuffer object.
         *
         * \return An ostream object.
         */
        friend std::ostream& operator<<(std::ostream& os, const PacketBuffer& packet_buffer)
        {
            for(unsigned int i=0; i<packet_buffer.size(); i++)
            {
                os << int(packet_buffer.at(i));

                if (i < packet_buffer.size()-1)
                {
                    os << ",";
                }
            }

            return os;
        }

    private:

        /**
         * \brief Maximum size in bytes.
         */
        unsigned int max_size;
};

#endif // PACKET_BUFFER_HPP_

//! \} End of packet_buffer group
