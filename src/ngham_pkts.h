/*
 * ngham_pkts.h
 * 
 * Copyright (C) 2017, Federal University of Santa Catarina.
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
 * \file ngham_pks.h
 * 
 * \brief NGHam Packets class.
 * 
 * \author Gabriel Mariano Marcelino <gabriel.mm8@gmail.com>
 * 
 * \version 1.0-dev
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

#include "packets.h"
#include "packet_data.h"
#include "protocol_statistic.h"

/**
 * \class NGHamPkts
 * 
 * \brief 
 */
class NGHamPkts: public Packets
{
    public:
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
};

#endif // NGHAM_PKTS_H_

//! \} End of ngham_pkts group
