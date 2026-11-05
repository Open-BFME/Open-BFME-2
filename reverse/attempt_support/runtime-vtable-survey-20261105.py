"""Runtime vtable survey: for every ??_7 the link would keep (first definer in
census link order over the CURRENT tree's objects), compare each slot with the
retail vftable at the table's code-proven address.

Retail address of a ??_7, in order of evidence:
  code  name_globals.load_index(): matched rows' DIR32 sites (ctor/dtor vptr
        stores) that byte-match retail; the retail word there is the table.
  ledger reverse/data_ledger.csv kind=vtable row whose name/names lists it.
Retail extent: the smallest of the data_ledger size at that address,
vftable_map's installed run, and the .text-pointer run up to the next table
start (any address a retail `mov dword ptr [m], imm32` stores, any ledger
vtable row, any code-proven table).

Per slot (RetailTruth's own relocation resolution, as the census judges a COMDAT):
  eq       our slot's name resolves to retail's word (stubs followed)
  purecall ours is __purecall, retail's is another body
  equiv    resolves elsewhere, but both reach the same body through E9 tail jumps
  wrong    resolves elsewhere
  unknown  our name has no ledger address (cannot judge)
usage (from the repository root, after ./build.sh and link_check.py --fetch-index):
  python3 reverse/attempt_support/runtime-vtable-survey-20261105.py OUT.tsv [--jobs N] [--full ALL.tsv]
"""
import bisect
import collections
import concurrent.futures
import csv
import pickle
import re
import struct
import sys
import time

sys.path.insert(0, "tools")
import build  # noqa: E402
import link_census as lc  # noqa: E402

BASE = 0x400000
DIR32 = 0x0006
SNAP = re.compile(r"^\?(loadPostProcess|LoadPostProcess|xfer|Xfer|DoXfer|crc|CRC)@")


def vt_of(path):
    try:
        data = open(path, "rb").read()
    except OSError:
        return path, None
    out = []
    for symbol, body, relocs, digest, size in lc._comdat_sections(data):
        if symbol["name"].startswith("??_7"):
            out.append(symbol["name"])
    return path, out


CTX_ORDER = ["saveload", "boot", "menu", "skirmish", "other", "unnamed"]
BOOT = ("Code/GameEngine/Source/Common/", "Code/Main/", "Code/GameEngineDevice/Source/Win32Device/",
        "Code/GameEngineDevice/Source/W3DDevice/Common/", "Code/GameEngine/Source/GameClient/System/",
        "Code/Libraries/Source/WWVegas/", "Code/Libraries/Source/debug/", "Code/Libraries/Source/Compression/",
        "Code/Libraries/Source/STLport", "Code/Libraries/Source/profile/", "Code/GameEngine/Source/GameClient/Display",
        "Code/GameEngine/Source/GameClient/GameClient", "Code/GameEngine/Source/GameLogic/System/")
MENU = ("Code/GameEngine/Source/GameClient/GUI/", "Code/GameEngine/Source/GameClient/Shell",
        "Code/Libraries/Source/Apt/", "Code/GameEngineDevice/Source/W3DDevice/GameClient/GUI/",
        "Code/GameEngine/Source/GameClient/MapUtil")
SKIRMISH = ("Code/GameEngine/Source/GameLogic/", "Code/GameEngine/Source/GameClient/",
            "Code/GameEngineDevice/Source/W3DDevice/GameClient/")
OTHER = ("Code/GameEngine/Source/GameClient/LivingWorld", "Code/GameEngine/Source/GameNetwork",
         "Code/Libraries/Source/DirtySock", "Code/Libraries/Source/GameSpy", "Code/Tools")


CLASS_HOME = {}


def class_home(vtable, kept):
    """The subsystem path of the table's class: a Code/ source named after the
    class (Class.cpp, else ClassXxx.cpp), else the kept unit's own path."""
    cls = vtable[4:].split("@")[0]
    if re.match(r"(Rva|Gen|Base|B\d|Iface|Opaque|\?\$)", cls) or len(cls) < 4:
        return None
    return CLASS_HOME.get(cls) or kept


