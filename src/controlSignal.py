"""

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
from pyqtgraph.Qt import QtGui, QtCore
import numpy as np
import pyqtgraph as pg
from rtlsdr import RtlSdr

class ControlSignal(object):
    """
    Controls SDR signal and plot it in a widget.
    
    Attributes:
        widget: QWidget instance, where the graph will be.
        sample_rate: Int value of the SDR sample rate.
        center_freq: Int value of the SDR center (desired) frequency.
        sample_size: Int value of the SDR sample size.
        gain: Int value of the SDR gain.
        timer_period: Int value of the QTimer timer period, in miliseconds.
        min_fft_y: Int minimum FFT Y graph value.
        max_fft_y: Int minimum FFT Y graph value.
        pw_fft: Pyqtgraph PlotWidget instance of the FFT.
        pw_waterfall: Pyqtgraph PlotWidget instance of the Waterfall.
        plot_fft: Pyqtgraph PlotWidget PlotItem instance of pw_fft, witch plots the FFT graph.
        plot_waterfll: Pyqtgraph PlotWidget PlotItem instance of pw_waterfall, witch plots the Waterfall graph.
        sdr: RtlSdr instance witch controls the SDR.
        timer: QTimer object, witch calls the graph to update every timer_period miliseconds.
        sdr_index: Int value of the SDR device index.
        _sdr_initiated: Bool representing if RtlSdr instance have already started.
        _sdr_running: Bool representing if SDR is being used by this software.
    """
    def __init__(self, widget):
        """
        Default values initialization, interface creation and timer instance creation
        """
        self.widget = widget
        self.sample_rate = 2.4e6
        self.center_freq = 100.9e6
        self.sample_size = 1024
        self.gain = 4
        self.timer_period = 100
        self.min_fft_y = -1
        self.max_fft_y = 50
        self.createInterface()
        self.timer = QtCore.QTimer()
        self.timer.timeout.connect(self.updateData)
        self.sdr_index = 0
        self._sdr_initiated = False
        self._sdr_running = False
        
    def createInterface(self):
        """
        Create interface and plot widget objects in order to show two plots: FFT and Waterfall
        """
        layout = QtGui.QVBoxLayout()
        self.widget.setLayout(layout)
        self.pw_fft = pg.PlotWidget(name='Plotion of heart')
        layout.addWidget(self.pw_fft)
        self.pw_waterfall = pg.PlotWidget(name='Plotion of water')
        layout.addWidget(self.pw_waterfall)
        self.plot_fft = self.pw_fft.plot()
        self.plot_waterfall = self.pw_fft.plot()
        self.pw_fft.setLabel('left', 'Relative Power', units='dB')
        self.pw_fft.setLabel('bottom', 'Frequency', units='Hz')
        self.pw_fft.setYRange(self.min_fft_y,self.max_fft_y)
        self.pw_fft.setMouseEnabled(x=False, y=False)
    
    def start(self):
        """
        It connects to SDR and start the timer in order to start showing data on the graphs.
        """
        if not self._sdr_running:
            if self._sdr_initiated:
                self.sdr.open(device_index=self.sdr_index)
            else:
                self.sdr = RtlSdr(device_index=self.sdr_index)
                self._sdr_initiated = True
            self.sdr.sample_rate = self.sample_rate
            self.sdr.center_freq = self.center_freq
            self.sdr.gain = self.gain
            self.timer.start(self.timer_period)
            self._sdr_running = True
    
    def stop(self):
        """
        Stop showing data, disconects from SDR and stop the timer.
        """
        if self._sdr_running:
            self.sdr.close()
            self.timer.stop()
            self._sdr_running = False

    def updateData(self):
        """
        Update a frame to the graphs (FFT and Waterfall).
        """
        samples = self.sdr.read_samples(self.sample_size)
        fft = np.fft.fft(samples)
        amplitude = np.absolute(fft)
        self.redefineFFTScale(amplitude)
        freq_scale = np.linspace(self.center_freq-self.sample_rate, self.center_freq+self.sample_rate, num=self.sample_size)
        self.plot_fft.setData(x = freq_scale, y = amplitude)
    
    def redefineFFTScale(self, amplitude):
        """
        Re-range the graph if a value read is bigger than the grapg maximum.
        """
        maximum = max(amplitude)
        minimum = min(amplitude)
        if self.min_fft_y > minimum:
            self.min_fft_y = minimum
            self.pw_fft.setYRange(self.min_fft_y,self.max_fft_y)
        if self.max_fft_y < maximum:
            self.max_fft_y = maximum
            self.pw_fft.setYRange(self.min_fft_y,self.max_fft_y)
    
    def setSampleRate(self, value):
        self.sample_rate = value
    
    def setCenterFreq(self, value):
        self.center_freq = value
    
    def setSampleSize(self, value):
        self.sample_size = value
    
    def setGain(self, value):
        self.gain = value
    
    def setTimerPeriod(self, value):
        self.timer_period = value
        
    def setMinFFTY(self, value):
        self.min_fft_y = value
    
    def setMaxFFTY(self, value):
        self.max_fft_y = value
    
    def setSDRIndex(self, value):
        self.sdr_index = value
    
    def getSampleRate(self):
        return self.sample_rate
    
    def getCenterFreq(self):
        return self.center_freq
    
    def getSampleSize(self):
        return self.sample_size
    
    def getGain(self):
        return self.gain
    
    def getTimerPeriod(self):
        return self.timer_period
        
    def getMinFFTY(self):
        return self.min_fft_y
    
    def getMaxFFTY(self):
        return self.max_fft_y
    
    def getSDRIndex(self):
        return self.sdr_index
