/*
 * log.cpp
 * 
 * Copyright (C) 2017-2019, Universidade Federal de Santa Catarina.
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
 * \brief A module for record data on a .txt file.
 * 
 * \author Gabriel Mariano Marcelino <gabriel.mm8@gmail.com>
 * 
 * \version 0.6.4
 * 
 * \date 07/05/2017
 * 
 * \addtogroup log
 * \{
 */

#include <sys/types.h>
#include <sys/stat.h>
#include <ctime>
#include <stdexcept>

#include "log.h"

using namespace std;

Log::Log()
{
    if (!VerifyDirectory(LOG_DEFAULT_DIR))
    {
        CreateDirectory(LOG_DEFAULT_DIR);
    }
}

Log::~Log()
{
    if (this->is_open())
    {
        this->close();
    }
}

bool Log::VerifyDirectory(const char *folder)
{
	struct stat info;
	
	if ((stat(folder, &info) != 0) && !(info.st_mode & S_IFDIR))
    {
		return false;
    }
	else
    {
		return true;
    }
}

void Log::CreateDirectory(const char* folder)
{
    mkdir(folder, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
}

string Log::CurrentDateTime(int output_format)
{
    time_t now = time(0);
    struct tm tstruct;
    char buf[80];
    tstruct = *localtime(&now);
    switch(output_format)
    {
        case LOG_DATA_TIME_FOR_FILE:
            strftime(buf, sizeof(buf), "%d-%m-%Y_%H-%M-%S", &tstruct);
            break;
        case LOG_DATA_TIME_FOR_LOG:
            strftime(buf, sizeof(buf), "%d/%m/%Y - %H:%M:%S", &tstruct);
            break;
        case LOG_DATA_TIME_FOR_LOG_CSV:
            strftime(buf, sizeof(buf), "%Y,%m,%d,%H,%M,%S,", &tstruct);
            break;
        case LOG_YEAR:
            strftime(buf, sizeof(buf), "%Y", &tstruct);
            break;
        case LOG_MONTH:
            strftime(buf, sizeof(buf), "%m", &tstruct);
            break;
        case LOG_DAY:
            strftime(buf, sizeof(buf), "%d", &tstruct);
            break;
        case LOG_HOUR:
            strftime(buf, sizeof(buf), "%H", &tstruct);
            break;
        case LOG_MINUTE:
            strftime(buf, sizeof(buf), "%M", &tstruct);
            break;
        case LOG_SECOND:
            strftime(buf, sizeof(buf), "%S", &tstruct);
            break;
        default:
            strftime(buf, sizeof(buf), "%d-%m-%Y_%H-%M-%S", &tstruct);
    }
    
    return buf;
}

//! \} End of log group
