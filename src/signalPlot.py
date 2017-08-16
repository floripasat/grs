from PySide import QtCore, QtGui
from pyqtgraph.Qt import QtGui, QtCore
import numpy as np
import pyqtgraph as pg

class SpectrumPlot(pg.PlotItem):
    def __init__(self, ctrl_signal):
        super(SpectrumPlot, self).__init__()
        self.ctrl_signal = ctrl_signal
        self.max = 100
        self.min = -1
        self.bandwidth = None
        
        center_freq = self.ctrl_signal.center_freq
        sample_rate = self.ctrl_signal.sample_rate
        self.plot = self.plot()
        self.setTitle('Frequency Spectrum')
        self.setLabel('left', 'Relative Power', units='')
        self.setLabel('bottom', 'Frequency', units='Hz')
        self.setYRange(self.min,self.max)
        self.autoRange()
        #self.setXRange(center_freq - sample_rate/2, center_freq + sample_rate/2)
        self.setMouseEnabled(x=False, y=False)
        self.bw_region = pg.LinearRegionItem([center_freq-sample_rate/8,center_freq+sample_rate/8])
        self.bw_region.setZValue(-10)
        self.addItem(self.bw_region)        
    
    def update(self):
        amplitude = self.ctrl_signal.amplitude
        freq = self.ctrl_signal.freq
        if amplitude is None or freq is None:
            return
        center_freq = self.ctrl_signal.center_freq
        freq_scale = freq + center_freq
        self.redefineScale(amplitude, freq_scale, center_freq)
        self.plot.setData(x = freq_scale, y = amplitude)
    
    def redefineScale(self, amplitude, freq_scale, center_freq):
        """
        Re-range the graph if a value read is bigger than the grapg maximum.
        """
        power_max = max(amplitude)
        power_min = min(amplitude)
        if self.min > power_min:
            self.min = power_min
            self.setYRange(self.min,self.max)
        if self.max < power_max:
            self.max = power_max
            self.setYRange(self.min,self.max)
        freq_max = freq_scale[-1]
        freq_min = freq_scale[0]
        self.setXRange(freq_min,freq_max)
        bw_begin,bw_end = self.bw_region.getRegion()
        if bw_begin < freq_min or bw_end > freq_max:
            begin = (3*center_freq+freq_min)/4
            end = (3*center_freq+freq_max)/4
            self.bw_region.setRegion((begin,end))
            
    
class WaterfallPlot(pg.PlotItem):
    def __init__(self, ctrl_signal, timer_period):
        super(WaterfallPlot, self).__init__()
        self.history_size = 100
        self.ctrl_signal = ctrl_signal
        
        self.setLabel("bottom", "Frequency", units="Hz")
        self.setLabel("left", "Time")
        self.hideAxis('bottom')
        self.setLimits(xMin=0, yMax=0)
        self.setMouseEnabled(x=False, y=False)
        if timer_period is not None:
            self.setupImage(timer_period)
        
    def setupImage(self, timer_period):
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
        amplitude = self.ctrl_signal.amplitude
        if amplitude is None:
            return
        self.imgArray = np.roll(self.imgArray, -1, axis=0)
        self.imgArray[-1] = amplitude
        self.img.setImage(self.imgArray.T, autoLevels=True, autoRange=True)
