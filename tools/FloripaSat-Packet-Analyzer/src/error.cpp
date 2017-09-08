/*
 * error.cpp
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
 * \file error.cpp
 * 
 * \brief Error messages handler.
 * 
 * \author Gabriel Mariano Marcelino <gabriel.mm8@gmail.com>
 * 
 * \version 1.0
 * 
 * \date 07/05/2017
 * 
 * \addtogroup error
 * \{
 */

#include <gtkmm.h>

#include "../inc/error.h"
#include "../inc/global_var.h"

void Error(const char* error_title, const char* error_text)
{
    Gtk::MessageDialog messagedialog_error(error_title, false, Gtk::MESSAGE_ERROR);
    messagedialog_error.set_secondary_text(error_text);
    messagedialog_error.set_transient_for(*widgets.main_window);

    messagedialog_error.run();
}

void Info(const char* info_title, const char* info_text)
{
    Gtk::MessageDialog messagedialog_info(info_title, false, Gtk::MESSAGE_INFO);
    messagedialog_info.set_secondary_text(info_text);
    messagedialog_info.set_transient_for(*widgets.main_window);

    messagedialog_info.run();
}

void Warning(const char* warning_title, const char* warning_text)
{
    Gtk::MessageDialog messagedialog_warning(warning_title, false, Gtk::MESSAGE_WARNING);
    messagedialog_warning.set_secondary_text(warning_text);
    messagedialog_warning.set_transient_for(*widgets.main_window);

    messagedialog_warning.run();
}

//! \} End of error implementation group
