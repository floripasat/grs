/*
 * log.cpp
 * 
 * Copyright (c) 2017, Federal University of Santa Catarina
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
 * \file log.cpp
 * 
 * \brief A module for record data on a .txt file.
 * 
 * \author Gabriel Mariano Marcelino <gabriel.mm8@gmail.com>
 * 
 * \version 1.0
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

Log::Log()
{
    if (!VerifyDirectory(LOG_DEFAULT_DIR))
    {
        CreateDirectory(LOG_DEFAULT_DIR);
    }
}

Log::~Log()
{
	close();
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
    if (mkdir(folder, ACCESSPERMS) == -1)
    {
        throw std::runtime_error("It is not possible to create a new log folder!");
    }
}

std::string Log::CurrentDateTime(int output_format)
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
            strftime(buf, sizeof(buf), "%d/%m/%Y-%H:%M:%S", &tstruct);
            break;
        default:
            strftime(buf, sizeof(buf), "%d-%m-%Y_%H-%M-%S", &tstruct);
    }
    
    return buf;
}

//! \} End of log implementation group
