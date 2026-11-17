"""Conservative current-byte consumers of a regenerated shared header.

This is discovery, not canonical-declaration or object-provider admission. An
unknown dependency receipt is a possible consumer, never evidence of absence.
"""
from dataclasses import dataclass, field
import csv
import hashlib
import json
import os
from pathlib import Path
import re
import subprocess
from types import MappingProxyType
from typing import Mapping

import header_dependents as H


ROOT = Path(__file__).resolve().parents[1]
LEDGERS = ("reverse/functions.csv", "reverse/data_rows.csv")
_NATIVE_DEFINE = re.compile(r"define\s+_STLP_NATIVE_[A-Z_]*HEADER\b")
_NATIVE_USE = re.compile(r"_STLP_NATIVE_(?:C_HEADER|CPP_C_HEADER|CPP_RUNTIME_HEADER|HEADER|OLD_STREAMS_HEADER)\s*\(")


class InputRefused(ValueError):
    """The complete population or the unchanged input snapshot is unproved."""


def _relative(path):
    if not isinstance(path, str) or not path or "\0" in path or "\\" in path:
        raise InputRefused(f"invalid repository path: {path!r}")
    parts = path.split("/")
    if path.startswith("/") or re.match(r"^[A-Za-z]:", path) or any(p in ("", ".", "..") for p in parts):
        raise InputRefused(f"noncanonical repository path: {path!r}")
    return path


def _tracked(root):
    done = subprocess.run(["git", "ls-files", "--stage", "-z"], cwd=root, capture_output=True)
    if done.returncode:
        raise InputRefused("cannot list the current tracked inputs")
    modes, folded = {}, {}
    try:
        for entry in done.stdout.split(b"\0"):
            if not entry:
                continue
            metadata, raw_path = entry.split(b"\t", 1)
            mode, _oid, stage = metadata.decode("ascii").split()
            path = _relative(raw_path.decode("utf-8", "strict"))
            if stage != "0" or path in modes:
                raise InputRefused(f"unmerged or duplicate tracked input: {path}")
            prior = folded.setdefault(path.casefold(), path)
            if prior != path:
                raise InputRefused(f"case-colliding tracked inputs: {prior}, {path}")
            modes[path] = mode
    except (UnicodeError, ValueError) as exc:
        raise InputRefused(f"cannot parse tracked inputs: {exc}") from exc
    return modes


def _key(root, path):
    path = Path(path)
    try:
        return path.relative_to(root).as_posix()
    except ValueError:
        return str(path)


def _stamp(stat):
    return stat.st_dev, stat.st_ino, stat.st_size, stat.st_mtime_ns, stat.st_ctime_ns


def _logical_text(body):
    text = body.decode("latin-1")
    text = re.sub(r"\?\?([=/'()!<>-])", lambda m: H.TRIGRAPHS[m[1]], text)
    text = re.sub(r"\\[ \t\f\v]*\r?\n", "", text)
    return H.COMMENT_OR_LITERAL.sub(
        lambda m: re.sub(r"[^\n]", " ", m[0]) if m[0].startswith("/") else m[0], text)


def _hash(path, *, retain=False):
    """Observe one generation; large ledgers and objects are hashed as streams."""
    try:
        before = path.stat()
        if not path.is_file() or path.is_symlink():
            raise InputRefused(f"not an ordinary input file: {path}")
        sha, md5, chunks = hashlib.sha256(), hashlib.md5(), []
        with path.open("rb") as stream:
            for block in iter(lambda: stream.read(1024 * 1024), b""):
                sha.update(block)
                md5.update(block)
                if retain:
                    chunks.append(block)
        if _stamp(before) != _stamp(path.stat()):
            raise InputRefused(f"input changed while reading: {path}")
    except OSError as exc:
        raise InputRefused(f"cannot read input {path}: {exc}") from exc
    return sha.hexdigest(), md5.hexdigest(), b"".join(chunks) if retain else None


@dataclass(frozen=True)
class CompilerInputs:
    fingerprint: str
    inventory: str | None
    forced: tuple[str, ...]
    reusable: bool


