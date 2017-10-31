/*
 * event_log.cpp
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
 * \file event_log.cpp
 * 
 * \brief Event log implementation.
 * 
 * \author Gabriel Mariano Marcelino <gabriel.mm8@gmail.com>
 * 
 * \version 1.0-dev
 * 
 * \date 07/10/2017
 * 
 * \addtogroup event_log
 * \{
 */

#include "event_log.h"
#include "aux.hpp"

EventLog::EventLog(Gtk::TextView *textview)
{
    textview_event_log = textview;
    textview_event_log_buffer = textview_event_log->get_buffer();
    
    if (!this->VerifyDirectory(LOG_DEFAULT_DIR))
    {
        this->CreateDirectory(LOG_DEFAULT_DIR);
    }
    
    event_tag_valid = textview_event_log_buffer->create_tag("valid-pkt");
    event_tag_valid->property_background() = "green";
    event_tag_valid->property_foreground() = "white";
    
    event_tag_invalid = textview_event_log_buffer->create_tag("invalid-pkt");
    event_tag_invalid->property_background() = "red";
    event_tag_invalid->property_foreground() = "white";
}

void EventLog::AddNewEvent(const char *event_description, uint8_t type)
{
    switch(type)
    {
        case EVENT_LOG_TYPE_NEW_VALID_PACKET:
            textview_event_log_buffer->insert_with_tag(textview_event_log_buffer->end(), this->CurrentDateTime(LOG_DATA_TIME_FOR_LOG).c_str(), event_tag_valid);
            textview_event_log_buffer->insert_with_tag(textview_event_log_buffer->end(), "\t", event_tag_valid);
            textview_event_log_buffer->insert_with_tag(textview_event_log_buffer->end(), event_description, event_tag_valid);
            textview_event_log_buffer->insert_with_tag(textview_event_log_buffer->end(), "\n", event_tag_valid);
            break;
        case EVENT_LOG_TYPE_NEW_INVALID_PACKET:
            textview_event_log_buffer->insert_with_tag(textview_event_log_buffer->end(), this->CurrentDateTime(LOG_DATA_TIME_FOR_LOG).c_str(), event_tag_invalid);
            textview_event_log_buffer->insert_with_tag(textview_event_log_buffer->end(), "\t", event_tag_invalid);
            textview_event_log_buffer->insert_with_tag(textview_event_log_buffer->end(), event_description, event_tag_invalid);
            textview_event_log_buffer->insert_with_tag(textview_event_log_buffer->end(), "\n", event_tag_invalid);
            break;
        default:
            textview_event_log_buffer->insert(textview_event_log_buffer->end(), this->CurrentDateTime(LOG_DATA_TIME_FOR_LOG).c_str());
            textview_event_log_buffer->insert(textview_event_log_buffer->end(), "\t");
            textview_event_log_buffer->insert(textview_event_log_buffer->end(), event_description);
            textview_event_log_buffer->insert(textview_event_log_buffer->end(), "\n");
            break;
    }
    
    auto iter_end = textview_event_log_buffer->end();
    
    textview_event_log->scroll_to(iter_end);
    
    *this << ToConstChar(int(type)) << "," << this->CurrentDateTime(LOG_DATA_TIME_FOR_LOG_CSV) << event_description << "\n";
}

//! \} End of event_log group
