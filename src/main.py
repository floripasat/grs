from PySide import QtCore, QtGui
from controlMainWindow import ControlMainWindow
import sys

if __name__ == "__main__":
    app = QtGui.QApplication(sys.argv)
    mySW = ControlMainWindow()
    mySW.show()
    sys.exit(app.exec_())