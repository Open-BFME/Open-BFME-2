"""tools/worktree_setup.py gives a linked worktree its own submodule gitdir that
borrows the main checkout's objects, and never touches the main checkout's store.

Each case builds a tiny local superproject with a file:// submodule at
reference/open-bfme-1, so nothing reaches the network.
"""
import os
import subprocess
import sys
from pathlib import Path

import pytest

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import worktree_setup as ws  # noqa: E402

SUB = ws.SUBMODULE


def run(cwd, *args):
    proc = subprocess.run(["git", *args], cwd=cwd, capture_output=True, text=True)
    assert proc.returncode == 0, f"git {' '.join(args)}: {proc.stderr}"
    return proc.stdout.strip()


@pytest.fixture(autouse=True)
def isolated_git(monkeypatch, tmp_path):
    # A hook runs these tests with GIT_DIR and friends set for the real repo.
    for name in list(os.environ):
        if name.startswith("GIT_"):
            monkeypatch.delenv(name)
    monkeypatch.setenv("GIT_CONFIG_NOSYSTEM", "1")
    monkeypatch.setenv("GIT_CONFIG_GLOBAL", str(tmp_path / "gitconfig"))
    (tmp_path / "gitconfig").write_text(
        "[user]\n\tname = t\n\temail = t@example.invalid\n"
        "[protocol \"file\"]\n\tallow = always\n[init]\n\tdefaultBranch = master\n",
        encoding="utf-8")


@pytest.fixture
def repos(tmp_path):
    """upstream (the BFME 1 stand-in) and main (a superproject pinning it)."""
    upstream = tmp_path / "upstream"
    upstream.mkdir()
    run(upstream, "init", "-q")
    (upstream / "inputs").mkdir()
    (upstream / "inputs" / "header.h").write_text("int x;\n", encoding="utf-8")
    (upstream / "game").mkdir()
    (upstream / "game" / "game.cpp").write_text("int y;\n", encoding="utf-8")
    run(upstream, "add", ".")
    run(upstream, "commit", "-qm", "one")
    main = tmp_path / "main"
    main.mkdir()
    run(main, "init", "-q")
    (main / "README").write_text("main\n", encoding="utf-8")
    run(main, "add", "README")
    run(main, "commit", "-qm", "root")
    run(main, "submodule", "add", "-q", upstream.as_uri(), SUB)
    run(main, "config", "core.hooksPath", str(main / ".githooks"))
    run(main, "commit", "-qm", "pin")
    return upstream, main


def bref(superproject, seat, pin):
    """The borrow ref a seat of `superproject` keeps in each donor store."""
    common = Path(run(superproject, "rev-parse", "--path-format=absolute", "--git-common-dir"))
    return ws.borrow_ref(f"{ws.owner_key(common)}/{seat}", pin)


def store_state(main):
    store = main / ".git" / "modules" / SUB
    files = sorted((p.relative_to(store).as_posix(), p.stat().st_mtime_ns)
                   for p in store.rglob("*") if p.is_file())
    return files


def test_create_borrows_objects_and_isolates_the_gitdir(repos, tmp_path):
    upstream, main = repos
    wt = tmp_path / "wt"
    pin = ws.create(wt, branch="seat", base="HEAD", cwd=main)
    before = store_state(main)
    assert pin == run(main, "rev-parse", f"HEAD:{SUB}")
    sub = wt / SUB
    assert (sub / "game" / "game.cpp").read_text(encoding="utf-8") == "int y;\n"
    gitdir = Path(run(sub, "rev-parse", "--path-format=absolute", "--git-dir"))
    assert ws.posix(gitdir) == ws.posix(main / ".git/worktrees/wt/modules" / SUB)
    alternates = (gitdir / "objects/info/alternates").read_bytes()
    assert alternates == (ws.posix(main / ".git/modules" / SUB / "objects") + "\n").encode()
    assert not list((gitdir / "objects/pack").glob("*.pack"))
    assert run(wt, "config", "--get", "core.hooksPath") == ".githooks"
    assert run(main, "config", "--get", "core.hooksPath") == str(main / ".githooks")
    assert run(wt, "branch", "--show-current") == "seat"
    # Work in the worktree's submodule lands in its own gitdir only.
    (sub / "new.txt").write_text("n\n", encoding="utf-8")
    run(sub, "add", "new.txt")
    run(sub, "commit", "-qm", "seat edit")
    run(sub, "gc", "-q")
    assert store_state(main) == before
    assert run(main / SUB, "rev-parse", "HEAD") == pin


