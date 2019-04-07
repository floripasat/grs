/*
 * ccsds_scrambler.h
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
 * \brief CCSDS scrambler definition.
 * 
 * \author Jon Petter Skagmo <web@skagmo.com>
 * \author Gabriel Mariano Marcelino <gabriel.mm8@gmail.com>
 * 
 * \version 0.3.6
 * 
 * \date 27/04/2017
 * 
 * \defgroup ccsds_scrambler CCSDS-Scrambler
 * \ingroup ngham
 * \{
 */

#ifndef CCSDS_SCRAMBLER_H_
#define CCSDS_SCRAMBLER_H_

#include <stdint.h>

/**
 * \brief CCSDS polynomial.
 */
extern const uint8_t ccsds_poly[255];

/**
 * \brief
 * 
 * \return None.
 */
void ngham_ccsds_scrambler_init();

/**
 * \brief Data should be Xored with the sequence, starting from index zero.
 * 
 * \param[in] data
 * 
 * \return None.
 */
uint8_t ngham_ccsds_scrambler_xor(uint8_t data);

#endif // CCSDS_SCRAMBLER_H_

//! \} End of ccsds_scrambler group
