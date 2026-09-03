"""Flag ledger rows whose control flow leaves the row.

A row that only ever exits by branching outside its own [rva, rva+size) is not
a function - it is a fragment of one, and the derived boundary that produced it
is wrong. Converting such a row can never match, because there is no C++ body
whose compiled form is a basic block that falls into its neighbour.

Run it over the gen-* placeholder rows before picking conversion work.
2026-09-03: the raw count this prints is mostly noise. Of the 34 gen rows it
flagged, exactly two are demonstrable fragments - 0x00011230 and 0x00012190,
each the first basic block of a body that continues in the row the ledger
lists next. The rest are the decoder mistaking bytes inside SSE operands and
immediates for jump opcodes. Read a flag before believing it: the test that
holds up is that EVERY escaping branch lands inside the row starting exactly
where this one ends, and even that admits 0x000032DA and 0x00003916, both of
which are complete functions ending in a ret.

The decoder is deliberately naive - it walks bytes looking for jump opcodes
and does not track instruction lengths - so an address far outside the image
is a misparse and only the near, in-image targets are worth reading.
"""

import sys,csv
sys.path.insert(0,'tools')
import build
rows=[]
for r in csv.DictReader(open('reverse/functions.csv',newline='',encoding='utf-8-sig')):
    if 'gen_asm' in (r.get('source') or ''):
        rows.append((int(r['target_rva'],16), int(r['target_size'])))
bad=[]
for rva,size in rows:
    b=build.read_target_bytes(rva,size); end=rva+size
    tg=[]
    i=0
    while i < len(b):
        op=b[i]
        if op in (0xEB,) and i+2<=len(b)-1:
            d=int.from_bytes(b[i+1:i+2],'little',signed=True); tg.append(('jmp8',rva+i+2+d)); i+=2; continue
        if 0x70<=op<=0x7F and i+2<=len(b):
            d=int.from_bytes(b[i+1:i+2],'little',signed=True); tg.append(('jcc8',rva+i+2+d)); i+=2; continue
        if op==0xE9 and i+5<=len(b):
            d=int.from_bytes(b[i+1:i+5],'little',signed=True); tg.append(('jmp32',rva+i+5+d)); i+=5; continue
        if op==0x0F and i+6<=len(b) and 0x80<=b[i+1]<=0x8F:
            d=int.from_bytes(b[i+2:i+6],'little',signed=True); tg.append(('jcc32',rva+i+6+d)); i+=6; continue
        i+=1
    out=[t for k,t in tg if t>=end or t<rva]
    if out: bad.append((rva,size,sorted(set(out))[:4]))
print('gen rows with a branch leaving the row:',len(bad),'of',len(rows))
for rva,size,o in bad: print(f"  {hex(rva):>9} {size:5}B -> {[hex(x) for x in o]}")
