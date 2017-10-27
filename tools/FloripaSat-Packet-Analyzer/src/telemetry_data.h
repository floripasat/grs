/*
 * telemetry_data.h
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
 * \file telemetry_data.h
 * 
 * \brief Telemetry data class.
 * 
 * \author Gabriel Mariano Marcelino <gabriel.mm8@gmail.com>
 * 
 * \version 2.0
 * 
 * \date 08/10/2017
 * 
 * \defgroup telemetry_data Telemetry Data
 * \{
 */

#ifndef TELEMETRY_DATA_H_
#define TELEMETRY_DATA_H_

#include <gtkmm.h>
#include <vector>
#include <stdint.h>
#include <string>

#include "packet_data.h"

#define TELEMETRY_DATA_UNKNOWN_VALUE    "-"

/**
 * \class TelemetryData
 * 
 * \brief 
 */
class TelemetryData: public PacketData
{
    private:
        Gtk::Label *label_telemetry_data_status_reset_counter;
        Gtk::Label *label_telemetry_data_status_reset_cause;
        Gtk::Label *label_telemetry_data_status_clock;
        Gtk::Label *label_telemetry_data_status_imu;
        Gtk::Label *label_telemetry_data_status_usd;
        Gtk::Label *label_telemetry_data_status_rush;
        Gtk::Label *label_telemetry_data_status_eps;
        Gtk::Label *label_telemetry_data_status_antenna;
        Gtk::Label *label_telemetry_data_uc_temp;
        Gtk::Label *label_telemetry_data_uc_voltage;
        Gtk::Label *label_telemetry_data_uc_current;
        Gtk::Label *label_telemetry_data_time_system;
        Gtk::Label *label_telemetry_data_time_system_up;
        Gtk::Label *label_telemetry_data_imu_accel_x;
        Gtk::Label *label_telemetry_data_imu_accel_y;
        Gtk::Label *label_telemetry_data_imu_accel_z;
        Gtk::Label *label_telemetry_data_imu_gyro_x;
        Gtk::Label *label_telemetry_data_imu_gyro_y;
        Gtk::Label *label_telemetry_data_imu_gyro_z;
        Gtk::Label *label_telemetry_data_sp_sun_p1;
        Gtk::Label *label_telemetry_data_sp_sun_p2;
        Gtk::Label *label_telemetry_data_sp_sun_p3;
        Gtk::Label *label_telemetry_data_sp_temp_p1;
        Gtk::Label *label_telemetry_data_sp_temp_p2;
        Gtk::Label *label_telemetry_data_sp_temp_p3;
        Gtk::Label *label_telemetry_data_eps_bat_mean_i;
        Gtk::Label *label_telemetry_data_eps_bat_temp;
        Gtk::Label *label_telemetry_data_eps_bat_1_volt;
        Gtk::Label *label_telemetry_data_eps_bat_2_volt;
        Gtk::Label *label_telemetry_data_eps_bat_current;
        Gtk::Label *label_telemetry_data_eps_bat_charge;
        Gtk::Label *label_telemetry_data_eps_bat_protection;
        Gtk::Label *label_telemetry_data_eps_bat_status;
        Gtk::Label *label_telemetry_data_eps_bat_cycles;
        Gtk::Label *label_telemetry_data_eps_bat_raac;
        Gtk::Label *label_telemetry_data_eps_bat_rsac;
        Gtk::Label *label_telemetry_data_eps_bat_rarc;
        Gtk::Label *label_telemetry_data_eps_bat_rsrc;
        Gtk::Label *label_telemetry_data_eps_sp_i_my;
        Gtk::Label *label_telemetry_data_eps_sp_i_px;
        Gtk::Label *label_telemetry_data_eps_sp_i_mx;
        Gtk::Label *label_telemetry_data_eps_sp_i_pz;
        Gtk::Label *label_telemetry_data_eps_sp_i_mz;
        Gtk::Label *label_telemetry_data_eps_sp_i_py;
        Gtk::Label *label_telemetry_data_eps_sp_v_mypx;
        Gtk::Label *label_telemetry_data_eps_sp_v_mxpz;
        Gtk::Label *label_telemetry_data_eps_sp_v_mzpy;
        Gtk::Label *label_telemetry_data_eps_misc_boost_v;
        Gtk::Label *label_telemetry_data_eps_misc_main_bus_v;
        Gtk::Label *label_telemetry_data_eps_misc_beacon_i;
        Gtk::Label *label_telemetry_data_eps_misc_uc_temp;
        Gtk::Label *label_telemetry_data_eps_misc_energy_level;
        
        // Packet Flags
        uint16_t packet_flags;
        
        // OBDH Status
        uint32_t reset_counter;
        uint8_t reset_cause;
        uint8_t clock_fault_flags;
        uint8_t test_module_flags;
        bool imu_status;
        bool usd_status;
        bool rush_status;
        bool eps_status;
        bool antenna_status;

        // IMU data
        double imu_1_accel_x;
        double imu_1_accel_y;
        double imu_1_accel_z;
        double imu_1_gyro_x;
        double imu_1_gyro_y;
        double imu_1_gyro_z;
        double imu_2_accel_x;
        double imu_2_accel_y;
        double imu_2_accel_z;
        double imu_2_gyro_x;
        double imu_2_gyro_y;
        double imu_2_gyro_z;

