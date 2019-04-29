/*
 * payload_x_status.h
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
 * \brief Payload X status packet definition.
 * 
 * \author Gabriel Mariano Marcelino <gabriel.mm8@gmail.com>
 * 
 * \version 0.4.5
 * 
 * \date 13/04/2019
 * 
 * \defgroup payload_x_status Payload X Status
 * \ingroup downlink_data
 * \{
 */

#ifndef PAYLOAD_X_STATUS_H_
#define PAYLOAD_X_STATUS_H_

#include <stdint.h>
#include <vector>

#include "downlink_data.h"
#include "../payload.h"

#define PAYLOAD_X_STATUS_SEQUENCE_NUMBER_POS        0
#define PAYLOAD_X_STATUS_STATUS_POS                 2

namespace grs
{
    /**
     * \brief Payload X status packet.
     */
    class PayloadXStatus: public grs::DownlinkData
    {
        public:

            /**
             * \brief Decodes an Payload X status packet.
             *
             * \parma[in] pl is the Payload X status packet payload to decode.
             *
             * \return None.
             */
            void decode(Payload pl);

            /**
             * \brief Gets the status packet sequence number.
             *
             * \return The sequence number of the status packets.
             */
            uint16_t get_sequence_number();

            /**
             * \brief Gets the status bytes.
             *
             * \return The status bytes.
             */
            std::vector<uint8_t> get_status();

        private:

            /**
             * \brief Sequence number of the status packets.
             */
            uint16_t sequence_number;

            /**
             * \brief Status flags.
             */
            std::vector<uint8_t> status;
    };
}

#endif // PAYLOAD_X_STATUS_H_

//! \} End of payload_x_status group
