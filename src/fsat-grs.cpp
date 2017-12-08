/*
 * fsat-grs.cpp
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
 * \file fsat-grs.cpp
 * 
 * \brief .
 * 
 * \author Gabriel Mariano Marcelino <gabriel.mm8@gmail.com>
 * 
 * \version 1.0-dev
 * 
 * \date 10/09/2017
 * 
 * \addtogroup fsat_grs
 * \{
 */

#include <fstream>
#include <string>
#include <cstdio>
#include <thread>
#include <array>

#include "fsat-grs.h"
#include "aux.hpp"
#include "beacon_data.h"
#include "telemetry_data.h"
#include "data_processing.hpp"
#include "sha256.h"

FSatGRS::FSatGRS()
{
    
}

FSatGRS::FSatGRS(Glib::RefPtr<Gtk::Builder> ref_builder, const char *ui_file)
{
    this->BuildWidgets(ref_builder, ui_file);
    
    system("mkdir -p ~/.fsat_grs");
}

FSatGRS::~FSatGRS()
{
    //delete ngham_statistic;
    //delete ax25_statistic;
    //delete telemetry_ngham_statistic;
    //delete beacon_data;
    //delete telemetry_data;
    delete event_log;
    delete main_window;
}

int FSatGRS::BuildWidgets(Glib::RefPtr<Gtk::Builder> ref_builder, const char *ui_file)
{
    try
    {
        ref_builder->add_from_file(ui_file);
    }
    catch(const Glib::FileError& ex)
    {
        this->RaiseErrorMessage("File error!", ex.what().c_str());
        
        return -1;
    }
    catch(const Glib::MarkupError& ex)
    {
        this->RaiseErrorMessage("Markup error!", ex.what().c_str());
        
        return -1;
    }
    catch(const Gtk::BuilderError& ex)
    {
        this->RaiseErrorMessage("Builder error!", ex.what().c_str());
        
        return -1;
    }
    
    ref_builder->get_widget("MainWindow", main_window);
    
    if (!main_window)
    {
        return -1;
    }
    
    // Toolbar
    ref_builder->get_widget("toolbutton_open_log_file", toolbutton_open_log_file);
    if (toolbutton_open_log_file)
    {
        toolbutton_open_log_file->signal_clicked().connect(sigc::mem_fun(*this, &FSatGRS::OnToolButtonOpenClicked));
    }
    
    ref_builder->get_widget("toolbutton_statistics", toolbutton_statistics);
    if (toolbutton_statistics)
    {
        toolbutton_statistics->signal_clicked().connect(sigc::mem_fun(*this, &FSatGRS::OnToolButtonStatisticsClicked));
    }
    
    ref_builder->get_widget("toolbutton_plot", toolbutton_plot);
    if (toolbutton_plot)
    {
        toolbutton_plot->signal_clicked().connect(sigc::mem_fun(*this, &FSatGRS::OnToolButtonPlotClicked));
    }
    
    ref_builder->get_widget("toolbutton_ping", toolbutton_ping);
    if (toolbutton_ping)
    {
        toolbutton_ping->signal_clicked().connect(sigc::mem_fun(*this, &FSatGRS::OnToolButtonPingClicked));
    }
    
    ref_builder->get_widget("toolbutton_request_data", toolbutton_request_data);
    if (toolbutton_request_data)
    {
        toolbutton_request_data->signal_clicked().connect(sigc::mem_fun(*this, &FSatGRS::OnToolButtonRequestDataClicked));
    }
    
    ref_builder->get_widget("toolbutton_shutdown", toolbutton_shutdown);
    if (toolbutton_shutdown)
    {
        toolbutton_shutdown->signal_clicked().connect(sigc::mem_fun(*this, &FSatGRS::OnToolButtonShutdownClicked));
    }
    
    ref_builder->get_widget("toolbutton_config", toolbutton_config);
    if (toolbutton_config)
    {
        toolbutton_config->signal_clicked().connect(sigc::mem_fun(*this, &FSatGRS::OnToolButtonConfigClicked));
    }
    
    ref_builder->get_widget("toolbutton_about", toolbutton_about);
    if (toolbutton_about)
    {
        toolbutton_about->signal_clicked().connect(sigc::mem_fun(*this, &FSatGRS::OnToolButtonAboutClicked));
    }
    
    // Beacon stream
    ref_builder->get_widget("radiobutton_beacon_src_sdr", radiobutton_beacon_src_sdr);
    ref_builder->get_widget("entry_beacon_sdr_dev", entry_beacon_sdr_dev);
    ref_builder->get_widget("radiobutton_beacon_src_tcp", radiobutton_beacon_src_tcp);
    ref_builder->get_widget("entry_beacon_tcp_ip", entry_beacon_tcp_ip);
    ref_builder->get_widget("entry_beacon_tcp_port", entry_beacon_tcp_port);
    ref_builder->get_widget("radiobutton_beacon_src_serial", radiobutton_beacon_src_serial);
    ref_builder->get_widget("entry_beacon_serial_port", entry_beacon_serial_port);
    ref_builder->get_widget("combobox_beacon_baudrate", combobox_beacon_baudrate);
    ref_builder->get_widget("radiobutton_beacon_src_file", radiobutton_beacon_src_file);
    ref_builder->get_widget("filechooserbutton_beacon", filechooserbutton_beacon);
    
    ref_builder->get_widget("togglebutton_play_beacon", togglebutton_play_beacon);
    if (togglebutton_play_beacon)
    {
        togglebutton_play_beacon->signal_toggled().connect(sigc::mem_fun(*this, &FSatGRS::OnToggleButtonPlayBeaconToggled));
    }
    
    ref_builder->get_widget("togglebutton_pause_beacon", togglebutton_pause_beacon);
    if (togglebutton_pause_beacon)
    {
        togglebutton_pause_beacon->signal_toggled().connect(sigc::mem_fun(*this, &FSatGRS::OnToggleButtonPauseBeaconToggled));
    }
    
    ref_builder->get_widget("button_stop_beacon", button_stop_beacon);
    if (button_stop_beacon)
    {
        button_stop_beacon->signal_clicked().connect(sigc::mem_fun(*this, &FSatGRS::OnButtonStopBeaconClicked));
    }
    
    ref_builder->get_widget("button_clear_all_beacon", button_clear_all_beacon);
    if (button_clear_all_beacon)
    {
        button_clear_all_beacon->signal_clicked().connect(sigc::mem_fun(*this, &FSatGRS::OnButtonClearAllBeaconClicked));
    }
    
    // Telemetry stream
    ref_builder->get_widget("radiobutton_telemetry_src_sdr", radiobutton_telemetry_src_sdr);
    ref_builder->get_widget("entry_telemetry_sdr_dev", entry_telemetry_sdr_dev);
    ref_builder->get_widget("radiobutton_telemetry_src_tcp", radiobutton_telemetry_src_tcp);
    ref_builder->get_widget("entry_telemetry_tcp_ip", entry_telemetry_tcp_ip);
    ref_builder->get_widget("entry_telemetry_tcp_port", entry_telemetry_tcp_port);
    ref_builder->get_widget("radiobutton_telemetry_src_serial", radiobutton_telemetry_src_serial);
    ref_builder->get_widget("entry_telemetry_serial_port", entry_telemetry_serial_port);
    ref_builder->get_widget("combobox_telemetry_baudrate", combobox_telemetry_baudrate);
    ref_builder->get_widget("radiobutton_telemetry_src_file", radiobutton_telemetry_src_file);
    ref_builder->get_widget("filechooserbutton_telemetry", filechooserbutton_telemetry);
    
    ref_builder->get_widget("togglebutton_play_telemetry", togglebutton_play_telemetry);
    if (togglebutton_play_telemetry)
    {
        togglebutton_play_telemetry->signal_toggled().connect(sigc::mem_fun(*this, &FSatGRS::OnToggleButtonPlayTelemetryToggled));
    }
    
    ref_builder->get_widget("togglebutton_pause_telemetry", togglebutton_pause_telemetry);
    if (togglebutton_pause_telemetry)
    {
        togglebutton_pause_telemetry->signal_toggled().connect(sigc::mem_fun(*this, &FSatGRS::OnToggleButtonPlayTelemetryToggled));
    }
    
    ref_builder->get_widget("button_stop_telemetry", button_stop_telemetry);
    if (button_stop_telemetry)
    {
        button_stop_telemetry->signal_clicked().connect(sigc::mem_fun(*this, &FSatGRS::OnButtonStopTelemetryClicked));
    }
    
    ref_builder->get_widget("button_clear_all_telemetry", button_clear_all_telemetry);
    if (button_clear_all_telemetry)
    {
        button_clear_all_telemetry->signal_clicked().connect(sigc::mem_fun(*this, &FSatGRS::OnButtonClearAllTelemetryClicked));
    }
    
    // Log checkbuttons
    ref_builder->get_widget("checkbutton_log_ngham_packets", checkbutton_log_ngham_packets);
    ref_builder->get_widget("checkbutton_log_ax25_packets", checkbutton_log_ax25_packets);
    ref_builder->get_widget("checkbutton_log_beacon_data", checkbutton_log_beacon_data);
    ref_builder->get_widget("checkbutton_log_telemetry_data", checkbutton_log_telemetry_data);
    
    // Event log
    ref_builder->get_widget("textview_event_log", textview_event_log);
    if (textview_event_log)
    {
        event_log = new EventLog(textview_event_log);
        event_log->open((LOG_DEFAULT_DIR "/EVENTS_" + event_log->CurrentDateTime() + ".csv").c_str(), std::ofstream::out);
    }
    
    // NGHam packet configuration preamble
    ref_builder->get_widget("entry_ngham_config_preamble_byte", entry_ngham_config_preamble_byte);
    ref_builder->get_widget("entry_ngham_config_preamble_quant", entry_ngham_config_preamble_quant);
    
    // NGHam packet configuration sync. bytes
    ref_builder->get_widget("entry_ngham_sync_bytes_s0", entry_ngham_sync_bytes_s0);
    ref_builder->get_widget("entry_ngham_sync_bytes_s1", entry_ngham_sync_bytes_s1);
    ref_builder->get_widget("entry_ngham_sync_bytes_s2", entry_ngham_sync_bytes_s2);
    ref_builder->get_widget("entry_ngham_sync_bytes_s3", entry_ngham_sync_bytes_s3);
    
    // AX25 packet configuration preamble
    ref_builder->get_widget("entry_ax25_config_preamble_byte", entry_ax25_config_preamble_byte);
    ref_builder->get_widget("entry_ax25_config_preamble_quant", entry_ax25_config_preamble_quant);
    
    // AX25 packet configuration sync. bytes
    ref_builder->get_widget("entry_ax25_sync_bytes_s0", entry_ax25_sync_bytes_s0);
    ref_builder->get_widget("entry_ax25_sync_bytes_s1", entry_ax25_sync_bytes_s1);
    ref_builder->get_widget("entry_ax25_sync_bytes_s2", entry_ax25_sync_bytes_s2);
    ref_builder->get_widget("entry_ax25_sync_bytes_s3", entry_ax25_sync_bytes_s3);
    
    // NGHam statistic
    ref_builder->get_widget("label_ngham_valid_value", label_ngham_valid_value);
    ref_builder->get_widget("label_ngham_invalid_value", label_ngham_invalid_value);
    ref_builder->get_widget("label_ngham_total_value", label_ngham_total_value);
    ref_builder->get_widget("label_ngham_lost_value", label_ngham_lost_value);
    
    ngham_statistic = new ProtocolStatistic(label_ngham_valid_value, label_ngham_invalid_value, label_ngham_total_value, label_ngham_lost_value);
    
    // AX25 statistic
    ref_builder->get_widget("label_ax25_valid_value", label_ax25_valid_value);
    ref_builder->get_widget("label_ax25_invalid_value", label_ax25_invalid_value);
    ref_builder->get_widget("label_ax25_total_value", label_ax25_total_value);
    ref_builder->get_widget("label_ax25_lost_value", label_ax25_lost_value);
    
    //ax25_statistic = new ProtocolStatistic(label_ax25_valid_value, label_ax25_invalid_value, label_ax25_total_value, label_ax25_lost_value);
    
    // Beacon Data
    ref_builder->get_widget("label_beacon_data_bat1_v_value", label_beacon_data_bat1_v_value);
    ref_builder->get_widget("label_beacon_data_bat2_v_value", label_beacon_data_bat2_v_value);
    ref_builder->get_widget("label_beacon_data_bat1_t_value", label_beacon_data_bat1_t_value);
    ref_builder->get_widget("label_beacon_data_bat2_t_value", label_beacon_data_bat2_t_value);
    ref_builder->get_widget("label_beacon_data_bat_c_value", label_beacon_data_bat_c_value);
    ref_builder->get_widget("label_beacon_data_sp_i_my", label_beacon_data_sp_i_my);
    ref_builder->get_widget("label_beacon_data_sp_i_px", label_beacon_data_sp_i_px);
    ref_builder->get_widget("label_beacon_data_sp_i_mx", label_beacon_data_sp_i_mx);
    ref_builder->get_widget("label_beacon_data_sp_i_pz", label_beacon_data_sp_i_pz);
    ref_builder->get_widget("label_beacon_data_sp_i_mz", label_beacon_data_sp_i_mz);
    ref_builder->get_widget("label_beacon_data_sp_i_py", label_beacon_data_sp_i_py);
    ref_builder->get_widget("label_beacon_data_sp_v_mypx", label_beacon_data_sp_v_mypx);
    ref_builder->get_widget("label_beacon_data_sp_v_mxpz", label_beacon_data_sp_v_mxpz);
    ref_builder->get_widget("label_beacon_data_sp_v_mzpy", label_beacon_data_sp_v_mzpy);
    ref_builder->get_widget("label_beacon_data_status_energy_level", label_beacon_data_status_energy_level);
    ref_builder->get_widget("label_beacon_data_status_imu", label_beacon_data_status_imu);
    ref_builder->get_widget("label_beacon_data_status_usd", label_beacon_data_status_usd);
    ref_builder->get_widget("label_beacon_data_status_rush", label_beacon_data_status_rush);
    ref_builder->get_widget("label_beacon_data_status_eps", label_beacon_data_status_eps);
    ref_builder->get_widget("label_beacon_data_status_antenna", label_beacon_data_status_antenna);
    ref_builder->get_widget("label_beacon_data_imu_accel_x", label_beacon_data_imu_accel_x);
    ref_builder->get_widget("label_beacon_data_imu_accel_y", label_beacon_data_imu_accel_y);
    ref_builder->get_widget("label_beacon_data_imu_accel_z", label_beacon_data_imu_accel_z);
    ref_builder->get_widget("label_beacon_data_imu_gyro_x", label_beacon_data_imu_gyro_x);
    ref_builder->get_widget("label_beacon_data_imu_gyro_y", label_beacon_data_imu_gyro_y);
    ref_builder->get_widget("label_beacon_data_imu_gyro_z", label_beacon_data_imu_gyro_z);
    ref_builder->get_widget("label_beacon_data_obdh_rst_value", label_beacon_data_obdh_rst_value);
    ref_builder->get_widget("label_beacon_data_system_time_value", label_beacon_data_system_time_value);
    
    std::vector<Gtk::Label *> beacon_data_labels;
    beacon_data_labels.push_back(label_beacon_data_bat1_v_value);
    beacon_data_labels.push_back(label_beacon_data_bat2_v_value);
    beacon_data_labels.push_back(label_beacon_data_bat1_t_value);
    beacon_data_labels.push_back(label_beacon_data_bat2_t_value);
    beacon_data_labels.push_back(label_beacon_data_bat_c_value);
    beacon_data_labels.push_back(label_beacon_data_sp_i_my);
    beacon_data_labels.push_back(label_beacon_data_sp_i_px);
    beacon_data_labels.push_back(label_beacon_data_sp_i_mx);
    beacon_data_labels.push_back(label_beacon_data_sp_i_pz);
    beacon_data_labels.push_back(label_beacon_data_sp_i_mz);
    beacon_data_labels.push_back(label_beacon_data_sp_i_py);
    beacon_data_labels.push_back(label_beacon_data_sp_v_mypx);
    beacon_data_labels.push_back(label_beacon_data_sp_v_mxpz);
    beacon_data_labels.push_back(label_beacon_data_sp_v_mzpy);
    beacon_data_labels.push_back(label_beacon_data_status_energy_level);
    beacon_data_labels.push_back(label_beacon_data_status_imu);
    beacon_data_labels.push_back(label_beacon_data_status_usd);
    beacon_data_labels.push_back(label_beacon_data_status_rush);
    beacon_data_labels.push_back(label_beacon_data_status_eps);
    beacon_data_labels.push_back(label_beacon_data_status_antenna);
    beacon_data_labels.push_back(label_beacon_data_imu_accel_x);
    beacon_data_labels.push_back(label_beacon_data_imu_accel_y);
    beacon_data_labels.push_back(label_beacon_data_imu_accel_z);
    beacon_data_labels.push_back(label_beacon_data_imu_gyro_x);
    beacon_data_labels.push_back(label_beacon_data_imu_gyro_y);
    beacon_data_labels.push_back(label_beacon_data_imu_gyro_z);
    beacon_data_labels.push_back(label_beacon_data_obdh_rst_value);
    beacon_data_labels.push_back(label_beacon_data_system_time_value);
    
    beacon_data = new BeaconData(beacon_data_labels);
    
    // Telemetry data
    ref_builder->get_widget("label_telemetry_data_status_reset_counter", label_telemetry_data_status_reset_counter);
    ref_builder->get_widget("label_telemetry_data_status_reset_cause", label_telemetry_data_status_reset_cause);
    ref_builder->get_widget("label_telemetry_data_status_clock", label_telemetry_data_status_clock);
    ref_builder->get_widget("label_telemetry_data_status_imu", label_telemetry_data_status_imu);
    ref_builder->get_widget("label_telemetry_data_status_usd", label_telemetry_data_status_usd);
    ref_builder->get_widget("label_telemetry_data_status_rush", label_telemetry_data_status_rush);
    ref_builder->get_widget("label_telemetry_data_status_eps", label_telemetry_data_status_eps);
    ref_builder->get_widget("label_telemetry_data_status_antenna", label_telemetry_data_status_antenna);
    ref_builder->get_widget("label_telemetry_data_uc_temp", label_telemetry_data_uc_temp);
    ref_builder->get_widget("label_telemetry_data_uc_voltage", label_telemetry_data_uc_voltage);
    ref_builder->get_widget("label_telemetry_data_uc_current", label_telemetry_data_uc_current);
    ref_builder->get_widget("label_telemetry_data_time_system", label_telemetry_data_time_system);
    ref_builder->get_widget("label_telemetry_data_time_system_up", label_telemetry_data_time_system_up);
    ref_builder->get_widget("label_telemetry_data_imu_accel_x", label_telemetry_data_imu_accel_x);
    ref_builder->get_widget("label_telemetry_data_imu_accel_y", label_telemetry_data_imu_accel_y);
    ref_builder->get_widget("label_telemetry_data_imu_accel_z", label_telemetry_data_imu_accel_z);
    ref_builder->get_widget("label_telemetry_data_imu_gyro_x", label_telemetry_data_imu_gyro_x);
    ref_builder->get_widget("label_telemetry_data_imu_gyro_y", label_telemetry_data_imu_gyro_y);
    ref_builder->get_widget("label_telemetry_data_imu_gyro_z", label_telemetry_data_imu_gyro_z);
    ref_builder->get_widget("label_telemetry_data_sp_sun_p1", label_telemetry_data_sp_sun_p1);
    ref_builder->get_widget("label_telemetry_data_sp_sun_p2", label_telemetry_data_sp_sun_p2);
    ref_builder->get_widget("label_telemetry_data_sp_sun_p3", label_telemetry_data_sp_sun_p3);
    ref_builder->get_widget("label_telemetry_data_sp_temp_p1", label_telemetry_data_sp_temp_p1);
    ref_builder->get_widget("label_telemetry_data_sp_temp_p2", label_telemetry_data_sp_temp_p2);
    ref_builder->get_widget("label_telemetry_data_sp_temp_p3", label_telemetry_data_sp_temp_p3);
    ref_builder->get_widget("label_telemetry_data_eps_bat_mean_i", label_telemetry_data_eps_bat_mean_i);
    ref_builder->get_widget("label_telemetry_data_eps_bat_temp", label_telemetry_data_eps_bat_temp);
    ref_builder->get_widget("label_telemetry_data_eps_bat_1_volt", label_telemetry_data_eps_bat_1_volt);
    ref_builder->get_widget("label_telemetry_data_eps_bat_2_volt", label_telemetry_data_eps_bat_2_volt);
    ref_builder->get_widget("label_telemetry_data_eps_bat_current", label_telemetry_data_eps_bat_current);
    ref_builder->get_widget("label_telemetry_data_eps_bat_charge", label_telemetry_data_eps_bat_charge);
    ref_builder->get_widget("label_telemetry_data_eps_bat_protection", label_telemetry_data_eps_bat_protection);
    ref_builder->get_widget("label_telemetry_data_eps_bat_status", label_telemetry_data_eps_bat_status);
    ref_builder->get_widget("label_telemetry_data_eps_bat_cycles", label_telemetry_data_eps_bat_cycles);
    ref_builder->get_widget("label_telemetry_data_eps_bat_raac", label_telemetry_data_eps_bat_raac);
    ref_builder->get_widget("label_telemetry_data_eps_bat_rsac", label_telemetry_data_eps_bat_rsac);
    ref_builder->get_widget("label_telemetry_data_eps_bat_rarc", label_telemetry_data_eps_bat_rarc);
    ref_builder->get_widget("label_telemetry_data_eps_bat_rsrc", label_telemetry_data_eps_bat_rsrc);
    ref_builder->get_widget("label_telemetry_data_eps_sp_i_my", label_telemetry_data_eps_sp_i_my);
    ref_builder->get_widget("label_telemetry_data_eps_sp_i_px", label_telemetry_data_eps_sp_i_px);
    ref_builder->get_widget("label_telemetry_data_eps_sp_i_mx", label_telemetry_data_eps_sp_i_mx);
    ref_builder->get_widget("label_telemetry_data_eps_sp_i_pz", label_telemetry_data_eps_sp_i_pz);
    ref_builder->get_widget("label_telemetry_data_eps_sp_i_mz", label_telemetry_data_eps_sp_i_mz);
    ref_builder->get_widget("label_telemetry_data_eps_sp_i_py", label_telemetry_data_eps_sp_i_py);
    ref_builder->get_widget("label_telemetry_data_eps_sp_v_mypx", label_telemetry_data_eps_sp_v_mypx);
    ref_builder->get_widget("label_telemetry_data_eps_sp_v_mxpz", label_telemetry_data_eps_sp_v_mxpz);
    ref_builder->get_widget("label_telemetry_data_eps_sp_v_mzpy", label_telemetry_data_eps_sp_v_mzpy);
    ref_builder->get_widget("label_telemetry_data_eps_misc_boost_v", label_telemetry_data_eps_misc_boost_v);
    ref_builder->get_widget("label_telemetry_data_eps_misc_main_bus_v", label_telemetry_data_eps_misc_main_bus_v);
    ref_builder->get_widget("label_telemetry_data_eps_misc_beacon_i", label_telemetry_data_eps_misc_beacon_i);
    ref_builder->get_widget("label_telemetry_data_eps_misc_uc_temp", label_telemetry_data_eps_misc_uc_temp);
    ref_builder->get_widget("label_telemetry_data_eps_misc_energy_level", label_telemetry_data_eps_misc_energy_level);
    
    std::vector<Gtk::Label *> telemetry_data_labels;
    telemetry_data_labels.push_back(label_telemetry_data_status_reset_counter);
    telemetry_data_labels.push_back(label_telemetry_data_status_reset_cause);
    telemetry_data_labels.push_back(label_telemetry_data_status_clock);
    telemetry_data_labels.push_back(label_telemetry_data_status_imu);
    telemetry_data_labels.push_back(label_telemetry_data_status_usd);
    telemetry_data_labels.push_back(label_telemetry_data_status_rush);
    telemetry_data_labels.push_back(label_telemetry_data_status_eps);
    telemetry_data_labels.push_back(label_telemetry_data_status_antenna);
    telemetry_data_labels.push_back(label_telemetry_data_uc_temp);
    telemetry_data_labels.push_back(label_telemetry_data_uc_voltage);
    telemetry_data_labels.push_back(label_telemetry_data_uc_current);
    telemetry_data_labels.push_back(label_telemetry_data_time_system);
    telemetry_data_labels.push_back(label_telemetry_data_time_system_up);
    telemetry_data_labels.push_back(label_telemetry_data_imu_accel_x);
    telemetry_data_labels.push_back(label_telemetry_data_imu_accel_y);
    telemetry_data_labels.push_back(label_telemetry_data_imu_accel_z);
    telemetry_data_labels.push_back(label_telemetry_data_imu_gyro_x);
    telemetry_data_labels.push_back(label_telemetry_data_imu_gyro_y);
    telemetry_data_labels.push_back(label_telemetry_data_imu_gyro_z);
    telemetry_data_labels.push_back(label_telemetry_data_sp_sun_p1);
    telemetry_data_labels.push_back(label_telemetry_data_sp_sun_p2);
    telemetry_data_labels.push_back(label_telemetry_data_sp_sun_p3);
    telemetry_data_labels.push_back(label_telemetry_data_sp_temp_p1);
    telemetry_data_labels.push_back(label_telemetry_data_sp_temp_p2);
    telemetry_data_labels.push_back(label_telemetry_data_sp_temp_p3);
    telemetry_data_labels.push_back(label_telemetry_data_eps_bat_mean_i);
    telemetry_data_labels.push_back(label_telemetry_data_eps_bat_temp);
    telemetry_data_labels.push_back(label_telemetry_data_eps_bat_1_volt);
    telemetry_data_labels.push_back(label_telemetry_data_eps_bat_2_volt);
    telemetry_data_labels.push_back(label_telemetry_data_eps_bat_current);
    telemetry_data_labels.push_back(label_telemetry_data_eps_bat_charge);
    telemetry_data_labels.push_back(label_telemetry_data_eps_bat_protection);
    telemetry_data_labels.push_back(label_telemetry_data_eps_bat_status);
    telemetry_data_labels.push_back(label_telemetry_data_eps_bat_cycles);
    telemetry_data_labels.push_back(label_telemetry_data_eps_bat_raac);
    telemetry_data_labels.push_back(label_telemetry_data_eps_bat_rsac);
    telemetry_data_labels.push_back(label_telemetry_data_eps_bat_rarc);
    telemetry_data_labels.push_back(label_telemetry_data_eps_bat_rsrc);
    telemetry_data_labels.push_back(label_telemetry_data_eps_sp_i_my);
    telemetry_data_labels.push_back(label_telemetry_data_eps_sp_i_px);
    telemetry_data_labels.push_back(label_telemetry_data_eps_sp_i_mx);
    telemetry_data_labels.push_back(label_telemetry_data_eps_sp_i_pz);
    telemetry_data_labels.push_back(label_telemetry_data_eps_sp_i_mz);
    telemetry_data_labels.push_back(label_telemetry_data_eps_sp_i_py);
    telemetry_data_labels.push_back(label_telemetry_data_eps_sp_v_mypx);
    telemetry_data_labels.push_back(label_telemetry_data_eps_sp_v_mxpz);
    telemetry_data_labels.push_back(label_telemetry_data_eps_sp_v_mzpy);
    telemetry_data_labels.push_back(label_telemetry_data_eps_misc_boost_v);
    telemetry_data_labels.push_back(label_telemetry_data_eps_misc_main_bus_v);
    telemetry_data_labels.push_back(label_telemetry_data_eps_misc_beacon_i);
    telemetry_data_labels.push_back(label_telemetry_data_eps_misc_uc_temp);
    telemetry_data_labels.push_back(label_telemetry_data_eps_misc_energy_level);
    
    telemetry_data = new TelemetryData(telemetry_data_labels);
    
    // Telemtry Packets Statistic
    ref_builder->get_widget("label_telemetry_pkt_statistic_total", label_telemetry_pkt_statistic_total);
    ref_builder->get_widget("label_telemetry_pkt_statistic_lost", label_telemetry_pkt_statistic_lost);
    
    telemetry_ngham_statistic = new ProtocolStatistic(label_telemetry_pkt_statistic_total, label_telemetry_pkt_statistic_total, label_telemetry_pkt_statistic_total, label_telemetry_pkt_statistic_lost);
    
    // Data to request
    ref_builder->get_widget("checkbutton_imu_1_accel_x", checkbutton_imu_1_accel_x);
    ref_builder->get_widget("checkbutton_imu_2_accel_x", checkbutton_imu_2_accel_x);
    ref_builder->get_widget("checkbutton_imu_1_accel_y", checkbutton_imu_1_accel_y);
    ref_builder->get_widget("checkbutton_imu_2_accel_y", checkbutton_imu_2_accel_y);
    ref_builder->get_widget("checkbutton_imu_1_accel_z", checkbutton_imu_1_accel_z);
    ref_builder->get_widget("checkbutton_imu_2_accel_z", checkbutton_imu_2_accel_z);
    ref_builder->get_widget("checkbutton_imu_1_gyro_x", checkbutton_imu_1_gyro_x);
    ref_builder->get_widget("checkbutton_imu_1_gyro_y", checkbutton_imu_1_gyro_y);
    ref_builder->get_widget("checkbutton_imu_1_gyro_z", checkbutton_imu_1_gyro_z);
    ref_builder->get_widget("checkbutton_imu_2_gyro_x", checkbutton_imu_2_gyro_x);
    ref_builder->get_widget("checkbutton_imu_2_gyro_y", checkbutton_imu_2_gyro_y);
    ref_builder->get_widget("checkbutton_imu_2_gyro_z", checkbutton_imu_2_gyro_z);
    ref_builder->get_widget("checkbutton_sp_sun_p1", checkbutton_sp_sun_p1);
    ref_builder->get_widget("checkbutton_sp_temp_p1", checkbutton_sp_temp_p1);
    ref_builder->get_widget("checkbutton_sp_sun_p2", checkbutton_sp_sun_p2);
    ref_builder->get_widget("checkbutton_sp_sun_p3", checkbutton_sp_sun_p3);
    ref_builder->get_widget("checkbutton_sp_temp_p2", checkbutton_sp_temp_p2);
    ref_builder->get_widget("checkbutton_sp_temp_p3", checkbutton_sp_temp_p3);
    ref_builder->get_widget("checkbutton_reset_counter", checkbutton_reset_counter);
    ref_builder->get_widget("checkbutton_clock_fault", checkbutton_clock_fault);
    ref_builder->get_widget("checkbutton_reset_cause", checkbutton_reset_cause);
    ref_builder->get_widget("checkbutton_obdh_uc_temp", checkbutton_obdh_uc_temp);
    ref_builder->get_widget("checkbutton_system_time", checkbutton_system_time);
    ref_builder->get_widget("checkbutton_imu_status", checkbutton_imu_status);
    ref_builder->get_widget("checkbutton_sd_card_status", checkbutton_sd_card_status);
    ref_builder->get_widget("checkbutton_rush_status", checkbutton_rush_status);
    ref_builder->get_widget("checkbutton_eps_status", checkbutton_eps_status);
    ref_builder->get_widget("checkbutton_antenna_status", checkbutton_antenna_status);
    ref_builder->get_widget("checkbutton_obdh_uc_voltage", checkbutton_obdh_uc_voltage);
    ref_builder->get_widget("checkbutton_obdh_uc_current", checkbutton_obdh_uc_current);
    ref_builder->get_widget("checkbutton_system_up_time", checkbutton_system_up_time);
    ref_builder->get_widget("checkbutton_rush_data", checkbutton_rush_data);
    ref_builder->get_widget("button_request_obdh_select_all", button_request_obdh_select_all);
    ref_builder->get_widget("button_request_obdh_unselect_all", button_request_obdh_unselect_all);
    
    if (button_request_obdh_select_all)
    {
        button_request_obdh_select_all->signal_clicked().connect(sigc::mem_fun(*this, &FSatGRS::OnButtonSelectOBDHDataClicked));
    }
    
    if (button_request_obdh_unselect_all)
    {
        button_request_obdh_unselect_all->signal_clicked().connect(sigc::mem_fun(*this, &FSatGRS::OnButtonUnselectOBDHDataClicked));
    }
    
    ref_builder->get_widget("checkbutton_bat_mean_current", checkbutton_bat_mean_current);
    ref_builder->get_widget("checkbutton_bat_temperature", checkbutton_bat_temperature);
    ref_builder->get_widget("checkbutton_bat_1_voltage", checkbutton_bat_1_voltage);
    ref_builder->get_widget("checkbutton_bat_2_voltage", checkbutton_bat_2_voltage);
    ref_builder->get_widget("checkbutton_bat_current", checkbutton_bat_current);
    ref_builder->get_widget("checkbutton_bat_charge", checkbutton_bat_charge);
    ref_builder->get_widget("checkbutton_bat_rsrc", checkbutton_bat_rsrc);
    ref_builder->get_widget("checkbutton_energy_level", checkbutton_energy_level);
    ref_builder->get_widget("checkbutton_sp_current_my", checkbutton_sp_current_my);
    ref_builder->get_widget("checkbutton_sp_current_px", checkbutton_sp_current_px);
    ref_builder->get_widget("checkbutton_sp_current_mx", checkbutton_sp_current_mx);
    ref_builder->get_widget("checkbutton_sp_current_pz", checkbutton_sp_current_pz);
    ref_builder->get_widget("checkbutton_sp_current_mz", checkbutton_sp_current_mz);
    ref_builder->get_widget("checkbutton_sp_current_py", checkbutton_sp_current_py);
    ref_builder->get_widget("checkbutton_sp_voltage_my_px", checkbutton_sp_voltage_my_px);
    ref_builder->get_widget("checkbutton_sp_voltage_mx_pz", checkbutton_sp_voltage_mx_pz);
    ref_builder->get_widget("checkbutton_sp_voltage_mz_py", checkbutton_sp_voltage_mz_py);
    ref_builder->get_widget("checkbutton_eps_uc_temp", checkbutton_eps_uc_temp);
    ref_builder->get_widget("checkbutton_bat_protection", checkbutton_bat_protection);
    ref_builder->get_widget("checkbutton_bat_status", checkbutton_bat_status);
    ref_builder->get_widget("checkbutton_bat_cycle_counting", checkbutton_bat_cycle_counting);
    ref_builder->get_widget("checkbutton_bat_raac", checkbutton_bat_raac);
    ref_builder->get_widget("checkbutton_bat_rsac", checkbutton_bat_rsac);
    ref_builder->get_widget("checkbutton_bat_rarc", checkbutton_bat_rarc);
    ref_builder->get_widget("checkbutton_boost_voltage", checkbutton_boost_voltage);
    ref_builder->get_widget("checkbutton_main_bus_voltage", checkbutton_main_bus_voltage);
    ref_builder->get_widget("checkbutton_beacon_current", checkbutton_beacon_current);
    ref_builder->get_widget("button_request_eps_select_all", button_request_eps_select_all);
    ref_builder->get_widget("button_request_eps_unselect_all", button_request_eps_unselect_all);
    
    if (button_request_eps_select_all)
    {
        button_request_eps_select_all->signal_clicked().connect(sigc::mem_fun(*this, &FSatGRS::OnButtonSelectEPSDataClicked));
    }
    
    if (button_request_eps_unselect_all)
    {
        button_request_eps_unselect_all->signal_clicked().connect(sigc::mem_fun(*this, &FSatGRS::OnButtonUnselectEPSDataClicked));
    }
    
    // Plot dialog
    ref_builder->get_widget("dialog_plot", dialog_plot);
    ref_builder->get_widget("filechooserbutton_plot_beacon", filechooserbutton_plot_beacon);
    ref_builder->get_widget("combobox_plot_beacon_data", combobox_plot_beacon_data);
    ref_builder->get_widget("checkbutton_plot_beacon_connect_points", checkbutton_plot_beacon_connect_points);
    ref_builder->get_widget("checkbutton_plot_beacon_best_curve", checkbutton_plot_beacon_best_curve);
    ref_builder->get_widget("checkbutton_plot_save_pdf_beacon", checkbutton_plot_save_pdf_beacon);
    ref_builder->get_widget("filechooserbutton_plot_telemetry", filechooserbutton_plot_telemetry);
    ref_builder->get_widget("combobox_plot_telemetry_data", combobox_plot_telemetry_data);
    ref_builder->get_widget("checkbutton_plot_telemetry_connect_points", checkbutton_plot_telemetry_connect_points);
    ref_builder->get_widget("checkbutton_plot_telemetry_best_curve", checkbutton_plot_telemetry_best_curve);
    ref_builder->get_widget("checkbutton_plot_save_pdf_telemetry", checkbutton_plot_save_pdf_telemetry);
    ref_builder->get_widget("button_plot", button_plot);
    
    if (button_plot)
    {
        button_plot->signal_clicked().connect(sigc::mem_fun(*this, &FSatGRS::OnButtonPlotClicked));
    }
    
    // Log Analysis Dialog
    ref_builder->get_widget("dialog_log_statistics", dialog_log_statistics);
    ref_builder->get_widget("filechooserbutton_log_analysis", filechooserbutton_log_analysis);
    ref_builder->get_widget("textview_log_analysis_result", textview_log_analysis_result);
    ref_builder->get_widget("button_run_log_analysis", button_run_log_analysis);
    ref_builder->get_widget("radio_button_log_analysis_beacon", radio_button_log_analysis_beacon);
    ref_builder->get_widget("radio_button_log_analysis_telemetry", radio_button_log_analysis_telemetry);
    
    if (button_run_log_analysis)
    {
        button_run_log_analysis->signal_clicked().connect(sigc::mem_fun(*this, &FSatGRS::OnButtonRunAnalysisClicked));
    }
    
    // Preferences dialog
    ref_builder->get_widget("dialog_config", dialog_config);
    ref_builder->get_widget("entry_config_general_admin_user", entry_config_general_admin_user);
    ref_builder->get_widget("entry_config_general_admin_password", entry_config_general_admin_password);
    ref_builder->get_widget("entry_config_general_new_user", entry_config_general_new_user);
    ref_builder->get_widget("entry_config_general_new_password", entry_config_general_new_password);
    ref_builder->get_widget("entry_config_general_admin_password_confirmation", entry_config_general_admin_password_confirmation);
    
    ref_builder->get_widget("button_config_general_add_new_user", button_config_general_add_new_user);
    if (button_config_general_add_new_user)
    {
        button_config_general_add_new_user->signal_clicked().connect(sigc::mem_fun(*this, &FSatGRS::OnButtonAddNewUserClicked));
    }
    
    ref_builder->get_widget("entry_config_downlink_beacon_freq", entry_config_downlink_beacon_freq);
    ref_builder->get_widget("entry_config_downlink_beacon_baudrate", entry_config_downlink_beacon_baudrate);
    ref_builder->get_widget("entry_config_downlink_beacon_filter", entry_config_downlink_beacon_filter);
    ref_builder->get_widget("entry_config_downlink_beacon_sample_rate", entry_config_downlink_beacon_sample_rate);
    ref_builder->get_widget("entry_config_downlink_telemetry_freq", entry_config_downlink_telemetry_freq);
    ref_builder->get_widget("entry_config_downlink_telemetry_baudrate", entry_config_downlink_telemetry_baudrate);
    ref_builder->get_widget("entry_config_downlink_telemetry_filter", entry_config_downlink_telemetry_filter);
    ref_builder->get_widget("entry_config_downlink_telemetry_sample_rate", entry_config_downlink_telemetry_sample_rate);
    ref_builder->get_widget("entry_config_uplink_telemetry_frequency", entry_config_uplink_telemetry_frequency);
    ref_builder->get_widget("entry_config_uplink_telemetry_burst", entry_config_uplink_telemetry_burst);
    ref_builder->get_widget("entry_config_uplink_telemetry_sdr", entry_config_uplink_telemetry_sdr);
    ref_builder->get_widget("entry_config_uplink_beacon_frequency", entry_config_uplink_beacon_frequency);
    ref_builder->get_widget("entry_config_uplink_beacon_burst", entry_config_uplink_beacon_burst);
    ref_builder->get_widget("entry_config_uplink_beacon_sdr", entry_config_uplink_beacon_sdr);
    ref_builder->get_widget("radiobutton_config_uplink_type_telemetry", radiobutton_config_uplink_type_telemetry);
    ref_builder->get_widget("radiobutton_config_uplink_type_beacon", radiobutton_config_uplink_type_beacon);
    ref_builder->get_widget("radiobutton_config_uplink_type_both", radiobutton_config_uplink_type_both);
    
    ref_builder->get_widget("button_config_ok", button_config_ok);
    if (button_config_ok)
    {
        button_config_ok->signal_clicked().connect(sigc::mem_fun(*this, &FSatGRS::OnButtonConfigOkClicked));
    }
    
    ref_builder->get_widget("button_config_default", button_config_default);
    if (button_config_default)
    {
        button_config_default->signal_clicked().connect(sigc::mem_fun(*this, &FSatGRS::OnButtonConfigDefaultClicked));
    }
    
    // Shutdown Command Authentication Dialog
    ref_builder->get_widget("dialog_shutdown_authentication", dialog_shutdown_authentication);
    ref_builder->get_widget("entry_sd_auth_user", entry_sd_auth_user);
    ref_builder->get_widget("entry_sd_auth_password", entry_sd_auth_password);
    
    ref_builder->get_widget("button_sd_auth_send", button_sd_auth_send);
    if (button_sd_auth_send)
    {
        button_sd_auth_send->signal_clicked().connect(sigc::mem_fun(*this, &FSatGRS::OnButtonShutdownAuthSendClicked));
    }
    
    ref_builder->get_widget("button_sd_auth_cancel", button_sd_auth_cancel);
    if (button_sd_auth_cancel)
    {
        button_sd_auth_cancel->signal_clicked().connect(sigc::mem_fun(*this, &FSatGRS::OnButtonShutdownAuthCancelClicked));
    }
    
    // About dialog
    ref_builder->get_widget("aboutdialog", aboutdialog);
    
    return 0;
}

