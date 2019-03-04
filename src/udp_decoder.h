/*
 * udp_decoder.h
 * 
 * Copyright (C) 2019, Universidade Federal de Santa Catarina.
 * 
 * This file is part of FloripaSat-GRS.
 * 
 * FloripaSat-GRS is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * FloripaSat-GRS is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public License
 * along with FloripaSat-GRS. If not, see <http://www.gnu.org/licenses/>.
 * 
 */

/**
 * \brief UDP decoder definition.
 * 
 * \author Gabriel Mariano Marcelino <gabriel.mm8@gmail.com>
 * 
 * \version 0.3.2
 * 
 * \date 03/03/2019
 * 
 * \defgroup udo_decoder UDP Decoder
 * \{
 */

#ifndef UDP_DECODER_H_
#define UDP_DECODER_H_

#include <string>
#include <vector>

#define UDP_DECODER_GRC_PYTHON_ARG              "-u"
#define UDP_DECODER_GRC_ADDRESS_ARG             "-a"
#define UDP_DECODER_GRC_PORT_ARG                "-p"
#define UDP_DECODER_GRC_SAMPLE_RATE_ARG         "-s"
#define UDP_DECODER_GRC_BAUDRATE_ARG            "-b"
#define UDP_DECODER_GRC_OUTPUT_FILE_ARG         "-o"

#define UDP_DECODER_DEFAULT_ADDRESS             "127.0.0.1"
#define UDP_DECODER_DEFAULT_PORT                7355
#define UDP_DECODER_DEFAULT_SAMPLE_RATE_HZ      48000
#define UDP_DECODER_DEFAULT_BAUDRATE_BPS        1200
#define UDP_DECODER_DEFAULT_OUTPUT_FILE         "buffer.bin"

/**
 * \brief UPD decoder.
 */
class udp_decoder
{
    private:

        /**
         * \brief IP address.
         */
        std::string address;

        /**
         * \brief Port number.
         */
        unsigned int port;

        /**
         * \brief Sample rate in Hertz.
         */
        unsigned int sample_rate;

        /**
         * \brief Baudrate in bps.
         */
        unsigned int baudrate;

        /**
         * \brief Output buffer file.
         */
        std::string output_file;

        /**
         * \brief Generates a list of arguments to be passed to a GNURadio script.
         *
         * \param[in] script is the script file to generate the arguments.
         *
         * \return A vector with the GNURadio script arguments.
         */
        std::vector<std::string> gen_script_args(std::string script);

    public:

        /**
         * \brief Constructor.
         *
         * \return None.
         */
        udp_decoder();

        /**
         * \brief Constructor (overloaded).
         *
         * \param[in] adr is the IP address of the server.
         * \param[in] p is the port of the server.
         * \param[in] samp is the audio sample rate in Hertz.
         * \param[in] baud is the satellite signal baudrare in bps.
         * \param[in] output is the output buffer file.
         *
         * \return None.
         */
        udp_decoder(std::string adr, unsigned int p, unsigned int samp, unsigned int baud, std::string output);

        /**
         * \brief Destructor.
         *
         * \return None.
         */
        ~udp_decoder();

        /**
         * \brief Sets the server IP address.
         *
         * \param[in] adr is the IP address of the server.
         *
         * \return None.
         */
        void set_address(std::string adr);

        /**
         * \brief Sets the address port.
         *
         * \param[in] p is the port of the server.
         *
         * \return None.
         */
        void set_port(unsigned int p);

        /**
         * \brief Sets the audio sample rate.
         *
         * \param[in] samp is the audio sample rate in Hertz.
         *
         * \return None.
         */
        void set_sample_rate(unsigned int samp);

        /**
         * \brief Sets the signal baudrate.
         *
         * \param[in] baud is the satellite signal baudrate in bps.
         *
         * \return None.
         */
        void set_baudrate(unsigned int baud);

        /**
         * \brief Sets the output buffer file.
         *
         * \param[in] output is the output buffer file.
         *
         * \return None.
         */
        void set_output_file(std::string output);

        /**
         * \brief Runs the UDP decoder.
         *
         * \param[in] script is the GNURadio script.
         *
         * \return None.
         */
        void run(std::string script);

        /**
         * \brief Runs the UDP decoder using the Python API for C.
         *
         * \param[in] script is the GNURadio script.
         *
         * \return None.
         */
        void run_using_python_api(std::string script);
};

#endif // UDP_DECODER_H_

//! \} End of udp_decoder group
