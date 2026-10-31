#!/usr/bin/env python3
"""Create or prepare a linked worktree with its own cheap reference/open-bfme-1.

A bare `git submodule update --init` in a new worktree re-downloads Open-BFME-1:
.gitmodules asks for a shallow clone, the depth-1 clone of upstream's tip
lacks the pinned commit, and the follow-up `git fetch origin <pin>` pulls the
whole history (580k objects, ~4 GB RAM, ~50 CPU-minutes per worktree).
`--reference` cannot help: git refuses a shallow reference repository, and
`submodule.alternateErrorStrategy=info` turns that refusal into an unshared
clone. `git clone --shared` from the shallow modules dir silently drops to a
packing transfer (2.5 GB RAM).

This tool gives the worktree its own submodule gitdir, in the worktree's own
`modules/` (where git itself would put it), that borrows the main checkout's
objects through objects/info/alternates and the shallow boundaries it needs.
Nothing is packed; the cost is writing the checkout. Git never writes into
an alternate object store, so commits, gc and fetches in the worktree's
submodule stay in the worktree's gitdir; nothing links into another checkout.

The donor is the main checkout's own BFME 1 gitdir, wherever git says it is
(`.git/modules/...`, or an embedded `.git` in a short-path fleet worker). The
donor's store may itself borrow through its alternates (a short-path worker's
`clone --shared` borrows from the primary checkout's store): the tool walks
that whole chain. A pin missing from the chain is fetched at depth 1, never
with its history, into the store at the end of the chain; if that fetch fails
the tool refuses and names the one-time fetch. Every store in the chain keeps
a ref refs/worktree-borrow/<superproject>/<seat>/<pin> for every pin a seat
borrows, so gc in no store drops objects a seat needs. `remove` drops a
seat's refs; `prune-borrows` drops the refs of seats git no longer has
registered (a locked seat stays registered). Every git command on a donor
store runs with auto gc and auto maintenance off: the tool never prunes or
repacks a donor.

A seat's superproject gets submodule.recurse=false and
fetch.recurseSubmodules=false in its config.worktree: a recursive pull to a
new pin would fetch the pin's whole ancestry into the seat. After pulling,
run `worktree_setup.py prepare` to move the seat to the new pin.

  python3 tools/worktree_setup.py create .claude/worktrees/NAME --branch NAME [--base origin/master]
  python3 tools/worktree_setup.py prepare [WORKTREE]    (also after every pull)
  python3 tools/worktree_setup.py check [WORKTREE]
  python3 tools/worktree_setup.py remove WORKTREE
  python3 tools/worktree_setup.py prune-borrows

Normal prepare expands an existing sparse reference checkout to the full pinned
tree. --inputs-only explicitly requests a partial inputs/ checkout (toolchains,
reference headers, vendor); it is not ready for builds that need game/ headers.
Check a partial checkout with check --inputs-only; normal check refuses it.
"""
import argparse
import hashlib
import subprocess
import sys
from pathlib import Path

SUBMODULE = "reference/open-bfme-1"
INPUTS_ONLY = ("inputs",)
BORROW_PREFIX = "refs/worktree-borrow/"
# On every git command that touches a donor store: a fetch or ref update must
# never start gc, repack or maintenance in a store other seats borrow from.
DONOR_CONFIGS = ("gc.auto=0", "maintenance.auto=false")
# The only refspec a seat fetches with, whatever the donor uses: a
# refs/heads/* wildcard makes a seat fetch pull upstream's other branches
# below the shallow boundary (600k objects, 7.5 GB RAM).
SEAT_REFSPEC = "+refs/heads/master:refs/remotes/origin/master"
# A seat superproject's config.worktree: no recursive fetch or update, and the
# submodule active even where the shared config never ran `submodule init`
# (short-path fleet workers).
SEAT_CONFIG = (("submodule.recurse", "false"), ("fetch.recurseSubmodules", "false"),
               (f"submodule.{SUBMODULE}.active", "true"))


class SetupError(Exception):
    pass


def git(cwd, *args, check=True, git_dir=None, configs=()):
    cmd = ["git"]
    for item in configs:
        cmd += ["-c", item]
    if git_dir is not None:
        cmd.append(f"--git-dir={git_dir}")
    cmd += list(args)
    proc = subprocess.run(cmd, cwd=cwd, capture_output=True, text=True)
    if check and proc.returncode != 0:
        raise SetupError(f"`{' '.join(cmd)}` failed in {cwd}:\n{proc.stderr.strip()}")
    return proc


