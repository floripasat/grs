/*
 * fsat-pkt-ana.h
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
 * \file fsat-pkt-ana.h
 * 
 * \brief .
 * 
 * \author Gabriel Mariano Marcelino <gabriel.mm8@gmail.com>
 * 
 * \version 1.2
 * 
 * \date 10/09/2017
 * 
 * \defgroup fsat_pkt_ana FloripaSat Packet Analyzer
 * \{
 */

#ifndef FSAT_PKT_ANA_H_
#define FSAT_PKT_ANA_H_

#include <gtkmm.h>
#include <vector>
#include <stdint.h>

#include "uart.h"
#include "event_log.h"
#include "log.h"
#include "protocol_statistic.h"
#include "beacon_data.h"
#include "ngham_pkts.h"

#define FSAT_PKT_ANA_DEFAULT_UI_FILE    "glade/MainWindow.glade"

#define DATA_RECEPTION_SAMPLE_RATE      1000

/**
 * \class FSatPktAna
 * 
 * \brief 
 */
class FSatPktAna
{
        // Main window
        Gtk::Window                     *main_window;
        
        // Toolbar
        Gtk::ToolButton                 *toolbutton_open_log_file;
        Gtk::ToolButton                 *toolbutton_config;
        Gtk::ToolButton                 *toolbutton_statistics;
        Gtk::ToolButton                 *toolbutton_gnuradio;
        Gtk::ToolButton                 *toolbutton_about;
        
        // Beacon stream
        Gtk::FileChooserButton          *filechooserbutton_beacon;
        Gtk::ToggleButton               *togglebutton_play_beacon;
        Gtk::ToggleButton               *togglebutton_pause_beacon;
        Gtk::Button                     *button_stop_beacon;
        Gtk::Button                     *button_clear_all_beacon;
        
        // Telemetry stream
        Gtk::FileChooserButton          *filechooserbutton_telemetry;
        Gtk::ToggleButton               *togglebutton_play_telemetry;
        Gtk::ToggleButton               *togglebutton_pause_telemetry;
        Gtk::Button                     *button_stop_telemetry;
        Gtk::Button                     *button_clear_all_telemetry;
        
        // Log
        Gtk::CheckButton                *checkbutton_log_ngham_packets;
        Gtk::CheckButton                *checkbutton_log_ax25_packets;
        Gtk::CheckButton                *checkbutton_log_beacon_data;
        Gtk::CheckButton                *checkbutton_log_telemetry_data;
        
        // Serial Port
        Gtk::Entry                      *entry_serial_port;
        Gtk::ComboBox                   *combobox_baudrate;
        Gtk::ToggleButton               *togglebutton_open_close_port;
        
        // Event log
        Gtk::TextView                   *textview_event_log;
        
        // NGHam Preamble
        Gtk::Entry                      *entry_ngham_config_preamble_byte;
        Gtk::Entry                      *entry_ngham_config_preamble_quant;
        
        // NGHam Sync. Bytes
        Gtk::Entry                      *entry_ngham_sync_bytes_s0;
        Gtk::Entry                      *entry_ngham_sync_bytes_s1;
        Gtk::Entry                      *entry_ngham_sync_bytes_s2;
        Gtk::Entry                      *entry_ngham_sync_bytes_s3;
        
        // AX25 Preamble
        Gtk::Entry                      *entry_ax25_config_preamble_byte;
        Gtk::Entry                      *entry_ax25_config_preamble_quant;
        
        // AX25 Sync. Bytes
        Gtk::Entry                      *entry_ax25_sync_bytes_s0;
        Gtk::Entry                      *entry_ax25_sync_bytes_s1;
        Gtk::Entry                      *entry_ax25_sync_bytes_s2;
        Gtk::Entry                      *entry_ax25_sync_bytes_s3;
        
        // NGHam Statistics
        Gtk::Label                      *label_ngham_valid_value;
        Gtk::Label                      *label_ngham_invalid_value;
        Gtk::Label                      *label_ngham_total_value;
        Gtk::Label                      *label_ngham_lost_value;
        
        // AX25 Statistics
        Gtk::Label                      *label_ax25_valid_value;
        Gtk::Label                      *label_ax25_invalid_value;
        Gtk::Label                      *label_ax25_total_value;
        Gtk::Label                      *label_ax25_lost_value;
        
