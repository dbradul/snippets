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

# ------------------------------------------------------------------------------------------------------------------
def _ftp_list_files(ftp_host, ftp_path, ftp_user, ftp_password):
    with closing(ftplib.FTP(ftp_host, ftp_user, ftp_password)) as ftp:
        ftp.cwd(ftp_path)
        result = ftp.nlst()

    return result


# ------------------------------------------------------------------------------------------------------------------
# chained maps
[ 
     functools.reduce(lambda y, z: z(y), maps, x)  
     for x in lst 
]

# chained filters
[
    x for x in lst
    if all(f(x) for f in filters)
]
