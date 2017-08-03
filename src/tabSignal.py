"""
Tab signal initialization, actions (buttons, comboboxes, etc) setups, layout management.
"""

#
#  tabSignal.py
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
from controlSignalGraph import ControlSignalGraph
from controlSDR import ControlSDR


BEACON_FREQ = 145.9e6
BEACON_SDR_INDEX = 0
TLTC_FREQ = 437.9e6
TLTC_SDR_INDEX = 0
SAMPLE_RATE = 2.4e6
SAMPLE_SIZE = 1024


class ControlTabSignal(object):
    """
    Controls all tab flight interface features.
    
    Attributes:
        ui: UI instance from the class instancer.
    """
    def __init__(self, ui):
        """
        Initializes tab features.
        
        Args:
            ui: UI interface instance.
        """
        super(ControlTabSignal, self).__init__()
        self.ui = ui
        self.setupTab()
        self.setupActions()
        self.setupControlGraphs()
    
    def setupControlGraphs(self):
        """
        Instances tabBeacon and tabTLTC graph controls and set default values.
        """
        self.signal_type = "beacon"
        self.ctrl_sdr = ControlSDR()
        self.csg_beacon = ControlSignalGraph(self.ui.tabBeacon, self.ctrl_sdr)
        self.csg_tltc = ControlSignalGraph(self.ui.tabTLTC, self.ctrl_sdr)
        self.csg_beacon.setCenterFreq(BEACON_FREQ)
        self.csg_beacon.setSampleRate(SAMPLE_RATE)
        self.csg_beacon.setSampleSize(SAMPLE_SIZE)
        self.csg_beacon.setSDRIndex(BEACON_SDR_INDEX)
        self.csg_tltc.setCenterFreq(TLTC_FREQ)
        self.csg_tltc.setSampleRate(SAMPLE_RATE)
        self.csg_tltc.setSampleSize(SAMPLE_SIZE)
        self.csg_tltc.setSDRIndex(TLTC_SDR_INDEX)
    
    def setupTab(self):
        """
        Setups tab content.
        """
        self.ui.SBbeaconfreq.setValue(BEACON_FREQ/1e6)
        self.ui.SBtltcfreq.setValue(TLTC_FREQ/1e6)
    
    def setupActions(self):
        """
        Setups signal connections and button actions.
        """
        QtCore.QObject.connect(self.ui.TWsignal, QtCore.SIGNAL("currentChanged(int)"), self.changeSignalType)
        print "set"
        QtGui.QShortcut(QtGui.QKeySequence("Ctrl+B"), self.ui.tabSignal, self.startBeacon, context=self.ui.tabSignal)
        QtGui.QShortcut(QtGui.QKeySequence("Ctrl+T"), self.ui.tabSignal, self.startTLTC, context=self.ui.tabSignal)
    
    def startBeacon(self):
        """
        Starts showing Beacon signal and, if needed, stops at TLTC.
        """
        self.csg_tltc.stopPlotting()
        self.csg_beacon.startPlotting()
    
    def startTLTC(self):
        """
        Starts showing TLTC signal and, if needed, stops at Beacon.
        """
        self.csg_beacon.stopPlotting()
        self.csg_tltc.startPlotting()
    
    def toggleSDR(self):
        """
        Open/close SDRa and stops plotting graphs.
        """
        if self.ctrl_sdr.isRunning():
            self.csg_beacon.stopPlotting()
            self.csg_tltc.stopPlotting()
            try:
                self.ctrl_sdr.close()
            except:
                pass
        else:
            try:
                self.ctrl_sdr.open()
                self.plotSignalGraph()
            except:
                pass#Emit eventlog signal

    def changeSignalType(self):
        """
        Changes self.signal_type value depending on the current tab. It also changes plot location if SDR is running.
        This functions is supposed to be called when the signal tab changes.
        """
        tab_index = self.ui.TWsignal.currentIndex()
        if tab_index == 0:
            self.signal_type = "beacon"
        elif tab_index == 1:
            self.signal_type = "tltc"
        if self.ctrl_sdr.isRunning():
            self.plotSignalGraph()

    def plotSignalGraph(self):
        """
        Plots the signal (FFT and Waterfall) in the selected tab graph.
        """
        if self.singal_type == "beacon":
            self.csg_tltc.stopPlotting()
            self.csg_beacon.startPlotting()
        elif self.signal_type == "tltc":
            self.csg_beacon.stopPlotting()
            self.csg_tltc.startPlotting()
            