#
#  bin2wav.py
#  
#  Copyright (C) 2020, Universidade Federal de Santa Catarina
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
__copyright__   = "Copyright (C) 2020, Universidade Federal de Santa Catarina"
__credits__     = ["Gabriel Mariano Marcelino"]
__license__     = "GPL3"
__version__     = "0.7.14"
__maintainer__  = "Gabriel Mariano Marcelino"
__email__       = "gabriel.mm8@gmail.com"
__status__      = "Development"


import wave, struct, math

def write_bit(wav_file, bit_samples, bit):
    for i in range(bit_samples):
        value = int()
        if bit == '1':
            value = 25000   # 32767
        else:
            value = -25000 # -32767
        data = struct.pack('<h', value)
        wav_file.writeframesraw(data)


def write_zeros(wav_file, samples):
    for i in range(samples):
        value = 0
        data = struct.pack('<h', value)
        wav_file.writeframesraw(data)


def int2bin(byte):
    return bin(byte)[2:].zfill(8)


def write_byte(wav_file, bit_samples, byte):
    i = 0
    for i in range(8):
        write_bit(wav_file, bit_samples, int2bin(byte)[i])


def main(args):
    sample_rate_hz = float(args[1])
    baudrate = int(args[2])

    bit_samples = int(sample_rate_hz/baudrate)

    wav_file = wave.open(args[3],'w')
    wav_file.setnchannels(1) # mono
    wav_file.setsampwidth(2)
    wav_file.setframerate(sample_rate_hz)

    write_zeros(wav_file, int(sample_rate_hz/20))

    pkt = [170,170,170,170,93,230,42,126,59,73,205,245,120,94,153,170,72,54,239,140,106,223,226,245,254,22,143,9,214,41,48,120,162,191,62,10,16,241,136,148,205,234,239,82,186,226,244,61,118,66,149,12,193,72,224,86,52,245]

    i = 0
    for i in range(len(pkt)):
        write_byte(wav_file, bit_samples, pkt[i])

    write_zeros(wav_file, int(sample_rate_hz/20))

    wav_file.close()


if __name__ == '__main__':
    import sys
    sys.exit(main(sys.argv))
