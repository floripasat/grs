/*
 * main.cpp
 * 
 * Copyright (C) 2017, Federal University of Santa Catarina
 * 
 * This file is part of FloripaSat-Ground-Station.
 * 
 * FloripaSat-Ground-Station is free software: you can redistribute it
 * and/or modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation, either version 3 of the
 * License, or (at your option) any later version.
 * 
 * FloripaSat-Ground-Station is distributed in the hope that it will be
 * useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with FloripaSat-Ground-Station.
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
 * \defgroup src Source
 * \{
 */

#include <gtkmm.h>

#include "widgets.h"
#include "error.h"

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
    auto app = Gtk::Application::create(argc, argv, "floripasat-grs");
    
    // Load the GtkBuilder file and instantiate its widgets:
    auto ref_builder = Gtk::Builder::create();
    try
    {
        ref_builder->add_from_file("glade/fsat-grs.glade");
    }
    catch(const Glib::FileError& ex)
    {
        Error("File error!", ex.what().c_str());
        
        return 1;
    }
    catch(const Glib::MarkupError& ex)
    {
        Error("Markup error!", ex.what().c_str());
        
        return 1;
    }
    catch(const Gtk::BuilderError& ex)
    {
        Error("Builder error!", ex.what().c_str());
        
        return 1;
    }
    
    Widgets widgets;

    ref_builder->get_widget("window_main", widgets.window_main);
    if (widgets.window_main)
    {
        //widgets.window_main->signal_show().connect(sigc::ptr_fun(on_window_main_show));
        
        //g_timeout_add(DATA_RECEPTION_SAMPLE_RATE, (GSourceFunc)timer_handler, (gpointer)widgets.main_window);
        //timer_handler();

        app->run(*widgets.window_main);
    }

    delete widgets.window_main;
    
    return 0;
}

//! \} End of fsat_grs group
