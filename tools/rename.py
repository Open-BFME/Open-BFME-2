#!/usr/bin/env python3
"""One verified rename per invocation, with its provenance in the ledger.

Renaming by hand is already a busy practice here (hundreds of Name/Rename
commits a week), and the byte gate cannot see most of what a hand rename
forgets. Names never reach the byte compare: build.py reads each body out of
the object by the row's MANGLED name and resolves every REL32 call through a
name -> address map built from functions.csv rows and symbols.csv pins. So a
rename that misses a caller's private declaration, a funclet's `parent=`
token, an `__ehhandler$<parent>` row, a pin, an `/alternatename` pragma or a
`present-unmatched` marker either fails some later gate far from the cause, or
-- worse -- passes every gate and breaks only the link (a stale pin keeps the
old name resolving; name_dependents then sees nothing "lost"). And
functions.csv union-merges, so a renamed-away (name, rva) without a
reverse/deleted_rows.csv tombstone can come back beside its successor, where
check_csv reads the pair as an ICF alias group. Only 9 of 240 recent rename
commits wrote that tombstone.

This tool makes the whole edit, verifies it, and records why:

  plan     every file, row, pin, note, marker and pragma the rename touches,
           computed in memory; `--dry-run` prints it and writes nothing;
  refuse   canonical names (retail exports, vendored= rows, .lib members,
           retail module class names, the retail RTTI exception classes,
           converged globals, evidence-tier names, anything spelled inside a
           string literal, anything name_basis.csv already records as
           canonical), a new name that collides or is itself a placeholder,
           an `inferred` basis replacing a real name, a generated source, a
           name a shrink-only baseline is keyed on, and a mangled-name change
           beyond the identifier (one exception: `function --virtual`, below);
  claim    every affected RVA, a `file:` scope for every Code/ or shim file
           written and `class:` for a class or member (tools/claims.py); claims
           this run newly took are KEPT for the lander, who releases them
           after the push (the command is printed), and released on failure;
  apply    under the ledger lock, after journalling the before-state to
           build/rename-journal/, then one ./build.sh over every touched
           ledger source (owner, callers, includers of a touched header) and
           the commit hooks' checks (check_csv, find_declared_unmatched, and
           class_gate, ledger_guard, code_identity_gate, link_debt,
           check_case_collisions, hatch_counters, data_check, eh_verify,
           pin_admission, pin_consistency, name_dependents on a private index
           holding the files written: commit_checks; the hook's other gates
           still run at commit);
           the rename stands only when all pass;
  restore  every touched file byte for byte on any failure, exception or
           SIGTERM; a run killed outright leaves its journal, and
           `rename.py recover` restores it (every run refuses to start while
           one is pending);
  record   a tombstone 'Renamed to <new> by tools/rename.py (<basis>)' for each
           renamed (name, rva) row, and one reverse/name_basis.csv row
           (kind,old,new,basis,evidence,source,rva).

Provenance is the owner's rule: a descriptive name that is not proven
canonical still gets a clean readable identifier, and the ledger -- not the
identifier -- says it is `inferred`. An inferred name may replace only a
placeholder or weak name (tools/name_metric.py's definition, shared rather
than copied); a canonical name may replace a placeholder or an inferred name;
nothing replaces a canonical name. A canonical function name may also take a
word another scope already spells, where every such spelling is provably a
scope the rewrite cannot reach (a member of an unrelated class, a local or
parameter of a function that never spells the old word, a prototype's
parameter): an inferred name is reverted by whole-word match and never shares
a word with the files it rewrites (the files outside the rewrite are not read
for it: a later revert refuses there rather than rewriting them), nor does a
canonical one share the word of an unreverted inferred landing.
Both bases are checked, never asserted:

  inferred   --evidence agree:<id> names a row of reverse/name_agreed.csv
             for this very rename, and the agreement is recomputed from the
             hashed votes in reverse/name_votes.csv (tools/name_agreement.py):
             one worker for an uncontested parameter/local, otherwise two
             distinct workers -- identities taken from the environment, not
             from a session label -- voted the spelling (or the same explicit
             scoped meaning), no
             rival spelling has as many, nothing disputed it. The record is an
             index, never the authority. A file may instead take mechanical:<rows>, a stem
             derived from a real-named row it owns. Refused, too, over a
             real-named pin, a WorldBuilder lead or an evidence-tier name at
             the address, and for a word only shaped like a placeholder that a
             Zero Hour, BFME 1 or vendored/SDK view declares.
  canonical  export, module, rtti, vendored/lib, file (an approved TU whose name is
             not provisional, or a retail __FILE__ path); wb, zh and bfme1 re-graded by
             tools/name_evidence.py's proof() -- the very rules that grade
             its candidates, so a hint never lands as a permanent name --
             with zh/bfme1 also citing a <path>:<line> that spells the name
             (never BFME 1's own ledgers, whose names agents chose; its
             ea_evidence.csv is EA's); string/assert citing the renamed
             function's own address in string_xrefs.tsv, whose string spells
             the word on word boundaries. Each verified.

When a rename respells a name another name_basis.csv record spells (a
method of a renamed class), a `carry` row moves that record with it.

After every `git pull --rebase` and before the push, the lane and the lander
run `rename.py check --range origin/master..HEAD`: a rename landed while
another seat added a pin, a caller or an extern with the old spelling passes
every gate (the byte gate masks DIR32, a stale pin keeps the old name
resolving) and breaks only the link; `check` refuses it.

A name that was spelled after its rename landed (a funclet row's `parent=`
token added by a seat working on a pre-rename tree) is carried forward by
`rename.py carry --all`: it replays every recorded rename over the notes
tokens of reverse/functions.csv (`parent=`, `parents=`, `icf-owner=`,
`dup-of=`, `object-symbol=`, prose), proves each respelling against the live
ledger (the old spelling names no row, pin or data row; the new one names
exactly one row, at the renamed function's RVA; a funclet's parent is in the
funclet's own source with its `__ehhandler$` row), changes only those notes
fields, and runs the same verify/rollback/journal path as a rename. It writes
no name_basis.csv row and no tombstone, and it refuses (exit 2, listed) what it
cannot prove.

Two kinds need more than a word rewrite. A `global` (one reverse/data_rows.csv
row) is invisible to the byte gate, which masks DIR32 operands: a consumer
left on the old extern still matches and only the link breaks, so consumers
are found by text and by object symbol table, and the rename refuses one it
cannot rewrite. Converged addresses (reverse/data_converged.csv) are never
renamed; reverse/data_ledger.csv, tool-written and protected, is reported
stale rather than edited. A `file` is a `git mv` within its directory (a move
across directories changes the region's default flags and the TU placement,
which are judgements) plus its path-keyed columns: functions.csv and
data_rows.csv `source`, tu_map.csv `source` and the docs/doxygen/sources.cfg
INPUT line. A unit keyed in a protected path-keyed register
(flag_overrides.csv, hatch_baseline.tsv, data_check_baseline.txt,
code_identity_baseline.tsv, data_ledger.csv) is refused as needing a
Verifier-Change commit, as is one that expands __FILE__ (the path reaches its
bytes), one another file #includes, and an approved retail TU path (a TU tu_map
approved under a provisional name is not one: its name still needs proof).

A `class` (one class/struct/union/enum token) is respelled as a whole token:
in every mangled name it scopes or types -- functions.csv names and notes
(`parent=`, `object-symbol=`), pins, data rows (`??_7X@@6B@`), funclet rows,
ctor/dtor/`??_G` rows, template arguments -- and in every source, header and
shim view that spells it, code and comments, plus the units whose objects
reference a renamed symbol. It refuses a word that is also a function or
datum identifier, a class registered in reverse/canonical_classes.csv (its
contract and class_gate key move in a class-reconciliation commit), and any
class that scopes an export, a vendored= or .lib row, an evidence-tier name or
a converged datum. Retail is /GR-, so no RTTI string carries a game class name.
A `member` (one non-static data member of one class) never reaches bytes:
every view declaring it and every file using it through a header view is
rewritten, a file that also declares the word for another class is refused.
A `param` or `local` is respelled inside one function body in one file, and
the rule asks only what the new spelling could capture and what the old one
could mean there. A local is refused in a file that compiles /Od (the `// cl:`
line, flag_overrides.csv and the region default, last /O winning), where a name
can reorder the frame. Either is refused when the function's own text already
spells the new word; when the unit spells it at file scope, as a member or in
a macro (the same spelling as a parameter or local of ANOTHER function is no
collision); or when the old word could mean an outer entity there: a global or
member visible to the function, a macro, a spelling after `->`, `.` or `::`.
An unrelated named class's member in the unit does not count when the
function's complete class/base chain is known; nested classes and unknown
bases retain the conservative refusal. An included
header decides only through a macro or a member of the function's class or a
base (an initializer list names a member beside the parameter of that name; a
base the headers never declare means any class's member counts): a header's
own parameters, locals, file-scope names and unrelated classes do not, and a
macro formal parameter binds only inside its macro. A local must also have
every spelling of its word inside the scope of one of its declarations (the
declaring block, or the statement whose `for`/`while`/`if`/`switch`/`catch`
header declares it): a spelling before the declaration, after its block or in
a sibling block may name a global, so it refuses. A unit or header that
spells either word and whose parentheses or braces do not balance (an
`#if`/`#else` split signature) cannot be classified and refuses too.
Their name_basis.csv rows are qualified (`Class::member`,
`Scope::function::param`), so a canonical record for one never protects an
unrelated name of the same spelling.

The tool never commits. It prints the files to stage and a suggested subject
('Rename <old> to <new> (<basis>)').

  python3 tools/rename.py function --rva 0x00658D50 --new readQuotedToken \\
      --basis inferred --evidence 'agree:<record>' --dry-run

  python3 tools/rename.py global --name '?g_00DFE9E0@@3UDisplayCriticalSection@@A' \\
      --new g_displayCriticalSection --basis inferred --evidence 'agree:<record>' --dry-run
  python3 tools/rename.py file --source Code/.../DrawableRva00278644.cpp \\
      --new Drawable_setAudible --basis inferred --evidence 'mechanical:<rows>' --dry-run

  python3 tools/rename.py class --name Rva0040ADDD --new AwardRecordView \\
      --basis inferred --evidence 'agree:<record>' --dry-run
  python3 tools/rename.py member --class Rva00362EC7 --member m_0C --new m_markerHandle \\
      --basis inferred --evidence 'agree:<record>' --dry-run
  python3 tools/rename.py local --source Code/.../BfmeCombine1236.cpp --function bfmeCombine1236 \\
      --name a4 --new rowScale --basis inferred --evidence 'agree:<record>' --dry-run

A landed inferred name that turns out wrong goes back through `revert`
(`rename.py revert --record <agreement id> --reason TEXT`, or the library's
revert()): basis `restored`, accepted only as the exact inverse of a
recorded inferred landing -- same kind and address, from the name's current
spelling (carry rows followed) to the placeholder it replaced. It is the one
rename whose new name may be a placeholder. The landing's tombstones leave
deleted_rows.csv (check_csv, a protected verifier, honours no other record;
teaching it to read `restored` rows is a Verifier-Change follow-up), the
landed name is tombstoned in turn, and the name_basis.csv row is append-only:
rename.py honours it if a union merge brings a lifted tombstone back, and
`check` reports that line.

`function --virtual` respells one row's decoration from non-virtual to
virtual (QAE->UAE, IAE->MAE, AAE->EAE; a destructor with its deleting
destructors), identifier, parameters and return type kept, and only when a
table retail code installs has a slot holding the row's address and that
table is the row's class's or a class's that a view derives from it (see
plan_virtual's section). It adds `virtual` to the class views that declare the
method, respells ledger rows, funclets, notes tokens, pins and spelled mangled
names, tombstones the old rows, carries a name_basis.csv record (the name's
basis is unchanged), and is byte-gated like any rename: a caller whose call
now goes through the vtable fails ./build.sh and everything is restored.

Kinds in this build: function, global, file, class, member, param, local;
plus `check`, `recover` and `revert`. Vendored and SDK sources (vendored= or .lib
rows, library directories, gamespy and Platform SDK shims) are refused for
every kind. The library API (plan_rename, apply_rename, is_placeholder,
is_protected, check_renames, recover) is what the lane tools call.
"""
import argparse
import collections
import hashlib
import base64
import concurrent.futures
import contextlib
import csv
import io
import json
import os
import posixpath
import re
import signal
import socket
import subprocess
import sys
import tempfile
import threading
import time
import uuid
from dataclasses import dataclass, field
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))

import ledger_io  # noqa: E402
import name_agreement  # noqa: E402
import name_metric  # noqa: E402
import tu_map  # noqa: E402

ROOT = Path(__file__).resolve().parents[1]
FUNCTIONS = "reverse/functions.csv"
SYMBOLS = "reverse/symbols.csv"
DATA_ROWS = "reverse/data_rows.csv"
DELETED = "reverse/deleted_rows.csv"
NAME_BASIS = "reverse/name_basis.csv"
NAME_BINDINGS = "reverse/name_bindings.csv"
NAME_BINDINGS_HEADER = "record,old,new,source,outer_sha256"
EXPORTS = "reverse/exports.csv"
NAME_TIERS = "reverse/name_tiers.csv"
CONVERGED = "reverse/data_converged.csv"
MODULES = "reverse/module_factory_registrations.csv"
DATA_LEDGER = "reverse/data_ledger.csv"
TU_MAP = "reverse/tu_map.csv"
LINK_STATUS = "reverse/link_status.csv"
SOURCES_CFG = "docs/doxygen/sources.cfg"
LOCK = "reverse/.add_match.lock"
NAME_BASIS_HEADER = "kind,old,new,basis,evidence,source,rva"
GENERATED = name_metric.GENERATED
SEARCH_ROOTS = ("Code", "reference/shims")
# The one donor gitlink whose explicitly quoted headers may prove a class's
# ancestry: reference/open-bfme-1, at the commit both the superproject's HEAD
# and index record. No other gitlink and no fallback path is trusted.
DONOR_GITLINK = "reference/open-bfme-1"
GIT_TIMEOUT = 30
HEADER_SUFFIXES = (".h", ".hpp", ".hh", ".hxx", ".inl", ".inc")
SOURCE_SUFFIXES = (".cpp", ".c")
# Files keyed by name that the verifier freeze forbids editing: a renamed debt
# row cannot be re-keyed there, so the excuse would silently stop applying.
FROZEN_KEYED = ("reverse/*baseline*", "reverse/*whitelist*", "reverse/data_ledger.csv")
# The retail RTTI names of game.dat's thrown exception classes (-GR- leaves
# no other game class RTTI): the type-name strings are retail bytes.
RTTI_CLASSES = frozenset({"INIException", "XferException", "FunctorNotSet", "DllHandle", "Exception",
                          "LoadFailure", "CAtlException", "_com_error", "exception", "type_info"})
# Machine-checked canonical evidence kinds (check_canonical). A harvested
# pin, a caller's guess, a table or a vtable shape is an inference, not
# proof: those go through the inferred (agreement) path. One table is the
# exception: iniblock, the retail INI block registration (token -> the exact
# parse callback INI::load dispatches to), recovered from game.dat by
# tools/ini_blocks.py into reverse/ini_blocks.tsv; it names that callback only.
CANONICAL_KINDS = frozenset({"export", "vendored", "lib", "rtti", "module", "string", "assert", "file",
                             "zh", "bfme1", "wb", "iniblock"})
AGREED = name_agreement.AGREED
AGREED_HEADER = ",".join(name_agreement.AGREED_COLUMNS)
BODY_OWNERS = "reverse/body_owners.csv"
WB_LEADS = "reverse/wb_name_leads.csv"
STRING_XREFS = "reverse/string_xrefs.tsv"
INI_BLOCKS = "reverse/ini_blocks.tsv"
BFME1 = "reference/open-bfme-1"
ZH_TREE = "inputs/reference/CnC_Generals_Zero_Hour"
# Third-party sources stay pristine: their names are upstream's (vendored=).
VENDORED_DIRS = ("Code/Libraries/Source/Lua/", "Code/Libraries/Source/Compression/ZLib/",
                 "Code/Libraries/Source/ATL/", "Code/Libraries/Source/GdiPlus/", "Code/Libraries/Source/DirectX/",
                 "Code/Libraries/Source/CRT/", "Code/GameEngine/Source/GameNetwork/GameSpy/gp/",
                 "Code/GameEngine/Source/GameNetwork/GameSpy/gstats/",
                 "Code/GameEngine/Source/GameNetwork/GameSpy/ghttp/",
                 "Code/GameEngine/Source/GameNetwork/GameSpy/serverbrowsing/", "vendor/",
                 "reference/shims/gamespy/")
# Platform SDK, DirectX, CRT and middleware views among the shims.
SDK_HEADER = re.compile(r"(?i)(?:win\w*|windowsx?|d3d\w*|ddraw|dinput\w*|dsound|dxerr\w*|mmsystem|mmreg|objbase"
                        r"|ocidl|ole\w*|shellapi|shlguid|shlobj|commctrl|comdef|comutil|atl\w*|dbghelp|imagehlp"
                        r"|lmcons|mapicode|netdb|process|direct|vfw|snmp|wmsdk|fstream|bink|mss|unknwn|wtypes"
                        r"|guiddef|basetsd|tchar|io|malloc|stdio|stdlib|string|math|time|limits|float|ctype"
                        r"|errno|assert|new|xstddef|excpt|stdarg|memory)\.h")
BASIS_RE = re.compile(r"inferred|restored|canonical:([a-z0-9-]+)")
# The one basis that may put a placeholder back: the exact inverse of a
# recorded inferred rename (revert()), evidence `revert:<agreement id> <reason>`.
RESTORED = "restored"
REVERT_RE = re.compile(r"revert:([A-Za-z0-9_.:-]+)(?:\s+(\S.*))?")
LANDED_TOMBSTONE = re.compile(r"Renamed to (\S+) by tools/rename\.py \(inferred\)")
IDENT = re.compile(r"[A-Za-z_][A-Za-z0-9_]*")
# A source split into the parts a rename treats differently. Literals end at a
# newline as the compiler's do, so a stray quote cannot swallow the file.
SEGMENT = re.compile(r'//[^\n]*|/\*.*?\*/|"(?:\\.|[^"\\\n])*"|\'(?:\\.|[^\'\\\n])*\'', re.S)
PRAGMA_LINKER = re.compile(r"[ \t]*#[ \t]*pragma[ \t]+comment[ \t]*\([ \t]*linker\b")
MARKER_WORDS = ("present-unmatched", "absent-from-retail")
# `__identifier("?mangled")` names a symbol, not text: it is a code reference
# (thousands of Code/ call sites take a function's address this way).
IDENTIFIER_CALL = re.compile(r"__identifier\s*\(\s*$")


def identifier_string(text, start):
    """True when the string literal at `start` is an __identifier(...) argument."""
    return IDENTIFIER_CALL.search(text, max(0, start - 64), start) is not None
# Path-keyed ledger columns a file rename repoints.
PATH_COLUMNS = (("reverse/functions.csv", "source"), ("reverse/data_rows.csv", "source"),
                ("reverse/tu_map.csv", "source"), ("reverse/body_owners.csv", "source"),
                ("reverse/header_queue.tsv", "source"))
# Path-keyed files a phase-1 file rename may not re-key: tool-owned or
# shrink-only (tools/protected_paths.py), so re-keying is a Verifier-Change commit.
PROTECTED_PATH_KEYED = ("reverse/flag_overrides.csv", "reverse/hatch_baseline.tsv",
                        "reverse/data_check_baseline.txt", "reverse/code_identity_baseline.tsv",
                        "reverse/data_ledger.csv")
IMAGE_BASE = 0x400000
# Characters that continue a mangled or C symbol on either side.
SYMBOL_CHAR = r"A-Za-z0-9_?@"


class Refusal(Exception):
    """The rename is refused; the message says why. Nothing was written."""


class VerifyFailed(Exception):
    """./build.sh did not report every touched source OK; everything was restored."""


# ---------------------------------------------------------------- shared rules

def is_placeholder(name, kind="function"):
    """True for a placeholder or weak identifier (tools/name_metric.py's
    definition: address/bfme/hex-run/offset/decompiler names, and for params
    and locals weak single letters and tmp/arg names). A mangled function name
    is judged by its identifier."""
    if kind == "function" and (name.startswith("?") or "@" in name):
        try:
            name = split_function_name(name)[1]
        except Refusal:
            return False
    return bool(name_metric.weak(kind, name))


def basis_kind(basis):
    """'inferred', 'canonical' or 'restored'; raises Refusal on anything else."""
    match = BASIS_RE.fullmatch(basis or "")
    if not match:
        raise Refusal(f"--basis must be 'inferred' or 'canonical:<evidence-kind>', got {basis!r}")
    if basis == RESTORED:
        return RESTORED
    if match.group(1) is not None:
        if match.group(1) not in CANONICAL_KINDS:
            raise Refusal(f"unknown canonical evidence kind {match.group(1)!r}; "
                          f"one of {', '.join(sorted(CANONICAL_KINDS))}")
        return "canonical"
    return "inferred"


def mangled_re(name):
    """`name` as a whole symbol: not part of a longer mangled or C name. `$`
    is a boundary, so `__ehhandler$<name>` and `__unwindfunclet$<name>$0` match;
    so is a local static's nested scope (`?s@?1??<name>@4HA`)."""
    return re.compile(r"(?<![%s])%s(?![%s])|(?<=\?[0-9]\?)%s(?=@)" % (
        SYMBOL_CHAR, re.escape(name), SYMBOL_CHAR, re.escape(name)))


def word_re(word):
    return re.compile(r"\b%s\b" % re.escape(word))


def split_function_name(mangled):
    """(prefix, identifier, suffix) of a function symbol whose identifier a
    rename may respell: `?ident@...` or a C name (`_ident`, `_ident@8`,
    `@ident@8`, `ident`). Special members, operators, templates and compiler
    labels are refused: their identifier is a class, or not text at all."""
    match = re.fullmatch(r"(\?)([A-Za-z_][A-Za-z0-9_]*)(@.+)", mangled)
    if match:
        return match.groups()
    if mangled.startswith("?"):
        raise Refusal(f"{mangled} is a special member, operator or template function; "
                      "its identifier is not a plain name (rename its class instead)")
    match = re.fullmatch(r"([_@]?)([A-Za-z_][A-Za-z0-9_]*?)((?:@\d+)?)", mangled)
    if match and not mangled.startswith(("__ehhandler$", "__unwindfunclet$")):
        return match.groups()
    raise Refusal(f"{mangled} is not a function name this tool can respell")


def refers_to_identifier(mangled, suffix):
    """True when `?ident@suffix` back-references its identifier (name fragment
    0) or cannot be read well enough to say it does not. The parser reads the
    NAME positions of the symbol: a `0` there is the name back-reference, while
    the same digit in a TYPE position (`PAUS@@0@Z`: the second argument has the
    first one's type) leaves the name table alone, so respelling the identifier
    changes nothing after it. A symbol outside the parser's subset keeps the
    textual test, which cannot tell the two apart and so refuses both."""
    refs = []
    try:
        fragments(mangled, refs=refs)
    except Unparsed:
        return bool(re.search(r"(?:[VUT]|W4|@)0@", suffix))
    return 0 in refs


def rename_function_symbol(mangled, new_ident):
    """`mangled` with only its identifier respelled; refuses when MSVC's
    name back-references would make the compiler spell the result differently
    (the identifier is name fragment 0: a later `V0@`/`U0@`/`W40@`/`@0@`
    refers to it, and a later fragment spelled like the new identifier would
    become such a reference)."""
    prefix, old_ident, suffix = split_function_name(mangled)
    if prefix == "?":
        if refers_to_identifier(mangled, suffix):
            raise Refusal(f"{mangled}: a back-reference to the identifier (fragment 0) follows it; "
                          "respelling it would change the rest of the signature")
        if re.search(r"(?<![A-Za-z0-9_])%s@" % re.escape(new_ident), suffix) or \
                re.search(r"[VUT]%s@" % re.escape(new_ident), suffix):
            raise Refusal(f"{mangled}: {new_ident} already names a fragment of the signature; "
                          "the compiler would encode it as a back-reference")
        if re.search(r"[VUT@]%s@" % re.escape(old_ident), suffix):
            raise Refusal(f"{mangled}: {old_ident} also names a scope or type in the signature")
    return prefix + new_ident + suffix


class Unparsed(ValueError):
    """A mangled name outside the subset `fragments` reads."""


FUNCLET_PREFIXES = ("__ehhandler$", "__unwindfunclet$")


class _Out(list):
    """fragments' output list; `refs` (when set) also collects the digit of
    every name back-reference the parser meets in a name position."""
    refs = None


def fragments(symbol, refs=None):
    """(start, end) of every name fragment of `symbol` -- each identifier of
    a qualified name, template name and C name -- in order. A class token is
    only ever one whole fragment, so `TBar` (a struct named TBar: `PAUTBar@@`)
    and the method `UBar` (`?UBar@Zed@@`) never contain the class Bar, which a
    lookbehind on V/U/T cannot tell apart. Raises Unparsed outside the MSVC
    7.1 subset the ledger uses; callers refuse rather than guess."""
    offset = 0
    for prefix in FUNCLET_PREFIXES:
        if symbol.startswith(prefix):
            offset = len(prefix)
    text = symbol[offset:]
    if not text.startswith("?"):
        match = re.fullmatch(r"[_@]?([A-Za-z_][A-Za-z0-9_]*?)(?:[@$][A-Za-z0-9_]+)?", text)
        if not match:
            raise Unparsed(symbol)
        return [(offset + match.start(1), offset + match.end(1))]
    out = _Out()
    out.refs = refs
    try:
        end = _parse_symbol(text, 0, out)
    except (IndexError, ValueError) as error:
        raise Unparsed(f"{symbol}: {error}") from None
    if text[end:] and not (offset and re.fullmatch(r"\$\d+", text[end:])):
        raise Unparsed(f"{symbol}: trailing {text[end:]!r}")
    return [(offset + a, offset + b) for a, b in out]


def _parse_symbol(s, i, out):
    if s[i] != "?":
        raise ValueError(f"symbol expected at {i}")
    i += 1
    if s[i] == "?" and s[i + 1] != "$":
        i += 1
        if s.startswith("__", i):
            i += 3
            if s[i] == "?":                              # ??__E?data@..@@YAXXZ: a nested symbol
                i = _parse_symbol(s, i, out)
                if s[i] != "@":
                    raise ValueError("dynamic initializer")
                return _parse_header(s, _parse_qualified(s, i + 1, out), out)
        elif s.startswith("_R0", i):
            i = _parse_type(s, i + 3, out)
            if not s.startswith("@8", i):
                raise ValueError("RTTI type descriptor")
            return i + 2
        elif s[i] == "_":
            if s.startswith("_R", i):
                raise ValueError("RTTI name")
            i += 2
        else:
            i += 1
    i = _parse_qualified(s, i, out)
    return _parse_header(s, i, out)


def _parse_qualified(s, i, out):
    """Fragments up to the terminating `@`; returns the index after it."""
    while True:
        c = s[i]
        if c == "@":
            return i + 1
        if c.isdigit():
            if out.refs is not None:
                out.refs.append(int(c))
            i += 1
        elif s.startswith("?$?", i):                    # template operator / special member
            k = i + 3
            k += 2 if s[k] == "_" else 1
            i = _parse_template_args(s, k, out)
        elif s.startswith("?$", i):
            j = s.index("@", i + 2)
            out.append((i + 2, j))
            i = _parse_template_args(s, j + 1, out)
        elif c == "?":
            if s[i + 1] == "A":                  # anonymous namespace ?A0x...@
                i = s.index("@", i) + 1
            elif s[i + 1].isdigit() and s[i + 2] == "?":   # ?1? + a nested function symbol
                i = _parse_symbol(s, i + 3, out)
            else:
                raise ValueError(f"scope at {i}")
        elif c.isalpha() or c == "_":
            j = s.index("@", i)
            if not IDENT.fullmatch(s[i:j]):
                raise ValueError(f"fragment {s[i:j]!r}")
            out.append((i, j))
            i = j + 1
        else:
            raise ValueError(f"name at {i}")


def _parse_template_args(s, i, out):
    while s[i] != "@":
        i = _parse_type(s, i, out)
    return i + 1


def _number_value(s, i):
    """(value, next index) of an encoded number."""
    sign = 1
    if s[i] == "?":
        sign, i = -1, i + 1
    if s[i].isdigit():
        return sign * (int(s[i]) + 1), i + 1
    j, value = i, 0
    while s[j] in "ABCDEFGHIJKLMNOP":
        value = value * 16 + "ABCDEFGHIJKLMNOP".index(s[j])
        j += 1
    if s[j] != "@":
        raise ValueError(f"number at {i}")
    return sign * value, j + 1


def _parse_number(s, i):
    if s[i] == "?":
        i += 1
    if s[i].isdigit():
        return i + 1
    j = i
    while s[j] in "ABCDEFGHIJKLMNOP":
        j += 1
    if s[j] != "@":
        raise ValueError(f"number at {i}")
    return j + 1


def _parse_function(s, i, out):
    """Return type, arguments and throw spec, after the calling convention."""
    i = i + 1 if s[i] == "@" else _parse_type(s, i, out)
    if s[i] == "X":
        i += 1
    else:
        while s[i] not in "@Z":
            i = _parse_type(s, i, out)
        i += 1
    if s[i] != "Z":
        raise ValueError(f"throw spec at {i}")
    return i + 1


def _parse_type(s, i, out):
    c = s[i]
    if c in "PQRSAB" and s[i + 1] == "6":                   # function pointer
        return _parse_function(s, i + 3, out)
    if c in "PQRSAB" and s[i + 1] == "8":                   # member function pointer
        i = _parse_qualified(s, i + 2, out)
        return _parse_function(s, i + 2, out)
    if c in "PQRSAB":
        i += 1
        if s[i] == "E":
            i += 1
        if s[i] not in "ABCD":
            raise ValueError(f"pointer cv at {i}")
        return _parse_type(s, i + 1, out)
    if c in "VUT":
        return _parse_qualified(s, i + 1, out)
    if c == "W" and s[i + 1].isdigit():
        return _parse_qualified(s, i + 2, out)
    if c == "?" and s[i + 1] in "AB":
        return _parse_type(s, i + 2, out)
    if c == "_" and s[i + 1].isalpha():
        return i + 2
    if s.startswith("$$C", i) and s[i + 3] in "ABCD":
        return _parse_type(s, i + 4, out)
    if s.startswith("$0", i):
        return _parse_number(s, i + 2)
    if s.startswith(("$1", "$E"), i):
        return _parse_symbol(s, i + 2, out)
    if c == "Y":                                            # array: dimension count, dimensions
        count, i = _number_value(s, i + 1)
        for _ in range(count):
            i = _parse_number(s, i)
        return _parse_type(s, i, out)
    if c.isdigit() or c in "CDEFGHIJKMNOXZ":
        return i + 1
    raise ValueError(f"type {c!r} at {i}")


def _parse_header(s, i, out):
    if i == len(s):
        return i
    c = s[i]
    if c in "01234":                                         # data: type, cv
        i = _parse_type(s, i + 1, out)
        if s[i] == "E":
            i += 1
        if s[i] not in "ABCD":
            raise ValueError(f"data cv at {i}")
        return i + 1
    if c in "67":                                            # vftable / vbtable
        i += 2
        while s[i] != "@":
            i = _parse_qualified(s, i, out)
        return i + 1
    if c == "8":
        return i + 1
    if c in "YZ":
        return _parse_function(s, i + 2, out)
    if c in "CDKLST":
        return _parse_function(s, i + 2, out)
    if c in "ABEFIJMNQRUV":
        i += 1
        if s[i] == "E":
            i += 1
        return _parse_function(s, i + 2, out)
    if c in "GHOPWX":
        i = _parse_number(s, i + 1)
        return _parse_function(s, i + 2, out)
    if c == "$" and s[i + 1] in "012345":                    # vtordisp thunk: two numbers
        i = _parse_number(s, _parse_number(s, i + 2))
        return _parse_function(s, i + 2, out)
    raise ValueError(f"header {c!r} at {i}")


def leading_fragment(symbol):
    """The identifier fragment of `?ident@...` or a C name, else None: the
    first fragment of a special member (`??0X`, `??1X`, `??_GX`, `??RX`) is
    its class, not an identifier."""
    text = symbol
    for prefix in FUNCLET_PREFIXES:
        if text.startswith(prefix):
            text = text[len(prefix):]
    if text.startswith("??"):
        return None
    try:
        spans = fragments(text)
    except Unparsed:
        return None
    return text[spans[0][0]:spans[0][1]] if spans else None


SYMBOL_TOKEN = re.compile(r"(?:__ehhandler\$|__unwindfunclet\$)?\?[A-Za-z0-9_?@$]+")


def class_spans(symbol, word):
    """Spans of `symbol`'s fragments spelling the type `word` (not its
    leading identifier). Raises Unparsed when `symbol` spells `word@` and
    cannot be read."""
    if f"{word}@" not in symbol:
        return []
    spans = fragments(symbol)
    lead = 0
    body = symbol
    for prefix in FUNCLET_PREFIXES:
        if body.startswith(prefix):
            body = body[len(prefix):]
    if body.startswith("?") and not body.startswith("??"):
        lead = 1
    return [(a, b) for a, b in spans[lead:] if symbol[a:b] == word]


def class_sub(text, word, new):
    """`text` with every mangled symbol in it respelling the type fragment
    `word` as `new`; returns (text, count). Raises Unparsed for a symbol that
    spells `word@` and cannot be tokenized."""
    out, last, count = [], 0, 0
    for match in SYMBOL_TOKEN.finditer(text):
        symbol = match.group(0)
        spans = class_spans(symbol, word)
        if not spans:
            continue
        pieces, prev = [], 0
        for a, b in spans:
            pieces += [symbol[prev:a], new]
            prev = b
        pieces.append(symbol[prev:])
        out += [text[last:match.start()], "".join(pieces)]
        last = match.end()
        count += len(spans)
    out.append(text[last:])
    return "".join(out), count


class ClassToken:
    """`class_sub` with the interface of a compiled regex (`search`, `sub`,
    `subn`), for the ledger and pragma rewrites."""

    def __init__(self, word):
        self.word = word

    def subn(self, new, text):
        try:
            return class_sub(text, self.word, new if isinstance(new, str) else new(None))
        except Unparsed as error:
            raise Refusal(f"cannot tokenize a mangled name spelling {self.word}: {error}") from None

    def sub(self, new, text):
        return self.subn(new, text)[0]

    def search(self, text):
        return self.subn(self.word + "\0", text)[1] > 0


def check_new_identifier(new, kind, basis=None):
    """A new name is an identifier, not a keyword, and not a placeholder --
    except under basis `restored`, which puts back the exact placeholder a
    recorded inferred rename replaced (check_restore proves it is that one)."""
    if not IDENT.fullmatch(new or ""):
        raise Refusal(f"new name {new!r} is not a C++ identifier")
    if new in name_metric.KEYWORDS:
        raise Refusal(f"new name {new!r} is a keyword")
    if basis != RESTORED and is_placeholder(new, kind):
        raise Refusal(f"new name {new} is itself a placeholder or weak name")


# ---------------------------------------------------------------- the tree

class Context:
    """The tree a rename reads and writes. Everything is relative to `root`;
    tests point it at a temporary git repository with miniature ledgers."""

    def __init__(self, root=ROOT, object_scan=True, sweep_dirs=("build",)):
        self.root = Path(root).resolve()
        self.object_scan = object_scan and self.root == ROOT.resolve()
        # where tools/name_evidence.py finds the zh/bfme1 sweep caches
        self.sweep_dirs = tuple(sweep_dirs)
        self._cache = {}
        # files earlier plans of this run wrote and kept (a rename_files run applies
        # batch after batch before anything is staged): the commit will contain them
        self.kept = set()

    def path(self, rel):
        return self.root / rel

    def read(self, rel):
        path = self.path(rel)
        return path.read_bytes() if path.exists() else None

    def dicts(self, rel):
        if rel not in self._cache:
            raw = self.read(rel)
            self._cache[rel] = list(csv.DictReader(io.StringIO(raw.decode("utf-8")))) if raw else []
        return self._cache[rel]

    def rows(self):
        return self.dicts(FUNCTIONS)

    def pins(self):
        return self.dicts(SYMBOLS)

    def git(self, *args):
        result = subprocess.run(["git", "-C", str(self.root), *args], capture_output=True, text=True)
        if result.returncode not in (0, 1):
            raise Refusal(f"git {' '.join(args[:2])} failed: {result.stderr.strip()[:200]}")
        return result.stdout

    def grep_files(self, needle, *, word=False, roots=SEARCH_ROOTS):
        """Tracked files under `roots` containing `needle` (fixed string)."""
        args = ["grep", "-l", "-F", "-I"] + (["-w"] if word else []) + ["-e", needle, "--", *roots]
        return sorted(p for p in self.git(*args).splitlines() if p)

    def ledger_sources(self):
        if "_sources" not in self._cache:
            self._cache["_sources"] = {r["source"] for r in self.rows() if r.get("status") == "matched"}
        return self._cache["_sources"]


def is_generated(rel):
    return rel.replace("\\", "/").startswith(GENERATED)


def name_basis_rows(ctx):
    return ctx.dicts(NAME_BASIS)


def recorded_basis(ctx, name):
    """The basis name_basis.csv last recorded for `name` as a NEW name, or None."""
    found = None
    for row in name_basis_rows(ctx):
        if row.get("new") == name:
            found = row.get("basis")
    return found


def current_records(ctx):
    """{spelling: last name_basis.csv row recording it as a new name}."""
    out = {}
    for row in name_basis_rows(ctx):
        if row.get("new"):
            out[row["new"]] = row
    return out


def carry_records(ctx, plan, transform):
    """Append a `carry` row for every name_basis.csv record whose spelling
    this rename changes (a method of a renamed class, a param of a renamed
    function): protection and provenance are looked up by spelling, so a
    record left on the old spelling would silently lapse."""
    lines = []
    for spelling, row in current_records(ctx).items():
        if spelling in (plan.old, plan.new):
            continue
        moved = transform(spelling)
        if moved and moved != spelling:
            plan.carried.append((spelling, moved, row.get("basis", "")))
            lines.append(csv_line(["carry", spelling, moved, row.get("basis", ""),
                                   f"scope renamed by {plan.subject()}", row.get("source", ""), row.get("rva", "")]))
    if lines:
        plan.edit(ctx, NAME_BASIS, appended(plan.after.get(NAME_BASIS, ctx.read(NAME_BASIS)), lines,
                                            header=NAME_BASIS_HEADER))