def out(cwd, *args, **kwargs):
    return git(cwd, *args, **kwargs).stdout.strip()


def store_git(store, *args, check=True, configs=()):
    """git on a donor store, with auto gc and maintenance off."""
    return git(store, *args, check=check, git_dir=store,
               configs=DONOR_CONFIGS + tuple(configs))


def store_out(store, *args, **kwargs):
    return store_git(store, *args, **kwargs).stdout.strip()


def posix(path):
    return str(Path(path).resolve()).replace("\\", "/")


def is_link(path):
    """A symlink or (Windows) directory junction: never let git run through one."""
    path = Path(path)
    if path.is_symlink():
        return True
    is_junction = getattr(path, "is_junction", None)
    if is_junction is not None:
        return is_junction()
    return False


def donor_store(common):
    """The main checkout's BFME 1 gitdir, as git resolves it.

    `.git/modules/...` for a normal submodule; an embedded `.git` directory in
    a short-path fleet worker. Uninitialized: the modules path, which
    fetch_hint() then names.
    """
    donor_sub = common.parent / SUBMODULE
    if not (donor_sub / ".git").exists():
        return common / "modules" / SUBMODULE
    proc = git(donor_sub, "rev-parse", "--path-format=absolute", "--git-dir",
               "--git-common-dir", check=False)
    lines = proc.stdout.splitlines()
    if proc.returncode != 0 or len(lines) != 2:
        raise SetupError(f"cannot resolve the gitdir of {donor_sub}:\n{proc.stderr.strip()}")
    store = Path(lines[1])
    if posix(store) == posix(common):
        raise SetupError(f"{donor_sub}/.git resolves to the superproject's own gitdir")
    return store


def alternates_of(store):
    """The stores store/objects/info/alternates names directly."""
    path = Path(store) / "objects" / "info" / "alternates"
    if not path.is_file():
        return []
    found = []
    for line in path.read_text(encoding="utf-8").splitlines():
        line = line.strip()
        if not line or line.startswith("#"):
            continue
        objects = Path(line)
        if not objects.is_absolute():
            objects = Path(store) / "objects" / objects
        found.append(objects.resolve().parent)
    return found


def store_chain(store):
    """The donor and every store its alternates reach, recursively, nearest
    first. Each must be a git repository: each gets borrow refs."""
    chain, todo, seen = [], [Path(store)], set()
    while todo:
        current = todo.pop(0)
        if posix(current) in seen:
            continue
        seen.add(posix(current))
        if chain and not (current / "HEAD").is_file():
            raise SetupError(f"{store} borrows objects from {current / 'objects'}, which "
                             f"is not in a git repository; it cannot hold borrow refs")
        chain.append(current)
        todo += alternates_of(current)
    return chain


def chain_ends(chain):
    """The stores of the chain that borrow from no other store."""
    return [store for store in chain if not alternates_of(store)]


def owner_key(common):
    """Names one superproject's borrow refs: short-path workers sharing a
    primary store may each have a seat with the same worktree id."""
    return hashlib.sha1(posix(common).encode()).hexdigest()[:12]


def borrow_ref(seat_id, pin):
    return f"{BORROW_PREFIX}{seat_id}/{pin}"


def layout(worktree):
    """Paths for one linked worktree: its submodule dir, gitdir and the main store."""
    worktree = Path(worktree).resolve()
    top = Path(out(worktree, "rev-parse", "--show-toplevel"))
    git_dir = Path(out(top, "rev-parse", "--path-format=absolute", "--git-dir"))
    common = Path(out(top, "rev-parse", "--path-format=absolute", "--git-common-dir"))
    if posix(git_dir) == posix(common):
        raise SetupError(
            f"{top} is the main checkout, not a linked worktree; it gets "
            f"{SUBMODULE} the normal way (tools/setup_hooks.sh).")
    modules = Path(out(top, "rev-parse", "--path-format=absolute",
                       "--git-path", f"modules/{SUBMODULE}"))
    seat_id = f"{owner_key(common)}/{git_dir.name}"
    if git(top, "check-ref-format", borrow_ref(seat_id, "x"), check=False).returncode != 0:
        raise SetupError(f"worktree id {seat_id!r} cannot name a borrow ref")
    return {
        "top": top,
        "sub": top / SUBMODULE,
        "gitdir": modules,
        "seat_id": seat_id,
        "main_store": donor_store(common),
        "main_top": common.parent,
    }


