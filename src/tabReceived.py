from PySide import QtCore, QtGui
from satelliteData import OBDH,EPS,TTC,PAYLOADS
from os import listdir
from os.path import isfile, join

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
        self.optionsData = [
                [OBDH,[self.ui.GBrecobdh,self.ui.verticalLayout_10]],
                [EPS,[self.ui.GBreceps,self.ui.verticalLayout_9]],
                [TTC,[self.ui.GBrecttc,self.ui.verticalLayout_12]],
                [PAYLOADS,[self.ui.GBrecpayloads,self.ui.verticalLayout_11]],
                ]
        self.dataShowMode = dataShowOptions[0]
        self.lastReceivedData = []
        self.setupTab()
        self.setupActions()
    
    def setupTab(self):
        self.ui.Ldatashow.setText(u"Showing")
        self.ui.CBdatashow.addItems(dataShowOptions)
        self.createReceiveDataLabels()
        self.changeDataShowMode()
    
    def setupActions(self):
        QtCore.QObject.connect(self.ui.CBdatashow, QtCore.SIGNAL("currentIndexChanged(int)"), self.changeDataShowMode)
        self.ui.Bdataopen.clicked.connect(self.openReceivedData)
        
    def createReceiveDataLabels(self):
        maxHeight = 20
        maxWidth = 16777215
        for GB in self.optionsData: 
            GroupBoxData = GB[0] 
            GroupBox = GB[1][0] 
            GroupBoxLayout = GB[1][1] 
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
            