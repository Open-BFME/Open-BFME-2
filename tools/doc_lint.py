#!/usr/bin/env python3
"""Advisory checker for the Doxygen developer guide in docs/doxygen/.

The guide is hand-written for human developers and lives entirely under
docs/doxygen/ (docs/doxygen/README.md). This tool keeps it consistent with
the repository's tools and with the reconstruction. It is advisory: no hook
or CI job runs it, and it never edits anything.

Checks over every file in docs/doxygen/ (or the staged copies, --staged):

  tool-string  text that a repository tool parses out of source comments
               (build flags, STLport switch, escape hatches, declaration
               markers, crosslink and merge prefixes); never write it, even
               in prose, so no copy of a doc block can change a build
  address      hand-copied retail addresses (hex with five or more digits);
               refer to functions by name, the ledger has the address
  offset/size  hand-copied member offsets and ledger sizes (warnings)
  brace        braces in .dox prose, unbalanced braces in code examples
  page-id      the id scheme: pages/X.md is page_X, pages/subsystems/X.md
               is sub_X, api/X.dox defines \\defgroup grp_X
  ref          every \\ref, \\subpage and \\ingroup target that follows the
               id scheme is defined; \\file names a file in sources.cfg
  sources      sources.cfg lists existing files only (no directories, no
               generated or placeholder-named files)
  name         every \\fn, \\class and \\see target exists in the ledger
               (reverse/functions.csv) or in Code/ or reference/shims/, is
               not placeholder-named, and is not a WorldBuilder-lead name;
               Class::member mentions in prose are checked as warnings
  placeholder  address-named placeholder tokens in prose (warnings)
  placement    no .h/.cpp/.c/.asm under docs/ (the placement hook refuses
               them and a .h would trigger the full byte gate)

--doxygen also runs Doxygen and reports its warnings about docs/doxygen/
files: unresolved \\fn and \\class signatures, unknown \\ref targets, \\param
names that do not match.

  python3 tools/doc_lint.py                 # static checks
  python3 tools/doc_lint.py --doxygen       # plus a Doxygen run
  python3 tools/doc_lint.py --staged        # the staged change, docs-only
  python3 tools/doc_lint.py docs/doxygen/api/x.dox ...   # report these only

Exit status: 0 clean or warnings only, 1 errors (or warnings with --strict),
2 usage or tool failure.
"""
import argparse
import csv
import re
import shutil
import subprocess
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
DOCS = "docs/doxygen"
LEDGER = "reverse/functions.csv"
SOURCES_CFG = DOCS + "/sources.cfg"
DOXYFILE = DOCS + "/Doxyfile"
WARN_LOG = "build/doxygen/warnings.log"
TREE_ROOTS = ("Code", "reference/shims")
TREE_EXT = (".cpp", ".c", ".cc", ".cxx", ".h", ".hpp", ".inl")
TEXT_EXT = (".md", ".dox", ".cfg")
ALLOWED_EXT = TEXT_EXT + (".py",)
CODE_EXT = (".h", ".hpp", ".hh", ".hxx", ".inl", ".c", ".cc", ".cpp", ".cxx", ".asm")

# --------------------------------------------------------------------------- findings


class Finding:
    def __init__(self, path, line, level, code, message):
        self.path, self.line, self.level, self.code, self.message = path, line, level, code, message

    def __str__(self):
        where = "%s:%d" % (self.path, self.line) if self.line else self.path
        return "%s: %s: [%s] %s" % (where, self.level, self.code, self.message)


# --------------------------------------------------------------------------- tool-parsed text

