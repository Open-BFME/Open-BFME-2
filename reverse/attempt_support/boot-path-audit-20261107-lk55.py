"""Boot-path walker (LINK-627, seat halilkkaya-lk55, 2026-11-07).

Walks retail's call graph from WinMain and from each call GameEngine::init makes
(0x0022E2E4, in instruction order; its `call [reg+disp]` sites are read as
Win32GameEngine's factory slots), at most --max-tier virtual hops deep: a
constructor's vptr store adds that table's slots one tier further. Direct
edges are E8 calls, outward E9 jumps, code immediates and code words inside
data-ledger rows the code references (INI and FieldParse tables). Every vptr
store found (`mov dword [m], imm32` where imm32 starts a run of .text words in
.rdata) is paired with OUR object's relocation at the same offset; a ??_7
name gets the given real link's bridge verdict (entries, correct, refusals)
and image-report row. This is reachability in boot order, not a trace.

  python3 reverse/attempt_support/boot-path-audit-20261107-lk55.py --rl DIR [--max-tier 2] [--out OUT.tsv]

Needs ./build.sh objects; reads retail, functions.csv and data_ledger.csv.
"""
import sys, csv, struct, bisect, json, re, collections, argparse
sys.path.insert(0, 'tools')
import callers_of as c
import build
from capstone import Cs, CS_ARCH_X86, CS_MODE_32
from capstone import x86_const as X

ap = argparse.ArgumentParser()
ap.add_argument('--max-tier', type=int, default=2)
ap.add_argument('--out', default=None)
ap.add_argument('--rl', required=True, help='a real-link artifact directory (vtable_bridge.json, image_report.json)')
ap.add_argument('--anchors', default='engine')
ap.add_argument('--no-ours', action='store_true')
args = ap.parse_args()

BASE = 0x400000
data, secs = c.load_image()
off = c.make_off(secs)
TEXT = (0x1000, 0x1000 + 0x7b8ce2)
RDATA = (0x7ba000, 0x7ba000 + 0x1e9783)
DATA = (0x9a4000, 0x9a4000 + 0x7f314)

def word(rva):
    o = off(rva)
    return struct.unpack_from('<I', data, o)[0] if o is not None else None

# ---- ledger rows
rows_all = build.load_function_rows()
by_start = {}
for r in rows_all:
    try:
        a = int(r['target_rva'], 16); s = int(r['target_size'])
    except Exception:
        continue
    if s <= 0:
        continue
    notes = r.get('notes', '')
    if 'gen-funclet' in notes or r['name'].startswith('uw_'):
        continue
    cur = by_start.get(a)
    if cur is None or (s > int(cur['target_size'])):
        by_start[a] = r
starts = sorted(by_start)
def containing(rva):
    i = bisect.bisect_right(starts, rva) - 1
    for j in range(i, max(i - 4, -1), -1):
        a = starts[j]
        if a <= rva < a + int(by_start[a]['target_size']):
            return a
    return None

name_to_start = {}
for a, r in by_start.items():
    name_to_start.setdefault(r['name'], a)

# ---- data ledger (for function-pointer tables)
dl = {}
with open('reverse/data_ledger.csv', newline='', encoding='utf-8') as f:
    for r in csv.DictReader(f):
        try:
            a = int(r['address'], 16); s = int(r['size'] or 0)
        except Exception:
            continue
        if a >= BASE:
            a -= BASE
        dl[a] = (s, r['kind'], r['name'])

def table_run(t):
    """slots of a vtable-looking run at rva t."""
    out = []
    a = t
    while True:
        w = word(a)
        if w is None or not (TEXT[0] <= w - BASE < TEXT[1]):
            break
        out.append(w - BASE)
        a += 4
        if a != t and a in dl and dl[a][1] not in ('', None) and len(out) > 0 and dl[a][2].startswith('??_R4'):
            break
    return out

