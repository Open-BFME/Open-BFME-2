#!/usr/bin/env python3
"""Focused tests for tools/progress.py; stdlib only."""
import csv
import importlib.util
import io
import re
import subprocess
import sys
import tempfile
from contextlib import contextmanager, redirect_stdout
from pathlib import Path
from unittest.mock import patch

ROOT = Path(__file__).resolve().parents[2]
TOOL = ROOT / "tools" / "progress.py"

sys.path.insert(0, str(ROOT / "tools"))
spec = importlib.util.spec_from_file_location("progress", TOOL)
progress = importlib.util.module_from_spec(spec)
spec.loader.exec_module(progress)


def row(name, rva, size, source):
    return {(name, f"0x{rva:X}"): (size, source)}


@contextmanager
def committed_progress_history():
    """Real Git inputs with a tiny controlled baseline, independent of repo history."""
    start = 0x1000
    image = b"\x90\x90\x90\xc3" * 3 + b"\xcc" * 4
    with tempfile.TemporaryDirectory() as directory:
        repo = Path(directory)

        def git(*args):
            return subprocess.run(
                ["git", *args], cwd=repo, check=True,
                capture_output=True, text=True,
            ).stdout.strip()

        git("init", "-q")
        sources = {
            "Code/clean.cpp": "void clean() {}\n",
            "Code/raw.cpp": "// _raw\n__declspec(naked) void raw() {\n"
                            " __asm {\n  nop\n  nop\n  nop\n  ret\n }\n}\n",
            "Code/gen_asm/raw.asm": "_raw PROC\n db 090h, 090h, 090h, 0C3h\n_raw ENDP\n",
            "Code/gen_asm/more.asm": "_more PROC\n db 090h, 090h, 090h, 0C3h\n_more ENDP\n",
            "Code/more.cpp": "void more() {}\n",
        }
        for name, text in sources.items():
            source = repo / name
            source.parent.mkdir(parents=True, exist_ok=True)
            source.write_text(text, encoding="utf-8")
        ledger = repo / progress.FUNCTIONS
        ledger.parent.mkdir(parents=True)

        def commit(rows, message):
            with ledger.open("w", encoding="utf-8", newline="") as stream:
                writer = csv.writer(stream)
                writer.writerow(("name", "target_rva", "target_size", "source", "status", "notes"))
                for name, rva, size, source, notes in rows:
                    writer.writerow((name, f"0x{rva:X}", size, source, "matched", notes))
            git("add", "--", progress.FUNCTIONS, *sources)
            git("-c", "user.name=Progress Test", "-c", "user.email=progress@example.invalid",
                "commit", "-qm", message)
            return git("rev-parse", "HEAD")

        clean = ("_clean", start, 4, "Code/clean.cpp", "")
        naked = ("_raw", start + 4, 4, "Code/raw.cpp", "")
        asm = ("_raw", start + 4, 4, "Code/gen_asm/raw.asm", "gen-dump;")
        alias = ("_alias", start + 4, 4, "Code/gen_asm/raw.asm", "gen-dump;")
        more_dump = ("_more", start + 8, 4, "Code/gen_asm/more.asm", "gen-dump;")
        more_cpp = ("_more", start + 8, 4, "Code/more.cpp", "")
        refs = {
            "naked": commit([clean, naked], "naked implementation"),
            "repointed": commit([clean, asm, alias], "repoint same bytes and add overlapping row"),
            "dumped": commit([clean, asm, alias, more_dump], "claim another dump body"),
            "recovered": commit([clean, asm, alias, more_cpp], "replace that dump with source"),
        }

        def reader(rva, size):
            assert start <= rva <= rva + size <= start + len(image)
            return image[rva - start:rva - start + size]

        # Only image I/O is synthetic. Git, row parsing, classifiers, interval
        # accounting and reporting all run normally against the committed inputs.
        with patch.object(progress, "ROOT", repo), \
                patch.object(progress, "retail_text", return_value=(start, len(image))), \
                patch.object(progress, "_text_image", return_value=(start, image)), \
                patch.object(progress.build, "read_target_bytes", side_effect=reader), \
                patch.object(progress, "data_denominator", return_value=0):
            yield refs