TOOL_STRINGS = [
    (re.compile(r"//\s*stlport", re.I), "a stlport comment (build.py switches a unit to STLport on it)"),
    (re.compile(r"//\s*cl:"), "a cl: comment (build.py and header_dependents read compiler flags from it)"),
    (re.compile(r"__emit"), "__emit (conversion_gate and hatch_counters scan for it)"),
    (re.compile(r"__declspec\s*\(\s*naked"), "a naked declspec (conversion_gate scans for it)"),
    (re.compile(r"present-unmatched"), "a declaration marker word (find_declared_unmatched)"),
    (re.compile(r"absent-from-retail"), "a declaration marker word (find_declared_unmatched)"),
    (re.compile(r"class-gate:"), "a class_gate directive"),
    (re.compile(r"/alternatename:"), "an alternatename hatch (hatch_counters)"),
    (re.compile(r"#\s*pragma\s+optimize\s*\("), "an optimize pragma (hatch_counters)"),
]
# Comment prefixes that crosslink, merge_cluster, tu_skeleton and the ledger
# annotations own; a line that begins with one is read as that tool's data.
TOOL_PREFIXES = ("// byte-exact reconstruction:", "// readable body of",
                 "// upstream layout:", "// ?")
DOC_PREFIX = re.compile(r"^\s*(?:///<?|//!<?|/\*\*|/\*!|\*)?\s*")

ADDRESS = re.compile(r"\b0x[0-9A-Fa-f]{5,}\b|\b00[0-9A-Fa-f]{6}\b")
PLACEHOLDER_TOKEN = re.compile(r"\b(?:Rva|rva|d_|uw_)[0-9A-Fa-f]{6,}\w*")
OFFSET = re.compile(r"(?:\+\s*|\boffset\s+)0x[0-9A-Fa-f]+\b", re.I)
LEDGER_SIZE = re.compile(r"\b\d+\s?B\b")

# --------------------------------------------------------------------------- ids and refs

ID_PREFIXES = ("page_", "sub_", "grp_")
ANCHOR = re.compile(r"\{#([A-Za-z_][\w-]*)\}")
LABEL_CMD = re.compile(r"[\\@](page|section|subsection|subsubsection|paragraph|anchor|"
                       r"defgroup|addtogroup|weakgroup)\s+([A-Za-z_][\w-]*)")
REF_CMD = re.compile(r"[\\@](ref|subpage)\s+([A-Za-z_~][\w:~.-]*)")
INGROUP_CMD = re.compile(r"[\\@]ingroup((?:\s+[A-Za-z_]\w*)+)")
FILE_CMD = re.compile(r"[\\@]file\s+(\S+)")
FN_CMD = re.compile(r"[\\@]fn\s+(.+)$")
CLASS_CMD = re.compile(r"[\\@](?:class|struct|union)\s+([A-Za-z_][\w:]*)")
SEE_CMD = re.compile(r"[\\@](?:see|sa)\s+(.+)$")
QUALIFIED = re.compile(r"(?<![\w:])([A-Za-z_]\w*(?:::~?[A-Za-z_]\w*)+)")
HEADING = re.compile(r"^\s{0,3}#{1,6}\s+\S")
FENCE = re.compile(r"^\s*(```|~~~)")
CODE_OPEN = re.compile(r"[\\@](code|verbatim)\b")
CODE_CLOSE = re.compile(r"[\\@](endcode|endverbatim)\b")

# Placeholder names (staging areas and generated rows) are never documented.
PLACEHOLDER = re.compile(r"^(?:Rva|rva|Bfme|bfme|dup_|uw_|d_[0-9A-Fa-f]{6})|Rva[0-9A-Fa-f]{6}")
GENERATED_DIRS = ("Code/gen_asm/", "Code/gen_small/", "Code/masm_dumps/")
SKIP_SCOPES = ("std", "_STL")

# --------------------------------------------------------------------------- inputs


class WorkTree:
    """Reads docs/doxygen/ from the working tree."""

    def __init__(self, root):
        self.root = Path(root)

    def files(self):
        base = self.root / DOCS
        if not base.is_dir():
            return []
        return sorted(p.relative_to(self.root).as_posix() for p in base.rglob("*")
                      if p.is_file() and "__pycache__" not in p.parts)

    def read(self, rel):
        return (self.root / rel).read_bytes()


