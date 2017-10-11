/*
 * telemetry_data.cpp
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
 * \file telemetry_data.cpp
 * 
 * \brief Telemetry data class implementation.
 * 
 * \author Gabriel Mariano Marcelino <gabriel.mm8@gmail.com>
 * 
 * \version 2.0
 * 
 * \date 08/10/2017
 * 
 * \addtogroup telemetry_data
 * \{
 */

#include "telemetry_data.h"
#include "aux.hpp"

TelemetryData::TelemetryData()
{
    
}

TelemetryData::TelemetryData(std::vector<Gtk::Label *> lbs)
{
    unsigned int pos = 0;
    
    label_telemetry_data_status_reset_counter   = lbs[pos++];
    label_telemetry_data_status_reset_cause     = lbs[pos++];
    label_telemetry_data_status_clock           = lbs[pos++];
    label_telemetry_data_status_modules         = lbs[pos++];
    label_telemetry_data_status_imu             = lbs[pos++];
    label_telemetry_data_status_rush            = lbs[pos++];
    label_telemetry_data_status_eps             = lbs[pos++];
    label_telemetry_data_status_antenna         = lbs[pos++];
    label_telemetry_data_uc_temp                = lbs[pos++];
    label_telemetry_data_uc_voltage             = lbs[pos++];
    label_telemetry_data_uc_current             = lbs[pos++];
    label_telemetry_data_time_system            = lbs[pos++];
    label_telemetry_data_time_system_up         = lbs[pos++];
    label_telemetry_data_imu_accel_x            = lbs[pos++];
    label_telemetry_data_imu_accel_y            = lbs[pos++];
    label_telemetry_data_imu_accel_z            = lbs[pos++];
    label_telemetry_data_imu_gyro_x             = lbs[pos++];
    label_telemetry_data_imu_gyro_y             = lbs[pos++];
    label_telemetry_data_imu_gyro_z             = lbs[pos++];
    label_telemetry_data_sp_sun_p1              = lbs[pos++];
    label_telemetry_data_sp_sun_p2              = lbs[pos++];
    label_telemetry_data_sp_sun_p3              = lbs[pos++];
    label_telemetry_data_sp_temp_p1             = lbs[pos++];
    label_telemetry_data_sp_temp_p2             = lbs[pos++];
    label_telemetry_data_sp_temp_p3             = lbs[pos++];
    label_telemetry_data_eps_bat_mean_i         = lbs[pos++];
    label_telemetry_data_eps_bat_temp           = lbs[pos++];
    label_telemetry_data_eps_bat_1_volt         = lbs[pos++];
    label_telemetry_data_eps_bat_2_volt         = lbs[pos++];
    label_telemetry_data_eps_bat_current        = lbs[pos++];
    label_telemetry_data_eps_bat_charge         = lbs[pos++];
    label_telemetry_data_eps_bat_protection     = lbs[pos++];
    label_telemetry_data_eps_bat_status         = lbs[pos++];
    label_telemetry_data_eps_bat_cycles         = lbs[pos++];
    label_telemetry_data_eps_bat_raac           = lbs[pos++];
    label_telemetry_data_eps_bat_rsac           = lbs[pos++];
    label_telemetry_data_eps_bat_rarc           = lbs[pos++];
    label_telemetry_data_eps_bat_rsrc           = lbs[pos++];
    label_telemetry_data_eps_sp_i_my            = lbs[pos++];
    label_telemetry_data_eps_sp_i_px            = lbs[pos++];
    label_telemetry_data_eps_sp_i_mx            = lbs[pos++];
    label_telemetry_data_eps_sp_i_pz            = lbs[pos++];
    label_telemetry_data_eps_sp_i_mz            = lbs[pos++];
    label_telemetry_data_eps_sp_i_py            = lbs[pos++];
    label_telemetry_data_eps_sp_v_mypx          = lbs[pos++];
    label_telemetry_data_eps_sp_v_mxpz          = lbs[pos++];
    label_telemetry_data_eps_sp_v_mzpy          = lbs[pos++];
    label_telemetry_data_eps_misc_boost_v       = lbs[pos++];
    label_telemetry_data_eps_misc_main_bus_v    = lbs[pos++];
    label_telemetry_data_eps_misc_beacon_i      = lbs[pos++];
    label_telemetry_data_eps_misc_uc_temp       = lbs[pos++];
    label_telemetry_data_eps_misc_energy_level  = lbs[pos++];
    
    this->Clear();
}