def progress_output(*args):
    output = io.StringIO()
    with patch.object(sys, "argv", [str(TOOL), *args]), redirect_stdout(output):
        progress.main()
    return output.getvalue()


def test_compiled_sdk_source_is_cpp_with_vendored_provenance():
    for source in (
        "Code/Libraries/Source/DirectX/strsafe.cpp",
        "Code/Libraries/Source/CRT/VS2003/security_cookie_report.cpp",
    ):
        assert progress.source_kind(source) == "cpp"
        assert progress.source_lane(source, "", False) == "vendored"
    assert progress.source_lane("Code/Libraries/Source/CRT/RtcStack.cpp", "", False) == "authored"


def test_marker_delta_handles_legacy_source_encoding():
    with tempfile.TemporaryDirectory() as directory:
        repo = Path(directory)
        subprocess.run(["git", "init", "-q", str(repo)], check=True)
        source = repo / "Code" / "legacy.cpp"
        source.parent.mkdir()
        source.write_bytes(b"// Copyright \xa9 EA\n// present-unmatched: old\n")
        subprocess.run(["git", "add", "Code/legacy.cpp"], cwd=repo, check=True)
        subprocess.run([
            "git", "-c", "user.name=Progress Test", "-c",
            "user.email=progress@example.invalid",
            "commit", "-qm", "baseline",
        ], cwd=repo, check=True)
        source.write_bytes(
            b"// Copyright \xa9 EA\n// absent-from-retail: new\n"
            b"// present-unmatched: another\n")
        with patch.object(progress, "ROOT", repo):
            assert progress.marker_delta("HEAD", None) == 1
    print("PASS legacy source encoding preserves marker delta")


def test_union_and_cpp_precedence():
    matched = {}
    matched.update(row("cpp-a", 0x1000, 10, "Code/a.cpp"))
    matched.update(row("cpp-b", 0x1005, 10, "Code/b.cpp"))
    matched.update(row("asm-overlap", 0x1008, 12, "Code/masm_dumps/a.asm"))
    matched.update(row("asm-only", 0x1030, 10, "Code/masm_dumps/b.asm"))
    stats = progress.coverage(matched, 0x1000, 100)
    assert stats == {
        "cpp": 15,
        "asm_only": 15,
        "data_only": 0,
        "unmatched": 70,
        "exact": 30,
        "text": 100,
    }, stats
    print("PASS interval union and C++ precedence")


def test_text_clipping():
    matched = {}
    matched.update(row("before", 0x0FF8, 12, "Code/a.cpp"))
    matched.update(row("after", 0x105E, 12, "Code/masm_dumps/a.asm"))
    stats = progress.coverage(matched, 0x1000, 100)
    assert stats["cpp"] == 4 and stats["asm_only"] == 6, stats
    assert stats["exact"] == 10 and stats["unmatched"] == 90, stats
    print("PASS .text boundary clipping")


def test_unknown_source_suffix_fails():
    matched = row("unknown", 0x1000, 10, "Code/generated/object.bin")
    try:
        progress.coverage(matched, 0x1000, 100)
    except SystemExit as exc:
        message = str(exc)
        assert "unsupported suffix .bin" in message and "object.bin" in message, message
    else:
        raise AssertionError("unknown matched-source suffix was counted as C++")
    print("PASS unknown matched-source suffix fails loudly")


