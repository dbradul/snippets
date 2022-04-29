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


##############################################
import logging
_logger = logging.getLogger(__name__)

class StreamToLogger(object):
   """
   Fake file-like stream object that redirects writes to a logger instance.
   """
   def __init__(self, logger, log_level=logging.INFO):
      self.logger = logger
      self.log_level = log_level
      self.linebuf = ''

   def write(self, buf):
      for line in buf.rstrip().splitlines():
         self.logger.log(self.log_level, line.rstrip())

   def flush(self, *args, **kwargs):
      pass
    
_slogger = StreamToLogger(_logger, logging.INFO)
sys.stdout = _slogger

    
# ------------------------------------------------------------------------------------------------------------------
def _download_ftp_file(ftp_host, ftp_path, ftp_user, ftp_password, ftp_filename, local_filename):
    with closing(ftplib.FTP(ftp_host, ftp_user, ftp_password)) as ftp:
        ftp.cwd(ftp_path)
        with open(local_filename, 'wb') as f:
            ftp.retrbinary('RETR ' + ftp_filename, f.write)

#
def _ftp_list_files(ftp_host, ftp_path, ftp_user, ftp_password):
    with closing(ftplib.FTP(ftp_host, ftp_user, ftp_password)) as ftp:
        ftp.cwd(ftp_path)
        result = ftp.nlst()

    return result


# ------------------------------------------------------------------------------------------------------------------
# chained maps
maps = [
    dict({i: chr(i) for i in range(64356)}).get,
    lambda x: x.upper()
]

res = [ 
    functools.reduce(lambda y, z: z(y), maps, x)  
    for x in [1059, 1082, 1088, 1072, 1111, 1085, 1072]
] # УКРАЇНА

# chained filters
filters = [
    lambda x: x % 4 == 0,
    lambda x: (x % 100 != 0) or (x % 400 == 0),
    lambda x: x > 1980
]
res = [
    x for x in range(64356)
    if all(f(x) for f in filters)
] # leaps since 1980

# ------------------------------------------------------------------------------------------------------------------
def camel_2_snake(name):
    "Converts CamelCase to camel_case"
    s1 = re.sub('(.)([A-Z][a-z]+)', r'\1_\2', name)
    return re.sub('([a-z0-9])([A-Z])', r'\1_\2', s1).lower()

# ------------------------------------------------------------------------------------------------------------------
import csv

to_csv = [
    {'name': 'bob', 'age': 25, 'weight': 200},
    {'name': 'jim', 'age': 31, 'weight': 180},
]

keys = to_csv[0].keys()

with open('people.csv', 'w', newline='') as output_file:
    dict_writer = csv.DictWriter(output_file, keys)
    dict_writer.writeheader()
    dict_writer.writerows(to_csv)
