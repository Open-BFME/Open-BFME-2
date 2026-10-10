"""data_check --converged: the enforced refusal of a second name at an address
reverse/data_converged.csv lists (each first brought down to one spelling).

The cases below are GPT-6.1-Sol's review reproductions (round 1), each with a
control: compiler-looking spellings, an array whose operand reaches a slot from
outside it, objects not proven current, a missing or malformed list, a list
that shrank, header dependents, and .asm rows."""
import json
import os
import struct
import subprocess
import sys
from pathlib import Path

import pytest

HERE = Path(__file__).resolve().parent
sys.path.insert(0, str(HERE.parent))
sys.path.insert(0, str(HERE))
import data_check as dc  # noqa: E402
import data_ledger as dl  # noqa: E402

GL = "?TheGameLogic@@3PAVGameLogic@@A"
SLOT = 0x009FE78C                                    # TheGameLogic's retail RVA
VA = SLOT + dl.IMAGE_BASE
CONVERGED = {SLOT: GL}


# ---------------------------------------------------------------- real COFF objects

def write_coff(path, code, relocs, symbols):
    """One i386 COFF object: a .text section holding `code` with DIR32 `relocs`
    [(offset, symbol index)], `symbols` [(name, value, section, storage, type)]."""
    head = 20 + 40
    body = bytearray(code)
    rel_ptr = head + len(body)
    for offset, index in relocs:
        body += struct.pack("<IIH", offset, index, dl.DIR32)
    sections = b".text\0\0\0" + struct.pack("<IIIIIIHHI", 0, 0, len(code), head, rel_ptr, 0,
                                             len(relocs), 0, 0x60000020)
    strings, table = bytearray(4), bytearray()
    for name, value, section, storage, typ in symbols:
        raw = name.encode("latin-1")
        field = raw.ljust(8, b"\0") if len(raw) <= 8 else struct.pack("<II", 0, len(strings))
        if len(raw) > 8:
            strings += raw + b"\0"
        table += field + struct.pack("<IhHBB", value, section, typ, storage, 0)
    struct.pack_into("<I", strings, 0, len(strings))
    path.write_bytes(struct.pack("<HHIIIHH", 0x14C, 1, 0, head + len(body), len(symbols), 0, 0)
                     + sections + bytes(body) + bytes(table) + bytes(strings))


def row(source="Code/A.cpp", name="?f@@YAXXZ"):
    return {"name": name, "target_rva": "0x00001000", "target_size": "6", "source": source,
            "status": "matched", "notes": ""}


def facts_for(tmp_path, monkeypatch, symbol, addend, retail_va, current=True, receipt="match"):
    """converged_facts over one row `mov eax,[symbol+addend]; ret` whose retail
    operand is `retail_va`, read through the real COFF reader. `receipt` is the
    object hash its build receipt (.deps.json) records: "match", "other" (the
    object was swapped after the build) or None (a receipt predating the field)."""
    obj = tmp_path / "a.obj"
    write_coff(obj, b"\xa1" + struct.pack("<i", addend) + b"\xc3", [(1, 1)],
               [("?f@@YAXXZ", 0, 1, dl.EXTERNAL, 0x20), (symbol, 0, 0, dl.EXTERNAL, 0)])
    meta = {} if receipt is None else {"object": dc.build._hash_file(str(obj)) if receipt == "match" else "0" * 32}
    dc.build._deps_sidecar(obj).write_text(json.dumps(meta))
    monkeypatch.setattr(dc.build, "row_object", lambda r: obj)
    monkeypatch.setattr(dc.build, "compile_is_current", lambda source, output: current)
    monkeypatch.setattr(dc.build, "read_target_bytes",
                        lambda rva, size: b"\xa1" + struct.pack("<I", retail_va) + b"\xc3")
    monkeypatch.setattr(dc.build, "ledger_object_symbol", lambda r: r["name"])
    unread = []
    return dc.converged_facts([row()], unread), unread


