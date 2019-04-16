/*
 * payload.h
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
 * \brief Payload object definition.
 * 
 * \author Gabriel Mariano Marcelino <gabriel.mm8@gmail.com>
 * 
 * \version 0.4.1
 * 
 * \date 08/04/2019
 * 
 * \defgroup payload Payload
 * \{
 */

#ifndef PAYLOAD_H_
#define PAYLOAD_H_

#include <stdint.h>

#include <iostream>
#include <vector>
#include <string>

/**
 * \brief Packet payload.
 */
class Payload: public std::vector<uint8_t>
{
    public:

        /**
         * \brief Constructor.
         *
         * \return None.
         */
        Payload();

        /**
         * \brief Constructor (overloaded).
         *
         * \return None.
         */
        Payload(std::vector<uint8_t> bytes);

        /**
         * \brief Constructor (overloaded).
         *
         * \return None.
         */
        Payload(uint8_t code, std::string callsign, std::vector<uint8_t> data);

        /**
         * \brief Destructor.
         *
         * \return None.
         */
        ~Payload();

        /**
         * \brief cout overload.
         *
         * \param[in] os is the ostream object.
         * \param[in] payload is the Payload object.
         *
         * \return An ostream object.
         */
        friend std::ostream& operator<<(std::ostream& os, const Payload& payload);

        /**
         * \brief Packet ID code.
         */
        uint8_t id;

        /**
         * \brief Packet source callsign.
         */
        std::string source_callsign;
};

#endif // PAYLOAD_H_

//! \} End of payload group