void TelemetryData::Display()
{
/*    label_telemetry_data_status_reset_counter->set_text(TELEMETRY_DATA_UNKNOWN_VALUE);
    label_telemetry_data_status_reset_cause->set_text(TELEMETRY_DATA_UNKNOWN_VALUE);
    label_telemetry_data_status_clock->set_text(TELEMETRY_DATA_UNKNOWN_VALUE);
    label_telemetry_data_status_modules->set_text(TELEMETRY_DATA_UNKNOWN_VALUE);
    label_telemetry_data_status_imu->set_text(TELEMETRY_DATA_UNKNOWN_VALUE);
    label_telemetry_data_status_rush->set_text(TELEMETRY_DATA_UNKNOWN_VALUE);
    label_telemetry_data_status_eps->set_text(TELEMETRY_DATA_UNKNOWN_VALUE);
    label_telemetry_data_status_antenna->set_text(TELEMETRY_DATA_UNKNOWN_VALUE);
    label_telemetry_data_uc_temp->set_text(TELEMETRY_DATA_UNKNOWN_VALUE);
    label_telemetry_data_uc_voltage->set_text(TELEMETRY_DATA_UNKNOWN_VALUE);
    label_telemetry_data_uc_current->set_text(TELEMETRY_DATA_UNKNOWN_VALUE);
    label_telemetry_data_time_system->set_text(TELEMETRY_DATA_UNKNOWN_VALUE);
    label_telemetry_data_time_system_up->set_text(TELEMETRY_DATA_UNKNOWN_VALUE);
    label_telemetry_data_imu_accel_x->set_text(TELEMETRY_DATA_UNKNOWN_VALUE);
    label_telemetry_data_imu_accel_y->set_text(TELEMETRY_DATA_UNKNOWN_VALUE);
    label_telemetry_data_imu_accel_z->set_text(TELEMETRY_DATA_UNKNOWN_VALUE);
    label_telemetry_data_imu_gyro_x->set_text(TELEMETRY_DATA_UNKNOWN_VALUE);
    label_telemetry_data_imu_gyro_y->set_text(TELEMETRY_DATA_UNKNOWN_VALUE);
    label_telemetry_data_imu_gyro_z->set_text(TELEMETRY_DATA_UNKNOWN_VALUE);
    label_telemetry_data_sp_sun_p1->set_text(TELEMETRY_DATA_UNKNOWN_VALUE);
    label_telemetry_data_sp_sun_p2->set_text(TELEMETRY_DATA_UNKNOWN_VALUE);
    label_telemetry_data_sp_sun_p3->set_text(TELEMETRY_DATA_UNKNOWN_VALUE);
    label_telemetry_data_sp_temp_p1->set_text(TELEMETRY_DATA_UNKNOWN_VALUE);
    label_telemetry_data_sp_temp_p2->set_text(TELEMETRY_DATA_UNKNOWN_VALUE);
    label_telemetry_data_sp_temp_p3->set_text(TELEMETRY_DATA_UNKNOWN_VALUE);
    label_telemetry_data_eps_bat_mean_i->set_text(TELEMETRY_DATA_UNKNOWN_VALUE);
    label_telemetry_data_eps_bat_temp->set_text(TELEMETRY_DATA_UNKNOWN_VALUE);
    label_telemetry_data_eps_bat_1_volt->set_text(TELEMETRY_DATA_UNKNOWN_VALUE);
    label_telemetry_data_eps_bat_2_volt->set_text(TELEMETRY_DATA_UNKNOWN_VALUE);
    label_telemetry_data_eps_bat_current->set_text(TELEMETRY_DATA_UNKNOWN_VALUE);
    label_telemetry_data_eps_bat_charge->set_text(TELEMETRY_DATA_UNKNOWN_VALUE);
    label_telemetry_data_eps_bat_protection->set_text(TELEMETRY_DATA_UNKNOWN_VALUE);
    label_telemetry_data_eps_bat_status->set_text(TELEMETRY_DATA_UNKNOWN_VALUE);
    label_telemetry_data_eps_bat_cycles->set_text(TELEMETRY_DATA_UNKNOWN_VALUE);
    label_telemetry_data_eps_bat_raac->set_text(TELEMETRY_DATA_UNKNOWN_VALUE);
    label_telemetry_data_eps_bat_rsac->set_text(TELEMETRY_DATA_UNKNOWN_VALUE);
    label_telemetry_data_eps_bat_rarc->set_text(TELEMETRY_DATA_UNKNOWN_VALUE);
    label_telemetry_data_eps_bat_rsrc->set_text(TELEMETRY_DATA_UNKNOWN_VALUE);
    label_telemetry_data_eps_sp_i_my->set_text(TELEMETRY_DATA_UNKNOWN_VALUE);
    label_telemetry_data_eps_sp_i_px->set_text(TELEMETRY_DATA_UNKNOWN_VALUE);
    label_telemetry_data_eps_sp_i_mx->set_text(TELEMETRY_DATA_UNKNOWN_VALUE);
    label_telemetry_data_eps_sp_i_pz->set_text(TELEMETRY_DATA_UNKNOWN_VALUE);
    label_telemetry_data_eps_sp_i_mz->set_text(TELEMETRY_DATA_UNKNOWN_VALUE);
    label_telemetry_data_eps_sp_i_py->set_text(TELEMETRY_DATA_UNKNOWN_VALUE);
    label_telemetry_data_eps_sp_v_mypx->set_text(TELEMETRY_DATA_UNKNOWN_VALUE);
    label_telemetry_data_eps_sp_v_mxpz->set_text(TELEMETRY_DATA_UNKNOWN_VALUE);
    label_telemetry_data_eps_sp_v_mzpy->set_text(TELEMETRY_DATA_UNKNOWN_VALUE);
    label_telemetry_data_eps_misc_boost_v->set_text(TELEMETRY_DATA_UNKNOWN_VALUE);
    label_telemetry_data_eps_misc_main_bus_v->set_text(TELEMETRY_DATA_UNKNOWN_VALUE);
    label_telemetry_data_eps_misc_beacon_i->set_text(TELEMETRY_DATA_UNKNOWN_VALUE);
    label_telemetry_data_eps_misc_uc_temp->set_text(TELEMETRY_DATA_UNKNOWN_VALUE);
    label_telemetry_data_eps_misc_energy_level->set_text(TELEMETRY_DATA_UNKNOWN_VALUE);
    
    label_telemetry_data_status_reset_counter->set_text();
    label_telemetry_data_status_reset_cause->set_text();
    label_telemetry_data_status_clock->set_text();
    label_telemetry_data_status_modules->set_text();
    label_telemetry_data_status_imu->set_text(imu_status? "\u2714" : "\u2718");
    label_telemetry_data_status_rush->set_text(rush_status? "\u2714" : "\u2718");
    label_telemetry_data_status_eps->set_text(eps_status? "\u2714" : "\u2718");
    label_telemetry_data_status_antenna->set_text(antenna_status? "\u2714" : "\u2718");
    label_telemetry_data_uc_temp->set_text();
    label_telemetry_data_uc_voltage->set_text();
    label_telemetry_data_uc_current->set_text();
    label_telemetry_data_time_system->set_text();
    label_telemetry_data_time_system_up->set_text();
    label_telemetry_data_imu_accel_x->set_text();
    label_telemetry_data_imu_accel_y->set_text();
    label_telemetry_data_imu_accel_z->set_text();
    label_telemetry_data_imu_gyro_x->set_text();
    label_telemetry_data_imu_gyro_y->set_text();
    label_telemetry_data_imu_gyro_z->set_text();
    label_telemetry_data_sp_sun_p1->set_text();
    label_telemetry_data_sp_sun_p2->set_text();
    label_telemetry_data_sp_sun_p3->set_text();
    label_telemetry_data_sp_temp_p1->set_text();
    label_telemetry_data_sp_temp_p2->set_text();
    label_telemetry_data_sp_temp_p3->set_text();
    label_telemetry_data_eps_bat_mean_i->set_text();
    label_telemetry_data_eps_bat_temp->set_text();
    label_telemetry_data_eps_bat_1_volt->set_text();
    label_telemetry_data_eps_bat_2_volt->set_text();
    label_telemetry_data_eps_bat_current->set_text();
    label_telemetry_data_eps_bat_charge->set_text();
    label_telemetry_data_eps_bat_protection->set_text();
    label_telemetry_data_eps_bat_status->set_text();
    label_telemetry_data_eps_bat_cycles->set_text();
    label_telemetry_data_eps_bat_raac->set_text();
    label_telemetry_data_eps_bat_rsac->set_text();
    label_telemetry_data_eps_bat_rarc->set_text();
    label_telemetry_data_eps_bat_rsrc->set_text();
    label_telemetry_data_eps_sp_i_my->set_text();
    label_telemetry_data_eps_sp_i_px->set_text();
    label_telemetry_data_eps_sp_i_mx->set_text();
    label_telemetry_data_eps_sp_i_pz->set_text();
    label_telemetry_data_eps_sp_i_mz->set_text();
    label_telemetry_data_eps_sp_i_py->set_text();
    label_telemetry_data_eps_sp_v_mypx->set_text();
    label_telemetry_data_eps_sp_v_mxpz->set_text();
    label_telemetry_data_eps_sp_v_mzpy->set_text();
    label_telemetry_data_eps_misc_boost_v->set_text();
    label_telemetry_data_eps_misc_main_bus_v->set_text();
    label_telemetry_data_eps_misc_beacon_i->set_text();
    label_telemetry_data_eps_misc_uc_temp->set_text();
    switch(energy_level)
    {
        case 0:
            label_telemetry_data_eps_misc_energy_level->set_text("\u2605\u2605\u2605\u2605\u2605");
            break;
        case 1:
            label_telemetry_data_eps_misc_energy_level->set_text("\u2605\u2605\u2605\u2605");
            break;
        case 2:
            label_telemetry_data_eps_misc_energy_level->set_text("\u2605\u2605\u2605");
            break;
        case 3:
            label_telemetry_data_eps_misc_energy_level->set_text("\u2605\u2605");
            break;
        case 4:
            label_telemetry_data_eps_misc_energy_level->set_text("\u2605");
            break;
        case 5:
            label_telemetry_data_eps_misc_energy_level->set_text("\u2620");
            break;
    }*/
}