int FSatGRS::Run(Glib::RefPtr<Gtk::Application> app)
{
    auto timer_slot = sigc::mem_fun(*this, &FSatGRS::Timer);
    auto conn = Glib::signal_timeout().connect(timer_slot, DATA_RECEPTION_SAMPLE_RATE);
    
    return app->run(*main_window);
}
/*
std::vector<uint8_t> FSatGRS::ProccessByte(uint8_t byte)
{
    std::vector<uint8_t> sync_bytes;
    
    sync_bytes.push_back(EntryToHex(entry_ngham_sync_bytes_s3->get_text()));
    sync_bytes.push_back(EntryToHex(entry_ngham_sync_bytes_s2->get_text()));
    sync_bytes.push_back(EntryToHex(entry_ngham_sync_bytes_s1->get_text()));
    sync_bytes.push_back(EntryToHex(entry_ngham_sync_bytes_s0->get_text()));
    
    std::vector<uint8_t> result;
    
    if (!receive_pkt)
    {
        sync_bytes_buffer.push_back(byte);
        
        if (sync_bytes_buffer.size() == 4)
        {
            if (sync_bytes_buffer == sync_bytes)
            {
                receive_pkt = true;
                sync_bytes_buffer.clear();
            }
            else
            {
                sync_bytes_buffer.erase(sync_bytes_buffer.begin());
            }
        }
    }
    else
    {
        uint8_t data[256];
        uint8_t data_len;
        switch(ngham_Decode(byte, data, &data_len))
        {
            case PKT_CONDITION_OK:
                receive_pkt = false;
                for(unsigned int j=0; j<data_len; j++)
                {
                    result.push_back(data[j]);
                }
                
                ngham_statistic->AddValidPkt();
                
                beacon_data->Update(data, data_len);
                
                if (checkbutton_log_beacon_data->get_active())
                {
                    *log_beacon_data << log_beacon_data->CurrentDateTime(LOG_DATA_TIME_FOR_LOG_CSV) << beacon_data->Log() << "\n";
                }
                
                break;
            case PKT_CONDITION_PREFAIL:
                break;
            case PKT_CONDITION_FAIL:
                result.push_back((uint8_t('E')));
                result.push_back((uint8_t('R')));
                result.push_back((uint8_t('R')));
                result.push_back((uint8_t('O')));
                result.push_back((uint8_t('R')));
                result.push_back((uint8_t('!')));
                
                receive_pkt = false;
                ngham_statistic->AddInvalidPkt();
                
                break;
        }
    }
    
    return result;
}*/

