/*
 * ngham_pkts.cpp
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
 * \file ngham_pks.cpp
 * 
 * \brief NGHam Packets class implementation.
 * 
 * \author Gabriel Mariano Marcelino <gabriel.mm8@gmail.com>
 * 
 * \version 1.0-dev
 * 
 * \date 06/10/2017
 * 
 * \addtogroup ngham_pks
 * \{
 */

#include <fstream>

extern "C"
{
    #include <libs/ngham/ngham.h>
}

#include "ngham_pkts.h"
#include "aux.hpp"

using namespace std;

NGHamPkts::NGHamPkts()
{
    make_log = false;
    make_data_log = false;
    
    ngham_Init();
}

NGHamPkts::NGHamPkts(EventLog *ev_log, PacketData *pkt_data, ProtocolStatistic *ngham_stat, bool l, bool pdl)
{
    event_log = ev_log;
    packet_data = pkt_data;
    protocol_statistic = ngham_stat;
    
    make_log = l;
    
    if (make_log)
    {
        log_pkts = new Log;
        log_pkts->open((LOG_DEFAULT_DIR "/NGHAM_" + log_pkts->CurrentDateTime() + ".csv").c_str(), ofstream::out);
    }
    
    make_data_log = pdl;
    
    if (make_data_log)
    {
        log_data_pkts = new Log;
        log_data_pkts->open((LOG_DEFAULT_DIR "/" + ToString(packet_data->getLabel()) + "_" + log_data_pkts->CurrentDateTime() + ".csv").c_str(), ofstream::out);
    }
    
    this->InitPkts();
    
    ngham_Init();
}

bool NGHamPkts::ProcessByte(uint8_t byte)
{                        
    uint8_t data[256];
    uint8_t data_len;
    string event_text;
    
    switch(ngham_Decode(byte, data, &data_len))
    {
        case PKT_CONDITION_OK:
            if (data_len < 10)      // Probably an uplink packet from the ground station
            {
                return true;
            }
            
            if (make_log)
            {
                *log_pkts << "V," << log_pkts->CurrentDateTime(LOG_DATA_TIME_FOR_LOG_CSV);
            }
            
            for(unsigned int j=0; j<data_len; j++)
            {
                stringstream byte_str;
                byte_str << (char)data[j];
                string b = byte_str.str();
                
                if (make_log)
                {
                    *log_pkts << HexToStr(data[j]) << ",";
                }
            }
            
            if ((data[0] == 'H') and (data[1] == 'e') and (data[2] == 'l'))
            {
                event_text = "Ping result received: ";
                for(uint8_t i=0; i<data_len; i++)
                {
                    event_text += char(data[i]);
                }
            }
            else if ((data[0] == 'S') and (data[1] == 'h') and (data[2] == 'u'))
            {
                event_text = "Shutdown result received: ";
                for(uint8_t i=0; i<data_len; i++)
                {
                    event_text += char(data[i]);
                }
            }
            else
            {
                event_text = "New valid NGHAM packet from " + string(packet_data->getLabel());
            }
            
            if (make_log)
            {
                *log_pkts << "\n";
            }
            
            event_log->AddNewEvent(event_text.c_str(), EVENT_LOG_TYPE_NEW_VALID_PACKET);
            
            protocol_statistic->AddValidPkt();
            
            packet_data->Update(data, data_len);
            
            if (make_data_log)
            {
                *log_data_pkts << log_data_pkts->CurrentDateTime(LOG_DATA_TIME_FOR_LOG_CSV) << packet_data->Log() << "\n";
            }
            
            receive_pkt = false;
            
            return true;
            
            break;
        case PKT_CONDITION_PREFAIL:
            return false;
            break;
        case PKT_CONDITION_FAIL:
            event_text = "New invalid NGHAM packet from " + string(packet_data->getLabel());
        
            event_log->AddNewEvent(event_text.c_str(), EVENT_LOG_TYPE_NEW_INVALID_PACKET);
            
            if (make_log)
            {
                *log_pkts << "I," << log_pkts->CurrentDateTime(LOG_DATA_TIME_FOR_LOG_CSV) << "\n";
            }
            
            protocol_statistic->AddInvalidPkt();
            
            receive_pkt = false;
            
            return true;
            break;
    }
}

void NGHamPkts::Generate(uint8_t *data, uint8_t len)
{
    NGHam_TX_Packet ngham_packet;
    
    ngham_TxPktGen(&ngham_packet, data, len);
    
    uint8_t pkt_str[300];
    uint16_t pkt_str_len;
    
    ngham_Encode(&ngham_packet, pkt_str, &pkt_str_len);
    
    ofstream file(NGHAM_PKT_GEN_FILE, ofstream::out);
    
    for(uint8_t i=0; i<pkt_str_len; i++)
    {
        file << pkt_str[i];
    }
    
    file.close();
}

//! \} End of ngham_pkts group
