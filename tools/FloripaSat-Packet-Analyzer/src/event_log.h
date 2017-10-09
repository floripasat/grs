/*
 * event_log.h
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
 * \file event_log.h
 * 
 * \brief Event log class.
 * 
 * \author Gabriel Mariano Marcelino <gabriel.mm8@gmail.com>
 * 
 * \version 2.0
 * 
 * \date 07/10/2017
 * 
 * \defgroup event_log Event Log
 * \{
 */

#ifndef EVENT_LOG_H_
#define EVENT_LOG_H_

#include <gtkmm.h>

#include "log.h"

#define EVENT_LOG_TYPE_NEW_VALID_PACKET     0
#define EVENT_LOG_TYPE_NEW_INVALID_PACKET   1
#define EVENT_LOG_TYPE_OTHERS               2

/**
 * \class EventLog
 * 
 * \brief 
 */
class EventLog: public Log
{
        /**
         * \brief 
         * 
         */
        Gtk::TextView *textview_event_log;
        /**
         * \brief 
         */
        Glib::RefPtr<Gtk::TextBuffer> textview_event_log_buffer;
        /**
         * \brief 
         */
        Glib::RefPtr<Gtk::TextBuffer::Tag> event_tag_valid;
        /**
         * \brief 
         */
        Glib::RefPtr<Gtk::TextBuffer::Tag> event_tag_invalid;
    public:
        /**
         * \brief 
         * 
         * \return None
         */
        EventLog(Gtk::TextView *textview);
        /**
         * \brief 
         * 
         * \param event_description
         * \param type
         * 
         * \return None
         */
        void AddNewEvent(const char *event_description, uint8_t type=EVENT_LOG_TYPE_OTHERS);
};

#endif // EVENT_LOG_H_

//! \} End of event_log group