md = Cs(CS_ARCH_X86, CS_MODE_32)
md.detail = True
_dis_cache = {}
def analyze(fa):
    if fa in _dis_cache:
        return _dis_cache[fa]
    r = by_start[fa]
    size = int(r['target_size'])
    o = off(fa)
    code = data[o:o + size]
    direct = []      # (kind, target)
    stores = []      # (insn_off, imm_off, table_rva, memop)
    for ins in md.disasm(code, fa):
        if ins.id == X.X86_INS_CALL and ins.bytes[0] == 0xE8:
            direct.append(('call', ins.operands[0].imm))
            continue
        if ins.id == X.X86_INS_CALL and ins.bytes[0] == 0xFF and ins.operands[0].type == X.X86_OP_MEM                 and ins.operands[0].mem.base != 0 and ins.operands[0].mem.index == 0:
            direct.append(('vcall', ins.operands[0].mem.disp))
            continue
        if ins.id == X.X86_INS_JMP and ins.bytes[0] == 0xE9:
            t = ins.operands[0].imm
            if not (fa <= t < fa + size):
                direct.append(('jmp', t))
            continue
        ops = ins.operands
        for k, op in enumerate(ops):
            if op.type == X.X86_OP_IMM:
                v = (op.imm & 0xFFFFFFFF) - BASE
                if TEXT[0] <= v < TEXT[1] and ins.id in (X.X86_INS_PUSH, X.X86_INS_MOV):
                    direct.append(('fnptr', v))
                elif RDATA[0] <= v < DATA[1]:
                    if (ins.id == X.X86_INS_MOV and k == 1 and ops[0].type == X.X86_OP_MEM
                            and ops[0].size == 4):
                        run = table_run(v)
                        if run:
                            m = ops[0].mem
                            memop = (ins.reg_name(m.base) if m.base else '', m.disp)
                            stores.append((ins.address - fa, ins.address - fa + ins.size - 4, v, memop))
                            continue
                    direct.append(('data', v))
            elif op.type == X.X86_OP_MEM and op.mem.base == 0 and op.mem.index == 0:
                v = (op.mem.disp & 0xFFFFFFFF) - BASE
                if RDATA[0] <= v < DATA[1]:
                    direct.append(('data', v))
    _dis_cache[fa] = (direct, stores)
    return direct, stores

def data_fnptrs(v):
    ent = dl.get(v)
    if not ent:
        return []
    s = ent[0]
    if s <= 0 or s > 0x8000:
        return []
    out = []
    for a in range(v, v + s - 3, 4):
        w = word(a)
        if w is not None and TEXT[0] <= w - BASE < TEXT[1] and (w - BASE) in by_start:
            out.append(w - BASE)
    return out

# ---- walk
visited = {}
store_log = []    # (order, anchor, tier, func, insn_off, imm_off, table, memop)
order = [0]

def walk(anchor_idx, anchor_name, roots, max_tier):
    tier_queue = [list(roots)]
    tier = 0
    while tier <= max_tier and tier < len(tier_queue):
        nxt = []
        for root in tier_queue[tier]:
            stack = [root]
            while stack:
                fa = stack.pop()
                if fa not in by_start:
                    ca = containing(fa)
                    if ca is None:
                        continue
                    fa = ca
                if fa in visited:
                    continue
                visited[fa] = (anchor_idx, tier, order[0])
                order[0] += 1
                direct, stores = analyze(fa)
                children = []
                for kind, t in direct:
                    if kind == 'vcall':
                        continue
                    if kind == 'data':
                        children.extend(data_fnptrs(t))
                    else:
                        children.append(t)
                for (io, imo, t, memop) in stores:
                    store_log.append((order[0], anchor_idx, anchor_name, tier, fa, io, imo, t, memop))
                    nxt.extend(table_run(t))
                stack.extend(reversed(children))
        if tier + 1 < len(tier_queue):
            tier_queue[tier + 1].extend(nxt)
        else:
            tier_queue.append(nxt)
        tier += 1

def S(name):
    a = name_to_start.get(name)
    if a is None:
        raise SystemExit('no row ' + name)
    return a

