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