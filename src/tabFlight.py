from PySide import QtCore, QtGui

mainMap = "worldmap-lq"
mapFolder = "../img/"

class ControlTabFlight(object):
    def __init__(self, ui):
        super(ControlTabFlight, self).__init__()
        self.ui = ui
        self.setupActions()
        self.setWorldMap(mainMap)
    
    def setupActions(self):
        QtGui.QShortcut(QtGui.QKeySequence("S+M+W"), self.ui.Lworldmap, self.superSecretWorldMap, context=self.ui.Lworldmap)
            
    def setWorldMap(self, imgName):
        imgDir = "%s.jpg" % (mapFolder+imgName)
        pixmap = QtGui.QPixmap(imgDir)
        pixmap = pixmap.scaled(640,360)
        self.ui.Lworldmap.setPixmap(pixmap)
    
    def superSecretWorldMap(self):
        self.setWorldMap("worldmap-smw")