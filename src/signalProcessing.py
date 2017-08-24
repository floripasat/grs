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
from scipy import signal


class SignalProcessing(QtCore.QObject):
    """Controls SDR signal.
    
    Attributes:
        varios
    """
    def __init__(self, index=0):
        """Default values initialization and timer defined.
        
        Args:
            index: Int value of SDR device index at system.
        """
        self.cutoff = None
        self.order = 6
        pass
    
    def bandFiltering(self, data, sample_rate):
        nyq = 0.5 * sample_rate
        cutoff = self.cutoff #/ nyq
        b, a = signal.butter(self.order, cutoff, btype='low')
        filtered = signal.lfilter(b, a, data)
        return filtered
    
    
        
        
        
        