class Index:
    """Reads docs/doxygen/ as staged."""

    def __init__(self, root):
        self.root = Path(root)

    def files(self):
        out = git(self.root, "ls-files", "--cached", "--", DOCS)
        return sorted(line for line in out.splitlines() if line)

    def read(self, rel):
        return subprocess.run(["git", "show", ":" + rel], cwd=self.root, capture_output=True,
                              check=True).stdout


def git(root, *argv):
    return subprocess.run(("git",) + argv, cwd=root, capture_output=True, text=True,
                          check=True).stdout


def decode(data):
    try:
        return data.decode("utf-8")
    except UnicodeDecodeError:
        return data.decode("latin-1")


# --------------------------------------------------------------------------- per-file text checks


def check_text(rel, text):
    """Tool strings, addresses, offsets, sizes and non-ASCII text."""
    found = []
    for n, line in enumerate(text.splitlines(), 1):
        for pattern, why in TOOL_STRINGS:
            if pattern.search(line):
                found.append(Finding(rel, n, "error", "tool-string", "contains " + why))
        bare = line.lstrip()
        doc = DOC_PREFIX.sub("", line, count=1)
        if any(bare.startswith(p) or doc.startswith(p) for p in TOOL_PREFIXES):
            found.append(Finding(rel, n, "error", "tool-string",
                                 "begins with a comment prefix a repository tool reads as its own data"))
        if rel.endswith(".py"):
            continue
        if ADDRESS.search(line):
            found.append(Finding(rel, n, "error", "address",
                                 "looks like a retail address (%s); name the function instead, the "
                                 "ledger holds its address" % ADDRESS.search(line).group(0)))
        if PLACEHOLDER_TOKEN.search(line):
            found.append(Finding(rel, n, "warning", "placeholder",
                                 "%s is an address-named placeholder; placeholder code is not "
                                 "documented" % PLACEHOLDER_TOKEN.search(line).group(0)))
        if OFFSET.search(line):
            found.append(Finding(rel, n, "warning", "offset",
                                 "member offset (%s) goes stale as layouts are reconciled; describe "
                                 "the field by its role" % OFFSET.search(line).group(0).strip()))
        if LEDGER_SIZE.search(line):
            found.append(Finding(rel, n, "warning", "size",
                                 "'%s' looks like a ledger size; sizes change as rows are repaired"
                                 % LEDGER_SIZE.search(line).group(0)))
        if any(ord(c) > 126 or (ord(c) < 32 and c not in "\t\r") for c in line):
            found.append(Finding(rel, n, "warning", "ascii", "non-ASCII or control character"))
    return found


def check_braces(rel, text):
    """Braces in .dox prose; unbalanced braces in code examples."""
    found = []
    in_code = False
    start = 0
    depth = 0
    for n, line in enumerate(text.splitlines(), 1):
        body = line if rel.endswith(".md") else DOC_PREFIX.sub("", line, count=1)
        fence = bool(FENCE.match(body))
        if not in_code and (fence or CODE_OPEN.search(body)):
            in_code, start, depth = True, n, 0
            continue
        if in_code and (fence or CODE_CLOSE.search(body)):
            if depth:
                found.append(Finding(rel, start, "warning", "brace",
                                     "code example has unbalanced braces"))
            in_code = False
            continue
        if in_code:
            depth += line.count("{") - line.count("}")
        elif rel.endswith(".dox") and line.lstrip().startswith("///") and re.search(r"[{}]", line):
            found.append(Finding(rel, n, "warning", "brace",
                                 "brace in doc prose; source tools count braces in comments, so this "
                                 "block could not move into a source file"))
    if in_code:
        found.append(Finding(rel, start, "warning", "brace", "code example is never closed"))
    return found


# --------------------------------------------------------------------------- ids, refs and files


def labels_in(rel, text):
    """(label, line, kind) for every id the file defines."""
    out = []
    for n, line in enumerate(text.splitlines(), 1):
        if rel.endswith(".md"):
            for m in ANCHOR.finditer(line):
                out.append((m.group(1), n, "anchor"))
        for m in LABEL_CMD.finditer(line):
            out.append((m.group(2), n, m.group(1)))
    return out