void TelemetryData::Update(uint8_t *data, uint8_t len)
{
    bat1_voltage        = BatVoltConv((data[10] << 8) | data[11]);
    bat2_voltage        = BatVoltConv((data[12] << 8) | data[13]);
    bat1_temp           = BatTempConv((data[14] << 16) | (data[15] << 8) | data[16]);
    bat2_temp           = BatTempConv((data[17] << 16) | (data[18] << 8) | data[19]);
    bat_charge          = BatChargeConv((data[20] << 8) | data[21]);
    solar_current_1     = SolarPanelCurrentConv((data[22] << 8) | data[23]);
    solar_current_2     = SolarPanelCurrentConv((data[24] << 8) | data[25]);
    solar_current_3     = SolarPanelCurrentConv((data[26] << 8) | data[27]);
    solar_current_4     = SolarPanelCurrentConv((data[28] << 8) | data[29]);
    solar_current_5     = SolarPanelCurrentConv((data[30] << 8) | data[31]);
    solar_current_6     = SolarPanelCurrentConv((data[32] << 8) | data[33]);
    solar_voltage_1     = SolarPanelVoltageConv((data[34] << 8) | data[35]);
    solar_voltage_2     = SolarPanelVoltageConv((data[36] << 8) | data[37]);
    solar_voltage_3     = SolarPanelVoltageConv((data[38] << 8) | data[39]);
    energy_level        = data[40];
    imu_status          = bool((data[41] << 4) & 0x08);
    usd_status          = bool((data[41] << 3) & 0x04);
    rush_status         = bool((data[41] << 1) & 0x02);
    eps_status          = bool((data[41] << 0) & 0x01);
    antenna_status      = bool((data[41] << 5) & 0x10);
    imu_accel_x         = IMUAccelConv((data[42] << 8) | data[43]);
    imu_accel_y         = IMUAccelConv((data[44] << 8) | data[45]);
    imu_accel_z         = IMUAccelConv((data[46] << 8) | data[47]);
    imu_gyro_x          = IMUGyroConv((data[48] << 8) | data[49]);
    imu_gyro_y          = IMUGyroConv((data[50] << 8) | data[51]);
    imu_gyro_z          = IMUGyroConv((data[52] << 8) | data[53]);
    system_time_sec     = data[54];
    system_time_min     = (data[55] | (data[56] << 8) | (data[57] << 16))%60;
    system_time_hou     = (data[55] | (data[56] << 8) | (data[57] << 16))/60;
    obdh_resets         = data[58] + data[59]*256;
}

