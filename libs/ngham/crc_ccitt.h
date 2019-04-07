/*
 * crc_ccitt.h
 *
 * Copyright (C) 2014, Jon Petter Skagmo.
 * Copyright (C) 2017, Universidade Federal de Santa Catarina.
 * 
 * This file is part of FloripaSat-GRS
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as
 * published by the Free Software Foundation, either version 3 of the
 * License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this program; if not, see <http://www.gnu.org/licenses/>
 * 
 */

/**
 * \brief CRC-CCITT definition.
 * 
 * \author Jon Petter Skagmo <web@skagmo.com>
 * \author Gabriel Mariano Marcelino <gabriel.mm8@gmail.com>
 * 
 * \version 0.3.6
 * 
 * \date 27/04/2017
 * 
 * \defgroup crc_ccitt CRC-CCITT
 * \ingroup ngham
 * \{
 */

#ifndef CRC_CCITT_H_
#define	CRC_CCITT_H_

#include <stdint.h>

/**
 * \brief 
 * 
 * \param buf
 * \param crc
 * 
 * \return 
 */
uint16_t ngham_crc_ccitt_byte(uint8_t buf, uint16_t crc);

/**
 * \brief 
 * 
 * \param *buf
 * \param buf_len
 * 
 * \return 
 */
uint16_t ngham_crc_ccitt(uint8_t *buf, uint16_t buf_len);

#endif // CRC_CCITT_H_

//! \} End of crc_ccitt group.
