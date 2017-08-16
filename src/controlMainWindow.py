"""
SetupsMainwindow buttons, icons, menu actions and shortcuts for main window. Window functions are defined here (eg. toggle fullscreen).
"""

#
#  controlMainWindow.py
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
import sys
sys.path.insert(0, '../gui')
from qt import Ui_MainWindow
from tabRequest import ControlTabRequest
from tabReceived import ControlTabReceived
from tabFlight import ControlTabFlight
from tabSignal import ControlTabSignal


class ControlMainWindow(QtGui.QMainWindow):
    """
    Main class, it manage other classes and main window features.
    
    Attributes:
        ui: UI instance.
    """
    def __init__(self, parent=None):
        """
        Initializes UI interface, tab control classes, buttons, icons, menu actions and main shortcuts for the main window context.
        """
        super(ControlMainWindow, self).__init__(parent)
        self.ui = Ui_MainWindow()
        self.ui.setupUi(self)
        self.setupControlTabs()
        self.setupButtons()
        self.setupIcons()
        self.setupMenuActions()
        self.setupShortcuts()
    
    def setupControlTabs(self):
        """
        Instances and initializes tab control classes.
        """
        self.ctrl_flight = ControlTabFlight(self.ui)
        self.ctrl_request = ControlTabRequest(self.ui)
        self.ctrl_received = ControlTabReceived(self.ui)
        self.ctrl_signal = ControlTabSignal(self.ui)
        
    def setupButtons(self):
        """
        Connects all main window buttons to functions.
        """
        self.ui.TBstartsdr.clicked.connect(self.ctrl_signal.toggleSDR)
    
    def setupIcons(self):
        """
        Sets toolbar buttons icon and connects them to functions.
        """
        self.icon_start = QtGui.QIcon()
        self.icon_start.addPixmap(QtGui.QPixmap("../img/icon/media-playback-start.png"), QtGui.QIcon.Normal, QtGui.QIcon.Off)
        self.ui.TBstartsdr.setIcon(self.icon_start)
        self.icon_ping = QtGui.QIcon()
        self.icon_ping.addPixmap(QtGui.QPixmap("../img/icon/reload.png"), QtGui.QIcon.Normal, QtGui.QIcon.Off)
        self.ui.TBping.setIcon(self.icon_ping)
        self.icon_send_request = QtGui.QIcon()
        self.icon_send_request.addPixmap(QtGui.QPixmap("../img/icon/go-up.png"), QtGui.QIcon.Normal, QtGui.QIcon.Off)
        self.ui.TBsendreq.setIcon(self.icon_send_request)
        self.icon_send_data_read = QtGui.QIcon()
        self.icon_send_data_read.addPixmap(QtGui.QPixmap("../img/icon/go-home.png"), QtGui.QIcon.Normal, QtGui.QIcon.Off)
        self.ui.TBsenddataread.setIcon(self.icon_send_data_read)
        self.icon_config = QtGui.QIcon()
        self.icon_config.addPixmap(QtGui.QPixmap("../img/icon/document-properties.png"), QtGui.QIcon.Normal, QtGui.QIcon.Off)
        self.ui.TBconfig.setIcon(self.icon_config)
    
    def setupMenuActions(self):
        """
        Connects all menu actions (options) to functions.
        """
        self.ui.actionFullscreen.triggered.connect(self.toggleFullScreen)
        self.ui.actionExit.triggered.connect(self.exit)
        self.ui.actionToolbar.triggered.connect(self.toggleToolbar)
        
    def setupShortcuts(self):
        """
        Creates shortcuts and connects the to functions.
        """
        QtGui.QShortcut(QtGui.QKeySequence("Alt+Return"), self, self.toggleFullScreen, context=self)
        QtGui.QShortcut(QtGui.QKeySequence("F11"), self, self.toggleFullScreen, context=self)
        QtGui.QShortcut(QtGui.QKeySequence("Ctrl+E"), self, self.toggleEventLog, context=self)
        QtGui.QShortcut(QtGui.QKeySequence("Esc"), self, self.exit, context=self)
    
    def toggleFullScreen(self):
        """
        Toggles fullscreen view mode.
        """
        if self.isFullScreen():
            self.showNormal()
        else:
            self.showFullScreen()
    
    def toggleEventLog(self):
        """
        Shows/unshows event log text block.
        """
        if self.ui.TEeventlog.isHidden():
            self.ui.TEeventlog.show()
        else:
            self.ui.TEeventlog.hide()
    
    def toggleToolbar(self):
        """
        Shows/unshows toolbar.
        """
        if self.ui.Toolbar.isHidden():
            self.ui.Toolbar.show()
        else:
            self.ui.Toolbar.hide()
            
    def exit(self):
        """
        Exits the program.
        """
        sys.exit()
        