@pytest.mark.parametrize("symbol, addend, retail_va, refused", [
    (GL, 0, VA, False),                                   # control: the one name
    (GL, 4, VA + 4, False),                               # control: the one name, a member at +4
    ("?g_00DFE78C@@3PAXA", 0, VA, True),                  # an address-named spelling
    ("?TheGameLogic@@3PAVGameLogicFrame@@A", 0, VA, True),  # a type-variant spelling
    ("$seat", 0, VA, True),                               # review: $-names were skipped
    ("__TIseat", 0, VA, True),                            # review: RTTI-looking names were exempt
    ("??_C@_00CNPNBAHC@?$AA@", 0, VA, True),              # nothing is exempt at a converged slot
    ("?g_arr@@3PAHA", 4, VA, True),                       # review: array+4 onto the slot from outside
    ("?g_other@@3PAHA", 0, VA + 0x10, False),             # control: another address
])
def test_real_objects_are_judged_by_name_and_reach(tmp_path, monkeypatch, symbol, addend, retail_va, refused):
    facts, unread = facts_for(tmp_path, monkeypatch, symbol, addend, retail_va)
    assert unread == [] and len(facts) == 1
    found = dc.converged_findings(facts, CONVERGED)
    assert bool(found) == refused, (facts, found)


def test_an_object_not_proven_current_is_not_judged(tmp_path, monkeypatch):
    facts, unread = facts_for(tmp_path, monkeypatch, GL, 0, VA, current=False)
    assert facts == [] and unread == [("Code/A.cpp", "?f@@YAXXZ", "object not current for its source")]
    monkeypatch.setattr(dc, "converged_rows", lambda sources: [row()])
    assert dc.check_converged(["Code/A.cpp"], CONVERGED) == 1          # no object, no verdict
    facts, unread = facts_for(tmp_path, monkeypatch, GL, 0, VA)         # control
    monkeypatch.setattr(dc, "converged_rows", lambda sources: [row()])
    assert dc.check_converged(["Code/A.cpp"], CONVERGED) == 0


def test_an_object_swapped_after_its_build_is_not_judged(tmp_path, monkeypatch):
    """Review round 2: replacing an alias object with a stale canonical one left
    it 'current'. The build receipt records the object's hash; it must match."""
    facts, unread = facts_for(tmp_path, monkeypatch, GL, 0, VA, receipt="other")
    assert facts == [] and unread == [("Code/A.cpp", "?f@@YAXXZ",
                                       "object is not the one its build receipt recorded")]
    facts, unread = facts_for(tmp_path, monkeypatch, "?g_00DFE78C@@3PAXA", 0, VA, receipt=None)
    assert unread == [] and dc.converged_findings(facts, CONVERGED)  # a receipt without the field: judged


def multi_row_audit(tmp_path, monkeypatch):
    """Two real COFF bodies sharing a real ordinary dependency receipt."""
    monkeypatch.setattr(dc, "ROOT", tmp_path)
    monkeypatch.setattr(dc.build, "ROOT", tmp_path)
    (tmp_path / "Code").mkdir()
    source = tmp_path / "Code" / "A.cpp"
    source.write_text("// cl: -O1\n")
    header = tmp_path / "Code" / "header.h"
    header.write_text("// dependency\n")
    obj = tmp_path / "a.obj"
    names = ["?f0@@YAXXZ", "?f1@@YAXXZ"]
    write_coff(obj, b"\xa1\0\0\0\0\xc3" * 2, [(1, 2), (7, 3)],
               [(names[0], 0, 1, dl.EXTERNAL, 0x20),
                (names[1], 6, 1, dl.EXTERNAL, 0x20),
                (GL, 0, 0, dl.EXTERNAL, 0),
                ("?alias@@3PAXA", 0, 0, dl.EXTERNAL, 0)])
    command = ["cl", "-O1"]
    env = {"INCLUDE": "headers"}
    monkeypatch.setattr(dc.build, "compiler_command", lambda source, output: (command[:], env.copy()))
    meta = {"cmd": dc.build._cmd_fingerprint(command, env),
            "source": dc.build._hash_file(str(source)),
            "deps": {"Code/header.h": dc.build._hash_file(str(header))},
            "object": dc.build._hash_file(str(obj))}
    dc.build._deps_sidecar(obj).write_text(json.dumps(meta))
    monkeypatch.setattr(dc.build, "row_object", lambda r: obj)
    monkeypatch.setattr(dc.build, "read_target_bytes",
                        lambda rva, size: b"\xa1" + struct.pack("<I", VA) + b"\xc3")
    monkeypatch.setattr(dc.build, "ledger_object_symbol", lambda r: r["name"])
    monkeypatch.setattr(dc.dl, "retail_sections", lambda: [(".text", 0x1000, 0, 0x100)])
    rows = [row(name=name) for name in names]
    rows[1]["target_rva"] = "0x00001010"
    return rows, source, header, obj, meta, command, env