void TelemetryData::Clear()
{
    bat1_voltage        = 0;
    bat2_voltage        = 0;
    bat1_temp           = 0;
    bat2_temp           = 0;
    bat_charge          = 0;
    solar_current_1     = 0;
    solar_current_2     = 0;
    solar_current_3     = 0;
    solar_current_4     = 0;
    solar_current_5     = 0;
    solar_current_6     = 0;
    solar_voltage_1     = 0;
    solar_voltage_2     = 0;
    solar_voltage_3     = 0;
    energy_level        = 0;
    imu_status          = false;
    usd_status          = false;
    rush_status         = false;
    eps_status          = false;
    antenna_status      = false;
    imu_accel_x         = 0;
    imu_accel_y         = 0;
    imu_accel_z         = 0;
    imu_gyro_x          = 0;
    imu_gyro_y          = 0;
    imu_gyro_z          = 0;
    system_time_sec     = 0;
    system_time_min     = 0;
    system_time_hou     = 0;
    obdh_resets         = 0;
}

std::string TelemetryData::Log()
{
    std::string log_entry = "";
    
    log_entry += ToString(bat1_voltage);
    log_entry += ",";
    log_entry += ToString(bat2_voltage);
    log_entry += ",";
    log_entry += ToString(bat1_temp);
    log_entry += ",";
    log_entry += ToString(bat2_temp);
    log_entry += ",";
    log_entry += ToString(bat_charge);
    log_entry += ",";
    log_entry += ToString(solar_current_1);
    log_entry += ",";
    log_entry += ToString(solar_current_2);
    log_entry += ",";
    log_entry += ToString(solar_current_3);
    log_entry += ",";
    log_entry += ToString(solar_current_4);
    log_entry += ",";
    log_entry += ToString(solar_current_5);
    log_entry += ",";
    log_entry += ToString(solar_current_6);
    log_entry += ",";
    log_entry += ToString(solar_voltage_1);
    log_entry += ",";
    log_entry += ToString(solar_voltage_2);
    log_entry += ",";
    log_entry += ToString(solar_voltage_3);
    log_entry += ",";
    log_entry += ToString(int(energy_level));
    log_entry += ",";
    log_entry += ToString(imu_status);
    log_entry += ",";
    log_entry += ToString(usd_status);
    log_entry += ",";
    log_entry += ToString(rush_status);
    log_entry += ",";
    log_entry += ToString(eps_status);
    log_entry += ",";
    log_entry += ToString(antenna_status);
    log_entry += ",";
    log_entry += ToString(imu_accel_x);
    log_entry += ",";
    log_entry += ToString(imu_accel_y);
    log_entry += ",";
    log_entry += ToString(imu_accel_z);
    log_entry += ",";
    log_entry += ToString(imu_gyro_x);
    log_entry += ",";
    log_entry += ToString(imu_gyro_y);
    log_entry += ",";
    log_entry += ToString(imu_gyro_z);
    log_entry += ",";
    log_entry += ToString(int(system_time_sec));
    log_entry += ",";
    log_entry += ToString(int(system_time_min));
    log_entry += ",";
    log_entry += ToString(int(system_time_hou));
    log_entry += ",";
    log_entry += ToString(obdh_resets);
    
    return log_entry;
}

