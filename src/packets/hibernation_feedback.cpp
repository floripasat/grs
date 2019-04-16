/*
 * hibernation_feedback.cpp
 * 
 * Copyright (C) 2019, Univerisdade Federal de Santa Catarina.
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
 * along with FloripaSat-GRS. If not, see <http://www.gnu.org/licenses/>.
 * 
 */

/**
 * \brief Hibernation feedback packet implementation.
 * 
 * \author Gabriel Mariano Marcelino <gabriel.mm8@gmail.com>
 * 
 * \version 0.4.4
 * 
 * \date 15/04/2019
 * 
 * \addtogroup hibernation_feedback
 * \{
 */

#include "hibernation_feedback.h"

using namespace grs;

void HibernationFeedback::decode(Payload pl)
{
    DownlinkData::decode(pl);

    this->hibernation_duration_hr = (pl[HIBERNATION_FEEDBACK_DURATION_POS] << 8) | pl[HIBERNATION_FEEDBACK_DURATION_POS+1];
}

uint16_t HibernationFeedback::get_hibernation_duration()
{
    return this->hibernation_duration_hr;
}

//! \} End of hibernation_feedback group
