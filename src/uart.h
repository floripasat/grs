/*
 * uart.h
 * 
 * Copyright (c) 2017, Federal University of Santa Catarina
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
 * \file uart.h
 * 
 * \brief Serial port class header.
 * 
 * \author Gabriel Mariano Marcelino <gabriel.mm8@gmail.com>
 * 
 * \version 1.0-dev
 * 
 * \date 10/11/2016
 * 
 * \defgroup uart UART
 * \ingroup src
 * \{ 
 */

#ifndef UART_H_
#define UART_H_

#include <stdint.h>

/**
 * \class UART
 * \brief UART port class.
 * 
 * This class implements the serial port.
 */
class UART
{
        int fd;         /**< File descriptor of the serial device. */
    public:
        /**
         * \brief The constructor of the class.
         * 
         * This constructor only initializes the file descriptor.
         */
        UART();
        /**
         * \brief The constructor of the class with the opening the serial port.
         * 
         * \param *device is the device to open.
         * \param baudrate is the comunication baudrate.
         */
        UART(const char* device, int baudrate);
        /**
         * \brief The destructor of the class
         */
        ~UART();
        /**
         * \brief Opens the serial port.
         * 
         * \return It returns:
         *              -\b TRUE if the port was open.
         *              -\b FALSE if the port was not open.
         *              .
         */
        bool Open(const char* device, int baudrate);
        /**
         * \brief Close the serial port.
         * 
         * \return It returns:
         *              -\b TRUE if the serial port was closed.
         *              -\b FALSE if the serial port was not closed.
         *              .
         */
        bool Close();
        /**
         * \brief Checks if the serial port is open.
         * 
         * \return It returns:
         *              -\b TRUE if the serial port is open.
         *              -\b FALSE if the serial port is not open.
         *              .
         */
        bool isOpened();
        /**
         * \brief Write a message in the serial port.
         * 
         * \param *message is a pointer to an array with the message.
         * \param size is the size of the message (array).
         * 
         * \return It returns:
         *              -\b TRUE if the message was written.
         *              -\b FALSE if the message was not written.
         *              .
         */
        bool Write(uint8_t *message, uint8_t size);
        /**
         * \brief Returns data availability in the reception buffer.
         * 
         * \return Returns the number of bytes available in the serial port.
         */
        int DataAvailable();
        /**
         * \brief Reads a single byte from the reception buffer.
         * 
         * \return The first available byte in the reception buffer.
         */
        uint8_t GetByte();
        /**
         * \brief Flush the serial buffers (TX and RX).
         * 
         * \return None
         */
        void Flush();
};

#endif // UART_H_

//! \} End of uart group
