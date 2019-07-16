#
#  csv_plot.py
#  
#  Copyright (C) 2017-2019, Universidade Federal de Santa Catarina
#  
#  This file is part of FloripaSat-GRS.
#
#  FloripaSat-GRS is free software; you can redistribute it
#  and/or modify it under the terms of the GNU General Public License as
#  published by the Free Software Foundation, either version 3 of the
#  License, or (at your option) any later version.
#  
#  FloripaSat-GRS is distributed in the hope that it will be useful,
#  but WITHOUT ANY WARRANTY; without even the implied warranty of
#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#  GNU General Public License for more details.
#  
#  You should have received a copy of the GNU General Public
#  License along with FloripaSat-GRS; if not, see <http://www.gnu.org/licenses/>.
#  
#

__author__      = "Gabriel Mariano Marcelino"
__copyright__   = "Copyright (C) 2017-2019, Universidade Federal de Santa Catarina"
__credits__     = ["Gabriel Mariano Marcelino"]
__license__     = "GPL3"
__version__     = "0.7.1"
__maintainer__  = "Gabriel Mariano Marcelino"
__email__       = "gabriel.mm8@gmail.com"
__status__      = "Development"


import csv
import matplotlib.pyplot as plt
import datetime

def plot_data(x, y, y_label="Data", c_title="Time x Data", con_points="1", best_curve="0", file_name=""):
    x_label = "Time [sec]"

    # Cubic Linear Regression
    if best_curve == "1":
        fit = plt.polyfit(x, y, 3)
        fit_fn = plt.poly1d(fit)
        plt.plot(x, fit_fn(x), '-g', label='Best curve')

    if con_points == "1":
        if best_curve == "1":
            plt.plot(x, y, '-bo', label='Measures')
        else:
            plt.plot(x, y, '-bo')
    else:
        if best_curve == "1":
            plt.plot(x, y, 'bo', label='Measures')
        else:
            plt.plot(x, y, 'bo')

    plt.title(c_title)
    plt.xlabel(x_label)
    plt.ylabel(y_label)
    if best_curve == "1":
        plt.legend(loc='best')
    #plt.axis([0, x[-1], min(y)*0.999, max(y)*1.001])
    if len(file_name) > 0:
        plt.savefig(file_name, bbox_inches='tight', dpi=600, transparent=True)
    plt.show()


def main(args):
    if len(args) <= 2 or args[1] == '--help':
        print("Usage:")
        print("\t- 1st argument must be the CSV file")                                                                      # args[1]
        print("\t- 2nd argument must be the column to display the data")                                                    # args[2]
        print("\t- 3rd argument (OPTIONAL) is the axis y label")                                                            # args[3]
        print("\t- 4th argument (OPTIONAL) is the plot title")                                                              # args[4]
        print("\t- 5th argument (OPTIONAL) is the connect points flag (True/False)")                                        # args[5]
        print("\t- 6th argument (OPTIONAL) is the plot best curve flag (True/False)")                                       # args[6]
        print("\t- 7th argument (OPTIONAL) is the option to use the system or the satellite time for the x-axis reference") # args[7]
        print("\t- 8th argument (OPTIONAL) is the name of the pdf file to save the plot")                                   # args[8]
        
        return 0

    use_sat_time = False
    if (len(args) == 8):
        if args[7] == "1":
            use_sat_time = True

    column = list()
    time = list()
    sat_time_sec = list()
    with open(args[1]) as csvfile:
        reader = csv.reader(csvfile, delimiter=',', quotechar='|')
        try:
            for row in reader:
                if len(row) > int(args[2]):
                    column.append(float(row[int(args[2])]))
                    if use_sat_time:
                        sat_time_sec.append((int(row[31])*60*60) + (int(row[32])*60) + int(row[33]))
                    else:
                        time.append(datetime.datetime(int(row[0]), int(row[1]), int(row[2]), int(row[3]), int(row[4]), int(row[5])))
        except:
            pass

    time_sec = list()
    i = 0
    if use_sat_time:
        initial_sat_time_sec = sat_time_sec[0]
        for i in range(len(sat_time_sec)):
            sat_time_sec[i] = sat_time_sec[i] - initial_sat_time_sec
            if (i > 1) and (sat_time_sec[i-1] > sat_time_sec[i]):
                sat_time_sec[i] = sat_time_sec[i-1]
            print(sat_time_sec[i])
    else:
        for t in time:
            time_sec.append(int((t - time[0]).total_seconds()))

    if len(args) == 4:          # CSV file, column
        if use_sat_time:
            plot_data(sat_time_sec, column, args[3])
        else:
            plot_data(time_sec, column, args[3])
    elif len(args) == 5:        # CSV file, column, y-axis string
        if use_sat_time:
            plot_data(sat_time_sec, column, args[3], args[4])
        else:
            plot_data(time_sec, column, args[3], args[4])
    elif len(args) == 6:        # CSV file, column, y-axis string, curve title
        if use_sat_time:
            plot_data(sat_time_sec, column, args[3], args[4], args[5])
        else:
            plot_data(time_sec, column, args[3], args[4], args[5])
    elif len(args) == 7:        # CSV file, column, y-axis string, curve title, connect points flag
        if use_sat_time:
            plot_data(sat_time_sec, column, args[3], args[4], args[5], args[6])
        else:
            plot_data(time_sec, column, args[3], args[4], args[5], args[6])
    elif len(args) >= 9:        # CSV file, column, y-axis string, curve title, connect points flag, best curve flag
        if use_sat_time:
            plot_data(sat_time_sec, column, args[3], args[4], args[5], args[6], args[8])
        else:
            plot_data(time_sec, column, args[3], args[4], args[5], args[6], args[8])
    else:
        if use_sat_time:
            plot_data(sat_time_sec, column)
        else:
            plot_data(time_sec, column)
    
    return 0


if __name__ == '__main__':
    import sys
    sys.exit(main(sys.argv))
