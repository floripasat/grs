/*
 * fsat-grs.h
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
 * \brief Main class for the FSatGRS.
 * 
 * \author Gabriel Mariano Marcelino <gabriel.mm8@gmail.com>
 * 
 * \version 0.2.7
 * 
 * \date 10/09/2017
 * 
 * \defgroup fsat_grs FloripaSat GRS
 * \{
 */

#ifndef FSAT_GRS_H_
#define FSAT_GRS_H_

#include <gtkmm.h>
#include <vector>
#include <stdint.h>
#include <thread>

#include "uart.h"
#include "event_log.h"
#include "log.h"
#include "protocol_statistic.h"
#include "packet_data.h"
#include "ngham_pkts.h"
#include "read_log.h"
#include "uplink_event.h"

#define FSAT_PKT_ANA_DEFAULT_UI_FILE        "/usr/share/floripasat-grs/glade/fsat_grs_gui.glade"
#define FSAT_PKT_ANA_DEFAULT_UI_FILE_LOCAL  "glade/fsat_grs_gui.glade"

#define DATA_RECEPTION_SAMPLE_RATE          1000

#define FSAT_GRS_RX_BEACON                  0
#define FSAT_GRS_RX_TELEMETRY               1

#define FSAT_GRS_RX_GRC_SCRIPT              "/usr/share/floripasat-grs/gnuradio/gfsk_rx.py"
#define FSAT_GRS_TX_GRC_SCRIPT              "/usr/share/floripasat-grs/gnuradio/gfsk_tx.py"
#define FSAT_GRS_RX_GRC_SCRIPT_LOCAL        "gnuradio/gfsk_rx.py"
#define FSAT_GRS_TX_GRC_SCRIPT_LOCAL        "gnuradio/gfsk_tx.py"

#define FSAT_GRS_PLOT_SCRIPT                "/usr/share/floripasat-grs/matplotlib/csv_plot.py"
#define FSAT_GRS_PLOT_SCRIPT_LOCAL          "matplotlib/csv_plot.py"

#define FSAT_GRS_VAL_BEACON_SCRIPT          "/usr/share/floripasat-grs/validate_beacon.csv"
#define FSAT_GRS_VAL_TELEMETRY_SCRIPT       "/usr/share/floripasat-grs/validate_telemetry.csv"
#define FSAT_GRS_VAL_BEACON_SCRIPT_LOCAL    "validate_beacon.csv"
#define FSAT_GRS_VAL_TELEMETRY_SCRIPT_LOCAL "validate_telemetry.csv"

#define FSAT_GRS_GRC_BEACON_BIN             "/tmp/bin_data_beacon.bin"
#define FSAT_GRS_GRC_TELEMETRY_BIN          "/tmp/bin_data_telemetry.bin"

#define FSAT_GRS_OUTPUT_DIR                 "$HOME/floripasat-grs/"
#define FSAT_GRS_BINDATA_DIR                "bindata"

#define FSAT_GRS_CONFIG_FILE                "/.fsat_grs/fsat_grs.conf"

#define FSAT_GRS_USERS_FILE                 "/.fsat_grs/users.key"
#define FSAT_GRS_USERS_PASSWORDS_FILE       "/.fsat_grs/passwords.key"

#define FSAT_GRS_ADMIN_HASH                 "ff06535ac1029cca2fc2b86ac7355a7b4e0b8d839fc76b51d30833f4e1347ddc"
#define FSAT_GRS_ADMIN_PASSWORD_HASH        "59dbdb4f174e20b2c26bad7c5f8fd6f9be20e741e28070d31acc72d6b732925c"

/**
 * \brief Uplink commands.
 */
enum uplink_cmds_t
{
    FSAT_GRS_UPLINK_PING = 0,               /**< Ping. */
    FSAT_GRS_UPLINK_REQUEST,                /**< Data request. */
    FSAT_GRS_UPLINK_SHUTDOWN,               /**< Shutdown (hibernation). */
    FSAT_GRS_UPLINK_RESET_CHARGE,           /**< Reset EPS charge. */
    FSAT_GRS_UPLINK_BROADCAST_MESSAGE,      /**< Broadcast message. */
    FSAT_GRS_UPLINK_PAYLOAD_X_SWAP          /**< Payload X swap. */
};