bool FSatGRS::Timer()
{
    /*if (togglebutton_open_close_port->get_active())
    {
        int bytes_buf = uart->DataAvailable();
        if (bytes_buf > 0)
        {
            while(bytes_buf--)
            {
                uint8_t byte = uart->GetByte();
                
                std::vector<uint8_t> r = this->ProccessByte(byte);
                if (!r.empty())
                {
                    if (checkbutton_log_ngham_packets->get_active())
                    {
                        *log_ngham_pkts << log_ngham_pkts->CurrentDateTime(LOG_DATA_TIME_FOR_LOG_CSV);
                    }
                    
                    for(unsigned int i=0;i<r.size();i++)
                    {
                        std::stringstream byte_str;
                        byte_str << (char)r[i];
                        std::string b_ngham = byte_str.str();
                        
                        if (checkbutton_log_ngham_packets->get_active())
                        {
                            *log_ngham_pkts << HexToStr(r[i]);
                        }
                    }
                    
                    textview_event_log_buffer->insert_at_cursor("\n");
                    
                    if (checkbutton_log_ngham_packets->get_active())
                    {
                        *log_ngham_pkts << "\n";
                    }
                    
                    auto iter_ngham = textview_event_log_buffer->end();
                    textview_event_log->scroll_to(iter_ngham);
                }
                
                // AX25 packets  >>>>>>>>> TO BE IMPLEMENTED
            }
        }
    }*/
    
    if (togglebutton_play_beacon->get_active())
    {
        if (!togglebutton_pause_beacon->get_active())
        {
            if (filechooserbutton_beacon->get_filename().size() > 0)
            {
                ngham_pkts_beacon->Search(filechooserbutton_beacon->get_filename().c_str());
                //ax25_pkts_beacon->Search(filechooserbutton_beacon->get_filename().c_str());
            }
            else
            {
                ngham_pkts_beacon->Search(FSAT_GRS_GRC_BEACON_BIN);
                //ax25_pkts_beacon->Search(FSAT_PKT_ANA_GRC_BEACON_BIN);
            }
        }
    }
    
    if (togglebutton_play_telemetry->get_active())
    {
        if (!togglebutton_pause_telemetry->get_active())
        {
            if (filechooserbutton_telemetry->get_filename().size() > 0)
            {
                ngham_pkts_telemetry->Search(filechooserbutton_telemetry->get_filename().c_str());
            }
            else
            {
                ngham_pkts_telemetry->Search(FSAT_GRS_GRC_TELEMETRY_BIN);
            }
        }
    }
    
	return true;
}

