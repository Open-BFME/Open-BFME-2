"""tu_skeleton --merge carries protected-register debt with the code: every absorbed
donor's key is re-keyed to the TU in the merge commit, the hooks read that as a
transfer (not growth, not a vanished-source retirement), and register totals hold."""
import collections
import csv
import importlib
import io
import os
import shutil
import subprocess
import sys
from pathlib import Path

import pytest

TOOLS = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(TOOLS))
import tu_skeleton as T  # noqa: E402
import protected_paths  # noqa: E402

A, B, C, TU = "Code/A.cpp", "Code/B.cpp", "Code/C.cpp", "Code/T.cpp"
HEADER = "name,export_rva,target_rva,target_size,source,status,notes\n"
TEXTS = {A: '#pragma optimize("", off)\nint a() { return 1; }\n#pragma optimize("", on)\n',
         B: "int b() { return 2; }\n",
         C: "int c() { return 3; }\n"}
IDENTITY = ("# Wrong code bindings, keyed source<TAB>row<TAB>symbol<TAB>retail target<TAB>class.\n# mode: shadow\n"
            f"{A}\t?a@@YAHXZ\t?x@@YAXXZ\t0x00005000\twrong\n"
            f"{B}\t?b@@YAHXZ\t?x@@YAXXZ\t0x00005000\tunowned\n"
            f"{C}\t?c@@YAHXZ\t?x@@YAXXZ\t0x00005000\twrong\n")
DATA = ("# source\tcheck\tsymbol\taddress -- shrink-only; written by tools/data_check.py\n"
        f"{A}\twrong-name\t?g_00A00000@@3HA\t0x00A00000\n"
        f"{B}\twrong-name\t?g_00A00000@@3HA\t0x00A00000\n"      # the same key under two donors: kept once
        f"{B}\tduplicate-def\t?TheX@@3HA\t0x00A00004\n"
        f"{C}\twrong-name\t?g_00A00000@@3HA\t0x00A00000\n")
OVERRIDES = ("source,flags,rows,default_lost,reason\n"
             f"{A},-O2,2,1,region default loses rows\n"
             f"{C},-O2,1,1,region default loses rows\n")
LEDGER = ("address,size,section,kind,name,source,status,names,defs,refs\n"
          f"0x00A00000,4,.data,global,?g@@3HA,{A},provisional,?g@@3HA;?s@@3HA@{B},1,2\n"
          f"0x00A00004,4,.data,global,?TheX@@3HA,{C},owned,,1,1\n")
HATCH = ("# Escape-hatch register, shrink-only. hatch\tpath\ttoken\tcount\n# mode: enforce\n"
         f'pragma_optimize\t{A}\t"",off\t1\n'
         f'pragma_optimize\t{A}\t"",on\t1\n')


def git(root, *args, check=True):
    return subprocess.run(["git", "-C", str(root), *args], capture_output=True, text=True, check=check)


@pytest.fixture
def repo(tmp_path, monkeypatch):
    files = {**TEXTS,
             "reverse/functions.csv": HEADER + f"?a@@YAHXZ,,0x00001000,8,{A},matched,\n"
                                               f"?b@@YAHXZ,,0x00001010,8,{B},matched,\n"
                                               f"?c@@YAHXZ,,0x00001020,8,{C},matched,\n",
             "reverse/code_identity_baseline.tsv": IDENTITY, "reverse/data_check_baseline.txt": DATA,
             "reverse/flag_overrides.csv": OVERRIDES, "reverse/data_ledger.csv": LEDGER,
             "reverse/hatch_baseline.tsv": HATCH}
    for rel, text in files.items():
        (tmp_path / rel).parent.mkdir(parents=True, exist_ok=True)
        (tmp_path / rel).write_text(text, encoding="utf-8", newline="\n")
    (tmp_path / "tools").mkdir()
    shutil.copy(TOOLS / "hatch_counters.py", tmp_path / "tools")   # stdlib only; ROOT is the fixture
    git(tmp_path, "init", "-q")
    git(tmp_path, "config", "core.autocrlf", "false")
    git(tmp_path, "add", ".")
    git(tmp_path, "-c", "user.name=t", "-c", "user.email=t@t", "commit", "-qm", "init")
    monkeypatch.chdir(tmp_path)          # protected_paths' git runs where the hook does
    protected_paths._LEDGERS.clear()
    return tmp_path


