/*
 * ngham.h
 * 
 * Copyright (C) 2014, Jon Petter Skagmo
 * Copyright (C) 2017, Universidade Federal de Santa Catarina
 * 
 * This file is part of FloripaSat-TTC.
 * 
 * FloripaSat-TTC is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * FloripaSat-TTC is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with FloripaSat-TTC.  If not, see <http://www.gnu.org/licenses/>.
 * 
 */

/**
 * \file ngham.h
 * 
 * \brief NGHam protocol functions.
 * 
 * \author Jon Petter Skagmo <skagmo.com>; Mods. for FloripaSat-TTC by Gabriel Mariano Marcelino <gabriel.mm8@gmail.com>
 * 
 * \date 10/02/2017
 * 
 * \defgroup ngham NGHam
 * \ingroup beacon
 * \{
 */

#ifndef NGHAM_H_
#define NGHAM_H_

#include <stdint.h>

#include "ngham_packets.h"  // tx_pkt_t

extern const uint8_t NGH_SYNC[];

#define NGH_PREAMBLE_SIZE               4
#define NGH_SYNC_SIZE                   4
#define NGH_PREAMBLE_SIZE_FOUR_LEVEL    8
#define NGH_SYNC_SIZE_FOUR_LEVEL        8
#define NGH_SIZE_TAG_SIZE               3
#define NGH_MAX_CODEWORD_SIZE           255
#define NGH_MAX_TOT_SIZE                (NGH_PREAMBLE_SIZE_FOUR_LEVEL+NGH_SYNC_SIZE_FOUR_LEVEL+NGH_SIZE_TAG_SIZE+NGH_MAX_CODEWORD_SIZE)

#define NGHAM_FOUR_LEVEL_MODULATION     0

#define NGH_PADDING_bm                  0x1f
#define NGH_FLAGS_bm                    0xe0
#define NGH_FLAGS_bp                    5

/**
 * \fn ngham_init_arrays
 * 
 * \brief Generates Reed Solomon tables.
 * 
 * Run only once - generates reed solomon tables for all 7 packet sizes
 * MM=8, genpoly=0x187, fcs=112, prim=11, nroots=32 or 16
 * 
 * \return None
 */
void ngham_init_arrays();

/**
 * \fn ngham_deinit_arrays
 * 
 * \brief Free Reed Solomon tables.
 * 
 * \return None
 */
void ngham_deinit_arrays();

/**
 * \fn ngham_init
 * 
 * \brief NGHam initialization.
 * 
 * \return None
 */
void ngham_init();

/**
 * \fn ngham_encode
 * 
 * \brief Packet encoding.
 * 
 * Packets to be transmitted are passed to this function - max. length 220 B
 * 
 * \return None
 */
void ngham_encode(tx_pkt_t* p, uint8_t* pkt, uint16_t* pkt_len);

/**
 * \fn ngham_decode
 * 
 * \brief Packet decoding.
 * 
 * \return 
 */
uint8_t ngham_decode(uint8_t d, uint8_t* msg, uint8_t* msg_len);

#endif // NGHAM_H_

//! \} End of NGHam group