def pinned_commit(top, rev="HEAD"):
    entry = out(top, "ls-tree", rev, "--", SUBMODULE).split()
    if len(entry) < 3 or entry[0] != "160000" or entry[1] != "commit":
        raise SetupError(f"{rev} has no submodule entry at {SUBMODULE}")
    return entry[2]


def fetch_hint(paths, pin):
    main_top = paths["main_top"]
    if not (paths["main_store"] / "objects").is_dir():
        how = (f"  git -C {posix(main_top)} submodule update --init --depth 1 {SUBMODULE}\n"
               f"(--depth 1 matters: without it git fetches the pin with its whole "
               f"history, 580k objects, ~4 GB RAM.)")
    else:
        how = (f"  git -C {posix(main_top / SUBMODULE)} fetch origin\n"
               f"(incremental: its narrow refspec fetches upstream master past what it "
               f"has). If the pin is not on upstream master:\n"
               f"  git -C {posix(main_top / SUBMODULE)} fetch --depth 1 origin {pin}")
    return (f"Fetch it once in the main checkout ({posix(main_top)}), not here:\n"
            f"{how}\nThen rerun this tool.")


def missing_objects(store, pin):
    """Objects of the pinned tree the main store cannot supply (empty: all there)."""
    if store_git(store, "cat-file", "-e", f"{pin}^{{commit}}",
                 check=False).returncode != 0:
        return [pin]
    proc = store_git(store, "rev-list", "--objects", "--no-walk", "--missing=print", pin,
                     check=False)
    if proc.returncode != 0:
        return [proc.stderr.strip() or pin]
    return [line[1:] for line in proc.stdout.splitlines() if line.startswith("?")]


def require_main_objects(paths, pin, ref=None):
    """Every store in the donor's alternates chain reads every object of the
    pin, fetched at depth 1 if not; returns the chain.

    The fetch lands in each store at the end of the chain, which the nearer
    stores read, so every store in the chain can hold a ref to the pin. With
    `ref`, every store points that borrow ref at the pin, so gc in none of
    them drops what the seat borrows.
    """
    store = paths["main_store"]
    if not (store / "objects").is_dir():
        raise SetupError(
            f"the main checkout has no {SUBMODULE} object store ({store}).\n"
            + fetch_hint(paths, pin))
    chain = store_chain(store)
    ends = chain_ends(chain)
    errors = []
    for end in ends:
        if not missing_objects(end, pin):
            continue
        # Bounded: the pin alone, never its history, tags or submodules.
        proc = store_git(end, "fetch", "-q", "--depth", "1", "--no-tags",
                         "--no-recurse-submodules", "--no-auto-maintenance", "origin", pin,
                         check=False, configs=("fetch.recurseSubmodules=false",))
        if proc.returncode != 0:
            errors.append(f"{end}: {proc.stderr.strip() or '(no error)'}")
    for each in chain:
        missing = missing_objects(each, pin)
        if missing:
            raise SetupError(
                f"the main checkout's {SUBMODULE} store {each} lacks {len(missing)} "
                f"object(s) of the pinned commit {pin} (first: {missing[0]}), and a "
                f"depth-1 fetch of it failed:\n  " + ("\n  ".join(errors) or "(no error)")
                + "\n" + fetch_hint(paths, pin))
    # A pin fetched at the end of the chain brings its shallow boundary along.
    for each in chain:
        for end in ends:
            if end is not each:
                merge_shallow(each, end)
    if ref:
        for each in chain:
            store_git(each, "update-ref", ref, pin)
    return chain


def borrow_refs(store, seat_id=None):
    prefix = BORROW_PREFIX + (f"{seat_id}/" if seat_id else "")
    return store_out(store, "for-each-ref", "--format=%(refname)", prefix).splitlines()


def drop_borrow_refs(store, refs):
    for ref in refs:
        store_git(store, "update-ref", "-d", ref)


