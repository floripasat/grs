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
 * \version 1.2
 * 
 * \date 10/09/2017
 * 
 * \addtogroup fsat_pkt_ana
 * \{
 */

#include <sstream>
#include <fstream>
#include <string>

#include "fsat-pkt-ana.h"
#include "aux.hpp"

extern "C"
{
    #include <libs/ngham/ngham.h>
}

FSatPktAna::FSatPktAna()
{
    
}

FSatPktAna::FSatPktAna(Glib::RefPtr<Gtk::Builder> ref_builder, const char *ui_file)
{
    receive_pkt = false;
    
    prev_fin_byte_counter = 0;
    fin_byte_counter = 0;
    
    serial_is_opened = false;
    
    this->BuildWidgets(ref_builder, ui_file);
}

FSatPktAna::~FSatPktAna()
{
    delete ngham_statistic;
    delete ax25_statistic;
    
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
    
    main_window->signal_show().connect(sigc::mem_fun(*this, &FSatPktAna::OnMainWindowShow));
    
    // Serial port
    ref_builder->get_widget("entry_serial_port", entry_serial_port);
    ref_builder->get_widget("combobox_baudrate", combobox_baudrate);
    
    ref_builder->get_widget("togglebutton_open_close_port", togglebutton_open_close_port);
    if (togglebutton_open_close_port)
    {
        togglebutton_open_close_port->signal_toggled().connect(sigc::mem_fun(*this, &FSatPktAna::OnToggleButtonOpenClosePortToggled));
    }
    
    // Log checkbuttons
    ref_builder->get_widget("checkbutton_log_raw_packets", checkbutton_log_raw_packets);
    ref_builder->get_widget("checkbutton_log_ngham_packets", checkbutton_log_ngham_packets);
    ref_builder->get_widget("checkbutton_log_ax25_packets", checkbutton_log_ax25_packets);
    ref_builder->get_widget("checkbutton_log_eps_data", checkbutton_log_data);
    
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
    
    // Packets
    ref_builder->get_widget("textview_raw_packets", textview_raw_packets);
    if (textview_raw_packets)
    {
        textview_raw_packets_buffer = textview_raw_packets->get_buffer();
    }
    
    ref_builder->get_widget("checkbutton_ngham_hex_output", checkbutton_ngham_hex_output);
    ref_builder->get_widget("textview_ngham_packets", textview_ngham_packets);
    if (textview_ngham_packets)
    {
        textview_ngham_packets_buffer = textview_ngham_packets->get_buffer();
    }
    
    ref_builder->get_widget("textview_ax25_packets", textview_ax25_packets);
    if (textview_ax25_packets)
    {
        textview_ax25_packets_buffer = textview_ax25_packets->get_buffer();
    }
    
    // Load raw packets
    ref_builder->get_widget("filechooserbutton_raw_packets", filechooserbutton_raw_packets);
    
    ref_builder->get_widget("togglebutton_play_stream", togglebutton_play_stream);
    if (togglebutton_play_stream)
    {
        togglebutton_play_stream->signal_toggled().connect(sigc::mem_fun(*this, &FSatPktAna::OnToggleButtonPlayStreamToggled));
    }
    
    ref_builder->get_widget("image_play_button", image_play_button);
    ref_builder->get_widget("image_stop_button", image_stop_button);
    
    ref_builder->get_widget("button_load_raw_packets", button_load_raw_packets);
    if (button_load_raw_packets)
    {
        button_load_raw_packets->signal_clicked().connect(sigc::mem_fun(*this, &FSatPktAna::OnButtonLoadRawPacketsClicked));
    }
    
    // Clear all
    ref_builder->get_widget("button_clear_all", button_clear_all);
    if (button_clear_all)
    {
        button_clear_all->signal_clicked().connect(sigc::mem_fun(*this, &FSatPktAna::OnButtonClearAllClicked));
    }
    
    // NGHam statistic
    ref_builder->get_widget("label_ngham_valid_value", label_ngham_valid_value);
    ref_builder->get_widget("label_ngham_invalid_value", label_ngham_invalid_value);
    ref_builder->get_widget("label_ngham_total_value", label_ngham_total_value);
    ref_builder->get_widget("label_ngham_lost_value", label_ngham_lost_value);
    
    // AX25 statistic
    ref_builder->get_widget("label_ax25_valid_value", label_ax25_valid_value);
    ref_builder->get_widget("label_ax25_invalid_value", label_ax25_invalid_value);
    ref_builder->get_widget("label_ax25_total_value", label_ax25_total_value);
    ref_builder->get_widget("label_ax25_lost_value", label_ax25_lost_value);
    
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
    
    // About
    ref_builder->get_widget("button_about", button_about);
    if (button_about)
    {
        button_about->signal_clicked().connect(sigc::mem_fun(*this, &FSatPktAna::OnButtonAboutClicked));
    }
    
    ref_builder->get_widget("aboutdialog", aboutdialog);
    
    return 0;
}

int FSatPktAna::Run(Glib::RefPtr<Gtk::Application> app)
{
    auto timer_slot = sigc::mem_fun(*this, &FSatPktAna::Timer);
    auto conn = Glib::signal_timeout().connect(timer_slot, DATA_RECEPTION_SAMPLE_RATE);
    
    return app->run(*main_window);
}

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
                receive_pkt = false;
                ngham_statistic->AddValidPkt();
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
}

