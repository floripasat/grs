from PySide import QtCore, QtGui
from pyqtgraph.Qt import QtGui, QtCore
import numpy as np
import pyqtgraph as pg
from signalPlot import SpectrumPlot, WaterfallPlot

class SignalGraphWidget(pg.GraphicsLayoutWidget):
    def __init__(self, ctrl_signal, timer_period=None):
        super(SignalGraphWidget, self).__init__()
        self.ctrl_signal = ctrl_signal
        self.timer_period = timer_period
        
        pg.setConfigOptions(antialias=True)
        self.spectrum = SpectrumPlot(self.ctrl_signal)
        self.waterfall = WaterfallPlot(self.ctrl_signal, self.timer_period)
        self.addItem(self.spectrum)
        self.nextRow()
        self.addItem(self.waterfall)
        
        self.timer = QtCore.QTimer()
        self.timer.timeout.connect(self.updatePlot)
    
    def updatePlot(self):
        self.spectrum.update()
        self.waterfall.update()
    
    def startPlot(self):
        self.timer.start(self.timer_period)
    
    def stopPlot(self):
        self.timer.stop()
        
    def setTimerPeriod(self, value):
        self.timer_period = value
        self.waterfall.setupImage(self.timer_period)