/*
 * fsat-pkt-ana.cpp
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
 * \file fsat-pkt-ana.cpp
 * 
 * \brief .
 * 
 * \author Gabriel Mariano Marcelino <gabriel.mm8@gmail.com>
 * 
 * \version 2.0
 * 
 * \date 10/09/2017
 * 
 * \addtogroup fsat_pkt_ana
 * \{
 */

#include <fstream>
#include <string>
#include <cstdio>
#include <thread>

#include "fsat-pkt-ana.h"
#include "aux.hpp"

FSatPktAna::FSatPktAna()
{
    
}

FSatPktAna::FSatPktAna(Glib::RefPtr<Gtk::Builder> ref_builder, const char *ui_file)
{
    this->BuildWidgets(ref_builder, ui_file);
}

FSatPktAna::~FSatPktAna()
{
    //delete ngham_statistic;
    //delete ax25_statistic;
    //delete beacon_data;
    //delete telemetry_data;
    delete event_log;
    delete main_window;
}

int FSatPktAna::BuildWidgets(Glib::RefPtr<Gtk::Builder> ref_builder, const char *ui_file)
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
        toolbutton_open_log_file->signal_clicked().connect(sigc::mem_fun(*this, &FSatPktAna::OnToolButtonOpenClicked));
    }
    
    ref_builder->get_widget("toolbutton_config", toolbutton_config);
    if (toolbutton_config)
    {
        toolbutton_config->signal_clicked().connect(sigc::mem_fun(*this, &FSatPktAna::OnToolButtonConfigClicked));
    }
    
    ref_builder->get_widget("toolbutton_statistics", toolbutton_statistics);
    if (toolbutton_statistics)
    {
        toolbutton_statistics->signal_clicked().connect(sigc::mem_fun(*this, &FSatPktAna::OnToolButtonStatisticsClicked));
    }
    
    ref_builder->get_widget("toolbutton_gnuradio", toolbutton_gnuradio);
    if (toolbutton_gnuradio)
    {
        toolbutton_gnuradio->signal_clicked().connect(sigc::mem_fun(*this, &FSatPktAna::OnToolButtonRunClicked));
    }
    
    ref_builder->get_widget("toolbutton_about", toolbutton_about);
    if (toolbutton_about)
    {
        toolbutton_about->signal_clicked().connect(sigc::mem_fun(*this, &FSatPktAna::OnToolButtonAboutClicked));
    }
    
    // Beacon stream
    ref_builder->get_widget("filechooserbutton_beacon", filechooserbutton_beacon);
    
    ref_builder->get_widget("togglebutton_play_beacon", togglebutton_play_beacon);
    if (togglebutton_play_beacon)
    {
        togglebutton_play_beacon->signal_toggled().connect(sigc::mem_fun(*this, &FSatPktAna::OnToggleButtonPlayBeaconToggled));
    }
    
    ref_builder->get_widget("togglebutton_pause_beacon", togglebutton_pause_beacon);
    if (togglebutton_pause_beacon)
    {
        togglebutton_pause_beacon->signal_toggled().connect(sigc::mem_fun(*this, &FSatPktAna::OnToggleButtonPauseBeaconToggled));
    }
    
    ref_builder->get_widget("button_stop_beacon", button_stop_beacon);
    if (button_stop_beacon)
    {
        button_stop_beacon->signal_clicked().connect(sigc::mem_fun(*this, &FSatPktAna::OnButtonStopBeaconClicked));
    }
    
    ref_builder->get_widget("button_clear_all_beacon", button_clear_all_beacon);
    if (button_clear_all_beacon)
    {
        button_clear_all_beacon->signal_clicked().connect(sigc::mem_fun(*this, &FSatPktAna::OnButtonClearAllBeaconClicked));
    }
    
    // Telemetry stream
    ref_builder->get_widget("filechooserbutton_telemetry", filechooserbutton_telemetry);
    
    ref_builder->get_widget("togglebutton_play_telemetry", togglebutton_play_telemetry);
    if (togglebutton_play_telemetry)
    {
        togglebutton_play_telemetry->signal_toggled().connect(sigc::mem_fun(*this, &FSatPktAna::OnToggleButtonPlayTelemetryToggled));
    }
    
    ref_builder->get_widget("togglebutton_pause_telemetry", togglebutton_pause_telemetry);
    if (togglebutton_pause_telemetry)
    {
        togglebutton_pause_telemetry->signal_toggled().connect(sigc::mem_fun(*this, &FSatPktAna::OnToggleButtonPlayTelemetryToggled));
    }
    
    ref_builder->get_widget("button_stop_telemetry", button_stop_telemetry);
    if (button_stop_telemetry)
    {
        button_stop_telemetry->signal_clicked().connect(sigc::mem_fun(*this, &FSatPktAna::OnButtonStopTelemetryClicked));
    }
    
    ref_builder->get_widget("button_clear_all_telemetry", button_clear_all_telemetry);
    if (button_clear_all_telemetry)
    {
        button_clear_all_telemetry->signal_clicked().connect(sigc::mem_fun(*this, &FSatPktAna::OnButtonClearAllTelemetryClicked));
    }
    
    // Log checkbuttons
    ref_builder->get_widget("checkbutton_log_ngham_packets", checkbutton_log_ngham_packets);
    ref_builder->get_widget("checkbutton_log_ax25_packets", checkbutton_log_ax25_packets);
    ref_builder->get_widget("checkbutton_log_beacon_data", checkbutton_log_beacon_data);
    ref_builder->get_widget("checkbutton_log_telemetry_data", checkbutton_log_telemetry_data);
    
    // Serial port
    ref_builder->get_widget("entry_serial_port", entry_serial_port);
    ref_builder->get_widget("combobox_baudrate", combobox_baudrate);
    
    ref_builder->get_widget("togglebutton_open_close_port", togglebutton_open_close_port);
    if (togglebutton_open_close_port)
    {
        togglebutton_open_close_port->signal_toggled().connect(sigc::mem_fun(*this, &FSatPktAna::OnToggleButtonOpenClosePortToggled));
    }
    
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
    
    ax25_statistic = new ProtocolStatistic(label_ax25_valid_value, label_ax25_invalid_value, label_ax25_total_value, label_ax25_lost_value);
    
    // Beacon Data
    ref_builder->get_widget("label_beacon_data_bat1_v_value", label_beacon_data_bat1_v_value);
    ref_builder->get_widget("label_beacon_data_bat2_v_value", label_beacon_data_bat2_v_value);
    ref_builder->get_widget("label_beacon_data_bat1_t_value", label_beacon_data_bat1_t_value);
    ref_builder->get_widget("label_beacon_data_bat2_t_value", label_beacon_data_bat2_t_value);
    ref_builder->get_widget("label_beacon_data_bat_c_value", label_beacon_data_bat_c_value);
    ref_builder->get_widget("label_beacon_data_solar_panel_i_value1", label_beacon_data_solar_panel_i_value1);
    ref_builder->get_widget("label_beacon_data_solar_panel_i_value2", label_beacon_data_solar_panel_i_value2);
    ref_builder->get_widget("label_beacon_data_solar_panel_v_value", label_beacon_data_solar_panel_v_value);
    ref_builder->get_widget("label_beacon_data_sat_status_value", label_beacon_data_sat_status_value);
    ref_builder->get_widget("label_beacon_data_imu_data_value1", label_beacon_data_imu_data_value1);
    ref_builder->get_widget("label_beacon_data_imu_data_value2", label_beacon_data_imu_data_value2);
    ref_builder->get_widget("label_beacon_data_system_time_value", label_beacon_data_system_time_value);
    ref_builder->get_widget("label_beacon_data_obdh_rst_value", label_beacon_data_obdh_rst_value);
    
    beacon_data = new BeaconData(label_beacon_data_bat1_v_value, label_beacon_data_bat2_v_value, label_beacon_data_bat1_t_value, label_beacon_data_bat2_t_value,
                                 label_beacon_data_bat_c_value, label_beacon_data_solar_panel_i_value1, label_beacon_data_solar_panel_i_value2, label_beacon_data_solar_panel_v_value,
                                 label_beacon_data_sat_status_value, label_beacon_data_imu_data_value1, label_beacon_data_imu_data_value2, label_beacon_data_system_time_value,
                                 label_beacon_data_obdh_rst_value);
    
    // Telemetry data
    //telemetry_data = new TelemetryData();
    
    // Preferences window
    ref_builder->get_widget("window_config", window_config);
    
    // About dialog
    ref_builder->get_widget("aboutdialog", aboutdialog);
    
    return 0;
}

