/*
 * protocol_statistic.h
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
 * \file protocol_statistic.h
 * 
 * \brief .
 * 
 * \author Gabriel Mariano Marcelino <gabriel.mm8@gmail.com>
 * 
 * \version 1.2
 * 
 * \date 12/09/2017
 * 
 * \defgroup protocol_statistic Protocol Statistic
 * \{
 */

#ifndef PROTOCOL_STATISTIC_H_
#define PROTOCOL_STATISTIC_H_

#include <gtkmm.h>

/**
 * \class ProtocolStatistic
 * 
 * \brief 
 */
class ProtocolStatistic
{
        Gtk::Label *label_valid;            /**< . */
        Gtk::Label *label_invalid;          /**< . */
        Gtk::Label *label_total;            /**< . */
        Gtk::Label *label_lost_perc;        /**< . */
        unsigned int number_valid;          /**< . */
        unsigned int number_invalid;        /**< . */
    public:
        /**
         * \brief 
         * 
         * \return None
         */
        ProtocolStatistic();
        /**
         * \brief 
         * 
         * \param valid
         * \param invalid
         * \param total
         * \param lost_perc
         * 
         * \return None
         */
        ProtocolStatistic(Gtk::Label *valid, Gtk::Label *invalid, Gtk::Label *total, Gtk::Label *lost_perc);
        /**
         * \brief 
         * 
         * \return None
         */
        ~ProtocolStatistic();
        /**
         * \brief 
         * 
         * \return None
         */
        void AddValidPkt();
        /**
         * \brief 
         * 
         * \param n
         * 
         * \return None
         */
        void AddValidPkt(unsigned int n);
        /**
         * \brief 
         * 
         * \return None
         */
        void AddInvalidPkt();
        /**
         * \brief 
         * 
         * \param n
         * 
         * \return None
         */
        void AddInvalidPkt(unsigned int n);
        /**
         * \brief 
         * 
         * \return None
         */
        void Update();
        /**
         * \brief 
         * 
         * \return None
         */
        void Clear();
};

#endif // PROTOCOL_STATISTIC_H_

//! \} End of protocol_statistic group
