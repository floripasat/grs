/*
 * beacon.cpp
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
 * \brief Beacon decoder implementation.
 * 
 * \author Gabriel Mariano Marcelino <gabriel.mm8@gmail.com>
 * 
 * \version 0.4.8
 * 
 * \date 07/04/2019
 * 
 * \addtogroup beacon
 * \{
 */

#include "beacon.h"
#include "packets/packets_ids.h"
#include "packets/obdh_data.h"
#include "packets/eps_data.h"
#include "packets/ttc_data.h"

#define BEACON_UDP_SERVER_MAX_BYTES     1472
#define BEACON_UDP_SERVER_TIMEOUT_MS    100

#define BEACON_PACKET_MIN_LEN           30
#define BEACON_PACKET_MAX_LEN           90

using namespace std;
using namespace grs;

Beacon::Beacon()
    : can_run(false)
{

}

Beacon::Beacon(string adr, unsigned int port, SyncWord sw)
    : Beacon()
{
    this->start(adr, port, sw);
}

Beacon::~Beacon()
{

}

bool Beacon::start(string adr, unsigned int port, SyncWord sw)
{
    this->udp_server = new UDPServer;

    if (!this->udp_server->connect(adr, port))
    {
        delete this->udp_server;

        return false;
    }

    this->sync_word = new SyncWord(sw);

    this->sniffer = new PacketSniffer(sw, (sw.size()/8) + BEACON_PACKET_MAX_LEN);

    this->ngham = new NGHamPlus;

    this->ax25 = new AX25;

    this->can_run = true;

    return true;
}

void Beacon::stop()
{
    if (this->can_run)
    {
        delete this->udp_server;

        delete this->sync_word;

        delete this->sniffer;

        delete this->ngham;

        delete this->ax25;
    }

    this->can_run = false;
}

void Beacon::run(FSatGRS *caller)
{
    while(this->can_run)
    {
        auto bits = this->udp_server->receive(BEACON_UDP_SERVER_MAX_BYTES, BEACON_UDP_SERVER_TIMEOUT_MS);

        for(unsigned int i=0; i<bits.size(); i++)
        {
            this->sniffer->sniff(bool(bits[i]));
        }

        if (this->sniffer->available_bytes() > BEACON_PACKET_MIN_LEN)
        {
            auto raw_bytes = this->sniffer->get_packet_bytes(BEACON_PACKET_MAX_LEN);

            PacketBuffer pkt;
            for(unsigned int i=this->sync_word->size()/8; i<raw_bytes.size(); i++)  // Removing the sync word bytes before the ngham decodification
            {
                pkt.push(raw_bytes[i]);
            }

            auto ngham_pl = this->ngham->decode(pkt);

            if (!ngham_pl.empty())
            {
                Payload payload(ngham_pl);

                lock_guard<mutex> lock(this->data_mutex);

                switch(payload.id)
                {
                    case FLORIPASAT_PACKET_BEACON_NGHAM_OBDH_DATA:  this->data = OBDHData(payload);     break;
                    case FLORIPASAT_PACKET_BEACON_NGHAM_EPS_DATA:   this->data = EPSData(payload);      break;
                    case FLORIPASAT_PACKET_BEACON_NGHAM_TTC_DATA:   this->data = TTCData(payload);      break;
                    default:                                        this->data = BeaconData();          break;
                }

//                caller->notify_new_beacon_data();
            }

            auto ax25_pl = this->ax25->decode(pkt);     // Removing the sync word bytes before the ngham decodification

            if (!ax25_pl.empty())
            {
                Payload payload(ax25_pl);

                lock_guard<mutex> lock(this->data_mutex);

                switch(payload.id)
                {
                    case FLORIPASAT_PACKET_BEACON_AX25_OBDH_DATA:   this->data = OBDHData(payload);     break;
                    case FLORIPASAT_PACKET_BEACON_AX25_EPS_DATA:    this->data = EPSData(payload);      break;
                    case FLORIPASAT_PACKET_BEACON_AX25_TTC_DATA:    this->data = TTCData(payload);      break;
                    default:                                        this->data = BeaconData();          break;
                }

//                caller->notify_new_beacon_data();
            }
        }
    }
}

BeaconData Beacon::get_data()
{
    lock_guard<mutex> lock(this->data_mutex);

    return this->data;
}

//! \} End of beacon group
