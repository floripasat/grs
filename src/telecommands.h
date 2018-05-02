/*
 * telecommands.h
 * 
 * Copyright (C) 2018, Federal University of Santa Catarina.
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
 * \file telecommands.h
 * 
 * \brief .
 * 
 * \author Elder Dominghini Tramontin <elderdtramontin@gmail.com>
 * 
 * \version 1.0-dev
 * 
 * \date 13/04/2018
 * 
 * \defgroup telecommands Telecommands
 * \ingroup fsat-grs
 * \{
 */

#ifndef TELECOMMANDS_H_
#define TELECOMMANDS_H_

//UPLINK COMMANDS
#define REQUEST_DATA_TELECOMMAND            (0x7764)    /**< uplink command to request whole data orbit - dw    */
#define REQUEST_SHUTDOWN_TELECOMMAND        (0x6473)    /**< uplink command to request a 24 hours shutdown - sd */
#define REQUEST_PING_TELECOMMAND            (0x6770)    /**< ping request - pg                                  */

#define OLDER_PACKAGES_ORIGIN               0
#define NEWER_PACKAGES_ORIGIN               1

/**
 * \struct request_data_packet_t
 *
 * \brief .
 */
typedef struct {
    uint16_t flags;             /**< modules flags to request just the wanted data*/
    uint8_t packages_count;     /**< number of packages to read, from offset */
    uint8_t packages_origin;    /**< position used as reference for the offset */
    int32_t packages_offset;    /**< number of packages to offset from origin */
} request_data_packet_t;

/**
 * \struct telecommand_t
 *
 * \brief .
 */
typedef struct {
    uint8_t ID[6];
    uint16_t request_action;    /**< the action (send data, shutdown, ping..) */
    uint8_t arguments[8];
    uint8_t reserved[12];
} telecommand_t;

#endif // TELECOMMANDS_H_

//! \} End of telecommands group