/**
 * \brief FSat GRS class.
 */
class FSatGRS
{
        // Main window
        Gtk::Window                     *window_fsat_grs;
        
        // Toolbar
        Gtk::ToolButton                 *toolbutton_open_log_file;
        Gtk::FileChooserDialog          *filechooserdialog_log_viewer;
        Gtk::Button                     *button_log_viewer_cancel;
        Gtk::Button                     *button_log_viewer_open;
        Gtk::ToolButton                 *toolbutton_close_log_file;
        Gtk::ToolButton                 *toolbutton_prev_log_line;
        Gtk::ToolButton                 *toolbutton_next_log_line;
        Gtk::ToolButton                 *toolbutton_statistics;
        Gtk::ToolButton                 *toolbutton_plot;
        Gtk::ToolButton                 *toolbutton_ping;
        Gtk::ToolButton                 *toolbutton_request_data;
        Gtk::ToolButton                 *toolbutton_reset_charge;
        Gtk::ToolButton                 *toolbutton_broadcast_message;
        Gtk::ToolButton                 *toolbutton_shutdown;
        Gtk::ToolButton                 *toolbutton_payload_x;
        Gtk::ToolButton                 *toolbutton_schedule_cmd;
        Gtk::ToolButton                 *toolbutton_open_gpredict;
        Gtk::ToolButton                 *toolbutton_open_grqx;
        Gtk::ToolButton                 *toolbutton_config;
        Gtk::ToolButton                 *toolbutton_about;
        
        // Beacon stream
        Gtk::RadioButton                *radiobutton_beacon_src_sdr;
        Gtk::ComboBox                   *combobox_beacon_sdr_dev;
        Gtk::RadioButton                *radiobutton_beacon_src_tcp;
        Gtk::Entry                      *entry_beacon_tcp_ip;
        Gtk::Entry                      *entry_beacon_tcp_port;
        Gtk::RadioButton                *radiobutton_beacon_src_serial;
        Gtk::Entry                      *entry_beacon_serial_port;
        Gtk::ComboBox                   *combobox_beacon_baudrate;
        Gtk::RadioButton                *radiobutton_beacon_src_file;
        Gtk::FileChooserButton          *filechooserbutton_beacon;
        Gtk::ToggleButton               *togglebutton_play_beacon;
        Gtk::ToggleButton               *togglebutton_pause_beacon;
        Gtk::Button                     *button_stop_beacon;
        Gtk::Button                     *button_clear_all_beacon;
        
        // Telemetry stream
        Gtk::RadioButton                *radiobutton_telemetry_src_sdr;
        Gtk::ComboBox                   *combobox_telemetry_sdr_dev;
        Gtk::RadioButton                *radiobutton_telemetry_src_tcp;
        Gtk::Entry                      *entry_telemetry_tcp_ip;
        Gtk::Entry                      *entry_telemetry_tcp_port;
        Gtk::RadioButton                *radiobutton_telemetry_src_serial;
        Gtk::Entry                      *entry_telemetry_serial_port;
        Gtk::ComboBox                   *combobox_telemetry_baudrate;
        Gtk::RadioButton                *radiobutton_telemetry_src_file;
        Gtk::FileChooserButton          *filechooserbutton_telemetry;
        Gtk::ToggleButton               *togglebutton_play_telemetry;
        Gtk::ToggleButton               *togglebutton_pause_telemetry;
        Gtk::Button                     *button_stop_telemetry;
        Gtk::Button                     *button_clear_all_telemetry;
        