def own_gitdir(paths):
    """The gitdir the worktree's submodule .git file names, or None if absent."""
    dotgit = paths["sub"] / ".git"
    if not dotgit.exists():
        return None
    if dotgit.is_dir():
        raise SetupError(f"{dotgit} is a directory; this tool only manages a gitdir "
                         f"under the worktree's modules/. Move it aside first.")
    text = dotgit.read_text(encoding="utf-8").strip()
    if not text.startswith("gitdir:"):
        raise SetupError(f"{dotgit} is not a gitdir file")
    target = Path(text[len("gitdir:"):].strip())
    if not target.is_absolute():
        target = paths["sub"] / target
    return target


def check_target(paths):
    """Refuse links and any submodule state this tool did not make."""
    sub = paths["sub"]
    for parent in (sub.parent, sub):
        if is_link(parent):
            raise SetupError(
                f"{parent} is a symlink or junction; git commands through it act on "
                f"another checkout. Remove the link itself (Windows: `rmdir` the "
                f"junction, never a recursive delete) and rerun.")
    gitdir = own_gitdir(paths)
    if gitdir is not None and posix(gitdir) != posix(paths["gitdir"]):
        raise SetupError(f"{sub}/.git names {gitdir}, not this worktree's "
                         f"{paths['gitdir']}; refusing to touch another gitdir.")
    if gitdir is None and sub.is_dir() and any(sub.iterdir()):
        raise SetupError(f"{sub} is not empty but has no .git; move it aside first.")


def write_alternates(gitdir, store):
    alternates = gitdir / "objects" / "info" / "alternates"
    alternates.parent.mkdir(parents=True, exist_ok=True)
    wanted = posix(store / "objects")
    lines = []
    if alternates.exists():
        lines = [l.strip() for l in alternates.read_text(encoding="utf-8").splitlines() if l.strip()]
    if wanted not in lines:
        lines.append(wanted)
    alternates.write_text("\n".join(lines) + "\n", encoding="utf-8", newline="\n")


def cat_batch(gitdir, oids, check_only=False):
    """{oid: raw object bytes, or True with check_only} for the oids gitdir has."""
    if not oids:
        return {}
    mode = "--batch-check" if check_only else "--batch"
    proc = subprocess.run(["git", f"--git-dir={gitdir}", "cat-file", mode],
                          input="".join(f"{oid}\n" for oid in oids).encode(),
                          capture_output=True)
    if proc.returncode != 0:
        raise SetupError(f"git cat-file {mode} failed in {gitdir}: "
                         f"{proc.stderr.decode(errors='replace').strip()}")
    found, data, pos = {}, proc.stdout, 0
    for oid in oids:
        end = data.index(b"\n", pos)
        header = data[pos:end].split()
        pos = end + 1
        if len(header) < 3:  # "<oid> missing"
            continue
        if check_only:
            found[oid] = True
            continue
        size = int(header[2])
        found[oid] = data[pos:pos + size]
        pos += size + 1
    return found


def merge_shallow(gitdir, store):
    """Borrowed history ends where the main store's does: add the main store's
    shallow boundaries, but only those whose parents the seat cannot read.

    A seat that deepened or unshallowed its own history keeps it; a boundary
    is never added back over parents the seat holds.
    """
    source = store / "shallow"
    if not source.exists():
        return
    target = gitdir / "shallow"
    have = set(target.read_text(encoding="utf-8").split()) if target.exists() else set()
    wanted = [oid for oid in source.read_text(encoding="utf-8").split() if oid not in have]
    parents = {}
    for oid, raw in cat_batch(gitdir, wanted).items():
        header = raw.split(b"\n\n", 1)[0]
        parents[oid] = [line.split()[1].decode() for line in header.splitlines()
                        if line.startswith(b"parent ")]
    present = cat_batch(gitdir, sorted({p for ps in parents.values() for p in ps}),
                        check_only=True)
    needed = {oid for oid, ps in parents.items() if any(p not in present for p in ps)}
    if needed:
        target.write_text("".join(f"{oid}\n" for oid in sorted(have | needed)),
                          encoding="utf-8", newline="\n")


def submodule_url(top):
    return out(top, "config", "-f", ".gitmodules", f"submodule.{SUBMODULE}.url")


