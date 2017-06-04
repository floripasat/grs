/*
 * error.h
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
 * \file error.h
 * 
 * \brief Error messages handler.
 * 
 * \author Gabriel Mariano Marcelino <gabriel.mm8@gmail.com>
 * 
 * \version 1.0
 * 
 * \date 07/05/2017
 * 
 * \defgroup error Error
 * \ingroup src
 * \{
 */

#ifndef ERROR_H_
#define ERROR_H_

/**
 * \fn Error
 * 
 * \brief Shows a message dialog with a given error message.
 * 
 * \param error_title is the title of the error.
 * \param error_text is a short explanation about the error.
 * 
 * \return None
 */
void Error(const char* error_title, const char* error_text);

/**
 * \fn Info
 * 
 * \brief Shows a message dialog with a given info message.
 * 
 * \param info_title is the title of the info.
 * \param info_text is a short explanation about the info.
 * 
 * \return None
 */
void Info(const char* info_title, const char* info_text);

/**
 * \fn Warning
 * 
 * \brief Shows a message dialog with a given warning message.
 * 
 * \param warning_title is the title of the warning.
 * \param warning_text is a short explanation about the warning.
 * 
 * \return None
 */
void Warning(const char* warning_title, const char* warning_text);

#endif // ERROR_H_

//! \} End of error group
