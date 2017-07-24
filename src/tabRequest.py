"""
Tab request initialization, actions (buttons, comboboxes, etc) setups, layout management, saving and openning config files.
"""

#
#  tabRequest.py
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
from satdata import fsattltc

class ControlTabRequest(object):
    '''
    Controls all tab request interface features.
    '''
    def __init__(self, ui):
        '''
        Initializes tab features.
        '''
        super(ControlTabRequest, self).__init__()
        self.ui = ui        
        self.optionsData = [["FSAT TLTC", fsattltc]]
        self.data = self.optionsData[0][1].data
        self.requestData = []
        self.setupTab()
        self.setupActions()
    
    def setupTab(self):
        '''
        Setups tab content.
        '''
        options = [o[0] for o in self.optionsData]
        self.ui.CBreqtype.addItems(options)
        self.createRequestData()
    
    def setupActions(self):
        '''
        Setups button, signal actions.
        '''
        self.ui.Bcfgsaveas.clicked.connect(self.saveRequestData)
        self.ui.Bcfgopen.clicked.connect(self.openRequestData)
        self.ui.Buncheckall.clicked.connect(self.uncheckAll)
        self.ui.Bcheckall.clicked.connect(self.checkAll)
        QtCore.QObject.connect(self.ui.CBreqtype, QtCore.SIGNAL("currentIndexChanged(int)"), self.changeDataType)
    
    def createRequestData(self):
        '''
        Creates interface, labels and groupboxes, for request data.
        '''
        self.clearTabWidget()
        maxCBHeight = 15
        maxLHeight = 20
        maxWidth = 16777215
        WidgetLayout = QtGui.QHBoxLayout(self.ui.Wrequestdata)
        WidgetLayout.setSpacing(6)
        WidgetLayout.setContentsMargins(9, 9, 9, 9)
        for GB in self.data:
            GroupBoxData = GB[1]
            GroupBox = QtGui.QGroupBox(self.ui.Wrequestdata)
            GroupBox.setTitle(u"%s" % GB[0])
            GroupBox.setAlignment(QtCore.Qt.AlignCenter)
            WidgetLayout.addWidget(GroupBox)
            GroupBoxLayout = QtGui.QVBoxLayout(GroupBox)
            GroupBoxLayout.setSpacing(6)
            GroupBoxLayout.setContentsMargins(9, 9, 9, 9)
            for group in GroupBoxData:
                title = group[0]
                content = group[1]
                Ltitle = QtGui.QLabel(GroupBox)
                Ltitle.setText(u"<html><em><strong>%s:</strong></em></html>" % title)
                Ltitle.setMaximumSize(QtCore.QSize(maxWidth, maxLHeight))
                GroupBoxLayout.addWidget(Ltitle)
                for option in content:
                    checkBox = QtGui.QCheckBox(GroupBox)
                    checkBox.setText(u"%s" % option)
                    checkBox.setMaximumSize(QtCore.QSize(maxWidth, maxCBHeight))
                    GroupBoxLayout.addWidget(checkBox)
            spacer = QtGui.QLabel(GroupBox)
            GroupBoxLayout.addWidget(spacer)
                
    def changeDataType(self):
        '''
        Changes requested data type.
        '''
        self.data = [data[1].data for data in self.optionsData if data[0] == str(self.ui.CBreqtype.currentText())][0]
    
    def getRequestData(self):
        '''
        Puts request data from the checkboxes into a class list object (requestData).
        '''
        self.requestData = []
        for GB in self.optionsData:
            CBs = GB[1][0].findChildren(QtGui.QCheckBox)
            for CB in CBs:
                self.requestData.append(CB.isChecked())
                
    
    def setRequestData(self):
        '''
        Set request data checkboxes from a class list object (requestData).
        '''
        i = 0
        for GB in self.optionsData:
            CBs = GB[1][0].findChildren(QtGui.QCheckBox)
            for CB in CBs:
                if self.requestData[i]:
                    status = QtCore.Qt.CheckState.Checked
                else:
                    status = QtCore.Qt.CheckState.Unchecked
                CB.setCheckState(status)
                i+=1
    
    def saveRequestData(self):
        '''
        Saves request data into a file.
        '''
        self.getRequestData()
        filename = QtGui.QFileDialog.getSaveFileName(title="Save Request Data Config",dir="cfg/",filter="Config file (*.cfg)")[0]
        try:
            strRequestData = [str(x) for x in self.requestData]
            text = ",".join(strRequestData)
            f = open(filename,"w")
            f.write(text)
            f.close()
        except:
            pass
        
    
    def openRequestData(self):
        '''
        Loads request data from a file.
        '''
        filename = QtGui.QFileDialog.getOpenFileName(title="Load Request Data Config",dir="cfg/",filter="Config file (*.cfg)")[0]
        try:
            f = open(filename, "r")
            text = f.read()
            f.close()
            self.requestData = [True if x=="True" else False for x in text.split(",")]
            self.setRequestData()
        except:
            pass
    
    def checkAll(self):
        '''
        Checks all request data checkboxes.
        '''
        for GB in self.optionsData:
            CBs = GB[1][0].findChildren(QtGui.QCheckBox)
            for CB in CBs:
                CB.setChecked(True)
    
    def uncheckAll(self):
        '''
        Unchecks all request data checkboxes.
        '''
        for GB in self.optionsData:
            CBs = GB[1][0].findChildren(QtGui.QCheckBox)
            for CB in CBs:
                CB.setChecked(False)
    
    def clearTabWidget(self):
        '''
        Clears (deletes) all QtGui objects from this tab main widget.
        '''
        layout = self.ui.Wrequestdata.layout()
        if layout != None:
            self.clearLayout(layout)
        QtGui.QWidget().setLayout(layout)
        
    def clearLayout(self, layout):
        '''
        Clear a widget layout.
        '''
        if layout is not None:
            while layout.count():
                item = layout.takeAt(0)
                widget = item.widget()
                if widget is not None:
                    widget.deleteLater()
                else:
                    self.clearLayout(item.layout())
