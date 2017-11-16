/*
 * beacon_data.cpp
 * 
 * Copyright (C) 2017, Federal University of Santa Catarina.
 * 
 * This file is part of FloripaSat-GRS.
 * 
 * FloripaSat-GRS is free software: you can redistribute it
 * and/or modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation, either version 3 of the
 * License, or (at your option) any later version.
 * 
 * FloripaSat-GRS is distributed in the hope that it will be
 * useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with FloripaSat-GRS. If not, see <http://www.gnu.org/licenses/>.
 * 
 */

/**
 * \file beacon_data.cpp
 * 
 * \brief Beacon data class implementation.
 * 
 * \author Gabriel Mariano Marcelino <gabriel.mm8@gmail.com>
 * 
 * \version 1.0-dev
 * 
 * \date 12/09/2017
 * 
 * \addtogroup beacon_data
 * \{
 */

#include <cmath>
#include <iomanip>

#include "beacon_data.h"
#include "aux.hpp"

using namespace std;

BeaconData::BeaconData()
{
    
}

BeaconData::BeaconData(vector<Gtk::Label *> lbs)
{
    unsigned int pos = 0;
    
    label_beacon_data_bat1_v_value          = lbs[pos++];
    label_beacon_data_bat2_v_value          = lbs[pos++];
    label_beacon_data_bat1_t_value          = lbs[pos++];
    label_beacon_data_bat2_t_value          = lbs[pos++];
    label_beacon_data_bat_c_value           = lbs[pos++];
    label_beacon_data_sp_i_my               = lbs[pos++];
    label_beacon_data_sp_i_px               = lbs[pos++];
    label_beacon_data_sp_i_mx               = lbs[pos++];
    label_beacon_data_sp_i_pz               = lbs[pos++];
    label_beacon_data_sp_i_mz               = lbs[pos++];
    label_beacon_data_sp_i_py               = lbs[pos++];
    label_beacon_data_sp_v_mypx             = lbs[pos++];
    label_beacon_data_sp_v_mxpz             = lbs[pos++];
    label_beacon_data_sp_v_mzpy             = lbs[pos++];
    label_beacon_data_status_energy_level   = lbs[pos++];
    label_beacon_data_status_imu            = lbs[pos++]; 
    label_beacon_data_status_usd            = lbs[pos++];
    label_beacon_data_status_rush           = lbs[pos++];
    label_beacon_data_status_eps            = lbs[pos++];
    label_beacon_data_status_antenna        = lbs[pos++];
    label_beacon_data_imu_accel_x           = lbs[pos++];
    label_beacon_data_imu_accel_y           = lbs[pos++];
    label_beacon_data_imu_accel_z           = lbs[pos++];
    label_beacon_data_imu_gyro_x            = lbs[pos++];
    label_beacon_data_imu_gyro_y            = lbs[pos++];
    label_beacon_data_imu_gyro_z            = lbs[pos++];
    label_beacon_data_obdh_rst_value        = lbs[pos++];
    label_beacon_data_system_time_value     = lbs[pos++];
    
    this->Clear();
}

