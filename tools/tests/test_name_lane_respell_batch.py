"""Prepared ordinary respells retain normal blind submit and atomic application.

Each test uses its own tiny repository. Only compilation is injected; votes,
approval checks, planning, journals, ledgers and source application are real.
"""
import csv
import json
import os
import shutil
import subprocess
import sys
from pathlib import Path
from types import SimpleNamespace

import pytest

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import name_lane
import name_review
import rename


SOURCES = ("Code/Game/Forward.cpp", "Code/Game/Thunk.cpp")
OLD = ("?rva00401000@Rva00401000Forward@@UAEXH@Z",
       "?rva00401000@Rva00401000Forward@@WBM@AEXH@Z")
NEW = ("?DoXfer@Base@Particle@@UAEXAAVXfer@@@Z",
       "?DoXfer@Base@Particle@@WBM@AEXAAVXfer@@@Z")
KEYS = tuple(f"{source}|function|0x{0x401000 + i * 8:08X}|rva00401000"
             for i, source in enumerate(SOURCES))
BEFORE = ("// cl: /O1\nclass Rva00401000Forward { public: virtual void rva00401000(int); };\n"
          "void Rva00401000Forward::rva00401000(int value) {}\n")
AFTER = ("// cl: /O1\nclass Xfer;\nnamespace Particle { class Base { public: virtual void DoXfer(Xfer &); }; }\n"
         "void Particle::Base::DoXfer(Xfer &value) {}\n")


def lane(root):
    return name_lane.Lane(root, rename.Context(root, object_scan=False))


def table(root, rel):
    path = root / rel
    return list(csv.DictReader(path.open(encoding="utf-8", newline=""))) if path.exists() else []


@pytest.fixture
def tree(tmp_path, monkeypatch):
    # Publication configuration belongs to the real checkout, never this child
    # fixture. Do not change the launching shell's environment or user config.
    for key in list(os.environ):
        if key.startswith("GIT_CONFIG_"):
            monkeypatch.delenv(key)
    monkeypatch.setenv("GIT_CONFIG_NOSYSTEM", "1")
    monkeypatch.setenv("GIT_CONFIG_GLOBAL", str(tmp_path / "empty-gitconfig"))
    monkeypatch.setenv("BFME_CLAIMS", "off")
    monkeypatch.setattr(name_lane, "AGREED_CUTOFF_ROWS", 0)
    monkeypatch.setattr(name_review, "maybe_launch", lambda *_a, **_kw: None)
    files = {
        "reverse/functions.csv": "name,export_rva,target_rva,target_size,source,status,notes\n" + "".join(
            f"{old},,0x{0x401000 + i * 8:08X},8,{source},matched,\n"
            for i, (old, source) in enumerate(zip(OLD, SOURCES))),
        "reverse/symbols.csv": "name,address,notes\n",
        "reverse/data_rows.csv": "name,address,address_kind,size,section,source,status,evidence,model\n",
        "reverse/deleted_rows.csv": "name,target_rva,reason\n",
        SOURCES[0]: BEFORE,
        SOURCES[1]: BEFORE,
    }
    for rel, text in files.items():
        path = tmp_path / rel
        path.parent.mkdir(parents=True, exist_ok=True)
        path.write_bytes(text.encode())
    def git(*args):
        return subprocess.run(["git", "-C", str(tmp_path), *args], check=True, capture_output=True)
    git("init", "-q")
    git("config", "user.name", "Fixture")
    git("config", "user.email", "fixture@example.invalid")
    git("config", "core.hooksPath", str(tmp_path / "empty-hooks"))
    git("add", "--", *files)
    git("commit", "-qm", "fixture")
    build = tmp_path / "build"
    build.mkdir()
    proposals = {}
    for i, source in enumerate(SOURCES):
        proposed = build / f"after-{i}.cpp.txt"
        proposed.write_bytes(AFTER.encode())
        proposals[source] = str(proposed.relative_to(tmp_path))
    manifest = build / "respell.json"
    manifest.write_text(json.dumps(dict(version=1,
        requests=[dict(key=key, new=new) for key, new in zip(KEYS, NEW)], prepared=proposals)))
    return tmp_path, manifest


