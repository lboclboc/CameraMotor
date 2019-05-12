#!/usr/bin/env python3

import sys
import re
import os

def escape(str):
    return str.replace('"', '\\"').replace('\n','\\n\\\n')

text = ''
with open(sys.argv[1]) as fin:
    text = fin.read()

chunk = ''
last_pos = 0
sep = ''
print('static const char *%s[] = {' % os.path.splitext(os.path.basename(sys.argv[1]))[0])

for item in re.finditer(r'{{[^{]*}}', text):
    start,end = item.span()
    chunk = text[last_pos:start]
    print('"%s",' % escape(chunk))
    print('template_%s,' % text[start+2:end-2])
    last_pos = end

print('"%s"};' % escape(text[last_pos:]))