void BeaconData::Display(uint8_t pkt_type)
{
    label_beacon_data_bat1_v_value->set_text(BEACON_DATA_UNKNOWN_VALUE);
    label_beacon_data_bat2_v_value->set_text(BEACON_DATA_UNKNOWN_VALUE);
    label_beacon_data_bat1_t_value->set_text(BEACON_DATA_UNKNOWN_VALUE);
    label_beacon_data_bat2_t_value->set_text(BEACON_DATA_UNKNOWN_VALUE);
    label_beacon_data_bat_c_value->set_text(BEACON_DATA_UNKNOWN_VALUE);
    label_beacon_data_sp_i_my->set_text(BEACON_DATA_UNKNOWN_VALUE);
    label_beacon_data_sp_i_px->set_text(BEACON_DATA_UNKNOWN_VALUE);
    label_beacon_data_sp_i_mx->set_text(BEACON_DATA_UNKNOWN_VALUE);
    label_beacon_data_sp_i_pz->set_text(BEACON_DATA_UNKNOWN_VALUE);
    label_beacon_data_sp_i_mz->set_text(BEACON_DATA_UNKNOWN_VALUE);
    label_beacon_data_sp_i_py->set_text(BEACON_DATA_UNKNOWN_VALUE);
    label_beacon_data_sp_v_mypx->set_text(BEACON_DATA_UNKNOWN_VALUE);
    label_beacon_data_sp_v_mxpz->set_text(BEACON_DATA_UNKNOWN_VALUE);
    label_beacon_data_sp_v_mzpy->set_text(BEACON_DATA_UNKNOWN_VALUE);
    label_beacon_data_status_energy_level->set_text(BEACON_DATA_UNKNOWN_VALUE);
    label_beacon_data_status_imu->set_text(BEACON_DATA_UNKNOWN_VALUE);
    label_beacon_data_status_usd->set_text(BEACON_DATA_UNKNOWN_VALUE);
    label_beacon_data_status_rush->set_text(BEACON_DATA_UNKNOWN_VALUE);
    label_beacon_data_status_eps->set_text(BEACON_DATA_UNKNOWN_VALUE);
    label_beacon_data_status_antenna->set_text(BEACON_DATA_UNKNOWN_VALUE);
    label_beacon_data_imu_accel_x->set_text(BEACON_DATA_UNKNOWN_VALUE);
    label_beacon_data_imu_accel_y->set_text(BEACON_DATA_UNKNOWN_VALUE);
    label_beacon_data_imu_accel_z->set_text(BEACON_DATA_UNKNOWN_VALUE);
    label_beacon_data_imu_gyro_x->set_text(BEACON_DATA_UNKNOWN_VALUE);
    label_beacon_data_imu_gyro_y->set_text(BEACON_DATA_UNKNOWN_VALUE);
    label_beacon_data_imu_gyro_z->set_text(BEACON_DATA_UNKNOWN_VALUE);
    label_beacon_data_obdh_rst_value->set_text(BEACON_DATA_UNKNOWN_VALUE);
    label_beacon_data_system_time_value->set_text(BEACON_DATA_UNKNOWN_VALUE);
    
    if (pkt_type < BEACON_DATA_EPS_PKT)
    {
        return;
    }
    
    if (pkt_type <= BEACON_DATA_OBDH_PKT)
    {
        label_beacon_data_bat1_v_value->set_text(ToConstChar(bat1_voltage));
        label_beacon_data_bat2_v_value->set_text(ToConstChar(bat2_voltage));
        label_beacon_data_bat1_t_value->set_text(ToConstChar(bat1_temp));
        label_beacon_data_bat2_t_value->set_text(ToConstChar(bat2_temp));
        label_beacon_data_bat_c_value->set_text(ToConstChar(bat_charge));
        label_beacon_data_sp_i_my->set_text(ToConstChar(solar_current_1));
        label_beacon_data_sp_i_px->set_text(ToConstChar(solar_current_2));
        label_beacon_data_sp_i_mx->set_text(ToConstChar(solar_current_3));
        label_beacon_data_sp_i_pz->set_text(ToConstChar(solar_current_4));
        label_beacon_data_sp_i_mz->set_text(ToConstChar(solar_current_5));
        label_beacon_data_sp_i_py->set_text(ToConstChar(solar_current_6));
        label_beacon_data_sp_v_mypx->set_text(ToConstChar(solar_voltage_1));
        label_beacon_data_sp_v_mxpz->set_text(ToConstChar(solar_voltage_2));
        label_beacon_data_sp_v_mzpy->set_text(ToConstChar(solar_voltage_3));
        switch(energy_level)
        {
            case 1:
                label_beacon_data_status_energy_level->set_text("\u2605\u2605\u2605\u2605\u2605");
                break;
            case 2:
                label_beacon_data_status_energy_level->set_text("\u2605\u2605\u2605\u2605");
                break;
            case 3:
                label_beacon_data_status_energy_level->set_text("\u2605\u2605\u2605");
                break;
            case 4:
                label_beacon_data_status_energy_level->set_text("\u2605\u2605");
                break;
            case 5:
                label_beacon_data_status_energy_level->set_text("\u2620");
                break;
            default:
                label_beacon_data_status_energy_level->set_text(BEACON_DATA_UNKNOWN_VALUE);
                break;
        }
    }
    
    if (pkt_type == BEACON_DATA_OBDH_PKT)
    {
        label_beacon_data_status_imu->set_text(imu_status? "\u2714" : "\u2718");
        label_beacon_data_status_usd->set_text(usd_status? "\u2714" : "\u2718");
        label_beacon_data_status_rush->set_text(rush_status? "\u2714" : "\u2718");
        label_beacon_data_status_eps->set_text(eps_status? "\u2714" : "\u2718");
        label_beacon_data_status_antenna->set_text(antenna_status? "\u2714" : "\u2718");
        label_beacon_data_imu_accel_x->set_text(ToConstChar(imu_accel_x));
        label_beacon_data_imu_accel_y->set_text(ToConstChar(imu_accel_y));
        label_beacon_data_imu_accel_z->set_text(ToConstChar(imu_accel_z));
        label_beacon_data_imu_gyro_x->set_text(ToConstChar(imu_gyro_x));
        label_beacon_data_imu_gyro_y->set_text(ToConstChar(imu_gyro_y));
        label_beacon_data_imu_gyro_z->set_text(ToConstChar(imu_gyro_z));
        label_beacon_data_obdh_rst_value->set_text(ToConstChar(obdh_resets));
        label_beacon_data_system_time_value->set_text(PrintTime(system_time_hou, system_time_min, system_time_sec));
    }
}