def expected_id(rel):
    """The id a page file must carry, or None when the scheme does not name one."""
    path = Path(rel)
    parts = path.relative_to(DOCS).parts
    if path.suffix != ".md" or parts[0] != "pages":
        return None
    if len(parts) == 2:
        return "page_" + path.stem
    if len(parts) == 3 and parts[1] == "subsystems":
        return "sub_" + path.stem
    return None


def check_ids(texts):
    """The page-id scheme, duplicate ids, and \\ref/\\subpage/\\ingroup targets."""
    found = []
    defined = {"index": ("(doxygen main page)", 0)}
    groups = set()
    for rel, text in texts.items():
        if not rel.endswith((".md", ".dox")):
            continue
        labels = labels_in(rel, text)
        for label, n, kind in labels:
            if kind in ("defgroup", "addtogroup", "weakgroup"):
                groups.add(label)
                if kind != "defgroup":
                    continue
            if label in defined and kind != "addtogroup":
                found.append(Finding(rel, n, "error", "page-id",
                                     "id '%s' is already defined at %s:%d" % ((label,) + defined[label])))
            defined.setdefault(label, (rel, n))
            if not label.startswith(ID_PREFIXES):
                found.append(Finding(rel, n, "warning", "page-id",
                                     "id '%s' does not follow the scheme (page_, sub_ or grp_ prefix)" % label))
        want = expected_id(rel)
        if want is not None:
            first = next((n for n, line in enumerate(text.splitlines(), 1) if HEADING.match(line)), 0)
            heading_ids = [label for label, n, kind in labels if kind == "anchor" and n == first]
            if heading_ids != [want]:
                found.append(Finding(rel, first or 1, "error", "page-id",
                                     "first heading must carry {#%s}" % want))
            for label, n, kind in labels:
                if n != first and not label.startswith(want + "_"):
                    found.append(Finding(rel, n, "warning", "page-id",
                                         "section id '%s' should start with '%s_'" % (label, want)))
        elif rel.endswith(".md"):
            found.append(Finding(rel, 1, "warning", "page-id",
                                 "pages go in pages/ or pages/subsystems/ only"))
        stem = Path(rel).stem
        if rel.startswith(DOCS + "/api/") and rel.endswith(".dox") and stem != "README":
            own = [label for label, n, kind in labels if kind == "defgroup"]
            if "grp_" + stem not in own:
                found.append(Finding(rel, 1, "error", "page-id",
                                     "api/%s.dox must define \\defgroup grp_%s" % (stem, stem)))
            for label, n, kind in labels:
                if kind == "defgroup" and label != "grp_" + stem and not label.startswith("grp_%s_" % stem):
                    found.append(Finding(rel, n, "warning", "page-id",
                                         "group '%s' in api/%s.dox should be grp_%s_<topic>" % (label, stem, stem)))
    subsystem_pages = {Path(r).stem for r in texts if r.startswith(DOCS + "/pages/subsystems/") and r.endswith(".md")}
    api_files = {Path(r).stem for r in texts if r.startswith(DOCS + "/api/") and r.endswith(".dox")} - {"README"}
    for stem in sorted(subsystem_pages - api_files):
        found.append(Finding("%s/pages/subsystems/%s.md" % (DOCS, stem), 1, "warning", "page-id",
                             "subsystem page has no api/%s.dox group" % stem))
    for rel, text in texts.items():
        if not rel.endswith((".md", ".dox")):
            continue
        for n, line in enumerate(text.splitlines(), 1):
            for m in REF_CMD.finditer(line):
                target = m.group(2).rstrip(".,;:")
                if (target == "index" or target.startswith(ID_PREFIXES)) and target not in defined:
                    found.append(Finding(rel, n, "error", "ref", "\\%s target '%s' is not defined"
                                         % (m.group(1), target)))
            for m in INGROUP_CMD.finditer(line):
                for target in m.group(1).split():
                    if target not in groups:
                        found.append(Finding(rel, n, "error", "ref",
                                             "\\ingroup target '%s' is not a defined group" % target))
    return found


