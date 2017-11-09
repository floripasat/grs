/*
 * data_processing.hpp
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
 * \file data_processing.hpp
 * 
 * \brief Data processing functions implementation.
 * 
 * \author Elder Dominghini Tramontin <elderdtramontin@gmail.com>
 * 
 * \version 1.0
 * 
 * \date 09/10/2017
 * 
 * \addtogroup data_processing
 * \{
 */


#ifndef DATA_PROCESSING_HPP_
#define DATA_PROCESSING_HPP_

#include <stdint.h>
#include <string>
#include <fstream>

/**
 * \class DataProcessing
 * 
 * \brief 
 */
class DataProcessing
{
    double *max, *min, *avg;
    int cols, rows;
    std::string dataFileName;
    public:
        /**
         * \brief 
         * 
         * \param ev_log
         * \param pkt_data
         * \param ngham_stat
         * \param l
         * \param pdl
         * 
         * \return None
         */
        DataProcessing(std::string fileName);
        ~DataProcessing();
        /**
         * \brief 
         * 
         * \param byte
         * 
         * \return 
         */
        double GetMax(int index);
        double GetMin(int index);
        double GetAverage(int index);
        int GetColumns();
        int GetRows();
        void Validate(std::string fileName);
};


#endif // DATA_PROCESSING_HPP_

//! \} End of data_processing group
