/*
 * uplink_event.cpp
 * 
 * Copyright (C) 2018, Federal University of Santa Catarina.
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
 * \file uplink_event.cpp
 * 
 * \brief .
 * 
 * \author Gabriel Mariano Marcelino <gabriel.mm8@gmail.com>
 * 
 * \version 1.0-dev
 * 
 * \date 22/02/2018
 * 
 * \addtogroup uplink_event
 * \{
 */

#include <algorithm>

#include "uplink_event.h"

using namespace std;

UplinkEvent::UplinkEvent()
{

}

UplinkEvent::UplinkEvent(unsigned int t)
{
    this->SetType(t);
    has_interval = false;
    has_period = false;
    has_cycles = false;
}

UplinkEvent::UplinkEvent(unsigned int t, string time_start, string date_start, string time_end, string date_end)
{
    this->SetType(t);
    this->SetInterval(time_start, date_start, time_end, date_end);
    has_period = false;
    has_cycles = false;
}

UplinkEvent::UplinkEvent(unsigned int t, string time_start, string date_start, string time_end, string date_end, unsigned int p)
{
    this->SetType(t);
    this->SetInterval(time_start, date_start, time_end, date_end);
    this->SetPeriod(p);
    has_cycles = false;
}

UplinkEvent::UplinkEvent(unsigned int t, string time_start, string date_start, string time_end, string date_end, unsigned int p, unsigned int c)
{
    this->SetType(t);
    this->SetInterval(time_start, date_start, time_end, date_end);
    this->SetPeriod(p);
    this->SetCycles(c);
}

UplinkEvent::~UplinkEvent()
{

}

bool UplinkEvent::CanTransmit()
{
    time_t now = time(0);

    if (has_interval)
    {
        if ((start <= now) and (end >= now))
        {
            if (has_period)
            {
                if ((last_tx + period_s) <= now)
                {
                    if (has_cycles)
                    {
                        if (tx_count <= cycles-1)
                        {
                            tx_count++;
                            
                            last_tx = now;

                            return true;
                        }
                        else
                        {
                            return false;
                        }
                    }
                    else
                    {
                        tx_count++;
                        
                        last_tx = now;

                        return true;
                    }
                }
                else
                {
                    return false;
                }
            }
            else
            {
                if (has_cycles)
                {
                    if (tx_count <= cycles-1)
                    {
                        tx_count++;

                        last_tx = now;

                        return true;
                    }
                    else
                    {
                        return false;
                    }
                }
                else
                {
                    tx_count++;
                    
                    last_tx = now;

                    return true;
                }
            }
        }
        else
        {
            return false;
        }
    }
    else
    {
        if (has_period)
        {
            if ((last_tx + period_s) <= now)
            {
                if (has_cycles)
                {
                    if (tx_count <= cycles-1)
                    {
                        tx_count++;

                        last_tx = now;

                        return true;
                    }
                    else
                    {
                        return false;
                    }
                }
                else
                {
                    tx_count++;

                    last_tx = now;

                    return true;
                }
            }
            else
            {
                return false;
            }
        }
        else
        {
            if (has_cycles)
            {
                if (tx_count <= cycles-1)
                {
                    tx_count++;

                    last_tx = now;

                    return true;
                }
                else
                {
                    return false;
                }
            }
            else
            {
                tx_count++;

                last_tx = now;

                return true;
            }
        }
    }
}

void UplinkEvent::SetType(unsigned int t)
{
    type = t;
}

void UplinkEvent::SetInterval(string start_time, string start_date, string end_time, string end_date)
{
    has_interval = true;
    
    tm start_tm = {0};

    start_tm.tm_sec   = stoi(start_time.substr(6,2), nullptr);
    start_tm.tm_min   = stoi(start_time.substr(3,2), nullptr);
    start_tm.tm_hour  = stoi(start_time.substr(0,2), nullptr);
    start_tm.tm_mday  = stoi(start_date.substr(0,2), nullptr);
    start_tm.tm_mon   = stoi(start_date.substr(3,2), nullptr) - 1;      // -1: January = 0
    start_tm.tm_year  = stoi(start_date.substr(6,4), nullptr) - 1900;

    start = mktime(&start_tm);
    
    tm end_tm = {0};

    end_tm.tm_sec   = stoi(end_time.substr(6,2), nullptr);
    end_tm.tm_min   = stoi(end_time.substr(3,2), nullptr);
    end_tm.tm_hour  = stoi(end_time.substr(0,2), nullptr);
    end_tm.tm_mday  = stoi(end_date.substr(0,2), nullptr);
    end_tm.tm_mon   = stoi(end_date.substr(3,2), nullptr) - 1;
    end_tm.tm_year  = stoi(end_date.substr(6,4), nullptr) - 1900;

    end = mktime(&end_tm);
}

void UplinkEvent::SetPeriod(unsigned int p)
{
    has_period = true;

    period_s = p;
}

void UplinkEvent::SetCycles(unsigned int c)
{
    has_cycles = true;
    tx_count = 0;

    cycles = c;
}

unsigned int UplinkEvent::GetType()
{
    return type;
}

//! \} End of uplink_event group