BOOT_CLASSES = {
    "Display", "W3DDisplay", "GameClient", "W3DGameClient", "GameLogic", "W3DGameLogic", "Mouse", "W3DMouse",
    "Keyboard", "DirectInputKeyboard", "GameWindowManager", "W3DGameWindowManager", "FontLibrary",
    "W3DFontLibrary", "AudioManager", "MilesAudioManager", "FileSystem", "LocalFileSystem", "ArchiveFileSystem",
    "Win32LocalFileSystem", "Win32BIGFileSystem", "Radar", "W3DRadar", "ParticleSystemManager",
    "W3DParticleSystemManager", "TerrainVisual", "W3DTerrainVisual", "GameEngine", "Win32GameEngine", "InGameUI",
    "MessageStream", "CommandList", "GameMessageList", "Shell", "ThingFactory", "ModuleFactory", "W3DModuleFactory",
    "FunctionLexicon", "W3DFunctionLexicon", "VideoPlayer", "BinkVideoPlayer", "GlobalData", "INI",
    "NameKeyGenerator", "GameTextManager", "GameText", "SubsystemInterface", "WW3D", "DX8Wrapper"}


def context(rec):
    cls = rec["vtable"][4:].split("@")[0]
    if rec["snapshot_slots_bad"] or re.search(r"^\?\?_7(Xfer|Snapshot|GameState|SaveGame)", rec["vtable"]):
        return "saveload"
    if cls in BOOT_CLASSES or "SubsystemInterface" in rec["vtable"]:
        return "boot"
    p = class_home(rec["vtable"], rec["kept_source"])
    if p is None:
        return "unnamed"
    if p.startswith(OTHER):
        return "other"
    if p.startswith(MENU):
        return "menu"
    if p.startswith(BOOT):
        return "boot"
    if p.startswith(SKIRMISH):
        return "skirmish"
    return "other"


def severity(rec):
    if rec["verdict"] in ("NO-RETAIL-ADDRESS",):
        return "unjudged"
    if int(rec["purecall"]) or int(rec["short_by"]):
        return "crash"
    if int(rec["wrong"]):
        return "misbehave"
    if int(rec["unknown"]):
        return "unproven"
    if int(rec["equiv"]) or int(rec["long_by"]):
        return "benign"
    return "ok"


def risk(rec):
    """T1 crash on the boot/menu/save-load path; T2 crash in a skirmish class;
    T3 misbehaviour on those paths; T4 crash/misbehave elsewhere; T5 unproven or
    benign; T6 not referenced by kept code (/OPT:REF drops it) or unjudged; T7 ok."""
    sev, ctx = rec["severity"], rec["context"]
    if rec["referenced"] == "no" or sev == "unjudged":
        return "T6"
    if sev == "crash":
        return "T1" if ctx in ("saveload", "boot", "menu") else "T2" if ctx == "skirmish" else "T4"
    if sev == "misbehave":
        return "T3" if ctx not in ("other", "unnamed") else "T4"
    if sev in ("unproven", "benign"):
        return "T5"
    return "T7"


