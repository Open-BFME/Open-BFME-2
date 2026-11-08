"""The pre-push hook keeps reverse/name_vote_sources.csv append-only and bound.

A vote's fingerprint binds only when its row is added (tools/class_gate.py). The hook
reads every commit of the outgoing range against its parent, and when it knows no remote
base (a new ref, no usable origin/master) it reads the file's whole history instead of
passing on the static ledger check alone. Round 8's probes: the real hook in a throwaway
repository, with the real class_gate behind a stub that points it at that repository."""
import hashlib
import sys
from pathlib import Path

import pytest

sys.path.insert(0, str(Path(__file__).resolve().parent))
from test_hook_fail_closed import git, push_refs, repo, run, write  # noqa: E402,F401  (the fixture)

TOOLS = Path(__file__).resolve().parents[1]
HEADER = "Code/Game/Canonical.h"
VOTES = "reverse/name_vote_sources.csv"
COLUMNS = "key,hash,worker,session,source_sha\n"


def real_class_gate(repo):
    write(repo, "tools/class_gate.py",
          f"import pathlib, sys\nsys.path.insert(0, {str(TOOLS)!r})\nimport class_gate\n"
          "class_gate.ROOT = pathlib.Path.cwd()\nraise SystemExit(class_gate.main())\n")
    write(repo, HEADER, "class Canonical {};\n")
    git(repo, "add", "--", HEADER, "tools")
    git(repo, "commit", "-qm", "fixture")
    return git(repo, "rev-parse", "HEAD"), hashlib.sha256((repo / HEADER).read_bytes()).hexdigest()


def commit_votes(repo, text, message):
    write(repo, VOTES, text)
    git(repo, "add", "--", VOTES)
    git(repo, "commit", "-qm", message)


@pytest.mark.parametrize("known", [True, False])
def test_a_fingerprint_added_then_rewritten_is_refused(repo, known):
    base, sha = real_class_gate(repo)
    row = f"{HEADER}|class||Canonical,h,w,s,{sha}\n"
    commit_votes(repo, COLUMNS + row, "append a bound fingerprint")
    commit_votes(repo, COLUMNS + row.replace(sha, "f" * 64), "rewrite it")
    result = run(repo, "pre-push", push_refs(repo, base if known else "0" * 40))
    assert result.returncode == 1, (result.stdout, result.stderr)
    assert "append-only" in result.stderr
    if not known:
        assert "no known remote base" not in result.stderr


def test_bound_appends_pass_with_no_known_base(repo):
    _base, sha = real_class_gate(repo)
    row = f"{HEADER}|class||Canonical,h,w,s,{sha}\n"
    commit_votes(repo, COLUMNS + row, "one vote")
    commit_votes(repo, COLUMNS + row + row.replace(",w,s,", ",w2,s2,"), "another")
    result = run(repo, "pre-push", push_refs(repo, "0" * 40))
    assert result.returncode == 0, (result.stdout, result.stderr)
    assert "no known remote base" in result.stderr


def test_a_local_branch_named_origin_master_is_no_base(repo):
    """The hook's base is refs/remotes/origin/master, never refs/heads/origin/master."""
    base, sha = real_class_gate(repo)
    commit_votes(repo, COLUMNS + f"{HEADER}|class||Canonical,h,w,s,{sha}\n", "a bound fingerprint")
    commit_votes(repo, COLUMNS + f"{HEADER}|class||Canonical,h,w,s,{'f' * 64}\n", "rewrite it")
    git(repo, "branch", "origin/master", "HEAD")
    result = run(repo, "pre-push", push_refs(repo, "0" * 40))
    assert result.returncode == 1 and "append-only" in result.stderr, (result.stdout, result.stderr)


# ---- a fingerprint a verified landing carried (name_lane.carry_verified_votes)

SOURCE = "Code/Game/Box.cpp"
LANDED_KEY = f"{SOURCE}|function|0x00401000|rva00401000"
SIBLING = f"{SOURCE}|member|Box|m_x"
AGREED = "reverse/name_agreed.csv"
AGREED_HEADER = "id,kind,old,new,rva,agents,key,status,detail\n"
BEFORE = "void rva00401000() {}\nint m_x;\n"
AFTER = "void sumBox() {}\nint m_x;\n"


def sha_of(text):
    return hashlib.sha256(text.encode()).hexdigest()


@pytest.fixture
def carrying(tmp_path, monkeypatch):
    """A repository where a vote at SIBLING fingerprints BEFORE, and the base to read from."""
    sys.path.insert(0, str(TOOLS))
    import class_gate
    monkeypatch.setattr(class_gate, "ROOT", tmp_path)
    git(tmp_path, "init", "-q")
    write(tmp_path, SOURCE, BEFORE)
    write(tmp_path, VOTES, COLUMNS + f"{SIBLING},h,w,s,{sha_of(BEFORE)}\n")
    write(tmp_path, AGREED, AGREED_HEADER)
    git(tmp_path, "add", "-A")
    git(tmp_path, "-c", "user.name=t", "-c", "user.email=t@t", "commit", "-qm", "the vote")
    return tmp_path, class_gate, git(tmp_path, "rev-parse", "HEAD")