int FSatPktAna::Run(Glib::RefPtr<Gtk::Application> app)
{
    auto timer_slot = sigc::mem_fun(*this, &FSatPktAna::Timer);
    auto conn = Glib::signal_timeout().connect(timer_slot, DATA_RECEPTION_SAMPLE_RATE);
    
    return app->run(*main_window);
}
/*
std::vector<uint8_t> FSatPktAna::ProccessByte(uint8_t byte)
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

bool FSatPktAna::Timer()
{
    if (togglebutton_open_close_port->get_active())
    {
        /*int bytes_buf = uart->DataAvailable();
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
        }*/
    }
    
    if (togglebutton_play_beacon->get_active())
    {
        if (!togglebutton_pause_beacon->get_active())
        {
            ngham_pkts_beacon->Search(filechooserbutton_beacon->get_filename().c_str());
            //ax25_pkts_beacon->Search();
        }
    }
    
    if (togglebutton_play_telemetry->get_active())
    {
        if (!togglebutton_pause_telemetry->get_active())
        {
            ngham_pkts_telemetry->Search(filechooserbutton_telemetry->get_filename().c_str());
        }
    }
    
	return true;
}

void FSatPktAna::OnToolButtonOpenClicked()
{
    
}

void FSatPktAna::OnToolButtonConfigClicked()
{
    /*window_config->set_transient_for(*main_window);
    
    int response = window_config->show();
    
    if ((response == Gtk::RESPONSE_DELETE_EVENT) or (response == Gtk::RESPONSE_CANCEL))
    {
        window_config->hide();
    }*/
}

