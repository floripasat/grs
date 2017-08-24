"""
Spectrum and Waterfall plots.
"""

#
#  signalPlot.py
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


class SpectrumPlot(pg.PlotItem):
    """Pyqtgraph PlotItem that shows frequency spectrum and a low pass filter bandwidth selector.
    
    Attributes:
        ctrl_signal: ControlSignal object.
        power_max: Int value of maximum signal power (Y axis).
        power_min: Int value of minimum signal power (Y axis).
        plot: This class plot object.
        bw_region: Pyqtgraph LinearRegionItem that selects a low pass filter bandwidth.
    """
    def __init__(self, ctrl_signal):
        """Default variables definition, plot initialization, low pass filter bandwidth selector initialization.
        
        Args:
            ctrl_signal: ControlSignal object.
        """
        super(SpectrumPlot, self).__init__()
        self.ctrl_signal = ctrl_signal
        self.power_max = 100
        self.power_min = -1
        # Plot initialization
        center_freq = self.ctrl_signal.center_freq
        sample_rate = self.ctrl_signal.sample_rate
        self.plot = self.plot()
        self.setTitle('Frequency Spectrum')
        self.setLabel('left', 'Relative Power', units='')
        self.setLabel('bottom', 'Frequency', units='Hz')
        self.setYRange(self.power_min,self.power_max)
        self.autoRange()
        self.setMouseEnabled(x=False, y=False)
        self.bw_region = pg.LinearRegionItem([center_freq-sample_rate/8,center_freq+sample_rate/8])
        self.bw_region.setZValue(-10)
        self.bw_region.sigRegionChanged.connect(self.changeBandwidthRegion)
        self.addItem(self.bw_region)
        self.changeBandwidthRegion()
    
    def update(self):
        """Update plot and redefine scale from both axis"""
        amplitude = self.ctrl_signal.amplitude
        freq = self.ctrl_signal.freq
        if amplitude is None or freq is None:
            return
        center_freq = self.ctrl_signal.center_freq
        freq_scale = freq + center_freq
        self.redefineScale(amplitude, freq_scale, center_freq)
        self.plot.setData(x = freq_scale, y = amplitude)
    
    def redefineScale(self, amplitude, freq_scale, center_freq):
        """Redefine scale from both axis and relocate region selector if it isn't at the graph.
        
        Args:
            amplitude: Numpy array of floats containing samples amplitudes got after fft.
            freq_scale: Numpy array of floats containing samples frequencies got after fft.
            center_freq: Int value of SDR center frequency.
        """
        # Y Axis
        power_max = max(amplitude)
        power_min = min(amplitude)
        if self.power_min > power_min:
            self.power_min = power_min
            self.setYRange(self.power_min,self.power_max)
        if self.power_max < power_max:
            self.power_max = power_max
            self.setYRange(self.power_min,self.power_max)
        # X Axis
        freq_max = freq_scale[-1]
        freq_min = freq_scale[0]
        self.setXRange(freq_min,freq_max)
        # Set bandwidth region bounds
        self.bw_region.setBounds([freq_min, freq_max])
        
    def changeBandwidthRegion(self):
        bw_begin,_ = self.bw_region.getRegion()
        center_freq = self.ctrl_signal.center_freq
        sample_rate = self.ctrl_signal.sample_rate
        low = (bw_begin - center_freq + sample_rate/2) / sample_rate
        self.ctrl_signal.signal_proc.cutoff = low
        
        
