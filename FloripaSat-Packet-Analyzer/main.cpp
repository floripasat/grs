/*
 * main.cpp
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

#include "inc/widgets.h"
#include "inc/global_var.h"
#include "inc/signals.h"
#include "inc/error.h"

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
    
    // Load the GtkBuilder file and instantiate its widgets:
    auto refBuilder = Gtk::Builder::create();
    try
    {
        refBuilder->add_from_file("glade/MainWindow.glade");
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

    refBuilder->get_widget("MainWindow", widgets.main_window);
    if (widgets.main_window)
    {
        widgets.main_window->signal_show().connect(sigc::ptr_fun(on_MainWindow_show));
        
        // Serial port
        refBuilder->get_widget("entry_serial_port", widgets.entry_serial_port);
        refBuilder->get_widget("combobox_baudrate", widgets.combobox_baudrate);
        
        refBuilder->get_widget("togglebutton_open_close_port", widgets.togglebutton_open_close_port);
        if (widgets.togglebutton_open_close_port)
        {
            widgets.togglebutton_open_close_port->signal_toggled().connect(sigc::ptr_fun(on_togglebutton_open_close_port_toggled));
        }
        
        // Log checkbuttons
        refBuilder->get_widget("checkbutton_log_raw_packets", widgets.checkbutton_log_raw_packets);
        refBuilder->get_widget("checkbutton_log_ngham_packets", widgets.checkbutton_log_ngham_packets);
        refBuilder->get_widget("checkbutton_log_ax25_packets", widgets.checkbutton_log_ax25_packets);
        refBuilder->get_widget("checkbutton_log_eps_data", widgets.checkbutton_log_eps_data);
        
        // NGHam packet configuration preamble
        refBuilder->get_widget("entry_ngham_config_preamble_byte", widgets.entry_ngham_config_preamble_byte);
        refBuilder->get_widget("entry_ngham_config_preamble_quant", widgets.entry_ngham_config_preamble_quant);
        
        // NGHam packet configuration sync. bytes
        refBuilder->get_widget("entry_ngham_sync_bytes_s0", widgets.entry_ngham_sync_bytes_s0);
        refBuilder->get_widget("entry_ngham_sync_bytes_s1", widgets.entry_ngham_sync_bytes_s1);
        refBuilder->get_widget("entry_ngham_sync_bytes_s2", widgets.entry_ngham_sync_bytes_s2);
        refBuilder->get_widget("entry_ngham_sync_bytes_s3", widgets.entry_ngham_sync_bytes_s3);
        
        // AX25 packet configuration preamble
        refBuilder->get_widget("entry_ax25_config_preamble_byte", widgets.entry_ax25_config_preamble_byte);
        refBuilder->get_widget("entry_ax25_config_preamble_quant", widgets.entry_ax25_config_preamble_quant);
        
        // AX25 packet configuration sync. bytes
        refBuilder->get_widget("entry_ax25_sync_bytes_s0", widgets.entry_ax25_sync_bytes_s0);
        refBuilder->get_widget("entry_ax25_sync_bytes_s1", widgets.entry_ax25_sync_bytes_s1);
        refBuilder->get_widget("entry_ax25_sync_bytes_s2", widgets.entry_ax25_sync_bytes_s2);
        refBuilder->get_widget("entry_ax25_sync_bytes_s3", widgets.entry_ax25_sync_bytes_s3);
        
        // Packets
        refBuilder->get_widget("textview_raw_packets", widgets.textview_raw_packets);
        if (widgets.textview_raw_packets)
        {
            widgets.textview_raw_packets_buffer = widgets.textview_raw_packets->get_buffer();
        }
        
        refBuilder->get_widget("textview_ngham_packets", widgets.textview_ngham_packets);
        if (widgets.textview_ngham_packets)
        {
            widgets.textview_ngham_packets_buffer = widgets.textview_ngham_packets->get_buffer();
        }
        
        refBuilder->get_widget("textview_ax25_packets", widgets.textview_ax25_packets);
        if (widgets.textview_ax25_packets)
        {
            widgets.textview_ax25_packets_buffer = widgets.textview_ax25_packets->get_buffer();
        }
        
        // Load raw packets
        refBuilder->get_widget("filechooserbutton_raw_packets", widgets.filechooserbutton_raw_packets);
        
        refBuilder->get_widget("button_load_raw_packets", widgets.button_load_raw_packets);
        if (widgets.button_load_raw_packets)
        {
            widgets.button_load_raw_packets->signal_clicked().connect(sigc::ptr_fun(on_button_load_raw_packets_clicked));
        }
        
        // Clear all
        refBuilder->get_widget("button_clear_all", widgets.button_clear_all);
        if (widgets.button_clear_all)
        {
            widgets.button_clear_all->signal_clicked().connect(sigc::ptr_fun(on_button_clear_all_clicked));
        }
        
        // EPS data
        refBuilder->get_widget("label_battery1_value", widgets.label_battery1_value);
        refBuilder->get_widget("label_battery2_value", widgets.label_battery2_value);
        refBuilder->get_widget("label_valid_data_value", widgets.label_valid_data_value);
        
        // NGHam statistic
        refBuilder->get_widget("label_ngham_valid_value", widgets.label_ngham_valid_value);
        refBuilder->get_widget("label_ngham_invalid_value", widgets.label_ngham_invalid_value);
        refBuilder->get_widget("label_ngham_total_value", widgets.label_ngham_total_value);
        refBuilder->get_widget("label_ngham_lost_value", widgets.label_ngham_lost_value);
        
        // AX25 statistic
        refBuilder->get_widget("label_ax25_valid_value", widgets.label_ax25_valid_value);
        refBuilder->get_widget("label_ax25_invalid_value", widgets.label_ax25_invalid_value);
        refBuilder->get_widget("label_ax25_total_value", widgets.label_ax25_total_value);
        refBuilder->get_widget("label_ax25_lost_value", widgets.label_ax25_lost_value);
        
        // About
        refBuilder->get_widget("button_about", widgets.button_about);
        if (widgets.button_about)
        {
            widgets.button_about->signal_clicked().connect(sigc::ptr_fun(on_button_about_clicked));
        }
        
        refBuilder->get_widget("aboutdialog", widgets.aboutdialog);
        
        // Status bar
        refBuilder->get_widget("label_serial_port_status", widgets.label_serial_port_status);
        
        g_timeout_add(DATA_RECEPTION_SAMPLE_RATE, (GSourceFunc)timer_handler, (gpointer)widgets.main_window);
        timer_handler();

        app->run(*widgets.main_window);
    }

    delete widgets.main_window;
    
    return 0;
}

//! \} End of fsat_pkt_ana group
