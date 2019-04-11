/*
 * beacon_data.h
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
 * \brief Beacon data packet definition.
 * 
 * \author Gabriel Mariano Marcelino <gabriel.mm8@gmail.com>
 * 
 * \version 0.4.0
 * 
 * \date 09/04/2019
 * 
 * \defgroup beacon_data Beacon Data
 * \ingroup packet
 * \{
 */

#ifndef BEACON_DATA_H_
#define BEACON_DATA_H_

#include "packet.h"

// Battery voltage
#define BEACON_DATA_BATTERY_VOLTAGE_CELL_1_POS          10
#define BEACON_DATA_BATTERY_VOLTAGE_CELL_2_POS          12

// Battery temperature
#define BEACON_DATA_BATTERY_TEMPERATURE_CELL_1_POS      14
#define BEACON_DATA_BATTERY_TEMPERATURE_CELL_2_POS      17

// Battery charge
#define BEACON_DATA_BATTERY_CHARGE_POS                  20

// Solar panel current
#define BEACON_DATA_SOLAR_PANEL_CURRENT_0_POS           22
#define BEACON_DATA_SOLAR_PANEL_CURRENT_1_POS           24
#define BEACON_DATA_SOLAR_PANEL_CURRENT_2_POS           26
#define BEACON_DATA_SOLAR_PANEL_CURRENT_3_POS           28
#define BEACON_DATA_SOLAR_PANEL_CURRENT_4_POS           30
#define BEACON_DATA_SOLAR_PANEL_CURRENT_5_POS           32

// Solar panel voltage
#define BEACON_DATA_SOLAR_PANEL_VOLTAGE_0_POS           34
#define BEACON_DATA_SOLAR_PANEL_VOLTAGE_1_POS           36
#define BEACON_DATA_SOLAR_PANEL_VOLTAGE_2_POS           38

// Energy level
#define BEACON_DATA_ENERGY_LEVEL_POS                    40

// Modules status
#define BEACON_DATA_IMU_STATUS_POS                      41
#define BEACON_DATA_SD_CARD_STATUS_POS                  41
#define BEACON_DATA_RUSH_STATUS_POS                     41
#define BEACON_DATA_EPS_STATUS_POS                      41
#define BEACON_DATA_ANTENNA_STATUS_POS                  41

// IMU accelerometer
#define BEACON_DATA_IMU_ACCEL_X_POS                     42
#define BEACON_DATA_IMU_ACCEL_Y_POS                     44
#define BEACON_DATA_IMU_ACCEL_Z_POS                     46

// IMU gyroscope
#define BEACON_DATA_IMU_GYRO_X_POS                      48
#define BEACON_DATA_IMU_GYRO_Y_POS                      50
#define BEACON_DATA_IMU_GYRO_Z_POS                      52

// System time
#define BEACON_DATA_SYSTEM_TIME_SEC_POS                 54
#define BEACON_DATA_SYSTEM_TIME_MIN_POS                 55
#define BEACON_DATA_SYSTEM_TIME_HOUR_POS                55

// OBDH resets
#define BEACON_DATA_RESETS_POS                          58

/**
 * \brief Beacon data IDs.
 */
