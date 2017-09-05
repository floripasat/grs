"""
Processes received and trasmited signal.
"""

#
#  signalProcessing.py
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
from scipy import signal, fft
import scipy.signal.signaltools as sigtool

class SignalProcessing(QtCore.QObject):
    """Controls SDR signal.
    
    Attributes:
        lpf_cutoff: Low pass filter cutoff frequency.
        butter_order: Butterworth order.
    """
    def __init__(self, index=0):
        """Default values initialization and timer defined.
        
        Args:
            index: Int value of SDR device index at system.
        """
        self.lpf_cutoff = None
        self.butter_order = 6
        self.bit_rate = 1.2e3
        pass
    
    def lowPassFiltering(self, samples, sample_rate):
        """Butterworth low pass filter at center frequecy
        
        Args:
            samples: Input samples to filter.
            sample_rate: Sample rate.
        
        Returns:
            Filtered samples.
        """
        nyq = 0.5 * sample_rate
        norm_cutoff = self.lpf_cutoff / nyq
        b, a = signal.butter(self.butter_order, norm_cutoff, btype='low')
        filtered = signal.lfilter(b, a, samples)
        return filtered
    
    def demodulator(self, samples, sample_rate):
        """GSFK samples demodulator.
        
        Args:
            samples: Array, tuple or list of samples.
            sample_rate: Signal sample rate.
        
        Returns:
            Numpy array type demodulated signal to a NRZ-like waveform.
        """
        abs_samples = np.absolute(samples)
        y_diff = np.diff(abs_samples,1)
        #create an envelope detector and then low-pass filter
        y_env = np.abs(sigtool.hilbert(y_diff))
        h=signal.firwin( numtaps=100, cutoff=self.bit_rate*2, nyq=sample_rate/2)
        y_filtered=signal.lfilter( h, 1.0, y_env)
        return y_filtered
    
    def binarySlicer(self, demod_samples, sample_rate):
        """Generate a bit sequence from demodulated semples
        
        Args:
            demod_samples: Demodulated samples.
            sample_rate: Signal sample rate.
        
        Returns:
            A list of bits.
        """
        mean = np.mean(demod_samples)
        #if the mean of the bit period is higher than the mean, the data is a 0
        rx_data = []
        sampled_signal = demod_samples[sample_rate/self.bit_rate/2:len(demod_samples):sample_rate/self.bit_rate]
        for bit in sampled_signal:
            if bit > mean:
                rx_data.append(0)
            else:
                rx_data.append(1)
        return rx_data
    
    
    # Nothing below are used now. The function called "sampleBits" calls the others bellow, and it is used to read
    # the SDR samples and convert to bits an NRZ-like waveform (not GFSK modulated).
        
    def findClockFrequency(self, spectrum):
        """Determine the clock frequency.
        
        Args:
            spectrum: magnitude spectrum of clock signal (np array).
        Returns: 
            FFT bin number of clock frequency
        """
        maxima = signal.argrelextrema(spectrum, np.greater_equal)[0]
        while maxima[0] < 2:
            maxima = maxima[1:]
        if maxima.any():
            threshold = max(spectrum[2:-1])*0.8
            indices_above_threshold = np.argwhere(spectrum[maxima] > threshold)
            return maxima[indices_above_threshold[0]]
        else:
            return 0
    
    def clockRecovery(self, samples):
        """whole packet clock recovery
        
        Args:
            samples: real valued NRZ-like waveform (array, tuple, or list).
                    must have at least 2 samples per symbol.
                    must have at least 2 symbol transitions.
        
        Returns:
            list of symbols.
        """
        a = samples
        if len(a) < 4:
            return []
        mean_a = np.mean(a)
        mean_a_greater = np.ma.masked_greater(a, mean_a)
        high = np.ma.median(mean_a_greater)
        mean_a_less_or_equal = np.ma.masked_array(a, ~mean_a_greater.mask)
        low = np.ma.median(mean_a_less_or_equal)
        mid_a = (high + low) / 2 
        b = (a > mid_a) * 1.0
        d = np.diff(b)**2
        if len(np.argwhere(d > 0)) < 2:
            return []
        f = fft(d, len(a))
        p = self.findClockFrequency(abs(f))
        if p == 0:
            return []
        cycles_per_sample = (p*1.0)/len(f)
        clock_phase = 0.5 + np.angle(f[p])/(2*np.pi)
        if clock_phase <= 0.5:
            clock_phase += 1
        symbols = []
        for i in range(len(a)):
            if clock_phase >= 1:
                clock_phase -= 1
                symbols.append(a[i])
            clock_phase += cycles_per_sample
        if False:
            print("peak frequency index: %d / %d" % (p, len(f)))
            print("samples per symbol: %f" % (1.0/cycles_per_sample))
            print("clock cycles per sample: %f" % (cycles_per_sample))
            print("clock phase in cycles between 1st and 2nd samples: %f" % (clock_phase))
            print("clock phase in cycles at 1st sample: %f" % (clock_phase - cycles_per_sample/2))
            print("symbol count: %d" % (len(symbols)))
        return symbols
    
    def sliceBits(self, symbols):
        """Convert soft symbols into bits (assuming binary symbols).
        
        Args:
            symbols: list of symbols.
        
        Return:
            List of bits (1 and 0).
        """
        symbols_average = np.average(symbols)
        bits = (symbols >= symbols_average)
        return np.array(bits, dtype=np.uint8)
    
    def samplesBits(self, samples):
        """Signal samples demodulation, clock recovery and binary slice to get the bit sequence.
        
        Args:
            samples: Array, tuple or list of samples.
            
        Returns:
            List of bits (1 and 0).
        """
        symbols = self.clockRecovery(samples)
        bits = self.sliceBits(symbols)
        return bits