def read_sources_cfg(text):
    """[(line, path)] from the INPUT += lines, plus findings for malformed lines."""
    entries, found = [], []
    for n, line in enumerate(text.splitlines(), 1):
        s = line.strip()
        if not s or s.startswith("#"):
            continue
        m = re.match(r"^INPUT\s*\+=\s*(.+)$", s)
        if not m:
            found.append(Finding(SOURCES_CFG, n, "error", "sources", "only 'INPUT += <path>' lines belong here"))
            continue
        for path in m.group(1).split():
            entries.append((n, path.strip('"')))
    return entries, found


def check_sources(root, entries):
    found = []
    seen = {}
    for n, path in entries:
        where = (SOURCES_CFG, n)
        if path in seen:
            found.append(Finding(*where, "warning", "sources", "%s is already listed on line %d" % (path, seen[path])))
        seen.setdefault(path, n)
        if Path(path).is_absolute() or ".." in Path(path).parts:
            found.append(Finding(*where, "error", "sources", "%s: use a path relative to the repository root" % path))
            continue
        full = Path(root) / path
        if path.startswith(GENERATED_DIRS):
            found.append(Finding(*where, "error", "sources", "%s is generated placeholder code" % path))
        if PLACEHOLDER.search(Path(path).name):
            found.append(Finding(*where, "error", "sources", "%s is placeholder-named; it is not documented" % path))
        if full.is_dir():
            found.append(Finding(*where, "error", "sources", "%s is a directory; list files only" % path))
        elif not full.is_file():
            submodule = Path(root) / "reference" / "open-bfme-1"
            if path.startswith("reference/open-bfme-1/") and not any(submodule.iterdir() if submodule.is_dir() else []):
                found.append(Finding(*where, "warning", "sources", "%s: the BFME 1 submodule is not checked out" % path))
            else:
                found.append(Finding(*where, "error", "sources", "%s does not exist" % path))
    return found


def check_file_cmds(texts, entries):
    found = []
    listed = [path for n, path in entries]
    for rel, text in texts.items():
        if not rel.endswith((".md", ".dox")):
            continue
        for n, line in enumerate(text.splitlines(), 1):
            m = FILE_CMD.search(line)
            if m and not any(p == m.group(1) or p.endswith("/" + m.group(1)) for p in listed):
                found.append(Finding(rel, n, "error", "ref",
                                     "\\file %s names no file listed in sources.cfg" % m.group(1)))
    return found


def check_placement(root, files):
    found = []
    docs = Path(root) / "docs"
    for p in docs.rglob("*") if docs.is_dir() else []:
        if p.is_file() and p.suffix.lower() in CODE_EXT:
            found.append(Finding(p.relative_to(root).as_posix(), 0, "error", "placement",
                                 "source-file extension under docs/: the placement hook refuses it"))
    for rel in files:
        name = Path(rel).name
        if name not in ("Doxyfile", "README.md") and Path(rel).suffix.lower() not in ALLOWED_EXT \
                and Path(rel).suffix.lower() not in CODE_EXT:
            found.append(Finding(rel, 0, "warning", "placement",
                                 "unexpected file type in docs/doxygen/ (.md, .dox, .cfg, .py)"))
    return found


# --------------------------------------------------------------------------- names


def fn_name(signature):
    """The (possibly qualified) function name in a \\fn signature, or None."""
    head = signature.split("(", 1)[0]
    if "operator" in head or "(" not in signature:
        return None
    head = re.sub(r"<[^<>]*>", "", head).strip()
    m = re.search(r"([A-Za-z_~][\w:~]*)\s*$", head)
    return m.group(1) if m else None


