/*
 * beacon_data.cpp
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
 * \file beacon_data.cpp
 * 
 * \brief .
 * 
 * \author Gabriel Mariano Marcelino <gabriel.mm8@gmail.com>
 * 
 * \version 1.2
 * 
 * \date 12/09/2017
 * 
 * \addtogroup beacon_data
 * \{
 */

#include <cmath>
#include <string>
#include <iomanip>

#include "beacon_data.h"
#include "aux.hpp"

BeaconData::BeaconData()
{
    
}

BeaconData::BeaconData(Gtk::Label *bat1_v, Gtk::Label *bat2_v, Gtk::Label *bat1_t,
                       Gtk::Label *bat2_t, Gtk::Label *bat_c, Gtk::Label *solar_i_1,
                       Gtk::Label *solar_i_2, Gtk::Label *solar_v, Gtk::Label *status,
                       Gtk::Label *imu_data1, Gtk::Label *imu_data2, Gtk::Label *system_time,
                       Gtk::Label *obdh_rst)
{
    label_bat1_v        = bat1_v;
    label_bat2_v        = bat2_v;
    label_bat1_t        = bat1_t;
    label_bat2_t        = bat2_t;
    label_bat_c         = bat_c;
    label_solar_i_1     = solar_i_1;
    label_solar_i_2     = solar_i_2;
    label_solar_v       = solar_v;
    label_status        = status;
    label_imu_data1     = imu_data1;
    label_imu_data2     = imu_data2;
    label_system_time   = system_time;
    label_obdh_rst      = obdh_rst;
    
    this->Clear();
}

BeaconData::~BeaconData()
{
    
}

void BeaconData::Display(uint8_t pkt_type)
{
    switch(pkt_type)
    {
        case BEACON_DATA_EPS_PKT:
            label_bat1_v->set_text(ToConstChar(bat1_voltage));
            label_bat2_v->set_text(ToConstChar(bat2_voltage));
            label_bat1_t->set_text(ToConstChar(bat1_temp));
            label_bat2_t->set_text(ToConstChar(bat2_temp));
            label_bat_c->set_text(ToConstChar(bat_charge));
            label_solar_i_1->set_text(PrintAxisData(solar_current_1, solar_current_2, solar_current_3));
            label_solar_i_2->set_text(PrintAxisData(solar_current_4, solar_current_5, solar_current_6));
            label_solar_v->set_text(PrintAxisData(solar_voltage_1, solar_voltage_2, solar_voltage_3));
            label_status->set_text(BEACON_DATA_UNKNOWN_VALUE);
            label_imu_data1->set_text(BEACON_DATA_UNKNOWN_VALUE);
            label_imu_data2->set_text(BEACON_DATA_UNKNOWN_VALUE);
            label_system_time->set_text(BEACON_DATA_UNKNOWN_VALUE);
            label_obdh_rst->set_text(BEACON_DATA_UNKNOWN_VALUE);
            break;
        case BEACON_DATA_OBDH_PKT:
            label_bat1_v->set_text(ToConstChar(bat1_voltage));
            label_bat2_v->set_text(ToConstChar(bat2_voltage));
            label_bat1_t->set_text(ToConstChar(bat1_temp));
            label_bat2_t->set_text(ToConstChar(bat2_temp));
            label_bat_c->set_text(ToConstChar(bat_charge));
            label_solar_i_1->set_text(PrintAxisData(solar_current_1, solar_current_2, solar_current_3));
            label_solar_i_2->set_text(PrintAxisData(solar_current_4, solar_current_5, solar_current_6));
            label_solar_v->set_text(PrintAxisData(solar_voltage_1, solar_voltage_2, solar_voltage_3));
            label_status->set_text(BEACON_DATA_UNKNOWN_VALUE);
            label_imu_data1->set_text(PrintAxisData(imu_accel_x, imu_accel_y, imu_accel_z));
            label_imu_data2->set_text(PrintAxisData(imu_gyro_x, imu_gyro_y, imu_gyro_z));
            label_system_time->set_text(ToConstChar(system_time_sec));
            label_obdh_rst->set_text(ToConstChar(obdh_resets));
            break;
        default:
            label_bat1_v->set_text(BEACON_DATA_UNKNOWN_VALUE);
            label_bat2_v->set_text(BEACON_DATA_UNKNOWN_VALUE);
            label_bat1_t->set_text(BEACON_DATA_UNKNOWN_VALUE);
            label_bat2_t->set_text(BEACON_DATA_UNKNOWN_VALUE);
            label_bat_c->set_text(BEACON_DATA_UNKNOWN_VALUE);
            label_solar_i_1->set_text(BEACON_DATA_UNKNOWN_VALUE);
            label_solar_i_2->set_text(BEACON_DATA_UNKNOWN_VALUE);
            label_solar_v->set_text(BEACON_DATA_UNKNOWN_VALUE);
            label_status->set_text(BEACON_DATA_UNKNOWN_VALUE);
            label_imu_data1->set_text(BEACON_DATA_UNKNOWN_VALUE);
            label_imu_data2->set_text(BEACON_DATA_UNKNOWN_VALUE);
            label_system_time->set_text(BEACON_DATA_UNKNOWN_VALUE);
            label_obdh_rst->set_text(BEACON_DATA_UNKNOWN_VALUE);
            break;
    }
}