def is_protected(ctx, kind, name, *, rva=None, identifier=None):
    """Why `name` (mangled for a function) is canonical and may not be renamed,
    or None. `identifier` is the bare word the rename respells. A class is
    judged by every mangled name it scopes (class_protected); a member, param
    or local (qualified `Scope::name`) only by name_basis.csv."""
    if kind == "class":
        return class_protected(ctx, name)
    if kind in ("member", "param", "local"):
        basis = recorded_basis(ctx, name)
        if basis and basis.startswith("canonical"):
            return f"{name} is recorded canonical ({basis}) in reverse/name_basis.csv"
        return None
    ident = identifier or name
    if any(row.get("name") == name for row in ctx.dicts(EXPORTS)):
        return f"{name} is a retail export (reverse/exports.csv)"
    for row in ctx.rows():
        if row.get("name") != name:
            continue
        notes = row.get("notes", "")
        if "vendored=" in notes:
            return f"{name} is a vendored= row (upstream's real identity)"
        if row.get("source", "").lower().endswith(".lib"):
            return f"{name} is a .lib member"
    for row in ctx.dicts(NAME_TIERS):
        if row.get("name") == name and row.get("name_tier") == "evidence":
            return f"{name} is evidence-tier in reverse/name_tiers.csv ({row.get('evidence')})"
    if ident in RTTI_CLASSES:
        return f"{ident} is a retail RTTI exception class name"
    if any(row.get("name") == ident for row in ctx.dicts(MODULES)):
        return f"{ident} is a retail module class name (reverse/module_factory_registrations.csv)"
    if any(row.get("name") == name for row in ctx.dicts(CONVERGED)):
        return f"{name} is a converged global (reverse/data_converged.csv)"
    for candidate in {name, ident}:
        basis = recorded_basis(ctx, candidate)
        if basis and basis.startswith("canonical"):
            return f"{candidate} is recorded canonical ({basis}) in reverse/name_basis.csv"
    return None


# ---------------------------------------------------------------- text rewrite

def rewrite_source(text, word, new_word, old_symbol, new_symbol):
    """Respell `word` in code, `old_symbol` in comments and linker pragmas, and
    `word` in present-unmatched/absent-from-retail markers. Returns
    (text, counts, string_hits): a string literal that still spells `word`
    afterwards is retail-locked text the rename must not touch."""
    words, symbol = word_re(word), mangled_re(old_symbol)
    out, last, string_hits = [], 0, []
    counts = {"code": 0, "comment": 0, "pragma": 0}

    def code(part):
        new, n = words.subn(new_word, part)
        counts["code"] += n
        return new

    for match in SEGMENT.finditer(text):
        out.append(code(text[last:match.start()]))
        seg = match.group(0)
        if seg.startswith(("//", "/*")):
            new, n = symbol.subn(new_symbol, seg)
            if any(w in seg for w in MARKER_WORDS):
                new, m = words.subn(new_word, new)
                n += m
            counts["comment"] += n
        else:
            line_start = text.rfind("\n", 0, match.start()) + 1
            new = seg
            if PRAGMA_LINKER.match(text, line_start):
                new, n = symbol.subn(new_symbol, seg)
                counts["pragma"] += n
            elif identifier_string(text, match.start()):
                new, n = symbol.subn(new_symbol, seg)
                if n:
                    counts["identifier"] = counts.get("identifier", 0) + n
            if words.search(new):
                string_hits.append(seg)
        out.append(new)
        last = match.end()
    out.append(code(text[last:]))
    return "".join(out), counts, string_hits


def code_mentions(text, word):
    """Occurrences of `word` in code (comments and literals blanked)."""
    return len(word_re(word).findall(name_metric.strip(text)))


# ---------------------------------------------------------------- ledger rewrite

def rewrite_records(raw, label, symbol_re, new_symbol):
    """Replace a whole symbol in every record of an LF ledger. Returns
    (new_raw, [(old_fields, new_fields)]) for the records that changed;
    every other record keeps its exact bytes."""
    ledger_io.lf_terminator(raw, label)
    out, changed = [], []
    for payload, term in ledger_io.split_records(raw):
        text = payload.decode("utf-8")
        new = symbol_re.sub(lambda _m: new_symbol, text)
        if new != text:
            changed.append((ledger_io.fields(payload), ledger_io.fields(new.encode("utf-8"))))
            payload = new.encode("utf-8")
        out.append(payload + term)
    return b"".join(out), changed


def csv_line(values):
    buffer = io.StringIO()
    csv.writer(buffer, lineterminator="\n").writerow(values)
    return buffer.getvalue().encode("utf-8")


def tombstone_line(name, rva, reason):
    """deleted_rows.csv's own spelling: bare name and RVA, quoted reason."""
    return f'{name},0x{rva:08X},"{reason.replace(chr(34), chr(34) * 2)}"\n'.encode("utf-8")


def appended(raw, lines, header=None):
    """`raw` plus `lines`; a missing file starts with `header`."""
    if raw is None:
        raw = (header + "\n").encode("utf-8") if header else b""
    elif raw and not raw.endswith(b"\n"):
        raise Refusal("ledger does not end with a newline (truncated last row?)")
    return raw + b"".join(lines)


# ---------------------------------------------------------------- the plan

@dataclass
class Plan:
    kind: str
    old: str
    new: str
    basis: str
    evidence: str
    source: str
    rva: int
    old_word: str = ""
    new_word: str = ""
    before: dict = field(default_factory=dict)    # rel -> bytes or None (absent)
    after: dict = field(default_factory=dict)     # rel -> bytes
    verify: list = field(default_factory=list)    # ledger sources ./build.sh must pass
    renamed_rows: list = field(default_factory=list)   # (old name, new name, rva)
    renamed_pins: list = field(default_factory=list)
    notes_rows: list = field(default_factory=list)
    source_counts: dict = field(default_factory=dict)
    claims: list = field(default_factory=list)
    warnings: list = field(default_factory=list)
    mentions: list = field(default_factory=list)  # files outside the rename that name the old name
    moves: list = field(default_factory=list)     # (old path, new path): git mv, undone by git mv
    moved_bytes: dict = field(default_factory=dict)  # old path -> its bytes when planned
    renamed_data: list = field(default_factory=list)  # data_rows.csv (old name, new name, rva)
    path_rows: dict = field(default_factory=dict)     # ledger -> records whose path column moved
    owner_rows: list = field(default_factory=list)    # body_owners.csv (name, rva) renamed with their row
    carried: list = field(default_factory=list)       # name_basis.csv records carried to a new spelling
    spellings: list = field(default_factory=list)     # carry: (old spelling, new spelling, occurrences)
    virtual: bool = False                             # function --virtual: the decoration, not the name

    def edit(self, ctx, rel, data):
        if rel not in self.before:
            self.before[rel] = ctx.read(rel)
        self.after[rel] = data

    def written(self):
        """Every path this plan writes: the files it edits and where it moves
        sources to (the old paths go with the move)."""
        return set(self.after) | {new for _old, new in self.moves}

    def subject(self):
        if self.virtual:
            return f"Respell {self.old} as virtual {self.new} (retail vtable slot)"
        if self.kind == "carry":
            return f"Carry {len(self.spellings)} renamed spelling(s) into ledger notes"
        if self.kind in ("member", "param", "local"):
            return f"Rename {self.old} to {self.new_word} ({self.basis})"
        return f"Rename {self.old_word or self.old} to {self.new_word or self.new} ({self.basis})"

    def report(self):
        where = f" at 0x{self.rva:08X}" if self.rva is not None else ""
        if self.kind == "carry":
            lines = [f"rename: carry {len(self.spellings)} spelling(s) into {len(self.notes_rows)} "
                     "functions.csv notes field(s)"]
            lines += [f"    {old} -> {new} (x{count})" for old, new, count in self.spellings]
        else:
            lines = [f"rename: {self.kind} {self.old} -> {self.new}{where} ({self.basis})",
                     f"  owner source: {self.source}"]
            if self.virtual:
                lines.append(f"  evidence: {self.evidence}")
        for old, new in self.moves:
            lines.append(f"  git mv {old} {new}")
        for rel, count in sorted(self.path_rows.items()):
            lines.append(f"  {rel}: {count} path field(s) repointed")
        if self.renamed_data:
            lines.append(f"  data_rows.csv rows renamed ({len(self.renamed_data)}), each tombstoned:")
            lines += [f"    0x{rva:08X} {old} -> {new}" for old, new, rva in self.renamed_data]
        if self.renamed_rows:
            lines.append(f"  functions.csv rows renamed ({len(self.renamed_rows)}), each tombstoned:")
            lines += [f"    0x{rva:08X} {old} -> {new}" for old, new, rva in self.renamed_rows]
        if self.notes_rows:
            lines.append(f"  functions.csv notes rewritten ({len(self.notes_rows)}):")
            lines += [f"    0x{rva:08X} {name}" for name, rva in self.notes_rows[:20]]
        if self.owner_rows:
            lines.append(f"  body_owners.csv owners renamed with their rows ({len(self.owner_rows)}):")
            lines += [f"    0x{rva:08X} {name}" for name, rva in self.owner_rows]
        if self.carried:
            lines.append(f"  name_basis.csv records carried ({len(self.carried)}):")
            lines += [f"    {old} -> {new} ({basis})" for old, new, basis in self.carried]
        if self.renamed_pins:
            lines.append(f"  symbols.csv pins renamed in place ({len(self.renamed_pins)}):")
            lines += [f"    {address} {old} -> {new}" for old, new, address in self.renamed_pins]
        if self.source_counts:
            lines.append(f"  sources rewritten ({len(self.source_counts)}):")
            for rel, counts in sorted(self.source_counts.items()):
                detail = ", ".join(f"{k} {v}" for k, v in counts.items() if v)
                lines.append(f"    {rel} ({detail})")
        lines.append(f"  verify ({len(self.verify)}): ./build.sh " + " ".join(self.verify))
        if self.claims:
            lines.append("  claims: " + " ".join(str(c) if isinstance(c, str) else f"0x{c:08X}"
                                                for c in self.claims))
        lines.append(f"  ledger files: {', '.join(sorted(r for r in self.after if r.startswith('reverse/')))}")
        for rel in self.mentions:
            lines.append(f"  mention (not rewritten): {rel}")
        for warning in self.warnings:
            lines.append(f"  warning: {warning}")
        lines.append(f"  suggested subject: {self.subject()}")
        return "\n".join(lines)


def is_vendored_path(ctx, rel):
    """True for a third-party or SDK source whose names are upstream's: a
    file any vendored= or .lib row lists as its source, a vendored library
    directory, the gamespy shims, or a Platform SDK/DirectX/CRT shim header."""
    rel = (rel or "").replace("\\", "/")
    if rel.lower().endswith(".lib") or rel.startswith(VENDORED_DIRS):
        return True
    if rel.startswith("reference/shims/") and SDK_HEADER.fullmatch(posixpath.basename(rel)):
        return True
    if "_vendored_sources" not in ctx._cache:
        by_source = {}
        for row in ctx.rows():
            by_source.setdefault(row.get("source", ""), []).append(row)
        ctx._cache["_vendored_sources"] = {
            source for source, rows in by_source.items()
            if (any("vendored=" in r.get("notes", "") for r in rows) or source.lower().endswith(".lib"))
            and not hosts_instantiations_only(source, rows)}
    return rel in ctx._cache["_vendored_sources"]


def qualified_name_parts(mangled):
    """The function's own qualified name, innermost first, as (text,
    is_template) pairs -- `?push_back@?$vector@PAUX@@V?$allocator@PAUX@@@_STL@@@_STL@@QAEX...`
    reads push_back, vector (a template), _STL -- never what its signature
    spells. A constructor, destructor or `??_G`-style row has no name part of
    its own, only its scope. MSVC's name back-references (`_STL` seen first
    inside the allocator's arguments is a digit in the scope) are resolved from
    the fragment table the parser keeps. None for a symbol outside the subset
    `fragments` reads, which a caller must treat as not an instantiation."""
    if not mangled.startswith("?"):
        return None
    out = _Out()
    parts = []
    try:
        if mangled.startswith("??$?"):                      # an operator template instance
            parts.append((mangled[3:5], True))               # (operators take no fragment-table slot)
            i = _parse_template_args(mangled, 5 + (mangled[4] == "_"), out)
        elif mangled.startswith("??$"):                     # a function template instance
            end = mangled.index("@", 3)
            out.append((3, end))
            parts.append((mangled[3:end], True))
            i = _parse_template_args(mangled, end + 1, out)
        elif mangled.startswith("??") and mangled[2] != "?":   # ctor, dtor, ??_G: scope only
            if mangled.startswith("??__"):
                return None
            i = 4 if mangled[2] == "_" else 3
        else:
            i = 1
        while mangled[i] != "@":
            c = mangled[i]
            if c.isdigit():
                begin, end = out[int(c)]
                parts.append((mangled[begin:end], mangled[begin - 2:begin] == "?$"))
                i += 1
            elif mangled.startswith("?$", i) and mangled[i + 2] != "?":
                end = mangled.index("@", i + 2)
                out.append((i + 2, end))
                parts.append((mangled[i + 2:end], True))
                i = _parse_template_args(mangled, end + 1, out)
            elif c.isalpha() or c == "_":
                end = mangled.index("@", i)
                if not IDENT.fullmatch(mangled[i:end]):
                    return None
                out.append((i, end))
                parts.append((mangled[i:end], False))
                i = end + 1
            else:
                return None
    except (IndexError, ValueError):
        return None
    return parts


def is_stlport_instantiation(mangled):
    """True when the row's own qualified name is a template instance in the
    `_STL` namespace: a function template (`??$__copy@...@_STL@@`), or a
    member of a class template instance (`?push_back@?$vector@...@_STL@@`,
    its constructors and destructors included). Only the name counts: a plain
    upstream method that takes a template instance as an argument
    (`?erase@list@_STL@@QAEXV?$_List_iterator@H@1@@Z`) is not one."""
    parts = qualified_name_parts(mangled)
    return bool(parts) and any(template for _text, template in parts) and \
        any(text == "_STL" and not template for text, template in parts)


def hosts_instantiations_only(source, rows):
    """True for a game unit whose only vendored rows are STLport template
    instantiations over its own types (`push_back@?$vector@PAULivingWorldArmy`):
    the unit's text is the game's, upstream's templates live in the STLport
    headers, and a row it merely instantiates is no upstream code in the
    file. It needs a row of its own besides the instantiations (a file made
    only of vendored rows is upstream's), must not be an STLport unit by
    name, and every vendored row's own qualified name must be a template
    instance in `_STL` (is_stlport_instantiation: a signature that merely
    spells one does not count; a plain upstream function or another
    library's row keeps the file vendored).
    The names those rows spell stay protected: `shared_identifier` refuses a
    word they spell."""
    if source.lower().endswith(".lib") or source.startswith(VENDORED_DIRS) or \
            posixpath.basename(source).lower().startswith("stlport"):
        return False
    vendored = [r for r in rows if "vendored=" in r.get("notes", "")]
    if not vendored or len(vendored) == len(rows):
        return False
    return all(re.search(r"vendored=stlport-", r.get("notes", "")) and is_stlport_instantiation(r["name"])
               for r in vendored)


def refuse_vendored(ctx, paths, what):
    vendored = sorted(p for p in paths if p and is_vendored_path(ctx, p))
    if vendored:
        raise Refusal(f"{what} touches vendored or SDK source {vendored[0]}: its names are upstream's "
                      "(canonical) and the file stays pristine")


def heuristic_placeholder(word, kind):
    """True when `word` is a placeholder only by name_metric's shape rules
    (an offset-like tail, a weak local) -- the ones that can misread a real
    name -- rather than by an address token, a bfme token, a hex run, a
    decompiler local or an unambiguous field-style offset (m_0C, unk14)."""
    if not is_placeholder(word, kind):
        return False
    if name_metric.ADDRESSED.fullmatch(word) or re.search(r"(?i)(^|_)bfme", word) or \
            re.search(r"[0-9A-F]{6,8}", word) or name_metric.HEXRUN.search(word) or \
            name_metric.OPAQUE.fullmatch(word) or name_metric.OFFSET_FIELD.fullmatch(word):
        return False
    return True


def reference_declarers(ctx, word, limit=40):
    """Files that declare `word` (name_metric.declared) in the Zero Hour
    tree, the BFME 1 game tree or this repo's vendored/SDK views."""
    found = []
    sub = ctx.path(BFME1)
    if (sub / ".git").exists():
        hits = subprocess.run(["git", "-C", str(sub), "grep", "-l", "-w", "-F", "-I", "-e", word, "--",
                               ZH_TREE, "game"], capture_output=True, text=True).stdout.splitlines()
        for hit in hits[:limit]:
            text = (sub / hit).read_text(encoding="utf-8", errors="replace")
            if any(name == word for kind, name in name_metric.declared(hit, text) if kind != "file"):
                found.append(f"{BFME1}/{hit}")
    for rel in ctx.grep_files(word, word=True):
        if is_vendored_path(ctx, rel):
            text = (ctx.read(rel) or b"").decode("utf-8", errors="replace")
            if any(name == word for kind, name in name_metric.declared(rel, text) if kind != "file"):
                found.append(rel)
    return found


def wb_rows(ctx, rva):
    return [r for r in ctx.dicts(WB_LEADS) if _rva(r.get("target_rva")) == rva and r.get("wb_name")]


def wb_identifiers(ctx):
    if "_wb_ids" not in ctx._cache:
        ids = set()
        for row in ctx.dicts(WB_LEADS):
            ids.update(p for p in re.split(r"::|[^A-Za-z0-9_]", row.get("wb_name", "")) if p)
        ctx._cache["_wb_ids"] = ids
    return ctx._cache["_wb_ids"]


def inferred_guards(ctx, kind, old_name, old_word, rva):
    """Refuse an inferred name over evidence already on record: a real-named
    pin, a WorldBuilder lead or an evidence-tier name at the address, an old
    word that WorldBuilder or the evidence tier spells, or (for a word that is
    a placeholder only by shape) one declared in a reference tree or a
    vendored/SDK view."""
    if rva is not None and kind in ("function", "global"):
        own = mangled_re(old_name)
        for pin in ctx.pins():
            name = pin.get("name", "")
            if _rva(pin.get("address")) != rva or not name or own.search(name):
                continue
            ident = leading_fragment(name) or (fragments_text(name) or [name])[0]
            if not is_placeholder(ident, "function"):
                raise Refusal(f"symbols.csv pin {name} already names 0x{rva:08X}; an inferred name may not "
                              "replace a body with a real name on record -- resolve it first "
                              "(tools/pin_consistency.py, or land it as canonical:<kind>)")
        if kind == "function":
            leads = wb_rows(ctx, rva)
            if leads:
                raise Refusal(f"WorldBuilder lead {leads[0]['wb_name']} (score {leads[0].get('score')}) names "
                              f"0x{rva:08X}; land it as canonical:wb if it fits, never an inferred name over it")
        for row in ctx.dicts(NAME_TIERS):
            if _rva(row.get("target_rva")) == rva and row.get("name_tier") == "evidence" \
                    and row.get("name") != old_name:
                raise Refusal(f"evidence-tier name {row.get('name')} ({row.get('evidence')}) is on record at "
                              f"0x{rva:08X}; an inferred name may not replace it")
    if old_word in wb_identifiers(ctx):
        raise Refusal(f"{old_word} is spelled by a WorldBuilder name in {WB_LEADS}: it may be EA's own")
    for row in ctx.dicts(NAME_TIERS):
        if row.get("name_tier") == "evidence" and old_word in (fragments_text(row.get("name", "")) or []):
            raise Refusal(f"{old_word} is part of the evidence-tier name {row.get('name')}")
    if kind in ("function", "class", "global", "member") and heuristic_placeholder(old_word, kind):
        declarers = reference_declarers(ctx, old_word)
        if declarers:
            raise Refusal(f"{old_word} is declared in {declarers[0]}: a reference or vendored name, "
                          "not a placeholder, whatever its shape")


def fragments_text(symbol):
    """The fragment texts of `symbol`, or None when it cannot be read."""
    try:
        return [symbol[a:b] for a, b in fragments(symbol)]
    except Unparsed:
        return None


def check_agreement(ctx, kind, evidence, old_names, new_names, rva):
    """An inferred name's review record: `agree:<id>` names a row of
    reverse/name_agreed.csv for this very rename, and the votes it indexes
    carry it. The row is only an index (kind, old, new, rva and the lane key
    source|kind|scope|placeholder); its `agents` column is not trusted. The
    agreement is recomputed from reverse/name_votes.csv by
    tools/name_agreement.py: one worker for an uncontested scoped name,
    otherwise two distinct workers voted the spelling or the same scoped meaning; no rival
    spelling has as many, and neither the record nor the
    spelling has been disputed."""
    match = re.fullmatch(r"agree:([A-Za-z0-9_.:-]+)", evidence.strip())
    if not match:
        raise Refusal("an inferred name needs a recorded naming approval: --evidence agree:<record-id> "
                      f"naming a row of {AGREED} (or mechanical:<rows> for a file named from its own rows)")
    rid = match.group(1)
    rows = [r for r in ctx.dicts(AGREED) if r.get("id") == rid]
    if not rows:
        raise Refusal(f"agreement record {rid} is not in {AGREED}")
    row = rows[-1]
    problems = []
    if row.get("kind") != kind:
        problems.append(f"kind {row.get('kind')!r}")
    if row.get("old") not in old_names:
        problems.append(f"old {row.get('old')!r}")
    if row.get("new") not in new_names:
        problems.append(f"new {row.get('new')!r}")
    if rva is not None and _rva(row.get("rva")) != rva:
        problems.append(f"rva {row.get('rva')!r}")
    key = row.get("key") or ""
    parts = key.split("|")
    if len(parts) != 4 or parts[1] != kind or parts[3] != row.get("old"):
        problems.append(f"lane key {key!r} (source|kind|scope|placeholder of this rename)")
    if any(r.get("status") == "disputed" for r in rows):
        problems.append("the record was disputed")
    if not problems:
        problems = name_agreement.verify(ctx.dicts(name_agreement.VOTES), ctx.dicts(AGREED), key,
                                         row.get("new", ""), meaning_votes=ctx.dicts(name_agreement.MEANINGS),
                                         meaning=name_agreement.record_meaning(rid))
    if problems:
        raise Refusal(f"agreement record {rid} does not agree to this rename: {'; '.join(problems)}")


def mechanical_stems(ctx, source):
    """File stems derivable from the real-named rows `source` owns: a row's
    identifier, its class, Class_method and ClassMethod."""
    stems = set()
    for row in ctx.rows():
        if row.get("source") != source or row.get("status") != "matched":
            continue
        scope = scope_of(row.get("name", "")) or ""
        parts = [p for p in scope.split("::") if p]
        if not parts or any(is_placeholder(p, "function") for p in parts):
            continue
        ident = parts[-1].lstrip("~")
        cls = parts[-2] if len(parts) > 1 else None
        stems.add(ident)
        if cls:
            stems.update({cls, f"{cls}_{ident}", cls + ident[:1].upper() + ident[1:]})
    return {s.lower() for s in stems}



# The reference block tables canonical:iniblock may cite: Zero Hour's INI.cpp
# table and BFME 1's REGISTER_BLOCK list (tools/ini_blocks.py reads the same).
INI_REFERENCE_TABLES = (
    ("reference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source/Common/INI/INI.cpp",
     r'\{\s*"(\w+)",\s*(?:\w+::)?(\w+)\s*\}'),
    ("reference/open-bfme-1/game/GameEngine/Source/Common/INI/ini.cpp",
     r'REGISTER_BLOCK\(\s*\w+,\s*"(\w+)",\s*(?:\w+::)?(\w+)\s*\)'))


def iniblock_contradiction(ctx, rva, old_word, new_word):
    """True only when the retail registration at `rva` contradicts its current
    real name: reverse/ini_blocks.tsv registers the callback for token T under
    a reference-cited (not derived) name equal to `new_word`, the cited
    reference table maps T to `new_word`, and a reference table maps `old_word`
    to a different token and never to T. A mislabel the tables disprove, and
    nothing else, lets canonical:iniblock replace a real name."""
    if rva is None or not old_word or old_word == new_word:
        return False
    regs = [line.split("\t") for line in (ctx.read(INI_BLOCKS) or b"").decode("utf-8", errors="replace")
            .splitlines()[1:] if line.count("\t") >= 6]
    hits = [r for r in regs if _rva(r[3]) == rva]
    if len(hits) != 1:
        return False
    token, name, source = hits[0][0], hits[0][5], hits[0][6].strip()
    if name != new_word or source == "derived" or ":" not in source:
        return False
    cited = source.rsplit(":", 1)[0]
    pairs = {}
    for path, pattern in INI_REFERENCE_TABLES:
        for line in (ctx.read(path) or b"").decode("utf-8", errors="replace").splitlines():
            m = re.search(pattern, line)
            if m:
                pairs.setdefault(path, set()).add((m.group(1), m.group(2)))
    if (token, new_word) not in pairs.get(cited, set()):
        return False
    every = set().union(*pairs.values()) if pairs else set()
    if (token, old_word) in every:
        return False
    return any(fn == old_word and tok != token for tok, fn in every)


def check_canonical(ctx, kind, evidence_kind, evidence, new_name, new_word, rva, *, old_word=None):
    """Verify a canonical basis against the record it cites; raises Refusal.
    A canonical name is permanent (nothing replaces it), so it is never
    self-asserted, and never weaker than tools/name_evidence.py's proof:
    wb, zh and bfme1 are re-graded by name_evidence.proof() (the same rules
    that grade the lane's candidates: a WB pairing that scores, asserts the
    name and is unique; a specific Zero Hour same-body placement at this
    address; a BFME 1 same-body placement with EA or Zero Hour same-body
    support) and the citation must still check out; string and assert need
    a retail string referenced by this very function (or, for a class, by a
    function it scopes) that spells the word on word boundaries."""
    def cite():
        match = re.search(r"((?:reference|Code|vendor)/[^\s:]+):(\d+)", evidence)
        if not match:
            raise Refusal(f"canonical:{evidence_kind} needs --evidence citing <path>:<line>")
        path, line = match.group(1), int(match.group(2))
        data = ctx.read(path)
        if data is None:
            raise Refusal(f"cited file {path} does not exist")
        lines = data.decode("utf-8", errors="replace").splitlines()
        if not 0 < line <= len(lines) or not word_re(new_word).search(lines[line - 1]):
            raise Refusal(f"{path}:{line} does not spell {new_word}")
        return path

    def graded(which):
        import name_evidence
        why = name_evidence.proof(ctx.root, which, kind, old_word, new_word, rva, sweep_dirs=ctx.sweep_dirs)
        if why:
            raise Refusal(f"canonical:{which}: tools/name_evidence.py does not grade {old_word} -> {new_word} "
                          f"as proof: {'; '.join(why)[:400]}")

    def cited_rva():
        match = re.search(r"0x([0-9A-Fa-f]{1,8})", evidence)
        return int(match.group(1), 16) if match else None

    if evidence_kind == "export":
        names = {r.get("name", "") for r in ctx.dicts(EXPORTS)}
        ok = new_name in names if kind in ("function", "global") else \
            any(new_word in (fragments_text(n) or []) for n in names)
        if not ok:
            raise Refusal(f"canonical:export: no retail export in {EXPORTS} spells {new_name}")
    elif evidence_kind == "module":
        if not any(r.get("name") == new_word for r in ctx.dicts(MODULES)):
            raise Refusal(f"canonical:module: {new_word} is not a retail module class name in {MODULES}")
    elif evidence_kind == "rtti":
        if new_word not in RTTI_CLASSES:
            raise Refusal(f"canonical:rtti: {new_word} is not a retail RTTI class name")
    elif evidence_kind in ("vendored", "lib"):
        upstream = any(new_word in (fragments_text(r.get("name", "")) or [])
                       for r in ctx.rows() if "vendored=" in r.get("notes", "")
                       or r.get("source", "").lower().endswith(".lib"))
        if not upstream:
            cite()
    elif evidence_kind in ("zh", "bfme1"):
        path = cite()
        if evidence_kind == "zh" and "CnC_Generals_Zero_Hour" not in path:
            raise Refusal(f"canonical:zh must cite a file in the Zero Hour tree ({BFME1}/{ZH_TREE})")
        if evidence_kind == "bfme1":
            if not path.startswith(BFME1 + "/"):
                raise Refusal(f"canonical:bfme1 must cite a file under {BFME1}/")
            if re.match(rf"{re.escape(BFME1)}/targets/[^/]+/reverse/", path) and \
                    posixpath.basename(path) != "ea_evidence.csv":
                raise Refusal(f"canonical:bfme1 may not cite {path}: BFME 1's ledgers hold names agents "
                              "chose; cite its ea_evidence.csv or a Zero Hour line")
        graded(evidence_kind)
    elif evidence_kind in ("string", "assert"):
        at = cited_rva()
        if at is None:
            raise Refusal(f"canonical:{evidence_kind} needs --evidence citing 0x<rva> of the renamed "
                          f"function's retail string in {STRING_XREFS}")
        if kind in ("function", "global"):
            if rva is None or at != rva:
                raise Refusal(f"canonical:{evidence_kind} must cite the renamed row's own address"
                              + (f" 0x{rva:08X}" if rva is not None else "") + f", not 0x{at:08X}")
        elif kind == "class":
            scoped = [r for r in ctx.rows() if _rva(r.get("target_rva")) == at
                      and (scope_of(r.get("name", "")) or "").split("::")[:-1][-1:] == [old_word]]
            if not old_word or not scoped:
                raise Refusal(f"canonical:{evidence_kind}: no function of {old_word} is at 0x{at:08X}")
        else:
            raise Refusal(f"canonical:{evidence_kind} names functions, globals and classes, not a {kind}")
        spelled = word_re(new_word)
        found = False
        for line in (ctx.read(STRING_XREFS) or b"").decode("utf-8", errors="replace").splitlines():
            if "\t" not in line:
                continue
            text, refs = line.rsplit("\t", 1)
            if at in {_rva(x.strip()) for x in refs.split(",")} and spelled.search(text):
                found = True
                break
        if not found:
            raise Refusal(f"canonical:{evidence_kind}: no retail string in {STRING_XREFS} referenced by "
                          f"0x{at:08X} spells {new_word} as a word")
    elif evidence_kind == "iniblock":
        if kind != "function":
            raise Refusal(f"canonical:iniblock names a block's parse callback, not a {kind}")
        regs = [line.split("\t") for line in (ctx.read(INI_BLOCKS) or b"").decode("utf-8", errors="replace")
                .splitlines()[1:] if line.count("\t") >= 6]
        hits = [r for r in regs if rva is not None and _rva(r[3]) == rva]
        if len(hits) != 1:
            raise Refusal(f"canonical:iniblock: {INI_BLOCKS} registers no block parser at "
                          + (f"0x{rva:08X}" if rva is not None else "this row"))
        token, recorded, name = hits[0][0], hits[0][4], hits[0][5]
        if not old_word or not (is_placeholder(old_word)
                                or iniblock_contradiction(ctx, rva, old_word, new_word)):
            raise Refusal(f"canonical:iniblock replaces only a placeholder, or a real name the reference "
                          f"block tables give to another token, not {old_word}")
        sharing = [r for r in ctx.rows() if _rva(r.get("target_rva")) == rva]
        if len(sharing) != 1 or sharing[0].get("name") != recorded:
            raise Refusal(f"canonical:iniblock: 0x{rva:08X} is not exactly the row {INI_BLOCKS} recorded "
                          f"({recorded}); regenerate with tools/ini_blocks.py")
        if new_word != name:
            raise Refusal(f"canonical:iniblock: 0x{rva:08X} parses block {token}; its name is {name}, "
                          f"not {new_word}")
        if not word_re(token).search(evidence):
            raise Refusal(f"canonical:iniblock needs --evidence naming the block token {token}")
    elif evidence_kind == "file":
        base = posixpath.basename(new_name).lower()
        approved = any(r.get("tu") == new_name and tu_map.canonical_tu(r) for r in ctx.dicts(TU_MAP))
        retail = any(line.split("\t")[0].replace("\\", "/").lower().endswith("/" + base)
                     for line in (ctx.read(STRING_XREFS) or b"").decode("utf-8", errors="replace").splitlines())
        if kind != "file" or not (approved or retail):
            raise Refusal(f"canonical:file needs an approved {TU_MAP} TU or a retail __FILE__ path ending in "
                          f"{base}")
    elif evidence_kind == "wb":
        at = rva if rva is not None else cited_rva()
        leads = wb_rows(ctx, at) if at is not None else []
        def fits(wb):
            parts = wb.split("::")
            return parts[-1] == new_word if kind == "function" else new_word in parts[:-1]
        if kind not in ("function", "class") or not any(fits(r["wb_name"]) for r in leads):
            raise Refusal(f"canonical:wb needs a {WB_LEADS} row at the address naming {new_word}")
        graded("wb")
    else:
        raise Refusal(f"canonical:{evidence_kind} is not machine-checkable")


def provisional_file(ctx, path):
    """True when tu_map approves rows for the TU at `path` only under a provisional name
    (tu_map.provisional_name) and never under a canonical one."""
    rows = [r for r in ctx.dicts(TU_MAP) if path and r.get("tu") == path]
    return any(tu_map.provisional_name(r) for r in rows) and not any(tu_map.canonical_tu(r) for r in rows)


def check_basis(ctx, kind, basis, evidence, old_name, old_word, rva, *, new_name=None, new_word=None,
                source=None):
    """Refuse a basis that may not replace `old_name`: an inferred name needs
    the naming approval record (or, for a file, a stem derived from its
    own real-named rows) and may replace only a placeholder with no evidence
    on record; a canonical basis is verified against the record it cites."""
    which = basis_kind(basis)
    ctx._cache.pop("_restoring", None)
    if not (evidence or "").strip():
        raise Refusal("--evidence is required (canonical: the evidence; inferred: the agreement record)")
    if any(c in evidence for c in "\r\n"):
        raise Refusal("--evidence must be one line")
    if which == RESTORED:
        check_restore(ctx, kind, evidence, old_name, new_name or new_word, rva)
        return which
    new_name = new_name or new_word
    new_word = new_word or new_name
    # A file named after a provisional TU (tu_map approved it for merging by grouping
    # alone) carries no name evidence: it is as replaceable as a placeholder.
    placeholder = is_placeholder(old_word, kind) or (kind == "file" and provisional_file(ctx, old_name))
    recorded = recorded_basis(ctx, old_name) or recorded_basis(ctx, old_word)
    if which == "inferred" and not placeholder:
        raise Refusal(f"{old_word} is a real name, not a placeholder; an inferred name may replace "
                      "only a placeholder or weak name")
    if which == "canonical" and not placeholder and not (recorded or "").startswith("inferred") \
            and not (basis == "canonical:iniblock" and kind == "function"
                     and iniblock_contradiction(ctx, rva, old_word, new_word)):
        raise Refusal(f"{old_word} is a real name that name_basis.csv does not record as inferred; "
                      "a canonical name may replace only a placeholder or an inferred name")
    if which == "inferred":
        inferred_guards(ctx, kind, old_name, old_word, rva)
        if evidence.strip().startswith("mechanical:"):
            if kind != "file":
                raise Refusal("mechanical: evidence names a file from its own rows; other kinds need agree:<id>")
            stem = posixpath.splitext(posixpath.basename(new_name or ""))[0]
            if stem.lower() not in mechanical_stems(ctx, source or old_name):
                raise Refusal(f"{stem} is not derived from a real-named row {source or old_name} owns "
                              "(identifier, Class, Class_method or ClassMethod)")
        else:
            check_agreement(ctx, kind, evidence, {old_name, old_word}, {new_name, new_word}, rva)
    else:
        check_canonical(ctx, kind, BASIS_RE.fullmatch(basis).group(1), evidence, new_name, new_word, rva,
                        old_word=old_word)
    return which


# ---------------------------------------------------------------- reverting an inferred name
#
# A disputed inferred name goes back to the placeholder it replaced. That one
# rename needs what every other is refused -- a placeholder as the new name,
# a non-placeholder old name, and the old (name, rva) back although its
# tombstone says it was renamed away -- so it is its own basis, `restored`,
# checked here as the exact inverse of a recorded `inferred` landing, never
# a lane-side override of the engine's checks.

def revert_id(evidence):
    match = REVERT_RE.fullmatch((evidence or "").strip())
    return match.group(1) if match else None


def word_of(kind, spelling):
    """The identifier a name_basis.csv spelling of `kind` respells."""
    if kind in ("function", "global"):
        try:
            return split_function_name(spelling)[1]
        except Refusal:
            return _identifier(spelling) or spelling
    if kind in ("member", "param", "local"):
        return spelling.rsplit("::", 1)[-1]
    return spelling


def respell(kind, spelling, word):
    """`spelling` (as name_basis.csv records it) with its identifier `word`."""
    if kind in ("function", "global"):
        return rename_function_symbol(spelling, word)
    if kind in ("member", "param", "local"):
        return f"{spelling.rsplit('::', 1)[0]}::{word}" if "::" in spelling else word
    return word


@dataclass
class Landing:
    """A recorded inferred rename and where its name stands now."""
    record: str
    kind: str
    placeholder: str      # the old word the landing replaced
    landed: str           # the word it landed
    current: str          # the landed spelling now (after carry rows)
    target: str           # that spelling with the placeholder back
    rva: object
    source: str


def landing(ctx, record):
    """The inferred rename `agree:<record>` landed, not yet restored. Carry
    rows (a renamed class or function respelling this record's scope) are
    followed to its current spelling."""
    rows = name_basis_rows(ctx)
    found = [i for i, r in enumerate(rows) if r.get("basis") == "inferred"
             and (r.get("evidence") or "").strip() == f"agree:{record}"]
    if not found:
        raise Refusal(f"no inferred rename with evidence agree:{record} is recorded in {NAME_BASIS}")
    at = found[-1]
    row = rows[at]
    kind = row.get("kind", "")
    if kind not in ("function", "global", "class", "member", "param", "local"):
        raise Refusal(f"agree:{record} renamed a {kind}; only lane kinds are reverted")
    if any(r.get("basis") == RESTORED and revert_id(r.get("evidence")) == record for r in rows[at + 1:]):
        raise Refusal(f"agree:{record} was already reverted")
    current, source = row.get("new", ""), row.get("source", "")
    for r in rows[at + 1:]:
        if r.get("kind") == "carry" and r.get("old") == current:
            current = r.get("new", "")
        if r.get("kind") == "file" and r.get("old") == source:
            source = r.get("new", "")
    placeholder, landed = word_of(kind, row.get("old", "")), word_of(kind, row.get("new", ""))
    if word_of(kind, current) != landed:
        raise Refusal(f"agree:{record}'s name {landed} has since been respelled ({current}); revert that first")
    return Landing(record, kind, placeholder, landed, current, respell(kind, current, placeholder),
                   _rva(row.get("rva")), source)


def check_restore(ctx, kind, evidence, old_name, new_name, rva):
    """Basis `restored`: --evidence `revert:<id> <reason>` names an inferred
    landing that this rename exactly inverts (same kind, its current spelling
    to the placeholder it replaced, same address)."""
    match = REVERT_RE.fullmatch(evidence.strip())
    if not match or not match.group(2):
        raise Refusal("basis restored needs --evidence 'revert:<agreement id> <reason>' "
                      "(python3 tools/rename.py revert --record <id> --reason ...)")
    land = landing(ctx, match.group(1))
    problems = []
    if land.kind != kind:
        problems.append(f"it renamed a {land.kind}, not a {kind}")
    if old_name != land.current:
        problems.append(f"its name is now {land.current}, not {old_name}")
    if new_name != land.target:
        problems.append(f"it replaced {land.target}, not {new_name}")
    if rva is not None and land.rva is not None and rva != land.rva:
        problems.append(f"it is at 0x{land.rva:08X}")
    if problems:
        raise Refusal(f"revert:{land.record} is not the exact inverse of that rename: {'; '.join(problems)}")
    ctx._cache["_restoring"] = (land.kind, land.landed, land.placeholder, land.rva)


