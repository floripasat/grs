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
from signalGraphWidget import SignalGraphWidget


BEACON_FREQ = 145.9e6
TLTC_FREQ = 437.9e6
SAMPLE_RATE = 1e6
SAMPLE_SIZE = 1024
GAIN = 4
TIMER_PERIOD = 100


class ControlTabSignal(object):
    """Controls all tab signal interface features.
    
    Attributes:
        ui: UI instance from the class instancer.
        ctrl_tab_signal: control signal object.
        signal_type: string containing signal type.
        ctrl_sdr: ControlSDR object to control sdr parameters and read data.
        csg_beacon: ControlSignalGraph object that controls tabBeacon graphs: signal spectrum and watefall.
        csg_tltc: ControlSignalGraph object that controls tabTLTC graphs: signal spectrum and watefall.
    """
    def __init__(self, ui, ctrl_signal):
        """Initializes tab features.
        
        Args:
            ui: UI interface instance.
        """
        super(ControlTabSignal, self).__init__()
        self.ui = ui
        self.ctrl_signal = ctrl_signal
        self.setupTab()
        self.setupActions()
        self.signal_type = "beacon"
    
    def setupTab(self):
        """Setups tab content."""
        self.ui.SBbeaconfreq.setValue(BEACON_FREQ/1e6)
        self.ui.SBtltcfreq.setValue(TLTC_FREQ/1e6)
        self.ctrl_signal.setCenterFreq(BEACON_FREQ)
        self.ctrl_signal.setSampleRate(SAMPLE_RATE)
        self.ctrl_signal.setSampleSize(SAMPLE_SIZE)
        self.ctrl_signal.setGain(GAIN)
        self.ctrl_signal.setTimerPeriod(TIMER_PERIOD)
        self.gw_beacon = SignalGraphWidget(self.ctrl_signal, TIMER_PERIOD)
        self.gw_tltc = SignalGraphWidget(self.ctrl_signal, TIMER_PERIOD)
        beaconLayout = QtGui.QVBoxLayout()
        beaconLayout.addWidget(self.gw_beacon)
        tltcLayout = QtGui.QVBoxLayout()
        tltcLayout.addWidget(self.gw_tltc)
        self.ui.tabBeacon.setLayout(beaconLayout)
        self.ui.tabTLTC.setLayout(tltcLayout)
     
    def setupActions(self):
        """Setups signal connections and button actions."""
        QtCore.QObject.connect(self.ui.TWsignal, QtCore.SIGNAL("currentChanged(int)"), self.changeSignalType)
    
    def plotSignalGraph(self):
        """Start plotting in the graph at the current tab."""
        if self.signal_type == "beacon":
            self.gw_beacon.startPlot()
            self.gw_tltc.stopPlot()
        elif self.signal_type == "tltc":
            self.gw_tltc.startPlot()
            self.gw_beacon.stopPlot()
            
    
    def toggleSDR(self):
        """Open/close SDRa and stops plotting graphs."""

        if self.ctrl_signal.isRunning():
            self.gw_beacon.stopPlot()
            self.gw_tltc.stopPlot()
            try:
                self.ctrl_signal.close()
            except:
                pass
        else:
            try:
                self.ctrl_signal.open()
                self.plotSignalGraph()
            except:
                pass#Emit eventlog signal - SDR load failure

    def changeSignalType(self):
        """Changes self.signal_type value depending on the current tab. It also changes plot location if SDR is running.
        This functions is supposed to be called when the signal tab changes.
        """
        tab_index = self.ui.TWsignal.currentIndex()
        if tab_index == 0:
            self.signal_type = "beacon"
            self.ctrl_signal.setCenterFreq(BEACON_FREQ)
        elif tab_index == 1:
            self.signal_type = "tltc"
            self.ctrl_signal.setCenterFreq(TLTC_FREQ)
        if self.ctrl_signal.isRunning():
            self.plotSignalGraph()
            