const char* TelemetryData::getLabel()
{
    return "TELEMETRY";
}

double TelemetryData::BatVoltConv(uint16_t val)
{
    return (val/32.0)*4.883e-3;
}

double TelemetryData::BatTempConv(uint32_t val)
{
    return (val*0.125)/32.0;
}

double TelemetryData::BatChargeConv(uint16_t val)
{
    return 0;
}

double TelemetryData::SolarPanelCurrentConv(uint16_t val)
{
    return val*(2.5/4095)*(1/(0.05*0.025*3300));
}

double TelemetryData::SolarPanelVoltageConv(uint16_t val)
{
    return val*(2.5/4095)*(100e3 + 93.1e3)/100e3;
}

double TelemetryData::IMUAccelConv(uint16_t val)
{
    return int16_t(val)*16.0/32768.0;
}

double TelemetryData::IMUGyroConv(uint16_t val)
{
    return int16_t(val)*250.0/32768.0;
}

const char* TelemetryData::PrintTime(uint8_t h, uint8_t m, uint8_t s)
{
    std::stringstream input_str;
    
    input_str << int(h);
    input_str << ":";
    input_str << int(m);
    input_str << ":";
    input_str << int(s);
    
    std::string output = input_str.str();
    
    return output.c_str();
}

//! \} End of telemetry_data
