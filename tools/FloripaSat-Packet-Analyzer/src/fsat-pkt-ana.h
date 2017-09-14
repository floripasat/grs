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
#include "log.h"
#include "protocol_statistic.h"
#include "beacon_data.h"

#define FSAT_PKT_ANA_DEFAULT_UI_FILE    "glade/MainWindow.glade"

#define DATA_RECEPTION_SAMPLE_RATE      1000

/**
 * \class FSatPktAna
 * 
 * \brief 
 */
class FSatPktAna
{
        Gtk::Window                     *main_window;

        // Serial Port
        Gtk::Entry                      *entry_serial_port;
        Gtk::ComboBox                   *combobox_baudrate;
        Gtk::ToggleButton               *togglebutton_open_close_port;

        // Log
        Gtk::CheckButton                *checkbutton_log_raw_packets;
        Gtk::CheckButton                *checkbutton_log_ngham_packets;
        Gtk::CheckButton                *checkbutton_log_ax25_packets;
        Gtk::CheckButton                *checkbutton_log_data;

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

        // Raw Packets
        Gtk::TextView                   *textview_raw_packets;
        Glib::RefPtr<Gtk::TextBuffer>   textview_raw_packets_buffer;

        // NGHam Packets
        Gtk::CheckButton                *checkbutton_ngham_hex_output;
        Gtk::TextView                   *textview_ngham_packets;
        Glib::RefPtr<Gtk::TextBuffer>   textview_ngham_packets_buffer;

        // AX25 Packets
        Gtk::TextView                   *textview_ax25_packets;
        Glib::RefPtr<Gtk::TextBuffer>   textview_ax25_packets_buffer;

        // Raw Packets File
        Gtk::FileChooserButton          *filechooserbutton_raw_packets;
        Gtk::ToggleButton               *togglebutton_play_stream;
        Gtk::Image                      *image_play_button;
        Gtk::Image                      *image_stop_button;

        // Clear Button
        Gtk::Button                     *button_clear_all;

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

        // About Dialog
        Gtk::Button                     *button_about;
        Gtk::AboutDialog                *aboutdialog;
        
        // Message Dialog
        Gtk::MessageDialog              *msg_dialog;
        
        bool receive_pkt;
        std::vector<uint8_t> sync_bytes_buffer;
        std::vector<uint8_t> byte_buffer;
        
        uint64_t prev_fin_byte_counter;
        uint64_t fin_byte_counter;
        
        bool serial_is_opened;
        
        UART                            *uart;                  /**< . */
        Log                             *log_raw_pkts;          /**< . */
        Log                             *log_ngham_pkts;        /**< . */
        //Log                             *log_ax25_pkts;         /**< . */
        Log                             *log_data_pkts;         /**< . */
        ProtocolStatistic               *ngham_statistic;       /**< . */
        ProtocolStatistic               *ax25_statistic;        /**< . */
        BeaconData                      *beacon_data;           /**< . */
        
        /**
         * \brief 
         * 
         * \return None
         */
        void OnMainWindowShow();
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
         * \return None
         */
        void OnToggleButtonPlayStreamToggled();
        /**
         * \brief 
         * 
         * \return None
         */
        void OnButtonClearAllClicked();
        /**
         * \brief 
         * 
         * \return None
         */
        void OnButtonAboutClicked();
        /**
         * \brief 
         * 
         * \return None
         */
        void SearchPackets();
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