def restore_lifts(ctx, kind, landed, placeholder, rva):
    """{(name, rva): line} of the deleted_rows.csv tombstones the landing of
    `landed` over `placeholder` wrote ('Renamed to <T> by tools/rename.py
    (inferred)' where <T> respelled back is the tombstoned name)."""
    out = {}
    if kind not in ("function", "global", "class"):
        return out
    raw = ctx.read(DELETED)
    if raw is None:
        return out
    pattern = re.compile(rf"(?<![A-Za-z0-9_]){re.escape(landed)}(?=@)")
    for line in raw.decode("utf-8", errors="surrogateescape").splitlines():
        if not line.strip() or line.startswith(("#", "name,")):
            continue
        row = next(csv.reader(io.StringIO(line)), [])
        if len(row) < 3 or _rva(row[1]) is None:
            continue
        target = LANDED_TOMBSTONE.match(row[2])
        if not target:
            continue
        if kind == "class":
            try:
                back = class_sub(target.group(1), landed, placeholder)[0]
            except Unparsed:
                continue
        else:
            back = pattern.sub(placeholder, target.group(1), count=1)
            if rva is not None and _rva(row[1]) != rva and not row[0].startswith(FUNCLET_PREFIXES):
                continue
        if back == row[0] and back != target.group(1):
            out[(row[0], _rva(row[1]))] = line
    return out


def lifted_tombstones(ctx):
    """{(name, rva): line} that recorded restores (and one being planned)
    took back out of deleted_rows.csv: rename.py honours them even if a union
    merge brings a line back (check_csv does not; `rename.py check` reports it)."""
    out = {}
    specs = [(r.get("kind"), word_of(r.get("kind"), r.get("old", "")), word_of(r.get("kind"), r.get("new", "")),
              _rva(r.get("rva"))) for r in name_basis_rows(ctx) if r.get("basis") == RESTORED]
    if ctx._cache.get("_restoring"):
        specs.append(ctx._cache["_restoring"])
    for spec in specs:
        out.update(restore_lifts(ctx, *spec))
    return out


def revert(ctx, record, reason, *, function=None, **run_kwargs):
    """Put the placeholder back over the inferred name `agree:<record>`
    landed: the exact inverse, through run() like any rename (claims,
    byte verification, restore on failure), recorded append-only in
    name_basis.csv as basis `restored`, with the landing's tombstones lifted
    and the landed name tombstoned in turn. `function` (Class::method#2)
    supplies the overload index for older param/local records that omitted
    it. New records retain it; a caller cannot redirect their inverse to
    another overload. The scope comes from the record, carry rows followed."""
    reason = " ".join((reason or "").split())
    if not reason:
        raise Refusal("a revert needs --reason: what the code shows against the landed name")
    land = landing(ctx, record)
    evidence = f"revert:{record} {reason}"
    common = dict(basis=RESTORED, evidence=evidence)
    if land.kind == "function":
        if land.rva is None:
            raise Refusal(f"agree:{record} recorded no address")
        kwargs = dict(rva=land.rva, new=land.placeholder, old=land.current)
    elif land.kind in ("global", "class"):
        kwargs = dict(name=land.current, new=land.placeholder)
    elif land.kind == "member":
        kwargs = dict(cls=land.current.rsplit("::", 1)[0], member=land.landed, new=land.placeholder)
    else:
        scope = land.current.rsplit("::", 1)[0]
        recorded = scope.rsplit("#", 1)[1] if "#" in scope else None
        overload = function.rsplit("#", 1)[1] if function and "#" in function else None
        if recorded and overload and recorded != overload:
            raise Refusal(f"agree:{record}'s recorded overload is {scope}, not {function}")
        kwargs = dict(source=land.source, name=land.landed, new=land.placeholder,
                      function=f"{scope}#{overload}" if overload and not recorded else scope)
    return run(land.kind, ctx, **common, **kwargs, **run_kwargs)


def includers(ctx, paths, limit):
    """Ledger sources that #include any of `paths` by file name, transitively.
    Names match case-insensitively on the basename, so doubt widens the set."""
    seen, frontier, found = set(paths), set(paths), set()
    while frontier:
        names = sorted({Path(p).name for p in frontier})
        frontier = set()
        pattern = r"#[[:space:]]*include[[:space:]]*[<\"]([^>\"]*/)?(%s)[>\"]" % "|".join(
            re.escape(n) for n in names)
        hits = ctx.git("grep", "-l", "-i", "-E", "-e", pattern, "--", *SEARCH_ROOTS).splitlines()
        for hit in hits:
            if hit in seen:
                continue
            seen.add(hit)
            if hit in ctx.ledger_sources():
                found.add(hit)
            if not hit.endswith(SOURCE_SUFFIXES) or hit not in ctx.ledger_sources():
                frontier.add(hit)
        if len(found) > limit:
            raise Refusal(f"touched headers reach more than {limit} ledger sources; "
                          "this tool has no batch mode: pass a larger --max-files (every unit is still verified) or leave the name")
    return found


def object_referencers(ctx, symbol):
    """Sources whose cached objects reference `symbol` (name_dependents' scan,
    which falls back to the source text where no current object exists)."""
    if not ctx.object_scan:
        return set()
    import name_dependents
    symbols = {symbol} if isinstance(symbol, str) else set(symbol)
    lookup = getattr(ctx, "_consumer_lookup", None)
    found = (lookup(symbols) if lookup is not None else
             name_dependents.dependents(symbols, name_dependents._row_objects(ctx.rows()), ctx.root))
    if hasattr(ctx, "_object_queries"):
        ctx._object_queries.append((symbols, found))
    return found


def alias_pins(ctx, old_name, rva):
    """symbols.csv pins at `rva` that spell the same qualified function as
    `old_name` under another mangled signature (a caller unit's private view
    of the class mangles back-references in its own order)."""
    scope = scope_of(old_name)
    out = set()
    for pin in ctx.pins():
        name = pin.get("name", "")
        if name == old_name or _rva(pin.get("address")) != rva or not name.startswith("?"):
            continue
        try:
            split_function_name(name)
        except Refusal:
            continue
        if scope and scope_of(name) == scope:
            out.add(name)
    return sorted(out)


def shared_identifier(ctx, word, own_re):
    """Another ledger, pin or data symbol whose spelling contains `word` as a
    name fragment (an identifier, scope or type), or None. Symbols `own_re`
    matches -- the renamed name and funclets embedding it -- are ours."""
    names = [r["name"] for r in ctx.rows()] + [p.get("name", "") for p in ctx.pins()] + \
        [d.get("name", "") for d in ctx.dicts(DATA_ROWS)]
    for other in names:
        if not other or word not in other or own_re.search(other):
            continue
        try:
            spans = fragments(other)
        except Unparsed:
            if re.search(r"(?<![A-Za-z0-9_])%s(?![A-Za-z0-9_])" % re.escape(word), other):
                return other      # unreadable, and it may spell the word: refuse
            continue
        if any(other[a:b] == word for a, b in spans):
            return other
    return None


def frozen_mentions(ctx, symbol):
    return ctx.grep_files(symbol, roots=FROZEN_KEYED)


def enclosing_types(code):
    """{body start: innermost enclosing type name or None} for every
    class/struct/union body in stripped `code`, with the body names."""
    bodies = type_bodies(code)
    out = []
    for name, start, end in bodies:
        outer = [(s, n) for n, s, e in bodies if s < start and end <= e and (s, e) != (start, end)]
        out.append((name, start, end, max(outer)[1] if outer else None))
    return out


def _signature(params):
    """`params` of a member declaration as a tuple of parameter types with the
    names, defaults and spacing taken out, or None where that cannot be done
    without guessing (templates, nested parentheses, a bare qualifier that
    may be a type or a name)."""
    params = params.strip()
    if "<" in params or "(" in params or ">" in params:
        return None
    if params in ("", "void"):
        return ()
    out = []
    for part in params.split(","):
        part = re.sub(r"\s+", " ", part.split("=")[0].strip())
        match = re.fullmatch(r"(.*?[\s*&])([A-Za-z_]\w*)(?: ?\[[^\]]*\])*", part)
        if match and re.search(r"[A-Za-z_]", match.group(1).replace("const", "").replace("volatile", "")
                               .replace("unsigned", "").replace("signed", "")) and \
                match.group(2) not in name_metric.KEYWORDS:
            part = match.group(1)
        elif re.fullmatch(r"(?:(?:const|volatile|unsigned|signed) ?)*[A-Za-z_]\w*", part) and \
                part.split()[0] in ("const", "volatile", "unsigned", "signed") and part.split()[-1] not in name_metric.KEYWORDS:
            return None
        out.append(re.sub(r"\s*([*&])\s*", r"\1", part.strip()))
    return tuple(out)


def _declaration(body, word):
    """(virtual?, signature, const?) of the one member function `word` that
    class `body` declares, or None when it declares none or several."""
    found = []
    for statement in flatten(body).split(";"):
        match = re.search(r"(?<![\w~:.>])%s\s*\(([^()]*)\)\s*(const\b)?" % re.escape(word), statement)
        if match and not re.search(r"\bfriend\b", statement):
            found.append((bool(re.search(r"\bvirtual\b", statement[:match.start()])),
                          _signature(match.group(1)), bool(match.group(2))))
    return found[0] if len(found) == 1 and found[0][1] is not None else None


def overrides_virtual(code, word, derived, base):
    """True when, in this stripped `code` alone, class `derived` derives
    (through classes declared here) from `base`, `base` declares `word`
    virtual and `derived` declares it with the same parameter types and
    constness: the one virtual function, and C++ gives an override the base's
    name. Anything this text does not prove -- a class declared elsewhere, a
    different signature, a non-virtual base declaration, an overload set --
    is False."""
    cls = derived
    if not cls or not base or cls == base:
        return False
    bodies, bases = {}, {}
    for match in re.finditer(r"\b(?:class|struct)\s+([A-Za-z_]\w*)\s*(?::([^{;]*))?\{", code):
        if match.group(1) in bodies:
            return False                       # two bodies of one name: no single reading
        bodies[match.group(1)] = code[match.end():name_metric.close(code, match.end() - 1)]
        bases[match.group(1)] = set()
        if match.group(2):
            names = base_clause_names(match.group(2))
            bases[match.group(1)].update([UNPARSED_BASE] if names is None else names)
    if cls not in bodies or base not in bodies:
        return False
    seen, todo = set(), [cls]
    while todo:
        for parent in bases.get(todo.pop(), ()):
            if parent not in seen:
                seen.add(parent)
                todo.append(parent)
    if base not in seen:
        return False
    mine, theirs = _declaration(bodies[cls], word), _declaration(bodies[base], word)
    return bool(mine and theirs and theirs[0] and mine[1:] == theirs[1:])


def same_virtual(code, word, cls, other):
    """`cls::word` and `other::word` are one virtual function in this code:
    either overrides the other (see overrides_virtual)."""
    return overrides_virtual(code, word, cls, other) or overrides_virtual(code, word, other, cls)


def foreign_declarations(code, word, cls, kind="function"):
    """How stripped `code` declares `word` as something other than the
    renamed entity: a type, typedef or enumerator, a data member, a method of
    another class, a function of another scope, a global (for a function), a
    parameter or a local. `cls` is the renamed function's class (None for a
    free function or a global)."""
    found = []
    pattern = re.escape(word)
    if declares_type(code, word) or re.search(r"\b(?:class|struct|union|enum)\s+%s\s*;" % pattern, code):
        found.append("a type")
    if re.search(r"\btypedef\b[^;{}]*\b%s\s*(?:\[[^\]]*\]\s*)*;" % pattern, code) or \
            re.search(r"\(\s*\*\s*%s\s*\)" % pattern, code):
        found.append("a typedef or function pointer")
    for body in re.finditer(r"\benum\b[^;{()]*\{([^{}]*)\}", code):
        if re.search(r"(?:^|,)\s*%s\s*(?:=|,|$)" % pattern, body.group(1).strip()):
            found.append("an enumerator")
    bodies = enclosing_types(code)
    for name, start, end, _outer in bodies:
        flat = flatten(code[start:end])
        if member_statements(code[start:end], word):
            found.append(f"a data member of {name}")
        elif name != cls and re.search(r"(?<![\w:.>~])%s\s*\(" % pattern, flat) and \
                not (kind == "function" and same_virtual(code, word, cls, name)):
            found.append(f"a method of {name}")
    for scope, start, _end, _params in name_metric.functions_in(code):
        base = scope.split("#")[0]
        if base.split("::")[-1] != word:
            continue
        inside = [n for n, s, e, _o in bodies if s <= start < e]
        owner = "::".join(base.split("::")[:-1]) or (inside[-1] if inside else None)
        if kind == "global" or (owner or None) != (cls or None) and \
                (owner or "").split("::")[-1] != (cls or "") and \
                not (kind == "function" and owner and same_virtual(code, word, cls, owner.split("::")[-1])):
            found.append(f"a function of {owner or 'the global scope'}")
    if kind != "global" and word in set(name_metric.global_names(code)):
        found.append("a global")
    for scope, start, end, params in name_metric.functions_in(code):
        if word in set(parameters(params)):
            found.append(f"a parameter of {scope}")
        if word in set(name_metric.local_names(code[code.find("{", start):end])):
            found.append(f"a local of {scope}")
    return found


def _enclosing_function(code, at):
    """(scope, header start, body start, end, params) of the function definition
    around offset `at` of stripped `code` (the outermost, so a call the scan
    mistakes for a definition inside a body is not it), or None."""
    found = [f for f in name_metric.functions_in(code) if f[1] <= at < f[2]]
    if not found:
        return None
    scope, start, end, params = min(found, key=lambda f: f[1])
    return scope, start, code.find("{", start), end, params


def _declaration_ends(code, paren):
    """True when the parenthesis at `paren` of stripped `code` closes and a `;`
    comes before any `{`: a declaration, not a definition this scan failed to
    recognise (an inline method that does not start its line)."""
    depth = 0
    for at in range(paren, len(code)):
        if code[at] == "(":
            depth += 1
        elif code[at] == ")":
            depth -= 1
            if depth == 0:
                rest = code[at + 1:]
                stops = [i for i in (rest.find(";"), rest.find("{")) if i >= 0]
                return bool(stops) and rest[min(stops)] == ";"
    return False


def unreverted_landings(ctx, word):
    """The `agree:` records of inferred landings (name_basis.csv) that landed
    `word` and have not been restored: `rename.py revert` puts the placeholder
    back by whole-word match, which another scope's rename of `word` would
    make inexact."""
    rows = name_basis_rows(ctx)
    found = []
    for at, row in enumerate(rows):
        match = re.fullmatch(r"agree:(\S+)", (row.get("evidence") or "").strip())
        if row.get("basis") != "inferred" or not match or not row.get("new"):
            continue
        if word_of(row.get("kind", ""), row["new"]) != word:
            continue
        if not any(r.get("basis") == RESTORED and revert_id(r.get("evidence")) == match.group(1)
                   for r in rows[at + 1:]):
            found.append(match.group(1))
    return found


def closure_type_bodies(ctx, rel, code):
    """{class name: [body text, ...]} of every class/struct/union declared in
    stripped `code` (the text of `rel`) and in the headers `rel` includes
    (every same-named header variant counts): the class relations of a unit
    whose classes are declared in a header and defined out of line."""
    out = {}
    for path in [None] + sorted(header_closure(ctx, rel)):
        text = code if path is None else name_metric.strip((ctx.read(path) or b"").decode("utf-8", "replace"))
        for name, start, end in type_bodies(text):
            out.setdefault(name, []).append(text[start:end])
    return out


# A continued #define: backslash-newline, also in a CRLF file. A blank between the backslash and the line
# end may or may not continue the line for cl, so a define is read both ways: _DEFINE_BLANK joins over the
# blank (the macro it reads is longer, which can only make the screen refuse more) and _DEFINE does not, so
# a #define on the line after a blank-continued one stays registered as a macro of its own.
_DEFINE = re.compile(r"^[ \t]*#[ \t]*define[ \t]+([A-Za-z_]\w*)((?:[^\n]*\\\r?\n)*[^\n]*)", re.M)
_DEFINE_BLANK = re.compile(r"^[ \t]*#[ \t]*define[ \t]+([A-Za-z_]\w*)((?:[^\n]*\\[ \t]*\r?\n)*[^\n]*)", re.M)


def macros_spelling(ctx, rel, code, word):
    """Names of the macros, defined in stripped `code` (the text of `rel`) or in
    a header it includes, whose expansion can spell `word`: the macro's own
    line does, or it invokes another such macro. The word rewrite respells a
    macro body, so a scope that invokes one of these meets the new spelling."""
    key = ("_macros", rel, word)
    if key in ctx._cache:
        return ctx._cache[key]
    bodies = {}
    for path in [None] + sorted(header_closure(ctx, rel)):
        text = code if path is None else name_metric.strip((ctx.read(path) or b"").decode("utf-8", "replace"))
        for pattern in (_DEFINE, _DEFINE_BLANK):
            for match in pattern.finditer(text):
                bodies.setdefault(match.group(1), []).append(match.group(2))
    spelling = {name for name, texts in bodies.items() if any(word_re(word).search(t) for t in texts)}
    grew = True
    while grew:
        grew = False
        for name, texts in bodies.items():
            if name not in spelling and any(word_re(inner).search(t) for inner in spelling for t in texts):
                spelling.add(name)
                grew = True
    ctx._cache[key] = spelling
    return spelling


def blank_continued_macro_spells(code, word):
    """True when a `#define` in stripped `code` spells `word` over a backslash that a blank
    follows. name_metric.PREPROCESSOR does not read that backslash as a continuation (it blanks what it
    matches), so occurrence_spots reads the next line as code; cl may continue the line, and then the
    macro spells the word. Read both ways, as macros_spelling does, the macro is the longer one, which can
    only make a caller refuse more. A formal parameter named like the word is not a spelling."""
    pattern = word_re(word)
    for match in _DEFINE_BLANK.finditer(code):
        line = match.group(0)
        if pattern.search(line):
            formals = _define_formals(line)
            if not (formals and formals[0] != word and word in formals[1]):
                return True
    return False


def invoked_macro(macros, code, begin=0, end=None):
    """The first of `macros` that stripped `code[begin:end]` spells, or None."""
    for name in sorted(macros):
        if word_re(name).search(code, begin, len(code) if end is None else end):
            return name
    return None


class ClassRelations:
    """How the classes visible from `rel` (its stripped text `code` and the
    headers it includes) stand to the classes a word rewrite respells.

    `renamed` is the row's class `cls` plus every base or descendant of it that
    spells `old_word` in its body: the rewrite respells those declarations too
    (foreign_declarations lets through only the classes that declare the one
    virtual function `cls` does, its bases and overriders). They are read
    across the header closure, since a base or overrider declared in a header
    is a renamed scope as much as one in the file. A class counts when it is a
    base or a descendant of `cls` and spells the old word in its body, a
    superset of the same-signature virtual pairs (foreign_declarations refuses
    any other such declaration in the file that holds it).

    `error` says why a renamed class's bases are not all declared (then
    nothing can be shown); `unrelated(other)` is None when `other` is a class
    declared with all its bases that is no renamed class, no base of one, not
    derived from one and not joint with one, else why not, and records each
    class it passes in `scopes`; `captured` then asks of those scopes whether
    the rewrite would land inside them."""

    def __init__(self, ctx, rel, code, old_word, new_word, cls):
        self.cls, self.old_word, self.new_word = cls, old_word, new_word
        self.bases = class_base_map(ctx, rel)
        self.old = word_re(old_word)
        self.declared = closure_type_bodies(ctx, rel, code)
        self.rel = rel
        chain, _known = class_chain(self.bases, cls)
        self.renamed = {cls} | {name for name, texts in self.declared.items()
                                if name != cls and any(self.old.search(t) for t in texts)
                                and (name in chain or cls in class_chain(self.bases, name)[0])}
        self.chains, self.error = {}, None
        for member in sorted(self.renamed):
            self.chains[member], known = class_chain(self.bases, member)
            if not known:
                self.error = f"a base of {member} is not declared in {rel} or its headers"
                break
        self.macros = macros_spelling(ctx, rel, code, old_word)
        self.scopes = set()

    def unrelated(self, other):
        if other == self.cls:
            return f"{self.cls} itself declares or qualifies {self.new_word}"
        for member in sorted(self.renamed):
            if other in self.chains[member]:
                return f"{other} is a base of {member}"
        chain, complete = class_chain(self.bases, other)
        if other not in self.bases or not complete:
            return f"{other} is not a class declared with all its bases in {self.rel} or its headers"
        for member in sorted(self.renamed):
            if member in chain:
                return f"{other} derives from {member}"
        for derived in sorted(self.bases):
            if derived in self.renamed or derived == other:
                continue
            below, whole = class_chain(self.bases, derived)
            for member in sorted(self.renamed):
                if member in below and (not whole or other in below):
                    return f"{derived} derives from {member} and from {other}"
        self.scopes.add(other)
        return None

    def captured(self, code, new_word):
        """Why the rewrite would land inside one of the passed scopes (their
        bodies in `self.rel` and its headers, and their out-of-line methods in
        `code`, the stripped text of `self.rel`), or None."""
        old, old_word, macros = self.old, self.old_word, self.macros
        for other in sorted(self.scopes):
            for text in self.declared.get(other, ()):
                macro = invoked_macro(macros, text)
                if macro:
                    return f"{other} invokes the macro {macro}, whose expansion spells {old_word}, where {new_word} would capture it"
            ranges = [(s, e) for name, s, e in type_bodies(code) if name == other] + \
                [(s, e) for scope, s, e, _p in name_metric.functions_in(code)
                 if "::" in scope.split("#")[0] and scope.split("#")[0].rsplit("::", 1)[0].split("::")[-1] == other]
            for begin, finish in ranges:
                macro = invoked_macro(macros, code, begin, finish)
                if macro:
                    return f"{other} invokes the macro {macro}, whose expansion spells {old_word}, where {new_word} would capture it"
            for begin, finish in ranges:
                for hit in old.finditer(code, begin, finish):
                    if not re.search(r"(?:->|\.|::)\s*$", code[:hit.start()]):
                        return f"{old_word} is spelled unqualified inside {other}, where {new_word} would capture it"
        return None


def other_scope_spellings(ctx, rel, code, old_word, new_word, cls):
    """None when every spelling of `new_word` in stripped `code` (a unit or
    header) provably names something that respelling `cls`'s `old_word` as
    `new_word` can neither capture nor make ambiguous; else why one cannot be
    shown. A spelling counts only as one of:

      * a member of, or `Other::word` through, a class Other that is not a
        renamed class (`cls`, or a base or descendant of it that spells
        `old_word` in its body, found across the file and its header closure:
        the word rewrite respells those declarations too) or a base of one, is
        not derived from one, and has no class deriving from both it and one,
        while no unqualified, non-member-access spelling of
        `old_word` sits in Other's body or in one of its methods (the rewrite
        would land in Other's scope) and none of them invokes a macro whose
        expansion spells `old_word` (macros_spelling);
      * a local or parameter of one function that spells `old_word` nowhere in
        its parameters or body and invokes no macro whose expansion spells it
        (so no rewritten site is in the scope), every
        unqualified spelling of the word in it lying inside a declaration's
        scope (local_scopes);
      * a parameter name in a function prototype.

    Everything else is refused: a spelling at file scope, in a macro, in a
    `friend` or `using` declaration, through `.` or `->` (the object's type is
    not known), in an anonymous class, and any class whose bases are not all
    declared in the unit or its headers. A free function (`cls` None) is not
    analysed. The byte build still decides."""
    if not cls:
        return "the renamed function has no class, so no scope separates the spellings"
    spots = occurrence_spots(code, new_word, rel)
    if not spots:
        return None
    relations = ClassRelations(ctx, rel, code, old_word, new_word, cls)
    if relations.error:
        return relations.error
    unrelated = relations.unrelated

    masked = {}              # function start -> its body with the word's qualified spellings blanked
    for at, kind in spots:
        before = code[:at]
        statement = before[max(before.rfind(c) for c in ";{}") + 1:]
        if kind == "macro":
            return f"a preprocessor line spells {new_word}"
        if re.search(r"\b(?:friend|using)\b", statement):
            return f"a friend or using declaration spells {new_word}"
        if re.search(r"::\s*$", before):
            qualifier = re.search(r"([A-Za-z_]\w*)\s*(?:<[^<>]*>\s*)?::\s*$", before)
            if not qualifier:
                return f"a global-scope ::{new_word}"
            why = unrelated(qualifier.group(1))
            if why:
                return why
            continue
        if re.search(r"(?:->|\.)\s*$", before):
            return f"{new_word} is reached through an object whose type this scan cannot see"
        if kind.startswith("class:"):
            if kind == "class:*":
                return f"{new_word} is a member of an anonymous type"
            why = unrelated(kind[6:])
            if why:
                return why
        elif kind in ("fnbody", "param"):
            func = _enclosing_function(code, at)
            if func is None:
                # a prototype's parameter name binds nowhere; a macro call's argument may
                paren = before.rfind("(")
                callee = re.search(r"([A-Za-z_]\w*)\s*$", before[:paren]) if paren >= 0 else None
                part = before[max(paren, before.rfind(",")) + 1:] + new_word
                if kind == "param" and callee and not re.fullmatch(r"[A-Z][A-Z0-9_]*", callee.group(1)) \
                        and len(name_metric.WORD.findall(part)) >= 2 and not re.search(r"[=()]", part) \
                        and _declaration_ends(code, paren):
                    continue
                return f"{new_word} is spelled where this scan finds no function and no prototype"
            scope, start, body_start, end, params = func
            body = code[body_start:end]
            header = code[start:body_start]            # the parameters and any initializer list
            if relations.old.search(header[header.find("("):]) or relations.old.search(body):
                return f"{scope} spells {old_word} itself, so its {new_word} could capture the rewrite"
            macro = invoked_macro(relations.macros, code, start, end)
            if macro:
                return (f"{scope} invokes the macro {macro}, whose expansion spells {old_word}, "
                        f"so its {new_word} could capture the rewrite")
            if kind == "param" and new_word not in set(parameters(params)):
                return f"{new_word} is spelled in {scope}'s header but is no parameter of it"
            if new_word in set(parameters(params)):
                continue
            if start not in masked:
                masked[start] = re.sub(r"(?<=::)(\s*)%s\b" % re.escape(new_word),
                                       lambda m: " " * len(m.group(0)), body)
            if local_use_outside_scope(masked[start], new_word) is not None:
                return f"{new_word} in {scope} is not confined to the scope of a local of that name"
        else:
            return f"{new_word} is a name at file scope"
    return relations.captured(code, new_word)


def relatives_outside_the_rewrite(ctx, touched, old_word, new_word, cls, max_files):
    """None, or why a canonical function rename may not share `new_word` with a
    class that sits outside the files the rewrite reads.

    other_scope_spellings runs on a touched file that spells `new_word`, but a
    class deriving from the renamed class (a base of one, or joint with one)
    that declares the word is often in a file that never spells `old_word`: a
    header the touched unit includes, or a unit that includes the touched
    header. Neither is touched, so neither was analysed, and the respelled
    method would hide or override the member there. So every other file that
    spells `new_word` is read here, once for each unit that sees the renamed
    class (a touched ledger source, or one that includes a touched header), over
    the unit's own text and its header closure. In those files:

      * each class that declares the word, or qualifies it, must be shown
        unrelated by ClassRelations;
      * a preprocessor line that spells the word is refused, as in a touched
        file (a macro can declare it inside any class);
      * an unqualified spelling inside a method of the renamed class, or of a
        class derived from one, is refused unless it is a parameter of that
        method or every use of it lies in the scope of a local of that name:
        after the rename it would bind to the renamed member instead of the
        global or inherited name it means now. The class is the one whose body
        holds the spelling or the one a qualified declarator names (spot_scope),
        so a member of a class template, an operator, a member-initializer
        list, a default argument and a static member's initializer are read as
        a plain method is. A method whose class is not declared with all its
        bases is refused too;
      * after the spellings, the scopes passed as unrelated are checked for
        the rewrite landing inside them (ClassRelations.captured), in the
        unit's text and in every header of its closure, since a method of an
        unrelated class may be defined out of line in either;
      * a spelling through `.` or `->`, a local or a file-scope name outside
        those methods has no bearing on the renamed class's scope and stays
        unread.

    A word an unreverted inferred landing holds is refused for the reason
    other files are (unreverted_landings). A file whose braces cannot be
    balanced is refused."""
    spelled = {}

    def code_of(path):
        if path not in spelled:
            spelled[path] = name_metric.strip((ctx.read(path) or b"").decode("utf-8", "replace"))
        return spelled[path]

    sharing = {p for p in ctx.grep_files(new_word, word=True) if code_mentions(code_of(p), new_word)}
    outside = sharing - set(touched)
    if not outside:
        return None
    landings = unreverted_landings(ctx, new_word)
    if landings:
        return (f"agree:{landings[0]} landed {new_word} as an inferred name, and reverting it is "
                "a whole-word rewrite this rename would make ambiguous")
    ledger = ctx.ledger_sources()
    headers = sorted(p for p in touched if p not in ledger)
    units = {p for p in touched if p in ledger}
    if headers:
        units |= includers(ctx, headers, max_files)
    for unit in sorted(units):
        closure = sorted(header_closure(ctx, unit))
        paths = [p for p in [unit] + closure if p in outside]
        relations = None
        for path in paths:
            text = code_of(path)
            if blank_continued_macro_spells(text, new_word):
                return f"a preprocessor line in {path} spells {new_word}, seen from {unit}"
            for at, kind in occurrence_spots(text, new_word, path):
                before = text[:at]
                if kind == "macro":
                    return f"a preprocessor line in {path} spells {new_word}, seen from {unit}"
                if re.search(r"::\s*$", before):
                    qualifier = re.search(r"([A-Za-z_]\w*)\s*(?:<[^<>]*>\s*)?::\s*$", before)
                    if not qualifier:
                        continue                    # ::word names a global, not a class member
                    other = qualifier.group(1)
                elif kind.startswith("class:"):
                    other = kind[6:]
                    if other == "*":
                        return f"{new_word} is a member of an anonymous type in {path}, seen from {unit}"
                elif kind in ("fnbody", "param", "ns") and not re.search(r"(?:->|\.)\s*$", before):
                    if kind != "fnbody" and not spot_scope(text, at, new_word)[0]:
                        continue                    # a file-scope name or a prototype's parameter name
                    other = None
                else:
                    continue
                if relations is None:
                    relations = ClassRelations(ctx, unit, code_of(unit), old_word, new_word, cls)
                    if relations.error:
                        return f"{relations.error}, and {path} spells {new_word}"
                if other is None:
                    why = capture_by_method(relations, text, at, new_word, kind)
                    if why:
                        return f"{why}; {path} spells {new_word}, which this rename does not rewrite"
                    continue
                why = relations.unrelated(other)
                if why:
                    return f"{why}; {path} spells {new_word}, which this rename does not rewrite"
        if relations is not None:
            for path in [unit] + closure:
                why = relations.captured(code_of(path), new_word)
                if why:
                    return why
    return None


def _blank_directives(text):
    return name_metric.PREPROCESSOR.sub(lambda m: re.sub(r"[^\n]", " ", m.group(0)), text)


def _collapse_parens(text):
    """`text` with each outermost parenthesised group emptied (an unclosed one is cut at its `(`)."""
    out, depth = [], 0
    for char in text:
        if char == "(":
            if depth == 0:
                out.append("(")
            depth += 1
        elif char == ")":
            depth = max(0, depth - 1)
            if depth == 0:
                out.append(")")
        elif depth == 0:
            out.append(char)
    return "".join(out)


_OPERATOR_NAME = re.compile(r"\boperator\s*(?:\(\s*\)|\[\s*\]|[-+*/%^&|~!=<>,]+|\w[\w \t*&:]*?(?=\s*\())")
_QUALIFIED_DECLARATOR = re.compile(r"([A-Za-z_]\w*)\s*::\s*~?\s*[A-Za-z_]\w*\s*(?=\(|\[|$)")


def _declarator_class(header):
    """The class a definition's declarator qualifies (`Sub` of `int Sub::k = `, `void Sub<T>::go`,
    `Sub::operator+`, `Sub::~Sub`), from the text of the statement or function header that holds it; None
    when the declared name is not qualified. A qualified name counts only as the declarator: followed by
    `(`, `[` or the end of the text that precedes the first `=`, outside every parenthesis, so a type
    (`Widget::Handle go()`) or a qualified call in an initializer or in a macro's arguments is not one."""
    head = _OPERATOR_NAME.sub("operator_", header)
    while True:
        flat = re.sub(r"(?<=\w)\s*<[^<>]*>", "", head)
        if flat == head:
            break
        head = flat
    head = _collapse_parens(re.sub(r"\btemplate\b", " ", head)).split("=", 1)[0].rstrip()
    match = _QUALIFIED_DECLARATOR.search(head)
    return match.group(1) if match else None


def spot_scope(text, at, word):
    """([class names], parameter list text, (begin, end) of the function body or None) of the unqualified
    spelling of `word` at offset `at` of stripped `text`, for the scopes that spelling can lie in without
    this scan recognising a function definition (name_metric.functions_in reads neither a member of a class
    template, nor an operator, nor a name that starts a line badly):

      * the class whose body holds it (a member declaration, a default argument, an inline method);
      * the class a qualified declarator names: `Sub` of `int Sub::k = ...`, of `Sub<T>::go() {...}`,
        of `Sub::operator+(...) {...}` and of `Sub::Sub() : a(...) {...}`, in the statement or in the header
        of the outermost braced block (a function body) that holds the spelling.

    The parameter list is that of the same declarator or header, up to the spelling; the body is the braced
    block, which is None when the spelling sits in the declarator itself (a default argument, a
    member-initializer list, a static member's initializer)."""
    code = _blank_directives(text)
    stack, parens, segment = [], 0, 0         # [kind, header start, `{` offset] of each open block
    for match in re.finditer(r"[{}();]", code[:at]):
        token = match.group(0)
        if token == "(":
            parens += 1
        elif token == ")":
            parens = max(0, parens - 1)
        elif parens:
            continue
        elif token == "{":
            stack.append((_segment_kind(code[segment:match.start()]), segment, match.start()))
            segment = match.end()
        elif token == "}":
            if stack:
                stack.pop()
            segment = match.end()
        else:
            segment = match.end()
    blocks = [(code[begin:brace], (brace, name_metric.close(code, brace))) for kind, begin, brace in stack
              if kind in ("fn", "other")]
    if not blocks:
        blocks = [(code[segment:at + len(word)], None)]
    header, body = next(((h, b) for h, b in blocks if _declarator_class(h)), blocks[0])
    qualifier = _declarator_class(header)
    # type_bodies reads `template<class T> class Sub {` as a class T, so a template head is blanked first
    heads = re.sub(r"\btemplate\s*<(?:[^<>]|<[^<>]*(?:<[^<>]*>[^<>]*)*>)*>", lambda m: " " * len(m.group(0)), code)
    names = [name for name in (qualifier, next((n for n, begin, stop in reversed(type_bodies(heads))
                                                if begin <= at < stop), None)) if name]
    paren = header.find("(", header.find("::") if qualifier else 0)
    params, depth = "", 0
    for char in (header[paren:] if paren >= 0 else ""):
        depth += (char == "(") - (char == ")")
        if depth == 0:
            break
        params += char
    return names, params[1:], body


def capture_by_method(relations, text, at, new_word, kind="fnbody"):
    """Why the unqualified spelling of `new_word` at offset `at` of stripped
    `text` (a function body, a member-initializer list, a default argument, a
    static member's initializer) would bind to the renamed member after the
    rewrite; None when it lies in no class that is or derives from a renamed
    class, or is a parameter of its function or confined to the scope of a
    local. `kind` is the occurrence_spots kind of the spelling. `relations` is
    the ClassRelations of the unit that sees `text`. A shape name_metric does not
    read as a function (spot_scope) is judged by the class it names or sits in."""
    func = _enclosing_function(text, at)
    names, params, body = spot_scope(text, at, new_word)
    if func is None:
        # a function this scan does not recognise: judged by the class body around it or the class its
        # declarator qualifies
        scope = None
        owners = names
    else:
        scope, start, body_start, end, fparams = func
        params = fparams
        body = (body_start, end)
        qualifiers = scope.split("#")[0].split("::")[:-1]
        owners = list(dict.fromkeys(qualifiers[-1:] + names))
    if new_word in set(parameters(params)):
        return None                                       # the parameter hides the member
    if body is not None and body[0] <= at:
        masked = re.sub(r"(?<=::)(\s*)%s\b" % re.escape(new_word), lambda m: " " * len(m.group(0)),
                        text[body[0]:body[1]])
        if local_use_outside_scope(masked, new_word) is None:
            return None                                   # every use is a local of that name
    if not owners:
        return None                                       # a free function: no class scope to capture
    where = "a function body this scan cannot delimit" if kind == "fnbody" else \
        "a declaration, initializer or default argument"
    for name in owners:
        chain, _known = class_chain(relations.bases, name)
        if chain & relations.renamed:
            if func is not None:
                return (f"{scope} is a method of {name}, which is or derives from a renamed class, and spells "
                        f"{new_word} unqualified, where the renamed member would capture it")
            return (f"{name} is or derives from a renamed class and spells {new_word} unqualified in {where}, "
                    "where the renamed member would capture it")
    if kind == "fnbody" or func is not None:
        for name in owners:
            if not class_chain(relations.bases, name)[1]:
                return f"{name}, in which {new_word} is spelled in a function, is not a class declared with all its bases"
    return None


def rewrite_units(ctx, plan, old_word, new_word, old_name, new_name, owner_source, max_files, *,
                  cls=None, kind="function", aliases=None):
    """Rewrite `old_word` in the owner, every file that spells it and every
    unit whose object references `old_name`; returns the ledger sources the
    build must verify (rewritten units, the owner, includers of a rewritten
    header). A word rewrite is whole-word, so a file that also declares the
    word as anything else (foreign_declarations) is refused."""
    touched = set(ctx.grep_files(old_word, word=True)) | {owner_source}
    by_object = object_referencers(ctx, old_name)
    for alias in aliases or ():
        by_object |= object_referencers(ctx, alias)
    touched |= by_object
    generated = sorted(p for p in touched if is_generated(p))
    if generated:
        raise Refusal(f"generated source(s) name {old_word}: {', '.join(generated[:5])}; "
                      "the rename would leave them stale and they are never edited")
    if len(touched) > max_files:
        raise Refusal(f"{len(touched)} files name {old_word} (over --max-files {max_files})")
    if kind == "function" and basis_kind(plan.basis) == "canonical" and cls:
        why = relatives_outside_the_rewrite(ctx, touched, old_word, new_word, cls, max_files)
        if why is not None:
            raise Refusal(f"{new_word} is already a name outside the files this rename rewrites ({why})")
    headers = []
    for rel in sorted(touched):
        data = ctx.read(rel)
        if data is None:
            raise Refusal(f"{rel} is listed but missing")
        text = data.decode("utf-8", errors="surrogateescape")
        if code_mentions(text, new_word):
            # A canonical function name is never reverted, so it may share its word
            # with another scope the rewrite cannot reach; an inferred name is
            # reverted by whole-word match, which must stay exact.
            why = "an inferred or global rename shares no word with another scope"
            if kind == "function" and basis_kind(plan.basis) == "canonical":
                why = other_scope_spellings(ctx, rel, name_metric.strip(text), old_word, new_word, cls)
                landings = unreverted_landings(ctx, new_word)
                if why is None and landings:
                    why = (f"agree:{landings[0]} landed {new_word} as an inferred name, and reverting it is "
                           "a whole-word rewrite this rename would make ambiguous")
            if why is not None:
                raise Refusal(f"{new_word} is already a name in {rel}" +
                              (f" ({why})" if kind == "function" and basis_kind(plan.basis) == "canonical" else ""))
        foreign = foreign_declarations(name_metric.strip(text), old_word, cls, kind)
        if foreign:
            raise Refusal(f"{rel} also declares {old_word} as {foreign[0]}; a word rewrite would rename "
                          "it too")
        new_text, counts, strings = rewrite_source(text, old_word, new_word, old_name, new_name)
        for alias, renamed in (aliases or {}).items():
            # a whole alias spelling in a comment or pragma (the word rewrite
            # leaves comments alone)
            new_text, n = mangled_re(alias).subn(lambda _m, r=renamed: r, new_text)
            counts["comment"] += n
        if strings:
            raise Refusal(f"{old_word} is spelled inside a string literal in {rel}: {strings[0][:80]} "
                          "(retail-locked text)")
        if new_text == text:
            if rel in by_object:
                raise Refusal(f"{rel}'s object references {old_name} but its text never spells "
                              f"{old_word} (a macro or generated name): cannot rewrite it")
            continue
        plan.source_counts[rel] = counts
        plan.edit(ctx, rel, new_text.encode("utf-8", errors="surrogateescape"))
        if not rel.endswith(SOURCE_SUFFIXES) or rel not in ctx.ledger_sources():
            headers.append(rel)
    verify = {rel for rel in plan.source_counts if rel in ctx.ledger_sources()}
    verify.add(owner_source)
    if headers:
        verify |= includers(ctx, headers, max_files)
    return verify


