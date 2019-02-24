/*
 * payload_x_upload.h
 * 
 * Copyright (C) 2019, Universidade Federal de Santa Catarina.
 * 
 * This file is part of FloripaSat-GRS.
 * 
 * FloripaSat-GRS is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * FloripaSat-GRS is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public License
 * along with FloripaSat-GRS. If not, see <http://www.gnu.org/licenses/>.
 * 
 */

/**
 * \brief Payload X upload command definition.
 * 
 * \author Gabriel Mariano Marcelino <gabriel.mm8@gmail.com>
 * 
 * \version 0.2.12
 * 
 * \date 23/02/2019
 * 
 * \defgroup payload_x_upload Payload X Upload
 * \{
 */

#ifndef PAYLOAD_X_UPLOAD_H_
#define PAYLOAD_X_UPLOAD_H_

#include <fstream>
#include <string>
#include <vector>
#include <stdint.h>

#define PAYLOAD_X_UPLOAD_DEFAULT_BLOCKS_SIZE            84

/**
 * \brief Payload X upload command.
 */
class PayloadXUpload: public std::ifstream
{
    private:

        /**
         * \brief Bitfile blocks size.
         */
        unsigned int block_size;

        /**
         * \brief Blocks counter (transferred blocks).
         */
        uint32_t block_counter;

        /**
         * \brief Blocks of the given bitfile.
         */
        std::vector<std::vector<uint8_t> > blocks;

    public:

        /**
         * \brief Constructor.
         *
         * \return None.
         */
        PayloadXUpload();

        /**
         * \brief Overloaded constructor.
         *
         * \param[in] filename is the bitfile to open and read.
         * \param[in] blk_size is the block size in bytes.
         *
         * \return None.
         */
        PayloadXUpload(std::string filename, unsigned int blk_size=PAYLOAD_X_UPLOAD_DEFAULT_BLOCKS_SIZE);

        /**
         * \brief Destructor.
         *
         * \return None.
         */
        ~PayloadXUpload();

        /**
         * \brief Sets the blocks size.
         *
         * \param[in] size is the new blocks size in bytes.
         *
         * \return None.
         */
        void set_block_size(unsigned int size);

        /**
         * \brief Gets the blocks size.
         *
         * \return The size of the blocks in bytes.
         */
        unsigned int get_block_size();

        /**
         * \brief Gets the number of required blocks of the given biftile.
         *
         * \return The number of required blocks.
         */
        unsigned int get_number_of_required_blocks();

        /**
         * \brief Gets the number of transmitted blocks.
         *
         * \return The number of transmitted blocks.
         */
        unsigned int get_number_of_transmitted_blocks();

        /**
         * \brief Gets the number of remaining blocks.
         *
         * \return The number of remaining blocks.
         */
        unsigned int get_number_of_remaining_blocks();

        /**
         * \brief Splits the given bitfile in blocks.
         *
         * \return None.
         */
        void split_bitfile();

        /**
         * \brief Gets the next block to transmit.
         *
         * \return The next block to transmit.
         */
        std::vector<uint8_t> get_next_block();

        /**
         * \brief Gets the progress of the upload.
         *
         * \return The percentage of transmitted blocks.
         */
        double get_progress();
};

#endif // PAYLOAD_X_UPLOAD_H_

//! \} End of payload_x_upload group