def submit(tree, session, monkeypatch, *, keys=KEYS, bind=False, answers=None, verify=None):
    root, manifest = tree
    monkeypatch.setenv("BFME_CLAIM_OWNER", f"seat-{session}")
    current = lane(root)
    args = SimpleNamespace(session=session, model="fixture-model", count=2,
                           files=list(dict.fromkeys(key.split("|")[0] for key in keys)), file=None,
                           key=list(keys), list_only=False)
    assert name_lane.cmd_next(current, args) == 0
    answer = root / "build" / f"answers-{session}.json"
    mapping = {}
    for key in keys:
        mapping.setdefault(key.split("|")[0], {})[key] = (answers or {}).get(key, "DoXfer")
    answer.write_text(json.dumps(mapping))
    args = SimpleNamespace(session=session, model="fixture-model", answer=str(answer),
                           auto_workflow=True, respell_batch=str(manifest) if bind else None)
    return name_lane.cmd_submit(lane(root), args, verify=verify or (lambda _ctx, _sources: True),
                                checks=lambda _ctx, _plan: [])


def apply(root, *, keys=KEYS, verify=None, **kw):
    args = SimpleNamespace(key=list(keys), retry_blocked=False, only_labels=None, lead=2,
                           min_models=1, claim=False, limit=None, **kw)
    return name_lane.cmd_apply(lane(root), args, verify=verify or (lambda _ctx, _sources: True),
                               checks=lambda _ctx, _plan: [])


def unchanged(root):
    assert all((root / source).read_bytes() == BEFORE.encode() for source in SOURCES)
    assert [r["name"] for r in table(root, "reverse/functions.csv")] == list(OLD)
    assert not table(root, rename.NAME_BASIS)


def test_normal_two_voter_submit_applies_full_pair_once(tree, monkeypatch):
    root, _manifest = tree
    calls, dispatches = [], []
    monkeypatch.setattr(name_review, "maybe_launch", lambda *a, **kw: dispatches.append(kw))
    def verify(_ctx, sources):
        calls.append(set(sources))
        assert all((root / source).read_bytes() == AFTER.encode() for source in SOURCES)
        assert [r["name"] for r in table(root, "reverse/functions.csv")] == list(NEW)
        return True
    assert submit(tree, "one", monkeypatch, bind=True, verify=verify) == 0
    unchanged(root)
    assert submit(tree, "two", monkeypatch, verify=verify) == 0
    assert calls == [set(SOURCES)]
    assert all(lane(root).state()[key]["status"] == "landed" for key in KEYS)
    assert len(table(root, rename.NAME_BASIS)) == 2
    assert len(table(root, rename.DELETED)) == 2
    assert len(table(root, name_lane.VOTES)) == 4
    assert len(dispatches) == 2 and all(d["apply_new"] for d in dispatches)


def test_one_approval_waits_and_fresh_last_key_completes_group(tree, monkeypatch):
    root, _ = tree
    submit(tree, "one", monkeypatch, bind=True)
    submit(tree, "two", monkeypatch, keys=KEYS[:1])
    unchanged(root)
    assert lane(root).state()[KEYS[0]]["status"] == "agreed"
    submit(tree, "three", monkeypatch, keys=KEYS[1:])
    assert [r["name"] for r in table(root, "reverse/functions.csv")] == list(NEW)


def test_automatic_independent_reviewer_keeps_prepared_group_blind_and_atomic(tree, monkeypatch):
    root, _ = tree
    submit(tree, "one", monkeypatch, bind=True)
    name_review.save_json(name_review.config_path(lane(root)), dict(
        enabled=True, worker="independent-reviewer", model="gpt-6.1-sol", count=2, max_keys=1,
        timeout=30, max_chars=150000, resolve_disagreements=False))
    calls = []
    def runner(packet, _config, _job):
        assert "DoXfer" not in json.dumps(packet)
        return {"answers": [dict(key=item["key"], name="DoXfer", reason="Transfers this object's state.")
                            for item in packet["targets"]]}
    name_review.dispatch(lane(root), runner=runner, apply_new=True,
                         verify=lambda _ctx, sources: calls.append(set(sources)) or True,
                         checks=lambda _ctx, _plan: [])
    assert calls == [set(SOURCES)]
    assert [r["name"] for r in table(root, "reverse/functions.csv")] == list(NEW)
    assert len({r["worker"] for r in table(root, name_lane.VOTES)}) == 2