anchors = []
anchors.append(('WinMain', [S('_WinMain@16')]))
ge = S('?init@GameEngine@@UAEXHQAPAD@Z')
# GameEngine::init top-level calls in order become anchors
direct, stores = analyze(ge)
anchors.append(('GameEngine::init(own)', []))
seq = []
W32 = table_run(0x00BC2530 - BASE)
for kind, t in direct:
    if kind in ('call', 'jmp', 'fnptr'):
        seq.append(t)
    elif kind == 'vcall' and t % 4 == 0 and 0 <= t // 4 < 40:
        seq.append(W32[t // 4])
for i, t in enumerate(seq):
    ca = t if t in by_start else containing(t)
    nm = by_start[ca]['name'] if ca is not None else hex(t)
    anchors.append(('GEinit#%d %s' % (i, nm[:60]), [t]))

# GameEngine::init itself: record its own stores first
visited[ge] = (1, 0, order[0]); order[0] += 1
for (io, imo, t, memop) in stores:
    store_log.append((order[0], 1, 'GameEngine::init(own)', 0, ge, io, imo, t, memop))
for i, (nm, roots) in enumerate(anchors):
    walk(i, nm, roots, 0 if i == 0 else args.max_tier)
# WinMain's virtual reach last
_vis_w = [fa for fa, v in visited.items() if v[0] == 0]
for fa in _vis_w:
    del visited[fa]
walk(len(anchors), 'WinMain(virtual)', [S('_WinMain@16')], args.max_tier)
# finally GameEngine::init's own tables' slots
print('visited', len(visited), 'stores', len(store_log), file=sys.stderr)

# ---- our side
bridge = json.load(open(args.rl + '/vtable_bridge.json'))
status = {}
for e in bridge['entries']:
    for n in e.get('names', [e['name']]):
        status.setdefault(n, 'bridged(%d)' % len(e.get('slots', [])))
for e in bridge['correct']:
    for n in e.get('names', [e['name']]):
        status.setdefault(n, 'correct')
for e in bridge['refusals']:
    for n in e.get('names', [e['name']]):
        status.setdefault(n, 'refused:' + str(e.get('reason', e.get('state', '?'))))
ir = json.load(open(args.rl + '/image_report.json'))
irrows = {}
for row in ir['vtables']['rows']:
    irrows.setdefault(row[1], row)

ZERO = set()
for _r in csv.reader(open('reverse/attempt_support/zero-vtable-placeholders-20261107-lk49.tsv', encoding='utf-8'), delimiter='	'):
    if len(_r) > 1:
        ZERO.add(_r[1])
objpaths = build.RowObjectPaths(build.require_row_object)
def our_reloc(fa, imo):
    r = by_start[fa]
    try:
        obj = objpaths.get(r)
        body, relocs = build.read_object_symbol_bytes(obj, build.ledger_object_symbol(r), int(r['target_size']))
    except SystemExit as e:
        return 'NOOBJ'
    except Exception as e:
        return 'ERR:' + type(e).__name__
    for o, t, sym in relocs:
        if o == imo:
            return sym
    return 'NORELOC:' + body[imo:imo + 4].hex()

out = open(args.out, 'w', encoding='utf-8') if args.out else sys.stdout
print('order\tanchor\ttier\tfunc_rva\tfunc\tsource\tinsn_off\tmemop\tretail_table\tretail_len\tour_symbol\tclass\tbridge\timage_report', file=out)
for (od, ai, an, tier, fa, io, imo, t, memop) in store_log:
    r = by_start[fa]
    sym = '' if args.no_ours else our_reloc(fa, imo)
    if sym.startswith('??_7'):
        cls = 'vtable'
    elif sym in ZERO:
        cls = 'ZERO'
    elif sym.startswith(('NOOBJ', 'ERR', 'NORELOC')):
        cls = 'unknown'
    else:
        cls = 'PLACEHOLDER'
    st = status.get(sym, '')
    irr = irrows.get(sym)
    irs = '%s %s/%s' % (irr[2], irr[4], irr[3]) if irr else ''
    print('%d\t%s\t%d\t0x%08X\t%s\t%s\t0x%X\t%s%+d\t0x%08X\t%d\t%s\t%s\t%s\t%s' % (
        od, an, tier, fa, r['name'][:90], r['source'], io, memop[0], memop[1], t + BASE,
        len(table_run(t)), sym, cls, st, irs), file=out)