def configure_worktree(top):
    """core.hooksPath=.githooks and no submodule recursion, for this worktree
    only (config.worktree)."""
    if out(top, "config", "--bool", "--get", "extensions.worktreeConfig", check=False) != "true":
        if out(top, "config", "--local", "--bool", "--get", "core.bare", check=False) == "true":
            raise SetupError("the shared config sets core.bare=true; move it to the main "
                             "worktree's config.worktree before enabling extensions.worktreeConfig")
        if out(top, "config", "--local", "--get", "core.worktree", check=False):
            raise SetupError("the shared config sets core.worktree; move it to the main "
                             "worktree's config.worktree before enabling extensions.worktreeConfig")
        git(top, "config", "--local", "extensions.worktreeConfig", "true")
    git(top, "config", "--worktree", "core.hooksPath", ".githooks")
    for key, value in SEAT_CONFIG:
        git(top, "config", "--worktree", key, value)


def prepare(worktree, inputs_only=False):
    paths = layout(worktree)
    top, sub, gitdir, store = paths["top"], paths["sub"], paths["gitdir"], paths["main_store"]
    pin = pinned_commit(top)
    check_target(paths)
    chain = require_main_objects(paths, pin, borrow_ref(paths["seat_id"], pin))
    configure_worktree(top)
    sub.mkdir(parents=True, exist_ok=True)
    # A gitdir whose HEAD never resolved is a failed earlier run: redo it.
    existing = (gitdir / "HEAD").exists() and git(
        sub, "rev-parse", "--verify", "--quiet", "HEAD^{commit}", check=False,
        git_dir=gitdir).returncode == 0
    if not existing:
        gitdir.parent.mkdir(parents=True, exist_ok=True)
        git(top, "init", "-q", f"--separate-git-dir={gitdir}", str(sub))
    write_alternates(gitdir, store)
    for each in chain:
        merge_shallow(gitdir, each)
    git(sub, "config", "core.worktree", posix(sub), git_dir=gitdir)
    url = submodule_url(top)
    if git(sub, "remote", "get-url", "origin", check=False, git_dir=gitdir).returncode == 0:
        git(sub, "remote", "set-url", "origin", url, git_dir=gitdir)
    else:
        git(sub, "remote", "add", "origin", url, git_dir=gitdir)
    # Master only, replacing whatever the donor or an earlier run set.
    git(sub, "config", "--replace-all", "remote.origin.fetch", SEAT_REFSPEC, git_dir=gitdir)
    git(sub, "config", "remote.origin.tagOpt", "--no-tags", git_dir=gitdir)
    if not existing:
        git(sub, "update-ref", "--no-deref", "HEAD", pin)
        if inputs_only:
            git(sub, "sparse-checkout", "set", "--cone", *INPUTS_ONLY)
        git(sub, "reset", "-q", "--hard", pin)
    else:
        if out(sub, "rev-parse", "HEAD", check=False) != pin:
            # An existing checkout may hold the seat's own edits: never reset it.
            git(sub, "checkout", "-q", "--detach", pin)
        if inputs_only:
            git(sub, "sparse-checkout", "set", "--cone", *INPUTS_ONLY)
        elif out(sub, "config", "--bool", "--get", "core.sparseCheckout", check=False) == "true":
            # A previous --inputs-only seat must become build-ready too. Git
            # preserves local edits and refuses conflicting untracked files.
            git(sub, "sparse-checkout", "disable")
    return verify(worktree, inputs_only=inputs_only)