def test_currency_is_shared_only_within_one_audit_and_every_body_is_read(tmp_path, monkeypatch):
    rows, _source, _header, _obj, _meta, _command, _env = multi_row_audit(tmp_path, monkeypatch)
    current = dc.build.compile_is_current
    calls = []
    monkeypatch.setattr(dc.build, "compile_is_current",
                        lambda source, output: calls.append((source, output)) or current(source, output))
    unread = []
    facts = dc.converged_facts(rows, unread)
    assert unread == [] and len(calls) == 2 and len(facts) == 2
    assert dc.converged_findings(facts, CONVERGED) == [
        ("Code/A.cpp", "wrong-name", "?alias@@3PAXA", f"0x{SLOT:08X}")]
    dc.converged_facts(rows, [])
    assert len(calls) == 4                   # no trusted verdict survives the call


@pytest.mark.parametrize("changed", ["source", "object", "receipt", "header", "command", "environment",
                                     "regions", "overrides", "ledger", "tool", "retail"])
def test_late_input_changes_discard_all_earlier_facts(tmp_path, monkeypatch, changed):
    rows, source, header, obj, meta, command, env = multi_row_audit(tmp_path, monkeypatch)
    config_paths = {
        "regions": tmp_path / "reverse" / "retail_inventory" / "flag_regions.csv",
        "overrides": tmp_path / "reverse" / "flag_overrides.csv",
        "ledger": tmp_path / "reverse" / "functions.csv",
        "tool": tmp_path / "tools" / "flag_defaults.py",
        "retail": tmp_path / "game.dat",
    }
    for path in config_paths.values():
        path.parent.mkdir(parents=True, exist_ok=True)
        path.write_bytes(b"original")
    monkeypatch.setattr(dc.build, "EXE", config_paths["retail"])
    read = dc.build.read_object_symbol_bytes

    def changed_read(*args, **kwargs):
        result = read(*args, **kwargs)
        if args[1] == rows[-1]["name"]:
            if changed in ("source", "header", "object", "receipt"):
                path = {"source": source, "header": header, "object": obj,
                        "receipt": dc.build._deps_sidecar(obj)}[changed]
                old_stat = path.stat()
                data = path.read_bytes()
                path.write_bytes(data[:-1] + bytes([data[-1] ^ 1]))
                # On Windows even ctime can stay unchanged: uncached content
                # checks must catch this same-size, restored-mtime write.
                os.utime(path, ns=(old_stat.st_atime_ns, old_stat.st_mtime_ns))
                if changed == "object":
                    import hashlib
                    fresh = {**meta, "object": hashlib.md5(obj.read_bytes()).hexdigest()}
                    dc.build._deps_sidecar(obj).write_text(json.dumps(fresh))
            elif changed == "command":
                command.append("-DCHANGED")
            elif changed == "environment":
                env["INCLUDE"] = "different headers"
            else:
                # These files are cached by flag_defaults/retail readers, so
                # the final ordinary command/currency call can stay green.
                config_paths[changed].write_bytes(b"modified")
        return result

    monkeypatch.setattr(dc.build, "read_object_symbol_bytes", changed_read)
    unread = []
    assert dc.converged_facts(rows, unread) == []
    assert [(source, name) for source, name, _why in unread] == [
        (r["source"], r["name"]) for r in rows]


def test_a_late_header_change_invalidates_every_object_using_it(tmp_path, monkeypatch):
    rows, source, header, obj, meta, _command, _env = multi_row_audit(tmp_path, monkeypatch)
    second = tmp_path / "b.obj"
    second.write_bytes(obj.read_bytes())
    second_source = tmp_path / "Code" / "B.cpp"
    second_source.write_bytes(source.read_bytes())
    dc.build._deps_sidecar(second).write_text(json.dumps(meta))
    rows[1]["source"] = "Code/B.cpp"
    monkeypatch.setattr(dc.build, "row_object", lambda r: obj if r["source"] == "Code/A.cpp" else second)
    read = dc.build.read_object_symbol_bytes

    def changed_read(*args, **kwargs):
        result = read(*args, **kwargs)
        if args[0] == second:
            header.write_text("// changed header\n")
        return result

    monkeypatch.setattr(dc.build, "read_object_symbol_bytes", changed_read)
    unread = []
    assert dc.converged_facts(rows, unread) == []
    assert {source for source, _name, _why in unread} == {"Code/A.cpp", "Code/B.cpp"}


