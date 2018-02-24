/*
 * uplink_events_columns.h
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
 * \file uplink_events_columns.h
 * 
 * \brief .
 * 
 * \author Gabriel Mariano Marcelino <gabriel.mm8@gmail.com>
 * 
 * \version 1.0-dev
 * 
 * \date 24/02/2018
 * 
 * \defgroup uplink_events_columns Uplink Events Columns
 * \ingroup fsat_grs
 * \{
 */

#ifndef UPLINK_EVENTS_COLUMNS_H_
#define UPLINK_EVENTS_COLUMNS_H_

#include <gtkmm.h>

/**
 * \class UplinkEventsColumns
 *
 * \brief 
 *
 * Reference: https://developer.gnome.org/gtkmm-tutorial/stable/sec-treeview-examples.html.en
 */
class UplinkEventsColumns : public Gtk::TreeModelColumnRecord
{
    public:
        /**
         * \brief Class constructor.
         *
         * \return None
         */
        UplinkEventsColumns()
        {
            add(events_cmd);
            add(events_start);
            add(events_end);
            add(events_period);
            add(events_cycles);
        }

        Gtk::TreeModelColumn<Glib::ustring> events_cmd;             /**< Command type column. */
        Gtk::TreeModelColumn<Glib::ustring> events_start;           /**< Start time/date column. */
        Gtk::TreeModelColumn<Glib::ustring> events_end;             /**< End time/date column. */
        Gtk::TreeModelColumn<Glib::ustring> events_period;          /**< Period column. */
        Gtk::TreeModelColumn<Glib::ustring> events_cycles;          /**< Cycles column. */
};

#endif // UPLINK_EVENTS_COLUMNS_H_

//! \} End of uplink_events_columns group