void FSatPktAna::DisplayBeaconData(uint8_t *data, uint8_t len)
{
    /*if (len > 10)
    {
        label_beacon_data_bat1_v_value->set_text(ToConstChar(BatVoltConv((data[10] << 8) | data[11])));
        label_beacon_data_bat2_v_value->set_text(ToConstChar(BatVoltConv((data[12] << 8) | data[13])));
        label_beacon_data_bat1_t_value->set_text(ToConstChar(BatTempConv(0xFFFF)));
        label_beacon_data_bat2_t_value->set_text(ToConstChar(BatTempConv(0xFFFF)));
        label_beacon_data_bat_c_value->set_text(ToConstChar(BatChargeConv((data[20] << 8) | data[21])));
        label_beacon_data_solar_panel_i_value1->set_text(ToConstChar(SolarPanelCurrentConv((data[22] << 8) | data[23])) );// "/" ToConstChar(SolarPanelCurrentConv((data[24] << 8) | data[25]))) "/" ToConstChar(SolarPanelCurrentConv((data[26] << 8) | data[27]))));
        label_beacon_data_solar_panel_i_value2->set_text(ToConstChar(SolarPanelCurrentConv((data[28] << 8) | data[29])) );//"/" ToConstChar(SolarPanelCurrentConv((data[30] << 8) | data[31]))) "/" ToConstChar(SolarPanelCurrentConv((data[32] << 8) | data[33]))));
        label_beacon_data_solar_panel_v_value->set_text(ToConstChar(SolarPanelVoltageConv((data[34] << 8) | data[35])) );//"/" ToConstChar(SolarPanelVoltageConv((data[36] << 8) | data[37])) "/" ToConstChar(SolarPanelVoltageConv((data[38] << 8) | data[39])));
        
        if (len > 40)
        {
            label_beacon_data_sat_status_value->set_text(ToConstChar((data[40] << 8) | data[41]));
            label_beacon_data_imu_data_value1->set_text(ToConstChar(IMUAccelConv((data[42] << 8) | data[43])) );//"/" ToConstChar(IMUAccelConv((data[44] << 8) | data[45])) "/" ToConstChar(IMUAccelConv((data[46] << 8) | data[47])));
            label_beacon_data_imu_data_value2->set_text(ToConstChar(IMUGyroConv((data[48] << 8) | data[49])) );//"/" ToConstChar(IMUGyroConv((data[50] << 8) | data[51])) "/" ToConstChar(IMUGyroConv((data[52] << 8) | data[53])));
            label_beacon_data_system_time_value->set_text(ToConstChar((data[54] << 24) | (data[55] << 16) | (data[56] << 8) | data[57]));
            label_beacon_data_obdh_rst_value->set_text(ToConstChar((data[58] << 8) | data[59]));
        }
        else
        {
            label_beacon_data_sat_status_value->set_text("-");
            label_beacon_data_imu_data_value1->set_text("-");
            label_beacon_data_imu_data_value2->set_text("-");
            label_beacon_data_system_time_value->set_text("-");
            label_beacon_data_obdh_rst_value->set_text("-");
        }
    }
    else
    {
        label_beacon_data_sat_status_value->set_text("-");
        label_beacon_data_imu_data_value1->set_text("-");
        label_beacon_data_imu_data_value2->set_text("-");
        label_beacon_data_system_time_value->set_text("-");
        label_beacon_data_obdh_rst_value->set_text("-");
    }*/
}