def plan_function(ctx, rva, new=None, basis=None, evidence="", *, old=None, max_files=25, virtual=False):
    """Plan respelling one RVA's function identifier everywhere it is named;
    with `virtual`, its decoration from non-virtual to virtual instead
    (plan_virtual: no new identifier, no basis, retail evidence)."""
    if virtual:
        if new or basis:
            raise Refusal("--virtual keeps the identifier and takes its evidence from retail: "
                          "pass neither a new name nor a basis")
        return plan_virtual(ctx, rva, evidence=evidence, old=old, max_files=max_files)
    rows = [r for r in ctx.rows() if _rva(r.get("target_rva")) == rva]
    if not rows:
        raise Refusal(f"no functions.csv row at 0x{rva:08X}")
    owners = [r for r in rows if not r["name"].startswith(("__ehhandler$", "__unwindfunclet$", "$L"))
              and "parent=" not in r.get("notes", "")]
    if old:
        owners = [r for r in owners if r["name"] == old]
        if not owners:
            raise Refusal(f"{old} has no row at 0x{rva:08X}")
    names = sorted({r["name"] for r in owners})
    if len(names) != 1:
        raise Refusal(f"0x{rva:08X} carries {len(names)} function names ({', '.join(names) or 'none'}); "
                      "pass --old to choose one")
    old_name = names[0]
    owner = owners[0]
    if is_generated(owner["source"]):
        raise Refusal(f"{old_name} lives in generated source {owner['source']}; "
                      "recover it as real C++ first (never edit Code/gen_*)")
    prefix, old_word, _ = split_function_name(old_name)
    new = new or ""
    if new.startswith("?"):
        # a full mangled spelling: it must equal the identifier-only rewrite
        new_word = split_function_name(new)[1]
        if new_word == old_word:
            raise Refusal("the new name is the old name")
        if rename_function_symbol(old_name, new_word) != new:
            raise Refusal(f"{new} changes the mangled signature beyond the identifier "
                          f"(identifier-only rewrite is {rename_function_symbol(old_name, new_word)})")
    else:
        new_word = new
    check_new_identifier(new_word, "function", basis)
    if new_word == old_word:
        raise Refusal("the new name is the old name")
    new_name = rename_function_symbol(old_name, new_word)

    reason = is_protected(ctx, "function", old_name, rva=rva, identifier=old_word)
    if reason:
        raise Refusal(f"canonical name: {reason}")
    refuse_vendored(ctx, [owner["source"]], f"renaming {old_name}")
    which = check_basis(ctx, "function", basis, evidence, old_name, old_word, rva, new_name=new_name,
                        new_word=new_word)

    # Collisions: one name, one identity.
    if any(r["name"] == new_name for r in ctx.rows()) or any(p.get("name") == new_name for p in ctx.pins()):
        raise Refusal(f"{new_name} already names a row or pin")
    tombstoned = _tombstones(ctx)
    if (new_name, rva) in tombstoned:
        raise Refusal(f"({new_name}, 0x{rva:08X}) is tombstoned in deleted_rows.csv: "
                      f"{tombstoned[(new_name, rva)][:120]}")
    # The identifier must denote only this function, or a word rewrite renames
    # something else too.
    old_re = mangled_re(old_name)
    statics = sorted(d.get("name", "") for d in ctx.dicts(DATA_ROWS) if old_re.search(d.get("name", "")))
    if statics:
        raise Refusal(f"data row {statics[0]} (a local static) embeds {old_name}; the function kind does not "
                      "rename data rows -- rename the static with the global kind's review first")
    # A caller unit that declares the function in its own view of the class
    # can mangle it differently (another back-reference order) and binds
    # through a pin at this same address: the same identity, so the same
    # rename. Only a pin at the address with the same qualified identifier
    # qualifies; anything else spelling the word is still refused below.
    aliases = alias_pins(ctx, old_name, rva)
    for alias in aliases:
        renamed = rename_function_symbol(alias, new_word)
        if any(r["name"] == renamed for r in ctx.rows()) or any(p.get("name") == renamed for p in ctx.pins()):
            raise Refusal(f"{renamed} (the alias pin {alias} renamed) already names a row or pin")
    own_re = re.compile("|".join(mangled_re(n).pattern for n in [old_name] + aliases))
    other = shared_identifier(ctx, old_word, own_re)
    if other:
        raise Refusal(f"{old_word} also spells {other}; a word rewrite would rename it too")
    frozen = frozen_mentions(ctx, old_name)
    if frozen:
        raise Refusal(f"{old_name} is a key in {', '.join(frozen)} (frozen, shrink-only); "
                      "renaming it needs a Verifier-Change commit")

    plan = Plan("function", old_name, new_name, basis, evidence.strip(), owner["source"], rva,
                old_word=old_word, new_word=new_word)

    # Ledgers.
    raw = ctx.read(FUNCTIONS)
    new_raw, changed = rewrite_records(raw, "functions.csv", old_re, new_name)
    for before, after in changed:
        at = _rva(before[2])
        if before[0] != after[0]:
            plan.renamed_rows.append((before[0], after[0], at))
        else:
            plan.notes_rows.append((before[0], at))
    for alias in aliases:
        new_raw, changed = rewrite_records(new_raw, "functions.csv", mangled_re(alias),
                                           rename_function_symbol(alias, new_word))
        for before, after in changed:
            if before[0] != after[0]:
                raise Refusal(f"functions.csv row {before[0]} embeds the alias pin {alias} in its name")
            plan.notes_rows.append((before[0], _rva(before[2])))
    plan.edit(ctx, FUNCTIONS, new_raw)
    raw = ctx.read(SYMBOLS)
    if raw is not None:
        new_raw, changed = rewrite_records(raw, "symbols.csv", old_re, new_name)
        for before, after in changed:
            plan.renamed_pins.append((before[0], after[0], before[1]))
        for alias in aliases:
            new_raw, changed_alias = rewrite_records(new_raw, "symbols.csv", mangled_re(alias),
                                                     rename_function_symbol(alias, new_word))
            for before, after in changed_alias:
                plan.renamed_pins.append((before[0], after[0], before[1]))
            changed = changed + changed_alias
        if changed:
            plan.edit(ctx, SYMBOLS, new_raw)
        others = sorted({p["name"] for p in ctx.pins() if _rva(p.get("address")) == rva
                         and p.get("name") != old_name and not own_re.search(p.get("name", ""))})
        for name in others:
            plan.warnings.append(f"pin {name} also names 0x{rva:08X} (not renamed; one address, one name)")
    # check_csv.check_body_owners: an audited owner's name must equal its row's.
    for before, _after in rewrite_ledger(ctx, plan, BODY_OWNERS, "body_owners.csv", old_re, new_name):
        plan.owner_rows.append((before[1], _rva(before[0])))
    reason_text = f"Renamed to {{new}} by tools/rename.py ({basis})"
    for old_row, new_row, at in plan.renamed_rows:
        if (old_row, at) in tombstoned:
            continue
        plan.edit(ctx, DELETED, appended(plan.after.get(DELETED, ctx.read(DELETED)),
                                         [tombstone_line(old_row, at, reason_text.format(new=new_row))],
                                         header="name,target_rva,reason"))
    plan.edit(ctx, NAME_BASIS, appended(ctx.read(NAME_BASIS), [csv_line(
        ["function", old_name, new_name, basis, plan.evidence, owner["source"], f"0x{rva:08X}"])],
        header=NAME_BASIS_HEADER))

    old_scope, new_scope = scope_of(old_name), scope_of(new_name)

    def carried(spelling):
        if old_re.search(spelling):
            return old_re.sub(lambda _m: new_name, spelling)
        if old_scope and new_scope and re.match(re.escape(old_scope) + r"(?:#\d+)?::", spelling):
            return new_scope + spelling[len(old_scope):]
        return None
    carry_records(ctx, plan, carried)
    scope = scope_of(old_name) or ""
    verify = rewrite_units(ctx, plan, old_word, new_word, old_name, new_name, owner["source"], max_files,
                           cls=scope.rsplit("::", 1)[0].split("::")[-1] if "::" in scope else None,
                           aliases={a: rename_function_symbol(a, new_word) for a in aliases})
    verify |= {r["source"] for r in ctx.rows() if r["name"] in {o for o, _, _ in plan.renamed_rows}}
    verify |= {r["source"] for r in ctx.rows()
               if (r["name"], _rva(r.get("target_rva"))) in set(plan.notes_rows)}
    plan.verify = sorted(v for v in verify if not is_generated(v))
    if len(plan.verify) > max_files:
        raise Refusal(f"{len(plan.verify)} sources to verify (over --max-files {max_files})")

    plan.claims = sorted({at for _, _, at in plan.renamed_rows} | {at for _, at in plan.notes_rows}) + \
        [f"file:{owner['source']}"]
    edited = set(plan.after) | {"reverse/re_attempts.log"}
    plan.mentions = sorted(set(ctx.grep_files(old_name, roots=("docs", "reverse"))) - edited) + \
        sorted(set(ctx.grep_files(old_word, word=True, roots=("docs",))) - edited
               - set(ctx.grep_files(old_name, roots=("docs",))))
    return plan


# ---------------------------------------------------------------- virtual respell
#
# A row spelled non-virtual (`?f@C@@QAEXH@Z`) whose function retail reaches
# through a vtable slot is `?f@C@@UAEXH@Z`: the identifier, scope, parameters
# and return type stay, one character of the decoration changes. `function`
# refuses that (a signature change) and no hand rename may make it over a real
# name, so `function --virtual` makes exactly that change, and only on retail
# evidence: a table that retail code installs (`mov dword ptr [reg+disp],
# imm32`, the store tools/vftable_map.py reads, here with a displacement too
# so a secondary table of a multiply-derived class counts) has a slot holding
# the row's address, and that table belongs to the row's class -- a ctor, dtor
# or deleting dtor of the class installs it, or the data ledger names it
# `??_7Class@@6B..@` -- or to a class that a view (the installer's unit and
# its headers) derives from the row's class. An address other rows or pins
# share (an ICF fold) proves only that some folded function is virtual, so it
# is refused. A destructor is virtual exactly when its deleting destructors
# are: `??1C`, `??_GC` and `??_EC` are respelled together, the deleting
# destructor on its slot and the destructor because that deleting
# destructor's retail body calls it. Every class body of C that declares the
# method (or `~C`) gains `virtual`, every spelled mangled name (comments,
# linker pragmas, __identifier strings) and every ledger, pin and notes token
# takes the new decoration, and ./build.sh decides: a caller whose call now
# goes through the vtable, or a view whose layout gains a vptr, changes bytes
# and the whole edit is restored.

NONVIRTUAL_ACCESS = {"A": "E", "I": "M", "Q": "U"}   # private / protected / public near member
VIRTUAL_ACCESS = frozenset("EFMNUV")
# A shared body: the row notes record an ICF fold or an alias.
FOLD_NOTES = re.compile(r"fold-proof=|icf-owner=|dup-of=|\bICF\b", re.I)
VIRTUAL_MEMBER = re.compile(r"\?([A-Za-z_]\w*)@((?:[A-Za-z_]\w*@)+)@")
VIRTUAL_DTOR = re.compile(r"\?\?(1|_G|_E)((?:[A-Za-z_]\w*@)+)@")
INSTALLER_CLASS = re.compile(r"\?\?(?:0|1|_G|_E)([A-Za-z_]\w*)@")
VTABLE_NAME = re.compile(r"\?\?_7([A-Za-z_]\w*)@")
DECLSPEC = re.compile(r"__declspec\s*\([^()]*\)")


def member_function_header(mangled):
    """(index of the access code, class, enclosing scopes, role) of a member
    function's decorated name; role is `method` (?f@C@@), `dtor` (??1C@@) or
    `deleting` (??_GC@@, ??_EC@@). Anything else -- a free function, a
    constructor, an operator, a template, a funclet -- is refused."""
    role = "method"
    match = VIRTUAL_MEMBER.match(mangled)
    if not match:
        match = VIRTUAL_DTOR.match(mangled)
        if not match:
            raise Refusal(f"{mangled} is not a method, destructor or deleting destructor this mode can "
                          "respell (constructors, operators, templates and funclets are not)")
        role = "dtor" if match.group(1) == "1" else "deleting"
    scopes = match.group(2).rstrip("@").split("@")
    at = match.end()
    try:
        end = _parse_header(mangled, at, _Out())
    except (IndexError, ValueError) as error:
        raise Refusal(f"{mangled}: cannot read its decoration ({error})") from None
    if end != len(mangled):
        raise Refusal(f"{mangled}: trailing {mangled[end:]!r} after its decoration")
    return at, scopes[0], scopes[1:], role


def virtual_symbol(mangled):
    """`mangled` with its access code respelled virtual (QAE -> UAE, IAE ->
    MAE, AAE -> EAE); identifier, scope, cv, convention, return type and
    parameters are kept byte for byte."""
    at, _cls, _scopes, _role = member_function_header(mangled)
    code = mangled[at]
    if code in VIRTUAL_ACCESS:
        raise Refusal(f"{mangled} is already spelled virtual")
    if code not in NONVIRTUAL_ACCESS:
        raise Refusal(f"{mangled} is not a non-static member function (access code {code!r}): only a member "
                      "function can be virtual")
    return mangled[:at] + NONVIRTUAL_ACCESS[code] + mangled[at + 1:]


def retail_vtables(ctx):
    """{table rva: (slot targets, {store rva: this offset})} for every table
    retail code installs with `mov dword ptr [reg], imm32` or `[reg+disp]`
    (tools/vftable_map.py's reading, with the displacement forms a secondary
    table's install takes): the immediate is an .rdata address whose run of
    .text pointers is the table, cut where the next installed table starts.
    Read from the md5-verified retail image (build.exe_image)."""
    key = "_retail_vtables"
    if key in ctx._cache:
        return ctx._cache[key]
    import struct
    import build
    image, sections = build.exe_image()
    named = {s["name"]: s for s in sections}
    text, rdata = named[".text"], named[".rdata"]
    t_lo, t_hi = text["rva"], text["rva"] + text["size"]
    r_lo, r_hi = rdata["rva"], rdata["rva"] + rdata["size"]

    def read(rva, size):
        try:
            offset = build.rva_to_file_offset(sections, rva)
        except ValueError:
            return None
        chunk = image[offset:offset + size]
        return chunk if len(chunk) == size else None

    code = image[build.rva_to_file_offset(sections, t_lo):][:min(text["size"], text["raw_size"])]
    installs = collections.defaultdict(dict)
    for match in re.finditer(rb"\xC7", code):
        i = match.start()
        if i + 11 > len(code):
            break
        modrm = code[i + 1]
        mod, reg, rm = modrm >> 6, (modrm >> 3) & 7, modrm & 7
        if reg or mod == 3 or rm == 4 or (mod == 0 and rm == 5):
            continue                      # C7 /0 through a base register, no SIB, no absolute address
        disp = 0 if mod == 0 else struct.unpack_from("<b" if mod == 1 else "<i", code, i + 2)[0]
        table = struct.unpack_from("<I", code, i + 2 + (0, 1, 4)[mod])[0] - IMAGE_BASE
        if not r_lo <= table < r_hi:
            continue
        first = read(table, 4)
        if first is None or not t_lo <= struct.unpack("<I", first)[0] - IMAGE_BASE < t_hi:
            continue
        installs[table][t_lo + i] = disp
    tables = {}
    ordered = sorted(installs)
    for at, table in enumerate(ordered):
        limit = (ordered[at + 1] - table) // 4 if at + 1 < len(ordered) else 512
        slots = []
        while len(slots) < min(limit, 512):
            word = read(table + 4 * len(slots), 4)
            if word is None or not t_lo <= struct.unpack("<I", word)[0] - IMAGE_BASE < t_hi:
                break
            slots.append(struct.unpack("<I", word)[0] - IMAGE_BASE)
        tables[table] = (slots, installs[table])
    ctx._cache[key] = tables
    return tables


def retail_calls(ctx, rva, size):
    """The targets of every `call rel32` in retail's bytes [rva, rva+size)."""
    import struct
    import build
    image, sections = build.exe_image()
    try:
        offset = build.rva_to_file_offset(sections, rva)
    except ValueError:
        return set()
    body = image[offset:offset + size]
    return {(rva + i + 5 + struct.unpack_from("<i", body, i + 1)[0]) & 0xFFFFFFFF
            for i in range(len(body) - 4) if body[i] == 0xE8}


def _row_spans(ctx):
    key = "_row_spans"
    if key not in ctx._cache:
        spans = []
        for row in ctx.rows():
            if row["name"].startswith(FUNCLET_PREFIXES + ("$L",)) or "parent=" in row.get("notes", ""):
                continue
            start = _rva(row.get("target_rva"))
            try:
                size = int(row.get("target_size") or 0)
            except ValueError:
                size = 0
            if start is not None and size > 0:
                spans.append((start, start + size, row))
        spans.sort(key=lambda s: s[0])
        ctx._cache[key] = ([s[0] for s in spans], spans)
    return ctx._cache[key]


def row_at(ctx, address):
    """The functions.csv owner row whose body holds `address`, or None."""
    import bisect
    starts, spans = _row_spans(ctx)
    k = bisect.bisect_right(starts, address) - 1
    while k >= 0 and address - spans[k][0] < 0x20000:
        if spans[k][0] <= address < spans[k][1]:
            return spans[k][2]
        k -= 1
    return None


def table_classes(ctx, table, stores, tables):
    """{class: how} that own retail table `table`: the class of a ctor, dtor
    or deleting dtor row that installs it (at a displacement only when that
    row also installs a table at +0: a polymorphic object's primary vptr, not
    a member object's), and a data_rows.csv `??_7Class@@6B..@` at its
    address."""
    primary = ctx._cache.get("_primary_stores")
    if primary is None:
        primary = sorted(store for _slots, installs in tables.values() for store, disp in installs.items()
                         if disp == 0)
        ctx._cache["_primary_stores"] = primary
    import bisect
    out = {}
    for store, disp in sorted(stores.items()):
        row = row_at(ctx, store)
        match = INSTALLER_CLASS.match(row["name"]) if row else None
        if not match:
            continue
        start = _rva(row["target_rva"])
        end = start + int(row["target_size"])
        k = bisect.bisect_left(primary, start)
        if disp and not (k < len(primary) and primary[k] < end):
            continue
        out.setdefault(match.group(1), (f"installed at +0x{disp:X} by 0x{start:08X} {row['name']}",
                                        row.get("source", "")))
    for data in ctx.dicts(DATA_ROWS):
        match = VTABLE_NAME.match(data.get("name", ""))
        if match and data_rva(data) == table:
            out.setdefault(match.group(1), (f"data_rows.csv names it {data['name']}", data.get("source", "")))
    return out


def virtual_slots(ctx, rva, cls, sources):
    """([(table, slot, how)] proving `rva` a virtual of `cls`, [why each other
    slot holding `rva` does not]). A table proves it when it is `cls`'s own
    or belongs to a class that a view derives from `cls` (class_base_map over
    the installer's unit, `sources` and their headers)."""
    found, rejected = [], []
    tables = retail_vtables(ctx)
    for table, (slots, stores) in sorted(tables.items()):
        for index, target in enumerate(slots):
            if target != rva:
                continue
            where = f"retail table 0x{table + IMAGE_BASE:08X} slot {index}"
            classes = table_classes(ctx, table, stores, tables)
            if cls in classes:
                found.append((table, index, f"{where}, {cls}'s table ({classes[cls][0]})"))
                continue
            proof = None
            for other, (how, source) in sorted(classes.items()):
                for rel in sorted({source, *sources} - {""}):
                    if cls in class_chain(class_base_map(ctx, rel), other)[0]:
                        proof = f"{where}, the table of {other} ({how}), which {rel} derives from {cls}"
                        break
                if proof:
                    break
            if proof:
                found.append((table, index, proof))
            else:
                owners = ", ".join(sorted(classes)) or "no class the ledger names"
                rejected.append(f"{where} belongs to {owners}, not {cls} nor a class a view derives from it")
    return found, rejected


def _brace_depth(code, start, at):
    return code.count("{", start, at) - code.count("}", start, at)


def _statement_start(code, start, at):
    """Where the member declaration holding offset `at` starts inside the class
    body that opens at `start`: after the last `;`, `{`, `}` or access
    specifier, past blanks and preprocessor lines."""
    cut = start
    for match in re.finditer(r"[;{}]", code[start:at]):
        cut = start + match.end()
    for match in ACCESS.finditer(code, start, at):
        cut = max(cut, match.end())
    while True:
        while cut < at and code[cut].isspace():
            cut += 1
        if cut < at and code[cut] == "#":
            newline = code.find("\n", cut)
            cut = at if newline < 0 or newline > at else newline + 1
            continue
        return cut


def virtual_declarations(code, cls, word=None):
    """[(offset, already virtual)] of each in-class declaration of member
    function `word` (or of `~cls` when `word` is None) directly in a body of
    class `cls` in stripped `code`. A call, initializer or friend declaration
    is not one; a static or template member, or two declarations in one body
    (an overload set: which one retail made virtual is not read here), is
    refused."""
    target = re.compile(r"~\s*%s\s*\(" % re.escape(cls) if word is None
                        else r"(?<![\w~:.>])%s\s*\(" % re.escape(word))
    shown = f"~{cls}" if word is None else word
    out = []
    for start, end in class_bodies(code, cls):
        found = []
        for match in target.finditer(code, start, end):
            if _brace_depth(code, start, match.start()):
                continue
            begin = _statement_start(code, start, match.start())
            bare = DECLSPEC.sub(" ", code[begin:match.start()])
            if re.search(r"[(){}=,?;]|(?<!:):(?!:)", bare) or re.search(r"\b(?:friend|typedef)\b", bare):
                continue
            if re.search(r"\b(?:static|template)\b", bare):
                raise Refusal(f"class {cls} declares {shown} static or as a template")
            found.append((begin, bool(re.search(r"\bvirtual\b", bare))))
        if len(found) > 1:
            raise Refusal(f"class {cls} declares {shown} {len(found)} times in one body (an overload set): "
                          "which one retail made virtual is not read here")
        out += found
    return out


def respell_virtual_text(text, cls, word, pairs):
    """(new text, declarations made virtual, mangled spellings respelled) for
    one file: `virtual` before each in-class declaration of `word` (`~cls`
    when None) in class `cls`, then every whole old mangled name of `pairs`
    respelled. A plain string literal spelling an old name is retail-locked
    text: refused."""
    for match in SEGMENT.finditer(text):
        seg = match.group(0)
        if seg.startswith(("//", "/*", "'")):
            continue
        line_start = text.rfind("\n", 0, match.start()) + 1
        if PRAGMA_LINKER.match(text, line_start) or identifier_string(text, match.start()):
            continue
        for old, _new in pairs:
            if mangled_re(old).search(seg):
                raise Refusal(f"{old} is spelled inside a string literal: {seg[:80]} (retail-locked text)")
    code = name_metric.strip(text)
    made = 0
    for begin, already in sorted(virtual_declarations(code, cls, word), reverse=True):
        if not already:
            text = text[:begin] + "virtual " + text[begin:]
            made += 1
    respelled = 0
    for old, new in pairs:
        text, count = mangled_re(old).subn(lambda _m, n=new: n, text)
        respelled += count
    return text, made, respelled


def object_confirms(ctx, rel, symbols):
    """True when a current object of `rel` (compiled from its present text, by
    the build's sidecar) names one of `symbols` in its symbol table."""
    import build
    import name_dependents
    objects = name_dependents._row_objects([r for r in ctx.rows() if r.get("source") == rel]).get(rel, [])
    digest = build._hash_file(str(ctx.path(rel))) if ctx.path(rel).exists() else None
    for path in objects:
        if not path.exists():
            continue
        if not rel.lower().endswith(build.LIB_SUFFIX) and not name_dependents.compiled_from(path, digest):
            continue
        if name_dependents.coff_symbol_names(path.read_bytes(), include_local=False) & set(symbols):
            return True
    return False


def plan_virtual(ctx, rva, *, evidence="", old=None, max_files=25):
    """Plan respelling one row (and, for a destructor, its deleting
    destructors, or the reverse) from non-virtual to virtual on retail vtable
    evidence; see the section comment. Raises Refusal; writes nothing."""
    owners = [r for r in ctx.rows() if _rva(r.get("target_rva")) == rva
              and not r["name"].startswith(FUNCLET_PREFIXES + ("$L",)) and "parent=" not in r.get("notes", "")]
    if old:
        owners = [r for r in owners if r["name"] == old]
        if not owners:
            raise Refusal(f"{old} has no row at 0x{rva:08X}")
    names = sorted({r["name"] for r in owners})
    if len(names) != 1:
        raise Refusal(f"0x{rva:08X} carries {len(names)} function names ({', '.join(names) or 'none'}); "
                      "pass --old to choose one")
    first = owners[0]
    _at, cls, scopes, role = member_function_header(first["name"])
    virtual_symbol(first["name"])

    # The group: the row, and for the destructor family every non-virtual
    # ??1 / ??_G / ??_E row of the same class, each on its own evidence.
    scope_text = "@".join([cls] + scopes) + "@@"
    if role == "method":
        family = [first]
    else:
        spelled = re.compile(r"\?\?(?:1|_G|_E)%s[AIQ]" % re.escape(scope_text))
        family = [r for r in ctx.rows() if spelled.match(r["name"]) and r.get("status") == "matched"]
        if first not in family:
            family.append(first)
    evidence_of, problems = {}, []
    sources = {r["source"] for r in family}
    for row in family:
        if member_function_header(row["name"])[3] == "dtor":
            continue
        found, rejected = virtual_slots(ctx, _rva(row["target_rva"]), cls, sources)
        if found:
            evidence_of[row["name"]] = found[0][2]
        else:
            problems.append(f"{row['name']} at 0x{_rva(row['target_rva']):08X}: no retail vtable slot of {cls} "
                            "or of a class a view derives from it holds it" +
                            (f" ({'; '.join(rejected[:3])})" if rejected else ""))
    for row in family:
        if member_function_header(row["name"])[3] != "dtor":
            continue
        at = _rva(row["target_rva"])
        callers = [d for d in family if d["name"] in evidence_of and
                   at in retail_calls(ctx, _rva(d["target_rva"]), int(d["target_size"]))]
        if callers:
            evidence_of[row["name"]] = (f"called by {callers[0]['name']} at 0x{_rva(callers[0]['target_rva']):08X}"
                                        f" ({evidence_of[callers[0]['name']]})")
        else:
            problems.append(f"{row['name']} at 0x{at:08X}: no deleting destructor of {cls} on a retail vtable "
                            "slot calls it")
    if problems:
        raise Refusal("no retail evidence for a virtual respell: " + "; ".join(problems))

    pairs, rvas = [], set()
    tombstoned = _tombstones(ctx)
    records = current_records(ctx)
    for row in family:
        name, at = row["name"], _rva(row["target_rva"])
        new_name = virtual_symbol(name)
        if is_generated(row["source"]):
            raise Refusal(f"{name} lives in generated source {row['source']}; recover it as real C++ first")
        # The identifier is kept: a method is judged by its word as `function`
        # judges it; a destructor's class token is not renamed, so only the
        # decorated name itself (an export, vendored, evidence-tier, canonical).
        reason = is_protected(ctx, "function", name, rva=at,
                              identifier=scope_of(name).rsplit("::", 1)[-1] if role == "method" else name)
        if reason:
            raise Refusal(f"canonical name: {reason}")
        refuse_vendored(ctx, [row["source"]], f"respelling {name}")
        if any(r["name"] == new_name for r in ctx.rows()) or any(p.get("name") == new_name for p in ctx.pins()):
            raise Refusal(f"{new_name} already names a row or pin")
        if (new_name, at) in tombstoned:
            raise Refusal(f"({new_name}, 0x{at:08X}) is tombstoned in deleted_rows.csv: "
                          f"{tombstoned[(new_name, at)][:120]}")
        shared = sorted({r["name"] for r in ctx.rows() if _rva(r.get("target_rva")) == at and r["name"] != name
                         and not r["name"].startswith(FUNCLET_PREFIXES + ("$L",))
                         and "parent=" not in r.get("notes", "")} |
                        {p.get("name", "") for p in ctx.pins() if _rva(p.get("address")) == at
                         and p.get("name") != name})
        if shared or FOLD_NOTES.search(row.get("notes", "")):
            raise Refusal(f"0x{at:08X} is a shared body ({', '.join(shared[:3]) or 'its notes record a fold'}): "
                          "a slot there proves only that some folded function is virtual")
        old_re = mangled_re(name)
        if any(old_re.search(d.get("name", "")) for d in ctx.dicts(DATA_ROWS)):
            raise Refusal(f"a data row (a local static) embeds {name}; rename the static first")
        frozen = frozen_mentions(ctx, name)
        if frozen:
            raise Refusal(f"{name} is a key in {', '.join(frozen)} (frozen, shrink-only)")
        pairs.append((name, new_name))
        rvas.add(at)

    plan = Plan("function", first["name"], virtual_symbol(first["name"]), "virtual",
                " ".join((evidence or "").split()), first["source"], rva, virtual=True)
    plan.evidence = "; ".join(f"{old} -> {new}: {evidence_of[old]}" for old, new in pairs) + \
        (f"; {plan.evidence}" if plan.evidence else "")

    # Ledgers: rows, funclet rows and notes tokens, pins, audited owners.
    raw = ctx.read(FUNCTIONS)
    for name, new_name in pairs:
        raw, changed = rewrite_records(raw, "functions.csv", mangled_re(name), new_name)
        for before, after in changed:
            if before[0] != after[0]:
                plan.renamed_rows.append((before[0], after[0], _rva(before[2])))
            else:
                plan.notes_rows.append((before[0], _rva(before[2])))
    plan.edit(ctx, FUNCTIONS, raw)
    raw = ctx.read(SYMBOLS)
    if raw is not None:
        edited = False
        for name, new_name in pairs:
            raw, changed = rewrite_records(raw, "symbols.csv", mangled_re(name), new_name)
            plan.renamed_pins += [(before[0], after[0], before[1]) for before, after in changed]
            edited = edited or bool(changed)
        if edited:
            plan.edit(ctx, SYMBOLS, raw)
    for name, new_name in pairs:
        for before, _after in rewrite_ledger(ctx, plan, BODY_OWNERS, "body_owners.csv", mangled_re(name),
                                             new_name):
            plan.owner_rows.append((before[1], _rva(before[0])))
    reason_text = "Renamed to {new} by tools/rename.py (virtual: retail vtable slot)"
    lines = [tombstone_line(old_row, at, reason_text.format(new=new_row))
             for old_row, new_row, at in plan.renamed_rows if (old_row, at) not in tombstoned]
    if lines:
        plan.edit(ctx, DELETED, appended(ctx.read(DELETED), lines, header="name,target_rva,reason"))
    # name_basis.csv: a record of the old spelling moves with it (a carry row,
    # as for a method of a renamed class); the name's basis is unchanged. A
    # name with no record keeps none (docs/naming.md, "Renaming by hand").
    carried = []
    for name, new_name in pairs:
        record = records.get(name)
        if record:
            plan.carried.append((name, new_name, record.get("basis", "")))
            carried.append(csv_line(["carry", name, new_name, record.get("basis", ""),
                                     f"virtual respell by tools/rename.py: {evidence_of[name]}",
                                     record.get("source", ""), record.get("rva", "")]))
        else:
            plan.warnings.append(f"{name} has no name_basis.csv record to carry: its tier is unchanged")
    if carried:
        plan.edit(ctx, NAME_BASIS, appended(ctx.read(NAME_BASIS), carried, header=NAME_BASIS_HEADER))

    # Sources: every file spelling an old name, every file declaring the
    # method in a body of the class, every unit whose object references one.
    word = scope_of(first["name"]).rsplit("::", 1)[-1] if role == "method" else None
    olds = [name for name, _new in pairs]
    candidates = set()
    for name in olds:
        candidates |= set(ctx.grep_files(name))
    declarers = set(ctx.grep_files(cls, word=True))
    candidates |= declarers & set(ctx.grep_files(word, word=True)) if word else declarers
    by_object = object_referencers(ctx, set(olds))
    candidates |= by_object | sources
    headers, rewritten = [], set()
    for rel in sorted(candidates):
        data = ctx.read(rel)
        if data is None:
            raise Refusal(f"{rel} is listed but missing")
        text = data.decode("utf-8", errors="surrogateescape")
        new_text, made, respelled = respell_virtual_text(text, cls, word, pairs)
        if new_text == text:
            # object_referencers widens to a text match where no current object
            # exists; only a current object naming an old symbol is a consumer
            # this rewrite would miss (name_dependents still builds the rest).
            if rel in by_object and object_confirms(ctx, rel, set(olds)):
                raise Refusal(f"{rel}'s object references {', '.join(olds)} but no body of class {cls} there "
                              f"declares {word or '~' + cls} to make virtual, nor does its text spell the name "
                              "(an implicit member or a base's declaration: reconcile the view first)")
            continue
        if is_generated(rel):
            raise Refusal(f"generated source {rel} declares or spells {first['name']}; it is never edited")
        refuse_vendored(ctx, [rel], f"respelling {first['name']}")
        rewritten.add(rel)
        plan.source_counts[rel] = {"virtual": made, "mangled": respelled}
        plan.edit(ctx, rel, new_text.encode("utf-8", errors="surrogateescape"))
        if not rel.endswith(SOURCE_SUFFIXES) or rel not in ctx.ledger_sources():
            headers.append(rel)
    if len(rewritten) > max_files:
        raise Refusal(f"{len(rewritten)} files to rewrite (over --max-files {max_files})")
    verify = {rel for rel in rewritten if rel in ctx.ledger_sources()} | sources
    if headers:
        verify |= includers(ctx, headers, max_files)
    renamed = {o for o, _, _ in plan.renamed_rows}
    verify |= {r["source"] for r in ctx.rows() if r["name"] in renamed}
    verify |= {r["source"] for r in ctx.rows() if (r["name"], _rva(r.get("target_rva"))) in set(plan.notes_rows)}
    plan.verify = sorted(v for v in verify if not is_generated(v))
    if len(plan.verify) > max_files:
        raise Refusal(f"{len(plan.verify)} sources to verify (over --max-files {max_files})")
    plan.claims = sorted({at for _, _, at in plan.renamed_rows} | {at for _, at in plan.notes_rows} | rvas) + \
        sorted(f"file:{rel}" for rel in sources)
    written = set(plan.after) | {"reverse/re_attempts.log"}
    plan.mentions = sorted({rel for name in olds for rel in ctx.grep_files(name, roots=("docs", "reverse"))}
                           - written)
    return plan


# ---------------------------------------------------------------- globals

def data_rva(row):
    """A data_rows.csv row's RVA (its address read the way address_kind says)."""
    address = _rva(row.get("address"))
    if address is None:
        return None
    return address - IMAGE_BASE if row.get("address_kind") == "va" else address


def _identifier(symbol):
    try:
        return split_function_name(symbol)[1]
    except Refusal:
        return None


