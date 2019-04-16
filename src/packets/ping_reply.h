/*
 * ping_reply.h
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
 * \brief Ping reply packet definition.
 * 
 * \author Gabriel Mariano Marcelino <gabriel.mm8@gmail.com>
 * 
 * \version 0.4.3
 * 
 * \date 13/04/2019
 * 
 * \defgroup ping_reply Ping Reply
 * \ingroup downlink_data
 * \{
 */

#ifndef PING_REPLY_H_
#define PING_REPLY_H_

#include "downlink_data.h"

namespace grs
{
    /**
     * \brief Ping reply packet.
     */
    class PingReply: public grs::DownlinkData
    {

    };
}

#endif // PING_REPLY_H_

//! \} End of ping_reply group
