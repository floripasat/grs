"""
This file has request data names for FloripaSat TLTC.
"""

#
#  fsattltc.py
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

data = [["OBDH",OBDH],["EPS",EPS],["TTC",TTC],["Payloads",PAYLOADS]]