def merged_text():
    return "".join(TEXTS[f] for f in (A, B))


def keys(text):
    return [line for line in text.splitlines() if line and not line.startswith("#")]


def tails(text):
    return collections.Counter(line.split("\t", 1)[1] for line in keys(text))


def hatch_totals(text):
    out = collections.Counter()
    for line in keys(text):
        hatch, _path, token, count = line.split("\t")[:4]
        out[(hatch, token)] += int(count)
    return out


def override_totals(text):
    rows = list(csv.DictReader(io.StringIO(text)))
    return sum(int(r["rows"]) for r in rows), sum(int(r["default_lost"]) for r in rows)


def test_a_merge_carries_every_protected_key_to_the_tu(repo):
    before = {rel: (repo / rel).read_text() for rel in T.rename.PROTECTED_PATH_KEYED}
    carry = T.Carry(repo, TU, [A, B], TEXTS, merged_text(), "-O2")
    assert carry.problems == [] and carry.collapsed == []
    assert carry.moved == {"reverse/code_identity_baseline.tsv": 2, "reverse/data_check_baseline.txt": 3,
                           "reverse/flag_overrides.csv": 1, "reverse/data_ledger.csv": 1,
                           "reverse/hatch_baseline.tsv": "hatch_counters --update"}
    assert carry.trailer().startswith("Verifier-Change: tu_skeleton --merge carried")
    moved = T.apply(TU, [A, B], merged_text(), root=repo, carry=carry)
    assert moved["reverse/hatch_baseline.tsv"] == "updated"
    after = {rel: (repo / rel).read_text() for rel in T.rename.PROTECTED_PATH_KEYED}

    # zero keys left on a deleted donor
    assert T.vanished({rel: text.encode() for rel, text in after.items()}, {A, B}) == []
    assert not (repo / A).exists() and not (repo / B).exists()
    # totals: every distinct key survives under the TU; counts and hatch totals are kept
    for rel in T.KEYED_LINES:
        assert set(tails(after[rel])) == set(tails(before[rel]))
    assert f"{TU}\t?a@@YAHXZ\t?x@@YAXXZ\t0x00005000\twrong" in after["reverse/code_identity_baseline.tsv"]
    assert keys(after["reverse/data_check_baseline.txt"]).count(f"{TU}\twrong-name\t?g_00A00000@@3HA\t0x00A00000") == 1
    assert hatch_totals(after["reverse/hatch_baseline.tsv"]) == hatch_totals(before["reverse/hatch_baseline.tsv"])
    assert f"\t{TU}\t" in after["reverse/hatch_baseline.tsv"]
    assert override_totals(after["reverse/flag_overrides.csv"]) == override_totals(before["reverse/flag_overrides.csv"])
    assert f"{TU},-O2,2,1,region default loses rows" in after["reverse/flag_overrides.csv"]
    assert f"?g@@3HA,{TU},provisional,?g@@3HA;?s@@3HA@{TU}," in after["reverse/data_ledger.csv"]

    # the hooks: verify-removed reads a transfer, no vanished-source accounting is needed
    os.environ["REPAIR_ROOT"] = str(repo)
    try:
        import repair_queue
        rq = importlib.reload(repair_queue)
    finally:
        del os.environ["REPAIR_ROOT"]
    for kind in ("data", "identity"):
        removed, staged = rq.removed_keys(kind)
        assert removed and all(rq._debt_transferred(kind, src, ks, staged) for src, ks in removed.items())
    assert rq.verify_removed_debt(build_cmd=[sys.executable, "-c", "raise SystemExit(1)"],
                                  header_verdict=lambda *a: ["unexpected"]) == []
    assert rq.verify_missing_debt("") == []
    # the shrink-only gates read the re-keyed lines as a move, not growth
    staged = set(git(repo, "diff", "--cached", "--name-only").stdout.split())
    assert protected_paths.growth(["HEAD"], ":", staged, set()) == []
    head, index = (git(repo, "show", f"{r}reverse/code_identity_baseline.tsv").stdout for r in ("HEAD:", ":"))
    grown = set(keys(index)) - set(keys(head))
    assert grown and protected_paths.transferred("HEAD", ":", grown, set(keys(head)) - set(keys(index))) == grown


