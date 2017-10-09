/*
 * packets.h
 * 
 * Copyright (C) 2017, Federal University of Santa Catarina.
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
 * \file packets.h
 * 
 * \brief Packets class.
 * 
 * \author Gabriel Mariano Marcelino <gabriel.mm8@gmail.com>
 * 
 * \version 2.0
 * 
 * \date 06/10/2017
 * 
 * \defgroup packets Packets
 * \{
 */

#ifndef PACKETS_H_
#define PACKETS_H_

#include <vector>
#include <string>
#include <fstream>
#include <stdint.h>

#include "event_log.h"
#include "packet_data.h"
#include "protocol_statistic.h"

#define PACKETS_SYNC_BYTE_S0_DEFAULT        0x7E
#define PACKETS_SYNC_BYTE_S1_DEFAULT        0x2A
#define PACKETS_SYNC_BYTE_S2_DEFAULT        0xE6
#define PACKETS_SYNC_BYTE_S3_DEFAULT        0x5D

/**
 * \class Packets
 * 
 * \brief 
 */
class Packets: public std::ifstream
{
    protected:
        /**
         * \brief 
         */
        std::vector<uint8_t> preamble;
        /**
         * \brief 
         */
        std::vector<uint8_t> sync_bytes;
        /**
         * \brief 
         */
        bool receive_pkt;
        /**
         * \brief 
         */
        std::vector<uint8_t> sync_bytes_buffer;
        /**
         * \brief 
         */
        std::vector<uint8_t> byte_buffer;
        /**
         * \brief 
         */
        bool make_log;
        /**
         * \brief 
         */
        Log *log_pkts;
        /**
         * \brief 
         */
        bool make_data_log;
        /**
         * \brief 
         */
        Log *log_data_pkts;
        /**
         * \brief 
         */
        EventLog *event_log;
        /**
         * \brief 
         */
        PacketData *packet_data;
        /**
         * \brief 
         */
        ProtocolStatistic *protocol_statistic;
        /**
         * \brief 
         */
        uint64_t prev_fin_byte_counter;
        /**
         * \brief 
         */
        uint64_t fin_byte_counter;
    public:
        /**
         * \brief 
         * 
         * \return None
         */
        Packets();
        /**
         * \brief Class destructor.
         * 
         * \return None
         */
        ~Packets();
        /**
         * \brief Variables initialization.
         * 
         * \return None
         */
        void InitPkts();
        /**
         * \brief Sets the preamle value.
         * 
         * \return None
         */
        void SetPreamble(uint8_t byte, uint8_t quant);
        /**
         * \brief Sets the sync. word.
         * 
         * \param s0
         * \param s1
         * \param s2
         * \param s3
         * 
         * \return None
         */
        void SetSyncBytes(uint8_t s0, uint8_t s1, uint8_t s2, uint8_t s3);
        /**
         * \brief 
         * 
         * \param b
         * 
         * \return 
         */
        virtual bool ProcessByte(uint8_t b);
        /**
         * \brief Search for packets in a binary file.
         * 
         * \param file
         * 
         * \return None
         */
        virtual void Search(const char *file);
        /**
         * \brief Log the payload of a found packet.
         * 
         * \return The respective log line of the packet payload to the log file.
         */
        std::string LogPayload();
};

#endif // PACKETS_H_

//! \} End of packets group