@pytest.mark.parametrize("damage", ["manifest-missing", "manifest-changed", "proposal-missing",
                                   "proposal-changed", "source-changed"])
def test_stale_operation_never_falls_back_to_identifier_application(tree, monkeypatch, damage, capsys):
    root, manifest = tree
    submit(tree, "one", monkeypatch, bind=True)
    if damage == "manifest-missing":
        manifest.unlink()
    elif damage == "manifest-changed":
        manifest.write_text(manifest.read_text() + "\n")
    elif damage == "proposal-missing":
        (root / "build/after-0.cpp.txt").unlink()
    elif damage == "proposal-changed":
        (root / "build/after-0.cpp.txt").write_text(AFTER + "// changed\n")
    else:
        (root / SOURCES[0]).write_text(BEFORE + "// changed\n")
    before = {source: (root / source).read_bytes() for source in SOURCES}
    submit(tree, "two", monkeypatch)
    assert {source: (root / source).read_bytes() for source in SOURCES} == before
    assert [r["name"] for r in table(root, "reverse/functions.csv")] == list(OLD)
    assert not table(root, rename.NAME_BASIS)
    assert "prepared respell" in capsys.readouterr().out


def test_different_independent_identifier_is_not_silently_replaced(tree, monkeypatch, capsys):
    root, _ = tree
    answers = {key: "TransferState" for key in KEYS}
    submit(tree, "one", monkeypatch, bind=True, answers=answers)
    submit(tree, "two", monkeypatch, answers=answers)
    unchanged(root)
    assert "does not match the independent approval" in capsys.readouterr().out
    assert all(lane(root).state()[key]["new"] == "TransferState" for key in KEYS)


def test_combined_verification_failure_restores_entire_pair(tree, monkeypatch):
    root, _ = tree
    submit(tree, "one", monkeypatch, bind=True)
    submit(tree, "two", monkeypatch, verify=lambda _ctx, _sources: False)
    unchanged(root)


def test_registered_group_stays_atomic_under_per_file_application(tree, monkeypatch):
    root, _ = tree
    submit(tree, "one", monkeypatch, bind=True)
    # Record the two new approvals through normal submit but let an explicit
    # one-key cap withhold this indivisible two-key operation.
    original_apply = name_lane.cmd_apply
    def limited(lane_, args, **kw):
        args.limit = 1
        return original_apply(lane_, args, **kw)
    with monkeypatch.context() as patch:
        patch.setattr(name_lane, "cmd_apply", limited)
        submit(tree, "two", monkeypatch)
    unchanged(root)
    calls = []
    apply(root, keys=KEYS[:1], per_file=True, verify=lambda _ctx, sources: calls.append(sources) or True)
    assert len(calls) == 1 and set(calls[0]) == set(SOURCES)


def test_ordinary_submit_still_applies_identifier_only(tree, monkeypatch):
    root, _ = tree
    # The ordinary identifier rewrite correctly refuses two distinct functions
    # sharing the old word. Give this control case an unrelated second word.
    path = root / SOURCES[1]
    path.write_bytes(BEFORE.replace("rva00401000", "rva00401008").encode())
    ledger = root / "reverse/functions.csv"
    ledger.write_bytes(ledger.read_bytes().replace(OLD[1].encode(), OLD[1].replace("rva00401000", "rva00401008").encode()))
    submit(tree, "one", monkeypatch, keys=KEYS[:1])
    submit(tree, "two", monkeypatch, keys=KEYS[:1])
    assert "rva00401000" not in (root / SOURCES[0]).read_text()
    assert "DoXfer" in (root / SOURCES[0]).read_text()
    assert table(root, "reverse/functions.csv")[0]["name"] == rename.rename_function_symbol(OLD[0], "DoXfer")


