/*
 * packet.h
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
 * \brief Packet definition.
 * 
 * \author Gabriel Mariano Marcelino <gabriel.mm8@gmail.com>
 * 
 * \version 0.4.0
 * 
 * \date 09/04/2019
 * 
 * \defgroup packet Packet
 * \{
 */

#ifndef PACKET_H_
#define PACKET_H_

#include <stdint.h>

#include <map>

#include "../payload.h"

namespace grs
{

    /**
     * \brief Packet object.
     */
    class Packet: public std::map<int, double>
    {
        public:

            /**
             * \brief Declaration constructor.
             *
             * \return None.
             */
            Packet();

            /**
             * \brief Constructor with initialization (overloaded).
             *
             * \return None.
             */
            Packet(Payload pl);

            /**
             * \brief Destructor.
             *
             * \return None.
             */
            ~Packet();

            /**
             * \brief .
             *
             * \param[in] pl
             *
             * \return None.
             */
            void decode(Payload pl);

            /**
             * \brief Packet ID code.
             */
            uint8_t id;

            /**
             * \brief Packet source callsign.
             */
            std::string src_callsign;

        protected:

            /**
             * \brief Computes a battery voltage from a raw value.
             *
             * \param[in] val is the raw value of a battery voltage.
             *
             * \return The given battery voltage in Volts.
             */
            virtual double calc_battery_voltage(uint16_t val) = 0;

            /**
             * \brief Computes a battery temperature from a raw value.
             *
             * \param[in] val is the raw value of a battery temperature
             *
             * \return The given battery temperature in Celsius.
             */
            virtual double calc_battery_temperature(uint32_t val) = 0;

            /**
             * \brief Computes a battery charge from a raw value.
             *
             * \param[in] val is the raw value of a battery charge.
             *
             * \return The given battery charge in Ah.
             */
            virtual double calc_battery_charge(uint16_t val) = 0;

            /**
             * \brief Computes a solar panel current from a raw value.
             *
             * \param[in] val is the raw value of a solar panel current.
             *
             * \return The given solar panel current in Ampere.
             */
            virtual double calc_solar_panel_current(uint16_t val) = 0;

            /**
             * \brief Computes a solar panel voltage from a raw value.
             *
             * \param[in] val is the raw value of a solar panel voltage.
             *
             * \return The given solar panel voltage in Volts.
             */
            virtual double calc_solar_panel_voltage(uint16_t val) = 0;

            /**
             * \brief Computes an IMU acceleration from a raw value.
             *
             * \param[in] val is the raw value of a IMU acceleration.
             *
             * \return The given IMU acceleration in ??.
             */
            virtual double calc_imu_accel(uint16_t val) = 0;

            /**
             * \brief Computes an IMU gyroscope acceleration from a raw value.
             *
             * \param[in] val is the raw value of a IMU gyroscope acceleration.
             *
             * \return The given IMU gyroscope acceleration in ??.
             */
            virtual double calc_imu_gyro(uint16_t val) = 0;
    };
}

#endif // PACKET_H_

//! \} End of packet group