def _compiler_inputs(root, source, output, cache=None):
    """Actual build flags/search inputs, without compiling or accepting providers."""
    import build
    if Path(build.ROOT).resolve() != root:
        raise InputRefused("build command belongs to a different checkout")
    command, env = build.compiler_command(root / source, output)
    forced = []
    index = 0
    while index < len(command):
        arg = command[index]
        if arg in ("-FI", "/FI"):
            index += 1
            if index == len(command) or not command[index]:
                raise InputRefused(f"{source}: incomplete forced-include operand")
            forced.append(command[index])
        elif arg.startswith(("-FI", "/FI")):
            forced.append(arg[3:])
        index += 1
    inventory = build.search_inventory(root / source, command, env, inventory_cache=cache)
    reusable = build.compile_is_current(root / source, output, strict=True, inventory_cache=cache)
    return CompilerInputs(build._cmd_fingerprint(command, env), inventory, tuple(forced), reusable)


@dataclass(frozen=True)
class Snapshot:
    root: Path = field(repr=False)
    files: Mapping[str, str]
    tracked: tuple[str, ...]
    _compiler: Mapping[str, tuple[str, CompilerInputs]] = field(default_factory=dict, repr=False)

    def __post_init__(self):
        object.__setattr__(self, "root", Path(self.root).resolve())
        object.__setattr__(self, "files", MappingProxyType(dict(self.files)))
        object.__setattr__(self, "_compiler", MappingProxyType(dict(self._compiler)))

    def revalidate(self):
        if tuple(sorted(_tracked(self.root))) != self.tracked:
            raise InputRefused("tracked input population changed after discovery")
        for path, expected in self.files.items():
            host = Path(path) if Path(path).is_absolute() else self.root / path
            if _hash(host)[0] != expected:
                raise InputRefused(f"input changed after discovery: {path}")
        cache = {}
        for source, (output, expected) in self._compiler.items():
            try:
                current = _compiler_inputs(self.root, source, Path(output), cache)
            except (Exception, SystemExit) as exc:
                raise InputRefused(f"{source}: compiler inputs cannot be revalidated: {exc}") from exc
            if current != expected:
                raise InputRefused(f"{source}: compiler/search inputs changed after discovery")
        return True


@dataclass(frozen=True)
class Discovery(Snapshot):
    header: str = ""
    sources: tuple[str, ...] = ()
    mandatory: tuple[str, ...] = ()
    uncertainty: tuple[str, ...] = ()
    rebuildable: frozenset[str] = frozenset()


def _receipt_path(root, source):
    stem = "_".join(Path(source).with_suffix("").parts)
    encoded = "".join("^" + c.lower() if c.isupper() else c for c in stem)
    return root / "build" / "match" / (encoded + ".deps.json")


