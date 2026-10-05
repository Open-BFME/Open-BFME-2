"""Declared-name counting, with BFME1's placeholder policy."""
import subprocess
import sys
from pathlib import Path

import pytest

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import name_metric as names


@pytest.mark.parametrize("kind, name, bad", [
    ("file", "Rva00123456", True), ("type", "BfmeThing", True),
    ("function", "d_00123456", True), ("member", "m_field_0x20", True),
    ("local", "local_20", True), ("param", "param_1", True),
    ("param", "tmp", True), ("local", "t2", True), ("local", "x", True),
    ("local", "i", False), ("local", "j", False), ("local", "k", False),
    ("member", "m_health", False), ("param", "targetPosition", False),
    ("function", "getHealth", False), ("file", "Generals", False),
])
def test_placeholder_policy(kind, name, bad):
    assert bool(names.weak(kind, name)) is bad


def test_all_declaration_kinds_and_no_comments_strings_or_padding():
    source = '''
// class Rva00123456 { int fake; };
const char *label = "int local_20;";
struct Unit {
    int m_health;
    char m_pad[4];
    void update(Unit *targetPosition) {
        int tmp = 0;
        int health = m_health;
    }
};
enum Side { Good, Evil };
extern int thePlayer;
'''
    assert names.declared("Code/Unit.cpp", source) == [
        ("file", "Unit"), ("type", "Unit"), ("member", "m_health"),
        ("type", "Side"), ("function", "update"), ("param", "targetPosition"),
        ("local", "tmp"), ("local", "health"),
        ("global", "label"), ("global", "thePlayer"),
    ]


def track(root, paths):
    subprocess.run(["git", "init", "-q", str(root)], check=True)
    for rel, text in paths.items():
        path = root / rel
        path.parent.mkdir(parents=True, exist_ok=True)
        path.write_text(text)
    subprocess.run(["git", "add", "--", *paths], cwd=root, check=True)


def test_only_tracked_source_counts_and_globals_are_deduplicated(tmp_path, monkeypatch):
    track(tmp_path, {
        "Code/First.cpp": "extern int thePlayer;\n",
        "Code/Second file.h": "extern int thePlayer;\n",
        "Code/gen_asm/Unknown.cpp": "int fake;\n",
        "Code/gen_small/Unknown.cpp": "int fake;\n",
        "Code/readme.txt": "int fake;\n",
        "reference/Donor.cpp": "int fake;\n",
    })
    (tmp_path / "Code/Untracked.cpp").write_text("int fake;\n")
    monkeypatch.setattr(names, "ROOT", tmp_path)
    assert names.readable() == (3, 0)  # two files, one global


def test_missing_tracked_source_aborts(tmp_path, monkeypatch):
    track(tmp_path, {"Code/Unit.cpp": "int health;\n"})
    (tmp_path / "Code/Unit.cpp").unlink()
    monkeypatch.setattr(names, "ROOT", tmp_path)
    with pytest.raises(FileNotFoundError):
        names.readable()


def test_empty_scope_aborts(tmp_path, monkeypatch):
    track(tmp_path, {"README.md": "No code"})
    monkeypatch.setattr(names, "ROOT", tmp_path)
    with pytest.raises(ValueError, match="No declared names"):
        names.readable()
