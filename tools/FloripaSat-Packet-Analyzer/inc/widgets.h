/*
 * widgets.h
 * 
 * Copyright (C) 2017, Universidade Federal de Santa Catarina
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
 * \file widgets.h
 * 
 * \brief Widgets struct.
 * 
 * \author Gabriel Mariano Marcelino <gabriel.mm8@gmail.com>
 * 
 * \version 1.0
 * 
 * \date 05/05/2017
 * 
 * \defgroup widgets Widgets
 * \ingroup fsat_pkt_ana
 * \{
 */

#ifndef WIDGETS_H_
#define WIDGETS_H_

#include <gtkmm.h>

/**
 * \struct Widgets
 * 
 * \brief 
 */
struct Widgets
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
    Gtk::CheckButton                *checkbutton_log_eps_data;
    
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
    Gtk::Button                     *button_load_raw_packets;
    
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
};

#endif // WIDGETS_H_

//! \} End of widgets group