void FSatGRS::OnToolButtonOpenClicked()
{
    this->RaiseErrorMessage("Under development!", "This functionality will be available soon.");
}

void FSatGRS::OnToolButtonConfigClicked()
{    
    int response = dialog_config->run();
    
    if ((response == Gtk::RESPONSE_DELETE_EVENT) or (response == Gtk::RESPONSE_CANCEL))
    {
        dialog_config->hide();
    }
}

void FSatGRS::OnButtonConfigOkClicked()
{
    dialog_config->hide();
}

void FSatGRS::OnButtonConfigDefaultClicked()
{
    //this->LoadDefaultConfiguration();
    
    dialog_config->hide();
}

void FSatGRS::OnToolButtonStatisticsClicked()
{
    int response = dialog_log_statistics->run();
    
    if ((response == Gtk::RESPONSE_DELETE_EVENT) or (response == Gtk::RESPONSE_CANCEL))
    {
        dialog_log_statistics->hide();
    }
}

void FSatGRS::OnToolButtonPlotClicked()
{
    int response = dialog_plot->run();
    
    if ((response == Gtk::RESPONSE_DELETE_EVENT) or (response == Gtk::RESPONSE_CANCEL))
    {
        dialog_plot->hide();
    }
}

void FSatGRS::OnToolButtonPingClicked()
{
    std::string ping_event = "Transmitting ";
    ping_event += entry_config_uplink_telemetry_burst->get_text();
    ping_event += " ping command(s)...";
    
    event_log->AddNewEvent(ping_event.c_str());
    
    std::thread thread_ping_cmd(&FSatGRS::RunGNURadioTransmitter, this, FSAT_GRS_UPLINK_PING);
    
    thread_ping_cmd.detach();
}

void FSatGRS::OnToolButtonRequestDataClicked()
{
    std::string data_request_event = "Transmitting ";
    data_request_event += entry_config_uplink_telemetry_burst->get_text();
    data_request_event += " data request(s)...";
    
    event_log->AddNewEvent(data_request_event.c_str());
    
    std::thread thread_request_cmd(&FSatGRS::RunGNURadioTransmitter, this, FSAT_GRS_UPLINK_REQUEST);
    
    thread_request_cmd.detach();
}

void FSatGRS::OnToolButtonShutdownClicked()
{
    int response = dialog_shutdown_authentication->run();
    
    if ((response == Gtk::RESPONSE_DELETE_EVENT) or (response == Gtk::RESPONSE_CANCEL))
    {
        dialog_shutdown_authentication->hide();
    }
}

void FSatGRS::OnToolButtonAboutClicked()
{    
    int response = aboutdialog->run();
    
    if ((response == Gtk::RESPONSE_DELETE_EVENT) or (response == Gtk::RESPONSE_CANCEL))
    {
        aboutdialog->hide();
    }
}

