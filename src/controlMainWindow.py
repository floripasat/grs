from PySide import QtCore, QtGui
import sys
sys.path.insert(0, '../gui')
from qt import Ui_MainWindow
from tabRequest import ControlTabRequest
from tabReceived import ControlTabReceived
from tabFlight import ControlTabFlight
from tabSignal import ControlTabSignal


class ControlMainWindow(QtGui.QMainWindow):
    def __init__(self, parent=None):
        super(ControlMainWindow, self).__init__(parent)
        self.ui = Ui_MainWindow()
        self.ui.setupUi(self)
        self.setupControlTabs()
        self.setupButtons()
        self.setupIcons()
        self.setupMenuActions()
        self.setupShortcuts()
    
    def setupControlTabs(self):
        self.CtrlFlight = ControlTabFlight(self.ui)
        self.CtrlRequest = ControlTabRequest(self.ui)
        self.CtrlReceived = ControlTabReceived(self.ui)
        self.CtrlSignal = ControlTabSignal(self.ui)
        
    def setupButtons(self):
        pass
    
    def setupIcons(self):
        self.iconStart = QtGui.QIcon()
        self.iconStart.addPixmap(QtGui.QPixmap("../img/icon/start.png"), QtGui.QIcon.Normal, QtGui.QIcon.Off)
        self.ui.TBstartsdr.setIcon(self.iconStart)
        self.iconPing = QtGui.QIcon()
        self.iconPing.addPixmap(QtGui.QPixmap("../img/icon/ping2.png"), QtGui.QIcon.Normal, QtGui.QIcon.Off)
        self.ui.TBping.setIcon(self.iconPing)
        self.iconSend = QtGui.QIcon()
        self.iconSend.addPixmap(QtGui.QPixmap("../img/icon/antenna3.png"), QtGui.QIcon.Normal, QtGui.QIcon.Off)
        self.ui.TBsend.setIcon(self.iconSend)
    
    def setupMenuActions(self):
        self.ui.actionFullscreen.triggered.connect(self.toggleFullScreen)
        self.ui.actionExit.triggered.connect(self.exit)
        self.ui.actionToolbar.triggered.connect(self.toggleToolbar)
        
    def setupShortcuts(self):
        QtGui.QShortcut(QtGui.QKeySequence("Alt+Return"), self, self.toggleFullScreen, context=self)
        QtGui.QShortcut(QtGui.QKeySequence("F11"), self, self.toggleFullScreen, context=self)
        QtGui.QShortcut(QtGui.QKeySequence("Ctrl+E"), self, self.toggleEventLog, context=self)
        QtGui.QShortcut(QtGui.QKeySequence("Esc"), self, self.exit, context=self)
    
    def toggleFullScreen(self):
        if self.isFullScreen():
            self.showNormal()
        else:
            self.showFullScreen()
    
    def toggleEventLog(self):
        if self.ui.TEeventlog.isHidden():
            self.ui.TEeventlog.show()
        else:
            self.ui.TEeventlog.hide()
    
    def toggleToolbar(self):
        if self.ui.Toolbar.isHidden():
            self.ui.Toolbar.show()
        else:
            self.ui.Toolbar.hide()
            
    def exit(self):
        sys.exit()