class WaterfallPlot(pg.PlotItem):
    """Pyqtgraph PlotItem that shows spectrum waterfall throught a imagem plotted.
    
    Attributes:
        ctrl_signal: ControlSignal object.
        timer_period: Int value of timer period in miliseconds.
        history_size: Int value of waterfall image array lenght.
        img: Pyqtgraph ImageItem object that is plotted.
        imgArray: Numpy array that stores spectrum aplitudes.
    """
    def __init__(self, ctrl_signal, timer_period=None, history_size=100):
        """Default variables definition, plot initialization, image and image array definition.
        
        Args:
            ctrl_signal: ControlSignal object.
            timer_period: Int value of timer period in miliseconds.
            history_size: Int value of waterfall image array lenght.
        """
        super(WaterfallPlot, self).__init__()
        self.ctrl_signal = ctrl_signal
        self.history_size = history_size
        # Plot initialization
        self.setLabel("bottom", "Frequency", units="Hz")
        self.setLabel("left", "Time")
        self.hideAxis('bottom')
        self.setLimits(xMin=0, yMax=0)
        self.setMouseEnabled(x=False, y=False)
        # Image initialization
        if timer_period is not None:
            self.setupImage(timer_period)
        
    def setupImage(self, timer_period):
        """Setups image and imagea array for plotting.
        
        Args:
            timer_period: Int value of timer period in miliseconds.
        """
        # Get actual values
        sample_rate = self.ctrl_signal.sample_rate
        sample_size = self.ctrl_signal.sample_size
        center_freq = self.ctrl_signal.center_freq
        # Set img and its array
        self.img = pg.ImageItem()
        self.clear()
        self.addItem(self.img)
        self.imgArray = np.zeros((self.history_size, sample_size))
        # Calculate parameters
        window_size = self.width()
        nyquist = sample_rate / 2
        bins = window_size / 2 + 1
        freq_step = nyquist / bins
        # Calculate bin indices
        low_index = int(np.floor(1 / freq_step))
        high_index = int(np.ceil(30 / freq_step))
        # Set waterfall levels and colors
        pos = np.array([0., 1., 0.5, 0.25, 0.75])
        color = np.array([[0,255,255,255], [255,255,0,255], [0,0,0,255], (0, 0, 255, 255), (255, 0, 0, 255)], dtype=np.ubyte)
        cmap = pg.ColorMap(pos, color)
        lut = cmap.getLookupTable(0.0, 1.0, 256)
        self.img.setLookupTable(lut)
        self.img.setLevels([-100,800])
        # Snap values to actual bin frequencies
        low_waterfall = freq_step * low_index
        high_waterfall = freq_step * high_index
        display_bins = high_index - low_index
        # Set waterfall position and scale
        history_time = self.history_size / sample_rate * timer_period / 1000
        self.img.resetTransform()
        self.img.setPos(center_freq - sample_rate/2, -history_time)
        self.img.scale((high_waterfall - low_waterfall) / display_bins, history_time / self.history_size)
    
    def update(self):
        """Update the image throught adding a amplitude array to the last image array item."""
        amplitude = self.ctrl_signal.amplitude
        if amplitude is None:
            return
        self.imgArray = np.roll(self.imgArray, -1, axis=0)
        self.imgArray[-1] = amplitude
        self.img.setImage(self.imgArray.T, autoLevels=True, autoRange=True)


class FilterPlot(pg.PlotItem):
    """Pyqtgraph PlotItem that shows frequency spectrum and a low pass filter bandwidth selector.
    
    Attributes:
        ctrl_signal: ControlSignal object.
        power_max: Int value of maximum signal power (Y axis).
        power_min: Int value of minimum signal power (Y axis).
        plot: This class plot object.
        bw_region: Pyqtgraph LinearRegionItem that selects a low pass filter bandwidth.
    """
    def __init__(self, ctrl_signal):
        """Default variables definition, plot initialization, low pass filter bandwidth selector initialization.
        
        Args:
            ctrl_signal: ControlSignal object.
        """
        super(FilterPlot, self).__init__()
        self.ctrl_signal = ctrl_signal
        self.power_max = 1
        self.power_min = -1
        # Plot initialization
        center_freq = self.ctrl_signal.center_freq
        sample_rate = self.ctrl_signal.sample_rate
        self.plot = self.plot()
        self.setTitle('Filtered Spectrum')
        self.setLabel('left', 'Relative Power', units='')
        self.setLabel('bottom', 'Frequency', units='Hz')
        self.setYRange(self.power_min,self.power_max)
        self.autoRange()
        #self.setXRange(center_freq - sample_rate/2, center_freq + sample_rate/2)
        self.setMouseEnabled(x=False, y=False)      
    
    def update(self, lowcut, highcut):
        """Update plot and redefine scale from both axis"""
        sample_rate = self.ctrl_signal.sample_rate
        center_freq = self.ctrl_signal.center_freq
        sample_size = self.ctrl_signal.sample_size
        """Update plot and redefine scale from both axis"""
        amplitude = self.ctrl_signal.filtered_amplitude
        freq = self.ctrl_signal.freq
        if amplitude is None or freq is None:
            return
        center_freq = self.ctrl_signal.center_freq
        freq_scale = freq + center_freq
        self.redefineScale(amplitude, freq_scale, center_freq)
        self.plot.setData(x = freq_scale, y = amplitude)
    
    def redefineScale(self, amplitude, freq_scale, center_freq):
        """Redefine scale from both axis and relocate region selector if it isn't at the graph.
        
        Args:
            amplitude: Numpy array of floats containing samples amplitudes got after fft.
            freq_scale: Numpy array of floats containing samples frequencies got after fft.
            center_freq: Int value of SDR center frequency.
        """
        # Y Axis
        power_max = max(amplitude)
        power_min = min(amplitude)
        if self.power_min > power_min:
            self.power_min = power_min
            self.setYRange(self.power_min,self.power_max)
        if self.power_max < power_max:
            self.power_max = power_max
            self.setYRange(self.power_min,self.power_max)
        # X Axis
        freq_max = freq_scale[-1]
        freq_min = freq_scale[0]
        self.setXRange(freq_min,freq_max)
