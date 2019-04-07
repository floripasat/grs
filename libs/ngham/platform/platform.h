/*
 * platform.h
 *
 * Copyright (C) 2014, Jon Petter Skagmo.
 * Copyright (C) 2017, Universidade Federal de Santa Catarina.
 * 
 * This file is part of FloripaSat-GRS
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as
 * published by the Free Software Foundation, either version 3 of the
 * License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this program; if not, see <http://www.gnu.org/licenses/>
 * 
 */

/**
 * \brief Platform definition.
 * 
 * \author Jon Petter Skagmo <web@skagmo.com>
 * \author Gabriel Mariano Marcelino <gabriel.mm8@gmail.com>
 * 
 * \version 0.3.6
 * 
 * \date 27/04/2017
 * 
 * \defgroup platform Platform
 * \ingroup ngham
 * \{
 */

#ifndef PLATFORM_NGHAM_H_
#define PLATFORM_NGHAM_H_

#include <stdint.h>

#include "../ngham_packets.h"	// Packet structs, NA-values etc.

/**
 * \brief NGHAM_BYTES_TILL_ACTION_HALFWAY is number of payload bytes until ngham_action_reception_halfway is executed.
 * 
 * Don't care about this if you don't use the mentioned function.
 */
#define NGHAM_BYTES_TILL_ACTION_HALFWAY 10	

extern uint8_t rx_buf[];        // Should hold the largest packet - ie. 255 B
extern uint16_t rx_buf_len;
extern ngham_rx_packet_t rx_pkt;
extern uint8_t decoder_state;

/**
 * \brief Data to be transmitted (to modulator).
 * 
 * Priority can be ignored if NGHam is not used for timing purposes.
 * 
 * \param *d
 * \param d_len
 * \param priority
 * \param *pkt
 * \param *pkt_len
 * 
 * \return None
 */
void ngham_action_send_data(uint8_t *d, uint16_t d_len, uint8_t priority, uint8_t *pkt, uint16_t *pkt_len);

/**
 * \brief Set packet size demodulator, if applicable, to make the demodulator stop outputting data when the packet is finished.
 * 
 * \param size
 * 
 * \return None
 */
void ngham_action_set_packet_size(uint8_t size);

/**
 * \brief Should return RSSI in dBm + 200.
 * 
 * \return RSSI
 */
uint8_t ngham_action_get_rssi();

/**
 * \brief Should return noise floor in dBm + 200.
 * 
 * \return Floor noise.
 */
uint8_t ngham_action_get_noise_floor();

/**
 * \brief Will always be called after packet reception is finished - whether it was successful or not.
 * 
 * This function should also handle reinitialization of your decoder/sync word detector.
 * 
 * \param condition
 * \param *p
 * \param *msg_len
 * \param *msg_len
 * 
 * \return None.
 */
void ngham_action_handle_packet(uint8_t condition, ngham_rx_packet_t *p, uint8_t *msg, uint8_t *msg_len);

/**
 * \brief 
 * 
 * Not required: Code to be executed when reception has just started.
 * This could be handling the time stamp of the sync word or starting RSSI readout.
 * 
 * \return None.
 */
void ngham_action_reception_started();

/**
 * \brief Not required: If there is more to do a little after reception start, do it here.
 * 
 * \return None.
 */
void ngham_action_reception_halfway();

#endif // PLATFORM_NGHAM_H_

//! \} End of platform group