        // Uplink stream
        Gtk::RadioButton                *radiobutton_uplink_output_sdr;
        Gtk::ComboBox                   *combobox_uplink_output_sdr_device;
        Gtk::RadioButton                *radiobutton_uplink_output_server;
        Gtk::Entry                      *entry_uplink_output_server_ip;
        Gtk::Entry                      *entry_uplink_output_server_port;
        Gtk::RadioButton                *radiobutton_uplink_output_serial;
        Gtk::Entry                      *entry_uplink_output_serial_dev;
        Gtk::ComboBox                   *combobox_uplink_output_serial_baudrate;
        Gtk::RadioButton                *radiobutton_uplink_grs_scheduler;
        Gtk::Button                     *button_uplink_control_open_grs_scheduler;
        Gtk::RadioButton                *radiobutton_uplink_server_control;
        Gtk::Entry                      *entry_uplink_server_ip;
        Gtk::Entry                      *entry_uplink_server_port;
        Gtk::RadioButton                *radiobutton_uplink_manual_control;
        Gtk::ToggleButton               *togglebutton_play_uplink;
        Gtk::ToggleButton               *togglebutton_pause_uplink;
        Gtk::Button                     *button_stop_uplink;

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
        Gtk::Label                      *label_beacon_data_sp_i_my;
        Gtk::Label                      *label_beacon_data_sp_i_px;
        Gtk::Label                      *label_beacon_data_sp_i_mx;
        Gtk::Label                      *label_beacon_data_sp_i_pz;
        Gtk::Label                      *label_beacon_data_sp_i_mz;
        Gtk::Label                      *label_beacon_data_sp_i_py;
        Gtk::Label                      *label_beacon_data_sp_v_mypx;
        Gtk::Label                      *label_beacon_data_sp_v_mxpz;
        Gtk::Label                      *label_beacon_data_sp_v_mzpy;
        Gtk::Label                      *label_beacon_data_status_energy_level;
        Gtk::Label                      *label_beacon_data_status_imu;
        Gtk::Label                      *label_beacon_data_status_usd;
        Gtk::Label                      *label_beacon_data_status_rush;
        Gtk::Label                      *label_beacon_data_status_eps;
        Gtk::Label                      *label_beacon_data_status_antenna;
        Gtk::Label                      *label_beacon_data_imu_accel_x;
        Gtk::Label                      *label_beacon_data_imu_accel_y;
        Gtk::Label                      *label_beacon_data_imu_accel_z;
        Gtk::Label                      *label_beacon_data_imu_gyro_x;
        Gtk::Label                      *label_beacon_data_imu_gyro_y;
        Gtk::Label                      *label_beacon_data_imu_gyro_z;
        Gtk::Label                      *label_beacon_data_obdh_rst_value;
        Gtk::Label                      *label_beacon_data_system_time_value;
        
        // Telemetry Data
        Gtk::Label                      *label_telemetry_data_status_reset_counter;
        Gtk::Label                      *label_telemetry_data_status_reset_cause;
        Gtk::Label                      *label_telemetry_data_status_clock;
        Gtk::Label                      *label_telemetry_data_status_imu;
        Gtk::Label                      *label_telemetry_data_status_usd;
        Gtk::Label                      *label_telemetry_data_status_rush;
        Gtk::Label                      *label_telemetry_data_status_eps;
        Gtk::Label                      *label_telemetry_data_status_antenna;
        Gtk::Label                      *label_telemetry_data_uc_temp;
        Gtk::Label                      *label_telemetry_data_uc_voltage;
        Gtk::Label                      *label_telemetry_data_uc_current;
        Gtk::Label                      *label_telemetry_data_time_system;
        Gtk::Label                      *label_telemetry_data_time_system_up;
        Gtk::Label                      *label_telemetry_data_imu_accel_x;
        Gtk::Label                      *label_telemetry_data_imu_accel_y;
        Gtk::Label                      *label_telemetry_data_imu_accel_z;
        Gtk::Label                      *label_telemetry_data_imu_gyro_x;
        Gtk::Label                      *label_telemetry_data_imu_gyro_y;
        Gtk::Label                      *label_telemetry_data_imu_gyro_z;
        Gtk::Label                      *label_telemetry_data_sp_sun_p1;
        Gtk::Label                      *label_telemetry_data_sp_sun_p2;
        Gtk::Label                      *label_telemetry_data_sp_sun_p3;
        Gtk::Label                      *label_telemetry_data_sp_temp_p1;
        Gtk::Label                      *label_telemetry_data_sp_temp_p2;
        Gtk::Label                      *label_telemetry_data_sp_temp_p3;
        Gtk::Label                      *label_telemetry_data_eps_bat_mean_i;
        Gtk::Label                      *label_telemetry_data_eps_bat_temp;
        Gtk::Label                      *label_telemetry_data_eps_bat_1_volt;
        Gtk::Label                      *label_telemetry_data_eps_bat_2_volt;
        Gtk::Label                      *label_telemetry_data_eps_bat_current;
        Gtk::Label                      *label_telemetry_data_eps_bat_charge;
        Gtk::Label                      *label_telemetry_data_eps_bat_protection;
        Gtk::Label                      *label_telemetry_data_eps_bat_status;
        Gtk::Label                      *label_telemetry_data_eps_bat_cycles;
        Gtk::Label                      *label_telemetry_data_eps_bat_raac;
        Gtk::Label                      *label_telemetry_data_eps_bat_rsac;
        Gtk::Label                      *label_telemetry_data_eps_bat_rarc;
        Gtk::Label                      *label_telemetry_data_eps_bat_rsrc;
        Gtk::Label                      *label_telemetry_data_eps_sp_i_my;
        Gtk::Label                      *label_telemetry_data_eps_sp_i_px;
        Gtk::Label                      *label_telemetry_data_eps_sp_i_mx;
        Gtk::Label                      *label_telemetry_data_eps_sp_i_pz;
        Gtk::Label                      *label_telemetry_data_eps_sp_i_mz;
        Gtk::Label                      *label_telemetry_data_eps_sp_i_py;
        Gtk::Label                      *label_telemetry_data_eps_sp_v_mypx;
        Gtk::Label                      *label_telemetry_data_eps_sp_v_mxpz;
        Gtk::Label                      *label_telemetry_data_eps_sp_v_mzpy;
        Gtk::Label                      *label_telemetry_data_eps_misc_boost_v;
        Gtk::Label                      *label_telemetry_data_eps_misc_main_bus_v;
        Gtk::Label                      *label_telemetry_data_eps_misc_beacon_i;
        Gtk::Label                      *label_telemetry_data_eps_misc_uc_temp;
        Gtk::Label                      *label_telemetry_data_eps_misc_energy_level;
        