def test_prepare_is_idempotent_and_sets_the_narrow_refspec(repos, tmp_path):
    upstream, main = repos
    store = main / ".git" / "modules" / SUB
    run(main, "--git-dir", str(store), "config", "--replace-all", "remote.origin.fetch",
        "+refs/heads/master:refs/remotes/origin/master")
    wt = tmp_path / "wt"
    ws.create(wt, cwd=main)
    (wt / SUB / "game" / "game.cpp").write_text("seat change\n", encoding="utf-8")
    pin = ws.prepare(wt)
    # A rerun never resets the seat's own edits.
    assert (wt / SUB / "game" / "game.cpp").read_text(encoding="utf-8") == "seat change\n"
    gitdir = main / ".git/worktrees/wt/modules" / SUB
    assert run(wt / SUB, "config", "--get-all", "remote.origin.fetch") == \
        "+refs/heads/master:refs/remotes/origin/master"
    assert run(wt / SUB, "remote", "get-url", "origin") == upstream.as_uri()
    assert (gitdir / "objects/info/alternates").read_text(encoding="utf-8").count("\n") == 1
    assert ws.verify(wt) == pin


def test_refuses_a_pin_the_main_store_cannot_fetch(repos, tmp_path):
    upstream, main = repos
    # Pin a commit that is neither in the main checkout nor upstream.
    elsewhere = tmp_path / "elsewhere"
    run(tmp_path, "clone", "-q", str(upstream), str(elsewhere))
    (elsewhere / "game" / "game.cpp").write_text("int z;\n", encoding="utf-8")
    run(elsewhere, "commit", "-qam", "two")
    newer = run(elsewhere, "rev-parse", "HEAD")
    run(main, "update-index", "--cacheinfo", f"160000,{newer},{SUB}")
    run(main, "commit", "-qm", "repin")
    with pytest.raises(ws.SetupError) as err:
        ws.create(tmp_path / "wt", cwd=main)
    message = str(err.value)
    assert newer in message and "main checkout" in message and "fetch" in message
    assert not (tmp_path / "wt").exists()


def test_refuses_the_main_checkout(repos):
    _, main = repos
    with pytest.raises(ws.SetupError, match="main checkout"):
        ws.prepare(main)


def test_refuses_a_link_into_another_checkout(repos, tmp_path, monkeypatch):
    _, main = repos
    wt = tmp_path / "wt"
    run(main, "-c", "submodule.recurse=false", "worktree", "add", "-q", "--detach", str(wt))
    sub = wt / SUB
    monkeypatch.setattr(ws, "is_link", lambda path: Path(path) == sub)
    with pytest.raises(ws.SetupError, match="junction"):
        ws.prepare(wt)


def test_refuses_a_gitdir_it_did_not_make(repos, tmp_path):
    _, main = repos
    wt = tmp_path / "wt"
    run(main, "-c", "submodule.recurse=false", "worktree", "add", "-q", "--detach", str(wt))
    (wt / SUB).mkdir(parents=True, exist_ok=True)
    (wt / SUB / ".git").write_text(f"gitdir: {ws.posix(main / '.git/modules' / SUB)}\n",
                                   encoding="utf-8")
    with pytest.raises(ws.SetupError, match="refusing to touch another gitdir"):
        ws.prepare(wt)