def plan_global(ctx, name, new, basis, evidence, *, max_files=25):
    """Plan respelling one reverse/data_rows.csv global everywhere it is named.

    The byte gate masks DIR32 operands, so a consumer left on the old name
    still byte-matches and only the link breaks: the plan has to find every
    consumer itself, by text and by object symbol table, and refuses when it
    cannot rewrite one."""
    rows = ctx.dicts(DATA_ROWS)
    if name.startswith("?") or "@" in name:
        owners = [r for r in rows if r.get("name") == name]
    else:
        owners = [r for r in rows if r.get("name") == name or _identifier(r.get("name", "")) == name]
    if not owners:
        raise Refusal(f"no reverse/data_rows.csv row names {name}")
    names = sorted({r["name"] for r in owners})
    if len(names) != 1:
        raise Refusal(f"{name} matches {len(names)} data rows ({', '.join(names[:4])}); "
                      "pass the mangled name")
    old_name = names[0]
    if len(owners) != 1:
        raise Refusal(f"{old_name} has {len(owners)} data_rows.csv rows; rename needs one global, one row")
    owner = owners[0]
    rva = data_rva(owner)
    if rva is None:
        raise Refusal(f"{old_name}'s data row has no readable address")
    source = owner.get("source", "")
    if is_generated(source):
        raise Refusal(f"{old_name} lives in generated source {source} (never edit Code/gen_*)")
    if source not in ctx.ledger_sources():
        raise Refusal(f"{source} owns no matched function row; ./build.sh could not verify the rename")
    if old_name.startswith("??"):
        raise Refusal(f"{old_name} is a compiler-named datum (vftable, RTTI, local static); "
                      "rename its class or function instead")
    _prefix, old_word, _ = split_function_name(old_name)
    new = new or ""
    if new.startswith("?") or "@" in new:
        new_word = _identifier(new)
        if not new_word or rename_function_symbol(old_name, new_word) != new:
            raise Refusal(f"{new} changes the mangled data symbol beyond the identifier")
    else:
        new_word = new
    check_new_identifier(new_word, "global", basis)
    if new_word == old_word:
        raise Refusal("the new name is the old name")
    new_name = rename_function_symbol(old_name, new_word)

    reason = is_protected(ctx, "global", old_name, rva=rva, identifier=old_word)
    if reason:
        raise Refusal(f"canonical name: {reason}")
    for row in ctx.dicts(CONVERGED):
        if _rva(row.get("address")) == rva:
            raise Refusal(f"0x{rva:08X} is a converged address (reverse/data_converged.csv binds "
                          f"{row.get('name')}); data_check --converged refuses renaming it")
    refuse_vendored(ctx, [source], f"renaming {old_name}")
    which = check_basis(ctx, "global", basis, evidence, old_name, old_word, rva, new_name=new_name,
                        new_word=new_word)

    if any(r.get("name") == new_name for r in rows) or any(r["name"] == new_name for r in ctx.rows()) \
            or any(p.get("name") == new_name for p in ctx.pins()):
        raise Refusal(f"{new_name} already names a data row, function or pin")
    clash = shared_identifier(ctx, new_word, re.compile(r"(?!)"))
    if clash:
        raise Refusal(f"{new_word} already spells {clash}")
    old_re = mangled_re(old_name)
    other = shared_identifier(ctx, old_word, old_re)
    if other:
        raise Refusal(f"{old_word} also spells {other}; a word rewrite would rename it too")
    frozen = [rel for rel in frozen_mentions(ctx, old_name) if rel != DATA_LEDGER]
    if frozen:
        raise Refusal(f"{old_name} is a key in {', '.join(frozen)} (frozen, shrink-only); "
                      "renaming it needs a Verifier-Change commit")

    plan = Plan("global", old_name, new_name, basis, evidence.strip(), source, rva,
                old_word=old_word, new_word=new_word)
    raw = ctx.read(DATA_ROWS)
    new_raw, changed = rewrite_records(raw, "data_rows.csv", old_re, new_name)
    for before, after in changed:
        if before[0] != after[0]:
            plan.renamed_data.append((before[0], after[0], rva))
    plan.edit(ctx, DATA_ROWS, new_raw)
    raw = ctx.read(FUNCTIONS)
    new_raw, changed = rewrite_records(raw, "functions.csv", old_re, new_name)
    for before, after in changed:
        if before[0] != after[0]:
            raise Refusal(f"functions.csv row {before[0]} embeds {old_name} in its name")
        plan.notes_rows.append((before[0], _rva(before[2])))
    if changed:
        plan.edit(ctx, FUNCTIONS, new_raw)
    raw = ctx.read(SYMBOLS)
    if raw is not None:
        new_raw, changed = rewrite_records(raw, "symbols.csv", old_re, new_name)
        for before, after in changed:
            plan.renamed_pins.append((before[0], after[0], before[1]))
        if changed:
            plan.edit(ctx, SYMBOLS, new_raw)
    tombstoned = _tombstones(ctx)
    reason_text = f"Renamed to {new_name} by tools/rename.py ({basis})"
    if (old_name, rva) not in tombstoned:
        plan.edit(ctx, DELETED, appended(ctx.read(DELETED), [tombstone_line(old_name, rva, reason_text)],
                                         header="name,target_rva,reason"))
    plan.edit(ctx, NAME_BASIS, appended(ctx.read(NAME_BASIS), [csv_line(
        ["global", old_name, new_name, basis, plan.evidence, source, f"0x{rva:08X}"])],
        header=NAME_BASIS_HEADER))

    verify = rewrite_units(ctx, plan, old_word, new_word, old_name, new_name, source, max_files,
                           kind="global")
    verify |= {r["source"] for r in ctx.rows()
               if (r["name"], _rva(r.get("target_rva"))) in set(plan.notes_rows)}
    plan.verify = sorted(v for v in verify if not is_generated(v))
    if len(plan.verify) > max_files:
        raise Refusal(f"{len(plan.verify)} sources to verify (over --max-files {max_files})")
    plan.claims = sorted({rva} | {at for _, at in plan.notes_rows if at is not None}) + [f"file:{source}"]
    edited = set(plan.after) | {"reverse/re_attempts.log"}
    if ctx.read(DATA_LEDGER) is not None and old_name.encode() in ctx.read(DATA_LEDGER):
        plan.warnings.append(f"{DATA_LEDGER} (tool-written, protected) still spells {old_name}; "
                             "data_check reads it in shadow mode until tools/data_ledger.py regenerates "
                             "it in a Verifier-Change commit")
    plan.mentions = sorted(set(ctx.grep_files(old_name, roots=("docs", "reverse"))) - edited) + \
        sorted(set(ctx.grep_files(old_word, word=True, roots=("docs",))) - edited
               - set(ctx.grep_files(old_name, roots=("docs",))))
    plan.warnings.append("the byte gate masks DIR32: a consumer the plan missed would still match; "
                         "the link census is the backstop")
    return plan


# ---------------------------------------------------------------- files

def field_spans(text, delimiter=","):
    """(start, end) of each delimited field, quotes included."""
    spans, i, n = [], 0, len(text)
    while True:
        start = i
        if i < n and text[i] == '"':
            i += 1
            while i < n:
                if text[i] == '"':
                    if i + 1 < n and text[i + 1] == '"':
                        i += 2
                        continue
                    i += 1
                    break
                i += 1
        while i < n and text[i] != delimiter:
            i += 1
        spans.append((start, i))
        if i >= n:
            return spans
        i += 1


def repoint_column(raw, label, column, old, new):
    """`raw` with every record whose `column` field is exactly `old` changed
    to `new`; returns (new_raw, count). The header queue's acceptance command
    follows its source; failure evidence and all other bytes are kept."""
    ledger_io.lf_terminator(raw, label)
    if old.encode("utf-8") not in raw:
        return raw, 0
    records = ledger_io.split_records(raw)
    header_queue = label == "reverse/header_queue.tsv"
    delimiter = "\t" if header_queue else ","
    header = next(csv.reader(io.StringIO(records[0][0].decode("utf-8")),
                             delimiter=delimiter), []) if records else []
    if column not in header:
        raise Refusal(f"{label} has no {column!r} column")
    index = header.index(column)
    out, count, needle = [records[0][0] + records[0][1]], 0, old.encode("utf-8")
    for payload, term in records[1:]:
        if needle in payload:
            text = payload.decode("utf-8")
            spans = field_spans(text, delimiter)
            if len(spans) > index:
                start, end = spans[index]
                value = text[start:end]
                if value in (old, f'"{old}"'):
                    edits = [(start, end, value.replace(old, new))]
                    if header_queue and column == "source" and "acceptance" in header:
                        command_index = header.index("acceptance")
                        if command_index < len(spans):
                            a, b = spans[command_index]
                            command = text[a:b]
                            suffix = '"' if command.startswith('"') else ''
                            if command.endswith(" " + old + suffix):
                                edits.append((a, b, command[:len(command) - len(old) - len(suffix)]
                                              + new + suffix))
                    for a, b, replacement in sorted(edits, reverse=True):
                        text = text[:a] + replacement + text[b:]
                    payload = text.encode("utf-8")
                    count += 1
        out.append(payload + term)
    return b"".join(out), count


def path_keyed_lines(ctx, rel, path):
    """1-based lines of `rel` with a tab- or comma-separated field equal to `path`."""
    raw = ctx.read(rel)
    if raw is None or path.encode("utf-8") not in raw:
        return []
    return [number for number, line in enumerate(raw.decode("utf-8", errors="replace").splitlines(), 1)
            if path in re.split(r"[\t,]", line)]


def plan_file(ctx, source, new, basis, evidence, *, max_files=25):
    """Plan `git mv` of one Code/ unit within its directory, with every
    path-keyed ledger column that names it.

    Phase 1 keeps the directory: a move across directories changes the flag
    region's default flags and the TU placement, which are judgements, not
    renames. It refuses a unit any protected, path-keyed register lists
    (flag_overrides.csv is tool-owned, the baselines are shrink-only and
    data_ledger.csv is tool-written): re-keying those is a Verifier-Change
    commit, and a stale key there would silently stop excusing or configuring
    the unit."""
    old = (source or "").replace("\\", "/")
    if not old.startswith("Code/"):
        raise Refusal(f"{old} is not under Code/")
    if is_generated(old):
        raise Refusal(f"{old} is a generated source (never renamed or edited)")
    suffix = posixpath.splitext(old)[1]
    if suffix not in SOURCE_SUFFIXES:
        raise Refusal(f"{old}: phase 1 renames .cpp/.c units only (a header rename rewrites its includers)")
    data = ctx.read(old)
    if data is None:
        raise Refusal(f"{old} does not exist")
    if ctx.git("ls-files", "--", old).strip() != old:
        raise Refusal(f"{old} is not tracked")
    new = (new or "").replace("\\", "/")
    if "/" not in new:
        new = posixpath.join(posixpath.dirname(old), new)
    if not posixpath.splitext(new)[1]:
        new += suffix
    if posixpath.splitext(new)[1] != suffix:
        raise Refusal(f"{new} changes the file type ({suffix})")
    if posixpath.dirname(new) != posixpath.dirname(old):
        raise Refusal("phase 1 renames within one directory: a move changes the region's default "
                      "flags and the TU placement")
    old_stem, new_stem = posixpath.splitext(posixpath.basename(old))[0], \
        posixpath.splitext(posixpath.basename(new))[0]
    if new == old:
        raise Refusal("the new name is the old name")
    check_new_identifier(new_stem, "file", basis)
    taken = [p for p in ctx.git("ls-files", "--", posixpath.dirname(old) + "/").splitlines()
             if p.lower() == new.lower() and p != old]
    if taken or ctx.path(new).exists():
        raise Refusal(f"{new} already exists ({(taken or [new])[0]}); paths are compared case-insensitively")
    rows = [r for r in ctx.rows() if r.get("source") == old]
    if not any(r.get("status") == "matched" for r in rows):
        raise Refusal(f"{old} owns no matched functions.csv row; ./build.sh could not verify the rename")

    for candidate in (old, old_stem):
        recorded = recorded_basis(ctx, candidate)
        if recorded and recorded.startswith("canonical"):
            raise Refusal(f"canonical name: {candidate} is recorded canonical ({recorded}) in {NAME_BASIS}")
    if any(r.get("tu") == old and tu_map.canonical_tu(r) for r in ctx.dicts(TU_MAP)):
        raise Refusal(f"canonical name: {old} is an approved retail TU in {TU_MAP}")
    refuse_vendored(ctx, [old], f"renaming {old}")
    which = check_basis(ctx, "file", basis, evidence, old, old_stem, None, new_name=new, new_word=new_stem,
                        source=old)
    keyed = {rel: lines for rel in PROTECTED_PATH_KEYED if (lines := path_keyed_lines(ctx, rel, old))}
    if keyed:
        detail = "; ".join(f"{rel} line {', '.join(map(str, lines[:3]))}" for rel, lines in keyed.items())
        raise Refusal(f"{old} is keyed in protected path-keyed files ({detail}); "
                      "renaming it needs a Verifier-Change commit")
    text = data.decode("utf-8", errors="surrogateescape")
    if "__FILE__" in name_metric.strip(text):
        raise Refusal(f"{old} expands __FILE__, which spells the path the build passes to cl: "
                      "a rename would change its bytes")
    name = posixpath.basename(old)
    pattern = r"#[[:space:]]*include[[:space:]]*[<\"]([^>\"]*/)?%s[>\"]" % re.escape(name)
    including = [p for p in ctx.git("grep", "-l", "-i", "-E", "-e", pattern, "--", *SEARCH_ROOTS).splitlines()
                 if p]
    if including:
        raise Refusal(f"{old} is #included by {', '.join(including[:3])}; phase 1 does not rewrite includes")

    plan = Plan("file", old, new, basis, evidence.strip(), new, None, old_word=old_stem, new_word=new_stem)
    plan.moves = [(old, new)]
    plan.moved_bytes[old] = data
    for rel, column in PATH_COLUMNS:
        raw = ctx.read(rel)
        if raw is None:
            continue
        new_raw, count = repoint_column(raw, rel, column, old, new)
        if count:
            plan.edit(ctx, rel, new_raw)
            plan.path_rows[rel] = count
    raw = ctx.read(SOURCES_CFG)
    if raw is not None:
        lines = raw.decode("utf-8").splitlines(keepends=True)
        hits = [i for i, line in enumerate(lines) if re.fullmatch(r"INPUT\s*\+=\s*%s\s*" % re.escape(old), line)]
        for i in hits:
            lines[i] = lines[i].replace(old, new)
        if hits:
            plan.edit(ctx, SOURCES_CFG, "".join(lines).encode("utf-8"))
            plan.path_rows[SOURCES_CFG] = len(hits)
    plan.edit(ctx, NAME_BASIS, appended(plan.after.get(NAME_BASIS, ctx.read(NAME_BASIS)), [csv_line(
        ["file", old, new, basis, plan.evidence, new, ""])], header=NAME_BASIS_HEADER))
    plan.verify = [new]
    data_rvas = {data_rva(r) for r in ctx.dicts(DATA_ROWS) if r.get("source") == old}
    plan.claims = sorted({_rva(r.get("target_rva")) for r in rows} | data_rvas - {None}) + \
        [f"file:{old}", f"file:{new}"]
    edited = set(plan.after) | {old}
    plan.mentions = sorted(set(ctx.grep_files(old, roots=("docs", "reverse", "Code", "reference/shims")))
                           - edited)
    plan.mentions += sorted(set(ctx.grep_files(name, roots=("Code", "reference/shims", "docs")))
                            - edited - set(plan.mentions))
    if LINK_STATUS in plan.mentions:
        plan.warnings.append(f"{LINK_STATUS} is census output; the next census re-keys {old}")
    return plan


# ---------------------------------------------------------------- classes

CANONICAL_CLASSES = "reverse/canonical_classes.csv"
CLASS_CONTRACTS = "reverse/class_contracts"
FLAG_OVERRIDES = "reverse/flag_overrides.csv"
# A source split for a token rewrite: whole #include lines first (their paths
# are the file kind's business), then comments and literals as SEGMENT has them.
TOKEN_SEGMENT = re.compile(r"(?m:^[ \t]*#[ \t]*include\b[^\n]*)|" + SEGMENT.pattern, re.S)
INCLUDE_LINE = re.compile(r"[ \t]*#[ \t]*include\b")
ACCESS = re.compile(r"\b(?:public|private|protected)\s*:")
OPTIMIZE = re.compile(r"[-/]O([dx12gs])$")


def type_fragment_re(word):
    """`word` as a type or scope fragment of a mangled symbol (a scope, a
    V/U/T class or W4 enum type, a template name, the class of a special
    member), read by the `fragments` tokenizer: a regex-like object."""
    return ClassToken(word)


class ClassText:
    """`word` as a C++ token in text, and as a type fragment inside every
    mangled name quoted there (comments, markers, linker pragmas,
    __identifier strings); never inside a longer identifier or as a mangled
    name's leading identifier."""

    def __init__(self, word):
        self.word = word
        self.plain = re.compile(r"(?<![A-Za-z0-9_?@$])%s(?![A-Za-z0-9_])" % re.escape(word))

    def subn(self, new, text):
        out, last, count = [], 0, 0
        for match in SYMBOL_TOKEN.finditer(text):
            plain, n = self.plain.subn(new, text[last:match.start()])
            try:
                symbol, m = class_sub(match.group(0), self.word, new)
            except Unparsed as error:
                raise Refusal(f"cannot tokenize a mangled name spelling {self.word}: {error}") from None
            out += [plain, symbol]
            count += n + m
            last = match.end()
        plain, n = self.plain.subn(new, text[last:])
        out.append(plain)
        return "".join(out), count + n

    def sub(self, new, text):
        return self.subn(new, text)[0]

    def search(self, text):
        return self.subn(self.word + "\0", text)[1] > 0


def class_token_re(word):
    return ClassText(word)


def rewrite_tokens(text, token, new_word, *, comments=True, span=None, identifiers=False):
    """Respell every `token` match in code, in comments (when `comments`) and
    in linker-pragma strings, within `span` (start, end) of `text`; with
    `identifiers` (a type token) also inside __identifier("?mangled")
    arguments, which are code references. #include lines are left alone, and
    without `identifiers` so are __identifier arguments (a member, param or
    local is never spelled in a mangled name). Returns (text, counts,
    string_hits, include_hits): any other string literal that spells the
    token is retail-locked text."""
    start, end = span or (0, len(text))
    region = text[start:end]
    out, last = [], 0
    counts = {"code": 0, "comment": 0, "pragma": 0}
    string_hits, include_hits = [], []

    def sub(part, key):
        new, n = token.subn(new_word, part)
        if n or key in counts:
            counts[key] = counts.get(key, 0) + n
        return new

    for match in TOKEN_SEGMENT.finditer(region):
        out.append(sub(region[last:match.start()], "code"))
        seg = match.group(0)
        line_start = region.rfind("\n", 0, match.start()) + 1
        if INCLUDE_LINE.match(seg):
            if token.search(seg):
                include_hits.append(seg.strip())
            out.append(seg)
        elif seg.startswith(("//", "/*")):
            out.append(sub(seg, "comment") if comments else seg)
        elif PRAGMA_LINKER.match(region, line_start):
            out.append(sub(seg, "pragma"))
        elif identifier_string(region, match.start()):
            out.append(sub(seg, "identifier") if identifiers else seg)
        else:
            if token.search(seg):
                string_hits.append(seg)
            out.append(seg)
        last = match.end()
    out.append(sub(region[last:], "code"))
    return text[:start] + "".join(out) + text[end:], counts, string_hits, include_hits


def class_protected(ctx, word):
    """Why the class/struct/enum `word` is canonical, or None: a retail RTTI or
    module class name, recorded canonical, or the scope or type of a retail
    export, a vendored= or .lib row, an evidence-tier name or a converged datum."""
    frag = type_fragment_re(word)
    if word in RTTI_CLASSES:
        return f"{word} is a retail RTTI exception class name"
    if any(row.get("name") == word for row in ctx.dicts(MODULES)):
        return f"{word} is a retail module class name (reverse/module_factory_registrations.csv)"
    basis = recorded_basis(ctx, word)
    if basis and basis.startswith("canonical"):
        return f"{word} is recorded canonical ({basis}) in reverse/name_basis.csv"
    for spelling, row in current_records(ctx).items():
        if not row.get("basis", "").startswith("canonical") or spelling == word:
            continue
        if word in spelling.split("::")[:-1] or ("@" in spelling and frag.search(spelling)):
            return f"{word} scopes {spelling}, recorded canonical ({row.get('basis')}) in reverse/name_basis.csv"
    for row in ctx.dicts(EXPORTS):
        if frag.search(row.get("name", "")):
            return f"{word} names the retail export {row['name']} (reverse/exports.csv)"
    for row in ctx.rows():
        if not frag.search(row.get("name", "")):
            continue
        if "vendored=" in row.get("notes", ""):
            return f"{word} is in the vendored= row {row['name']} (upstream's real identity)"
        if row.get("source", "").lower().endswith(".lib"):
            return f"{word} is in the .lib member {row['name']}"
    for row in ctx.dicts(NAME_TIERS):
        if row.get("name_tier") == "evidence" and frag.search(row.get("name", "")):
            return f"{word} is in the evidence-tier name {row['name']} ({row.get('evidence')})"
    for row in ctx.dicts(CONVERGED):
        if frag.search(row.get("name", "")):
            return f"{word} is in the converged global {row['name']} (reverse/data_converged.csv)"
    return None


def declares_type(code, word):
    """True when stripped `code` defines a class/struct/union/enum body named `word`."""
    return re.search(r"\b(?:class|struct|union|enum)\s+%s\b[^;{()]*\{" % re.escape(word), code) is not None


def leading_identifier(name, word):
    """True when `word` is the identifier (not a scope or type) of symbol `name`."""
    return leading_fragment(name) == word


def include_walk(ctx, paths, limit=2000):
    """Every tracked file under SEARCH_ROOTS that #includes any of `paths`,
    transitively (basename match, case-insensitive: doubt widens the set)."""
    seen, frontier = set(paths), set(paths)
    while frontier:
        names = sorted({Path(p).name for p in frontier})
        frontier = set()
        pattern = r"#[[:space:]]*include[[:space:]]*[<\"]([^>\"]*/)?(%s)[>\"]" % "|".join(
            re.escape(n) for n in names)
        for hit in ctx.git("grep", "-l", "-i", "-E", "-e", pattern, "--", *SEARCH_ROOTS).splitlines():
            if hit and hit not in seen:
                seen.add(hit)
                if not (hit.endswith(SOURCE_SUFFIXES) and hit in ctx.ledger_sources()):
                    frontier.add(hit)
        if len(seen) > limit:
            raise Refusal(f"the touched headers are included by more than {limit} files; "
                          "this tool has no batch mode: pass a larger --max-files (every unit is still verified) or leave the name")
    return seen - set(paths)


def rewrite_ledger(ctx, plan, rel, label, regex, replacement):
    """rewrite_records over one ledger; records the edit when anything changed."""
    raw = ctx.read(rel)
    if raw is None:
        return []
    new_raw, changed = rewrite_records(raw, label, regex, replacement)
    if changed:
        plan.edit(ctx, rel, new_raw)
    return changed


def plan_class(ctx, name, new, basis, evidence, *, max_files=25):
    """Plan respelling one class/struct/union/enum type token everywhere: every
    mangled name it scopes or types (functions.csv names and notes, pins, data
    rows), every source, header and shim view that spells it, and the units
    whose objects reference a renamed symbol. The rewrite is the whole token,
    so it refuses when the word also names a function or datum."""
    old = name or ""
    if not IDENT.fullmatch(old):
        raise Refusal(f"{old!r} is not a type identifier")
    check_new_identifier(new or "", "class", basis)
    if new == old:
        raise Refusal("the new name is the old name")
    reason = class_protected(ctx, old)
    if reason:
        raise Refusal(f"canonical name: {reason}")
    if any(row.get("class") == old for row in ctx.dicts(CANONICAL_CLASSES)) or \
            ctx.path(f"{CLASS_CONTRACTS}/{old}.json").exists():
        raise Refusal(f"{old} is registered in {CANONICAL_CLASSES} / {CLASS_CONTRACTS}; its key, contract "
                      "and class_gate allowances move in a class-reconciliation commit, not here")
    which = check_basis(ctx, "class", basis, evidence, old, old, None, new_name=new, new_word=new)

    frag = type_fragment_re(old)
    token = class_token_re(old)
    names = [r["name"] for r in ctx.rows()] + [p.get("name", "") for p in ctx.pins()] + \
        [d.get("name", "") for d in ctx.dicts(DATA_ROWS)]
    scoped = sorted({n for n in names if n and frag.search(n)})
    # One token, one type: `X::Node` and `Y::Node` would both be respelled.
    enclosing = set()
    for symbol in scoped:
        spans = fragments(symbol)
        starts = {a: symbol[a:b] for a, b in spans}
        for _a, b in class_spans(symbol, old):
            enclosing.add(None if symbol[b + 1:b + 2] == "@" else starts.get(b + 1))
    for other in names:
        if other and leading_identifier(other, old):
            raise Refusal(f"{old} is also the identifier of {other}; a token rewrite would rename it too")
    # Collisions: the new token must be free everywhere a mangled name or a
    # source could spell it.
    taken = ctx.grep_files(new, word=True)
    if taken:
        raise Refusal(f"{new} already appears in {', '.join(taken[:3])}")
    new_frag = type_fragment_re(new)
    clash = next((n for n in names if n and (new_frag.search(n) or leading_identifier(n, new))), None) or \
        shared_identifier(ctx, new, re.compile(r"(?!)"))
    if clash:
        raise Refusal(f"{new} already spells {clash}")
    for rel in ctx.grep_files(old, roots=FROZEN_KEYED):
        if rel == DATA_LEDGER:
            continue
        if frag.search((ctx.read(rel) or b"").decode("utf-8", errors="replace")):
            raise Refusal(f"{old} scopes a key in {rel} (frozen, shrink-only); "
                          "renaming it needs a Verifier-Change commit")

    texts = {}
    for rel in ctx.grep_files(old):
        data = ctx.read(rel)
        if data is None:
            continue
        text = data.decode("utf-8", errors="surrogateescape")
        if token.search(text):
            texts[rel] = text
    declarers = sorted(rel for rel, text in texts.items() if declares_type(name_metric.strip(text), old))
    for text in texts.values():
        enclosing |= {outer for name, _s, _e, outer in enclosing_types(name_metric.strip(text)) if name == old}
    if len(enclosing) > 1:
        raise Refusal(f"{old} names types in {len(enclosing)} different scopes "
                      f"({', '.join(sorted(e or '<global>' for e in enclosing))}); a token rewrite would rename "
                      "them all -- phase 1 renames one type only when its spelling is unique")
    if not scoped and not declarers:
        raise Refusal(f"no class, struct, union or enum named {old} (no definition, no ledger name)")
    by_object = set()
    if ctx.object_scan and scoped:
        import name_dependents
        by_object = object_referencers(ctx, set(scoped))
    touched = set(texts) | by_object
    refuse_vendored(ctx, touched | set(declarers), f"renaming the type {old}")
    generated = sorted(p for p in touched if is_generated(p))
    if generated:
        raise Refusal(f"generated source(s) spell {old}: {', '.join(generated[:5])}; "
                      "the rename would leave them stale and they are never edited")
    if len(touched) > max_files:
        raise Refusal(f"{len(touched)} files spell {old} (over --max-files {max_files})")

    owner = next((d for d in declarers if d in ctx.ledger_sources()), declarers[0] if declarers else "")
    plan = Plan("class", old, new, basis, evidence.strip(), owner, None, old_word=old, new_word=new)

    for before, after in rewrite_ledger(ctx, plan, FUNCTIONS, "functions.csv", frag, new):
        at = _rva(before[2])
        if before[0] != after[0]:
            plan.renamed_rows.append((before[0], after[0], at))
        else:
            plan.notes_rows.append((before[0], at))
    for before, after in rewrite_ledger(ctx, plan, SYMBOLS, "symbols.csv", frag, new):
        plan.renamed_pins.append((before[0], after[0], before[1]))
    for before, _after in rewrite_ledger(ctx, plan, BODY_OWNERS, "body_owners.csv", frag, new):
        plan.owner_rows.append((before[1], _rva(before[0])))
    data_index = {d.get("name"): data_rva(d) for d in ctx.dicts(DATA_ROWS)}
    for before, after in rewrite_ledger(ctx, plan, DATA_ROWS, "data_rows.csv", frag, new):
        if before[0] != after[0]:
            plan.renamed_data.append((before[0], after[0], data_index.get(before[0])))
    tombstoned = _tombstones(ctx)
    lines = [tombstone_line(o, at, f"Renamed to {n} by tools/rename.py ({basis})")
             for o, n, at in plan.renamed_rows + plan.renamed_data
             if at is not None and (o, at) not in tombstoned]
    if lines:
        plan.edit(ctx, DELETED, appended(ctx.read(DELETED), lines, header="name,target_rva,reason"))
    plan.edit(ctx, NAME_BASIS, appended(ctx.read(NAME_BASIS), [csv_line(
        ["class", old, new, basis, plan.evidence, owner, ""])], header=NAME_BASIS_HEADER))

    def carried(spelling):
        if "@" in spelling or spelling.startswith("?"):
            return frag.sub(new, spelling)
        parts = spelling.split("::")
        return "::".join(new if i < len(parts) - 1 and p == old else p for i, p in enumerate(parts))
    carry_records(ctx, plan, carried)
    # A class rename that reverts an earlier one would recreate tombstoned pairs.
    for _o, n, at in plan.renamed_rows:
        if (n, at) in tombstoned:
            raise Refusal(f"({n}, 0x{at:08X}) is tombstoned in deleted_rows.csv: {tombstoned[(n, at)][:120]}")

    headers = []
    for rel in sorted(touched):
        text = texts.get(rel)
        if text is None:
            data = ctx.read(rel)
            text = data.decode("utf-8", errors="surrogateescape") if data is not None else ""
        new_text, counts, strings, includes = rewrite_tokens(text, token, new, identifiers=True)
        if strings:
            raise Refusal(f"{old} is spelled inside a string literal in {rel}: {strings[0][:80]} "
                          "(retail-locked text)")
        for line in includes:
            plan.warnings.append(f"{rel}: {line} names {old} in a path (not renamed; use the file kind)")
        if new_text == text:
            if rel in by_object:
                raise Refusal(f"{rel}'s object references a {old} symbol but its text never spells "
                              f"{old} (a macro or generated name): cannot rewrite it")
            continue
        plan.source_counts[rel] = counts
        plan.edit(ctx, rel, new_text.encode("utf-8", errors="surrogateescape"))
        if not rel.endswith(SOURCE_SUFFIXES) or rel not in ctx.ledger_sources():
            headers.append(rel)
    verify = {rel for rel in plan.source_counts if rel in ctx.ledger_sources()}
    renamed = {o for o, _, _ in plan.renamed_rows}
    verify |= {r["source"] for r in ctx.rows() if r["name"] in renamed}
    verify |= {r["source"] for r in ctx.rows() if (r["name"], _rva(r.get("target_rva"))) in set(plan.notes_rows)}
    renamed_data = {o for o, _, _ in plan.renamed_data}
    verify |= {d.get("source", "") for d in ctx.dicts(DATA_ROWS) if d.get("name") in renamed_data}
    if headers:
        verify |= includers(ctx, headers, max_files)
    plan.verify = sorted(v for v in verify if v and not is_generated(v) and v in ctx.ledger_sources())
    if len(plan.verify) > max_files:
        raise Refusal(f"{len(plan.verify)} sources to verify (over --max-files {max_files})")
    if not plan.verify:
        raise Refusal(f"no ledger source compiles {old}; ./build.sh could not verify the rename")

    prose = len(word_re(old).findall(plan.after.get(FUNCTIONS, b"").decode("utf-8", errors="replace")))
    if prose:
        plan.warnings.append(f"functions.csv notes still spell {old} {prose} time(s) in prose (left as written)")
    plan.claims = sorted({at for _, _, at in plan.renamed_rows if at is not None} |
                         {at for _, at in plan.notes_rows if at is not None}) + [f"class:{old}"]
    if ctx.read(DATA_LEDGER) is not None and \
            frag.search(ctx.read(DATA_LEDGER).decode("utf-8", errors="replace")):
        plan.warnings.append(f"{DATA_LEDGER} (tool-written, protected) still spells {old} symbols; "
                             "tools/data_ledger.py regenerates it in a Verifier-Change commit")
    edited = set(plan.after) | {"reverse/re_attempts.log"}
    plan.mentions = sorted(set(ctx.grep_files(old, word=True, roots=("docs", "reverse"))) - edited)
    stems = sorted(rel for rel in plan.source_counts if old in Path(rel).stem)
    for rel in stems:
        plan.warnings.append(f"{rel}: its file name spells {old} (not renamed; use the file kind)")
    return plan


# ---------------------------------------------------------------- members

def flatten(body):
    """`body` with nested brace blocks collapsed to `;` (name_metric.members' view)."""
    while True:
        flat = re.sub(r"\{[^{}]*\}", ";", body)
        if flat == body:
            return body
        body = flat


def comment_mentions(data, word):
    """True when a comment in `data` (bytes) spells `word`."""
    text = (data or b"").decode("utf-8", errors="replace")
    return any(word_re(word).search(m.group(0)) for m in SEGMENT.finditer(text)
               if m.group(0).startswith(("//", "/*")))


def class_bodies(code, cls):
    """(start, end) of every class/struct/union body named `cls` in stripped `code`."""
    pattern = re.compile(r"\b(?:class|struct|union)\s+%s\b[^;{()]*\{" % re.escape(cls))
    return [(m.end(), name_metric.close(code, m.end() - 1)) for m in pattern.finditer(code)]


def type_bodies(code):
    """(name, start, end) of every class/struct/union body in stripped `code`."""
    pattern = re.compile(r"\b(?:class|struct|union)\s+([A-Za-z_]\w*)\b[^;{()]*\{")
    return [(m.group(1), m.end(), name_metric.close(code, m.end() - 1)) for m in pattern.finditer(code)]


def member_statements(body, word):
    """The declaration statements in one class body that declare data member `word`."""
    flat = ACCESS.sub(";", flatten(body))
    return [stmt for stmt in flat.split(";") if word in name_metric.members(stmt)]


def parameters(params):
    """The names a parameter list declares (`int count` counts, unlike
    name_metric.param_names, which wants two non-keyword words)."""
    for part in params.split(","):
        words = name_metric.WORD.findall(part.split("=")[0])
        if len(words) >= 2 and words[-1] not in name_metric.KEYWORDS:
            yield words[-1]


def prototype_param_spans(code, scope, params, name, skip, new=None):
    """Spans of the parameter `name` in this file's in-class declarations of
    `scope` (Class::method): a declaration with the definition's arity whose
    parameter at the same position is spelled `name`. A parameter list with
    nested parentheses or template commas is left alone (positions would be
    guesses); `skip` (start, end) is the definition itself; a declaration that already
    spells `new` is refused."""
    parts = scope.split("#")[0].split("::")
    if len(parts) < 2 or "(" in params or "<" in params:
        return []
    cls, method = parts[-2], parts[-1]
    mine = [part.split("=")[0] for part in params.split(",")]
    index = [i for i, part in enumerate(mine) if name_metric.WORD.findall(part)[-1:] == [name]]
    if len(index) != 1:
        return []
    spans = []
    for tname, body_start, body_end in type_bodies(code):
        if tname != cls:
            continue
        for match in re.finditer(r"(?<![\w~])%s\s*\(" % re.escape(method), code[body_start:body_end]):
            open_ = body_start + match.end()
            close = code.find(")", open_)
            if close < 0 or close > body_end or skip[0] <= open_ < skip[1]:
                continue
            decl = code[open_:close]
            if "(" in decl or "<" in decl:
                continue
            theirs = decl.split(",")
            if len(theirs) != len(mine):
                continue
            words = name_metric.WORD.findall(theirs[index[0]].split("=")[0])
            if len(words) >= 2 and words[-1] == name:
                if new and word_re(new).search(decl):
                    raise Refusal(f"{new} is already a name in the in-class declaration of {scope}")
                at = open_ + sum(len(t) + 1 for t in theirs[:index[0]])
                spans.append((at, at + len(theirs[index[0]])))
    return spans


def other_declarations(code, word, cls=None, *, member_classes=None):
    """Where stripped `code` declares `word` other than as a member of `cls`.
    `member_classes` restricts named member owners when a scoped rename has
    proven its lookup classes; None retains the conservative all-class scan.
    Globals, parameters and locals are unaffected by that restriction."""
    found = []
    for name, start, end in type_bodies(code):
        if name != cls and (member_classes is None or name in member_classes) and \
                member_statements(code[start:end], word):
            found.append(f"a member of {name}")
    if word in set(name_metric.global_names(code)):
        found.append("a global")
    for scope, start, end, params in name_metric.functions_in(code):
        if word in set(parameters(params)):
            found.append(f"a parameter of {scope}")
        if word in set(name_metric.local_names(code[code.find("{", start):end])):
            found.append(f"a local of {scope}")
    return found


def _define_formals(line):
    """(macro name, formal parameters) of a function-like `#define` line, else None."""
    match = re.match(r"[ \t]*#[ \t]*define[ \t]+([A-Za-z_]\w*)\(([^)]*)\)", line)
    if not match:
        return None
    return match.group(1), [part.strip() for part in match.group(2).split(",")]


def _segment_kind(segment):
    """What a `{` after `segment` (text since the last `;`, `{` or `}`) opens:
    'class:Name' ('class:*' when anonymous), 'enum', 'ns', 'fn' or 'other'.
    A shape it does not know is 'other', which counts as a function body
    only for names used elsewhere; callers treat a class as the dangerous
    reading, so a class it fails to recognise is its blind spot (headers
    with `__declspec` or attributes are stripped first)."""
    text = re.sub(r"__declspec\s*\([^)]*\)|__attribute__\s*\(\([^)]*\)\)", " ", segment).strip()
    if re.search(r"\benum\b[^;{()]*$", text):
        return "enum"
    if re.search(r"\bnamespace\b[^;{()]*$", text) or re.fullmatch(r"(?:extern\s*)?", text):
        return "ns"
    if re.search(r"\)\s*(?:(?:const|volatile)\s*)*(?:throw\s*\([^)]*\)\s*)?$", text):
        return "fn"
    if re.search(r"\b(?:class|struct|union)\b", text):
        names = re.findall(r"\b(?:class|struct|union)\s+([A-Za-z_]\w*)\b", text)
        return "class:" + (names[-1] if names else "*")
    return "fn" if ")" in text else "other"


class UnbalancedScan(Refusal):
    """occurrence_kinds could not balance a text's parentheses and braces, so
    it cannot say what any spelling in it means."""


def occurrence_kinds(code, word, where="the scanned text"):
    """The kind of each place stripped header or source `code` spells `word`
    (occurrence_spots without the offsets)."""
    return [kind for _at, kind in occurrence_spots(code, word, where)]


def occurrence_spots(code, word, where="the scanned text"):
    """One (offset, kind) entry for each place stripped header or source `code`
    spells `word`, by what the spelling can mean to a function elsewhere:

      'macro'    a preprocessor line spells it, unless it is a formal
                 parameter of a function-like `#define` (a formal binds
                 only inside its own macro)
      'ns'       namespace or file scope: a type, variable, function,
                 typedef, enumerator, or a use there
      'class:X'  directly in the body of class X (a member, or a member
                 function defined in the class; 'class:*' when anonymous)
      'param'    in the parameter list of a declaration at namespace or
                 class scope
      'fnbody'   inside a function body, or another braced initializer:
                 a local, or a use whose declaration is elsewhere

    The scan fails closed: a text whose parentheses or braces do not balance
    (an `#if`/`#else` split signature, which the blanked preprocessor lines
    leave with two openers for one closer; a stray closer) would read every
    later spelling as a parameter, or as the wrong scope, and hide class
    members from a caller. It raises UnbalancedScan (a Refusal naming `where`)
    instead of guessing, but only for a text that spells `word`."""
    pattern = word_re(word)
    if not pattern.search(code):
        return []
    out = []

    def blank(match):
        line = match.group(0)
        if pattern.search(line):
            formals = _define_formals(line)
            if not (formals and formals[0] != word and word in formals[1]):
                out.append([match.start(), "macro"])
        return re.sub(r"[^\n]", " ", line)

    code = name_metric.PREPROCESSOR.sub(blank, code)
    stack, parens, segment = [], 0, 0          # stack of [kind, indexes into out of its anonymous members]
    stray = None
    for match in re.finditer(r"[{}();]|\b%s\b" % re.escape(word), code):
        token = match.group(0)
        if token == "(":
            parens += 1
        elif token == ")":
            if not parens:
                stray = stray or "a ')' closes nothing"
            parens = max(0, parens - 1)
        elif token == "{":
            if parens == 0:
                stack.append([_segment_kind(code[segment:match.start()]), []])
                segment = match.end()
        elif token == "}":
            if parens == 0 and not stack:
                stray = stray or "a '}' closes nothing"
            if parens == 0 and stack:
                kind, anonymous = stack.pop()
                segment = match.end()
                if kind == "class:*" and anonymous:
                    # the members of an anonymous aggregate belong to the class it sits in, or
                    # to the typedef name that follows its closing brace
                    outer = stack[-1][0] if stack else "ns"
                    named = re.match(r"\s*(?:const\s+)?\**\s*([A-Za-z_]\w*)", code[match.end():])
                    owner = outer if outer.startswith("class:") else \
                        ("class:" + named.group(1) if named else "class:*")
                    for index in anonymous:
                        out[index][1] = owner
                    if owner == "class:*" and stack:
                        stack[-1][1].extend(anonymous)
        elif token == ";":
            if parens == 0:
                segment = match.end()
        else:
            top = stack[-1][0] if stack else "ns"
            at = match.start()
            if parens and (top == "ns" or top.startswith("class:")):
                out.append([at, "param"])
            elif top in ("fn", "other"):
                out.append([at, "fnbody"])
            elif top == "enum":
                inner = next((k for k, _ in reversed(stack[:-1]) if k.startswith("class:")), None)
                out.append([at, inner or "ns"])
            else:
                out.append([at, top])
                if top == "class:*":
                    stack[-1][1].append(len(out) - 1)
    if parens:
        stray = stray or f"{parens} '(' never closed"
    if stack:
        stray = stray or f"{len(stack)} '{{' never closed"
    if stray:
        raise UnbalancedScan(f"cannot balance the parentheses and braces of {where} ({stray}; an #if/#else "
                             f"split declaration, perhaps), so a spelling of {word} there cannot be classified")
    return [(at, kind) for at, kind in out]


