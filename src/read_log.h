/*
 * read_log.h
 * 
 * Copyright (C) 2017-2018, Federal University of Santa Catarina
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
 * \file read_log.h
 * 
 * \brief A module for read data from a .csv log file.
 * 
 * \author Gabriel Mariano Marcelino <gabriel.mm8@gmail.com>
 * 
 * \version 1.0-dev
 * 
 * \date 13/02/2018
 * 
 * \defgroup read_log Read log
 * \ingroup fsat_grs
 * \{
 */

#ifndef READ_LOG_H_
#define READ_LOG_H_

#include <fstream>
#include <string>
#include <vector>

/**
 * \class ReadLog
 * 
 * \brief 
 * 
 */
class ReadLog: public std::ifstream
{
    private:
        /**
         * \brief Name and path of the log file to read.
         */
        std::string file_name;
        /**
         * \brief Line position in the log file.
         */
        unsigned int pos;
    public:
        /**
         * \brief Object constructor.
         */
        ReadLog();
        /**
         * \brief Opens a log file.
         *
         * \param f is name of the log file.
         *
         * \return None
         */
        void open(const char *f);
        /**
         * \brief Gets the number of lines of the input file.
         *
         * \return The number of lines.
         */
        unsigned int getLines();
        /**
         * \brief Gets the type of the log file (Beacon, telemetry or unknown).
         *
         * \return An string with the file type ("BEACON", "TELEMETRY" or "UNKNOWN").
         */
        std::string getLogType();
        /**
         * \brief Gets a line of data from the log file.
         *
         * \param l is the line number of the file.
         *
         * \return A vector of strings with the data from a line of the log file.
         */
        std::vector<std::string> getDataLine(unsigned int l);
        /**
         * \brief 
         *
         * \return 
         */
        std::vector<std::string> getPrevious();
        /**
         * \brief 
         *
         * \return 
         */
        std::vector<std::string> getNext();
};

#endif // READ_LOG_H_

//! \} End of read_log group