def discover(header, root=ROOT):
    """Freeze current tracked bytes and all possible function/data consumers.

    Missing or unbound receipts widen the population. A readable receipt adds
    positive include evidence even when stale; only a fully current receipt may
    exclude a source not reached by the conservative current-byte graph.
    """
    root = Path(root).resolve()
    header = _relative(header)
    modes = _tracked(root)
    if modes.get(header) not in ("100644", "100755"):
        raise InputRefused(f"canonical header is not a tracked ordinary file: {header}")
    files, observations = {}, {}

    def observe(path, retain=False):
        path = Path(path)
        sha, md5, raw = _hash(path, retain=retain)
        key = _key(root, path)
        if key in files and files[key] != sha:
            raise InputRefused(f"input changed during discovery: {key}")
        files[key] = sha
        observations[key] = md5
        return raw

    sources = set()
    for ledger in LEDGERS:
        if ledger not in modes:
            if ledger == LEDGERS[0] or (root / ledger).exists():
                raise InputRefused(f"ledger is not tracked: {ledger}")
            continue
        if modes[ledger] not in ("100644", "100755"):
            raise InputRefused(f"ledger is not an ordinary tracked file: {ledger}")
        observe(root / ledger)
        try:
            with (root / ledger).open(encoding="utf-8-sig", newline="") as stream:
                reader = csv.DictReader(stream)
                if not reader.fieldnames or "source" not in reader.fieldnames or len(reader.fieldnames) != len(set(reader.fieldnames)):
                    raise InputRefused(f"ledger has no unambiguous source column: {ledger}")
                for row in reader:
                    source = row.get("source")
                    if source and source.lower().endswith(H.SOURCE_SUFFIXES):
                        sources.add(_relative(source))
        except (OSError, UnicodeError, csv.Error) as exc:
            raise InputRefused(f"cannot read source population from {ledger}: {exc}") from exc
        observe(root / ledger)
    for source in sources:
        if modes.get(source) not in ("100644", "100755"):
            raise InputRefused(f"ledger source is not a tracked ordinary file: {source}")

    # Read effective bytes, never git's index blobs. Nonstandard include suffixes
    # join the scan to a fixed point when another scanned file names them.
    bodies = {}
    for path, mode in modes.items():
        if path.startswith(H.SCANNED_ROOTS) or path in sources or path == header:
            if mode == "160000":
                continue  # a submodule gitlink is not a parent-checkout file
            if mode not in ("100644", "100755"):
                raise InputRefused(f"include population has a nonordinary file: {path}")
            bodies[path] = observe(root / path, retain=True)
    logicals = {path: _logical_text(body) for path, body in bodies.items()}
    native_overridden = any(_NATIVE_DEFINE.search(body) for body in logicals.values())
    edges, macro, uncertainty = {}, set(), set()
    scan_uncertainty = set()
    pending = {path for path in bodies if path == header or path in sources or path.lower().endswith(H.HEADER_SUFFIXES + H.SOURCE_SUFFIXES)}
    scanned = set()
    def drain(pending):
        while pending:
            for path in sorted(pending):
                body = bodies[path]
                try:
                    if re.search(r"(?m)^[ \t\f\v]*%:", logicals[path]):
                        raise H.Widen(f"{path}: digraph directive needs wider discovery")
                    names, has_macro = H.read_whole(path, body)
                    edges.setdefault(path, set()).update(names)
                    if has_macro or native_overridden and _NATIVE_USE.search(logicals[path]):
                        macro.add(path)
                except H.Widen as exc:
                    uncertainty.add(str(exc))
                    scan_uncertainty.add(str(exc))
                scanned.add(path)
            referenced = set().union(*edges.values()) if edges else set()
            pending = {p for p in bodies if p not in scanned and H.name(p) in referenced}

    drain(pending)

    mandatory = set(H.dependents([header], H.graph(edges), macro)) & sources
    if scan_uncertainty:
        mandatory.update(sources)
    compiler, inventory_cache = {}, {}
    header_host = os.path.normcase(str((root / header).resolve()))
    for source in sorted(sources):
        receipt = _receipt_path(root, source)
        reason = None
        try:
            raw = observe(receipt, retain=True)
            meta = json.loads(raw)
            if not isinstance(meta, dict) or not isinstance(meta.get("deps"), dict):
                raise InputRefused("malformed dependency map")
            deps = meta["deps"]
            if any(not isinstance(p, str) or not p or "\0" in p for p in deps):
                raise InputRefused("invalid dependency path")
            for dep in deps:
                host = Path(dep) if Path(dep).is_absolute() else root / dep
                if os.path.normcase(str(host.resolve())) == header_host:
                    mandatory.add(source)
            if meta.get("path") != source:
                raise InputRefused("receipt belongs to another source")
            output = receipt.with_name(receipt.name[:-len(".deps.json")] + ".obj")
            state = _compiler_inputs(root, source, output, inventory_cache)
            edges.setdefault(source, set()).update(H.name(p) for p in state.forced)
            if not state.reusable:
                raise InputRefused("dependency receipt is not current with search inventory")
            observe(root / source)
            observe(output)
            if meta.get("source") != observations[source] or meta.get("object") != observations[_key(root, output)]:
                raise InputRefused("receipt does not bind the current source and object")
            for dep, expected in deps.items():
                host = Path(dep) if Path(dep).is_absolute() else root / dep
                observe(host)
                if not isinstance(expected, str) or expected != observations[_key(root, host)]:
                    raise InputRefused("dependency bytes differ from receipt")
            compiler[source] = (str(output), state)
        except (Exception, SystemExit) as exc:
            reason = str(exc)
        if reason is not None:
            mandatory.add(source)
            uncertainty.add(f"{source}: {reason}")
    # Actual command /FI inputs may first name a table or another nonstandard
    # suffix. Their newly reachable input closure must be scanned as well.
    referenced = set().union(*edges.values()) if edges else set()
    drain({p for p in bodies if p not in scanned and H.name(p) in referenced})
    mandatory.update(set(H.dependents([header], H.graph(edges), macro)) & sources)
    if scan_uncertainty:
        mandatory.update(sources)
    result = Discovery(root=root, files=files, tracked=tuple(sorted(modes)), _compiler=compiler,
                       header=header, sources=tuple(sorted(sources)), mandatory=tuple(sorted(mandatory)),
                       uncertainty=tuple(sorted(uncertainty)), rebuildable=frozenset(
                           _key(root, artifact) for source in sources
                           for artifact in (_receipt_path(root, source), _receipt_path(root, source).with_name(
                               _receipt_path(root, source).name[:-len(".deps.json")] + ".obj"))))
    result.revalidate()
    return result