def main():
    out_path = sys.argv[1]
    jobs = int(sys.argv[sys.argv.index("--jobs") + 1]) if "--jobs" in sys.argv else 10
    t0 = time.time()
    rows = lc.ledger()
    present, missing = lc.objects(rows)
    sources = {o.name: s for o, s in lc._object_sources(rows).items()}
    print(f"objects present={len(present)} missing={len(missing)}", flush=True)

    # 1. who defines which ??_7, in link order
    definers = collections.defaultdict(list)
    with concurrent.futures.ProcessPoolExecutor(jobs) as pool:
        res = dict(pool.map(vt_of, [str(o) for o in present], chunksize=64))
    for pos, o in enumerate(present):
        for n in res.get(str(o)) or ():
            definers[n].append(pos)
    print(f"vtable names defined: {len(definers)} ({time.time()-t0:.0f}s)", flush=True)

    # 2. retail addresses
    import name_globals
    code_addr = collections.defaultdict(set)
    for va, syms in name_globals.load_index().items():
        for s in syms:
            if s.startswith("??_7"):
                code_addr[s].add(va - BASE)
    ledger_addr, ledger_size = collections.defaultdict(set), {}
    with open("reverse/data_ledger.csv", newline="", encoding="utf-8") as h:
        for r in csv.DictReader(h):
            if r["kind"] != "vtable":
                continue
            a = int(r["address"], 16)
            ledger_size[a] = int(r["size"] or 0)
            for n in {r["name"]} | set(filter(None, (r.get("names") or "").split(";"))):
                if n.startswith("??_7"):
                    ledger_addr[n].add(a)
    import vftable_map
    image, secs, by = vftable_map.sections()
    read = vftable_map.reader(image, secs)
    installed, _ = vftable_map.scan(image, secs, by)
    text = by[".text"]
    t_lo, t_hi = text["rva"], text["rva"] + text["size"]
    starts = sorted(set(installed) | set(ledger_size))

    # every vptr store in retail code (`mov dword ptr [modrm], imm32`, any addressing form, C7 /0)
    # names a table's first word, so the stored addresses bound each table
    rdata = by[".rdata"]
    r_lo, r_hi = rdata["rva"], rdata["rva"] + rdata["size"]
    code = read(t_lo, text["size"])
    code_refs = set()
    for m in re.finditer(re.escape(bytes([0xC7])), code):
        i = m.start()
        if i + 2 >= len(code):
            continue
        modrm = code[i + 1]
        mod, reg, rm = modrm >> 6, (modrm >> 3) & 7, modrm & 7
        if reg != 0 or mod == 3:
            continue
        n = 2 + (1 if rm == 4 else 0)
        n += 4 if (mod == 0 and rm == 5) or mod == 2 else 1 if mod == 1 else 0
        if mod == 0 and rm == 4 and (code[i + 2] & 7) == 5:
            n += 4
        if i + n + 4 > len(code):
            continue
        tgt = struct.unpack_from("<I", code, i + n)[0] - BASE
        if r_lo <= tgt < r_hi:
            w = read(tgt, 4)
            if w and t_lo <= struct.unpack("<I", w)[0] - BASE < t_hi:
                code_refs.add(tgt)
    print(f"code-referenced .rdata addresses: {len(code_refs)}", flush=True)
    starts = sorted(set(starts) | {a for v in code_addr.values() for a in v} | code_refs)

    def extent(a):
        """Smallest of: ledger size, installed run, .text-pointer run up to the next known table."""
        k = bisect.bisect_right(starts, a)
        limit = (starts[k] - a) // 4 if k < len(starts) else 512
        n = 0
        while n < min(limit, 512):
            w = read(a + 4 * n, 4)
            if w is None or not t_lo <= struct.unpack("<I", w)[0] - BASE < t_hi:
                break
            n += 1
        cands = [(n, "run")]
        if ledger_size.get(a):
            cands.append((ledger_size[a] // 4, "ledger"))
        if a in installed:
            cands.append((len(installed[a]), "installed"))
        return min(cands)

    names_at = collections.defaultdict(list)
    size_at = {}
    for r in rows:
        names_at[int(r["target_rva"], 16)].append(r["name"])
        try:
            size_at.setdefault(int(r["target_rva"], 16), int(r["target_size"] or 0))
        except ValueError:
            pass

    def jump_chain(a):
        seen = [a]
        for _ in range(6):
            op = read(a, 5)
            if op is None or op[0] != 0xE9:
                break
            a = (a + 5 + struct.unpack_from("<i", op, 1)[0]) & 0xFFFFFFFF
            seen.append(a)
        return seen

    truth = lc.RetailTruth(rows)
    purecall = truth.addresses("__purecall", DIR32) or set()
    ix = pickle.load(open("build/link_census/link_index.pkl", "rb"))
    referenced = (ix.get("references") or {}).get("referenced")
    print(f"truth ready ({time.time()-t0:.0f}s)", flush=True)

    def score(symbol, relocs, size, weak, addr, rext):
        """(eq slots, slots ours lacks or gets wrong) of one copy against retail."""
        nslots = (size - symbol["value"]) // 4
        refs = {(w - symbol["value"]) // 4: r for w, k, r in relocs if k == DIR32}
        eq = 0
        for i in range(min(nslots, rext)):
            ref = refs.get(i)
            w = read(addr + 4 * i, 4)
            if ref is None or w is None:
                continue
            target = struct.unpack("<I", w)[0] - BASE
            exp = truth.addresses(ref["name"], DIR32) or (truth.addresses(weak[ref["name"]], DIR32) if ref["name"] in weak else None)
            if exp and truth._lands(target, exp):
                eq += 1
        return eq, rext - eq

    # 3. judge kept copies
    need = collections.defaultdict(list)
    for n, poss in definers.items():
        need[poss[0]].append(n)
    out = []
    for pos, names in sorted(need.items()):
        obj = present[pos]
        data = obj.read_bytes()
        secs_by = {s["name"]: (s, b, rl, d, sz) for s, b, rl, d, sz in lc._comdat_sections(data)
                   if s["name"] in names}
        weak = dict(lc._weak_externals(data))
        for n in names:
            symbol, body, relocs, digest, size = secs_by[n]
            nslots = (size - symbol["value"]) // 4
            ours = {}
            for where, kind, ref in relocs:
                if kind == DIR32 and where % 4 == symbol["value"] % 4:
                    ours[(where - symbol["value"]) // 4] = ref
            if n in code_addr and len(code_addr[n]) == 1:
                addr, evid = next(iter(code_addr[n])), "code"
            elif n in code_addr:
                addr, evid = None, "code-ambiguous:" + ";".join(f"0x{a+BASE:08X}" for a in sorted(code_addr[n]))
            elif len(ledger_addr.get(n, ())) == 1:
                addr, evid = next(iter(ledger_addr[n])), "ledger"
            elif n in ledger_addr:
                addr, evid = None, "ledger-ambiguous"
            else:
                addr, evid = None, "none"
            other = [present[p].name for p in definers[n][1:]]
            rec = {"vtable": n, "kept_source": str(sources.get(obj.name, obj.name)).replace(str(build.ROOT) + "\\", "").replace("\\", "/"),
                   "copies": len(definers[n]), "referenced": ("" if referenced is None else ("yes" if n in referenced else "no")),
                   "evidence": evid, "retail_va": "", "ours_slots": nslots, "retail_slots": "", "extent_from": "",
                   "eq": 0, "purecall": 0, "equiv": 0, "wrong": 0, "unknown": 0, "short_by": 0, "long_by": 0, "bad_rowed": 0,
                   "verdict": "", "snapshot_slots_bad": "", "better_copy": "", "detail": ""}
            if addr is None:
                rec["verdict"] = "NO-RETAIL-ADDRESS"
                out.append(rec)
                continue
            rext, src = extent(addr)
            rec.update(retail_va=f"0x{addr+BASE:08X}", retail_slots=rext, extent_from=src)
            details, snapbad = [], []
            for i in range(nslots):
                w = read(addr + 4 * i, 4)
                if i >= rext or w is None:
                    break
                target = struct.unpack("<I", w)[0] - BASE
                ref = ours.get(i)
                rnames = names_at.get(target) or []
                chain_r = jump_chain(target)
                rname = rnames[0] if rnames else next((names_at[c][0] for c in chain_r if names_at.get(c)), "?")
                if ref is None:
                    kind = "unknown"
                    oname = "<no reloc>"
                else:
                    oname = ref["name"]
                    expected = truth.addresses(oname, DIR32)
                    if not expected and oname in weak:
                        expected = truth.addresses(weak[oname], DIR32)
                    if expected and truth._lands(target, expected):
                        kind = "eq"
                    elif not expected and ref.get("definition") is not None and truth._defined_at(ref["definition"], target):
                        kind = "eq"
                    elif oname == "__purecall":
                        kind = "purecall"
                    elif expected and all(e in truth.shared for e in expected):
                        kind = "unknown"  # an over-claimed address proves nothing (RetailTruth's rule)
                    elif expected:
                        end_r = chain_r[-1]
                        end_o = {jump_chain(e)[-1] for e in expected}
                        kind = "equiv" if end_r in end_o else "wrong"
                        if kind == "wrong":
                            # an unfolded byte twin: same bytes, no rel32 branch (position-independent)
                            br = read(end_r, size_at.get(end_r, 0)) if size_at.get(end_r) else None
                            for e in end_o:
                                bo = read(e, size_at.get(e, 0)) if size_at.get(e) else None
                                if br and bo == br and len(br) <= 48 and not any(x in br for x in (0xE8, 0xE9)):
                                    kind = "equiv"
                    else:
                        kind = "unknown"
                rec[kind] += 1
                if kind != "eq":
                    details.append(f"{i}:{kind}:{oname[:48]}->0x{target:08X}={rname[:48]}")
                    if i <= 4 and (SNAP.search(rname) or SNAP.search(oname)):
                        snapbad.append(str(i))
                    if kind in ("purecall", "wrong", "unknown") and rnames:
                        rec["bad_rowed"] += 1
            if nslots < rext:
                rec["short_by"] = rext - nslots
            elif nslots > rext:
                rec["long_by"] = nslots - rext
            rec["snapshot_slots_bad"] = ",".join(snapbad)
            v = []
            if rec["purecall"]:
                v.append("PURECALL")
            if rec["wrong"]:
                v.append("WRONG")
            if rec["short_by"]:
                v.append("SHORT")
            if rec["long_by"]:
                v.append("LONG")
            if rec["equiv"]:
                v.append("EQUIV")
            if rec["unknown"]:
                v.append("UNKNOWN")
            rec["verdict"] = "+".join(v) or "OK"
            if len(definers[n]) > 1:
                best = None
                for p2 in definers[n][1:]:
                    o2 = present[p2]
                    d2 = o2.read_bytes()
                    for s2, b2, rl2, dg2, sz2 in lc._comdat_sections(d2):
                        if s2["name"] == n:
                            sc = score(s2, rl2, sz2, dict(lc._weak_externals(d2)), addr, rext)
                            if best is None or sc[0] > best[0][0]:
                                best = (sc, o2)
                if best and best[0][0] > rec["eq"]:
                    src2 = str(sources.get(best[1].name, best[1].name)).replace(str(build.ROOT) + "\\", "").replace("\\", "/")
                    rec["better_copy"] = f"{src2} eq={best[0][0]}/{rext}"
            rec["detail"] = " | ".join(details[:3]) + (f" | +{len(details)-3} more" if len(details) > 3 else "")
            out.append(rec)
    stems = collections.defaultdict(list)
    for r in rows:
        src = r["source"]
        if src.startswith("Code/") and src.endswith(".cpp"):
            stems[src.rsplit("/", 1)[-1][:-4]].append(src)
    for stem in sorted(stems):
        CLASS_HOME.setdefault(stem, stems[stem][0])
    for rec in out:
        cls = rec["vtable"][4:].split("@")[0]
        if cls not in CLASS_HOME:
            hit = next((stems[st][0] for st in sorted(stems) if st.startswith(cls)), None)
            if hit:
                CLASS_HOME[cls] = hit
        rec["context"] = context(rec)
        rec["severity"] = severity(rec)
        rec["risk"] = risk(rec)
    out.sort(key=lambda r: (r["risk"], CTX_ORDER.index(r["context"]), -(int(r["purecall"]) + int(r["short_by"])),
                            -int(r["wrong"]), r["vtable"]))
    for i, rec in enumerate(out, 1):
        rec["rank"] = i
    lead = ["rank", "risk", "severity", "context"]
    out = [{k: r[k] for k in lead + [k for k in r if k not in lead]} for r in out]
    if "--full" in sys.argv:
        with open(sys.argv[sys.argv.index("--full") + 1], "w", newline="", encoding="utf-8") as h:
            w = csv.DictWriter(h, fieldnames=list(out[0]), delimiter="\t", lineterminator="\n")
            w.writeheader()
            w.writerows(out)
    # the committed form: every table at risk T1-T5, per-slot detail for T1-T3
    cols = ["rank", "risk", "severity", "context", "vtable", "kept_source", "copies", "retail_va", "ours_slots",
            "retail_slots", "eq", "purecall", "wrong", "equiv", "unknown", "short_by", "long_by",
            "snapshot_slots_bad", "better_copy", "detail"]
    with open(out_path, "w", newline="", encoding="utf-8") as h:
        w = csv.writer(h, delimiter="\t", lineterminator="\n")
        w.writerow(cols)
        for r in out:
            if r["risk"] in ("T1", "T2", "T3", "T4", "T5"):
                w.writerow([("" if c == "detail" and r["risk"] not in ("T1", "T2", "T3") else r[c]) for c in cols])
    print("risk", dict(sorted(collections.Counter(r["risk"] for r in out).items())))
    print("severity", dict(collections.Counter(r["severity"] for r in out).most_common()))
    print("context x risk", dict(sorted(collections.Counter((r["risk"], r["context"]) for r in out).items())))
    live = [r for r in out if r["referenced"] != "no"]
    print("slots in referenced tables: purecall", sum(int(r["purecall"]) for r in live),
          "wrong", sum(int(r["wrong"]) for r in live), "missing (short)", sum(int(r["short_by"]) for r in live),
          "eq", sum(int(r["eq"]) for r in live))
    c = collections.Counter(r["verdict"].split("+")[0] if r["verdict"] else "" for r in out)
    print("tables", len(out), dict(c), f"({time.time()-t0:.0f}s)")


if __name__ == "__main__":
    main()
