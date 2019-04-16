/*
 * eps_data.cpp
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
 * \brief EPS data packet implementation.
 * 
 * \author Gabriel Mariano Marcelino <gabriel.mm8@gmail.com>
 * 
 * \version 0.4.2
 * 
 * \date 09/04/2019
 * 
 * \addtogroup eps_data
 * \{
 */

#include "eps_data.h"

using namespace std;
using namespace grs;

EPSData::EPSData(Payload pl)
{
    this->decode(pl);
}

void EPSData::decode(Payload pl)
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
    uint32_t raw_battery_temperature = (pl[BEACON_DATA_BATTERY_TEMPERATURE_CELL_1_POS] << 16) | (pl[BEACON_DATA_BATTERY_TEMPERATURE_CELL_1_POS+1] << 8) | pl[BEACON_DATA_BATTERY_TEMPERATURE_CELL_1_POS+2];
    this->insert(pair<int, double>(BEACON_DATA_BATTERY_TEMPERATURE_CELL_1, this->calc_battery_temperature(raw_battery_temperature)));

    // Battery cell 2 temperature
    raw_battery_temperature = (pl[BEACON_DATA_BATTERY_TEMPERATURE_CELL_2_POS] << 16) | (pl[BEACON_DATA_BATTERY_TEMPERATURE_CELL_2_POS+1] << 8) | pl[BEACON_DATA_BATTERY_TEMPERATURE_CELL_2_POS+2];
    this->insert(pair<int, double>(BEACON_DATA_BATTERY_TEMPERATURE_CELL_2, this->calc_battery_temperature(raw_battery_temperature)));

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
}

//! \} End of eps_data group