def test_naked_cpp_to_clean_cpp_shifts_category_only():
    matched = row("?convert@Widget@@QAEXXZ", 0x1000, 3, "Code/convert.cpp")
    naked_text = """\
// ?convert@Widget@@QAEXXZ
__declspec(naked) void Widget::convert()
{
    __asm { __emit 0x8b __emit 0xc1 __emit 0xc3 }
}
"""
    naked_rows = progress.naked_cpp_rows(
        matched, {"Code/convert.cpp": naked_text},
        target_reader=lambda rva, size: bytes.fromhex("8b c1 c3"))
    assert naked_rows == set(matched), naked_rows

    before = progress.coverage(matched, 0x1000, 100, naked_rows)
    after = progress.coverage(matched, 0x1000, 100)
    assert before["asm_only"] == 3 and before["cpp"] == 0, before
    assert after["asm_only"] == 0 and after["cpp"] == 3, after
    assert before["exact"] == after["exact"] == 3
    assert before["unmatched"] == after["unmatched"] == 97
    print("PASS naked .cpp -> clean C++ shifts category but not exact coverage")


def test_bare_asm_emit_spray_is_asm_but_partial_emit_is_cpp():
    """A plain function whose __asm block emits the row's full retail bytes is
    a lift, not C++ (18 fleet commits smuggled these past the naked-only scan);
    a real body using the period _emit idiom for a few opcodes stays C++."""
    spray = row("?showBox@@YAXXZ", 0x1000, 8, "Code/spray.cpp")
    spray_text = """\
void showBox()
{
    __asm {
        __emit 0x8b;
        __emit 0xc1;
        call helper
        __emit 0x59;
        __emit 0xc3;
    }
}
"""
    found = progress.naked_cpp_rows(
        spray, {"Code/spray.cpp": spray_text},
        target_reader=lambda rva, size: bytes.fromhex("8bc1e800000000" + "59c3")[:size])
    assert found == set(spray), found

    idiom = row("?Init_CPU@@YAXXZ", 0x2000, 200, "Code/cpu.cpp")
    idiom_text = """\
void Init_CPU()
{
    int regs;
    __asm {
        mov eax, 1
        _emit 0x0f
        _emit 0xa2
        mov regs, eax
    }
}
"""
    found = progress.naked_cpp_rows(
        idiom, {"Code/cpu.cpp": idiom_text},
        target_reader=lambda rva, size: b"\x0f\xa2" + bytes(size - 2))
    assert found == set(), found
    print("PASS bare __asm emit spray is ASM; partial _emit idiom stays C++")


def test_mixed_file_marks_only_proven_naked_row():
    matched = {}
    matched.update(row("?raw@Widget@@QAEXXZ", 0x1000, 1, "Code/mixed.cpp"))
    matched.update(row("?clean@Widget@@QAEXXZ", 0x1010, 1, "Code/mixed.cpp"))
    text = """\
__declspec(naked) void Widget::raw() { __asm { ret } }
void Widget::clean() {}
"""
    found = progress.naked_cpp_rows(matched, {"Code/mixed.cpp": text})
    assert found == {("?raw@Widget@@QAEXXZ", "0x1000")}, found
    print("PASS mixed source classifies only signature-proven naked row")


def test_naked_body_callee_is_not_signature_evidence():
    matched = {}
    matched.update(row("?raw@Widget@@QAEXXZ", 0x1000, 1, "Code/wrapper.cpp"))
    matched.update(row("?clean@Widget@@QAEXXZ", 0x1010, 1, "Code/wrapper.cpp"))
    text = """\
__declspec(naked) void Widget::raw()
{
    __asm { call Widget::clean ret }
}
void Widget::clean() {}
"""
    found = progress.naked_cpp_rows(matched, {"Code/wrapper.cpp": text})
    assert found == {("?raw@Widget@@QAEXXZ", "0x1000")}, found
    print("PASS naked callee text cannot reclassify a clean row")


def test_naked_declaration_is_not_a_body():
    text = """\
__declspec(naked) void Widget::declared();
__declspec(naked) void Widget::defined() { __asm { ret } }
"""
    bodies = progress.scan_naked_bodies(text)
    assert len(bodies) == 1 and "Widget::defined" in bodies[0]["signature"], bodies
    print("PASS naked declarations are not counted as ASM bodies")