def test_a_key_the_tu_already_holds_collapses_and_prints_its_debt_retired_line(repo):
    path = repo / "reverse/data_check_baseline.txt"
    path.write_text(DATA + f"{TU}\tduplicate-def\t?TheX@@3HA\t0x00A00004\n", newline="\n")
    (repo / TU).write_text("int t() { return 0; }\n")
    carry = T.Carry(repo, TU, [TU, A, B], {**TEXTS, TU: "int t() { return 0; }\n"}, merged_text(), "-O2")
    line = f"{B}\tduplicate-def\t?TheX@@3HA\t0x00A00004"
    assert carry.collapsed == [("reverse/data_check_baseline.txt", line)]
    assert carry.retired() == [f"Debt-Retired: {line} {B} merged into {TU}, which already holds this key"]
    assert line not in carry.new["reverse/data_check_baseline.txt"].decode()


def test_a_merge_that_would_leave_a_key_on_a_deleted_donor_is_refused(repo):
    # a register line naming the donor in a column carry() does not rewrite
    path = repo / "reverse/data_check_baseline.txt"
    path.write_text(DATA + f"{C}\twrong-name\t{A}\t0x00A00008\n", newline="\n")
    carry = T.Carry(repo, TU, [A, B], TEXTS, merged_text(), "-O2")
    assert any("would still key a deleted donor" in p for p in carry.problems)


def test_hatch_growth_in_the_merged_text_is_refused(repo):
    text = merged_text() + '#pragma optimize("", off)\n'
    carry = T.Carry(repo, TU, [A, B], TEXTS, text, "-O2")
    assert any("escape-hatch" in p for p in carry.problems)


def test_overrides_disagreeing_with_the_verified_flags_are_refused(repo):
    carry = T.Carry(repo, TU, [A, B], TEXTS, merged_text(), "-O1")
    assert any("disagree" in p for p in carry.problems)


def test_without_protected_keys_nothing_is_carried(repo):
    for rel in T.rename.PROTECTED_PATH_KEYED:
        text = (repo / rel).read_text()
        (repo / rel).write_text("".join(l for l in text.splitlines(True) if A not in l and B not in l),
                                newline="\n")
    carry = T.Carry(repo, TU, [A, B], {A: "int a();\n", B: "int b();\n"}, "int a();\nint b();\n", "-O2")
    assert carry.moved == {} and carry.problems == [] and carry.trailer() is None



# Compiler-label funclet rows (label_renames). The Object.cpp merge (2026-11-13): two PoolKey donors each carried an
# unwind funclet row `$L310`; one TU scopes one label, so check_csv refused "$L310 claims two addresses" after the
# merge. The merge renames each to the address name Ghidra gives it, as the merge lane did by hand.
PARENT_A, PARENT_B = "?getKey@AHelper@@UBEHXZ", "?getKey@BHelper@@UBEHXZ"
LABELS = (f"$L310,,0x0077436A,13,{A},matched,gen-funclet;parent={PARENT_A}; Exact parent EH graph places $L310\n"
          f"$L310,,0x00774522,13,{B},matched,\"gen-funclet;parent={PARENT_B}; Exact parent, places $L310\"\n"
          f"$L310,,0x00774313,13,{C},matched,gen-funclet;parent=?getKey@CHelper@@UBEHXZ\n")
GHIDRA_CSV = "rva,size,name\n0x77436A,13,Unwind@00b7436a\n0x774522,13,Unwind@00b74522\n0x774313,13,Unwind@00b74313\n"


