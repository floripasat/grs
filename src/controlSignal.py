"""
Controls important functions and parameters of a SDR.
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


class ControlSignal(QtCore.QObject):
    """Controls SDR signal.
    
    Attributes:
        index: Int value of SDR device index at system.
        running: Bool value to identify if SDR is running.
        sdr: RtlSdr object.
    """
    def __init__(self, index=0):
        """Default values initialization.
        
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
        self.freq = None
        self.running = False
        self.timer = QtCore.QTimer()
        self.timer.timeout.connect(self.updateData)
    
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
        fft = np.fft.fft(self.samples, self.sample_size)
        amplitude = np.absolute(fft)
        sample_spacing = 1/self.sample_rate
        freq = np.fft.fftfreq(self.sample_size,sample_spacing)
        argsort = freq.argsort()
        freq_sorted = freq[argsort]
        amplitude_sorted = amplitude[argsort]
        self.amplitude = amplitude_sorted
        self.freq = freq_sorted
    
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
        self.sample_rate = value
        if self.isRunning():
            self.sdr.sample_rate = value
    
    def setCenterFreq(self, value):
        self.center_freq = value
        if self.isRunning():
            self.sdr.center_freq = value
    
    def setGain(self, value):
        self.gain = value
        if self.isRunning():
            self.sdr.gain = value
    
    def setSampleSize(self, value):
        self.sample_size = value
        
    def setTimerPeriod(self, value):
        self.timer_period = value
