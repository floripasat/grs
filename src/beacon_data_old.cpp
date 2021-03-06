/*
 * beacon_data.cpp
 * 
 * Copyright (C) 2017, Universidade Federal de Santa Catarina.
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
 * \brief Beacon data class implementation.
 * 
 * \author Gabriel Mariano Marcelino <gabriel.mm8@gmail.com>
 * 
 * \version 0.7.11
 * 
 * \date 12/09/2017
 * 
 * \addtogroup beacon_data
 * \{
 */

#include <cmath>
#include <iomanip>

#include "beacon_data_old.h"
#include "aux.hpp"

using namespace std;

BeaconDataOld::BeaconDataOld()
{
    
}

BeaconDataOld::BeaconDataOld(vector<Gtk::Label *> lbs)
{
    unsigned int pos = 0;

    label_beacon_data_bat1_v_value          = lbs[pos++];
    label_beacon_data_bat2_v_value          = lbs[pos++];
    label_beacon_data_bat_mon_value         = lbs[pos++];
    label_beacon_data_bat_current_value     = lbs[pos++];
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
    label_beacon_data_uc_temp_value         = lbs[pos++];
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

void BeaconDataOld::Display(uint8_t pkt_type)
{
    label_beacon_data_bat1_v_value->set_text(BEACON_DATA_UNKNOWN_VALUE);
    label_beacon_data_bat2_v_value->set_text(BEACON_DATA_UNKNOWN_VALUE);
    label_beacon_data_bat_mon_value->set_text(BEACON_DATA_UNKNOWN_VALUE);
    label_beacon_data_bat_current_value->set_text(BEACON_DATA_UNKNOWN_VALUE);
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
    label_beacon_data_uc_temp_value->set_text(BEACON_DATA_UNKNOWN_VALUE);
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
        label_beacon_data_bat_mon_value->set_text(to_string(bat_monitor_temp).c_str());
        label_beacon_data_bat_current_value->set_text(to_string(bat_current).c_str());
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
    label_beacon_data_uc_temp_value->set_text(to_string(eps_uc_temp).c_str());
    
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

void BeaconDataOld::Update(uint8_t *data, uint8_t len)
{
    if (len > 8)
    {
    #if BEACON_DATA_ENDIENESS == BEACON_DATA_LSB_FIRST
        bat1_voltage        = BatVoltConv((data[9] << 8) | data[8]);
        bat2_voltage        = BatVoltConv((data[11] << 8) | data[10]);
//        bat1_temp           = BatTempConv((data[14] << 16) | (data[13] << 8) | data[12]);
//        bat2_temp           = BatTempConv((data[17] << 16) | (data[16] << 8) | data[15]);
        bat_monitor_temp    = BatMonitorTempConv(((uint16_t)data[13] << 8) | data[12]);
        bat_current         = BatCurrentConv(((uint16_t)data[15] << 8) | data[14]);
        eps_uc_temp         = EPSuCTempConv(((uint16_t)data[17] << 8) | data[16]);
        bat_charge          = BatChargeConv((data[19] << 8) | data[18]);
        solar_current_1     = SolarPanelCurrentConv((data[21] << 8) | data[20]);
        solar_current_2     = SolarPanelCurrentConv((data[23] << 8) | data[22]);
        solar_current_3     = SolarPanelCurrentConv((data[25] << 8) | data[24]);
        solar_current_4     = SolarPanelCurrentConv((data[27] << 8) | data[26]);
        solar_current_5     = SolarPanelCurrentConv((data[29] << 8) | data[28]);
        solar_current_6     = SolarPanelCurrentConv((data[31] << 8) | data[30]);
        solar_voltage_1     = SolarPanelVoltageConv((data[33] << 8) | data[32]);
        solar_voltage_2     = SolarPanelVoltageConv((data[35] << 8) | data[34]);
        solar_voltage_3     = SolarPanelVoltageConv((data[37] << 8) | data[36]);
    #elif BEACON_DATA_ENDIENESS == BEACON_DATA_MSB_FIRST
        bat1_voltage        = BatVoltConv((data[8] << 8) | data[9]);
        bat2_voltage        = BatVoltConv((data[10] << 8) | data[11]);
//        bat1_temp           = BatTempConv((data[12] << 16) | (data[13] << 8) | data[14]);
//        bat2_temp           = BatTempConv((data[15] << 16) | (data[16] << 8) | data[17]);
        bat_monitor_temp    = BatMonitorTempConv(((uint16_t)data[12] << 8) | data[13]);
        bat_current         = BatCurrentConv(((uint16_t)data[14] << 8) | data[15]);
        eps_uc_temp         = EPSuCTempConv(((uint16_t)data[16] << 8) | data[17]);
        bat_charge          = BatChargeConv((data[18] << 8) | data[19]);
        solar_current_1     = SolarPanelCurrentConv((data[20] << 8) | data[21]);
        solar_current_2     = SolarPanelCurrentConv((data[22] << 8) | data[23]);
        solar_current_3     = SolarPanelCurrentConv((data[24] << 8) | data[25]);
        solar_current_4     = SolarPanelCurrentConv((data[26] << 8) | data[27]);
        solar_current_5     = SolarPanelCurrentConv((data[28] << 8) | data[29]);
        solar_current_6     = SolarPanelCurrentConv((data[30] << 8) | data[31]);
        solar_voltage_1     = SolarPanelVoltageConv((data[32] << 8) | data[33]);
        solar_voltage_2     = SolarPanelVoltageConv((data[34] << 8) | data[35]);
        solar_voltage_3     = SolarPanelVoltageConv((data[36] << 8) | data[37]);
    #endif // BEACON_DATA_ENDIENESS
        energy_level        = data[38];
        type_last_pkt = BEACON_DATA_EPS_PKT;
        
        if (len > 39)
        {
            imu_status          = bool((data[39] >> 4) & 1);
            usd_status          = bool((data[39] >> 3) & 1);
            rush_status         = bool((data[39] >> 1) & 1);
            eps_status          = bool((data[39] >> 0) & 1);
            antenna_status      = bool((data[39] >> 5) & 1);
        #if BEACON_DATA_ENDIENESS == BEACON_DATA_LSB_FIRST
            imu_accel_x         = IMUAccelConv((data[41] << 8) | data[40]);
            imu_accel_y         = IMUAccelConv((data[43] << 8) | data[42]);
            imu_accel_z         = IMUAccelConv((data[45] << 8) | data[44]);
            imu_gyro_x          = IMUGyroConv((data[47] << 8) | data[46]);
            imu_gyro_y          = IMUGyroConv((data[49] << 8) | data[48]);
            imu_gyro_z          = IMUGyroConv((data[51] << 8) | data[50]);
            system_time_sec     = data[52];
            system_time_min     = ((data[55] << 16) | (data[54] << 8) | data[53])%60;
            system_time_hou     = ((data[55] << 16) | (data[54] << 8) | data[53])/60;    
            obdh_resets         = data[56] + data[57]*256;
        #elif BEACON_DATA_ENDIENESS == BEACON_DATA_MSB_FIRST
            imu_accel_x         = IMUAccelConv((data[40] << 8) | data[41]);
            imu_accel_y         = IMUAccelConv((data[42] << 8) | data[43]);
            imu_accel_z         = IMUAccelConv((data[44] << 8) | data[45]);
            imu_gyro_x          = IMUGyroConv((data[46] << 8) | data[47]);
            imu_gyro_y          = IMUGyroConv((data[48] << 8) | data[49]);
            imu_gyro_z          = IMUGyroConv((data[50] << 8) | data[51]);
            system_time_sec     = data[52];
            system_time_min     = ((data[53] << 16) | (data[54] << 8) | data[55])%60;
            system_time_hou     = ((data[53] << 16) | (data[54] << 8) | data[55])/60;
            obdh_resets         = data[57] + data[56]*256;
        #endif // BEACON_DATA_ENDIENESS
            
            type_last_pkt = BEACON_DATA_OBDH_PKT;
            
            this->Display(uint8_t(BEACON_DATA_OBDH_PKT));
        }
        else
        {
            this->Display(uint8_t(BEACON_DATA_EPS_PKT));
        }
    }
    else
    {
        type_last_pkt = BEACON_DATA_SAT_ID_PKT;
        
        this->Display(uint8_t(BEACON_DATA_SAT_ID_PKT));
    }
}

void BeaconDataOld::Clear()
{
    bat1_voltage        = 0;
    bat2_voltage        = 0;
    bat1_temp           = 0;
    bat2_temp           = 0;
    bat_monitor_temp    = 0;
    bat_current         = 0;
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
    eps_uc_temp         = 0;
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

string BeaconDataOld::Log()
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
//        log_entry += ToString(bat1_temp);
//        log_entry += ",";
//        log_entry += ToString(bat2_temp);
//        log_entry += ",";
        log_entry += ToString(bat_monitor_temp);
        log_entry += ",";
        log_entry += ToString(bat_current);
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
    else
    {
        log_entry += ",";
        log_entry += ",";
        log_entry += ",";
        log_entry += ",";
        log_entry += ",";
        log_entry += ",";
        log_entry += ",";
        log_entry += ",";
        log_entry += ",";
        log_entry += ",";
        log_entry += ",";
        log_entry += ",";
        log_entry += ",";
        log_entry += ",";
        log_entry += ",";
        log_entry += ",";
        log_entry += ToString(eps_uc_temp);
    }
    
    return log_entry;
}

const char* BeaconDataOld::getLabel()
{
    return "Beacon";
}

void BeaconDataOld::ForceDisplay(vector<string> data)
{
    while(data.size() < 32)
    {
        data.push_back(std::string("-"));
    }

    unsigned int i = 6;

    label_beacon_data_bat1_v_value->set_text(data[i++]);
    label_beacon_data_bat2_v_value->set_text(data[i++]);
//    label_beacon_data_bat1_t_value->set_text(data[i++]);
//    label_beacon_data_bat2_t_value->set_text(data[i++]);
    label_beacon_data_bat_mon_value->set_text(data[i++]);
    label_beacon_data_bat_current_value->set_text(data[i++]);
    label_beacon_data_bat_c_value->set_text(data[i++]);
    label_beacon_data_sp_i_my->set_text(data[i++]);
    label_beacon_data_sp_i_px->set_text(data[i++]);
    label_beacon_data_sp_i_mx->set_text(data[i++]);
    label_beacon_data_sp_i_pz->set_text(data[i++]);
    label_beacon_data_sp_i_mz->set_text(data[i++]);
    label_beacon_data_sp_i_py->set_text(data[i++]);
    label_beacon_data_sp_v_mypx->set_text(data[i++]);
    label_beacon_data_sp_v_mxpz->set_text(data[i++]);
    label_beacon_data_sp_v_mzpy->set_text(data[i++]);
    label_beacon_data_status_energy_level->set_text(data[i++]);
    label_beacon_data_status_imu->set_text(data[i++]);
    label_beacon_data_status_usd->set_text(data[i++]);
    label_beacon_data_status_rush->set_text(data[i++]);
    label_beacon_data_status_eps->set_text(data[i++]);
    label_beacon_data_status_antenna->set_text(data[i++]);
    label_beacon_data_imu_accel_x->set_text(data[i++]);
    label_beacon_data_imu_accel_y->set_text(data[i++]);
    label_beacon_data_imu_accel_z->set_text(data[i++]);
    label_beacon_data_imu_gyro_x->set_text(data[i++]);
    label_beacon_data_imu_gyro_y->set_text(data[i++]);
    label_beacon_data_imu_gyro_z->set_text(data[i++]);
    label_beacon_data_obdh_rst_value->set_text(data[i++]);
    label_beacon_data_system_time_value->set_text(data[i++]);
}

double BeaconDataOld::BatVoltConv(uint16_t val)
{
    return (val/32.0)*4.883e-3;
}

double BeaconDataOld::BatTempConv(uint32_t val)
{
    return (val*0.125)/32.0;
}

double BeaconDataOld::BatChargeConv(uint16_t val)
{
    return val*(6.25*1e-4);
}

double BeaconDataOld::SolarPanelCurrentConv(uint16_t val)
{
    return val*(2.5/4095)*(1/(0.05*0.025*3300));
}

double BeaconDataOld::SolarPanelVoltageConv(uint16_t val)
{
    return val*(2.5/4095)*(100e3 + 93.1e3)/100e3;
}

double BeaconDataOld::IMUAccelConv(uint16_t val)
{
    return int16_t(val)*16.0/32768.0;
}

double BeaconDataOld::IMUGyroConv(uint16_t val)
{
    return int16_t(val)*250.0/32768.0;
}

const char* BeaconDataOld::PrintTime(uint16_t h, uint8_t m, uint8_t s)
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

double BeaconDataOld::BatMonitorTempConv(uint16_t val)
{
    return (int16_t)(val) * 0.125 / 32.0;
}

double BeaconDataOld::BatCurrentConv(uint16_t val)
{
    return int16_t(val) * (1.5625e-6 / 0.01);
}

double BeaconDataOld::EPSuCTempConv(uint16_t val)
{
    return (val * (2.5 / 4095.0)  - 0.680) * 70.0 / 0.170;
}

//! \} End of beacon_data group
