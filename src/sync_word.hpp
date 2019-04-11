/*
 * sync_word.hpp
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
 * \brief Sync Word object.
 * 
 * \author Gabriel Mariano Marcelino <gabriel.mm8@gmail.com>
 * 
 * \version 0.3.7
 * 
 * \date 06/04/2019
 * 
 * \defgroup sync_word Sync Word
 * \{
 */

#ifndef SYNC_WORD_HPP_
#define SYNC_WORD_HPP_

#include <stdint.h>

#include <vector>
#include <string>
#include <bitset>
#include <iostream>

#include "byte_buffer.hpp"

/**
 * \brief Sync Word object.
 */
class SyncWord: public std::vector<bool>
{
    public:

        /**
         * \brief Constructor.
         *
         * \return None.
         */
        SyncWord()
        {
        }

        /**
         * \brief Constructor (overloaded).
         *
         * \param[in] bytes is a std::vector with the sync word sequence.
         *
         * \return None.
         */
        SyncWord(std::vector<uint8_t> bytes)
        {
            this->set_sync_word(bytes);
        }

        /**
         * \brief Sets the sync word.
         *
         * \param[in] bytes is a std::vector with the sync word sequence.
         *
         * \return None.
         */
        void set_sync_word(std::vector<uint8_t> bytes)
        {
            this->clear();

            for(unsigned int i=0; i<bytes.size(); i++)
            {
                this->append(bytes[i]);
            }
        }

        /**
         * \brief Appends a new byte to the sync word sequence.
         *
         * \param[in] byte is a byte to append to the sync word sequence.
         *
         * \return None.
         */
        void append(uint8_t byte)
        {
            std::string byte_str = std::bitset<8>(byte).to_string();

            for(unsigned int i=0; i<byte_str.size(); i++)
            {
                switch(byte_str[i])
                {
                    case '0':   this->push_back(false);   break;
                    case '1':   this->push_back(true);    break;
                }
            }
        }

        /**
         * \brief Gets the sync word bytes.
         *
         * \return The sync word as a vector of bytes.
         */
        std::vector<uint8_t> get_bytes()
        {
            ByteBuffer byte_buffer;
            vector<uint8_t> sync_word_bytes;

            for(unsigned int i=0; i<this->size(); i++)
            {
                byte_buffer.push(this->at(i));

                if (byte_buffer.is_full())
                {
                    sync_word_bytes.push_back(byte_buffer.to_byte());
                    byte_buffer.clear();
                }
            }

            return sync_word_bytes;
        }

        /**
         * \brief cout overload.
         *
         * \param[in] os is the ostream object.
         * \param[in] sync_word is the SyncWord object.
         *
         * \return An ostream object.
         */
        friend std::ostream& operator<<(std::ostream& os, const SyncWord& sync_word)
        {
            for(unsigned int i=0; i<sync_word.size(); i++)
            {
                os << sync_word.at(i);
            }

            return os;
        }
};

#endif // SYNC_WORD_HPP_

//! \} End of sync_word group
