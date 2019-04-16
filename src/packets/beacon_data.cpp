/*
 * beacon_data.cpp
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
 * \brief Beacon data packet implementation.
 * 
 * \author Gabriel Mariano Marcelino <gabriel.mm8@gmail.com>
 * 
 * \version 0.4.0
 * 
 * \date 09/04/2019
 * 
 * \addtogroup beacon_data
 * \{
 */

#include "beacon_data.h"

using namespace grs;

double BeaconData::calc_battery_voltage(uint16_t val)
{
    return (val/32.0)*4.883e-3;
}

double BeaconData::calc_battery_temperature(uint32_t val)
{
    return (val*0.125)/32.0;
}

double BeaconData::calc_battery_charge(uint16_t val)
{
    return val*(6.25*1e-4);
}

double BeaconData::calc_solar_panel_current(uint16_t val)
{
    return val*(2.5/4095)*(1/(0.05*0.025*3300));
}

double BeaconData::calc_solar_panel_voltage(uint16_t val)
{
    return val*(2.5/4095)*(100e3 + 93.1e3)/100e3;
}

double BeaconData::calc_imu_accel(uint16_t val)
{
    return int16_t(val)*16.0/32768.0;
}

double BeaconData::calc_imu_gyro(uint16_t val)
{
    return int16_t(val)*250.0/32768.0;
}

//! \} End of beacon_data group