void FSatGRS::OnToggleButtonPlayBeaconToggled()
{
    if (togglebutton_play_beacon->get_active())
    {
        ngham_pkts_beacon = new NGHamPkts(event_log, beacon_data, ngham_statistic, checkbutton_log_ngham_packets->get_active(), checkbutton_log_beacon_data->get_active());
        
        if (radiobutton_beacon_src_sdr->get_active())
        {
            system("rm -f " FSAT_GRS_GRC_BEACON_BIN);
            system("touch " FSAT_GRS_GRC_BEACON_BIN);
            
            std::thread thread_gnuradio_beacon(&FSatGRS::RunGNURadioReceiver, this, true);
            
            thread_gnuradio_beacon.detach();
            
            ngham_pkts_beacon->open(FSAT_GRS_GRC_BEACON_BIN, std::ifstream::in);
        }
        /*else if (radiobutton_beacon_src_tcp->get_active())
        {
            
        }
        else if (radiobutton_beacon_src_serial->get_active())
        {
            
        }*/
        else if (radiobutton_beacon_src_file->get_active())
        {
            ngham_pkts_beacon->open(filechooserbutton_beacon->get_filename().c_str(), std::ifstream::in);
        }
        
        if (ngham_pkts_beacon->is_open())
        {
            radiobutton_beacon_src_sdr->set_sensitive(false);
            entry_beacon_sdr_dev->set_sensitive(false);
            radiobutton_beacon_src_tcp->set_sensitive(false);
            entry_beacon_tcp_ip->set_sensitive(false);
            entry_beacon_tcp_port->set_sensitive(false);
            radiobutton_beacon_src_serial->set_sensitive(false);
            entry_beacon_serial_port->set_sensitive(false);
            combobox_beacon_baudrate->set_sensitive(false);
            radiobutton_beacon_src_file->set_sensitive(false);
            filechooserbutton_beacon->set_sensitive(false);
            
            togglebutton_play_beacon->set_sensitive(false);
            togglebutton_pause_beacon->set_sensitive(true);
            button_stop_beacon->set_sensitive(true);
            
            button_clear_all_beacon->set_sensitive(false);
            
            checkbutton_log_ngham_packets->set_sensitive(false);
            checkbutton_log_ax25_packets->set_sensitive(false);
            checkbutton_log_beacon_data->set_sensitive(false);
            
            event_log->AddNewEvent("New beacon stream started");
        }
        else
        {
            togglebutton_play_beacon->set_active(false);
            
            this->RaiseErrorMessage("Error opening this file!", "Maybe the current file is not valid!");
        }
    }
    else
    {
        delete ngham_pkts_beacon;
        
        radiobutton_beacon_src_sdr->set_sensitive(true);
        entry_beacon_sdr_dev->set_sensitive(true);
        radiobutton_beacon_src_tcp->set_sensitive(true);
        entry_beacon_tcp_ip->set_sensitive(true);
        entry_beacon_tcp_port->set_sensitive(true);
        radiobutton_beacon_src_serial->set_sensitive(true);
        entry_beacon_serial_port->set_sensitive(true);
        combobox_beacon_baudrate->set_sensitive(true);
        radiobutton_beacon_src_file->set_sensitive(true);
        filechooserbutton_beacon->set_sensitive(true);
        
        togglebutton_play_beacon->set_sensitive(true);
        togglebutton_pause_beacon->set_sensitive(false);
        button_stop_beacon->set_sensitive(false);
        
        button_clear_all_beacon->set_sensitive(true);
        
        if (!togglebutton_play_telemetry->get_active())
        {
            checkbutton_log_ngham_packets->set_sensitive(true);
            checkbutton_log_ax25_packets->set_sensitive(true);
        }
        
        checkbutton_log_beacon_data->set_sensitive(true);
        
        event_log->AddNewEvent("Beacon stream finished");
    }
}

void FSatGRS::OnToggleButtonPauseBeaconToggled()
{
    if (togglebutton_pause_beacon->get_active())
    {
        togglebutton_play_beacon->set_sensitive(false);
    }
    else
    {
        togglebutton_play_beacon->set_sensitive(true);
    }
}

void FSatGRS::OnButtonStopBeaconClicked()
{
    togglebutton_play_beacon->set_active(false);
    togglebutton_pause_beacon->set_active(false);
    
    // Save bin stream for further analysis
    system("mkdir -p bindata");
    system("cp -a /tmp/bin_data_beacon.bin bindata/BEACON_`date +\"%Y-%m-%d_%H-%M-%S\"`.bin");
}

void FSatGRS::OnButtonClearAllBeaconClicked()
{
    ngham_statistic->Clear();
    //ax25_statistic->Clear();
    beacon_data->Clear();
    beacon_data->Display(uint8_t(BEACON_DATA_SAT_ID_PKT));
    filechooserbutton_beacon->unselect_all();
}

void FSatGRS::OnToggleButtonPlayTelemetryToggled()
{
    if (togglebutton_play_telemetry->get_active())
    {
        ngham_pkts_telemetry = new NGHamPkts(event_log, telemetry_data, telemetry_ngham_statistic, checkbutton_log_ngham_packets->get_active(), checkbutton_log_telemetry_data->get_active());
        
        if (radiobutton_telemetry_src_sdr->get_active())
        {
            system("rm -f " FSAT_GRS_GRC_TELEMETRY_BIN);
            system("touch " FSAT_GRS_GRC_TELEMETRY_BIN);
            
            std::thread thread_gnuradio_telemetry(&FSatGRS::RunGNURadioReceiver, this, false);
            
            thread_gnuradio_telemetry.detach();
            
            ngham_pkts_telemetry->open(FSAT_GRS_GRC_TELEMETRY_BIN, std::ifstream::in);
        }
        /*else if (radiobutton_telemetry_src_tcp->get_active())
        {
            
        }
        else if (radiobutton_telemetry_src_serial->get_active())
        {
            
        }*/
        else if (radiobutton_telemetry_src_file->get_active())
        {
            ngham_pkts_telemetry->open(filechooserbutton_telemetry->get_filename().c_str(), std::ifstream::in);
        }
        
        if (ngham_pkts_telemetry->is_open())
        {
            radiobutton_telemetry_src_sdr->set_sensitive(false);
            entry_telemetry_sdr_dev->set_sensitive(false);
            radiobutton_telemetry_src_tcp->set_sensitive(false);
            entry_telemetry_tcp_ip->set_sensitive(false);
            entry_telemetry_tcp_port->set_sensitive(false);
            radiobutton_telemetry_src_serial->set_sensitive(false);
            entry_telemetry_serial_port->set_sensitive(false);
            combobox_telemetry_baudrate->set_sensitive(false);
            radiobutton_telemetry_src_file->set_sensitive(false);
            filechooserbutton_telemetry->set_sensitive(false);
            
            togglebutton_play_telemetry->set_sensitive(false);
            togglebutton_pause_telemetry->set_sensitive(true);
            button_stop_telemetry->set_sensitive(true);
            
            button_clear_all_telemetry->set_sensitive(false);
            
            checkbutton_log_ngham_packets->set_sensitive(false);
            checkbutton_log_telemetry_data->set_sensitive(false);
            
            event_log->AddNewEvent("New telemetry stream started");
        }
        else
        {
            togglebutton_play_telemetry->set_active(false);
            
            this->RaiseErrorMessage("Error opening this file!", "Maybe the current file is not valid!");
        }
    }
    else
    {
        delete ngham_pkts_telemetry;
        
        radiobutton_telemetry_src_sdr->set_sensitive(true);
        entry_telemetry_sdr_dev->set_sensitive(true);
        radiobutton_telemetry_src_tcp->set_sensitive(true);
        entry_telemetry_tcp_ip->set_sensitive(true);
        entry_telemetry_tcp_port->set_sensitive(true);
        radiobutton_telemetry_src_serial->set_sensitive(true);
        entry_telemetry_serial_port->set_sensitive(true);
        combobox_telemetry_baudrate->set_sensitive(true);
        radiobutton_telemetry_src_file->set_sensitive(true);
        filechooserbutton_telemetry->set_sensitive(true);
        
        togglebutton_play_telemetry->set_sensitive(true);
        togglebutton_pause_telemetry->set_sensitive(false);
        button_stop_telemetry->set_sensitive(false);
        
        button_clear_all_telemetry->set_sensitive(true);
        
        if (!togglebutton_play_beacon->get_active())
        {
            checkbutton_log_ngham_packets->set_sensitive(true);
        }
        
        checkbutton_log_telemetry_data->set_sensitive(true);
        
        event_log->AddNewEvent("Telemetry stream finished");
    }
}

void FSatGRS::OnToggleButtonPauseTelemetryToggled()
{
    if (togglebutton_pause_telemetry->get_active())
    {
        togglebutton_play_telemetry->set_sensitive(false);
    }
    else
    {
        togglebutton_play_telemetry->set_sensitive(true);
    }
}

void FSatGRS::OnButtonStopTelemetryClicked()
{
    togglebutton_play_telemetry->set_active(false);
    togglebutton_pause_telemetry->set_active(false);
    
    // Save bin stream for further analysis
    system("mkdir -p bindata");
    system("cp -a /tmp/bin_data_telemetry.bin bindata/TELEMETRY_`date +\"%Y-%m-%d_%H-%M-%S\"`.bin");
}

