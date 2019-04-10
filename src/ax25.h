/*
 * ax25.h
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
 * \brief AX25 encoder and decoder definition.
 * 
 * \author Gabriel Mariano Marcelino <gabriel.mm8@gmail.com>
 * 
 * \version 0.3.7
 * 
 * \date 10/04/2019
 * 
 * \defgroup ax25 AX25
 * \{
 */

#ifndef AX25_H_
#define AX25_H_

#include <stdint.h>

#include <vector>
#include <string>

/**
 * \brief AX25 encoder and decoder.
 */
class AX25
{
    public:

        /**
         * \brief Constructor.
         *
         * \return None.
         */
        AX25();

        /**
         * \brief Destructor.
         *
         * \return None.
         */
        ~AX25();

        /**
         * \brief Decodes an incoming packet.
         *
         * \param[in] pkt is the pack of bytes to decode.
         *
         * \return The decoded packet payload.
         */
        std::vector<uint8_t> decode(std::vector<uint8_t> pkt);

        /**
         * \brief Encodes a pack of bytes as AX25 packet.
         *
         * \param[in] data is the data to encode as a AX25 packet.
         *
         * \return The encoded packet.
         */
        std::vector<uint8_t> encode(std::vector<uint8_t> data);

        /**
         * \brief Source callsign.
         */
        std::string src_callsign;

        /**
         * \brief Destination callsign.
         */
        std::string dst_callsign;

    private:
};

#endif // AX25_H_

//! \} End of ax25 group
