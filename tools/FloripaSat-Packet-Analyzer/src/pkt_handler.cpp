/*
 * pkt_handler.cpp
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
 * \file pkt_handler.cpp
 * 
 * \brief .
 * 
 * \author Gabriel Mariano Marcelino <gabriel.mm8@gmail.com>
 * 
 * \version 1.0
 * 
 * \date 07/05/2017
 * 
 * \addtogroup pkt_hdl
 * \{
 */

#include "../inc/pkt_handler.h"
#include "../inc/widgets.h"
#include "../inc/global_var.h"
#include "../inc/aux.hpp"

extern "C"
{
    #include "../ngham/ngham.h"
}

std::vector<uint8_t> proccess_byte(uint8_t byte)
{
    std::vector<uint8_t> sync_bytes;
    
    sync_bytes.push_back(EntryToHex(widgets.entry_ngham_sync_bytes_s3->get_text()));
    sync_bytes.push_back(EntryToHex(widgets.entry_ngham_sync_bytes_s2->get_text()));
    sync_bytes.push_back(EntryToHex(widgets.entry_ngham_sync_bytes_s1->get_text()));
    sync_bytes.push_back(EntryToHex(widgets.entry_ngham_sync_bytes_s0->get_text()));
    
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
                ngham_pkt_counter++;
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
                for(unsigned int j=0;j<data_len;j++)
                {
                    result.push_back(data[j]);
                }
                receive_pkt = false;
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
                ngham_lost_pkts++;
                break;
        }
    }
    
    return result;
}

void display_beacon_data(uint8_t *data, uint8_t len)
{
    if (len > 10)
    {
        widgets.label_beacon_data_bat1_v_value->set_text(ToConstChar(BatVoltConv((data[10] << 8) | data[11])));
        widgets.label_beacon_data_bat2_v_value->set_text(ToConstChar(BatVoltConv((data[12] << 8) | data[13])));
        widgets.label_beacon_data_bat1_t_value->set_text(ToConstChar(BatTempConv(0xFFFF)));
        widgets.label_beacon_data_bat2_t_value->set_text(ToConstChar(BatTempConv(0xFFFF)));
        widgets.label_beacon_data_bat_c_value->set_text(ToConstChar(BatChargeConv((data[20] << 8) | data[21])));
        widgets.label_beacon_data_solar_panel_i_value1->set_text(ToConstChar(SolarPanelCurrentConv((data[22] << 8) | data[23])) );// "/" ToConstChar(SolarPanelCurrentConv((data[24] << 8) | data[25]))) "/" ToConstChar(SolarPanelCurrentConv((data[26] << 8) | data[27]))));
        widgets.label_beacon_data_solar_panel_i_value2->set_text(ToConstChar(SolarPanelCurrentConv((data[28] << 8) | data[29])) );//"/" ToConstChar(SolarPanelCurrentConv((data[30] << 8) | data[31]))) "/" ToConstChar(SolarPanelCurrentConv((data[32] << 8) | data[33]))));
        widgets.label_beacon_data_solar_panel_v_value->set_text(ToConstChar(SolarPanelVoltageConv((data[34] << 8) | data[35])) );//"/" ToConstChar(SolarPanelVoltageConv((data[36] << 8) | data[37])) "/" ToConstChar(SolarPanelVoltageConv((data[38] << 8) | data[39])));
        
        if (len > 40)
        {
            widgets.label_beacon_data_sat_status_value->set_text(ToConstChar((data[40] << 8) | data[41]));
            widgets.label_beacon_data_imu_data_value1->set_text(ToConstChar(IMUAccelConv((data[42] << 8) | data[43])) );//"/" ToConstChar(IMUAccelConv((data[44] << 8) | data[45])) "/" ToConstChar(IMUAccelConv((data[46] << 8) | data[47])));
            widgets.label_beacon_data_imu_data_value2->set_text(ToConstChar(IMUGyroConv((data[48] << 8) | data[49])) );//"/" ToConstChar(IMUGyroConv((data[50] << 8) | data[51])) "/" ToConstChar(IMUGyroConv((data[52] << 8) | data[53])));
            widgets.label_beacon_data_system_time_value->set_text(ToConstChar((data[54] << 24) | (data[55] << 16) | (data[56] << 8) | data[57]));
            widgets.label_beacon_data_obdh_rst_value->set_text(ToConstChar((data[58] << 8) | data[59]));
        }
        else
        {
            widgets.label_beacon_data_sat_status_value->set_text("-");
            widgets.label_beacon_data_imu_data_value1->set_text("-");
            widgets.label_beacon_data_imu_data_value2->set_text("-");
            widgets.label_beacon_data_system_time_value->set_text("-");
            widgets.label_beacon_data_obdh_rst_value->set_text("-");
        }
    }
    else
    {
        widgets.label_beacon_data_sat_status_value->set_text("-");
        widgets.label_beacon_data_imu_data_value1->set_text("-");
        widgets.label_beacon_data_imu_data_value2->set_text("-");
        widgets.label_beacon_data_system_time_value->set_text("-");
        widgets.label_beacon_data_obdh_rst_value->set_text("-");
    }
}

//! \} End of pkt_hdl implementation group
