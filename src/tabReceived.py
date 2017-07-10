from PySide import QtCore, QtGui
from satdata import fsattltc, fsatbeacon
from os import listdir
from os.path import isfile, join
from time import sleep

dataShowOptions = ["Current","From file"]
pathToReceivedData = "received/"

def getFolderFiles(mypath):
    allfiles = listdir(mypath)
    onlyfiles = [f for f in allfiles if isfile(join(mypath, f))]
    return onlyfiles

class ControlTabReceived(object):
    def __init__(self, ui):
        super(ControlTabReceived, self).__init__()
        self.ui = ui
        self.optionsData = [["FSAT TLTC", fsattltc],["FSAT BEACON", fsatbeacon]]
        self.data = self.optionsData[0][1].data
        self.dataShowMode = dataShowOptions[0]
        self.lastReceivedData = []
        self.setupTab()
        self.setupActions()
    
    def setupTab(self):
        self.ui.Ldatashow.setText(u"Showing")
        self.ui.CBdatashow.addItems(dataShowOptions)
        options = [o[0] for o in self.optionsData]
        self.ui.CBrectype.addItems(options)
        self.createReceivedDataLabels()
        self.changeDataShowMode()
    
    def setupActions(self):
        self.ui.Bdataopen.clicked.connect(self.openReceivedData)
        QtCore.QObject.connect(self.ui.CBdatashow, QtCore.SIGNAL("currentIndexChanged(int)"), self.changeDataShowMode)
        QtCore.QObject.connect(self.ui.CBrectype, QtCore.SIGNAL("currentIndexChanged(int)"), self.changeDataType)
        
    def createReceivedDataLabels(self):
        self.clearTabWidget()
        maxHeight = 20
        maxWidth = 16777215
        WidgetLayout = QtGui.QHBoxLayout(self.ui.Wreceiveddata)
        WidgetLayout.setSpacing(6)
        WidgetLayout.setContentsMargins(9, 9, 9, 9)
        for GB in self.data:
            GroupBoxData = GB[1]
            GroupBox = QtGui.QGroupBox(self.ui.Wreceiveddata)
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
                Ltitle.setText(u"<html><em><strong>%s</strong></em></html>" % title) 
                Ltitle.setMaximumSize(QtCore.QSize(maxWidth, maxHeight)) 
                GroupBoxLayout.addWidget(Ltitle)
                for option in content: 
                    HLcontent = QtGui.QHBoxLayout() 
                    HLcontent.setContentsMargins(0, 0, 0, 0) 
                    HLcontent.setSpacing(0) 
                    Loption = QtGui.QLabel(GroupBox) 
                    Loption.setText(u"%s:" % option) 
                    Loption.setAlignment(QtCore.Qt.AlignLeft) 
                    Loption.setMaximumSize(QtCore.QSize(maxWidth, maxHeight))
                    Lvalue = QtGui.QLabel(GroupBox)
                    Lvalue.setAlignment(QtCore.Qt.AlignLeft) 
                    Lvalue.setMaximumSize(QtCore.QSize(maxWidth, maxHeight))
                    HLcontent.addWidget(Loption) 
                    HLcontent.addWidget(Lvalue) 
                    widget = QtGui.QWidget(GroupBox) 
                    widget.setLayout(HLcontent) 
                    widget.setMaximumSize(QtCore.QSize(maxWidth, maxHeight)) 
                    GroupBoxLayout.addWidget(widget) 
            spacer = QtGui.QLabel(GroupBox) 
            GroupBoxLayout.addWidget(spacer)
    
    def changeDataType(self):
        self.data = [data[1].data for data in self.optionsData if data[0] == str(self.ui.CBrectype.currentText())][0]
        self.createReceivedDataLabels()
        
    def changeDataShowMode(self):
        CBindex = self.ui.CBdatashow.currentIndex()
        self.dataShowMode = dataShowOptions[CBindex]
        if self.dataShowMode == "From file":
            self.ui.Bdataopen.setEnabled(True)
            self.ui.Ldatashowfile.setEnabled(True)
        else:
            self.ui.Bdataopen.setEnabled(False)
            self.ui.Ldatashowfile.setEnabled(False)
            
    def openReceivedData(self):
        filename = QtGui.QFileDialog.getOpenFileName(title="Load Received Data",dir=pathToReceivedData,filter="Raw data (*.raw)")[0]
        try:
            f = open(filename, "r")
            text = f.read()
            f.close()
            # LEITURA DOS DADOS (text)
            dataShowOpenedFilename = filename.split("/")[-1]
            self.ui.Ldatashowfile.setText(dataShowOpenedFilename)
        except:
            pass
    
    def showData(self):
        if self.dataShowMode == "Current":
            data = self.lastReceivedData
        elif self.dataShowMode == "From file":
            pass#da outro jeito de pegar os dados
        #Agora mostra os dados da variavel "data"
        
    def clearTabWidget(self):
        layout = self.ui.Wreceiveddata.layout()
        if layout != None:
            self.clearLayout(layout)
        QtGui.QWidget().setLayout(layout)
        
    def clearLayout(self, layout):
        if layout is not None:
            while layout.count():
                item = layout.takeAt(0)
                widget = item.widget()
                if widget is not None:
                    widget.deleteLater()
                else:
                    self.clearLayout(item.layout())
            