def label_repo(repo, ghidra=GHIDRA_CSV, extra=""):
    functions = repo / "reverse/functions.csv"
    functions.write_text(functions.read_text() + LABELS + extra, encoding="utf-8", newline="\n")
    (repo / "reverse/ghidra_functions.csv").write_text(ghidra, encoding="utf-8", newline="\n")
    (repo / "reverse/deleted_rows.csv").write_text('name,target_rva,reason\n?gone@@YAXXZ,0x00100000,"old"\n',
                                                   encoding="utf-8", newline="\n")
    git(repo, "add", ".")
    git(repo, "-c", "user.name=t", "-c", "user.email=t@t", "commit", "-qm", "labels")
    return repo


def test_a_label_two_merging_files_carry_is_renamed_to_its_address_name(repo):
    label_repo(repo)
    carry = T.Carry(repo, TU, [A, B], TEXTS, merged_text(), "-O2")
    assert carry.problems == []
    assert carry.labels == [("$L310", 0x0077436A, "Unwind@00b7436a"), ("$L310", 0x00774522, "Unwind@00b74522")]
    assert carry.report()["label_renames"] == ["$L310 0x0077436A -> Unwind@00b7436a",
                                               "$L310 0x00774522 -> Unwind@00b74522"]
    moved = T.apply(TU, [A, B], merged_text(), root=repo, carry=carry)
    assert moved["reverse/deleted_rows.csv"] == 2
    rows = list(csv.DictReader(io.StringIO((repo / "reverse/functions.csv").read_text())))
    by_rva = {r["target_rva"]: r for r in rows}
    assert by_rva["0x0077436A"]["name"] == "Unwind@00b7436a" and by_rva["0x0077436A"]["source"] == TU
    assert by_rva["0x0077436A"]["notes"].startswith(f"gen-funclet;parent={PARENT_A};object-symbol=$L310;")
    assert by_rva["0x00774522"]["notes"].startswith(f"gen-funclet;parent={PARENT_B};object-symbol=$L310;")
    # the third file is not in this merge: its own $L310 stays, scoped to its own TU
    assert by_rva["0x00774313"]["name"] == "$L310" and by_rva["0x00774313"]["source"] == C
    deleted = (repo / "reverse/deleted_rows.csv").read_text().splitlines()
    assert deleted[-2].startswith('$L310,0x0077436A,"Renamed to Unwind@00b7436a: tu_skeleton merge into Code/T.cpp')
    assert deleted[-1].startswith('$L310,0x00774522,"Renamed to Unwind@00b74522')
    # every other byte of functions.csv is kept
    before = git(repo, "show", "HEAD:reverse/functions.csv").stdout.splitlines()
    after = (repo / "reverse/functions.csv").read_text().splitlines()
    assert [b for b, a in zip(before, after) if b != a and "$L310" not in b and A not in b and B not in b] == []


@pytest.mark.parametrize("ghidra,extra,pin,why", [
    (GHIDRA_CSV.replace("Unwind@00b74522", "FUN_00b74522"), "", "", "Ghidra names 0x00774522 FUN_00b74522"),
    (GHIDRA_CSV, "Unwind@00b74522,,0x00999999,4,Code/Z.cpp,matched,\n", "", "Unwind@00b74522 is already a row"),
    (GHIDRA_CSV, "", "$L310,0x00774522,pin\n", "a pin, eh_baseline.csv or body_owners.csv keys it"),
])
def test_a_label_that_cannot_take_its_address_name_refuses_the_merge(repo, ghidra, extra, pin, why):
    if pin:
        (repo / "reverse/symbols.csv").write_text("name,address,notes\n" + pin, encoding="utf-8", newline="\n")
    label_repo(repo, ghidra=ghidra, extra=extra)
    carry = T.Carry(repo, TU, [A, B], TEXTS, merged_text(), "-O2")
    assert any(why in problem for problem in carry.problems), carry.problems


