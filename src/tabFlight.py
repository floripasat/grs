from PySide import QtCore, QtGui

mainMap = "worldmap-lq"
mapFolder = "../img/"

class ControlTabFlight(object):
    def __init__(self, ui):
        super(ControlTabFlight, self).__init__()
        self.ui = ui
        self.setWorldMap(mainMap)
    
    def setWorldMap(self, imgName):
        imgDir = "%s.jpg" % (mapFolder+imgName)
        pixmap = QtGui.QPixmap(imgDir)
        pixmap = pixmap.scaled(640,360)
        self.ui.Lworldmap.setPixmap(pixmap)