def test_two_sources_mapping_to_one_object_do_not_share_currency(tmp_path, monkeypatch):
    rows, _source, _header, _obj, _meta, _command, _env = multi_row_audit(tmp_path, monkeypatch)
    rows[1]["source"] = "Code/Missing.cpp"
    unread = []
    facts = dc.converged_facts(rows, unread)
    assert len(facts) == 1
    assert len(unread) == 1 and unread[0][:2] == ("Code/Missing.cpp", rows[1]["name"])


@pytest.mark.parametrize("damage", ["missing", "malformed", "bad-deps", "bad-dep-path"])
def test_bad_receipts_remain_unjudged_for_every_row(tmp_path, monkeypatch, damage):
    rows, _source, _header, obj, meta, _command, _env = multi_row_audit(tmp_path, monkeypatch)
    receipt = dc.build._deps_sidecar(obj)
    if damage == "missing":
        receipt.unlink()
    elif damage == "malformed":
        receipt.write_text("{broken")
    else:
        receipt.write_text(json.dumps({**meta, "deps": [] if damage == "bad-deps" else {"../bad": "hash"}}))
    unread = []
    assert dc.converged_facts(rows, unread) == []
    assert len(unread) == len(rows)


def test_an_old_same_stamp_layout_is_not_trusted_with_a_new_receipt(tmp_path, monkeypatch):
    import hashlib
    rows, _source, _header, obj, meta, _command, _env = multi_row_audit(tmp_path, monkeypatch)
    # Warm the exact reader cache, then change a relocation's symbol name
    # without changing file size or mtime. A fresh receipt alone is insufficient.
    dc.build.read_object_symbol_bytes(obj, rows[0]["name"], 6)
    old_stat = obj.stat()
    old = obj.read_bytes()
    assert b"?alias@@3PAXA" in old
    obj.write_bytes(old.replace(b"?alias@@3PAXA", b"?other@@3PAXA"))
    os.utime(obj, ns=(old_stat.st_atime_ns, old_stat.st_mtime_ns))
    dc.build._deps_sidecar(obj).write_text(json.dumps({**meta, "object": hashlib.md5(obj.read_bytes()).hexdigest()}))
    unread = []
    assert dc.converged_facts(rows, unread) == []
    assert len(unread) == len(rows)
    assert all(why == "cached object layout differs from its build receipt" for _s, _n, why in unread)


def test_a_reloaded_layout_generation_cannot_hide_a_transient_swap(tmp_path, monkeypatch):
    rows, _source, _header, obj, _meta, _command, _env = multi_row_audit(tmp_path, monkeypatch)
    original = obj.read_bytes()
    old_stat = obj.stat()
    real_stat = Path.stat
    # Reproduce Windows' unchanged same-size, restored-mtime file identity on
    # every host. The uncached disk content returns to its original bytes too.
    monkeypatch.setattr(Path, "stat", lambda path, *a, **kw:
                        old_stat if path == obj else real_stat(path, *a, **kw))
    read = dc.build.read_object_symbol_bytes

    def swapped_read(*args, **kwargs):
        if args[1] != rows[-1]["name"]:
            return read(*args, **kwargs)
        # Interleaved rows can evict the original layout from the bounded LRU.
        dc.build._object_layout.cache_clear()
        obj.write_bytes(original.replace(b"?alias@@3PAXA", b"?other@@3PAXA"))
        result = read(*args, **kwargs)
        obj.write_bytes(original)
        return result

    monkeypatch.setattr(dc.build, "read_object_symbol_bytes", swapped_read)
    unread = []
    assert dc.converged_facts(rows, unread) == []
    assert len(unread) == len(rows)


