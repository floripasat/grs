/*
 * pkt_handler.h
 * 
 * Copyright (C) 2017, Universidade Federal de Santa Catarina
 * 
 * This file is part of FloripaSat-Packet-Analyzer.
 * 
 * FloripaSat-Packet-Analyzer is free software: you can redistribute it
 * and/or modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation, either version 3 of the
 * License, or (at your option) any later version.
 * 
 * FloripaSat-Packet-Analyzer is distributed in the hope that it will be
 * useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with FloripaSat-Packet-Analyzer.
 * If not, see <http://www.gnu.org/licenses/>.
 * 
 */

/**
 * \file pkt_handler.h
 * 
 * \brief .
 * 
 * \author Gabriel Mariano Marcelino <gabriel.mm8@gmail.com>
 * 
 * \version 1.0
 * 
 * \date 07/05/2017
 * 
 * \defgroup pkt_hdl Packet handler
 * \ingroup fsat_pkt_ana
 * \{
 */

#ifndef PKT_HANDLER_H_
#define PKT_HANDLER_H_

#include <vector>
#include <stdint.h>

/**
 * \fn process_byte
 * 
 * \brief 
 * 
 * \param byte
 * 
 * \return 
 */
std::vector<uint8_t> proccess_byte(uint8_t byte);

/**
 * \fn display_beacon_data
 * 
 * \brief 
 * 
 * \param data
 * \param len
 * 
 * \return None
 */
void display_beacon_data(uint8_t *data, uint8_t len);

#endif // PKT_HANDLER_H_

//! \} End of pkt_hdl group
