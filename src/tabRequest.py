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
    """Controls all tab request interface features.
    
    Attributes:
        ui: UI instance from the class instancer.
        OPTIONS_DATA: A list that represents what where at request combobox DATA type selector.
        DATA: A list of lists of ordered requestable DATA.
        request_data: A list of request DATA gathered from checkboxes.
    """
    def __init__(self, ui):
        """Initializes tab features.
        
        Args:
            ui: UI interface instance.
        """
        super(ControlTabRequest, self).__init__()
        self.ui = ui        
        self.OPTIONS_DATA = [["FSAT TLTC", fsattltc]]
        self.data = self.OPTIONS_DATA[0][1].DATA
        self.request_data = []
        self.setupTab()
        self.setupActions()
    
    def setupTab(self):
        """Setups tab content."""
        options = [o[0] for o in self.OPTIONS_DATA]
        self.ui.CBreqtype.addItems(options)
        self.createRequestData()
    
    def setupActions(self):
        """Setups button, signal actions."""
        self.ui.Bcfgsaveas.clicked.connect(self.saveRequestData)
        self.ui.Bcfgopen.clicked.connect(self.openRequestData)
        self.ui.Buncheckall.clicked.connect(self.uncheckAll)
        self.ui.Bcheckall.clicked.connect(self.checkAll)
        QtCore.QObject.connect(self.ui.CBreqtype, QtCore.SIGNAL("currentIndexChanged(int)"), self.changeDataType)
    
    def createRequestData(self):
        """Creates interface, labels and groupboxes, for request DATA."""
        self.clearTabWidget()
        max_checkbox_height = 20
        max_label_height = 20
        max_width = 16777215
        sizePolicy = QtGui.QSizePolicy(QtGui.QSizePolicy.Maximum, QtGui.QSizePolicy.Maximum)
        widget_layout = QtGui.QHBoxLayout(self.ui.Wrequestdata)
        widget_layout.setSpacing(6)
        widget_layout.setContentsMargins(9, 9, 9, 9)
        for gb in self.data:
            groupbox_data = gb[1]
            groupbox = QtGui.QGroupBox(self.ui.Wrequestdata)
            groupbox.setTitle(u"%s" % gb[0])
            groupbox.setAlignment(QtCore.Qt.AlignCenter)
            widget_layout.addWidget(groupbox)
            groupbox_layout = QtGui.QVBoxLayout(groupbox)
            groupbox_layout.setSpacing(6)
            groupbox_layout.setContentsMargins(9, 9, 9, 9)
            for group in groupbox_data:
                title = group[0]
                content = group[1]
                label_title = QtGui.QLabel(groupbox)
                label_title.setText(u"<html><em><strong>%s:</strong></em></html>" % title)
                #label_title.setMaximumSize(QtCore.QSize(max_width, max_label_height))
                label_title.setSizePolicy(sizePolicy)
                groupbox_layout.addWidget(label_title)
                for option in content:
                    checkBox = QtGui.QCheckBox(groupbox)
                    checkBox.setText(u"%s" % option)
                    #checkBox.setMaximumSize(QtCore.QSize(max_width, max_checkbox_height))
                    checkBox.setSizePolicy(sizePolicy)
                    groupbox_layout.addWidget(checkBox)
            spacer = QtGui.QLabel(groupbox)
            groupbox_layout.addWidget(spacer)
                
    def changeDataType(self):
        """Changes requested DATA type."""
        self.data = [DATA[1].data for DATA in self.OPTIONS_DATA if DATA[0] == str(self.ui.CBreqtype.currentText())][0]
    
    def getRequestData(self):
        """Puts request DATA from the checkboxes into a class list object (request_data)."""
        self.request_data = []
        for gb in self.OPTIONS_DATA:
            checkboxes = gb[1][0].findChildren(QtGui.QCheckBox)
            for checkbox in checkboxes:
                self.request_data.append(checkbox.isChecked())
                
    
    def setRequestData(self):
        """Set request DATA checkboxes from a class list object (request_data)."""
        i = 0
        for gb in self.OPTIONS_DATA:
            checkboxes = gb[1][0].findChildren(QtGui.QCheckBox)
            for checkbox in checkboxes:
                if self.request_data[i]:
                    status = QtCore.Qt.CheckState.Checked
                else:
                    status = QtCore.Qt.CheckState.Unchecked
                checkbox.setCheckState(status)
                i+=1
    
    def saveRequestData(self):
        """Saves request DATA into a file."""
        self.getRequestData()
        filepath = QtGui.QFileDialog.getSaveFileName(title="Save Request Data Config",dir="cfg/",filter="Config file (*.cfg)")[0]
        try:
            str_request_data = [str(x) for x in self.request_data]
            text = ",".join(str_request_data)
            f = open(filepath,"w")
            f.write(text)
            f.close()
        except:
            pass
        
    
    def openRequestData(self):
        """Loads request DATA from a file."""
        filepath = QtGui.QFileDialog.getOpenFileName(title="Load Request Data Config",dir="cfg/",filter="Config file (*.cfg)")[0]
        try:
            f = open(filepath, "r")
            text = f.read()
            f.close()
            self.request_data = [True if x=="True" else False for x in text.split(",")]
            self.setRequestData()
        except:
            pass
    
    def checkAll(self):
        """Checks all request DATA checkboxes."""
        for gb in self.OPTIONS_DATA:
            checkboxes = gb[1][0].findChildren(QtGui.QCheckBox)
            for checkbox in checkboxes:
                checkbox.setChecked(True)
    
    def uncheckAll(self):
        """Unchecks all request DATA checkboxes."""
        for gb in self.OPTIONS_DATA:
            checkboxes = gb[1][0].findChildren(QtGui.QCheckBox)
            for checkbox in checkboxes:
                checkbox.setChecked(False)
    
    def clearTabWidget(self):
        """Clears (deletes) all QtGui objects from this tab main widget."""
        layout = self.ui.Wrequestdata.layout()
        if layout != None:
            self.clearLayout(layout)
        QtGui.QWidget().setLayout(layout)
        
    def clearLayout(self, layout):
        """Clear this widget layout."""
        if layout is not None:
            while layout.count():
                item = layout.takeAt(0)
                widget = item.widget()
                if widget is not None:
                    widget.deleteLater()
                else:
                    self.clearLayout(item.layout())
