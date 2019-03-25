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
seagull_row = wave*7 + seagull + wave*18 + "\n\n\n"
fish_row = wave*4 + fish + wave*21 + "\n"
wale_row = wave*10 + wale + wave*15 + "\n"
penguin_row = wave*7 + penguin + wave*18 + "\n"
octopus_row = wave*17 + octopus + wave*8 + "\n"

sea = (seagull_row + row + fish_row + wale_row + penguin_row + octopus_row)
print (sea)

##############################################
delimiter = "    "
print("%s%s%s" % ("City",   delimiter, "Population"))
print("----------------------")
print("%s%s%s" % ("Odessa", delimiter, 1000001))
print("%s%s%s" % ("Kiev",   delimiter, 4000001))
print("%s%s%s" % ("Lviv",   delimiter, 900000))
print("%s%s%s" % ("Dnepr",  delimiter, 1000002))


# -----------------------------------------------------------------
# Print unicode symbol
print("Unicode of %s is %d" % ('a', ord('a')))
print("Symbol with unicode %d is %s" % (97, chr(97)))

print("Unicode of %s is %d" % ('\u26BD', ord('\u26BD')))
print("Symbol with unicode %d is %s" % (0x26BD, chr(0x26BD)))

# listify
print(list(line.strip() for line in open('<new-lines-delimited-file>').read().split('\n')))


# -----------------------------------------------------------------
def chopper(lst, chunk_size):
    return [lst[x : x + chunk_size]
            for x in range(0, len(lst), chunk_size)]


# -----------------------------------------------------------------
dates_to_process = [start_date+timedelta(days=x) for x in range((end_date - start_date).days+1)]


# -----------------------------------------------------------------
# to and from binary represenation
s = 'Слава Україні!'

bin_repr = ''.join(['{:08b}'.format(b) for b in s.encode()])
s2 = bytes([int(bin_repr[x : x + 8], 2) for x in range(0, len(bin_repr), 8)]).decode()

assert s == s2


