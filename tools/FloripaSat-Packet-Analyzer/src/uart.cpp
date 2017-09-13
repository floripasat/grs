/*
 * uart.cpp
 * 
 * Copyright (C) 2017, Universidade Federal de Santa Catarina
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
 * \file uart.cpp
 * 
 * \brief UART port class implementation.
 * 
 * \author Gabriel Mariano Marcelino <gabriel.mm8@gmail.com>
 * 
 * \version 1.0
 * 
 * \date 10/11/2016
 * 
 * \addtogroup uart
 * \{ 
 */

#include "uart.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>

UART::UART()
{
    fd = 0;
}

UART::UART(const char* device, int baudrate)
{
    fd = 0;
    Open(device, baudrate);
}

UART::~UART()
{
    Close();
}

bool UART::Open(const char* device, int baudrate)
{
    struct termios options;
    speed_t myBaud;
    int status;

    switch(baudrate)
    {
        case     50:    myBaud =     B50; break;
        case     75:    myBaud =     B75; break;
        case    110:    myBaud =    B110; break;
        case    134:    myBaud =    B134; break;
        case    150:    myBaud =    B150; break;
        case    200:    myBaud =    B200; break;
        case    300:    myBaud =    B300; break;
        case    600:    myBaud =    B600; break;
        case   1200:    myBaud =   B1200; break;
        case   1800:    myBaud =   B1800; break;
        case   2400:    myBaud =   B2400; break;
        case   4800:    myBaud =   B4800; break;
        case   9600:    myBaud =   B9600; break;
        case  19200:    myBaud =  B19200; break;
        case  38400:    myBaud =  B38400; break;
        case  57600:    myBaud =  B57600; break;
        case 115200:    myBaud = B115200; break;
        case 230400:    myBaud = B230400; break;

        default:
            return false;
    }

    if ((fd = open(device, O_RDWR | O_NOCTTY | O_NDELAY | O_NONBLOCK)) == -1)
    {
        return false;
    }

    fcntl(fd, F_SETFL, O_RDWR);

    // Get and modify current options:

    tcgetattr(fd, &options);

    cfmakeraw(&options);
    cfsetispeed(&options, myBaud);
    cfsetospeed(&options, myBaud);

    options.c_cflag |= (CLOCAL | CREAD);
    options.c_cflag &= ~PARENB;
    options.c_cflag &= ~CSTOPB;
    options.c_cflag &= ~CSIZE;
    options.c_cflag |= CS8;
    options.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);
    options.c_oflag &= ~OPOST;

    options.c_cc [VMIN]  =   0;
    options.c_cc [VTIME] = 100;     // Ten seconds (100 deciseconds)

    tcsetattr(fd, TCSANOW | TCSAFLUSH, &options);

    ioctl(fd, TIOCMGET, &status);

    status |= TIOCM_DTR;
    status |= TIOCM_RTS;

    ioctl(fd, TIOCMSET, &status);

    usleep(10000) ; // 10 ms
    
    return true;
}

bool UART::Close()
{
    if (close(fd) >= 0)
        return true;
    else
        return false;
}

bool UART::isOpened()
{
    if (fd >= 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool UART::Write(uint8_t* message, uint8_t size)
{
    if (isOpened())
    {
        if (write(fd, message, size) == size)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }
}

int UART::DataAvailable()
{
    int result;

	if (ioctl(fd, FIONREAD, &result) == -1)
    {
		return -1;
    }
    else
    {
        return result;
    }
}

uint8_t UART::GetByte()
{
    uint8_t byte;

	if (read(fd, &byte, 1) != 1)
    {
        return 0xFF;
    }
    else
    {
        return byte;
    }
}

void UART::Flush()
{
    tcflush(fd, TCIOFLUSH);
}

//! \} End of serial group
