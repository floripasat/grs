/*
 * platform.c
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
 * \brief Platform implementation.
 * 
 * \author Jon Petter Skagmo <web@skagmo.com>
 * \author Gabriel Mariano Marcelino <gabriel.mm8@gmail.com>
 * 
 * \version 0.3.6
 * 
 * \date 27/04/2017
 * 
 * \addtogroup platform
 * \{
 */

#include <stdint.h>

#include "../ngham_packets.h"       // Packet structs, NA-values etc.
#include "../ngham_extension.h"

#include "platform.h"

// Temporary buffer for the decoder, rx packet variable and state variable.
uint8_t rx_buf[255];	// Should hold the largest packet - ie. 255 B
uint16_t rx_buf_len;
ngham_rx_packet_t rx_pkt;
uint8_t decoder_state;

uint8_t ngham_action_get_rssi()
{
    return RSSI_NA;
}

uint8_t ngham_action_get_noise_floor()
{
    return RSSI_NA;
}

void ngham_action_set_packet_size(uint8_t size)
{

}

void ngham_action_send_data(uint8_t *d, uint16_t d_len, uint8_t priority, uint8_t *pkt, uint16_t *pkt_len)
{
    int16_t i = 0;
    switch (priority)
    {
        case PKT_PRIORITY_NORMAL:
            for(i=0;i<d_len;i++)
            {
                pkt[i] = d[i];
            }
            *pkt_len = d_len;
            break;
        case PKT_PRIORITY_FIRST_IN_SLOT:
            break;
    }
}

void ngham_action_handle_packet(uint8_t condition, ngham_rx_packet_t *p, uint8_t *msg, uint8_t *msg_len)
{
    uint8_t i = 0;
    switch (condition)
    {
        case PKT_CONDITION_OK:
            // Add statistics?
            // Handle the received packet in p->pl[]
            for(i=0;i<p->pl_len;i++)
            {
                msg[i] = p->pl[i];
            }
            *msg_len = p->pl_len;
            break;
        case PKT_CONDITION_PREFAIL:
            // Count as fail
            break;
        case PKT_CONDITION_FAIL:
            // Count as fail and prepare for new sync word immediately
            break;
    }

    // Reset RX packet content
    ngham_rx_pkt_init(&rx_pkt);
}

void ngham_action_reception_started()
{
    // rx_pkt.timestamp = ;
}

void ngham_action_reception_halfway()
{

}

//! \} End of platform group
