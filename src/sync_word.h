/*
 * sync_word.h
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
 * \brief Sync Word definition.
 * 
 * \author Gabriel Mariano Marcelino <gabriel.mm8@gmail.com>
 * 
 * \version 0.4.0
 * 
 * \date 06/04/2019
 * 
 * \defgroup sync_word Sync Word
 * \{
 */

#ifndef SYNC_WORD_H_
#define SYNC_WORD_H_

#include <stdint.h>

#include <vector>
#include <string>
#include <bitset>
#include <iostream>

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
        SyncWord();

        /**
         * \brief Constructor (overloaded).
         *
         * \param[in] bytes is a std::vector with the sync word sequence.
         *
         * \return None.
         */
        SyncWord(std::vector<uint8_t> bytes);

        /**
         * \brief Sets the sync word.
         *
         * \param[in] bytes is a std::vector with the sync word sequence.
         *
         * \return None.
         */
        void set_sync_word(std::vector<uint8_t> bytes);

        /**
         * \brief Appends a new byte to the sync word sequence.
         *
         * \param[in] byte is a byte to append to the sync word sequence.
         *
         * \return None.
         */
        void append(uint8_t byte);

        /**
         * \brief Gets the sync word bytes.
         *
         * \return The sync word as a vector of bytes.
         */
        std::vector<uint8_t> get_bytes();

        /**
         * \brief cout overload.
         *
         * \param[in] os is the ostream object.
         * \param[in] sync_word is the SyncWord object.
         *
         * \return An ostream object.
         */
        friend std::ostream& operator<<(std::ostream& os, const SyncWord& sync_word);
};

#endif // SYNC_WORD_H_

//! \} End of sync_word group
