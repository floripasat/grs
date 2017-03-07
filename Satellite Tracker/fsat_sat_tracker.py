#!/usr/bin/env python2
# -*- coding: utf-8 -*-
##################################################
# GNU Radio Python Flow Graph
# Title: FloripaSat Satellite Tracker
# Author: Gabriel Mariano Marcelino
# Description: A tool for satellite tracking
# Generated: Tue Mar  7 00:37:41 2017
##################################################

if __name__ == '__main__':
    import ctypes
    import sys
    if sys.platform.startswith('linux'):
        try:
            x11 = ctypes.cdll.LoadLibrary('libX11.so')
            x11.XInitThreads()
        except:
            print "Warning: failed to XInitThreads()"

from gnuradio import blocks
from gnuradio import eng_notation
from gnuradio import filter
from gnuradio import gr
from gnuradio import wxgui
from gnuradio.eng_option import eng_option
from gnuradio.fft import window
from gnuradio.filter import firdes
from gnuradio.wxgui import fftsink2
from gnuradio.wxgui import forms
from gnuradio.wxgui import waterfallsink2
from grc_gnuradio import blks2 as grc_blks2
from grc_gnuradio import wxgui as grc_wxgui
from optparse import OptionParser
import osmosdr
import time
import wx


class fsat_sat_tracker(grc_wxgui.top_block_gui):

    def __init__(self):
        grc_wxgui.top_block_gui.__init__(self, title="FloripaSat Satellite Tracker")
        _icon_path = "/usr/share/icons/hicolor/32x32/apps/gnuradio-grc.png"
        self.SetIcon(wx.Icon(_icon_path, wx.BITMAP_TYPE_ANY))

        ##################################################
        # Variables
        ##################################################
        self.save_file_check_box = save_file_check_box = True
        self.samp_rate = samp_rate = 1e6
        self.freq = freq = 437.5e6
        self.file_sink = file_sink = "raw_data.bin"

        ##################################################
        # Blocks
        ##################################################
        self._save_file_check_box_check_box = forms.check_box(
        	parent=self.GetWin(),
        	value=self.save_file_check_box,
        	callback=self.set_save_file_check_box,
        	label="Save raw data",
        	true=False,
        	false=True,
        )
        self.GridAdd(self._save_file_check_box_check_box, 7, 4, 1, 1)
        self._samp_rate_text_box = forms.text_box(
        	parent=self.GetWin(),
        	value=self.samp_rate,
        	callback=self.set_samp_rate,
        	label="Sample rate [S/s]",
        	converter=forms.float_converter(),
        )
        self.GridAdd(self._samp_rate_text_box, 5, 0, 1, 2)
        self._freq_text_box = forms.text_box(
        	parent=self.GetWin(),
        	value=self.freq,
        	callback=self.set_freq,
        	label="Frequency [Hz]",
        	converter=forms.float_converter(),
        )
        self.GridAdd(self._freq_text_box, 6, 0, 1, 2)
        self._file_sink_text_box = forms.text_box(
        	parent=self.GetWin(),
        	value=self.file_sink,
        	callback=self.set_file_sink,
        	label="File ",
        	converter=forms.str_converter(),
        )
        self.GridAdd(self._file_sink_text_box, 7, 0, 1, 4)
        self.wxgui_waterfallsink2_0 = waterfallsink2.waterfall_sink_c(
        	self.GetWin(),
        	baseband_freq=0,
        	dynamic_range=100,
        	ref_level=0,
        	ref_scale=2.0,
        	sample_rate=samp_rate,
        	fft_size=512,
        	fft_rate=15,
        	average=False,
        	avg_alpha=None,
        	title="Waterfall Plot",
        )
        self.GridAdd(self.wxgui_waterfallsink2_0.win, 0, 6, 4, 5)
        self.wxgui_fftsink2_0 = fftsink2.fft_sink_c(
        	self.GetWin(),
        	baseband_freq=0,
        	y_per_div=10,
        	y_divs=10,
        	ref_level=0,
        	ref_scale=2.0,
        	sample_rate=samp_rate,
        	fft_size=1024,
        	fft_rate=15,
        	average=False,
        	avg_alpha=None,
        	title="FFT Plot",
        	peak_hold=False,
        )
        self.GridAdd(self.wxgui_fftsink2_0.win, 0, 0, 4, 5)
        self.osmosdr_source_0 = osmosdr.source( args="numchan=" + str(1) + " " + "" )
        self.osmosdr_source_0.set_sample_rate(samp_rate)
        self.osmosdr_source_0.set_center_freq(freq, 0)
        self.osmosdr_source_0.set_freq_corr(0, 0)
        self.osmosdr_source_0.set_dc_offset_mode(0, 0)
        self.osmosdr_source_0.set_iq_balance_mode(0, 0)
        self.osmosdr_source_0.set_gain_mode(False, 0)
        self.osmosdr_source_0.set_gain(10, 0)
        self.osmosdr_source_0.set_if_gain(20, 0)
        self.osmosdr_source_0.set_bb_gain(20, 0)
        self.osmosdr_source_0.set_antenna("", 0)
        self.osmosdr_source_0.set_bandwidth(0, 0)
          
        self.file_sink_valve = grc_blks2.valve(item_size=gr.sizeof_gr_complex*1, open=bool(save_file_check_box))
        self.blocks_file_sink_0 = blocks.file_sink(gr.sizeof_gr_complex*1, file_sink, False)
        self.blocks_file_sink_0.set_unbuffered(False)

        ##################################################
        # Connections
        ##################################################
        self.connect((self.file_sink_valve, 0), (self.blocks_file_sink_0, 0))    
        self.connect((self.osmosdr_source_0, 0), (self.file_sink_valve, 0))    
        self.connect((self.osmosdr_source_0, 0), (self.wxgui_fftsink2_0, 0))    
        self.connect((self.osmosdr_source_0, 0), (self.wxgui_waterfallsink2_0, 0))    

    def get_save_file_check_box(self):
        return self.save_file_check_box

    def set_save_file_check_box(self, save_file_check_box):
        self.save_file_check_box = save_file_check_box
        self.file_sink_valve.set_open(bool(self.save_file_check_box))
        self._save_file_check_box_check_box.set_value(self.save_file_check_box)

    def get_samp_rate(self):
        return self.samp_rate

    def set_samp_rate(self, samp_rate):
        self.samp_rate = samp_rate
        self._samp_rate_text_box.set_value(self.samp_rate)
        self.osmosdr_source_0.set_sample_rate(self.samp_rate)
        self.wxgui_fftsink2_0.set_sample_rate(self.samp_rate)
        self.wxgui_waterfallsink2_0.set_sample_rate(self.samp_rate)

    def get_freq(self):
        return self.freq

    def set_freq(self, freq):
        self.freq = freq
        self._freq_text_box.set_value(self.freq)
        self.osmosdr_source_0.set_center_freq(self.freq, 0)

    def get_file_sink(self):
        return self.file_sink

    def set_file_sink(self, file_sink):
        self.file_sink = file_sink
        self._file_sink_text_box.set_value(self.file_sink)
        self.blocks_file_sink_0.open(self.file_sink)


def main(top_block_cls=fsat_sat_tracker, options=None):
    if gr.enable_realtime_scheduling() != gr.RT_OK:
        print "Error: failed to enable real-time scheduling."

    tb = top_block_cls()
    tb.Start(True)
    tb.Wait()


if __name__ == '__main__':
    main()
