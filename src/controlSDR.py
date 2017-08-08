"""
Controls important functions and parameters of a SDR.
"""

#
#  controlSDR.py
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

from rtlsdr import RtlSdr


class ControlSDR(object):
    """
    Controls SDR signal.
    
    Attributes:
        index: Int value of SDR device index at system.
        running: Bool value to identify if SDR is running.
        sdr: RtlSdr object.
    """
    def __init__(self, index=0):
        """
        Default values initialization.
        
        Args:
            index: Int value of SDR device index at system.
        """
        self.index = index
        self.running = False
    
    def open(self):
        """
        Opens SDR and run.
        """
        self.sdr = RtlSdr(device_index = self.index)
        self.running = True
    
    def close(self):
        """
        Closes SDR.
        """
        self.sdr.close()
        self.running = False
    
    def setParameters(self, sample_rate, center_freq, bandwidth, gain):
        """
        Set sample rate, center frequency and gain parameters on SDR.
        
        Args:
            sample_rate: SDR sample rate.
            center_freq: SDR center frequency.
            gain: SDR gain.
        """
        self.sdr.sample_rate = sample_rate
        self.sdr.center_freq = center_freq
        self.sdr.set_bandwidth(bandwidth)
        self.sdr.gain = gain
    
    def readSamples(self, sample_size):
        """
        Read samples from SDR in a desired sample size.
        
        Args:
            sample_size: sample size.
        
        Returns:
            A list of values (complex).
        """
        return self.sdr.read_samples(sample_size)
    
    def setIndex(self, value):
        """
        Set a new index for loading SDR device.
        """
        self.index = value
        
    def isRunning(self):
        """
        Returns:
            A bool value representing if SDR is running (openned).
        """
        return self.running