        // OBDH Misc
        double MSP_temperature;
        double supply_voltage;
        double supply_current;

        // OBDH Time
        uint8_t system_time_sec;
        uint8_t system_time_min;
        uint16_t system_time_hou;

        // Solar Panels
        double solar_current_1;
        double solar_current_2;
        double solar_current_3;
        double solar_current_4;
        double solar_current_5;
        double solar_current_6;
        double solar_voltage_1;
        double solar_voltage_2;
        double solar_voltage_3;
        
        // EPS Misc
        double boost_voltage;
        double main_power_voltage;
        double BEACON_EPS_current;
        double ADC_temperature;

        // Battery Monitor
        double bat_average_current;
        double bat_temperature;
        double bat1_voltage;
        double bat2_voltage;
        double bat_current;
        double bat_accumulated_current;
        uint8_t protection_register;
        uint8_t status_register;
        uint16_t cycle_counter_register;
        double active_absolute_capacity;
        double standby_absolute_capacity;
        double active_relative_capacity;
        double standby_relative_capacity;

        // Temperatures
        double RTD_measurement_1;
        double RTD_measurement_2;
        double RTD_measurement_3;
        double RTD_measurement_4;
        double RTD_measurement_5;
        double RTD_measurement_6;
        double RTD_measurement_7;

        // Task Scheduler
        uint8_t EPS_status;
        
        // Data convertion functions
        /**
         * \brief 
         * 
         * \param val
         * 
         * \return 
         */
        double BatVoltConv(uint16_t val);
        /**
         * \brief 
         * 
         * \param val
         * 
         * \return 
         */
        double ADCConv(uint32_t val);
        /**
         * \brief 
         * 
         * \param val
         * 
         * \return 
         */
        double BatChargeConv(uint16_t val);
        /**
         * \brief 
         * 
         * \param val
         * 
         * \return 
         */
        double SolarPanelCurrentConv(uint16_t val);
        /**
         * \brief 
         * 
         * \param val
         * 
         * \return 
         */
        double SolarPanelVoltageConv(uint16_t val);
        /**
         * \brief 
         * 
         * \param val
         * 
         * \return 
         */
        double IMUAccelConv(uint16_t val);
        /**
         * \brief 
         * 
         * \param val
         * 
         * \return 
         */
        double IMUGyroConv(uint16_t val);
        /**
         * \brief 
         * 
         * \param val
         * 
         * \return 
         */
        double MSPInternalTempConv(uint16_t val);
        /**
         * \brief 
         * 
         * \param val
         * 
         * \return 
         */
        double OBDHSupplyVoltConv(uint16_t val);
        /**
         * \brief 
         * 
         * \param val
         * 
         * \return 
         */
        double OBDHSupplyCurrentConv(uint16_t val);
        /**
         * \brief 
         * 
         * \param val
         * 
         * \return 
         */
        double ADCVoltConv(uint16_t val);
        /**
         * \brief 
         * 
         * \param val
         * 
         * \return 
         */
        double BeaconEPSCurrentConv(uint16_t val);
        /**
         * \brief 
         * 
         * \param val
         * 
         * \return 
         */
        double ADCInternalTempConv(uint16_t val);
        /**
         * \brief 
         * 
         * \param val
         * 
         * \return 
         */
        double BatCurrentConv(uint16_t val);
        /**
         * \brief 
         * 
         * \param val
         * 
         * \return 
         */
        double BatAccumulatedCurrentConv(uint16_t val);
        /**
         * \brief 
         * 
         * \param val
         * 
         * \return 
         */
        double BatMonitorTempConv(uint16_t val);
        /**
         * \brief 
         * 
         * \param val
         * 
         * \return 
         */
        double CycleCountRegisterConv(uint16_t val);
        /**
         * \brief 
         * 
         * \param val
         * 
         * \return 
         */
        double RemainingAbsoluteCapacityConv(uint16_t val);
        /**
         * \brief 
         * 
         * \param h is the hour
         * \param m is the minute
         * \param s is the second
         * 
         * \return 
         */
        const char* PrintTime(uint8_t h, uint8_t m, uint8_t s);
        /**
         * \brief 
         * 
         * \param imu_1
         * \param imu_2
         * \param digits
         * 
         * \return 
         */
        const char* PrintIMUs(double imu_1, double imu_2, unsigned int digits=4);
    public:
        /**
         * \brief 
         * 
         * \return None
         */
        TelemetryData();
        /**
         * \brief 
         * 
         * \param lbs
         * 
         * \return None
         */
        TelemetryData(std::vector<Gtk::Label *> lbs);
        /**
         * \brief 
         * 
         * \param no_data 
         * 
         * \return None
         */
        void Display(bool no_data=false);
        /**
         * \brief 
         * 
         * \param data
         * \param len
         * 
         * \return None
         */
        void Update(uint8_t *data, uint8_t len);
        /**
         * \brief 
         * 
         * \return None
         */
        void Clear();
        /**
         * \brief 
         * 
         * \return 
         */
        std::string Log();
        /**
         * \brief 
         * 
         * \return 
         */
        const char* getLabel();
};

#endif // TELEMTRY_DATA_H_

//! \} End of telemetry_data group
