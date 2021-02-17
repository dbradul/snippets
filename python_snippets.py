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



# # -------------------------------------------------------------------------------------------------
# def run_as_process(func, max_request_quota, restore_rate):
#     """
#     """
#     @functools.wraps(func)
#     def inner(self, *args, **kw):
#
#         # # job._cr = cr
#
#         # conn = sql_db.db_connect(cr.dbname)
#         # cr = conn.cursor()
#
#         conn, pool = pooler.restart_pool(cr.dbname, update_module=True)
#         self.pool = pool
#         cr = conn.cursor()
#
#         # cr = pooler.get_db(cr.dbname).cursor()
#         _job_obj = self.pool.get('external.job')
#         job = _job_obj.browse(cr, uid, job.id)
#
#         result = func(self, *args, **kw)
#
#         cr.close()
#         pooler.delete(cr.dbname)
#
#
#         return result
#
#     return inner
    
    
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