def test_inputs_only_checks_out_inputs(repos, tmp_path):
    _, main = repos
    wt = tmp_path / "wt"
    ws.create(wt, cwd=main, inputs_only=True)
    assert (wt / SUB / "inputs" / "header.h").exists()
    assert not (wt / SUB / "game").exists()
    assert ws.verify(wt, inputs_only=True) == run(main, "rev-parse", f"HEAD:{SUB}")
    with pytest.raises(ws.SetupError, match="partial sparse checkout"):
        ws.verify(wt)


def test_prepare_expands_existing_partial_checkout_and_preserves_edits(repos, tmp_path):
    _, main = repos
    wt = tmp_path / "wt"
    pin = ws.create(wt, cwd=main, inputs_only=True)
    header = wt / SUB / "inputs/header.h"
    header.write_text("local header edit\n", encoding="utf-8")
    assert not (wt / SUB / "game/game.cpp").exists()

    assert ws.prepare(wt) == pin
    assert (wt / SUB / "game/game.cpp").read_text(encoding="utf-8") == "int y;\n"
    assert header.read_text(encoding="utf-8") == "local header edit\n"
    assert run(wt / SUB, "rev-parse", "HEAD") == pin
    assert ws.verify(wt) == pin


def test_explicit_inputs_only_applies_to_existing_checkout(repos, tmp_path):
    _, main = repos
    wt = tmp_path / "wt"
    pin = ws.create(wt, cwd=main)
    assert ws.prepare(wt, inputs_only=True) == pin
    assert not (wt / SUB / "game/game.cpp").exists()
    with pytest.raises(ws.SetupError, match="partial sparse checkout"):
        ws.verify(wt)


def test_cli_cannot_report_partial_checkout_as_full_ready(repos, tmp_path, capsys):
    _, main = repos
    wt = tmp_path / "wt"
    ws.create(wt, cwd=main, inputs_only=True)
    assert ws.main(["check", str(wt)]) == 1
    assert "prepare without --inputs-only" in capsys.readouterr().err
    assert ws.main(["check", str(wt), "--inputs-only"]) == 0
    assert "PARTIAL inputs-only checkout" in capsys.readouterr().out
    assert ws.main(["prepare", str(wt)]) == 0
    assert "; full checkout" in capsys.readouterr().out


def test_check_reports_deleted_build_input(repos, tmp_path):
    _, main = repos
    wt = tmp_path / "wt"
    ws.create(wt, cwd=main)
    (wt / SUB / "inputs/header.h").unlink()
    with pytest.raises(ws.SetupError, match="missing tracked build inputs: inputs/header.h"):
        ws.verify(wt)


def commit_upstream(upstream, text, message):
    (upstream / "game" / "game.cpp").write_text(text, encoding="utf-8")
    run(upstream, "commit", "-qam", message)
    return run(upstream, "rev-parse", "HEAD")


def has_object(repo, oid):
    return subprocess.run(["git", "cat-file", "-e", oid], cwd=repo,
                          capture_output=True).returncode == 0


def borrow_refs(donor):
    return run(donor, "for-each-ref", "--format=%(refname)", ws.BORROW_PREFIX).splitlines()


def test_borrow_ref_keeps_the_pin_through_donor_gc(repos, tmp_path):
    upstream, main = repos
    wt = tmp_path / "wt"
    pin = ws.create(wt, cwd=main)
    donor = main / SUB
    assert borrow_refs(donor) == [bref(main, "wt", pin)]
    # Move the donor to an unrelated commit and drop all its own refs to the pin.
    run(upstream, "checkout", "-q", "--orphan", "other")
    run(upstream, "rm", "-rq", "--cached", ".")
    (upstream / "other.txt").write_text("unrelated\n", encoding="utf-8")
    run(upstream, "add", "other.txt")
    run(upstream, "commit", "-qm", "unrelated")
    run(donor, "fetch", "-q", "origin", "other")
    run(donor, "checkout", "-q", "--detach", "FETCH_HEAD")
    for ref in run(donor, "for-each-ref", "--format=%(refname)").splitlines():
        if not ref.startswith(ws.BORROW_PREFIX):
            run(donor, "update-ref", "--no-deref", "-d", ref)
    run(donor, "reflog", "expire", "--expire=now", "--all")
    run(donor, "gc", "-q", "--prune=now")
    run(wt / SUB, "fsck", "--connectivity-only")
    assert ws.verify(wt) == pin
    # Without the borrow ref the same gc drops the pin, and check says so.
    run(donor, "update-ref", "-d", bref(main, "wt", pin))
    run(donor, "gc", "-q", "--prune=now")
    assert not has_object(donor, pin)
    with pytest.raises(ws.SetupError, match="git fsck"):
        ws.verify(wt)