        // Telemetry Packets Statistic
        Gtk::Label                      *label_telemetry_pkt_statistic_total;
        Gtk::Label                      *label_telemetry_pkt_statistic_lost;
        
        // Preferences Dialog
        Gtk::Dialog                     *dialog_config;
        Gtk::Entry                      *entry_config_general_gs_id;
        Gtk::Entry                      *entry_config_general_admin_user;
        Gtk::Entry                      *entry_config_general_admin_password;
        Gtk::Entry                      *entry_config_general_new_user;
        Gtk::Entry                      *entry_config_general_new_password;
        Gtk::Entry                      *entry_config_general_admin_password_confirmation;
        Gtk::Button                     *button_config_general_add_new_user;
        Gtk::CheckButton                *checkbutton_log_ngham_packets;
        Gtk::CheckButton                *checkbutton_log_ax25_packets;
        Gtk::CheckButton                *checkbutton_log_beacon_data;
        Gtk::CheckButton                *checkbutton_log_telemetry_data;
        Gtk::Entry                      *entry_config_downlink_beacon_freq;
        Gtk::Entry                      *entry_config_downlink_beacon_baudrate;
        Gtk::Entry                      *entry_config_downlink_beacon_filter;
        Gtk::Entry                      *entry_config_downlink_beacon_sample_rate;
        Gtk::Entry                      *entry_config_downlink_telemetry_freq;
        Gtk::Entry                      *entry_config_downlink_telemetry_baudrate;
        Gtk::Entry                      *entry_config_downlink_telemetry_filter;
        Gtk::Entry                      *entry_config_downlink_telemetry_sample_rate;
        Gtk::Entry                      *entry_config_uplink_burst;
        Gtk::Entry                      *entry_config_uplink_telemetry_frequency;
        Gtk::Entry                      *entry_config_uplink_beacon_frequency;
        Gtk::RadioButton                *radiobutton_config_uplink_type_telemetry;
        Gtk::RadioButton                *radiobutton_config_uplink_type_beacon;
        Gtk::Button                     *button_config_ok;
        Gtk::Button                     *button_config_default;
        
        // About Dialog
        Gtk::AboutDialog                *aboutdialog;
        