def test_rows_of_asm_sources_are_read_and_lib_members_are_not(tmp_path, monkeypatch):
    (tmp_path / "reverse").mkdir()
    (tmp_path / "reverse" / "functions.csv").write_text(
        "name,export_rva,target_rva,target_size,source,status,notes\n"
        "?a@@YAXXZ,,0x00001000,6,Code/A.asm,matched,\n"
        "?b@@YAXXZ,,0x00001010,6,Code/B.cpp,matched,\n"
        "?c@@YAXXZ,,0x00001020,6,Lib/C.lib,matched,\n"
        "?d@@YAXXZ,,0x00001030,6,Code/D.cpp,present-unmatched,\n", encoding="utf-8")
    monkeypatch.setattr(dc, "ROOT", tmp_path)
    got = dc.converged_rows(["Code/A.asm", "Code/B.cpp", "Lib/C.lib", "Code/D.cpp"])
    assert [r["name"] for r in got] == ["?a@@YAXXZ", "?b@@YAXXZ"]
    assert [r["name"] for r in dc.converged_rows_all()] == ["?a@@YAXXZ", "?b@@YAXXZ"]


# ---------------------------------------------------------------- the list, read from git

@pytest.fixture
def repo(tmp_path, monkeypatch):
    def git(*args):
        return subprocess.run(["git", *args], cwd=tmp_path, check=True, capture_output=True)
    git("init", "-q")
    git("config", "user.name", "T")
    git("config", "user.email", "t@example.invalid")
    git("config", "core.autocrlf", "false")
    monkeypatch.setattr(dc, "ROOT", tmp_path)
    monkeypatch.setattr(dc, "CONVERGED", tmp_path / "reverse" / "data_converged.csv")
    (tmp_path / "reverse").mkdir()
    (tmp_path / "x").write_text("x", encoding="utf-8")
    git("add", "x")
    git("commit", "-qm", "before the list")
    return git


def put(text):
    dc.CONVERGED.write_text(text, encoding="utf-8")


def test_the_list_is_read_from_the_ref_and_refuses_every_doubt(repo):
    put(f"address,name,evidence\n0x009FE78C,{GL},x\n")
    repo("add", "reverse/data_converged.csv")
    put("address,name,evidence\n")                                     # unstaged: emptied
    assert dc.load_converged(ref=":") == CONVERGED                      # the index is judged
    with pytest.raises(ValueError):
        dc.load_converged()                                             # the working copy: empty
    with pytest.raises(ValueError):
        dc.load_converged(ref="HEAD")                                   # HEAD lacks it: missing
    assert dc.load_converged(ref="HEAD", required=False) is None
    with pytest.raises(OSError):
        dc.text_at("no-such-ref", dc.CONVERGED)                         # unknown ref
    for bad in ("address,evidence\n0x009FE78C,x\n",                     # no name column
                f"address,name,evidence\n0x009FE78C\n",                 # short row
                f"address,name,evidence\n0x009FE78C,{GL},x,extra\n",    # long row
                "address,name,evidence\nnot-hex,?a@@3HA,x\n",
                "address,name,evidence\n0x009FE78C,TheGameLogic,x\n",   # not a symbol
                f"address,name,evidence\n0x009FE78C,{GL},x\n0x009FE78C,{GL},y\n"):
        put(bad)
        with pytest.raises(ValueError):
            dc.load_converged()


def test_the_list_only_grows(repo):
    put(f"address,name,evidence\n0x009FE78C,{GL},x\n0x009FE16C,?TheScriptEngine@@3PAVScriptEngine@@A,x\n")
    repo("add", "reverse/data_converged.csv")
    repo("commit", "-qm", "list")
    keep = dc.load_converged()
    assert dc.lost_addresses("HEAD", keep) == []
    assert dc.lost_addresses("HEAD~1", {SLOT: GL}) == []                # base without the list
    assert dc.lost_addresses("HEAD", {SLOT: GL}) == [0x009FE16C]        # dropped
    assert dc.lost_addresses("HEAD", {**keep, SLOT: "?Other@@3PAXA"}) == [SLOT]   # renamed
    assert dc.lost_addresses("HEAD", {**keep, 0x009FF0F8: "?TheAI@@3PAVAI@@A"}) == []  # grown


