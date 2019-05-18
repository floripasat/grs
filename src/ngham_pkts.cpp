/*
 * ngham_pkts.cpp
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
 * \brief NGHam Packets class implementation.
 * 
 * \author Gabriel Mariano Marcelino <gabriel.mm8@gmail.com>
 * 
 * \version 0.5.1
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
#include "packets/packets_ids.h"

using namespace std;

NGHamPkts::NGHamPkts()
{
    make_log = false;
    make_data_log = false;

    ngham_init();
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
    
    ngham_init();
}

bool NGHamPkts::ProcessByte(uint8_t byte)
{                        
    uint8_t data[256];
    uint8_t data_len;
    string event_text;

    switch(ngham_decode(byte, data, &data_len))
    {
        case PKT_CONDITION_OK:
            if (data_len < 8)   // Minimum packet content: ID (6 bytes) + command (2 bytes)
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
            else if ((data[6] == 'b') and (data[7] == 'r'))
            {
                event_text = "Broadcast message received from ";
                for(uint8_t i=0; i<6; i++)
                {
                    event_text += char(data[i]);
                }

                event_text += ": ";

                for(uint8_t i=8; i<data_len; i++)
                {
                    event_text += char(data[i]);
                }
            }
            else if ((data[6] == 'X') and (data[7] == 'S'))
            {
                event_text = "Payload X status received: ";

                for(uint8_t i=8; i<data_len; i++)
                {
                    event_text += HexToStr(data[i]);

                    if (i < data_len-1)
                    {
                        event_text += ", ";
                    }
                }
            }
            else
            {
                string callsign = "";

                for(unsigned int i=1; i<8; i++)
                {
                    callsign += data[i];
                }

                switch(data[0])
                {
                    case FLORIPASAT_PACKET_BEACON_NGHAM_OBDH_DATA:
                        event_text = "New valid BEACON packet from ";
                        event_text += substr_to_callsign(callsign);
                        event_text += " containing OBDH data!";
                        break;
                    case FLORIPASAT_PACKET_BEACON_NGHAM_EPS_DATA:
                        event_text = "New valid BEACON packet from ";
                        event_text += substr_to_callsign(callsign);
                        event_text += " containing EPS data!";
                        break;
                    case FLORIPASAT_PACKET_BEACON_NGHAM_TTC_DATA:
                        event_text = "New valid BEACON packet from ";
                        event_text += substr_to_callsign(callsign);
                        event_text += " containing TTC data!";
                        break;
                    case FLORIPASAT_PACKET_DOWNLINK_TELEMETRY:
                        event_text = "New valid DOWNLINK packet from ";
                        event_text += substr_to_callsign(callsign);
                        event_text += " containing TELEMETRY data!";
                        break;
                    default:
                        event_text = "New valid NGHAM packet from " + string(packet_data->getLabel());
                }
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

    return false;
}

void NGHamPkts::Generate(uint8_t *data, uint8_t len)
{
    ngham_tx_packet_t ngham_packet;

    ngham_tx_pkt_gen(&ngham_packet, data, len);

    uint8_t pkt_str[300];
    uint16_t pkt_str_len;

    ngham_encode(&ngham_packet, pkt_str, &pkt_str_len);

    ofstream file(NGHAM_PKT_GEN_FILE, ofstream::out);

    for(uint8_t i=0; i<pkt_str_len; i++)
    {
        file << pkt_str[i];
    }

    file.close();
}

string NGHamPkts::substr_to_callsign(string cs)
{
    string callsign;

    // The minimum length of a callsign is 4 characters, the maximum is 7
    if ((cs[0] == '0') and (cs[+1] == '0') and (cs[+2] == '0'))     // 4 characters ("000XXXX")
    {
        callsign.assign(cs.begin() + 3, cs.end());
    }
    else if ((cs[0] == '0') and (cs[1] == '0'))                     // 5 characters ("00XXXXX")
    {
        callsign.assign(cs.begin() + 2, cs.end());
    }
    else if (cs[0] == '0')                                          // 6 characters ("0XXXXXX")
    {
        callsign.assign(cs.begin() + 1, cs.end());
    }
    else                                                            // 7 characters ("XXXXXXX")
    {
        callsign = cs;
    }

    return callsign;
}

//! \} End of ngham_pkts group
