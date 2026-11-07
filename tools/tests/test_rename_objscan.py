"""A class rename's object scan (false-reject 0x004E156B, 73eaea475f).

Renaming Rva003B7BA0Record -> EnableRegionRecord scoped two symbols: the class's
destructor and `?append@Rva003B7BA0Owner@@QAEXPAVRva003B7BA0Record@@@Z`, a member of
another class that takes it. For a source without a current object the scan fell back
to each symbol's own identifier, so every stale unit spelling `append` counted (208).
A class rename now searches the class itself there; a current object is still read by
its exact symbol names."""
import hashlib
import json
import subprocess
import sys
from pathlib import Path

import pytest

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
sys.path.insert(0, str(Path(__file__).resolve().parent))
import name_dependents  # noqa: E402
import rename  # noqa: E402
from rename import Refusal  # noqa: E402
from test_name_dependents import coff  # noqa: E402

OLD = "Rva00401000Record"
OWNER = "Code/Game/Spawn.cpp"
DTOR = "??1Rva00401000Record@@UAE@XZ"
APPEND = "?append@Owner@@QAEXPAVRva00401000Record@@@Z"
OTHERS = [f"Code/Game/Other{i:02d}.cpp" for i in range(30)]
SPAWN = ("// cl: /O2\nclass Rva00401000Record { public: virtual ~Rva00401000Record(); int m; };\n"
         "Rva00401000Record::~Rva00401000Record() {}\n"
         "class Owner { public: void append(Rva00401000Record *r); Rva00401000Record *m_last; };\n"
         "void Owner::append(Rva00401000Record *r) { m_last = r; }\n")


@pytest.fixture
def repo(tmp_path, monkeypatch):
    monkeypatch.setenv("BFME_CLAIMS", "off")
    monkeypatch.setattr(rename, "check_agreement", lambda *args, **kwargs: None)
    files = {OWNER: SPAWN}
    rows = [f"{DTOR},,0x00401000,8,{OWNER},matched,", f"{APPEND},,0x00401010,8,{OWNER},matched,"]
    for i, rel in enumerate(OTHERS):          # an unrelated append in every one, objects all stale
        files[rel] = f"// cl: /O2\nstruct Str{i} {{ void append(int); }};\nvoid f{i}(Str{i} &s) {{ s.append(1); }}\n"
        rows.append(f"?f{i}@@YAXAAUStr{i}@@@Z,,0x{0x00402000 + 0x10 * i:08X},8,{rel},matched,")
    files.update({
        "reverse/functions.csv": "name,export_rva,target_rva,target_size,source,status,notes\n" + "\n".join(rows) + "\n",
        "reverse/symbols.csv": "name,address,notes\n",
        "reverse/data_rows.csv": "name,address,address_kind,size,section,source,status,evidence,model\n",
        "reverse/deleted_rows.csv": "name,target_rva,reason\n",
    })
    for rel, text in files.items():
        path = tmp_path / rel
        path.parent.mkdir(parents=True, exist_ok=True)
        path.write_bytes(text.encode())
    subprocess.run(["git", "init", "-q", str(tmp_path)], check=True)
    subprocess.run(["git", "-C", str(tmp_path), "add", "-A"], check=True)
    monkeypatch.setattr(rename, "ROOT", tmp_path)
    objects = {rel: [tmp_path / "obj" / (Path(rel).stem + ".obj")] for rel in [OWNER] + OTHERS}
    monkeypatch.setattr(name_dependents, "_row_objects", lambda _rows: objects)
    return tmp_path, objects


def current_object(root, objects, rel, names):
    """Give `rel` a current object (its sidecar records its text) holding `names`."""
    import build
    obj = objects[rel][0]
    obj.parent.mkdir(exist_ok=True)
    obj.write_bytes(coff([".text"] + names))
    digest = hashlib.md5((root / rel).read_bytes()).hexdigest()
    build._deps_sidecar(obj).write_text(json.dumps({"cmd": "x", "source": digest, "deps": {}}))


def plan(root, **kw):
    ctx = rename.Context(root, object_scan=True)
    return rename.plan_rename("class", ctx=ctx, name=OLD, new="EnableRegionRecord", basis="inferred",
                              evidence="agree:test", **kw)


def test_the_unrelated_member_word_used_to_list_every_stale_unit(repo):
    root, objects = repo
    found = name_dependents.dependents({APPEND}, objects, root)
    assert found == {OWNER, *OTHERS}           # each symbol's own word: the old widening


def test_a_dtor_only_class_rename_selects_only_its_real_units(repo):
    root, _objects = repo
    p = plan(root)
    assert p.verify == [OWNER]
    assert set(p.source_counts) == {OWNER}
    assert not any(rel in p.after for rel in OTHERS)


def test_a_real_stale_consumer_is_still_found_and_counted(repo):
    root, _objects = repo
    stale = OTHERS[0]
    (root / stale).write_text("// cl: /O2\nclass Rva00401000Record;\nclass Owner { public: void append(Rva00401000Record *r); };\n"
                              "void f0(Owner &o, Rva00401000Record *r) { o.append(r); }\n")
    p = plan(root)
    assert set(p.verify) == {OWNER, stale}
    with pytest.raises(Refusal, match="over --max-files 1"):
        plan(root, max_files=1)


def test_a_current_object_naming_the_symbol_without_the_word_still_refuses(repo):
    # its text reaches the class through a pasted name the rewrite cannot see
    root, objects = repo
    macro = OTHERS[1]
    (root / macro).write_text("// cl: /O2\n#define CLS(a, b) a##b\nclass CLS(Rva00401000, Record);\n"
                              "class Owner { public: void append(CLS(Rva00401000, Record) *r); };\n"
                              "void f1(Owner &o) { o.append(0); }\n")
    current_object(root, objects, macro, [APPEND])
    with pytest.raises(Refusal, match="text never spells Rva00401000Record"):
        plan(root)


def test_the_identifier_override_reads_current_objects_by_exact_names(repo):
    root, objects = repo
    current_object(root, objects, OTHERS[2], [".text", APPEND])       # its text never spells Rva00401000Record
    found = name_dependents.dependents({APPEND}, objects, root, identifier=lambda _name: OLD)
    assert found == {OWNER, OTHERS[2]}