        // Plot Dialog
        Gtk::Dialog                     *dialog_plot;
        Gtk::FileChooserButton          *filechooserbutton_plot_beacon;
        Gtk::ComboBox                   *combobox_plot_beacon_data;
        Gtk::CheckButton                *checkbutton_plot_beacon_connect_points;
        Gtk::CheckButton                *checkbutton_plot_beacon_best_curve;
        Gtk::CheckButton                *checkbutton_plot_save_pdf_beacon;
        Gtk::CheckButton                *checkbutton_plot_use_sat_time_beacon;
        Gtk::FileChooserButton          *filechooserbutton_plot_telemetry;
        Gtk::ComboBox                   *combobox_plot_telemetry_data;
        Gtk::CheckButton                *checkbutton_plot_telemetry_connect_points;
        Gtk::CheckButton                *checkbutton_plot_telemetry_best_curve;
        Gtk::CheckButton                *checkbutton_plot_save_pdf_telemetry;
        Gtk::CheckButton                *checkbutton_plot_use_sat_time_telemetry;
        Gtk::Button                     *button_plot;
        
        // Log Analysis Dialog
        Gtk::Dialog                     *dialog_log_statistics;
        Gtk::FileChooserButton          *filechooserbutton_log_analysis;
        Gtk::TextView                   *textview_log_analysis_result;
        Gtk::Button                     *button_run_log_analysis;
        Gtk::RadioButton                *radio_button_log_analysis_beacon;
        Gtk::RadioButton                *radio_button_log_analysis_telemetry;
        
        // Data Request Dialog
        Gtk::Dialog                     *dialog_data_request;
        Gtk::CheckButton                *checkbutton_request_packet_flags;
        Gtk::CheckButton                *checkbutton_request_obdh_status;
        Gtk::CheckButton                *checkbutton_request_imu;
        Gtk::CheckButton                *checkbutton_request_obdh_time;
        Gtk::CheckButton                *checkbutton_request_obdh_mis;
        Gtk::CheckButton                *checkbutton_request_solar_panels_sensors;
        Gtk::CheckButton                *checkbutton_request_main_radio;
        Gtk::CheckButton                *checkbutton_request_solar_panels;
        Gtk::CheckButton                *checkbutton_request_eps_misc;
        Gtk::CheckButton                *checkbutton_request_battery_monitor;
        Gtk::CheckButton                *checkbutton_request_temperatures;
        Gtk::CheckButton                *checkbutton_request_task_scheduler;
        Gtk::CheckButton                *checkbutton_request_rush;
        Gtk::Entry                      *entry_uplink_request_pkt_quant;
        Gtk::Entry                      *entry_uplink_request_offset;
        Gtk::RadioButton                *radiobutton_uplink_data_request_start;
        Gtk::RadioButton                *radiobutton_uplink_data_request_end;
        Gtk::Button                     *button_data_request_send;
        Gtk::Button                     *button_data_request_cancel;

        // Message Broadcast Dialog
        Gtk::Dialog                     *dialog_broadcast_message;
        Gtk::Entry                      *entry_dialog_broadcast_message;
        Gtk::Button                     *dialog_broadcast_message_send;
        Gtk::Button                     *dialog_broadcast_message_cancel;

        // Shutdown Command Authentication Dialog
        Gtk::Dialog                     *dialog_shutdown_authentication;
        Gtk::Entry                      *entry_sd_auth_user;
        Gtk::Entry                      *entry_sd_auth_password;
        Gtk::Button                     *button_sd_auth_send;
        Gtk::Button                     *button_sd_auth_cancel;

