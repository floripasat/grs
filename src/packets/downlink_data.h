/*
 * downlink_data.h
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
 * \brief Downlink data packet definition.
 * 
 * \author Gabriel Mariano Marcelino <gabriel.mm8@gmail.com>
 * 
 * \version 0.4.3
 * 
 * \date 13/04/2019
 * 
 * \defgroup downlink_data Downlink Data
 * \ingroup packets
 * \{
 */

#ifndef DOWNLINK_DATA_H_
#define DOWNLINK_DATA_H_

#include "packet.h"

namespace grs
{
    /**
     * \brief Downlink data packet.
     */
    class DownlinkData: public grs::Packet
    {
        public:

            /**
             * \brief Decodes a downlink packet payload.
             *
             * \param[in] pl is the downlink packet payload to decode.
             *
             * \return None.
             */
            void decode(Payload pl);

            /**
             * \brief Gets the callsign of the command requester.
             *
             * \return The callsign of the command requester in ASCII.
             */
            std::string get_requester_callsign();

        private:

            /**
             * \brief Command requester callsign.
             */
            std::string requester_callsign;
    };
}

#endif // DOWNLINK_DATA_H_

//! \} End of downlink_data group
