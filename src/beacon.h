/*
 * beacon.h
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
 * \brief Beacon decoder definition.
 * 
 * \author Gabriel Mariano Marcelino <gabriel.mm8@gmail.com>
 * 
 * \version 0.4.1
 * 
 * \date 07/04/2019
 * 
 * \defgroup beacon Beacon
 * \{
 */

#ifndef BEACON_H_
#define BEACON_H_

#include <string>
#include <mutex>

#include "fsat-grs.h"
#include "udp_server.h"
#include "sync_word.h"
#include "packet_sniffer.h"
#include "ngham_plus.h"
#include "ax25.h"
#include "packets/beacon_data.h"
#include "packets/obdh_data.h"
#include "packets/eps_data.h"
#include "packets/ttc_data.h"

class FSatGRS;

/**
 * \brief Beacon receiver.
 */
class Beacon
{
    public:

        /**
         * \brief Constructor.
         *
         * \return None.
         */
        Beacon();

        /**
         * \brief Constructor with start (overloaded).
         *
         * \param[in] adr is the UDP client address.
         * \param[in] port is the UDP client port.
         * \param[in] sw is the beacon sync word.
         *
         * \return None.
         */
        Beacon(std::string adr, unsigned int port, SyncWord sw);

        /**
         * \brief Destructor.
         *
         * \return None.
         */
        ~Beacon();

        /**
         * \brief Initializes the beacon receiver.
         *
         * \param[in] adr is the UDP client address.
         * \param[in] port is the UDP client port.
         * \param[in] sw is the beacon sync word.
         *
         * \return TRUE/FALSE if successful or not.
         */
        bool start(std::string adr, unsigned int port, SyncWord sw);

        /**
         * \brief Stops the beacon receiver.
         *
         * \return None.
         */
        void stop();

        /**
         * \brief Runs the beacon receiver.
         *
         * \param[in] caller is a pointer to the beacon receiver caller.
         *
         * \return None.
         */
        void run(FSatGRS *caller);

        /**
         * \brief Gets the last received beacon data.
         *
         * \return The beacon data from the buffer.
         */
        grs::BeaconData get_data();

    private:

        SyncWord *sync_word;            /**< Beacon sync word. */
        UDPServer *udp_server;          /**< UDP server. */
        PacketSniffer *sniffer;         /**< Packet sniffer. */
        NGHamPlus *ngham;               /**< NGHam decoder. */
        AX25 *ax25;                     /**< AX25 decoder. */
        bool can_run;                   /**< Can run flag. */
        mutable std::mutex data_mutex;  /**< Beacon data buffer. */
        grs::BeaconData data;           /**< Beacon data buffer. */
};

#endif // BEACON_H_

//! \} End of beacon group