void FSatPktAna::OnToolButtonStatisticsClicked()
{
    
}

void FSatPktAna::OnToolButtonRunClicked()
{
    std::thread thread_gnuradio(&FSatPktAna::RunGNURadioReceiver, this);
    
    thread_gnuradio.detach();
}

void FSatPktAna::OnToolButtonAboutClicked()
{
    aboutdialog->set_transient_for(*main_window);
    
    int response = aboutdialog->run();
    
    if ((response == Gtk::RESPONSE_DELETE_EVENT) or (response == Gtk::RESPONSE_CANCEL))
    {
        aboutdialog->hide();
    }
}

void FSatPktAna::OnToggleButtonPlayBeaconToggled()
{
    if (togglebutton_play_beacon->get_active())
    {
        ngham_pkts_beacon = new NGHamPkts(event_log, beacon_data, ngham_statistic, checkbutton_log_ngham_packets->get_active(), checkbutton_log_beacon_data->get_active());
        
        ngham_pkts_beacon->open(filechooserbutton_beacon->get_filename().c_str(), std::ifstream::in);
        
        if (ngham_pkts_beacon->is_open())
        {
            filechooserbutton_beacon->set_sensitive(false);
            
            togglebutton_play_beacon->set_sensitive(false);
            togglebutton_pause_beacon->set_sensitive(true);
            button_stop_beacon->set_sensitive(true);
            
            button_clear_all_beacon->set_sensitive(false);
            
            checkbutton_log_ngham_packets->set_sensitive(false);
            checkbutton_log_ax25_packets->set_sensitive(false);
            checkbutton_log_beacon_data->set_sensitive(false);
            
            entry_serial_port->set_sensitive(false);
            combobox_baudrate->set_sensitive(false);
            togglebutton_open_close_port->set_sensitive(false);
            
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
        
        filechooserbutton_beacon->set_sensitive(true);
        
        togglebutton_play_beacon->set_sensitive(true);
        togglebutton_pause_beacon->set_sensitive(false);
        button_stop_beacon->set_sensitive(false);
        
        button_clear_all_beacon->set_sensitive(true);
        
        if (!togglebutton_play_telemetry->get_active())
        {
            checkbutton_log_ngham_packets->set_sensitive(true);
            checkbutton_log_ax25_packets->set_sensitive(true);
            entry_serial_port->set_sensitive(true);
            combobox_baudrate->set_sensitive(true);
            togglebutton_open_close_port->set_sensitive(true);
        }
        
        checkbutton_log_beacon_data->set_sensitive(true);
        
        event_log->AddNewEvent("Beacon stream finished");
    }
}

void FSatPktAna::OnToggleButtonPauseBeaconToggled()
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

void FSatPktAna::OnButtonStopBeaconClicked()
{
    togglebutton_play_beacon->set_active(false);
    togglebutton_pause_beacon->set_active(false);
}

void FSatPktAna::OnButtonClearAllBeaconClicked()
{
    ngham_statistic->Clear();
    ax25_statistic->Clear();
    beacon_data->Clear();
}

void FSatPktAna::OnToggleButtonPlayTelemetryToggled()
{
    if (togglebutton_play_telemetry->get_active())
    {
        filechooserbutton_telemetry->set_sensitive(false);
        
        togglebutton_play_telemetry->set_sensitive(false);
        togglebutton_pause_telemetry->set_sensitive(true);
        button_stop_telemetry->set_sensitive(true);
        
        button_clear_all_telemetry->set_sensitive(false);
        
        checkbutton_log_ngham_packets->set_sensitive(false);
        checkbutton_log_telemetry_data->set_sensitive(false);
        
        entry_serial_port->set_sensitive(false);
        combobox_baudrate->set_sensitive(false);
        togglebutton_open_close_port->set_sensitive(false);
        
        //ngham_pkts_telemetry = new NGHamPkts(event_log, telemetry_data);
    }
    else
    {
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
        
        if (!togglebutton_play_beacon->get_active())
        {
            entry_serial_port->set_sensitive(true);
            combobox_baudrate->set_sensitive(true);
            togglebutton_open_close_port->set_sensitive(true);
        }
        
        //delete ngham_pkts_telemetry;
    }
}

void FSatPktAna::OnToggleButtonPauseTelemetryToggled()
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

void FSatPktAna::OnButtonStopTelemetryClicked()
{
    togglebutton_play_telemetry->set_active(false);
    togglebutton_pause_telemetry->set_active(false);
}

void FSatPktAna::OnButtonClearAllTelemetryClicked()
{
    //telemetry_data->Clear();
}

void FSatPktAna::OnToggleButtonOpenClosePortToggled()
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
            
            this->OpenLogFiles();
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
            this->CloseLogFiles();
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

void FSatPktAna::OpenLogFiles()
{
    if (checkbutton_log_beacon_data->get_active())
    {
        log_beacon_data = new Log;
        log_beacon_data->open((LOG_DEFAULT_DIR "/BEACON_DATA_" + log_beacon_data->CurrentDateTime() + ".csv").c_str(), std::ofstream::out);
    }
}

void FSatPktAna::CloseLogFiles()
{    
    if (checkbutton_log_beacon_data->get_active())
    {
        delete log_beacon_data;
    }
}

void FSatPktAna::RaiseErrorMessage(const char* error_title, const char* error_text)
{
    msg_dialog = new Gtk::MessageDialog(error_title, false, Gtk::MESSAGE_ERROR);
    msg_dialog->set_secondary_text(error_text);
    msg_dialog->set_transient_for(*main_window);
    
    msg_dialog->run();
    
    delete msg_dialog;
}

void FSatPktAna::RunGNURadioReceiver()
{
    system("python gnuradio/fsat_grs.py");
}

//! \} End of fsat_pkt_ana group