def test_an_unreadable_base_list_is_not_taken_for_a_missing_one(repo, tmp_path):
    """Review round 6: a base whose list blob could not be read counted as having
    no list, so the shrink went unseen. Only a listing without the file is absence."""
    put(f"address,name,evidence\n0x009FE78C,{GL},x\n0x009FE16C,?TheScriptEngine@@3PAVScriptEngine@@A,x\n")
    repo("add", "reverse/data_converged.csv")
    repo("commit", "-qm", "list")
    assert dc.lost_addresses("HEAD", {SLOT: GL}) == [0x009FE16C]                   # control
    sha = subprocess.run(["git", "rev-parse", "HEAD:reverse/data_converged.csv"], cwd=tmp_path,
                         capture_output=True, text=True, check=True).stdout.strip()
    loose = tmp_path / ".git" / "objects" / sha[:2] / sha[2:]
    loose.chmod(0o644)                                                              # git writes objects read-only
    loose.unlink()
    with pytest.raises(OSError):
        dc.lost_addresses("HEAD", {SLOT: GL})
    assert dc.lost_addresses("HEAD~1", {SLOT: GL}) == []                            # genuine absence


def test_a_list_tracked_under_another_case_is_refused(repo):
    """Windows reads reverse/Data_Converged.csv as the list; git's exact lookup
    would miss it and the list would count as absent (review round 6)."""
    variant = dc.CONVERGED.parent / "Data_Converged.csv"
    variant.write_text(f"address,name,evidence\n0x009FE78C,{GL},x\n", encoding="utf-8")
    repo("add", "reverse/Data_Converged.csv")
    with pytest.raises(OSError):
        dc.load_converged(ref=":")
    repo("commit", "-qm", "variant")
    with pytest.raises(OSError):
        dc.load_converged(ref="HEAD", required=False)


def test_a_base_list_under_a_miscased_directory_is_refused(repo, tmp_path):
    """A base whose list is tracked as Reverse/data_converged.csv was taken for a
    base without one, so a staged canonical list could shrink (review round 7)."""
    blob = tmp_path / "blob.tmp"
    blob.write_text(f"address,name,evidence\n0x009FE78C,{GL},x\n0x009FE16C,?TheScriptEngine@@3PAVScriptEngine@@A,x\n",
                    encoding="utf-8")
    sha = subprocess.run(["git", "hash-object", "-w", str(blob)], cwd=tmp_path, capture_output=True, text=True,
                         check=True).stdout.strip()
    repo("update-index", "--add", "--cacheinfo", f"100644,{sha},Reverse/data_converged.csv")
    repo("commit", "-qm", "variant list")
    with pytest.raises(OSError):
        dc.lost_addresses("HEAD", {SLOT: GL})


def test_main_refuses_a_bad_or_shrunk_list_and_judges_sources(repo, monkeypatch, tmp_path):
    put(f"address,name,evidence\n0x009FE78C,{GL},x\n0x009FE16C,?TheScriptEngine@@3PAVScriptEngine@@A,x\n")
    repo("add", "reverse/data_converged.csv")
    repo("commit", "-qm", "list")
    listing = tmp_path / "sources"
    listing.write_bytes(b"Code/A.cpp\0")
    seen = []
    monkeypatch.setattr(dc, "check_converged", lambda sources, conv: seen.append(sources) or 0)
    assert dc.main(["--converged", "--ref", ":", "--converged-base", "HEAD", "--sources-from", str(listing)]) == 0
    assert seen == [["Code/A.cpp"]]
    put(f"address,name,evidence\n0x009FE78C,{GL},x\n")
    repo("add", "reverse/data_converged.csv")
    assert dc.main(["--converged", "--ref", ":", "--converged-base", "HEAD", "--sources-from", str(listing)]) == 1
    put("address,name,evidence\n")
    repo("add", "reverse/data_converged.csv")
    assert dc.main(["--converged", "--ref", ":", "--sources-from", str(listing)]) == 1
    assert dc.main(["--converged", "--ref", "no-such-ref", "--sources-from", str(listing)]) == 1
    assert len(seen) == 1


def test_sources_from_is_nul_separated(tmp_path):
    p = tmp_path / "s"
    p.write_bytes(b"Code/A b.cpp\0Code/C.cpp\0")
    assert dc.read_sources_from(str(p)) == ["Code/A b.cpp", "Code/C.cpp"]


