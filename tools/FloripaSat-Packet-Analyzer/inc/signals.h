/*
 * signals.h
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
 * \file signals.h
 * 
 * \brief .
 * 
 * \author Gabriel Mariano Marcelino <gabriel.mm8@gmail.com>
 * 
 * \version 1.0
 * 
 * \date 07/05/2017
 * 
 * \defgroup signals Signals functions
 * \ingroup fsat_pkt_ana
 * \{
 */

#ifndef SIGNALS_H_
#define SIGNALS_H_

/**
 * \var
 * 
 * \brief
 */
extern uint64_t prev_fin_byte_counter;

/**
 * \var
 * 
 * \brief 
 */
extern uint64_t fin_byte_counter;

/**
 * \fn on_MainWindow_show
 * 
 * \brief 
 * 
 * \return None
 */
void on_MainWindow_show();

/**
 * \fn on_togglebutton_open_close_port_toggled
 * 
 * \brief 
 * 
 * \return None
 */
void on_togglebutton_open_close_port_toggled();

/**
 * \fn on_button_load_raw_packets_clicked
 * 
 * \brief 
 * 
 * \return None
 */
void on_button_load_raw_packets_clicked();

/**
 * \fn on_button_clear_all_clicked
 * 
 * \brief 
 * 
 * \return None
 */
void on_button_clear_all_clicked();

/**
 * \fn on_button_about_clicked
 * 
 * \brief 
 * 
 * \return None
 */
void on_button_about_clicked();

/**
 * \fn timer_handler
 * 
 * \brief 
 * 
 * \return 
 */
bool timer_handler();

/**
 * \fn on_togglebutton_play_stream_toggled
 * 
 * \brief 
 * 
 * \return None
 */
void on_togglebutton_play_stream_toggled();

#endif // SIGNALS_H_

//! \} End of signals group
