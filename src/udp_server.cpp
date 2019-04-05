/*
 * udp_server.cpp
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
 * \brief UDP server implementation.
 * 
 * \author Gabriel Mariano Marcelino <gabriel.mm8@gmail.com>
 * 
 * \version 0.3.5
 * 
 * \date 05/04/2019
 * 
 * \addtogroup udp_server
 * \{
 */

#include <stdexcept>
#include <unistd.h>
#include <limits.h>

#include "udp_server.h"

using namespace std;

udp_server::udp_server(const string& addr, int port)
    : f_port(port), f_addr(addr)
{
    char decimal_port[16];
    snprintf(decimal_port, sizeof(decimal_port), "%d", f_port);
    decimal_port[sizeof(decimal_port) / sizeof(decimal_port[0]) - 1] = '\0';

    struct addrinfo hints;
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_DGRAM;
    hints.ai_protocol = IPPROTO_UDP;
    int r = getaddrinfo(addr.c_str(), decimal_port, &hints, &f_addrinfo);

    if (r != 0 || f_addrinfo == NULL)
    {
        throw runtime_error(("Invalid address or port for UDP socket: \"" + addr + ":" + decimal_port + "\"").c_str());
    }

    f_socket = socket(f_addrinfo->ai_family, SOCK_DGRAM | SOCK_CLOEXEC, IPPROTO_UDP);
    if (f_socket == -1)
    {
        freeaddrinfo(f_addrinfo);
        throw runtime_error(("Could not create UDP socket for: \"" + addr + ":" + decimal_port + "\"").c_str());
    }

    r = bind(f_socket, f_addrinfo->ai_addr, f_addrinfo->ai_addrlen);
    if (r != 0)
    {
        freeaddrinfo(f_addrinfo);
        close(f_socket);
        throw runtime_error(("Could not bind UDP socket with: \"" + addr + ":" + decimal_port + "\"").c_str());
    }
}

udp_server::~udp_server()
{
    freeaddrinfo(f_addrinfo);
    close(f_socket);
}

int udp_server::get_socket() const
{
    return f_socket;
}

int udp_server::get_port() const
{
    return f_port;
}

string udp_server::get_addr() const
{
    return f_addr;
}

int udp_server::recv(char *msg, size_t max_size)
{
    return ::recv(f_socket, msg, max_size, 0);
}

vector<uint8_t> udp_server::receive(size_t max_size)
{
    char msg[USHRT_MAX];

    int ret = this->recv(msg, max_size);

    vector<uint8_t> pkt;

    if (ret < 0)
    {
        return pkt;
    }

    for(size_t i=0; i<ret; i++)
    {
        pkt.push_back(msg[i]);
    }

    return pkt;
}

int udp_server::timed_recv(char *msg, size_t max_size, int max_wait_ms)
{
    fd_set s;
    FD_ZERO(&s);
    FD_SET(f_socket, &s);
    struct timeval timeout;
    timeout.tv_sec = max_wait_ms / 1000;
    timeout.tv_usec = (max_wait_ms % 1000) * 1000;

    int retval = select(f_socket + 1, &s, &s, &s, &timeout);
    if (retval == -1)
    {
        // select() set errno accordingly
        return -1;
    }

    if (retval > 0)
    {
        // our socket has data
        return ::recv(f_socket, msg, max_size, 0);
    }

    // our socket has no data
    errno = EAGAIN;

    return -1;
}

vector<uint8_t> udp_server::receive(size_t max_size, unsigned int timeout)
{
    char msg[USHRT_MAX];
    int ret = this->timed_recv(msg, max_size, timeout);

    vector<uint8_t> pkt;

    if (ret < 0)
    {
        return pkt;
    }

    for(size_t i=0; i<ret; i++)
    {
        pkt.push_back(msg[i]);
    }

    return pkt;
}

//! \} End of udp_server group