def test_signature_prefix_does_not_match_another_method():
    matched = {}
    matched.update(row("?raw@Widget@@QAEXXZ", 0x1000, 1, "Code/prefix.cpp"))
    matched.update(row("?rawHelper@Widget@@QAEXXZ", 0x1010, 1, "Code/prefix.cpp"))
    text = """\
void Widget::raw() {}
__declspec(naked) void Widget::rawHelper() { __asm { ret } }
"""
    found = progress.naked_cpp_rows(matched, {"Code/prefix.cpp": text})
    assert found == {("?rawHelper@Widget@@QAEXXZ", "0x1010")}, found
    print("PASS naked signature matching respects method boundaries")


def test_c_naked_signature_matches_decorated_row():
    matched = row("_GetPreviewFromMap", 0x1000, 1, "Code/free.cpp")
    text = "__declspec(naked) void *GetPreviewFromMap(void *, void *) { __asm { ret } }\n"
    found = progress.naked_cpp_rows(matched, {"Code/free.cpp": text})
    assert found == set(matched), found
    print("PASS C-linkage naked signature maps to its decorated row")


def test_live_naked_and_clean_rows_are_distinguished():
    """Every naked classification must point at a source that really contains a
    naked body, and clean rows must dominate.

    This used to pin two symbols by name, which rots by design: the project's
    goal is to convert every naked row, so any pinned naked symbol eventually
    becomes clean and the test breaks on progress (it died when the fleet
    converted ?construct@BFMENetworkBackend). Self-consistency over whatever
    is naked right now cannot rot, and an empty naked set is success."""
    matched = progress.matched_at("HEAD")
    naked = progress.naked_cpp_rows_at(matched, "HEAD")
    texts = progress.naked_source_texts(matched, "HEAD")
    for key in naked:
        source = matched[key][1]
        assert source in texts and (
            progress.NAKED_RE.search(texts[source])
            or progress.EMIT_RE.search(texts[source])), (
            f"{key} classified asm but {source} carries no naked or emit marker")
    clean = {key for key, (_, src) in matched.items()
             if src.endswith(".cpp")} - set(naked)
    assert len(clean) > len(naked), (len(clean), len(naked))
    print(f"PASS live ledger: {len(naked)} naked rows all self-consistent, "
          f"{len(clean)} clean")


def test_naked_repoint_is_zero_byte_progress():
    with committed_progress_history() as refs:
        start, size = progress.retail_text()
        before_rows = progress.matched_at(refs["naked"])
        after_rows = progress.matched_at(refs["repointed"])
        before = progress.coverage(
            before_rows, start, size, progress.naked_cpp_rows_at(before_rows, refs["naked"]))
        after = progress.coverage(
            after_rows, start, size, progress.naked_cpp_rows_at(after_rows, refs["repointed"]))
        assert len(after_rows) > len(before_rows)
        assert before == after, (before, after)
        assert after["cpp"] == 4 and after["asm_only"] == 4 and after["exact"] == 8, after
        output = progress_output(f"{refs['naked']}..{refs['repointed']}")
    # Every delta the scorecard prints must be zero, on whichever views exist.
    # Pinning the line count instead broke the moment the real-code view added
    # six more of them, which is a report gaining detail, not progress moving.
    deltas = output.count("delta ")
    assert deltas and len(re.findall(r"delta \+0 (?:bytes|items|files|copies), \+0\.00 pp", output)) == deltas, output
    assert "matched rows" not in output, output
    print(f"PASS naked repoint reports zero byte progress on all {deltas} reported lanes")


