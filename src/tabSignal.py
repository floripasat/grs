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
from controlSignal import ControlSignal

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
        self.cs_beacon = ControlSignal(self.ui.tabBeacon)
        self.cs_tltc = ControlSignal(self.ui.tabTLTC)
        self.cs_beacon.setCenterFreq(BEACON_FREQ)
        self.cs_beacon.setSampleRate(SAMPLE_RATE)
        self.cs_beacon.setSampleSize(SAMPLE_SIZE)
        self.cs_beacon.setSDRIndex(BEACON_SDR_INDEX)
        self.cs_tltc.setCenterFreq(TLTC_FREQ)
        self.cs_tltc.setSampleRate(SAMPLE_RATE)
        self.cs_tltc.setSampleSize(SAMPLE_SIZE)
        self.cs_tltc.setSDRIndex(TLTC_SDR_INDEX)
    
    def setupTab(self):
        """
        Setups tab content.
        """
        self.ui.SBbeaconfreq.setValue(BEACON_FREQ/1e6)
        self.ui.SBtltcfreq.setValue(TLTC_FREQ/1e6)
    
    def setupActions(self):
        """
        Setups shortcut actions.
        """
        QtGui.QShortcut(QtGui.QKeySequence("Ctrl+B"), self.ui.tabSignal, self.startBeacon, context=self.ui.tabSignal)
        QtGui.QShortcut(QtGui.QKeySequence("Ctrl+T"), self.ui.tabSignal, self.startTLTC, context=self.ui.tabSignal)
    
    def startBeacon(self):
        """
        Starts showing Beacon signal and, if needed, stops at TLTC.
        """
        if self.cs_beacon.getSDRIndex() == self.cs_tltc.getSDRIndex():
            self.cs_tltc.stop()
        self.cs_beacon.start()
    
    def startTLTC(self):
        """
        Starts showing TLTC signal and, if needed, stops at Beacon.
        """
        if self.cs_beacon.getSDRIndex() == self.cs_tltc.getSDRIndex():
            self.cs_beacon.stop()
        self.cs_tltc.start()
