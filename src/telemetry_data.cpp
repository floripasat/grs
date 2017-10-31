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
    if (len > 140)
    {
        packet_flags                = (data[0] << 8) | data[1];
        reset_counter               = (data[4] << 16) | (data[3] << 8) | data[2];
        reset_cause                 = data[5];
        clock_fault_flags           = data[6];
        test_module_flags           = data[7];
        imu_status                  = bool((data[7] >> 4) & 1);
        usd_status                  = bool((data[7] >> 3) & 1);
        rush_status                 = bool((data[7] >> 1) & 1);
        eps_status                  = bool((data[7] >> 0) & 1);
        antenna_status              = bool((data[7] >> 5) & 1);
        imu_1_accel_x               = IMUAccelConv((data[8] << 8) | data[9]);
        imu_1_accel_y               = IMUAccelConv((data[10] << 8) | data[11]);
        imu_1_accel_z               = IMUAccelConv((data[12] << 8) | data[13]);
        imu_1_gyro_x                = IMUGyroConv((data[14] << 8) | data[15]);
        imu_1_gyro_y                = IMUGyroConv((data[16] << 8) | data[17]);
        imu_1_gyro_z                = IMUGyroConv((data[18] << 8) | data[19]);
        imu_2_accel_x               = IMUAccelConv((data[20] << 8) | data[21]);
        imu_2_accel_y               = IMUAccelConv((data[22] << 8) | data[23]);
        imu_2_accel_z               = IMUAccelConv((data[24] << 8) | data[25]);
        imu_2_gyro_x                = IMUGyroConv((data[26] << 8) | data[27]);
        imu_2_gyro_y                = IMUGyroConv((data[28] << 8) | data[29]);
        imu_2_gyro_z                = IMUGyroConv((data[30] << 8) | data[31]);
        MSP_temperature             = MSPInternalTempConv((data[32] << 8) | data[33]);
        supply_voltage              = OBDHSupplyVoltConv((data[34] << 8) | data[35]);
        supply_current              = OBDHSupplyCurrentConv((data[36] << 8) | data[37]);
        system_time_sec             = data[38];
        system_time_min             = (data[39] | (data[40] << 8) | (data[41] << 16))%60;
        system_time_hou             = (data[39] | (data[40] << 8) | (data[41] << 16))/60;            
        solar_current_1             = SolarPanelCurrentConv((data[140] << 8) | data[139]);
        solar_current_2             = SolarPanelCurrentConv((data[142] << 8) | data[141]);
        solar_current_3             = SolarPanelCurrentConv((data[144] << 8) | data[143]);
        solar_current_4             = SolarPanelCurrentConv((data[146] << 8) | data[145]);
        solar_current_5             = SolarPanelCurrentConv((data[148] << 8) | data[147]);
        solar_current_6             = SolarPanelCurrentConv((data[150] << 8) | data[149]);
        solar_voltage_1             = SolarPanelVoltageConv((data[152] << 8) | data[151]);
        solar_voltage_2             = SolarPanelVoltageConv((data[154] << 8) | data[153]);
        solar_voltage_3             = SolarPanelVoltageConv((data[156] << 8) | data[155]);
        boost_voltage               = ADCVoltConv((data[158] << 8) | data[157]);
        main_power_voltage          = ADCVoltConv((data[160] << 8) | data[159]);
        BEACON_EPS_current          = BeaconEPSCurrentConv((data[162] << 8) | data[161]);
        ADC_temperature             = ADCInternalTempConv((data[164] << 8) | data[163]);
        bat_average_current         = BatCurrentConv((data[166] << 8) | data[165]);
        bat_temperature             = BatMonitorTempConv((data[168] << 8) | data[167]);
        bat1_voltage                = BatVoltConv((data[170] << 8) | data[169]);
        bat2_voltage                = BatVoltConv((data[172] << 8) | data[171]);
        bat_current                 = BatCurrentConv((data[174] << 8) | data[173]);
        bat_accumulated_current     = BatAccumulatedCurrentConv((data[176] << 8) | data[175]);
        protection_register         = data[177];
        status_register             = data[178];
        cycle_counter_register      = CycleCountRegisterConv(data[179]);
        active_absolute_capacity    = RemainingAbsoluteCapacityConv((data[181] << 8) | data[180]);
        standby_absolute_capacity   = RemainingAbsoluteCapacityConv((data[183] << 8) | data[182]);
        active_relative_capacity    = data[184];
        standby_relative_capacity   = data[185];
        RTD_measurement_1           = ADCConv(data[188] << 16 | (data[187] << 8) | data[186]);
        RTD_measurement_2           = ADCConv(data[191] << 16 | (data[190] << 8) | data[189]);
        RTD_measurement_3           = ADCConv(data[194] << 16 | (data[193] << 8) | data[192]);
        RTD_measurement_4           = ADCConv(data[197] << 16 | (data[196] << 8) | data[195]);
        RTD_measurement_5           = ADCConv(data[200] << 16 | (data[199] << 8) | data[198]);
        RTD_measurement_6           = ADCConv(data[203] << 16 | (data[202] << 8) | data[201]);
        RTD_measurement_7           = ADCConv(data[206] << 16 | (data[205] << 8) | data[204]);
        EPS_status                  = data[207];
        
        this->Display();
    }
    else
    {
        this->Clear();
    }
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
    return int16_t(val) * (6.25e-6 / 0.01);
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
