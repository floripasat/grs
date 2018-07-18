/*
 * telemetry_data.cpp
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
 * \file telemetry_data.cpp
 *
 * \brief Telemetry data class implementation.
 *
 * \author Gabriel Mariano Marcelino <gabriel.mm8@gmail.com>
 *
 * \version 1.0-dev
 *
 * \date 08/10/2017
 *
 * \addtogroup telemetry_data
 * \{
 */

#include <iomanip>
#include <fstream>
#include <string>

#include "telemetry_data.h"
#include "aux.hpp"

#define  OBDH_STATUS_FLAG           (0x0001)
#define  IMU_FLAG                   (0x0002)
#define  OBDH_MISC_FLAG             (0x0004)
#define  SOLAR_PANELS_SENSORS_FLAG  (0x0008)
#define  MAIN_RADIO_FLAG            (0x0010)
#define  SOLAR_PANELS_FLAG          (0x0020)
#define  EPS_MISC_FLAG              (0x0040)
#define  BATTERY_MONITOR_FLAG       (0x0080)
#define  TEMPERATURES_FLAG          (0x0100)
#define  ENERGY_LEVEL_FLAG          (0x0200)
#define  PAYLOAD1_FLAG              (0x0400)
#define  PAYLOAD2_FLAG              (0x0800)

#define WHOLE_ORBIT_DATA_FLAG       (0x8000)

#define has_flag(x,y)   (x & y)

typedef struct {
    uint16_t package_flags;
    //obdh
    uint8_t obdh_status             [6];
    uint8_t imu                     [24];
    uint8_t obdh_misc               [6];
    uint8_t obdh_uptime             [4];
    uint8_t solar_panels_sensors    [12];
    uint8_t main_radio              [19];
    //eps
    uint8_t solar_panels            [18];
    uint8_t eps_misc                [8];
    uint8_t battery_monitor         [21];
    uint8_t temperatures            [21];
    uint8_t energy_level            [1];
    //payloads
    uint8_t payload1                [40];
    uint8_t payload2                [7];
} data_packet_t;

using namespace std;

TelemetryData::TelemetryData()
{

}

