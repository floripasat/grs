/*
 * main.cpp
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
 * \file main.cpp
 * 
 * \brief Main file.
 * 
 * \author Gabriel Mariano Marcelino <gabriel.mm8@gmail.com>
 * 
 * \version 1.0
 * 
 * \date 05/05/2017
 * 
 * \defgroup fsat_pkt_ana FloripaSat Packet Analyzer
 * \{
 */

#include <gtkmm.h>

#include "fsat-pkt-ana.h"

#define GLADE_UI_FILE       "glade/MainWindow.glade"

/**
 * \fn main
 * 
 * \brief The main function.
 * 
 * \param argc Number of arguments passed in on the command line.
 * \param argv A pointer to an array of pointers to the arguments.
 * 
 * \return Returns the error code upon termination.
 */
int main(int argc, char *argv[])
{
    auto app = Gtk::Application::create(argc, argv, "org.gtkmm.floripasat");
    
    auto ref_builder = Gtk::Builder::create();

    FSatPktAna fsat_pkt_ana;
    
    fsat_pkt_ana.BuildWidgets(ref_builder, GLADE_UI_FILE);
    
    return fsat_pkt_ana.Run(app);
}

//! \} End of fsat_pkt_ana group
