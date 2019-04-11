#!/usr/bin/env python2
# -*- coding: utf-8 -*-
##################################################
# GNU Radio Python Flow Graph
# Title: Udp Decoder
# Author: Gabriel Mariano Marcelino
# Generated: Mon Apr  8 13:10:05 2019
##################################################


from gnuradio import blocks
from gnuradio import digital
from gnuradio import eng_notation
from gnuradio import gr
from gnuradio.eng_option import eng_option
from gnuradio.filter import firdes
from optparse import OptionParser


class udp_decoder(gr.top_block):

    def __init__(self, baudrate=2400, client_address='127.0.0.1', client_port=4337, host_address='127.0.0.1', host_port=4327, samp_rate=48000):
        gr.top_block.__init__(self, "Udp Decoder")

        ##################################################
        # Parameters
        ##################################################
        self.baudrate = baudrate
        self.client_address = client_address
        self.client_port = client_port
        self.host_address = host_address
        self.host_port = host_port
        self.samp_rate = samp_rate

        ##################################################
        # Blocks
        ##################################################
        self.digital_clock_recovery_mm_xx_0 = digital.clock_recovery_mm_ff(samp_rate/baudrate, 0.001, 0, 0.25, 0.001)
        self.digital_binary_slicer_fb_0 = digital.binary_slicer_fb()
        self.blocks_udp_source_0 = blocks.udp_source(gr.sizeof_short*1, host_address, host_port, 1472, True)
        self.blocks_udp_sink_0 = blocks.udp_sink(gr.sizeof_char*1, client_address, client_port, 1472, True)
        self.blocks_short_to_float_0 = blocks.short_to_float(1, 32767)



        ##################################################
        # Connections
        ##################################################
        self.connect((self.blocks_short_to_float_0, 0), (self.digital_clock_recovery_mm_xx_0, 0))
        self.connect((self.blocks_udp_source_0, 0), (self.blocks_short_to_float_0, 0))
        self.connect((self.digital_binary_slicer_fb_0, 0), (self.blocks_udp_sink_0, 0))
        self.connect((self.digital_clock_recovery_mm_xx_0, 0), (self.digital_binary_slicer_fb_0, 0))

    def get_baudrate(self):
        return self.baudrate

    def set_baudrate(self, baudrate):
        self.baudrate = baudrate
        self.digital_clock_recovery_mm_xx_0.set_omega(self.samp_rate/self.baudrate)

    def get_client_address(self):
        return self.client_address

    def set_client_address(self, client_address):
        self.client_address = client_address

    def get_client_port(self):
        return self.client_port

    def set_client_port(self, client_port):
        self.client_port = client_port

    def get_host_address(self):
        return self.host_address

    def set_host_address(self, host_address):
        self.host_address = host_address

    def get_host_port(self):
        return self.host_port

    def set_host_port(self, host_port):
        self.host_port = host_port

    def get_samp_rate(self):
        return self.samp_rate

    def set_samp_rate(self, samp_rate):
        self.samp_rate = samp_rate
        self.digital_clock_recovery_mm_xx_0.set_omega(self.samp_rate/self.baudrate)


def argument_parser():
    parser = OptionParser(usage="%prog: [options]", option_class=eng_option)
    parser.add_option(
        "-b", "--baudrate", dest="baudrate", type="intx", default=2400,
        help="Set baudrate [default=%default]")
    parser.add_option(
        "-d", "--client-address", dest="client_address", type="string", default='127.0.0.1',
        help="Set client_address [default=%default]")
    parser.add_option(
        "-c", "--client-port", dest="client_port", type="intx", default=4337,
        help="Set client_port [default=%default]")
    parser.add_option(
        "-a", "--host-address", dest="host_address", type="string", default='127.0.0.1',
        help="Set host_address [default=%default]")
    parser.add_option(
        "-p", "--host-port", dest="host_port", type="intx", default=4327,
        help="Set host_port [default=%default]")
    parser.add_option(
        "-s", "--samp-rate", dest="samp_rate", type="intx", default=48000,
        help="Set samp_rate [default=%default]")
    return parser


def set_procname(newname):
    from ctypes import cdll, byref, create_string_buffer
    libc = cdll.LoadLibrary('libc.so.6')        # Loading a 3rd party library C
    buff = create_string_buffer(len(newname)+1) # Note: One larger than the name (man prctl says that)
    buff.value = newname                        # Null terminated string as it should be
    libc.prctl(15, byref(buff), 0, 0, 0)        # Refer to "#define" of "/usr/include/linux/prctl.h" for the misterious value 16 & arg[3..5] are zero as the man page says.


def main(top_block_cls=udp_decoder, options=None):
    set_procname("grs_downlink")
    if options is None:
        options, _ = argument_parser().parse_args()
    if gr.enable_realtime_scheduling() != gr.RT_OK:
        print "Error: failed to enable real-time scheduling."

    tb = top_block_cls(baudrate=options.baudrate, client_address=options.client_address, client_port=options.client_port, host_address=options.host_address, host_port=options.host_port, samp_rate=options.samp_rate)
    tb.start()
    tb.wait()


if __name__ == '__main__':
    main()
