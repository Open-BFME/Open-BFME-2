"""gen_dump --orphans: a Code/gen_asm/ file is ORPHAN only when nothing but records names it."""
import subprocess
import sys
from pathlib import Path

import pytest

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import gen_dump

ASM = "Code/gen_asm/d_00000100.asm"
PROC = "?d_00000100@@YAXXZ"
DUMP = (".386\n.model flat\n_TEXT SEGMENT\npublic {p}\n{p} PROC\n    db 0C3h\n{p} ENDP\n"
        "_TEXT ENDS\nEND\n").format(p=PROC)
INPUTS = {
    "reverse/functions.csv": "name,export_rva,target_rva,target_size,source,status,notes\n"
                             "?kept@@YAXXZ,,0x00000200,1,Code/Kept.cpp,matched,\n",
    "reverse/data_rows.csv": "name,address,address_kind,size,section,source,status,evidence,model\n",
    "reverse/symbols.csv": "name,address,notes\n",
    "reverse/pin_consistency_baseline.csv": "# PIN-CONSISTENCY BACKLOG\n",
    "reverse/export_aliases.csv": "export,target,notes\n",
    "reverse/body_owners.csv": "target_rva,name,target_size,source,evidence\n",
    "reverse/hatch_baseline.tsv": f"# mode: enforce\nasm_bytes\t{ASM}\t*\t1\n",
    "Code/Kept.cpp": "void kept() {}\n",
    ASM: DUMP,
}


@pytest.fixture
def repo(tmp_path):
    def write(path, text):
        target = tmp_path / path
        target.parent.mkdir(parents=True, exist_ok=True)
        target.write_text(text, encoding="utf-8")
        subprocess.run(["git", "add", path], cwd=tmp_path, check=True)

    subprocess.run(["git", "init", "-q"], cwd=tmp_path, check=True)
    for path, text in INPUTS.items():
        write(path, text)
    return tmp_path, write


def report(root):
    lines, status = gen_dump.orphan_report(root)
    assert status == 0, lines
    return lines


def test_unnamed_file_is_orphan_with_its_hatch_bytes(repo):
    root, _ = repo
    lines = report(root)
    assert lines[0] == f"ORPHAN {ASM} asm_bytes=1"
    assert lines[-1] == "total 1 orphaned 1 referenced 0 asm_bytes_orphaned 1"


@pytest.mark.parametrize("path,text", [
    # Negative controls: each of these keeps the file alive.
    ("reverse/functions.csv", INPUTS["reverse/functions.csv"] + f"{PROC},,0x00000100,1,{ASM},matched,gen-dump\n"),
    ("reverse/functions.csv", INPUTS["reverse/functions.csv"] + f"{PROC},,0x00000100,1,Code/Other.cpp,matched,\n"),
    ("reverse/symbols.csv", INPUTS["reverse/symbols.csv"] + f"{PROC},0x00000100,pin\n"),
    ("reverse/export_aliases.csv", INPUTS["reverse/export_aliases.csv"] + f"_export,{PROC},alias\n"),
    ("Code/Caller.cpp", f'extern "C" void d_00000100();\nvoid caller() {{ d_00000100(); }}\n'),
    ("Code/Caller.cpp", f'#pragma comment(linker, "/alternatename:_x={PROC}")\n'),
    ("build.sh", f"./tools/build.py {ASM}\n"),
    ("tools/some_tool.py", f'DUMP = "{ASM}"\n'),
    ("tools/tests/test_opens_dump.py", f'open("{ASM}")\n'),
    # Review probes (2026-11-10): each was classed a record before the fix.
    ("tools/tests/test_opens_dump.py", 'open(ROOT / "Code" / "gen_asm" / "d_00000100.asm")\n'),
    ("tools/tests/test_opens_dump.py", f'DIR = "Code/gen_asm"\nLINES = ["{PROC} PROC"]\n'),
    ("tools/tests/test_opens_dump.py", 'directory = ROOT / "Code" / ("gen" + "_asm")\nname = "d_00000100"\n'
                                       'open(directory / (name + ".asm"))\n'),
    # No fixture exemption: any stem or PROC spelling under tools/tests/ is a reference.
    ("tools/tests/test_fixture.py", f'LINES = ["{PROC} PROC", "    db 0C3h"]\n'),
    ("tools/tests/test_fixture.py", f'# a gen_asm lane test\ndef test_gen_asm_x():\n'
                                    f'    row("Code/gen_asm/d_00000200.asm")\n    LINES = ["{PROC} PROC"]\n'),
    ("tools/tests/test_fixture.py", "# d_00000100 in a comment\n"),
    ("Code/Caller.cpp", "/* explanation */ extern void d_00000100();\n"),
    ("Code/Caller.cpp", 'const char *u = "https://host"; void f() { d_00000100(); }\n'),
])
def test_a_reference_keeps_the_file(repo, path, text):
    root, write = repo
    write(path, text)
    lines = report(root)
    assert lines[0].startswith(f"REFERENCED {ASM} by "), lines
    assert lines[-1] == "total 1 orphaned 0 referenced 1 asm_bytes_orphaned 0"


@pytest.mark.parametrize("path,text", [
    # Records: provenance and history name the file without using it.
    ("reverse/functions.csv", INPUTS["reverse/functions.csv"]
     + f"?real@@YAXXZ,,0x00000100,1,Code/Real.cpp,matched,clean C++ replacing {ASM}\n"),
    ("Code/Real.cpp", f"// The body carried only a byte dump in {ASM}.\nvoid real() {{}}\n"),
    ("Code/Real.cpp", f"void real() {{}}  // was {PROC}\n"),
    ("reverse/deleted_rows.csv", f"name,target_rva,reason\n{PROC},0x00000100,retracted\n"),
    ("reverse/re_attempts.log", f"{PROC}\t0x00000100\t1\tconverted\tlanded\n"),
    ("reverse/name_tiers.csv", f"name,target_rva,name_tier,evidence\n{PROC},0x00000100,address,placeholder\n"),
    ("reverse/wb_name_leads.csv", "target_rva,current_name,current_kind,wb_name,wb_file,score,evidence\n"
                                  "0x00000100,d_00000100,PLACEHOLDER,,,1.0,callgraph\n"),
    ("docs/note.md", f"{ASM}\n"),
    ("Code/Real.cpp", f"/* was {PROC} */ void real() {{}}\n"),
    # A test naming only other dumps does not hold this one.
    ("tools/tests/test_fixture.py", 'row("Code/gen_asm/d_00000200.asm")\nLINES = ["?d_00000200@@YAXXZ PROC"]\n'),
])
def test_a_record_does_not(repo, path, text):
    root, write = repo
    write(path, text)
    assert report(root)[0].startswith(f"ORPHAN {ASM} asm_bytes=1")


def test_another_hatch_line_naming_the_file_is_a_reference(repo):
    root, write = repo
    write("reverse/hatch_baseline.tsv", INPUTS["reverse/hatch_baseline.tsv"] + f"pin\tCode/X.cpp\t{PROC}\t1\n")
    assert report(root)[0].startswith(f"REFERENCED {ASM} by reverse/hatch_baseline.tsv:")


def test_an_unreadable_input_exits_2(repo):
    root, _ = repo
    (root / "reverse/symbols.csv").unlink()
    lines, status = gen_dump.orphan_report(root)
    assert status == 2 and "reverse/symbols.csv" in lines[0]
