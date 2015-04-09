import re
import sys

with open(sys.argv[1]) as f:
    lines = f.readlines()

lines = filter(lambda l: '//' in l, lines)
lines = map(lambda l: l.strip()[-8:], lines)
lines = map(lambda l: re.findall('..', l)[::-1], lines)
lines = map(lambda l: map(lambda b: chr(int(b, 16)), l), lines)

code = ''.join(reduce(lambda a, b: a + b, lines, []))

with open('il.bin', 'w') as f:
    f.write(code)
