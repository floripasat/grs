/*
 * obdh_data.cpp
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
 * \brief OBDH data packet implementation.
 * 
 * \author Gabriel Mariano Marcelino <gabriel.mm8@gmail.com>
 * 
 * \version 0.7.9
 * 
 * \date 09/04/2019
 * 
 * \addtogroup obdh_data
 * \{
 */

#include "obdh_data.h"

using namespace std;
using namespace grs;

OBDHData::OBDHData(Payload pl)
{
    this->decode(pl);
}

void OBDHData::decode(Payload pl)
{
    Packet::decode(pl);

    this->clear();

    // Battery cell 1 voltage
    uint16_t raw_battery_voltage = (pl[BEACON_DATA_BATTERY_VOLTAGE_CELL_1_POS] << 8) | pl[BEACON_DATA_BATTERY_VOLTAGE_CELL_1_POS+1];
    this->insert(pair<int, double>(BEACON_DATA_BATTERY_VOLTAGE_CELL_1, this->calc_battery_voltage(raw_battery_voltage)));

    // Battery cell 2 voltage
    raw_battery_voltage = (pl[BEACON_DATA_BATTERY_VOLTAGE_CELL_2_POS] << 8) | pl[BEACON_DATA_BATTERY_VOLTAGE_CELL_2_POS+1];
    this->insert(pair<int, double>(BEACON_DATA_BATTERY_VOLTAGE_CELL_2, this->calc_battery_voltage(raw_battery_voltage)));

    // Battery cell 1 temperature
//    uint32_t raw_battery_temperature = (pl[BEACON_DATA_BATTERY_TEMPERATURE_CELL_1_POS] << 16) | (pl[BEACON_DATA_BATTERY_TEMPERATURE_CELL_1_POS+1] << 8) | pl[BEACON_DATA_BATTERY_TEMPERATURE_CELL_1_POS+2];
//    this->insert(pair<int, double>(BEACON_DATA_BATTERY_TEMPERATURE_CELL_1, this->calc_battery_temperature(raw_battery_temperature)));

    // Battery cell 2 temperature
//    raw_battery_temperature = (pl[BEACON_DATA_BATTERY_TEMPERATURE_CELL_2_POS] << 16) | (pl[BEACON_DATA_BATTERY_TEMPERATURE_CELL_2_POS+1] << 8) | pl[BEACON_DATA_BATTERY_TEMPERATURE_CELL_2_POS+2];
//    this->insert(pair<int, double>(BEACON_DATA_BATTERY_TEMPERATURE_CELL_2, this->calc_battery_temperature(raw_battery_temperature)));

    // Battery charge
    uint16_t raw_battery_charge = (pl[BEACON_DATA_BATTERY_CHARGE_POS] << 8) | pl[BEACON_DATA_BATTERY_CHARGE_POS+1];
    this->insert(pair<int, double>(BEACON_DATA_BATTERY_CHARGE, this->calc_battery_charge(raw_battery_charge)));

    // Solar panel current 0
    uint16_t raw_solar_panel_current = (pl[BEACON_DATA_SOLAR_PANEL_CURRENT_0_POS] << 8) | pl[BEACON_DATA_SOLAR_PANEL_CURRENT_0_POS+1];
    this->insert(pair<int, double>(BEACON_DATA_SOLAR_PANEL_CURRENT_0, this->calc_solar_panel_current(raw_solar_panel_current)));

    // Solar panel current 1
    raw_solar_panel_current = (pl[BEACON_DATA_SOLAR_PANEL_CURRENT_1_POS] << 8) | pl[BEACON_DATA_SOLAR_PANEL_CURRENT_1_POS+1];
    this->insert(pair<int, double>(BEACON_DATA_SOLAR_PANEL_CURRENT_1, this->calc_solar_panel_current(raw_solar_panel_current)));

    // Solar panel current 2
    raw_solar_panel_current = (pl[BEACON_DATA_SOLAR_PANEL_CURRENT_2_POS] << 8) | pl[BEACON_DATA_SOLAR_PANEL_CURRENT_2_POS+1];
    this->insert(pair<int, double>(BEACON_DATA_SOLAR_PANEL_CURRENT_2, this->calc_solar_panel_current(raw_solar_panel_current)));

    // Solar panel current 3
    raw_solar_panel_current = (pl[BEACON_DATA_SOLAR_PANEL_CURRENT_3_POS] << 8) | pl[BEACON_DATA_SOLAR_PANEL_CURRENT_3_POS+1];
    this->insert(pair<int, double>(BEACON_DATA_SOLAR_PANEL_CURRENT_3, this->calc_solar_panel_current(raw_solar_panel_current)));

    // Solar panel current 4
    raw_solar_panel_current = (pl[BEACON_DATA_SOLAR_PANEL_CURRENT_4_POS] << 8) | pl[BEACON_DATA_SOLAR_PANEL_CURRENT_4_POS+1];
    this->insert(pair<int, double>(BEACON_DATA_SOLAR_PANEL_CURRENT_4, this->calc_solar_panel_current(raw_solar_panel_current)));

    // Solar panel current 5
    raw_solar_panel_current = (pl[BEACON_DATA_SOLAR_PANEL_CURRENT_5_POS] << 8) | pl[BEACON_DATA_SOLAR_PANEL_CURRENT_5_POS+1];
    this->insert(pair<int, double>(BEACON_DATA_SOLAR_PANEL_CURRENT_5, this->calc_solar_panel_current(raw_solar_panel_current)));

    // Solar panel voltage 0
    uint16_t raw_solar_panel_voltage = (pl[BEACON_DATA_SOLAR_PANEL_VOLTAGE_0_POS] << 8) | pl[BEACON_DATA_SOLAR_PANEL_VOLTAGE_0_POS+1];
    this->insert(pair<int, double>(BEACON_DATA_SOLAR_PANEL_VOLTAGE_0, this->calc_solar_panel_voltage(raw_solar_panel_voltage)));

    // Solar panel voltage 1
    raw_solar_panel_voltage = (pl[BEACON_DATA_SOLAR_PANEL_VOLTAGE_1_POS] << 8) | pl[BEACON_DATA_SOLAR_PANEL_VOLTAGE_1_POS+1];
    this->insert(pair<int, double>(BEACON_DATA_SOLAR_PANEL_VOLTAGE_1, this->calc_solar_panel_voltage(raw_solar_panel_voltage)));

    // Solar panel voltage 2
    raw_solar_panel_voltage = (pl[BEACON_DATA_SOLAR_PANEL_VOLTAGE_2_POS] << 8) | pl[BEACON_DATA_SOLAR_PANEL_VOLTAGE_2_POS+1];
    this->insert(pair<int, double>(BEACON_DATA_SOLAR_PANEL_VOLTAGE_2, this->calc_solar_panel_voltage(raw_solar_panel_voltage)));

    // Energy level
    this->insert(pair<int, double>(BEACON_DATA_ENERGY_LEVEL, pl[BEACON_DATA_ENERGY_LEVEL_POS]));

    // IMU status
    double imu_status = (pl[BEACON_DATA_IMU_STATUS_POS] >> 4) & 1;
    this->insert(pair<int, double>(BEACON_DATA_IMU_STATUS, imu_status));

    // SD card status
    double sd_card_status = (pl[BEACON_DATA_SD_CARD_STATUS_POS] >> 3) & 1;
    this->insert(pair<int, double>(BEACON_DATA_SD_CARD_STATUS, sd_card_status));

    // RUSH status
    double rush_status = (pl[BEACON_DATA_RUSH_STATUS_POS] >> 1) & 1;
    this->insert(pair<int, double>(BEACON_DATA_RUSH_STATUS, rush_status));

    // EPS status
    double eps_status = (pl[BEACON_DATA_EPS_STATUS_POS] >> 0) & 1;
    this->insert(pair<int, double>(BEACON_DATA_EPS_STATUS, eps_status));

    // Antenna status
    double antenna_status = (pl[BEACON_DATA_ANTENNA_STATUS_POS] >> 5) & 1;
    this->insert(pair<int, double>(BEACON_DATA_ANTENNA_STATUS, antenna_status));

    // IMU accelerometer x-axis
    uint16_t raw_imu_accel = (pl[BEACON_DATA_IMU_ACCEL_X_POS] << 8) | pl[BEACON_DATA_IMU_ACCEL_X_POS+1];
    this->insert(pair<int, double>(BEACON_DATA_IMU_ACCEL_X, this->calc_imu_accel(raw_imu_accel)));

    // IMU accelerometer y-axis
    raw_imu_accel = (pl[BEACON_DATA_IMU_ACCEL_Y_POS] << 8) | pl[BEACON_DATA_IMU_ACCEL_Y_POS+1];
    this->insert(pair<int, double>(BEACON_DATA_IMU_ACCEL_Y, this->calc_imu_accel(raw_imu_accel)));

    // IMU accelerometer z-axis
    raw_imu_accel = (pl[BEACON_DATA_IMU_ACCEL_Z_POS] << 8) | pl[BEACON_DATA_IMU_ACCEL_Z_POS+1];
    this->insert(pair<int, double>(BEACON_DATA_IMU_ACCEL_Z, this->calc_imu_accel(raw_imu_accel)));

    // IMU gyroscope x-axis
    uint16_t raw_imu_gyro = (pl[BEACON_DATA_IMU_GYRO_X_POS] << 8) | pl[BEACON_DATA_IMU_GYRO_X_POS];
    this->insert(pair<int, double>(BEACON_DATA_IMU_GYRO_X, this->calc_imu_gyro(raw_imu_gyro)));

    // IMU gyroscope y-axis
    raw_imu_gyro = (pl[BEACON_DATA_IMU_GYRO_Y_POS] << 8) | pl[BEACON_DATA_IMU_GYRO_Y_POS];
    this->insert(pair<int, double>(BEACON_DATA_IMU_GYRO_Y, this->calc_imu_gyro(raw_imu_gyro)));

    // IMU gyroscope z-axis
    raw_imu_gyro = (pl[BEACON_DATA_IMU_GYRO_Z_POS] << 8) | pl[BEACON_DATA_IMU_GYRO_Z_POS];
    this->insert(pair<int, double>(BEACON_DATA_IMU_GYRO_Z, this->calc_imu_gyro(raw_imu_gyro)));

    // System time seconds
    this->insert(pair<int, double>(BEACON_SYSTEM_TIME_SECOND, pl[BEACON_DATA_SYSTEM_TIME_SEC_POS]));

    // System time minutes
    unsigned int time = ((pl[BEACON_DATA_SYSTEM_TIME_MIN_POS] << 16) | (pl[BEACON_DATA_SYSTEM_TIME_MIN_POS+1] << 8) | pl[BEACON_DATA_SYSTEM_TIME_MIN_POS+2])%60;
    this->insert(pair<int, double>(BEACON_SYSTEM_TIME_MINUTE, time));

    // System time hours
    time = ((pl[BEACON_DATA_SYSTEM_TIME_MIN_POS] << 16) | (pl[BEACON_DATA_SYSTEM_TIME_MIN_POS+1] << 8) | pl[BEACON_DATA_SYSTEM_TIME_MIN_POS+2])/60;
    this->insert(pair<int, double>(BEACON_SYSTEM_TIME_HOUR, time));

    // OBDH resets
    double obdh_resets = pl[BEACON_DATA_RESETS_POS+1] + pl[BEACON_DATA_RESETS_POS]*256;
    this->insert(pair<int, double>(BEACON_DATA_OBDH_RESETS, obdh_resets));
}

//! \} End of obdh_data group
