import zlib

for i in xrange(0, 100000000):
    buf = str(i).rjust(3, '0')

    if zlib.crc32(buf) & 0xffffffff == 0x4c61e280:
        print '[*]',buf
    if i % 1000000 == 0:
        print i
