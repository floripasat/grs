#!/usr/bin/env python2
# -*- coding: utf-8 -*-
##################################################
# GNU Radio Python Flow Graph
# Title: FloripaSat GS Receiver
# Author: Gabriel Mariano Marcelino, Ruan Molgero
# Generated: Tue Mar  7 00:58:39 2017
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
from gnuradio import gr
from gnuradio import wxgui
from gnuradio.eng_option import eng_option
from gnuradio.fft import window
from gnuradio.filter import firdes
from gnuradio.wxgui import fftsink2
from gnuradio.wxgui import forms
from gnuradio.wxgui import scopesink2
from gnuradio.wxgui import waterfallsink2
from grc_gnuradio import wxgui as grc_wxgui
from optparse import OptionParser
import math
import osmosdr
import time
import wx


class fsat_grs(grc_wxgui.top_block_gui):

    def __init__(self):
        grc_wxgui.top_block_gui.__init__(self, title="FloripaSat GS Receiver")
        _icon_path = "/usr/share/icons/hicolor/32x32/apps/gnuradio-grc.png"
        self.SetIcon(wx.Icon(_icon_path, wx.BITMAP_TYPE_ANY))

        ##################################################
        # Variables
        ##################################################
        self.signal_source_freq = signal_source_freq = 0
        self.samp_rate = samp_rate = 1e6
        self.freq = freq = 437.5e6
        self.dc_level = dc_level = 0
        self.baudrate = baudrate = 1.2e3
        self.bandwidth = bandwidth = 12.5e3

        ##################################################
        # Blocks
        ##################################################
        self.notebook_0 = self.notebook_0 = wx.Notebook(self.GetWin(), style=wx.NB_TOP)
        self.notebook_0.AddPage(grc_wxgui.Panel(self.notebook_0), "Frequency correction")
        self.notebook_0.AddPage(grc_wxgui.Panel(self.notebook_0), "DC level correction")
        self.GridAdd(self.notebook_0, 0, 0, 1, 1)
        _signal_source_freq_sizer = wx.BoxSizer(wx.VERTICAL)
        self._signal_source_freq_text_box = forms.text_box(
        	parent=self.notebook_0.GetPage(0).GetWin(),
        	sizer=_signal_source_freq_sizer,
        	value=self.signal_source_freq,
        	callback=self.set_signal_source_freq,
        	label="Shifted Frequency",
        	converter=forms.float_converter(),
        	proportion=0,
        )
        self._signal_source_freq_slider = forms.slider(
        	parent=self.notebook_0.GetPage(0).GetWin(),
        	sizer=_signal_source_freq_sizer,
        	value=self.signal_source_freq,
        	callback=self.set_signal_source_freq,
        	minimum=-100e3,
        	maximum=100e3,
        	num_steps=200,
        	style=wx.SL_HORIZONTAL,
        	cast=float,
        	proportion=1,
        )
        self.notebook_0.GetPage(0).GridAdd(_signal_source_freq_sizer, 1, 0, 1, 1)
        _dc_level_sizer = wx.BoxSizer(wx.VERTICAL)
        self._dc_level_text_box = forms.text_box(
        	parent=self.notebook_0.GetPage(1).GetWin(),
        	sizer=_dc_level_sizer,
        	value=self.dc_level,
        	callback=self.set_dc_level,
        	label="DC Level",
        	converter=forms.float_converter(),
        	proportion=0,
        )
        self._dc_level_slider = forms.slider(
        	parent=self.notebook_0.GetPage(1).GetWin(),
        	sizer=_dc_level_sizer,
        	value=self.dc_level,
        	callback=self.set_dc_level,
        	minimum=-0.05,
        	maximum=0.05,
        	num_steps=100,
        	style=wx.SL_HORIZONTAL,
        	cast=float,
        	proportion=1,
        )
        self.notebook_0.GetPage(1).GridAdd(_dc_level_sizer, 1, 0, 1, 2)
        self.wxgui_waterfallsink2_0 = waterfallsink2.waterfall_sink_c(
        	self.notebook_0.GetPage(0).GetWin(),
        	baseband_freq=0,
        	dynamic_range=100,
        	ref_level=0,
        	ref_scale=2.0,
        	sample_rate=samp_rate,
        	fft_size=512,
        	fft_rate=15,
        	average=False,
        	avg_alpha=None,
        	title="Waterfall Plot After Correction",
        	size=((480,50)),
        )
        self.notebook_0.GetPage(0).GridAdd(self.wxgui_waterfallsink2_0.win, 2, 1, 1, 1)
        self.wxgui_scopesink2_0 = scopesink2.scope_sink_f(
        	self.notebook_0.GetPage(1).GetWin(),
        	title="Scope Plot",
        	sample_rate=samp_rate,
        	v_scale=0,
        	v_offset=0,
        	t_scale=0,
        	ac_couple=False,
        	xy_mode=False,
        	num_inputs=1,
        	trig_mode=wxgui.TRIG_MODE_FREE,
        	y_axis_label="Counts",
        	size=(1000,50),
        )
        self.notebook_0.GetPage(1).GridAdd(self.wxgui_scopesink2_0.win, 2, 0, 1, 4)
        self.wxgui_fftsink2_0 = fftsink2.fft_sink_c(
        	self.notebook_0.GetPage(0).GetWin(),
        	baseband_freq=freq,
        	y_per_div=10,
        	y_divs=10,
        	ref_level=0,
        	ref_scale=2.0,
        	sample_rate=samp_rate,
        	fft_size=1024,
        	fft_rate=15,
        	average=False,
        	avg_alpha=None,
        	title="FFT After Correction",
        	peak_hold=False,
        	size=((480,50)),
        )
        self.notebook_0.GetPage(0).GridAdd(self.wxgui_fftsink2_0.win, 2, 0, 1, 1)
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
          
        self.low_pass_filter_1 = filter.fir_filter_fff(100, firdes.low_pass(
        	1, samp_rate, baudrate, baudrate/6, firdes.WIN_HAMMING, 6.76))
        self.low_pass_filter_0 = filter.fir_filter_ccf(1, firdes.low_pass(
        	1, samp_rate, bandwidth/2, bandwidth/2/6, firdes.WIN_HAMMING, 6.76))
        self.digital_clock_recovery_mm_xx_0 = digital.clock_recovery_mm_ff(samp_rate/(baudrate*100), 0.001, 0, 0.25, 0.001)
        self.digital_binary_slicer_fb_0 = digital.binary_slicer_fb()
        self.blocks_multiply_xx_0 = blocks.multiply_vcc(1)
        self.blocks_file_sink_1 = blocks.file_sink(gr.sizeof_char*1, "/code/gnuradio/bin_data.bin", False)
        self.blocks_file_sink_1.set_unbuffered(False)
        self.blocks_file_sink_0 = blocks.file_sink(gr.sizeof_gr_complex*1, "/code/gnuradio/raw_data.bin", False)
        self.blocks_file_sink_0.set_unbuffered(False)
        self.blocks_add_const_vxx_0 = blocks.add_const_vff((dc_level, ))
        self.analog_sig_source_x_0 = analog.sig_source_c(samp_rate, analog.GR_COS_WAVE, signal_source_freq, 1, 0)
        self.analog_quadrature_demod_cf_0 = analog.quadrature_demod_cf(1)

        ##################################################
        # Connections
        ##################################################
        self.connect((self.analog_quadrature_demod_cf_0, 0), (self.low_pass_filter_1, 0))    
        self.connect((self.analog_sig_source_x_0, 0), (self.blocks_multiply_xx_0, 1))    
        self.connect((self.blocks_add_const_vxx_0, 0), (self.digital_clock_recovery_mm_xx_0, 0))    
        self.connect((self.blocks_add_const_vxx_0, 0), (self.wxgui_scopesink2_0, 0))    
        self.connect((self.blocks_multiply_xx_0, 0), (self.low_pass_filter_0, 0))    
        self.connect((self.blocks_multiply_xx_0, 0), (self.wxgui_fftsink2_0, 0))    
        self.connect((self.blocks_multiply_xx_0, 0), (self.wxgui_waterfallsink2_0, 0))    
        self.connect((self.digital_binary_slicer_fb_0, 0), (self.blocks_file_sink_1, 0))    
        self.connect((self.digital_clock_recovery_mm_xx_0, 0), (self.digital_binary_slicer_fb_0, 0))    
        self.connect((self.low_pass_filter_0, 0), (self.analog_quadrature_demod_cf_0, 0))    
        self.connect((self.low_pass_filter_1, 0), (self.blocks_add_const_vxx_0, 0))    
        self.connect((self.osmosdr_source_0, 0), (self.blocks_file_sink_0, 0))    
        self.connect((self.osmosdr_source_0, 0), (self.blocks_multiply_xx_0, 0))    

    def get_signal_source_freq(self):
        return self.signal_source_freq

    def set_signal_source_freq(self, signal_source_freq):
        self.signal_source_freq = signal_source_freq
        self._signal_source_freq_slider.set_value(self.signal_source_freq)
        self._signal_source_freq_text_box.set_value(self.signal_source_freq)
        self.analog_sig_source_x_0.set_frequency(self.signal_source_freq)

    def get_samp_rate(self):
        return self.samp_rate

    def set_samp_rate(self, samp_rate):
        self.samp_rate = samp_rate
        self.analog_sig_source_x_0.set_sampling_freq(self.samp_rate)
        self.digital_clock_recovery_mm_xx_0.set_omega(self.samp_rate/(self.baudrate*100))
        self.low_pass_filter_0.set_taps(firdes.low_pass(1, self.samp_rate, self.bandwidth/2, self.bandwidth/2/6, firdes.WIN_HAMMING, 6.76))
        self.low_pass_filter_1.set_taps(firdes.low_pass(1, self.samp_rate, self.baudrate, self.baudrate/6, firdes.WIN_HAMMING, 6.76))
        self.osmosdr_source_0.set_sample_rate(self.samp_rate)
        self.wxgui_fftsink2_0.set_sample_rate(self.samp_rate)
        self.wxgui_scopesink2_0.set_sample_rate(self.samp_rate)
        self.wxgui_waterfallsink2_0.set_sample_rate(self.samp_rate)

    def get_freq(self):
        return self.freq

    def set_freq(self, freq):
        self.freq = freq
        self.osmosdr_source_0.set_center_freq(self.freq, 0)
        self.wxgui_fftsink2_0.set_baseband_freq(self.freq)

    def get_dc_level(self):
        return self.dc_level

    def set_dc_level(self, dc_level):
        self.dc_level = dc_level
        self._dc_level_slider.set_value(self.dc_level)
        self._dc_level_text_box.set_value(self.dc_level)
        self.blocks_add_const_vxx_0.set_k((self.dc_level, ))

    def get_baudrate(self):
        return self.baudrate

    def set_baudrate(self, baudrate):
        self.baudrate = baudrate
        self.digital_clock_recovery_mm_xx_0.set_omega(self.samp_rate/(self.baudrate*100))
        self.low_pass_filter_1.set_taps(firdes.low_pass(1, self.samp_rate, self.baudrate, self.baudrate/6, firdes.WIN_HAMMING, 6.76))

    def get_bandwidth(self):
        return self.bandwidth

    def set_bandwidth(self, bandwidth):
        self.bandwidth = bandwidth
        self.low_pass_filter_0.set_taps(firdes.low_pass(1, self.samp_rate, self.bandwidth/2, self.bandwidth/2/6, firdes.WIN_HAMMING, 6.76))


def main(top_block_cls=fsat_grs, options=None):

    tb = top_block_cls()
    tb.Start(True)
    tb.Wait()


if __name__ == '__main__':
    main()
