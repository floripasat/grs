/*
 * global_var.h
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
 * \file global_var.h
 * 
 * \brief .
 * 
 * \author Gabriel Mariano Marcelino <gabriel.mm8@gmail.com>
 * 
 * \version 1.0
 * 
 * \date 07/05/2017
 * 
 * \defgroup global_var Global variables
 * \ingroup fsat_pkt_ana
 * \{
 */

#ifndef GLOBAL_VAR_H_
#define GLOBAL_VAR_H_

#include <vector>
#include <stdint.h>

#include "widgets.h"
#include "uart.h"
#include "log.h"

#define DATA_RECEPTION_SAMPLE_RATE  1000

extern Widgets widgets;

extern UART uart;

extern Log log_raw_pkts;
extern Log log_ngham_pkts;
//extern Log log_ax25_pkts;
//extern Log log_data_pkts;

extern bool receive_pkt;
extern std::vector<uint8_t> sync_bytes_buffer;
extern std::vector<uint8_t> byte_buffer;
extern uint16_t ngham_pkt_counter;
extern uint16_t ngham_lost_pkts;

#endif // GLOBAL_VAR_H_

//! \} End of gloval_var group
