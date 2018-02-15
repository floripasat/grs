/*
 * beacon_data.h
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
 * \file beacon_data.h
 * 
 * \brief Beacon data class.
 * 
 * \author Gabriel Mariano Marcelino <gabriel.mm8@gmail.com>
 * 
 * \version 1.0-dev
 * 
 * \date 12/09/2017
 * 
 * \defgroup beacon_data Beacon Data
 * \ingroup fsat_grs
 * \{
 */

#ifndef BEACON_DATA_H_
#define BEACON_DATA_H_

#include <gtkmm.h>
#include <vector>
#include <stdint.h>
#include <string>

#include "packet_data.h"

#define BEACON_DATA_SAT_ID_PKT              0
#define BEACON_DATA_EPS_PKT                 1
#define BEACON_DATA_OBDH_PKT                2

#define BEACON_DATA_UNKNOWN_VALUE           "-"

#define BEACON_DATA_MSB_FIRST               0
#define BEACON_DATA_LSB_FIRST               1

#define BEACON_DATA_ENDIENESS               BEACON_DATA_MSB_FIRST

/**
 * \class BeaconData
 * 
 * \brief 
 */
class BeaconData: public PacketData
{
    private:
        Gtk::Label *label_beacon_data_bat1_v_value;
        Gtk::Label *label_beacon_data_bat2_v_value;
        Gtk::Label *label_beacon_data_bat1_t_value;
        Gtk::Label *label_beacon_data_bat2_t_value;
        Gtk::Label *label_beacon_data_bat_c_value;
        Gtk::Label *label_beacon_data_sp_i_my;
        Gtk::Label *label_beacon_data_sp_i_px;
        Gtk::Label *label_beacon_data_sp_i_mx;
        Gtk::Label *label_beacon_data_sp_i_pz;
        Gtk::Label *label_beacon_data_sp_i_mz;
        Gtk::Label *label_beacon_data_sp_i_py;
        Gtk::Label *label_beacon_data_sp_v_mypx;
        Gtk::Label *label_beacon_data_sp_v_mxpz;
        Gtk::Label *label_beacon_data_sp_v_mzpy;
        Gtk::Label *label_beacon_data_status_energy_level;
        Gtk::Label *label_beacon_data_status_imu;
        Gtk::Label *label_beacon_data_status_usd;
        Gtk::Label *label_beacon_data_status_rush;
        Gtk::Label *label_beacon_data_status_eps;
        Gtk::Label *label_beacon_data_status_antenna;
        Gtk::Label *label_beacon_data_imu_accel_x;
        Gtk::Label *label_beacon_data_imu_accel_y;
        Gtk::Label *label_beacon_data_imu_accel_z;
        Gtk::Label *label_beacon_data_imu_gyro_x;
        Gtk::Label *label_beacon_data_imu_gyro_y;
        Gtk::Label *label_beacon_data_imu_gyro_z;
        Gtk::Label *label_beacon_data_obdh_rst_value;
        Gtk::Label *label_beacon_data_system_time_value;
        
        double bat1_voltage;
        double bat2_voltage;
        double bat1_temp;
        double bat2_temp;
        double bat_charge;
        double solar_current_1;
        double solar_current_2;
        double solar_current_3;
        double solar_current_4;
        double solar_current_5;
        double solar_current_6;
        double solar_voltage_1;
        double solar_voltage_2;
        double solar_voltage_3;
        double imu_accel_x;
        double imu_accel_y;
        double imu_accel_z;
        double imu_gyro_x;
        double imu_gyro_y;
        double imu_gyro_z;
        uint8_t system_time_sec;
        uint8_t system_time_min;
        uint8_t system_time_hou;
        uint16_t obdh_resets;
        uint8_t energy_level;
        bool imu_status;
        bool usd_status;
        bool rush_status;
        bool eps_status;
        bool antenna_status;
        /**
         * \brief 
         */
        uint8_t type_last_pkt;
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
         * \param 
         * 
         * \return 
         */
        double BatTempConv(uint32_t val);
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
         * \param h
         * \param m
         * \param s
         * 
         * \return 
         */
        const char* PrintTime(uint8_t h, uint8_t m, uint8_t s);
    public:
        /**
         * \brief 
         * 
         * \return None
         */
        BeaconData();
        /**
         * \brief 
         * 
         * \param lbs
         * 
         * \return None
         */
        BeaconData(std::vector<Gtk::Label *> lbs);
        /**
         * \brief 
         * 
         * \param pkt_type
         * 
         * \return None
         */
        void Display(uint8_t pkt_type=0);
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
         * \return None
         */
        const char* getLabel();
        /**
         * \brief Forces the data to display into the beacon panel.
         *
         * \param data is a vector of strings with the data to display in the beacon panel.
         *
         * \return None
         */
        void ForceDisplay(std::vector<std::string> data);
};

#endif // BEACON_DATA_H_

//! \} End of beacon_data group
