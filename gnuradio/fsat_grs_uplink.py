#!/usr/bin/env python2
# -*- coding: utf-8 -*-
##################################################
# GNU Radio Python Flow Graph
# Title: FloripaSat GRS Transmitter
# Author: Gabriel Mariano Marcelino
# Generated: Wed Dec  6 23:45:22 2017
##################################################

from gnuradio import blocks
from gnuradio import digital
from gnuradio import eng_notation
from gnuradio import filter
from gnuradio import gr
from gnuradio.eng_option import eng_option
from gnuradio.filter import firdes
from optparse import OptionParser
import osmosdr
import time


class fsat_grs_uplink(gr.top_block):

    def __init__(self, sdr_dev="rtl=1", frequency="437.9e6", baud_rate="2.4e3"):
        gr.top_block.__init__(self, "FloripaSat GRS Transmitter")

        ##################################################
        # Variables
        ##################################################
        self.sps = sps = 10
        self.deviation = deviation = 5000
        self.baudrate = baudrate = int(baud_rate)
        self.samp_rate_tx = samp_rate_tx = int(4e6)
        self.samp_rate = samp_rate = sps*baudrate
        self.mod_index = mod_index = deviation/baudrate/0.628
        self.freq = freq = float(frequency)
        self.bps = bps = 1

        ##################################################
        # Blocks
        ##################################################
        self.rational_resampler_xxx_0 = filter.rational_resampler_ccc(
                interpolation=samp_rate_tx,
                decimation=samp_rate,
                taps=None,
                fractional_bw=None,
        )
        self.osmosdr_sink_0 = osmosdr.sink( args="numchan=" + str(1) + " " + sdr_dev )
        self.osmosdr_sink_0.set_sample_rate(samp_rate_tx)
        self.osmosdr_sink_0.set_center_freq(freq, 0)
        self.osmosdr_sink_0.set_freq_corr(0, 0)
        self.osmosdr_sink_0.set_gain(30, 0)
        self.osmosdr_sink_0.set_if_gain(20, 0)
        self.osmosdr_sink_0.set_bb_gain(20, 0)
        self.osmosdr_sink_0.set_antenna("", 0)
        self.osmosdr_sink_0.set_bandwidth(0, 0)
          
        self.digital_gfsk_mod_0 = digital.gfsk_mod(
        	samples_per_symbol=sps,
        	sensitivity=(3.14*mod_index)/sps,
        	bt=0.5,
        	verbose=False,
        	log=False,
        )
        self.blocks_file_source_0 = blocks.file_source(gr.sizeof_char*1, "/tmp/uplink_pkt.bin", False)

        ##################################################
        # Connections
        ##################################################
        self.connect((self.blocks_file_source_0, 0), (self.digital_gfsk_mod_0, 0))    
        self.connect((self.digital_gfsk_mod_0, 0), (self.rational_resampler_xxx_0, 0))    
        self.connect((self.rational_resampler_xxx_0, 0), (self.osmosdr_sink_0, 0))    

    def get_sps(self):
        return self.sps

    def set_sps(self, sps):
        self.sps = sps
        self.set_samp_rate(self.sps*self.baudrate)

    def get_deviation(self):
        return self.deviation

    def set_deviation(self, deviation):
        self.deviation = deviation
        self.set_mod_index(self.deviation/self.baudrate/0.628)

    def get_baudrate(self):
        return self.baudrate

    def set_baudrate(self, baudrate):
        self.baudrate = baudrate
        self.set_mod_index(self.deviation/self.baudrate/0.628)
        self.set_samp_rate(self.sps*self.baudrate)

    def get_samp_rate_tx(self):
        return self.samp_rate_tx

    def set_samp_rate_tx(self, samp_rate_tx):
        self.samp_rate_tx = samp_rate_tx
        self.osmosdr_sink_0.set_sample_rate(self.samp_rate_tx)

    def get_samp_rate(self):
        return self.samp_rate

    def set_samp_rate(self, samp_rate):
        self.samp_rate = samp_rate

    def get_mod_index(self):
        return self.mod_index

    def set_mod_index(self, mod_index):
        self.mod_index = mod_index

    def get_freq(self):
        return self.freq

    def set_freq(self, freq):
        self.freq = freq
        self.osmosdr_sink_0.set_center_freq(self.freq, 0)

    def get_bps(self):
        return self.bps

    def set_bps(self, bps):
        self.bps = bps


def main(top_block_cls=fsat_grs_uplink, sdr="rtl=1", freq="437.9e6", baud="2.4e3"):
    if gr.enable_realtime_scheduling() != gr.RT_OK:
        print "Error: failed to enable real-time scheduling."
    
    tb = top_block_cls(sdr, freq, baud)
    tb.start()
    tb.wait()


if __name__ == '__main__':
    import sys
    main(sdr=sys.argv[1], freq=sys.argv[2], baud=sys.argv[3])
