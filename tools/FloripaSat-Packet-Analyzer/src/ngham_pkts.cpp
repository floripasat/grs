/*
 * ngham_pkts.cpp
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
 * \file ngham_pks.cpp
 * 
 * \brief NGHam Packets class implementation.
 * 
 * \author Gabriel Mariano Marcelino <gabriel.mm8@gmail.com>
 * 
 * \version 2.0
 * 
 * \date 06/10/2017
 * 
 * \addtogroup ngham_pks
 * \{
 */

extern "C"
{
    #include <libs/ngham/ngham.h>
}

#include "ngham_pkts.h"
#include "aux.hpp"

NGHamPkts::NGHamPkts(EventLog *ev_log, PacketData *pkt_data, ProtocolStatistic *ngham_stat, bool l, bool pdl)
{
    event_log = ev_log;
    packet_data = pkt_data;
    protocol_statistic = ngham_stat;
    
    make_log = l;
    
    if (make_log)
    {
        log_pkts = new Log;
        log_pkts->open((LOG_DEFAULT_DIR "/NGHAM_" + log_pkts->CurrentDateTime() + ".csv").c_str(), std::ofstream::out);
    }
    
    make_data_log = pdl;
    
    if (make_data_log)
    {
        log_data_pkts = new Log;
        log_data_pkts->open((LOG_DEFAULT_DIR "/" + ToString(packet_data->getLabel()) + "_" + log_data_pkts->CurrentDateTime() + ".csv").c_str(), std::ofstream::out);
    }
    
    this->InitPkts();
    
    ngham_Init();
}

bool NGHamPkts::ProcessByte(uint8_t byte)
{                        
    uint8_t data[256];
    uint8_t data_len;
    switch(ngham_Decode(byte, data, &data_len))
    {
        case PKT_CONDITION_OK:
            if (make_log)
            {
                *log_pkts << "V," << log_pkts->CurrentDateTime(LOG_DATA_TIME_FOR_LOG_CSV);
            }
            
            for(unsigned int j=0; j<data_len; j++)
            {
                std::stringstream byte_str;
                byte_str << (char)data[j];
                std::string b = byte_str.str();
                
                if (make_log)
                {
                    *log_pkts << HexToStr(data[j]) << ",";
                }
            }
            
            event_log->AddNewEvent("New valid NGHAM packet from beacon", EVENT_LOG_TYPE_NEW_VALID_PACKET);
            
            if (make_log)
            {
                *log_pkts << "\n";
            }
            
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
            event_log->AddNewEvent("New invalid NGHAM packet from beacon", EVENT_LOG_TYPE_NEW_INVALID_PACKET);
            
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

//! \} End of ngham_pkts group