void BeaconData::Update(uint8_t *data, uint8_t len)
{
    if (len > 10)
    {
    #if BEACON_DATA_ENDIENESS == BEACON_DATA_LSB_FIRST
        bat1_voltage        = BatVoltConv((data[11] << 8) | data[10]);
        bat2_voltage        = BatVoltConv((data[13] << 8) | data[12]);
        bat1_temp           = BatTempConv((data[16] << 16) | (data[15] << 8) | data[14]);
        bat2_temp           = BatTempConv((data[19] << 16) | (data[18] << 8) | data[17]);
        bat_charge          = BatChargeConv((data[21] << 8) | data[20]);
        solar_current_1     = SolarPanelCurrentConv((data[23] << 8) | data[22]);
        solar_current_2     = SolarPanelCurrentConv((data[25] << 8) | data[24]);
        solar_current_3     = SolarPanelCurrentConv((data[27] << 8) | data[26]);
        solar_current_4     = SolarPanelCurrentConv((data[29] << 8) | data[28]);
        solar_current_5     = SolarPanelCurrentConv((data[31] << 8) | data[30]);
        solar_current_6     = SolarPanelCurrentConv((data[33] << 8) | data[32]);
        solar_voltage_1     = SolarPanelVoltageConv((data[35] << 8) | data[34]);
        solar_voltage_2     = SolarPanelVoltageConv((data[37] << 8) | data[36]);
        solar_voltage_3     = SolarPanelVoltageConv((data[39] << 8) | data[38]);
    #elif BEACON_DATA_ENDIENESS == BEACON_DATA_MSB_FIRST
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
    #endif // BEACON_DATA_ENDIENESS
        energy_level        = data[40];
        type_last_pkt = BEACON_DATA_EPS_PKT;
        
        if (len > 41)
        {
            imu_status          = bool((data[41] >> 4) & 1);
            usd_status          = bool((data[41] >> 3) & 1);
            rush_status         = bool((data[41] >> 1) & 1);
            eps_status          = bool((data[41] >> 0) & 1);
            antenna_status      = bool((data[41] >> 5) & 1);
        #if BEACON_DATA_ENDIENESS == BEACON_DATA_LSB_FIRST
            imu_accel_x         = IMUAccelConv((data[43] << 8) | data[42]);
            imu_accel_y         = IMUAccelConv((data[45] << 8) | data[44]);
            imu_accel_z         = IMUAccelConv((data[47] << 8) | data[46]);
            imu_gyro_x          = IMUGyroConv((data[49] << 8) | data[48]);
            imu_gyro_y          = IMUGyroConv((data[51] << 8) | data[50]);
            imu_gyro_z          = IMUGyroConv((data[53] << 8) | data[52]);
            system_time_sec     = data[54];
            system_time_min     = (data[57] | (data[56] << 8) | (data[55] << 16))%60;
            system_time_hou     = (data[57] | (data[56] << 8) | (data[55] << 16))/60;
            obdh_resets         = data[59] + data[58]*256;
        #elif BEACON_DATA_ENDIENESS == BEACON_DATA_MSB_FIRST
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
        #endif // BEACON_DATA_ENDIENESS
            
            type_last_pkt = BEACON_DATA_OBDH_PKT;
            
            this->Display(BEACON_DATA_OBDH_PKT);
        }
        else
        {
            this->Display(BEACON_DATA_EPS_PKT);
        }
    }
    else
    {
        type_last_pkt = BEACON_DATA_SAT_ID_PKT;
        
        this->Display(BEACON_DATA_SAT_ID_PKT);
    }
}

void BeaconData::Clear()
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

string BeaconData::Log()
{
    string log_entry = "";
    
    if (type_last_pkt < BEACON_DATA_EPS_PKT)
    {
        return log_entry;
    }
    
    if (type_last_pkt <= BEACON_DATA_OBDH_PKT)
    {
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
    }
    
    if (type_last_pkt == BEACON_DATA_OBDH_PKT)
    {
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
    }
    
    return log_entry;
}

const char* BeaconData::getLabel()
{
    return "BEACON";
}

double BeaconData::BatVoltConv(uint16_t val)
{
    return (val/32.0)*4.883e-3;
}

double BeaconData::BatTempConv(uint32_t val)
{
    return (val*0.125)/32.0;
}

double BeaconData::BatChargeConv(uint16_t val)
{
    return val*(6.25*1e-4);
}

double BeaconData::SolarPanelCurrentConv(uint16_t val)
{
    return val*(2.5/4095)*(1/(0.05*0.025*3300));
}

double BeaconData::SolarPanelVoltageConv(uint16_t val)
{
    return val*(2.5/4095)*(100e3 + 93.1e3)/100e3;
}

double BeaconData::IMUAccelConv(uint16_t val)
{
    return int16_t(val)*16.0/32768.0;
}

double BeaconData::IMUGyroConv(uint16_t val)
{
    return int16_t(val)*250.0/32768.0;
}

const char* BeaconData::PrintTime(uint8_t h, uint8_t m, uint8_t s)
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

//! \} End of beacon_data group