def test_remove_and_prune_borrows_drop_the_seat_refs(repos, tmp_path):
    _, main = repos
    pin = ws.create(tmp_path / "a", cwd=main)
    ws.create(tmp_path / "b", cwd=main)
    donor = main / SUB
    assert len(borrow_refs(donor)) == 2
    ws.remove(tmp_path / "a")
    assert not (tmp_path / "a").exists()
    assert borrow_refs(donor) == [bref(main, "b", pin)]
    # A seat removed behind the tool's back leaves a stale ref for prune-borrows.
    run(main, "worktree", "remove", "--force", str(tmp_path / "b"))
    assert ws.prune_borrows(main) == [bref(main, "b", pin)]
    assert borrow_refs(donor) == []


def test_pull_never_recurses_and_prepare_fetches_the_new_pin_at_depth_1(repos, tmp_path):
    upstream, main = repos
    run(main, "config", "submodule.recurse", "true")  # tools/setup_hooks.sh sets it
    wt = tmp_path / "wt"
    old = ws.create(wt, branch="seat", cwd=main)
    assert run(wt, "config", "--get", "submodule.recurse") == "false"
    assert run(wt, "config", "--get", "fetch.recurseSubmodules") == "false"
    two = commit_upstream(upstream, "int two;\n", "two")
    three = commit_upstream(upstream, "int three;\n", "three")
    run(main, "update-index", "--cacheinfo", f"160000,{three},{SUB}")
    run(main, "commit", "-qm", "repin")
    run(wt, "pull", "-q", "--no-rebase", ".", "master")
    # The pull fetched nothing into the seat's submodule and left it alone.
    assert run(wt / SUB, "rev-parse", "HEAD") == old
    counts = run(wt / SUB, "count-objects", "-v")
    assert "count: 0" in counts and "in-pack: 0" in counts
    assert ws.prepare(wt) == three
    assert run(wt / SUB, "rev-parse", "HEAD") == three
    donor = main / SUB
    # The donor fetched the pin alone, never its history, and keeps it.
    assert has_object(donor, three) and not has_object(donor, two)
    assert bref(main, "wt", three) in borrow_refs(donor)
    assert bref(main, "wt", old) in borrow_refs(donor)


def test_a_donor_wildcard_refspec_is_never_copied(repos, tmp_path):
    upstream, main = repos
    wildcard = "+refs/heads/*:refs/remotes/origin/*"
    run(main / SUB, "config", "--replace-all", "remote.origin.fetch", wildcard)
    run(upstream, "branch", "side")
    wt = tmp_path / "wt"
    ws.create(wt, cwd=main)
    assert run(wt / SUB, "config", "--get-all", "remote.origin.fetch") == ws.SEAT_REFSPEC
    run(wt / SUB, "fetch", "-q", "origin")
    fetched = run(wt / SUB, "for-each-ref", "--format=%(refname)", "refs/remotes/")
    assert "refs/remotes/origin/master" in fetched.splitlines()
    assert "side" not in fetched
    # A wildcard added later fails check, and prepare rewrites it.
    run(wt / SUB, "config", "--add", "remote.origin.fetch", wildcard)
    with pytest.raises(ws.SetupError, match="fetches"):
        ws.verify(wt)
    ws.prepare(wt)
    assert run(wt / SUB, "config", "--get-all", "remote.origin.fetch") == ws.SEAT_REFSPEC