        // Uplink Scheduler Manager Dialog
        Gtk::Dialog                     *dialog_uplink_scheduler_manager;
        Gtk::TreeView                   *treeview_uplink_scheduler_manager_events;
        Glib::RefPtr<Gtk::ListStore>    liststore_uplink_events;
        Gtk::Button                     *button_uplink_scheduler_manager_add;
        Gtk::Button                     *button_uplink_scheduler_manager_delete;
        Gtk::Dialog                     *dialog_uplink_scheduler_manager_new_event;
        Gtk::ComboBox                   *combobox_uplink_scheduler_manager_new_event_cmd;
        Gtk::Switch                     *switch_uplink_scheduler_manager_new_event_interval;
        Gtk::Entry                      *entry_uplink_scheduler_manager_new_event_start_time;
        Gtk::Entry                      *entry_uplink_scheduler_manager_new_event_start_date;
        Gtk::Entry                      *entry_uplink_scheduler_manager_new_event_end_time;
        Gtk::Entry                      *entry_uplink_scheduler_manager_new_event_end_date;
        Gtk::Switch                     *switch_uplink_scheduler_manager_new_event_period;
        Gtk::Entry                      *entry_uplink_scheduler_manager_new_event_period_value;
        Gtk::Switch                     *switch_uplink_scheduler_manager_new_event_cycles;
        Gtk::Entry                      *entry_uplink_scheduler_manager_new_event_cycles_value;
        Gtk::Button                     *button_uplink_scheduler_manager_new_event_add;
        Gtk::Button                     *button_uplink_scheduler_manager_new_event_cancel;

        // Message Dialog
        Gtk::MessageDialog              *msg_dialog;
        
        /**
         * \brief 
         */
        UART                            *uart;
        /**
         * \brief 
         */
        EventLog                        *event_log;
        /**
         * \brief 
         */
        ProtocolStatistic               *ngham_statistic;
        /**
         * \brief 
         */
        //ProtocolStatistic               *ax25_statistic;
        /**
         * \brief 
         */
        ProtocolStatistic               *telemetry_ngham_statistic;
        /**
         * \brief 
         */
        PacketData                      *beacon_data;
        /**
         * \brief 
         */
        PacketData                      *telemetry_data;
        /**
         * \brief 
         */
        NGHamPkts                       *ngham_pkts_beacon;
        /**
         * \brief 
         */
        //AX25Pkts                        *ax25_pkts_beacon;
        /**
         * \brief 
         */
        NGHamPkts                       *ngham_pkts_telemetry;
        /**
         * \brief 
         */
        ReadLog                         *read_log;
        /**
         * \brief A vector to hold all the scheduled events.
         */
        std::vector<UplinkEvent>        uplink_events;
        
