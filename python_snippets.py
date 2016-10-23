"""
Converts float (32 bits) to/from its raw binary represetation according to IEEE754
"""
import struct

def float2bin(num):
    return ''.join(bin(c).replace('0b', '').rjust(8, '0') for c in struct.pack('!f', num))

def bin2float(binary):
    sign = (-1) ** int(binary[0])
    exponent = int(binary[1:9], 2) - 127
    mantissa = '1' + binary[9:]
    result = 0
    for i in mantissa:
        result += int(i) * 2 ** (exponent)
        exponent -= 1
    return sign*result

i=delta=0
while (i <= 100):
    print(bin2float(float2bin(delta)))
    i += 1
    delta += 0.1

    
##############################################
wave  = "~"
boat = "\U0001F6A3"
seagull = "\u033C"
fish = "\U0001F41F"
penguin = "\U0001F427"
wale = "\U0001F40B"
octopus = "\U0001F419"


row = wave*10 + boat + wave*15 + "\n"
fish_row = wave*4 + fish + wave*21 + "\n"
wale_row = wave*10 + wale + wave*15 + "\n"
penguin_row = wave*7 + penguin + wave*18 + "\n"
octopus_row = wave*17 + octopus + wave*8 + "\n"

sea = (row + fish_row + wale_row + penguin_row + octopus_row)
print (sea)

##############################################
print("City\t\t\tPopulation")
print("Odessa\t\t\t1 000 001")
print("Kiev\t\t\t4 000 001")
print("Lviv\t\t\t900 001")
print("Dnepr\t\t\t1 000 002")