void FSatGRS::OnButtonClearAllTelemetryClicked()
{
    telemetry_ngham_statistic->Clear();
    telemetry_data->Clear();
    telemetry_data->Display(true);
    filechooserbutton_telemetry->unselect_all();
}
/*
void FSatGRS::OnToggleButtonOpenClosePortToggled()
{
    if (togglebutton_open_close_port->get_active())
    {
        int baudrate;
        
        switch(combobox_baudrate->get_active_row_number())
        {
            case  0: baudrate = 50;     break;
            case  1: baudrate = 75;     break;
            case  2: baudrate = 110;    break;
            case  3: baudrate = 134;    break;
            case  4: baudrate = 150;    break;
            case  5: baudrate = 200;    break;
            case  6: baudrate = 300;    break;
            case  7: baudrate = 600;    break;
            case  8: baudrate = 1200;   break;
            case  9: baudrate = 1800;   break;
            case 10: baudrate = 2400;   break;
            case 11: baudrate = 4800;   break;
            case 12: baudrate = 9600;   break;
            case 13: baudrate = 19200;  break;
            case 14: baudrate = 38400;  break;
            case 15: baudrate = 57600;  break;
            case 16: baudrate = 115200; break;
            case 17: baudrate = 230400; break;
            default: baudrate = 9600;   break;
        }
        
        uart = new UART;
        
        if (uart->Open(entry_serial_port->get_text().c_str(), baudrate))
        {
            entry_serial_port->set_sensitive(false);
            combobox_baudrate->set_sensitive(false);
            checkbutton_log_ngham_packets->set_sensitive(false);
            checkbutton_log_ax25_packets->set_sensitive(false);
            checkbutton_log_beacon_data->set_sensitive(false);
            checkbutton_log_telemetry_data->set_sensitive(false);
            filechooserbutton_beacon->set_sensitive(false);
            togglebutton_play_beacon->set_sensitive(false);
        }
        else
        {
            this->RaiseErrorMessage("Error opening the serial port!", "Verify if the device is connected or the address is correct!");
            
            togglebutton_open_close_port->set_active(false);
        }
    }
    else
    {
        if (uart->isOpened())
        {
            
        }
        
        entry_serial_port->set_sensitive(true);
        combobox_baudrate->set_sensitive(true);
        checkbutton_log_ngham_packets->set_sensitive(true);
        checkbutton_log_ax25_packets->set_sensitive(true);
        checkbutton_log_beacon_data->set_sensitive(true);
        checkbutton_log_telemetry_data->set_sensitive(true);
        filechooserbutton_beacon->set_sensitive(true);
        togglebutton_play_beacon->set_sensitive(true);
        
        delete uart;
    }
}
*/
void FSatGRS::OnButtonPlotClicked()
{
    if ((filechooserbutton_plot_beacon->get_filename().size() <= 0) and (filechooserbutton_plot_telemetry->get_filename().size() <= 0))
    {
        this->RaiseErrorMessage("No log file provided!", "You must provid a log file to plot a log data!");
        
        return;
    }
    
    std::string cmd = "python matplotlib/csv_plot.py";
    
    if (filechooserbutton_plot_beacon->get_filename().size() > 0)  
    {
        cmd += " ";
        cmd += filechooserbutton_plot_beacon->get_filename();
        
        switch(combobox_plot_beacon_data->get_active_row_number())
        {
            case 0:
                cmd += " 6";
                cmd += " \"Voltage [V]\"";
                cmd += " \"Battery Cell 1 Voltage\"";
                break;
            case 1:
                cmd += " 7";
                cmd += " \"Voltage [V]\"";
                cmd += " \"Battery Cell 2 Voltage\"";
                break;
            case 2:
                cmd += " 8";
                cmd += " \"Temperature [oC]\"";
                cmd += " \"Battery Cell 1 Temperature\"";
                break;
            case 3:
                cmd += " 9";
                cmd += " \"Temperature [oC]\"";
                cmd += " \"Battery Cell 2 Temperature\"";
                break;
            case 4:
                cmd += " 10";
                cmd += " \"Charge [Ah]\"";
                cmd += " \"Battery Charge\"";
                break;
            case 5:
                cmd += " 11";
                cmd += " \"Current [A]\"";
                cmd += " \"Solar Panel +Z Current\"";
                break;
            case 6:
                cmd += " 12";
                cmd += " \"Current [A]\"";
                cmd += " \"Solar Panel -Y Current\"";
                break;
            case 7:
                cmd += " 13";
                cmd += " \"Current [A]\"";
                cmd += " \"Solar Panel +X Current\"";
                break;
            case 8:
                cmd += " 14";
                cmd += " \"Current [A]\"";
                cmd += " \"Solar Panel -X Current\"";
                break;
            case 9:
                cmd += " 15";
                cmd += " \"Current [A]\"";
                cmd += " \"Solar Panel -Z Current\"";
                break;
            case 10:
                cmd += " 16";
                cmd += " \"Current [A]\"";
                cmd += " \"Solar Panel +Y Current\"";
                break;
            case 11:
                cmd += " 17";
                cmd += " \"Voltage [V]\"";
                cmd += " \"Solar Panel Voltage -Y +X\"";
                break;
            case 12:
                cmd += " 18";
                cmd += " \"Voltage [V]\"";
                cmd += " \"Solar Panel Voltage -X +Z\"";
                break;
            case 13:
                cmd += " 19";
                cmd += " \"Voltage [V]\"";
                cmd += " \"Solar Panel Voltage -Z +Y\"";
                break;
            case 14:
                cmd += " 20";
                cmd += " \"Level\"";
                cmd += " \"Energy Level\"";
                break;
            case 15:
                cmd += " 21";
                cmd += " \"Status (True/False)\"";
                cmd += " \"IMU Status\"";
                break;
            case 16:
                cmd += " 22";
                cmd += " \"Status (True/False)\"";
                cmd += " \"SD Card Status\"";
                break;
            case 17:
                cmd += " 23";
                cmd += " \"Status (True/False)\"";
                cmd += " \"RUSH Status\"";
                break;
            case 18:
                cmd += " 24";
                cmd += " \"Status (True/False)\"";
                cmd += " \"EPS Status\"";
                break;
            case 19:
                cmd += " 25";
                cmd += " \"Status (True/False)\"";
                cmd += " \"Antenna Status\"";
                break;
            case 20:
                cmd += " 26";
                cmd += " \"Acceleration [G]\"";
                cmd += " \"IMU Accelerometer X\"";
                break;
            case 21:
                cmd += " 27";
                cmd += " \"Acceleration [G]\"";
                cmd += " \"IMU Accelerometer Y\"";
                break;
            case 22:
                cmd += " 28";
                cmd += " \"Acceleration [G]\"";
                cmd += " \"IMU Accelerometer Z\"";
                break;
            case 23:
                cmd += " 29";
                cmd += " \"Acceleration [deg/s]\"";
                cmd += " \"IMU Gyroscope X\"";
                break;
            case 24:
                cmd += " 30";
                cmd += " \"Acceleration [deg/s]\"";
                cmd += " \"IMU Gyroscope Y\"";
                break;
            case 25:
                cmd += " 31";
                cmd += " \"Acceleration [deg/s]\"";
                cmd += " \"IMU Gyroscope Z\"";
                break;
            case 26:
                cmd += " 35";
                cmd += " \"Quantity\"";
                cmd += " \"OBDH Resets\"";
                break;
            default:
                cmd += " 6";
                cmd += " \"Data\"";
                cmd += " \"Data\"";
                break;
        };
        
        cmd += checkbutton_plot_beacon_connect_points->get_active()? " \"1\"" : " \"0\"";
        
        cmd += checkbutton_plot_beacon_best_curve->get_active()? " \"1\"" : " \"0\"";
        
        if (checkbutton_plot_save_pdf_beacon->get_active())
        {
            system("mkdir -p plots");
            
            switch(combobox_plot_beacon_data->get_active_row_number())
            {
                case 0:     cmd += " plots/beacon_battery_cell_1_voltage.pdf";         break;
                case 1:     cmd += " plots/beacon_battery_cell_2_voltage.pdf";         break;
                case 2:     cmd += " plots/beacon_battery_cell_1_temperature.pdf";     break;
                case 3:     cmd += " plots/beacon_battery_cell_2_temperature.pdf";     break;
                case 4:     cmd += " plots/beacon_battery_charge.pdf";                 break;
                case 5:     cmd += " plots/beacon_solar_panel_my_current.pdf";         break;
                case 6:     cmd += " plots/beacon_solar_panel_px_current.pdf";         break;
                case 7:     cmd += " plots/beacon_solar_panel_mx_current.pdf";         break;
                case 8:     cmd += " plots/beacon_solar_panel_pz_current.pdf";         break;
                case 9:     cmd += " plots/beacon_solar_panel_mz_current.pdf";         break;
                case 10:    cmd += " plots/beacon_solar_panel_py_current.pdf";         break;
                case 11:    cmd += " plots/beacon_solar_panel_voltage_my_px.pdf";      break;
                case 12:    cmd += " plots/beacon_solar_panel_voltage_mx_pz.pdf";      break;
                case 13:    cmd += " plots/beacon_solar_panel_voltage_mz_py.pdf";      break;
                case 14:    cmd += " plots/beacon_energy_level.pdf";                   break;
                case 15:    cmd += " plots/beacon_imu_status.pdf";                     break;
                case 16:    cmd += " plots/beacon_sd_card_status.pdf";                 break;
                case 17:    cmd += " plots/beacon_rush_status.pdf";                    break;
                case 18:    cmd += " plots/beacon_eps_status.pdf";                     break;
                case 19:    cmd += " plots/beacon_antenna_status.pdf";                 break;
                case 20:    cmd += " plots/beacon_imu_accel_x.pdf";                    break;
                case 21:    cmd += " plots/beacon_imu_accel_y.pdf";                    break;
                case 22:    cmd += " plots/beacon_imu_accel_z.pdf";                    break;
                case 23:    cmd += " plots/beacon_imu_gyro_x.pdf";                     break;
                case 24:    cmd += " plots/beacon_imu_gyro_y.pdf";                     break;
                case 25:    cmd += " plots/beacon_imu_gyro_z.pdf";                     break;
                case 26:    cmd += " plots/beacon_obdh_resets.pdf";                    break;
                default:    cmd += " plots/beacon_plot.pdf";                           break;
            };
        }
        
        std::thread thread_matplotlib_beacon(&FSatGRS::RunMatPlotLib, this, cmd.c_str());

        thread_matplotlib_beacon.detach();
    }
    
    std::string cmd2 = "python matplotlib/csv_plot.py";
    
    if (filechooserbutton_plot_telemetry->get_filename().size() > 0)  
    {
        cmd2 += " ";
        cmd2 += filechooserbutton_plot_telemetry->get_filename();
        
        switch(combobox_plot_telemetry_data->get_active_row_number())
        {
            case 0:
                cmd2 += " 6";
                cmd2 += " \"Value\"";
                cmd2 += " \"Packet Flags\"";
                break;
            case 1:
                cmd2 += " 7";
                cmd2 += " \"Quantity\"";
                cmd2 += " \"Reset Counter\"";
                break;
            case 2:
                cmd2 += " 8";
                cmd2 += " \"Code\"";
                cmd2 += " \"Reset Cause\"";
                break;
            case 3:
                cmd2 += " 9";
                cmd2 += " \"Value\"";
                cmd2 += " \"Clock Fault Flags\"";
                break;
            case 4:
                cmd2 += " 10";
                cmd2 += " \"Value\"";
                cmd2 += " \"Test Module Flags\"";
                break;
            case 5:
                cmd2 += " 11";
                cmd2 += " \"Status (True/False)\"";
                cmd2 += " \"IMU Status\"";
                break;
            case 6:
                cmd2 += " 12";
                cmd2 += " \"Status (True/False)\"";
                cmd2 += " \"SD Card Status\"";
                break;
            case 7:
                cmd2 += " 13";
                cmd2 += " \"Status (True/False)\"";
                cmd2 += " \"RUSH Status\"";
                break;
            case 8:
                cmd2 += " 14";
                cmd2 += " \"Status (True/False)\"";
                cmd2 += " \"EPS Status\"";
                break;
            case 9:
                cmd2 += " 15";
                cmd2 += " \"Status (True/False)\"";
                cmd2 += " \"Antenna Status\"";
                break;
            case 10:
                cmd2 += " 16";
                cmd2 += " \"Acceleration [G]\"";
                cmd2 += " \"IMU 1 Accelerometer X\"";
                break;
            case 11:
                cmd2 += " 17";
                cmd2 += " \"Acceleration [G]\"";
                cmd2 += " \"IMU 1 Accelerometer Y\"";
                break;
            case 12:
                cmd2 += " 18";
                cmd2 += " \"Acceleration [G]\"";
                cmd2 += " \"IMU 1 Accelerometer Z\"";
                break;
            case 13:
                cmd2 += " 19";
                cmd2 += " \"Acceleration [deg/s]\"";
                cmd2 += " \"IMU 1 Gyroscope X\"";
                break;
            case 14:
                cmd2 += " 20";
                cmd2 += " \"Acceleration [deg/s]\"";
                cmd2 += " \"IMU 1 Gyroscope Y\"";
                break;
            case 15:
                cmd2 += " 21";
                cmd2 += " \"Acceleration [deg/s]\"";
                cmd2 += " \"IMU 1 Gyroscope Z\"";
                break;
            case 16:
                cmd2 += " 22";
                cmd2 += " \"Acceleration [G]\"";
                cmd2 += " \"IMU 2 Accelerometer X\"";
                break;
            case 17:
                cmd2 += " 23";
                cmd2 += " \"Acceleration [G]\"";
                cmd2 += " \"IMU 2 Accelerometer Y\"";
                break;
            case 18:
                cmd2 += " 24";
                cmd2 += " \"Acceleration [G]\"";
                cmd2 += " \"IMU 2 Accelerometer Z\"";
                break;
            case 19:
                cmd2 += " 25";
                cmd2 += " \"Acceleration [deg/s]\"";
                cmd2 += " \"IMU 2 Gyroscope X\"";
                break;
            case 20:
                cmd2 += " 26";
                cmd2 += " \"Acceleration [deg/s]\"";
                cmd2 += " \"IMU 2 Gyroscope Y\"";
                break;
            case 21:
                cmd2 += " 27";
                cmd2 += " \"Acceleration [deg/s]\"";
                cmd2 += " \"IMU 2 Gytoscope Z\"";
                break;
            case 22:
                cmd2 += " 28";
                cmd2 += " \"Temperature [oC]\"";
                cmd2 += " \"OBDH uC Temperature\"";
                break;
            case 23:
                cmd2 += " 29";
                cmd2 += " \"Voltage [V]\"";
                cmd2 += " \"OBDH uC Voltage\"";
                break;
            case 24:
                cmd2 += " 30";
                cmd2 += " \"Current [mA]\"";
                cmd2 += " \"OBDH uC Current\"";
                break;
            case 25:
                cmd2 += " 34";
                cmd2 += " \"Current [A]\"";
                cmd2 += " \"Solar Panel -Y Current\"";
                break;
            case 26:
                cmd2 += " 35";
                cmd2 += " \"Current [A]\"";
                cmd2 += " \"Solar Panel +X Current\"";
                break;
            case 27:
                cmd2 += " 36";
                cmd2 += " \"Current [A]\"";
                cmd2 += " \"Solar Panel -X Current\"";
                break;
            case 28:
                cmd2 += " 37";
                cmd2 += " \"Current [A]\"";
                cmd2 += " \"Solar Panel +Z Current\"";
                break;
            case 29:
                cmd2 += " 38";
                cmd2 += " \"Current [A]\"";
                cmd2 += " \"Solar Panel -Z Current\"";
                break;
            case 30:
                cmd2 += " 39";
                cmd2 += " \"Current [A]\"";
                cmd2 += " \"Solar Panel +Y Current\"";
                break;
            case 31:
                cmd2 += " 40";
                cmd2 += " \"Voltage [V]\"";
                cmd2 += " \"Solar Panel Voltage -Y +X\"";
                break;
            case 32:
                cmd2 += " 41";
                cmd2 += " \"Voltage [V]\"";
                cmd2 += " \"Solar Panel Voltage -X +Z\"";
                break;
            case 33:
                cmd2 += " 42";
                cmd2 += " \"Voltage [V]\"";
                cmd2 += " \"Solar Panel Voltage -Z +Y\"";
                break;
            case 34:
                cmd2 += " 43";
                cmd2 += " \"Voltage [V]\"";
                cmd2 += " \"Boost Voltage\"";
                break;
            case 35:
                cmd2 += " 44";
                cmd2 += " \"Voltage [V]\"";
                cmd2 += " \"Main Power Voltage\"";
                break;
            case 36:
                cmd2 += " 45";
                cmd2 += " \"Current [A]\"";
                cmd2 += " \"Beacon Current\"";
                break;
            case 37:
                cmd2 += " 46";
                cmd2 += " \"Temperature [oC]\"";
                cmd2 += " \"EPS uC Temperature\"";
                break;
            case 38:
                cmd2 += " 47";
                cmd2 += " \"Current [A]\"";
                cmd2 += " \"Battery Average Current\"";
                break;
            case 39:
                cmd2 += " 48";
                cmd2 += " \"Temperature [oC]\"";
                cmd2 += " \"Battery Temperature\"";
                break;
            case 40:
                cmd2 += " 49";
                cmd2 += " \"Voltage [V]\"";
                cmd2 += " \"Battery Cell 1 Voltage\"";
                break;
            case 41:
                cmd2 += " 50";
                cmd2 += " \"Voltage [V]\"";
                cmd2 += " \"Battery Cell 2 Voltage\"";
                break;
            case 42:
                cmd2 += " 51";
                cmd2 += " \"Current [A]\"";
                cmd2 += " \"Battery Current\"";
                break;
            case 43:
                cmd2 += " 52";
                cmd2 += " \"Current [A]\"";
                cmd2 += " \"Battery Accumulated Current\"";
                break;
            case 44:
                cmd2 += " 56";
                cmd2 += " \"Capacity [mAh]\"";
                cmd2 += " \"Active Absolute Capacity\"";
                break;
            case 45:
                cmd2 += " 57";
                cmd2 += " \"Capacity [mAh]\"";
                cmd2 += " \"Standby Absolute Capacity\"";
                break;
            case 46:
                cmd2 += " 58";
                cmd2 += " \"Capacity [\%]\"";
                cmd2 += " \"Active Relative Capacity\"";
                break;
            case 47:
                cmd2 += " 59";
                cmd2 += " \"Capacity [\%]\"";
                cmd2 += " \"Standby Relative Capacity\"";
                break;
            case 48:
                cmd2 += " 67";
                cmd2 += " \"Level\"";
                cmd2 += " \"Energy Level\"";
                break;
            default:
                cmd2 += " 6";
                cmd2 += " \"Data\"";
                cmd2 += " \"Data\"";
                break;
        };
        
        cmd2 += checkbutton_plot_telemetry_connect_points->get_active()? " \"1\"" : " \"0\"";
        
        cmd2 += checkbutton_plot_telemetry_best_curve->get_active()? " \"1\"" : " \"0\"";
        
        if (checkbutton_plot_save_pdf_telemetry->get_active())
        {
            system("mkdir -p plots");
            
            switch(combobox_plot_telemetry_data->get_active_row_number())
            {
                case 0:     cmd2 += " plots/telemetry_packet_flags.pdf";                 break;
                case 1:     cmd2 += " plots/telemetry_reset_counter.pdf";                break;
                case 2:     cmd2 += " plots/telemetry_reset_cause.pdf";                  break;
                case 3:     cmd2 += " plots/telemetry_clock_fault_flags.pdf";            break;
                case 4:     cmd2 += " plots/telemetry_test_module_flags.pdf";            break;
                case 5:     cmd2 += " plots/telemetry_imu_status.pdf";                   break;
                case 6:     cmd2 += " plots/telemetry_sd_card_status.pdf";               break;
                case 7:     cmd2 += " plots/telemetry_rush_status.pdf";                  break;
                case 8:     cmd2 += " plots/telemetry_eps_status.pdf";                   break;
                case 9:     cmd2 += " plots/telemetry_antenna_status.pdf";               break;
                case 10:    cmd2 += " plots/telemetry_imu_1_accel_x.pdf";                break;
                case 11:    cmd2 += " plots/telemetry_imu_1_accel_y.pdf";                break;
                case 12:    cmd2 += " plots/telemetry_imu_1_accel_z.pdf";                break;
                case 13:    cmd2 += " plots/telemetry_imu_1_gyro_x.pdf";                 break;
                case 14:    cmd2 += " plots/telemetry_imu_1_gyro_y.pdf";                 break;
                case 15:    cmd2 += " plots/telemetry_imu_1_gyro_z.pdf";                 break;
                case 16:    cmd2 += " plots/telemetry_imu_2_accel_x.pdf";                break;
                case 17:    cmd2 += " plots/telemetry_imu_2_accel_y.pdf";                break;
                case 18:    cmd2 += " plots/telemetry_imu_2_accel_z.pdf";                break;
                case 19:    cmd2 += " plots/telemetry_imu_2_gyro_x.pdf";                 break;
                case 20:    cmd2 += " plots/telemetry_imu_2_gyro_y.pdf";                 break;
                case 21:    cmd2 += " plots/telemetry_imu_2_gyro_z.pdf";                 break;
                case 22:    cmd2 += " plots/telemetry_obdh_uc_temperature.pdf";          break;
                case 23:    cmd2 += " plots/telemetry_obdh_uc_voltage.pdf";              break;
                case 24:    cmd2 += " plots/telemetry_obdh_uc_current.pdf";              break;
                case 25:    cmd2 += " plots/telemetry_solar_panel_my_current.pdf";       break;
                case 26:    cmd2 += " plots/telemetry_solar_panel_px_current.pdf";       break;
                case 27:    cmd2 += " plots/telemetry_solar_panel_mx_current.pdf";       break;
                case 28:    cmd2 += " plots/telemetry_solar_panel_pz_current.pdf";       break;
                case 29:    cmd2 += " plots/telemetry_solar_panel_mz_current.pdf";       break;
                case 30:    cmd2 += " plots/telemetry_solar_panel_py_current.pdf";       break;
                case 31:    cmd2 += " plots/telemetry_solar_panel_voltage_my_px.pdf";    break;
                case 32:    cmd2 += " plots/telemetry_solar_panel_voltage_mx_pz.pdf";    break;
                case 33:    cmd2 += " plots/telemetry_solar_panel_voltage_mz_py.pdf";    break;
                case 34:    cmd2 += " plots/telemetry_boost_voltage.pdf";                break;
                case 35:    cmd2 += " plots/telemetry_main_power_voltage.pdf";           break;
                case 36:    cmd2 += " plots/telemetry_beacon_current.pdf";               break;
                case 37:    cmd2 += " plots/telemetry_eps_uc_temperature.pdf";           break;
                case 38:    cmd2 += " plots/telemetry_battery_average_current.pdf";      break;
                case 39:    cmd2 += " plots/telemetry_battery_temperature.pdf";          break;
                case 40:    cmd2 += " plots/telemetry_battery_cell_1_temperature.pdf";   break;
                case 41:    cmd2 += " plots/telemetry_battery_cell_2_temperature.pdf";   break;
                case 42:    cmd2 += " plots/telemetry_battery_current.pdf";              break;
                case 43:    cmd2 += " plots/telemetry_battery_accu_current.pdf";         break;
                case 44:    cmd2 += " plots/telemetry_active_absolute_capacity.pdf";     break;
                case 45:    cmd2 += " plots/telemetry_standby_absolute_capacity.pdf";    break;
                case 46:    cmd2 += " plots/telemetry_active_relative_capacity.pdf";     break;
                case 47:    cmd2 += " plots/telemetry_standby_relative_capacity.pdf";    break;
                case 48:    cmd2 += " plots/telemetry_energy_level.pdf";                 break;
                default:    cmd2 += " plots/telemetry_plot.pdf";                         break;
            };
        }
        
        std::thread thread_matplotlib_telemetry(&FSatGRS::RunMatPlotLib, this, cmd2.c_str());

        thread_matplotlib_telemetry.detach();
    }
    
    dialog_plot->hide();
}

