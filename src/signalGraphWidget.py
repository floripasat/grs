"""
Tab flight graphic widget class.
"""

#
#  signalGraphWidget.py
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
from signalPlot import SpectrumPlot, WaterfallPlot


class SignalGraphWidget(pg.GraphicsLayoutWidget):
    """Qt Widget that manages both Spectrum and Waterfall plots of a graphic.
    
    Attributes:
        ctrl_signal: ControlSignal object.
        spectrum: Pyqtgraph PlotItem object to plot spectrum.
        waterfall: Pyqtgraph PlotItem object to plot waterfall.
        timer_period: Int value of timer period in miliseconds.
        timer: QTimer object timer that calls for data updating.
    """
    def __init__(self, ctrl_signal, timer_period=100):
        """Class vairiables definition, Spectrum and Waterfall plots initialization,
        graphics layout and timer definition.
        
        Args:
            ctrl_signal: ControlSignal object.
            timer_period: Int value of timer period in miliseconds.
        """
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
        """Update plots, triggered when timer ends."""
        self.spectrum.update()
        self.waterfall.update()
    
    def startPlot(self):
        """Start timer at timer_period to trigger updatePlot for plot updating."""
        self.timer.start(self.timer_period)
    
    def stopPlot(self):
        """Stop the timer, consequently stops updating plot."""
        self.timer.stop()
        
    def setTimerPeriod(self, value):
        """Set timer period (time between each plot update) and also resets waterfall plot.
        
        Args:
            value: Int value of timer period (time between each plot update) in miliseconds.
        """
        self.timer_period = value
        self.waterfall.setupImage(self.timer_period)
