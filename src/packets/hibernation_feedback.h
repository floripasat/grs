/*
 * hibernation_feedback.h
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
 * \brief Hibernation feedback packet definition.
 * 
 * \author Gabriel Mariano Marcelino <gabriel.mm8@gmail.com>
 * 
 * \version 0.4.4
 * 
 * \date 15/04/2019
 * 
 * \defgroup hibernation_feedback Hibernation Feedback
 * \ingroup downlink_data
 * \{
 */

#ifndef HIBERNATION_FEEDBACK_H_
#define HIBERNATION_FEEDBACK_H_

#include <stdint.h>

#include "downlink_data.h"

#define HIBERNATION_FEEDBACK_DURATION_POS       7

namespace grs
{

    /**
     * \brief Hibernation feedback packet.
     */
    class HibernationFeedback: public grs::DownlinkData
    {
        public:

            /**
             * \brief Decodes an hibernation feedback packet.
             *
             * \parma[in] pl is the hibernation feedback packet payload to decode.
             *
             * \return None.
             */
            void decode(Payload pl);

            /**
             * \brief Gets the hibernation duration.
             *
             * \return The hibernation duration in hours.
             */
            uint16_t get_hibernation_duration();

        private:

            /**
             * \brief Hibernation duration in hours.
             */
            uint16_t hibernation_duration_hr;
    };
}

#endif // HIBERNATION_FEEDBACK_H_

//! \} End of hibernation_feedback group
