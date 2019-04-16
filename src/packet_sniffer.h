/*
 * packet_sniffer.h
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
 * \brief Packet sniffer definition.
 * 
 * \author Gabriel Mariano Marcelino <gabriel.mm8@gmail.com>
 * 
 * \version 0.4.0
 * 
 * \date 05/04/2019
 * 
 * \defgroup packet_sniffer Packet Sniffer
 * \{
 */

#ifndef PACKET_SNIFFER_H_
#define PACKET_SNIFFER_H_

#include <stdint.h>

#include <vector>
#include <climits>

#include "sync_word.h"
#include "bit_buffer.h"
#include "byte_buffer.h"
#include "packet_buffer.h"

/**
 * \brief Sync word detector.
 */
class PacketSniffer
{
    public:

        /**
         * \brief Constructor.
         *
         * \return None.
         */
        PacketSniffer();

        /**
         * \brief Constructor (overloaded).
         *
         * \param[in] sw is the new sync word to search.
         * \param[in] len is the maximum lenght of the packet buffer.
         *
         * \return None.
         */
        PacketSniffer(std::vector<uint8_t> sw, unsigned int len=USHRT_MAX);

        /**
         * \brief Constructor (overloaded).
         *
         * \param[in] sw is the new sync word to search.
         * \param[in] len is the maximum lenght of the packet buffer.
         *
         * \return None.
         */
        PacketSniffer(SyncWord sw, unsigned int len=USHRT_MAX);

        /**
         * \brief Destructor.
         *
         * \return None.
         */
        ~PacketSniffer();

        /**
         * \brief Sets the sync word to search for incoming packets.
         *
         * \param[in] sw is the new sync word to search.
         *
         * \return None.
         */
        void set_sync_word(std::vector<uint8_t> sw);

        /**
         * \brief Sets the sync word to search for incoming packets.
         *
         * \param[in] sw is the new sync word to search.
         *
         * \return None.
         */
        void set_sync_word(SyncWord sw);

        /**
         * \brief Sets the maximum size of the packet buffer.
         *
         * \param[in] max is the maximum size in bytes of the packet buffer.
         *
         * \return None.
         */
        void set_packet_buffer_size(unsigned int max);

        /**
         * \brief Searches for incoming packets by detecting the sync word sequence.
         *
         * \param[in] bit is an incoming bit from the demodulator.
         *
         * \return None.
         */
        void sniff(bool bit);

        /**
         * \brief Gets the n bytes from the packet buffer.
         *
         * \param[in] n is the number of bytes to get from the packet buffer.
         *
         * \return n bytes from the packet buffer as a vector.
         */
        PacketBuffer get_packet_bytes(unsigned int n);

        /**
         * \brief Gets the number of available bytes in the packet buffer.
         *
         * \return The number of available bytes.
         */
        unsigned int available_bytes();

    private:

        /**
         * \brief Sync word bytes to search.
         */
        SyncWord sync_word;

        /**
         * \brief Sync bytes buffer.
         */
        BitBuffer sync_word_buffer;

        /**
         * \brief Byte buffer.
         */
        ByteBuffer byte_buffer;

        /**
         * \brief Packet buffer (bytes after a sync word detection).
         */
        PacketBuffer packet_buffer;
};

#endif // PACKET_SNIFFER_H_

//! \} End of packet_sniffer group