def test_short_path_worker_with_an_embedded_gitdir(repos, tmp_path):
    # tools/setup_local_fleet.py --short-path: a clone whose BFME 1 is a
    # `clone --shared` with its own .git directory, no .git/modules.
    _, main = repos
    worker = tmp_path / "w01"
    run(tmp_path, "clone", "-q", "--shared", "--no-recurse-submodules", str(main), str(worker))
    pin = ws.pinned_commit(worker)
    run(tmp_path, "clone", "-q", "--shared", "--no-checkout", "--no-recurse-submodules",
        str(main / SUB), str(worker / SUB))
    run(worker / SUB, "checkout", "-q", "--detach", pin)
    assert (worker / SUB / ".git").is_dir() and not (worker / ".git" / "modules").exists()
    wt = tmp_path / "wt"
    assert ws.create(wt, cwd=worker) == pin
    gitdir = Path(run(wt / SUB, "rev-parse", "--path-format=absolute", "--git-dir"))
    assert (gitdir / "objects/info/alternates").read_text(encoding="utf-8") == \
        ws.posix(worker / SUB / ".git" / "objects") + "\n"
    assert borrow_refs(worker / SUB) == [bref(worker, "wt", pin)]
    assert (wt / SUB / "game" / "game.cpp").read_text(encoding="utf-8") == "int y;\n"


def test_prepare_keeps_history_a_seat_unshallowed(repos, tmp_path):
    upstream, _ = repos
    commit_upstream(upstream, "int two;\n", "two")
    commit_upstream(upstream, "int three;\n", "three")
    main = tmp_path / "shallow-main"
    main.mkdir()
    run(main, "init", "-q")
    run(main, "submodule", "add", "-q", "--depth", "1", upstream.as_uri(), SUB)
    run(main, "commit", "-qm", "pin")
    assert (main / ".git/modules" / SUB / "shallow").exists()
    wt = tmp_path / "wt"
    pin = ws.create(wt, cwd=main)
    sub = wt / SUB
    gitdir = Path(run(sub, "rev-parse", "--path-format=absolute", "--git-dir"))
    assert (gitdir / "shallow").read_text(encoding="utf-8").split() == [pin]
    assert run(sub, "rev-list", "--count", "HEAD") == "1"
    run(sub, "fetch", "-q", "--unshallow", "origin")
    assert run(sub, "rev-list", "--count", "HEAD") == "3"
    assert ws.prepare(wt) == pin
    assert not (gitdir / "shallow").exists()
    assert run(sub, "rev-list", "--count", "HEAD") == "3"


def pack_state(store):
    return sorted((p.name, p.stat().st_mtime_ns) for p in (store / "objects/pack").iterdir())


def test_the_donor_fetch_never_runs_auto_gc(repos, tmp_path):
    upstream, main = repos
    store = main / ".git" / "modules" / SUB
    donor = main / SUB
    run(donor, "repack", "-adq")
    # Any second pack trips auto gc, and gc runs in the foreground.
    run(donor, "config", "gc.autoPackLimit", "1")
    run(donor, "config", "gc.autoDetach", "false")
    run(donor, "config", "transfer.unpackLimit", "1")
    marker = tmp_path / "auto-gc-ran"
    hook = store / "hooks" / "pre-auto-gc"
    hook.parent.mkdir(exist_ok=True)
    hook.write_text(f"#!/bin/sh\necho ran > '{ws.posix(marker)}'\n", encoding="utf-8",
                    newline="\n")
    hook.chmod(0o755)
    before = pack_state(store)
    three = commit_upstream(upstream, "int three;\n", "three")
    run(main, "update-index", "--cacheinfo", f"160000,{three},{SUB}")
    run(main, "commit", "-qm", "repin")
    assert ws.create(tmp_path / "wt", cwd=main) == three
    assert not marker.exists()
    after = pack_state(store)
    assert set(before) <= set(after) and len(after) > len(before)