void BeaconData::Update(uint8_t *data, uint8_t len)
{
    if (len > 10)
    {
        bat1_voltage        = BatVoltConv((data[10] << 8) | data[11]);
        bat1_voltage        = BatVoltConv((data[12] << 8) | data[13]);
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
        
        type_last_pkt = BEACON_DATA_EPS_PKT;
        
        if (len > 40)
        {
            imu_accel_x         = IMUAccelConv((data[42] << 8) | data[43]);
            imu_accel_y         = IMUAccelConv((data[44] << 8) | data[45]);
            imu_accel_z         = IMUAccelConv((data[46] << 8) | data[47]);
            imu_gyro_x          = IMUGyroConv((data[48] << 8) | data[49]);
            imu_gyro_y          = IMUGyroConv((data[50] << 8) | data[51]);
            imu_gyro_z          = IMUGyroConv((data[52] << 8) | data[53]);
            system_time_sec     = data[54] + (60*data[55]);
            obdh_resets         = (data[58] << 8) | data[59];
            
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
    imu_accel_x         = 0;
    imu_accel_y         = 0;
    imu_accel_z         = 0;
    imu_gyro_x          = 0;
    imu_gyro_y          = 0;
    imu_gyro_z          = 0;
    system_time_sec     = 0;
    obdh_resets         = 0;
    
    this->Display(BEACON_DATA_SAT_ID_PKT);
}

const char* BeaconData::Log()
{
    std::string log_entry = "";
    
    switch(type_last_pkt)
    {
        case BEACON_DATA_EPS_PKT:
            log_entry += bat1_voltage;
            log_entry += ",";
            log_entry += bat2_voltage;
            log_entry += ",";
            log_entry += bat1_temp;
            log_entry += ",";
            log_entry += bat2_temp;
            log_entry += ",";
            log_entry += bat_charge;
            log_entry += ",";
            log_entry += solar_current_1;
            log_entry += ",";
            log_entry += solar_current_2;
            log_entry += ",";
            log_entry += solar_current_3;
            log_entry += ",";
            log_entry += solar_current_4;
            log_entry += ",";
            log_entry += solar_current_5;
            log_entry += ",";
            log_entry += solar_current_6;
            log_entry += ",";
            log_entry += solar_voltage_1;
            log_entry += ",";
            log_entry += solar_voltage_2;
            log_entry += ",";
            log_entry += solar_voltage_3;
            log_entry += ",,,,,,,,";
            break;
        case BEACON_DATA_OBDH_PKT:
            log_entry += bat1_voltage;
            log_entry += ",";
            log_entry += bat2_voltage;
            log_entry += ",";
            log_entry += bat1_temp;
            log_entry += ",";
            log_entry += bat2_temp;
            log_entry += ",";
            log_entry += bat_charge;
            log_entry += ",";
            log_entry += solar_current_1;
            log_entry += ",";
            log_entry += solar_current_2;
            log_entry += ",";
            log_entry += solar_current_3;
            log_entry += ",";
            log_entry += solar_current_4;
            log_entry += ",";
            log_entry += solar_current_5;
            log_entry += ",";
            log_entry += solar_current_6;
            log_entry += ",";
            log_entry += solar_voltage_1;
            log_entry += ",";
            log_entry += solar_voltage_2;
            log_entry += ",";
            log_entry += solar_voltage_3;
            log_entry += ",";
            log_entry += imu_accel_x;
            log_entry += ",";
            log_entry += imu_accel_y;
            log_entry += ",";
            log_entry += imu_accel_z;
            log_entry += ",";
            log_entry += imu_gyro_x;
            log_entry += ",";
            log_entry += imu_gyro_y;
            log_entry += ",";
            log_entry += imu_gyro_z;
            log_entry += ",";
            log_entry += system_time_sec;
            log_entry += ",";
            log_entry += obdh_resets;
            break;
        default:
            log_entry += ",,,,,,,,,,,,,,,,,,,,,";
            break;
    };
    
    return log_entry.c_str();
}

double BeaconData::BatVoltConv(uint16_t val)
{
    return (val/32)*4.883e-3;
}

double BeaconData::BatTempConv(uint32_t val)
{
    return ((val*(1.65*2/pow(2, 24))*1e3)-1000)*1/3.85;
}

double BeaconData::BatChargeConv(uint16_t val)
{
    return 0;
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

const char* BeaconData::PrintAxisData(double x, double y, double z, uint8_t dig)
{
    std::stringstream input_str;
    
    input_str << std::fixed << std::setprecision(dig) << x;
    input_str << "/";
    input_str << std::fixed << std::setprecision(dig) << y;
    input_str << "/";
    input_str << std::fixed << std::setprecision(dig) << z;
    
    std::string output = input_str.str();
    
    return output.c_str();
}

//! \} End of beacon_data group
