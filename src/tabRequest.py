OBDH = [
        ["Systems Status",  ["Reset counter",
                             "Test Modules Flags"]],
        
        ["IMU",             ["Accelerometer",
                             "Gyroscope",
                             "Magnetometer",
                             "Temperature"]],
        
        ["MSP Sensors",     ["Voltage",
                             "Current",
                             "Temperature"]],
        
        ["Systick",         ["System Tick Count"]],
        
        ["Solar Panels",    ["Acceleromoter",
                             "Gyroscope",
                             "Magnetometer",
                             "Sun Sensor",
                             "Temperature"]],
        
        ["Transciever",     ["Last 5 received cmd and data uplink"]],
    ]


EPS = [
        ["ADC Solar Panels",["Solar Panel Voltage",
                             "Solar Panel Current"]],
        
        ["ADC",             ["Total Voltage",
                             "Bus Voltage",
                             "Beacon/EPS Current",
                             "Internal Temp. Sensor"]],
        
        ["Battery Monitor", ["Average Current",
                             "Temperature",
                             "Voltage",
                             "Current",
                             "Accumulated Current",
                             "Protection Register",
                             "Status Register",
                             "Cycle Counter Register",
                             "Remaining Active Absolute Capacity Reg.",
                             "Remaining Standby Absolute Capacity Reg.",
                             "Remaining Active Relative Capacity",
                             "Remaining Standby Relative Capacity"]],
        
        ["ADS1248",         ["7 RTDs Measurements"]],
        
        ["Task Scheduler",  ["Task Scheduler"]],
    ]


TTC = [
        ["Beacon",          ["TX Temperature",
                             "Transmitted Power",
                             "DAC Voltage"]],
        
        ["Transceiver",     ["Transceiver Temperature",
                             "Received Signal Power",
                             "Transmitted Power",
                             "DAC Voltage"]],
    ]

PAYLOADS = [
        ["Joinville",       ["Thermoeletric Generator Voltage",
                             "Stored Energy (last 3 min)"]],
        
        ["RUSH",             ["RUSH Data"]],
    ]

from PySide import QtCore, QtGui

class ControlTabRequest(object):
    def __init__(self, ui):
        super(ControlTabRequest, self).__init__()
        self.ui = ui
        self.optionsData = [
                [OBDH,[self.ui.GBreqobdh,self.ui.verticalLayout_4]],
                [EPS,[self.ui.GBreqeps,self.ui.verticalLayout_5]],
                [TTC,[self.ui.GBreqttc,self.ui.verticalLayout_6]],
                [PAYLOADS,[self.ui.GBreqpayloads,self.ui.verticalLayout_7]],
                ]
        self.requestData = []
        self.createRequestData()
        
        
    def createRequestData(self):
        maxCBHeight = 15
        maxLHeight = 20
        maxWidth = 16777215
        for GB in self.optionsData:
            GroupBoxData = GB[0]
            GroupBox = GB[1][0]
            GroupBoxLayout = GB[1][1]
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
                
    def refreshRequestData(self):
        self.requestData = []
        for GB in self.optionsData:
            CBs = GB[1][0].findChildren(QtGui.QCheckBox)
            for CB in CBs:
                self.requestData.append(CB.isChecked())
                
    
    def setRequestData(self):
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
        self.refreshRequestData()
        filename = QtGui.QFileDialog.getSaveFileName(title="Save Request Data Config",dir="cfg/",filter="Config file (*.cfg)")[0]
        try:
            strRequestData = [str(x) for x in self.requestData]
            text = ",".join(strRequestData)
            f = open(filename,"w")
            f.write(text)
            f.close()
            self.ui.LEcfgfile.setText(unicode(filename))
        except:
            pass
        
    
    def loadRequestData(self):
        filename = QtGui.QFileDialog.getOpenFileName(title="Load Request Data Config",dir="cfg/",filter="Config file (*.cfg)")[0]
        try:
            f = open(filename, "r")
            text = f.read()
            f.close()
            self.requestData = [True if x=="True" else False for x in text.split(",")]
            self.setRequestData()
            self.ui.LEcfgfile.setText(unicode(filename))
        except:
            pass
    
    def checkAll(self):
        for GB in self.optionsData:
            CBs = GB[1][0].findChildren(QtGui.QCheckBox)
            for CB in CBs:
                CB.setChecked(True)
    
    def uncheckAll(self):
        for GB in self.optionsData:
            CBs = GB[1][0].findChildren(QtGui.QCheckBox)
            for CB in CBs:
                CB.setChecked(False)
        