def short_path_worker(main, tmp_path, name="w01"):
    worker = tmp_path / name
    run(tmp_path, "clone", "-q", "--shared", "--no-recurse-submodules", str(main), str(worker))
    pin = ws.pinned_commit(worker)
    run(tmp_path, "clone", "-q", "--shared", "--no-checkout", "--no-recurse-submodules",
        str(main / SUB), str(worker / SUB))
    run(worker / SUB, "checkout", "-q", "--detach", pin)
    return worker, pin


def drop_all_but_borrows_and_gc(repo):
    run(repo, "symbolic-ref", "HEAD", "refs/heads/empty")
    run(repo, "rm", "-rqf", "--cached", "--ignore-unmatch", ".")
    for ref in run(repo, "for-each-ref", "--format=%(refname)").splitlines():
        if not ref.startswith(ws.BORROW_PREFIX):
            run(repo, "update-ref", "--no-deref", "-d", ref)
    run(repo, "reflog", "expire", "--expire=now", "--all")
    run(repo, "gc", "-q", "--prune=now")


def test_borrow_refs_reach_every_store_in_the_alternates_chain(repos, tmp_path):
    # The worker's BFME 1 is a `clone --shared` of the primary's: the pinned
    # objects live in the primary store, which the worker's refs never protect.
    upstream, main = repos
    worker, pin = short_path_worker(main, tmp_path)
    # A second worker sharing the primary store, with a seat of the same id.
    other, _ = short_path_worker(main, tmp_path, "w02")
    wt = tmp_path / "wt"
    assert ws.create(wt, cwd=worker) == pin
    ref = bref(worker, "wt", pin)
    assert borrow_refs(worker / SUB) == [ref]
    assert borrow_refs(main / SUB) == [ref]
    drop_all_but_borrows_and_gc(main / SUB)
    run(wt / SUB, "fsck", "--connectivity-only")
    assert ws.verify(wt) == pin
    # A new pin is fetched into the store at the end of the chain, so every
    # store can hold a ref to it.
    three = commit_upstream(upstream, "int three;\n", "three")
    run(worker, "update-index", "--cacheinfo", f"160000,{three},{SUB}")
    run(worker, "commit", "-qm", "repin")
    run(wt, "pull", "-q", "--no-rebase", str(worker), "master")
    assert ws.prepare(wt) == three
    for repo in (worker / SUB, main / SUB):
        assert bref(worker, "wt", three) in borrow_refs(repo)
    drop_all_but_borrows_and_gc(main / SUB)
    run(wt / SUB, "fsck", "--connectivity-only")
    # One worker's remove or prune-borrows never drops the other's refs.
    ws.create(tmp_path / "w02-seats" / "wt", cwd=other)
    theirs = bref(other, "wt", pin)
    assert theirs != ref and theirs in borrow_refs(main / SUB)
    ws.remove(wt)
    assert borrow_refs(worker / SUB) == [] and borrow_refs(main / SUB) == [theirs]
    assert ws.prune_borrows(worker) == [] and borrow_refs(main / SUB) == [theirs]


def test_prune_borrows_keeps_a_locked_or_registered_seat(repos, tmp_path):
    _, main = repos
    wt = tmp_path / "wt"
    pin = ws.create(wt, cwd=main)
    ref = bref(main, "wt", pin)
    run(main, "worktree", "lock", "--reason", "on a removable drive", str(wt))
    wt.rename(tmp_path / "away")
    assert ws.prune_borrows(main) == []
    run(main, "worktree", "prune")
    assert ws.prune_borrows(main) == [] and borrow_refs(main / SUB) == [ref]
    run(main, "worktree", "unlock", str(wt))
    assert ws.prune_borrows(main) == []  # registered until git prunes it
    run(main, "worktree", "prune")
    assert ws.prune_borrows(main) == [ref]
