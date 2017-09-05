"""
Controls signal: SDR, spectrum, frequencies and data recognition.
"""

#
#  controlSignal.py
#  
#  Copyright (C) 2017, Federal University of Santa Catarina.
#  
#  This file is part of FloripaSat-GRS.
#
#  FloripaSat-GRS is free software; you can redistribute it and/or modify
#  it under the terms of the GNU General Public License as published by
#  the Free Software Foundation, either version 3 of the License, or
#  (at your option) any later version.
#  
#  FloripaSat-GRS is distributed in the hope that it will be useful,
#  but WITHOUT ANY WARRANTY; without even the implied warranty of
#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
#  GNU General Public License for more details.
#  
#  You should have received a copy of the GNU General Public License
#  along with FloripaSat-GRS. If not, see <http://www.gnu.org/licenses/>.
#  
#

__author__      = "Samuel Eduardo Noll"
__copyright__   = "Copyright (C) 2017, Federal University of Santa Catarina"
__credits__     = ["Fabricio Silva","Gabriel Mariano Marcelino","Samuel Eduardo Noll"]
__license__     = "GPL3"
__version__     = "1.0-dev"
__maintainer__  = "Samuel Eduardo Noll"
__email__       = "samuelnoll96@gmail.com"
__status__      = "Prototype"

from PySide import QtCore, QtGui
from rtlsdr import RtlSdr
import numpy as np
from signalProcessing import SignalProcessing


class ControlSignal(QtCore.QObject):
    """Controls SDR signal.
    
    Attributes:
        index: Int value of SDR device index at system.
        sample_rate: Int value of SDR sampple rate.
        center_freq: Int value of SDR center frequency.
        gain: Int value of SDR gain.
        sample_size: Int value of SDR sample size.
        samples: Numpy array of complex floats containing whats read at SDR.
        spectrum: Numpy array of frequency spectrum of the signal.
        amplitude: Numpy array of floats containing samples amplitudes got after fft.
        freq: Numpy array of floats containing samples frequencies got after fft.
        samples_bits: List of bits read from SDR after filtering and demodulating.
        fft_size: Int value of fft sample size.
        sample_bits: Numpy binary array of demodulated bits read on SDR.
        running: Bool value to identify if SDR is running.
        timer_period: Int value of timer period in miliseconds.
        timer: QTimer object timer that calls for data updating.
        sdr: RtlSdr object.
    """
    def __init__(self, index=0):
        """Default values initialization and timer defined.
        
        Args:
            index: Int value of SDR device index at system.
        """
        self.index = index
        self.sample_rate = None
        self.sample_size = None
        self.center_freq = None
        self.gain = None
        self.samples = None
        self.amplitude = None
        self.filtered_amplitude = None
        self.freq = None
        self.samples_bits = None
        self.fft_size = None
        self.running = False
        self.timer_period = None
        self.timer = QtCore.QTimer()
        self.timer.timeout.connect(self.updateData)
        self.signal_proc = SignalProcessing()
    
    def open(self):
        """Opens SDR and run."""
        self.sdr = RtlSdr(device_index = self.index)
        self.sdr.sample_rate = self.sample_rate
        self.sdr.center_freq = self.center_freq
        self.sdr.gain = self.gain
        self.timer.start(self.timer_period)
        self.running = True
    
    def close(self):
        """Closes SDR."""
        self.timer.stop()
        self.sdr.close()
        self.running = False
    
    def updateData(self):
        """Read samples from SDR in a desired sample size.
        
        Args:
            sample_size: sample size.
        
        Returns:
            A list of values (complex).
        """
        self.samples = self.sdr.read_samples(self.sample_size)
        self.spectrum = np.fft.fft(self.samples, self.fft_size)
        spec_amplitude = np.absolute(self.spectrum)
        sample_spacing = 1/self.sample_rate
        freq = np.fft.fftfreq(self.fft_size,sample_spacing)
        argsort = freq.argsort()
        freq_sorted = freq[argsort]
        spec_amplitude_sorted = spec_amplitude[argsort]
        self.amplitude = spec_amplitude_sorted
        self.freq = freq_sorted
        
        self.filtered_samples = self.signal_proc.lowPassFiltering(self.samples, self.sample_rate)
        self.filtered_spectrum = np.fft.fft(self.filtered_samples, self.fft_size)
        filt_amplitude = np.absolute(self.filtered_spectrum)
        filt_amplitude_sorted = filt_amplitude[argsort]
        self.filtered_amplitude = filt_amplitude_sorted
        self.readBits()
        
    def readBits(self):
        """GFSK demodulation and then bits generation."""
        fil = self.signal_proc.demodulator(self.filtered_samples, self.sample_rate)
        self.samples_bits = self.signal_proc.binarySlicer(fil, self.sample_rate)        
    
    def setIndex(self, value):
        """Set a new index for loading SDR device.
        
        Args:
            value: int sdr device index.
        """
        self.index = value
        
    def isRunning(self):
        """Returns:
            A bool value representing if SDR is running (openned).
        """
        return self.running
    
    def setSampleRate(self, value):
        """Set SDR sample rate.
        
        Args:
            value: Int value of sample rate.
        """
        self.sample_rate = value
        if self.isRunning():
            self.sdr.sample_rate = value
    
    def setCenterFreq(self, value):
        """Set SDR center frequency.
        
        Args:
            value: Int value of center frequency.
        """
        self.center_freq = value
        if self.isRunning():
            self.sdr.center_freq = value
    
    def setGain(self, value):
        """Set SDR gain.
        
        Args:
            value: Int value of gain.
        """
        self.gain = value
        if self.isRunning():
            self.sdr.gain = value
    
    def setSampleSize(self, value):
        """Set sample size (SDR sample length).
        
        Args:
            value: Int value of sample size (SDR sample length).
        """
        self.sample_size = value
        
    def setTimerPeriod(self, value):
        """Set timer period (time between each sample processing).
        
        Args:
            value: Int value of timer period (time between each sample processing) in miliseconds.
        """
        self.timer_period = value
    
    def setFFTSize(self, value):
        """Set fft length.
        
        Args:
            value: Int value of fft length.
        """
        self.fft_size = value