def test_details_are_opt_in():
    with committed_progress_history() as refs:
        compare = f"{refs['naked']}..{refs['repointed']}"
        plain = progress_output(compare)
        detailed = progress_output("--details", compare)
    assert "ledger details" not in plain
    assert "ledger details" in detailed and "distinct RVAs" in detailed
    assert "ASM-backed rows:" in detailed and "ASM-bearing files:" in detailed
    assert re.search(r"matched rows:\s+2\s+->\s+3\b", detailed), detailed
    assert re.search(r"distinct RVAs:\s+2\s+->\s+2\b", detailed), detailed
    print("PASS ledger diagnostics require --details")


def test_source_lanes_partition_claims_and_exclude_dumps():
    """Provenance lanes must cover every claimed byte exactly once, and only
    human-written source may land in the recovered lane."""
    matched, notes = {}, {}
    for name, rva, size, source, note in (
        ("authored", 0x1000, 10, "Code/GameEngine/Source/a.cpp", ""),
        ("vendored", 0x1010, 10, "Code/Libraries/Source/Lua/l.c", ""),
        ("gen-noted", 0x1020, 10, "Code/GameEngine/Source/b.cpp", "gen-thunk;"),
        ("gen-path", 0x1030, 10, "Code/gen_small/uw_gen_001.cpp", ""),
        ("lib", 0x1040, 10, "vendor/d3dx9/d3dx9.lib", ""),
        ("dump", 0x1050, 10, "Code/gen_asm/d_001050.asm", "gen-dump;"),
        ("emit", 0x1060, 10, "Code/GameEngine/Source/c.cpp", ""),
        # An ICF alias of the authored row, claimed again as a dump: the byte
        # is credited once, to the claim that says the most about it.
        ("alias", 0x1000, 10, "Code/gen_asm/d_001000.asm", "gen-dump;"),
    ):
        matched.update(row(name, rva, size, source))
        notes[(name, f"0x{rva:X}")] = note

    split = progress.source_split(matched, notes, 0x1000, 200,
                                  naked_rows={("emit", "0x1060")})
    assert split == {"authored": 10, "vendored": 10, "generated": 20,
                     "library": 10, "data": 0, "assembly": 0, "dump": 20, "recovered": 20}, split
    stats = progress.coverage(matched, 0x1000, 200, {("emit", "0x1060")})
    assert sum(split[lane] for lane in progress.SOURCE_LANES) == stats["exact"]
    print("PASS provenance lanes partition claimed bytes; dumps excluded")


def test_zero_hour_reference_source_is_not_authored():
    """A row compiled out of the pristine Zero Hour tree is EA's source, not ours.

    BFME 2 reaches that tree through its BFME 1 submodule. Cover both layouts:
    progress compares recorded ledger paths, so the historical spelling must
    remain vendored after the submodule moves its reference tree into inputs/.
    Reclassifying source must not change the recovered or rebuildable totals.
    """
    roots = (
        "reference/open-bfme-1/reference/CnC_Generals_Zero_Hour",
        "reference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour",
    )
    for root in roots:
        zh = root + "/GeneralsMD/Code/GameEngine/Source/"
        source = zh + "GameClient/GUI/ControlBar/ControlBar.cpp"
        assert progress.source_lane(source, "", False) == "vendored", root
        assert progress.source_lane(source, "gen-alias;", False) == "generated", root
        assert progress.source_lane(source, "", True) == "dump", root
        assert progress.source_lane(root + "-local/x.cpp", "", False) == "authored", root

        matched, notes = {}, {}
        for name, rva, size, source in (
            ("zh-twin", 0x1000, 10, zh + "Common/x.cpp"),
            ("ours", 0x1010, 10, "Code/GameEngine/Source/Common/y.cpp"),
        ):
            matched.update(row(name, rva, size, source))
            notes[(name, f"0x{rva:X}")] = ""
        split = progress.source_split(matched, notes, 0x1000, 100)
        assert split["vendored"] == 10 and split["authored"] == 10, (root, split)
        assert progress.rebuildable(split) == 20, (root, split)
        assert progress.decompiled(split) == 20, (root, split)

    # The project's shims and game source remain authored.
    assert progress.source_lane("reference/shims/controlbar/x.cpp", "", False) == "authored"
    assert progress.source_lane("Code/GameEngine/Source/Common/x.cpp", "", False) == "authored"
    print("PASS both Zero Hour reference layouts land in the vendored lane")


