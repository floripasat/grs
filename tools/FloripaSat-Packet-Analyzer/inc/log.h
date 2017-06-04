/*
 * log.h
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
 * \file log.h
 * 
 * \brief A module for record data on a .txt file.
 * 
 * \author Gabriel Mariano Marcelino <gabriel.mm8@gmail.com>
 * 
 * \version 1.0
 * 
 * \date 07/05/2017
 * 
 * \defgroup log Log
 * \ingroup fsat_pkt_ana
 * \{
 */

#ifndef LOG_H_
#define LOG_H_

#include <fstream>
#include <string>

#define LOG_DEFAULT_DIR             "logs"

#define LOG_DATA_TIME_FOR_FILE      0
#define LOG_DATA_TIME_FOR_LOG       1

/**
 * \class Log
 * 
 * \brief 
 * 
 */
class Log: public std::ofstream
{
    public:
        /**
         * \brief Object constructor (without arguments)
         */
        Log();
        /**
         * \brief Object destructor.
         */
        ~Log();
        /**
         * \brief 
         * 
         * \param folder
         * 
         * \return 
         */
        bool VerifyDirectory(const char* folder);
        /**
         * \brief 
         * 
         * \param folder
         * 
         * \return None
         */
        void CreateDirectory(const char* folder);
        /**
         * \brief 
         * 
         * \param output_format
         * 
         * \return 
         */
        std::string CurrentDateTime(int output_format=LOG_DATA_TIME_FOR_FILE);
};

#endif // LOG_H_

//! \} End of log group