# ---------------------------------------------------------------- the hook

# A data_check stand-in for the hook fixtures: records each --converged call and
# answers --print-claimed as data_check.claimed_sources does (matched rows).
RECORDER = """import csv, json, sys
args = sys.argv[1:]
srcs = [p.decode() for p in sys.stdin.buffer.read().split(b"\\0") if p] if "-" in args else []
if "--print-claimed" in args:
    claimed = {r["source"] for r in csv.DictReader(open("reverse/functions.csv")) if r["status"] == "matched"}
    sys.stdout.buffer.write(b"".join(s.encode() + b"\\0" for s in srcs if s in claimed))
    sys.exit(0)
open("conv-calls.jsonl", "a").write(json.dumps({"argv": args, "sources": srcs}) + "\\n")
"""

@pytest.mark.parametrize("header", ["Code/Shared.h", "Code/Shared.hpp"])
def test_pre_commit_judges_the_sources_a_header_reaches(tmp_path, header):
    """Review round 1: a header-only commit built its dependents (scoped header
    gate) and never ran --converged on them. Round 2: a .hpp-only change was not
    a header change at all."""
    import test_hook_argmax as argmax
    repo = argmax.make_repo(tmp_path, 3)
    parked = "Code/GameEngine/Source/Parked.cpp"                       # a draft with no row
    argmax.write(repo, "tools/data_check.py", RECORDER)
    argmax.write(repo, "tools/header_dependents.py",       # LF lines, as the real tool prints for mapfile
                 f"import sys\nsys.stdout.reconfigure(newline='\\n')\nprint({argmax.source(1)!r})\nprint({parked!r})\n")
    argmax.write(repo, parked, "// parked\n")
    argmax.write(repo, header, "struct Shared {};\n")
    argmax.git(repo, "add", "-A")
    argmax.git(repo, "commit", "-qm", "stubs", "--no-verify")              # fixture setup, not the hook under test
    argmax.write(repo, header, "struct Shared { int m; };\n")             # a header-only change
    argmax.git(repo, "add", header)
    result = subprocess.run([argmax._bash(), str(argmax.HOOK)], cwd=repo, capture_output=True, text=True,
                            encoding="utf-8", errors="replace", timeout=900)
    assert result.returncode == 0, result.stderr[-3000:]
    calls = [json.loads(line) for line in (repo / "conv-calls.jsonl").read_text().splitlines()]
    judged = [c for c in calls if "--converged" in c["argv"] and c["sources"]]
    assert any(argmax.source(1) in c["sources"] for c in judged), calls
    assert any("--converged-base" in c["argv"] for c in calls)              # the list check ran too
    assert not any(parked in c["sources"] for c in judged)                  # review round 3: no row,
    assert parked not in {s for call in argmax.calls(repo, "build-calls.jsonl") for s in call}   # not built


def test_claimed_sources_are_those_owning_a_matched_function_or_data_row(tmp_path, monkeypatch, capsysbinary):
    (tmp_path / "reverse").mkdir()
    (tmp_path / "reverse" / "functions.csv").write_text(
        "name,export_rva,target_rva,target_size,source,status,notes\n"
        "?a@@YAXXZ,,0x00001000,6,Code/A.cpp,matched,\n"
        "?b@@YAXXZ,,0x00001010,6,Code/B.cpp,present-unmatched,\n", encoding="utf-8")
    (tmp_path / "reverse" / "data_rows.csv").write_text(
        "name,address,address_kind,size,section,source,status,evidence,model\n"
        "?g@@3HA,0x009E0000,rva,4,.data,Code/D.cpp,matched,e,m\n", encoding="utf-8")
    monkeypatch.setattr(dc, "ROOT", tmp_path)
    assert dc.claimed_sources(["Code/B.cpp", "Code/D.cpp", "Code/A.cpp", "Code/P.cpp"]) == ["Code/D.cpp", "Code/A.cpp"]
    listing = tmp_path / "s"
    listing.write_bytes(b"Code/P.cpp\0Code/A.cpp\0")
    assert dc.main(["--print-claimed", "--sources-from", str(listing)]) == 0
    assert capsysbinary.readouterr().out == b"Code/A.cpp\0"