bool FSatPktAna::Timer()
{
    if (togglebutton_open_close_port->get_active())
    {
        int bytes_buf = uart->DataAvailable();
        if (bytes_buf > 0)
        {
            if (checkbutton_log_raw_packets->get_active())
            {
                *log_raw_pkts << log_raw_pkts->CurrentDateTime(LOG_DATA_TIME_FOR_LOG_CSV);
            }
            
            while(bytes_buf--)
            {
                uint8_t byte = uart->GetByte();
                
                std::string b = HexToStr(byte);
                
                textview_raw_packets_buffer->insert_at_cursor(b.c_str());
                textview_raw_packets_buffer->insert_at_cursor(", ");
                
                if (checkbutton_log_raw_packets->get_active())
                {
                    *log_raw_pkts << b << ",";
                }
                
                auto iter_raw = textview_raw_packets_buffer->end();
                textview_raw_packets->scroll_to(iter_raw);
                
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
                        if (checkbutton_ngham_hex_output->get_active())
                        {
                            textview_ngham_packets_buffer->insert_at_cursor(HexToStr(r[i]).c_str());
                            textview_ngham_packets_buffer->insert_at_cursor(" ");
                        }
                        else
                        {
                            textview_ngham_packets_buffer->insert_at_cursor(b_ngham.c_str());
                        }
                        if (checkbutton_log_ngham_packets->get_active())
                        {
                            *log_ngham_pkts << b_ngham;
                        }
                    }
                    
                    textview_ngham_packets_buffer->insert_at_cursor("\n");
                    
                    if (checkbutton_log_ngham_packets->get_active())
                    {
                        *log_ngham_pkts << "\n";
                    }
                    
                    auto iter_ngham = textview_ngham_packets_buffer->end();
                    textview_ngham_packets->scroll_to(iter_ngham);
                }
                
                // AX25 packets  >>>>>>>>> TO BE IMPLEMENTED
            }
            
            textview_raw_packets_buffer->insert_at_cursor("\n\n");
            if (checkbutton_log_raw_packets->get_active())
            {
                *log_raw_pkts << "\n";
            }
        }
    }
    
    if (togglebutton_play_stream->get_active())
    {
        this->SearchPackets();
    }
    
	return true;
}

void FSatPktAna::OnMainWindowShow()
{
    ngham_Init();
    
    ngham_statistic = new ProtocolStatistic(label_ngham_valid_value, label_ngham_invalid_value, label_ngham_total_value, label_ngham_lost_value);
    ax25_statistic = new ProtocolStatistic(label_ax25_valid_value, label_ax25_invalid_value, label_ax25_total_value, label_ax25_lost_value);
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
            checkbutton_log_raw_packets->set_sensitive(false);
            checkbutton_log_ngham_packets->set_sensitive(false);
            checkbutton_log_ax25_packets->set_sensitive(false);
            checkbutton_log_data->set_sensitive(false);
            filechooserbutton_raw_packets->set_sensitive(false);
            togglebutton_play_stream->set_sensitive(false);
            button_load_raw_packets->set_sensitive(false);
            
            this->OpenLogFiles();
            
            serial_is_opened = true;
        }
        else
        {
            delete uart;
            
            this->RaiseErrorMessage("Error opening the serial port!", "Verify if the device is connected or the address is correct!");
            
            serial_is_opened = false;
            
            togglebutton_open_close_port->set_active(false);
        }
    }
    else
    {
        if (serial_is_opened)
        {
            delete uart;
            this->CloseLogFiles();
        }
        
        serial_is_opened = false;
        
        entry_serial_port->set_sensitive(true);
        combobox_baudrate->set_sensitive(true);
        checkbutton_log_raw_packets->set_sensitive(true);
        checkbutton_log_ngham_packets->set_sensitive(true);
        checkbutton_log_ax25_packets->set_sensitive(true);
        checkbutton_log_data->set_sensitive(true);
        filechooserbutton_raw_packets->set_sensitive(true);
        togglebutton_play_stream->set_sensitive(true);
        button_load_raw_packets->set_sensitive(true);
    }
}

void FSatPktAna::OnToggleButtonPlayStreamToggled()
{
    if (togglebutton_play_stream->get_active())
    {
        togglebutton_play_stream->set_image(*image_stop_button);
        
        entry_serial_port->set_sensitive(false);
        combobox_baudrate->set_sensitive(false);
        togglebutton_open_close_port->set_sensitive(false);
        checkbutton_log_raw_packets->set_sensitive(false);
        checkbutton_log_ngham_packets->set_sensitive(false);
        checkbutton_log_ax25_packets->set_sensitive(false);
        checkbutton_log_data->set_sensitive(false);
        filechooserbutton_raw_packets->set_sensitive(false);
        button_load_raw_packets->set_sensitive(false);
        button_clear_all->set_sensitive(false);
        
        this->OpenLogFiles();
    }
    else
    {
        this->CloseLogFiles();
        
        togglebutton_play_stream->set_image(*image_play_button);
        
        entry_serial_port->set_sensitive(true);
        combobox_baudrate->set_sensitive(true);
        togglebutton_open_close_port->set_sensitive(true);
        checkbutton_log_raw_packets->set_sensitive(true);
        checkbutton_log_ngham_packets->set_sensitive(true);
        checkbutton_log_ax25_packets->set_sensitive(true);
        checkbutton_log_data->set_sensitive(true);
        filechooserbutton_raw_packets->set_sensitive(true);
        button_load_raw_packets->set_sensitive(true);
        button_clear_all->set_sensitive(true);
    }
}

