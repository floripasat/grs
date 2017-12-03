/*
 * ax25_pkts.cpp
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
 * \file ax25_pks.cpp
 * 
 * \brief AX.25 packets class implementation.
 * 
 * \author Gabriel Mariano Marcelino <gabriel.mm8@gmail.com>
 * 
 * \version 1.0-dev
 * 
 * \date 02/11/2017
 * 
 * \addtogroup ax25_pkts
 * \{
 */

#include "ax25_pkts.h"

AX25Pkts::AX25Pkts(EventLog *ev_log, PacketData *pkt_data, ProtocolStatistic *ax25_stat, bool l, bool pdl)
{
    
}

bool AX25Pkts::ProcessByte(uint8_t byte)
{
    return true;
}

//! \} End of ax25_pkts group