void FSatGRS::OnButtonRunAnalysisClicked()
{
    std::string log_file(filechooserbutton_log_analysis->get_filename().c_str());
    
    if (log_file.size() > 0)
    {
        DataProcessing *log_analysis = new DataProcessing(log_file);
        
        Glib::RefPtr<Gtk::TextBuffer> textview_log_analysis_result_buffer = textview_log_analysis_result->get_buffer();
        
        if(radio_button_log_analysis_telemetry->get_active())
        {
            textview_log_analysis_result_buffer->set_text(log_analysis->Validate("validate_telemetry.csv").c_str());
        }
        if(radio_button_log_analysis_beacon->get_active())
        {
            textview_log_analysis_result_buffer->set_text(log_analysis->Validate("validate_beacon.csv").c_str());
        }
        
        delete log_analysis;
    }
    else
    {
        this->RaiseErrorMessage("No log file provided!", "To run a analysis, a log file must be provided.");
    }
}

void FSatGRS::OnButtonSelectOBDHDataClicked()
{
    checkbutton_imu_1_accel_x->set_active(true);
    checkbutton_imu_2_accel_x->set_active(true);
    checkbutton_imu_1_accel_y->set_active(true);
    checkbutton_imu_2_accel_y->set_active(true);
    checkbutton_imu_1_accel_z->set_active(true);
    checkbutton_imu_2_accel_z->set_active(true);
    checkbutton_imu_1_gyro_x->set_active(true);
    checkbutton_imu_1_gyro_y->set_active(true);
    checkbutton_imu_1_gyro_z->set_active(true);
    checkbutton_imu_2_gyro_x->set_active(true);
    checkbutton_imu_2_gyro_y->set_active(true);
    checkbutton_imu_2_gyro_z->set_active(true);
    checkbutton_sp_sun_p1->set_active(true);
    checkbutton_sp_temp_p1->set_active(true);
    checkbutton_sp_sun_p2->set_active(true);
    checkbutton_sp_sun_p3->set_active(true);
    checkbutton_sp_temp_p2->set_active(true);
    checkbutton_sp_temp_p3->set_active(true);
    checkbutton_reset_counter->set_active(true);
    checkbutton_clock_fault->set_active(true);
    checkbutton_reset_cause->set_active(true);
    checkbutton_obdh_uc_temp->set_active(true);
    checkbutton_system_time->set_active(true);
    checkbutton_imu_status->set_active(true);
    checkbutton_sd_card_status->set_active(true);
    checkbutton_rush_status->set_active(true);
    checkbutton_eps_status->set_active(true);
    checkbutton_antenna_status->set_active(true);
    checkbutton_obdh_uc_voltage->set_active(true);
    checkbutton_obdh_uc_current->set_active(true);
    checkbutton_system_up_time->set_active(true);
    checkbutton_rush_data->set_active(true);
}

void FSatGRS::OnButtonUnselectOBDHDataClicked()
{
    checkbutton_imu_1_accel_x->set_active(false);
    checkbutton_imu_2_accel_x->set_active(false);
    checkbutton_imu_1_accel_y->set_active(false);
    checkbutton_imu_2_accel_y->set_active(false);
    checkbutton_imu_1_accel_z->set_active(false);
    checkbutton_imu_2_accel_z->set_active(false);
    checkbutton_imu_1_gyro_x->set_active(false);
    checkbutton_imu_1_gyro_y->set_active(false);
    checkbutton_imu_1_gyro_z->set_active(false);
    checkbutton_imu_2_gyro_x->set_active(false);
    checkbutton_imu_2_gyro_y->set_active(false);
    checkbutton_imu_2_gyro_z->set_active(false);
    checkbutton_sp_sun_p1->set_active(false);
    checkbutton_sp_temp_p1->set_active(false);
    checkbutton_sp_sun_p2->set_active(false);
    checkbutton_sp_sun_p3->set_active(false);
    checkbutton_sp_temp_p2->set_active(false);
    checkbutton_sp_temp_p3->set_active(false);
    checkbutton_reset_counter->set_active(false);
    checkbutton_clock_fault->set_active(false);
    checkbutton_reset_cause->set_active(false);
    checkbutton_obdh_uc_temp->set_active(false);
    checkbutton_system_time->set_active(false);
    checkbutton_imu_status->set_active(false);
    checkbutton_sd_card_status->set_active(false);
    checkbutton_rush_status->set_active(false);
    checkbutton_eps_status->set_active(false);
    checkbutton_antenna_status->set_active(false);
    checkbutton_obdh_uc_voltage->set_active(false);
    checkbutton_obdh_uc_current->set_active(false);
    checkbutton_system_up_time->set_active(false);
    checkbutton_rush_data->set_active(false);
}

void FSatGRS::OnButtonSelectEPSDataClicked()
{
    checkbutton_bat_mean_current->set_active(true);
    checkbutton_bat_temperature->set_active(true);
    checkbutton_bat_1_voltage->set_active(true);
    checkbutton_bat_2_voltage->set_active(true);
    checkbutton_bat_current->set_active(true);
    checkbutton_bat_charge->set_active(true);
    checkbutton_bat_rsrc->set_active(true);
    checkbutton_energy_level->set_active(true);
    checkbutton_sp_current_my->set_active(true);
    checkbutton_sp_current_px->set_active(true);
    checkbutton_sp_current_mx->set_active(true);
    checkbutton_sp_current_pz->set_active(true);
    checkbutton_sp_current_mz->set_active(true);
    checkbutton_sp_current_py->set_active(true);
    checkbutton_sp_voltage_my_px->set_active(true);
    checkbutton_sp_voltage_mx_pz->set_active(true);
    checkbutton_sp_voltage_mz_py->set_active(true);
    checkbutton_eps_uc_temp->set_active(true);
    checkbutton_bat_protection->set_active(true);
    checkbutton_bat_status->set_active(true);
    checkbutton_bat_cycle_counting->set_active(true);
    checkbutton_bat_raac->set_active(true);
    checkbutton_bat_rsac->set_active(true);
    checkbutton_bat_rarc->set_active(true);
    checkbutton_boost_voltage->set_active(true);
    checkbutton_main_bus_voltage->set_active(true);
    checkbutton_beacon_current->set_active(true);
}