void FSatPktAna::OnButtonLoadRawPacketsClicked()
{
    this->SearchPackets();
}

void FSatPktAna::OnButtonClearAllClicked()
{
    prev_fin_byte_counter = 0;
    fin_byte_counter = 0;
    
    ngham_statistic->Clear();
    ax25_statistic->Clear();
    
    textview_raw_packets_buffer->set_text("");
    textview_ngham_packets_buffer->set_text("");
    textview_ax25_packets_buffer->set_text("");
    
    label_beacon_data_bat1_v_value->set_text("-");
    label_beacon_data_bat2_v_value->set_text("-");
    label_beacon_data_bat1_t_value->set_text("-");
    label_beacon_data_bat2_t_value->set_text("-");
    label_beacon_data_bat_c_value->set_text("-");
    label_beacon_data_solar_panel_i_value1->set_text("-");
    label_beacon_data_solar_panel_i_value2->set_text("-");
    label_beacon_data_solar_panel_v_value->set_text("-");
    label_beacon_data_sat_status_value->set_text("-");
    label_beacon_data_imu_data_value1->set_text("-");
    label_beacon_data_imu_data_value2->set_text("-");
    label_beacon_data_system_time_value->set_text("-");
    label_beacon_data_obdh_rst_value->set_text("-");
}

void FSatPktAna::OnButtonAboutClicked()
{
    aboutdialog->set_transient_for(*main_window);
    
    int response = aboutdialog->run();
    
    if ((response == Gtk::RESPONSE_DELETE_EVENT) or (response == Gtk::RESPONSE_CANCEL))
    {
        aboutdialog->hide();
    }
}

