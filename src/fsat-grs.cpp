/*
 * fsat-grs.cpp
 * 
 * Copyright (C) 2017-2019, Universidade Federal de Santa Catarina.
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
 * \brief Implementation of the main class of the FSatGRS.
 * 
 * \author Gabriel Mariano Marcelino <gabriel.mm8@gmail.com>
 * 
 * \version 0.2.8
 * 
 * \date 10/09/2017
 * 
 * \addtogroup fsat_grs
 * \ingroup src
 * \{
 */

#include <fstream>
#include <string>
#include <cstdio>
#include <stdlib.h>
#include <sys/stat.h>

#include "fsat-grs.h"
#include "version.h"
#include "aux.hpp"
#include "beacon_data.h"
#include "telemetry_data.h"
#include "telecommands.h" 
#include "data_processing.hpp"
#include "sha256.h"
#include "uplink_events_columns.h"

using namespace std;

FSatGRS::FSatGRS()
{
    
}

FSatGRS::FSatGRS(Glib::RefPtr<Gtk::Builder> ref_builder)
{
    this->BuildWidgets(ref_builder);
}

FSatGRS::~FSatGRS()
{
    //delete ngham_statistic;
    //delete ax25_statistic;
    //delete telemetry_ngham_statistic;
    //delete beacon_data;
    //delete telemetry_data;
    delete event_log;
    delete window_fsat_grs;
}