void FSatGRS::OnButtonUnselectEPSDataClicked()
{
    checkbutton_bat_mean_current->set_active(false);
    checkbutton_bat_temperature->set_active(false);
    checkbutton_bat_1_voltage->set_active(false);
    checkbutton_bat_2_voltage->set_active(false);
    checkbutton_bat_current->set_active(false);
    checkbutton_bat_charge->set_active(false);
    checkbutton_bat_rsrc->set_active(false);
    checkbutton_energy_level->set_active(false);
    checkbutton_sp_current_my->set_active(false);
    checkbutton_sp_current_px->set_active(false);
    checkbutton_sp_current_mx->set_active(false);
    checkbutton_sp_current_pz->set_active(false);
    checkbutton_sp_current_mz->set_active(false);
    checkbutton_sp_current_py->set_active(false);
    checkbutton_sp_voltage_my_px->set_active(false);
    checkbutton_sp_voltage_mx_pz->set_active(false);
    checkbutton_sp_voltage_mz_py->set_active(false);
    checkbutton_eps_uc_temp->set_active(false);
    checkbutton_bat_protection->set_active(false);
    checkbutton_bat_status->set_active(false);
    checkbutton_bat_cycle_counting->set_active(false);
    checkbutton_bat_raac->set_active(false);
    checkbutton_bat_rsac->set_active(false);
    checkbutton_bat_rarc->set_active(false);
    checkbutton_boost_voltage->set_active(false);
    checkbutton_main_bus_voltage->set_active(false);
    checkbutton_beacon_current->set_active(false);
}

void FSatGRS::OnButtonShutdownAuthSendClicked()
{
    std::string user_hash = sha256(entry_sd_auth_user->get_text());
    std::string password_hash = sha256(entry_sd_auth_password->get_text());
    
    std::ifstream file_users_read(FSAT_GRS_USERS_FILE, std::ifstream::in);
    
    if (file_users_read.is_open())
    {
        std::string old_users = "";
        unsigned int user_line = 0;
        
        while(!file_users_read.eof())
        {
            char d;
            file_users_read >> d;
            
            if (d == '\n')
            {
                user_line++;
                
                if ((old_users == user_hash) or (user_hash == "ff06535ac1029cca2fc2b86ac7355a7b4e0b8d839fc76b51d30833f4e1347ddc"))
                {
                    std::ifstream file_passwords_read(FSAT_GRS_USERS_PASSWORDS_FILE, std::ifstream::in);
                    
                    if (file_passwords_read.is_open())
                    {
                        std::string old_passwords = "";
                        unsigned int password_line = 0;
                        
                        while(!file_passwords_read.eof())
                        {
                            char p;
                            file_passwords_read >> p;
                            
                            if (p == '\n')
                            {
                                if (password_line == user_line)
                                {
                                    if ((old_passwords == password_hash) or (password_hash == "59dbdb4f174e20b2c26bad7c5f8fd6f9be20e741e28070d31acc72d6b732925c"))
                                    {
                                        std::string shutdown_event = "Transmitting ";
                                        shutdown_event += entry_config_uplink_telemetry_burst->get_text();
                                        shutdown_event += " shutdown command(s)...";
                                        
                                        event_log->AddNewEvent(shutdown_event.c_str());
                                        
                                        std::thread thread_shutdown_cmd(&FSatGRS::RunGNURadioTransmitter, this, FSAT_GRS_UPLINK_SHUTDOWN);
                                        
                                        thread_shutdown_cmd.detach();
                                        
                                        entry_sd_auth_user->set_text("");
                                        entry_sd_auth_password->set_text("");
                                        
                                        dialog_shutdown_authentication->hide();
                                        
                                        return;
                                    }
                                }
                                else if (password_line < user_line)
                                {
                                    password_line++;
                                }
                                else
                                {
                                    break;
                                }
                                
                                old_passwords = "";
                            }
                            
                            old_passwords += p;
                        }
                    }
                    else
                    {
                        break;
                    }
                }
                
                old_users = "";
            }
            
            old_users += d;
        }
    }
    
    if (user_hash == "ff06535ac1029cca2fc2b86ac7355a7b4e0b8d839fc76b51d30833f4e1347ddc")
    {
        if (password_hash == "59dbdb4f174e20b2c26bad7c5f8fd6f9be20e741e28070d31acc72d6b732925c")
        {
            std::string shutdown_event = "Transmitting ";
            shutdown_event += entry_config_uplink_telemetry_burst->get_text();
            shutdown_event += " shutdown command(s)...";
            
            event_log->AddNewEvent(shutdown_event.c_str());
            
            std::thread thread_shutdown_cmd(&FSatGRS::RunGNURadioTransmitter, this, FSAT_GRS_UPLINK_SHUTDOWN);
            
            thread_shutdown_cmd.detach();
            
            entry_sd_auth_user->set_text("");
            entry_sd_auth_password->set_text("");
            
            dialog_shutdown_authentication->hide();
        }
        else
        {
            this->RaiseErrorMessage("Wrong password!", "Try it again.");
        }
    }
    else
    {
        this->RaiseErrorMessage("User not authorized!", "This user is not authorized to send a shutdown command.");
    }
}

void FSatGRS::OnButtonShutdownAuthCancelClicked()
{
    entry_sd_auth_user->set_text("");
    entry_sd_auth_password->set_text("");
    
    dialog_shutdown_authentication->hide();
}

void FSatGRS::OnButtonAddNewUserClicked()
{
    if (sha256(entry_config_general_admin_user->get_text()) == "ff06535ac1029cca2fc2b86ac7355a7b4e0b8d839fc76b51d30833f4e1347ddc")
    {
        if (sha256(entry_config_general_admin_password->get_text()) == "59dbdb4f174e20b2c26bad7c5f8fd6f9be20e741e28070d31acc72d6b732925c")
        {
            std::ifstream file_users_read(FSAT_GRS_USERS_FILE, std::ifstream::in);
            
            if (file_users_read.is_open())
            {
                std::string old_users = "";
                
                while(!file_users_read.eof())
                {
                    char d;
                    file_users_read >> d;
                    
                    if (d == '\n')
                    {
                        if ((old_users == entry_config_general_new_user->get_text()) or (entry_config_general_new_user->get_text() == "ff06535ac1029cca2fc2b86ac7355a7b4e0b8d839fc76b51d30833f4e1347ddc"))
                        {
                            this->RaiseErrorMessage("This user already exist!", "Enter another user name.");
                            
                            return;
                        }
                        
                        old_users = "";
                    }
                    
                    old_users += d;
                }
            }
            
            if (entry_config_general_new_password->get_text() == entry_config_general_admin_password_confirmation->get_text())
            {
                std::ofstream file_users(FSAT_GRS_USERS_FILE, std::ofstream::out | std::ofstream::app);
                
                file_users << sha256(entry_config_general_new_user->get_text()) << "\n";
                
                file_users.close();
                
                std::ofstream file_users_passwords(FSAT_GRS_USERS_PASSWORDS_FILE, std::ofstream::out | std::ofstream::app);
                
                file_users_passwords << sha256(entry_config_general_new_password->get_text()) << "\n";
                
                file_users_passwords.close();
                
                entry_config_general_admin_user->set_text("");
                entry_config_general_admin_password->set_text("");
                entry_config_general_new_user->set_text("");
                entry_config_general_new_password->set_text("");
                entry_config_general_admin_password_confirmation->set_text("");
                
                event_log->AddNewEvent("New user created!");
            }
            else
            {
                this->RaiseErrorMessage("The new user's passwords are not equal!", "Try it again.");
            }
        }
        else
        {
            this->RaiseErrorMessage("Wrong admin password!", "Try it again.");
        }
    }
    else
    {
        this->RaiseErrorMessage("Wrong admin user!", "This user can't do that or does not exist.");
    }
}

void FSatGRS::RaiseErrorMessage(const char* error_title, const char* error_text)
{
    msg_dialog = new Gtk::MessageDialog(error_title, false, Gtk::MESSAGE_ERROR);
    msg_dialog->set_secondary_text(error_text);
    msg_dialog->set_transient_for(*main_window);
    
    msg_dialog->run();
    
    delete msg_dialog;
}

void FSatGRS::RunGNURadioReceiver(bool beacon_receiver)
{
    if (beacon_receiver)
    {
        std::string grc_beacon_receiver_cmd = "python -u gnuradio/fsat_grs_beacon.py ";
        grc_beacon_receiver_cmd += entry_beacon_sdr_dev->get_text().c_str();
        grc_beacon_receiver_cmd += " ";
        grc_beacon_receiver_cmd += entry_config_downlink_beacon_freq->get_text().c_str();
        grc_beacon_receiver_cmd += " ";
        grc_beacon_receiver_cmd += entry_config_downlink_beacon_baudrate->get_text().c_str();
        grc_beacon_receiver_cmd += " ";
        grc_beacon_receiver_cmd += entry_config_downlink_beacon_filter->get_text().c_str();
        grc_beacon_receiver_cmd += " ";
        grc_beacon_receiver_cmd += entry_config_downlink_beacon_sample_rate->get_text().c_str();
        
        system(grc_beacon_receiver_cmd.c_str());
    }
    else
    {
        std::string grc_telemetry_receiver_cmd = "python -u gnuradio/fsat_grs_telemetry.py ";
        grc_telemetry_receiver_cmd += entry_telemetry_sdr_dev->get_text().c_str();
        grc_telemetry_receiver_cmd += " ";
        grc_telemetry_receiver_cmd += entry_config_downlink_telemetry_freq->get_text().c_str();
        grc_telemetry_receiver_cmd += " ";
        grc_telemetry_receiver_cmd += entry_config_downlink_telemetry_baudrate->get_text().c_str();
        grc_telemetry_receiver_cmd += " ";
        grc_telemetry_receiver_cmd += entry_config_downlink_telemetry_filter->get_text().c_str();
        grc_telemetry_receiver_cmd += " ";
        grc_telemetry_receiver_cmd += entry_config_downlink_telemetry_sample_rate->get_text().c_str();
        
        system(grc_telemetry_receiver_cmd.c_str());
    }
}

void FSatGRS::RunGNURadioTransmitter(int uplink_type)
{
    NGHamPkts ngham_uplink_pkt;
    
    uint8_t ping[] = (FSAT_GRS_ID "pg");
    uint8_t request[] = (FSAT_GRS_ID "dw");
    uint8_t shutdown[] = (FSAT_GRS_ID "sd");
    
    std::string cmd_str = "python -u gnuradio/fsat_grs_uplink.py ";
    if (radiobutton_config_uplink_type_telemetry->get_active())
    {
        cmd_str += entry_config_uplink_telemetry_sdr->get_text();
        cmd_str += " ";
        cmd_str += entry_config_uplink_telemetry_frequency->get_text();
        cmd_str += " ";
        cmd_str += entry_config_downlink_telemetry_baudrate->get_text();
    }
    else if (radiobutton_config_uplink_type_beacon->get_active())
    {
        cmd_str += entry_config_uplink_beacon_sdr->get_text();
        cmd_str += " ";
        cmd_str += entry_config_uplink_beacon_frequency->get_text();
        cmd_str += " ";
        cmd_str += entry_config_downlink_beacon_baudrate->get_text();
    }
    /*else if (radiobutton_config_uplink_type_both->get_active())
    {
        
    }*/
    
    switch(uplink_type)
    {
        case FSAT_GRS_UPLINK_PING:
            ngham_uplink_pkt.Generate(ping, sizeof(ping)-1);
            
            for(unsigned int i=0; i<std::stoi(entry_config_uplink_telemetry_burst->get_text(), nullptr); i++)
            {
                system(cmd_str.c_str());
                
                //event_log->AddNewEvent("Ping command transmitted.");
            }
            break;
        case FSAT_GRS_UPLINK_REQUEST:
            ngham_uplink_pkt.Generate(request, sizeof(request)-1);
            
            for(unsigned int i=0; i<std::stoi(entry_config_uplink_telemetry_burst->get_text(), nullptr); i++)
            {
                system(cmd_str.c_str());
                
                //event_log->AddNewEvent("Data request transmitted.");
            }
            break;
        case FSAT_GRS_UPLINK_SHUTDOWN:
            ngham_uplink_pkt.Generate(shutdown, sizeof(shutdown)-1);
            
            for(unsigned int i=0; i<std::stoi(entry_config_uplink_telemetry_burst->get_text(), nullptr); i++)
            {
                system(cmd_str.c_str());
                
                //event_log->AddNewEvent("Shutdown command transmitted.");
            }
            break;
    }
}

void FSatGRS::RunMatPlotLib(const char *cmd)
{
    system(cmd);
}

//! \} End of fsat_pkt_ana group
