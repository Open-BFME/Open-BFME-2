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
