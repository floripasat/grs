/*
 * packet.h
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
 * \brief Packet definition.
 * 
 * \author Gabriel Mariano Marcelino <gabriel.mm8@gmail.com>
 * 
 * \version 0.4.3
 * 
 * \date 09/04/2019
 * 
 * \defgroup packet Packet
 * \{
 */

#ifndef PACKET_H_
#define PACKET_H_

#include <stdint.h>
#include <string>

#include <map>

#include "../payload.h"

namespace grs
{

    /**
     * \brief Packet object.
     */
    class Packet: public std::map<int, double>
    {
        public:

            /**
             * \brief Declaration constructor.
             *
             * \return None.
             */
            Packet();

            /**
             * \brief Constructor with initialization (overloaded).
             *
             * \return None.
             */
            Packet(Payload pl);

            /**
             * \brief Destructor.
             *
             * \return None.
             */
            ~Packet();

            /**
             * \brief .
             *
             * \param[in] pl
             *
             * \return None.
             */
            void decode(Payload pl);

            /**
             * \brief Packet ID code.
             */
            uint8_t id;

            /**
             * \brief Packet source callsign.
             */
            std::string src_callsign;

            /**
             * \brief Gets the callsign of the command requester.
             *
             * \return The callsign of the command requester in ASCII.
             */
            virtual std::string get_requester_callsign() = 0;

        protected:

            /**
             * \brief Gets a callsign from a 7 characters substring.
             *
             * \param[in] cs is substring with a callsign (7 characters).
             *
             * \return The given callsign as an string.
             */
            std::string substr_to_callsign(std::string cs);
    };
}

#endif // PACKET_H_

//! \} End of packet group
