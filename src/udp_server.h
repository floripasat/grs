/*
 * udp_server.h
 * 
 * Copyright (C) 2013,  Made to Order Software Corp.
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
 * \brief UDP server definition.
 * 
 * \author Gabriel Mariano Marcelino <gabriel.mm8@gmail.com>
 * 
 * \version 0.3.5
 * 
 * \date 05/04/2019
 * 
 * \defgroup udp_server UDP Server
 * \{
 */

#ifndef UDP_SERVER_H_
#define UDP_SERVER_H_

#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdint.h>
#include <vector>

/**
 * \brief UDP server.
 */
class udp_server
{
    public:

        /**
         * \brief Initialize a UDP server object.
         *
         * This function initializes a UDP server object making it ready to
         * receive messages.
         *
         * The server address and port are specified in the constructor so
         * if you need to receive messages from several different addresses
         * and/or port, you'll have to create a server for each.
         *
         * The address is a string and it can represent an IPv4 or IPv6
         * address.
         *
         * Note that this function calls connect() to connect the socket
         * to the specified address. To accept data on different UDP addresses
         * and ports, multiple UDP servers must be created.
         *
         * \note The socket is open in this process. If you fork() or exec() then the
         * socket will be closed by the operating system.
         *
         * \warning We only make use of the first address found by getaddrinfo(). All
         * the other addresses are ignored.
         *
         * \exception udp_client_server_runtime_error
         * The udp_client_server_runtime_error exception is raised when the address
         * and port combinaison cannot be resolved or if the socket cannot be
         * opened.
         *
         * \param[in] addr The address we receive on.
         * \param[in] port The port we receive from.
         *
         * \return None.
         */
        udp_server(const std::string& addr, int port);

        /**
         * \brief Clean up the UDP server.
         *
         * This function frees the address info structures and close the socket.
         *
         * \return None.
         */
        ~udp_server();

        /**
         * \brief The socket used by this UDP server.
         *
         * This function returns the socket identifier. It can be useful if you are
         * doing a select() on many sockets.
         *
         * \return The socket of this UDP server.
         */
        int get_socket() const;

        /**
         * \brief The port used by this UDP server.
         *
         * This function returns the port attached to the UDP server. It is a copy
         * of the port specified in the constructor.
         *
         * \return The port of the UDP server.
         */
        int get_port() const;

        /**
         * \brief Return the address of this UDP server.
         *
         * This function returns a verbatim copy of the address as passed to the
         * constructor of the UDP server (i.e. it does not return the canonalized
         * version of the address.)
         *
         * \return The address as passed to the constructor.
         */
        std::string get_addr() const;

        /**
         * \brief Wait on a message.
         *
         * This function waits until a message is received on this UDP server.
         * There are no means to return from this function except by receiving
         * a message. Remember that UDP does not have a connect state so whether
         * another process quits does not change the status of this UDP server
         * and thus it continues to wait forever.
         *
         * Note that you may change the type of socket by making it non-blocking
         * (use the get_socket() to retrieve the socket identifier) in which
         * case this function will not block if no message is available. Instead
         * it returns immediately.
         *
         * \param[in,out] msg The buffer where the message is saved.
         * \param[in] max_size The maximum size the message (i.e. size of the \p msg buffer.)
         *
         * \return The number of bytes read or -1 if an error occurs.
         */
        int recv(char *msg, size_t max_size);

        /**
         * \brief Wait for data to come in.
         *
         * This function waits for a given amount of time for data to come in. If
         * no data comes in after max_wait_ms, the function returns with -1 and
         * errno set to EAGAIN.
         *
         * The socket is expected to be a blocking socket (the default,) although
         * it is possible to setup the socket as non-blocking if necessary for
         * some other reason.
         *
         * This function blocks for a maximum amount of time as defined by
         * max_wait_ms. It may return sooner with an error or a message.
         *
         * \param[in,out] msg The buffer where the message will be saved.
         * \param[in] max_size The size of the \p msg buffer in bytes.
         * \param[in] max_wait_ms The maximum number of milliseconds to wait for a message.
         *
         * \return -1 if an error occurs or the function timed out, the number of bytes received otherwise.
         */
        int timed_recv(char *msg, size_t max_size, int max_wait_ms);

        /**
         * \brief Wait on a message (overloaded).
         *
         * \param[in] max_size The maximum size the message (i.e. size of the \p msg buffer.)
         *
         * \return An std::vector with the received message (empty vector if an error occurs).
         */
        std::vector<uint8_t> receive(size_t max_size);

        /**
         * \brief Wait for data to come in (overloaded).
         *
         * \param[in] max_size The size of the \p msg buffer in bytes.
         * \param[in] timeout The maximum number of milliseconds to wait for a message.
         *
         * \return An std::vector with the received message (empty vector if an error occurs).
         */
        std::vector<uint8_t> receive(size_t max_size, unsigned int timeout);

    private:

        int f_socket;                   /**< UDP server socket. */
        int f_port;                     /**< UDP server port. */
        std::string f_addr;             /**< UDP server address. */
        struct addrinfo *f_addrinfo;    /**< UDP server address info structure. */
};

#endif // UDP_SERVER_H_

//! \} End of udp_server group
