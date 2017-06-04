/*
 * log.h
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
 * \ingroup src
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
 * \brief A class to implement a log module.
 * 
 */
class Log: public std::ofstream
{
    public:
        /**
         * \brief Object constructor.
         */
        Log();
        /**
         * \brief Object destructor.
         */
        ~Log();
        /**
         * \brief Check if a directory already exists or not.
         * 
         * \param folder is the directory name.
         * 
         * \return It returns:
         *          -\b TRUE if the directory already exists;
         *          -\b FALSE is the directory does not exists.
         *          .
         */
        bool VerifyDirectory(const char* folder);
        /**
         * \brief Creates a new directory to record the log files.
         * 
         * \param folder is new directory name.
         * 
         * \return None
         */
        void CreateDirectory(const char* folder);
        /**
         * \brief Returns the actual date and time of the system.
         * 
         * \param output_format is format of data to output.
         * 
         * \return It returns a string with the data and time.
         */
        std::string CurrentDateTime(int output_format=LOG_DATA_TIME_FOR_FILE);
};

#endif // LOG_H_

//! \} End of log group
