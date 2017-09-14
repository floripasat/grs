/*
 * beacon_data.h
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
 * \file beacon_data.h
 * 
 * \brief .
 * 
 * \author Gabriel Mariano Marcelino <gabriel.mm8@gmail.com>
 * 
 * \version 1.2
 * 
 * \date 12/09/2017
 * 
 * \defgroup beacon_data Beacon Data
 * \{
 */

#ifndef BEACON_DATA_H_
#define BEACON_DATA_H_

#include <gtkmm.h>
#include <stdint.h>

#define BEACON_DATA_SAT_ID_PKT          0
#define BEACON_DATA_EPS_PKT             1
#define BEACON_DATA_OBDH_PKT            2

#define BEACON_DATA_UNKNOWN_VALUE       "-"

/**
 * \class BeaconData
 * 
 * \brief 
 */
class BeaconData
{
    private:
        Gtk::Label      *label_bat1_v;      /**< . */
        Gtk::Label      *label_bat2_v;      /**< . */
        Gtk::Label      *label_bat1_t;      /**< . */
        Gtk::Label      *label_bat2_t;      /**< . */
        Gtk::Label      *label_bat_c;       /**< . */
        Gtk::Label      *label_solar_i_1;   /**< . */
        Gtk::Label      *label_solar_i_2;   /**< . */
        Gtk::Label      *label_solar_v;     /**< . */
        Gtk::Label      *label_status;      /**< . */
        Gtk::Label      *label_imu_data1;   /**< . */
        Gtk::Label      *label_imu_data2;   /**< . */
        Gtk::Label      *label_system_time; /**< . */
        Gtk::Label      *label_obdh_rst;    /**< . */
        
        double bat1_voltage;                /**< . */
        double bat2_voltage;                /**< . */
        double bat1_temp;                   /**< . */
        double bat2_temp;                   /**< . */
        double bat_charge;                  /**< . */
        double solar_current_1;             /**< . */
        double solar_current_2;             /**< . */
        double solar_current_3;             /**< . */
        double solar_current_4;             /**< . */
        double solar_current_5;             /**< . */
        double solar_current_6;             /**< . */
        double solar_voltage_1;             /**< . */
        double solar_voltage_2;             /**< . */
        double solar_voltage_3;             /**< . */
        double imu_accel_x;                 /**< . */
        double imu_accel_y;                 /**< . */
        double imu_accel_z;                 /**< . */
        double imu_gyro_x;                  /**< . */
        double imu_gyro_y;                  /**< . */
        double imu_gyro_z;                  /**< . */
        uint32_t system_time_sec;           /**< . */
        uint16_t obdh_resets;               /**< . */
        
        uint8_t type_last_pkt;              /**< . */
        
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
         * \param bat1_v
         * \param bat2_v
         * \param bat1_t
         * \param bat2_t
         * \param bat_c
         * \param solar_i_1
         * \param solar_i_2
         * \param solar_v
         * \param status
         * \param imu_data1
         * \param imu_data2
         * \param system_time
         * \param obdh_rst
         * 
         * \return None
         */
        BeaconData(Gtk::Label *bat1_v, Gtk::Label *bat2_v, Gtk::Label *bat1_t,
                   Gtk::Label *bat2_t, Gtk::Label *bat_c, Gtk::Label *solar_i_1,
                   Gtk::Label *solar_i_2, Gtk::Label *solar_v, Gtk::Label *status,
                   Gtk::Label *imu_data1, Gtk::Label *imu_data2, Gtk::Label *system_time,
                   Gtk::Label *obdh_rst);
        /**
         * \brief 
         * 
         * \return None
         */
        ~BeaconData();
        /**
         * \brief 
         * 
         * \param pkt_type
         * 
         * \return None
         */
        void Display(uint8_t pkt_type);
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
        const char* Log();
};

#endif // BEACON_DATA_H_

//! \} End of beacon_data group
