#!/usr/bin/env python2
# -*- coding: utf-8 -*-
##################################################
# GNU Radio Python Flow Graph
# Title: FloripaSat GFSK Beacon Receiver
# Author: Gabriel Mariano Marcelino
# Generated: Fri Oct 27 10:37:30 2017
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

from gnuradio import analog
from gnuradio import blocks
from gnuradio import digital
from gnuradio import eng_notation
from gnuradio import filter
from gnuradio import fosphor
from gnuradio import gr
from gnuradio.eng_option import eng_option
from gnuradio.fft import window
from gnuradio.filter import firdes
from gnuradio.wxgui import forms
from grc_gnuradio import wxgui as grc_wxgui
from optparse import OptionParser
import math
import osmosdr
import time
import wx


class fsat_grs_beacon(grc_wxgui.top_block_gui):

    def __init__(self):
        grc_wxgui.top_block_gui.__init__(self, title="FloripaSat GFSK Beacon Receiver")
        _icon_path = "/usr/share/icons/hicolor/32x32/apps/gnuradio-grc.png"
        self.SetIcon(wx.Icon(_icon_path, wx.BITMAP_TYPE_ANY))

        ##################################################
        # Variables
        ##################################################
        self.variable_static_text_0_0 = variable_static_text_0_0 = ""
        self.variable_static_text_0 = variable_static_text_0 = ""
        self.sdr_rf_gain = sdr_rf_gain = 10
        self.sdr_if_gain = sdr_if_gain = 20
        self.sdr_bb_gain = sdr_bb_gain = 20
        self.samp_rate = samp_rate = 1e6
        self.freq = freq = 145.9e6
        self.bin_file_sink = bin_file_sink = "/tmp/bin_data_beacon.bin"
        self.baudrate = baudrate = 1.2e3
        self.bandwidth = bandwidth = 30e3

        ##################################################
        # Blocks
        ##################################################
        _sdr_rf_gain_sizer = wx.BoxSizer(wx.VERTICAL)
        self._sdr_rf_gain_text_box = forms.text_box(
        	parent=self.GetWin(),
        	sizer=_sdr_rf_gain_sizer,
        	value=self.sdr_rf_gain,
        	callback=self.set_sdr_rf_gain,
        	label="RF gain [dB]",
        	converter=forms.int_converter(),
        	proportion=0,
        )
        self._sdr_rf_gain_slider = forms.slider(
        	parent=self.GetWin(),
        	sizer=_sdr_rf_gain_sizer,
        	value=self.sdr_rf_gain,
        	callback=self.set_sdr_rf_gain,
        	minimum=0,
        	maximum=20,
        	num_steps=20,
        	style=wx.SL_HORIZONTAL,
        	cast=int,
        	proportion=1,
        )
        self.GridAdd(_sdr_rf_gain_sizer, 3, 1, 1, 1)
        _sdr_if_gain_sizer = wx.BoxSizer(wx.VERTICAL)
        self._sdr_if_gain_text_box = forms.text_box(
        	parent=self.GetWin(),
        	sizer=_sdr_if_gain_sizer,
        	value=self.sdr_if_gain,
        	callback=self.set_sdr_if_gain,
        	label="IF gain [dB]",
        	converter=forms.int_converter(),
        	proportion=0,
        )
        self._sdr_if_gain_slider = forms.slider(
        	parent=self.GetWin(),
        	sizer=_sdr_if_gain_sizer,
        	value=self.sdr_if_gain,
        	callback=self.set_sdr_if_gain,
        	minimum=0,
        	maximum=30,
        	num_steps=30,
        	style=wx.SL_HORIZONTAL,
        	cast=int,
        	proportion=1,
        )
        self.GridAdd(_sdr_if_gain_sizer, 4, 1, 1, 1)
        _sdr_bb_gain_sizer = wx.BoxSizer(wx.VERTICAL)
        self._sdr_bb_gain_text_box = forms.text_box(
        	parent=self.GetWin(),
        	sizer=_sdr_bb_gain_sizer,
        	value=self.sdr_bb_gain,
        	callback=self.set_sdr_bb_gain,
        	label="BB gain [dB]",
        	converter=forms.int_converter(),
        	proportion=0,
        )
        self._sdr_bb_gain_slider = forms.slider(
        	parent=self.GetWin(),
        	sizer=_sdr_bb_gain_sizer,
        	value=self.sdr_bb_gain,
        	callback=self.set_sdr_bb_gain,
        	minimum=0,
        	maximum=30,
        	num_steps=30,
        	style=wx.SL_HORIZONTAL,
        	cast=int,
        	proportion=1,
        )
        self.GridAdd(_sdr_bb_gain_sizer, 5, 1, 1, 1)
        _samp_rate_sizer = wx.BoxSizer(wx.VERTICAL)
        self._samp_rate_text_box = forms.text_box(
        	parent=self.GetWin(),
        	sizer=_samp_rate_sizer,
        	value=self.samp_rate,
        	callback=self.set_samp_rate,
        	label="Sample rate [S/s]",
        	converter=forms.float_converter(),
        	proportion=0,
        )
        self._samp_rate_slider = forms.slider(
        	parent=self.GetWin(),
        	sizer=_samp_rate_sizer,
        	value=self.samp_rate,
        	callback=self.set_samp_rate,
        	minimum=100e3,
        	maximum=2e6,
        	num_steps=1000,
        	style=wx.SL_HORIZONTAL,
        	cast=float,
        	proportion=1,
        )
        self.GridAdd(_samp_rate_sizer, 2, 1, 1, 1)
        _freq_sizer = wx.BoxSizer(wx.VERTICAL)
        self._freq_text_box = forms.text_box(
        	parent=self.GetWin(),
        	sizer=_freq_sizer,
        	value=self.freq,
        	callback=self.set_freq,
        	label="Frequency [Hz]",
        	converter=forms.float_converter(),
        	proportion=0,
        )
        self._freq_slider = forms.slider(
        	parent=self.GetWin(),
        	sizer=_freq_sizer,
        	value=self.freq,
        	callback=self.set_freq,
        	minimum=145e6,
        	maximum=146e6,
        	num_steps=100,
        	style=wx.SL_HORIZONTAL,
        	cast=float,
        	proportion=1,
        )
        self.GridAdd(_freq_sizer, 1, 1, 1, 1)
        self._baudrate_text_box = forms.text_box(
        	parent=self.GetWin(),
        	value=self.baudrate,
        	callback=self.set_baudrate,
        	label="Baudrate [bps]",
        	converter=forms.int_converter(),
        )
        self.GridAdd(self._baudrate_text_box, 11, 1, 1, 1)
        _bandwidth_sizer = wx.BoxSizer(wx.VERTICAL)
        self._bandwidth_text_box = forms.text_box(
        	parent=self.GetWin(),
        	sizer=_bandwidth_sizer,
        	value=self.bandwidth,
        	callback=self.set_bandwidth,
        	label="Bandwidth [Hz]",
        	converter=forms.float_converter(),
        	proportion=0,
        )
        self._bandwidth_slider = forms.slider(
        	parent=self.GetWin(),
        	sizer=_bandwidth_sizer,
        	value=self.bandwidth,
        	callback=self.set_bandwidth,
        	minimum=0,
        	maximum=40e3,
        	num_steps=40,
        	style=wx.SL_HORIZONTAL,
        	cast=float,
        	proportion=1,
        )
        self.GridAdd(_bandwidth_sizer, 10, 1, 1, 1)
        self._variable_static_text_0_0_static_text = forms.static_text(
        	parent=self.GetWin(),
        	value=self.variable_static_text_0_0,
        	callback=self.set_variable_static_text_0_0,
        	label="Receiver Configuration",
        	converter=forms.str_converter(),
        )
        self.GridAdd(self._variable_static_text_0_0_static_text, 9, 1, 1, 1)
        self._variable_static_text_0_static_text = forms.static_text(
        	parent=self.GetWin(),
        	value=self.variable_static_text_0,
        	callback=self.set_variable_static_text_0,
        	label="SDR Configuration",
        	converter=forms.str_converter(),
        )
        self.GridAdd(self._variable_static_text_0_static_text, 0, 1, 1, 1)
        self.osmosdr_source_0 = osmosdr.source( args="numchan=" + str(1) + " " + "rtl=0" )
        self.osmosdr_source_0.set_sample_rate(samp_rate)
        self.osmosdr_source_0.set_center_freq(freq, 0)
        self.osmosdr_source_0.set_freq_corr(0, 0)
        self.osmosdr_source_0.set_dc_offset_mode(0, 0)
        self.osmosdr_source_0.set_iq_balance_mode(0, 0)
        self.osmosdr_source_0.set_gain_mode(False, 0)
        self.osmosdr_source_0.set_gain(sdr_rf_gain, 0)
        self.osmosdr_source_0.set_if_gain(sdr_if_gain, 0)
        self.osmosdr_source_0.set_bb_gain(sdr_bb_gain, 0)
        self.osmosdr_source_0.set_antenna("", 0)
        self.osmosdr_source_0.set_bandwidth(0, 0)
          
        self.low_pass_filter_1 = filter.fir_filter_fff(100, firdes.low_pass(
        	1, samp_rate, baudrate, baudrate/6, firdes.WIN_HAMMING, 6.76))
        self.low_pass_filter_0 = filter.fir_filter_ccf(1, firdes.low_pass(
        	1, samp_rate, bandwidth/2, bandwidth/2/6, firdes.WIN_HAMMING, 6.76))
        self.fosphor_wx_sink_c_0 = fosphor.wx_sink_c(
        	self.GetWin()
        )
        self.fosphor_wx_sink_c_0.set_fft_window(window.WIN_BLACKMAN_hARRIS)
        self.fosphor_wx_sink_c_0.set_frequency_range(freq, samp_rate)
        self.GridAdd(self.fosphor_wx_sink_c_0.win, 0, 0, 12, 1)
        self.digital_clock_recovery_mm_xx_0 = digital.clock_recovery_mm_ff(samp_rate/(baudrate*100), 0.001, 0, 0.25, 0.001)
        self.digital_binary_slicer_fb_0 = digital.binary_slicer_fb()
        self.blocks_file_sink_1 = blocks.file_sink(gr.sizeof_char*1, bin_file_sink, False)
        self.blocks_file_sink_1.set_unbuffered(False)
        self.analog_quadrature_demod_cf_0 = analog.quadrature_demod_cf(1)

        ##################################################
        # Connections
        ##################################################
        self.connect((self.analog_quadrature_demod_cf_0, 0), (self.low_pass_filter_1, 0))    
        self.connect((self.digital_binary_slicer_fb_0, 0), (self.blocks_file_sink_1, 0))    
        self.connect((self.digital_clock_recovery_mm_xx_0, 0), (self.digital_binary_slicer_fb_0, 0))    
        self.connect((self.low_pass_filter_0, 0), (self.analog_quadrature_demod_cf_0, 0))    
        self.connect((self.low_pass_filter_1, 0), (self.digital_clock_recovery_mm_xx_0, 0))    
        self.connect((self.osmosdr_source_0, 0), (self.fosphor_wx_sink_c_0, 0))    
        self.connect((self.osmosdr_source_0, 0), (self.low_pass_filter_0, 0))    

    def get_variable_static_text_0_0(self):
        return self.variable_static_text_0_0

    def set_variable_static_text_0_0(self, variable_static_text_0_0):
        self.variable_static_text_0_0 = variable_static_text_0_0
        self._variable_static_text_0_0_static_text.set_value(self.variable_static_text_0_0)

    def get_variable_static_text_0(self):
        return self.variable_static_text_0

    def set_variable_static_text_0(self, variable_static_text_0):
        self.variable_static_text_0 = variable_static_text_0
        self._variable_static_text_0_static_text.set_value(self.variable_static_text_0)

    def get_sdr_rf_gain(self):
        return self.sdr_rf_gain

    def set_sdr_rf_gain(self, sdr_rf_gain):
        self.sdr_rf_gain = sdr_rf_gain
        self._sdr_rf_gain_slider.set_value(self.sdr_rf_gain)
        self._sdr_rf_gain_text_box.set_value(self.sdr_rf_gain)
        self.osmosdr_source_0.set_gain(self.sdr_rf_gain, 0)

    def get_sdr_if_gain(self):
        return self.sdr_if_gain

    def set_sdr_if_gain(self, sdr_if_gain):
        self.sdr_if_gain = sdr_if_gain
        self._sdr_if_gain_slider.set_value(self.sdr_if_gain)
        self._sdr_if_gain_text_box.set_value(self.sdr_if_gain)
        self.osmosdr_source_0.set_if_gain(self.sdr_if_gain, 0)

    def get_sdr_bb_gain(self):
        return self.sdr_bb_gain

    def set_sdr_bb_gain(self, sdr_bb_gain):
        self.sdr_bb_gain = sdr_bb_gain
        self._sdr_bb_gain_slider.set_value(self.sdr_bb_gain)
        self._sdr_bb_gain_text_box.set_value(self.sdr_bb_gain)
        self.osmosdr_source_0.set_bb_gain(self.sdr_bb_gain, 0)

    def get_samp_rate(self):
        return self.samp_rate

    def set_samp_rate(self, samp_rate):
        self.samp_rate = samp_rate
        self._samp_rate_slider.set_value(self.samp_rate)
        self._samp_rate_text_box.set_value(self.samp_rate)
        self.digital_clock_recovery_mm_xx_0.set_omega(self.samp_rate/(self.baudrate*100))
        self.fosphor_wx_sink_c_0.set_frequency_range(self.freq, self.samp_rate)
        self.low_pass_filter_0.set_taps(firdes.low_pass(1, self.samp_rate, self.bandwidth/2, self.bandwidth/2/6, firdes.WIN_HAMMING, 6.76))
        self.low_pass_filter_1.set_taps(firdes.low_pass(1, self.samp_rate, self.baudrate, self.baudrate/6, firdes.WIN_HAMMING, 6.76))
        self.osmosdr_source_0.set_sample_rate(self.samp_rate)

    def get_freq(self):
        return self.freq

    def set_freq(self, freq):
        self.freq = freq
        self._freq_slider.set_value(self.freq)
        self._freq_text_box.set_value(self.freq)
        self.fosphor_wx_sink_c_0.set_frequency_range(self.freq, self.samp_rate)
        self.osmosdr_source_0.set_center_freq(self.freq, 0)

    def get_bin_file_sink(self):
        return self.bin_file_sink

    def set_bin_file_sink(self, bin_file_sink):
        self.bin_file_sink = bin_file_sink
        self.blocks_file_sink_1.open(self.bin_file_sink)

    def get_baudrate(self):
        return self.baudrate

    def set_baudrate(self, baudrate):
        self.baudrate = baudrate
        self._baudrate_text_box.set_value(self.baudrate)
        self.digital_clock_recovery_mm_xx_0.set_omega(self.samp_rate/(self.baudrate*100))
        self.low_pass_filter_1.set_taps(firdes.low_pass(1, self.samp_rate, self.baudrate, self.baudrate/6, firdes.WIN_HAMMING, 6.76))

    def get_bandwidth(self):
        return self.bandwidth

    def set_bandwidth(self, bandwidth):
        self.bandwidth = bandwidth
        self._bandwidth_slider.set_value(self.bandwidth)
        self._bandwidth_text_box.set_value(self.bandwidth)
        self.low_pass_filter_0.set_taps(firdes.low_pass(1, self.samp_rate, self.bandwidth/2, self.bandwidth/2/6, firdes.WIN_HAMMING, 6.76))


def main(top_block_cls=fsat_grs_beacon, options=None):
    if gr.enable_realtime_scheduling() != gr.RT_OK:
        print "Error: failed to enable real-time scheduling."

    tb = top_block_cls()
    tb.Start(True)
    tb.Wait()


if __name__ == '__main__':
    main()
