/*
 * signals.cpp
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
 * \file signals.cpp
 * 
 * \brief .
 * 
 * \author Gabriel Mariano Marcelino <gabriel.mm8@gmail.com>
 * 
 * \version 1.0
 * 
 * \date 07/05/2017
 * 
 * \addtogroup signals
 * \{
 */

#include <gtkmm.h>
#include <sstream>
#include <fstream>
#include <string>
#include <stdint.h>
#include <vector>

#include "../inc/signals.h"
#include "../inc/aux.hpp"
#include "../inc/global_var.h"
#include "../inc/pkt_handler.h"
#include "../inc/error.h"

extern "C"
{
    #include "../ngham/ngham.h"
}

void on_MainWindow_show()
{
    ngham_Init();
}

void on_togglebutton_open_close_port_toggled()
{
    if (widgets.togglebutton_open_close_port->get_active())
    {
        int baudrate;
        
        switch(widgets.combobox_baudrate->get_active_row_number())
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
        
        if (uart.Open(widgets.entry_serial_port->get_text().c_str(), baudrate))
        {
            if (widgets.checkbutton_log_raw_packets->get_active())
            {
                log_raw_pkts.open((LOG_DEFAULT_DIR "/RAW_" + log_raw_pkts.CurrentDateTime() + ".txt").c_str(), std::ofstream::out);
            }
            if (widgets.checkbutton_log_ngham_packets->get_active())
            {
                log_ngham_pkts.open((LOG_DEFAULT_DIR "/NGHAM_" + log_ngham_pkts.CurrentDateTime() + ".txt").c_str(), std::ofstream::out);
            }
            //if (widgets.checkbutton_log_ax25_packets->get_active())
            //{
            //    log_ax25_pkts.open((LOG_DEFAULT_DIR "/AX25_" + log_ngham_pkts.CurrentDateTime() + ".txt").c_str(), std::ofstream::out);
            //}
            
            widgets.entry_serial_port->set_sensitive(false);
            widgets.combobox_baudrate->set_sensitive(false);
            widgets.checkbutton_log_raw_packets->set_sensitive(false);
            widgets.checkbutton_log_ngham_packets->set_sensitive(false);
            widgets.checkbutton_log_ax25_packets->set_sensitive(false);
            widgets.checkbutton_log_eps_data->set_sensitive(false);
            widgets.filechooserbutton_raw_packets->set_sensitive(false);
            widgets.button_load_raw_packets->set_sensitive(false);
            
            widgets.label_serial_port_status->set_text("Serial port: Open");
        }
        else
        {
            Error("Error opening the serial port!", "Verify if the device is connected or the address is correct!");
            
            widgets.togglebutton_open_close_port->set_active(false);
        }
    }
    else
    {
        uart.Close();
        log_raw_pkts.close();
        log_ngham_pkts.close();
        //log_ax25_pkts.close();
        
        widgets.entry_serial_port->set_sensitive(true);
        widgets.combobox_baudrate->set_sensitive(true);
        widgets.checkbutton_log_raw_packets->set_sensitive(true);
        widgets.checkbutton_log_ngham_packets->set_sensitive(true);
        widgets.checkbutton_log_ax25_packets->set_sensitive(true);
        widgets.checkbutton_log_eps_data->set_sensitive(true);
        widgets.filechooserbutton_raw_packets->set_sensitive(true);
        widgets.button_load_raw_packets->set_sensitive(true);
        
        widgets.label_serial_port_status->set_text("Serial port: Closed");
    }
}

void on_button_load_raw_packets_clicked()
{
    if (widgets.checkbutton_log_raw_packets->get_active())
    {
        log_raw_pkts.open((LOG_DEFAULT_DIR "/RAW_" + log_raw_pkts.CurrentDateTime() + ".txt").c_str(), std::ofstream::out);
    }
    if (widgets.checkbutton_log_ngham_packets->get_active())
    {
        log_ngham_pkts.open((LOG_DEFAULT_DIR "/NGHAM_" + log_ngham_pkts.CurrentDateTime() + ".txt").c_str(), std::ofstream::out);
    }
    //if (widgets.checkbutton_log_ax25_packets->get_active())
    //{
    //    log_ax25_pkts.open((LOG_DEFAULT_DIR "/AX25_" + log_ngham_pkts.CurrentDateTime() + ".txt").c_str(), std::ofstream::out);
    //}
    
    std::ifstream fin;
    
    fin.open(widgets.filechooserbutton_raw_packets->get_filename().c_str(), std::ifstream::in);
    
    if (!fin.is_open())
    {
        Error("Error opening this file!", "Maybe the current file is not valid!");
    }
    else
    {
        std::vector<uint8_t> sync_bytes;

        sync_bytes.push_back(EntryToHex(widgets.entry_ngham_sync_bytes_s3->get_text()));
        sync_bytes.push_back(EntryToHex(widgets.entry_ngham_sync_bytes_s2->get_text()));
        sync_bytes.push_back(EntryToHex(widgets.entry_ngham_sync_bytes_s1->get_text()));
        sync_bytes.push_back(EntryToHex(widgets.entry_ngham_sync_bytes_s0->get_text()));
        
        std::vector<uint8_t> sync_bits_buffer;
        
        while(!fin.eof())
        {
            uint8_t byte;
            fin >> byte;
            
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
                        ngham_pkt_counter++;
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
                    
                    uint8_t data[256];
                    uint8_t data_len;
                    switch(ngham_Decode(byte, data, &data_len))
                    {
                        case PKT_CONDITION_OK:
                            receive_pkt = false;
                            for(unsigned int j=0;j<data_len;j++)
                            {
                                std::stringstream byte_str;
                                byte_str << (char)data[j];
                                std::string b = byte_str.str();
                                widgets.textview_ngham_packets_buffer->insert_at_cursor(b.c_str());
                                if (widgets.checkbutton_log_ngham_packets->get_active())
                                {
                                    log_ngham_pkts << b;
                                }
                            }
                            widgets.textview_ngham_packets_buffer->insert_at_cursor("\n");
                    
                            if (widgets.checkbutton_log_ngham_packets->get_active())
                            {
                                log_ngham_pkts << "\n";
                            }
                            
                            receive_pkt = false;
                            break;
                        case PKT_CONDITION_PREFAIL:
                            break;
                        case PKT_CONDITION_FAIL:
                            widgets.textview_ngham_packets_buffer->insert_at_cursor("ERROR!\n");
                            if (widgets.checkbutton_log_ngham_packets->get_active())
                            {
                                log_ngham_pkts << "ERROR!\n";
                            }
                            receive_pkt = false;
                            ngham_lost_pkts++;
                            break;
                    }
                    
                    byte_buffer.clear();
                }
            }
        }
        
        widgets.label_ngham_valid_value->set_text(ToConstChar(ngham_pkt_counter - ngham_lost_pkts));
        widgets.label_ngham_invalid_value->set_text(ToConstChar(ngham_lost_pkts));
        widgets.label_ngham_total_value->set_text(ToConstChar(ngham_pkt_counter));
        widgets.label_ngham_lost_value->set_text(ToConstChar((float)(ngham_lost_pkts*100.0/ngham_pkt_counter)));
        
        fin.close();
        
        log_raw_pkts.close();
        log_ngham_pkts.close();
        //log_ax25_pkts.close();
    }
}

