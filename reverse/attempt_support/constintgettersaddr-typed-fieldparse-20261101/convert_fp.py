"""Rewrite raw-int FieldParse tables in ConstIntGettersAddr.cpp as typed tables.
Field names read from retail; parsers named by the matched row at the parser RVA;
userData named only for owned lists (data_rows.csv), else left as the literal."""
import sys, re, struct
sys.path.insert(0, 'tools')
import build
BASE = 0x400000
SRC = 'Code/GameEngine/Source/Common/ConstIntGettersAddr.cpp'
OWNED_LISTS = {0x00DBC284: 'TheWeaponSlotTypeNames', 0x00DBB4F0: 'TheLocomotorSetNames'}
want = set(sys.argv[1:])
text = open(SRC, encoding='utf-8', newline='').read()
pat = re.compile(r'(// Retail VA (0x[0-9a-fA-F]+)[^\n]*\n)extern const int (\w+)\[(\d+)\] = \{(.*?)\};', re.S)
need = set()
blocks = []
for m in pat.finditer(text):
    if m.group(3) not in want: continue
    words = [int(w, 16) for w in re.findall(r'0x[0-9A-Fa-f]+', m.group(5))]
    blocks.append((m, words))
    for i in range(1, len(words), 4): need.add('0x%08X' % (words[i] - BASE))
rows = {}
for l in open('reverse/functions.csv', encoding='utf-8'):
    f = l.split(',')
    if len(f) > 5 and f[2].upper().replace('0X', '0x') in need and f[5] == 'matched':
        rows.setdefault(f[2].upper().replace('0X', '0x'), []).append(f[0])
def cstr(va):
    b = build.read_target_bytes(va - BASE, 256)
    s = b[:b.index(b'\0')].decode('ascii')
    assert '"' not in s and chr(92) not in s
    return s
used = set()
out = text
report = []
for m, words in reversed(blocks):
    va = int(m.group(2), 16); name = m.group(3)
    retail = build.read_target_bytes(va - BASE, len(words) * 4)
    assert struct.unpack('<%dI' % len(words), retail) == tuple(words), name
    lines = []
    left = 0
    for i in range(0, len(words), 4):
        n, p, u, o = words[i:i+4]
        if n == 0 and p == 0 and u == 0 and o == 0:
            lines.append('    { 0, 0, 0, 0 },'); continue
        pr = rows.get('0x%08X' % (p - BASE), [])
        assert len(pr) == 1, (name, hex(p), pr)
        sym = pr[0]; used.add(sym)
        if u == 0: us = '0'
        elif u in OWNED_LISTS: us = OWNED_LISTS[u]
        elif u < BASE: us = '(const void *)%d' % u
        else: us = '(const void *)0x%08X' % u; left += 1
        lines.append('    { "%s", (FieldParseProc)&__identifier("%s"), %s, 0x%X },' % (cstr(n), sym, us, o))
    count = len(words) // 4
    new = m.group(1) + 'extern const FieldParse %s[%d] = {\n%s\n};' % (name, count, '\n'.join(lines))
    out = out[:m.start()] + new + out[m.end():]
    report.append((name, hex(va), count * 16, left))
# add missing parser declarations to the extern "C" block
decl_end = out.index('}\n\nextern const char *TheLocomotorSetNames[];')
existing = set(re.findall(r'void __identifier\("([^"]+)"\)\(\);', out[:decl_end]))
add = sorted(used - existing)
out = out[:decl_end] + ''.join('void __identifier("%s")();\n' % s for s in add) + out[decl_end:]
open(SRC, 'w', encoding='utf-8', newline='').write(out)
for r in reversed(report): print('table %s VA %s size %d unnamed-userData-literals %d' % r)
print('added decls:', add)