def test_gamespy_sdk_c_is_vendored_but_the_cpp_beside_it_is_not():
    """GameSpy's SDK is the one vendored tree that shares a directory with the
    game's own code, so the lane split has to key on extension there.

    Before this was fixed, every GameSpy .c row scored as "C++ we wrote" and
    90,073 bytes of a 2004 third-party SDK inflated the authored figure -- the
    exact defect d57cc1fcf named when it routed LZHCompress. The .cpp assertion
    is the half that keeps the fix from over-reaching: PeerDefs.cpp and the
    thunks beside gp.c ARE this project's.
    """
    root = "Code/GameEngine/Source/GameNetwork/GameSpy/"
    assert progress.source_lane(root + "gp/gp.c", "", False) == "vendored"
    assert progress.source_lane(root + "nonport.c", "", False) == "vendored"
    assert progress.source_lane(root + "PeerDefs.cpp", "", False) == "authored"
    assert progress.source_lane(root + "gp/gp.c", "gen-alias;", False) == "generated"

    # ...and the headline may not move when a byte changes lane, because
    # rebuildable() spans authored and vendored alike.
    matched, notes = {}, {}
    for name, rva, size, source in (
        ("sdk-c", 0x1000, 10, root + "qr2/qr2.c"),
        ("game-cpp", 0x1010, 10, root + "GSConfig.cpp"),
    ):
        matched.update(row(name, rva, size, source))
        notes[(name, f"0x{rva:X}")] = ""
    split = progress.source_split(matched, notes, 0x1000, 100)
    assert split["vendored"] == 10 and split["authored"] == 10, split
    assert progress.rebuildable(split) == 20, split
    print("PASS GameSpy SDK .c routes to the vendored lane; .cpp stays authored")


def test_dump_pass_moved_zero_recovered_bytes():
    """New dump coverage must not gain source credit; a clean conversion must."""
    with committed_progress_history() as refs:
        start, size = progress.retail_text()
        figures, exact = [], []
        for state in ("repointed", "dumped", "recovered"):
            ref = refs[state]
            rows = progress.matched_at(ref)
            naked = progress.naked_cpp_rows_at(rows, ref)
            figures.append(progress.real_split(rows, progress.notes_at(ref), start, size, naked))
            exact.append(progress.coverage(rows, start, size, naked)["exact"])
        before, dumped, recovered = figures
        assert progress.decompiled(before) == progress.decompiled(dumped) == 4, figures
        assert dumped["dump"] - before["dump"] == 4, figures
        assert exact == [8, 12, 12], exact
        assert progress.decompiled(recovered) - progress.decompiled(dumped) == 4, figures
        assert dumped["dump"] - recovered["dump"] == 4, figures
    print("PASS dumps add exact coverage only; clean source gains recovered credit")