void on_button_clear_all_clicked()
{
    widgets.textview_raw_packets_buffer->set_text("");
    widgets.textview_ngham_packets_buffer->set_text("");
    widgets.textview_ax25_packets_buffer->set_text("");
    
    widgets.label_battery1_value->set_text("0 V");
    widgets.label_battery2_value->set_text("0 V");
    widgets.label_valid_data_value->set_text("-");
    
    widgets.label_ngham_valid_value->set_text("0");
    widgets.label_ngham_invalid_value->set_text("0");
    widgets.label_ngham_total_value->set_text("0");
    widgets.label_ngham_lost_value->set_text("0");
    
    widgets.label_ax25_valid_value->set_text("0");
    widgets.label_ax25_invalid_value->set_text("0");
    widgets.label_ax25_total_value->set_text("0");
    widgets.label_ax25_lost_value->set_text("0");
    
    ngham_pkt_counter = 0;
    ngham_lost_pkts = 0;
}

void on_button_about_clicked()
{
    widgets.aboutdialog->run();
}

bool timer_handler()
{    
    if (uart.isOpened())
    {
        int bytes_buf = uart.DataAvailable();
        if (bytes_buf > 0)
        {
            if (widgets.checkbutton_log_raw_packets->get_active())
            {
                log_raw_pkts << log_raw_pkts.CurrentDateTime(LOG_DATA_TIME_FOR_LOG) << " - ";
            }
            
            while(bytes_buf--)
            {
                uint8_t byte = uart.GetByte();
                
                std::string b = HexToStr(byte);
                
                widgets.textview_raw_packets_buffer->insert_at_cursor(b.c_str());
                widgets.textview_raw_packets_buffer->insert_at_cursor(", ");
                
                if (widgets.checkbutton_log_raw_packets->get_active())
                {
                    log_raw_pkts << b << ", ";
                }
                
                auto iter_raw = widgets.textview_raw_packets_buffer->end();
                widgets.textview_raw_packets->scroll_to(iter_raw);
                
                std::vector<uint8_t> r = proccess_byte(byte);
                if (!r.empty())
                {
                    if (widgets.checkbutton_log_ngham_packets->get_active())
                    {
                        log_ngham_pkts << log_ngham_pkts.CurrentDateTime(LOG_DATA_TIME_FOR_LOG) << " - ";
                    }
                    
                    for(unsigned int i=0;i<r.size();i++)
                    {
                        std::stringstream byte_str;
                        byte_str << (char)r[i];
                        std::string b = byte_str.str();
                        widgets.textview_ngham_packets_buffer->insert_at_cursor(b.c_str());
                        if (widgets.checkbutton_log_ngham_packets->get_active())
                        {
                            log_ngham_pkts << b;
                        }
                    }
                    
                    widgets.textview_ngham_packets_buffer->insert_at_cursor("\n");
                    
                    if (widgets.checkbutton_log_ngham_packets->get_active())
                    {
                        log_ngham_pkts << "\n";
                    }
                    
                    auto iter_ngham = widgets.textview_ngham_packets_buffer->end();
                    widgets.textview_ngham_packets->scroll_to(iter_ngham);
                }
                
                // AX25 packets  >>>>>>>>> TO BE IMPLEMENTED
            }
            
            widgets.textview_raw_packets_buffer->insert_at_cursor("\n\n");
            if (widgets.checkbutton_log_raw_packets->get_active())
            {
                log_raw_pkts << "\n";
            }
            
            widgets.label_ngham_valid_value->set_text(ToConstChar(ngham_pkt_counter - ngham_lost_pkts));
            widgets.label_ngham_invalid_value->set_text(ToConstChar(ngham_lost_pkts));
            widgets.label_ngham_total_value->set_text(ToConstChar(ngham_pkt_counter));
            widgets.label_ngham_lost_value->set_text(ToConstChar((float)(ngham_lost_pkts*100.0/ngham_pkt_counter)));
        }
    }
    
	return true;
}

//! \} End of signals implementation group