        //******************************************************************************************
        //******************************************************************************************
        //-- THREADS -------------------------------------------------------------------------------
        //******************************************************************************************
        //******************************************************************************************
        /**
         * \brief 
         */
        std::thread                     *thread_downlink_beacon;
        std::thread                     *thread_downlink_telemetry;
        //std::thread                     *thread_uplink;
        //std::thread                     *thread_plot;

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
         * \return 
         */
        void OnButtonLogViewerCancelClicked();
        /**
         * \brief 
         * 
         * \return 
         */
        void OnButtonLogViewerOpenClicked();
        /**
         * \brief 
         * 
         * \return 
         */
        void OnToolButtonCloseClicked();
        /**
         * \brief 
         * 
         * \return 
         */
        void OnToolButtonPrevClicked();
        /**
         * \brief 
         * 
         * \return 
         */
        void OnToolButtonNextClicked();
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
        void OnToolButtonPlotClicked();
        /**
         * \brief Ping button click signal handler.
         * 
         * \return None
         */
        void OnToolButtonPingClicked();
        /**
         * \brief Request data button click signal handler.
         * 
         * \return None
         */
        void OnToolButtonRequestDataClicked();
        /**
         * \brief Resets the charge value from EPS batteries.
         *
         * \return None
         */
        void OnToolButtonResetChargeClicked();
        /**
         * \brief Transmits a broadcast command with a custom message.
         *
         * \return None.
         */
        void OnToolButtonBroadcastMessageClicked();
        /**
         * \brief Shutdown command button click signal handler.
         * 
         * \return None
         */
        void OnToolButtonShutdownClicked();
        /**
         * \brief Payload X control click signal handler.
         *
         * \return None.
         */
        void OnToolButtonPayloadXClicked();
        /**
         * \brief Telecommand scheduler button click signal handler.
         * 
         * \return None
         */
        void OnToolButtonCmdSchedulerClicked();
        /**
         * \brief Open GPredict software.
         * 
         * \return None
         */
        void OnToolButtonOpenGPredictClicked();
        /**
         * \brief Open GQRX software.
         * 
         * \return None
         */
        void OnToolButtonOpenGQRXClicked();
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
        void OnButtonConfigOkClicked();
        /**
         * \brief 
         * 
         * \return None
         */
        void OnButtonConfigDefaultClicked();
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
        void OnButtonPlotClicked();
        /**
         * \brief 
         * 
         * \return None
         */
        void OnButtonRunAnalysisClicked();
        /**
         * \brief Sends the data request command.
         * 
         * \return None
         */
        void OnButtonDataRequestSendClicked();
        /**
         * \brief Cancels the data request
         * 
         * Closes the data request dialog.
         * 
         * \return None
         */
        void OnButtonDataRequestCancelClicked();
        /**
         * \brief Sends the broadcast command with a message.
         *
         * \return None.
         */
        void OnButtonBroadcastDialogSendClicked();
        /**
         * \brief Cancel and closes the broadcast message dialog.
         *
         * \return None.
         */
        void OnButtonBroadcastDialogCancelClicked();
        /**
         * \brief 
         * 
         * \return None
         */
        void OnButtonShutdownAuthSendClicked();
        /**
         * \brief 
         * 
         * \return None
         */
        void OnButtonShutdownAuthCancelClicked();
        /**
         * \brief 
         * 
         * \return None
         */
        void OnButtonAddNewUserClicked();
        /**
         * \brief 
         * 
         * \return None
         */
        void OnButtonGRSSchedulerClicked();
        /**
         * \brief 
         * 
         * \return None
         */
        void OnToggleButtonPlayUplinkStreamToggled();
        /**
         * \brief 
         * 
         * \return None
         */
        void OnToggleButtonPauseUplinkStreamToggled();
        /**
         * \brief 
         * 
         * \return None
         */
        void OnButtonStopUplinkStreamClicked();
        /**
         * \brief 
         * 
         * \return None
         */
        void OnButtonUplinkSchedulerManagerAddClicked();
        /**
         * \brief 
         * 
         * \return None
         */
        void OnButtonUplinkSchedulerManagerDeleteClicked();
        /**
         * \brief 
         * 
         * \return None
         */
        void OnButtonUplinkSchedulerManagerNewEventAddClicked();
        /**
         * \brief 
         * 
         * \return None
         */
        void OnButtonUplinkSchedulerManagerNewEventCancelClicked();

        /**
         * \brief 
         * 
         * \return None
         */
        void RaiseErrorMessage(const char* error_title, const char* error_text);
        /**
         * \brief 
         * 
         * \param beacon_receiver
         * 
         * \return None
         */
        void RunGNURadioReceiver(uint8_t rx_type=FSAT_GRS_RX_BEACON);
        /**
         * \brief 
         * 
         * \param uplink_type
         * 
         * \return None
         */
        void RunGNURadioTransmitter(int uplink_type);
        /**
         * \brief Plot a log data column using matplotlib.
         * 
         * \param cmd is the command with the arguments to run the python script to call matplotlib.
         * 
         * \return None
         */
        void RunMatPlotLib(const char *cmd);
        /**
         * \brief Load configuration parameters from a configuration parameters file.
         * 
         * \return None
         */
        void LoadConfigs();
        /**
         * \brief Save configuration parameters to a configuration parameters file.
         * 
         * \return None
         */
        void SaveConfigs();
        /**
         * \brief Load the default configuration parameters.
         * 
         * \return None
         */
        void LoadDefaultConfigs();

        /**
         * \brief Checks the existence of a file.
         *
         * \param file is the file to check the existence.
         *
         * \return TRUE/FALSE if the file exist or not.
         */
        bool CheckFile(const char *file);
    public:
        /**
         * \brief 
         * 
         * \return None
         */
        FSatGRS();
        /**
         * \brief 
         * 
         * \param ref_builder
         * 
         * \return None
         */
        FSatGRS(Glib::RefPtr<Gtk::Builder> ref_builder);
        /**
         * \brief 
         * 
         * \return None
         */
        ~FSatGRS();
        /**
         * \brief 
         * 
         * \param ref_builder
         * 
         * \return Status code.
         */
        int BuildWidgets(Glib::RefPtr<Gtk::Builder> ref_builder);
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

#endif // FSAT_GRS_H_

//! \} End of fsat_grs group