def test_readme_headline_is_a_recovered_figure():
    """The card's byte figures -- byte match, linking and hand-written code --
    may not exceed what progress.py prints for them (BYTE-MATCHED, LINKING and
    AUTHORED C++).

    A README that lags is fine (contributors land continuously, the census is
    daily) and a README that flatters is not.
    """
    printed = subprocess.run([sys.executable, str(TOOL)],
                             cwd=ROOT, capture_output=True, text=True, check=True).stdout.splitlines()

    def figure(prefix):
        line = next(l for l in printed if l.startswith(prefix))
        # "not measured" (no census yet) is 0%: the badge may not claim more.
        return float(line.split("(")[1].split("%")[0]) if "(" in line else 0.0

    tool = {"rebuilt": figure("BYTE-MATCHED "), "authored": figure("AUTHORED C++ "), "linking": figure("LINKING ")}
    readme = (ROOT / "README.md").read_text(encoding="utf-8")
    assert "docs/progress.svg" in readme, "README no longer shows the progress badge"
    svg = (ROOT / "docs/progress.svg").read_text(encoding="utf-8")
    title = re.search(r"<title[^>]*>BFME 2 · Road to a finished decomp: ([\d.]+)% byte match, "
                      r"(?:([\d.]+)% linking|linking not measured)", svg)
    assert title, "the badge's title no longer states its figures"
    written = re.search(r"<desc[^>]*>[^<]*hand-written code ([\d.]+)%", svg)
    assert written, "the badge's description no longer states hand-written code"
    badge = {"rebuilt": float(title.group(1)), "authored": float(written.group(1)),
             "linking": float(title.group(2) or 0)}
    for key, value in badge.items():
        assert value <= tool[key] + 0.005, (
            f"README says {value}% {key} where progress.py says {tool[key]}%; it may lag, never flatter")
    assert badge["rebuilt"] >= tool["rebuilt"] - 5.0, (
        f"README says {badge['rebuilt']}% rebuilt where the project is at {tool['rebuilt']}%: more than five points stale")
    print(f"PASS README {badge} against {tool}")


def test_readme_never_overstates_coverage():
    """The README quotes ONE headline: what rebuilds from what we hold. No
    figure in it may exceed that, and the headline itself must be the tool's.

    The project reports a single number on purpose. Anything a reader could
    mistake for it — total-claimed, which counts byte-true dumps of retail —
    flatters by ~56 points, so the guard is that nothing quoted goes above the
    headline. Equality with the headline is asserted (it is one pinned number
    now, and a stale headline is the failure this test exists to catch), but
    the other figures are only bounded: they are allowed to lag.
    """
    printed = subprocess.run([sys.executable, str(TOOL)],
                             cwd=ROOT, capture_output=True, text=True, check=True).stdout
    line = next(l for l in printed.splitlines()
                if l.startswith("BYTE-MATCHED "))
    rebuilds = float(line.split("(")[1].split("%")[0])

    readme = (ROOT / "README.md").read_text(encoding="utf-8")
    readme += (ROOT / "docs/progress.svg").read_text(encoding="utf-8")
    quoted = sorted(float(v) for v in re.findall(r"(\d+\.\d+)%", readme))
    assert quoted, "README quotes no coverage figure at all"
    for value in quoted:
        assert value <= rebuilds + 0.005, (
            f"README quotes {value}%, above the {rebuilds}% that rebuilds from "
            f"what we hold. The bigger figures the tool prints -- total claimed, "
            f"the dump share -- are not coverage, and quoting one here reads as "
            f"if it were")
    print(f"PASS all {len(quoted)} README figures stay at or under {rebuilds}%")


def main():
    test_marker_delta_handles_legacy_source_encoding()
    test_union_and_cpp_precedence()
    test_text_clipping()
    test_unknown_source_suffix_fails()
    test_naked_cpp_to_clean_cpp_shifts_category_only()
    test_bare_asm_emit_spray_is_asm_but_partial_emit_is_cpp()
    test_mixed_file_marks_only_proven_naked_row()
    test_naked_body_callee_is_not_signature_evidence()
    test_naked_declaration_is_not_a_body()
    test_signature_prefix_does_not_match_another_method()
    test_c_naked_signature_matches_decorated_row()
    test_live_naked_and_clean_rows_are_distinguished()
    test_naked_repoint_is_zero_byte_progress()
    test_details_are_opt_in()
    test_source_lanes_partition_claims_and_exclude_dumps()
    test_zero_hour_reference_source_is_not_authored()
    test_gamespy_sdk_c_is_vendored_but_the_cpp_beside_it_is_not()
    test_dump_pass_moved_zero_recovered_bytes()
    test_readme_headline_is_a_recovered_figure()
    test_readme_never_overstates_coverage()
    print("ALL TESTS PASSED")


if __name__ == "__main__":
    main()