def verify(worktree, inputs_only=False):
    paths = layout(worktree)
    top, sub, store = paths["top"], paths["sub"], paths["main_store"]
    pin = pinned_commit(top)
    problems = []
    for parent in (sub.parent, sub):
        if is_link(parent):
            problems.append(f"{parent} is a link")
    if not problems:
        gitdir = out(sub, "rev-parse", "--path-format=absolute", "--git-dir", check=False)
        if posix(gitdir or sub) != posix(paths["gitdir"]):
            problems.append(f"{SUBMODULE} uses gitdir {gitdir or '(none)'}, "
                            f"not {paths['gitdir']}")
        head = out(sub, "rev-parse", "HEAD", check=False)
        if head != pin:
            problems.append(f"{SUBMODULE} HEAD is {head or '(none)'}, pin is {pin}")
        sparse = out(sub, "config", "--bool", "--get", "core.sparseCheckout", check=False) == "true"
        if sparse and not inputs_only:
            problems.append(f"{SUBMODULE} is a partial sparse checkout; game headers may be absent. "
                            "Run tools/worktree_setup.py prepare without --inputs-only before source work; "
                            "check --inputs-only only validates the partial setup")
        roots = INPUTS_ONLY if inputs_only else ("inputs", "game", "Code")
        missing = out(sub, "ls-files", "--deleted", "--", *roots).splitlines()
        if missing:
            problems.append(f"{SUBMODULE} has missing tracked build inputs: " + ", ".join(missing[:5]))
        status = git(top, "submodule", "status", "--", SUBMODULE, check=False).stdout
        if not status.startswith(" "):
            problems.append(f"git submodule status: {status.strip()!r}")
        refspecs = out(sub, "config", "--get-all", "remote.origin.fetch",
                       check=False).splitlines()
        if refspecs != [SEAT_REFSPEC]:
            problems.append(f"{SUBMODULE} fetches {refspecs}, not only {SEAT_REFSPEC}")
        ref = borrow_ref(paths["seat_id"], pin)
        for each in store_chain(store):
            if store_out(each, "rev-parse", "--verify", "--quiet", ref, check=False) != pin:
                problems.append(f"the donor store {each} has no {ref}; its gc may drop "
                                f"the pin")
        if not (sparse and not inputs_only) and not missing:
            fsck = git(sub, "fsck", "--connectivity-only", "--no-dangling", "--no-progress",
                       check=False)
            if fsck.returncode != 0:
                detail = (fsck.stdout + fsck.stderr).strip().splitlines()[:3]
                problems.append(f"{SUBMODULE} objects are missing (git fsck): " + "; ".join(detail))
    hooks = out(top, "config", "--get", "core.hooksPath", check=False)
    if hooks != ".githooks":
        problems.append(f"core.hooksPath is {hooks!r}, not .githooks")
    for key, value in SEAT_CONFIG:
        got = out(top, "config", "--worktree", "--get", key, check=False)
        if got != value:
            problems.append(f"config.worktree {key} is {got!r}, not {value}")
    if problems:
        raise SetupError("worktree not ready:\n  " + "\n  ".join(problems))
    return pin


def create(path, branch=None, base="HEAD", inputs_only=False, cwd=None):
    """`git worktree add` without touching submodules, then prepare()."""
    cwd = Path(cwd or Path.cwd())
    path = Path(path)
    if not path.is_absolute():
        path = cwd / path
    if path.exists() and any(path.iterdir()):
        raise SetupError(f"{path} exists and is not empty")
    # LF checkouts: tu_skeleton refuses CRLF ledgers, and system git on the
    # seats sets core.autocrlf=true. The submodule is set up by prepare().
    configs = ("core.autocrlf=false", "submodule.recurse=false")
    start = base
    if branch is not None and git(cwd, "rev-parse", "--verify", "--quiet",
                                  f"refs/heads/{branch}", check=False).returncode == 0:
        start = branch
    # Refuse before `worktree add`, not after it leaves a half-made worktree;
    # prepare() then pins the commit with the seat's borrow ref.
    common = Path(out(cwd, "rev-parse", "--path-format=absolute", "--git-common-dir"))
    require_main_objects({"main_store": donor_store(common), "main_top": common.parent},
                         pinned_commit(cwd, start))
    args = ["worktree", "add"]
    if branch is None:
        args += ["--detach", str(path), base]
    elif start == branch:
        args += [str(path), branch]
    else:
        args += ["-b", branch, str(path), base]
    git(cwd, *args, configs=configs)
    return prepare(path, inputs_only=inputs_only)


def remove(worktree):
    """`git worktree remove` a clean seat, then drop its borrow refs."""
    paths = layout(worktree)
    top, sub, store = paths["top"], paths["sub"], paths["main_store"]
    if out(top, "status", "--porcelain", "--ignore-submodules=none"):
        raise SetupError(f"{top} has changes or untracked files; commit or remove them first")
    if (sub / ".git").exists():
        if out(sub, "status", "--porcelain"):
            raise SetupError(f"{sub} has changes or untracked files")
        own = [ref for ref in out(sub, "for-each-ref", "--format=%(refname)").splitlines()
               if not ref.startswith("refs/remotes/")]
        if own:
            raise SetupError(f"{sub} has its own refs ({', '.join(own)}); push or delete them")
        head = out(sub, "rev-parse", "HEAD", check=False)
        if head and store_git(store, "cat-file", "-e", f"{head}^{{commit}}",
                              check=False).returncode != 0:
            raise SetupError(f"{sub} HEAD {head} exists only in the seat; keep it first")
    # --force: git refuses any worktree holding a submodule gitdir; the checks
    # above stand in for the ones --force skips.
    git(paths["main_top"], "worktree", "remove", "--force", str(top))
    for each in store_chain(store):
        drop_borrow_refs(each, borrow_refs(each, paths["seat_id"]))


