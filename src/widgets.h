/*
 * widgets.h
 * 
 * Copyright (C) 2017, Federal University of Santa Catarina
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
 * \file widgets.h
 * 
 * \brief Widgets struct.
 * 
 * \author Gabriel Mariano Marcelino <gabriel.mm8@gmail.com>
 * 
 * \version 1.0
 * 
 * \date 03/06/2017
 * 
 * \defgroup widgets Widgets
 * \ingroup src
 * \{
 */

#ifndef WIDGETS_H_
#define WIDGETS_H_

#include <gtkmm.h>

/**
 * \struct Widgets
 * 
 * \brief 
 */
struct Widgets
{
    Gtk::Window                     *window_main;
};

#endif // WIDGETS_H_

//! \} End of widgets groups
