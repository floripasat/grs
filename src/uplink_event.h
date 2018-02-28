/*
 * uplink_event.h
 * 
 * Copyright (C) 2018, Federal University of Santa Catarina.
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
 * \file uplink_event.h
 * 
 * \brief .
 * 
 * \author Gabriel Mariano Marcelino <gabriel.mm8@gmail.com>
 * 
 * \version 1.0-dev
 * 
 * \date 22/02/2018
 * 
 * \defgroup uplink_event Uplink Event
 * \ingroup fsat_grs
 * \{
 */

#ifndef UPLINK_EVENT_H_
#define UPLINK_EVENT_H_

#define UPLINK_EVENT_TYPE_PING              0
#define UPLINK_EVENT_TYPE_DATA_REQUEST      1
#define UPLINK_EVENT_TYPE_SHUTDOWN          2

#include <ctime>
#include <string>

/**
 * \class UplinkEvent
 *
 * \brief A class to hold an uplink event data, and its occurrency.
 */
class UplinkEvent
{
    private:
        unsigned int type;          /**< Type of uplink command. */
        bool has_interval;          /**< True/False if the event has an interval or not. */
        time_t start;               /**< Start of the interval since epoch. */
        time_t end;                 /**< End of the interval since epoch. */
        bool has_period;            /**< True/False if the event has a period between transmissions or not. */
        unsigned int period_s;      /**< Period, in seconds, between multiple transmissions. */
        bool has_cycles;            /**< True/False if the event has a number of transmissions or not. */
        unsigned int cycles;        /**< Number of transmissions (Related or not to the period). */
        unsigned int tx_count;      /**< The number of transmissions of the event since its creation. */
        time_t last_tx;             /**< Time, since epoch, of the last transmission. */
    public:
        /**
         * \brief Class constructor (Without parameters).
         *
         * \return None
         */
        UplinkEvent();
        /**
         * \brief Class constructor.
         *
         * \param type is a string with the type of the command.
         *
         * \return None
         */
        UplinkEvent(std::string type);
        /**
         * \brief Class constructor.
         *
         * \param t is a string with the type of the command.
         * \param time_start is a string with the start time of the interval (HH:MM:SS).
         * \param date_start is a string with the start date of the interval (DD/MM/YYYY).
         * \param time_end is a string with the end time of the interval (HH:MM:SS).
         * \param date_end is a string with the end date of the interval (DD/MM/YYYY).
         *
         * \return None
         */
        UplinkEvent(std::string t, std::string time_start, std::string date_start, std::string time_end, std::string date_end);
        /**
         * \brief Class constructor.
         *
         * \param t is a string with the type of the command.
         * \param time_start is a string with the start time of the interval (HH:MM:SS).
         * \param date_start is a string with the start date of the interval (DD/MM/YYYY).
         * \param time_end is a string with the end time of the interval (HH:MM:SS).
         * \param date_end is a string with the end date of the interval (DD/MM/YYYY).
         * \param p is a string with the period value (in seconds).
         *
         * \return None
         */
        UplinkEvent(std::string t, std::string time_start, std::string date_start, std::string time_end, std::string date_end, std::string p);
        /**
         * \brief Class constructor.
         *
         * \param t is a string with the type of the command.
         * \param time_start is a string with the start time of the interval (HH:MM:SS).
         * \param date_start is a string with the start date of the interval (DD/MM/YYYY).
         * \param time_end is a string with the end time of the interval (HH:MM:SS).
         * \param date_end is a string with the end date of the interval (DD/MM/YYYY).
         * \param p is a string with the period value (in seconds).
         * \param c is a string with the number of cycles.
         *
         * \return None
         */
        UplinkEvent(std::string t, std::string time_start, std::string date_start, std::string time_end, std::string date_end, std::string p, std::string c);
        /**
         * \brief Class destructor.
         *
         * \return None 
         */
        ~UplinkEvent();
        /**
         * \brief Checks if the event can occur.
         *
         * \return TRUE/FALSE if the current time is or not between the start and end period.
         */
        bool CanTransmit();
        /**
         * \brief Sets the type of the uplink command.
         *
         * \param t is a string with the type of command.
         *
         * \return None
         */
        void SetType(std::string t);
        /**
         * \brief Sets the time/date interval of the event.
         *
         * \param start_time
         * \param start_date
         * \param end_time
         * \param end_date
         *
         * \return None
         */
        void SetInterval(std::string start_time, std::string start_date, std::string end_time, std::string end_date);
        /**
         * \brief Sets the period of the transmissions of the event.
         *
         * \param p is a string with the period.
         *
         * \return None
         */
        void SetPeriod(std::string p);
        /**
         * \brief Sets the number of cycles of transmissions.
         *
         * \param c is a string with the number of cycles.
         *
         * \return None
         */
        void SetCycles(std::string c);
        /**
         * \brief Gets the type of the event.
         *
         * \return The type of the event (Type of command).
         */
        unsigned int GetType();
};

#endif // UPLINK_EVENT_H_

//! \} End of uplink_event group