def test_corrupt_binding_registry_refuses_all_application(tree, monkeypatch):
    root, _ = tree
    submit(tree, "one", monkeypatch, bind=True)
    name_lane.respell_registry_path(lane(root)).write_text("{broken")
    with pytest.raises(SystemExit, match="registry refuses"):
        apply(root)
    unchanged(root)


def test_registration_rejects_a_retarget_without_generic_fallback(tree, monkeypatch):
    root, manifest = tree
    submit(tree, "one", monkeypatch, bind=True)
    data = json.loads(manifest.read_text())
    data["requests"][0]["new"] = NEW[0].replace("@Base@", "@OtherBase@")
    manifest.write_text(json.dumps(data))
    with pytest.raises(SystemExit, match="already bound"):
        submit(tree, "two", monkeypatch, bind=True)
    unchanged(root)


def test_failed_validation_does_not_register_or_vote(tree, monkeypatch):
    root, manifest = tree
    data = json.loads(manifest.read_text())
    data["requests"][0]["key"] = KEYS[0].replace("00401000", "00409999")
    manifest.write_text(json.dumps(data))
    with pytest.raises(SystemExit, match="ordinary function key"):
        submit(tree, "one", monkeypatch, bind=True)
    assert not name_lane.respell_registry_path(lane(root)).exists()
    assert not table(root, name_lane.VOTES)
    unchanged(root)


def test_build_cleanup_preserves_intent_and_cannot_trigger_generic_application(tree, monkeypatch, capsys):
    root, _ = tree
    submit(tree, "one", monkeypatch, bind=True)
    submit(tree, "two", monkeypatch, keys=KEYS[:1])
    registry = name_lane.respell_registry_path(lane(root))
    scratch = (root / "build").resolve()
    assert scratch.parent == root.resolve()
    assert not registry.is_relative_to(scratch)
    shutil.rmtree(scratch)
    assert registry.exists()
    submit(tree, "three", monkeypatch, keys=KEYS[1:])
    unchanged(root)
    assert "inputs are missing or stale" in capsys.readouterr().out


def test_structural_preparation_does_not_reuse_other_selected_approval_fingerprints(tree, monkeypatch):
    root, _ = tree
    other_key = f"{SOURCES[0]}|function|0x00402000|rva00402000"
    extra = "\nvoid rva00402000() {}\n"
    (root / SOURCES[0]).write_bytes((BEFORE + extra).encode())
    ledger = root / "reverse/functions.csv"
    ledger.write_bytes(ledger.read_bytes() +
        f"?rva00402000@@YAXXZ,,0x00402000,1,{SOURCES[0]},matched,\n".encode())
    (root / "build/after-0.cpp.txt").write_bytes((AFTER + extra).encode())
    subprocess.run(["git", "-C", str(root), "add", "--", SOURCES[0], "reverse/functions.csv"],
                   check=True, capture_output=True)
    subprocess.run(["git", "-C", str(root), "commit", "-qm", "fixture extra approval"],
                   check=True, capture_output=True)
    keys = KEYS + (other_key,)
    answers = {other_key: "ResetTrace"}
    calls = []
    submit(tree, "one", monkeypatch, keys=keys, answers=answers, bind=True)
    submit(tree, "two", monkeypatch, keys=keys, answers=answers,
           verify=lambda _ctx, sources: calls.append(set(sources)) or True)
    assert calls == [set(SOURCES)]
    assert "rva00402000" in (root / SOURCES[0]).read_text()
    assert lane(root).state()[other_key]["status"] == "agreed"
    assert len([row for row in table(root, name_lane.VOTE_SOURCES) if row["key"] == other_key]) == 2
    apply(root, keys=[other_key])
    assert lane(root).state()[other_key]["status"] == "source-changed"
    assert "ResetTrace" not in (root / SOURCES[0]).read_text()