void FSatPktAna::SearchPackets()
{
    std::ifstream fin;
    
    fin.open(filechooserbutton_raw_packets->get_filename().c_str(), std::ifstream::in);
    
    if (!fin.is_open())
    {
        this->RaiseErrorMessage("Error opening this file!", "Maybe the current file is not valid!");
        
        if (togglebutton_play_stream->get_active())
        {
            togglebutton_play_stream->set_active(false);
        }
    }
    else
    {
        std::vector<uint8_t> sync_bytes;
        
        sync_bytes.push_back(EntryToHex(entry_ngham_sync_bytes_s3->get_text()));
        sync_bytes.push_back(EntryToHex(entry_ngham_sync_bytes_s2->get_text()));
        sync_bytes.push_back(EntryToHex(entry_ngham_sync_bytes_s1->get_text()));
        sync_bytes.push_back(EntryToHex(entry_ngham_sync_bytes_s0->get_text()));
        
        std::vector<uint8_t> sync_bits_buffer;
        
        uint32_t byte_counter = 0;
        
        while(!fin.eof())
        {
            uint8_t byte;
            fin >> byte;
            fin_byte_counter++;
            
            if (fin_byte_counter <= prev_fin_byte_counter)
            {                
                continue;
            }
            else
            {
                prev_fin_byte_counter = fin_byte_counter;
            }
            
            if (!receive_pkt)
            {
                sync_bits_buffer.push_back(byte);
                if (sync_bits_buffer.size() == sync_bytes.size()*8)  // 1 byte = 8 bits
                {
                    std::vector<uint8_t> sync_bytes_buffer(sync_bytes.size(), 0x00);
                    unsigned int j = 7;
                    unsigned int k = 0;
                    for(unsigned int l=0;l<sync_bits_buffer.size();l++)
                    {
                        sync_bytes_buffer[k] |= (uint8_t)(sync_bits_buffer[l] << j);
                        if (j == 0)
                        {
                            j = 7;
                            k++;
                        }
                        else
                        {
                            j--;
                        }
                    }
                    
                    if (sync_bytes_buffer == sync_bytes)
                    {
                        receive_pkt = true;
                    }
                    
                    sync_bits_buffer.erase(sync_bits_buffer.begin());
                }
            }
            else
            {
                byte_buffer.push_back(byte);
                if (byte_buffer.size() == 8)
                {
                    uint8_t byte = 0x00;
                    unsigned int k = 8-1;
                    for(unsigned int j=0;j<byte_buffer.size();j++)
                    {
                        byte |= (uint8_t)(byte_buffer[j] << k);
                        k--;
                    }
                    
                    if ((byte == 125) and (byte_counter == 0))
                    {
                        receive_pkt = false;
                    }
                    else
                    {
                        byte_counter++;
                        
                        uint8_t data[256];
                        uint8_t data_len;
                        switch(ngham_Decode(byte, data, &data_len))
                        {
                            case PKT_CONDITION_OK:                                
                                if (checkbutton_log_ngham_packets->get_active())
                                {
                                    *log_ngham_pkts << "V," << log_ngham_pkts->CurrentDateTime(LOG_DATA_TIME_FOR_LOG_CSV);
                                }
                                
                                for(unsigned int j=0; j<data_len; j++)
                                {
                                    std::stringstream byte_str;
                                    byte_str << (char)data[j];
                                    std::string b = byte_str.str();
                                    if (checkbutton_ngham_hex_output->get_active())
                                    {
                                        textview_ngham_packets_buffer->insert_at_cursor(HexToStr(data[j]).c_str());
                                        textview_ngham_packets_buffer->insert_at_cursor(" ");
                                    }
                                    else
                                    {
                                        textview_ngham_packets_buffer->insert_at_cursor(b.c_str());
                                    }
                                    if (checkbutton_log_ngham_packets->get_active())
                                    {
                                        *log_ngham_pkts << b;
                                    }
                                }
                                textview_ngham_packets_buffer->insert_at_cursor("\n");
                                
                                if (checkbutton_log_ngham_packets->get_active())
                                {
                                    *log_ngham_pkts << "\n";
                                }
                                
                                ngham_statistic->AddValidPkt();
                                this->DisplayBeaconData(data, data_len);
                                
                                receive_pkt = false;
                                
                                byte_counter = 0;
                                
                                break;
                            case PKT_CONDITION_PREFAIL:
                                break;
                            case PKT_CONDITION_FAIL:
                                textview_ngham_packets_buffer->insert_at_cursor("ERROR!\n");
                                
                                if (checkbutton_log_ngham_packets->get_active())
                                {
                                    *log_ngham_pkts << "I," << log_ngham_pkts->CurrentDateTime(LOG_DATA_TIME_FOR_LOG_CSV) << ",\n";
                                }
                                
                                ngham_statistic->AddInvalidPkt();
                                
                                receive_pkt = false;
                                byte_counter = 0;
                                break;
                        }
                    }
                    
                    byte_buffer.clear();
                }
            }
        }
        
        fin_byte_counter = 0;
        
        fin.close();
    }
}

void FSatPktAna::OpenLogFiles()
{
    /*if (checkbutton_log_raw_packets->get_active())
    {
        log_raw_pkts = new Log;
        log_raw_pkts->open((LOG_DEFAULT_DIR "/RAW_" + log_raw_pkts->CurrentDateTime() + ".csv").c_str(), std::ofstream::out);
    }*/
    
    if (checkbutton_log_ngham_packets->get_active())
    {
        log_ngham_pkts = new Log;
        log_ngham_pkts->open((LOG_DEFAULT_DIR "/NGHAM_" + log_ngham_pkts->CurrentDateTime() + ".csv").c_str(), std::ofstream::out);
    }
    
    /*if (widgets.checkbutton_log_ax25_packets->get_active())
    {
        log_ax25_pkts = new Log;
        log_ax25_pkts->open((LOG_DEFAULT_DIR "/AX25_" + log_ax25_pkts->CurrentDateTime() + ".csv").c_str(), std::ofstream::out);
    }*/
    
    if (checkbutton_log_data->get_active())
    {
        log_data_pkts = new Log;
        log_data_pkts->open((LOG_DEFAULT_DIR "/DATA_" + log_data_pkts->CurrentDateTime() + ".csv").c_str(), std::ofstream::out);
    }
}

void FSatPktAna::CloseLogFiles()
{
    /*if (checkbutton_log_raw_packets->get_active())
    {
        delete log_raw_pkts;
    }*/
    
    if (checkbutton_log_ngham_packets->get_active())
    {
        delete log_ngham_pkts;
    }
    
    /*if (widgets.checkbutton_log_ax25_packets->get_active())
    {
        delete log_ax25_pkts;
    }*/
    
    if (checkbutton_log_ngham_packets->get_active())
    {
        delete log_data_pkts;
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

//! \} End of fsat_pkt_ana group
