/*
 * message_broadcast.h
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
 * \brief Message broadcast packet definition.
 * 
 * \author Gabriel Mariano Marcelino <gabriel.mm8@gmail.com>
 * 
 * \version 0.4.3
 * 
 * \date 15/04/2019
 * 
 * \defgroup message_broadcast Message Broadcast
 * \ingroup downlink_data
 * \{
 */

#ifndef MESSAGE_BROADCAST_H_
#define MESSAGE_BROADCAST_H_

#include <string>

#include "downlink_data.h"
#include "../payload.h"

// Packet content positions
#define MESSAGE_BROADCAST_DST_CALLSIGN_POS      7
#define MESSAGE_BROADCAST_MESSAGE_POS           14

namespace grs
{
    
    /**
     * \brief Message broadcast packet.
     */
    class MessageBroadcast: public grs::DownlinkData
    {
        public:

            /**
             * \brief Decodes a message broadcast packet payload.
             *
             * \param[in] pl is the message broadcast packet payload to decode.
             *
             * \return None.
             */
            void decode(Payload pl);

            /**
             * \brief Gets the destination of the message.
             *
             * \return The destination callsign in ASCII.
             */
            std::string get_destination_callsign();

            /**
             * \brief Gets the received message.
             *
             * \return The received message.
             */
            std::string get_message();

        private:

            /**
             * \brief Destination callsign.
             */
            std::string destination_callsign;

            /**
             * \brief Message (ASCII characters).
             */
            std::string message;
    };
}

#endif // MESSAGE_BROADCAST_H_

//! \} End of message_broadcast group
