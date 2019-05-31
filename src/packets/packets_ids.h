/*
 * packets_ids.h
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
 * \brief Packets IDs definition.
 * 
 * \author Gabriel Mariano Marcelino <gabriel.mm8@gmail.com>
 * 
 * \version 0.5.11
 * 
 * \date 10/04/2019
 * 
 * \defgroup packets_ids Packets IDs
 * \{
 */

#ifndef PACKETS_IDS_H_
#define PACKETS_IDS_H_

// Beacon packets
#define FLORIPASAT_PACKET_BEACON_NGHAM_OBDH_DATA            0x00    /**< Beacon NGHam packet with OBDH data. */
#define FLORIPASAT_PACKET_BEACON_NGHAM_EPS_DATA             0x01    /**< Beacon NGHam packet with EPS data. */
#define FLORIPASAT_PACKET_BEACON_NGHAM_TTC_DATA             0x02    /**< Beacon NGHam packet with TTC data. */
#define FLORIPASAT_PACKET_BEACON_AX25_OBDH_DATA             0x03    /**< Beacon AX25 packet with OBDH data. */
#define FLORIPASAT_PACKET_BEACON_AX25_EPS_DATA              0x04    /**< Beacon AX25 packet with EPS data. */
#define FLORIPASAT_PACKET_BEACON_AX25_TTC_DATA              0x05    /**< Beacon AX25 packet with TTC data. */

// Downlink packets
#define FLORIPASAT_PACKET_DOWNLINK_TELEMETRY                0x10    /**< Downlink packet with telemetry data. */
#define FLORIPASAT_PACKET_DOWNLINK_PING_ANSWER              0x11    /**< Ping answer. */
#define FLORIPASAT_PACKET_DOWNLINK_DATA_REQUEST_ANSWER      0x12    /**< Data request answer. */
#define FLORIPASAT_PACKET_DOWNLINK_HIBERNATION_FEEDBACK     0x13    /**< Hibernation feedback. */
#define FLORIPASAT_PACKET_DOWNLINK_CHARGE_RESET_FEEDBACK    0x14    /**< Charge reset feedback. */
#define FLORIPASAT_PACKET_DOWNLINK_MESSAGE_BROADCAST        0x15    /**< Message Broadcast. */
#define FLORIPASAT_PACKET_DOWNLINK_PAYLOAD_X_STATUS         0x16    /**< Payload X status. */
#define FLORIPASAT_PACKET_DOWNLINK_RUSH_STATUS              0x17    /**< RUSH status. */

// Uplink packets
#define FLORIPASAT_PACKET_UPLINK_PING_REQUEST               0x20    /**< Ping request. */
#define FLORIPASAT_PACKET_UPLINK_DATA_REQUEST               0x21    /**< Data request. */
#define FLORIPASAT_PACKET_UPLINK_ENTER_HIBERNATION          0x22    /**< Enter hibernation. */
#define FLORIPASAT_PACKET_UPLINK_LEAVE_HIBERNATION          0x23    /**< Leave hibernation. */
#define FLORIPASAT_PACKET_UPLINK_CHARGE_RESET               0x24    /**< Charge reset. */
#define FLORIPASAT_PACKET_UPLINK_BROADCAST_MESSAGE          0x25    /**< Broadcast message. */
#define FLORIPASAT_PACKET_UPLINK_PAYLOAD_X_STATUS_REQUEST   0x26    /**< Payload X status request. */
#define FLORIPASAT_PACKET_UPLINK_PAYLOAD_X_SWAP             0x27    /**< Payload X swap. */
#define FLORIPASAT_PACKET_UPLINK_PAYLOAD_X_DATA_UPLOAD      0x28    /**< Payload data upload. */
#define FLORIPASAT_PACKET_UPLINK_RUSH_ENABLE                0x29    /**< RUSH enable. */

#endif // PACKETS_IDS_H_

//! \} End of packets_ids group
