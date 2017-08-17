"""
Tab flight initialization, actions (buttons, comboboxes, etc) setups, layout management.
"""

#
#  tabFlight.py
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

MAIN_MAP = "worldmap-lq"
MAP_FOLDER = "../img/"


class ControlTabFlight(object):
    """Controls all tab flight interface features.
    
    Attributes:
        ui: UI instance from the class instancer.
    """
    def __init__(self, ui):
        """Initializes tab features.
        
        Args:
            ui: UI interface instance.
        """
        super(ControlTabFlight, self).__init__()
        self.ui = ui
        self.setupActions()
        self.setWorldMap(MAIN_MAP)
    
    def setupActions(self):
        """Setups tab shortcuts actions."""
        QtGui.QShortcut(QtGui.QKeySequence("S+M+W"), self.ui.Lworldmap, self.superSecretWorldMap, context=self.ui.Lworldmap)
            
    def setWorldMap(self, img_name):
        """Change world map picture.
        
        Args:
            img_name: A string containg the worldmap image name.
        """
        img_path = "%s.jpg" % (MAP_FOLDER+img_name)
        pixmap = QtGui.QPixmap(img_path)
        pixmap = pixmap.scaled(640,360)
        self.ui.Lworldmap.setPixmap(pixmap)
    
    def superSecretWorldMap(self):
        """Change world map to Super Mario World map as an easter egg.
        """
        self.setWorldMap("worldmap-smw")