enum beacon_data_id
{
    BEACON_DATA_BATTERY_VOLTAGE_CELL_1 = 0,         /**< Battery cell 1 voltage. */
    BEACON_DATA_BATTERY_VOLTAGE_CELL_2,             /**< Battery cell 2 voltage. */
    BEACON_DATA_BATTERY_TEMPERATURE_CELL_1,         /**< Battery cell 1 temperature. */
    BEACON_DATA_BATTERY_TEMPERATURE_CELL_2,         /**< Battery cell 2 temperature. */
    BEACON_DATA_BATTERY_CHARGE,                     /**< Battery charge. */
    BEACON_DATA_SOLAR_PANEL_CURRENT_0,              /**< Solar panel current 0. */
    BEACON_DATA_SOLAR_PANEL_CURRENT_1,              /**< Solar panel current 1. */
    BEACON_DATA_SOLAR_PANEL_CURRENT_2,              /**< Solar panel current 2. */
    BEACON_DATA_SOLAR_PANEL_CURRENT_3,              /**< Solar panel current 3. */
    BEACON_DATA_SOLAR_PANEL_CURRENT_4,              /**< Solar panel current 4. */
    BEACON_DATA_SOLAR_PANEL_CURRENT_5,              /**< Solar panel current 5. */
    BEACON_DATA_SOLAR_PANEL_VOLTAGE_0,              /**< Solar panell voltage 0. */
    BEACON_DATA_SOLAR_PANEL_VOLTAGE_1,              /**< Solar panell voltage 1. */
    BEACON_DATA_SOLAR_PANEL_VOLTAGE_2,              /**< Solar panell voltage 2. */
    BEACON_DATA_ENERGY_LEVEL,                       /**< Satellite energy level. */
    BEACON_DATA_IMU_STATUS,                         /**< IMU status flag. */
    BEACON_DATA_SD_CARD_STATUS,                     /**< SD card status flag. */
    BEACON_DATA_RUSH_STATUS,                        /**< RUSH status flag. */
    BEACON_DATA_EPS_STATUS,                         /**< EPS status flag. */
    BEACON_DATA_ANTENNA_STATUS,                     /**< Antenna status flag. */
    BEACON_DATA_IMU_ACCEL_X,                        /**< IMU accelerometer x-axis. */
    BEACON_DATA_IMU_ACCEL_Y,                        /**< IMU accelerometer y-axis. */
    BEACON_DATA_IMU_ACCEL_Z,                        /**< IMU accelerometer z-axis. */
    BEACON_DATA_IMU_GYRO_X,                         /**< IMU gyroscope x-axis. */
    BEACON_DATA_IMU_GYRO_Y,                         /**< IMU gyroscope y-axis. */
    BEACON_DATA_IMU_GYRO_Z,                         /**< IMU gyroscope z-axis. */
    BEACON_SYSTEM_TIME_SECOND,                      /**< System time hour. */
    BEACON_SYSTEM_TIME_MINUTE,                      /**< System time minute. */
    BEACON_SYSTEM_TIME_HOUR,                        /**< System time hour. */
    BEACON_DATA_OBDH_RESETS                         /**< Number of resets of the OBDH module. */
};

/**
 * \brief Beacon data packet.
 */
class BeaconData: public Packet
{
    protected:

        /**
         * \brief Computes a battery voltage from a raw value.
         *
         * \param[in] val is the raw value of a battery voltage.
         *
         * \return The given battery voltage in Volts.
         */
        double calc_battery_voltage(uint16_t val);

        /**
         * \brief Computes a battery temperature from a raw value.
         *
         * \param[in] val is the raw value of a battery temperature
         *
         * \return The given battery temperature in Celsius.
         */
        double calc_battery_temperature(uint32_t val);

        /**
         * \brief Computes a battery charge from a raw value.
         *
         * \param[in] val is the raw value of a battery charge.
         *
         * \return The given battery charge in Ah.
         */
        double calc_battery_charge(uint16_t val);

        /**
         * \brief Computes a solar panel current from a raw value.
         *
         * \param[in] val is the raw value of a solar panel current.
         *
         * \return The given solar panel current in Ampere.
         */
        double calc_solar_panel_current(uint16_t val);

        /**
         * \brief Computes a solar panel voltage from a raw value.
         *
         * \param[in] val is the raw value of a solar panel voltage.
         *
         * \return The given solar panel voltage in Volts.
         */
        double calc_solar_panel_voltage(uint16_t val);

        /**
         * \brief Computes an IMU acceleration from a raw value.
         *
         * \param[in] val is the raw value of a IMU acceleration.
         *
         * \return The given IMU acceleration in ??.
         */
        double calc_imu_accel(uint16_t val);

        /**
         * \brief Computes an IMU gyroscope acceleration from a raw value.
         *
         * \param[in] val is the raw value of a IMU gyroscope acceleration.
         *
         * \return The given IMU gyroscope acceleration in ??.
         */
        double calc_imu_gyro(uint16_t val);
};

#endif // BEACON_DATA_H_

//! \} End of beacon_data group