        // Beacon Data
        Gtk::Label                      *label_beacon_data_bat1_v_value;
        Gtk::Label                      *label_beacon_data_bat2_v_value;
        Gtk::Label                      *label_beacon_data_bat1_t_value;
        Gtk::Label                      *label_beacon_data_bat2_t_value;
        Gtk::Label                      *label_beacon_data_bat_c_value;
        Gtk::Label                      *label_beacon_data_solar_panel_i_value1;
        Gtk::Label                      *label_beacon_data_solar_panel_i_value2;
        Gtk::Label                      *label_beacon_data_solar_panel_v_value;
        Gtk::Label                      *label_beacon_data_sat_status_value;
        Gtk::Label                      *label_beacon_data_imu_data_value1;
        Gtk::Label                      *label_beacon_data_imu_data_value2;
        Gtk::Label                      *label_beacon_data_system_time_value;
        Gtk::Label                      *label_beacon_data_obdh_rst_value;
        
        // Preferences window
        Gtk::Window                     *window_config;
        
        // About Dialog
        Gtk::AboutDialog                *aboutdialog;
        
        // Message Dialog
        Gtk::MessageDialog              *msg_dialog;
        
        UART                            *uart;                  /**< . */
        EventLog                        *event_log;             /**< . */
        //Log                             *log_ax25_pkts;         /**< . */
        Log                             *log_beacon_data;       /**< . */
        Log                             *log_telemetry_data;    /**< . */
        ProtocolStatistic               *ngham_statistic;       /**< . */
        ProtocolStatistic               *ax25_statistic;        /**< . */
        //BeaconData                      *beacon_data;           /**< . */
        PacketData                      *beacon_data;           /**< . */
        //TelemetryData                   *telemetry_data;        /**< . */
        PacketData                      *telemetry_data;        /**< . */
        
        NGHamPkts                       *ngham_pkts_beacon;     /**< . */
        NGHamPkts                       *ngham_pkts_telemetry;  /**< . */
        //AX25Pkts                        *ax25_pkts_beacon;
        
        /**
         * \brief 
         * 
         * \return None
         */
        void OnToggleButtonOpenClosePortToggled();
        /**
         * \brief 
         * 
         * \return
         */
        bool Timer();
        /**
         * \brief 
         * 
         * \return 
         */
        void OnToolButtonOpenClicked();
        /**
         * \brief 
         * 
         * \return None
         */
        void OnToolButtonConfigClicked();
        /**
         * \brief 
         * 
         * \return None
         */
        void OnToolButtonStatisticsClicked();
        /**
         * \brief 
         * 
         * \return None
         */
        void OnToolButtonRunClicked();
        /**
         * \brief 
         * 
         * \return None
         */
        void OnToolButtonAboutClicked();
        /**
         * \brief 
         * 
         * \return None
         */
        void OnToggleButtonPlayBeaconToggled();
        /**
         * \brief 
         * 
         * \return None
         */
        void OnToggleButtonPauseBeaconToggled();
        /**
         * \brief 
         * 
         * \return None
         */
        void OnButtonStopBeaconClicked();
        /**
         * \brief 
         * 
         * \return None
         */
        void OnButtonClearAllBeaconClicked();
        /**
         * \brief 
         * 
         * \return None
         */
        void OnToggleButtonPlayTelemetryToggled();
        /**
         * \brief 
         * 
         * \return None
         */
        void OnToggleButtonPauseTelemetryToggled();
        /**
         * \brief 
         * 
         * \return None
         */
        void OnButtonStopTelemetryClicked();
        /**
         * \brief 
         * 
         * \return None
         */
        void OnButtonClearAllTelemetryClicked();
        /**
         * \brief 
         * 
         * \return None
         */
        void OpenLogFiles();
        /**
         * \brief 
         * 
         * \return None
         */
        void CloseLogFiles();
        /**
         * \brief 
         * 
         * \return None
         */
        void RaiseErrorMessage(const char* error_title, const char* error_text);
        /**
         * \brief 
         * 
         * \return None
         */
        void RunGNURadioReceiver();
    public:
        /**
         * \brief 
         * 
         * \return None
         */
        FSatPktAna();
        /**
         * \brief 
         * 
         * \param ref_builder
         * \param ui_file
         * 
         * \return None
         */
        FSatPktAna(Glib::RefPtr<Gtk::Builder> ref_builder, const char *ui_file);
        /**
         * \brief 
         * 
         * \return None
         */
        ~FSatPktAna();
        /**
         * \brief 
         * 
         * \param ref_builder
         * \param ui_file
         * 
         * \return Status code.
         */
        int BuildWidgets(Glib::RefPtr<Gtk::Builder> ref_builder, const char *ui_file);
        /**
         * \brief 
         * 
         * \param app
         * 
         * \return 
         */
        int Run(Glib::RefPtr<Gtk::Application> app);
        /**
         * \brief 
         * 
         * \param byte
         * 
         * \return 
         */
        std::vector<uint8_t> ProccessByte(uint8_t byte);
};

#endif // FSAT_PKT_ANA_H_

//! \} End of fsat_pkt_ana group