TelemetryData::TelemetryData(std::vector<Gtk::Label *> lbs)
{
    unsigned int pos = 0;

    label_telemetry_data_status_reset_counter   = lbs[pos++];
    label_telemetry_data_status_reset_cause     = lbs[pos++];
    label_telemetry_data_status_clock           = lbs[pos++];
    label_telemetry_data_status_imu             = lbs[pos++];
    label_telemetry_data_status_usd             = lbs[pos++];
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

void TelemetryData::Display(bool no_data)
{
    if (no_data)
    {
        label_telemetry_data_status_reset_counter->set_text(TELEMETRY_DATA_UNKNOWN_VALUE);
        label_telemetry_data_status_reset_cause->set_text(TELEMETRY_DATA_UNKNOWN_VALUE);
        label_telemetry_data_status_clock->set_text(TELEMETRY_DATA_UNKNOWN_VALUE);
        label_telemetry_data_status_imu->set_text(TELEMETRY_DATA_UNKNOWN_VALUE);
        label_telemetry_data_status_usd->set_text(TELEMETRY_DATA_UNKNOWN_VALUE);
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
    }
    else
    {
        label_telemetry_data_status_reset_counter->set_text(ToConstChar(reset_counter));
        label_telemetry_data_status_reset_cause->set_text(ToConstChar(int(reset_cause)));
        label_telemetry_data_status_clock->set_text(ToConstChar(int(clock_fault_flags)));
        label_telemetry_data_status_imu->set_text(imu_status? "\u2714" : "\u2718");
        label_telemetry_data_status_usd->set_text(usd_status? "\u2714" : "\u2718");
        label_telemetry_data_status_rush->set_text(rush_status? "\u2714" : "\u2718");
        label_telemetry_data_status_eps->set_text(eps_status? "\u2714" : "\u2718");
        label_telemetry_data_status_antenna->set_text(antenna_status? "\u2714" : "\u2718");
        label_telemetry_data_uc_temp->set_text(ToConstChar(MSP_temperature));
        label_telemetry_data_uc_voltage->set_text(ToConstChar(supply_voltage));
        label_telemetry_data_uc_current->set_text(ToConstChar(supply_current));
        label_telemetry_data_time_system->set_text(this->PrintTime(system_time_hou, system_time_min, system_time_sec));
        label_telemetry_data_time_system_up->set_text(this->PrintTime(system_time_hou, system_time_min, system_time_sec));
        label_telemetry_data_imu_accel_x->set_text(this->PrintIMUs(imu_1_accel_x, imu_2_accel_x));
        label_telemetry_data_imu_accel_y->set_text(this->PrintIMUs(imu_1_accel_y, imu_2_accel_y));
        label_telemetry_data_imu_accel_z->set_text(this->PrintIMUs(imu_1_accel_z, imu_2_accel_z));
        label_telemetry_data_imu_gyro_x->set_text(this->PrintIMUs(imu_1_gyro_x, imu_2_gyro_x));
        label_telemetry_data_imu_gyro_y->set_text(this->PrintIMUs(imu_1_gyro_y, imu_2_gyro_y));
        label_telemetry_data_imu_gyro_z->set_text(this->PrintIMUs(imu_1_gyro_z, imu_2_gyro_z));
        label_telemetry_data_sp_sun_p1->set_text(ToConstChar(RTD_measurement_1));
        label_telemetry_data_sp_sun_p2->set_text(ToConstChar(RTD_measurement_2));
        label_telemetry_data_sp_sun_p3->set_text(ToConstChar(RTD_measurement_3));
        label_telemetry_data_sp_temp_p1->set_text(ToConstChar(RTD_measurement_4));
        label_telemetry_data_sp_temp_p2->set_text(ToConstChar(RTD_measurement_5));
        label_telemetry_data_sp_temp_p3->set_text(ToConstChar(RTD_measurement_6));
        label_telemetry_data_eps_bat_mean_i->set_text(ToConstChar(bat_average_current));
        label_telemetry_data_eps_bat_temp->set_text(ToConstChar(bat_temperature));
        label_telemetry_data_eps_bat_1_volt->set_text(ToConstChar(bat1_voltage));
        label_telemetry_data_eps_bat_2_volt->set_text(ToConstChar(bat2_voltage));
        label_telemetry_data_eps_bat_current->set_text(ToConstChar(bat_current));
        label_telemetry_data_eps_bat_charge->set_text(ToConstChar(bat_accumulated_current));
        label_telemetry_data_eps_bat_protection->set_text(ToConstChar(int(protection_register)));
        label_telemetry_data_eps_bat_status->set_text(ToConstChar(int(status_register)));
        label_telemetry_data_eps_bat_cycles->set_text(ToConstChar(cycle_counter_register));
        label_telemetry_data_eps_bat_raac->set_text(ToConstChar(active_absolute_capacity));
        label_telemetry_data_eps_bat_rsac->set_text(ToConstChar(standby_absolute_capacity));
        label_telemetry_data_eps_bat_rarc->set_text(ToConstChar(active_relative_capacity));
        label_telemetry_data_eps_bat_rsrc->set_text(ToConstChar(standby_relative_capacity));
        label_telemetry_data_eps_sp_i_my->set_text(ToConstChar(solar_current_1));
        label_telemetry_data_eps_sp_i_px->set_text(ToConstChar(solar_current_2));
        label_telemetry_data_eps_sp_i_mx->set_text(ToConstChar(solar_current_3));
        label_telemetry_data_eps_sp_i_pz->set_text(ToConstChar(solar_current_4));
        label_telemetry_data_eps_sp_i_mz->set_text(ToConstChar(solar_current_5));
        label_telemetry_data_eps_sp_i_py->set_text(ToConstChar(solar_current_6));
        label_telemetry_data_eps_sp_v_mypx->set_text(ToConstChar(solar_voltage_1));
        label_telemetry_data_eps_sp_v_mxpz->set_text(ToConstChar(solar_voltage_2));
        label_telemetry_data_eps_sp_v_mzpy->set_text(ToConstChar(solar_voltage_3));
        label_telemetry_data_eps_misc_boost_v->set_text(ToConstChar(boost_voltage));
        label_telemetry_data_eps_misc_main_bus_v->set_text(ToConstChar(main_power_voltage));
        label_telemetry_data_eps_misc_beacon_i->set_text(ToConstChar(BEACON_EPS_current));
        label_telemetry_data_eps_misc_uc_temp->set_text(ToConstChar(ADC_temperature));
        switch(EPS_status)
        {
            case 1:
                label_telemetry_data_eps_misc_energy_level->set_text("\u2605\u2605\u2605\u2605\u2605");
                break;
            case 2:
                label_telemetry_data_eps_misc_energy_level->set_text("\u2605\u2605\u2605\u2605");
                break;
            case 3:
                label_telemetry_data_eps_misc_energy_level->set_text("\u2605\u2605\u2605");
                break;
            case 4:
                label_telemetry_data_eps_misc_energy_level->set_text("\u2605\u2605");
                break;
            case 5:
                label_telemetry_data_eps_misc_energy_level->set_text("\u2620");
                break;
            default:
                label_telemetry_data_eps_misc_energy_level->set_text(TELEMETRY_DATA_UNKNOWN_VALUE);
                break;
        }
    }
}

void TelemetryData::Update(uint8_t *data, uint8_t len)
{
    data_packet_t packet;

    uint16_t flags = ((uint16_t)data[1]<<8) | (uint16_t) data[0];
    uint16_t rqt_flags;
    //flags = flags & rqt_packet.flags;
    uint16_t packageSize = 2;

    unsigned int i;

    string homepath = getenv("HOME");

    ifstream file_flags((homepath + "/.fsat_grs/packet_flags.txt").c_str(), ifstream::in);
    if (file_flags.is_open())
    {
        file_flags.read((char *)&rqt_flags, 2);
        file_flags.close();
    }

    /** Periodic telemetry or first requested frame: ignore the flags cause it has the whole orbit data anyway */
    if (has_flag(flags, WHOLE_ORBIT_DATA_FLAG))
    {
        flags = 0xffff;
        packet_flags = packet.package_flags;
    }
    else
    {
       flags =  flags & rqt_flags;
       packet_flags = packet.package_flags;
    }

    for(i = 0; i < sizeof(packet.obdh_uptime); i++)
    {
        packet.obdh_uptime[i] = data[packageSize++];
    }
    system_time_sec = packet.obdh_uptime[0];
    system_time_min = ((packet.obdh_uptime[1] << 16) | (packet.obdh_uptime[2] << 8) | packet.obdh_uptime[3])%60;
    system_time_hou = ((packet.obdh_uptime[1] << 16) | (packet.obdh_uptime[2] << 8) | packet.obdh_uptime[3])/60;

    if(has_flag(flags, OBDH_STATUS_FLAG))
    {
        for(i = 0; i < sizeof(packet.obdh_status); i++)
        {
            packet.obdh_status[i] = data[packageSize++];
        }
        reset_counter     = (packet.obdh_status[0] << 16) | (packet.obdh_status[1] << 8) | packet.obdh_status[2];
        reset_cause       = packet.obdh_status[3];
        clock_fault_flags = packet.obdh_status[4];
        test_module_flags = packet.obdh_status[5];
        imu_status        = bool((test_module_flags >> 4) & 1);
        usd_status        = bool((test_module_flags >> 3) & 1);
        rush_status       = bool((test_module_flags >> 1) & 1);
        eps_status        = bool((test_module_flags >> 0) & 1);
        antenna_status    = bool((test_module_flags >> 5) & 1);
    }
    if(has_flag(flags, IMU_FLAG))
    {
        for(i = 0; i < sizeof(packet.imu); i++)
        {
            packet.imu[i] = data[packageSize++];
        }
        imu_1_accel_x = IMUAccelConv((packet.imu[0] << 8) | packet.imu[1]);
        imu_1_accel_y = IMUAccelConv((packet.imu[2] << 8) | packet.imu[3]);
        imu_1_accel_z = IMUAccelConv((packet.imu[4] << 8) | packet.imu[5]);
        imu_1_gyro_x  = IMUGyroConv((packet.imu[6] << 8) | packet.imu[7]);
        imu_1_gyro_y  = IMUGyroConv((packet.imu[8] << 8) | packet.imu[9]);
        imu_1_gyro_z  = IMUGyroConv((packet.imu[10] << 8) | packet.imu[11]);
        imu_2_accel_x = IMUAccelConv((packet.imu[12] << 8) | packet.imu[13]);
        imu_2_accel_y = IMUAccelConv((packet.imu[14] << 8) | packet.imu[15]);
        imu_2_accel_z = IMUAccelConv((packet.imu[16] << 8) | packet.imu[17]);
        // TODO: Add conversions
        imu_2_gyro_x  = ((packet.imu[18] << 8) | packet.imu[19]);
        imu_2_gyro_y  = ((packet.imu[20] << 8) | packet.imu[21]);
        imu_2_gyro_z  = ((packet.imu[22] << 8) | packet.imu[23]); // can be the angle
    }
    if(has_flag(flags, OBDH_MISC_FLAG))
    {
        for(i = 0; i < sizeof(packet.obdh_misc); i++)
        {
            packet.obdh_misc[i] = data[packageSize++];
        }
        MSP_temperature = MSPInternalTempConv((packet.obdh_misc[0] << 8) | packet.obdh_misc[1]);
        supply_voltage  = OBDHSupplyVoltConv((packet.obdh_misc[2] << 8) | packet.obdh_misc[3]);
        supply_current  = OBDHSupplyCurrentConv((packet.obdh_misc[4] << 8) | packet.obdh_misc[5]);
    }
    if(has_flag(flags, SOLAR_PANELS_SENSORS_FLAG))
    {
        for(i = 0; i < sizeof(packet.solar_panels_sensors); i++)
        {
            packet.solar_panels_sensors[i] = data[packageSize++];
        }
    }
    if(has_flag(flags, MAIN_RADIO_FLAG))
    {
        for(i = 0; i < sizeof(packet.main_radio); i++)
        {
            packet.main_radio[i] = data[packageSize++];
        }
    }

    if(has_flag(flags, SOLAR_PANELS_FLAG))
    {
        for(i = 0; i < sizeof(packet.solar_panels); i++)
        {
            packet.solar_panels[i] = data[packageSize++];
        }
        solar_current_1 = SolarPanelCurrentConv((packet.solar_panels[0] << 8) | packet.solar_panels[1]);
        solar_current_2 = SolarPanelCurrentConv((packet.solar_panels[2] << 8) | packet.solar_panels[3]);
        solar_current_3 = SolarPanelCurrentConv((packet.solar_panels[4] << 8) | packet.solar_panels[5]);
        solar_current_4 = SolarPanelCurrentConv((packet.solar_panels[6] << 8) | packet.solar_panels[7]);
        solar_current_5 = SolarPanelCurrentConv((packet.solar_panels[8] << 8) | packet.solar_panels[9]);
        solar_current_6 = SolarPanelCurrentConv((packet.solar_panels[10] << 8) | packet.solar_panels[11]);
        solar_voltage_1 = SolarPanelVoltageConv((packet.solar_panels[12] << 8) | packet.solar_panels[13]);
        solar_voltage_2 = SolarPanelVoltageConv((packet.solar_panels[14] << 8) | packet.solar_panels[15]);
        solar_voltage_3 = SolarPanelVoltageConv((packet.solar_panels[16] << 8) | packet.solar_panels[17]);
    }
    if(has_flag(flags, EPS_MISC_FLAG))
    {
        for(i = 0; i < sizeof(packet.eps_misc); i++)
        {
            packet.eps_misc[i] = data[packageSize++];
        }
        boost_voltage      = ADCVoltConv((packet.eps_misc[0] << 8) | packet.eps_misc[1]);
        main_power_voltage = ADCVoltConv((packet.eps_misc[2] << 8) | packet.eps_misc[3]);
        BEACON_EPS_current = BeaconEPSCurrentConv((packet.eps_misc[4] << 8) | packet.eps_misc[5]);
        ADC_temperature    = ADCInternalTempConv((packet.eps_misc[6] << 8) | packet.eps_misc[7]);
    }
    if(has_flag(flags, BATTERY_MONITOR_FLAG))
    {
        for(i = 0; i < sizeof(packet.battery_monitor); i++)
        {
            packet.battery_monitor[i] = data[packageSize++];
        }
        bat_average_current       = BatCurrentConv((packet.battery_monitor[0] << 8) | packet.battery_monitor[1]);
        bat_temperature           = BatMonitorTempConv((packet.battery_monitor[2] << 8) | packet.battery_monitor[3]);
        bat1_voltage              = BatVoltConv((packet.battery_monitor[4] << 8) | packet.battery_monitor[5]);
        bat2_voltage              = BatVoltConv((packet.battery_monitor[6] << 8) | packet.battery_monitor[7]);
        bat_current               = BatCurrentConv((packet.battery_monitor[8] << 8) | packet.battery_monitor[9]);
        bat_accumulated_current   = BatAccumulatedCurrentConv((packet.battery_monitor[10] << 8) | packet.battery_monitor[11]);
        protection_register       = packet.battery_monitor[12];
        status_register           = packet.battery_monitor[13];
        cycle_counter_register    = CycleCountRegisterConv(packet.battery_monitor[14]);
        active_absolute_capacity  = RemainingAbsoluteCapacityConv((packet.battery_monitor[15] << 8) | packet.battery_monitor[16]);
        standby_absolute_capacity = RemainingAbsoluteCapacityConv((packet.battery_monitor[17] << 8) | packet.battery_monitor[18]);
        active_relative_capacity  = packet.battery_monitor[19];
        standby_relative_capacity = packet.battery_monitor[20];
    }
    if(has_flag(flags, TEMPERATURES_FLAG))
    {
        for(i = 0; i < sizeof(packet.temperatures); i++)
        {
            packet.temperatures[i] = data[packageSize++];
        }
        RTD_measurement_1 = ADCConv(packet.temperatures[0] << 16 | (packet.temperatures[1] << 8) | packet.temperatures[2]);
        RTD_measurement_2 = ADCConv(packet.temperatures[3] << 16 | (packet.temperatures[4] << 8) | packet.temperatures[5]);
        RTD_measurement_3 = ADCConv(packet.temperatures[6] << 16 | (packet.temperatures[7] << 8) | packet.temperatures[8]);
        RTD_measurement_4 = ADCConv(packet.temperatures[9] << 16 | (packet.temperatures[10] << 8) | packet.temperatures[11]);
        RTD_measurement_5 = ADCConv(packet.temperatures[12] << 16 | (packet.temperatures[13] << 8) | packet.temperatures[14]);
        RTD_measurement_6 = ADCConv(packet.temperatures[15] << 16 | (packet.temperatures[16] << 8) | packet.temperatures[17]);
        RTD_measurement_7 = ADCConv(packet.temperatures[18] << 16 | (packet.temperatures[19] << 8) | packet.temperatures[20]);
    }
    if(has_flag(flags, ENERGY_LEVEL_FLAG))
    {
        for(i = 0; i < sizeof(packet.energy_level); i++)
        {
            packet.energy_level[i] = data[packageSize++];
        }
        EPS_status = packet.energy_level[0];
    }
    if(has_flag(flags, PAYLOAD1_FLAG))
    {
        for(i = 0; i < sizeof(packet.payload1); i++)
        {
            packet.payload1[i] = data[packageSize++];
        }
    }
    if(has_flag(flags, PAYLOAD2_FLAG))
    {
        for(i = 0; i < sizeof(packet.payload2); i++)
        {
            packet.payload2[i] = data[packageSize++];
        }
    }

    this->Display();
    //    this->Clear();
}

void TelemetryData::Clear()
{
    packet_flags                = 0;
    imu_status                  = false;
    usd_status                  = false;
    rush_status                 = false;
    eps_status                  = false;
    antenna_status              = false;
    reset_counter               = 0;
    reset_cause                 = 0;
    clock_fault_flags           = 0;
    test_module_flags           = 0;
    imu_1_accel_x               = 0;
    imu_1_accel_y               = 0;
    imu_1_accel_z               = 0;
    imu_1_gyro_x                = 0;
    imu_1_gyro_y                = 0;
    imu_1_gyro_z                = 0;
    imu_2_accel_x               = 0;
    imu_2_accel_y               = 0;
    imu_2_accel_z               = 0;
    imu_2_gyro_x                = 0;
    imu_2_gyro_y                = 0;
    imu_2_gyro_z                = 0;
    MSP_temperature             = 0;
    supply_voltage              = 0;
    supply_current              = 0;
    system_time_sec             = 0;
    system_time_min             = 0;
    system_time_hou             = 0;
    solar_current_1             = 0;
    solar_current_2             = 0;
    solar_current_3             = 0;
    solar_current_4             = 0;
    solar_current_5             = 0;
    solar_current_6             = 0;
    solar_voltage_1             = 0;
    solar_voltage_2             = 0;
    solar_voltage_3             = 0;
    boost_voltage               = 0;
    main_power_voltage          = 0;
    BEACON_EPS_current          = 0;
    ADC_temperature             = 0;
    bat_average_current         = 0;
    bat_temperature             = 0;
    bat1_voltage                = 0;
    bat2_voltage                = 0;
    bat_current                 = 0;
    bat_accumulated_current     = 0;
    protection_register         = 0;
    status_register             = 0;
    cycle_counter_register      = 0;
    active_absolute_capacity    = 0;
    standby_absolute_capacity   = 0;
    active_relative_capacity    = 0;
    standby_relative_capacity   = 0;
    RTD_measurement_1           = 0;
    RTD_measurement_2           = 0;
    RTD_measurement_3           = 0;
    RTD_measurement_4           = 0;
    RTD_measurement_5           = 0;
    RTD_measurement_6           = 0;
    RTD_measurement_7           = 0;
    EPS_status                  = 0;
}

std::string TelemetryData::Log()
{
    std::string log_entry = "";

    log_entry += ToString(int(packet_flags));
    log_entry += ",";
    log_entry += ToString(int(reset_counter));
    log_entry += ",";
    log_entry += ToString(int(reset_cause));
    log_entry += ",";
    log_entry += ToString(int(clock_fault_flags));
    log_entry += ",";
    log_entry += ToString(int(test_module_flags));
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
    log_entry += ToString(imu_1_accel_x);
    log_entry += ",";
    log_entry += ToString(imu_1_accel_y);
    log_entry += ",";
    log_entry += ToString(imu_1_accel_z);
    log_entry += ",";
    log_entry += ToString(imu_1_gyro_x);
    log_entry += ",";
    log_entry += ToString(imu_1_gyro_y);
    log_entry += ",";
    log_entry += ToString(imu_1_gyro_z);
    log_entry += ",";
    log_entry += ToString(imu_2_accel_x);
    log_entry += ",";
    log_entry += ToString(imu_2_accel_y);
    log_entry += ",";
    log_entry += ToString(imu_2_accel_z);
    log_entry += ",";
    log_entry += ToString(imu_2_gyro_x);
    log_entry += ",";
    log_entry += ToString(imu_2_gyro_y);
    log_entry += ",";
    log_entry += ToString(imu_2_gyro_z);
    log_entry += ",";
    log_entry += ToString(MSP_temperature);
    log_entry += ",";
    log_entry += ToString(supply_voltage);
    log_entry += ",";
    log_entry += ToString(supply_current);
    log_entry += ",";
    log_entry += ToString(int(system_time_hou));
    log_entry += ",";
    log_entry += ToString(int(system_time_min));
    log_entry += ",";
    log_entry += ToString(int(system_time_sec));
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
    log_entry += ToString(boost_voltage);
    log_entry += ",";
    log_entry += ToString(main_power_voltage);
    log_entry += ",";
    log_entry += ToString(BEACON_EPS_current);
    log_entry += ",";
    log_entry += ToString(ADC_temperature);
    log_entry += ",";
    log_entry += ToString(bat_average_current);
    log_entry += ",";
    log_entry += ToString(bat_temperature);
    log_entry += ",";
    log_entry += ToString(bat1_voltage);
    log_entry += ",";
    log_entry += ToString(bat2_voltage);
    log_entry += ",";
    log_entry += ToString(bat_current);
    log_entry += ",";
    log_entry += ToString(bat_accumulated_current);
    log_entry += ",";
    log_entry += ToString(int(protection_register));
    log_entry += ",";
    log_entry += ToString(int(status_register));
    log_entry += ",";
    log_entry += ToString(int(cycle_counter_register));
    log_entry += ",";
    log_entry += ToString(active_absolute_capacity);
    log_entry += ",";
    log_entry += ToString(standby_absolute_capacity);
    log_entry += ",";
    log_entry += ToString(active_relative_capacity);
    log_entry += ",";
    log_entry += ToString(standby_relative_capacity);
    log_entry += ",";
    log_entry += ToString(RTD_measurement_1);
    log_entry += ",";
    log_entry += ToString(RTD_measurement_2);
    log_entry += ",";
    log_entry += ToString(RTD_measurement_3);
    log_entry += ",";
    log_entry += ToString(RTD_measurement_4);
    log_entry += ",";
    log_entry += ToString(RTD_measurement_5);
    log_entry += ",";
    log_entry += ToString(RTD_measurement_6);
    log_entry += ",";
    log_entry += ToString(RTD_measurement_7);
    log_entry += ",";
    log_entry += ToString(int(EPS_status));

    return log_entry;
}

const char* TelemetryData::getLabel()
{
    return "TELEMETRY";
}

void TelemetryData::ForceDisplay(std::vector<std::string> data)
{
    while(data.size() < 57)
    {
        data.push_back(std::string("-"));
    }

    unsigned int i = 6;

    label_telemetry_data_status_reset_counter->set_text(data[i++]);
    label_telemetry_data_status_reset_cause->set_text(data[i++]);
    label_telemetry_data_status_clock->set_text(data[i++]);
    label_telemetry_data_status_imu->set_text(data[i++]);
    label_telemetry_data_status_usd->set_text(data[i++]);
    label_telemetry_data_status_rush->set_text(data[i++]);
    label_telemetry_data_status_eps->set_text(data[i++]);
    label_telemetry_data_status_antenna->set_text(data[i++]);
    label_telemetry_data_uc_temp->set_text(data[i++]);
    label_telemetry_data_uc_voltage->set_text(data[i++]);
    label_telemetry_data_uc_current->set_text(data[i++]);
    label_telemetry_data_time_system->set_text(data[i++]);
    label_telemetry_data_time_system_up->set_text(data[i++]);
    label_telemetry_data_imu_accel_x->set_text(data[i++]);
    label_telemetry_data_imu_accel_y->set_text(data[i++]);
    label_telemetry_data_imu_accel_z->set_text(data[i++]);
    label_telemetry_data_imu_gyro_x->set_text(data[i++]);
    label_telemetry_data_imu_gyro_y->set_text(data[i++]);
    label_telemetry_data_imu_gyro_z->set_text(data[i++]);
    label_telemetry_data_sp_sun_p1->set_text(data[i++]);
    label_telemetry_data_sp_sun_p2->set_text(data[i++]);
    label_telemetry_data_sp_sun_p3->set_text(data[i++]);
    label_telemetry_data_sp_temp_p1->set_text(data[i++]);
    label_telemetry_data_sp_temp_p2->set_text(data[i++]);
    label_telemetry_data_sp_temp_p3->set_text(data[i++]);
    label_telemetry_data_eps_bat_mean_i->set_text(data[i++]);
    label_telemetry_data_eps_bat_temp->set_text(data[i++]);
    label_telemetry_data_eps_bat_1_volt->set_text(data[i++]);
    label_telemetry_data_eps_bat_2_volt->set_text(data[i++]);
    label_telemetry_data_eps_bat_current->set_text(data[i++]);
    label_telemetry_data_eps_bat_charge->set_text(data[i++]);
    label_telemetry_data_eps_bat_protection->set_text(data[i++]);
    label_telemetry_data_eps_bat_status->set_text(data[i++]);
    label_telemetry_data_eps_bat_cycles->set_text(data[i++]);
    label_telemetry_data_eps_bat_raac->set_text(data[i++]);
    label_telemetry_data_eps_bat_rsac->set_text(data[i++]);
    label_telemetry_data_eps_bat_rarc->set_text(data[i++]);
    label_telemetry_data_eps_bat_rsrc->set_text(data[i++]);
    label_telemetry_data_eps_sp_i_my->set_text(data[i++]);
    label_telemetry_data_eps_sp_i_px->set_text(data[i++]);
    label_telemetry_data_eps_sp_i_mx->set_text(data[i++]);
    label_telemetry_data_eps_sp_i_pz->set_text(data[i++]);
    label_telemetry_data_eps_sp_i_mz->set_text(data[i++]);
    label_telemetry_data_eps_sp_i_py->set_text(data[i++]);
    label_telemetry_data_eps_sp_v_mypx->set_text(data[i++]);
    label_telemetry_data_eps_sp_v_mxpz->set_text(data[i++]);
    label_telemetry_data_eps_sp_v_mzpy->set_text(data[i++]);
    label_telemetry_data_eps_misc_boost_v->set_text(data[i++]);
    label_telemetry_data_eps_misc_main_bus_v->set_text(data[i++]);
    label_telemetry_data_eps_misc_beacon_i->set_text(data[i++]);
    label_telemetry_data_eps_misc_uc_temp->set_text(data[i++]);
    label_telemetry_data_eps_misc_energy_level->set_text(data[i++]);
}

double TelemetryData::BatVoltConv(uint16_t val)
{
    return (int16_t(val)/32)*4.883e-3;
}

double TelemetryData::ADCConv(uint32_t val)
{
    return ((val*(1.65*2/pow(2, 24))*1e3)-1000)*1/3.85;
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

double TelemetryData::MSPInternalTempConv(uint16_t val)
{
    return ((val * 2.0 - 2048.0) * 55.0) / (2432.0 - 2048.0) + 30.0;        // CAL1 = 2145 and CAL2 = 2508 for the OBDH MSP (F6659)
}

double TelemetryData::OBDHSupplyVoltConv(uint16_t val)
{
    return (val * 2 * 3.0) / 4095.0;
}

double TelemetryData::OBDHSupplyCurrentConv(uint16_t val)
{
    return (1000 * val * 3.0) / (4095 * 0.05 * 0.025 * 20000);
}

double TelemetryData::ADCVoltConv(uint16_t val)
{
    return val * (2.5 / 4095.0) * (300e3 + 100e3) / (100e3);
}

double TelemetryData::BeaconEPSCurrentConv(uint16_t val)
{
    return val * (2.5 / 4095.0)  * (1.0 /( 0.075 * 0.025 * 4020));
}

double TelemetryData::ADCInternalTempConv(uint16_t val)
{
    return (val * (2.5 / 4095.0)  - 0.680) * 70.0 / 0.170;
}

double TelemetryData::BatCurrentConv(uint16_t val)
{
    return int16_t(val) * (1.5625e-6 / 0.01);
}

double TelemetryData::BatAccumulatedCurrentConv(uint16_t val)
{
    return uint16_t(val) * (6.25e-6 / 0.01);
}

double TelemetryData::BatMonitorTempConv(uint16_t val)
{
    return int16_t(val) * 0.125 / 32.0;
}

double TelemetryData::CycleCountRegisterConv(uint16_t val)
{
    return val * 2;
}

double TelemetryData::RemainingAbsoluteCapacityConv(uint16_t val)
{
    return val * 1.6;
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

const char* TelemetryData::PrintIMUs(double imu_1, double imu_2, unsigned int digits)
{
    std::stringstream input_str;

    input_str << std::fixed << std::setprecision(digits) << imu_1;
    input_str << "/";
    input_str << std::fixed << std::setprecision(digits) << imu_2;

    std::string output = input_str.str();

    return output.c_str();
}

//! \} End of telemetry_data
