#!/usr/bin/env python

"""
FloripaSat-GRS: The ground station software of the FloripaSat project. This script runs the software.

Main functions that calls all control objects:
    ControlMainWindow: for controling Qt window content.
    ControlSignal: for controling signal read and processing.
"""

#
#  main.py
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
from controlMainWindow import ControlMainWindow
from controlSignal import ControlSignal
import sys


if __name__ == "__main__":
    app = QtGui.QApplication(sys.argv)
    ctrl_signal = ControlSignal()
    my_sw = ControlMainWindow(ctrl_signal)
    my_sw.show()
    sys.exit(app.exec_())