def registered_seats(common):
    """Worktree ids git still has registered, locked or not, present or not.

    A locked seat on a missing or unmounted path stays registered: only
    `git worktree remove`, or `git worktree prune` (which skips locked seats),
    unregisters one.
    """
    admin = common / "worktrees"
    if not admin.is_dir():
        return set()
    return {entry.name for entry in admin.iterdir() if entry.is_dir()}


def prune_borrows(cwd=None):
    """Drop this superproject's borrow refs, in every store of the chain, for
    seats git no longer has registered; return them."""
    common = Path(out(Path(cwd or Path.cwd()), "rev-parse", "--path-format=absolute",
                      "--git-common-dir"))
    store = donor_store(common)
    if not (store / "objects").is_dir():
        return []
    owner = owner_key(common)
    live = registered_seats(common)
    stale = []
    for each in store_chain(store):
        refs = [ref for ref in borrow_refs(each, owner)
                if ref[len(BORROW_PREFIX) + len(owner) + 1:].split("/", 1)[0] not in live]
        drop_borrow_refs(each, refs)
        stale += [ref for ref in refs if ref not in stale]
    return stale


def main(argv=None):
    parser = argparse.ArgumentParser(description=__doc__.split("\n")[0])
    sub = parser.add_subparsers(dest="cmd", required=True)
    c = sub.add_parser("create", help="git worktree add, then prepare it")
    c.add_argument("path")
    c.add_argument("--branch", help="branch to check out (created from --base if new)")
    c.add_argument("--base", default="HEAD", help="start point (default HEAD)")
    c.add_argument("--inputs-only", action="store_true",
                   help=f"check out only {', '.join(INPUTS_ONLY)}/ of {SUBMODULE}")
    p = sub.add_parser("prepare", help="set up hooks and the submodule in an existing "
                                       "worktree; rerun after every pull")
    p.add_argument("path", nargs="?", default=".")
    p.add_argument("--inputs-only", action="store_true",
                   help=f"check out only {', '.join(INPUTS_ONLY)}/ of {SUBMODULE}")
    k = sub.add_parser("check", help="verify a worktree's checkout, hooks, gitdir, pin and objects")
    k.add_argument("path", nargs="?", default=".")
    k.add_argument("--inputs-only", action="store_true",
                   help="validate only a partial reference checkout; game headers are not guaranteed")
    r = sub.add_parser("remove", help="remove a clean worktree and its borrow refs")
    r.add_argument("path")
    sub.add_parser("prune-borrows", help="drop the borrow refs of worktrees git no "
                                         "longer has registered")
    args = parser.parse_args(argv)
    try:
        if args.cmd == "create":
            pin = create(args.path, args.branch, args.base, args.inputs_only)
        elif args.cmd == "prepare":
            pin = prepare(args.path, args.inputs_only)
        elif args.cmd == "remove":
            remove(args.path)
            print(f"worktree_setup: removed {args.path} and its borrow refs")
            return 0
        elif args.cmd == "prune-borrows":
            stale = prune_borrows()
            print(f"worktree_setup: dropped {len(stale)} stale borrow ref(s)")
            for ref in stale:
                print(f"  {ref}")
            return 0
        else:
            pin = verify(args.path, inputs_only=args.inputs_only)
    except SetupError as exc:
        print(f"worktree_setup: {exc}", file=sys.stderr)
        return 1
    mode = "; PARTIAL inputs-only checkout: game headers not guaranteed" if args.inputs_only else "; full checkout"
    print(f"worktree_setup: {args.cmd} OK: {SUBMODULE} at {pin}, own gitdir, "
          f"objects borrowed from the main checkout, core.hooksPath=.githooks{mode}")
    return 0


if __name__ == "__main__":
    sys.exit(main())
