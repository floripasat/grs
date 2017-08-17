"""
Tab received initialization, actions (buttons, comboboxes, etc) setups, layout management, openning DATA files.
"""

#
#  tabReceived.py
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
from satdata import fsattltc, fsatbeacon
from os import listdir
from os.path import isfile, join
from time import sleep

DATA_SHOW_OPTIONS = ["Current","From file"]
PATH_TO_RECEIVED_DATA = "received/"

def getFolderFiles(folder_path):
    """Fetches a list of path to files (string) from a folder.

    Args:
        folder_path: a string representing the path to the folder
        
    Returns:
        A list of path to files in the folder
    """
    all_content = listdir(folder_path)
    only_files = [f for f in all_content if isfile(join(folder_path, f))]
    return only_files


class ControlTabReceived(object):
    """Controls all tab received interface features.
    
    Attributes:
        ui: UI instance from the class instancer.
        OPTIONS_DATA: A list that represents what where at received combobox DATA type selector.
        DATA: A list of lists of ordered requestable DATA.
        data_show_mode: A string representing the current DATA show mode.
        last_received_data: A string containing last received DATA from satellite.
    """
    def __init__(self, ui):
        """Initializes tab features.
        
        Args:
            ui: UI interface instance.
        """
        super(ControlTabReceived, self).__init__()
        self.ui = ui
        self.OPTIONS_DATA = [["FSAT TLTC", fsattltc],["FSAT BEACON", fsatbeacon]]
        self.data = self.OPTIONS_DATA[0][1].DATA
        self.data_show_mode = DATA_SHOW_OPTIONS[0]
        self.last_received_data = []
        self.setupTab()
        self.setupActions()
    
    def setupTab(self):
        """Setups tab content."""
        self.ui.Ldatashow.setText(u"Showing")
        self.ui.CBdatashow.addItems(DATA_SHOW_OPTIONS)
        options = [o[0] for o in self.OPTIONS_DATA]
        self.ui.CBrectype.addItems(options)
        self.createReceivedDataLabels()
        self.changeDataShowMode()
    
    def setupActions(self):
        """Setups button, signal actions."""
        self.ui.Bdataopen.clicked.connect(self.openReceivedData)
        QtCore.QObject.connect(self.ui.CBdatashow, QtCore.SIGNAL("currentIndexChanged(int)"), self.changeDataShowMode)
        QtCore.QObject.connect(self.ui.CBrectype, QtCore.SIGNAL("currentIndexChanged(int)"), self.changeDataType)
        
    def createReceivedDataLabels(self):
        """Creates interface, labels and groupboxes, for received DATA for the selected DATA type (beacon, tltc, etc.)."""
        self.clearTabWidget()
        max_height = 20
        max_width = 16777215
        widget_layout = QtGui.QHBoxLayout(self.ui.Wreceiveddata)
        widget_layout.setSpacing(6)
        widget_layout.setContentsMargins(9, 9, 9, 9)
        for GB in self.data:
            groupbox_data = GB[1]
            groupbox = QtGui.QGroupBox(self.ui.Wreceiveddata)
            groupbox.setTitle(u"%s" % GB[0])
            groupbox.setAlignment(QtCore.Qt.AlignCenter)
            widget_layout.addWidget(groupbox)
            groupbox_layout = QtGui.QVBoxLayout(groupbox)
            groupbox_layout.setSpacing(6)
            groupbox_layout.setContentsMargins(9, 9, 9, 9)
            for group in groupbox_data: 
                title = group[0] 
                content = group[1] 
                label_title = QtGui.QLabel(groupbox) 
                label_title.setText(u"<html><em><strong>%s</strong></em></html>" % title) 
                label_title.setMaximumSize(QtCore.QSize(max_width, max_height)) 
                groupbox_layout.addWidget(label_title)
                for option in content: 
                    horizontal_layout_content = QtGui.QHBoxLayout() 
                    horizontal_layout_content.setContentsMargins(0, 0, 0, 0) 
                    horizontal_layout_content.setSpacing(0) 
                    label_option = QtGui.QLabel(groupbox) 
                    label_option.setText(u"%s:" % option) 
                    label_option.setAlignment(QtCore.Qt.AlignLeft) 
                    label_option.setMaximumSize(QtCore.QSize(max_width, max_height))
                    label_value = QtGui.QLabel(groupbox)
                    label_value.setAlignment(QtCore.Qt.AlignLeft) 
                    label_value.setMaximumSize(QtCore.QSize(max_width, max_height))
                    horizontal_layout_content.addWidget(label_option) 
                    horizontal_layout_content.addWidget(label_value) 
                    widget = QtGui.QWidget(groupbox) 
                    widget.setLayout(horizontal_layout_content) 
                    widget.setMaximumSize(QtCore.QSize(max_width, max_height)) 
                    groupbox_layout.addWidget(widget) 
            spacer = QtGui.QLabel(groupbox) 
            groupbox_layout.addWidget(spacer)
    
    def changeDataType(self):
        """Changes received DATA type, calling createReceivedDataLabels() for the selected DATA type (beacon, tltc, etc.)."""
        self.data = [DATAM[1].DATA for DATAM in self.OPTIONS_DATA if DATAM[0] == str(self.ui.CBrectype.currentText())][0]
        self.createReceivedDataLabels()
        
    def changeDataShowMode(self):
        """Changes DATA show mode, enabling/disabling file open button."""
        cb_index = self.ui.CBdatashow.currentIndex()
        self.data_show_mode = DATA_SHOW_OPTIONS[cb_index]
        if self.data_show_mode == "From file":
            self.ui.Bdataopen.setEnabled(True)
            self.ui.Ldatashowfile.setEnabled(True)
        else:
            self.ui.Bdataopen.setEnabled(False)
            self.ui.Ldatashowfile.setEnabled(False)
            
    def openReceivedData(self):
        """Loads received DATA from a file, reading its content and showing it in the tab."""
        filepath = QtGui.QFileDialog.getOpenFileName(title="Load Received Data",dir=PATH_TO_RECEIVED_DATA,filter="Raw DATA (*.raw)")[0]
        try:
            f = open(filepath, "r")
            text = f.read()
            f.close()
            # LEITURA DOS DADOS (text)
            filename = filepath.split("/")[-1]
            self.ui.Ldatashowfile.setText(filename)
        except:
            pass
    
    def showData(self):
        """Shows "Current" or "From file" DATA in the tab."""
        if self.data_show_mode == "Current":
            DATA = self.last_received_data
        elif self.data_show_mode == "From file":
            pass#da outro jeito de pegar os dados
        #Agora mostra os dados da variavel "DATA"
        
    def clearTabWidget(self):
        """Clears (deletes) all QtGui objects from this tab main widget."""
        layout = self.ui.Wreceiveddata.layout()
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