def citations(texts, labels=()):
    """{(rel, line, name): strict} for every name the docs cite."""
    out = {}

    def add(rel, n, name, strict):
        name = name.strip().rstrip("().,;:")
        if not name or name.split("::")[0] in SKIP_SCOPES or name.startswith(ID_PREFIXES) or "." in name \
                or name in labels or name in ("index", "mainpage"):
            return
        if not re.match(r"^~?[A-Za-z_][\w:~]*$", name):
            return
        out[(rel, n, name)] = out.get((rel, n, name), False) or strict

    for rel, text in texts.items():
        if not rel.endswith((".md", ".dox")):
            continue
        for n, line in enumerate(text.splitlines(), 1):
            m = FN_CMD.search(line)
            if m:
                name = fn_name(m.group(1))
                if name:
                    add(rel, n, name, True)
            for m in CLASS_CMD.finditer(line):
                add(rel, n, m.group(1), True)
            m = SEE_CMD.search(line)
            if m:
                for item in m.group(1).split(","):
                    if item.strip():
                        add(rel, n, item.split()[0], True)
            for m in REF_CMD.finditer(line):
                add(rel, n, m.group(2), True)
            for m in QUALIFIED.finditer(line):
                add(rel, n, m.group(1), False)
    return out


def demangle(mangled):
    """(qualified names, class scopes) named by one ledger symbol, approximately."""
    if not mangled.startswith("?"):
        m = re.match(r"^[_@]?([A-Za-z_]\w*?)(?:@\d+)?$", mangled)
        names = {mangled}
        if m:
            names.add(m.group(1))
        return names, set()
    body = mangled[1:]
    special = None
    if body.startswith("?0"):
        special, body = "ctor", body[2:]
    elif body.startswith("?1"):
        special, body = "dtor", body[2:]
    elif body.startswith("?"):
        special, body = "op", body[3:] if body[1:2] == "_" else body[2:]
    parts = []
    i = 0
    while i < len(body) and body[i] != "@":
        if body.startswith("?$", i):
            j = body.find("@", i + 2)
            if j > i + 2:
                parts.append(body[i + 2:j])
            break
        j = body.find("@", i)
        if j < 0:
            break
        part = body[i:j]
        if part and not part[0].isdigit() and not part.startswith("?"):
            parts.append(part)
        i = j + 1
    if not parts:
        return set(), set()
    if special:
        scopes = list(reversed(parts))
        func = {"ctor": scopes[-1], "dtor": "~" + scopes[-1]}.get(special)
    else:
        func, scopes = parts[0], list(reversed(parts[1:]))
    names = set()
    if func:
        full = scopes + [func]
        for k in range(1, len(full) + 1):
            if k > 1 or not scopes:
                names.add("::".join(full[-k:]))
    return names, set(scopes)


def load_ledger(root):
    """{name: [tag sets]} and the set of class names, from reverse/functions.csv."""
    funcs, classes = {}, set()
    path = Path(root) / LEDGER
    if not path.is_file():
        return None, None
    with open(path, newline="", encoding="utf-8", errors="replace") as fh:
        reader = csv.reader(fh)
        header = next(reader)
        col = {name: k for k, name in enumerate(header)}
        for row in reader:
            if len(row) < len(header):
                continue
            notes, source = row[col["notes"]], row[col["source"]]
            tags = set()
            if "wb-name-unverified" in notes or "wb-lead" in notes:
                tags.add("wb")
            if re.search(r"\bT3\b", notes):
                tags.add("t3")
            if notes.startswith("gen-") or source.startswith(GENERATED_DIRS):
                tags.add("gen")
            names, scopes = demangle(row[col["name"]])
            for name in names:
                funcs.setdefault(name, []).append(frozenset(tags))
            classes.update(scopes)
    return funcs, classes