UNPARSED_BASE = "<an unparsed base>"      # never a declared class, so a chain through it is not known

_BASE_PART = re.compile(r"\s*(?:(?:public|protected|private|virtual)\s+)*"
                        r"(?:::\s*)?((?:[A-Za-z_]\w*\s*::\s*)*[A-Za-z_]\w*)\s*(<.*>)?\s*", re.S)


def base_clause_names(clause):
    """The class names a base clause (the text after `:` of a class head)
    derives from, or None when it cannot be read with certainty. It splits on
    top-level commas only and takes each base's name before its `<`; the
    template arguments are balanced but never read, since a template's own
    bases are those of its definition. A dependent base (`typename T::X`,
    `Pair<A>::Inner`), a pack expansion or any bracket that does not balance
    is None, so a caller treats the chain as not known."""
    parts, depth, begin = [], 0, 0
    for at, char in enumerate(clause):
        if char in "<(":
            depth += 1
        elif char in ">)":
            depth -= 1
            if depth < 0:
                return None
        elif char == "," and depth == 0:
            parts.append(clause[begin:at])
            begin = at + 1
    if depth:
        return None
    parts.append(clause[begin:])
    names = []
    for part in parts:
        match = _BASE_PART.fullmatch(part)
        if not match or match.group(1) in ("public", "protected", "private", "virtual", "typename"):
            return None
        if match.group(2):
            inner, level = match.group(2), 0
            for at, char in enumerate(inner):
                level += (char in "<(") - (char in ">)")
                if level == 0 and at < len(inner) - 1:
                    return None             # `<A>::Inner` or a split the group swallowed
            if level:
                return None
        names.append(re.split(r"\s*::\s*", match.group(1))[-1])
    return names


def class_base_map(ctx, rel):
    """{class name: base class names} read from `rel` and the headers it
    includes (every same-named header variant counts). A template
    specialization's head (`class X<0> : public Y`) and every other body of the
    same name add their bases to the one entry, so a chain that runs through a
    specialization is not cut."""
    key = ("_bases", rel)
    if key in ctx._cache:
        return ctx._cache[key]
    bases = {}
    for path in [rel] + sorted(header_closure(ctx, rel)):
        code = name_metric.strip((ctx.read(path) or b"").decode("utf-8", "replace"))
        for match in re.finditer(r"\b(?:class|struct)\s+([A-Za-z_]\w*)\s*(?:<[^{};]*?>\s*)?(?::([^{;]*))?\{", code):
            entry = bases.setdefault(match.group(1), set())
            if match.group(2):
                names = base_clause_names(match.group(2))
                entry.update([UNPARSED_BASE] if names is None else names)
    ctx._cache[key] = bases
    return bases


def class_chain(bases, cls):
    """(`cls` and every base class named in `bases`, whether every one of them
    has a body in `bases`)."""
    seen, todo, known = set(), [cls], True
    while todo:
        name = todo.pop()
        if name in seen:
            continue
        seen.add(name)
        if name not in bases:
            known = False
            continue
        todo.extend(bases[name])
    return seen, known


def class_ancestors(ctx, rel, cls):
    """`cls` and every base class, read from `rel` and the headers it
    includes (every same-named header variant counts); None when `cls` or a
    base is not declared there, so a caller must assume any class."""
    key = ("_ancestors", rel, cls)
    if key in ctx._cache:
        return ctx._cache[key]
    seen, known = class_chain(class_base_map(ctx, rel), cls)
    ctx._cache[key] = seen if known else None
    return ctx._cache[key]


def meant_by_function(ctx, rel, code, word, cls, *, strict, where="the scanned text", member_classes=None):
    """Why a spelling of `word` in `code` (a header, or the unit itself with
    the function blanked out) could be what the function means, or is
    captured by what it declares; None when none can. A macro can always
    bind, and so can a member of the function's class or of a base (an
    initializer list names a member beside the parameter of that name). A
    namespace-scope name or any class's member counts too when `strict`
    (unless `member_classes` restricts named owners for an exact inverse);
    parameters and function bodies elsewhere never do. Raises UnbalancedScan
    (a Refusal naming `where`) when the text's brackets do not balance."""
    for kind in occurrence_kinds(code, word, where):
        if kind == "macro":
            return "a macro"
        if kind == "ns" and strict:
            return "a name at file scope"
        if kind.startswith("class:"):
            if strict and member_classes is not None and kind != "class:*" and kind[6:] not in member_classes:
                continue
            if strict or kind == "class:*":
                return f"a member of {kind[6:]}" if kind != "class:*" else "a member of an anonymous type"
            if cls is not None:
                ancestors = class_ancestors(ctx, rel, cls)
                if ancestors is None or kind[6:] in ancestors:
                    return f"a member of {kind[6:]}"
    return None


def plan_member(ctx, cls, member, new, basis, evidence, *, max_files=25):
    """Plan respelling one non-static data member of `cls` in every view that
    declares it and every file that uses it through those views. Member names
    never reach bytes (offsets do), so no ledger row changes; the build still
    verifies every unit that compiles a touched file."""
    for word in (cls, member):
        if not IDENT.fullmatch(word or ""):
            raise Refusal(f"{word!r} is not an identifier")
    check_new_identifier(new or "", "member", basis)
    if new == member:
        raise Refusal("the new name is the old name")
    old_q, new_q = f"{cls}::{member}", f"{cls}::{new}"
    reason = is_protected(ctx, "member", old_q, identifier=member)
    if reason:
        raise Refusal(f"canonical name: {reason}")
    which = check_basis(ctx, "member", basis, evidence, old_q, member, None, new_name=new_q, new_word=new)

    views, texts = [], {}
    for rel in sorted(set(ctx.grep_files(cls, word=True)) & set(ctx.grep_files(member, word=True))):
        text = ctx.read(rel).decode("utf-8", errors="surrogateescape")
        code = name_metric.strip(text)
        statements = [s for start, end in class_bodies(code, cls)
                      for s in member_statements(code[start:end], member)]
        if not statements:
            continue
        if any(re.search(r"\bstatic\b", s) for s in statements):
            raise Refusal(f"{old_q} is a static data member in {rel}; rename it with the global kind")
        views.append(rel)
        texts[rel] = text
    if not views:
        raise Refusal(f"no view of {cls} declares a data member {member}")
    headers = [v for v in views if not (v.endswith(SOURCE_SUFFIXES) and v in ctx.ledger_sources())]
    users = include_walk(ctx, headers) if headers else set()
    users = {rel for rel in users
             if code_mentions(ctx.read(rel).decode("utf-8", errors="surrogateescape"), member)}
    touched = set(views) | users
    refuse_vendored(ctx, touched, f"renaming {old_q}")
    generated = sorted(p for p in touched if is_generated(p))
    if generated:
        raise Refusal(f"generated source(s) use {old_q}: {', '.join(generated[:5])} (never edited)")
    if len(touched) > max_files:
        raise Refusal(f"{len(touched)} files use {old_q} (over --max-files {max_files})")

    plan = Plan("member", old_q, new_q, basis, evidence.strip(), views[0], None, old_word=member, new_word=new)
    token = word_re(member)
    edited_headers = []
    for rel in sorted(touched):
        text = texts.get(rel) or ctx.read(rel).decode("utf-8", errors="surrogateescape")
        code = name_metric.strip(text)
        elsewhere = other_declarations(code, member, cls)
        if elsewhere:
            raise Refusal(f"{rel} also declares {member} as {elsewhere[0]}; a word rewrite there is ambiguous")
        if code_mentions(text, new):
            raise Refusal(f"{new} is already a name in {rel}")
        new_text, counts, strings, _includes = rewrite_tokens(text, token, new, comments=False)
        if strings:
            raise Refusal(f"{member} is spelled inside a string literal in {rel}: {strings[0][:80]}")
        if new_text == text:
            continue
        plan.source_counts[rel] = counts
        plan.edit(ctx, rel, new_text.encode("utf-8", errors="surrogateescape"))
        if not (rel.endswith(SOURCE_SUFFIXES) and rel in ctx.ledger_sources()):
            edited_headers.append(rel)
    verify = {rel for rel in plan.source_counts if rel in ctx.ledger_sources()}
    if edited_headers:
        verify |= includers(ctx, edited_headers, max_files)
    plan.verify = sorted(v for v in verify if not is_generated(v))
    if not plan.verify:
        raise Refusal(f"no ledger source compiles a view of {cls}; ./build.sh could not verify the rename")
    if len(plan.verify) > max_files:
        raise Refusal(f"{len(plan.verify)} sources to verify (over --max-files {max_files})")
    for rel in sorted(rel for rel in plan.source_counts if comment_mentions(ctx.read(rel), member)):
        plan.warnings.append(f"{rel}: comments still mention {member} (left as written)")
    plan.edit(ctx, NAME_BASIS, appended(ctx.read(NAME_BASIS), [csv_line(
        ["member", old_q, new_q, basis, plan.evidence, views[0], ""])], header=NAME_BASIS_HEADER))
    plan.claims = [f"class:{cls}"]
    plan.mentions = sorted(set(ctx.grep_files(old_q, roots=("docs", "reverse"))) - set(plan.after))
    return plan


# ---------------------------------------------------------------- params and locals

def scope_of(mangled):
    """`Class::method` for a plain mangled function name, `Class::Class` /
    `Class::~Class` for a constructor/destructor, the bare name for a C
    symbol; None for anything else (operators, templates, labels)."""
    match = re.match(r"\?\?([01])((?:[A-Za-z_]\w*@)+)@", mangled)
    if match:
        parts = match.group(2).rstrip("@").split("@")
        cls = parts[0]
        return "::".join(reversed(parts)) + "::" + ("~" if match.group(1) == "1" else "") + cls
    match = re.match(r"\?([A-Za-z_]\w*)@((?:[A-Za-z_]\w*@)*)@", mangled)
    if match:
        parts = [match.group(1)] + [p for p in match.group(2).split("@") if p]
        return "::".join(reversed(parts))
    match = re.fullmatch(r"[_@]?([A-Za-z_]\w*?)(?:@\d+)?", mangled)
    return match.group(1) if match else None


def compile_flags(ctx, rel):
    """The flags build.py compiles `rel` with ('-' style), last one winning:
    build.compiler_command's base `-O2`, then on the real tree
    build.source_extra_flags (the `// cl:` line, flag_overrides.csv and the
    region default); elsewhere the `// cl:` line then any flag_overrides.csv row."""
    if ctx.root == ROOT.resolve():
        import build
        return ["-O2"] + [f.replace("/", "-", 1) if f.startswith("/") else f
                          for f in build.source_extra_flags(ROOT / rel)]
    flags = ["-O2"]
    data = ctx.read(rel) or b""
    for line in data.decode("utf-8-sig", errors="replace").splitlines():
        if line.startswith("// cl:"):
            flags += line[len("// cl:"):].split()
            break
    for row in ctx.dicts(FLAG_OVERRIDES):
        if row.get("source") == rel:
            flags += (row.get("flags") or "").split()
    return [f.replace("/", "-", 1) if f.startswith("/") else f for f in flags]


def optimized(flags):
    """False when the effective (last) optimisation level is /Od, or none is given
    (cl's own default)."""
    levels = [m.group(1) for m in (OPTIMIZE.match(f) for f in flags) if m]
    return bool(levels) and levels[-1] != "d"


def _git_bytes(root, *args):
    """stdout of a read-only git command in `root`, or None when it fails or
    times out. A caller treats None as no evidence (fail closed)."""
    try:
        result = subprocess.run(["git", "--no-replace-objects", "-C", str(root), *args], capture_output=True,
                                timeout=GIT_TIMEOUT)
    except (OSError, subprocess.TimeoutExpired):
        return None
    return result.stdout if result.returncode == 0 else None


def _git_path(text):
    return text.decode("utf-8", "surrogateescape")


def _tree_entry(root, revision, rel):
    """(mode, type, sha) of the one tree entry at exactly `rel`, or None."""
    out = _git_bytes(root, "--literal-pathspecs", "ls-tree", "-z", revision, "--", rel)
    if out is None:
        return None
    entries = [entry for entry in out.split(b"\0") if entry]
    if len(entries) != 1:
        return None
    meta, sep, path = entries[0].partition(b"\t")
    fields = meta.split()
    if not sep or _git_path(path) != rel or len(fields) != 3:
        return None
    return tuple(_git_path(field) for field in fields)


def _index_entry(root, rel):
    """(mode, sha) of the one stage-0 index entry at exactly `rel`, or None."""
    out = _git_bytes(root, "--literal-pathspecs", "ls-files", "-s", "-z", "--", rel)
    if out is None:
        return None
    entries = [entry for entry in out.split(b"\0") if entry]
    if len(entries) != 1:
        return None
    meta, sep, path = entries[0].partition(b"\t")
    fields = meta.split()
    if not sep or _git_path(path) != rel or len(fields) != 3 or fields[2] != b"0":
        return None
    return _git_path(fields[0]), _git_path(fields[1])


def donor_pin(ctx):
    """The commit both HEAD and the index record for DONOR_GITLINK, or None.
    A missing entry, a mode that is not a gitlink, an unmerged index or two
    different pins is no evidence, so no donor header is trusted."""
    key = "_donor_pin"
    if key in ctx._cache:
        return ctx._cache[key]
    ctx._cache[key] = None
    head = _tree_entry(ctx.root, "HEAD", DONOR_GITLINK)
    index = _index_entry(ctx.root, DONOR_GITLINK)
    if head is None or index is None:
        return None
    mode, kind, sha = head
    index_mode, index_sha = index
    if mode != "160000" or kind != "commit" or index_mode != "160000":
        return None
    if sha != index_sha or not re.fullmatch(r"(?:[0-9a-f]{40}|[0-9a-f]{64})", sha):
        return None
    ctx._cache[key] = sha
    return sha


def _safe_component_path(root, rel):
    """`root/rel` when every component is a real directory or the final real
    file, with no symlink anywhere and nothing resolving outside `root`;
    otherwise None."""
    base = Path(root)
    top = base.resolve()
    current = base
    for part in rel.split("/"):
        if part in ("", "."):
            continue
        if part == "..":
            return None
        current = current / part
        if current.is_symlink():
            return None
    try:
        current.resolve().relative_to(top)
    except (OSError, ValueError):
        return None
    return current


def _pinned_donor_checkout(ctx):
    """The donor submodule path when its checkout is exactly the HEAD/index pin
    and has no tracked modifications; otherwise None."""
    key = "_donor_checkout"
    if key in ctx._cache:
        return ctx._cache[key]
    ctx._cache[key] = None
    pin = donor_pin(ctx)
    if pin is None:
        return None
    sub = _safe_component_path(ctx.root, DONOR_GITLINK)
    if sub is None or sub.is_symlink() or not sub.is_dir():
        return None
    head = _git_bytes(sub, "rev-parse", "--verify", "HEAD^{commit}")
    if head is None or _git_path(head).strip() != pin:
        return None
    status = _git_bytes(sub, "status", "--porcelain", "--untracked-files=no",
                        "--ignore-submodules=none")
    if status is None or status.strip():
        return None
    ctx._cache[key] = sub
    return sub


def trusted_donor_header(ctx, includer, include):
    """The repository path of an explicitly quoted `include` written by
    `includer` when it resolves, relative to that actual includer, to a
    committed regular file inside DONOR_GITLINK at the pinned commit, with an
    unchanged worktree. None for a mismatched or uncommitted pin, a dirty
    checkout, an untracked substitution, a symlink escape or a relative
    include that leaves the donor (no nested cross-repository recursion)."""
    if not include or "\0" in include or "\\" in include or include.startswith("/"):
        return None
    target = posixpath.normpath(posixpath.join(posixpath.dirname(includer), include))
    if not target.startswith(DONOR_GITLINK + "/"):
        return None
    sub = _pinned_donor_checkout(ctx)
    if sub is None:
        return None
    header_rel = target[len(DONOR_GITLINK) + 1:]
    if not header_rel or header_rel.startswith("../") or "/../" in header_rel:
        return None
    work = _safe_component_path(sub, header_rel)
    if work is None or work.is_symlink() or not work.is_file():
        return None
    entry = _tree_entry(sub, donor_pin(ctx), header_rel)
    if entry is None:
        return None
    mode, kind, sha = entry
    if mode not in ("100644", "100755") or kind != "blob":
        return None
    blob = _git_bytes(sub, "cat-file", "blob", sha)
    if blob is None:
        return None
    try:
        if work.read_bytes() != blob:
            return None
    except OSError:
        return None
    return target


def header_closure(ctx, rel, limit=400):
    """Tracked headers under SEARCH_ROOTS that `rel` #includes, transitively,
    resolved by basename (case-insensitive; doubt widens the set). An
    explicitly quoted include written by `rel` itself, or by a donor header it
    reached, is also resolved relative to that actual includer when it is a
    committed header in the pinned BFME1 gitlink."""
    if "_by_base" not in ctx._cache:
        index = {}
        for path in ctx.git("ls-files", "--", *SEARCH_ROOTS).splitlines():
            index.setdefault(Path(path).name.lower(), []).append(path)
        ctx._cache["_by_base"] = index
    index = ctx._cache["_by_base"]
    seen, frontier = set(), [rel]
    while frontier and len(seen) < limit:
        current = frontier.pop()
        data = ctx.read(current) or b""
        text = data.decode("utf-8", "replace")
        for delimiter, name in re.findall(r'^[ \t]*#[ \t]*include[ \t]*([<"])([^>"]+)[>"]', text, re.M):
            for path in index.get(Path(name).name.lower(), []):
                if path not in seen and path != rel:
                    seen.add(path)
                    frontier.append(path)
            if delimiter == '"' and (current == rel or current.startswith(DONOR_GITLINK + "/")):
                path = trusted_donor_header(ctx, current, name)
                if path is not None and path not in seen and path != rel:
                    seen.add(path)
                    frontier.append(path)
    return seen


def pick_function(code, function):
    """The name_metric.functions_in entry `function` names: its exact scope
    (`Class::method`, `Class::method#2` for the second overload in the file),
    or a bare method name when one function in the file has it."""
    found = name_metric.functions_in(code)
    # functions_in leaves the first overload unsuffixed; #1 makes that
    # choice explicit without making a bare overloaded scope unambiguous.
    if function.endswith("#1"):
        first = [f for f in found if f[0] == function[:-2]]
        if first:
            return first[0]
    exact = [f for f in found if f[0] == function]
    same = [f for f in found if f[0].split("#")[0] == function.split("#")[0]]
    if exact and ("#" in function or len(same) == 1):
        return exact[0]
    loose = [f for f in found if f[0].split("#")[0] == function
             or f[0].split("#")[0].split("::")[-1] == function]
    if len(loose) == 1:
        return loose[0]
    if not loose:
        raise Refusal(f"no function {function} defined in the file")
    raise Refusal(f"{function} is ambiguous here: {', '.join(f[0] for f in loose)}")


# What name_metric.local_names does not read as a declaration: `return x;` and kin.
NOT_A_DECLARATION = frozenset({"return", "delete", "goto", "throw", "case", "new", "else", "do", "typedef",
                               "using", "sizeof"})
SCOPING_HEADS = re.compile(r"\b(?:for|while|if|switch|catch)\s*$")


def _bracket_pairs(text, opener, closer):
    """(open, close) offsets of every balanced pair; a pair never closed ends
    at the end of the text."""
    pairs, stack = [], []
    for match in re.finditer(re.escape(opener) + "|" + re.escape(closer), text):
        if match.group(0) == opener:
            stack.append(match.start())
        elif stack:
            pairs.append((stack.pop(), match.start()))
    pairs.extend((begin, len(text)) for begin in stack)
    return pairs


def local_scopes(body, name):
    """(start, end) of the region each declaration of the local `name` in
    function `body` (stripped text starting at its `{`) governs: from the
    declared name to the end of the block that holds it. A declaration in the
    header of a `for`/`while`/`if`/`switch`/`catch` governs that statement
    only (its braced body, else up to the next `;`); one in any other
    parenthesis is no declaration (`f(w * a)` reads as `type name`, and a
    `type name` spelling in a call's argument list is never a declaration), nor
    is `if (w & a)` (a condition declares only with an initializer) or a `for`'s
    later clause. Narrow errors refuse more, wide ones would let a rename
    through, so an unrecognised shape takes the narrower reading."""
    braces = _bracket_pairs(body, "{", "}")
    parens = _bracket_pairs(body, "(", ")")
    scopes = []
    for match in name_metric.LOCAL.finditer(body):
        if match.group(2) != name or match.group(1) in NOT_A_DECLARATION or match.group(2) in name_metric.KEYWORDS:
            continue
        at = match.start(2)
        block = max((p for p in braces if p[0] < at < p[1]), default=(0, len(body)))
        paren = max((p for p in parens if p[0] < at < p[1]), default=None)
        end = block[1]
        if paren is not None and paren[0] > block[0]:
            end = paren[1]
            head = SCOPING_HEADS.search(body[:paren[0]])
            # `f(w * a)` and `if (w & a)` read as `type name`; a declaration inside a
            # parenthesis is only a statement's own: a condition's carries an initializer
            # (`if (T *a = f())`), a loop's is its first clause, a handler's is its parameter
            if not head or body[match.start()] != "(":
                continue
            word = head.group(0).split()[0]
            tail = body[match.end(2):].lstrip()
            if word in ("if", "while", "switch") and not re.match(r"=(?!=)", tail) or \
                    word == "for" and tail.startswith(")"):
                continue
            after = re.compile(r"\s*").match(body, paren[1] + 1).end()
            if body.startswith("{", after):
                end = next(close for begin, close in braces if begin == after)
            else:
                stop = body.find(";", after)
                end = len(body) if stop < 0 else stop
        scopes.append((at, end))
    return scopes


def local_use_outside_scope(body, name):
    """Offset in `body` of the first spelling of `name` that no declaration of
    that local reaches (before its declaration, after its block closed, or in
    a sibling block), where a global or a header's declaration may be what the
    function means; None when each spelling is inside some declaration's scope."""
    scopes = local_scopes(body, name)
    for use in word_re(name).finditer(body):
        if not any(begin <= use.start() <= end for begin, end in scopes):
            return use.start()
    return None


def scalar_local_binding(body, name):
    """A unique ordinary scalar declaration's lexical span, or no proof.

    Deliberately excludes control initializers, arrays, local types, lambdas
    and directives. Those need a fuller C++ parser; a byte match cannot prove
    that a replacement selected the intended binding.
    """
    if re.search(r"#|\b(?:class|struct|union|enum|typedef|using|__asm|asm|goto)\b|\[[^]]*\]\s*(?:\([^)]*\)[^;{}]*)?\{", body):
        return None
    scopes = local_scopes(body, name)
    if len(scopes) != 1:
        return None
    begin, end = scopes[0]
    candidates = [m for m in name_metric.LOCAL.finditer(body)
                  if m.group(2) == name and m.group(1) not in NOT_A_DECLARATION]
    if len(candidates) != 1 or re.search(rf"\b{re.escape(name)}\s*:(?!:)", body):
        return None
    decl = next((m for m in name_metric.LOCAL.finditer(body) if m.start(2) == begin), None)
    if decl is None or decl.group(1) not in {"int", "float", "double", "char", "short", "long", "bool", "wchar_t"}:
        return None
    if not re.match(r"\s*(?:=(?!=)|;)", body[decl.end(2):]):
        return None
    blocks = _bracket_pairs(body, "{", "}")
    block = max((pair for pair in blocks if pair[0] < begin < pair[1]), default=None)
    if block is None or block[1] >= len(body):
        return None
    if any(block[0] < a < begin < b for a, b in _bracket_pairs(body, "(", ")")):
        return None
    # A matched declaration in a balanced ordinary block is the only binding
    # of this spelling in the function. Scope starts at its identifier, so
    # `int x = x` refers to the new local in its own initializer.
    return begin, end + 1


def scope_changing_macro(ctx, rel, body):
    """An invoked macro whose possible expansion changes lexical braces.

    Include aliases transitively and retain every conditional definition.
    The proof is conservative: even a balanced do/while macro is declined.
    """
    definitions = collections.defaultdict(list)
    for path in [rel] + sorted(header_closure(ctx, rel)):
        text = name_metric.strip((ctx.read(path) or b"").decode("utf-8", "replace"))
        for directive in name_metric.PREPROCESSOR.finditer(text):
            match = re.match(r"[ \t]*#[ \t]*define[ \t]+([A-Za-z_]\w*)(.*)", directive.group(), re.S)
            if match:
                definitions[match.group(1)].append(match.group(2))
    changing = {name for name, values in definitions.items() if any("{" in v or "}" in v for v in values)}
    while True:
        expanded = changing | {name for name, values in definitions.items()
                               if any(set(name_metric.WORD.findall(value)) & changing for value in values)}
        if expanded == changing:
            break
        changing = expanded
    return next((name for name in sorted(changing) if word_re(name).search(body)), None)


def outer_binding_digest(ctx, rel, code, start, end):
    """Fingerprint the context the scalar proof was permitted to shadow.

    Omit the selected function so other local/parameter names in the same
    batch do not invalidate the proof. Keep the rest of the source and full
    header snapshots: changed outer declarations require a fresh review.
    """
    headers = [(path, hashlib.sha256(ctx.read(path) or b"").hexdigest())
               for path in sorted(header_closure(ctx, rel))]
    payload = json.dumps([rel, code[:start] + code[end:], headers], ensure_ascii=True)
    return hashlib.sha256(payload.encode("utf-8")).hexdigest()


def recorded_local_binding(ctx, evidence, rel, code, start, end):
    """Only the exact recorded landing may reuse an unchanged outer context."""
    record = revert_id(evidence)
    if not record:
        return False
    land = landing(ctx, record)
    if land.kind != "local" or land.source != rel:
        return False
    current = outer_binding_digest(ctx, rel, code, start, end)
    return any(row.get("record") == f"agree:{record}" and row.get("source") == rel
               and row.get("old") == land.target and row.get("new") == land.current
               and row.get("outer_sha256") == current for row in ctx.dicts(NAME_BINDINGS))


def plan_scoped(kind, ctx, source, name, new, basis, evidence, *, function=None, rva=None, max_files=25, local_binding=False):
    """Plan respelling one parameter or local inside one function body. Names
    of params and locals never reach bytes under optimisation; a local under
    /Od can (frame order), so /Od files are refused for locals. The rename is
    confined to the function's text, so it refuses whenever the old word
    could mean something else there or the new word could capture a use."""
    rel = (source or "").replace("\\", "/")
    if is_generated(rel):
        raise Refusal(f"{rel} is a generated source (never edit Code/gen_*)")
    if rel not in ctx.ledger_sources():
        raise Refusal(f"{rel} owns no matched function row; ./build.sh could not verify the rename")
    for word in (name, new):
        if not IDENT.fullmatch(word or ""):
            raise Refusal(f"{word!r} is not an identifier")
    check_new_identifier(new, kind, basis)
    if new == name:
        raise Refusal("the new name is the old name")
    if function is None and rva is not None:
        scopes = {scope_of(r["name"]) for r in ctx.rows()
                  if r.get("source") == rel and _rva(r.get("target_rva")) == rva}
        scopes.discard(None)
        if len(scopes) != 1:
            raise Refusal(f"0x{rva:08X} does not name exactly one plain function in {rel}; pass --function")
        function = scopes.pop()
        overloads = [f[0] for f in name_metric.functions_in(name_metric.strip(
            ctx.read(rel).decode("utf-8", errors="surrogateescape"))) if f[0].split("#")[0] == function]
        if len(overloads) > 1:
            raise Refusal(f"{rel} defines {len(overloads)} overloads of {function} ({', '.join(overloads)}); "
                          f"0x{rva:08X} is one of them -- pass --function {function}#N for the right one "
                          "(a parameter name never reaches the bytes, so the build cannot catch a wrong pick)")
    if not function:
        raise Refusal("--function (or --rva) is required")
    text = ctx.read(rel).decode("utf-8", errors="surrogateescape")
    code = name_metric.strip(text)
    scope, start, end, params = pick_function(code, function)
    brace = code.find("{", start)
    body = code[brace:end]
    binding = scalar_local_binding(body, name) if kind == "local" and (local_binding or basis == RESTORED) else None
    if binding and basis == RESTORED and not recorded_local_binding(ctx, evidence, rel, code, start, end):
        binding = None
    rewrite_span = (brace + binding[0], brace + binding[1]) if binding else (start, end)
    if binding:
        macro = scope_changing_macro(ctx, rel, body)
        if macro or any("{" in flag or "}" in flag for flag in compile_flags(ctx, rel)):
            raise Refusal(f"{scope} uses a scope-changing macro ({macro or 'compile flags'}); local binding needs expanded C++")
    if kind == "param":
        if name not in set(parameters(params)):
            raise Refusal(f"{name} is not a parameter of {scope}")
    else:
        if name in set(parameters(params)):
            raise Refusal(f"{name} is a parameter of {scope}, not a local")
        if name not in set(name_metric.local_names(body)):
            raise Refusal(f"{name} is not a local of {scope}")
        flags = compile_flags(ctx, rel)
        if re.search(r'^[ \t]*#[ \t]*pragma[ \t]+optimize[ \t]*\([^)]*\boff\b', text, re.M):
            raise Refusal(f"{rel} turns optimisation off with #pragma optimize; a local's name can reorder "
                          "that /Od frame")
        if not optimized(flags):
            raise Refusal(f"{rel} compiles without optimisation ({' '.join(flags) or 'no /O flag'}); "
                          "renaming a local can reorder the /Od frame")
        first_use = word_re(name).search(body)
        first_decl = min((m.start(2) for m in name_metric.LOCAL.finditer(body) if m.group(2) == name),
                         default=None)
        if not binding and first_use and first_decl is not None and first_use.start() < first_decl:
            raise Refusal(f"{name} is used in {scope} before its declaration (it names something outer there)")
        stray = local_use_outside_scope(body, name)
        if stray is not None and not binding:
            raise Refusal(f"{name} is used in {scope} at line {code.count(chr(10), 0, brace + stray) + 1}, outside "
                          "the block that declares it (a global or an outer declaration may be what is meant)")
    record_scope = function if function.endswith("#1") else scope
    # Keep an old landing's exact inverse when a caller supplies the
    # selector its historical record omitted. Never discard a new record's.
    if basis == RESTORED and revert_id(evidence):
        land = landing(ctx, revert_id(evidence))
        if "#" not in land.current.rsplit("::", 1)[0]:
            record_scope = scope.split("#")[0]
    old_q, new_q = f"{record_scope}::{name}", f"{record_scope}::{new}"
    legacy_q = f"{scope.split('#')[0]}::{name}"
    reason = (is_protected(ctx, kind, old_q, identifier=name)
              or is_protected(ctx, kind, legacy_q, identifier=name))
    if reason:
        raise Refusal(f"canonical name: {reason}")
    refuse_vendored(ctx, [rel], f"renaming {old_q}")
    which = check_basis(ctx, kind, basis, evidence, old_q, name, rva, new_name=new_q, new_word=new)
    region = code[start:end]
    if re.search(r"(?:->|\.|::)\s*%s\b" % re.escape(name), code[rewrite_span[0]:rewrite_span[1]]):
        raise Refusal(f"{scope} spells {name} after ->, . or ::; it also names a member there")
    # The new name may not be spelled in the function (a use would be captured)
    # nor at file scope, as a member or in a macro: the same spelling as a
    # parameter or local of ANOTHER function is no collision.
    parts = scope.split("#")[0].split("::")
    types = enclosing_types(code)
    inside = [n for n, begin, finish, _outer in types if begin <= start < finish]
    owner_class = parts[-2] if len(parts) > 1 else (inside[-1] if inside else None)
    # A field of an unrelated named type cannot be the parameter/local's
    # meaning. Reuse the header scan's complete base-chain proof, but keep
    # nested owners conservative: their enclosing classes also affect lookup.
    member_classes = class_ancestors(ctx, rel, owner_class) if owner_class else set()
    if member_classes:
        for path in [rel] + sorted(header_closure(ctx, rel)):
            declared_types = types if path == rel else enclosing_types(name_metric.strip(
                (ctx.read(path) or b"").decode("utf-8", errors="replace")))
            if any(n in member_classes and outer for n, _b, _e, outer in declared_types):
                member_classes = None
                break
    restoring_binding = bool(binding and basis == RESTORED)
    capture_region = code[rewrite_span[0]:rewrite_span[1]] if restoring_binding else region
    if word_re(new).search(capture_region):
        raise Refusal(f"{new} is already a name in {scope} ({rel})")
    outside = code[:start] + " " * (end - start) + code[end:]
    # check_basis already proved a RESTORED plan is the recorded exact inverse.
    # Its original word can coexist with the unrelated member that did not
    # block the landing; ordinary new names retain the all-member screen.
    clash = meant_by_function(ctx, rel, outside, new, owner_class, strict=True, where=rel,
                              member_classes=member_classes if basis == RESTORED else None)
    if restoring_binding and "macro" in occurrence_kinds(outside, new, rel):
        raise Refusal(f"{new} is spelled in a macro in {rel}")
    if clash and not restoring_binding:
        raise Refusal(f"{new} is already a name in {rel} ({clash})")
    elsewhere = [d for d in other_declarations(outside, name, member_classes=member_classes)
                 if not d.startswith(("a parameter", "a local"))]
    if elsewhere and not binding:
        raise Refusal(f"{name} is also {elsewhere[0]} in {rel}; the function may mean it")
    if "macro" in occurrence_kinds(outside, name, rel):
        raise Refusal(f"{name} is also spelled in a macro in {rel}; the function may mean it")
    # An included header spelling either name decides only through a macro or a
    # member of the function's class or a base (an initializer list names a
    # member beside the parameter of that name): a parameter or local of some
    # other function there, or a file-scope name, is not what this function
    # declares.
    for header in sorted(header_closure(ctx, rel)):
        data = ctx.read(header)
        if data is None:
            continue
        header_code = name_metric.strip(data.decode("utf-8", errors="replace"))
        for word, what in ((name, "the function may mean it"), (new, "it would capture or shadow it")):
            if binding and (word == name or restoring_binding):
                if "macro" in occurrence_kinds(header_code, word, header):
                    raise Refusal(f"{word} is spelled in a macro in included header {header}")
                continue
            clash = meant_by_function(ctx, rel, header_code, word, owner_class, strict=False,
                                      where=f"included header {header}")
            if clash:
                raise Refusal(f"{word} is also spelled in included header {header} ({clash}); {what}")

    new_text, counts, strings, _ = rewrite_tokens(text, word_re(name), new, span=rewrite_span)
    if strings:
        raise Refusal(f"{name} is spelled inside a string literal in {scope}: {strings[0][:80]}")
    if new_text == text:
        raise Refusal(f"{name} does not occur in {scope}'s text")
    if kind == "param":
        # the in-class prototype names the parameter too; leaving it on the
        # old word makes the declaration and the definition disagree
        protos = prototype_param_spans(code, scope, params, name, (start, end), new)
        new_text = text
        for span in sorted(protos + [(start, end)], reverse=True):
            new_text, part, _strings, _ = rewrite_tokens(new_text, word_re(name), new, span=span)
            if span != (start, end):
                counts = {k: counts.get(k, 0) + part.get(k, 0) for k in set(counts) | set(part)}
    if rva is None:
        rvas = {_rva(r.get("target_rva")) for r in ctx.rows()
                if r.get("source") == rel and scope_of(r["name"]) == scope.split("#")[0]}
        rva = rvas.pop() if len(rvas) == 1 and "#" not in scope else None
    plan = Plan(kind, old_q, new_q, basis, evidence.strip(), rel, rva, old_word=name, new_word=new)
    plan.source_counts[rel] = counts
    plan.edit(ctx, rel, new_text.encode("utf-8", errors="surrogateescape"))
    plan.edit(ctx, NAME_BASIS, appended(ctx.read(NAME_BASIS), [csv_line(
        [kind, old_q, new_q, basis, plan.evidence, rel, f"0x{rva:08X}" if rva is not None else ""])],
        header=NAME_BASIS_HEADER))
    if binding and basis == "inferred":
        plan.edit(ctx, NAME_BINDINGS, appended(ctx.read(NAME_BINDINGS), [csv_line(
            [plan.evidence, old_q, new_q, rel, outer_binding_digest(ctx, rel, code, start, end)])],
            header=NAME_BINDINGS_HEADER))
    plan.verify = [rel]
    plan.claims = ([rva] if rva is not None else []) + [f"file:{rel}"]
    return plan


def plan_param(ctx, source, name, new, basis, evidence, *, function=None, rva=None, max_files=25):
    return plan_scoped("param", ctx, source, name, new, basis, evidence,
                       function=function, rva=rva, max_files=max_files)


def plan_local(ctx, source, name, new, basis, evidence, *, function=None, rva=None, max_files=25, local_binding=False):
    return plan_scoped("local", ctx, source, name, new, basis, evidence,
                       function=function, rva=rva, max_files=max_files, local_binding=local_binding)


def _rva(text):
    try:
        return int(text, 16)
    except (TypeError, ValueError):
        return None


def _tombstones(ctx, honour_restores=True):
    """(name, rva) -> reason of deleted_rows.csv; a tombstone a `restored`
    rename lifted does not count (honour_restores) even if it came back."""
    out = {}
    raw = ctx.read(DELETED)
    if raw is None:
        return out
    for line in raw.decode("utf-8", errors="replace").splitlines():
        if not line.strip() or line.startswith(("#", "name,")):
            continue
        row = next(csv.reader(io.StringIO(line)))
        if len(row) >= 2 and _rva(row[1]) is not None:
            out[(row[0], _rva(row[1]))] = row[2] if len(row) > 2 else ""
    if honour_restores:
        for pair in lifted_tombstones(ctx):
            out.pop(pair, None)
    return out


PLANNERS = {"function": plan_function, "global": plan_global, "file": plan_file, "class": plan_class,
            "member": plan_member, "param": plan_param, "local": plan_local}


def plan_rename(kind, *, ctx=None, **kwargs):
    """Plan one rename of `kind`; raises Refusal. Writes nothing."""
    if kind not in PLANNERS:
        raise Refusal(f"kind {kind!r} is not implemented in this build ({', '.join(PLANNERS)})")
    ctx = ctx or Context()
    plan = PLANNERS[kind](ctx, **kwargs)
    restoring = ctx._cache.pop("_restoring", None)
    if plan.basis == RESTORED and restoring:
        # check_csv keeps no record of a restore, so the landing's tombstones
        # must leave deleted_rows.csv; the restored name_basis.csv row is what
        # rename.py (and `check`) still knows them by
        lifted = set(restore_lifts(ctx, *restoring).values())
        if lifted:
            raw = plan.after.get(DELETED, ctx.read(DELETED)).decode("utf-8", errors="surrogateescape")
            kept = [l for l in raw.splitlines(keepends=True) if l.rstrip("\r\n") not in lifted]
            plan.edit(ctx, DELETED, "".join(kept).encode("utf-8", errors="surrogateescape"))
            plan.warnings.append(f"lifted {len(lifted)} tombstone(s) the landing wrote")
    return plan


