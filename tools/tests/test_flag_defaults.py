"""Region default flags: a `// cl:` codegen flag counts only when the tool listed it.

research/25 found the game built per project (BFME2 GameEngine /O1 /arch:SSE
/G7) while 14,768 `// cl:` lines were fitted per file. tools/flag_defaults.py
gives every Code/ TU its region's /O, /arch and /G and passes every other token
through; reverse/flag_overrides.csv, written only by the tool, is the list of
files whose own codegen flags still win.
"""
import sys
from pathlib import Path

import pytest

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import flag_defaults as fd


REGIONS = """rva_start,rva_end,opt,arch,tune,n_funcs,n_opt_evidence
0x00001000,0x00001FFF,O2,?,G6,100,40
0x00002000,0x00002FFF,O1,SSE,?,100,40
0x00003000,0x00003FFF,O2,?,G7,20000,5
"""
FUNCTIONS = """name,export_rva,target_rva,target_size,source,status,notes
a,,0x00002010,100,Code/Engine/A.cpp,matched,
b,,0x00001010,40,Code/Engine/A.cpp,matched,
c,,0x00001010,40,Code/Lib/B.cpp,matched,
d,,0x00003010,999,Code/Engine/C.cpp,matched,
e,,0x00002010,10,Code/Engine/D.cpp,matched,
"""


@pytest.fixture
def tree(tmp_path, monkeypatch):
    (tmp_path / "reverse" / "retail_inventory").mkdir(parents=True)
    (tmp_path / "reverse" / "retail_inventory" / "flag_regions.csv").write_text(REGIONS)
    (tmp_path / "reverse" / "functions.csv").write_text(FUNCTIONS)
    (tmp_path / "reverse" / "flag_overrides.csv").write_text(
        "source,flags,rows,default_lost,reason\nCode/Engine/D.cpp,-O2,1,1,region default loses rows\n")
    monkeypatch.setattr(fd, "ROOT", tmp_path)
    monkeypatch.setattr(fd, "REGIONS", tmp_path / "reverse" / "retail_inventory" / "flag_regions.csv")
    monkeypatch.setattr(fd, "FUNCTIONS", tmp_path / "reverse" / "functions.csv")
    monkeypatch.setattr(fd, "OVERRIDES", tmp_path / "reverse" / "flag_overrides.csv")
    monkeypatch.setattr(fd, "_cache", {})
    monkeypatch.delenv("FLAG_DEFAULTS", raising=False)
    return tmp_path


def test_region_replaces_codegen_flags_and_keeps_the_rest(tree):
    # A.cpp: 100 bytes in the /O1 /G7 region beat 40 in the /O2 one.
    flags = ["-O2", "-DNDEBUG", "-Ob2", "-G6", "-MD", "-EHsc", "-Ireference/x"]
    assert fd.apply(tree / "Code/Engine/A.cpp", flags) == [
        "-O1", "-arch:SSE", "-G7", "-DNDEBUG", "-Ob2", "-MD", "-EHsc", "-Ireference/x"]


def test_blend_region_adds_no_tune_or_arch_flag(tree):
    assert fd.apply(tree / "Code/Lib/B.cpp", ["-O1", "-arch:SSE", "-G7"]) == ["-O2"]


def test_listed_override_keeps_its_own_flags(tree):
    assert fd.apply(tree / "Code/Engine/D.cpp", ["-O2", "-DX"]) == ["-O2", "-DX"]


def test_unlisted_override_is_ignored(tree):
    """The positive control: before this tool an edited `// cl:` line changed codegen."""
    assert fd.apply(tree / "Code/Engine/A.cpp", ["-O2", "-G6"]) == ["-O1", "-arch:SSE", "-G7"]


def test_non_voting_region_and_foreign_sources_keep_their_line(tree):
    assert fd.apply(tree / "Code/Engine/C.cpp", ["-O1"]) == ["-O1"]   # .text$x-like region
    assert fd.apply(tree / "reference/zh/X.cpp", ["-O1"]) == ["-O1"]  # not Code/
    assert fd.apply(tree / "Code/gen_asm/X.asm", ["-O1"]) == ["-O1"]  # not C/C++


def test_kill_switch_and_forced_modes(tree, monkeypatch):
    source = tree / "Code/Engine/A.cpp"
    with fd.forced_mode("g7"):
        assert fd.apply(source, ["-O1"]) == ["-O1", "-G7"]
    with fd.forced_mode("default"):
        assert fd.apply(tree / "Code/Engine/D.cpp", ["-O2"]) == ["-O1", "-arch:SSE", "-G7"]
    monkeypatch.setenv("FLAG_DEFAULTS", "off")
    assert fd.apply(source, ["-O2"]) == ["-O2"]


def test_strip_line_keeps_line_and_non_codegen_tokens():
    assert fd.strip_line("// cl: /O1 /DNDEBUG /MD /arch:SSE /G7") == "// cl: /DNDEBUG /MD"
    assert fd.strip_line("// cl: /O2 /Ob0") == "// cl: /Ob0"
    assert fd.strip_line("// cl: /Os ") == fd.CL_PLACEHOLDER
    assert fd.strip_line('// cl: /O1 /I"a b/c" /GX') == '// cl: /I"a b/c" /GX'


def test_decide():
    current = {"source": "s", "flags": "-O2", "rows": 3, "compiled": True, "fail": []}
    green = {"compiled": True, "fail": []}
    assert fd.decide(current, green) is None
    assert fd.decide(current, {"compiled": True, "fail": ["x@1"]}) == (1, "region default loses rows")
    assert fd.decide(current, {"compiled": False, "fail": []}) == (3, "region default does not compile")
    # A row that fails under both is not the default's loss.
    assert fd.decide(dict(current, fail=["x@1"]), {"compiled": True, "fail": ["x@1"]}) is None


def test_check_flags_a_hand_edited_override(tree, capsys):
    source = tree / "Code/Engine/D.cpp"
    source.parent.mkdir(parents=True)
    source.write_text("// cl: /O2 /DNDEBUG\nint x;\n")
    assert fd.cmd_check(None) == 0
    source.write_text("// cl: /O1 /DNDEBUG\nint x;\n")
    assert fd.cmd_check(None) == 1
    assert "propose" in capsys.readouterr().out