LANDED_ROW = f"nl-1,function,rva00401000,sumBox,0x00401000,,{LANDED_KEY},landed,\n"


def land(root, source, rows, agreed=LANDED_ROW):
    write(root, SOURCE, source)
    with open(root / VOTES, "a", newline="\n") as f:
        f.writelines(rows)
    with open(root / AGREED, "a", newline="\n") as f:
        f.write(agreed)
    git(root, "add", "-A")
    git(root, "-c", "user.name=t", "-c", "user.email=t@t", "commit", "-qm", "the landing")


def carry(start, end):
    return f"{SIBLING},h,w,carried:{sha_of(start)}:s,{sha_of(end)}\n"


def test_a_landing_that_is_exactly_its_rename_carries(carrying):
    root, gate, base = carrying
    land(root, AFTER, [carry(BEFORE, AFTER)])
    assert gate.vote_sources_range_problems(base, "HEAD") == []


def test_the_staged_landing_is_read_the_same_way(carrying):
    root, gate, _base = carrying
    write(root, SOURCE, AFTER + "// an unrelated edit\n")
    with open(root / VOTES, "a", newline="\n") as f:
        f.write(carry(BEFORE, AFTER + "// an unrelated edit\n"))
    with open(root / AGREED, "a", newline="\n") as f:
        f.write(LANDED_ROW)
    git(root, "add", "-A")
    problems = gate.vote_sources_problems()
    assert problems and "differs by more than the renames" in problems[0]


def test_the_review_string_edit_is_refused(carrying):
    root, gate, _base = carrying
    start = 'void rva00401000() {}\nchar *s = "rva00401000";\nint m_x;\n'
    end = 'void sumBox() {}\nchar *s = "sumBox";\nint m_x;\n'
    write(root, SOURCE, start)
    write(root, VOTES, COLUMNS + f"{SIBLING},h,w,s,{sha_of(start)}\n")
    git(root, "add", "-A")
    git(root, "-c", "user.name=t", "-c", "user.email=t@t", "commit", "-qm", "the literal")
    base = git(root, "rev-parse", "HEAD")
    land(root, end, [f"{SIBLING},h,w,carried:{sha_of(start)}:s,{sha_of(end)}\n"])
    problems = gate.vote_sources_range_problems(base, "HEAD")
    assert problems and "differs by more than the renames" in problems[0]


def test_a_rename_owned_by_one_file_carries_in_another_it_touches(carrying):
    """The review's repro: the agreement's key names the owner, and B also spells the function."""
    root, gate, _base = carrying
    other = "Code/Game/User.cpp"
    other_key = f"{other}|member|User|m_y"
    other_start, other_end = "void rva00401000();\nint m_y;\n", "void sumBox();\nint m_y;\n"
    write(root, other, other_start)
    with open(root / VOTES, "a", newline="\n") as f:
        f.write(f"{other_key},h,w,s,{sha_of(other_start)}\n")
    git(root, "add", "-A")
    git(root, "-c", "user.name=t", "-c", "user.email=t@t", "commit", "-qm", "another file's vote")
    base = git(root, "rev-parse", "HEAD")
    write(root, other, other_end)
    land(root, AFTER, [carry(BEFORE, AFTER), f"{other_key},h,w,carried:{sha_of(other_start)}:s,{sha_of(other_end)}\n"])
    assert gate.vote_sources_range_problems(base, "HEAD") == []


def test_two_landings_in_one_commit_carry_through_the_text_between(carrying):
    root, gate, base = carrying
    final = AFTER.replace("m_x", "m_width")
    second = f"nl-2,member,m_x,m_width,,,{SOURCE}|member|Box|m_x2,landed,\n"
    land(root, final, [carry(BEFORE, AFTER), carry(AFTER, final)], agreed=LANDED_ROW + second)
    assert gate.vote_sources_range_problems(base, "HEAD") == []


@pytest.mark.parametrize("source,rows,agreed,message", [
    (AFTER + "// an unrelated edit\n", [carry(BEFORE, AFTER + "// an unrelated edit\n")], LANDED_ROW, "differs by more"),
    (AFTER, [carry(BEFORE, AFTER)], "", "differs by more"),                     # no landing recorded
    (AFTER, [carry(BEFORE, AFTER)], LANDED_ROW.replace(",landed,", ",agreed,"), "differs by more"),
    (AFTER, [carry(BEFORE + "// older\n", AFTER)], LANDED_ROW, "does not run"),  # starts from another text
    (AFTER, [carry(BEFORE, BEFORE + "// elsewhere\n")], LANDED_ROW, "does not run"),  # ends at another text
    (AFTER, [carry(BEFORE, "x"), carry("y", AFTER)], LANDED_ROW, "does not run"),  # a gap in the chain
])
def test_a_carry_the_change_does_not_prove_is_refused(carrying, source, rows, agreed, message):
    root, gate, base = carrying
    land(root, source, rows, agreed=agreed)
    problems = gate.vote_sources_range_problems(base, "HEAD")
    assert problems and message in problems[0], problems