# ---------------------------------------------------------------- apply

def build_verify(ctx, sources, cancel=None):
    """One ./build.sh over `sources`; True only on exit 0 with `Functions: OK`.
    `cancel`, a threading.Event, kills the build once set (False then)."""
    command = ([sys.executable, str(ctx.path("tools/build.py"))] if sys.platform == "win32"
               else [str(ctx.path("build.sh"))]) + list(sources)
    print(f"rename: verifying {len(sources)} source(s): ./build.sh {' '.join(sources)}", flush=True)
    if cancel is None:
        result = subprocess.run(command, cwd=ctx.root, capture_output=True, text=True)
    else:
        result = _run_cancellable(command, cancel, cwd=ctx.root)
        if result is None:
            return False
    output = result.stdout + result.stderr
    tail = "\n".join(output.rstrip().splitlines()[-25:])
    print(tail)
    return result.returncode == 0 and re.search(r"^Functions: OK \d+/\d+", output, re.M) is not None


def restore(ctx, before):
    """Put every file back exactly as it was; remove files that did not exist."""
    for rel, data in before.items():
        path = ctx.path(rel)
        if data is None:
            if path.exists():
                path.unlink()
        else:
            path.write_bytes(data)


# ---------------------------------------------------------------- journal
#
# The container is killed every 20-40 minutes and a class or caller-heavy
# ./build.sh takes minutes, so the in-process rollback is not enough: before
# the first write the plan's before-state is journalled, and a run that dies
# (SIGKILL, power) leaves the journal for `rename.py recover`. Every new run
# refuses to start while one exists.

JOURNAL_DIR = "build/rename-journal"


def _boot_id():
    try:
        return Path("/proc/sys/kernel/random/boot_id").read_text().strip()
    except OSError:
        return ""


def _b64(data):
    return None if data is None else base64.b64encode(data).decode("ascii")


def _unb64(text):
    return None if text is None else base64.b64decode(text)


def journals(ctx):
    """[(path, record)] of every rename journal in this tree."""
    out = []
    for path in sorted(ctx.path(JOURNAL_DIR).glob("*.json")) if ctx.path(JOURNAL_DIR).is_dir() else []:
        try:
            out.append((path, json.loads(path.read_text(encoding="utf-8"))))
        except (OSError, ValueError):
            out.append((path, None))
    return out


def journal_alive(record):
    """True while the process that wrote `record` may still be running."""
    if not record or record.get("host") != socket.gethostname() or record.get("boot") != _boot_id():
        return False
    try:
        pid = int(record.get("pid", 0))
    except ValueError:
        return False
    if not _pid_alive(pid):
        return False
    return pid != os.getpid()


def _pid_alive(pid):
    """True while process `pid` runs. On Windows os.kill(pid, 0) is not a
    probe: signal 0 is CTRL_C_EVENT, which interrupts the console group, so
    ask the process handle for its exit code instead."""
    if pid <= 0:
        return False
    if os.name == "nt":
        import ctypes
        from ctypes import wintypes
        k32 = ctypes.WinDLL("kernel32", use_last_error=True)
        k32.OpenProcess.restype = wintypes.HANDLE
        handle = k32.OpenProcess(0x1000, False, pid)        # PROCESS_QUERY_LIMITED_INFORMATION
        if not handle:
            return ctypes.get_last_error() == 5              # access denied: it exists
        try:
            code = wintypes.DWORD()
            if not k32.GetExitCodeProcess(handle, ctypes.byref(code)):
                return False
            return code.value == 259                         # STILL_ACTIVE
        finally:
            k32.CloseHandle(handle)
    try:
        os.kill(pid, 0)
    except OSError:
        return False
    return True


def write_journal(ctx, plan, claimed=None):
    """Persist everything a restore needs before the first write."""
    record = {"id": uuid.uuid4().hex, "pid": os.getpid(), "host": socket.gethostname(), "boot": _boot_id(),
              "started": time.strftime("%Y-%m-%dT%H:%M:%SZ", time.gmtime()), "subject": plan.subject(),
              "before": {rel: _b64(data) for rel, data in plan.before.items()},
              "moves": [list(m) for m in plan.moves],
              "moved_bytes": {old: _b64(data) for old, data in plan.moved_bytes.items()},
              "claims": [str(k) if not isinstance(k, int) else f"0x{k:08X}" for k in (claimed.new if claimed else [])],
              "tokens": {str(k): v for k, v in (claimed.tokens if claimed else {}).items()}}
    folder = ctx.path(JOURNAL_DIR)
    folder.mkdir(parents=True, exist_ok=True)
    path = folder / f"{record['id']}.json"
    tmp = path.with_suffix(".tmp")
    tmp.write_text(json.dumps(record), encoding="utf-8")
    with tmp.open("r+b") as handle:  # Windows: fsync needs a writable handle
        os.fsync(handle.fileno())
    os.replace(tmp, path)
    return path


def restore_journal(ctx, record):
    """Undo one journalled rename: moves back, every file's bytes back."""
    for old, new in reversed(record.get("moves", [])):
        if ctx.path(new).exists() and not ctx.path(old).exists():
            moved = subprocess.run(["git", "-C", str(ctx.root), "mv", "--", new, old], capture_output=True)
            if moved.returncode == 0:
                continue
        data = _unb64(record.get("moved_bytes", {}).get(old))
        if data is not None:
            ctx.path(old).parent.mkdir(parents=True, exist_ok=True)
            ctx.path(old).write_bytes(data)
        if ctx.path(new).exists():
            ctx.path(new).unlink()
        subprocess.run(["git", "-C", str(ctx.root), "reset", "-q", "--", old, new], capture_output=True)
        subprocess.run(["git", "-C", str(ctx.root), "add", "--", old], capture_output=True)
    restore(ctx, {rel: _unb64(data) for rel, data in record.get("before", {}).items()})


def recover(ctx, *, release_claims=True):
    """Restore every journal whose process is gone; returns (restored, busy)."""
    restored, busy = [], []
    for path, record in journals(ctx):
        if record is None:
            raise Refusal(f"{path} is unreadable; inspect it by hand (the before-state is in it)")
        if journal_alive(record):
            busy.append(record.get("subject", path.name))
            continue
        restore_journal(ctx, record)
        if release_claims and record.get("claims") and os.environ.get("BFME_CLAIMS", "on") != "off":
            import claims
            claims.release(record["claims"], root=ctx.root,
                           tokens={claims.key_of(k): v for k, v in record.get("tokens", {}).items()})
        path.unlink()
        restored.append(record.get("subject", path.name))
    return restored, busy


def refuse_pending_journal(ctx):
    pending = journals(ctx)
    if pending:
        path, record = pending[0]
        state = "is still running" if journal_alive(record) else "did not finish"
        raise Refusal(f"a rename {state} ({(record or {}).get('subject', path.name)}; journal {path}): "
                      "run `python3 tools/rename.py recover` first")


# ---------------------------------------------------------------- apply

def ledger_checks(ctx, plan, csv_checks=None, skip=()):
    """What the commit hooks will say about the result: check_csv over the
    ledgers, find_declared_unmatched over the touched units, and the hook's
    other checks on a private index (commit_checks). [] when all pass (or when
    the tree has no such tools, as in a fixture). commit_checks runs beside the
    other two: its longest tool is the one that sets the time. A signal or an
    error in the main thread cancels it (its running tool is killed) and
    propagates at once (in whichever of the two waits it lands: check_csv or the
    hook tools), so the restore does not wait for the tools.
    `csv_checks(ctx, plan)` replaces the main-thread half (rename_files' tolerant
    lane judges check_csv against a baseline) and `skip` names hook checks to
    leave out; both keep this cancellation."""
    cancel = threading.Event()
    pool = concurrent.futures.ThreadPoolExecutor(max_workers=1)
    gates = pool.submit(commit_checks, ctx, plan, skip=skip, cancel=cancel)
    try:
        problems = (csv_checks or _csv_checks)(ctx, plan)
        found = gates.result()           # most of the time is spent here: a signal must cancel it too
    except BaseException:
        cancel.set()
        pool.shutdown(wait=False, cancel_futures=True)
        raise
    pool.shutdown()
    return problems + found


def _csv_checks(ctx, plan):
    problems = []
    if ctx.path("tools/check_csv.py").exists():
        result = subprocess.run([sys.executable, "tools/check_csv.py"], cwd=ctx.root, capture_output=True,
                                text=True)
        if result.returncode:
            problems.append("check_csv: " + " | ".join((result.stdout + result.stderr).strip().splitlines()[-5:]))
    units = sorted({rel for rel in plan.after if rel.startswith("Code/") and rel.endswith(SOURCE_SUFFIXES)} |
                   {new for _old, new in plan.moves})
    if units and ctx.path("tools/find_declared_unmatched.py").exists():
        result = subprocess.run([sys.executable, "tools/find_declared_unmatched.py", "--fail", *units],
                                cwd=ctx.root, capture_output=True, text=True)
        if result.returncode:
            problems.append("find_declared_unmatched: " +
                            " | ".join((result.stdout + result.stderr).strip().splitlines()[-5:]))
    return problems


# The pre-commit hook's other checks, run on what the commit will contain.
# They read the git index (`--staged`, `--ref :`), and rename.py does not
# stage, so each runs against a PRIVATE COPY of the index (GIT_INDEX_FILE) with
# exactly the files the plan wrote added, and the ones earlier plans of the same run
# left in the tree (ctx.kept): the lander's `git add <those paths>`,
# by the same tools and arguments as .githooks/pre-commit, without touching the
# real index. A plan that passed only check_csv and find_declared_unmatched
# could still fail at commit -- e.g. a renamed alias pin giving one address a
# second real name (pin_admission).
#
#   class_gate         a unit that now declares a registered class's body
#   ledger_guard       a ledger or compiler input edited outside the plan
#   code_identity_gate a wrong binding, duplicate definition or hand-made alias
#   link_debt          a new hard-coded image address
#   check_case_collisions   a path differing from another only in case
#   hatch_counters     an escape hatch (pin, alias row, marker) that grew
#   data_check         the data baseline, and (converged) a second name for a
#                      converged data address in a unit the plan builds
#   eh_verify          exception data of the built units against retail
#   pin_admission      pins/alias rows (only when a ledger file is staged)
#   pin_consistency    a pin naming a different function (the same condition)
#   name_dependents    other units that call a name the plan took away; the hook
#                      byte-verifies them, so they are built here too
#
# Not run here, because a rename cannot change what they judge: conversion_gate
# (a row repointed to assembly), tu_ownership and invented_names (shadow),
# header_dependents and the scoped build (the plan's own ./build.sh covers the
# units it names), and the baseline shrink-only assertions (rename.py never
# edits a baseline). They still run at commit.
# COMMIT_LEDGER_FILES switches on pin_admission and pin_consistency and is the hook's own
# `ledger_changed` list (a test compares them). NAME_LEDGER_FILES switches on name_dependents
# alone: the hook runs that on every commit, and these are the ledgers it reads names from.
COMMIT_LEDGER_FILES = ("reverse/functions.csv", "reverse/symbols.csv", "reverse/deleted_rows.csv",
                       "reverse/re_attempts.log")
NAME_LEDGER_FILES = ("reverse/functions.csv", "reverse/symbols.csv", "reverse/data_rows.csv")


@contextlib.contextmanager
def staged_index(ctx, paths):
    """Environment whose GIT_INDEX_FILE is a copy of the repository's index with
    `paths` staged (additions, edits and deletions alike); None when ctx.root
    is no git tree. A path git refuses to stage raises Refusal. This never
    writes the real index (a file rename's `git mv` has already staged its move
    there, and a failed run undoes it)."""
    found = subprocess.run(["git", "-C", str(ctx.root), "rev-parse", "--git-path", "index"],
                           capture_output=True, text=True)
    if found.returncode:
        yield None
        return
    source = ctx.root / found.stdout.strip()
    with tempfile.TemporaryDirectory(prefix="rename-index-") as folder:
        private = Path(folder) / "index"
        if source.exists():
            private.write_bytes(source.read_bytes())
        env = dict(os.environ, GIT_INDEX_FILE=str(private), RENAME_SCRATCH=folder)
        staged = subprocess.run(["git", "-C", str(ctx.root), "add", "-A", "--pathspec-from-file=-",
                                 "--pathspec-file-nul"], input="\0".join(paths) + "\0", env=env,
                                capture_output=True, text=True)
        if staged.returncode:
            raise Refusal("the commit gates cannot be judged: git add of the plan's files failed: "
                          + (staged.stderr.strip().splitlines() or ["?"])[-1][:200])
        yield env


def _matched_sources(ctx):
    """Sources owning a matched function or data row: all the hook builds."""
    owned = set()
    for rel in (FUNCTIONS, DATA_ROWS):
        raw = ctx.read(rel)           # not ctx.dicts: that is the pre-rename state
        if raw:
            owned |= {r.get("source") for r in csv.DictReader(io.StringIO(raw.decode("utf-8")))
                      if r.get("status") == "matched"}
    return owned


def _hook_jobs(ctx, plan, paths):
    """{label: (tool, argv after the tool path, stdin bytes or None)} for the
    hook checks this plan calls for, in the hook's own spelling."""
    ledger = any(rel in COMMIT_LEDGER_FILES for rel in paths)
    names = any(rel in NAME_LEDGER_FILES for rel in paths)
    built = sorted(set(plan.verify) & _matched_sources(ctx))
    listed = ("\0".join(built) + "\0").encode() if built else None
    jobs = {
        "class_gate": ("class_gate", ["--staged"], None),
        "ledger_guard": ("ledger_guard", ["--staged"], None),
        "code_identity_gate": ("code_identity_gate", ["--staged"], None),
        "link_debt": ("link_debt", ["--staged"], None),
        "check_case_collisions": ("check_case_collisions", [], None),
        "hatch_counters": ("hatch_counters", ["--staged", "--note-file", "{scratch}/hatch-note"], None),
        "data_check": ("data_check", ["--staged"], None),
    }
    if ledger:
        jobs["pin_admission"] = ("pin_admission", ["--staged"], None)
        jobs["pin_consistency"] = ("pin_consistency", ["--check"], None)
    if names:
        jobs["name_dependents"] = ("name_dependents", ["--staged"], None)
    if built:
        jobs["data_converged"] = ("data_check", ["--converged", "--ref", ":", "--sources-from", "-"], listed)
        jobs["eh_verify"] = ("eh_verify", ["--sources-from", "-"], listed)
    return jobs


def _run_cancellable(argv, cancel, **kwargs):
    """subprocess.run that polls `cancel` (a threading.Event) and kills the
    process (its whole session, where there is one) when it is set; returns
    None then. `input` (bytes) is any size: it goes to the child through an
    unnamed temporary file, not a pipe, so a child that reads it late or never
    cannot block this call (communicate(input, timeout=...) writes only what the
    pipe takes and, once it has timed out, never sends the rest)."""
    stdin = kwargs.pop("input", None)
    posix = sys.platform != "win32"
    with contextlib.ExitStack() as stack:
        feed = None
        if stdin is not None:
            feed = stack.enter_context(tempfile.TemporaryFile())
            feed.write(stdin)
            feed.flush()
            feed.seek(0)
        process = subprocess.Popen(argv, stdin=feed, stdout=subprocess.PIPE, stderr=subprocess.PIPE,
                                   start_new_session=posix, **kwargs)
        while True:
            if cancel is not None and cancel.is_set():
                try:
                    if posix:
                        os.killpg(process.pid, signal.SIGKILL)       # the tool's own children too (./build.sh)
                    else:
                        process.kill()
                except OSError:
                    pass
                process.communicate()
                return None
            try:
                out, err = process.communicate(timeout=0.2)
                return subprocess.CompletedProcess(argv, process.returncode, out.decode("utf-8", "replace"),
                                                   err.decode("utf-8", "replace"))
            except subprocess.TimeoutExpired:
                pass


def commit_checks(ctx, plan, verify=None, skip=(), cancel=None, missing_ok=None):
    """Problems the hook's checks (see the table above) would raise on the
    change the plan makes (already written to the tree), each prefixed with the
    check's name. [] when all pass, when the plan writes nothing (the
    pre-rename call), when `ctx.root` is no git tree, or for the checks named
    in `skip`. A check whose tool is missing is a problem in the repository
    this module lives in; a fixture tree (any other root, or `missing_ok=True`)
    simply lacks it. Units name_dependents lists that the plan does not already
    verify are built with `verify` (default ./build.sh). `cancel`, a
    threading.Event, kills the running tools and returns [] once set."""
    own = plan.written()
    if not own:
        return []
    # the commit holds what earlier plans of this run left in the tree as well: an
    # unstaged leftover of theirs is not dirt from outside (ledger_guard would
    # refuse a ledger the private index lacked), while an edit nobody here wrote is
    paths = sorted(own | {rel for rel in ctx.kept if ctx.path(rel).exists()})
    if missing_ok is None:
        missing_ok = ctx.root.resolve() != ROOT.resolve()
    problems, jobs = [], {}
    for label, job in _hook_jobs(ctx, plan, paths).items():
        if label in skip:
            continue
        if ctx.path(f"tools/{job[0]}.py").exists():
            jobs[label] = job
        elif not missing_ok:
            problems.append(f"{label}: tools/{job[0]}.py is missing, so the hook's check cannot be judged")
    if not jobs:
        return problems
    with staged_index(ctx, paths) as env:
        if env is None:
            return problems

        def run_tool(label):
            tool, args, stdin = jobs[label]
            argv = [sys.executable, f"tools/{tool}.py", *[a.replace("{scratch}", env["RENAME_SCRATCH"]) for a in args]]
            return _run_cancellable(argv, cancel, cwd=ctx.root, env=env, input=stdin)
        with concurrent.futures.ThreadPoolExecutor(max_workers=len(jobs)) as pool:
            results = dict(zip(jobs, pool.map(run_tool, list(jobs))))
        if any(result is None for result in results.values()):
            return []
        for label, result in results.items():
            if result.returncode:
                text = (result.stdout + result.stderr).strip().splitlines()
                problems.append(f"{label}: " + " | ".join(text[-5:]))
        listed = results.get("name_dependents")
        if listed is not None and not listed.returncode:
            extra = sorted({line.strip() for line in listed.stdout.splitlines() if line.strip()}
                           - set(plan.verify))
            if extra:
                dirty = subprocess.run(["git", "-C", str(ctx.root), "diff", "--name-only", "-z"], env=env,
                                       capture_output=True, text=True).stdout.split("\0")
                unstaged = [rel for rel in extra if rel in dirty]
                if unstaged:
                    problems.append("name_dependents: unstaged edits in " + ", ".join(unstaged[:3]) +
                                    ", which call a name this change removes: the hook refuses them")
                owned = _matched_sources(ctx)
                extra = [rel for rel in extra if rel in owned and rel not in unstaged]
                if extra and not (cancel is not None and cancel.is_set()):
                    built = verify(ctx, extra) if verify else build_verify(ctx, extra, cancel=cancel)
                    if cancel is not None and cancel.is_set():
                        return []            # stopped part-way: nothing was judged
                    if not built:
                        problems.append(f"name_dependents: byte-verify of {len(extra)} unit(s) calling a name "
                                        f"this change removes failed ({', '.join(extra[:3])})")
    return problems


def refusing(problems):
    """The checks behind `problems` (each starts `<check>: `), once each, in order."""
    return ", ".join(dict.fromkeys(p.split(":", 1)[0] for p in problems))


def apply_rename(plan, *, ctx=None, verify=build_verify, checks=ledger_checks, claimed=None):
    """Write the plan, verify it (./build.sh, then the hooks' ledger checks),
    restore everything on any failure. A journal written before the first
    write makes a killed run recoverable (`rename.py recover`). Raises
    Refusal when the tree moved since planning or a journal is pending,
    VerifyFailed when the build or the ledger checks refuse the result."""
    ctx = ctx or Context()
    refuse_pending_journal(ctx)
    for rel, data in plan.before.items():
        if ctx.read(rel) != data:
            raise Refusal(f"{rel} changed since the rename was planned; plan again")
    for old, new in plan.moves:
        if ctx.read(old) != plan.moved_bytes.get(old) or ctx.path(new).exists():
            raise Refusal(f"{old} or {new} changed since the rename was planned; plan again")
    if checks:
        already = checks(ctx, Plan(plan.kind, plan.old, plan.new, plan.basis, plan.evidence, plan.source,
                                   plan.rva))
        if already:
            raise Refusal(f"the ledger checks already fail before the rename: {already[0][:300]}; "
                          "repair the ledger first (AGENTS.md step 2)")
    journal = write_journal(ctx, plan, claimed)
    moved = []
    try:
        for old, new in plan.moves:
            ctx.path(new).parent.mkdir(parents=True, exist_ok=True)
            result = subprocess.run(["git", "-C", str(ctx.root), "mv", "--", old, new],
                                    capture_output=True, text=True)
            if result.returncode:
                raise Refusal(f"git mv {old} {new} failed: {result.stderr.strip()[:200]}")
            moved.append((old, new))
        for rel, data in plan.after.items():
            ctx.path(rel).parent.mkdir(parents=True, exist_ok=True)
            ctx.path(rel).write_bytes(data)
        if not verify(ctx, plan.verify):
            raise VerifyFailed(f"verification failed for {plan.old} -> {plan.new}; every file restored")
        problems = checks(ctx, plan) if checks else []
        if problems:
            error = VerifyFailed(f"the commit hooks would refuse {plan.old} -> {plan.new} "
                                 f"[{refusing(problems)}] ({problems[0][:300]}); every file restored")
            error.problems = problems  # preserve diagnostics for targeted retries
            raise error
    except BaseException:
        unmove(ctx, plan, moved)
        restore(ctx, plan.before)
        journal.unlink()
        raise
    journal.unlink()
    ctx.kept |= plan.written()
    return plan


def unmove(ctx, plan, moved):
    """Undo `git mv`s newest first; the bytes go back even when git cannot."""
    for old, new in reversed(moved):
        result = subprocess.run(["git", "-C", str(ctx.root), "mv", "--", new, old],
                                capture_output=True, text=True)
        if result.returncode:
            ctx.path(old).write_bytes(plan.moved_bytes[old])
            if ctx.path(new).exists():
                ctx.path(new).unlink()
            subprocess.run(["git", "-C", str(ctx.root), "reset", "-q", "--", old, new],
                           capture_output=True)
            print(f"rename: warning: git mv {new} {old} failed; bytes restored, index reset "
                  f"for both paths ({result.stderr.strip()[:120]})", file=sys.stderr)


# ---------------------------------------------------------------- claims

def claim_keys(plan):
    """Every RVA the plan names, a file: scope for every Code/ or shim file it
    writes or moves, and class: for a class or member rename."""
    keys = [k for k in plan.claims if isinstance(k, int)]
    scopes = {k for k in plan.claims if isinstance(k, str)}
    for rel in list(plan.after) + [p for move in plan.moves for p in move]:
        if rel.startswith(("Code/", "reference/shims/")):
            scopes.add(f"file:{rel}")
    if plan.kind == "class":
        scopes.add(f"class:{plan.old_word}")
    if plan.kind == "member":
        scopes.add(f"class:{plan.old.split('::')[0]}")
    return sorted(set(keys)) + sorted(scopes)


def claim_label(key):
    return f"0x{key:08X}" if isinstance(key, int) else str(key)


@dataclass
class Claimed:
    new: list = field(default_factory=list)       # keys this run took (not ones it already held)
    tokens: dict = field(default_factory=dict)    # key -> fencing token, for a safe release
    unconfirmed: list = field(default_factory=list)

    def release(self, root=None):
        if not self.new:
            return []
        import claims
        tokens = {claims.key_of(k): v for k, v in self.tokens.items()}
        released = claims.release(self.new, root=root, tokens=tokens)
        self.new = []
        return released


def take_claims(keys, enabled, root=None):
    """Claim `keys`. Returns a Claimed holding only the keys this run newly
    took, so releasing it never drops a claim the caller already held.
    Prior ownership comes from claim()'s acquisition snapshot, not a separate
    active() fetch that could be cached or race the acquisition.
    Refuses when another worker holds any key; keys origin could not confirm
    (network trouble, nobody else holding them) are reported, not refused."""
    if not enabled or os.environ.get("BFME_CLAIMS", "on") == "off" or not keys:
        return Claimed()
    import claims
    try:
        result = claims.claim(keys, note="tools/rename.py", root=root)
    except claims.ClaimsUnavailable as error:
        if error.refused:
            claims.release([k for k in error.claimed], root=root)
            raise Refusal(f"claimed by another worker: {', '.join(map(claim_label, error.refused))}")
        print(f"rename: warning: claims unavailable ({error}); working unclaimed", file=sys.stderr)
        return Claimed(new=list(error.claimed))
    claimed, refused = result
    held = {claims.key_of(k) for k in result.prior}
    unconfirmed = set(getattr(result, "unconfirmed", []))
    taken = Claimed(new=[k for k in claimed if claims.key_of(k) not in held],
                    tokens={k: v for k, v in result.tokens.items() if claims.key_of(k) not in held},
                    unconfirmed=sorted(unconfirmed, key=str))
    others = [k for k in refused if k not in unconfirmed]
    if others:
        taken.release(root)
        raise Refusal(f"claimed by another worker: {', '.join(map(claim_label, others))}")
    if unconfirmed:
        print("rename: warning: origin could not confirm claims on "
              f"{', '.join(map(claim_label, unconfirmed))} (network; nobody else holds them): working unclaimed "
              "there", file=sys.stderr)
    return taken


# ---------------------------------------------------------------- run

class _Terminated(KeyboardInterrupt):
    """SIGTERM, raised so the rollback in apply_rename runs."""


def _on_sigterm(signum, frame):
    raise _Terminated(f"signal {signum}")


def run_scoped_batch(ctx, requests, *, claim=True, verify=build_verify, checks=ledger_checks):
    """Compose same-file param/local plans in memory, then claim and verify once.

    Each request still goes through its ordinary planner, including agreement,
    capture and optimisation checks. The usual apply journal covers the combined
    before-state, so a failed build/check or interruption restores every edit.
    """
    from portable_lock import lock, unlock

    class View(Context):
        def read(self, rel):
            return combined.after[rel] if rel in combined.after else ctx.read(rel)

    if len(requests) < 2:
        raise Refusal("a scoped batch needs at least two renames")
    refuse_pending_journal(ctx)
    combined = Plan("local", "scoped names", "readable names", "inferred", "", None, None,
                    new_word=f"{len(requests)} readable names")
    view = View(ctx.root, object_scan=ctx.object_scan, sweep_dirs=ctx.sweep_dirs)
    plans = []
    previous = None
    if threading.current_thread() is threading.main_thread():
        previous = signal.signal(signal.SIGTERM, _on_sigterm)
    try:
        with ctx.path(LOCK).open("a") as handle:
            lock(handle, exclusive=True, wait_notice="rename: waiting for the ledger lock...")
            try:
                for kind, kwargs in requests:
                    if kind not in ("param", "local"):
                        raise Refusal("scoped batches support only parameter and local renames")
                    plan = plan_rename(kind, ctx=view, **kwargs)
                    if combined.source is None:
                        combined.source = plan.source
                    if plan.source != combined.source or plan.moves or set(plan.after) - {plan.source, NAME_BASIS, NAME_BINDINGS}:
                        raise Refusal("scoped batch plans must edit one source and its naming records only")
                    for rel, before in plan.before.items():
                        combined.before.setdefault(rel, before)
                    combined.after.update(plan.after)
                    combined.claims += claim_keys(plan)
                    combined.verify = sorted(set(combined.verify) | set(plan.verify))
                    plans.append(plan)
                    view._cache.clear()
                combined.claims = claim_keys(combined)
                for plan in plans:
                    print(plan.report())
                print(f"rename: batch of {len(plans)} scoped names; one verification.", flush=True)
                claimed = take_claims(combined.claims, claim, ctx.root)
                try:
                    apply_rename(combined, ctx=ctx, verify=verify, checks=checks, claimed=claimed)
                except BaseException:
                    claimed.release(ctx.root)
                    raise
                if claimed.new:
                    print("rename: claims kept until the rename is pushed; then run: python3 tools/claims.py release "
                          + " ".join(map(claim_label, claimed.new)))
                print(f"rename: batch verified OK ({len(plans)} names, {len(combined.verify)} source(s)).")
                return plans
            finally:
                ctx._cache.clear()
                unlock(handle)
    finally:
        if previous is not None:
            signal.signal(signal.SIGTERM, previous)


def run_member_batch(ctx, requests, *, claim=True, verify=build_verify, checks=ledger_checks):
    """Compose approved same-source member plans and verify their union once.

    Each request still passes through plan_member against the previous plans'
    in-memory result. The combined journal restores all edits if verification
    or a ledger check fails.
    """
    from portable_lock import lock, unlock

    if len(requests) < 2:
        raise Refusal("a member batch needs at least two renames")
    sources = {request.get("source") for request in requests}
    if len(sources) != 1 or None in sources:
        raise Refusal("member batches must be for one owner source")
    source = next(iter(sources))
    max_files = min(request.get("max_files", 25) for request in requests)

    class View(Context):
        def read(self, rel):
            return combined.after[rel] if rel in combined.after else ctx.read(rel)

    refuse_pending_journal(ctx)
    combined = Plan("member-batch", f"{len(requests)} approved members", f"{len(requests)} names",
                    "inferred", "approved member batch", source, None)
    view = View(ctx.root, object_scan=ctx.object_scan, sweep_dirs=ctx.sweep_dirs)
    plans = []
    previous = None
    if threading.current_thread() is threading.main_thread():
        previous = signal.signal(signal.SIGTERM, _on_sigterm)
    try:
        with ctx.path(LOCK).open("a") as handle:
            lock(handle, exclusive=True, wait_notice="rename: waiting for the ledger lock...")
            try:
                for request in requests:
                    kwargs = dict(request)
                    expected_source = kwargs.pop("source")
                    plan = plan_rename("member", ctx=view, **kwargs)
                    if expected_source not in plan.source_counts:
                        raise Refusal(f"{plan.old} is not declared in its approved owner source {expected_source}")
                    for rel, before in plan.before.items():
                        combined.before.setdefault(rel, before)
                    combined.after.update(plan.after)
                    for rel, counts in plan.source_counts.items():
                        target = combined.source_counts.setdefault(rel, {})
                        for name, count in counts.items():
                            target[name] = target.get(name, 0) + count
                    combined.claims.extend(claim_keys(plan))
                    combined.verify = sorted(set(combined.verify) | set(plan.verify))
                    combined.mentions = sorted(set(combined.mentions) | set(plan.mentions))
                    combined.warnings.extend(plan.warnings)
                    plans.append(plan)
                    view._cache.clear()

                changed_sources = {rel for rel in combined.after
                                   if rel.startswith(("Code/", "reference/shims/"))}
                if len(changed_sources) > max_files:
                    raise Refusal(f"member batch touches {len(changed_sources)} sources "
                                  f"(over --max-files {max_files})")
                if len(combined.verify) > max_files:
                    raise Refusal(f"member batch verifies {len(combined.verify)} sources "
                                  f"(over --max-files {max_files})")
                combined.claims = claim_keys(combined)
                for plan in plans:
                    print(plan.report())
                print(f"rename: batch of {len(plans)} member names; one verification.", flush=True)
                claimed = take_claims(combined.claims, claim, ctx.root)
                try:
                    apply_rename(combined, ctx=ctx, verify=verify, checks=checks, claimed=claimed)
                except BaseException:
                    claimed.release(ctx.root)
                    raise
                if claimed.new:
                    print("rename: claims kept until the rename is pushed; then run: python3 tools/claims.py release "
                          + " ".join(map(claim_label, claimed.new)))
                print(f"rename: batch verified OK ({len(plans)} names, {len(combined.verify)} source(s)).")
                return plans
            finally:
                ctx._cache.clear()
                view._cache.clear()
                unlock(handle)
    finally:
        if previous is not None:
            signal.signal(signal.SIGTERM, previous)


def pin_preflight(ctx, plan):
    """Cheap subset of pin admission; proof/native checks remain final gates."""
    if SYMBOLS not in plan.after and FUNCTIONS not in plan.after:
        return []
    import pin_admission
    def rows(rel, after=False):
        raw = (plan.after.get(rel, ctx.read(rel)) if after else ctx.read(rel))
        return pin_admission.csv_rows(raw.decode("utf-8")) if raw else []
    # Tiny test/foreign repositories need not contain the retail image.
    if not (ctx.root / "tools/pin_admission.py").exists():
        return []
    return pin_admission.judge(rows(SYMBOLS), rows(SYMBOLS, True),
                               rows(FUNCTIONS), rows(FUNCTIONS, True), static_only=True)


def diagnostic_suspects(plans, messages):
    """Exact pin names from gate diagnostics, used only to partition retries."""
    pins = set(re.findall(r"reverse/symbols\.csv:\s*([^,\s]+),0x[0-9A-Fa-f]+:",
                          "\n".join(messages)))
    return [index for index, plan in plans if any(
        name in pins for pin in plan.renamed_pins for name in pin[:2])]


def _argument_chunks(values, budget=12000):
    """Leave room for Git options and quoting under Windows' command limit."""
    chunk, size = [], 0
    for value in values:
        cost = len(value) + 4
        if chunk and size + cost > budget:
            yield chunk
            chunk, size = [], 0
        chunk.append(value)
        size += cost
    if chunk:
        yield chunk


def _planning_names(ctx, requests):
    """Potential function/global queries; ownership and permission stay in planners."""
    kinds = {kind for kind, _ in requests}
    by_rva = collections.defaultdict(list)
    if "function" in kinds:
        for row in ctx.rows():
            by_rva[_rva(row.get("target_rva"))].append(row)
    data = ctx.dicts(DATA_ROWS) if "global" in kinds else []
    symbols, terms = set(), set()
    for kind, kwargs in requests:
        if kind == "function":
            rva = kwargs.get("rva")
            old = kwargs.get("old")
            owners = [row["name"] for row in by_rva.get(rva, ())
                      if not row["name"].startswith(("__ehhandler$", "__unwindfunclet$", "$L"))
                      and "parent=" not in row.get("notes", "")
                      and (not old or row["name"] == old)]
            for name in list(owners):
                owners.extend(alias_pins(ctx, name, rva))
        elif kind == "global":
            old = kwargs.get("name")
            owners = [row["name"] for row in data
                      if row.get("name") == old or _identifier(row.get("name", "")) == old]
        else:
            continue
        symbols.update(owners)
        for name in [*owners, kwargs.get("new")]:
            if not isinstance(name, str) or not name:
                continue
            terms.add(name)
            word = _identifier(name)
            if word:
                terms.add(word)
    # Invalid or non-ASCII requests use the ordinary planner/search path.
    terms = {term for term in terms if term.isascii() and len(term) <= 1024
             and not any(c in term for c in "\r\n\0")}
    return terms, symbols


class _PlanningSearches:
    """Narrow exact Git queries using one shared candidate scan per root group.

    The candidate scan is a superset: Git still decides each query's word,
    binary and tracked-file semantics. This snapshot belongs to one ledger-lock
    interval only; restored retries construct a new one and see new callers.
    """
    def __init__(self, ctx, terms):
        self.ctx = ctx
        self.terms = sorted(terms)
        self.groups = {}
        self.results = {}

    def grep_files(self, needle, *, word=False, roots=SEARCH_ROOTS):
        if needle not in self.terms:
            return self.ctx.grep_files(needle, word=word, roots=roots)
        roots = tuple(roots)
        group = (word, roots)
        if group not in self.groups:
            candidates = {term: set() for term in self.terms}
            scanned = set()
            encoded = [(term, term.encode("ascii")) for term in self.terms]
            for chunk in _argument_chunks(self.terms):
                args = ["grep", "-l", "-z", "-F", "-I"] + (["-w"] if word else [])
                for term in chunk:
                    args.extend(("-e", term))
                output = self.ctx.git(*args, "--", *roots)
                for rel in filter(None, output.split("\0")):
                    if rel in scanned:
                        continue
                    data = self.ctx.read(rel)
                    if data is None:
                        raise Refusal(f"{rel} disappeared during the batch search")
                    scanned.add(rel)
                    for term, raw in encoded:
                        if raw in data:
                            candidates[term].add(rel)
            self.groups[group] = candidates
        key = (needle, word, roots)
        if key not in self.results:
            found = set()
            paths = [":(literal)" + path for path in sorted(self.groups[group][needle])]
            for chunk in _argument_chunks(paths):
                args = ["grep", "-l", "-z", "-F", "-I"] + (["-w"] if word else [])
                found.update(filter(None, self.ctx.git(*args, "-e", needle, "--", *chunk).split("\0")))
            self.results[key] = sorted(found)
        return list(self.results[key])


class _PlanningConsumers:
    """Read current objects and stale-source text once for all prepared symbols."""
    def __init__(self, ctx, symbols):
        self.ctx = ctx
        self.symbols = symbols
        self.by_name = None
        self.objects = None

    def __call__(self, symbols):
        import name_dependents
        if self.objects is None:
            self.objects = name_dependents._row_objects(self.ctx.rows())
        if symbols <= self.symbols:
            if self.by_name is None:
                self.by_name = name_dependents.dependents_by_name(self.symbols, self.objects, self.ctx.root)
            return set().union(*(self.by_name[name] for name in symbols))
        # Scope changes can introduce a symbol outside the initial request set.
        return name_dependents.dependents(symbols, self.objects, self.ctx.root)


class RunBatchSession:
    """Prepared plans and fenced claims shared by restored retries.

    A cached plan is reused only while its recorded reads, tracked searches and
    object-query generation remain valid. Full verification still runs per group.
    """
    def __init__(self, ctx):
        self.ctx = ctx
        self.prepared = {}
        self.held = set()
        self.claimed = Claimed()
        self.kept = set()
        self.object_generation = 0
        self.object_stamp = None

    def refresh_object_stamp(self):
        """Detect builds in this or another worker before trusting object queries."""
        if not self.ctx.object_scan:
            return
        import build
        import name_dependents
        objects = name_dependents._row_objects(self.ctx.rows())
        paths = {path for group in objects.values() for path in group}
        stamp = []
        for source in sorted(objects):
            path = self.ctx.path(source)
            try:
                stat = path.stat()
                item = (stat.st_size, stat.st_mtime_ns, stat.st_ctime_ns)
            except OSError:
                item = None
            stamp.append((source, item))
        for output in sorted(paths, key=str):
            for path in (output, build._deps_sidecar(output)):
                try:
                    stat = path.stat()
                    item = (stat.st_size, stat.st_mtime_ns, stat.st_ctime_ns)
                except OSError:
                    item = None
                stamp.append((str(path), item))
        stamp = tuple(stamp)
        if self.object_stamp is not None and stamp != self.object_stamp:
            self.object_generation += 1
        self.object_stamp = stamp

    def acquire(self, keys, enabled):
        missing = [key for key in keys if key not in self.held]
        got = take_claims(missing, enabled, self.ctx.root)
        self.held.update(missing)
        self.claimed.new.extend(got.new)
        self.claimed.tokens.update(got.tokens)
        self.claimed.unconfirmed.extend(got.unconfirmed)
        # Recovery of this transaction may release its new claims, but must
        # preserve those supporting an earlier verified group.
        current = [key for key in self.claimed.new if key in keys and key not in self.kept]
        return Claimed(current, {k: v for k, v in self.claimed.tokens.items() if k in current})

    def close(self):
        unused = [key for key in self.claimed.new if key not in self.kept]
        Claimed(unused, {k: v for k, v in self.claimed.tokens.items() if k in unused}).release(self.ctx.root)
        self.claimed.new = [key for key in self.claimed.new if key in self.kept]


