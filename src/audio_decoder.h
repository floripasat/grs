/*
 * audio_decoder.h
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
 * \brief Audio decoder definition.
 * 
 * \author Gabriel Mariano Marcelino <gabriel.mm8@gmail.com>
 * 
 * \version 0.4.11
 * 
 * \date 29/04/2019
 * 
 * \defgroup audio_decoder Audio Decoder
 * \{
 */

#ifndef AUDIO_DECODER_H_
#define AUDIO_DECODER_H_

#include <string>
#include <vector>

#define AUDIO_DECODER_GRC_PYTHON_ARG            "-u"
#define AUDIO_DECODER_GRC_INPUT_FILE_ARG        "-i"
#define AUDIO_DECODER_GRC_SAMPLE_RATE_ARG       "-s"
#define AUDIO_DECODER_GRC_BAUDRATE_ARG          "-b"
#define AUDIO_DECODER_GRC_OUTPUT_FILE_ARG       "-o"

#define AUDIO_DECODER_DEFAULT_INPUT_FILE        "audio.wav"
#define AUDIO_DECODER_DEFAULT_SAMPLE_RATE_HZ    48000
#define AUDIO_DECODER_DEFAULT_BAUDRATE_BPS      1200
#define AUDIO_DECODER_DEFAULT_OUTPUT_FILE       "buffer.bin"

/**
 * \brief Audio decoder.
 */
class AudioDecoder
{
    public:

        /**
         * \brief Constructor.
         *
         * \return None.
         */
        AudioDecoder();

        /**
         * \brief Constructor (overloaded).
         *
         * \param[in] input is the input audio file.
         * \param[in] samp is the audio sample rate in Hertz.
         * \param[in] baud is the satellite signal baudrare in bps.
         * \param[in] output is the output buffer file.
         *
         * \return None.
         */
        AudioDecoder(std::string input, unsigned int samp, unsigned int baud, std::string output);

        /**
         * \brief Destructor.
         *
         * \return None.
         */
        ~AudioDecoder();

        /**
         * \brief Sets the input file.
         *
         * \param[in] input is the input audio file.
         *
         * \return None.
         */
        void set_input_file(std::string input);

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

    private:

        /**
         * \brief Input audio file.
         */
        std::string input_file;

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
};

#endif // AUDIO_DECODER_H_

//! \} End of audio_decoder group
