/*
 * fec.h
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
 * \brief Forward error correction definition.
 * 
 * \author Jon Petter Skagmo <web@skagmo.com>
 * \author Gabriel Mariano Marcelino <gabriel.mm8@gmail.com>
 * 
 * \version 0.3.6
 * 
 * \date 13/04/2017
 * 
 * \defgroup fec FEC
 * \ingroup ngham
 * \{
 */

#ifndef FEC_H_
#define FEC_H_

#include <stdint.h>

#ifndef MIN
#define	MIN(a, b)   ((a) < (b) ? (a) : (b))
#endif // MIN

/**
 * \brief Reed-Solomon codec control block.
 */
typedef struct rs
{
    uint16_t mm;            // Bits per symbol
    uint16_t nn;            // Symbols per block (= (1 << mm)-1)
    uint8_t *alpha_to;      // log lookup table
    uint8_t *index_of;      // Antilog lookup table
    uint8_t *genpoly;       // Generator polynomial
    uint16_t nroots;        // Number of generator roots = number of parity symbols
    uint16_t fcr;           // First consecutive root, index form
    uint16_t prim;          // Primitive element, index form
    uint16_t iprim;         // prim-th root of 1, index form
    uint16_t pad;           // Padding bytes in shortened block
} RS;

/**
 * \brief .
 * 
 * \param rs_ptr
 * 
 * \return None
 */
void free_rs_char(RS *rs_ptr);

/**
 * \brief .
 *
 * \param *rs_ptr
 * \param *data
 * \param *parity
 * 
 * \return None
 */
void encode_rs_char(RS *rs_ptr, uint8_t *data, uint8_t *parity);

/**
 * \brief .
 *
 * \param *rs_ptr
 * \param *data
 * \param *eras_pos
 * \param no_eras
 * 
 * \return retval
 */
int16_t decode_rs_char(RS *rs_ptr, uint8_t *data, int16_t *eras_pos, int16_t no_eras);

/**
 * \brief 
 * 
 * \param *rs
 * \param x
 * 
 * \return 
 */
int16_t modnn(RS *rs_ptr, int16_t x);

#endif // FEC_H_

//! \} End of fec group
