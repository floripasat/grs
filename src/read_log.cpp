/*
 * read_log.cpp
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
 * \file read_log.cpp
 * 
 * \brief A module for read data from a .csv log file.
 * 
 * \author Gabriel Mariano Marcelino <gabriel.mm8@gmail.com>
 * 
 * \version 1.0-dev
 * 
 * \date 13/02/2018
 * 
 * \addtogroup read_log
 * \{
 */

#include "read_log.h"

using namespace std;

ReadLog::ReadLog()
{
    pos = 0;
}

void ReadLog::open(const char *f)
{
    file_name = f;

    ifstream::open(f, std::ifstream::in);
}

unsigned int ReadLog::getLines()
{
    unsigned int lines = 0;
    char line[300];

    if (!this->is_open())
    {
        ifstream::open(file_name, std::ifstream::in);
    }
    
    while(this->getline(line, 300))
    {
        lines++;
    }
    
    this->close();

    return lines;
}

string ReadLog::getLogType()
{
    if (file_name.find("BEACON") != string::npos)
    {
        return "BEACON";
    }
    else if (file_name.find("TELEMETRY") != string::npos)
    {
        return "TELEMETRY";
    }
    else
    {
        return "UNKNOWN";
    }
}

vector<string> ReadLog::getDataLine(unsigned int l)
{
    vector<string> data;
    string cell = "";
    char c;
    unsigned int line_counter = 0;

    if (!this->is_open())
    {
        ifstream::open(file_name, std::ifstream::in);
    }

    while(this->get(c))
    {
        switch(c)
        {
            case ',':
                if (line_counter == l)
                {
                    data.push_back(cell);
                    cell = "";
                }
                break;
            case '\n':
                line_counter++;
                break;
            default:
                if (line_counter == l)
                {
                    cell += c;
                }
        }

        if (line_counter > l)
        {
            break;
        }
    }
    
    this->close();

    return data;
}

vector<string> ReadLog::getPrevious()
{
    if (pos == 0)
    {
        pos = this->getLines()-1;
    }
    else
    {
        pos--;
    }

    return this->getDataLine(pos);
}

vector<string> ReadLog::getNext()
{
    if (pos == (this->getLines()-1))
    {
        pos = 0;
    }
    else
    {
        pos++;
    }

    return this->getDataLine(pos);
}

//! \} End of read_log group
