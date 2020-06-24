#
#  pkt2wav.py
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
    # args[1] = input bin file
    # args[2] = sample rate in Hz
    # args[3] = baudrate
    # args[4] = output wav file
    input_file = args[1]
    sample_rate_hz = float(args[2])
    baudrate = int(args[3])

    bit_samples = int(sample_rate_hz/baudrate)

    wav_file = wave.open(args[4],'w')
    wav_file.setnchannels(1) # mono
    wav_file.setsampwidth(2)
    wav_file.setframerate(sample_rate_hz)

    write_zeros(wav_file, int(sample_rate_hz/20))

    with open(input_file, "rb") as f:
        byte = f.read(1)
        while byte != b"":
            write_byte(wav_file, bit_samples, ord(byte))
            byte = f.read(1)

    write_zeros(wav_file, int(sample_rate_hz/20))

    wav_file.close()


if __name__ == '__main__':
    import sys
    sys.exit(main(sys.argv))
