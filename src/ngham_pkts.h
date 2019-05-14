/*
 * ngham_pkts.h
 * 
 * Copyright (C) 2017-2019, Universidade Federal de Santa Catarina.
 * 
 * This file is part of FloripaSat-GRS.
 * 
 * FloripaSat-GRS is free software: you can redistribute it
 * and/or modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation, either version 3 of the
 * License, or (at your option) any later version.
 * 
 * FloripaSat-GRS is distributed in the hope that it will be
 * useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with FloripaSat-GRS. If not, see <http://www.gnu.org/licenses/>.
 * 
 */

/**
 * \brief NGHam Packets class definition.
 * 
 * \author Gabriel Mariano Marcelino <gabriel.mm8@gmail.com>
 * 
 * \version 0.5.0
 * 
 * \date 06/10/2017
 * 
 * \defgroup ngham_pks NGHam Packets
 * \ingroup fsat_grs
 * \{
 */

#ifndef NGHAM_PKS_H_
#define NGHAM_PKS_H_

#include <stdint.h>
#include <string>

#include "packets.h"
#include "packet_data.h"
#include "protocol_statistic.h"

#define NGHAM_PKT_GEN_FILE      "/tmp/tx_data.bin"

/**
 * \brief NGHamPkts
 */
class NGHamPkts: public Packets
{
    public:
        /**
         * \brief 
         * 
         * \return None
         */
        NGHamPkts();
        /**
         * \brief 
         * 
         * \param ev_log
         * \param pkt_data
         * \param ngham_stat
         * \param l
         * \param pdl
         * 
         * \return None
         */
        NGHamPkts(EventLog *ev_log, PacketData *pkt_data, ProtocolStatistic *ngham_stat, bool l=true, bool pdl=true);
        /**
         * \brief 
         * 
         * \param byte
         * 
         * \return 
         */
        bool ProcessByte(uint8_t byte);
        /**
         * \brief Generates a NGHam packet with the data and saves it on a file.
         * 
         * \param data is an array with payload of the data.
         * \param len is the length of the payload, in bytes.
         * 
         * \return None
         */
        void Generate(uint8_t *data, uint8_t len);

        /**
         * \brief Gets a callsign from a 7 characters substring.
         *
         * \param[in] cs is substring with a callsign (7 characters).
         *
         * \return The given callsign as an string.
         */
        std::string substr_to_callsign(std::string cs);
};

#endif // NGHAM_PKTS_H_

//! \} End of ngham_pkts group
