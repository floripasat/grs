"""
Manage a single graph,containing FTT and Waterfall from a SDR.
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


class ControlSignalGraph(object):
    """
    Control signal graph. It creates a graph and plots into it the FFT and Waterfall signal read on SDR.
    
    Attributes:
        widget: QWidget object, where the graph will be created.
        sample_rate: Int value of the SDR sample rate.
        center_freq: Int value of the SDR center (desired) frequency.
        sample_size: Int value of the SDR sample size.
        gain: Int value of the SDR gain.
        timer_period: Int value of the QTimer timer period, in miliseconds.
        min_fft_y: Int minimum FFT Y graph value.
        max_fft_y: Int minimum FFT Y graph value.
        pw_spectrum: Pyqtgraph PlotWidget object of the FFT.
        pw_waterfall: Pyqtgraph PlotWidget object of the Waterfall.
        plot_spectrum: Pyqtgraph PlotWidget PlotItem object of pw_spectrum, witch plots the FFT graph.
        plot_waterfll: Pyqtgraph PlotWidget PlotItem object of pw_waterfall, witch plots the Waterfall graph.
        timer: QTimer object, witch calls the graph to update every timer_period miliseconds.
    """
    def __init__(self, widget, ctrl_sdr):
        """
        Default values initialization, interface creation and timer instance creation.
        
        Args:
            widget: QWidget instance, where the graph will be created.
            ctrl_sdr: ControlSDR instance.
        """
        self.widget = widget
        self.sample_rate = 2.4e6
        self.center_freq = 100.9e6
        self.bandwidth = 10e6
        self.sample_size = 1024
        self.gain = 4
        self.timer_period = 100
        self.min_fft_y = -1
        self.max_fft_y = 50
        self.history_size = 100
        self.low_waterfall = 1
        self.high_waterfall = 30
        self.createInterface()
        self.setupWaterfall()
        self.timer = QtCore.QTimer()
        self.timer.timeout.connect(self.updateData)
        self.ctrl_sdr = ctrl_sdr
        
    def createInterface(self):
        """
        Create interface and plot widget objects in order to show two plots: FFT and Waterfall.
        """
        layout = QtGui.QVBoxLayout()
        self.widget.setLayout(layout)
        self.pw_spectrum = pg.PlotWidget(name='Plotion of heart')
        layout.addWidget(self.pw_spectrum)
        self.pw_waterfall = pg.PlotWidget(name='Plotion of water')
        layout.addWidget(self.pw_waterfall)
        self.plot_spectrum = self.pw_spectrum.plot()
        self.pw_spectrum.setLabel('left', 'Relative Power', units='dB')
        self.pw_spectrum.setLabel('bottom', 'Frequency', units='Hz')
        self.pw_spectrum.setYRange(self.min_fft_y,self.max_fft_y)
        self.pw_spectrum.setMouseEnabled(x=False, y=False)
        self.pw_waterfall.setLabel("bottom", "Frequency", units="Hz")
        self.pw_waterfall.setLabel("left", "Time", units="s")
        #self.pw_waterfall.setYRange(-self.history_size, 0)
        self.pw_waterfall.setLimits(xMin=0, yMax=0)
        self.pw_waterfall.setMouseEnabled(x=False, y=False)
    
    def setupWaterfall(self):
        self.waterfallImg = pg.ImageItem()
        self.pw_waterfall.clear()
        self.pw_waterfall.addItem(self.waterfallImg)
        
        window_size = self.pw_waterfall.width()
        self.waterfall_counter = 0
        nyquist = self.sample_rate / 2
        bins = window_size / 2 + 1
        freq_step = nyquist / bins

        # Calculate bin indices
        self.low_index = int(np.floor(self.low_waterfall / freq_step))
        self.high_index = int(np.ceil(self.high_waterfall / freq_step))

        # Snap values to actual bin frequencies
        self.low_waterfall = freq_step * self.low_index
        self.high_waterfall = freq_step * self.high_index

        display_bins = self.high_index - self.low_index

        """
        self.waterfallImgArray = np.zeros((self.history_size, display_bins))
        history_time = self.history_size / self.sample_rate * self.timer_period
        self.waterfallImg.resetTransform()
        self.waterfallImg.setPos(self.low_waterfall, -history_time)
        self.waterfallImg.scale((self.high_waterfall - self.low_waterfall) / display_bins, history_time / self.history_size)
        """
        self.waterfallImgArray = np.zeros((self.history_size, self.sample_size))
        history_time = self.history_size / self.sample_rate * self.timer_period / 1000
        self.waterfallImg.resetTransform()
        self.waterfallImg.setPos(self.center_freq, -history_time)
        self.waterfallImg.scale((self.high_waterfall - self.low_waterfall) / display_bins, history_time / self.history_size)
        #self.waterfallImg.scale((self.high_waterfall - self.low_waterfall) / self.sample_size, history_time / self.history_size)

    def updateData(self):
        """
        Update a frame to the graphs (Spectrum and Waterfall).
        """
        samples = self.ctrl_sdr.readSamples(self.sample_size)
        
        # UPDATE FFT
        fft = np.fft.fft(samples, self.sample_size)
        amplitude = np.absolute(fft)
        
        sample_spacing = 1/self.sample_rate
        freq = np.fft.fftfreq(self.sample_size,sample_spacing)
        
        argsort = freq.argsort()
        freq_sorted = freq[argsort]
        amplitude_sorted = amplitude[argsort]
        freq_scale = freq_sorted + self.center_freq
        
        
        # UPDATE SPECTRUM
        #freq_sorted = np.sort(freq)
        self.redefineSpectrumScale(amplitude_sorted)
        #freq_scale = np.linspace(self.center_freq-self.sample_rate/2, self.center_freq+self.sample_rate/2, num=self.sample_size)
        self.plot_spectrum.setData(x = freq_scale, y = amplitude_sorted)
        
        # UPDATE WATERFALL
        self.waterfallImgArray = np.roll(self.waterfallImgArray, -1, axis=0)
        self.waterfallImgArray[-1] = amplitude_sorted
        self.waterfallImg.setImage(self.waterfallImgArray.T, autoLevels=True, autoRange=True)

    def redefineSpectrumScale(self, amplitude):
        """
        Re-range the graph if a value read is bigger than the grapg maximum.
        """
        maximum = max(amplitude)
        minimum = min(amplitude)
        if self.min_fft_y > minimum:
            self.min_fft_y = minimum
            self.pw_spectrum.setYRange(self.min_fft_y,self.max_fft_y)
        if self.max_fft_y < maximum:
            self.max_fft_y = maximum
            self.pw_spectrum.setYRange(self.min_fft_y,self.max_fft_y)
    
    def startPlotting(self):
        """
        It connects to SDR and start the timer in order to start showing data on the graphs.
        """
        if self.ctrl_sdr.isRunning():
            self.ctrl_sdr.setParameters(self.sample_rate, self.center_freq, self.bandwidth, self.gain)
            self.timer.start(self.timer_period)
    
    def stopPlotting(self):
        """
        Stop showing data, disconects from SDR and stop the timer.
        """
        self.timer.stop()
    
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