def test_a_label_only_one_merging_file_carries_is_left_alone(repo):
    label_repo(repo)
    carry = T.Carry(repo, TU, [A, TU], {**TEXTS, TU: "int t() { return 0; }\n"}, merged_text(), "-O2")
    assert carry.labels == [] and "label_renames" not in carry.report()


@pytest.mark.parametrize("change", [
    lambda repo: (repo / "reverse/functions.csv").write_text((repo / "reverse/functions.csv").read_text()+"\n"),
    lambda repo: (repo / "reverse/ghidra_functions.csv").write_text("rva,size,name\n"),
    lambda repo: (repo / "reverse/deleted_rows.csv").write_text("name,target_rva,reason\n"),
    lambda repo: (repo / "reverse/symbols.csv").write_text("name,address,notes\n"),
])
def test_changed_label_inputs_refuse_before_any_apply_write(repo,change):
    label_repo(repo)
    carry=T.Carry(repo,TU,[A,B],TEXTS,merged_text(),"-O2")
    change(repo)
    before={str(p.relative_to(repo)):p.read_bytes() for p in repo.rglob("*") if p.is_file() and ".git" not in p.parts}
    with pytest.raises(T.NothingWritten,match="inputs changed"):
        T.apply(TU,[A,B],merged_text(),root=repo,carry=carry)
    after={str(p.relative_to(repo)):p.read_bytes() for p in repo.rglob("*") if p.is_file() and ".git" not in p.parts}
    assert before==after


def test_same_label_and_rva_outside_merge_refuses_before_global_tombstone(repo):
    import check_csv
    label_repo(repo,extra=f"$L310,,0x77436a,13,{C},matched,gen-funclet;parent=?other@@YAXXZ\n")
    path=repo/"reverse/functions.csv"
    path.write_text("".join(line for line in path.read_text().splitlines(keepends=True)
                            if not line.startswith("$L310,,0x00774313,")), encoding="utf-8", newline="\n")
    before=path.read_bytes()
    problems=[]
    check_csv.check_functions(before,problems,{A,B,C},(repo/"reverse/deleted_rows.csv").read_bytes())
    assert not problems,problems
    carry=T.Carry(repo,TU,[A,B],TEXTS,merged_text(),"-O2")
    assert not carry.labels and any("outside funclet" in p for p in carry.problems)
    assert path.read_bytes()==before
    problems=[]
    check_csv.check_functions(path.read_bytes(),problems,{A,B,C},(repo/"reverse/deleted_rows.csv").read_bytes())
    assert not problems,problems


@pytest.mark.parametrize("edit,why", [
    (lambda s:s.replace(f"gen-funclet;parent={PARENT_A}","gen-funclet"),"parent-bound"),
    (lambda s:s.replace(f"parent={PARENT_A}",f"parent={PARENT_A};object-symbol=$L999"),"conflicting object-symbol"),
    (lambda s:s+f"$L310,,0x0077436A,13,{A},matched,gen-funclet;parent={PARENT_A}\n","uniquely"),
])
def test_ambiguous_or_unbound_funclets_refuse(repo,edit,why):
    label_repo(repo)
    p=repo/"reverse/functions.csv";p.write_text(edit(p.read_text()))
    carry=T.Carry(repo,TU,[A,B],TEXTS,merged_text(),"-O2")
    assert any(why in p for p in carry.problems)


def test_conflicting_ghidra_inventory_refuses(repo):
    label_repo(repo,ghidra=GHIDRA_CSV+"0x77436A,13,Catch@00b7436a\n")
    carry=T.Carry(repo,TU,[A,B],TEXTS,merged_text(),"-O2")
    assert any("conflicting Ghidra" in p for p in carry.problems)


def test_old_label_keyed_by_protected_register_refuses(repo):
    label_repo(repo)
    p=repo/"reverse/code_identity_baseline.tsv"
    p.write_text(p.read_text()+f"{A}\t$L310\t?x@@YAXXZ\t0x0077436A\twrong\n")
    carry=T.Carry(repo,TU,[A,B],TEXTS,merged_text(),"-O2")
    assert any("protected path register" in p for p in carry.problems)
