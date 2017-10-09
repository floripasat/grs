/*
 * telemetry_data.h
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
 * \file telemetry_data.h
 * 
 * \brief Telemetry data class.
 * 
 * \author Gabriel Mariano Marcelino <gabriel.mm8@gmail.com>
 * 
 * \version 2.0
 * 
 * \date 08/10/2017
 * 
 * \defgroup telemetry_data Telemetry Data
 * \{
 */

#ifndef TELEMETRY_DATA_H_
#define TELEMETRY_DATA_H_

#include <stdint.h>
#include <string>

/**
 * \class TelemetryData
 * 
 * \brief 
 */
class TelemetryData
{
    public:
        /**
         * \brief 
         * 
         * \return None
         */
        TelemetryData();
        /**
         * \brief 
         * 
         * \return None
         */
        ~TelemetryData();
        /**
         * \brief 
         * 
         * \return None
         */
        void Display();
        /**
         * \brief 
         * 
         * \param data
         * \param len
         * 
         * \return None
         */
        void Update(uint8_t *data, uint8_t len);
        /**
         * \brief 
         * 
         * \return None
         */
        void Clear();
        /**
         * \brief 
         * 
         * \return 
         */
        std::string Log();
};

#endif // TELEMTRY_DATA_H_

//! \} End of telemetry_data group
