/*
 * global_var.cpp
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
 * \file global_var.cpp
 * 
 * \brief .
 * 
 * \author Gabriel Mariano Marcelino <gabriel.mm8@gmail.com>
 * 
 * \version 1.0
 * 
 * \date 07/05/2017
 * 
 * \addtogroup global_var
 * \{
 */

#include "../inc/global_var.h"

Widgets widgets;

UART uart;

Log log_raw_pkts;
Log log_ngham_pkts;
//Log log_ax25_pkts;
//Log log_data_pkts;

bool receive_pkt = false;
std::vector<uint8_t> sync_bytes_buffer;
std::vector<uint8_t> byte_buffer;
uint16_t ngham_pkt_counter = 0;
uint16_t ngham_lost_pkts = 0;

//! \} End of global_var implementation group
