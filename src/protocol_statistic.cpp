/*
 * protocol_statistic.cpp
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
 * \file protocol_statistic.cpp
 * 
 * \brief .
 * 
 * \author Gabriel Mariano Marcelino <gabriel.mm8@gmail.com>
 * 
 * \version 1.0-dev
 * 
 * \date 12/09/2017
 * 
 * \addtogroup protocol_statistic
 * \{
 */

#include "protocol_statistic.h"
#include "aux.hpp"

ProtocolStatistic::ProtocolStatistic()
{
    
}

ProtocolStatistic::ProtocolStatistic(Gtk::Label *valid, Gtk::Label *invalid, Gtk::Label *total, Gtk::Label *lost_perc)
{    
    label_valid     = valid;
    label_invalid   = invalid;
    label_total     = total;
    label_lost_perc = lost_perc;
    
    this->Clear();
}

ProtocolStatistic::~ProtocolStatistic()
{
    //this->Clear();
}

void ProtocolStatistic::AddValidPkt()
{
    number_valid++;
    this->Update();
}

void ProtocolStatistic::AddValidPkt(unsigned int n)
{
    number_valid += n;
    this->Update();
}

void ProtocolStatistic::AddInvalidPkt()
{
    number_invalid++;
    this->Update();
}

void ProtocolStatistic::AddInvalidPkt(unsigned int n)
{
    number_invalid += n;
    this->Update();
}

void ProtocolStatistic::Update()
{
    label_valid->set_text(ToConstChar(number_valid));
    label_invalid->set_text(ToConstChar(number_invalid));
    label_total->set_text(ToConstChar(number_valid + number_invalid));
    
    float stat;
    
    if ((number_valid == 0) and (number_invalid == 0))
    {
        stat = 0;
    }
    else
    {
        stat = (float)(number_invalid*100.0/(number_valid + number_invalid));
    }
    
    label_lost_perc->set_text(ToConstChar(stat));
}

void ProtocolStatistic::Clear()
{
    number_valid    = 0;
    number_invalid  = 0;
    
    this->Update();
}

//! \} End of protocol_statistic group