def tree_lookup(root, names):
    """The subset of names found in Code/ or reference/shims/ source text."""
    pending = {}
    for name in names:
        if "::" in name:
            cls, _, member = name.rpartition("::")
            last = cls.rpartition("::")[2]
            pending[name] = [re.compile(r"\b%s::%s\b" % (re.escape(last), re.escape(member))),
                             (re.compile(r"\b(?:class|struct|union)\s+%s\b" % re.escape(last)),
                              re.compile(r"(?<![\w~])%s\s*\(" % re.escape(member)))]
        else:
            pending[name] = [re.compile(r"\b(?:class|struct|union)\s+%s\b" % re.escape(name)),
                             re.compile(r"(?<![\w:])%s\s*\(" % re.escape(name))]
    found = set()
    for top in TREE_ROOTS:
        base = Path(root) / top
        if not base.is_dir():
            continue
        for path in base.rglob("*"):
            if not pending:
                return found
            if path.suffix.lower() not in TREE_EXT or not path.is_file():
                continue
            text = None
            for name in list(pending):
                key = name.rpartition("::")[2].lstrip("~")
                if text is None:
                    text = path.read_bytes().decode("latin-1")
                if key not in text:
                    continue
                for test in pending[name]:
                    hit = all(t.search(text) for t in test) if isinstance(test, tuple) else test.search(text)
                    if hit:
                        found.add(name)
                        del pending[name]
                        break
    return found


def check_names(root, texts):
    found = []
    labels = {label for rel, text in texts.items() for label, n, kind in labels_in(rel, text)}
    cited = citations(texts, labels)
    if not cited:
        return found
    funcs, classes = load_ledger(root)
    if funcs is None:
        return [Finding(LEDGER, 0, "warning", "name", "ledger not found; names were not checked")]
    unknown = set()
    for (rel, n, name), strict in sorted(cited.items()):
        parts = [p.lstrip("~") for p in name.split("::")]
        if any(PLACEHOLDER.search(p) for p in parts):
            found.append(Finding(rel, n, "error", "name",
                                 "%s is placeholder-named; placeholder code is not documented" % name))
            continue
        rows = funcs.get(name)
        if rows:
            if all("gen" in t for t in rows):
                found.append(Finding(rel, n, "error", "name", "%s names only generated placeholder rows" % name))
            elif all("wb" in t for t in rows):
                found.append(Finding(rel, n, "error", "name",
                                     "%s is a WorldBuilder-lead name not yet confirmed; skip it" % name))
            elif any("wb" in t for t in rows):
                found.append(Finding(rel, n, "warning", "name",
                                     "some ledger rows named %s are unconfirmed WorldBuilder leads; "
                                     "document only a confirmed one" % name))
            elif all("t3" in t for t in rows):
                found.append(Finding(rel, n, "warning", "name",
                                     "%s is a T3 (folded-address) name guess" % name))
            continue
        if "::" not in name and name in classes:
            continue
        unknown.add(name)
    present = tree_lookup(root, unknown) if unknown else set()
    for (rel, n, name), strict in sorted(cited.items()):
        if name in unknown and name not in present:
            found.append(Finding(rel, n, "error" if strict else "warning", "name",
                                 "%s is not in the ledger, Code/ or reference/shims/%s"
                                 % (name, "" if strict else "; if it is a Zero Hour name, say so")))
    return found


# --------------------------------------------------------------------------- doxygen


WARNING_START = re.compile(r"^(.*?):(\d+): (warning|error): (.*)$")


def parse_warnings(text):
    """[(path, line, level, message)] with continuation lines joined."""
    records = []
    for line in text.splitlines():
        m = WARNING_START.match(line)
        if m:
            records.append([m.group(1), int(m.group(2)), m.group(3), m.group(4)])
        elif records and line.strip():
            records[-1][3] += " " + line.strip()
    return [tuple(r) for r in records]


def doxygen_findings(root, log_text):
    found, elsewhere = [], 0
    docs = (Path(root) / DOCS).resolve()
    for path, line, level, message in parse_warnings(log_text):
        p = Path(path)
        p = (p if p.is_absolute() else Path(root) / p).resolve()
        if p == docs or docs in p.parents:
            found.append(Finding(p.relative_to(Path(root).resolve()).as_posix(), line, "error",
                                 "doxygen", message))
        else:
            elsewhere += 1
    if elsewhere:
        found.append(Finding(WARN_LOG, 0, "note", "doxygen",
                             "%d warning(s) about listed source files (declarations Doxygen could not "
                             "place); they matter only for members you document" % elsewhere))
    return found