int FSatGRS::BuildWidgets(Glib::RefPtr<Gtk::Builder> ref_builder)
{
    try
    {
        if (this->CheckFile(FSAT_PKT_ANA_DEFAULT_UI_FILE))
        {
            ref_builder->add_from_file(FSAT_PKT_ANA_DEFAULT_UI_FILE);
        }
        else
        {
            ref_builder->add_from_file(FSAT_PKT_ANA_DEFAULT_UI_FILE_LOCAL);
        }
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
    
    ref_builder->get_widget("window_fsat_grs", window_fsat_grs);
    
    if (!window_fsat_grs)
    {
        return -1;
    }
    
    // Toolbar
    ref_builder->get_widget("toolbutton_open_log_file", toolbutton_open_log_file);
    if (toolbutton_open_log_file)
    {
        toolbutton_open_log_file->signal_clicked().connect(sigc::mem_fun(*this, &FSatGRS::OnToolButtonOpenClicked));
    }
    
    ref_builder->get_widget("filechooserdialog_log_viewer", filechooserdialog_log_viewer);
    
    ref_builder->get_widget("button_log_viewer_cancel", button_log_viewer_cancel);
    if (button_log_viewer_cancel)
    {
        button_log_viewer_cancel->signal_clicked().connect(sigc::mem_fun(*this, &FSatGRS::OnButtonLogViewerCancelClicked));
    }

    ref_builder->get_widget("button_log_viewer_open", button_log_viewer_open);
    if (button_log_viewer_open)
    {
        button_log_viewer_open->signal_clicked().connect(sigc::mem_fun(*this, &FSatGRS::OnButtonLogViewerOpenClicked));
    }

    ref_builder->get_widget("toolbutton_close_log_file", toolbutton_close_log_file);
    if (toolbutton_close_log_file)
    {
        toolbutton_close_log_file->signal_clicked().connect(sigc::mem_fun(*this, &FSatGRS::OnToolButtonCloseClicked));
    }

    ref_builder->get_widget("toolbutton_prev_log_line", toolbutton_prev_log_line);
    if (toolbutton_prev_log_line)
    {
        toolbutton_prev_log_line->signal_clicked().connect(sigc::mem_fun(*this, &FSatGRS::OnToolButtonPrevClicked));
    }

    ref_builder->get_widget("toolbutton_next_log_line", toolbutton_next_log_line);
    if (toolbutton_next_log_line)
    {
        toolbutton_next_log_line->signal_clicked().connect(sigc::mem_fun(*this, &FSatGRS::OnToolButtonNextClicked));
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

    ref_builder->get_widget("toolbutton_reset_charge", toolbutton_reset_charge);
    if (toolbutton_reset_charge)
    {
        toolbutton_reset_charge->signal_clicked().connect(sigc::mem_fun(*this, &FSatGRS::OnToolButtonResetChargeClicked));
    }

    ref_builder->get_widget("toolbutton_broadcast_message", toolbutton_broadcast_message);
    if (toolbutton_broadcast_message)
    {
        toolbutton_broadcast_message->signal_clicked().connect(sigc::mem_fun(*this, &FSatGRS::OnToolButtonBroadcastMessageClicked));
    }

    ref_builder->get_widget("toolbutton_shutdown", toolbutton_shutdown);
    if (toolbutton_shutdown)
    {
        toolbutton_shutdown->signal_clicked().connect(sigc::mem_fun(*this, &FSatGRS::OnToolButtonShutdownClicked));
    }

    ref_builder->get_widget("toolbutton_payload_x", toolbutton_payload_x);
    if (toolbutton_payload_x)
    {
        toolbutton_payload_x->signal_clicked().connect(sigc::mem_fun(*this, &FSatGRS::OnToolButtonPayloadXClicked));
    }

    ref_builder->get_widget("toolbutton_schedule_cmd", toolbutton_schedule_cmd);
    if (toolbutton_schedule_cmd)
    {
        toolbutton_schedule_cmd->signal_clicked().connect(sigc::mem_fun(*this, &FSatGRS::OnToolButtonCmdSchedulerClicked));
    }

    ref_builder->get_widget("toolbutton_open_gpredict", toolbutton_open_gpredict);
    if (toolbutton_open_gpredict)
    {
        toolbutton_open_gpredict->signal_clicked().connect(sigc::mem_fun(*this, &FSatGRS::OnToolButtonOpenGPredictClicked));
    }
    
    ref_builder->get_widget("toolbutton_open_grqx", toolbutton_open_grqx);
    if (toolbutton_open_grqx)
    {
        toolbutton_open_grqx->signal_clicked().connect(sigc::mem_fun(*this, &FSatGRS::OnToolButtonOpenGQRXClicked));
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
    ref_builder->get_widget("combobox_beacon_sdr_dev", combobox_beacon_sdr_dev);
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
    ref_builder->get_widget("combobox_telemetry_sdr_dev", combobox_telemetry_sdr_dev);
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
    
    // Uplink stream
    ref_builder->get_widget("radiobutton_uplink_output_sdr", radiobutton_uplink_output_sdr);
    ref_builder->get_widget("combobox_uplink_output_sdr_device", combobox_uplink_output_sdr_device);
    ref_builder->get_widget("radiobutton_uplink_output_server", radiobutton_uplink_output_server);
    ref_builder->get_widget("entry_uplink_output_server_ip", entry_uplink_output_server_ip);
    ref_builder->get_widget("entry_uplink_output_server_port", entry_uplink_output_server_port);
    ref_builder->get_widget("radiobutton_uplink_output_serial", radiobutton_uplink_output_serial);
    ref_builder->get_widget("entry_uplink_output_serial_dev", entry_uplink_output_serial_dev);
    ref_builder->get_widget("combobox_uplink_output_serial_baudrate", combobox_uplink_output_serial_baudrate);
    ref_builder->get_widget("radiobutton_uplink_grs_scheduler", radiobutton_uplink_grs_scheduler);
    
    ref_builder->get_widget("button_uplink_control_open_grs_scheduler", button_uplink_control_open_grs_scheduler);
    if (button_uplink_control_open_grs_scheduler)
    {
        button_uplink_control_open_grs_scheduler->signal_clicked().connect(sigc::mem_fun(*this, &FSatGRS::OnButtonGRSSchedulerClicked));
    }

    ref_builder->get_widget("radiobutton_uplink_server_control", radiobutton_uplink_server_control);
    ref_builder->get_widget("entry_uplink_server_ip", entry_uplink_server_ip);
    ref_builder->get_widget("entry_uplink_server_port", entry_uplink_server_port);
    ref_builder->get_widget("radiobutton_uplink_manual_control", radiobutton_uplink_manual_control);
    
    ref_builder->get_widget("togglebutton_play_uplink", togglebutton_play_uplink);
    if (togglebutton_play_uplink)
    {
        togglebutton_play_uplink->signal_clicked().connect(sigc::mem_fun(*this, &FSatGRS::OnToggleButtonPlayUplinkStreamToggled));
    }

    ref_builder->get_widget("togglebutton_pause_uplink", togglebutton_pause_uplink);
    if (togglebutton_pause_uplink)
    {
        togglebutton_pause_uplink->signal_clicked().connect(sigc::mem_fun(*this, &FSatGRS::OnToggleButtonPauseUplinkStreamToggled));
    }

    ref_builder->get_widget("button_stop_uplink", button_stop_uplink);
    if (button_stop_uplink)
    {
        button_stop_uplink->signal_clicked().connect(sigc::mem_fun(*this, &FSatGRS::OnButtonStopUplinkStreamClicked));
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
        event_log->open((LOG_DEFAULT_DIR "/EVENTS_" + event_log->CurrentDateTime() + ".csv").c_str(), ofstream::out);
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
    
    vector<Gtk::Label *> beacon_data_labels;
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
    
    vector<Gtk::Label *> telemetry_data_labels;
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
    
    // Telemetry Packets Statistic
    ref_builder->get_widget("label_telemetry_pkt_statistic_total", label_telemetry_pkt_statistic_total);
    ref_builder->get_widget("label_telemetry_pkt_statistic_lost", label_telemetry_pkt_statistic_lost);
    
    telemetry_ngham_statistic = new ProtocolStatistic(label_telemetry_pkt_statistic_total, label_telemetry_pkt_statistic_total, label_telemetry_pkt_statistic_total, label_telemetry_pkt_statistic_lost);
    
    // Plot dialog
    ref_builder->get_widget("dialog_plot", dialog_plot);
    ref_builder->get_widget("filechooserbutton_plot_beacon", filechooserbutton_plot_beacon);
    ref_builder->get_widget("combobox_plot_beacon_data", combobox_plot_beacon_data);
    ref_builder->get_widget("checkbutton_plot_beacon_connect_points", checkbutton_plot_beacon_connect_points);
    ref_builder->get_widget("checkbutton_plot_beacon_best_curve", checkbutton_plot_beacon_best_curve);
    ref_builder->get_widget("checkbutton_plot_save_pdf_beacon", checkbutton_plot_save_pdf_beacon);
    ref_builder->get_widget("checkbutton_plot_use_sat_time_beacon", checkbutton_plot_use_sat_time_beacon);
    ref_builder->get_widget("filechooserbutton_plot_telemetry", filechooserbutton_plot_telemetry);
    ref_builder->get_widget("combobox_plot_telemetry_data", combobox_plot_telemetry_data);
    ref_builder->get_widget("checkbutton_plot_telemetry_connect_points", checkbutton_plot_telemetry_connect_points);
    ref_builder->get_widget("checkbutton_plot_telemetry_best_curve", checkbutton_plot_telemetry_best_curve);
    ref_builder->get_widget("checkbutton_plot_save_pdf_telemetry", checkbutton_plot_save_pdf_telemetry);
    ref_builder->get_widget("checkbutton_plot_use_sat_time_telemetry", checkbutton_plot_use_sat_time_telemetry);
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
    ref_builder->get_widget("entry_config_general_gs_id", entry_config_general_gs_id);
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
    ref_builder->get_widget("entry_config_uplink_burst", entry_config_uplink_burst);
    ref_builder->get_widget("entry_config_uplink_telemetry_frequency", entry_config_uplink_telemetry_frequency);
    ref_builder->get_widget("entry_config_uplink_beacon_frequency", entry_config_uplink_beacon_frequency);
    ref_builder->get_widget("radiobutton_config_uplink_type_telemetry", radiobutton_config_uplink_type_telemetry);
    ref_builder->get_widget("radiobutton_config_uplink_type_beacon", radiobutton_config_uplink_type_beacon);
    
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
    
    // Data to request
    ref_builder->get_widget("dialog_data_request", dialog_data_request);
    ref_builder->get_widget("checkbutton_request_packet_flags", checkbutton_request_packet_flags);
    ref_builder->get_widget("checkbutton_request_obdh_status", checkbutton_request_obdh_status);
    ref_builder->get_widget("checkbutton_request_imu", checkbutton_request_imu);
    ref_builder->get_widget("checkbutton_request_obdh_time", checkbutton_request_obdh_time);
    ref_builder->get_widget("checkbutton_request_obdh_mis", checkbutton_request_obdh_mis);
    ref_builder->get_widget("checkbutton_request_solar_panels_sensors", checkbutton_request_solar_panels_sensors);
    ref_builder->get_widget("checkbutton_request_main_radio", checkbutton_request_main_radio);
    ref_builder->get_widget("checkbutton_request_solar_panels", checkbutton_request_solar_panels);
    ref_builder->get_widget("checkbutton_request_eps_misc", checkbutton_request_eps_misc);
    ref_builder->get_widget("checkbutton_request_battery_monitor", checkbutton_request_battery_monitor);
    ref_builder->get_widget("checkbutton_request_temperatures", checkbutton_request_temperatures);
    ref_builder->get_widget("checkbutton_request_task_scheduler", checkbutton_request_task_scheduler);
    ref_builder->get_widget("checkbutton_request_rush", checkbutton_request_rush);
    ref_builder->get_widget("entry_uplink_request_pkt_quant", entry_uplink_request_pkt_quant);
    ref_builder->get_widget("entry_uplink_request_offset", entry_uplink_request_offset);
    ref_builder->get_widget("radiobutton_uplink_data_request_start", radiobutton_uplink_data_request_start);
    ref_builder->get_widget("radiobutton_uplink_data_request_end", radiobutton_uplink_data_request_end);
    ref_builder->get_widget("button_data_request_send", button_data_request_send);
    ref_builder->get_widget("button_data_request_cancel", button_data_request_cancel);
    
    if (button_data_request_send)
    {
        button_data_request_send->signal_clicked().connect(sigc::mem_fun(*this, &FSatGRS::OnButtonDataRequestSendClicked));
    }
    
    if (button_data_request_cancel)
    {
        button_data_request_cancel->signal_clicked().connect(sigc::mem_fun(*this, &FSatGRS::OnButtonDataRequestCancelClicked));
    }

    // Message Broadcast Dialog
    ref_builder->get_widget("dialog_broadcast_message", dialog_broadcast_message);
    ref_builder->get_widget("entry_dialog_broadcast_message", entry_dialog_broadcast_message);

    ref_builder->get_widget("dialog_broadcast_message_send", dialog_broadcast_message_send);
    if (dialog_broadcast_message_send)
    {
        dialog_broadcast_message_send->signal_clicked().connect(sigc::mem_fun(*this, &FSatGRS::OnButtonBroadcastDialogSendClicked));
    }

    ref_builder->get_widget("dialog_broadcast_message_cancel", dialog_broadcast_message_cancel);
    if (dialog_broadcast_message_cancel)
    {
        dialog_broadcast_message_cancel->signal_clicked().connect(sigc::mem_fun(*this, &FSatGRS::OnButtonBroadcastDialogCancelClicked));
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
    
    // Uplink Scheduler Manager Dialog
    ref_builder->get_widget("dialog_uplink_scheduler_manager", dialog_uplink_scheduler_manager);
    ref_builder->get_widget("treeview_uplink_scheduler_manager_events", treeview_uplink_scheduler_manager_events);
    liststore_uplink_events = Glib::RefPtr<Gtk::ListStore>::cast_static(ref_builder->get_object("liststore_uplink_events"));
    ref_builder->get_widget("button_uplink_scheduler_manager_add", button_uplink_scheduler_manager_add);
    if (button_uplink_scheduler_manager_add)
    {
        button_uplink_scheduler_manager_add->signal_clicked().connect(sigc::mem_fun(*this, &FSatGRS::OnButtonUplinkSchedulerManagerAddClicked));
    }

    ref_builder->get_widget("button_uplink_scheduler_manager_delete", button_uplink_scheduler_manager_delete);
    if (button_uplink_scheduler_manager_delete)
    {
        button_uplink_scheduler_manager_delete->signal_clicked().connect(sigc::mem_fun(*this, &FSatGRS::OnButtonUplinkSchedulerManagerDeleteClicked));
    }

    ref_builder->get_widget("dialog_uplink_scheduler_manager_new_event", dialog_uplink_scheduler_manager_new_event);
    ref_builder->get_widget("combobox_uplink_scheduler_manager_new_event_cmd", combobox_uplink_scheduler_manager_new_event_cmd);
    ref_builder->get_widget("switch_uplink_scheduler_manager_new_event_interval", switch_uplink_scheduler_manager_new_event_interval);
    ref_builder->get_widget("entry_uplink_scheduler_manager_new_event_start_time", entry_uplink_scheduler_manager_new_event_start_time);
    ref_builder->get_widget("entry_uplink_scheduler_manager_new_event_start_date", entry_uplink_scheduler_manager_new_event_start_date);
    ref_builder->get_widget("entry_uplink_scheduler_manager_new_event_end_time", entry_uplink_scheduler_manager_new_event_end_time);
    ref_builder->get_widget("entry_uplink_scheduler_manager_new_event_end_date", entry_uplink_scheduler_manager_new_event_end_date);
    ref_builder->get_widget("switch_uplink_scheduler_manager_new_event_period", switch_uplink_scheduler_manager_new_event_period);
    ref_builder->get_widget("entry_uplink_scheduler_manager_new_event_period_value", entry_uplink_scheduler_manager_new_event_period_value);
    ref_builder->get_widget("switch_uplink_scheduler_manager_new_event_cycles", switch_uplink_scheduler_manager_new_event_cycles);
    ref_builder->get_widget("entry_uplink_scheduler_manager_new_event_cycles_value", entry_uplink_scheduler_manager_new_event_cycles_value);
    ref_builder->get_widget("button_uplink_scheduler_manager_new_event_add", button_uplink_scheduler_manager_new_event_add);
    if (button_uplink_scheduler_manager_new_event_add)
    {
        button_uplink_scheduler_manager_new_event_add->signal_clicked().connect(sigc::mem_fun(*this, &FSatGRS::OnButtonUplinkSchedulerManagerNewEventAddClicked));
    }

    ref_builder->get_widget("button_uplink_scheduler_manager_new_event_cancel", button_uplink_scheduler_manager_new_event_cancel);
    if (button_uplink_scheduler_manager_new_event_cancel)
    {
        button_uplink_scheduler_manager_new_event_cancel->signal_clicked().connect(sigc::mem_fun(*this, &FSatGRS::OnButtonUplinkSchedulerManagerNewEventCancelClicked));
    }

    // Payload X Control
    ref_builder->get_widget("window_payload_x_control", window_payload_x_control);
    ref_builder->get_widget("button_payload_x_request_status", button_payload_x_request_status);
    ref_builder->get_widget("filechooser_payload_x_bitfile", filechooser_payload_x_bitfile);
    ref_builder->get_widget("label_payload_x_bitfile_transferred", label_payload_x_bitfile_transferred);
    ref_builder->get_widget("label_payload_x_bitfile_total", label_payload_x_bitfile_total);
    ref_builder->get_widget("progreebar_payload_x_packet_transfer", progreebar_payload_x_packet_transfer);
    ref_builder->get_widget("button_payload_x_bitfile_send", button_payload_x_bitfile_send);
    ref_builder->get_widget("button_payload_x_bitfile_swap", button_payload_x_bitfile_swap);
    if (button_payload_x_bitfile_swap)
    {
        button_payload_x_bitfile_swap->signal_clicked().connect(sigc::mem_fun(*this, &FSatGRS::OnButtonPayloadXSwapClicked));
    }

    // About dialog
    ref_builder->get_widget("aboutdialog", aboutdialog);
    
    return 0;
}

int FSatGRS::Run(Glib::RefPtr<Gtk::Application> app)
{
    system("mkdir -p $HOME/.fsat_grs");
    
    string cmd = "touch $HOME";
    system((cmd + FSAT_GRS_USERS_FILE + " || exit").c_str());
    system((cmd + FSAT_GRS_USERS_PASSWORDS_FILE + " || exit").c_str());
    
    cmd = "grep -q -F \"" FSAT_GRS_ADMIN_HASH "\" $HOME" FSAT_GRS_USERS_FILE " || echo \"" FSAT_GRS_ADMIN_HASH "\" > $HOME" FSAT_GRS_USERS_FILE;
    system(cmd.c_str());
    
    cmd = "grep -q -F \"" FSAT_GRS_ADMIN_PASSWORD_HASH "\" $HOME" FSAT_GRS_USERS_PASSWORDS_FILE " || echo \"" FSAT_GRS_ADMIN_PASSWORD_HASH "\" > $HOME" FSAT_GRS_USERS_PASSWORDS_FILE;
    system(cmd.c_str());
    
    this->LoadConfigs();
    
    auto timer_slot = sigc::mem_fun(*this, &FSatGRS::Timer);
    auto conn = Glib::signal_timeout().connect(timer_slot, DATA_RECEPTION_SAMPLE_RATE);

    return app->run(*window_fsat_grs);
}
/*
vector<uint8_t> FSatGRS::ProccessByte(uint8_t byte)
{
    vector<uint8_t> sync_bytes;
    
    sync_bytes.push_back(EntryToHex(entry_ngham_sync_bytes_s3->get_text()));
    sync_bytes.push_back(EntryToHex(entry_ngham_sync_bytes_s2->get_text()));
    sync_bytes.push_back(EntryToHex(entry_ngham_sync_bytes_s1->get_text()));
    sync_bytes.push_back(EntryToHex(entry_ngham_sync_bytes_s0->get_text()));
    
    vector<uint8_t> result;
    
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
                
                vector<uint8_t> r = this->ProccessByte(byte);
                if (!r.empty())
                {
                    if (checkbutton_log_ngham_packets->get_active())
                    {
                        *log_ngham_pkts << log_ngham_pkts->CurrentDateTime(LOG_DATA_TIME_FOR_LOG_CSV);
                    }
                    
                    for(unsigned int i=0;i<r.size();i++)
                    {
                        stringstream byte_str;
                        byte_str << (char)r[i];
                        string b_ngham = byte_str.str();
                        
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
    
    if (togglebutton_play_uplink->get_active())
    {
        if (radiobutton_uplink_grs_scheduler->get_active())
        {
            for(unsigned int i=0; i<uplink_events.size(); i++)
            {
                if (uplink_events[i].CanTransmit())
                {
                    if (uplink_events[i].GetType() == UPLINK_EVENT_TYPE_PING)
                    {
                        string ping_event = "Transmitting ";
                        ping_event += entry_config_uplink_burst->get_text();
                        ping_event += " ping command(s)...";

                        event_log->AddNewEvent(ping_event.c_str());

                        thread thread_ping_cmd(&FSatGRS::RunGNURadioTransmitter, this, FSAT_GRS_UPLINK_PING);

                        thread_ping_cmd.detach();
                    }

                    if (uplink_events[i].GetType() == UPLINK_EVENT_TYPE_DATA_REQUEST)
                    {
                        string data_request_event = "Transmitting ";
                        data_request_event += entry_config_uplink_burst->get_text();
                        data_request_event += " data request(s)...";

                        event_log->AddNewEvent(data_request_event.c_str());

                        thread thread_request_cmd(&FSatGRS::RunGNURadioTransmitter, this, FSAT_GRS_UPLINK_REQUEST);

                        thread_request_cmd.detach();
                    }

                    if (uplink_events[i].GetType() == UPLINK_EVENT_TYPE_SHUTDOWN)
                    {
                        string shutdown_event = "Transmitting ";
                        shutdown_event += entry_config_uplink_burst->get_text();
                        shutdown_event += " shutdown command(s)...";

                        event_log->AddNewEvent(shutdown_event.c_str());

                        thread thread_shutdown_cmd(&FSatGRS::RunGNURadioTransmitter, this, FSAT_GRS_UPLINK_SHUTDOWN);

                        thread_shutdown_cmd.detach();
                    }
                }
            }
        }
    }

	return true;
}

void FSatGRS::OnToolButtonOpenClicked()
{
    int response = filechooserdialog_log_viewer->run();
    
    if ((response == Gtk::RESPONSE_DELETE_EVENT) or (response == Gtk::RESPONSE_CANCEL))
    {
        filechooserdialog_log_viewer->hide();
    }
}

void FSatGRS::OnButtonLogViewerCancelClicked()
{
    filechooserdialog_log_viewer->hide();
}

void FSatGRS::OnButtonLogViewerOpenClicked()
{
    string log_file = filechooserdialog_log_viewer->get_filename();

    read_log = new ReadLog;

    read_log->open(log_file.c_str());

    filechooserdialog_log_viewer->hide();
    
    if (read_log->is_open())
    {
        string log_text = read_log->getLogType();
        log_text += " log file ";
        log_text += log_file.c_str();
        log_text += " with ";
        log_text += ToString(read_log->getLines());
        log_text += " entries opened.";

        event_log->AddNewEvent(log_text.c_str());

        beacon_data->ForceDisplay(read_log->getDataLine(0));
        
        toolbutton_open_log_file->set_sensitive(false);
        toolbutton_close_log_file->set_sensitive(true);
        toolbutton_prev_log_line->set_sensitive(true);
        toolbutton_next_log_line->set_sensitive(true);
    }
    else
    {
        delete read_log;

        this->RaiseErrorMessage("Error opening the log file!", "The selected file is invalid or corrupted.");
    }
}

void FSatGRS::OnToolButtonCloseClicked()
{
    if (read_log->is_open())
    {
        read_log->close();
        
        delete read_log;
    }

    toolbutton_open_log_file->set_sensitive(true);
    toolbutton_close_log_file->set_sensitive(false);
    toolbutton_prev_log_line->set_sensitive(false);
    toolbutton_next_log_line->set_sensitive(false);

    event_log->AddNewEvent("Log file closed.");
}

void FSatGRS::OnToolButtonPrevClicked()
{
    if (read_log->getLogType() == "BEACON")
    {
        beacon_data->ForceDisplay(read_log->getPrevious());
    }
    else if (read_log->getLogType() == "TELEMETRY")
    {
        telemetry_data->ForceDisplay(read_log->getPrevious());
    }
    else
    {
        this->RaiseErrorMessage("Type of log file unknown!", "Nothing to display.");
    }
}

void FSatGRS::OnToolButtonNextClicked()
{
    if (read_log->getLogType() == "BEACON")
    {
        beacon_data->ForceDisplay(read_log->getNext());
    }
    else if (read_log->getLogType() == "TELEMETRY")
    {
        telemetry_data->ForceDisplay(read_log->getNext());
    }
    else
    {
        this->RaiseErrorMessage("Type of log file unknown!", "Nothing to display.");
    }
}

void FSatGRS::OnToolButtonConfigClicked()
{    
    int response = dialog_config->run();
    
    if ((response == Gtk::RESPONSE_DELETE_EVENT) or (response == Gtk::RESPONSE_CANCEL))
    {
        this->LoadConfigs();
        
        dialog_config->hide();
    }
}

void FSatGRS::OnButtonConfigOkClicked()
{
    this->SaveConfigs();
    
    dialog_config->hide();
}

void FSatGRS::OnButtonConfigDefaultClicked()
{
    this->LoadDefaultConfigs();
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
    string ping_event = "Transmitting ";
    ping_event += entry_config_uplink_burst->get_text();
    ping_event += " ping command(s)...";
    
    event_log->AddNewEvent(ping_event.c_str());
    
    thread thread_ping_cmd(&FSatGRS::RunGNURadioTransmitter, this, FSAT_GRS_UPLINK_PING);
    
    thread_ping_cmd.detach();
}

void FSatGRS::OnToolButtonRequestDataClicked()
{
    int response = dialog_data_request->run();
    
    if ((response == Gtk::RESPONSE_DELETE_EVENT) or (response == Gtk::RESPONSE_CANCEL))
    {
        dialog_data_request->hide();
    }
}

void FSatGRS::OnToolButtonResetChargeClicked()
{
    string reset_charge_event = "Transmitting ";
    reset_charge_event += entry_config_uplink_burst->get_text();
    reset_charge_event += " reset charge command(s)...";

    event_log->AddNewEvent(reset_charge_event.c_str());

    thread thread_reset_charge_cmd(&FSatGRS::RunGNURadioTransmitter, this, FSAT_GRS_UPLINK_RESET_CHARGE);

    thread_reset_charge_cmd.detach();
}

void FSatGRS::OnToolButtonBroadcastMessageClicked()
{
    int response = dialog_broadcast_message->run();

    if ((response == Gtk::RESPONSE_DELETE_EVENT) or (response == Gtk::RESPONSE_CANCEL))
    {
        dialog_broadcast_message->hide();
    }
}

void FSatGRS::OnToolButtonShutdownClicked()
{
    int response = dialog_shutdown_authentication->run();
    
    if ((response == Gtk::RESPONSE_DELETE_EVENT) or (response == Gtk::RESPONSE_CANCEL))
    {
        dialog_shutdown_authentication->hide();
    }
}

void FSatGRS::OnToolButtonPayloadXClicked()
{
    window_payload_x_control->show();
}

void FSatGRS::OnToolButtonCmdSchedulerClicked()
{
    int response = dialog_uplink_scheduler_manager->run();
    
    if ((response == Gtk::RESPONSE_DELETE_EVENT) or (response == Gtk::RESPONSE_CANCEL))
    {
        dialog_uplink_scheduler_manager->hide();
    }
}

void FSatGRS::OnToolButtonOpenGPredictClicked()
{
    if ((access("/usr/bin/gpredict", X_OK) == 0) or (access("/usr/local/bin/gpredict", X_OK) == 0))
    {
        system("gpredict &");
        
        event_log->AddNewEvent("Opening GPredict software...");
    }
    else
    {
        this->RaiseErrorMessage("GPredict not installed!", "The GPredict software is not installed.");
    }
}

void FSatGRS::OnToolButtonOpenGQRXClicked()
{
    if (access("/usr/bin/gqrx", X_OK) == 0)
    {
        system("gqrx &");
        
        event_log->AddNewEvent("Opening GQRX software...");
    }
    else
    {
        this->RaiseErrorMessage("GQRX not installed!", "The GQRX software is not installed.");
    }
}

void FSatGRS::OnToolButtonAboutClicked()
{
    this->aboutdialog->set_version(GRS_SOFTWARE_VERSION);

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
            
            thread_downlink_beacon = new thread(&FSatGRS::RunGNURadioReceiver, this, FSAT_GRS_RX_BEACON);
            thread_downlink_beacon->detach();
            
            ngham_pkts_beacon->open(FSAT_GRS_GRC_BEACON_BIN, ifstream::in);
        }
        /*else if (radiobutton_beacon_src_tcp->get_active())
        {
            
        }
        else if (radiobutton_beacon_src_serial->get_active())
        {
            
        }*/
        else if (radiobutton_beacon_src_file->get_active())
        {
            ngham_pkts_beacon->open(filechooserbutton_beacon->get_filename().c_str(), ifstream::in);
        }
        
        if (ngham_pkts_beacon->is_open())
        {
            toolbutton_open_log_file->set_sensitive(false);
            toolbutton_close_log_file->set_sensitive(false);
            toolbutton_prev_log_line->set_sensitive(false);
            toolbutton_next_log_line->set_sensitive(false);
            radiobutton_beacon_src_sdr->set_sensitive(false);
            combobox_beacon_sdr_dev->set_sensitive(false);
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
        if (togglebutton_play_beacon->get_active())
        {
            delete thread_downlink_beacon;
        }

        toolbutton_open_log_file->set_sensitive(true);
        toolbutton_close_log_file->set_sensitive(false);
        toolbutton_prev_log_line->set_sensitive(false);
        toolbutton_next_log_line->set_sensitive(false);
        radiobutton_beacon_src_sdr->set_sensitive(true);
        combobox_beacon_sdr_dev->set_sensitive(true);
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
    string bindata_dir = FSAT_GRS_OUTPUT_DIR;
    bindata_dir += FSAT_GRS_BINDATA_DIR;

    string cmd = "mkdir -p ";
    cmd += bindata_dir;
    system(cmd.c_str());

    cmd = "cp -a ";
    cmd += FSAT_GRS_GRC_BEACON_BIN;
    cmd += " ";
    cmd += bindata_dir;
    cmd += "/BEACON_`date +\"%Y-%m-%d_%H-%M-%S\"`.bin";
    system(cmd.c_str());
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
            
            thread_downlink_telemetry = new thread(&FSatGRS::RunGNURadioReceiver, this, FSAT_GRS_RX_TELEMETRY);
            thread_downlink_telemetry->detach(); 
            
            ngham_pkts_telemetry->open(FSAT_GRS_GRC_TELEMETRY_BIN, ifstream::in);
        }
        /*else if (radiobutton_telemetry_src_tcp->get_active())
        {
            
        }
        else if (radiobutton_telemetry_src_serial->get_active())
        {
            
        }*/
        else if (radiobutton_telemetry_src_file->get_active())
        {
            ngham_pkts_telemetry->open(filechooserbutton_telemetry->get_filename().c_str(), ifstream::in);
        }
        
        if (ngham_pkts_telemetry->is_open())
        {
            toolbutton_open_log_file->set_sensitive(false);
            toolbutton_close_log_file->set_sensitive(false);
            toolbutton_prev_log_line->set_sensitive(false);
            toolbutton_next_log_line->set_sensitive(false);
            radiobutton_telemetry_src_sdr->set_sensitive(false);
            combobox_telemetry_sdr_dev->set_sensitive(false);
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
        if (radiobutton_telemetry_src_sdr->get_active())
        {
            delete thread_downlink_telemetry;
        }
        
        toolbutton_open_log_file->set_sensitive(true);
        toolbutton_close_log_file->set_sensitive(false);
        toolbutton_prev_log_line->set_sensitive(false);
        toolbutton_next_log_line->set_sensitive(false);
        radiobutton_telemetry_src_sdr->set_sensitive(true);
        combobox_telemetry_sdr_dev->set_sensitive(true);
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
    string bindata_dir = FSAT_GRS_OUTPUT_DIR;
    bindata_dir += FSAT_GRS_BINDATA_DIR;

    string cmd = "mkdir -p ";
    cmd += bindata_dir;
    system(cmd.c_str());

    cmd = "cp -a ";
    cmd += FSAT_GRS_GRC_TELEMETRY_BIN;
    cmd += " ";
    cmd += bindata_dir;
    cmd += "/TELEMETRY_`date +\"%Y-%m-%d_%H-%M-%S\"`.bin";
    system(cmd.c_str());
}

void FSatGRS::OnButtonClearAllTelemetryClicked()
{
    telemetry_ngham_statistic->Clear();
    telemetry_data->Clear();
    telemetry_data->Display(true);
    filechooserbutton_telemetry->unselect_all();
}

//***************************************************************************************************************************************
//***************************************************************************************************************************************
//-- UPLINK -----------------------------------------------------------------------------------------------------------------------------
//***************************************************************************************************************************************
//***************************************************************************************************************************************
void FSatGRS::OnButtonGRSSchedulerClicked()
{
    int response = dialog_uplink_scheduler_manager->run();
    
    if ((response == Gtk::RESPONSE_DELETE_EVENT) or (response == Gtk::RESPONSE_CANCEL))
    {
        dialog_uplink_scheduler_manager->hide();
    }
}

void FSatGRS::OnToggleButtonPlayUplinkStreamToggled()
{
    if (togglebutton_play_uplink->get_active())
    {
        radiobutton_uplink_output_sdr->set_sensitive(false);
        combobox_uplink_output_sdr_device->set_sensitive(false);
        radiobutton_uplink_output_server->set_sensitive(false);
        entry_uplink_output_server_ip->set_sensitive(false);
        entry_uplink_output_server_port->set_sensitive(false);
        radiobutton_uplink_output_serial->set_sensitive(false);
        entry_uplink_output_serial_dev->set_sensitive(false);
        combobox_uplink_output_serial_baudrate->set_sensitive(false);
        radiobutton_uplink_grs_scheduler->set_sensitive(false);
        button_uplink_control_open_grs_scheduler->set_sensitive(false);
        radiobutton_uplink_server_control->set_sensitive(false);
        entry_uplink_server_ip->set_sensitive(false);
        entry_uplink_server_port->set_sensitive(false);
        radiobutton_uplink_manual_control->set_sensitive(false);
        
        togglebutton_play_uplink->set_sensitive(false);
        togglebutton_pause_uplink->set_sensitive(true);
        button_stop_uplink->set_sensitive(true);
        
        if (radiobutton_uplink_manual_control->get_active())
        {
            toolbutton_ping->set_sensitive(true);
            toolbutton_request_data->set_sensitive(true);
            toolbutton_shutdown->set_sensitive(true);
            toolbutton_reset_charge->set_sensitive(true);
            toolbutton_broadcast_message->set_sensitive(true);

            toolbutton_payload_x->set_sensitive(true);
        }
        
        event_log->AddNewEvent("New uplink stream started");
        
        if (radiobutton_uplink_output_server->get_active() or radiobutton_uplink_output_serial->get_active())
        {
            this->RaiseErrorMessage("Under development!", "The uplink output via a serial device or an external server will be available soon.");
            
            togglebutton_play_uplink->set_active(false);
        }
        /*else if (radiobutton_uplink_grs_scheduler->get_active() or radiobutton_uplink_server_control->get_active())
        {
            this->RaiseErrorMessage("Under development!", "The uplink control using the GRS scheduler or an external server will be available soon.");
            
            togglebutton_play_uplink->set_active(false);
        }*/
    }
    else
    {
        radiobutton_uplink_output_sdr->set_sensitive(true);
        combobox_uplink_output_sdr_device->set_sensitive(true);
        radiobutton_uplink_output_server->set_sensitive(true);
        entry_uplink_output_server_ip->set_sensitive(true);
        entry_uplink_output_server_port->set_sensitive(true);
        radiobutton_uplink_output_serial->set_sensitive(true);
        entry_uplink_output_serial_dev->set_sensitive(true);
        combobox_uplink_output_serial_baudrate->set_sensitive(true);
        radiobutton_uplink_grs_scheduler->set_sensitive(true);
        button_uplink_control_open_grs_scheduler->set_sensitive(true);
        radiobutton_uplink_server_control->set_sensitive(true);
        entry_uplink_server_ip->set_sensitive(true);
        entry_uplink_server_port->set_sensitive(true);
        radiobutton_uplink_manual_control->set_sensitive(true);
        togglebutton_play_uplink->set_sensitive(true);
        togglebutton_pause_uplink->set_sensitive(false);
        button_stop_uplink->set_sensitive(false);

        if (radiobutton_uplink_manual_control->get_active())
        {
            toolbutton_ping->set_sensitive(false);
            toolbutton_request_data->set_sensitive(false);
            toolbutton_shutdown->set_sensitive(false);
            toolbutton_reset_charge->set_sensitive(false);
            toolbutton_broadcast_message->set_sensitive(false);
            toolbutton_payload_x->set_sensitive(false);
        }

        event_log->AddNewEvent("Uplink stream finished");
    }
}

void FSatGRS::OnToggleButtonPauseUplinkStreamToggled()
{
    if (togglebutton_pause_uplink->get_active())
    {
        togglebutton_play_uplink->set_sensitive(false);
    }
    else
    {
        togglebutton_play_uplink->set_sensitive(true);
    }
}

void FSatGRS::OnButtonStopUplinkStreamClicked()
{
    togglebutton_play_uplink->set_active(false);
    togglebutton_pause_uplink->set_active(false);
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
    
    string cmd = "python ";

    if (this->CheckFile(FSAT_GRS_PLOT_SCRIPT))
    {
        cmd += FSAT_GRS_PLOT_SCRIPT;
    }
    else
    {
        cmd += FSAT_GRS_PLOT_SCRIPT_LOCAL;
    }
    
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

        cmd += checkbutton_plot_use_sat_time_beacon->get_active()? " \"1\"" : " \"0\"";

        thread thread_matplotlib_beacon(&FSatGRS::RunMatPlotLib, this, cmd.c_str());

        thread_matplotlib_beacon.detach();
    }
    
    string cmd2 = "python matplotlib/csv_plot.py";
    
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
                cmd2 += " \"IMU 2 Gyroscope Z\"";
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

        cmd2 += checkbutton_plot_use_sat_time_telemetry->get_active()? " \"1\"" : " \"0\"";

        thread thread_matplotlib_telemetry(&FSatGRS::RunMatPlotLib, this, cmd2.c_str());

        thread_matplotlib_telemetry.detach();
    }
    
    dialog_plot->hide();
}

void FSatGRS::OnButtonRunAnalysisClicked()
{
    string log_file(filechooserbutton_log_analysis->get_filename().c_str());
    
    if (log_file.size() > 0)
    {
        DataProcessing *log_analysis = new DataProcessing(log_file);
        
        Glib::RefPtr<Gtk::TextBuffer> textview_log_analysis_result_buffer = textview_log_analysis_result->get_buffer();
        
        if(radio_button_log_analysis_telemetry->get_active())
        {
            if (this->CheckFile(FSAT_GRS_VAL_TELEMETRY_SCRIPT))
            {
                textview_log_analysis_result_buffer->set_text(log_analysis->Validate(FSAT_GRS_VAL_TELEMETRY_SCRIPT).c_str());
            }
            else
            {
                textview_log_analysis_result_buffer->set_text(log_analysis->Validate(FSAT_GRS_VAL_TELEMETRY_SCRIPT_LOCAL).c_str());
            }
        }
        if(radio_button_log_analysis_beacon->get_active())
        {
            if (this->CheckFile(FSAT_GRS_VAL_BEACON_SCRIPT))
            {
                textview_log_analysis_result_buffer->set_text(log_analysis->Validate(FSAT_GRS_VAL_BEACON_SCRIPT).c_str());
            }
            else
            {
                textview_log_analysis_result_buffer->set_text(log_analysis->Validate(FSAT_GRS_VAL_BEACON_SCRIPT_LOCAL).c_str());
            }
        }
        
        delete log_analysis;
    }
    else
    {
        this->RaiseErrorMessage("No log file provided!", "To run a analysis, a log file must be provided.");
    }
}

void FSatGRS::OnButtonDataRequestSendClicked()
{
    string data_request_event = "Transmitting ";
    data_request_event += entry_config_uplink_burst->get_text();
    data_request_event += " data request(s)...";
    
    event_log->AddNewEvent(data_request_event.c_str());
    
    thread thread_request_cmd(&FSatGRS::RunGNURadioTransmitter, this, FSAT_GRS_UPLINK_REQUEST);
    
    thread_request_cmd.detach();
    
    dialog_data_request->hide();
}

void FSatGRS::OnButtonDataRequestCancelClicked()
{
    dialog_data_request->hide();
}

void FSatGRS::OnButtonBroadcastDialogSendClicked()
{
    if (entry_dialog_broadcast_message->get_text().size() <= 20)
    {
        string message_broadcast_event = "Transmitting ";
        message_broadcast_event += entry_config_uplink_burst->get_text();
        message_broadcast_event += " message(s) to broadcast...";

        event_log->AddNewEvent(message_broadcast_event.c_str());

        thread thread_broadcast_cmd(&FSatGRS::RunGNURadioTransmitter, this, FSAT_GRS_UPLINK_BROADCAST_MESSAGE);

        thread_broadcast_cmd.detach();

        dialog_broadcast_message->hide();
    }
    else
    {
        this->RaiseErrorMessage("The message is too large!", "The message to broadcast must be lesser or equal to 20 characters.");
    }
}

void FSatGRS::OnButtonBroadcastDialogCancelClicked()
{
    entry_dialog_broadcast_message->set_text("");

    dialog_broadcast_message->hide();
}

void FSatGRS::OnButtonShutdownAuthSendClicked()
{
    string user_hash = sha256(entry_sd_auth_user->get_text());
    string password_hash = sha256(entry_sd_auth_password->get_text());
    
    string homepath = getenv("HOME");
    
    ifstream file_users_read((homepath + FSAT_GRS_USERS_FILE).c_str(), ifstream::in);
    ifstream file_passwords_read((homepath + FSAT_GRS_USERS_PASSWORDS_FILE).c_str(), ifstream::in);
    
    if (file_users_read.is_open() and file_passwords_read.is_open())
    {
        string file_users_line;
        string file_passwords_line;
        
        while(getline(file_users_read, file_users_line) and getline(file_passwords_read, file_passwords_line))
        {
            if (file_users_line == user_hash)
            {
                if (file_passwords_line == password_hash)
                {
                    string shutdown_event = "Transmitting ";
                    shutdown_event += entry_config_uplink_burst->get_text();
                    shutdown_event += " shutdown command(s)...";
                    
                    event_log->AddNewEvent(shutdown_event.c_str());
                    
                    thread thread_shutdown_cmd(&FSatGRS::RunGNURadioTransmitter, this, FSAT_GRS_UPLINK_SHUTDOWN);
                    
                    thread_shutdown_cmd.detach();
                    
                    entry_sd_auth_user->set_text("");
                    entry_sd_auth_password->set_text("");
                    
                    dialog_shutdown_authentication->hide();
                    
                    return;
                }
            }
        }
        
        this->RaiseErrorMessage("Incorrect user or password!", "Try it again.");
    }
    else
    {
        this->RaiseErrorMessage("Users or passwords database not found!", "Try to create a new user in the preferences dialog.");
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
    string new_user = sha256(entry_config_general_new_user->get_text());
    
    if (sha256(entry_config_general_admin_user->get_text()) == FSAT_GRS_ADMIN_HASH)
    {
        if (sha256(entry_config_general_admin_password->get_text()) == FSAT_GRS_ADMIN_PASSWORD_HASH)
        {
            string homepath = getenv("HOME");
            
            ifstream file_users_read((homepath + FSAT_GRS_USERS_FILE).c_str(), ifstream::in);
            
            if (file_users_read.is_open())
            {
                string file_users_line;
                
                while(getline(file_users_read, file_users_line))
                {
                    if ((file_users_line == new_user) or (new_user == FSAT_GRS_ADMIN_HASH))
                    {
                        this->RaiseErrorMessage("This user already exist!", "Enter another user name.");
                        
                        return;
                    }
                }
            }
            
            if ((entry_config_general_new_password->get_text() == entry_config_general_admin_password_confirmation->get_text()) or (entry_config_general_new_password->get_text() == ""))
            {
                ofstream file_users((homepath + FSAT_GRS_USERS_FILE).c_str(), ofstream::out | ofstream::app);
                
                file_users << sha256(entry_config_general_new_user->get_text()) << "\n";
                
                file_users.close();
                
                ofstream file_users_passwords((homepath + FSAT_GRS_USERS_PASSWORDS_FILE).c_str(), ofstream::out | ofstream::app);
                
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
                this->RaiseErrorMessage("The new user's passwords are not equal!", "Or the password field is empty. Try it again.");
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

//***************************************************************************************************************************************
//***************************************************************************************************************************************
//-- UPLINK SCHEDULER MANAGER DIALOG ----------------------------------------------------------------------------------------------------
//***************************************************************************************************************************************
//***************************************************************************************************************************************
void FSatGRS::OnButtonUplinkSchedulerManagerAddClicked()
{
    int response = dialog_uplink_scheduler_manager_new_event->run();
    
    if ((response == Gtk::RESPONSE_DELETE_EVENT) or (response == Gtk::RESPONSE_CANCEL))
    {
        dialog_uplink_scheduler_manager_new_event->hide();
    }
}

void FSatGRS::OnButtonUplinkSchedulerManagerDeleteClicked()
{
    Glib::RefPtr<Gtk::TreeSelection> selection = treeview_uplink_scheduler_manager_events->get_selection();

    vector<Gtk::TreeModel::Path> paths = selection->get_selected_rows();
    
    for(int i=paths.size()-1; i>=0; i--)
    {
        liststore_uplink_events->erase(liststore_uplink_events->get_iter(paths[i]));

        uplink_events.erase(uplink_events.begin() + stoi(paths[i].to_string(), nullptr));
    }
}

void FSatGRS::OnButtonUplinkSchedulerManagerNewEventAddClicked()
{
    UplinkEventsColumns columns;
    
    Gtk::TreeModel::Row row = *(liststore_uplink_events->append());
    
    unsigned int uplink_events_pos = uplink_events.size();

    string cmd_name;
    switch(combobox_uplink_scheduler_manager_new_event_cmd->get_active_row_number())
    {
        case 0:
            cmd_name = "Ping";
            uplink_events.push_back(UplinkEvent(UPLINK_EVENT_TYPE_PING));
            break;
        case 1:
            cmd_name = "Data request";
            uplink_events.push_back(UplinkEvent(UPLINK_EVENT_TYPE_DATA_REQUEST));
            break;
        case 2:
            cmd_name = "Shutdown";
            uplink_events.push_back(UplinkEvent(UPLINK_EVENT_TYPE_SHUTDOWN));
            break;
        default:
            cmd_name = "Ping";
            uplink_events.push_back(UplinkEvent(UPLINK_EVENT_TYPE_PING));
            break;
    }
    
    string start_str = "-";
    string end_str = "-";
    if (switch_uplink_scheduler_manager_new_event_interval->get_active())
    {
        start_str = entry_uplink_scheduler_manager_new_event_start_time->get_text();
        start_str += "-";
        start_str += entry_uplink_scheduler_manager_new_event_start_date->get_text();
        
        end_str = entry_uplink_scheduler_manager_new_event_end_time->get_text();
        end_str += "-";
        end_str += entry_uplink_scheduler_manager_new_event_end_date->get_text();

        uplink_events[uplink_events_pos].SetInterval(entry_uplink_scheduler_manager_new_event_start_time->get_text(), entry_uplink_scheduler_manager_new_event_start_date->get_text(),
                                                     entry_uplink_scheduler_manager_new_event_end_time->get_text(), entry_uplink_scheduler_manager_new_event_end_date->get_text());
    }

    string period_str = "-";
    if (switch_uplink_scheduler_manager_new_event_period->get_active())
    {
        period_str = entry_uplink_scheduler_manager_new_event_period_value->get_text();

        uplink_events[uplink_events_pos].SetPeriod(stoi(period_str, nullptr));
    }

    string cycles_str = "-";
    if (switch_uplink_scheduler_manager_new_event_cycles->get_active())
    {
        cycles_str = entry_uplink_scheduler_manager_new_event_cycles_value->get_text();
        
        uplink_events[uplink_events_pos].SetCycles(stoi(cycles_str, nullptr));
    }

    row[columns.events_cmd]     = cmd_name;
    row[columns.events_start]   = start_str;
    row[columns.events_end]     = end_str;
    row[columns.events_period]  = period_str;
    row[columns.events_cycles]  = cycles_str;
    
    dialog_uplink_scheduler_manager_new_event->hide();
}

void FSatGRS::OnButtonUplinkSchedulerManagerNewEventCancelClicked()
{
    dialog_uplink_scheduler_manager_new_event->hide();
}

//***************************************************************************************************************************************
//***************************************************************************************************************************************
//-- ERRORS -----------------------------------------------------------------------------------------------------------------------------
//***************************************************************************************************************************************
//***************************************************************************************************************************************
void FSatGRS::RaiseErrorMessage(const char* error_title, const char* error_text)
{
    msg_dialog = new Gtk::MessageDialog(error_title, false, Gtk::MESSAGE_ERROR);
    msg_dialog->set_secondary_text(error_text);
    msg_dialog->set_transient_for(*window_fsat_grs);
    
    msg_dialog->run();
    
    delete msg_dialog;
}

//***************************************************************************************************************************************
//***************************************************************************************************************************************
//-- GNURADIO ---------------------------------------------------------------------------------------------------------------------------
//***************************************************************************************************************************************
//***************************************************************************************************************************************
void FSatGRS::RunGNURadioReceiver(uint8_t rx_type)
{
    string grc_cmd = "python -u ";

    if (this->CheckFile(FSAT_GRS_RX_GRC_SCRIPT))
    {
        grc_cmd += FSAT_GRS_RX_GRC_SCRIPT;
    }
    else
    {
        grc_cmd += FSAT_GRS_RX_GRC_SCRIPT_LOCAL;
    }

    switch(rx_type)
    {
        case FSAT_GRS_RX_BEACON:
            switch(combobox_beacon_sdr_dev->get_active_row_number())
            {
                case 0:     grc_cmd += " -d rtl=0";      break;
                case 1:     grc_cmd += " -d rtl=1";      break;
                case 2:     grc_cmd += " -d fcd=0";      break;
                case 3:     grc_cmd += " -d fcd=1";      break;
                case 4:     grc_cmd += " -d uhd=0";      break;
                case 5:     grc_cmd += " -d uhd=1";      break;
                default:    this->RaiseErrorMessage("Invalid SDR device!", "Check the SDR connection or model type.");
            }

            grc_cmd += " -f ";
            grc_cmd += entry_config_downlink_beacon_freq->get_text().c_str();

            grc_cmd += " -b ";
            grc_cmd += entry_config_downlink_beacon_baudrate->get_text().c_str();

            grc_cmd += " -p ";
            grc_cmd += entry_config_downlink_beacon_filter->get_text().c_str();

            grc_cmd += " -s ";
            grc_cmd += entry_config_downlink_beacon_sample_rate->get_text().c_str();
            
            grc_cmd += " -o ";
            grc_cmd += FSAT_GRS_GRC_BEACON_BIN;

            system(grc_cmd.c_str());

            break;
        case FSAT_GRS_RX_TELEMETRY:
            switch(combobox_telemetry_sdr_dev->get_active_row_number())
            {
                case 0:     grc_cmd += " -d rtl=0";      break;
                case 1:     grc_cmd += " -d rtl=1";      break;
                case 2:     grc_cmd += " -d fcd=0";      break;
                case 3:     grc_cmd += " -d fcd=1";      break;
                case 4:     grc_cmd += " -d uhd=0";      break;
                case 5:     grc_cmd += " -d uhd=1";      break;
                default:    this->RaiseErrorMessage("Invalid SDR device!", "Check the SDR connection or model type.");
            }

            grc_cmd += " -f ";
            grc_cmd += entry_config_downlink_telemetry_freq->get_text().c_str();

            grc_cmd += " -b ";
            grc_cmd += entry_config_downlink_telemetry_baudrate->get_text().c_str();

            grc_cmd += " -p ";
            grc_cmd += entry_config_downlink_telemetry_filter->get_text().c_str();

            grc_cmd += " -s ";
            grc_cmd += entry_config_downlink_telemetry_sample_rate->get_text().c_str();
            
            grc_cmd += " -o ";
            grc_cmd += FSAT_GRS_GRC_TELEMETRY_BIN;
            
            system(grc_cmd.c_str());

            break;
        default:
            this->RaiseErrorMessage("Invalid RX type!", "There is no receiver of this type.");
    }
}

void FSatGRS::RunGNURadioTransmitter(int uplink_type)
{
    NGHamPkts ngham_uplink_pkt;
    
    string homepath = getenv("HOME");        
    ofstream file_config((homepath + "/.fsat_grs/packet_flags.txt").c_str(), ofstream::out);    
    
    string grs_id = entry_config_general_gs_id->get_text();
    while(grs_id.size() < 6)
    {
        grs_id += " ";
    }
    
    uint8_t ping[9];
    uint8_t request[16];
    uint8_t shutdown[9];
    uint8_t reset_charge[9];
    uint8_t broadcast[30];
    uint8_t payload_x[30];
    request_data_packet_t rqt_packet; 
    unsigned int packets_number = 1;

    string cmd_str = "python -u ";

    if (this->CheckFile(FSAT_GRS_TX_GRC_SCRIPT))
    {
        cmd_str += FSAT_GRS_TX_GRC_SCRIPT;
    }
    else
    {
        cmd_str += FSAT_GRS_TX_GRC_SCRIPT_LOCAL;
    }

    switch(combobox_uplink_output_sdr_device->get_active_row_number())
    {
        case 0:     cmd_str += " -d uhd=0";    break;
        case 1:     cmd_str += " -d uhd=1";    break;
        case 2:     cmd_str += " -d uhd=2";    break;
        default:    cmd_str += " -d uhd=0";    break;
    }

    if (radiobutton_config_uplink_type_telemetry->get_active())
    {
        cmd_str += " -f ";
        cmd_str += entry_config_uplink_telemetry_frequency->get_text();
        cmd_str += " -b ";
        cmd_str += entry_config_downlink_telemetry_baudrate->get_text();
    }
    else if (radiobutton_config_uplink_type_beacon->get_active())
    {
        cmd_str += " -f ";
        cmd_str += entry_config_uplink_beacon_frequency->get_text();
        cmd_str += " -b ";
        cmd_str += entry_config_downlink_beacon_baudrate->get_text();
    }
    
    switch(uplink_type)
    {
        case FSAT_GRS_UPLINK_PING:
            for(unsigned int i=0; i<6; i++)
            {
                ping[i] = grs_id[i];
            }
            
            ping[6] = 'p';
            ping[7] = 'g';
            
            ngham_uplink_pkt.Generate(ping, 8);
            
            for(unsigned int i=0; i<stoi(entry_config_uplink_burst->get_text(), nullptr); i++)
            {
                system(cmd_str.c_str());
            }
            break;
        case FSAT_GRS_UPLINK_REQUEST:
            for(unsigned int i=0; i<6; i++)
            {
                request[i] = grs_id[i];
            }
                    
            rqt_packet.packages_count = stoi(entry_uplink_request_pkt_quant->get_text());
            rqt_packet.packages_origin = radiobutton_uplink_data_request_start->get_active()? NEWER_PACKAGES_ORIGIN : OLDER_PACKAGES_ORIGIN;
            rqt_packet.packages_offset = stoi(entry_uplink_request_offset->get_text());
            rqt_packet.flags = 0;

            //rqt_packet.flags =  (checkbutton_request_packet_flags->get_active()         ?   0x : 0);
            rqt_packet.flags =  (checkbutton_request_obdh_status->get_active()          ?   0x0001 : 0);
            rqt_packet.flags += (checkbutton_request_imu->get_active()                  ?   0x0002 : 0);
            rqt_packet.flags += (checkbutton_request_obdh_mis->get_active()             ?   0x0004 : 0);
            rqt_packet.flags += (checkbutton_request_solar_panels_sensors->get_active() ?   0x0008 : 0);
            rqt_packet.flags += (checkbutton_request_main_radio->get_active()           ?   0x0010 : 0);
            rqt_packet.flags += (checkbutton_request_solar_panels->get_active()         ?   0x0020 : 0);
            rqt_packet.flags += (checkbutton_request_eps_misc->get_active()             ?   0x0040 : 0);
            rqt_packet.flags += (checkbutton_request_battery_monitor->get_active()      ?   0x0080 : 0);
            rqt_packet.flags += (checkbutton_request_temperatures->get_active()         ?   0x0100 : 0);
            rqt_packet.flags += (checkbutton_request_task_scheduler->get_active()       ?   0x0200 : 0);
            rqt_packet.flags += (checkbutton_request_rush->get_active()                 ?   0x0400 : 0);
            
            file_config.write((char *)&(rqt_packet.flags), 2);
            file_config.close();

            request[6]  = REQUEST_DATA_TELECOMMAND    & 0xFF;
            request[7]  = REQUEST_DATA_TELECOMMAND>>8 & 0xFF;
            request[8]  = rqt_packet.flags>>8;
            request[9]  = rqt_packet.flags & 0xFF;
            request[10] = rqt_packet.packages_count;
            request[11] = rqt_packet.packages_origin;
            request[12] = rqt_packet.packages_offset>>24 & 0xFF;
            request[13] = rqt_packet.packages_offset>>16 & 0xFF;
            request[14] = rqt_packet.packages_offset>>8  & 0xFF;
            request[15] = rqt_packet.packages_offset     & 0xFF;

            ngham_uplink_pkt.Generate(request, 16);
            
            for(unsigned int i=0; i<stoi(entry_config_uplink_burst->get_text(), nullptr); i++)
            {
                system(cmd_str.c_str());
            }
            break;
        case FSAT_GRS_UPLINK_SHUTDOWN:
            for(unsigned int i=0; i<6; i++)
            {
                shutdown[i] = grs_id[i];
            }
            
            shutdown[6] = 's';
            shutdown[7] = 'd';
            
            ngham_uplink_pkt.Generate(shutdown, 8);
            
            packets_number = stoi(entry_config_uplink_burst->get_text(), nullptr);

            for(unsigned int i=0; i<packets_number; i++)
            {
                system(cmd_str.c_str());
            }
            break;
        case FSAT_GRS_UPLINK_RESET_CHARGE:
            for(unsigned int i=0; i<6; i++)
            {
                reset_charge[i] = grs_id[i];
            }

            reset_charge[6] = 'c';
            reset_charge[7] = 'r';

            ngham_uplink_pkt.Generate(reset_charge, 8);

            for(unsigned int i=0; i<stoi(entry_config_uplink_burst->get_text(), nullptr); i++)
            {
                system(cmd_str.c_str());
            }
            break;
        case FSAT_GRS_UPLINK_BROADCAST_MESSAGE:
            for(unsigned int i=0; i<6; i++)
            {
                broadcast[i] = grs_id[i];
            }

            broadcast[6] = 'r';
            broadcast[7] = 'p';

            for(unsigned int i=0; i<entry_dialog_broadcast_message->get_text().size(); i++)
            {
                broadcast[i+8] = entry_dialog_broadcast_message->get_text()[i];
            }

            ngham_uplink_pkt.Generate(broadcast, 8 + entry_dialog_broadcast_message->get_text().size());

            for(unsigned int i=0; i<stoi(entry_config_uplink_burst->get_text(), nullptr); i++)
            {
                system(cmd_str.c_str());
            }
            break;
        case FSAT_GRS_UPLINK_PAYLOAD_X_SWAP:
            for(unsigned int i=0; i<6; i++)
            {
                payload_x[i] = grs_id[i];
            }

            payload_x[6] = 'X';
            payload_x[7] = 'C';

            ngham_uplink_pkt.Generate(payload_x, 8);

            for(unsigned int i=0; i<stoi(entry_config_uplink_burst->get_text(), nullptr); i++)
            {
                system(cmd_str.c_str());
            }
            break;
    }
}

//***************************************************************************************************************************************
//***************************************************************************************************************************************
//-- MATPLOTLIB -------------------------------------------------------------------------------------------------------------------------
//***************************************************************************************************************************************
//***************************************************************************************************************************************
void FSatGRS::RunMatPlotLib(const char *cmd)
{
    system(cmd);
}

//***************************************************************************************************************************************
//***************************************************************************************************************************************
//-- PAYLOAD X --------------------------------------------------------------------------------------------------------------------------
//***************************************************************************************************************************************
//***************************************************************************************************************************************

void FSatGRS::OnButtonPayloadXSwapClicked()
{
    event_log->AddNewEvent("Transmitting swap command to Payload X...");

    thread thread_payload_x_swap_cmd(&FSatGRS::RunGNURadioTransmitter, this, FSAT_GRS_UPLINK_PAYLOAD_X_SWAP);

    thread_payload_x_swap_cmd.detach();
}

//***************************************************************************************************************************************
//***************************************************************************************************************************************
//-- CONFIGURATION ----------------------------------------------------------------------------------------------------------------------
//***************************************************************************************************************************************
//***************************************************************************************************************************************
void FSatGRS::LoadConfigs()
{
    string homepath = getenv("HOME");
    
    ifstream file_config((homepath + FSAT_GRS_CONFIG_FILE).c_str(), ifstream::in);
    
    if (file_config.is_open())
    {
        vector<string> configs_str;
        
        string file_config_line;
        
        while(getline(file_config, file_config_line))
        {
            configs_str.push_back(file_config_line);
        }
        
        file_config.close();
        
        entry_config_general_gs_id->set_text(configs_str[0]);
        entry_config_general_admin_user->set_text("");
        entry_config_general_admin_password->set_text("");
        entry_config_general_new_user->set_text("");
        entry_config_general_new_password->set_text("");
        entry_config_general_admin_password_confirmation->set_text("");
        checkbutton_log_ngham_packets->set_active((configs_str[1] == "1"? true : false));
        checkbutton_log_ax25_packets->set_active((configs_str[2] == "1"? true : false));
        checkbutton_log_beacon_data->set_active((configs_str[3] == "1"? true : false));
        checkbutton_log_telemetry_data->set_active((configs_str[4] == "1"? true : false));
        entry_config_downlink_beacon_freq->set_text(configs_str[5]);
        entry_config_downlink_beacon_baudrate->set_text(configs_str[6]);
        entry_config_downlink_beacon_filter->set_text(configs_str[7]);
        entry_config_downlink_beacon_sample_rate->set_text(configs_str[8]);
        entry_config_downlink_telemetry_freq->set_text(configs_str[9]);
        entry_config_downlink_telemetry_baudrate->set_text(configs_str[10]);
        entry_config_downlink_telemetry_filter->set_text(configs_str[11]);
        entry_config_downlink_telemetry_sample_rate->set_text(configs_str[12]);
        entry_config_uplink_burst->set_text(configs_str[13]);
        entry_config_uplink_telemetry_frequency->set_text(configs_str[14]);
        entry_config_uplink_beacon_frequency->set_text(configs_str[15]);
        radiobutton_config_uplink_type_telemetry->set_active((configs_str[16] == "1"? true : false));
        radiobutton_config_uplink_type_beacon->set_active((configs_str[17] == "1"? true : false));
    }
    else
    {
        this->LoadDefaultConfigs();
    }
}

void FSatGRS::SaveConfigs()
{
    string homepath = getenv("HOME");
    
    ofstream file_config((homepath + FSAT_GRS_CONFIG_FILE).c_str(), ofstream::out);
    
    file_config << entry_config_general_gs_id->get_text();
    file_config << "\n";
    file_config << (checkbutton_log_ngham_packets->get_active()? "1" : "0");
    file_config << "\n";
    file_config << (checkbutton_log_ax25_packets->get_active()? "1" : "0");
    file_config << "\n";
    file_config << (checkbutton_log_beacon_data->get_active()? "1" : "0");
    file_config << "\n";
    file_config << (checkbutton_log_telemetry_data->get_active()? "1" : "0");
    file_config << "\n";
    file_config << entry_config_downlink_beacon_freq->get_text();
    file_config << "\n";
    file_config << entry_config_downlink_beacon_baudrate->get_text();
    file_config << "\n";
    file_config << entry_config_downlink_beacon_filter->get_text();
    file_config << "\n";
    file_config << entry_config_downlink_beacon_sample_rate->get_text();
    file_config << "\n";
    file_config << entry_config_downlink_telemetry_freq->get_text();
    file_config << "\n";
    file_config << entry_config_downlink_telemetry_baudrate->get_text();
    file_config << "\n";
    file_config << entry_config_downlink_telemetry_filter->get_text();
    file_config << "\n";
    file_config << entry_config_downlink_telemetry_sample_rate->get_text();
    file_config << "\n";
    file_config << entry_config_uplink_burst->get_text();
    file_config << "\n";
    file_config << entry_config_uplink_telemetry_frequency->get_text();
    file_config << "\n";
    file_config << entry_config_uplink_beacon_frequency->get_text();
    file_config << "\n";
    file_config << (radiobutton_config_uplink_type_telemetry->get_active()? "1" : "0");
    file_config << "\n";
    file_config << (radiobutton_config_uplink_type_beacon->get_active()? "1" : "0");
    file_config << "\n";
    
    file_config.close();
}

void FSatGRS::LoadDefaultConfigs()
{
    entry_config_general_gs_id->set_text("PY0EFS");
    entry_config_general_admin_user->set_text("");
    entry_config_general_admin_password->set_text("");
    entry_config_general_new_user->set_text("");
    entry_config_general_new_password->set_text("");
    entry_config_general_admin_password_confirmation->set_text("");
    checkbutton_log_ngham_packets->set_active(true);
    checkbutton_log_ax25_packets->set_active(true);
    checkbutton_log_beacon_data->set_active(true);
    checkbutton_log_telemetry_data->set_active(true);
    entry_config_downlink_beacon_freq->set_text("145.9e6");
    entry_config_downlink_beacon_baudrate->set_text("1200");
    entry_config_downlink_beacon_filter->set_text("30e3");
    entry_config_downlink_beacon_sample_rate->set_text("1e6");
    entry_config_downlink_telemetry_freq->set_text("437.9e6");
    entry_config_downlink_telemetry_baudrate->set_text("2400");
    entry_config_downlink_telemetry_filter->set_text("50e3");
    entry_config_downlink_telemetry_sample_rate->set_text("1e6");
    entry_config_uplink_burst->set_text("1");
    entry_config_uplink_telemetry_frequency->set_text("437.9318e6");
    entry_config_uplink_beacon_frequency->set_text("145.911e6");
    radiobutton_config_uplink_type_telemetry->set_active(true);
    radiobutton_config_uplink_type_beacon->set_active(false);
}

bool FSatGRS::CheckFile(const char *file)
{
    struct stat buffer;

    return (stat(file, &buffer) == 0) ? true : false;
}

//! \} End of fsat_pkt_ana group
