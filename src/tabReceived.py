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
                [OBDH,[self.ui.GBrecobdh,self.ui.verticalLayout_4]],
                [EPS,[self.ui.GBreceps,self.ui.verticalLayout_5]],
                [TTC,[self.ui.GBrecttc,self.ui.verticalLayout_6]],
                [PAYLOADS,[self.ui.GBrecpayloads,self.ui.verticalLayout_7]],
                ]
        self.dataShowMode = dataShowOptions[0]
        self.lastReceivedData = []
        self.setupTab()
        self.setupActions()
    
    def setupTab(self):
        self.ui.Ldatashow.setText(u"Showing")
        self.ui.CBdatashow.addItems(dataShowOptions)
        self.changeDataShowMode()
    
    def setupActions(self):
        QtCore.QObject.connect(self.ui.CBdatashow, QtCore.SIGNAL("currentIndexChanged(int)"), self.changeDataShowMode)
        self.ui.Bdataopen.clicked.connect(self.openReceivedData)
    
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
            