@dataclass
class RunBatchResult:
    plans: list = field(default_factory=list)    # (request index, ordinary Plan)
    refused: dict = field(default_factory=dict)  # request index -> planning refusal
    failure: Exception = None                  # the combined transaction was restored
    suspects: list = field(default_factory=list)  # exact diagnostic request indices


def run_batch(ctx, requests, *, claim=True, verify=build_verify, checks=ledger_checks, session=None):
    """Plan each name normally, then claim/apply/verify the complete union.

    Planning refusals affect only their request. A failed combined transaction
    is restored by apply_rename and returned to the caller for smaller retries.
    Unexpected errors and interrupts propagate after recovery and claim release.
    Source moves are excluded: this API batches identifier changes only.
    """
    from portable_lock import lock, unlock

    refuse_pending_journal(ctx)
    requests = list(requests)
    result = RunBatchResult()
    own_session = session is None
    session = session or RunBatchSession(ctx)
    reads = {}
    searches = {}
    git_searches = {}
    combined = Plan("run-batch", "approved names", "readable names", "inferred", "", None, None)

    class View(Context):
        def read(self, rel):
            data = combined.after[rel] if rel in combined.after else ctx.read(rel)
            reads[rel] = data
            return data

        def git(self, *args):
            output = ctx.git(*args)
            if args and args[0] == "grep":
                git_searches[tuple(args)] = output
            return output

        def grep_files(self, needle, *, word=False, roots=SEARCH_ROOTS):
            # git grep reads the real worktree. Reflect earlier in-memory plans
            # too, including newly introduced words and removed spellings.
            found = set(batch_searches.grep_files(needle, word=word, roots=roots))
            for rel, data in combined.after.items():
                if not any(rel == base.rstrip("/") or rel.startswith(base.rstrip("/") + "/")
                           for base in roots):
                    continue
                text = data.decode("utf-8", errors="surrogateescape") if data is not None else ""
                matches = word_re(needle).search(text) if word else needle in text
                if matches:
                    found.add(rel)
                else:
                    found.discard(rel)
            result = sorted(found)
            searches[(needle, word, tuple(roots))] = result
            return result

    view = View(ctx.root, object_scan=ctx.object_scan, sweep_dirs=ctx.sweep_dirs)
    previous = None
    if threading.current_thread() is threading.main_thread():
        previous = signal.signal(signal.SIGTERM, _on_sigterm)
    try:
        with ctx.path(LOCK).open("a") as handle:
            lock(handle, exclusive=True, wait_notice="rename: waiting for the ledger lock...")
            try:
                session.refresh_object_stamp()
                terms, symbols = _planning_names(ctx, requests)
                batch_searches = _PlanningSearches(ctx, terms)
                view._consumer_lookup = _PlanningConsumers(ctx, symbols)
                for index, (kind, kwargs) in enumerate(requests):
                    try:
                        if kind not in PLANNERS or kind == "file":
                            raise Refusal("run batches support identifier renames, not source moves")
                        key = (kind, repr(sorted(kwargs.items())))
                        cached = session.prepared.get(key)
                        reads.clear()
                        searches.clear()
                        git_searches.clear()
                        valid = bool(kwargs.get("basis") == "inferred" and cached)
                        if valid:
                            plan, expected_reads, expected_searches, expected_git, object_queries, generation = cached
                            valid = all(view.read(rel) == data for rel, data in expected_reads.items())
                            if valid:
                                valid = all(view.grep_files(needle, word=word, roots=roots) == result
                                            for (needle, word, roots), result in expected_searches.items())
                            if valid:
                                valid = all(view.git(*command) == result
                                            for command, result in expected_git.items())
                            if valid and generation != session.object_generation:
                                valid = all(object_referencers(view, symbols) == found
                                            for symbols, found in object_queries)
                        if valid:
                            plan = cached[0]
                        else:
                            reads.clear()
                            searches.clear()
                            git_searches.clear()
                            view._cache.clear()
                            view._object_queries = []
                            plan = plan_rename(kind, ctx=view, **kwargs)
                            session.prepared[key] = (plan, dict(reads), dict(searches), dict(git_searches),
                                                     list(view._object_queries), session.object_generation)
                            del view._object_queries
                        if plan.moves:
                            raise Refusal("a run batch may not move source files")
                        # Reject a pin conflict before it contaminates the union
                        # and forces clean proposals through a restored retry.
                        if SYMBOLS in plan.after:
                            problems = pin_preflight(view, plan)
                            if problems:
                                raise Refusal("pin_admission: " + "; ".join(problems))
                    except Refusal as exc:
                        result.refused[index] = str(exc)
                        view._cache.clear()
                        continue
                    for rel, before in plan.before.items():
                        combined.before.setdefault(rel, before)
                    combined.after.update(plan.after)
                    combined.verify = sorted(set(combined.verify) | set(plan.verify))
                    combined.claims.extend(claim_keys(plan))
                    for attr in ("renamed_rows", "renamed_pins", "notes_rows", "warnings", "mentions",
                                 "renamed_data", "owner_rows", "carried", "spellings"):
                        getattr(combined, attr).extend(getattr(plan, attr))
                    for rel, counts in plan.source_counts.items():
                        target = combined.source_counts.setdefault(rel, {})
                        for label, count in counts.items():
                            target[label] = target.get(label, 0) + count
                    result.plans.append((index, plan))
                    view._cache.clear()
                if not result.plans:
                    return result
                combined.claims = claim_keys(combined)
                for _, plan in result.plans:
                    print(plan.report())
                print(f"rename: run batch of {len(result.plans)} names; "
                      f"one verification of {len(combined.verify)} source(s).", flush=True)
                claimed = None
                try:
                    problems = pin_preflight(ctx, combined)
                    if problems:
                        message = "pin_admission: " + "; ".join(problems)
                        result.suspects = diagnostic_suspects(result.plans, problems)
                        raise VerifyFailed(message)
                    claimed = session.acquire(combined.claims, claim)
                    apply_rename(combined, ctx=ctx, verify=verify, checks=checks, claimed=claimed)
                except (Refusal, VerifyFailed) as exc:
                    if not result.suspects:
                        result.suspects = diagnostic_suspects(result.plans, getattr(exc, "problems", [str(exc)]))
                    result.failure = exc
                    return result
                except BaseException:
                    raise
                session.kept.update(combined.claims)
                if claimed.new:
                    print("rename: claims kept until the rename is pushed; then run: python3 tools/claims.py release "
                          + " ".join(map(claim_label, claimed.new)))
                print(f"rename: run batch verified OK ({len(result.plans)} names, "
                      f"{len(combined.verify)} source(s)).")
                return result
            finally:
                ctx._cache.clear()
                unlock(handle)
    finally:
        if own_session:
            session.close()
        if previous is not None:
            signal.signal(signal.SIGTERM, previous)


def run(kind, ctx, *, dry_run=False, claim=True, keep_claims=None, verify=build_verify, checks=ledger_checks,
        **kwargs):
    """Plan under the ledger lock, then (unless dry-run) claim, apply and
    keep the claims for the lander (released after the push), or release
    them when the rename fails."""
    from portable_lock import lock, unlock
    keep_claims = (not dry_run) if keep_claims is None else keep_claims
    if not dry_run:
        refuse_pending_journal(ctx)
    handle = None
    previous = None
    if not dry_run and threading.current_thread() is threading.main_thread():
        previous = signal.signal(signal.SIGTERM, _on_sigterm)
    try:
        if not dry_run:
            handle = ctx.path(LOCK).open("a")
            lock(handle, exclusive=True, wait_notice="rename: waiting for the ledger lock...")
        plan = plan_rename(kind, ctx=ctx, **kwargs)
        plan.claims = claim_keys(plan)
        print(plan.report())
        if dry_run:
            print("rename: --dry-run: nothing written")
            return plan
        claimed = take_claims(plan.claims, claim, ctx.root)
        try:
            apply_rename(plan, ctx=ctx, verify=verify, checks=checks, claimed=claimed)
        except BaseException:
            claimed.release(ctx.root)
            raise
        if not keep_claims:
            claimed.release(ctx.root)
        elif claimed.new:
            print("rename: claims kept until the rename is pushed; then run: python3 tools/claims.py release "
                  + " ".join(map(claim_label, claimed.new)))
        staged = " (git mv already staged " + ", ".join(n for _, n in plan.moves) + ")" if plan.moves else ""
        print(f"rename: verified OK. Stage: git add {' '.join(sorted(plan.after))}{staged}")
        print("rename: after every pull --rebase, before the push: python3 tools/rename.py check "
              "--range origin/master..HEAD")
        print(f"rename: suggested subject: {plan.subject()}")
        return plan
    finally:
        if handle is not None:
            unlock(handle)
            handle.close()
        if previous is not None:
            signal.signal(signal.SIGTERM, previous)


# ---------------------------------------------------------------- post-rebase check
#
# A rename is verified against the tree it was planned on. While it was in
# flight another seat may have landed a pin with the old name (symbols.csv
# union-merges), a caller declaring or calling it, or a data consumer extern:
# the byte gate masks DIR32 and a stale pin keeps the old name resolving, so
# all of that passes every gate and breaks only the link. `check` re-reads
# the merged tree for every rename the range landed.

CHECK_LEDGERS = (FUNCTIONS, SYMBOLS, DATA_ROWS, BODY_OWNERS)


def basis_rows_in_range(ctx, spec):
    """name_basis.csv rows the commits in `spec` (A..B) added."""
    diff = ctx.git("diff", "--unified=0", spec, "--", NAME_BASIS)
    added = [line[1:] for line in diff.splitlines() if line.startswith("+") and not line.startswith("+++")]
    rows = list(csv.DictReader(io.StringIO(NAME_BASIS_HEADER + "\n" + "\n".join(added))))
    return [r for r in rows if r.get("kind") != "kind"]


def code_spellers(ctx, word):
    """Non-generated Code/ and shim files that spell `word` as a code token."""
    out = []
    for rel in ctx.grep_files(word, word=True):
        if is_generated(rel):
            continue
        text = (ctx.read(rel) or b"").decode("utf-8", errors="replace")
        if code_mentions(text, word) or any(w in text for w in MARKER_WORDS) and word_re(word).search(text):
            out.append(rel)
    return out


def check_row(ctx, row, texts):
    """Problems with one landed rename: its old spelling still in use."""
    kind, old = row.get("kind"), row.get("old", "")
    problems = []
    if kind in ("function", "global"):
        old_re = mangled_re(old)
        for rel in CHECK_LEDGERS:
            if old_re.search(texts[rel]):
                problems.append(f"{rel} still spells {old}")
        word = _identifier(old) or old
        for rel in code_spellers(ctx, word):
            problems.append(f"{rel} still spells {word}")
    elif kind == "class":
        token = ClassToken(old)
        for rel in CHECK_LEDGERS:
            if token.search(texts[rel]):
                problems.append(f"{rel} still has a mangled name scoped or typed by {old}")
        for rel in code_spellers(ctx, old):
            problems.append(f"{rel} still spells {old}")
    elif kind == "file":
        if ctx.path(old).exists():
            problems.append(f"{old} exists again")
        for rel, _column in PATH_COLUMNS:
            if path_keyed_lines(ctx, rel, old):
                problems.append(f"{rel} still keys {old}")
    elif kind == "member" and "::" in old:
        cls, member = old.rsplit("::", 1)
        for rel in sorted(set(ctx.grep_files(cls, word=True)) & set(ctx.grep_files(member, word=True))):
            code = name_metric.strip((ctx.read(rel) or b"").decode("utf-8", errors="replace"))
            if any(member_statements(code[a:b], member) for a, b in class_bodies(code, cls)):
                problems.append(f"{rel} still declares {old}")
    elif kind in ("param", "local") and old.count("::") >= 1:
        scope, name = old.rsplit("::", 1)
        source = row.get("source", "")
        data = ctx.read(source) if source else None
        if data is None and "#" in scope:
            problems.append(f"{source}: source is missing for {scope}")
        if data is not None:
            code = name_metric.strip(data.decode("utf-8", errors="replace"))
            if "#" in scope:
                try:
                    functions = [pick_function(code, scope)]
                except Refusal as error:
                    problems.append(f"{source}: {error}")
                    functions = []
            else:
                # Old records did not store an overload selector. Retain
                # their conservative all-overloads check.
                functions = [f for f in name_metric.functions_in(code) if f[0].split("#")[0] == scope]
            for found, start, end, params in functions:
                body = code[code.find("{", start):end]
                if name in set(parameters(params)) | set(name_metric.local_names(body)):
                    problems.append(f"{source}: {found} still declares {kind} {name}")
    return problems


def check_renames(ctx, rows):
    """Problems with landed renames `rows` (name_basis.csv records): an old
    spelling back in a ledger, a pin, a source, a marker or a pragma, and any
    tombstoned (name, address) data row (functions.csv's tombstones are
    check_csv's). A row a later rename deliberately reverted is skipped."""
    texts = {rel: (ctx.read(rel) or b"").decode("utf-8", errors="replace") for rel in CHECK_LEDGERS}
    every = name_basis_rows(ctx)
    problems = []
    for row in rows:
        if row.get("kind") == "carry":
            continue
        position = next((i for i, r in enumerate(every) if r == row), -1)
        if any(r.get("new") == row.get("old") for r in every[position + 1:]):
            continue
        checked = row
        if row.get("kind") in ("param", "local"):
            current, source = row.get("new", ""), row.get("source", "")
            for later in every[position + 1:]:
                if later.get("kind") == "carry" and later.get("old") == current:
                    current = later.get("new", "")
                if later.get("kind") == "file" and later.get("old") == source:
                    source = later.get("new", "")
            if current != row.get("new") or source != row.get("source"):
                checked = dict(row, old=respell(row["kind"], current, word_of(row["kind"], row["old"])),
                               new=current, source=source)
                if any(r.get("new") == checked["old"] for r in every[position + 1:]):
                    continue
        problems += [f"{row.get('kind')} {row.get('old')} -> {row.get('new')}: {p}"
                     for p in check_row(ctx, checked, texts)]
    tombstoned = _tombstones(ctx)
    for (name, at), line in sorted(lifted_tombstones(ctx).items(), key=lambda kv: (kv[0][0], kv[0][1] or 0)):
        if (name, at) in _tombstones(ctx, honour_restores=False):
            problems.append(f"{DELETED} has the tombstone of restored {name} at 0x{at:08X} again (a union "
                            "merge brought it back); delete that line again -- check_csv refuses the row")
    for data in ctx.dicts(DATA_ROWS):
        if (data.get("name"), data_rva(data)) in tombstoned:
            problems.append(f"{DATA_ROWS} row {data.get('name')} at 0x{data_rva(data):08X} is tombstoned "
                            f"({tombstoned[(data.get('name'), data_rva(data))][:80]})")
    return problems


# ---------------------------------------------------------------- carry
#
# `check` finds a landed rename's old spelling back in a ledger. The commonest
# way is a notes token: a seat working on a tree older than the rename adds a
# `gen-funclet` row whose `parent=` still spells the parent's old name, and the
# union merge keeps it. No rename can fix that (the owner row already carries
# the new name, so the request reads as "the new name is the old name"), and
# the stale `parent=` stops build.py locating the funclet from its parent's
# exact EH graph: the row then rides on its `object-symbol=$L` pin alone while
# the byte gate stays green. `carry` replays the recorded renames over the
# notes tokens of functions.csv and writes the spelling the token would have
# had if it had existed at the time, only where the live ledger proves it.

CARRY_KINDS = ("function", "global", "class", "carry")
# Tokens whose value is a symbol of this ledger. `import=` and `target=` hold
# DLL import names (never renamed); any other `key=` is not understood.
CARRY_KEYS = frozenset({"parent", "parents", "icf-owner", "dup-of", "object-symbol"})
NOTES_TOKEN = re.compile(r"(?:__ehhandler\$|__unwindfunclet\$)?[A-Za-z_?@][A-Za-z0-9_?@$]*")
NOTES_KEY = re.compile(r"\s*([A-Za-z][A-Za-z0-9_-]*)=(?:[^|;=]*\|)*")


class NothingToCarry(Exception):
    """No notes token spells a renamed-away name (or none could be proven)."""


class _Unparsed(Exception):
    def __init__(self, record, why):
        super().__init__(why)
        self.record, self.why = record, why


@dataclass
class CarryRecord:
    order: int           # position among the effective records (chronological)
    row: dict            # the name_basis.csv record
    rva: object = None   # a function record's RVA
    pattern: object = None

    @property
    def kind(self):
        return self.row["kind"]

    @property
    def old(self):
        return self.row["old"]

    @property
    def new(self):
        return self.row["new"]

    def label(self):
        return f"{self.kind} {self.old} -> {self.new}"

    def quick(self):
        """A substring every symbol this record changes contains."""
        return f"{self.old}@" if self.kind == "class" else self.old

    def apply(self, symbol):
        if self.quick() not in symbol:
            return symbol
        if self.kind == "class":
            try:
                return class_sub(symbol, self.old, self.new)[0]
            except Unparsed as error:
                raise _Unparsed(self, f"cannot tokenize a mangled name spelling {self.old}: {error}") from None
        return self.pattern.sub(lambda _m: self.new, symbol)


def carry_candidates(ctx):
    """The name_basis.csv records a notes token can lag behind, in file order:
    function, global, class and (mangled) carry rows, minus a row whose old
    spelling a later row takes as its new one (check_renames skips it too: a
    restore, or a spelling reused for another name, so an old token is ambiguous
    and never carried). Records that fork (one old spelling renamed to two
    different names) stay in and are refused by plan_carry."""
    every = name_basis_rows(ctx)
    out = []
    for position, row in enumerate(every):
        old, new = row.get("old", ""), row.get("new", "")
        if row.get("kind") not in CARRY_KINDS or not old or not new or old == new:
            continue
        if row["kind"] == "carry" and not old.startswith("?"):
            continue
        if any(r.get("new") == old for r in every[position + 1:]):
            continue
        record = CarryRecord(len(out), row, rva=_rva(row.get("rva")) if row["kind"] == "function" else None)
        if row["kind"] != "class":
            record.pattern = mangled_re(old)
        out.append(record)
    return out


def notes_key(notes, start):
    """The `key` of the `key=` token a symbol at `start` is the value of, None
    for free prose, "?" for an `=` that no token key explains."""
    head = notes[:start]
    head = head[head.rfind(";") + 1:]
    if not head.strip():
        return None
    match = NOTES_KEY.fullmatch(head)
    if match:
        return match.group(1)
    return "?" if head.rstrip().endswith("=") else None


def rebuilt_payload(payload, flds, notes):
    """The record `payload` with only its notes field (the last) replaced, or
    None when the quoting would change anything else."""
    canonical = csv_line(flds)[:-1]
    if canonical == payload:
        return csv_line(flds[:-1] + [notes])[:-1]
    plain = ',"\r\n'
    old = flds[-1]
    if old and not any(c in old + notes for c in plain) and payload.endswith(old.encode("utf-8")):
        return payload[:-len(old.encode("utf-8"))] + notes.encode("utf-8")
    return None


def plan_carry(ctx, *, max_files=25, only=None):
    """Plan carrying every recorded rename onto the functions.csv notes tokens
    still spelling a renamed-away name. Returns (Plan or None, refusals) where
    refusals are (record label, reason). Writes nothing. `only` limits the work
    to occurrences whose chain holds one of those name_basis.csv records."""
    records = carry_candidates(ctx)
    refused = {}

    def refuse(record, why):
        refused.setdefault(record.order, []).append(why)

    by_old = {}
    for record in records:
        by_old.setdefault(record.old, set()).add(record.new)
    for record in records:
        if len(by_old[record.old]) > 1:
            refuse(record, f"{record.old} is renamed to {len(by_old[record.old])} different names (a forked chain)")
    if not records:
        return None, []

    raw = ctx.read(FUNCTIONS)
    ledger_io.lf_terminator(raw, "functions.csv")
    lines = [(payload, term, ledger_io.fields(payload)) for payload, term in ledger_io.split_records(raw)]
    header = lines[0][2]
    try:
        column = {name: header.index(name) for name in ("name", "target_rva", "source", "status", "notes")}
    except ValueError:
        raise Refusal("functions.csv header lacks name/target_rva/source/status/notes") from None
    if column["notes"] != len(header) - 1:
        raise Refusal("functions.csv: notes is not the last column")
    width = len(header)

    functions, name_source, live = {}, set(), set()
    for _payload, _term, flds in lines[1:]:
        if len(flds) != width:
            continue
        name = flds[column["name"]]
        live.add(name)
        name_source.add((name, flds[column["source"]]))
        functions.setdefault(name, []).append(flds)
    live |= {p.get("name", "") for p in ctx.pins()}
    data_names = {}
    for row in ctx.dicts(DATA_ROWS):
        data_names[row.get("name", "")] = data_names.get(row.get("name", ""), 0) + 1
    live |= set(data_names)

    quick = re.compile("|".join(re.escape(r.quick()) for r in records))
    cache = {}

    def replay(token):
        if token not in cache:
            current, chain = token, []
            try:
                for record in records:
                    moved = record.apply(current)
                    if moved != current:
                        chain.append(record)
                        current = moved
                cache[token] = (current, chain)
            except _Unparsed as error:
                cache[token] = error
        return cache[token]

    occurrences = []   # dicts: line, key, old, new, chain, start, end
    for number, (_payload, _term, flds) in enumerate(lines):
        if number == 0 or len(flds) != width:
            continue
        notes = flds[column["notes"]]
        if not quick.search(notes):
            continue
        for match in NOTES_TOKEN.finditer(notes):
            token = match.group(0)
            if "?" not in token and not any(r.pattern is not None and r.old in token for r in records):
                continue
            found = replay(token)
            if isinstance(found, _Unparsed):
                refuse(found.record, found.why)
                continue
            current, chain = found
            if chain:
                occurrences.append(dict(line=number, key=notes_key(notes, match.start()), old=token, new=current,
                                        chain=chain, start=match.start(), end=match.end()))
    if only is not None:
        occurrences = [o for o in occurrences if any(r.row in only for r in o["chain"])]

    def matched_rows(name):
        return [f for f in functions.get(name, []) if f[column["status"]] == "matched"]

    # Per-occurrence proof; a failure refuses every record of the chain.
    for o in occurrences:
        old, new, chain = o["old"], o["new"], o["chain"]
        flds = lines[o["line"]][2]
        where = f"0x{_rva(flds[column['target_rva']]) or 0:08X} {flds[column['name']]}"
        fail = None
        core = new
        for prefix in FUNCLET_PREFIXES:
            core = core.removeprefix(prefix)
        if is_generated(flds[column["source"]]):
            fail = f"{where}: the row is in generated source {flds[column['source']]} (carry does not verify Code/gen_*)"
        elif o["key"] is not None and o["key"] not in CARRY_KEYS:
            fail = f"{where}: {old} is the value of `{o['key']}=`, which carry does not rewrite"
        elif old in live:
            fail = f"{where}: {old} still names a live row, pin or data row (current, or a resurrected owner)"
        else:
            fn_rows, data_count = matched_rows(new), data_names.get(new, 0)
            if not ((len(fn_rows) == 1 and not data_count) or (not fn_rows and data_count == 1)):
                fail = (f"{where}: {new} names {len(fn_rows)} matched functions.csv row(s) and {data_count} "
                        "data row(s), not exactly one")
            else:
                rvas = {r.rva for r in chain if r.kind == "function"}
                if len(rvas) > 1 or None in rvas:
                    fail = f"{where}: the chain renames more than one address ({sorted(map(str, rvas))})"
                elif rvas:
                    at = {_rva(f[column["target_rva"]]) for f in matched_rows(core)}
                    if at != rvas:
                        fail = (f"{where}: {core} is at {', '.join(f'0x{a:08X}' for a in sorted(at) if a is not None) or 'no address'}, "
                                f"not the renamed function's 0x{next(iter(rvas)):08X}")
                if not fail and o["key"] == "parent" and "gen-funclet" in {t.strip() for t in
                                                                           flds[column["notes"]].split(";")}:
                    source = flds[column["source"]]
                    parents = matched_rows(new)
                    if len(parents) != 1 or parents[0][column["source"]] != source:
                        fail = f"{where}: parent {new} is not a row of the funclet's own source {source}"
                    elif ("__ehhandler$" + new, source) not in name_source:
                        fail = f"{where}: __ehhandler${new} is not a row of {source}"
        if fail:
            for record in chain:
                refuse(record, fail)

    # A record is all or nothing: drop every occurrence a refused record touches,
    # and every record whose rewrite still leaves its old spelling elsewhere.
    def surviving():
        return [o for o in occurrences if not any(r.order in refused for r in o["chain"])]

    def render(live_occurrences):
        by_line = {}
        for o in live_occurrences:
            by_line.setdefault(o["line"], []).append(o)
        out = []
        for number, (payload, term, flds) in enumerate(lines):
            if number in by_line:
                notes = flds[column["notes"]]
                for o in sorted(by_line[number], key=lambda o: -o["start"]):
                    notes = notes[:o["start"]] + o["new"] + notes[o["end"]:]
                rebuilt = rebuilt_payload(payload, flds, notes)
                if rebuilt is None or ledger_io.fields(rebuilt) != flds[:-1] + [notes]:
                    for o in by_line[number]:
                        for record in o["chain"]:
                            refuse(record, f"line {number + 1}: the notes field cannot be rewritten without "
                                           "touching another field's bytes")
                    out.append(payload + term)
                    continue
                payload = rebuilt
            out.append(payload + term)
        return b"".join(out)

    kept = surviving()
    while True:
        if not kept:
            return None, refusal_list(records, refused)
        text = render(kept).decode("utf-8")
        if surviving() != kept:
            kept = surviving()
            continue
        texts = {rel: (ctx.read(rel) or b"").decode("utf-8", errors="replace") for rel in CHECK_LEDGERS}
        texts[FUNCTIONS] = text
        bad = {}
        for record in {r.order: r for o in kept for r in o["chain"]}.values():
            problems = check_row(ctx, record.row, texts)
            if problems:
                bad[record.order] = (record, problems[0])
        if not bad:
            break
        for record, why in bad.values():
            refuse(record, f"{why} (outside the notes carry rewrites; resolve that first)")
        kept = surviving()

    changed = {o["line"] for o in kept}
    new_raw = render(kept)
    spellings = {}
    for o in kept:
        key = (o["old"], o["new"])
        spellings[key] = spellings.get(key, 0) + 1
    plan = Plan("carry", "", "", "carry", "", "", None)
    plan.edit(ctx, FUNCTIONS, new_raw)
    plan.spellings = [(old, new, count) for (old, new), count in sorted(spellings.items())]
    for number in sorted(changed):
        flds = lines[number][2]
        plan.notes_rows.append((flds[column["name"]], _rva(flds[column["target_rva"]])))
    sources = sorted({lines[n][2][column["source"]] for n in changed})
    plan.verify = sources
    if len(sources) > max_files:
        raise Refusal(f"{len(sources)} sources to verify (over --max-files {max_files}); carry fewer "
                      "renames at once (--range) or raise --max-files")
    plan.claims = sorted({at for _name, at in plan.notes_rows if at is not None}) + \
        [f"file:{s}" for s in sources if s.startswith("Code/")]
    for number in changed:   # the in-memory proof: only the notes field moved
        old_flds, new_flds = lines[number][2], ledger_io.fields(ledger_io.split_records(new_raw)[number][0])
        if old_flds[:-1] != new_flds[:-1]:
            raise Refusal(f"internal error: line {number + 1} changed outside its notes field")
    return plan, refusal_list(records, refused)


def refusal_list(records, refused):
    """[(record label, reason)] for every refused record, in record order."""
    by_order = {r.order: r for r in records}
    return [(by_order[order].label(), why) for order in sorted(refused) for why in dict.fromkeys(refused[order])]


def _plan_carry_kind(ctx, max_files=25, only=None):
    """plan_rename's entry for `carry`: the refusals ride on the context."""
    plan, refusals = plan_carry(ctx, max_files=max_files, only=only)
    ctx._cache["_carry_refusals"] = refusals
    if plan is None:
        raise NothingToCarry()
    return plan


PLANNERS["carry"] = _plan_carry_kind


def main(argv=None):
    parser = argparse.ArgumentParser(description=__doc__.split("\n\n")[0],
                                     formatter_class=argparse.RawDescriptionHelpFormatter,
                                     epilog=__doc__.split("\n\n", 1)[1])
    common = argparse.ArgumentParser(add_help=False)
    common.add_argument("--basis", help="'inferred' or 'canonical:<evidence-kind>' "
                        f"({', '.join(sorted(CANONICAL_KINDS))}); required except for function --virtual")
    common.add_argument("--evidence",
                        help="canonical: the evidence; inferred: the naming approval record; function --virtual: "
                             "an optional note beside the retail evidence the tool records itself")
    common.add_argument("--dry-run", action="store_true", help="print the full plan, write nothing")
    common.add_argument("--no-claim", action="store_true", help="skip tools/claims.py (tests)")
    common.add_argument("--no-object-scan", action="store_true",
                        help="find referencing units by text only, not cached object symbol tables")
    common.add_argument("--max-files", type=int, default=25, help="refuse a larger blast radius (default 25)")
    common.add_argument("--root", type=Path, default=ROOT, help="TEST-ONLY: operate on another tree")
    common.add_argument("--sweep-dir", action="append", default=None,
                        help="canonical:zh/bfme1: directory holding zh_sweep/ and bfme1_sweep/ caches "
                             "(default build/; repeatable), as tools/name_evidence.py takes it")
    common.add_argument("--release-claims", action="store_true",
                        help="release this run's claims when it ends (default: keep them for the lander, "
                             "who releases them after the push)")
    kinds = parser.add_subparsers(dest="kind", required=True)
    checker = kinds.add_parser("check", help="after a pull --rebase: refuse when a landed rename's old "
                                             "spelling is back (pins, callers, externs, markers)")
    span = checker.add_mutually_exclusive_group(required=True)
    span.add_argument("--range", dest="span", help="the commits to check, e.g. origin/master..HEAD")
    span.add_argument("--all", action="store_true", help="every name_basis.csv record")
    checker.add_argument("--root", type=Path, default=ROOT, help="TEST-ONLY: operate on another tree")
    carrier = kinds.add_parser("carry", help="write a landed rename's new spelling into the functions.csv notes "
                                             "tokens (parent=, icf-owner=, ...) that still spell the old one; "
                                             "not the name_basis.csv `carry` kind, and it records no basis row")
    reach = carrier.add_mutually_exclusive_group(required=True)
    reach.add_argument("--range", dest="span", help="only renames the commits in A..B added")
    reach.add_argument("--all", action="store_true", help="every name_basis.csv record")
    carrier.add_argument("--dry-run", action="store_true", help="print the plan and the refusals, write nothing")
    carrier.add_argument("--no-claim", action="store_true", help="skip tools/claims.py (tests)")
    carrier.add_argument("--max-files", type=int, default=25, help="refuse a larger blast radius (default 25)")
    carrier.add_argument("--release-claims", action="store_true",
                         help="release this run's claims when it ends (default: keep them for the lander)")
    carrier.add_argument("--root", type=Path, default=ROOT, help="TEST-ONLY: operate on another tree")
    recovery = kinds.add_parser("recover", help="restore every rename a killed run left half-applied")
    recovery.add_argument("--root", type=Path, default=ROOT, help="TEST-ONLY: operate on another tree")
    back = kinds.add_parser("revert", help="put the placeholder back over a landed inferred name "
                                           "(the exact inverse, recorded as basis restored)")
    back.add_argument("--record", required=True, help="the agreement id the landing cited (agree:<id>)")
    back.add_argument("--reason", required=True, help="what the code shows against the landed name")
    back.add_argument("--function", help="param/local only: Class::method#N when the function is overloaded")
    for flag, text in (("--dry-run", "print the full plan, write nothing"), ("--no-claim", "skip tools/claims.py"),
                       ("--no-object-scan", "find referencing units by text only"),
                       ("--release-claims", "release this run's claims when it ends")):
        back.add_argument(flag, action="store_true", help=text)
    back.add_argument("--root", type=Path, default=ROOT, help="TEST-ONLY: operate on another tree")
    function = kinds.add_parser("function", parents=[common],
                                help="respell one RVA's function identifier")
    function.add_argument("--rva", required=True, help="the function's target RVA (hex)")
    function.add_argument("--new",
                          help="new identifier, or the full mangled name (identifier change only); "
                               "required unless --virtual")
    function.add_argument("--old", help="the current mangled name, when several share the RVA")
    function.add_argument("--virtual", action="store_true",
                          help="respell the row non-virtual -> virtual (QAE->UAE, IAE->MAE, AAE->EAE), keeping "
                               "identifier, parameters and return type; refused unless a retail vtable slot of "
                               "the row's class (or of a class a view derives from it) holds the address")
    data = kinds.add_parser("global", parents=[common],
                            help="respell one reverse/data_rows.csv global and every consumer")
    data.add_argument("--name", required=True, help="the global's mangled name, or its bare identifier")
    data.add_argument("--new", required=True,
                      help="new identifier, or the full mangled name (identifier change only)")
    unit = kinds.add_parser("file", parents=[common],
                            help="git mv one Code/ unit within its directory, with its path-keyed rows")
    unit.add_argument("--source", required=True, help="the unit's repo-relative path")
    unit.add_argument("--new", required=True, help="new file name or stem (same directory), or full path")
    klass = kinds.add_parser("class", parents=[common],
                             help="respell one class/struct/union/enum token in every name and view")
    klass.add_argument("--name", required=True, help="the type's current identifier")
    klass.add_argument("--new", required=True, help="the new identifier")
    member = kinds.add_parser("member", parents=[common],
                              help="respell one non-static data member in every view and use")
    member.add_argument("--class", dest="cls", required=True, help="the class whose member it is")
    member.add_argument("--member", required=True, help="the member's current identifier")
    member.add_argument("--new", required=True, help="the new identifier")
    for kind in ("param", "local"):
        scoped = kinds.add_parser(kind, parents=[common],
                                  help=f"respell one {kind} inside one function body in one file")
        scoped.add_argument("--source", required=True, help="the ledger source defining the function")
        scoped.add_argument("--function", help="Class::method (Class::method#2 for a later overload)")
        scoped.add_argument("--rva", help="or the function's target RVA (hex)")
        scoped.add_argument("--name", required=True, help=f"the {kind}'s current identifier")
        scoped.add_argument("--new", required=True, help="the new identifier")
        if kind == "local":
            scoped.add_argument("--local-binding", action="store_true", help="prove one ordinary scalar binding and preserve outer uses")
    args = parser.parse_args(argv)
    if args.kind == "recover":
        ctx = Context(args.root, object_scan=False)
        try:
            restored, busy = recover(ctx)
        except Refusal as why:
            print(f"rename: refused: {why}", file=sys.stderr)
            return 2
        for subject in restored:
            print(f"rename: restored: {subject}")
        for subject in busy:
            print(f"rename: still running (left alone): {subject}")
        if not restored and not busy:
            print("rename: no rename journal; nothing to recover")
        return 1 if busy else 0
    if args.kind == "revert":
        ctx = Context(args.root, object_scan=not args.no_object_scan)
        try:
            revert(ctx, args.record.removeprefix("agree:"), args.reason, function=args.function,
                   dry_run=args.dry_run, claim=not args.no_claim,
                   keep_claims=False if args.release_claims else None)
        except Refusal as why:
            print(f"rename: refused: {why}", file=sys.stderr)
            return 2
        except VerifyFailed as why:
            print(f"rename: {why}", file=sys.stderr)
            return 1
        return 0
    if args.kind == "carry":
        ctx = Context(args.root, object_scan=False)
        try:
            only = None if args.all else basis_rows_in_range(ctx, args.span)
            run("carry", ctx, dry_run=args.dry_run, claim=not args.no_claim,
                keep_claims=False if args.release_claims else None, max_files=args.max_files, only=only)
        except NothingToCarry:
            print("rename: carry: no notes token spells a renamed-away name that carry can prove")
        except Refusal as why:
            print(f"rename: refused: {why}", file=sys.stderr)
            return 2
        except VerifyFailed as why:
            print(f"rename: {why}", file=sys.stderr)
            return 1
        refusals = ctx._cache.get("_carry_refusals", [])
        for label, why in refusals:
            print(f"rename: carry refused: {label}: {why}", file=sys.stderr)
        return 2 if refusals else 0
    if args.kind == "check":
        ctx = Context(args.root, object_scan=False)
        rows = name_basis_rows(ctx) if args.all else basis_rows_in_range(ctx, args.span)
        problems = check_renames(ctx, rows)
        for problem in problems:
            print(f"rename: check: {problem}", file=sys.stderr)
        print(f"rename: check: {len(rows)} rename(s), {len(problems)} problem(s)")
        if any(f"{FUNCTIONS} still " in problem for problem in problems):
            try:
                coverable, _refusals = plan_carry(ctx, only=rows)
            except Refusal:
                coverable = True
            if coverable:
                print("rename: check: a stale spelling in functions.csv notes (parent=, icf-owner=, ...) is "
                      "carried by: python3 tools/rename.py carry " + ("--all" if args.all else f"--range {args.span}"),
                      file=sys.stderr)
        return 1 if problems else 0
    virtual = args.kind == "function" and args.virtual
    if virtual and (args.new or args.basis):
        parser.error("function --virtual keeps the identifier and takes its evidence from retail: "
                     "pass neither --new nor --basis")
    if not virtual and (args.basis is None or args.evidence is None or args.new is None):
        parser.error("the following arguments are required: " +
                     ", ".join(f for f, v in (("--new", args.new), ("--basis", args.basis),
                                              ("--evidence", args.evidence)) if v is None))
    ctx = Context(args.root, object_scan=not args.no_object_scan, sweep_dirs=args.sweep_dir or ("build",))
    kwargs = dict(new=args.new, basis=args.basis, evidence=args.evidence, max_files=args.max_files)
    if virtual:
        kwargs = dict(virtual=True, evidence=args.evidence or "", max_files=args.max_files)
    if args.kind == "function":
        try:
            kwargs.update(rva=int(args.rva, 16), old=args.old)
        except ValueError:
            parser.error(f"--rva {args.rva!r} is not hex")
    elif args.kind in ("global", "class"):
        kwargs.update(name=args.name)
    elif args.kind == "member":
        kwargs.update(cls=args.cls, member=args.member)
    elif args.kind in ("param", "local"):
        try:
            rva = int(args.rva, 16) if args.rva else None
        except ValueError:
            parser.error(f"--rva {args.rva!r} is not hex")
        kwargs.update(source=args.source, name=args.name, function=args.function, rva=rva)
        if args.kind == "local":
            kwargs["local_binding"] = args.local_binding
    else:
        kwargs.update(source=args.source)
    try:
        run(args.kind, ctx, dry_run=args.dry_run, claim=not args.no_claim,
            keep_claims=False if args.release_claims else None, **kwargs)
    except Refusal as why:
        print(f"rename: refused: {why}", file=sys.stderr)
        return 2
    except VerifyFailed as why:
        print(f"rename: {why}", file=sys.stderr)
        return 1
    return 0


if __name__ == "__main__":
    sys.exit(main())