def run_doxygen(root):
    if not shutil.which("doxygen"):
        return [Finding(DOXYFILE, 0, "error", "doxygen", "doxygen is not installed")]
    (Path(root) / "build" / "doxygen").mkdir(parents=True, exist_ok=True)
    proc = subprocess.run(["doxygen", DOXYFILE], cwd=root, capture_output=True, text=True)
    found = []
    if proc.returncode != 0:
        found.append(Finding(DOXYFILE, 0, "error", "doxygen",
                             "doxygen exited %d: %s" % (proc.returncode, proc.stderr.strip()[-500:])))
    log = Path(root) / WARN_LOG
    return found + doxygen_findings(root, log.read_text(errors="replace") if log.is_file() else "")


# --------------------------------------------------------------------------- staged scope


def check_staged_scope(root):
    found = []
    for path in git(root, "diff", "--cached", "--name-only").splitlines():
        if path.startswith(("Code/", "reference/", "reverse/")):
            found.append(Finding(path, 0, "error", "scope",
                                 "a documentation commit never touches Code/, reference/ or reverse/"))
    return found


# --------------------------------------------------------------------------- driver


def lint(root, source, run_doxy=False, names=True, staged=False):
    files = source.files()
    texts = {}
    for rel in files:
        if Path(rel).suffix.lower() in ALLOWED_EXT or Path(rel).name in ("Doxyfile",):
            texts[rel] = decode(source.read(rel))
    # Only pages/ and api/ are Doxygen input; README.md and the config files
    # get the text checks alone.
    inputs = {rel: text for rel, text in texts.items()
              if rel.startswith((DOCS + "/pages/", DOCS + "/api/")) and rel.endswith((".md", ".dox"))}
    found = []
    for rel, text in texts.items():
        found += check_text(rel, text)
    for rel, text in inputs.items():
        found += check_braces(rel, text)
    found += check_ids(inputs)
    entries, cfg_found = read_sources_cfg(texts.get(SOURCES_CFG, ""))
    found += cfg_found + check_sources(root, entries) + check_file_cmds(inputs, entries)
    found += check_placement(root, files)
    if names:
        found += check_names(root, inputs)
    if staged:
        found += check_staged_scope(root)
    if run_doxy:
        found += run_doxygen(root)
    return found


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__.split("\n\n")[0])
    ap.add_argument("files", nargs="*", help="report findings for these files only")
    ap.add_argument("--staged", action="store_true", help="lint the staged docs; refuse non-doc paths")
    ap.add_argument("--doxygen", action="store_true", help="also run doxygen and report its warnings")
    ap.add_argument("--no-names", action="store_true", help="skip the ledger and tree name checks")
    ap.add_argument("--strict", action="store_true", help="fail on warnings too")
    args = ap.parse_args(argv)
    source = Index(ROOT) if args.staged else WorkTree(ROOT)
    try:
        found = lint(ROOT, source, run_doxy=args.doxygen, names=not args.no_names, staged=args.staged)
    except (OSError, subprocess.CalledProcessError) as exc:
        print("doc_lint: %s" % exc, file=sys.stderr)
        return 2
    if args.files:
        wanted = {Path(f).resolve() for f in args.files}
        found = [f for f in found if (ROOT / f.path).resolve() in wanted]
    order = {"error": 0, "warning": 1, "note": 2}
    found.sort(key=lambda f: (f.path, f.line, order[f.level]))
    for f in found:
        print(f)
    errors = sum(f.level == "error" for f in found)
    warnings = sum(f.level == "warning" for f in found)
    print("doc_lint: %d error(s), %d warning(s)" % (errors, warnings), file=sys.stderr)
    return 1 if errors or (args.strict and warnings) else 0


if __name__ == "__main__":
    sys.exit(main())
