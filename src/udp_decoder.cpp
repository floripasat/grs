/*
 * udp_decoder.cpp
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
 * \brief UDP decoder implementation.
 * 
 * \author Gabriel Mariano Marcelino <gabriel.mm8@gmail.com>
 * 
 * \version 0.3.2
 * 
 * \date 03/03/2019
 * 
 * \addtogroup udp_decoder
 * \{
 */

#include <python2.7/Python.h>

#include "udp_decoder.h"

using namespace std;

vector<string> udp_decoder::gen_script_args(string script)
{
    vector<string> args;

    args.push_back(UDP_DECODER_GRC_PYTHON_ARG);
    args.push_back(script);

    args.push_back(UDP_DECODER_GRC_ADDRESS_ARG);
    args.push_back(this->address);

    args.push_back(UDP_DECODER_GRC_PORT_ARG);
    args.push_back(to_string(this->port));

    args.push_back(UDP_DECODER_GRC_SAMPLE_RATE_ARG);
    args.push_back(to_string(this->sample_rate));

    args.push_back(UDP_DECODER_GRC_BAUDRATE_ARG);
    args.push_back(to_string(this->baudrate));

    args.push_back(UDP_DECODER_GRC_OUTPUT_FILE_ARG);
    args.push_back(this->output_file);

    return args;
}

udp_decoder::udp_decoder()
{
    this->set_address(UDP_DECODER_DEFAULT_ADDRESS);
    this->set_port(UDP_DECODER_DEFAULT_PORT);
    this->set_sample_rate(UDP_DECODER_DEFAULT_SAMPLE_RATE_HZ);
    this->set_baudrate(UDP_DECODER_DEFAULT_BAUDRATE_BPS);
    this->set_output_file(UDP_DECODER_DEFAULT_OUTPUT_FILE);
}

udp_decoder::udp_decoder(string adr, unsigned int p, unsigned int samp, unsigned int baud, string output)
    : udp_decoder()
{
    this->set_address(adr);
    this->set_port(p);
    this->set_sample_rate(samp);
    this->set_baudrate(baud);
    this->set_output_file(output);
}

udp_decoder::~udp_decoder()
{
}

void udp_decoder::set_address(string adr)
{
    this->address = adr;
}

void udp_decoder::set_port(unsigned int p)
{
    this->port = p;
}

void udp_decoder::set_sample_rate(unsigned int samp)
{
    this->sample_rate = samp;
}

void udp_decoder::set_baudrate(unsigned int baud)
{
    this->baudrate = baud;
}

void udp_decoder::set_output_file(std::string output)
{
    this->output_file = output;
}

void udp_decoder::run(string script)
{
    auto args = this->gen_script_args(script);

    string cmd = "python ";

    for(unsigned int i=0; i<args.size(); i++)
    {
        cmd += args[i];
        if (i < args.size()-1)
        {
            cmd += " ";
        }
    }

    system(cmd.c_str());
}

void udp_decoder::run_using_python_api(std::string script)
{
    auto args = this->gen_script_args(script);

    string cmd = "import sys\n";

    cmd += "sys.argv = [";

    for(unsigned int i=0; i<args.size(); i++)
    {
        cmd += "'";
        cmd += args[i];
        if (i == args.size()-1)
        {
            cmd += "'";
        }
        else
        {
            cmd += "',";
        }
    }

    cmd += "]\n";
    cmd += "execfile(\"";
    cmd += script;
    cmd += "\")\n";

    Py_Initialize();

    PyRun_SimpleString(cmd.c_str());

    Py_Finalize();
}

//! \} End of udp_decoder group
