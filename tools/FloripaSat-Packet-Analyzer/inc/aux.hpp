/*
 * aux.hpp
 * 
 * Copyright (C) 2017, Universidade Federal de Santa Catarina
 * 
 * This file is part of FloripaSat-GRS.
 * 
 * FloripaSat-GRS is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * FloripaSat-GRS is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with FloripaSat-GRS.  If not, see <http://www.gnu.org/licenses/>.
 * 
 */

/**
 * \file aux.hpp
 * 
 * \brief Auxiliary functions.
 * 
 * \author Gabriel Mariano Marcelino <gabriel.mm8@gmail.com>
 * 
 * \version 1.0
 * 
 * \date 07/05/2017
 * 
 * \defgroup aux Aux. functions
 * \ingroup fsat_pkt_ana
 * \{
 */

#ifndef AUX_HPP_
#define AUX_HPP_

#include <gtkmm.h>
#include <stdint.h>
#include <string>

/**
 * \fn EntryToHex
 * 
 * \brief 
 * 
 * \param byte_str 
 * 
 * \return The hex. value of byte_str
 */
uint8_t EntryToHex(Glib::ustring byte_str);

/**
 * \fn HexToStr
 * 
 * \brief 
 * 
 * \param byte
 * 
 * \return 
 */
std::string HexToStr(uint8_t byte);

/**
 * \fn ToConstChar
 * 
 * \brief
 * 
 * \param input
 * 
 * \return 
 */
template <typename T>
const char* ToConstChar(T input)
{
    std::stringstream input_str;
    input_str << input;
    std::string output = input_str.str();
    
    return output.c_str();
}

/**
 * \fn BatVoltConv
 * 
 * \brief 
 * 
 * \param val
 * 
 * \return 
 */
double BatVoltConv(uint16_t val);

/**
 * \fn BatTempConv
 * 
 * \brief 
 * 
 * \param 
 * 
 * \return 
 */
double BatTempConv(uint16_t val);

/**
 * \fn BatChargeConv
 * 
 * \brief 
 * 
 * \param val
 * 
 * \return 
 */
double BatChargeConv(uint16_t val);

/**
 * \fn SolarPanelCurrentConv
 * 
 * \brief 
 * 
 * \param val
 * 
 * \return 
 */
double SolarPanelCurrentConv(uint16_t val);

/**
 * \fn SolarPanelVoltageConv
 * 
 * \brief 
 * 
 * \param val
 * 
 * \return 
 */
double SolarPanelVoltageConv(uint16_t val);

/**
 * \fn IMUAccelConv
 * 
 * \brief 
 * 
 * \param val
 * 
 * \return 
 */
double IMUAccelConv(uint16_t val);

/**
 * \fn IMUGyroConv
 * 
 * \brief 
 * 
 * \param val
 * 
 * \return 
 */
double IMUGyroConv(uint16_t val);

#endif // AUX_HPP_

//! \} End of aux group
