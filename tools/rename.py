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
           beyond the identifier (two exceptions, both below: `function
           --virtual`, and `function --respell`, which takes prepared C++ for
           every unit that names the row and runs no word rewrite);
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
datum identifier and any class that scopes an export, a vendored= or .lib row,
an evidence-tier name or a converged datum. Retail is /GR-, so no RTTI string
carries a game class name. A placeholder class registered in
reverse/canonical_classes.csv moves with its registration: the registry key
(and its contract note), the contract (git mv to reverse/class_contracts/NEW.json,
its spellings respelled) and its reverse/header_queue.tsv rows (same sources,
same RVAs); the header keeps its path, and after ./build.sh no rebuilt object
may name a symbol of the old spelling (the "registered classes" section). A
readable registered class, a NEW already registered and a mismatched contract
are refused.
A `member` (one non-static data member of one class) never reaches bytes:
every view declaring it and every file using it through a header view is
rewritten, a file that also declares the word for another class is refused;
a registered class's contract field of that name is respelled with it.
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

`class --fold OLD --into NEW` respells placeholder class OLD as NEW, the name
the class's retail vftable already carries, when retail proves one class: an
OLD constructor/destructor/deleting destructor installs a vftable as its own
whose `??_7` names are NEW's, no third class owns that table (retail ICF-folds
identical vftables of distinct classes), the deleting destructors sit in its
slots, and OLD and NEW never both row one special-member kind (see
plan_fold's section), or when retail's only initializer of a global typed NEW
runs OLD's constructor (initializer_tie). It invents no name: no name_basis.csv record, tombstones
`(fold: retail vftable 0x...)`, and a pin the respelling makes a row's own name
is dropped. A readable OLD is refused.

`function --rva R --to-class C --new WORD [--prepared REL=FILE ...]` moves a
placeholder-class member (`?rva00550B4C@Rva00550B4C@@QAEXXZ`) into the real
class C as its virtual `WORD` (or the full mangled name given), keeping cv,
convention, return type and parameters, only when retail proves it: a table
that a constructor/destructor/deleting destructor row of C installs holds R in
exactly one slot, no unrelated class's table holds R, and the vftable C's own
installer units compile names the new symbol in that slot (checked against the
current objects when planning and against the rebuilt ones after ./build.sh;
the other slots that resolve must agree with retail's). The C++ is supplied
as prepared sources (the definition under C, its callers); the tool respells
ledger rows, funclets, notes tokens, pins, body owners and spelled mangled
names, tombstones `(to-class: retail vftable 0x... slot N)`, writes no
name_basis.csv record (the name comes from C's declaration, not an agent), and
is byte-gated like any rename (see plan_to_class's section). A full mangled
--new may respell a guessed int return as the enum a registered class header
declares for that virtual (ENUM_RETURN), and `--also RVA=NEW` moves further
slots of the same table in one plan, for a table whose slots all still sit
under other placeholders.

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
import struct
import subprocess
import sys
import tempfile
import threading
import time
import uuid
from dataclasses import dataclass, field
from pathlib import Path, PurePosixPath

sys.path.insert(0, str(Path(__file__).resolve().parent))

import cl_flags  # noqa: E402
import git_trust  # noqa: E402
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
CODE_IDENTITY_BASELINE = "reverse/code_identity_baseline.tsv"
NAME_BINDINGS = "reverse/name_bindings.csv"
NAME_BINDINGS_HEADER = "record,old,new,source,outer_sha256"
EXPORTS = "reverse/exports.csv"
NAME_TIERS = "reverse/name_tiers.csv"
CONVERGED = "reverse/data_converged.csv"
MODULES = "reverse/module_factory_registrations.csv"
DATA_LEDGER = "reverse/data_ledger.csv"
FOLD_CENSUS = "reverse/initializer_fold_census.csv"
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
# prepared sources one transaction carries: the default, and the ceiling above which
# --max-prepared also needs --beyond-prepared-ceiling
PREPARED_DEFAULT, PREPARED_CEILING = 32, 256
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


class ClaimConflict(Refusal):
    """Acquisition refused these canonical claim keys; no edits were made."""
    def __init__(self, keys):
        import claims
        self.claim_keys = tuple(claims.key_of(key) for key in keys)
        super().__init__("claimed by another worker: " + ", ".join(map(claim_label, self.claim_keys)))


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


SIGNATURE_ONLY = "signature-only:"


def signature_only_change(old, new):
    """Refuse unless `new` is `old` with only parameter or return-type cv-qualifiers or
    pointer-ness changed: the same identifier, class, access, `this` cv and calling convention
    (byte-identical through the member header), every name fragment byte-identical, and each
    differing character a pointer/reference code or its pointee's cv letter at a type position the
    parser reads in both names."""
    at_old = member_function_header(old)[0]
    at_new = member_function_header(new)[0]
    head = at_old + 3              # access code, `this` cv, calling convention
    if at_old != at_new or old[:head] != new[:head]:
        raise Refusal(f"{new} changes more than a parameter's or the return type's qualifiers: the identifier, "
                      f"class, access, `this` cv or calling convention differs from {old} (a naming claim, "
                      "not a signature-only respell)")
    if len(old) != len(new):
        raise Refusal(f"{new} adds or removes type codes against {old}: only a cv-qualifier or pointer-ness "
                      "change of the same types is a signature-only respell")
    if old == new:
        raise Refusal(f"{new} is {old}")
    try:
        quals_old, names_old = qualifier_positions(old)
        quals_new, names_new = qualifier_positions(new)
    except Unparsed as error:
        raise Refusal(f"cannot read the type positions of the respell ({error})") from None
    if names_old != names_new or any(old[a:b] != new[a:b] for a, b in names_old):
        raise Refusal(f"{new} changes a name against {old} (a class, scope or template name), not a qualifier")
    for i in (i for i, (a, b) in enumerate(zip(old, new)) if a != b):
        if i < head or i not in quals_old or i not in quals_new:
            raise Refusal(f"{new} differs from {old} at '{old[i]}' -> '{new[i]}' (index {i}), which is neither a "
                          "pointer/reference code nor the cv of what one points to")


# A virtual's `this` cv is part of what it overrides: `bool Cull_Sphere(const
# SphereClass &) const` in a class deriving CameraClass fills CameraClass's slot,
# while the same method declared non-const adds a slot of its own. So a row
# rowed with the wrong `this` cv (UAE for UBE) is respelled, without a vote, only
# when retail proves the const: the row's address sits in exactly one slot of a
# table its class's own constructor or destructor installs (to_class_evidence),
# and retail's bytes of every such install store the table through `this` (ecx,
# or a register copied from it with no load between) at offset 0; a base in the
# class's canonical ancestry (its reverse/canonical_classes.csv record: the
# contract's bases, else its registered header's class head -- never a prepared
# declaration) installs, through `this` too, a table whose same slot holds a
# registered row with the same identifier, convention and parameters, and every
# such base virtual has the new `this` cv. After ./build.sh, the installers'
# rebuilt table must name the respelled row in that slot (to_class_slot_problems).

def this_cv_change(old, new):
    """True when `new` is `old` with only `this`'s cv-qualifier changed: the
    same identifier, class, access, calling convention and parameters."""
    try:
        at_old = member_function_header(old)[0]
        at_new = member_function_header(new)[0]
    except Refusal:
        return False
    i = at_old + 1
    return (at_old == at_new and len(old) == len(new) and old[:i] == new[:i] and old[i + 1:] == new[i + 1:]
            and old[i] != new[i] and old[i] in "ABCD" and new[i] in "ABCD")


REG32 = ("eax", "ebx", "ecx", "edx", "esi", "edi", "ebp", "esp")
# a sub-register write clobbers its full register
FULL_REG = dict({r: r for r in REG32},
                **{r[1:]: r for r in REG32}, al="eax", ah="eax", bl="ebx", bh="ebx", cl="ecx", ch="ecx",
                dl="edx", dh="edx", sil="esi", dil="edi", bpl="ebp", spl="esp")


def eh_prolog_rva(ctx):
    """The address of the ledger's one __EH_prolog row, or None. Several rows of that name give no
    helper at all: an ambiguous row must not widen the calls that keep `this`."""
    rows = [r for r in ctx.rows() if r["name"] == "__EH_prolog"]
    return _rva(rows[0].get("target_rva")) if len(rows) == 1 else None


def this_store_problem(ctx, row, store):
    """None when the vptr store at retail `store` (`mov dword ptr [reg], imm32`) in
    `row`'s retail bytes writes through `this`: ecx at entry, or a register copied
    from it (`mov reg, reg`) with no load or other write in between, at offset 0
    (the primary vfptr). Else why not. The bytes from the row's start to the store
    are decoded in order; a branch before the store, or a store that is not an
    instruction boundary, is refused rather than followed. A call drops ecx, eax and
    edx, except that the ledger's one __EH_prolog row (eh_prolog_rva) leaves ecx in place:
    an EH frame opens with `mov eax,<FuncInfo>; call __EH_prolog` before the body copies
    `this`."""
    import capstone
    from capstone import x86
    import build
    start, size = _rva(row.get("target_rva")), int(row.get("target_size") or 0)
    if start is None or not start <= store < start + size:
        return f"0x{store:08X} is outside {row['name']}"
    try:
        code = build.read_target_bytes(start, store - start + 16)
    except (OSError, ValueError) as error:
        return f"retail's bytes of {row['name']} cannot be read ({error})"
    md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
    md.detail = True
    this = {"ecx"}
    eh_prolog = eh_prolog_rva(ctx)
    for ins in md.disasm(code, start):
        ops = ins.operands
        if ins.address == store:
            if ins.mnemonic != "mov" or len(ops) != 2 or ops[0].type != x86.X86_OP_MEM \
                    or ops[1].type != x86.X86_OP_IMM:
                return f"0x{store:08X} is not a vptr store (`{ins.mnemonic} {ins.op_str}`)"
            mem = ops[0].mem
            base = ins.reg_name(mem.base) if mem.base else None
            if mem.index or mem.segment or base not in this:
                return (f"0x{store:08X} stores through `{ins.op_str.split(',')[0]}`, not `this` (ecx, or a "
                        "register copied from it with no load in between)")
            if mem.disp:
                return f"0x{store:08X} stores at this+{mem.disp:#x}, not the primary vfptr at this+0"
            return None
        if ins.address > store:
            break
        if any(ins.group(g) for g in (capstone.CS_GRP_JUMP, capstone.CS_GRP_RET, capstone.CS_GRP_IRET,
                                      capstone.CS_GRP_INT)):
            return f"a branch at 0x{ins.address:08X} precedes the store at 0x{store:08X}"
        if ins.mnemonic == "mov" and len(ops) == 2 and ops[0].type == x86.X86_OP_REG \
                and ops[1].type == x86.X86_OP_REG and ins.reg_name(ops[0].reg) in REG32 \
                and ins.reg_name(ops[1].reg) in this:
            this.add(ins.reg_name(ops[0].reg))
            continue
        _read, written = ins.regs_access()
        for reg in written:
            this.discard(FULL_REG.get(ins.reg_name(reg), ins.reg_name(reg)))
        if ins.group(capstone.CS_GRP_CALL):
            frame = ops and ops[0].type == x86.X86_OP_IMM and ops[0].imm == eh_prolog
            this -= {"eax", "edx"} if frame else {"eax", "ecx", "edx"}
    return f"0x{store:08X} is not an instruction boundary of {row['name']}"


def receiver_problems(ctx, stores, installers):
    """[problem] unless every store {rva: displacement} of a table that one of the
    `installers` rows makes goes through `this` at offset 0 (this_store_problem);
    a table none of them stores is a problem too."""
    names = {r["name"] for r in installers}
    checked, problems = 0, []
    for store, _disp in sorted(stores.items()):
        row = row_at(ctx, store)
        if not row or row["name"] not in names:
            continue
        checked += 1
        why = this_store_problem(ctx, row, store)
        if why:
            problems.append(f"{row['name']}: {why}")
    if not checked:
        problems.append("none of its installers' stores was found")
    return problems


def canonical_ancestry(ctx, cls, registered):
    """`cls` and every class its canonical record derives from: a registered
    class's bases come from its contract (reverse/class_contracts/<class>.json
    `bases`), else from its own class head in its registered header; a base
    without a record is an ancestor whose own bases are not read. Prepared
    sources and private views are never read."""
    seen, todo = set(), [cls]
    while todo:
        name = todo.pop()
        if name in seen:
            continue
        seen.add(name)
        record = registered.get(name)
        if not record:
            continue
        bases = None
        contract = ctx.read(f"{CLASS_CONTRACTS}/{name}.json")
        if contract:
            try:
                bases = json.loads(contract.decode("utf-8")).get("bases")
            except (ValueError, UnicodeDecodeError, AttributeError):
                bases = None
        if not isinstance(bases, list):
            heads = {}
            _class_heads(heads, (ctx.read(record.get("header", "")) or b"").decode("utf-8", "replace"))
            bases = sorted(heads.get(name, ()))
        todo.extend(b for b in bases if isinstance(b, str) and b and b != UNPARSED_BASE)
    return seen


def this_cv_proof(ctx, rva, old, new, source, prepared):
    """(evidence, slot check) for a `this`-cv-only respell of the row at `rva`;
    Refusal unless the base virtual it overrides at its retail slot has the
    new cv (see the comment above)."""
    at, cls, scopes, role = member_function_header(old)
    if role != "method" or scopes:
        raise Refusal(f"{old}: a this-cv respell reads a method of a global class")
    if old[at] not in VIRTUAL_ACCESS:
        raise Refusal(f"{old} is not virtual: only a base virtual's slot can prove `this`'s cv")
    try:
        refs, type_refs, _names = back_references(old)
    except Unparsed as error:
        raise Refusal(f"cannot read {old} ({error})") from None
    if refs or type_refs:
        raise Refusal(f"{old}'s signature holds a back-reference, whose meaning in a base's spelling differs")
    sources = sorted({source, *(prepared or {})})
    table, slot, slots, installers, proof = to_class_evidence(ctx, rva, cls, sources)
    tables = retail_vtables(ctx)
    # the class's own table: its special members install it through `this`
    bad = receiver_problems(ctx, tables[table][1], installers)
    if bad:
        raise Refusal(f"retail table 0x{table + IMAGE_BASE:08X} is not proved {cls}'s own: {bad[0]}")
    # its ancestry: the canonical record, never a prepared declaration
    registered = {row.get("class"): row for row in ctx.dicts(CANONICAL_CLASSES) if row.get("class")}
    if cls not in registered:
        raise Refusal(f"{cls} has no record in {CANONICAL_CLASSES}: a this-cv respell reads the class's ancestry "
                      "from its canonical record (contract or registered header), never from prepared "
                      "declarations")
    bases = canonical_ancestry(ctx, cls, registered) - {cls}
    ident = old[1:old.index("@")]
    found = []
    for base in sorted(bases & set(registered)):
        for base_table, (base_slots, stores) in sorted(tables.items()):
            if slot >= len(base_slots):
                continue
            own = class_installers(ctx, base, stores, tables)
            if own and not receiver_problems(ctx, stores, [r for r, _d in own]):
                found.append((base, base_table, base_slots[slot]))
    if not found:
        raise Refusal(f"no canonical base in {cls}'s canonical ancestry ({', '.join(sorted(bases)) or 'none'}) "
                      f"installs, through `this`, a retail table with a slot {slot}: the virtual {old} overrides "
                      "is not proved")
    want = new[at + 1]
    proofs = []
    for base, base_table, word in found:
        rows = sorted({r["name"] for r in ctx.rows() if _rva(r.get("target_rva")) == word
                       and r.get("status") == "matched" and not r["name"].startswith(FUNCLET_PREFIXES + ("$L",))
                       and "parent=" not in r.get("notes", "")})
        prefix = f"?{ident}@{base}@@"
        here = f"retail table 0x{base_table + IMAGE_BASE:08X} slot {slot}"
        if not rows:
            raise Refusal(f"{base}'s {here} holds 0x{word:08X}, which is no registered row: the base virtual "
                          f"{old} overrides is not proved")
        same = [n for n in rows if n.startswith(prefix) and len(n) == len(prefix) + len(old) - at
                and n[len(prefix)] in VIRTUAL_ACCESS and n[len(prefix) + 2:] == old[at + 2:]]
        if len(same) != 1:
            raise Refusal(f"{base}'s {here} holds {', '.join(rows)}: not {ident} with {old}'s convention and "
                          "parameters, so it is not the virtual this row overrides")
        base_cv = same[0][len(prefix) + 1]
        if base_cv != want:
            raise Refusal(f"{same[0]} ({base}'s {here}) has `this` cv {base_cv!r}, not {want!r}: {new} would "
                          "not override it")
        proofs.append(f"overrides {same[0]} (0x{word:08X}, {base}'s {here})")
    installer_sources = sorted({r["source"] for r in installers})
    check = {"cls": cls, "table": table, "slot": slot, "new": new, "retail": list(slots),
             "sources": installer_sources, "moved": {new: rva}}
    edited = set(prepared or {})
    early = to_class_slot_problems(ctx, dict(check, sources=[s for s in installer_sources if s not in edited]))
    if early:
        raise Refusal(f"the vftable {cls}'s installers compile does not put {new} in slot {slot}: {early[0]}")
    evidence = f"this-cv: 0x{rva:08X} fills {proof} (stored through `this`); " + "; ".join(proofs)
    return evidence, check


def this_cv_siblings(ctx, rva, proof, also, prepared):
    """[{rva, old, new, source, evidence}] for the --also rows of a this-cv
    respell, each passing the same proof as the primary row (this_cv_proof),
    and `proof`'s slot check widened to every slot: one retail table, judged
    after one build with each slot by the others. Refusal otherwise."""
    check = dict(proof[1], slots={proof[1]["slot"]: proof[1]["new"]}, moved=dict(proof[1]["moved"]))
    rows = ctx.rows()
    seen_rvas, seen_names = {rva}, {proof[1]["new"]}
    out = []
    for at, new in also:
        if at in seen_rvas or new in seen_names:
            raise Refusal("a this-cv --also batch names each RVA and each new name once")
        seen_rvas.add(at)
        seen_names.add(new)
        # the primary row's own checks, so the two cannot drift apart
        old, owner = function_owner(ctx, at)
        if not this_cv_change(old, new):
            raise Refusal(f"--also 0x{at:08X}: {new} is not {old} with only `this`'s cv changed")
        word = split_function_name(old)[1]
        function_identity_checks(ctx, at, old, word, owner)
        function_collision_checks(ctx, at, old, new, word, word, respell=True)
        # the batch edits no pin or body owner of a sibling (the primary's path rewrites them)
        old_re = mangled_re(old)
        if any(old_re.search(p.get("name", "")) for p in ctx.pins()) or \
                old_re.search((ctx.read(BODY_OWNERS) or b"").decode("utf-8", "replace")):
            raise Refusal(f"--also {old} is named by a pin or body_owners.csv: respell it in its own plan")
        evidence, sibling = this_cv_proof(ctx, at, old, new, owner["source"], prepared)
        if (sibling["cls"], sibling["table"]) != (check["cls"], check["table"]):
            raise Refusal(f"--also 0x{at:08X} sits in {sibling['cls']}'s retail table "
                          f"0x{sibling['table'] + IMAGE_BASE:08X}, not 0x{check['table'] + IMAGE_BASE:08X}: a this-cv "
                          "batch respells slots of one retail table")
        if sibling["slot"] in check["slots"]:
            raise Refusal(f"--also 0x{at:08X} sits in slot {sibling['slot']}, which the batch already respells")
        check["slots"][sibling["slot"]] = new
        check["moved"][new] = at
        check["sources"] = sorted(set(check["sources"]) | set(sibling["sources"]))
        out.append(dict(rva=at, old=old, new=new, source=owner["source"], evidence=evidence))
    proof[1].clear()
    proof[1].update(check)
    return out


def check_signature_basis(basis, evidence):
    """A signature-only respell's record: basis `inferred` and evidence `signature-only: <reason>`."""
    if basis != "inferred":
        raise Refusal(f"a signature-only respell is recorded as labelled inference: --basis inferred "
                      f"(got {basis!r})")
    reason = (evidence or "").strip()
    if any(c in reason for c in "\r\n"):
        raise Refusal("--evidence must be one line")
    if not reason.startswith(SIGNATURE_ONLY) or not reason[len(SIGNATURE_ONLY):].strip():
        raise Refusal(f"a signature-only respell needs --evidence '{SIGNATURE_ONLY} <reason>'")
    return "inferred"


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
    every name back-reference the parser meets in a name position, and
    `type_refs` (when set) the digit of every argument-type back-reference
    (a digit where a type is expected: `PAUS@@0@Z`)."""
    refs = None
    type_refs = None
    quals = None      # (when set) the index of every pointer/reference code and of its cv letter


def qualifier_positions(symbol):
    """(qualifier indices, name fragments) of a decorated `?...` symbol, read by the type parser:
    the index of each pointer/reference code (P Q R S A B) where the grammar expects a type, and of
    the cv letter (A B C D) of what it points to. Raises Unparsed outside the parser's subset."""
    out = _Out()
    out.refs, out.type_refs, out.quals = [], [], []
    try:
        end = _parse_symbol(symbol, 0, out)
    except (IndexError, ValueError) as error:
        raise Unparsed(f"{symbol}: {error}") from None
    if symbol[end:]:
        raise Unparsed(f"{symbol}: trailing {symbol[end:]!r}")
    return set(out.quals), [(a, b) for a, b in out]


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


def back_references(symbol):
    """(name back-references, argument-type back-references, name fragments)
    of a decorated `?...` symbol, read by the same parser as `fragments`: a
    digit counts only where the grammar expects a name or a type, never
    inside an identifier (`PBUCoord3D@@` holds none), an enum's `W4` or an
    encoded number. Raises Unparsed outside the parser's subset."""
    out = _Out()
    out.refs, out.type_refs = [], []
    try:
        end = _parse_symbol(symbol, 0, out)
    except (IndexError, ValueError) as error:
        raise Unparsed(f"{symbol}: {error}") from None
    if symbol[end:]:
        raise Unparsed(f"{symbol}: trailing {symbol[end:]!r}")
    return out.refs, out.type_refs, [(a, b) for a, b in out]


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
            elif re.match(r"\?(?:\d|[A-P]+@)\?", s[i:]):    # ?1? / ?BC@? + a nested function symbol
                # a function-local scope: its discriminator is an encoded number (a digit, or
                # hex letters A-P ended by `@`), then the enclosing function's own symbol
                i = _parse_symbol(s, i + re.match(r"\?(?:\d|[A-P]+@)\?", s[i:]).end(), out)
            else:
                raise ValueError(f"scope at {i}")
        elif c.isalpha() or c == "_":
            j = s.index("@", i)
            if not IDENT.fullmatch(s[i:j]):
                raise ValueError(f"fragment {s[i:j]!r}")
            out.append((i, j))
            i = j + 1
        elif c == "$" and re.match(r"\$[A-Za-z0-9_]+@", s[i:]):
            # a compiler-generated name: `?$S4@?7??f@C@@...@4IA` is the guard of a function-local
            # static inside C::f. It names no class or member, so it is no fragment.
            i = s.index("@", i) + 1
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
        code = i
        i += 1
        if s[i] == "E":
            i += 1
        if s[i] not in "ABCD":
            raise ValueError(f"pointer cv at {i}")
        if out.quals is not None:
            out.quals += [code, i]
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
    if c.isdigit():
        if out.type_refs is not None:
            out.type_refs.append(int(c))
        return i + 1
    if c in "CDEFGHIJKMNOXZ":
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


def class_sub(text, word, new, check=None, post=None):
    """`text` with every mangled symbol in it respelling the type fragment
    `word` as `new`; returns (text, count). Raises Unparsed for a symbol that
    spells `word@` and cannot be tokenized. `check(symbol, respelled)` sees
    every symbol it changes (and may raise). `post(respelled)`, when given,
    returns the final spelling of each changed symbol (class --fold --access
    respells the folded class's destructor family there)."""
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
        respelled = "".join(pieces)
        if post is not None:
            respelled = post(respelled)
        if check is not None:
            check(symbol, respelled)
        out += [text[last:match.start()], respelled]
        last = match.end()
        count += len(spans)
    out.append(text[last:])
    return "".join(out), count


class ClassToken:
    """`class_sub` with the interface of a compiled regex (`search`, `sub`,
    `subn`), for the ledger and pragma rewrites."""

    def __init__(self, word, check=None, post=None):
        self.word = word
        self.check = check
        self.post = post

    def subn(self, new, text):
        try:
            return class_sub(text, self.word, new if isinstance(new, str) else new(None), self.check, self.post)
        except Unparsed as error:
            raise Refusal(f"cannot tokenize a mangled name spelling {self.word}: {error}") from None

    def sub(self, new, text):
        return self.subn(new, text)[0]

    def search(self, text):
        try:
            return class_sub(text, self.word, self.word + "\0")[1] > 0
        except Unparsed as error:
            raise Refusal(f"cannot tokenize a mangled name spelling {self.word}: {error}") from None


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
        # how many prepared sources one transaction may carry (--max-prepared)
        self.max_prepared = PREPARED_DEFAULT

    def path(self, rel):
        return self.root / rel

    def read(self, rel):
        path = self.path(rel)
        return path.read_bytes() if path.exists() else None

    def resolution_source_sha(self, rel):
        data = self.read(rel)
        return hashlib.sha256(data).hexdigest() if data is not None else ""

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
    fold: int = None                                  # class --fold: the retail vftable rva proving one class
    fold_tie: dict = None                             # class --fold by retail's initializer: what the build must prove
    fold_layouts: dict = None                         # class --fold, prepared unregistered NEW: each unit's layout
    dropped_pins: list = field(default_factory=list)  # class --fold: (old pin, its respelling, address) removed
    to_class: dict = None                             # function --to-class: the slot the rebuilt vftable must name
    retype: dict = None                               # global --retype: what the rebuilt objects must prove
    registered: dict = None                           # class on a canonical_classes.csv key: what moves with it
    identity: dict = None                             # function --respell --identity: what the rebuilt
                                                      # objects' code-identity scan must prove
    removed: list = field(default_factory=list)       # sources the plan deletes (--move-to empties them)
    this_cv: dict = None                              # function --respell of `this` cv: the slot the rebuilt
                                                      # installers' vftable must name

    def edit(self, ctx, rel, data):
        if rel not in self.before:
            self.before[rel] = ctx.read(rel)
        self.after[rel] = data

    def written(self):
        """Every path this plan writes: the files it edits and where it moves
        sources to (the old paths go with the move)."""
        return set(self.after) | {new for _old, new in self.moves} | set(self.removed)

    def subject(self):
        if self.identity:
            rows = self.identity["rows"]
            what = (f"{self.old} as {self.new}" if len(rows) == 1 else
                    f"{len(rows)} rows ({', '.join(f'0x{at:08X}' for at, _o, _n in rows)})")
            where = f", moved to {self.source}" if self.removed else ""
            if self.identity.get("retail"):
                return f"Respell {what} by retail identity"
            return f"Respell {what} by code identity{where}"
        if self.retype:
            return (f"Retype {self.retype['word']} as {self.retype['type']} "
                    f"({self.retype['size']} B, retail extent verified)")
        if self.virtual:
            return f"Respell {self.old} as virtual {self.new} (retail vtable slot)"
        if self.fold is not None:
            return f"Fold class {self.old} into {self.new} (retail vftable 0x{self.fold + IMAGE_BASE:08X})"
        if self.to_class and len(self.to_class.get("slots") or ()) > 1:
            slots = sorted(self.to_class["slots"])
            return (f"Move {len(slots)} members into {self.to_class['cls']} (retail vftable "
                    f"0x{self.to_class['table'] + IMAGE_BASE:08X} slots {', '.join(map(str, slots))})")
        if self.to_class and self.to_class.get("where"):
            return f"Move {self.old} into {self.to_class['cls']} as {self.new} ({self.to_class['where']})"
        if self.to_class:
            return (f"Move {self.old} into {self.to_class['cls']} as {self.new} "
                    f"(retail vftable 0x{self.to_class['table'] + IMAGE_BASE:08X} slot {self.to_class['slot']})")
        if self.this_cv and len(self.this_cv.get("slots") or ()) > 1:
            slots = sorted(self.this_cv["slots"])
            return (f"Respell `this` cv of {len(slots)} {self.this_cv['cls']} virtuals (retail vftable "
                    f"0x{self.this_cv['table'] + IMAGE_BASE:08X} slots {', '.join(map(str, slots))})")
        if getattr(self, "signature_only", False):
            return f"Respell {self.old} as {self.new} (signature only: qualifiers or pointer-ness)"
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
            if self.virtual or self.fold is not None or self.to_class:
                lines.append(f"  evidence: {self.evidence}")
        for old, new in self.moves:
            lines.append(f"  git mv {old} {new}")
        if self.registered:
            lines.append(f"  registered: {CANONICAL_CLASSES} key {self.registered['old']} -> "
                         f"{self.registered['new']} (header {self.registered['header']} kept)")
            lines += [f"    {what}" for what in self.registered["moved"]]
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
        if self.dropped_pins:
            lines.append(f"  symbols.csv pins dropped (now the row's own name) ({len(self.dropped_pins)}):")
            lines += [f"    {address} {old} (would read {new})" for old, new, address in self.dropped_pins]
        if self.source_counts:
            lines.append(f"  sources rewritten ({len(self.source_counts)}):")
            for rel, counts in sorted(self.source_counts.items()):
                detail = ", ".join(f"{k} {v}" for k, v in counts.items() if v)
                lines.append(f"    {rel} ({detail})")
        if self.removed:
            lines.append(f"  sources removed ({len(self.removed)}): " + " ".join(self.removed))
        if self.identity:
            lines.append(f"  evidence: {self.evidence}")
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


def wb_lead_names(row):
    """A reverse/wb_name_leads.csv row names its address only through a non-empty
    wb_name: most rows (PLACEHOLDER pairings) pair a body and name nothing. The one
    rule for this engine's guard and tools/name_lane.py's queue."""
    return bool(row.get("wb_name"))


def wb_rows(ctx, rva):
    return [r for r in ctx.dicts(WB_LEADS) if _rva(r.get("target_rva")) == rva and wb_lead_names(r)]


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
        if rid.startswith("nr-"):
            source_sha = ctx.resolution_source_sha(parts[0]) if len(parts) == 4 else ""
            expected = "nr-" + hashlib.sha256(
                f"{key}|{row.get('new', '')}|{source_sha}".encode()).hexdigest()[:24]
            if rid != expected:
                problems.append("the source changed after the reviewed resolution")
            else:
                problems = name_agreement.verify_resolution(
                    ctx.dicts(name_agreement.VOTES), ctx.dicts(AGREED),
                    ctx.dicts(name_agreement.RESOLUTIONS), key, row.get("new", ""), source_sha)
        else:
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
    direct = evidence.strip().startswith("direct:")
    if direct and (kind not in ("param", "local") or not re.fullmatch(
            r"direct:nd-[0-9a-f]{24}(?: +[^\r\n]+)?", evidence.strip())):
        raise Refusal("direct: evidence needs a scoped parameter/local nd-<24 hex digits> record")
    if which == "inferred" and not placeholder and not direct:
        raise Refusal(f"{old_word} is a real name, not a placeholder; an inferred name may replace "
                      "only a placeholder or weak name")
    if which == "canonical" and not placeholder and not (recorded or "").startswith("inferred") \
            and not (basis == "canonical:iniblock" and kind == "function"
                     and iniblock_contradiction(ctx, rva, old_word, new_word)):
        raise Refusal(f"{old_word} is a real name that name_basis.csv does not record as inferred; "
                      "a canonical name may replace only a placeholder or an inferred name")
    if which == "inferred":
        inferred_guards(ctx, kind, old_name, old_word, rva)
        if direct:
            pass  # The scoped lane supplies its parent-reviewed record; no shared name enters here.
        elif evidence.strip().startswith("mechanical:"):
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


def inferred_record(evidence):
    """Identity of an agreement-backed or direct scoped inferred landing."""
    match = re.fullmatch(r"agree:(\S+)|direct:(nd-[0-9a-f]{24})(?: +[^\r\n]+)?",
                         (evidence or "").strip())
    return (match.group(1) or match.group(2)) if match else None


def landing(ctx, record):
    """The inferred rename `agree:<record>` landed, not yet restored. Carry
    rows (a renamed class or function respelling this record's scope) are
    followed to its current spelling."""
    rows = name_basis_rows(ctx)
    found = [i for i, r in enumerate(rows) if r.get("basis") == "inferred"
             and inferred_record(r.get("evidence")) == record]
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


def object_referencers(ctx, symbol, *, word=None):
    """Sources whose cached objects reference `symbol` (name_dependents' scan,
    which falls back to the source text where no current object exists).

    `word`: the identifier a source without a current object must spell to
    reference any of the symbols, instead of each symbol's own (bare_identifier).
    A class rename passes its class: every symbol it scopes mangles the class,
    and a unit can reference one only through a declaration that spells it --
    in its own text (searched here) or in a header, which the plan rewrites and
    whose includers it verifies. A member of another class that merely takes
    the class (`?append@Owner@@QAEXPAVOld@@@Z`) would otherwise list every
    stale source spelling `append` (false-reject 0x004E156B, 73eaea475f). A
    current object is read by its exact symbol names either way."""
    if not ctx.object_scan:
        return set()
    import name_dependents
    symbols = {symbol} if isinstance(symbol, str) else set(symbol)
    lookup = getattr(ctx, "_consumer_lookup", None) if word is None else None
    found = (lookup(symbols) if lookup is not None else
             name_dependents.dependents(symbols, name_dependents._row_objects(ctx.rows()), ctx.root,
                                        identifier=None if word is None else (lambda _name: word)))
    if hasattr(ctx, "_object_queries"):
        ctx._object_queries.append((symbols, found, word))
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
        record = inferred_record(row.get("evidence"))
        if row.get("basis") != "inferred" or not record or not row.get("new"):
            continue
        if word_of(row.get("kind", ""), row["new"]) != word:
            continue
        if not any(r.get("basis") == RESTORED and revert_id(r.get("evidence")) == record
                   for r in rows[at + 1:]):
            found.append(record)
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


def function_owner(ctx, rva, old=None):
    """(name, owner row) of the one function name at `rva` (`old` chooses among several)."""
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
    return old_name, owner


def function_identity_checks(ctx, rva, old_name, old_word, owner):
    """Refuse a canonical name (by its spelling or its bare identifier) or a vendored source."""
    reason = is_protected(ctx, "function", old_name, rva=rva, identifier=old_word)
    if reason:
        raise Refusal(f"canonical name: {reason}")
    refuse_vendored(ctx, [owner["source"]], f"renaming {old_name}")


def function_collision_checks(ctx, rva, old_name, new_name, old_word, new_word, *, respell, frozen_ok=frozenset()):
    """Refuse a new name that collides, a local static, an alias pin a respell cannot follow, an
    identifier another function shares (a word rewrite) or a frozen key; the alias pins a word
    rewrite renames too."""
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
    if respell and aliases:
        # An alias pin is the same identity mangled through another unit's view;
        # its own signature change cannot be derived from this one.
        raise Refusal(f"0x{rva:08X} carries the alias pin(s) {', '.join(aliases)}: a respell would have to "
                      "change each one's signature too, which this plan cannot derive")
    for alias in aliases:
        renamed = rename_function_symbol(alias, new_word)
        if any(r["name"] == renamed for r in ctx.rows()) or any(p.get("name") == renamed for p in ctx.pins()):
            raise Refusal(f"{renamed} (the alias pin {alias} renamed) already names a row or pin")
    own_re = re.compile("|".join(mangled_re(n).pattern for n in [old_name] + aliases))
    # A respell runs no word rewrite, so another function sharing the identifier
    # is not at risk from it; the prepared sources are authoritative instead.
    other = None if respell else shared_identifier(ctx, old_word, own_re)
    if other:
        raise Refusal(f"{old_word} also spells {other}; a word rewrite would rename it too")
    frozen = [rel for rel in frozen_mentions(ctx, old_name) if rel not in frozen_ok]
    if frozen:
        raise Refusal(f"{old_name} is a key in {', '.join(frozen)} (frozen, shrink-only); "
                      "renaming it needs a Verifier-Change commit")
    return aliases


def plan_function(ctx, rva, new=None, basis=None, evidence="", *, old=None, max_files=25, virtual=False,
                  to_class=None, prepared=None, access=None, also=None, respell=False, identity=False,
                  move_to=None, move_rows=(), forced_moves=()):
    """Plan respelling one RVA's function identifier everywhere it is named;
    with `virtual`, its decoration from non-virtual to virtual instead
    (plan_virtual: no new identifier, no basis, retail evidence); with
    `to_class`, moving a placeholder-class member into that class as its
    virtual (plan_to_class: retail vftable evidence, prepared C++)."""
    if to_class:
        if basis:
            raise Refusal("--to-class takes its evidence from retail's vftable: pass no --basis")
        return plan_to_class(ctx, rva, to_class, new, evidence=evidence, old=old, prepared=prepared,
                             max_files=max_files, also=also)
    if identity or move_to:
        if not respell or identity is False:
            raise Refusal("--identity and --move-to go with --respell --identity only")
        if basis == "retail":
            return plan_retail_respell(ctx, rva, new, old=old, prepared=prepared, also=also, move_to=move_to,
                                       move_rows=move_rows, forced_moves=forced_moves, evidence=evidence,
                                       max_files=max_files)
        if move_rows:
            raise Refusal("--move-rows goes with --basis retail only")
        if forced_moves:
            raise Refusal("--forced-move goes with --basis retail only")
        return plan_identity_respell(ctx, rva, new, old=old, prepared=prepared, also=also, move_to=move_to,
                                     basis=basis, evidence=evidence, max_files=max_files)
    if also and not respell:
        raise Refusal("--also adds slots of one retail table to a --to-class move only")
    if prepared and not (virtual or respell):
        raise Refusal("--prepared sources go with --to-class, --virtual or --respell only")
    if access is not None and not virtual:
        raise Refusal("--access goes with --virtual only")
    if virtual:
        if new or basis:
            raise Refusal("--virtual keeps the identifier and takes its evidence from retail: "
                          "pass neither a new name nor a basis")
        return plan_virtual(ctx, rva, evidence=evidence, old=old, max_files=max_files, prepared=prepared,
                            access=access)
    old_name, owner = function_owner(ctx, rva, old)
    prefix, old_word, _ = split_function_name(old_name)
    new = new or ""
    # --respell: `new` is the row's whole name even where it differs beyond the
    # identifier, and the prepared C++ carries the change the word rewrite below
    # cannot express.
    literal = ""
    if new.startswith("?"):
        # a full mangled spelling: it must equal the identifier-only rewrite
        new_word = split_function_name(new)[1]
        if new_word == old_word and not respell:
            raise Refusal("the new name is the old name")
        if rename_function_symbol(old_name, new_word) != new:
            if not respell:
                raise Refusal(f"{new} changes the mangled signature beyond the identifier "
                              f"(identifier-only rewrite is {rename_function_symbol(old_name, new_word)}; "
                              "--respell with --prepared sources carries a signature change)")
            literal = new
    else:
        new_word = new
        if respell:
            raise Refusal("--respell needs --new as the row's whole mangled name, not an identifier")
    check_new_identifier(new_word, "function", basis)
    if respell:
        if not literal:
            raise Refusal(f"{new} is the identifier-only rewrite of {old_name}; "
                          "rename it with function --new alone, without --respell")
        if not prepared:
            raise Refusal("--respell needs --prepared sources for every unit whose C++ must change, "
                          "since no word rewrite can change a return type, parameter or template argument")
    elif new_word == old_word:
        raise Refusal("the new name is the old name")
    new_name = literal or rename_function_symbol(old_name, new_word)

    signature_only = respell and new_word == old_word
    this_cv, siblings = None, []
    function_identity_checks(ctx, rva, old_name, old_word, owner)
    if signature_only:
        # The same function, the same identifier: no naming claim. Only a parameter's or the return
        # type's cv-qualifier or pointer-ness changes, the prepared units are rebuilt byte-exact, and
        # the record is labelled inference with its reason.
        if this_cv_change(old_name, new_name):
            # only `this`'s cv: proved by the base virtual the row overrides at its retail slot
            this_cv = this_cv_proof(ctx, rva, old_name, new_name, owner["source"], prepared)
            if also:
                # siblings: the same proof each, every slot judged after one build
                siblings = this_cv_siblings(ctx, rva, this_cv, also, prepared)
        else:
            signature_only_change(old_name, new_name)
        which = check_signature_basis(basis, evidence)
    else:
        which = check_basis(ctx, "function", basis, evidence, old_name, old_word, rva, new_name=new_name,
                            new_word=new_word)
    if also and not this_cv:
        raise Refusal("--also with --respell (no --identity) adds rows to a this-cv respell only")

    old_re = mangled_re(old_name)
    aliases = function_collision_checks(ctx, rva, old_name, new_name, old_word, new_word, respell=respell)
    tombstoned = _tombstones(ctx)
    own_re = re.compile("|".join(mangled_re(n).pattern for n in [old_name] + aliases))

    plan = Plan("function", old_name, new_name, basis, evidence.strip(), owner["source"], rva,
                old_word=old_word, new_word=new_word)
    plan.signature_only = signature_only
    if signature_only and this_cv:
        plan.evidence = "; ".join([plan.evidence, this_cv[0]] + [f"0x{b['rva']:08X}: {b['evidence']}"
                                                                  for b in siblings])
        plan.this_cv = this_cv[1]

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
    for b in siblings:
        new_raw, changed = rewrite_records(new_raw, "functions.csv", mangled_re(b["old"]), b["new"])
        for before, after in changed:
            if before[0] != after[0]:
                plan.renamed_rows.append((before[0], after[0], _rva(before[2])))
            else:
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
        ["function", old_name, new_name, basis, plan.evidence, owner["source"], f"0x{rva:08X}"])] + [csv_line(
            ["function", b["old"], b["new"], basis, plan.evidence, b["source"], f"0x{b['rva']:08X}"])
            for b in siblings],
        header=NAME_BASIS_HEADER))

    old_scope, new_scope = scope_of(old_name), scope_of(new_name)

    def carried(spelling):
        if old_re.search(spelling):
            return old_re.sub(lambda _m: new_name, spelling)
        if old_scope and new_scope and re.match(re.escape(old_scope) + r"(?:#\d+)?::", spelling):
            return new_scope + spelling[len(old_scope):]
        return None
    carry_records(ctx, plan, carried)
    for b in siblings:
        # its own spelling is recorded by its function line, as the primary row's is
        carry_records(ctx, plan, lambda spelling, b=b: mangled_re(b["old"]).sub(lambda _m: b["new"], spelling)
                      if spelling != b["old"] and mangled_re(b["old"]).search(spelling) else None)
    scope = scope_of(old_name) or ""
    if respell:
        # The prepared C++ is the whole source change: a word rewrite cannot turn
        # `Object *` into `Drawable *` or `BitFlags<304>` into `BitFlags<591>`.
        # Nothing may be left spelling the old name, in a prepared unit or out of
        # it, or the ledger and the source would disagree about this address.
        _batch_source_edits(ctx, plan, prepared)
        verify = set(prepared) | set((plan.this_cv or {}).get("sources", ()))
        left = sorted(rel for rel, data in plan.after.items()
                      if rel in prepared and mangled_re(old_name).search(data.decode("utf-8", "replace")))
        if left:
            raise Refusal(f"prepared {', '.join(left)} still spells {old_name}")
        for spelled in [old_name] + [b["old"] for b in siblings]:
            left = sorted(rel for rel, data in plan.after.items()
                          if rel in prepared and mangled_re(spelled).search(data.decode("utf-8", "replace")))
            if left:
                raise Refusal(f"prepared {', '.join(left)} still spells {spelled}")
            elsewhere = sorted(set(ctx.grep_files(spelled, roots=("Code",))) - set(prepared))
            if elsewhere:
                raise Refusal(f"{', '.join(elsewhere[:4])} still spells {spelled}: prepare every unit that "
                              "names it, so no source disagrees with the respelled row")
    else:
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
        [f"file:{src}" for src in sorted({owner["source"]} | {b["source"] for b in siblings})]
    edited = set(plan.after) | {"reverse/re_attempts.log"}
    plan.mentions = sorted({m for spelled in [old_name] + [b["old"] for b in siblings]
                            for m in ctx.grep_files(spelled, roots=("docs", "reverse"))} - edited) + \
        sorted(set(ctx.grep_files(old_word, word=True, roots=("docs",))) - edited
               - set(ctx.grep_files(old_name, roots=("docs",))))
    return plan


# ---------------------------------------------------------------- code-identity respell
#
# `function --respell --identity` respells a compiler-spelled row (an operator,
# special member or template member) whose old spelling names a placeholder type
# and whose bytes already match retail while its calls bind the wrong code: a row
# typed `map<Placeholder, int>` whose retail body calls the rowed clear and
# _M_copy of `_Rb_tree<Record, ..., _Identity>` compiles to the same bytes, yet
# its calls bind local COMDATs of the wrong instantiation. Which spelling is right
# is a naming judgement -- a callee's class does not prove the caller's (`mov
# ecx,[ecx+4]; call clear` acts on a contained object) -- so the new spelling
# comes from the naming route: --basis inferred, --evidence agree:<id> for every
# row, two blind votes on the row's own key (its current source, kind, address
# and placeholder: docs/naming.md). Only placeholder names and the vendored
# STLport namespace's names (a qualified name under `_STL` that the vendored
# STLport headers declare: map, set, _Rb_tree, pair, ...) may change; every other
# real name -- project classes, global types, scope and member identifiers --
# keeps its qualified path and its place in the decoded type tree (back-references
# resolved), and a canonical class is never replaced, wherever it appears. The
# code-identity checks are hard gates on top:
#
#   1. before: the identity scan of a respelled row reports a wrong binding, or
#      the row calls another row the same plan respells;
#   2. no callee is ICF-marked or carries two names, and a callee pin refuses
#      unless it is the old-type spelling the respell retires (below);
#   3. after (./build.sh exact on every unit the plan touches): every reference
#      of every respelled row binds its retail owner directly (no alias, fold,
#      pin or ICF-marked callee), and no row in a touched source gains a wrong
#      binding;
#   4. the new mangled name is owned by no row or pin, and both spellings are
#      compiler-spelled with the same operator code or identifier (the primary
#      row checks of plan_function run on every row).
#
# A callee pin spelling the callee under the respelled row's old class (the
# symbol the old object binds there) is retired only when no object outside the
# rebuilt units references it. Every object the real link takes (exit_link's own
# inventory: function and data providers) is parsed whole -- symbol table, weak
# externals and .drectve (/alternatename, /INCLUDE); a missing object or one that
# does not parse refuses; a stale object whose source, or a header it includes, spells the pin
# or one of its placeholder types is rebuilt with ./build.sh first (refused when
# it cannot be). The rebuilt units' objects are read again after the build.
# `--move-to TU` also moves the respelled rows to their approved TU (the map
# rebuilt in memory from current inputs when the committed one is stale): every
# row of the owner source must be in the plan, its path-keyed columns follow, and
# the emptied source is deleted.

IDENTITY = "code-identity:"
COMPILER_HEAD = re.compile(r"\?\?(_?[0-9A-Z])|\?([A-Za-z_]\w*)@")
AGREE_TOKEN = re.compile(r"agree:[A-Za-z0-9_.:-]+")


# non-static member access codes (private, protected, public; plain and virtual;
# near and far): with `this` cv and convention E they are a thiscall member
THIS_CALL_ACCESS = frozenset("ABEFIJMNQRUV")


def identity_scope(mangled, i):
    """(elements, class template arguments, index after the scope's `@`) of the
    qualified scope at `i`, or None. Each element is its text as spelled (an
    identifier with its `@`, a template with its argument list), innermost first;
    the class template arguments are the innermost element's. A name
    back-reference, anonymous namespace or nested symbol in the scope is refused
    rather than resolved: two scopes compare by their spelling."""
    elements, args = [], ()
    out = _Out()
    try:
        while mangled[i] != "@":
            if mangled.startswith("?$", i):
                j = mangled.index("@", i + 2)
                if not IDENT.fullmatch(mangled[i + 2:j]):
                    return None
                k, these = j + 1, []
                while mangled[k] != "@":
                    end = _parse_type(mangled, k, out)
                    these.append(mangled[k:end])
                    k = end
                if not elements:
                    args = tuple(these)
                elements.append(mangled[i:k + 1])
                i = k + 1
            elif mangled[i].isalpha() or mangled[i] == "_":
                j = mangled.index("@", i)
                if not IDENT.fullmatch(mangled[i:j]):
                    return None
                elements.append(mangled[i:j + 1])
                i = j + 1
            else:
                return None
    except (IndexError, ValueError):
        return None
    return tuple(elements), args, i + 1


def identity_head(mangled):
    """The operator code (`??4` -> '??4') or identifier of a compiler-spelled
    name, or None for a hand-written one: no `??` code, and no template in the
    scope (a free function taking a template type is hand-written)."""
    match = COMPILER_HEAD.match(mangled or "")
    if not match:
        return None
    if match.group(1):
        return "??" + match.group(1)
    scope = identity_scope(mangled, match.end())
    return match.group(2) if scope and any(el.startswith("?$") for el in scope[0]) else None


def identity_class(mangled):
    """(scope elements, class template arguments) of a thiscall member's
    decorated name, or None for anything else (a free or static function, a
    scope identity_scope will not read, a name the parser refuses)."""
    match = COMPILER_HEAD.match(mangled or "")
    if not match:
        return None
    scope = identity_scope(mangled, match.end())
    if not scope or not scope[0]:
        return None
    try:
        back_references(mangled)
    except Unparsed:
        return None
    elements, args, i = scope
    if i >= len(mangled) or mangled[i] not in THIS_CALL_ACCESS:
        return None
    i += 1
    if mangled[i:i + 1] == "E":
        i += 1
    if mangled[i:i + 1] not in ("A", "B", "C", "D") or mangled[i + 1:i + 2] != "E":
        return None
    return elements, args


STL_NAMESPACE = "_STL"
STLPORT_HEADERS = "vendor/stlport-4.6/stlport"   # the pristine STLport 4.6 retail linked


class _TypeTree:
    """A decorated `?...` symbol decoded into a tree whose back-references are
    resolved to the subtree they name: ("Q", elements) a qualified name, innermost
    element first, each ("N", name) or ("T", name, (argument types...)); ("C",
    code, Q) a class, struct, union or enum; ("P", code, cv, type) a pointer or
    reference; ("B", code) a builtin; ("F", return, (arguments...), throw) a
    function signature; and the special forms the grammar has. Each template
    argument list has its own name table (the template's name is entry 0) and type
    table. Outside the grammar it reads (anonymous namespaces, nested symbols,
    template operators): ValueError."""

    def __init__(self, s):
        self.s = s

    def symbol(self, i, ctx):
        s = self.s
        if s[i] != "?":
            raise ValueError(f"symbol expected at {i}")
        i += 1
        head = ""
        if s[i] == "?" and s[i + 1] != "$":
            i += 1
            if s[i] == "_":
                if s.startswith(("__", "_R"), i):
                    raise ValueError("special name")
                head, i = "??" + s[i:i + 2], i + 2
            else:
                head, i = "??" + s[i], i + 1
        i, scope = self.qualified(i, ctx)
        i, header = self.header(i, ctx)
        return i, ("SYM", head, scope, header)

    def qualified(self, i, ctx):
        s = self.s
        elements = []
        while True:
            c = s[i]
            if c == "@":
                return i + 1, ("Q", tuple(elements))
            if c.isdigit():
                elements.append(ctx["names"][int(c)])
                i += 1
            elif s.startswith("?$", i):
                if s[i + 2] == "?":
                    raise ValueError("template operator")
                j = s.index("@", i + 2)
                name = s[i + 2:j]
                inner = {"names": [("N", name)], "types": []}
                i, args = self.arguments(j + 1, inner, "@")
                element = ("T", name, args)
                elements.append(element)
                if len(ctx["names"]) < 10:
                    ctx["names"].append(element)
            elif c.isalpha() or c == "_":
                j = s.index("@", i)
                element = ("N", s[i:j])
                elements.append(element)
                if len(ctx["names"]) < 10:
                    ctx["names"].append(element)
                i = j + 1
            else:
                raise ValueError(f"scope at {i}")

    def arguments(self, i, ctx, stop):
        """Types up to `stop` (`@` ends a template's list, `@`/`Z` a function's)."""
        out = []
        while self.s[i] not in stop:
            start = i
            i, node = self.type(i, ctx)
            if i - start > 1 and len(ctx["types"]) < 10:
                ctx["types"].append(node)
            out.append(node)
        return i + 1, tuple(out)

    def function(self, i, ctx):
        s = self.s
        if s[i] == "@":
            ret, i = ("B", "@"), i + 1
        else:
            i, ret = self.type(i, ctx)
        if s[i] == "X":
            args, i = ("ARGS", ("B", "X")), i + 1
        else:
            i, nodes = self.arguments(i, ctx, "@Z")
            args = ("ARGS",) + nodes + ((("B", "..."),) if s[i - 1] == "Z" else ())
        if s[i] != "Z":
            raise ValueError(f"throw spec at {i}")
        return i + 1, ("F", ret, args)

    def type(self, i, ctx):
        s = self.s
        c = s[i]
        if c in "PQRSAB" and s[i + 1] == "6":
            code = s[i:i + 3]
            j, fn = self.function(i + 3, ctx)
            return j, ("FP", code, fn)
        if c in "PQRSAB" and s[i + 1] == "8":
            pointer = s[i:i + 2]
            j, scope = self.qualified(i + 2, ctx)
            code = s[j:j + 2]
            j, fn = self.function(j + 2, ctx)
            return j, ("MP", pointer, scope, code, fn)
        if c in "PQRSAB":
            j = i + 1
            if s[j] == "E":
                j += 1
            if s[j] not in "ABCD":
                raise ValueError(f"pointer cv at {j}")
            code = s[i:j + 1]
            j, inner = self.type(j + 1, ctx)
            return j, ("P", code, inner)
        if c in "VUT":
            j, scope = self.qualified(i + 1, ctx)
            return j, ("C", c, scope)
        if c == "W" and s[i + 1].isdigit():
            j, scope = self.qualified(i + 2, ctx)
            return j, ("C", s[i:i + 2], scope)
        if c == "?" and s[i + 1] in "AB":
            j, inner = self.type(i + 2, ctx)
            return j, ("CV", s[i:i + 2], inner)
        if c == "_" and s[i + 1].isalpha():
            return i + 2, ("B", s[i:i + 2])
        if s.startswith("$$C", i) and s[i + 3] in "ABCD":
            j, inner = self.type(i + 4, ctx)
            return j, ("CV", s[i:i + 4], inner)
        if s.startswith("$0", i):
            j = _parse_number(s, i + 2)
            return j, ("B", s[i:j])
        if s.startswith(("$1", "$E"), i):
            j, sym = self.symbol(i + 2, {"names": [], "types": []})
            return j, ("ADDR", s[i:i + 2], sym)
        if c == "Y":
            count, j = _number_value(s, i + 1)
            for _ in range(count):
                j = _parse_number(s, j)
            dims = s[i:j]
            j, inner = self.type(j, ctx)
            return j, ("Y", dims, inner)
        if c.isdigit():
            return i + 1, ctx["types"][int(c)]
        if c in "CDEFGHIJKMNOXZ":
            return i + 1, ("B", c)
        raise ValueError(f"type {c!r} at {i}")

    def header(self, i, ctx):
        s = self.s
        if i == len(s):
            return i, ("H", "")
        c = s[i]
        if c in "01234":
            j, node = self.type(i + 1, ctx)
            k = j + (1 if s[j] == "E" else 0)
            if s[k] not in "ABCD":
                raise ValueError(f"data cv at {k}")
            return k + 1, ("H", c + s[j:k + 1], node)
        if c in "YZCDKLST":
            j, fn = self.function(i + 2, ctx)
            return j, ("H", s[i:i + 2], fn)
        if c in "ABEFIJMNQRUV":
            j = i + 1 + (1 if s[i + 1] == "E" else 0)
            code = s[i:j + 2]
            j, fn = self.function(j + 2, ctx)
            return j, ("H", code, fn)
        if c in "GHOPWX":
            j = _parse_number(s, i + 1)
            code = s[i:j + 2]
            j, fn = self.function(j + 2, ctx)
            return j, ("H", code, fn)
        raise ValueError(f"header {c!r} at {i}")


def type_tree(mangled):
    """The decoded tree of `mangled` (see _TypeTree). Raises Unparsed."""
    try:
        end, node = _TypeTree(mangled).symbol(0, {"names": [], "types": []})
    except (IndexError, ValueError) as error:
        raise Unparsed(f"{mangled}: {error}") from None
    if end != len(mangled):
        raise Unparsed(f"{mangled}: trailing {mangled[end:]!r}")
    return node


C_NOISE = re.compile(r'/\*.*?\*/|//[^\n]*|"(?:\\.|[^"\\\n])*"|\'(?:\\.|[^\'\\\n])*\'', re.S)
# a preprocessor line with its continuations: removed whole, so a declaration split by
# `#ifdef ... #endif` reads as both branches together, and a macro body declares nothing
C_DIRECTIVE = re.compile(r"^[ \t]*#(?:[^\n]*\\\n)*[^\n]*", re.M)
# a class, struct or union declared or defined (`{`, `;`, a base clause or a specialization's
# `<` follows the name; a template parameter's `class T` is followed by `,`, `>` or `=`)
STLPORT_RECORD = re.compile(r"\b(?:class|struct|union)\s+(?:_STLP_\w+\s+)*([A-Za-z_]\w*)\s*(?=[{;:<])")
# a plain typedef names the identifier before its `;` (or array bound) -- unless a `)` comes
# right before it: that is a function or member-pointer declarator's trailing cv, whose name is
# read below (`typedef int (Owner::*Callback)() const;` declares Callback, not const)
STLPORT_TYPEDEF = re.compile(r"\btypedef\b[^;{}]*?\b([A-Za-z_]\w*)\s*(?:\[[^\]]*\]\s*)?;")
# `typedef R (*name)(...)` and `typedef R (Owner::*name)(...) const`: the declarator in parentheses
STLPORT_FN_TYPEDEF = re.compile(r"\btypedef\b[^;{}]*?\(\s*(?:_STLP_\w+\s*)*"
                                r"(?:[A-Za-z_]\w*\s*(?:<[^;{}()]*>)?\s*::\s*)*\*\s*([A-Za-z_]\w*)\s*\)\s*\(")
C_CONTINUATION = re.compile(r"\\\r?\n")
# never a declared name: a last guard behind the patterns above
C_KEYWORDS = frozenset("""
    auto bool break case catch char class const const_cast continue default delete do double
    dynamic_cast else enum explicit extern false float for friend goto if inline int long mutable
    namespace new operator private protected public register reinterpret_cast return short signed
    sizeof static static_cast struct switch template this throw true try typedef typeid typename
    union unsigned using virtual void volatile wchar_t while""".split())
# The pin: sha256 and file count of the public headers (stlport_files: the files in stlport/
# itself and everything under stlport/stl/, as sorted relative paths, lengths and contents),
# kept in a hook-protected data file (tools/protected_paths.py): the vendored tree the index
# trusts. Neither git history nor refs are read; a change to these headers moves the pin in its
# own reviewed (Verifier-Change) commit.
STLPORT_MANIFEST = "reverse/stlport_manifest.txt"


def stlport_names(text):
    """The record and typedef names `text` declares: line continuations joined, then
    comments, string literals and preprocessor lines stripped; never a keyword."""
    # line continuations join first (a `//` comment or a directive continued onto the next
    # line swallows it), then comments and literals go, then preprocessor lines
    code = C_DIRECTIVE.sub(" ", C_NOISE.sub(" ", C_CONTINUATION.sub("", text)))
    names = set(STLPORT_RECORD.findall(code)) | set(STLPORT_FN_TYPEDEF.findall(code))
    names |= {m.group(1) for m in STLPORT_TYPEDEF.finditer(code) if not code[:m.start(1)].rstrip().endswith(")")}
    return names - C_KEYWORDS


def stlport_files(ctx):
    """[(path relative to the headers, bytes)] of the public headers STLport ships for
    inclusion: the files in stlport/ itself and everything under stlport/stl/ -- never
    config/, configure scripts, tests or the other compilers' trees."""
    root = ctx.path(STLPORT_HEADERS)
    found = []
    if root.is_dir():
        found += [path for path in root.iterdir() if path.is_file()]
        if (root / "stl").is_dir():
            found += [path for path in (root / "stl").rglob("*") if path.is_file()]
    return sorted((path.relative_to(root).as_posix(), path.read_bytes()) for path in found)


def stlport_manifest(files):
    digest = hashlib.sha256()
    for rel, data in files:
        digest.update(rel.encode() + b"\0" + str(len(data)).encode() + b"\0" + data)
    return digest.hexdigest()


def stlport_pin(ctx):
    """(sha256, file count) the protected STLPORT_MANIFEST file pins; Refusal when it is
    missing or not exactly `sha256 <64 hex>` and `files <count>`."""
    text = (ctx.read(STLPORT_MANIFEST) or b"").decode("ascii", "replace")
    match = re.fullmatch(r"sha256 ([0-9a-f]{64})\nfiles ([1-9][0-9]*)\n", text)
    if not match:
        raise Refusal(f"{STLPORT_MANIFEST} is missing or not `sha256 <hex>` and `files <count>`: the STLport "
                      "index has no pin")
    return match.group(1), int(match.group(2))


def stlport_declared(ctx):
    """Every class, struct, union and typedef name the vendored STLport public headers declare,
    read from disk once their manifest and count equal the pin (stlport_pin); Refusal otherwise."""
    key = "_stlport_declared"
    if key not in ctx._cache:
        files = stlport_files(ctx)
        got = stlport_manifest(files)
        pinned, count = stlport_pin(ctx)
        if (got, len(files)) != (pinned, count):
            raise Refusal(f"{STLPORT_HEADERS}'s public headers ({len(files)} files) hash to {got[:16]}, not the "
                          f"pinned {pinned[:16]} ({count} files, {STLPORT_MANIFEST}): the STLport index is read "
                          "only from the pinned tree")
        names = set()
        for _rel, data in files:
            names |= stlport_names(data.decode("latin-1"))
        ctx._cache[key] = frozenset(names)
    return ctx._cache[key]


def _tree_stl_scoped(q):
    return bool(q[1]) and q[1][-1] == ("N", STL_NAMESPACE)


def _tree_names(node, inside_stl=False):
    """[(name, STLport-scoped)] of every name a node spells, scope and template names included."""
    out = []
    if isinstance(node, tuple) and node and node[0] == "Q":
        stl = _tree_stl_scoped(node)
        for element in node[1]:
            out.append((element[1], stl))
            if element[0] == "T":
                for arg in element[2]:
                    out += _tree_names(arg)
        return out
    if isinstance(node, tuple):
        for child in node[1:]:
            out += _tree_names(child)
    return out


def identity_shape_problem(old, new, canonical=frozenset(), stlport=frozenset()):
    """None when `new` changes only what an identity respell may change against `old`,
    comparing the decoded trees (back-references resolved). A protected name -- a
    registered canonical class anywhere, or any name that is neither a placeholder
    nor STLport-scoped (a qualified name under `_STL`) -- keeps its exact qualified
    path and its place in the tree: the argument index and the nesting depth. A
    subtree may differ only where it is a placeholder class or an `_STL`-scoped name
    with no protected name inside; a single placeholder or `_STL`-scoped element of
    a qualified name may be renamed in place. Every `_STL`-scoped name that changes
    must be declared in the vendored STLport headers. Anything else that differs --
    a scope, a code, an argument count, a nesting -- refuses. Else why not."""
    try:
        a, b = type_tree(old), type_tree(new)
    except Unparsed as error:
        return f"its names cannot be read ({error})"
    changed = set()

    def protected(name, stl):
        return name in canonical or (not stl and not name_metric.placeholder(name))

    def free(node):
        """May `node` be replaced whole: a placeholder class or an _STL-scoped name, nothing protected inside."""
        q = node[2] if node[0] == "C" else node if node[0] == "Q" else None
        if q is None or not q[1]:
            return False
        names = _tree_names(q)
        if any(protected(n, s) for n, s in names):
            return False
        return _tree_stl_scoped(q) or (len(q[1]) == 1 and q[1][0][0] == "N" and name_metric.placeholder(q[1][0][1]))

    def describe(node):
        return ", ".join(n for n, _s in _tree_names(node)[:4]) or node[0]

    def compare(x, y, where):
        if x == y:
            return None
        if isinstance(x, tuple) and x and x[0] in ("C", "Q") and free(x) and \
                (x[0] == y[0] if x[0] == "Q" else isinstance(y, tuple) and y and y[0] == "C"):
            changed.update(n for n, s in _tree_names(x) + _tree_names(y) if s)
            return None
        if not (isinstance(x, tuple) and isinstance(y, tuple)) or x[0] != y[0] or len(x) != len(y):
            return f"its shape differs at {where} ({describe(x) if isinstance(x, tuple) else x!r})"
        if x[0] == "Q":
            if len(x[1]) != len(y[1]):
                return f"the qualified name {describe(x)} at {where} changes its scope"
            stl = _tree_stl_scoped(x) and _tree_stl_scoped(y)
            # from a protected name outward (its scopes), every element is its path
            guarded = next((d for d, e in enumerate(x[1]) if protected(e[1], _tree_stl_scoped(x))), None)
            for depth, (e, f) in enumerate(zip(x[1], y[1])):
                spot = f"{where} element {depth}"
                if e[0] != f[0]:
                    return f"its shape differs at {spot} ({e[1]})"
                if guarded is not None and depth > guarded and e != f:
                    return (f"it changes the enclosing scope {e[1]} of the protected name {x[1][guarded][1]} "
                            f"(its name or template arguments, {spot})")
                if e[1] != f[1]:
                    if protected(e[1], stl):
                        kind = "canonical class" if e[1] in canonical else "real name"
                        return f"it replaces the {kind} {e[1]} with {f[1]} ({spot})"
                    if stl:
                        changed.update((e[1], f[1]))
                if e[0] == "T":
                    if len(e[2]) != len(f[2]):
                        return f"the template {e[1]} at {spot} changes its argument count"
                    for index, (g, h) in enumerate(zip(e[2], f[2])):
                        why = compare(g, h, f"{spot} argument {index}")
                        if why:
                            return why
            return None
        for index, (g, h) in enumerate(zip(x[1:], y[1:])):
            if isinstance(g, tuple) and isinstance(h, tuple):
                why = compare(g, h, f"{where}/{x[0]}{index}")
                if why:
                    return why
            elif g != h:
                return f"its shape differs at {where} ({x[0]}: {g!r} -> {h!r})"
        return None

    why = compare(a, b, "the root")
    if why:
        return why
    undeclared = sorted(n for n in changed - {STL_NAMESPACE} if n not in stlport)
    if undeclared:
        return (f"it changes the _STL-scoped name(s) {', '.join(undeclared[:4])}, which the vendored STLport "
                f"headers ({STLPORT_HEADERS}) do not declare: `_STL` is reopened in this codebase, so the "
                "decoration alone does not prove STLport")
    return None


def placeholder_types(mangled):
    """The placeholder identifiers (Rva.../Bfme... and name_metric's other
    placeholder shapes) among the name fragments of `mangled`."""
    try:
        spans = fragments(mangled)
    except Unparsed:
        return []
    return sorted({mangled[a:b] for a, b in spans if name_metric.placeholder(mangled[a:b])})


def identity_refs(ctx, sources):
    """[{source, row, rva, symbol, target, cls}] for every reference of the rows
    in `sources`, classified by tools/allowed_symbols.py against the tree's
    current ledger and objects. Tests replace this through ctx.identity_refs."""
    hook = getattr(ctx, "identity_refs", None)
    if hook:
        return hook(sorted(sources))
    import allowed_symbols as allowed
    ident, rows = allowed.load(sorted(sources))
    return [dict(source=row["source"], row=row["name"], rva=_rva(row.get("target_rva")), symbol=name,
                 target=target, cls=cls, detail=detail)
            for row, _offset, _kind, name, target, cls, detail in allowed.scan(ident, rows)]


def identity_wrong(refs):
    import allowed_symbols as allowed
    return [r for r in refs if r["cls"] in allowed.WRONG]


def _identity_key(ref, renames):
    """A wrong binding's key (source, row, referenced symbol, target, class: the
    identity register's) with the plan's renames applied (old -> new)."""
    return (ref["source"], renames.get(ref["row"], ref["row"]), ref["rva"],
            renames.get(ref["symbol"], ref["symbol"]), ref["target"], ref["cls"])


def identity_direct(ref):
    """A reference bound straight to retail's row (`owner`), or the row's own
    handler or same-section label; an alias, fold or anything else is not."""
    return ref["cls"] in ("owner", "eh") or (ref["cls"] == "label" and not ref.get("detail"))


def callee_marks(rows):
    """({rva: function names}, {rva: notes}) of the ledger's function rows (funclets left out)."""
    named, notes = collections.defaultdict(set), collections.defaultdict(list)
    for r in rows:
        if r["name"].startswith(FUNCLET_PREFIXES + ("$L",)) or "parent=" in r.get("notes", ""):
            continue
        at = _rva(r.get("target_rva"))
        named[at].add(r["name"])
        notes[at].append(r.get("notes", ""))
    return named, notes


def folded_callee(named, notes, at):
    """Why the callee at `at` proves no one name (ICF notes or two names), or None."""
    if len(named.get(at, ())) > 1:
        return f"names {', '.join(sorted(named[at]))}"
    marked = [n for n in notes.get(at, ()) if FOLD_NOTES.search(n)]
    return f"ICF-marked ({marked[0][:80]})" if marked else None


# ---- the objects that could still reference a retired pin

def link_objects(ctx):
    """{source: [object paths]} of every object the real link takes: tools/exit_link.py's own
    inventory (expected_objects: each matched functions.csv row's object and each data_rows.csv
    provider's), less the placement-only objects its link_setup leaves out. An object no source
    names (a vendored library member) is keyed by its file name."""
    if ctx.root.resolve() != ROOT.resolve():
        raise Refusal("the real link's object inventory is read from the repository itself")
    import exit_link
    import link_census
    rows = link_census.ledger()
    omitted = set(exit_link.placement_objects(rows))
    sources = link_census._object_sources(rows)
    out = collections.defaultdict(list)
    for path in exit_link.expected_objects(rows):
        if path in omitted:
            continue
        source = sources.get(path)
        key = Path(os.path.relpath(source, ROOT)).as_posix() if source else f"({path.name})"
        out[key].append(path)
    return dict(out)


def source_objects(ctx, sources):
    """{source: [object path]} of the units the plan rebuilds (build.obj_path, as the link names them)."""
    import build
    return {src: [build.obj_path(ctx.path(src))] for src in sources}


def object_is_current(ctx, source, path):
    """build.compile_is_current: the object was compiled from the source's text and every header it read."""
    import build
    if source.lower().endswith(build.LIB_SUFFIX):
        return True
    try:
        return build.compile_is_current(ctx.path(source), Path(path))
    except (OSError, ValueError, SystemExit):
        return False


def rebuild_sources(ctx, sources):
    """./build.sh over `sources`, the normal build path; True when it passed."""
    try:
        result = subprocess.run(["./build.sh", *sources], cwd=str(ctx.root), capture_output=True, text=True)
    except OSError:                      # no build here: nothing was rebuilt
        return False
    return result.returncode == 0


PIN_INCLUDE_LINE = r'^[ \t]*#[ \t]*include[ \t]*[<"](?:[^>"\r\n]*[/\\])?%s[>"]'


def mentioning_sources(ctx, words):
    """Tracked Code files that spell one of `words`, and every file that includes
    one of those (by file name, case-insensitively, transitively)."""
    seen = set()
    for word in words:
        seen |= set(ctx.grep_files(word, roots=("Code",)))
    frontier = set(seen)
    while frontier:
        names = sorted({Path(rel).name for rel in frontier})
        frontier = set()
        for name in names:
            line = re.compile(PIN_INCLUDE_LINE % re.escape(name), re.M | re.I)
            for rel in ctx.grep_files(name, roots=("Code",)):
                if rel not in seen and line.search((ctx.read(rel) or b"").decode("utf-8", "replace")):
                    seen.add(rel)
                    frontier.add(rel)
    return seen


def coff_layout_problem(data):
    """Why `data` is not a whole i386 COFF object, or None. Every structure is
    walked within its declared counts: the header, each section (raw data and
    relocations inside the file, each relocation's symbol index inside the symbol
    table, a `/n` long name inside the string table), each symbol record and its
    auxiliary records (which must end inside the symbol table), each symbol's
    section number, and each long name's offset (inside the string table, ending
    in a NUL there)."""
    import struct
    if len(data) < 20:
        return "shorter than a COFF header"
    machine, count, _stamp, symbols, nsyms, optional, _flags = struct.unpack_from("<HHIIIHH", data, 0)
    if machine != 0x14C:
        return f"machine {machine:#x} is not an i386 COFF object"
    table = 20 + optional
    if table + 40 * count > len(data):
        return "its section table runs past the end"
    strings = symbols + 18 * nsyms
    if strings + 4 > len(data):
        return "its symbol table runs past the end"
    size = struct.unpack_from("<I", data, strings)[0]
    if size < 4 or strings + size > len(data):
        return "its string table runs past the end"

    def long_name(offset, what):
        if not 4 <= offset < size:
            return f"{what}'s name offset {offset} is outside the string table"
        if data.find(b"\0", strings + offset, strings + size) < 0:
            return f"{what}'s name runs past the string table"
        return None

    raw = []
    sizes = []
    for index in range(count):
        header = table + 40 * index
        name = data[header:header + 8]
        if name[:1] == b"/":
            digits = name[1:].rstrip(b"\0")
            if not digits.isdigit():
                return f"section {index + 1}'s long name is not a string-table offset"
            bad = long_name(int(digits), f"section {index + 1}")
            if bad:
                return bad
        size_raw, pointer, relocs = struct.unpack_from("<III", data, header + 16)
        nrelocs = struct.unpack_from("<H", data, header + 32)[0]
        flags = struct.unpack_from("<I", data, header + 36)[0]
        sizes.append(size_raw)
        if pointer and pointer + size_raw > len(data):
            return f"section {index + 1}'s raw data runs past the end"
        if pointer and size_raw:
            raw.append((pointer, pointer + size_raw, index + 1))
        if flags & 0x01000000:            # IMAGE_SCN_LNK_NRELOC_OVFL: the count is the first record's
            if nrelocs != 0xFFFF or relocs + 10 > len(data):
                return f"section {index + 1} flags a relocation overflow without its 0xFFFF marker and record"
            nrelocs = struct.unpack_from("<I", data, relocs)[0]
            if nrelocs < 2:
                return f"section {index + 1}'s overflow relocation count is {nrelocs}"
        if nrelocs:
            if relocs + 10 * nrelocs > len(data):
                return f"section {index + 1}'s relocations run past the end"
            for _offset, symbol, _type in struct.iter_unpack("<IIH", data[relocs:relocs + 10 * nrelocs]):
                if symbol >= nsyms:
                    return f"section {index + 1} relocates against symbol {symbol}, past the symbol table"
    raw.sort()
    for (_a, end, one), (start, _b, two) in zip(raw, raw[1:]):
        if start < end:
            return f"sections {one} and {two} overlap in the file"
    index = 0
    while index < nsyms:
        record = symbols + 18 * index
        if data[record:record + 4] == b"\0\0\0\0":
            bad = long_name(struct.unpack_from("<I", data, record + 4)[0], f"symbol {index}")
            if bad:
                return bad
        # unsigned: a unit with more than 0x7FFF COMDATs numbers sections past int16
        # (build.COFF_SECTION_CEILING); 0xFFFF and 0xFFFE are absolute and debug
        section = struct.unpack_from("<H", data, record + 12)[0]
        if section > count and section < 0xFFFE:
            return f"symbol {index}'s section number {section} names no section"
        value = struct.unpack_from("<I", data, record + 8)[0]
        if 1 <= section <= count and value > sizes[section - 1]:
            return f"symbol {index}'s value {value:#x} is past section {section}'s {sizes[section - 1]:#x} bytes"
        aux = data[record + 17]
        if index + aux >= nsyms:
            return f"symbol {index}'s {aux} auxiliary record(s) run past the symbol table"
        index += 1 + aux
    return None


def object_pin_references(objects, names):
    """[problem] for the objects {source: [paths]}: one missing, unreadable or not a whole COFF
    object, or one whose symbol table, weak externals or .drectve (/alternatename either side,
    /INCLUDE) names one of `names`. Every object is parsed whole: none is passed as clean unread."""
    import link_census
    problems = []
    for src, paths in sorted(objects.items()):
        if not paths:
            problems.append(f"{src} has no object to read")
            continue
        for path in paths:
            path = Path(path)
            try:
                data = path.read_bytes()
            except OSError:
                data = b""
            if not data:
                problems.append(f"{src}'s object {path.name} is missing or unreadable")
                break
            bad = coff_layout_problem(data)
            if bad:
                problems.append(f"{src}'s object {path.name} is unreadable: {bad}")
                break
            try:
                defined, referenced, weak, alternate, includes = link_census.object_symbols(path, data)
            except Exception as error:      # a damaged object: refuse, never read as clean
                problems.append(f"{src}'s object {path.name} is unreadable ({type(error).__name__})")
                break
            spelled = set(defined) | set(referenced) | set(includes) | set(alternate) | set(alternate.values())
            for entry in weak:
                spelled |= set(entry) if isinstance(entry, (tuple, list)) else {entry}
            hit = sorted(set(names) & spelled)
            if hit:
                problems.append(f"{src}'s object {path.name} references {hit[0]}")
    return problems


def pin_consumers(ctx, names, words, rebuilt):
    """(problems, count rebuilt) for retiring the pins `names` (placeholder types `words`): every
    rowed object outside `rebuilt` (the units the plan rebuilds) is read. A stale object whose source
    or an included header spells a pin or a type is rebuilt through ./build.sh first."""
    objects = link_objects(ctx)
    mentioned = mentioning_sources(ctx, sorted(set(names) | set(words)))
    stale = sorted(src for src in mentioned if objects.get(src) and src not in rebuilt
                   and not all(object_is_current(ctx, src, path) for path in objects[src]))
    if stale:
        if not rebuild_sources(ctx, stale):
            return [f"./build.sh could not rebuild the stale object(s) of {', '.join(stale[:4])}, which spell a "
                    "retired pin or its placeholder types"], 0
        objects = link_objects(ctx)
        still = [src for src in stale if not objects.get(src)
                 or not all(object_is_current(ctx, src, path) for path in objects[src])]
        if still:
            return [f"{', '.join(still[:4])} still has no current object after ./build.sh"], 0
    return object_pin_references({s: p for s, p in objects.items() if s not in rebuilt}, names), len(stale)


def identity_approvals(ctx, entries, evidence):
    """Give each entry its `agree` token: the naming approval among `evidence` that covers its
    exact old and new spelling at its address, under the row's own current key (source, kind,
    address, placeholder: the votes behind it are on this row). Every token covers one row, once."""
    tokens = (evidence or "").split()
    if not tokens or any(not AGREE_TOKEN.fullmatch(tok) for tok in tokens):
        raise Refusal("--identity needs --evidence 'agree:<id> [agree:<id> ...]', one naming approval per "
                      "row (two blind votes on its placeholder key)")
    for e in entries:
        inferred_guards(ctx, "function", e["old"], e["old"], e["rva"])
        why = []
        key = f"{e['source']}|function|0x{e['rva']:08X}|{e['old']}"
        for tok in tokens:
            try:
                check_agreement(ctx, "function", tok, {e["old"]}, {e["new"]}, e["rva"])
            except Refusal as error:
                why.append(f"{tok}: {error}")
                continue
            record = [r for r in ctx.dicts(AGREED) if r.get("id") == tok[len("agree:"):]][-1]
            if record.get("key") != key:
                why.append(f"{tok}: its key {record.get('key')!r} is not this row's key {key!r}")
                continue
            e["agree"] = tok
            break
        else:
            raise Refusal(f"no naming approval covers {e['old']} -> {e['new']} at 0x{e['rva']:08X} "
                          f"({'; '.join(why)[:400]})")
    used = [e["agree"] for e in entries]
    if len(set(tokens)) != len(tokens) or len(set(used)) != len(used) or set(used) != set(tokens):
        raise Refusal("--evidence names one approval per respelled row, each once")


def plan_identity_respell(ctx, rva, new, *, old=None, prepared=None, also=(), move_to=None, basis=None,
                          evidence="", max_files=25):
    if basis != "inferred":
        raise Refusal("--identity takes the naming route's approval: --basis inferred with --evidence "
                      "agree:<id> for every row (two blind votes on its placeholder key)")
    if not prepared:
        raise Refusal("--identity needs --prepared sources for every unit whose C++ must change")
    targets = [(rva, new, old)] + [(at, name, None) for at, name in (also or ())]
    if len({t[0] for t in targets}) != len(targets) or len({t[1] for t in targets}) != len(targets):
        raise Refusal("--identity: each RVA and each new name may appear once")
    rows = ctx.rows()
    entries = []
    for at, new_name, want in targets:
        old_name, owner = function_owner(ctx, at, want)
        if not new_name or not new_name.startswith("?"):
            raise Refusal("--identity needs each new name as its whole mangled spelling")
        if new_name == old_name:
            raise Refusal(f"0x{at:08X}: the new name is the old name")
        head_old, head_new = identity_head(old_name), identity_head(new_name)
        if head_old is None or head_new is None:
            raise Refusal(f"{old_name if head_old is None else new_name} is a hand-written name, not an operator, "
                          "special member or template member the compiler spells from its types: rename it "
                          "with function --new and its basis")
        if head_old != head_new:
            raise Refusal(f"{new_name} changes the operator or identifier of {old_name} ({head_old} -> "
                          f"{head_new}): only the types the compiler spells may change")
        if not placeholder_types(old_name):
            raise Refusal(f"{old_name} names no placeholder type (Rva.../Bfme...): an identity respell replaces "
                          "a placeholder-typed spelling only")
        # tree by tree: placeholder and vendored-STLport subtrees may change; every other
        # name keeps its qualified path and place, and a canonical class is never replaced
        canonical = {r.get("class") for r in ctx.dicts(CANONICAL_CLASSES)} - {"", None}
        why = identity_shape_problem(old_name, new_name, canonical, stlport_declared(ctx))
        if why:
            raise Refusal(f"{new_name} changes more than an identity respell may of {old_name}: {why}")
        # the primary row checks of plan_function, on every row
        function_identity_checks(ctx, at, old_name, old_name, owner)
        function_collision_checks(ctx, at, old_name, new_name, old_name, new_name, respell=True)
        pinned = sorted(p.get("name", "") for p in ctx.pins() if _rva(p.get("address")) == at)
        if pinned:
            raise Refusal(f"0x{at:08X} carries pin(s) {', '.join(pinned)}: an identity respell cannot derive "
                          "their spellings")
        entries.append(dict(rva=at, old=old_name, new=new_name, source=owner["source"]))
    identity_approvals(ctx, entries, evidence)

    # 1. the code-identity check is the reason for the respell
    owner_sources = {e["source"] for e in entries}
    before = identity_refs(ctx, owner_sources | set(prepared))
    planned = {e["rva"] for e in entries}
    callees = {}
    for e in entries:
        own = [r for r in before if r["row"] == e["old"] and r["rva"] == e["rva"]]
        if not own:
            raise Refusal(f"the code-identity check has no references for {e['old']} (its object is missing or "
                          "stale: ./build.sh its source first, or it calls nothing an identity respell could prove)")
        wrong = identity_wrong(own)
        inner = sorted({r["target"] for r in own if r["target"] in planned and r["target"] != e["rva"]})
        if not wrong and not inner:
            raise Refusal(f"the code-identity check reports no wrong binding for {e['old']} and it calls no row "
                          "this plan respells: there is nothing for an identity respell to prove")
        e["wrong"] = sorted({r["target"] for r in wrong})
        e["inner"] = inner
        e["bound"] = sorted({r["target"] for r in own if r["cls"] not in ("label", "eh")
                             and r["target"] != e["rva"]})
        callees[e["rva"]] = sorted({r["target"] for r in own})
    if not any(e["wrong"] for e in entries):
        raise Refusal("the code-identity check reports no wrong binding for any row of this plan")

    # 2. a folded callee's binding proves no one name
    named, notes = callee_marks(rows)
    for e in entries:
        for t in e["bound"]:
            folded = None if t in planned else folded_callee(named, notes, t)
            if folded:
                raise Refusal(f"{e['old']} calls 0x{t:08X}, which {folded}: a folded callee's binding proves "
                              "no one name")

    # Callee pins: a pinned callee binds through the pin, so a pin refuses, except
    # the one the respell makes obsolete -- the callee spelled under the respelled
    # row's old class, the symbol its old object binds there -- once no object
    # outside the rebuilt units references it.
    pins_at = collections.defaultdict(list)
    for p in ctx.pins():
        pins_at[_rva(p.get("address"))].append(p.get("name", ""))
    pin_count = collections.Counter(p.get("name", "") for p in ctx.pins())
    row_names = {r["name"] for r in rows}
    matched = {r["name"] for r in rows if r.get("status") == "matched"}
    retire = {}
    for e in entries:
        old_cls = identity_class(e["old"])
        for t in e["bound"]:
            for name in pins_at.get(t, ()):
                callee = min(named[t]) if len(named.get(t, ())) == 1 else None
                bound = {r["symbol"] for r in before if r["row"] == e["old"] and r["rva"] == e["rva"]
                         and r["target"] == t}
                pin_cls = identity_class(name)
                if not (callee in matched and old_cls and pin_cls and pin_cls[0] == old_cls[0]
                        and identity_head(name) == identity_head(callee) and name in bound
                        and pin_count[name] == 1 and name not in row_names):
                    raise Refusal(f"{e['old']} calls 0x{t:08X}, which carries pin {name}: only that callee's "
                                  "old-type spelling, which the respelled row's object binds there, is retired; "
                                  "any other pinned callee proves nothing")
                retire[(name, t)] = callee
    rebuilt = 0
    if retire:
        names = sorted({name for name, _t in retire})
        words = sorted({w for name in names for w in placeholder_types(name)})
        problems, rebuilt = pin_consumers(ctx, names, words, owner_sources | set(prepared))
        if problems:
            raise Refusal(f"the old-type pin(s) cannot be retired: {problems[0]}"
                          + (f" (and {len(problems) - 1} more)" if len(problems) > 1 else ""))

    # --move-to: the approved TU of every respelled row; every row of the owner source moves with them
    removed = []
    if move_to:
        move_to = move_to.replace("\\", "/")
        import tu_map
        # a stale committed map is rebuilt in memory from current inputs (as tools/tu_skeleton.py
        # reads it); the rebuild's approval decides
        try:
            map_rows, stale = tu_map.current_rows(tu_map.Layout(ctx.root))
        except tu_map.NoZhTree as error:
            raise Refusal(f"--move-to cannot rebuild {TU_MAP} from current inputs: {error}") from None
        approved = {}
        for row in map_rows:
            approved.setdefault(_rva(row.get("rva")), (row.get("tu", ""), row.get("confidence", "")))
        for e in entries:
            tu, confidence = approved.get(e["rva"], ("", ""))
            if tu != move_to or confidence != "approved":
                raise Refusal(f"0x{e['rva']:08X} is not approved for {move_to} in {TU_MAP}"
                              + (" (rebuilt in memory: the committed map is stale)" if stale else "") +
                              f" ({tu or 'no TU'}, {confidence or 'unlisted'}): rows move only into their "
                              "approved unit")
        if move_to not in prepared:
            raise Refusal(f"--move-to {move_to} needs its prepared bytes (the moved definitions)")
        moved_names = {e["old"] for e in entries}
        for src in sorted(owner_sources):
            if src == move_to:
                continue
            stay = [r for r in rows if r["source"] == src and r["name"] not in moved_names
                    and not any(mangled_re(n).search(r["name"]) or f"parent={n}" in r.get("notes", "")
                                for n in moved_names)]
            if stay:
                raise Refusal(f"{src} also holds {stay[0]['name']} (0x{_rva(stay[0].get('target_rva')):08X}), "
                              "which this plan does not move: --move-to moves a whole owner source")
            if src in prepared:
                raise Refusal(f"{src} is emptied by --move-to {move_to}: do not prepare it")
            if any(d.get("source") == src for d in ctx.dicts(DATA_ROWS)):
                raise Refusal(f"{src} owns data rows: move them with their own tool first")
            keyed = [rel for rel in PROTECTED_PATH_KEYED if (ctx.read(rel) or b"").find(src.encode()) >= 0]
            if keyed:
                raise Refusal(f"{src} is a key in {', '.join(keyed)} (protected, path-keyed)")
            removed.append(src)

    renames = {e["old"]: e["new"] for e in entries}
    primary = entries[0]

    def hexes(rvas):
        return ", ".join(f"0x{t:08X}" for t in rvas)

    facts = IDENTITY + " " + "; ".join(
        f"0x{e['rva']:08X} calls " + (hexes(callees[e["rva"]]) or "nothing") + " (" +
        (f"wrong before: {hexes(e['wrong'])}" if e["wrong"] else f"calls the respelled {hexes(e['inner'])}") + ")"
        for e in entries)
    if retire:
        facts += (f"; retires the old-type pin(s) at {hexes(sorted({t for _n, t in retire}))} "
                  f"({rebuilt} stale object(s) rebuilt for the consumer scan)")
    plan = Plan("function", primary["old"], primary["new"], "inferred",
                " ".join(e["agree"] for e in entries) + "; " + facts, move_to or primary["source"], primary["rva"])

    # Ledgers: every row, funclet and notes token spelling an old name.
    raw = ctx.read(FUNCTIONS)
    for e in entries:
        raw, changed = rewrite_records(raw, "functions.csv", mangled_re(e["old"]), e["new"])
        for b, a in changed:
            at = _rva(b[2])
            if b[0] != a[0]:
                plan.renamed_rows.append((b[0], a[0], at))
            else:
                plan.notes_rows.append((b[0], at))
    if move_to:
        for src in removed:
            raw, _count = repoint_column(raw, FUNCTIONS, "source", src, move_to)
    plan.edit(ctx, FUNCTIONS, raw)
    if retire:
        raw = ctx.read(SYMBOLS)
        ledger_io.lf_terminator(raw, "symbols.csv")
        out = []
        for index, (payload, term) in enumerate(ledger_io.split_records(raw)):
            flds = ledger_io.fields(payload)
            if index and len(flds) >= 2 and (flds[0], _rva(flds[1])) in retire:
                plan.dropped_pins.append((flds[0], retire[(flds[0], _rva(flds[1]))], flds[1]))
                continue
            out.append(payload + term)
        plan.edit(ctx, SYMBOLS, b"".join(out))
        hatches = (ctx.read(HATCH_BASELINE) or b"").decode("utf-8", "replace")
        for _name, t in sorted(retire, key=lambda k: k[1]):
            if f"pin\t{SYMBOLS}\t0x{t:08X}\t" in hatches:
                plan.warnings.append(f"{HATCH_BASELINE} still grants pin 0x{t:08X}: python3 tools/hatch_counters.py "
                                     "--update tightens it (Verifier-Change)")
    if move_to:
        for rel, column in PATH_COLUMNS:
            if rel == FUNCTIONS or ctx.read(rel) is None:
                continue
            data = ctx.read(rel)
            for src in removed:
                data, _count = repoint_column(data, rel, column, src, move_to)
            if data != ctx.read(rel):
                plan.edit(ctx, rel, data)
    tombstoned = _tombstones(ctx)
    for old_row, new_row, at in plan.renamed_rows:
        if (old_row, at) not in tombstoned:
            plan.edit(ctx, DELETED, appended(plan.after.get(DELETED, ctx.read(DELETED)), [tombstone_line(
                old_row, at, f"Respelled to {new_row} by tools/rename.py (code identity)")],
                header="name,target_rva,reason"))
    # the record is the approval alone (agree:<id>), as every inferred landing's, so revert finds it
    plan.edit(ctx, NAME_BASIS, appended(ctx.read(NAME_BASIS), [csv_line(
        ["function", e["old"], e["new"], "inferred", e["agree"], move_to or e["source"], f"0x{e['rva']:08X}"])
        for e in entries], header=NAME_BASIS_HEADER))

    # Sources: the prepared C++ is the whole change; nothing may still spell an old name.
    _batch_source_edits(ctx, plan, prepared)
    for src in removed:
        plan.before.setdefault(src, ctx.read(src))
        plan.removed.append(src)
    for e in entries:
        left = sorted(rel for rel, data in plan.after.items()
                      if rel in prepared and mangled_re(e["old"]).search(data.decode("utf-8", "replace")))
        if left:
            raise Refusal(f"prepared {', '.join(left)} still spells {e['old']}")
        elsewhere = sorted(set(ctx.grep_files(e["old"], roots=("Code",))) - set(prepared) - set(removed))
        if elsewhere:
            raise Refusal(f"{', '.join(elsewhere[:4])} still spells {e['old']}: prepare every unit that names it")
    verify = (set(prepared) | owner_sources) - set(removed)
    verify |= {r["source"] for r in rows if (r["name"], _rva(r.get("target_rva"))) in set(plan.notes_rows)}
    plan.verify = sorted(v for v in verify if not is_generated(v) and v not in removed)
    if len(plan.verify) > max_files:
        raise Refusal(f"{len(plan.verify)} sources to verify (over --max-files {max_files})")
    plan.identity = dict(
        rows=[(e["rva"], e["old"], e["new"]) for e in entries],
        sources=sorted(set(plan.verify)),
        wrong_before=sorted({_identity_key(r, renames) for r in identity_wrong(before)}),
        callees={e["rva"]: callees[e["rva"]] for e in entries},
        retired=sorted((name, t, callee) for (name, t), callee in retire.items()))
    plan.claims = sorted({at for _, _, at in plan.renamed_rows} | {at for _, at in plan.notes_rows} |
                         {t for _n, t in retire}) + \
        [f"file:{s}" for s in sorted(owner_sources | ({move_to} if move_to else set()))]
    edited = set(plan.after) | {"reverse/re_attempts.log"}
    plan.mentions = sorted({m for e in entries for m in ctx.grep_files(e["old"], roots=("docs", "reverse"))}
                           - edited)
    return plan


def repoint_row_source(raw, label, keycol, rva, old, new):
    """`raw` with the `source` of the records keyed `rva` in `keycol` changed from `old` to `new`;
    (new_raw, count), every other byte kept. A row moves alone: the owner source stays."""
    ledger_io.lf_terminator(raw, label)
    records = ledger_io.split_records(raw)
    header = ledger_io.fields(records[0][0]) if records else []
    if keycol not in header or "source" not in header:
        raise Refusal(f"{label} lacks {keycol!r} or 'source'")
    ki, si = header.index(keycol), header.index("source")
    out, count = [records[0][0] + records[0][1]], 0
    for payload, term in records[1:]:
        text = payload.decode("utf-8")
        spans = field_spans(text)
        if len(spans) > max(ki, si) and _rva(text[spans[ki][0]:spans[ki][1]].strip('"')) == rva:
            start, end = spans[si]
            value = text[start:end]
            if value in (old, f'"{old}"'):
                payload = (text[:start] + value.replace(old, new) + text[end:]).encode("utf-8")
                count += 1
        out.append(payload + term)
    return b"".join(out), count


ROW_KEYED_LEDGERS = ((FUNCTIONS, "target_rva"), (TU_MAP, "rva"), ("reverse/body_owners.csv", "target_rva"))

# The owner's exception of 2026-11-09 (docs/consolidation.md, "A row a rename forces out"): the record of
# each row moved with no approved unit, so a later pass can place it. It approves nothing.
FORCED_MOVES = "reverse/forced_row_moves.csv"
FORCED_MOVE_STATEMENT = ("not in its true unit: a rename forced it out and the map has no approved unit; "
                         "placed_in is placement evidence, no approval")


def forced_move_object(ctx, source):
    hook = getattr(ctx, "forced_move_object", None)
    if hook:
        return hook(source)
    import build
    return build.obj_path(ctx.path(source))


def forced_move_is_current(ctx, source, path):
    hook = getattr(ctx, "forced_move_current", None)
    if hook:
        return hook(source)
    import build
    return object_receipt_holds(ctx.path(source), Path(path))


def object_receipt_holds(source, path):
    """The census-grade receipt (strict: include search directories too) for `source`, and the object at
    `path` is the one that receipt recorded: compile_is_current reads neither the bytes nor, unless
    strict, the search path, so a replaced object would pass it."""
    import build
    if not build.compile_is_current(source, path, strict=True):
        return False
    try:
        recorded = json.loads(build._deps_sidecar(path).read_text()).get("object")
        return bool(recorded) and recorded == hashlib.md5(path.read_bytes()).hexdigest()
    except (OSError, ValueError, AttributeError):
        return False


def forced_move_references(path, name):
    """Whether the COFF object at `path` names `name` at all, defined or not; None when it cannot be read."""
    import link_census
    try:
        return any(s["name"] == name for s in link_census._coff_symbols(Path(path).read_bytes()))
    except (OSError, ValueError, IndexError, KeyError, TypeError, struct.error):
        return None


def forced_destination_problem(ctx, dest):
    """Why `dest` cannot take a forced row, or None: as strict as a prepared source, since it must already be
    an owned, tracked, hand-written Code C++ unit with matched rows."""
    parsed = PurePosixPath(dest)
    if (not dest.startswith("Code/") or not dest.endswith(".cpp") or ".." in parsed.parts
            or parsed.as_posix() != dest or "\\" in dest):
        return f"--forced-move needs an existing Code C++ source, not {dest}"
    path = ctx.path(dest)
    if (path.is_symlink() or not path.is_file()
            or not path.resolve().is_relative_to((ctx.root / "Code").resolve())):
        return f"--forced-move destination is missing or outside the Code tree: {dest}"
    if is_generated(dest):
        return f"--forced-move cannot place a row in generated source {dest}"
    if dest not in ctx.ledger_sources():
        return f"--forced-move destination has no matched rows: {dest}"
    if dest not in ctx.git("ls-files", "--", dest).splitlines():
        return f"--forced-move destination is untracked: {dest}"
    return None


def map_units(ctx):
    """{rva: (tu, confidence)} of the map as the current inputs build it, whether or not the committed
    file has caught up: that is the current map, before the move and after it."""
    import tu_map
    try:
        map_rows, _stale = tu_map.current_rows(tu_map.Layout(ctx.root))
    except tu_map.NoZhTree as error:
        raise Refusal(f"cannot rebuild {TU_MAP} from current inputs: {error}") from None
    units = {}
    for row in map_rows:
        units.setdefault(_rva(row.get("rva")), (row.get("tu", ""), row.get("confidence", "")))
    return units


def plan_forced_move(ctx, rows, family, at, dest, prepared, units):
    """The refusals of one --forced-move before anything is written: the family's reviewed table names this
    row from this file, this rename rewrites that file, the map has no unit for it, and a current object
    shows it there today. Whether the rewrite really stops defining and naming it is the rebuilt objects'
    answer (forced_move_problems)."""
    import tu_skeleton
    if at in family.rows or at in family.pins:
        raise Refusal(f"0x{at:08X} is the family's own row: --forced-move is for a row the rename forces out")
    entry = getattr(family, "forced_moves", {}).get(at)
    if entry is None:
        raise Refusal(f"0x{at:08X} is not in the family's reviewed forced_moves (tools/retail_identity.py)")
    held = [r for r in rows if _rva(r.get("target_rva")) == at]
    if len(held) != 1 or held[0].get("status") != "matched":
        raise Refusal(f"0x{at:08X} must be exactly one matched row, not {len(held)}")
    row = held[0]
    old = row["source"]
    if (row["name"], old) != tuple(entry):
        raise Refusal(f"0x{at:08X} is {row['name']} in {old}; the family reviewed {entry[0]} in {entry[1]}")
    if old not in prepared:
        raise Refusal(f"no rename forces 0x{at:08X} out: this respell does not change {old}")
    if dest == old:
        raise Refusal(f"0x{at:08X} is already in {dest}")
    why = forced_destination_problem(ctx, dest)
    if why:
        raise Refusal(why)
    if at not in units:
        raise Refusal(f"0x{at:08X} is not in {TU_MAP}: cannot show it has no approved unit")
    tu, confidence = units[at]
    if tu or confidence == "approved":
        raise Refusal(f"0x{at:08X} has a unit in {TU_MAP} ({tu or 'no TU'}, {confidence}): "
                      "rows move only into their approved unit, --move-to")
    carried = [r["name"] for r in rows if f"parent={row['name']}" in r.get("notes", "")]
    if carried:
        raise Refusal(f"0x{at:08X} has funclets ({carried[0]}): a row with funclets does not move alone")
    path = forced_move_object(ctx, old)
    if not forced_move_is_current(ctx, old, path):
        raise Refusal(f"{old}'s object has no current census-grade receipt, so it proves nothing about the row "
                      f"before the move: python3 tools/link_check.py --prepare-current {old} first")
    defined = tu_skeleton.coff_definitions(path)
    before = tu_skeleton.section_identity(path, row["name"])
    if defined is None or row["name"] not in defined or before is None:
        raise Refusal(f"{old}'s object does not show {row['name']} before the move: nothing is forced, or "
                      f"./build.sh {old} first")
    return dict(rva=at, name=row["name"], size=int(row["target_size"]), old=old, dest=dest, before=before)


def slot_operand_problem(rows, family):
    """Why the ledger does not tie a SlotOperandFamily's retail facts to its rows, or None: the table's writer, the
    element's destructor and each iterator rowed (matched) at their addresses under exactly those names, the writer's
    stores inside its row, and every push, call and handler load inside the copy's row. The table's name is not read."""
    import retail_identity

    def row(name, at):
        found = [r for r in rows if r["name"] == name and _rva(r.get("target_rva")) == at and r.get("status") == "matched"]
        return found[0] if len(found) == 1 else None

    def inside(fact, start, size):
        return start <= fact.site and fact.site + len(retail_identity.expected(fact)) <= start + size

    writer = family.writer
    got = row(writer["name"], writer["rva"])
    if got is None:
        return f"{writer['name']} is not rowed at 0x{writer['rva']:08X}: the table's writer ties it to the element's class"
    for fact in writer["facts"]:
        if not inside(fact, writer["rva"], int(got["target_size"])):
            return f"0x{fact.site:08X} is outside {writer['name']}'s row"
    dtor = family.element_dtor
    if row(dtor["name"], dtor["rva"]) is None:
        return f"{dtor['name']} is not rowed at 0x{dtor['rva']:08X}: the element is proved by its destructor's row"
    for at, name in sorted(family.iterators.items()):
        if row(name, at) is None:
            return f"{name} is not rowed at 0x{at:08X}"
    copy_name = family.rows[family.copy][0]
    got = row(copy_name, family.copy)
    if got is None:
        return f"{copy_name} is not rowed at 0x{family.copy:08X}"
    size = int(got["target_size"])
    loads = [f for at, (_name, facts) in family.rows.items() if at != family.copy for f in facts]
    for fact in [f for push, call in family.operands for f in (push, call)] + loads:
        if not inside(fact, family.copy, size):
            return f"0x{fact.site:08X} is outside {copy_name}'s row"
    return None


def slot_operand_bindings(family, source, name):
    """[(source, name, offset, type, target)]: what the rebuilt copy must bind for a SlotOperandFamily."""
    out = []
    for push, call in family.operands:
        out.append((source, name, push.site + 1 - family.copy, DIR32, family.element_dtor["name"]))
        out.append((source, name, call.site + 1 - family.copy, REL32, family.iterators[call.value]))
    return out


def plan_retail_respell(ctx, rva, new, *, old=None, prepared=None, also=(), move_to=None, move_rows=(),
                        forced_moves=(), evidence="", max_files=25):
    """--respell --identity --basis retail: the whole family tools/retail_identity.py spells out, from
    its stand-in class to the class retail proves, on retail's own bytes and no vote: every fact is read
    from the image, the class's own rowed member installs the same table, and the data ledger names that
    table for the class. After ./build.sh the rebuilt copy must bind the class's table, and no touched
    row may gain a wrong binding (retail_identity_problems). `move_rows` moves those rows alone into
    `move_to`, the unit the map approves, because retail reached them from its code; their owner stays.
    `forced_moves` are rows outside the family that the rename forces out of a file it rewrites, with no
    unit in the map: plan_forced_move and forced_move_problems hold the owner's terms."""
    import retail_identity
    family = retail_identity.family_of(rva, new)
    if family is None:
        raise Refusal(f"--basis retail proves only the families in tools/retail_identity.py; 0x{rva:08X} -> {new} "
                      "is not one")
    if old or also:
        raise Refusal("--basis retail respells the family its table spells out: no --old, no --also")
    if not prepared:
        raise Refusal("--basis retail needs --prepared sources for every unit whose C++ must change")
    if evidence != family.evidence():
        raise Refusal(f"--evidence must name the proof: {family.evidence()!r}")
    problems = retail_identity.facts_problems(family.facts())
    if problems:
        raise Refusal(f"retail does not state {family.old} -> {family.new}: {problems[0]}")
    rows = ctx.rows()
    no_table = isinstance(family, retail_identity.BodyFamily)
    slot_kind = isinstance(family, retail_identity.SlotOperandFamily)
    if slot_kind:
        problem = slot_operand_problem(rows, family)
        if problem:
            raise Refusal(problem)
    elif no_table:
        for label, members in (("new", family.members), ("old", family.old_members)):
            for at, name in sorted(members.items()):
                if not any(r["name"] == name and _rva(r.get("target_rva")) == at and r.get("status") == "matched"
                           for r in rows):
                    raise Refusal(f"{name} is not rowed at 0x{at:08X}: with no table, the {label} class's rows "
                                  "are what tie the proof to it")
    else:
        owner = family.owner
        if not any(r["name"] == owner["name"] and _rva(r.get("target_rva")) == owner["rva"] and r.get("status") == "matched"
                   for r in rows):
            raise Refusal(f"{owner['name']} is not rowed at 0x{owner['rva']:08X}: the table proves no class without its member")
        table_row = [r for r in ctx.dicts("reverse/data_ledger.csv")
                     if _rva(r.get("address")) == family.table - retail_identity.IMAGE_BASE]
        owner_size = next(int(r["target_size"]) for r in rows
                          if r["name"] == owner["name"] and _rva(r.get("target_rva")) == owner["rva"])
        if not table_row or not retail_identity.table_named(family, table_row[0], owner_size):
            raise Refusal(f"the data ledger does not name 0x{family.table:08X} {family.table_name}")
    leaves = getattr(family, "leaves", {})
    for at, size in sorted(leaves.items()):
        found = [r for r in rows if r["name"] == family.rows[at][0] and _rva(r.get("target_rva")) == at]
        if len(found) != 1 or int(found[0]["target_size"]) != size:
            raise Refusal(f"leaf 0x{at:08X} is not rowed at its declared {size} bytes")
        try:
            problem = retail_identity.leaf_problem(at, size)
        except Exception as error:                     # noqa: BLE001 - an unread body is no leaf
            problem = f"it cannot be read: {error}"
        if problem:
            raise Refusal(f"retail's 0x{at:08X} is no leaf: {problem}")
    table_stores = getattr(family, "table_stores", {})
    for at, offset in sorted(table_stores.items()):
        fact = retail_identity.table_store_fact(family, at)
        if fact is None:
            raise Refusal(f"0x{at:08X} declares no store of 0x{family.table:08X} at +{offset}")
        found = [r for r in rows if r["name"] == family.rows[at][0] and _rva(r.get("target_rva")) == at]
        if len(found) != 1 or int(found[0]["target_size"]) < offset + 4:
            raise Refusal(f"0x{at:08X}'s store of the table at +{offset} is past its row")
        problems = retail_identity.facts_problems([fact])
        if problems:
            raise Refusal(f"retail's 0x{at:08X} does not store the table: {problems[0]}")
    entries = []
    for at, (old_name, facts) in sorted(family.rows.items()):
        found = [r for r in rows if r["name"] == old_name and _rva(r.get("target_rva")) == at]
        if len(found) != 1:
            raise Refusal(f"{old_name} is not the one row of that name at 0x{at:08X}")
        new_name = family.respell(old_name)
        function_identity_checks(ctx, at, old_name, old_name, found[0])
        function_collision_checks(ctx, at, old_name, new_name, old_name, new_name, respell=True,
                                  frozen_ok=frozenset({CODE_IDENTITY_BASELINE}) if at == family.copy else frozenset())
        entries.append(dict(rva=at, old=old_name, new=new_name, source=found[0]["source"], facts=facts))
    pins = {(p.get("name", ""), _rva(p.get("address"))) for p in ctx.pins()}
    names = {p.get("name", "") for p in ctx.pins()} | {r["name"] for r in rows}
    for at, (old_name, _facts) in sorted(family.pins.items()):
        if (old_name, at) not in pins:
            raise Refusal(f"pin {old_name} is not at 0x{at:08X}")
        if family.respell(old_name) in names:
            raise Refusal(f"{family.respell(old_name)} already names a row or pin")
    retired = getattr(family, "retired", {})
    for at, (old_name, _facts) in sorted(retired.items()):
        if (old_name, at) not in pins:
            raise Refusal(f"pin {old_name} is not at 0x{at:08X}")
        if at not in family.members:
            raise Refusal(f"0x{at:08X} is not rowed for {family.new}: only a pin the new class's row replaces is retired")

    moved = sorted(set(move_rows or ()))
    if moved:
        if not move_to:
            raise Refusal("--move-rows names the rows --move-to moves")
        if move_to not in prepared:
            raise Refusal(f"--move-to {move_to} needs its prepared bytes (what emits the moved rows)")
        strangers = [at for at in moved if at not in family.rows]
        if strangers:
            raise Refusal(f"0x{strangers[0]:08X} is not a row of the family")
        import tu_map
        try:
            map_rows, stale = tu_map.current_rows(tu_map.Layout(ctx.root))
        except tu_map.NoZhTree as error:
            raise Refusal(f"--move-to cannot rebuild {TU_MAP} from current inputs: {error}") from None
        approved = {}
        for row in map_rows:
            approved.setdefault(_rva(row.get("rva")), (row.get("tu", ""), row.get("confidence", "")))
        for at in moved:
            tu, confidence = approved.get(at, ("", ""))
            if tu != move_to or confidence != "approved":
                raise Refusal(f"0x{at:08X} is not approved for {move_to} in {TU_MAP}"
                              + (" (rebuilt in memory: the committed map is stale)" if stale else "") +
                              f" ({tu or 'no TU'}, {confidence or 'unlisted'}): rows move only into their approved unit")
            carried = [r["name"] for r in rows if f"parent={family.rows[at][0]}" in r.get("notes", "")]
            if carried:
                raise Refusal(f"0x{at:08X} has funclets ({carried[0]}): a row with funclets does not move alone")
    elif move_to:
        raise Refusal("--basis retail moves the rows --move-rows names, and only those")
    forced = []
    units_before = None
    if forced_moves:
        units_before = map_units(ctx)
        if len({at for at, _dest in forced_moves}) != len(forced_moves):
            raise Refusal("--forced-move names one row twice")
        forced = [plan_forced_move(ctx, rows, family, at, dest, prepared, units_before)
                  for at, dest in sorted(forced_moves)]

    primary = next(e for e in entries if e["rva"] == family.copy)
    plan = Plan("function", primary["old"], primary["new"], retail_identity.BASIS, family.evidence(),
                move_to if family.copy in moved else primary["source"], primary["rva"])
    source_of = {e["rva"]: (move_to if e["rva"] in moved else e["source"]) for e in entries}

    # Ledgers: every row, funclet, pin and notes token spelling an old name.
    raw = ctx.read(FUNCTIONS)
    pin_raw = ctx.read(SYMBOLS)
    for e in entries:
        raw, changed = rewrite_records(raw, "functions.csv", mangled_re(e["old"]), e["new"])
        for b, a in changed:
            at = _rva(b[2])
            if b[0] != a[0]:
                plan.renamed_rows.append((b[0], a[0], at))
            else:
                plan.notes_rows.append((b[0], at))
        pin_raw, _changed = rewrite_records(pin_raw, "symbols.csv", mangled_re(e["old"]), e["new"])
    for at, (old_name, _facts) in sorted(family.pins.items()):
        raw, changed = rewrite_records(raw, "functions.csv", mangled_re(old_name), family.respell(old_name))
        plan.notes_rows.extend((b[0], _rva(b[2])) for b, _a in changed)
        pin_raw, changed = rewrite_records(pin_raw, "symbols.csv", mangled_re(old_name), family.respell(old_name))
        plan.renamed_pins.extend((b[0], family.respell(old_name), f"0x{at:08X}") for b, _a in changed)
    if retired:
        drop = {(old_name, at) for at, (old_name, _facts) in retired.items()}
        problems, _rebuilt = pin_consumers(ctx, sorted(name for name, _at in drop), [family.old],
                                           {e["source"] for e in entries} | set(prepared))
        if problems:
            raise Refusal(f"the old class's pin(s) cannot be retired: {problems[0]}"
                          + (f" (and {len(problems) - 1} more)" if len(problems) > 1 else ""))
        ledger_io.lf_terminator(pin_raw, "symbols.csv")
        kept = []
        for index, (payload, term) in enumerate(ledger_io.split_records(pin_raw)):
            flds = ledger_io.fields(payload)
            if index and len(flds) >= 2 and (flds[0], _rva(flds[1])) in drop:
                plan.dropped_pins.append((flds[0], family.members[_rva(flds[1])], flds[1]))
                continue
            kept.append(payload + term)
        pin_raw = b"".join(kept)
    plan.edit(ctx, SYMBOLS, pin_raw)
    edited = {FUNCTIONS: raw}
    for at in moved:
        for rel, keycol in ROW_KEYED_LEDGERS:
            data = edited.get(rel, ctx.read(rel))
            if data is None:
                continue
            data, _count = repoint_row_source(data, rel, keycol, at, next(e["source"] for e in entries if e["rva"] == at), move_to)
            edited[rel] = data
    for move in forced:
        for rel, keycol in ROW_KEYED_LEDGERS:
            data = edited.get(rel, ctx.read(rel))
            if data is None:
                continue
            data, _count = repoint_row_source(data, rel, keycol, move["rva"], move["old"], move["dest"])
            edited[rel] = data
    for rel, data in edited.items():
        if data != ctx.read(rel):
            plan.edit(ctx, rel, data)
    tombstoned = _tombstones(ctx)
    for old_row, new_row, at in plan.renamed_rows:
        if (old_row, at) not in tombstoned:
            plan.edit(ctx, DELETED, appended(plan.after.get(DELETED, ctx.read(DELETED)), [tombstone_line(
                old_row, at, f"Respelled to {new_row} by tools/rename.py (retail identity)")],
                header="name,target_rva,reason"))
    plan.edit(ctx, NAME_BASIS, appended(ctx.read(NAME_BASIS), [csv_line(
        ["function", e["old"], e["new"], retail_identity.BASIS, retail_identity.record(e["facts"]),
         source_of[e["rva"]], f"0x{e['rva']:08X}"]) for e in entries], header=NAME_BASIS_HEADER))

    if forced:
        register = ctx.read(FORCED_MOVES)
        if register is None:
            raise Refusal(f"{FORCED_MOVES} is missing: every forced move is recorded there")
        plan.edit(ctx, FORCED_MOVES, appended(register, [csv_line(
            [f"0x{m['rva']:08X}", m["name"], m["old"], m["dest"], family.evidence(), FORCED_MOVE_STATEMENT])
            for m in forced]))

    # Sources: the prepared C++ is the whole change; nothing may still spell an old name.
    _batch_source_edits(ctx, plan, prepared)
    for old_name in ([e["old"] for e in entries] + [name for name, _f in family.pins.values()]
                     + [name for name, _f in retired.values()]):
        left = sorted(rel for rel, data in plan.after.items()
                      if rel in prepared and mangled_re(old_name).search(data.decode("utf-8", "replace")))
        if left:
            raise Refusal(f"prepared {', '.join(left)} still spells {old_name}")
        elsewhere = sorted(set(ctx.grep_files(old_name, roots=("Code",))) - set(prepared))
        if elsewhere:
            raise Refusal(f"{', '.join(elsewhere[:4])} still spells {old_name}: prepare every unit that names it")
    owner_sources = {e["source"] for e in entries}
    verify = set(prepared) | owner_sources
    verify |= {r["source"] for r in rows if (r["name"], _rva(r.get("target_rva"))) in set(plan.notes_rows)}
    verify |= {m["dest"] for m in forced}
    plan.verify = sorted(v for v in verify if not is_generated(v))
    if len(plan.verify) > max_files:
        raise Refusal(f"{len(plan.verify)} sources to verify (over --max-files {max_files})")
    import allowed_symbols
    try:
        before = identity_refs(ctx, set(plan.verify))
    except allowed_symbols.UnverifiedFunclet as error:
        raise Refusal(f"the code-identity scan cannot read the units as they stand ({error}): "
                      f"./build.sh {' '.join(plan.verify)} first") from None
    renames = {e["old"]: e["new"] for e in entries}
    plan.identity = dict(
        retail=True, rows=[(e["rva"], e["old"], e["new"]) for e in entries], sources=sorted(set(plan.verify)),
        wrong_before=sorted({_identity_key(r, renames) for r in identity_wrong(before)}),
        copy=family.copy, copy_name=primary["new"], copy_source=source_of[family.copy], retired=[], moved=moved)
    if forced:
        plan.identity.update(forced=forced, units_before=units_before)
    if slot_kind:
        plan.identity["operands"] = slot_operand_bindings(family, source_of[family.copy], primary["new"])
    elif no_table:
        by_rva = {e["rva"]: e["new"] for e in entries}
        plan.identity["bindings"] = [(source_of[at], by_rva[at], offset, target) for at, offset, target in family.bindings]
        plan.identity["retired"] = sorted((name, at, family.members[at]) for at, (name, _f) in retired.items())
    else:
        plan.identity.update(table_name=family.table_name, copy_store=family.copy_store,
                             leaves={at: (source_of[at], family.respell(family.rows[at][0])) for at in leaves},
                             table_stores={at: (source_of[at], family.respell(family.rows[at][0]), offset)
                                           for at, offset in table_stores.items()})
    plan.claims = sorted({at for _, _, at in plan.renamed_rows} | {at for _, at in plan.notes_rows}) + \
        [f"file:{s}" for s in sorted(owner_sources | ({move_to} if move_to else set()))]
    plan.claims += sorted(m["rva"] for m in forced) + \
        [f"file:{s}" for s in sorted({m["old"] for m in forced} | {m["dest"] for m in forced})]
    done = set(plan.after) | {"reverse/re_attempts.log"}
    plan.mentions = sorted({m for e in entries for m in ctx.grep_files(e["old"], roots=("docs", "reverse"))} - done)
    if any(CODE_IDENTITY_BASELINE in ctx.grep_files(e["old"], roots=FROZEN_KEYED) for e in entries):
        plan.warnings.append(f"{CODE_IDENTITY_BASELINE} keys {primary['old']}: python3 tools/repair_queue.py retire "
                             f"identity {primary['source']} in the next commit (it refuses while HEAD holds the row)")
    return plan


DIR32 = 6
REL32 = 20


def object_symbol_relocs(ctx, source, name):
    """[(offset, type, target)] of `name`'s body in `source`'s rebuilt object; [] when it cannot be
    read. Tests replace this through ctx.object_symbol_relocs."""
    hook = getattr(ctx, "object_symbol_relocs", None)
    if hook:
        return hook(source, name)
    import build
    try:
        return list(build.read_object_symbol_bytes(build.obj_path(ctx.path(source)), name, code_only=True)[1])
    except (OSError, SystemExit, ValueError, KeyError, IndexError):
        return []


def object_symbol_relocs_or_none(ctx, source, name):
    """As object_symbol_relocs, but None when the body cannot be read: a leaf's empty list is a finding, so an
    unread body must not look like one."""
    hook = getattr(ctx, "object_symbol_relocs", None)
    if hook:
        return hook(source, name)
    import build
    try:
        return list(build.read_object_symbol_bytes(build.obj_path(ctx.path(source)), name, code_only=True)[1])
    except (OSError, SystemExit, ValueError, KeyError, IndexError):
        return None


def retail_body_problem(name, at, size, code, relocs, rows):
    """Why the body `code` with `relocs` is not retail's at `at`, or None: its bytes outside the relocated
    words, and each relocated word's retail target a row of the relocation's own symbol. A target with no
    row or a kind this cannot read refuses: unread never passes."""
    import retail_identity
    if len(code) < size:
        return f"{name} is {len(code)} bytes, its row {size}"
    if len(code) > size and any(code[size:]):
        return f"{name} runs past its row's {size} bytes"
    retail = bytearray(retail_identity.read_retail(at, size))
    ours = bytearray(code[:size])
    for offset, kind, target in relocs:
        if offset + 4 > size:
            return f"{name} has a relocation past its row at +{offset}"
        word = int.from_bytes(retail[offset:offset + 4], "little", signed=kind == REL32)
        if kind == REL32:
            want = at + offset + 4 + word
        elif kind == DIR32:
            want = word - 0x400000
        else:
            return f"{name} has a relocation of type {kind} at +{offset} this cannot compare"
        if not any(r["name"] == target and _rva(r.get("target_rva")) == want for r in rows):
            return f"{name} binds {target} at +{offset}, and no row of that name is retail's 0x{want:08X}"
        retail[offset:offset + 4] = ours[offset:offset + 4] = b"\0\0\0\0"
    if retail != ours:
        return f"{name}'s bytes differ from retail at 0x{at:08X}"
    return None


def forced_move_problems(ctx, identity):
    """The owner's mechanical proof of each --forced-move on the rebuilt objects: the old file no longer
    defines the symbol or refers to it, the new file defines the same body (tu_skeleton.transfer_problem),
    that body is retail's, and the map still gives every row the unit it gave before: a move never
    approves anything."""
    import build
    import tu_skeleton
    moves = identity.get("forced", ())
    if not moves:
        return []
    problems = []
    written = ctx.path(FUNCTIONS).read_bytes().decode("utf-8", "surrogateescape")
    rows = list(csv.DictReader(io.StringIO(written)))
    for m in moves:
        objects = {m["old"]: forced_move_object(ctx, m["old"]), m["dest"]: forced_move_object(ctx, m["dest"])}
        why = tu_skeleton.transfer_problem(m["name"], m["old"], m["dest"], objects, {m["name"]: m["before"]})
        if why:
            problems.append(f"0x{m['rva']:08X} {m['name']} forced from {m['old']}: {why}")
            continue
        named = forced_move_references(objects[m["old"]], m["name"])
        if named is None:
            problems.append(f"{m['old']}'s rebuilt object cannot be read for {m['name']}: inconclusive")
            continue
        if named:
            problems.append(f"{m['old']}'s rebuilt object still refers to {m['name']}: the rename has not retired it there")
            continue
        try:
            code, relocs = build.read_object_symbol_bytes(objects[m["dest"]], m["name"], code_only=True)[:2]
        except (OSError, SystemExit, ValueError, KeyError, IndexError) as error:
            problems.append(f"{m['dest']}'s body of {m['name']} cannot be read: {error}")
            continue
        why = retail_body_problem(m["name"], m["rva"], m["size"], bytes(code), list(relocs), rows)
        if why:
            problems.append(f"0x{m['rva']:08X} forced to {m['dest']}: {why}")
    units = map_units(ctx)
    changed = sorted(at for at in set(units) | set(identity["units_before"])
                     if units.get(at) != identity["units_before"].get(at))
    if changed:
        problems.append(f"the map would change at 0x{changed[0]:08X} ({len(changed)} row(s)): {identity['units_before'].get(changed[0])} "
                        f"-> {units.get(changed[0])}; a forced move approves nothing")
    return problems


def retail_identity_problems(ctx, identity):
    """What the rebuilt objects say against a retail respell: the copy no longer binding the class's
    table, a respelled row with no references, a wrong binding new to a touched source, or a forced
    move its objects do not prove."""
    import allowed_symbols
    try:
        refs = identity_refs(ctx, identity["sources"])
    except allowed_symbols.UnverifiedFunclet as error:
        return [f"the code-identity scan cannot read the rebuilt units: {error}"]
    problems = forced_move_problems(ctx, identity)
    leaves = identity.get("leaves", {})
    table_stores = identity.get("table_stores", {})
    for at, _old, new in identity["rows"]:
        if at in table_stores:
            source, name, offset = table_stores[at]
            relocs = object_symbol_relocs_or_none(ctx, source, name)
            if relocs is None:
                problems.append(f"{new} (0x{at:08X}), which stores the table, cannot be read after the respell")
            elif (offset, DIR32, identity["table_name"]) not in relocs:
                problems.append(f"{new} (0x{at:08X}) does not store {identity['table_name']} at +{offset} after the respell")
            continue
        if at in leaves:
            relocs = object_symbol_relocs_or_none(ctx, leaves[at][0], leaves[at][1])
            if relocs is None:
                problems.append(f"the declared leaf {new} (0x{at:08X}) cannot be read after the respell")
            elif relocs:
                problems.append(f"the declared leaf {new} (0x{at:08X}) has {len(relocs)} relocation(s) after the respell")
            continue
        if not any(r["row"] == new and r["rva"] == at for r in refs):
            problems.append(f"{new} (0x{at:08X}) has no references after the respell")
    if "operands" in identity:
        if not identity["operands"]:
            problems.append("a slot-and-operand family has no operands to check")
        for source, name, offset, kind, target in identity["operands"]:
            relocs = object_symbol_relocs_or_none(ctx, source, name)
            if relocs is None:
                problems.append(f"{name}, whose operands prove the element, cannot be read after the respell ({source})")
            elif (offset, kind, target) not in relocs:
                problems.append(f"{name} does not bind {target} at +{offset} after the respell ({source})")
    elif "bindings" in identity:
        if not identity["bindings"]:
            problems.append("a family with no table has no bindings to check")
        for source, name, offset, target in identity["bindings"]:
            if (offset, REL32, target) not in object_symbol_relocs(ctx, source, name):
                problems.append(f"{name} does not bind {target} at +{offset} after the respell ({source})")
        written = ctx.path(SYMBOLS).read_bytes().decode("utf-8") if ctx.path(SYMBOLS).exists() else ""
        left = {(p.get("name", ""), _rva(p.get("address"))) for p in csv.DictReader(io.StringIO(written))}
        for name, at, _member in identity.get("retired", ()):
            if (name, at) in left:
                problems.append(f"pin {name} at 0x{at:08X} is still in {SYMBOLS}")
            if any(r["symbol"] == name for r in refs):
                problems.append(f"a rebuilt object still binds the retired pin {name}")
        names = sorted({name for name, _at, _member in identity.get("retired", ())})
        if names:
            problems += object_pin_references(source_objects(ctx, identity["sources"]), names)
    else:
        relocs = object_symbol_relocs(ctx, identity["copy_source"], identity["copy_name"])
        if (identity["copy_store"], DIR32, identity["table_name"]) not in relocs:
            problems.append(f"{identity['copy_name']} does not store {identity['table_name']} at +{identity['copy_store']} "
                            f"after the respell ({identity['copy_source']})")
    known = {tuple(k) for k in identity["wrong_before"]}
    for r in identity_wrong(refs):
        if _identity_key(r, {}) not in known:
            problems.append(f"{r['row']} in {r['source']} gains a wrong binding of {r['symbol']} "
                            f"at 0x{r['target']:08X} ({r['cls']})")
    return problems


def identity_problems(ctx, identity):
    """What the rebuilt objects say against an identity respell: a respelled row
    with no references, one not bound directly to retail's row (an alias, fold,
    pinned or ICF-marked callee), a retired pin still named, or a wrong binding new
    to a touched source."""
    refs = identity_refs(ctx, identity["sources"])
    problems = []
    # the ledgers as written now (ctx's tables are the plan-time snapshot)
    written = ctx.path(SYMBOLS).read_bytes().decode("utf-8") if ctx.path(SYMBOLS).exists() else ""
    pin_rows = list(csv.DictReader(io.StringIO(written)))
    pins = {(p.get("name", ""), _rva(p.get("address"))) for p in pin_rows}
    pinned = collections.defaultdict(list)
    for p in pin_rows:
        pinned[_rva(p.get("address"))].append(p.get("name", ""))
    rows_now = list(csv.DictReader(io.StringIO(ctx.path(FUNCTIONS).read_bytes().decode("utf-8"))))
    named, notes = callee_marks(rows_now)
    for at, old, new in identity["rows"]:
        own = [r for r in refs if r["row"] == new and r["rva"] == at]
        if not own:
            problems.append(f"{new} (0x{at:08X}) has no code-identity references after the respell")
        elif not any(r["cls"] == "owner" for r in own):
            problems.append(f"{new} (0x{at:08X}) binds no retail row directly after the respell")
        for r in own:
            if not identity_direct(r):
                problems.append(f"{new} (0x{at:08X}) still binds {r['symbol']} at 0x{r['target']:08X} "
                                f"({r['cls']}), not retail's row")
            elif r["cls"] == "owner" and r["target"] != at:
                if pinned.get(r["target"]):
                    problems.append(f"{new} (0x{at:08X}) binds 0x{r['target']:08X}, which carries pin "
                                    f"{pinned[r['target']][0]}")
                folded = folded_callee(named, notes, r["target"])
                if folded:
                    problems.append(f"{new} (0x{at:08X}) binds 0x{r['target']:08X}, which {folded}")
    for name, t, callee in identity.get("retired", ()):
        if (name, t) in pins:
            problems.append(f"pin {name} at 0x{t:08X} is still in {SYMBOLS}")
        if any(r["symbol"] == name for r in refs):
            problems.append(f"a rebuilt object still binds the retired pin {name}")
        if not any(r["symbol"] == callee and r["target"] == t and r["cls"] == "owner"
                   for at, _old, new in identity["rows"] for r in refs if r["row"] == new and r["rva"] == at):
            problems.append(f"no respelled row binds {callee} at 0x{t:08X} directly after the pin is retired")
    if identity.get("retired"):
        names = sorted({name for name, _t, _c in identity["retired"]})
        problems += object_pin_references(source_objects(ctx, identity["sources"]), names)
        if (ctx.root / "tools/pin_consistency.py").exists():
            result = subprocess.run([sys.executable, "tools/pin_consistency.py", "--check"], cwd=str(ctx.root),
                                    capture_output=True, text=True)
            if result.returncode:
                problems.append("pin_consistency --check: " + (result.stdout + result.stderr).strip()[-300:])
    known = {tuple(k) for k in identity["wrong_before"]}
    for r in identity_wrong(refs):
        if any(r["row"] == new and r["rva"] == at for at, _old, new in identity["rows"]):
            continue
        if _identity_key(r, {}) not in known:
            problems.append(f"{r['row']} in {r['source']} gains a wrong binding of {r['symbol']} "
                            f"at 0x{r['target']:08X} ({r['cls']})")
    return problems


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
# `function --virtual --access`: the virtual near member's access code, and the
# access each non-virtual code already has (the declaration's label).
VIRTUAL_CODE_OF = {"private": "E", "protected": "M", "public": "U"}
ACCESS_OF_CODE = {"A": "private", "I": "protected", "Q": "public"}
# `class --fold --access`: the near virtual codes a folded destructor family
# may be respelled from, and a deleting destructor's this-adjustor thunk codes
# (G private, O protected, W public; near).
VIRTUAL_NEAR_CODES = frozenset("EMU")
THUNK_CODE_OF = {"private": "G", "protected": "O", "public": "W"}
THUNK_NEAR_CODES = frozenset("GOW")
# A shared body: the row notes record an ICF fold or an alias.
FOLD_NOTES = re.compile(r"fold-proof=|icf-owner=|dup-of=|\bICF\b", re.I)
VIRTUAL_MEMBER = re.compile(r"\?([A-Za-z_]\w*)@((?:[A-Za-z_]\w*@)+)@")
VIRTUAL_DTOR = re.compile(r"\?\?(1|_G|_E)((?:[A-Za-z_]\w*@)+)@")
VIRTUAL_STREAM = re.compile(r"\?\?(6)((?:[A-Za-z_]\w*@)+)@")
INSTALLER_CLASS = re.compile(r"\?\?(?:0|1|_G|_E)([A-Za-z_]\w*)@")
VTABLE_NAME = re.compile(r"\?\?_7([A-Za-z_]\w*)@")
DECLSPEC = re.compile(r"__declspec\s*\([^()]*\)")


def member_function_header(mangled):
    """(index of the access code, class, enclosing scopes, role) of a member
    function's decorated name; role is `method` (?f@C@@), `dtor` (??1C@@) or
    `deleting` (??_GC@@, ??_EC@@), or `stream` (??6C@@). Other operators,
    free functions, constructors, templates and funclets are refused."""
    role = "method"
    match = VIRTUAL_MEMBER.match(mangled)
    if not match:
        match = VIRTUAL_DTOR.match(mangled)
        if not match:
            match = VIRTUAL_STREAM.match(mangled)
            if not match:
                raise Refusal(f"{mangled} is not a method, destructor or supported stream operator this mode "
                              "can respell (constructors, other operators, templates and funclets are not)")
            role = "stream"
        else:
            role = "dtor" if match.group(1) == "1" else "deleting"
    scopes = match.group(2).rstrip("@").split("@")
    if role == "stream" and len(scopes) != 1:
        raise Refusal(f"{mangled}: stream virtual respell currently requires a global non-template class")
    at = match.end()
    try:
        end = _parse_header(mangled, at, _Out())
    except (IndexError, ValueError) as error:
        raise Refusal(f"{mangled}: cannot read its decoration ({error})") from None
    if end != len(mangled):
        raise Refusal(f"{mangled}: trailing {mangled[end:]!r} after its decoration")
    return at, scopes[0], scopes[1:], role


def virtual_stream_operand(mangled, at):
    """The supported exact operator<<(bool/int64) signature, never just its word.

    These non-const thiscall overloads return their own class by reference.
    Other parameter/return/cv shapes need their own declaration selector.
    """
    match = re.fullmatch(r"AEAAV0@(_N|_J|_K)@Z", mangled[at + 1:])
    if not match:
        raise Refusal(f"{mangled}: stream virtual respell supports only non-const thiscall operator<< "
                      "returning its class by reference and taking bool, __int64 or unsigned __int64")
    return {"_N": "bool", "_J": "__int64", "_K": "unsigned __int64"}[match.group(1)]


def virtual_symbol(mangled, access=None):
    """`mangled` with its access code respelled virtual (QAE -> UAE, IAE ->
    MAE, AAE -> EAE); identifier, scope, cv, convention, return type and
    parameters are kept byte for byte. `access` ('public', 'protected' or
    'private') picks the virtual member's access instead of keeping the
    row's (QAE -> MAE for 'protected')."""
    at, _cls, _scopes, role = member_function_header(mangled)
    code = mangled[at]
    if code in VIRTUAL_ACCESS:
        raise Refusal(f"{mangled} is already spelled virtual")
    if code not in NONVIRTUAL_ACCESS:
        raise Refusal(f"{mangled} is not a non-static member function (access code {code!r}): only a member "
                      "function can be virtual")
    if access is not None and access not in VIRTUAL_CODE_OF:
        raise Refusal(f"--access {access!r} is not one of {', '.join(sorted(VIRTUAL_CODE_OF))}")
    if role == "stream":
        virtual_stream_operand(mangled, at)
    virtual = NONVIRTUAL_ACCESS[code] if access is None else VIRTUAL_CODE_OF[access]
    return mangled[:at] + virtual + mangled[at + 1:]


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


def virtual_declarations(code, cls, word=None, *, stream_operand=None):
    """[(offset, already virtual)] of each in-class declaration of member
    function `word` (or of `~cls` when `word` is None) directly in a body of
    class `cls` in stripped `code`. A call, initializer or friend declaration
    is not one; a static or template member, or two declarations in one body
    (an overload set: which one retail made virtual is not read here), is
    refused. The supported stream overload is selected by its exact primitive
    operand and class-reference return type; its siblings are untouched."""
    if stream_operand is not None:
        if word != "operator<<" or stream_operand not in ("bool", "__int64", "unsigned __int64"):
            raise Refusal("unsupported virtual stream declaration selector")
        target = re.compile(r"(?<![\w~:.>])operator\s*<<\s*\(")
    else:
        target = re.compile(r"~\s*%s\s*\(" % re.escape(cls) if word is None
                            else r"(?<![\w~:.>])%s\s*\(" % re.escape(word))
    shown = f"~{cls}" if word is None else word
    out = []
    for start, end in class_bodies(code, cls):
        if stream_operand is not None and _brace_depth(code, 0, start) != 1:
            # The supported decoration names a global class. A same-spelled
            # class in a namespace or another class is a different type.
            continue
        found = []
        for match in target.finditer(code, start, end):
            if _brace_depth(code, start, match.start()):
                continue
            if stream_operand is not None:
                close = code.find(")", match.end(), end)
                if close < 0:
                    raise Refusal(f"class {cls} has an unterminated stream declaration")
                operand = re.escape(stream_operand).replace(r"\ ", r"\s+")
                if stream_operand == "__int64":
                    operand = r"(?:signed\s+)?" + operand
                params = code[match.end():close].strip()
                if not re.fullmatch(r"(?:const\s+)?" + operand +
                                    r"(?:\s+const)?(?:\s+[A-Za-z_]\w*)?", params):
                    continue
                # A const member is a different overload from the non-const
                # member the decoration identifies. Parameter const is above.
                suffix = re.split(r"[;{]", code[close + 1:end], maxsplit=1)[0]
                if re.search(r"\b(?:const|volatile)\b|&", suffix):
                    continue
            begin = _statement_start(code, start, match.start())
            bare = DECLSPEC.sub(" ", code[begin:match.start()])
            if re.search(r"[(){}=,?;]|(?<!:):(?!:)", bare) or re.search(r"\b(?:friend|typedef)\b", bare):
                continue
            if re.search(r"\b(?:static|template)\b", bare):
                raise Refusal(f"class {cls} declares {shown} static or as a template")
            if stream_operand is not None:
                returned = re.sub(r"\b(?:virtual|inline|__forceinline|__thiscall)\b", " ", bare).strip()
                if not re.fullmatch(r"(?:::)?" + re.escape(cls) + r"\s*&", returned):
                    raise Refusal(f"class {cls}'s {shown}({stream_operand}) does not return {cls}&")
            found.append((begin, bool(re.search(r"\bvirtual\b", bare))))
        if len(found) > 1:
            raise Refusal(f"class {cls} declares {shown} {len(found)} times in one body (an overload set): "
                          "which one retail made virtual is not read here")
        out += found
    return out


def _member_declaration_end(code, begin, end):
    """The offset just past the member declaration starting at `begin` in a
    class body ending at `end` of stripped `code`: its `;`, or the close of
    an inline body (and a `;` right after that)."""
    def paren_close(at):
        depth = 0
        for index in range(at, end):
            depth += {"(": 1, ")": -1}.get(code[index], 0)
            if depth == 0:
                return index
        raise Refusal("a member declaration runs past its class body")
    opened = code.find("(", begin, end)
    if opened < 0:
        raise Refusal("a member declaration without a parameter list cannot take an access label")
    at = paren_close(opened) + 1
    while at < end:
        char = code[at]
        if char == ";":
            return at + 1
        if char == "{":
            at = name_metric.close(code, at) + 1
            follow = at
            while follow < end and code[follow].isspace():
                follow += 1
            return follow + 1 if follow < end and code[follow] == ";" else at
        if char == "(":
            at = paren_close(at) + 1
            continue
        at += 1
    raise Refusal("a member declaration runs past its class body")


def access_at(code, start, begin):
    """The access in force at `begin` inside the class body that opens at
    `start` in stripped `code`: the last label at the body's own depth, else
    the class key's default (`class`: private, `struct`/`union`: public)."""
    label = None
    for match in ACCESS.finditer(code, start, begin):
        if not _brace_depth(code, start, match.start()):
            label = match.group(0).split(":")[0].strip()
    if label:
        return label
    keys = list(re.finditer(r"\b(class|struct|union)\b", code[:code.rfind("{", 0, start)]))
    return "private" if keys and keys[-1].group(1) == "class" else "public"


def respell_virtual_text(text, cls, word, pairs, *, stream_operand=None, access=None):
    """(new text, declarations made virtual, mangled spellings respelled) for
    one file: `virtual` before each in-class declaration of `word` (`~cls`
    when None) in class `cls`, then every whole old mangled name of `pairs`
    respelled. A plain string literal spelling an old name is retail-locked
    text: refused. With `access`, a declaration under another access is
    wrapped in that label, and the access it had is restored after it unless
    nothing or another label follows it in the body."""
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
    bodies = class_bodies(code, cls) if access is not None else []
    for begin, already in sorted(virtual_declarations(code, cls, word, stream_operand=stream_operand),
                                 reverse=True):
        label = ""
        if access is not None:
            start, end = next((s, e) for s, e in bodies if s <= begin < e)
            current = access_at(code, start, begin)
            if current != access:
                stop = _member_declaration_end(code, begin, end)
                rest = code[stop:end].lstrip()
                if rest and not ACCESS.match(rest):
                    text = text[:stop] + f" {current}:" + text[stop:]
                label = f"{access}: "
        if not already or label:
            text = text[:begin] + label + ("" if already else "virtual ") + text[begin:]
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


def plan_virtual(ctx, rva, *, evidence="", old=None, max_files=25, prepared=None, access=None):
    """Plan respelling one row (and, for a destructor, its deleting
    destructors, or the reverse) from non-virtual to virtual on retail vtable
    evidence; see the section comment. `prepared` ({rel: bytes}) supplies the
    C++ of units whose view a `virtual` keyword alone cannot make virtual (a
    base held as a member at +0 must become a base class, or the vptr would
    shift every field); each is still respelled, compiled and byte-gated, and
    must spell no old name afterwards. `access` gives the virtual member
    another access than the row's (QAE -> MAE for 'protected'): each
    in-class declaration is put under that label. Raises Refusal; writes
    nothing."""
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
    virtual_symbol(first["name"], access)

    # The group: the row, and for the destructor family every non-virtual
    # ??1 / ??_G / ??_E row of the same class, each on its own evidence.
    scope_text = "@".join([cls] + scopes) + "@@"
    if role in ("method", "stream"):
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
        new_name = virtual_symbol(name, access)
        if is_generated(row["source"]):
            raise Refusal(f"{name} lives in generated source {row['source']}; recover it as real C++ first")
        # The identifier is kept: a method is judged by its word as `function`
        # judges it; a destructor's class token is not renamed, so only the
        # decorated name itself (an export, vendored, evidence-tier, canonical).
        identifier = ("operator<<" if role == "stream" else
                      scope_of(name).rsplit("::", 1)[-1] if role == "method" else name)
        reason = is_protected(ctx, "function", name, rva=at, identifier=identifier)
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

    plan = Plan("function", first["name"], virtual_symbol(first["name"], access), "virtual",
                " ".join((evidence or "").split()), first["source"], rva, virtual=True)
    prepared_rels = set(prepared or {})
    _batch_source_edits(ctx, plan, prepared)
    plan.evidence = "; ".join(f"{old} -> {new}: {evidence_of[old]}" for old, new in pairs) + \
        (f"; {access} access requested" if access is not None and
         access != ACCESS_OF_CODE.get(first["name"][_at]) else "") + \
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
    word = ("operator<<" if role == "stream" else
            scope_of(first["name"]).rsplit("::", 1)[-1] if role == "method" else None)
    stream_operand = virtual_stream_operand(first["name"], _at) if role == "stream" else None
    olds = [name for name, _new in pairs]
    candidates = set()
    for name in olds:
        candidates |= set(ctx.grep_files(name))
    declarers = set(ctx.grep_files(cls, word=True))
    search_word = "operator" if role == "stream" else word
    candidates |= declarers & set(ctx.grep_files(search_word, word=True)) if word else declarers
    by_object = object_referencers(ctx, set(olds))
    candidates |= by_object | sources | prepared_rels
    headers, rewritten = [], set(prepared_rels)
    # A unit whose object references an old name but whose own text declares
    # nothing may get its view from a header this plan makes virtual; it is
    # refused only after every candidate is read, when no such header covers it.
    undeclared, declaring_headers = [], set()
    for rel in sorted(candidates):
        data = plan.after.get(rel, ctx.read(rel))
        if data is None:
            raise Refusal(f"{rel} is listed but missing")
        text = data.decode("utf-8", errors="surrogateescape")
        new_text, made, respelled = respell_virtual_text(text, cls, word, pairs,
                                                      stream_operand=stream_operand, access=access)
        if made and not rel.endswith(SOURCE_SUFFIXES):
            declaring_headers.add(rel)
        if rel in prepared_rels:
            left = [name for name in olds if name in new_text]
            if left:
                raise Refusal(f"prepared {rel} still spells {', '.join(left)} after the respell")
        if new_text == text and rel in prepared_rels:
            if rel not in ctx.ledger_sources():
                headers.append(rel)
            continue
        if new_text == text:
            # object_referencers widens to a text match where no current object
            # exists; only a current object naming an old symbol is a consumer
            # this rewrite would miss (name_dependents still builds the rest).
            if rel in by_object and object_confirms(ctx, rel, set(olds)):
                undeclared.append(rel)
            continue
        if is_generated(rel):
            raise Refusal(f"generated source {rel} declares or spells {first['name']}; it is never edited")
        refuse_vendored(ctx, [rel], f"respelling {first['name']}")
        rewritten.add(rel)
        plan.source_counts[rel] = dict(plan.source_counts.get(rel, {}), virtual=made, mangled=respelled)
        plan.edit(ctx, rel, new_text.encode("utf-8", errors="surrogateescape"))
        if not rel.endswith(SOURCE_SUFFIXES) or rel not in ctx.ledger_sources():
            headers.append(rel)
    covered = includers(ctx, sorted(declaring_headers), max_files) if declaring_headers else set()
    for rel in undeclared:
        if rel not in covered:
            raise Refusal(f"{rel}'s object references {', '.join(olds)} but no body of class {cls} there "
                          f"declares {word or '~' + cls} to make virtual, nor does its text spell the name "
                          "(an implicit member or a base's declaration: reconcile the view first)")
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
        sorted(f"file:{rel}" for rel in sources | prepared_rels)
    written = set(plan.after) | {"reverse/re_attempts.log"}
    plan.mentions = sorted({rel for name in olds for rel in ctx.grep_files(name, roots=("docs", "reverse"))}
                           - written)
    return plan


# ---------------------------------------------------------------- function --to-class
#
# A seat that rowed a vftable slot before it knew the slot's class spelled it
# under an address-derived class: `?rva00550B4C@Rva00550B4C@@QAEXXZ`. When the
# real class C is known, every route to its own spelling is refused: `function`
# changes only the identifier, `class --fold` needs special members of the
# placeholder class (a lone slot has none), and `class` would collide with C.
# `function --rva R --to-class C --new WORD` moves the row into C as its
# virtual WORD (cv, convention, return type and parameters kept) on retail
# evidence alone, and refuses without it:
#
# - the row's class is a placeholder (tools/name_metric.py); a readable class
#   is a naming decision, not this mode's;
# - retail tables hold R, and exactly one (table, slot) pair belongs to C: a
#   constructor, destructor or deleting destructor row of C installs that
#   table (the installers table_classes reads; a data_rows.csv name alone is
#   not enough); no table of a class unrelated to C holds R (a fold), and R
#   carries no second row, pin or fold note;
# - the vftable that C's installer units compile from their own views names
#   the new symbol in that slot, and every other slot whose symbol the ledger
#   resolves agrees with retail's table: the declared virtual order matches
#   retail's at that slot. It is read from the current objects when planning
#   (when they are current) and always from the rebuilt objects after
#   ./build.sh (a prepared view change counts only once compiled).
#
# The C++ comes from the caller as prepared sources (`--prepared REL=FILE`):
# the definition under C and any caller spelling the old member. The tool
# owns the ledgers: rows, funclet rows and notes tokens, pins in place, body
# owners, spelled mangled names in any file, `(to-class: retail vftable 0x...
# slot N)` tombstones; it writes no name_basis.csv record (the identifier is
# the one C's own declaration gives that slot) and carries an existing one.

THIS_CV = frozenset("ABCD")   # the `this` qualifier of a near member: none, const, volatile, both

# An int-return placeholder override (`?update@Rva0028F976@@UAEHXZ`): the seat
# that rowed the slot guessed `int` where the base's virtual returns an enum
# (UpdateModuleInterface::update returns UpdateSleepTime), and C++ forbids an
# int override of an enum virtual, so C's view cannot name the slot unless the
# move respells the return type. MSVC returns an int-sized enum (`W4`) in eax
# exactly as it returns an int, so the body cannot tell them apart; the enum
# is a declaration fact. A full mangled --new may respell the return type
# `H` -> `?AW4E@@` (and nothing else of the tail) only when a registered class
# header (reverse/canonical_classes.csv) declares `virtual E WORD(` in C or a
# class C's views derive from (declared_enum_return). The rebuilt vftable must
# still name the respelled symbol in the slot and ./build.sh keep the body
# exact, as for any move.
ENUM_RETURN = re.compile(r"\?AW4([A-Za-z_]\w*)@@")


def enum_return_respelling(tail, new_tail):
    """The enum E when `new_tail` is `tail` (this-cv, convention, return type,
    parameters) of a thiscall member with only its return type respelled from
    int (`H`) to a global int-sized enum (`?AW4E@@`); else None."""
    if len(tail) < 3 or tail[0] not in THIS_CV or tail[1] != "E" or tail[2] != "H":
        return None
    if new_tail[:2] != tail[:2]:
        return None
    match = ENUM_RETURN.match(new_tail, 2)
    if not match or new_tail[match.end():] != tail[3:]:
        return None
    return match.group(1)


def to_class_symbol(old_name, cls, new, *, return_enum=None):
    """The new decorated name: `?WORD@C@@` plus the old access code made
    virtual (or kept virtual) and the old tail (cv, convention, return type,
    parameters); or `new` itself when it is a full mangled name, which must
    keep that tail and spell a virtual near member of C. A full name may
    give `this` another cv than the placeholder guessed (const or not
    compiles to the same body): C's declaration decides, and the compiled
    vftable must name exactly that spelling. With `return_enum` E (the caller
    holds declared_enum_return's evidence), a full name may instead respell
    an int return as enum E (enum_return_respelling)."""
    at, _cls, scopes, role = member_function_header(old_name)
    if role != "method" or scopes:
        raise Refusal(f"{old_name}: --to-class moves an ordinary method of a global class only")
    tail = old_name[at + 1:]
    # A back-reference in the signature is refused: a name one (`PAV1@`) can
    # point at the placeholder class or the identifier the move respells, and
    # an argument-type one (`PAUS@@0@Z`) is kept out too. Only the grammar's
    # name and type positions count: a digit inside an identifier
    # (`PBUCoord3D@@`), an enum's `W4` or an encoded number is no reference.
    try:
        name_refs, type_refs, spans = back_references(old_name)
    except Unparsed as error:
        raise Refusal(f"{old_name}: its decoration cannot be read to rule out back-references ({error})")
    if name_refs or type_refs:
        raise Refusal(f"{old_name}: its parameters name a type by back-reference; a class move would change "
                      "what they refer to")
    tail_names = {old_name[a:b] for a, b in spans if a > at}
    code = old_name[at]
    if new.startswith("?"):
        nat, ncls, nscopes, nrole = member_function_header(new)
        if nrole != "method" or nscopes or ncls != cls:
            raise Refusal(f"{new} is not a method of the global class {cls}")
        if new[nat] not in VIRTUAL_ACCESS:
            raise Refusal(f"{new} is not spelled virtual: a vftable slot proves only a virtual member")
        if new[nat + 1:] != tail and not (new[nat + 1] in THIS_CV and tail[:1] in THIS_CV
                                          and new[nat + 2:] == tail[1:]):
            enum = enum_return_respelling(tail, new[nat + 1:])
            if enum is None or enum != return_enum:
                raise Refusal(f"{new} changes the convention, return type or parameters of {old_name}")
            # The enum's name enters the name table ahead of the parameters: a
            # parameter spelling it, or the class or identifier, would then be
            # decorated as a back-reference, not the kept tail.
            if enum in tail_names or enum in (cls, new[1:new.index("@")]):
                raise Refusal(f"{new}: its return enum {enum} is spelled again in the signature or names the "
                              "class or identifier; the compiler would spell a back-reference")
        _refuse_spelled_in_tail(old_name, tail_names, cls, new[1:new.index("@")])
        return new
    if not IDENT.fullmatch(new or "") or new in name_metric.KEYWORDS:
        raise Refusal(f"{new!r} is not a method identifier")
    if code in VIRTUAL_ACCESS:
        access = code
    elif code in NONVIRTUAL_ACCESS:
        access = NONVIRTUAL_ACCESS[code]
    else:
        raise Refusal(f"{old_name} is not a non-static member function (access code {code!r})")
    _refuse_spelled_in_tail(old_name, tail_names, cls, new)
    return f"?{new}@{cls}@@{access}{tail}"


def _refuse_spelled_in_tail(old_name, tail_names, cls, ident):
    """A signature that already spells the new class or identifier as a name
    would be decorated with a back-reference to it after the move, so the
    kept tail would not be what the compiler emits."""
    for word in (cls, ident):
        if word in tail_names:
            raise Refusal(f"{old_name}: its signature already names {word}; after the move the compiler "
                          "would spell it as a back-reference")


def declared_enum_return(ctx, cls, word, enum, sources, prepared=None):
    """[evidence] that a registered class header declares `virtual ENUM WORD(`
    inside the body of `cls` or of a class `cls`'s views derive from (read from
    each of `sources`, cls's installer units, prepared bytes first, and the
    headers they include):
    the declaration that fixes an int-return placeholder's respelled return
    type (see ENUM_RETURN). Refusal when no registered header does."""
    registered = {}
    for row in ctx.dicts(CANONICAL_CLASSES):
        if row.get("class") and row.get("header"):
            registered.setdefault(row["class"], row["header"])
    ancestors = {cls}
    for rel in sorted(set(sources) - {""}):
        ancestors |= class_chain(prepared_base_map(ctx, rel, prepared), cls)[0]
    pattern = re.compile(r"\bvirtual\s+(?:enum\s+)?%s\s+%s\s*\(" % (re.escape(enum), re.escape(word)))
    evidence = []
    for base in sorted(ancestors & set(registered)):
        header = registered[base]
        code = name_metric.strip((ctx.read(header) or b"").decode("utf-8", "replace"))
        if any(pattern.search(code, start, end) for start, end in class_bodies(code, base)):
            evidence.append(f"{base} (registered, {header}) declares virtual {enum} {word}()")
    if not evidence:
        raise Refusal(f"the move respells {word}'s int return as enum {enum}, but no class registered in "
                      f"{CANONICAL_CLASSES} among {cls} and the bases its views derive from "
                      f"({', '.join(sorted(ancestors - {UNPARSED_BASE})) or 'none'}) declares virtual {enum} "
                      f"{word}( in its header: the enum is a declaration fact, never a guess")
    return evidence


def class_installers(ctx, cls, stores, tables):
    """[(row, displacement)] for each constructor, destructor or deleting
    destructor row of `cls` that installs a table through `stores` (at a
    displacement only when the row also installs a table at +0: the object's
    primary vptr, not a member object's)."""
    import bisect
    primary = sorted(store for _slots, installs in tables.values() for store, disp in installs.items()
                     if disp == 0)
    out = []
    for store, disp in sorted(stores.items()):
        row = row_at(ctx, store)
        match = INSTALLER_CLASS.match(row["name"]) if row else None
        if not match or match.group(1) != cls:
            continue
        start = _rva(row["target_rva"])
        end = start + int(row["target_size"])
        k = bisect.bisect_left(primary, start)
        if disp and not (k < len(primary) and primary[k] < end):
            continue
        if all(r is not row for r, _d in out):
            out.append((row, disp))
    return out


def to_class_evidence(ctx, rva, cls, sources, reviewed=None, base=None, found=None):
    """(table, slot, retail slots, [installer rows], proof) for the one slot of
    a table `cls`'s own special members install that holds `rva`; Refusal
    when there is none, more than one, or a table of an unrelated class holds
    it too. `reviewed` (function --to-class alone) is the code-owned entry in
    tools/retail_identity.py that relates the tables it names, at the slot it
    names, once retail holds all of its facts. `base` (function --to-class
    alone) is a reviewed base-slot entry for a class with no retail table of
    its own: it relates the tables it lists and its dead tables at its slot,
    once retail holds its facts, and then `found['bases']` lists every live
    table holding `rva` with its classes' installer units, whose compiled
    tables to_class_slot_problems judges in place of `cls`'s own."""
    tables = retail_vtables(ctx)
    hits = [(table, index) for table, (slots, _stores) in sorted(tables.items())
            for index, target in enumerate(slots) if target == rva]
    if not hits:
        raise Refusal(f"no retail vftable slot holds 0x{rva:08X}: a class move needs one of {cls}'s slots")
    own, foreign, cleared, based = [], [], [], []
    for table, index in hits:
        slots, stores = tables[table]
        installers = class_installers(ctx, cls, stores, tables)
        where = f"retail table 0x{table + IMAGE_BASE:08X} slot {index}"
        if installers:
            own.append((table, index, slots, [r for r, _d in installers], where))
            continue
        classes = table_classes(ctx, table, stores, tables)
        derived = any(cls in class_chain(class_base_map(ctx, rel), other)[0]
                      for other, (_how, source) in classes.items()
                      for rel in sorted({source, *sources} - {""}))
        if not derived:
            if reviewed and table + IMAGE_BASE in reviewed.tables and index == reviewed.slot:
                cleared.append(table)
                continue
            if base and index == base.slot and (table + IMAGE_BASE in base.tables or table + IMAGE_BASE in base.dead):
                based.append(table)
                continue
            foreign.append(f"{where} belongs to {', '.join(sorted(classes)) or 'no class the ledger names'}")
    if not own and base and based and not foreign:
        return base_slot_evidence(ctx, rva, base, hits, tables, based, found)
    if not own:
        raise Refusal(f"no constructor, destructor or deleting destructor row of {cls} installs a retail table "
                      f"holding 0x{rva:08X} ({'; '.join(foreign[:3]) or 'only unowned tables hold it'})")
    if foreign:
        raise Refusal(f"0x{rva:08X} is also in a table of a class unrelated to {cls} ({'; '.join(foreign[:3])}"
                      f"{f'; and {len(foreign) - 3} more' if len(foreign) > 3 else ''}): "
                      "a shared (folded) body proves no one class's member")
    if reviewed and cleared:
        import retail_identity
        wrong = retail_identity.shared_slot_problems(reviewed)
        if not any(table + IMAGE_BASE == reviewed.table and index == reviewed.slot for table, index, _s, _r, _w in own):
            wrong.insert(0, f"it names table 0x{reviewed.table:08X} slot {reviewed.slot}, which is not {cls}'s own")
        if wrong:
            raise Refusal(f"retail_identity's reviewed entry for 0x{rva:08X} does not hold: {wrong[0]}")
    if len({(table, index) for table, index, _s, _r, _w in own}) != 1:
        raise Refusal(f"0x{rva:08X} sits in {len(own)} slots of {cls}'s own tables "
                      f"({', '.join(w for *_x, w in own)}): which member it is is not read here")
    table, index, slots, installers, where = own[0]
    first = installers[0]
    proof = (f"{where}, installed by {first['name']} at 0x{_rva(first['target_rva']):08X}"
             + (f" and {len(installers) - 1} more {cls} special member(s)" if len(installers) > 1 else "")
             + (f"; {len(cleared)} table(s) cleared by retail_identity's reviewed entry: "
                + ", ".join(f"0x{t + IMAGE_BASE:08X}" for t in cleared) if cleared else ""))
    return table, index, slots, installers, proof


def base_slot_evidence(ctx, rva, base, hits, tables, based, found):
    """to_class_evidence's answer under a reviewed base-slot entry (retail_identity.BASE_SLOTS): every table holding
    `rva` is related by a view or listed, retail holds the entry's facts, and nothing reaches its dead tables. The
    compiled check then reads each live table's own classes (`found['bases']`): `cls` has no table to compile."""
    import retail_identity
    wrong = retail_identity.base_slot_problems(base)
    if wrong:
        raise Refusal(f"retail_identity's reviewed base entry for 0x{rva:08X} does not hold: {wrong[0]}")
    if {index for _table, index in hits} != {base.slot}:
        raise Refusal(f"0x{rva:08X} sits outside slot {base.slot} of some table: the base entry names that slot alone")
    records = []
    for table, _index in hits:
        if table + IMAGE_BASE in base.dead:
            continue
        slots, stores = tables[table]
        classes = table_classes(ctx, table, stores, tables)
        listed = base.tables.get(table + IMAGE_BASE)
        if listed and listed[0] not in classes:
            raise Refusal(f"retail_identity's base entry names table 0x{table + IMAGE_BASE:08X} {listed[0]}'s, but "
                          f"its installers are {', '.join(sorted(classes)) or 'no class the ledger names'}'s")
        for other, (_how, source) in sorted(classes.items()):
            if source:
                records.append({"cls": other, "table": table, "retail": list(slots), "sources": [source]})
    if not records:
        raise Refusal(f"no live table holding 0x{rva:08X} has an installer unit to compile it")
    name = next((key for key, value in vars(retail_identity).items() if value is base), "a BASE_SLOTS entry")
    if found is not None:
        found["bases"] = records
        found["where"] = f"slot {base.slot} of the {len(base.tables)} tables in retail_identity.{name}"
    live = sorted({r["table"] for r in records})
    proof = (f"slot {base.slot} of {len(live)} retail tables of classes with no {base.cls} table between them; "
             f"{len(based) - len(base.dead)} related by retail_identity's reviewed base entry (each built by a data "
             f"factory ModuleFactory registers), {len(base.dead)} dead: "
             + ", ".join(f"0x{t:08X}" for t in sorted(base.dead)))
    return live[0], base.slot, records[0]["retail"], [], proof


REAL_LINK_REPO = "Open-BFME/Open-BFME-2"


def _gh(*args, timeout=120):
    return subprocess.run(["gh", *args], capture_output=True, text=True, timeout=timeout)


def newest_real_link(ctx):
    """{'commit', 'run', 'bridged': {retail table rva}} for the newest successful real link on master, listed afresh
    at every call (each admission: planning and again after ./build.sh), or None when it cannot be read, which
    excuses nothing. Its own vtable_bridge_queue.tsv is downloaded under build/rename/real_link/<commit>/ and reused
    only while that commit is still the newest. Tests replace this."""
    try:
        import csv
        listed = _gh("run", "list", "--repo", REAL_LINK_REPO, "--workflow", "real-link.yml", "--branch", "master",
                     "--status", "success", "--limit", "1", "--json", "databaseId,headSha")
        runs = json.loads(listed.stdout or "[]") if listed.returncode == 0 else []
        if not runs:
            return None
        commit, run = runs[0]["headSha"], runs[0]["databaseId"]
        cached = ctx._cache.get("_newest_real_link")
        if cached and cached["commit"] == commit:
            return cached
        where = ctx.path(f"build/rename/real_link/{commit}")
        queue = where / "vtable_bridge_queue.tsv"
        if not queue.exists():
            got = _gh("run", "download", str(run), "--repo", REAL_LINK_REPO, "-n", f"real-link-{commit}",
                      "-D", str(where), timeout=1800)
            if got.returncode:
                return None
        csv.field_size_limit(2 ** 31 - 1)
        with open(queue, encoding="utf-8", newline="") as handle:
            bridged = {int(row["retail_rva"], 16) for row in csv.DictReader(handle, delimiter="\t")
                       if row.get("state") == "bridged"}
        link = {"commit": commit, "run": run, "bridged": bridged}
        ctx._cache["_newest_real_link"] = link
        return link
    except Exception:                                   # noqa: BLE001 - an unreadable link excuses nothing
        return None


def base_slot_compiled_problems(ctx, check, *, current=True):
    """to_class_slot_problems under a base entry: each live table's classes' installer units compile that class's
    table. A copy's name at the slot must be the moved body (`check['rva']`): its row, pin or the moved name; an
    /alternatename is never followed. A copy naming anything else there refuses when it agrees with retail at its
    other resolved slots (a wrong identity), bridged or not. One that already differs from retail at another slot,
    or where nothing else resolves, is reported and does not refuse, but only while the newest real link, read again
    at this admission, bridges its table; otherwise it refuses too. Each call's reports replace `check['reports']`. A
    copy that names the moved body and agrees with retail elsewhere proves the move; after ./build.sh one must."""
    slot, new, moved = check["slot"], check["new"], check["rva"]
    address = {}
    for row in ctx.rows():
        at = _rva(row.get("target_rva"))
        if at is not None and row.get("status") == "matched":
            address.setdefault(row["name"], at)
    for pin in ctx.pins():
        at = _rva(pin.get("address"))
        if at is not None:
            address.setdefault(pin.get("name", ""), at)
    address[new] = moved
    reports = check["reports"] = []
    state = {}

    def link():
        if "link" not in state:
            state["link"] = newest_real_link(ctx)
        return state["link"]
    reach = address.get
    problems, proved = [], 0
    for record in check["bases"]:
        retail = record["retail"]
        for rel in record["sources"]:
            compiled = compiled_vtables(ctx, rel, current=current) or {}
            for symbol, names in sorted(compiled.items()):
                if _vtable_class(symbol) != record["cls"] or slot >= len(names) or not names[slot]:
                    continue
                if reach(names[slot]) == moved:
                    continue
                agree = {j for j, name in enumerate(names) if j != slot and j < len(retail)
                         and (reach(name) == retail[j] or deleting_slot_agrees(name, record["cls"], retail[j], address))}
                clash = sorted(j for j, name in enumerate(names) if j != slot and reach(name) is not None
                               and (j >= len(retail) or not same_slot_body(ctx, reach(name), retail[j])))
                what = f"{rel}'s {symbol} slot {slot} names {names[slot]}, not {new}"
                if agree and not clash:
                    problems.append(what + " (it agrees with retail elsewhere: a wrong identity)")
                    continue
                table = f"0x{record['table'] + IMAGE_BASE:08X}"
                differs = (f"it already differs from retail table {table} at slot(s) {', '.join(map(str, clash))}"
                           if clash else f"nothing else in it resolves against retail table {table}")
                now = link()
                if now and record["table"] in now["bridged"]:
                    reports.append(f"{what}: {differs}, and real link run {now['run']} at {now['commit'][:10]} "
                                   "bridges that table; reported, not refused")
                    continue
                problems.append(f"{what} ({differs}, and " + (f"real link {now['commit'][:10]} does not bridge it"
                                if now else "the newest real link's bridge queue could not be read") + ")")
        sub_check = {"cls": record["cls"], "table": record["table"], "slot": slot, "new": new,
                     "retail": record["retail"], "sources": record["sources"]}
        if any(_vtable_class(symbol) == record["cls"] for rel in record["sources"]
               for symbol in (compiled_vtables(ctx, rel, current=current) or {})) \
                and not to_class_slot_problems(ctx, sub_check, current=current):
            proved += 1
    if not current and not proved:
        problems.append(f"no installer unit of a table holding slot {slot} compiles a copy that names {new} there "
                        "and agrees with retail elsewhere")
    return problems


def record_base_reports(ctx, plan):
    """After the rebuilt check of a base-slot move: print its final reports as warnings and write each into the
    move's tombstones in deleted_rows.csv, the record of the move."""
    reports = plan.to_class.get("reports") or []
    for report in reports:
        print(f"rename: warning: {report}")
        if report not in plan.warnings:
            plan.warnings.append(report)
    if not reports:
        return
    raw = ctx.read(DELETED) or b""
    for old_row, at, reason in plan.to_class.get("tombstones") or ():
        before = tombstone_line(old_row, at, reason)
        after = tombstone_line(old_row, at, reason[:-1] + "; reported: " + " | ".join(reports) + ")")
        if raw.count(before) != 1:
            raise VerifyFailed(f"the tombstone of {old_row} is not where the move wrote it; every file restored")
        raw = raw.replace(before, after)
    ctx.path(DELETED).write_bytes(raw)
    plan.after[DELETED] = raw


def _source_object(ctx, rel, current=True):
    """The object of ledger source `rel`, or None when it has none (or, with
    `current`, none compiled from the present text)."""
    import build
    import name_dependents
    rows = [r for r in ctx.rows() if r.get("source") == rel]
    objects = name_dependents._row_objects(rows).get(rel, [])
    digest = build._hash_file(str(ctx.path(rel))) if ctx.path(rel).exists() else None
    for path in objects:
        if not path.exists():
            continue
        if current and not name_dependents.compiled_from(path, digest):
            continue
        return path
    return None


def external_vtables(ctx, rel, current=True):
    """{`??_7...` symbol} that the object of ledger source `rel` references
    without defining (a constructor storing the real table another unit
    emits); None when it has no object (as compiled_vtables)."""
    import build
    path = _source_object(ctx, rel, current)
    if path is None:
        return None
    symbols = build.read_object_symbols(path.read_bytes())
    defined = {s.get("name") for s in symbols if s.get("section", 0) > 0}
    return {s.get("name") for s in symbols
            if (s.get("name") or "").startswith("??_7") and s.get("section", 0) == 0
            and s.get("storage") == 2 and s.get("name") not in defined}


def compiled_vtables(ctx, rel, current=True):
    """{`??_7...` symbol: [slot target names]} that the object of ledger source
    `rel` defines; None when it has no object (or, with `current`, none
    compiled from the present text)."""
    import build
    path = _source_object(ctx, rel, current)
    if path is not None:
        out = {}
        for symbol in build.read_object_symbols(path.read_bytes()):
            name = symbol.get("name") or ""
            if not name.startswith("??_7") or symbol.get("section", 0) <= 0 or name in out:
                continue
            data, relocs = build.read_object_symbol_bytes(path, name)
            names = {}
            for offset, _type, target in relocs:
                if offset % 4 == 0:
                    names.setdefault(offset // 4, target)
            out[name] = [names.get(i, "") for i in range(max(names) + 1)] if names else []
        return out
    return None


def retail_jump(ctx, rva):
    """Where the `jmp rel32` (E9) at retail .text `rva` lands, or None when
    the instruction there is not one or lands outside .text (any byte can be
    0xE9: build.follow_thunk's bound). Read from the md5-verified retail
    image (build.exe_image)."""
    key = "_retail_jump"
    cache = ctx._cache.setdefault(key, {})
    if rva in cache:
        return cache[rva]
    import struct
    import build
    image, sections = build.exe_image()
    text = next(s for s in sections if s["name"] == ".text")
    lo, hi = text["rva"], text["rva"] + text["size"]
    target = None
    if lo <= rva < hi:
        try:
            offset = build.rva_to_file_offset(sections, rva)
        except ValueError:
            offset = None
        stub = image[offset:offset + 5] if offset is not None else b""
        if len(stub) == 5 and stub[0] == 0xE9:
            landed = (rva + 5 + struct.unpack_from("<i", stub, 1)[0]) & 0xFFFFFFFF
            target = landed if lo <= landed < hi else None
    cache[rva] = target
    return target


def same_slot_body(ctx, ours, theirs):
    """Does a slot whose name the ledger places at `ours` call the body retail's
    slot word `theirs` calls? Equal addresses, or one side's entry is a single
    `jmp rel32` to the other, or both are a single `jmp rel32` to one body.
    BFME 2's empty `X::loadPostProcess() { Base::loadPostProcess(); }`
    overrides compile to one ICF-folded `jmp` (retail 0x00497805 is
    `jmp 0x0058B03E`, UpdateModule::loadPostProcess's row), so a view that
    inherits the base's slot calls the same code at that slot. Only one hop is
    followed on each side: a chain proves no more, and a jump anywhere else
    is still a different body."""
    if ours == theirs:
        return True
    hop_ours, hop_theirs = retail_jump(ctx, ours), retail_jump(ctx, theirs)
    return hop_theirs == ours or hop_ours == theirs or (hop_ours is not None and hop_ours == hop_theirs)


def _vtable_class(symbol):
    """The class a `??_7Class@@6B...` symbol names, else None."""
    match = VTABLE_NAME.match(symbol or "")
    return match.group(1) if match else None


def deleting_slot_agrees(name, cls, word, address):
    """Does slot name `name` of class `cls`'s own compiled table agree with retail's slot `word`
    because it is the deleting destructor? The compiler's table names the vector deleting
    destructor ??_E, where retail's table holds the scalar one rowed ??_G (MSVC folds the two):
    342 of 342 compiled tables sampled do so. That counts only for this class's own ??_E, unrowed,
    with this class's ??_G row at exactly that word: no general equivalence of the two names."""
    found = special_member(name)
    return bool(found and found[0] == "_E" and found[1] == cls and name not in address
                and address.get("??_G" + name[len("??_E"):]) == word)


def to_class_slot_problems(ctx, check, *, current=True):
    """Why the vftable `check['cls']`'s installer units compile does not name
    `check['new']` in retail's slot `check['slot']`: [] when every installer
    object agrees. With `current`, a source whose object is stale is skipped
    (planning); otherwise a missing object is a problem (after ./build.sh).
    Another slot agrees when its name's address is retail's word; it clashes
    unless both reach one body through a single `jmp rel32` (same_slot_body),
    which neither agrees nor clashes. An installer whose object defines no
    `??_7` of the class but references one (it stores the table another unit
    emits) compiles no copy to judge and is passed over; so is a stand-in
    installer, whose copies of the class's tables name nothing the ledger
    resolves (neither a row, a pin nor a moved name: no slot agrees or
    clashes) under `??_7` symbols no other installer compiles: a destructor
    scaffold whose view keeps placeholder bases (Rva004DF7C2Derived.cpp's
    one-slot `??_7ObjectWeaponStatusHelper@@6BRva004DF8A9_B2@@@`), whose tables
    no constructor table shares a name with. After ./build.sh at least one
    installer must still compile a matching table.

    A batch (`check['moved']` {new symbol: rva}, `check['slots']` {slot: new
    symbol}; plan_to_class with --also) moves several slots of one table at
    once: each moved name resolves to its row's address, so each moved slot
    is judged against the others, and every moved slot must agree with at
    least one slot other than itself and clash with none.

    A retail table of exactly one slot has no other slot to agree with: a
    compiled copy of exactly one slot that names the moved symbol in it is
    the matching table (the plan already proved the class's special member
    installs that table and that no other table holds the address).

    A compiled ??_E of the class agrees with retail's ??_G row of that class in
    its slot (deleting_slot_agrees).

    Under a base entry (`check['bases']`, base_slot_evidence) the class has no
    table: base_slot_compiled_problems judges the tables' own classes."""
    if check.get("bases"):
        return base_slot_compiled_problems(ctx, check, current=current)
    cls, retail = check["cls"], check["retail"]
    wanted = {int(k): v for k, v in (check.get("slots") or {check["slot"]: check["new"]}).items()}
    address = {}
    for row in ctx.rows():
        at = _rva(row.get("target_rva"))
        if at is not None and row.get("status") == "matched":
            address.setdefault(row["name"], at)
    for pin in ctx.pins():
        at = _rva(pin.get("address"))
        if at is not None:
            address.setdefault(pin.get("name", ""), at)
    address.update(check.get("moved") or {})
    problems, proved, referencing, standins, judged = [], 0, [], [], set()
    for rel in check["sources"]:
        tables = compiled_vtables(ctx, rel, current=current)
        if tables is None:
            if not current:
                problems.append(f"{rel} has no object to read {cls}'s vftable from")
            continue
        if cls not in {_vtable_class(symbol) for symbol in tables}:
            external = external_vtables(ctx, rel, current=current) or set()
            if cls in {_vtable_class(symbol) for symbol in external}:
                referencing.append(rel)
                continue
        verdicts = []
        for symbol, names in sorted(tables.items()):
            match = VTABLE_NAME.match(symbol)
            if not match or match.group(1) != cls:
                continue
            agree = {j for j, name in enumerate(names) if j < len(retail)
                     and (address.get(name) == retail[j] or deleting_slot_agrees(name, cls, retail[j], address))}
            clash = {j for j, name in enumerate(names) if name in address
                     and (j >= len(retail) or not same_slot_body(ctx, address[name], retail[j]))}
            # each moved slot is judged by the slots other than itself
            agreeing = min(len(agree - {k}) for k in wanted)
            differing = max(len(clash - {k}) for k in wanted)
            # A one-slot retail table has no other slot to agree with. Its
            # compiled copy proves itself when it too is exactly one slot and
            # that slot names the moved symbol (re_attempts 0x004B8851).
            if (not agreeing and not differing and len(retail) == 1 and len(names) == 1
                    and set(wanted) == {0} and names[0] == wanted[0]):
                agreeing = 1
            verdicts.append((symbol, names, agreeing, differing))
        if verdicts and not any(name in address or name in wanted.values()
                                for _s, names, _a, _c in verdicts for name in names):
            standins.append((rel, {s for s, _n, _a, _c in verdicts}))
            continue
        judged |= {s for s, _n, _a, _c in verdicts}
        matching = [v for v in verdicts if v[2] and not v[3]]
        if not matching:
            seen = "; ".join(f"{s}: {a} slot(s) agree, {c} differ" for s, _n, a, c in verdicts)
            problems.append(f"{rel} compiles no {cls} vftable that matches retail table "
                            f"0x{check['table'] + IMAGE_BASE:08X} ({seen or 'no ??_7' + cls + ' at all'})")
            continue
        proved += 1
        for symbol, names, _agree, _clash in matching:
            for slot, new in sorted(wanted.items()):
                spelled = names[slot] if slot < len(names) else "(no such slot)"
                if spelled != new:
                    where = [j for j, name in enumerate(names) if name == new]
                    problems.append(f"{rel}'s {symbol} slot {slot} names {spelled}, not {new}" +
                                    (f" (it sits in slot {where[0]}: the declared virtual order differs from "
                                     "retail's)" if where else ""))
    for rel, symbols in standins:
        if symbols & judged:
            problems.append(f"{rel} compiles no {cls} vftable that matches retail table "
                            f"0x{check['table'] + IMAGE_BASE:08X} (its {', '.join(sorted(symbols & judged))} names "
                            "no slot the ledger resolves, and another installer compiles that table too)")
    stand = [rel for rel, symbols in standins if not symbols & judged]
    if (referencing or stand) and not proved and not problems and not current:
        problems.append(f"no installer of {cls} compiles its vftable ({', '.join(referencing + stand)} only "
                        "reference it" + (" or compile stand-in copies)" if stand else ")"))
    return problems


def respell_mangled_text(text, pairs):
    """(new text, mangled spellings respelled) for one file: every whole old
    mangled name of `pairs` respelled. A plain string literal spelling an old
    name is retail-locked text: refused."""
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
    respelled = 0
    for old, new in pairs:
        text, count = mangled_re(old).subn(lambda _m, n=new: n, text)
        respelled += count
    return text, respelled


def local_static_keys(ctx, name, source):
    """The data_ledger.csv spellings that embed method `name`, each a local static of it
    (`?s@?1??<name>@4HA`, a guard's `?$S1@?1??<name>@4IA`) defined in its own `source`, since the
    ledger keys them by the method's decorated name. Raises Refusal on any other mention."""
    scope = re.compile(r"\?\$?\w+@\?[0-9A-Z]\?" + re.escape(name) + "@4")
    keys = set()
    for data in ctx.dicts(DATA_LEDGER):
        spellings = {data.get("name", ""), *(data.get("names") or "").split(";")} - {""}
        hits = {spelling for spelling in spellings if mangled_re(name).search(spelling)}
        for spelling in hits:
            if not scope.match(spelling):
                raise Refusal(f"{spelling} in {DATA_LEDGER} embeds {name} and is no local static of it")
        if hits and data.get("source") != source:
            raise Refusal(f"{sorted(hits)[0]} in {DATA_LEDGER} is defined in {data.get('source') or 'no source'}, "
                          f"not {name}'s {source}")
        keys |= hits
    return sorted(keys)


def object_defined_symbols(ctx, rel):
    """The names the fresh object of ledger source `rel` defines, or None with no object."""
    import build
    path = _source_object(ctx, rel, current=False)
    if path is None:
        return None
    return {symbol.get("name") for symbol in build.read_object_symbols(path.read_bytes())
            if symbol.get("section", 0) > 0}


def to_class_static_problems(ctx, check):
    """After ./build.sh: each moved method's object defines its local statics under the respelled
    keys the data ledger now holds, and no longer under the old ones."""
    problems = []
    for rel, pairs in sorted((check.get("statics") or {}).items()):
        defined = object_defined_symbols(ctx, rel)
        if defined is None:
            problems.append(f"{rel} has no object to read its local statics from")
            continue
        for old_key, new_key in sorted(pairs.items()):
            if new_key not in defined:
                problems.append(f"{rel}'s object does not define {new_key}, the data ledger's new key")
            if old_key in defined:
                problems.append(f"{rel}'s object still defines {old_key}")
    return problems


def _to_class_move(ctx, rva, cls, new, *, old=None, prepared=None):
    """Every check of one --to-class move of the row at `rva` into `cls` as
    `new` (see the section comment), up to its retail slot; a dict of what
    plan_to_class writes. Raises Refusal; writes nothing."""
    if not new:
        raise Refusal("--to-class needs --new: the member's identifier in that class, or its full mangled name")
    owners = [r for r in ctx.rows() if _rva(r.get("target_rva")) == rva
              and not r["name"].startswith(FUNCLET_PREFIXES + ("$L",)) and "parent=" not in r.get("notes", "")]
    if old:
        owners = [r for r in owners if r["name"] == old]
        if not owners:
            raise Refusal(f"{old} has no row at 0x{rva:08X}")
    names = sorted({r["name"] for r in owners})
    if len(names) != 1:
        raise Refusal(f"0x{rva:08X} carries {len(names)} function names ({', '.join(names) or 'none'}); "
                      "a class move needs exactly one (pass --old to choose)")
    row = owners[0]
    name = row["name"]
    at, old_cls, _scopes, _role = member_function_header(name)
    if old_cls == cls:
        raise Refusal(f"{name} is already a member of {cls}")
    if not is_placeholder(old_cls, "class"):
        raise Refusal(f"{name}'s class {old_cls} is a readable name: --to-class moves only a placeholder class's "
                      "member (choosing between two readable classes is a naming decision)")
    return_enum = None
    if new.startswith("?"):
        try:
            nat = member_function_header(new)[0]
        except Refusal:
            nat = None
        if nat is not None:
            return_enum = enum_return_respelling(name[at + 1:], new[nat + 1:])
    new_name = to_class_symbol(name, cls, new, return_enum=return_enum)
    if is_generated(row["source"]):
        raise Refusal(f"{name} lives in generated source {row['source']}; recover it as real C++ first")
    reason = is_protected(ctx, "function", name, rva=rva, identifier=scope_of(name).rsplit("::", 1)[-1])
    if reason:
        raise Refusal(f"canonical name: {reason}")
    refuse_vendored(ctx, [row["source"]], f"moving {name}")
    if any(r["name"] == new_name for r in ctx.rows()) or any(p.get("name") == new_name for p in ctx.pins()):
        raise Refusal(f"{new_name} already names a row or pin")
    tombstoned = _tombstones(ctx)
    if (new_name, rva) in tombstoned:
        raise Refusal(f"({new_name}, 0x{rva:08X}) is tombstoned in deleted_rows.csv: "
                      f"{tombstoned[(new_name, rva)][:120]}")
    shared = sorted({r["name"] for r in ctx.rows() if _rva(r.get("target_rva")) == rva and r["name"] != name
                     and not r["name"].startswith(FUNCLET_PREFIXES + ("$L",))
                     and "parent=" not in r.get("notes", "")} |
                    {p.get("name", "") for p in ctx.pins() if _rva(p.get("address")) == rva
                     and p.get("name") != name})
    if shared or FOLD_NOTES.search(row.get("notes", "")):
        raise Refusal(f"0x{rva:08X} is a shared body ({', '.join(shared[:3]) or 'its notes record a fold'}): "
                      "a slot there proves only that some folded function is a member")
    if any(mangled_re(name).search(d.get("name", "")) for d in ctx.dicts(DATA_ROWS)):
        raise Refusal(f"a data row (a local static) embeds {name}; rename the static first")
    frozen = [rel for rel in frozen_mentions(ctx, name) if rel != DATA_LEDGER]
    if frozen:
        raise Refusal(f"{name} is a key in {', '.join(frozen)} (frozen, shrink-only)")
    statics = local_static_keys(ctx, name, row["source"])

    import retail_identity
    found = {}
    table, slot, retail, installers, proof = to_class_evidence(ctx, rva, cls, {row["source"]},
                                                               reviewed=retail_identity.shared_slot_of(rva, cls, new_name),
                                                               base=retail_identity.base_slot_of(rva, cls, new_name),
                                                               found=found)
    declared = []
    if return_enum is not None:
        # read from the installers: their view of cls compiles the table
        declared = declared_enum_return(ctx, cls, split_function_name(new_name)[1], return_enum,
                                        {r["source"] for r in installers}, prepared)
    return {"rva": rva, "row": row, "name": name, "new_name": new_name, "table": table, "slot": slot,
            "retail": retail, "installers": installers, "proof": proof, "declared": declared,
            "tombstoned": tombstoned, "statics": statics, "bases": found.get("bases"), "where": found.get("where")}


def plan_to_class(ctx, rva, cls, new, *, evidence="", old=None, prepared=None, max_files=25, also=None):
    """Plan moving one placeholder-class member into class `cls` as its
    virtual `new`; see the section comment. `also` [(rva, new)] moves more
    slots of the same retail table in the same plan (a batch: the slots of a
    table still rowed under other placeholders, which no single move can
    prove; to_class_slot_problems judges each moved slot by the others).
    Raises Refusal; writes nothing."""
    cls = cls or ""
    if not IDENT.fullmatch(cls) or cls in name_metric.KEYWORDS:
        raise Refusal(f"{cls!r} is not a class identifier")
    moves = [_to_class_move(ctx, rva, cls, new, old=old, prepared=prepared)]
    for extra_rva, extra_new in also or ():
        moves.append(_to_class_move(ctx, extra_rva, cls, extra_new, prepared=prepared))
    first = moves[0]
    if len(moves) > 1 and any(m["bases"] for m in moves):
        raise Refusal("a base-slot move (retail_identity.BASE_SLOTS) moves one slot; --also is not read with it")
    if len(moves) > 1:
        tables = sorted({m["table"] for m in moves})
        if len(tables) != 1:
            raise Refusal("a --to-class batch moves slots of one retail table, installed by one class's special "
                          "members; these sit in " + ", ".join(f"0x{t + IMAGE_BASE:08X}" for t in tables))
        for key, what in (("rva", "address"), ("slot", "slot"), ("new_name", "new name")):
            seen = [m[key] for m in moves]
            if len(set(seen)) != len(seen):
                raise Refusal(f"a --to-class batch names one {what} twice")
    table, retail = first["table"], first["retail"]
    installers = []
    for move in moves:
        installers += [r for r in move["installers"] if all(r is not i for i in installers)]
    installer_sources = sorted({r["source"] for r in installers})
    check = {"cls": cls, "table": table, "slot": first["slot"], "new": first["new_name"], "retail": list(retail),
             "sources": installer_sources}
    if len(moves) > 1:
        check["slots"] = {m["slot"]: m["new_name"] for m in moves}
        check["moved"] = {m["new_name"]: m["rva"] for m in moves}
    if first["bases"]:
        check["bases"] = first["bases"]
        check["where"] = first["where"]
        check["rva"] = first["rva"]
    edited = set(prepared or {})
    early_check = dict(check, sources=[s for s in installer_sources if s not in edited])
    if check.get("bases"):
        # a prepared installer unit is judged after ./build.sh, as an own installer is
        early_check["bases"] = [dict(record, sources=[s for s in record["sources"] if s not in edited])
                                for record in check["bases"]]
    early = to_class_slot_problems(ctx, early_check)
    if early:
        raise Refusal("the vftable " + cls + "'s installers compile does not prove the slot: " + early[0])

    name, new_name, row = first["name"], first["new_name"], first["row"]
    plan = Plan("function", name, new_name, "to-class", " ".join((evidence or "").split()), row["source"], rva,
                old_word=scope_of(name), new_word=f"{cls}::{split_function_name(new_name)[1]}")
    plan.warnings.extend(early_check.get("reports", ()))
    plan.to_class = check
    plan.evidence = "; ".join(f"{m['name']} -> {m['new_name']}: {m['proof']}" + "".join(
        f"; return type: {d}" for d in m["declared"]) for m in moves) + \
        (f"; {plan.evidence}" if plan.evidence else "")
    _batch_source_edits(ctx, plan, prepared)

    # Ledgers: the rows, their funclet rows and notes tokens, pins, audited owners.
    pairs = [(m["name"], m["new_name"]) for m in moves]
    raw = ctx.read(FUNCTIONS)
    for before_name, after_name in pairs:
        raw, changed = rewrite_records(raw, "functions.csv", mangled_re(before_name), after_name)
        for before, after in changed:
            if before[0] != after[0]:
                plan.renamed_rows.append((before[0], after[0], _rva(before[2])))
            else:
                plan.notes_rows.append((before[0], _rva(before[2])))
    plan.edit(ctx, FUNCTIONS, raw)
    raw = ctx.read(SYMBOLS)
    if raw is not None:
        pinned = False
        for before_name, after_name in pairs:
            raw, changed = rewrite_records(raw, "symbols.csv", mangled_re(before_name), after_name)
            plan.renamed_pins += [(before[0], after[0], before[1]) for before, after in changed]
            pinned = pinned or bool(changed)
        if pinned:
            plan.edit(ctx, SYMBOLS, raw)
    for before_name, after_name in pairs:
        for before, _after in rewrite_ledger(ctx, plan, BODY_OWNERS, "body_owners.csv", mangled_re(before_name),
                                             after_name):
            plan.owner_rows.append((before[1], _rva(before[0])))
    # A method's local statics are keyed by its decorated name: they move with it, and the
    # rebuilt object must define them under the new keys (to_class_static_problems).
    if any(m["statics"] for m in moves):
        raw = ctx.read(DATA_LEDGER)
        statics = {}
        for move in moves:
            pattern = mangled_re(move["name"])
            raw = rewrite_records(raw, "data_ledger.csv", pattern, move["new_name"])[0]
            if move["statics"]:
                statics.setdefault(move["row"]["source"], {}).update(
                    {key: pattern.sub(lambda _m, n=move["new_name"]: n, key) for key in move["statics"]})
        plan.edit(ctx, DATA_LEDGER, raw)
        check["statics"] = statics
    tombstoned = first["tombstoned"]

    def reason_text(old_row, new_row):
        # a funclet row renamed with a moved row tombstones under that row's
        # slot: the moved name it embeds decides which
        move = next((m for m in moves if m["name"] in old_row), first)
        where = check.get("where") or f"retail vftable 0x{table + IMAGE_BASE:08X} slot {move['slot']}"
        return (f"Renamed to {new_row} by tools/rename.py (to-class: {where}"
                + "".join(f"; return type: {d}" for d in move["declared"]) + ")")
    lines = [tombstone_line(old_row, at, reason_text(old_row, new_row))
             for old_row, new_row, at in plan.renamed_rows if (old_row, at) not in tombstoned]
    if check.get("bases"):
        check["tombstones"] = [(old_row, at, reason_text(old_row, new_row))
                               for old_row, new_row, at in plan.renamed_rows if (old_row, at) not in tombstoned]
    if lines:
        plan.edit(ctx, DELETED, appended(ctx.read(DELETED), lines, header="name,target_rva,reason"))
    records = current_records(ctx)
    carried = []
    for move in moves:
        record = records.get(move["name"])
        if record:
            plan.carried.append((move["name"], move["new_name"], record.get("basis", "")))
            carried.append(csv_line(["carry", move["name"], move["new_name"], record.get("basis", ""),
                                     f"class move by tools/rename.py: {move['proof']}", record.get("source", ""),
                                     record.get("rva", "")]))
        else:
            plan.warnings.append(f"{move['name']} has no name_basis.csv record: {move['new_name']} is the "
                                 f"identifier {cls}'s own declaration gives that slot, and no basis row is "
                                 "written for it")
    if carried:
        plan.edit(ctx, NAME_BASIS, appended(ctx.read(NAME_BASIS), carried, header=NAME_BASIS_HEADER))

    # Sources: the prepared C++ as given, then every file spelling an old
    # mangled name respelled; a unit whose object references an old name must
    # be prepared or spell it.
    olds = {m["name"] for m in moves}
    candidates = set(edited)
    for before_name in sorted(olds):
        candidates |= set(ctx.grep_files(before_name))
    by_object = object_referencers(ctx, olds)
    headers, rewritten = [], set(edited)
    for rel in sorted(candidates | by_object):
        data = plan.after.get(rel, ctx.read(rel))
        if data is None:
            raise Refusal(f"{rel} is listed but missing")
        text = data.decode("utf-8", errors="surrogateescape")
        new_text, respelled = respell_mangled_text(text, pairs)
        if new_text == text:
            if rel in by_object and rel not in edited and object_confirms(ctx, rel, olds):
                raise Refusal(f"{rel}'s object references {', '.join(sorted(olds))}: prepare that source too "
                              "(--prepared)")
            continue
        if is_generated(rel):
            raise Refusal(f"generated source {rel} spells {', '.join(sorted(olds))}; it is never edited")
        refuse_vendored(ctx, [rel], f"moving {name}")
        rewritten.add(rel)
        counts = plan.source_counts.setdefault(rel, {})
        counts["mangled"] = counts.get("mangled", 0) + respelled
        plan.edit(ctx, rel, new_text.encode("utf-8", errors="surrogateescape"))
        if not rel.endswith(SOURCE_SUFFIXES) or rel not in ctx.ledger_sources():
            headers.append(rel)
    if len(rewritten) > max_files:
        raise Refusal(f"{len(rewritten)} files to rewrite (over --max-files {max_files})")
    verify = ({rel for rel in rewritten if rel in ctx.ledger_sources()} | {m["row"]["source"] for m in moves}
              | set(installer_sources))
    if headers:
        verify |= includers(ctx, headers, max_files)
    renamed = {o for o, _, _ in plan.renamed_rows}
    verify |= {r["source"] for r in ctx.rows() if r["name"] in renamed}
    verify |= {r["source"] for r in ctx.rows() if (r["name"], _rva(r.get("target_rva"))) in set(plan.notes_rows)}
    plan.verify = sorted(v for v in verify if not is_generated(v))
    if len(plan.verify) > max_files:
        raise Refusal(f"{len(plan.verify)} sources to verify (over --max-files {max_files})")
    plan.claims = sorted({at for _, _, at in plan.renamed_rows} | {at for _, at in plan.notes_rows} |
                         {m["rva"] for m in moves}) + \
        sorted({f"file:{rel}" for rel in {m["row"]["source"] for m in moves} | edited})
    written = set(plan.after) | {"reverse/re_attempts.log"}
    plan.mentions = sorted({rel for before_name in olds
                            for rel in ctx.grep_files(before_name, roots=("docs", "reverse"))} - written)
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


def plan_global(ctx, name, new, basis, evidence, *, max_files=25, retype=None, size=None, initializer=None,
                prepared=None, address=None, absorb=(), model=None):
    """Plan respelling one reverse/data_rows.csv global everywhere it is named.

    The byte gate masks DIR32 operands, so a consumer left on the old name
    still byte-matches and only the link breaks: the plan has to find every
    consumer itself, by text and by object symbol table, and refuses when it
    cannot rewrite one. With `retype` (a C++ type) it is `global --retype`
    (plan_retype): the identifier stays, the type and size change."""
    if retype is not None:
        return plan_retype(ctx, name, new, retype, size, evidence, initializer=initializer, prepared=prepared,
                           max_files=max_files, address=address, absorb=absorb, model=model)
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


# ---------------------------------------------------------------- global --retype
#
# A rowed global's placeholder type can be smaller than the retail object it
# stands for: `unsigned g_00DFE1AC;` (4 bytes) where retail's code reads +4 and
# +8 of a 12-byte vector. image_iso flags every such read as an out-of-object
# pointer. Changing the type changes the mangled name, which `global --new`
# refuses (identifier changes only), and nothing else could re-key the data
# row. `global --retype TYPE --size N --new MANGLED` changes the type and size
# and keeps the identifier: every declaration is respelled, the data row,
# pins, notes and the data_ledger.csv row are re-keyed, an /alternatename
# that only bridged the two spellings is removed with its hatch_baseline.tsv
# line, and ./build.sh plus a post-build object check prove it. Refused: an
# extent another owner overlaps (a data row, a function row, a converged or
# ledger address inside it), one leaving its retail section, non-zero retail
# bytes with no --initializer, a second definition, a declaration it cannot
# parse, the old mangled name surviving anywhere, and a new type the owner's
# object would construct with its own dynamic initializer (retail's rowed
# initializer already constructs these: the image would run both).
#
# A placeholder can also start too late or hold a neighbour's field. `--address`
# moves the start down over unrowed space and `--absorb` takes a row wholly inside
# the extent, its readers rewritten by --prepared. Neither has a compiler or a byte
# to prove what the object is, so each makes only the change an entry of
# tools/retail_identity.py's EXTENTS spells out, on facts read from the image. A global only
# data_ledger.csv owns gains its data row here, and a const placeholder of a table
# retail writes becomes mutable.

HATCH_BASELINE = "reverse/hatch_baseline.tsv"
ZERO_INIT = re.compile(r"^\s*=\s*(?:0[uUlL]*|NULL|\{\s*0?\s*\})\s*$")
ALTERNATENAME = re.compile(r'(?m)^[ \t]*#[ \t]*pragma[ \t]+comment[ \t]*\([ \t]*linker[ \t]*,[ \t]*'
                           r'"/alternatename:(?P<a>[^="\s]+)=(?P<b>[^"\s]+)"[ \t]*\)[^\n]*(?:\n|$)')
NOT_A_TYPE = ("return", "delete", "throw", "case", "goto", "else", "do", "sizeof", "new", "typedef", "using",
              "operator", "co_return", "if", "while", "for", "switch")


def declaration_re(word, anchored=True):
    """A declaration or definition of `word` starting a line (file scope in practice):
    leading space, `extern`, the type, pointer/reference marks, the identifier, an array
    bound, an initializer, `;`. Tokens may be split by any whitespace, newlines included
    (review of 03c0d18c27: `extern unsigned int\\n g;` escaped a [ \\t] pattern)."""
    return re.compile(
        (r"(?m)^" if anchored else r"(?m)(?:^|(?<=[;{}]))") + r"(?P<lead>[ \t]*)(?P<extern>extern\s+(?:\"C\"\s+)?)?"
        r"(?P<spec>(?!(?:" + "|".join(NOT_A_TYPE) + r")\b)(?:(?:const|volatile|static|unsigned|signed|struct|class|"
        r"union|enum)\s+)*[A-Za-z_][\w:]*(?:\s*<[^;(){}]*>)?)"
        r"(?P<marks>[\s\*&]*(?:const[\s\*&]+)*)" + re.escape(word) +
        r"\b(?P<array>\s*\[[^\]]*\])?(?P<init>\s*=[^;]*)?\s*;")


def declaration_sites(code, word):
    """Offsets in comment- and string-stripped `code` where `word` is declared, found
    without the declaration pattern: the identifier followed by `;`, `[` or `=` (not `==`)
    and preceded, past pointer marks and whitespace, by a type-like token (an identifier
    that is no statement keyword, or a template's `>`). A site no declaration_re match
    covers is a declaration the retype cannot respell."""
    directives = [d.end() for d in re.finditer(r"(?m)^[ \t]*#[^\n]*", code)]
    keyword = re.compile(r"\s*(?:extern\b|(?!(?:" + "|".join(NOT_A_TYPE) + r")\b)[A-Za-z_][\w:]*)")
    for m in re.finditer(r"(?<![\w.>:])" + re.escape(word) + r"\b", code):
        after = code[m.end():].lstrip()
        if not after:
            continue
        # a statement that starts like a declaration and has no call or assignment before
        # the identifier declares it, as one declarator of a list too (`extern unsigned a, g;`)
        start = max([code.rfind(c, 0, m.start()) + 1 for c in ";{}"] + [e for e in directives if e <= m.start()])
        statement = code[start:m.start()]
        if after[0] in ";[=," and not after.startswith("==") and statement.strip() and "(" not in statement \
                and "=" not in statement and keyword.match(statement):
            yield m.start()
            continue
        if after[0] not in ";[=" or after.startswith("=="):
            continue
        before = code[:m.start()].rstrip().rstrip("*& \t\r\n")
        token = re.search(r"([A-Za-z_]\w*|>)$", before)
        if not token or token.group(1) in NOT_A_TYPE:
            continue
        lead = before[:token.start()].rstrip()
        if token.group(1) != ">" and lead.endswith(("->", ".", "::")):
            continue
        yield m.start()


ARITHMETIC = frozenset(("unsigned", "signed", "char", "short", "int", "long", "__int8", "__int16", "__int32",
                        "__int64", "float", "double", "bool", "wchar_t", "const", "volatile"))
RETAIL_IMAGE_SPAN = (IMAGE_BASE, 0x01000000)     # a VA literal anywhere here could be a pointer into retail
NUMBER = re.compile(r"(?<![\w.])(0[xX][0-9a-fA-F]+|\d+)(?:[uUlL]*)\b")
DEFINE = re.compile(r"(?m)^[ \t]*#[ \t]*define[ \t]+(?P<name>[A-Za-z_]\w*)(?P<params>\([^)]*\))?(?P<body>(?:[^\n]*\\\n)*[^\n]*)")
COMPUTED_INCLUDE = r"^[[:space:]]*#[[:space:]]*include[[:space:]]+[A-Za-z_]"


def arithmetic_type_problem(new_type):
    """Why `new_type` is not an arithmetic scalar or an array of one, or None. A retype
    gives a placeholder its retail extent (the 13 out-of-object globals are integer
    arrays); a pointer would need relocations that data_rows.py only checks where the
    object already has them (review of 010e6e9e21)."""
    base, _array = split_type(new_type)
    words = base.split()
    if not words or any(w not in ARITHMETIC for w in words) or not any(w not in ("const", "volatile") for w in words):
        return f"{new_type} is not an arithmetic type (or an array of one): a retype gives a placeholder its extent " \
               "and never a pointer, reference or class, whose relocations or construction it cannot prove"
    return None


def image_literals(initializer):
    """Integer literals in `initializer` that lie in retail's address range: a pointer spelled
    as a number keeps retail's address in a rebased image and no relocation follows it."""
    out = []
    for m in NUMBER.finditer(name_metric.strip(initializer or "")):     # not inside a string or char literal
        digits = m.group(1)
        value = int(digits, 16) if digits.lower().startswith("0x") else \
            int(digits, 8) if len(digits) > 1 and digits.startswith("0") else int(digits)
        if RETAIL_IMAGE_SPAN[0] <= value < RETAIL_IMAGE_SPAN[1]:
            out.append(m.group(0))
    return out


def retail_relocated(ctx, rva, size):
    """Offsets inside [rva, rva + size) where retail relocates a dword (its recovered DIR32
    sites, as boot_image and real_image read them): a pointer lives there."""
    if "_retail_sites" not in ctx._cache:
        sys.path.insert(0, str(ROOT / "tools"))
        import boot_image
        ctx._cache["_retail_sites"] = sorted(boot_image.all_sites(boot_image.Retail())[0])
    import bisect
    sites = ctx._cache["_retail_sites"]
    i = bisect.bisect_left(sites, rva - 3)
    out = []
    while i < len(sites) and sites[i] < rva + size:
        out.append(sites[i] - rva)
        i += 1
    return out


def function_like_macros(ctx):
    """Names the tree defines as function-like macros (`#define NAME(`)."""
    if "_fn_macros" not in ctx._cache:
        found = ctx.git("grep", "-h", "-o", "-E", r"#[[:space:]]*define[[:space:]]+[A-Za-z_][A-Za-z0-9_]*\(", "--",
                        *SEARCH_ROOTS)
        ctx._cache["_fn_macros"] = {re.sub(r"^#\s*define\s+", "", m).rstrip("(") for m in found.splitlines()}
    return ctx._cache["_fn_macros"]


def macro_problems(text, code, word, spans, macros):
    """Mentions of `word` the declaration scans cannot read (review of 010e6e9e21): an
    argument of a function-like macro, a #define body shaped like a declaration, and a
    file-scope statement outside the covered declarations that is not an initializer."""
    for d in DEFINE.finditer(text):
        body = d.group("body")
        if re.search(r"\b" + re.escape(word) + r"\b", name_metric.strip(body)):
            if re.search(r"\bextern\b", body) or any(True for _ in declaration_sites(name_metric.strip(body), word)):
                yield f"#define {d.group('name')} declares {word} in its body"
    # (start, end) of code at file scope: outside function and class bodies, where a
    # namespace or extern "C" block still counts as file scope
    scope, file_scope, start = [], [], 0             # scope: one flag per open brace, True if transparent
    for m in re.finditer(r"[{}]", code):
        if m.group() == "{":
            head = code[max(0, code.rfind(";", 0, m.start()), code.rfind("}", 0, m.start())):m.start()]
            transparent = bool(re.search(r"\bnamespace\b[^;{}]*$|\bextern\s+\"C(?:\+\+)?\"\s*$", head))
            if all(scope):
                file_scope.append((start, m.start()))
            scope.append(transparent)
            if all(scope):
                start = m.end()
        elif scope:
            if all(scope):                           # closing a namespace from inside it
                file_scope.append((start, m.start()))
            scope.pop()
            if all(scope):
                start = m.end()
    if all(scope):
        file_scope.append((start, len(code)))
    directives = [(d.start(), d.end()) for d in re.finditer(r"(?m)^[ \t]*#[^\n]*(?:\\\n[^\n]*)*", code)]
    for m in re.finditer(r"(?<![\w.>:])" + re.escape(word) + r"\b", code):
        at = m.start()
        if any(a <= at < b for a, b in spans) or any(a <= at < b for a, b in directives):
            continue
        callee = re.search(r"([A-Za-z_]\w*)\s*\([^()]*$", code[:at])
        if callee and callee.group(1) in macros:
            yield f"{word} is an argument of the function-like macro {callee.group(1)}"
            continue
        if any(a <= at < b for a, b in file_scope):
            begin = max([code.rfind(c, 0, at) + 1 for c in ";{}"] + [b for _a, b in directives if b <= at])
            if "=" not in code[begin:at]:
                line = code.count("\n", 0, at) + 1
                yield f"line {line} names {word} at file scope outside any declaration the retype reads"


SAME_BUILTIN = {"unsigned": "unsigned int", "signed": "int", "signed int": "int", "short int": "short",
                "signed short": "short", "signed short int": "short", "unsigned short int": "unsigned short",
                "long int": "long", "signed long": "long", "signed long int": "long",
                "unsigned long int": "unsigned long", "signed __int64": "__int64"}


def same_type(spec, array=""):
    """A declaration's type as a comparable value: whitespace and pointer marks spaced the
    same, cv-qualifiers in a fixed order, and builtin spellings of one type made one
    (`unsigned` is `unsigned int`)."""
    words = spec.replace("*", " * ").replace("&", " & ").split()
    words = [w for w in words if w != "extern"]
    cv = sorted(w for w in words if w in ("const", "volatile"))
    rest = " ".join(w for w in words if w not in ("const", "volatile"))
    head, _, marks = rest.partition(" *") if " *" in rest else (rest, "", "")
    head = SAME_BUILTIN.get(head, head)
    return (" ".join(cv + [head]) + (" *" + marks if _ else ""), "".join(array.split()))


def check_declarations(text, word, new_type, rel, owner, macros=frozenset()):
    """Refuse when `text` (after the retype) declares `word` anywhere the declaration
    pattern does not cover, as another type, or defines it outside the owner. Returns the
    number of definitions."""
    code = name_metric.strip(text)
    base, array = split_type(new_type)
    want = same_type(base, array)
    spans, definitions = [], 0
    for m in declaration_re(word).finditer(code):
        spans.append((m.start(), m.end()))
        spec = (m.group("spec") + m.group("marks")).replace("*", " * ").replace("&", " & ")
        got = same_type(spec, m.group("array") or "")
        if got != want:
            raise Refusal(f"{rel} declares {word} as `{' '.join(m.group(0).split())[:80]}`, not {new_type}")
        if not m.group("extern"):
            if not owner:
                raise Refusal(f"{rel} defines {word} outside its data row's source (a second definition)")
            definitions += 1
    for at in declaration_sites(code, word):
        if not any(a <= at < b for a, b in spans):
            line = code.count("\n", 0, at) + 1
            raise Refusal(f"{rel}:{line} declares {word} in a form the retype cannot respell")
    for why in macro_problems(text, code, word, spans, macros):
        raise Refusal(f"{rel}: {why} (a macro-built declaration would keep the old type)")
    return definitions


def split_type(new_type):
    """(base, array suffix) of a C++ type spelled for a declaration: `unsigned int [3]`
    is ('unsigned int', '[3]'), `_STL::vector<void *>` has no suffix."""
    text = " ".join(new_type.split())
    m = re.match(r"^(?P<base>.*?)\s*(?P<array>(?:\[[^\]]*\])+)$", text)
    return (m.group("base"), m.group("array")) if m else (text, "")


def retype_declarations(text, word, new_type, *, owner, initializer=None):
    """`text` with every declaration of `word` respelled as `new_type`: (new text, number
    of extern declarations, number of definitions). The definition (owner only) takes
    `initializer`, or keeps none when its old one is a zero; anything else refuses."""
    base, array = split_type(new_type)
    counts = {"extern": 0, "definition": 0}

    def respell(m):
        if "static" in m.group("spec").split():
            raise Refusal(f"a TU-local `static {word}` is not the rowed global")
        extern = bool(m.group("extern"))
        if extern and '"C"' in m.group("extern"):
            raise Refusal(f'an extern "C" declaration of {word} names a C symbol, not {word}\'s mangled one')
        init = m.group("init") or ""
        if extern:
            if init:
                raise Refusal(f"an extern declaration of {word} carries an initializer: {m.group(0).strip()[:80]}")
            counts["extern"] += 1
            tail = ""
        else:
            if not owner:
                raise Refusal(f"a second definition of {word} outside its data row's source: "
                              f"{m.group(0).strip()[:80]}")
            counts["definition"] += 1
            if initializer is not None:
                tail = f" = {initializer.strip()}"
            elif not init or ZERO_INIT.match(init):
                tail = ""
            else:
                raise Refusal(f"{word}'s definition has the initializer `{init.strip()[1:].strip()[:60]}`, which "
                              "the new type would need respelled: pass --initializer")
        sep = "" if base.endswith(("*", "&")) else " "
        return f"{m.group('lead')}{'extern ' if extern else ''}{base}{sep}{word}{array}{tail};"
    return declaration_re(word).sub(respell, text), counts["extern"], counts["definition"]


def remove_bridging_aliases(text, old_name, new_name):
    """`text` without each `/alternatename:A=B` pragma line where A and B are the old and
    new spellings of this global (the bridge the retype makes redundant): (text, [A])."""
    removed = []

    def drop(m):
        if {m.group("a"), m.group("b")} == {old_name, new_name}:
            removed.append(m.group("a"))
            return ""
        return m.group(0)
    return ALTERNATENAME.sub(drop, text), removed


def retail_extent(ctx, rva, size):
    """(section at the first byte, section at the last byte, bytes) of retail over
    [rva, rva + size): the image data_rows.py verifies against."""
    if "_retail_image" not in ctx._cache:
        sys.path.insert(0, str(ROOT / "tools"))
        import reloc_ledger
        ctx._cache["_retail_image"] = reloc_ledger.Image()
    img = ctx._cache["_retail_image"]
    va = IMAGE_BASE + rva
    return img.section(va), img.section(va + size - 1), img.read(va, size)


def extent_overlaps(ctx, rva, size, own):
    """Every owner or name that meets [rva, rva + size), but those `own` {name: rva} gives
    up: the retyped global and the rows it absorbs, where they stand today."""
    end, found = rva + size, []
    for row in ctx.dicts(DATA_ROWS):
        at = data_rva(row)
        if at is None or own.get(row.get("name")) == at:
            continue
        span = int(row.get("size") or 0) or 1
        if at < end and rva < at + span:
            found.append(f"data row {row.get('name')} at 0x{at:08X}+{span}")
    for row in ctx.rows():
        at, span = _rva(row.get("target_rva")), int(row.get("target_size") or 0)
        if at is not None and span and at < end and rva < at + span:
            found.append(f"function row {row.get('name')} at 0x{at:08X}+{span}")
    for row in ctx.dicts(CONVERGED):
        at = _rva(row.get("address"))
        if at is not None and rva < at < end:
            found.append(f"converged global {row.get('name')} at 0x{at:08X}")
    for row in ctx.dicts(DATA_LEDGER):
        at = _rva(row.get("address"))
        if at is None or own.get(row.get("name")) == at:
            continue
        # one at the start itself is the row re-keying must find, and refuses there
        if rva < at < end or at < rva < at + int(row.get("size") or 0):
            found.append(f"data_ledger.csv name {row.get('name')} at 0x{at:08X}+{row.get('size')} ({row.get('status')})")
    return found


def rekey_csv_record(raw, label, match, update):
    """`raw` with the one record `match(fields dict)` selects rewritten by `update(dict)`,
    every other record byte for byte. Returns (raw, old dict) or (raw, None)."""
    ledger_io.lf_terminator(raw, label)
    records = ledger_io.split_records(raw)
    header = next(csv.reader(io.StringIO(records[0][0].decode("utf-8"))))
    out, found = [records[0][0] + records[0][1]], None
    for payload, term in records[1:]:
        values = next(csv.reader(io.StringIO(payload.decode("utf-8"))), [])
        row = dict(zip(header, values))
        if found is None and values and match(row):
            found = dict(row)
            update(row)
            payload = csv_line([row.get(h, "") for h in header]).rstrip(b"\n")
        out.append(payload + term)
    return b"".join(out), found


def drop_csv_record(raw, label, match):
    """`raw` without the one record `match(fields dict)` selects, every other record byte
    for byte. Returns (raw, its dict) or (raw, None)."""
    ledger_io.lf_terminator(raw, label)
    records = ledger_io.split_records(raw)
    header = next(csv.reader(io.StringIO(records[0][0].decode("utf-8"))))
    out, found = [records[0][0] + records[0][1]], None
    for payload, term in records[1:]:
        values = next(csv.reader(io.StringIO(payload.decode("utf-8"))), [])
        row = dict(zip(header, values))
        if found is None and values and match(row):
            found = row
            continue
        out.append(payload + term)
    return b"".join(out), found


def hatch_lines_lowered(raw, removed):
    """hatch_baseline.tsv with one occurrence taken off each (path, token) in `removed`
    (a line at 0 goes): a shrink, which the register allows by hand and re-verifies."""
    lines = raw.decode("utf-8").splitlines(keepends=True)
    out, left = [], collections.Counter(removed)
    for line in lines:
        cols = line.rstrip("\n").split("\t")
        key = (cols[1], cols[2]) if len(cols) >= 4 and cols[0] == "alternatename" else None
        if key in left and left[key]:
            count = int(cols[3]) - left.pop(key)
            if count > 0:
                cols[3] = str(count)
                out.append("\t".join(cols) + "\n")
            continue
        out.append(line)
    if left:
        raise Refusal(f"hatch_baseline.tsv has no alternatename line for {sorted(left)[0]}")
    return "".join(out).encode("utf-8")


def forced_include_units(ctx, word, headers):
    """Units whose // cl: flags force-include (/FI) a header that names `word` or #includes,
    through any chain, one of `headers`: no #include line of the unit names it."""
    forced = collections.defaultdict(set)
    for line in ctx.git("grep", "-E", r"//[[:space:]]*cl:.*[/-]FI[^[:space:]]+\.(h|hpp|inl)", "--",
                        *SEARCH_ROOTS).splitlines():
        rel, _, flags = line.partition(":")
        for header in re.findall(r"[/-]FI(\S+\.(?:h|hpp|inl))", flags):
            forced[header.replace("\\", "/").rsplit("/", 1)[-1].lower()].add(rel)
    if not forced:
        return set()
    by_name = collections.defaultdict(list)
    for rel in ctx.git("ls-files", "--", *SEARCH_ROOTS).splitlines():
        by_name[rel.rsplit("/", 1)[-1].lower()].append(rel)
    wanted = {h.rsplit("/", 1)[-1].lower() for h in headers}
    out = set()
    for name, units in forced.items():
        seen, frontier, reaches = {name}, [name], False
        while frontier and not reaches:
            current = frontier.pop()
            for rel in by_name.get(current, []):
                text = (ctx.read(rel) or b"").decode("utf-8", errors="replace")
                if current in wanted or re.search(r"\b" + re.escape(word) + r"\b", text):
                    reaches = True
                    break
                for inc in re.findall(r'(?m)^\s*#\s*include\s*[<"]([^>"]+)[>"]', text):
                    inc = inc.replace("\\", "/").rsplit("/", 1)[-1].lower()
                    if inc not in seen:
                        seen.add(inc)
                        frontier.append(inc)
        if reaches:
            out |= units
    return out


def retype_owner(ctx, name, model):
    """(row, True when it is new) of the global `name` retypes: its reverse/data_rows.csv row,
    or the row a global only data_ledger.csv owns gains (P30: rowed there alone, source known)."""
    def named(row):
        return row.get("name") == name or (not name.startswith("?") and _identifier(row.get("name", "")) == name)
    owners = [r for r in ctx.dicts(DATA_ROWS) if named(r)]
    if len(owners) > 1:
        raise Refusal(f"{name} names {len(owners)} reverse/data_rows.csv rows; a retype needs exactly one")
    if owners:
        return owners[0], False
    ledgered = [r for r in ctx.dicts(DATA_LEDGER) if named(r)]
    if len(ledgered) != 1 or ledgered[0].get("status") != "owned" or ledgered[0].get("kind") != "global" \
            or not ledgered[0].get("source"):
        raise Refusal(f"{name} names 0 reverse/data_rows.csv rows and {len(ledgered)} data_ledger.csv rows, none it "
                      "can take as a source-owned global; a retype needs exactly one")
    if not (model or "").strip():
        raise Refusal(f"{ledgered[0]['name']} has no data row yet: --model names who lands the one this adds")
    row = ledgered[0]
    return {"name": row["name"], "address": row["address"], "address_kind": "rva", "size": row["size"],
            "section": row["section"], "source": row["source"], "status": "matched", "evidence": "",
            "model": model.strip()}, True


def absorbed_rows(ctx, names, old_name, source, rva, size):
    """The rows `names` hands to the retyped global, each wholly inside its extent past the
    start and defined by its source; their data rows and ledger rows go, so nothing may still
    key on them: [{name, word, rva, size, row, ledger}]. Their readers are the caller's."""
    out = []
    rows, ledger = ctx.dicts(DATA_ROWS), ctx.dicts(DATA_LEDGER)
    hatches = ctx.read(HATCH_BASELINE) or b""
    for name in dict.fromkeys(names):
        word = _identifier(name)
        if name.startswith("??") or not word or not re.fullmatch(r"\?" + re.escape(word) + r"@@3.+[AB]", name):
            raise Refusal(f"--absorb {name} is not a global datum spelled ?<identifier>@@3<type>")
        if name == old_name or word == _identifier(old_name):
            raise Refusal(f"--absorb {name} is the global being retyped")
        row = [r for r in rows if r.get("name") == name]
        booked = [r for r in ledger if r.get("name") == name]
        if len(row) > 1 or len(booked) > 1 or not (row or booked):
            raise Refusal(f"--absorb {name} names {len(row)} data rows and {len(booked)} data_ledger.csv rows; "
                          "it needs one of each at most, and at least one")
        at = data_rva(row[0]) if row else _rva(booked[0].get("address"))
        span = int((row[0] if row else booked[0]).get("size") or 0)
        if at is None or span <= 0 or not (rva < at and at + span <= rva + size):
            raise Refusal(f"--absorb {name} at 0x{at or 0:08X}+{span} is not wholly inside the extent past its start "
                          f"(0x{rva:08X}+{size})")
        if booked and _rva(booked[0].get("address")) != at:
            raise Refusal(f"data_ledger.csv puts {name} at {booked[0].get('address')}, its data row at 0x{at:08X}")
        if booked and at + int(booked[0].get("size") or 0) > rva + size:
            raise Refusal(f"data_ledger.csv gives {name} {booked[0].get('size')} B at 0x{at:08X}: not wholly inside the "
                          f"extent past its start (0x{rva:08X}+{size})")
        # both records must agree; beside a data row, a ledger row with no source claims nothing
        for claimed in [r.get("source") for r in row] + [r.get("source") for r in booked if r.get("source") or not row]:
            if claimed != source:
                raise Refusal(f"--absorb {name} is defined by {claimed or 'no source'}, not {source}: "
                              "the retype takes a row of its own unit")
        if booked and {n for n in (booked[0].get("names") or "").split(";") if n} - {name}:
            raise Refusal(f"data_ledger.csv binds other spellings at {name}'s address ({booked[0].get('names')}): "
                          "reconcile them first")
        if any(p.get("name") == name for p in ctx.pins()):
            raise Refusal(f"symbols.csv pins {name}: a pin keeps the symbol alive, and absorbing it leaves no definition")
        frozen = [rel for rel in frozen_mentions(ctx, name) if rel not in (DATA_LEDGER, HATCH_BASELINE)]
        if frozen or name.encode() in hatches:
            raise Refusal(f"{name} is a key in {', '.join(frozen) or HATCH_BASELINE} (frozen, shrink-only); absorbing it "
                          "needs a Verifier-Change commit that re-keys it")
        out.append({"name": name, "word": word, "rva": at, "size": span, "row": bool(row),
                    "refs": int(booked[0].get("refs") or 0) if booked else 0})
    return out


RETYPE_SCAN_WORKERS = 8
PREPROCESSOR_LINE = re.compile(r"(?m)^[ \t]*#[ \t]*line\b[^\n]*\n")
LITERAL_JOIN = re.compile(r'"\s*L?"')
STRING_LITERAL = re.compile(r"""(L?)"((?:\\.|[^"\\\n])*)\"""")
ESCAPE = re.compile(r"\\(x[0-9A-Fa-f]*|[0-7]{1,3}|u[0-9A-Fa-f]{4}|U[0-9A-Fa-f]{8}|.)", re.S)
SIMPLE_ESCAPES = {"n": "\n", "t": "\t", "v": "\v", "b": "\b", "r": "\r", "f": "\f", "a": "\a", "\\": "\\", "?": "?",
                  "'": "'", '"': '"'}


def decoded_literal(body):
    """A literal's text with its escapes decoded, or None when one does not read cleanly."""
    clean = True

    def decode(m):
        nonlocal clean
        escape = m.group(1)
        if escape[0] in "xuU" and len(escape) > 1 or escape[0] in "01234567":
            value = int(escape, 8) if escape[0] in "01234567" else int(escape[1:], 16)
            if value <= 0x10FFFF:
                return chr(value)
        elif escape in SIMPLE_ESCAPES:
            return SIMPLE_ESCAPES[escape]
        clean = False
        return m.group(0)
    decoded = ESCAPE.sub(decode, body)
    return decoded if clean else None


def preprocessed_spells(text, words):
    """Does a unit's preprocessed text spell any of `words` anywhere? It is searched as text, so
    string literals, `__identifier`, `__asm` and `#pragma comment(linker, ...)` all count, and a
    longer name holding the word counts too. The scan decides what gets compiled, so a miss clears
    a unit that nothing then checks, while a false hit only adds a rebuild; every doubt is a hit.
    The preprocessor leaves escapes and adjacent literals as written and the compiler resolves
    them later: each literal is decoded on its own, as the compiler does, then joined, across a
    `#line` between them, and both the written and the decoded text are searched. A literal that
    does not decode cleanly counts as spelling it."""
    written = PREPROCESSOR_LINE.sub("", text)
    unreadable = False

    def literal(m):
        nonlocal unreadable
        decoded = decoded_literal(m.group(2))
        if decoded is None:
            unreadable = True
            return m.group(0)
        return m.group(1) + '"' + decoded + '"'
    decoded_text = STRING_LITERAL.sub(literal, written) if "\\" in written else written
    return unreadable or any(word in LITERAL_JOIN.sub("", each) for word in words for each in (written, decoded_text))


def paste_reach(ctx, word):
    """Compiled units that can reach any `##`, whatever it pastes. Which pastes could build a name
    is the preprocessor's to say (compiler_scan), not this text's."""
    pasting = ctx.git("grep", "-l", "-F", "-e", "##", "--", *SEARCH_ROOTS).splitlines()
    units = {rel for rel in pasting if rel in ctx.ledger_sources()}
    others = sorted(rel for rel in pasting if rel not in ctx.ledger_sources())
    computed = ctx.git("grep", "-l", "-E", "-e", COMPUTED_INCLUDE, "--", *SEARCH_ROOTS).splitlines()
    units |= {rel for rel in computed if rel in ctx.ledger_sources()}
    others += [rel for rel in computed if rel not in ctx.ledger_sources()]
    if others:
        units |= includers(ctx, others, len(ctx.ledger_sources()))
        units |= {rel for rel in forced_include_units(ctx, word, others) if rel in ctx.ledger_sources()}
    return {rel for rel in units if rel.endswith(SOURCE_SUFFIXES)}


def file_digest(path):
    """A file's sha256, None when it cannot be read."""
    try:
        with open(path, "rb") as handle:
            return hashlib.sha256(handle.read()).hexdigest()
    except OSError:
        return None


def unit_command_fingerprint(ctx, rel):
    """The build's own fingerprint of a unit's command and include path, None when it has none."""
    sys.path.insert(0, str(ctx.root / "tools"))
    import build
    source = ctx.path(rel)
    try:
        command, env = build.compiler_command(source, ctx.root / "build" / "retype_pp" / (source.stem + ".obj"))
    except (Exception, SystemExit):                  # no command now is a changed command
        return None
    return build._cmd_fingerprint(command, env)


def compiler_scan(ctx, words, *, workers=RETYPE_SCAN_WORKERS):
    """Ask the compiler which units spell `words`: every unit that can reach a `##`, and every unit
    whose object is stale or missing, preprocessed under its own build command with no cache.
    {"spelled": units that spell one and join the rebuild, "asm": stale or missing objects no
    preprocessor can read and that rebuild instead, "cleared": the rest, {unit: (its command's
    fingerprint, the files it read)}, "hashes": {file: its sha256 when read}, which hold a clearance
    to the source state it was reached on (cleared_input_problems)}. A unit that fails to
    preprocess never counts as not spelling it: the retype refuses."""
    sys.path.insert(0, str(ctx.root / "tools"))
    import build
    import name_dependents
    objects = name_dependents.merged(name_dependents._row_objects(ctx.rows()),
                                     name_dependents._data_row_objects(ctx.dicts(DATA_ROWS)))
    stale, asm = set(), set()
    for rel, paths in objects.items():
        if rel.lower().endswith(build.LIB_SUFFIX):
            continue
        if not paths or not all(p.exists() and build.compile_is_current(ctx.path(rel), p) for p in paths):
            (stale if rel.endswith(SOURCE_SUFFIXES) else asm).add(rel)
    units = sorted(paste_reach(ctx, words[0]) | stale)
    started = time.time()
    print(f"rename: asking the compiler whether {len(units)} units spell {', '.join(words)} "
          f"({len(stale)} with stale or missing objects, {workers} at a time)", flush=True)

    hashes = {}

    def asked(rel):
        command = unit_command_fingerprint(ctx, rel)
        read = []
        text, why = preprocess_unit(ctx, rel, read)
        files = tuple(sys.intern(str(each)) for each in dict.fromkeys([str(ctx.path(rel))] + [str(r) for r in read]))
        for each in files:                           # at first read: a later edit shows as a difference
            if each not in hashes:
                hashes[each] = file_digest(each)
        return rel, None if text is None else preprocessed_spells(text, words), why, command, files
    spelled, failed, cleared = set(), {}, {}
    with concurrent.futures.ThreadPoolExecutor(max_workers=workers) as pool:
        for rel, spells, why, command, files in pool.map(asked, units):
            if spells is None:
                failed[rel] = why
            elif spells:
                spelled.add(rel)
            else:
                cleared[rel] = (command, files)
    print(f"rename: the compiler asked in {time.time() - started:.0f} s: {len(spelled)} spell it, "
          f"{len(failed)} failed", flush=True)
    for rel in sorted(spelled)[:40]:
        print(f"rename:   spells it: {rel}", flush=True)
    if failed:
        for rel, why in sorted(failed.items()):
            print(f"rename: did not preprocess: {rel}: {' '.join(str(why).split())[:200]}", flush=True)
        raise Refusal(f"{len(failed)} unit(s) did not preprocess, so nothing says they do not spell {words[0]}: "
                      f"{', '.join(sorted(failed)[:3])}")
    return {"spelled": spelled, "asm": asm, "cleared": cleared, "hashes": hashes}


def plan_retype(ctx, name, new, new_type, size, evidence, *, initializer=None, prepared=None, max_files=25,
                address=None, absorb=(), model=None):
    """Plan `global --retype`: one global's type and size, its identifier kept; with `address` and
    `absorb` its start and the rows inside it too, as tools/retail_identity.py's EXTENTS spell out."""
    rows = ctx.dicts(DATA_ROWS)
    owner, new_owner = retype_owner(ctx, name, model)
    old_name, source, old_rva = owner["name"], owner.get("source", ""), data_rva(owner)
    if old_rva is None:
        raise Refusal(f"{old_name}'s data row has no readable address")
    rva = old_rva
    if address is not None:
        try:
            rva = int(str(address), 0)
        except ValueError:
            raise Refusal(f"--address {address!r} is not a number") from None
        if rva >= old_rva:
            raise Refusal(f"--address 0x{rva:08X} is not below 0x{old_rva:08X}: it moves a start down, over unrowed "
                          "space (an RVA, as data_ledger.csv spells it)")
    if is_generated(source):
        raise Refusal(f"{old_name} lives in generated source {source} (never edit Code/gen_*)")
    if source not in ctx.ledger_sources():
        raise Refusal(f"{source} owns no matched function row; ./build.sh could not verify the retype")
    if old_name.startswith("??"):
        raise Refusal(f"{old_name} is a compiler-named datum; it has no declaration to retype")
    word = _identifier(old_name)
    m = re.fullmatch(r"\?" + re.escape(word or "") + r"@@3(.+)A", new or "")
    if not word or not m or not re.fullmatch(r"\?" + re.escape(word) + r"@@3.+[AB]", old_name):
        raise Refusal(f"{new} is not a global datum spelled ?{word}@@3<type>A: a retype keeps the identifier "
                      "and the global scope")
    if old_name.endswith("B") and owner.get("section") != ".data":
        raise Refusal(f"{old_name} is const and retail keeps it in {owner.get('section')}: only a table in retail's "
                      ".data can become mutable")
    if new == old_name:
        raise Refusal("the new mangled name is the old one: nothing to retype")
    if not new_type or not new_type.strip():
        raise Refusal("--retype needs the C++ type")
    why = arithmetic_type_problem(new_type)
    if why:
        raise Refusal(why)
    literals = image_literals(initializer)
    if literals:
        raise Refusal(f"--initializer spells {', '.join(literals[:3])}, inside retail's address range: a pointer "
                      "written as a number keeps retail's address in a rebased image")
    try:
        size = int(str(size), 0)
    except ValueError:
        raise Refusal(f"--size {size!r} is not a number") from None
    if size <= 0:
        raise Refusal("--size must be positive")
    if size < int(owner.get("size") or 0):
        raise Refusal(f"--size {size} is smaller than the row's {owner.get('size')} B: a retype grows a placeholder "
                      "to its retail extent, and a shrink would drop retail bytes from verification")
    if rva + size < old_rva + int(owner.get("size") or 0):
        raise Refusal(f"0x{rva:08X}+{size} does not contain the row's 0x{old_rva:08X}+{owner.get('size')}: a move "
                      "would drop retail bytes from verification")
    absorbed = absorbed_rows(ctx, absorb, old_name, source, rva, size)
    extent = None
    if rva != old_rva or absorbed:
        import retail_identity
        extent = retail_identity.extent_of(old_name, new)
        spelled = (rva, size, {(row["name"], row["rva"]) for row in absorbed})
        if extent is None or (extent.start, extent.size, set(extent.absorbs)) != spelled:
            raise Refusal(f"--address and --absorb make only a change an entry of tools/retail_identity.py's EXTENTS "
                          f"spells out; none takes {old_name} to {new} at 0x{rva:08X}+{size} with these rows "
                          "(a new entry is a reviewed one, Verifier-Change)")
        problems = retail_identity.extent_problems(extent)
        if problems:
            raise Refusal(f"retail does not state 0x{rva:08X}+{size}: {problems[0]}")
    for row in ctx.dicts(CONVERGED):
        if _rva(row.get("address")) in (rva, old_rva):
            raise Refusal(f"0x{_rva(row.get('address')):08X} is a converged address (reverse/data_converged.csv binds "
                          f"{row.get('name')}); data_check --converged refuses a changed name there")
    if any(r.get("name") == new for r in rows) or any(r["name"] == new for r in ctx.rows()) \
            or any(p.get("name") == new for p in ctx.pins()):
        raise Refusal(f"{new} already names a data row, function or pin")
    refuse_vendored(ctx, [source], f"retyping {old_name}")
    for symbol in [old_name] + [row["name"] for row in absorbed]:     # consumers with no compile unit
        if symbol.encode("utf-8") in (ctx.read(EXPORTS) or b""):
            raise Refusal(f"{EXPORTS} names {symbol}: an exported name is retail's own, and a retype would retire it")
        shims = ctx.grep_files(_identifier(symbol), word=True, roots=("reference/shims",))
        if shims:
            raise Refusal(f"{', '.join(shims[:3])} names {_identifier(symbol)}: a shim is not this retype's to respell")

    overlaps = extent_overlaps(ctx, rva, size, {old_name: old_rva, **{a["name"]: a["rva"] for a in absorbed}})
    if overlaps:
        raise Refusal(f"0x{rva:08X}+{size} overlaps another owner: {'; '.join(overlaps[:3])}")
    first, last, retail = retail_extent(ctx, rva, size)
    if first != owner.get("section") or last != owner.get("section"):
        raise Refusal(f"0x{rva:08X}+{size} is not inside retail {owner.get('section')} ({first} .. {last})")
    if any(retail):
        relocated = retail_relocated(ctx, rva, size)
        if relocated:
            raise Refusal(f"retail relocates a dword at 0x{rva:08X}+{relocated[0]:#x}: a pointer lives in this extent, "
                          "and an arithmetic retype cannot carry its relocation")
    if initializer is None and any(retail):
        at = next(i for i, b in enumerate(retail) if b)
        raise Refusal(f"retail holds non-zero bytes at 0x{rva:08X}+{at:#x} ({retail[at:at + 8].hex()}): the extent "
                      "is not zero-filled; pass the --initializer that spells retail's bytes")

    old_re = mangled_re(old_name)
    if extent:
        evidence = "; ".join((retail_identity.record(extent.facts), (evidence or "").strip())).strip("; ")
    plan = Plan("global", old_name, new, "retype", (evidence or "").strip(), source, rva,
                old_word=word, new_word=word)
    # sources: every file that spells the identifier, and the prepared ones
    prepared = dict(prepared or {})
    by_object = object_referencers(ctx, old_name)
    touched = set(ctx.grep_files(word, word=True, roots=("Code",))) | {source} | set(prepared) | by_object
    for row in absorbed:                             # only hand-written bytes can turn a read into an offset
        readers = set(ctx.grep_files(row["word"], word=True, roots=("Code",))) | object_referencers(ctx, row["name"])
        unprepared = sorted(readers - set(prepared))
        if unprepared:
            raise Refusal(f"{', '.join(unprepared[:3])} names {row['name']}: --absorb needs --prepared bytes reading "
                          f"it as an offset of {word}")
        touched |= readers
    generated = sorted(p for p in touched if is_generated(p))
    if generated:
        raise Refusal(f"generated source(s) name {word}: {', '.join(generated[:5])} (never edited)")
    if len(touched) > max_files:
        raise Refusal(f"{len(touched)} files name {word} (over --max-files {max_files})")
    removed, definitions, headers, mentioned = [], 0, [], set()
    for rel in sorted(touched):
        data = ctx.read(rel)
        if data is None:
            raise Refusal(f"{rel} is listed but missing")
        text = data.decode("utf-8", errors="surrogateescape")
        if rel in by_object and not re.search(r"\b" + re.escape(word) + r"\b", text):
            raise Refusal(f"{rel}'s object references {old_name} but its text never spells {word} (a macro or "
                          "generated name): the retype cannot respell it")
        if rel in prepared:
            new_text = prepared[rel].decode("utf-8", errors="surrogateescape")
        else:
            new_text, _ext, _defs = retype_declarations(text, word, new_type, owner=rel == source,
                                                         initializer=initializer)
        definitions += check_declarations(new_text, word, new_type, rel, rel == source, function_like_macros(ctx))
        for row in absorbed:
            if row["name"] in new_text or re.search(r"\b" + re.escape(row["word"]) + r"\b", name_metric.strip(new_text)):
                raise Refusal(f"{rel} still names {row['word']}, absorbed into {word}")
        new_text, _gone = remove_bridging_aliases(new_text, old_name, new)
        kept = [(a.group("a"), a.group("b")) for a in ALTERNATENAME.finditer(new_text)]
        if old_name in name_metric.strip(new_text) or any(old_name in pair for pair in kept):
            raise Refusal(f"{rel} still spells {old_name} in code (a pin, pragma or alias the retype cannot "
                          "respell): the old symbol would survive as a second name")
        # every /alternatename that named the old symbol and is gone now (bridged here, or
        # dropped by a prepared source) takes its hatch_baseline.tsv occurrence with it
        before = collections.Counter((a.group("a"), a.group("b")) for a in ALTERNATENAME.finditer(text)
                                     if old_name in (a.group("a"), a.group("b")))
        removed += [(rel, a) for (a, b), n in before.items() for _ in range(n - kept.count((a, b)))]
        new_text = old_re.sub(lambda _m: new, new_text)      # comments spelling the old symbol
        mentioned.add(rel)
        if not rel.endswith(SOURCE_SUFFIXES) or rel not in ctx.ledger_sources():
            headers.append(rel)
        if new_text == text:
            continue
        plan.source_counts[rel] = {"retyped": 1}
        plan.edit(ctx, rel, new_text.encode("utf-8", errors="surrogateescape"))
    if definitions != 1:
        raise Refusal(f"{source} holds {definitions} definitions of {word} the retype can parse; it needs exactly one")

    frozen = [rel for rel in frozen_mentions(ctx, old_name) if rel not in (DATA_LEDGER, HATCH_BASELINE)]
    if frozen:
        raise Refusal(f"{old_name} is a key in {', '.join(frozen)} (frozen, shrink-only); retyping it needs a "
                      "Verifier-Change commit that re-keys it")
    if removed:
        plan.edit(ctx, HATCH_BASELINE, hatch_lines_lowered(ctx.read(HATCH_BASELINE), removed))
    elif old_name.encode() in (ctx.read(HATCH_BASELINE) or b""):
        raise Refusal(f"hatch_baseline.tsv is keyed on {old_name}, but no bridging pragma was removed")

    moved = {} if rva == old_rva else {
        "address": f"0x{rva + IMAGE_BASE if owner.get('address_kind') == 'va' else rva:08X}"}
    new_row = dict(owner, name=new, size=str(size), **moved)
    note = f"Retyped from {old_name} ({owner.get('size')} B) to {new_type.strip()} ({size} B) by tools/rename.py " \
           f"global --retype: {plan.evidence}"
    new_row["evidence"] = (owner.get("evidence", "") + "; " + note).strip("; ")
    raw = ctx.read(DATA_ROWS)
    if new_owner:
        header = next(csv.reader(io.StringIO(raw.split(b"\n", 1)[0].decode("utf-8"))))
        raw = appended(raw, [csv_line([new_row.get(column, "") for column in header])])
    else:
        raw, found = rekey_csv_record(raw, DATA_ROWS, lambda r: r.get("name") == old_name,
                                      lambda r: r.update(name=new, size=str(size), evidence=new_row["evidence"], **moved))
    for row in absorbed:
        if row["row"]:
            raw, found = drop_csv_record(raw, DATA_ROWS, lambda r, gone=row["name"]: r.get("name") == gone)
    plan.edit(ctx, DATA_ROWS, raw)
    plan.renamed_data.append((old_name, new, old_rva))
    plan.renamed_data += [(row["name"], new, row["rva"]) for row in absorbed]
    for rel, label in ((FUNCTIONS, "functions.csv"), (SYMBOLS, "symbols.csv")):
        raw = ctx.read(rel)
        if raw is None:
            continue
        new_raw, changed = raw, []
        for symbol_re in [old_re] + [mangled_re(row["name"]) for row in absorbed]:
            new_raw, more = rewrite_records(new_raw, label, symbol_re, new)
            changed += more
        for before, after in changed:
            if rel == FUNCTIONS and before[0] != after[0]:
                raise Refusal(f"functions.csv row {before[0]} embeds {old_name} in its name")
            if rel == FUNCTIONS:
                plan.notes_rows.append((before[0], _rva(before[2])))
            else:
                plan.renamed_pins.append((before[0], after[0], before[1]))
        if changed:
            plan.edit(ctx, rel, new_raw)
    for row in ctx.dicts(DATA_LEDGER):
        if _rva(row.get("address")) in (rva, old_rva) and (row.get("name") != old_name
                                                           or row.get("source") not in ("", source)):
            raise Refusal(f"data_ledger.csv binds {row.get('address')} to {row.get('name')} "
                          f"({row.get('source') or 'no source'}), "
                          f"not {old_name} in {source}: another owner's row is not this retype's to re-key")
    if ctx.read(DATA_LEDGER) is not None:
        def rekey(r):
            # every declaration of the identifier now spells the new type, so any other
            # spelling of it bound here (an alias's class-typed extern) is gone with the retype
            names = [n for n in (r.get("names") or "").split(";") if n]
            names = sorted({new} | {n for n in names
                                    if _identifier(re.split(r"@(?=(?:Code|reference)/)", n)[0]) != word})
            r.update(name=new, size=str(size), source=source, address=f"0x{rva:08X}" if moved else r["address"])
            if absorbed:
                r["refs"] = str(int(r.get("refs") or 0) + sum(row["refs"] for row in absorbed))
            if len(names) <= 1:
                r.update(names="", defs="1", status="owned")
            else:
                r["names"] = ";".join(names)
        raw, found = rekey_csv_record(ctx.read(DATA_LEDGER), DATA_LEDGER, lambda r: _rva(r.get("address")) == old_rva,
                                      rekey)
        if found is None:
            plan.warnings.append(f"{DATA_LEDGER} has no row at 0x{old_rva:08X}; tools/data_ledger.py adds it")
        for row in absorbed:
            raw, gone = drop_csv_record(raw, DATA_LEDGER, lambda r, name=row["name"]: r.get("name") == name)
            found = found or gone
        if found is not None:
            plan.edit(ctx, DATA_LEDGER, raw)
    tombstones = [tombstone_line(gone, at, note + (f"; absorbed at 0x{at:08X} into {new}" if gone != old_name else ""))
                  for gone, at in [(old_name, old_rva)] + [(row["name"], row["rva"]) for row in absorbed]
                  if (gone, at) not in _tombstones(ctx)]
    if tombstones:
        plan.edit(ctx, DELETED, appended(ctx.read(DELETED), tombstones, header="name,target_rva,reason"))

    # every unit that spells the identifier or references the old symbol is rebuilt and
    # its object read, changed or not: an unchanged one must already be right
    verify = {rel for rel in mentioned if rel in ctx.ledger_sources()} | {source}
    if headers:
        verify |= includers(ctx, headers, max_files)
        # an `#include MACRO` names its header only after preprocessing: such a unit may
        # reach a touched header the literal-include search cannot see, so it is rebuilt
        computed = ctx.git("grep", "-l", "-E", "-e", COMPUTED_INCLUDE, "--", *SEARCH_ROOTS).splitlines()
        verify |= {rel for rel in computed if rel in ctx.ledger_sources()}
        others = [rel for rel in computed if rel not in ctx.ledger_sources()]
        if others:
            verify |= includers(ctx, others, max_files)
        for each in [word] + [row["word"] for row in absorbed]:
            verify |= {rel for rel in forced_include_units(ctx, each, headers) if rel in ctx.ledger_sources()}
    # whatever a macro builds, and whatever a stale object cannot show, the compiler says
    scan = compiler_scan(ctx, [word] + [row["word"] for row in absorbed])
    generated = sorted(rel for rel in scan["spelled"] | scan["asm"] if is_generated(rel))
    if generated:
        raise Refusal(f"generated source(s) must rebuild for {word}: {', '.join(generated[:5])} (never edited)")
    verify |= scan["spelled"] | scan["asm"]
    verify |= {r["source"] for r in ctx.rows() if (r["name"], _rva(r.get("target_rva"))) in set(plan.notes_rows)}
    plan.verify = sorted(v for v in verify if not is_generated(v))
    if len(plan.verify) > max_files:
        raise Refusal(f"{len(plan.verify)} sources to verify (over --max-files {max_files})")
    plan.claims = sorted({rva, old_rva} | {row["rva"] for row in absorbed}
                         | {at for _, at in plan.notes_rows if at is not None}) + \
        [f"file:{rel}" for rel in sorted(plan.source_counts)]
    plan.retype = {"word": word, "old": old_name, "new": new, "type": new_type.strip(), "size": size,
                   "owner": source, "row": new_row, "sources": sorted(plan.verify), "removed": removed,
                   "start": rva, "absorbed": [(row["word"], row["name"]) for row in absorbed],
                   "cleared": scan["cleared"], "hashes": scan["hashes"]}
    plan.mentions = sorted(set(ctx.grep_files(old_name, roots=("docs", "reverse"))) - set(plan.after))
    return plan


PREPROCESS_TIMEOUT = 300                             # seconds an attempt may take; a unit takes seconds
MISSING_INCLUDE = b"Cannot open include file"


def run_preprocessor(command, env, cwd, build, timeout):
    """(return code or None when it timed out, stdout, stderr) of one `cl -E`. Output goes to named
    files, never a pipe (try_compile_source's reason), and the whole tree is killed on the way
    out. cl -E can spin forever under Wine after reporting C1083, so a missing include ends the
    attempt as soon as it is reported."""
    with tempfile.NamedTemporaryFile("w+b") as out, tempfile.NamedTemporaryFile("w+b") as err:
        process = subprocess.Popen(command, cwd=cwd, env=env, stdin=subprocess.DEVNULL, stdout=out, stderr=err,
                                   start_new_session=True)
        deadline = time.monotonic() + timeout
        code = None
        try:
            while True:
                try:
                    code = process.wait(timeout=0.25)
                    break
                except subprocess.TimeoutExpired:
                    with open(err.name, "rb") as reported:
                        if MISSING_INCLUDE in reported.read():
                            build.kill_process_tree(process)
                            code = 1
                            break
                    if time.monotonic() >= deadline:
                        build.kill_process_tree(process)
                        break
        except BaseException:                        # interrupted: never leave the compiler running
            build.kill_process_tree(process)
            raise
        out.seek(0)
        err.seek(0)
        return code, out.read(), err.read()


def preprocess_unit(ctx, rel, includes=None):
    """(text, None) of `rel` after the compiler's preprocessor (cl -E under the unit's own
    build command, no -c and no -Fo, so no object is written and build/match is
    untouched), or (None, why). Its inputs are the build's: like try_compile_source, a missing
    include retries once with the sweep include directories, and a Wine launch that says nothing
    retries. An attempt past PREPROCESS_TIMEOUT retries once, and a second one reports why. Given
    a list `includes`, the compiler's /showIncludes notes fill it with the host path of every
    file the unit includes."""
    sys.path.insert(0, str(ctx.root / "tools"))
    import build
    source = ctx.path(rel)
    scratch = ctx.root / "build" / "retype_pp"
    scratch.mkdir(parents=True, exist_ok=True)
    try:
        command, env = build.compiler_command(source, scratch / (source.stem + ".obj"))
    except (Exception, SystemExit) as error:         # a unit with no build command is never read as clean
        return None, f"no build command to preprocess it with: {error}"
    command = [c for c in command if not c.startswith(("-Fo", "/Fo")) and c not in ("-c", "/c")]
    command.insert(len(command) - 1, "-E")
    if includes is not None:
        command.insert(len(command) - 1, "-showIncludes")
    swept, launches, timeouts = False, 0, 0
    while True:
        try:
            code, stdout, stderr = run_preprocessor(command, env, str(ctx.root), build, PREPROCESS_TIMEOUT)
        except OSError as error:
            return None, f"the preprocessor did not run: {error}"
        if code is None:
            timeouts += 1
            if timeouts < 2:
                continue
            return None, f"the preprocessor timed out twice, {PREPROCESS_TIMEOUT} s each"
        if code == 0:
            break
        if MISSING_INCLUDE in stderr and not swept and any(d.exists() for d in build._SWEEP_INCLUDE_DIRS):
            swept = True
            present = [d for d in build._SWEEP_INCLUDE_DIRS if d.exists()]
            env = dict(env, INCLUDE=";".join([env["INCLUDE"]] + [build.wine_path(d) for d in present]))
            command = command[:-1] + [f"-I{build.wine_path(d)}" for d in present] + command[-1:]
            continue
        said = stderr.decode("latin-1", "replace").strip()
        if launches < 2 and (not (stdout.strip() or said) or "Application could not be started" in said
                             or "ShellExecuteEx failed" in said):
            launches += 1
            continue
        return None, f"the preprocessor refused it: {said[-300:]}"
    if includes is not None:
        note = "Note: including file:"
        for line in stderr.decode("latin-1").splitlines():
            if line.startswith(note):
                host = build._case_resolve(build._host_path(line[len(note):]))
                if host is None:
                    return None, f"an included file cannot be found: {line.strip()[:200]}"
                includes.append(host)
    return stdout.decode("latin-1"), None


EXPRESSION_KEYWORDS = frozenset(("return", "sizeof", "case", "throw", "delete", "new", "else", "do", "co_return",
                                 "typeid", "decltype", "__alignof", "alignof", "if", "while", "for", "switch",
                                 "static_cast", "reinterpret_cast", "const_cast", "dynamic_cast"))
BUILTIN_TYPES = frozenset(("void", "bool", "char", "short", "int", "long", "float", "double", "signed", "unsigned",
                           "wchar_t", "__int8", "__int16", "__int32", "__int64"))
QUALIFIERS = frozenset(("const", "volatile", "static", "register", "struct", "class", "union", "enum", "typename",
                        "inline", "mutable"))
SPEC_TOKEN = re.compile(r'\s*(?P<tok>"C(?:\+\+)?"|[A-Za-z_][\w:]*)')
ATTRIBUTE_WORDS = frozenset(("__declspec", "__attribute__", "alignas", "__align"))

NAME_TOKEN = re.compile(r"\s*(?:::\s*)?([A-Za-z_]\w*)")


def _skip_balanced(text, pos, opening, closing):
    """End of the bracketed run starting at the next non-space `opening` after `pos`, or
    `pos` when there is none; None when it never closes."""
    j = pos
    while j < len(text) and text[j].isspace():
        j += 1
    if j >= len(text) or text[j] != opening:
        return pos
    depth = 0
    for k in range(j, len(text)):
        depth += 1 if text[k] == opening else -1 if text[k] == closing else 0
        if depth == 0:
            return k + 1
    return None


def declaration_shaped(prefix, types, functions):
    """Whether `prefix`, a statement's text up to the identifier, has a declaration's shape:
    a run of names (each optionally `::`-qualified and templated, attributes with their
    parentheses, cv-qualifiers), then only declarator punctuation (`*`, `&`, `(`, `const`,
    `volatile`) or earlier comma-separated declarators. Decided by syntax alone, never by
    whether a name is a known type (review of 3da3431c75: `typedef struct {...} T;`
    escaped a type list): such a statement must parse as a declaration of the new type or
    refuse. An expression statement of that shape (`a * g;`) does nothing and refuses too.
    One exception: a call whose first argument is the identifier, alone or behind unary
    `&`/`*` or redundant parentheses (`f(g)`, `memset(&g, 0, 16)`, `f((g))`), where the unit
    declares `f` as a function and not as a type."""
    pos, names = 0, []
    while True:
        m = NAME_TOKEN.match(prefix, pos)
        if not m:
            break
        name, end = m.group(1), m.end()
        if name in ATTRIBUTE_WORDS:
            end = _skip_balanced(prefix, end, "(", ")")
        else:
            while end is not None:
                end = _skip_balanced(prefix, end, "<", ">")
                tail = re.match(r"\s*::\s*[A-Za-z_]\w*", prefix[end:]) if end is not None else None
                if not tail:
                    break
                end += tail.end()
        if end is None:
            return True                              # an unclosed bracket in a type: not readable, refuse
        names.append(name)
        pos = end
    if not names or names[0] in EXPRESSION_KEYWORDS:
        return False
    parts = _split_top(prefix[pos:])
    if not re.fullmatch(r"(?:[\s\*&(]|\bconst\b|\bvolatile\b)*", parts[-1][1]):
        return False
    if len(parts) == 1 and len(names) == 1 and names[0] in functions and names[0] not in types \
            and re.fullmatch(r"\s*\((?:\s*[&*(])*\s*", parts[-1][1]):
        return False                                 # f(g), f(&g): a declared function's call
    return True


def _spec_token(statement, pos):
    """(token, end) of the next declaration-specifier token at `pos`: a name with its
    template arguments matched bracket for bracket (`vector<T, allocator<T> >`) and any
    `::name` after them, or None."""
    m = SPEC_TOKEN.match(statement, pos)
    if not m:
        return None
    tok, end = m.group("tok"), m.end()
    if tok in ATTRIBUTE_WORDS:                       # `__declspec(align(4))`: its parentheses, nested ones too
        j = end
        while j < len(statement) and statement[j].isspace():
            j += 1
        if j < len(statement) and statement[j] == "(":
            depth, k = 0, j
            while k < len(statement):
                depth += {"(": 1, ")": -1}.get(statement[k], 0)
                if depth == 0:
                    return statement[m.start("tok"):k + 1], k + 1
                k += 1
            return None                              # unbalanced: not a specifier this parser can read
        return tok, end
    while tok[0].isalpha() or tok[0] == "_":
        j = end
        while j < len(statement) and statement[j].isspace():
            j += 1
        if j >= len(statement) or statement[j] != "<":
            break
        depth, k = 0, j
        while k < len(statement):
            if statement[k] == "<":
                depth += 1
            elif statement[k] == ">":
                depth -= 1
                if depth == 0:
                    break
            elif statement[k] in ";{}":
                return tok, end                      # not template arguments: leave the name alone
            k += 1
        if depth:
            return tok, end
        end = k + 1
        tail = re.match(r"\s*::\s*[A-Za-z_][\w:]*", statement[end:])
        tok = statement[m.start("tok"):end + (tail.end() if tail else 0)]
        end += tail.end() if tail else 0
        if not tail:
            break
    return tok, end


def split_declaration(statement, types):
    """(extern, C linkage, specifier text, offset where the declarators start) when
    `statement` starts with declaration specifiers naming a type, else None. Qualifiers and
    builtin type words are part of the type; one other type name is, when the unit
    declares it as a type; the first identifier after a type is a declarator."""
    pos, words, saw_type, extern, c_linkage = 0, [], False, False, False
    while True:
        token = _spec_token(statement, pos)
        if token is None:
            break
        tok, token_end = token
        base = re.sub(r"\s*<.*", "", tok, flags=re.S).split("::")[-1]
        if tok == "extern":
            extern = True
        elif tok.startswith('"C'):
            if not extern:
                break
            c_linkage = tok == '"C"'
        elif tok in QUALIFIERS or tok.split("(")[0].strip() in ATTRIBUTE_WORDS:
            words.append(tok)
        elif base in BUILTIN_TYPES:
            words.append(tok)
            saw_type = True
        elif not saw_type and base in types:
            words.append(tok)
            saw_type = True
        else:
            break
        pos = token_end
    return (extern, c_linkage, " ".join(words), pos) if saw_type else None


DECLARATOR = re.compile(r'^\s*(?P<marks>(?:[\*&]\s*|const\s+|volatile\s+)*)(?P<lp>\(\s*(?:[\*&]\s*)*)?'
                        r'(?P<name>[A-Za-z_]\w*)\s*(?P<rp>\))?\s*(?P<array>(?:\[[^\]]*\]\s*)*)(?P<init>=.*)?$', re.S)


def _statement(code, at):
    """(start, end) of the statement around offset `at`: back to a `;`, `{` or `}` outside
    parentheses, forward to its `;` (an initializer's braces after `=` included); end is
    None when a block opens first (a function or class head)."""
    depth, i = 0, at - 1
    while i >= 0:
        c = code[i]
        if c == ")":
            depth += 1
        elif c == "(":
            depth -= 1
        elif c in ";{}" and depth <= 0:
            break
        i -= 1
    start, depth, seen_equals, j = i + 1, 0, False, i + 1     # forward from the start: depth counts from 0
    while j < len(code):
        c = code[j]
        if c in "([":
            depth += 1
        elif c in ")]":
            depth -= 1
        elif c == "=" and depth == 0:
            seen_equals = True
        elif c == "{":
            if depth == 0 and not seen_equals:
                return start, None
            depth += 1
        elif c == "}":
            depth -= 1
            if depth < 0:
                return start, None
        elif c == ";" and depth == 0:
            return start, j
        j += 1
    return start, None


def _split_top(text):
    """[(offset, part)] of `text` split at commas outside (), [], {} and <>."""
    parts, depth, last = [], 0, 0
    for i, c in enumerate(text):
        if c in "([{<":
            depth += 1
        elif c in ")]}>":
            depth -= 1
        elif c == "," and depth == 0:
            parts.append((last, text[last:i]))
            last = i + 1
    parts.append((last, text[last:]))
    return parts


# a declarator group: calling conventions or `C::`, then `*`/`&`, then the name and any bounds
DECLARATOR_GROUP = re.compile(r"\s*((?:(?:__\w+|[A-Za-z_]\w*\s*::)\s*)*)([*&\s]*)([A-Za-z_]\w*)\s*(?:\[[^\]]*\]\s*)*")


def _typedef_names(decl):
    """Every name one typedef's declarators declare (`decl`: its text after `typedef`, or after
    a struct body, up to the `;`), function types included (review of 83ba508ece: `typedef void
    F(int);` read as a function let `F(*g);` pass as a call). Per comma-separated declarator:
    the name in its first parenthesised group when that group is a declarator (a pointer,
    reference or member pointer, or a lone name followed by parameters or a bound:
    `(*F)(int)`, `(C::*F)(int)`, `(__cdecl *F)(int)`, `(F)(int)`, `(&F)[3]`); else the name
    before its parameters (`F(int)`, `F(char *p)`); else its last name (`A`, `*B`, `C[3]`)."""
    names = set()
    for _, part in _split_top(decl):
        at = part.find("(")
        close = _skip_balanced(part, at, "(", ")") if at >= 0 else None
        group = DECLARATOR_GROUP.fullmatch(part[at + 1:close - 1]) if close else None
        if group and (group.group(1).strip() or group.group(2).strip()
                      or re.match(r"\s*[(\[]", part[close:])):
            names.add(group.group(3))
            continue
        before = re.search(r"([A-Za-z_]\w*)\s*$", part[:at]) if at >= 0 else None
        if before and before.group(1) not in BUILTIN_TYPES | QUALIFIERS:
            names.add(before.group(1))
            continue
        last = re.findall(r"[A-Za-z_]\w*", re.sub(r"\[[^\]]*\]", "", part if at < 0 else part[:at]))
        if last:
            names.add(last[-1])
    return names


def _names(code):
    """(type names, function names) the preprocessed unit declares."""
    types = set(BUILTIN_TYPES)
    types |= set(re.findall(r"\b(?:class|struct|union|enum|typename)\s+([A-Za-z_]\w*)", code))
    types |= set(re.findall(r"\btypedef\b[^;{}]*?\b([A-Za-z_]\w*)\s*(?:\[[^\]]*\]\s*)*;", code))
    types |= set(re.findall(r"\btypedef\b[^;{}]*?\(\s*[\*&]\s*([A-Za-z_]\w*)\s*\)", code))
    types |= set(re.findall(r"\busing\s+([A-Za-z_]\w*)\s*=", code))
    # every name a typedef declares, after a struct body or in a list (`typedef unsigned int A, B;`):
    # these only help the parser; declaration_shaped never depends on them
    for m in re.finditer(r"\btypedef\b", code):
        body_end = _skip_balanced(code, code.find("{", m.end()) if re.match(r"[^;]*?\{", code[m.end():]) else m.end(),
                                  "{", "}")
        stop = code.find(";", body_end or m.end())
        if stop > 0:
            types |= set(re.findall(r"([A-Za-z_]\w*)\s*(?:\[[^\]]*\]\s*)*(?=,|$)", code[body_end or m.end():stop]))
            types |= _typedef_names(code[body_end or m.end():stop])
    functions = set(re.findall(r"(?:[\w>]\s+|[\*&]\s*)(?:[A-Za-z_]\w*::)*([A-Za-z_]\w*)\s*\(", code))
    functions -= BUILTIN_TYPES | QUALIFIERS | EXPRESSION_KEYWORDS | {"extern", "__declspec"}
    return types, functions


def _c_blocks(raw, code):
    """[(open, close)] of every `extern "C" { ... }` block (C linkage inside)."""
    out, stack = [], []
    for m in re.finditer(r"[{}]", code):
        if m.group() == "{":
            head = raw[max(code.rfind(c, 0, m.start()) for c in ";{}") + 1:m.start()]
            stack.append((m.start(), bool(re.search(r'\bextern\s*"C"\s*$', head))))
        elif stack:
            opened, is_c = stack.pop()
            if is_c:
                out.append((opened, m.start()))
    return out


def preprocessed_problems(text, word, new_type):
    """Every occurrence of `word` in a unit's preprocessed text that is not (i) a declaration
    parsed as `new_type` with C++ linkage, outside any extern "C" block, or (ii) a plain use:
    an initializer, a call argument of a declared function, an operand. Whatever cannot be
    classified refuses (review of 92c6d902ed: stop enumerating declaration shapes)."""
    if not re.search(r"\b" + re.escape(word) + r"\b", text):
        return []
    raw = "\n".join("" if line.lstrip().startswith("#") else line for line in text.split("\n"))
    code = name_metric.strip(raw)                    # same offsets, strings and comments blanked
    base, array = split_type(new_type)
    want = same_type(base, array)
    types, functions = _names(code)
    c_blocks = _c_blocks(raw, code)
    problems = []

    def show(a, b):
        return " ".join(raw[a:b].split())[:120]
    for m in re.finditer(r"(?<![\w$])" + re.escape(word) + r"\b", code):
        at = m.start()
        before = code[:at].rstrip()
        if before.endswith((".", "->")) or re.search(r"[A-Za-z_]\w*\s*::$", before):
            continue                                 # a member of something else, not this global
        start, end = _statement(code, at)
        statement = code[start:end] if end is not None else None
        head = split_declaration(statement, types) if statement else None
        declarator = None
        if head:
            for offset, part in _split_top(statement[head[3]:]):
                lo = start + head[3] + offset
                if lo <= at < lo + len(part):
                    declarator = (lo, DECLARATOR.match(part))
                    break
        if declarator is not None:
            lo, d = declarator
            if d is None:
                problems.append(f"declares {word} in a form the check cannot read: `{show(start, end + 1)}`")
                continue
            if d.group("init") is not None and at >= lo + d.start("init"):
                continue                             # used in an initializer
            if d.group("name") != word or lo + d.start("name") != at:
                if "[" in part[:at - lo] and d.group("array"):
                    continue                         # inside an array bound
                problems.append(f"names {word} inside a declaration it cannot read: `{show(start, end + 1)}`")
                continue
            spec = head[2] + " " + d.group("marks") + (d.group("lp") or "").replace("(", " ")
            got = same_type(spec, d.group("array"))
            # the C linkage marker is a string literal, blanked in `code`: read it from `raw`
            c_linkage = bool(head[0] and re.match(r'\s*extern\s+"C"', raw[start:start + head[3]]))
            c_linkage |= any(a < at < b for a, b in c_blocks)
            if got != want or c_linkage:
                problems.append(f"declares {word} as `{show(start, end + 1)}`" + (" (C linkage)" if c_linkage else "")
                                + " after preprocessing")
            continue
        # not inside a declaration this check parsed: a declaration-shaped statement refuses,
        # anything else is a plain use or refuses below
        if declaration_shaped(code[start:at], types, functions):
            problems.append(f"names {word} in a statement shaped like a declaration that does not parse as one: "
                            f"`{show(start, (end or at + len(word)) + 1)}`")
            continue
        # a parameter is a declaration too: the current comma part inside the innermost open
        # parenthesis (`void f(int a, unsigned *g)`); a call's argument has no name run there
        depth, q = 0, at - 1
        while q >= start:
            depth += {")": 1, "(": -1}.get(code[q], 0)
            if depth < 0:
                break
            q -= 1
        if q >= start and declaration_shaped(_split_top(code[q + 1:at])[-1][1], types, set()):
            problems.append(f"names {word} where a parameter is declared: `{show(start, (end or at + len(word)) + 1)}`")
            continue
        prev = before[-1:] if before else ""
        word_before = re.search(r"([A-Za-z_]\w*)$", before)
        if word_before and word_before.group(1) not in EXPRESSION_KEYWORDS:
            problems.append(f"names {word} after `{word_before.group(1)}`, which the check cannot read as a use: "
                            f"`{show(start, (end or at + len(word)) + 1)}`")
            continue
        if prev == "(" and re.search(r"([A-Za-z_][\w:]*)\s*\($", before):
            callee = re.search(r"([A-Za-z_][\w:]*)\s*\($", before).group(1)
            # a declared function's argument, a keyword's operand, or a functional cast
            # (`unsigned(g) + 1`): the statement is not declaration-shaped, checked above
            if callee.split("::")[-1] not in functions | types and callee not in EXPRESSION_KEYWORDS:
                problems.append(f"names {word} as the argument of `{callee}`, neither a declared function nor an "
                                f"expression keyword: `{show(start, (end or at + len(word)) + 1)}`")
            continue
        if prev == ">" and not before.endswith("->"):
            problems.append(f"names {word} after a template's `>`: `{show(start, (end or at + len(word)) + 1)}`")
            continue
        if statement is not None and head:
            problems.append(f"names {word} in a declaration it cannot read: `{show(start, end + 1)}`")
            continue
        # operand of an operator, a cast, an argument after `,`/`(`, or a statement start: a use
    return problems


def linker_directives(data):
    """The text of an object's .drectve sections: references no symbol table has to show."""
    sys.path.insert(0, str(ROOT / "tools"))
    import reloc_ledger
    sections, _symbols = reloc_ledger.parse_coff(data)
    return "".join(s["body"].decode("latin-1") for s in sections if s["name"] == ".drectve" and s["body"])


def cleared_input_problems(ctx, retype):
    """Why a clearance no longer holds: the source, an included file or the command a cleared unit
    was read with has changed since the scan, so the scan's answer was about other text. Refusing
    is enough: a retype is rare, and re-running it asks again. A unit this retype rebuilds is
    judged on its object, not its clearance."""
    cleared, hashes = retype.get("cleared") or {}, retype.get("hashes") or {}
    changed = {each for each, digest in hashes.items() if file_digest(each) != digest}
    problems = []
    for rel, (command, files) in sorted(cleared.items()):
        if rel in retype["sources"]:
            continue
        moved = sorted(changed.intersection(files))
        if moved:
            problems.append(f"{rel} was cleared by the compiler scan but {moved[0]} changed since: re-run the retype")
        elif unit_command_fingerprint(ctx, rel) != command:
            problems.append(f"{rel} was cleared by the compiler scan but its build command changed since: re-run the retype")
    return problems


def outside_references(ctx, retype, objects):
    """Why an object outside the rebuilt set may still name the old, new or absorbed symbols: it
    does, in its symbol table or its linker directives, or it is stale or missing and compiler_scan
    did not clear its unit. Nothing falls back to a source's text."""
    import build
    import name_dependents
    names = {retype["old"], retype["new"]} | {name for _word, name in retype["absorbed"]}
    words = [retype["word"]] + [word for word, _name in retype["absorbed"]]
    problems = []
    for rel, paths in sorted(objects.items()):
        if rel in retype["sources"]:
            continue
        library = rel.lower().endswith(build.LIB_SUFFIX)
        if paths and all(p.exists() and (library or build.compile_is_current(ctx.path(rel), p)) for p in paths):
            datas = [p.read_bytes() for p in paths]
            if any(names & name_dependents.coff_symbol_names(data, include_local=False) for data in datas):
                problems.append(f"{rel} references {retype['word']} but this retype did not rebuild it")
            for word in words:
                if any(word.encode() in data and word in linker_directives(data) for data in datas):
                    problems.append(f"{rel}'s linker directives name {word} but this retype did not rebuild it")
        elif rel not in retype.get("cleared", ()):
            problems.append(f"{rel}'s object is stale or missing and the compiler scan did not clear it")
    return problems


def retype_reference_problems(ctx, retype):
    """Every absolute reference a rebuilt row makes into the extent goes through the new symbol
    at its start. The byte gate masks DIR32 operands, so a wrong addend (P35's table read at +0
    rather than +0x100) or another symbol placed inside the extent passes it: here retail's
    pointer less the compiled addend must be the start. A reference to the symbol anywhere else
    in a rebuilt object must lie in a row too, a data row's initializer proven by data_rows.py,
    and no object outside the rebuilt set may name the old, new or absorbed symbols: what cannot
    be compared with retail refuses (outside_references)."""
    sys.path.insert(0, str(ctx.root / "tools"))
    import build
    import data_rows
    import name_dependents
    import reloc_ledger
    start = IMAGE_BASE + retype["start"]
    end, sources, statics, problems = start + retype["size"], set(retype["sources"]), {}, []
    rows, datas = build.load_function_rows(), data_rows.load()
    objects = name_dependents.merged(name_dependents._row_objects(rows), name_dependents._data_row_objects(datas))
    problems += cleared_input_problems(ctx, retype)
    problems += outside_references(ctx, retype, objects)
    spans = collections.defaultdict(list)            # {source: [(symbol, size, data row or None)]}
    for row in rows:
        if row["source"] in sources:
            spans[row["source"]].append((build.ledger_object_symbol(row), int(row.get("target_size") or 0), None))
    for row in datas:
        if row.get("source") in sources:
            spans[row["source"]].append((row["name"], int(row.get("size") or 0), row))
    img, resolve = None, None
    for rel in sorted(sources):
        path = build.obj_path(ctx.path(rel))
        if not path.exists():
            problems.append(f"{rel} has no object to read its references from")
            continue
        sections, symbols = reloc_ledger.parse_coff(path.read_bytes())
        where = {s["name"]: s for s in symbols.values() if s["section"] > 0}
        for section in sections:
            if section["name"].startswith(".debug"):
                continue
            for offset, index, _kind in section["relocs"]:
                if symbols[index]["name"] != retype["new"]:
                    continue
                owners = [(size, row) for symbol, size, row in spans[rel] if symbol in where
                          and where[symbol]["section"] == section["number"]
                          and where[symbol]["value"] <= offset < where[symbol]["value"] + size]
                if not owners:
                    problems.append(f"{rel} references {retype['new']} at {section['name']}+{offset:#x}, where no row "
                                    "says what retail holds: nothing can prove its addend")
                for _size, row in owners:
                    if row is not None:
                        if img is None:
                            img, resolve = reloc_ledger.Image(), data_rows.Resolver(datas)
                        ok, message = data_rows.verify_row(row, img, resolve, compile=False)
                        if not ok:
                            problems.append(f"{row['name']}'s initializer references {retype['new']}: {message}")
    for row in rows:
        if row["source"] not in sources:
            continue
        pairs = build._dir32_row_pairs(row, build.obj_path(ctx.path(row["source"])), statics)
        if pairs is None:
            problems.append(f"{row['name']}'s body cannot be read from {row['source']}'s object")
            continue
        for identity, base in pairs:
            if identity == retype["new"]:
                if base != start:
                    problems.append(f"{row['name']} reads {identity} from base 0x{base:08X}, not 0x{start:08X}: "
                                    "its addend is not its offset in the extent")
            elif start <= base < end:
                problems.append(f"{row['name']} reaches 0x{base:08X}, inside the extent, through {identity}")
    return problems


def retype_object_problems(ctx, retype):
    """After ./build.sh: every rebuilt unit's preprocessed text declares the global only as
    the new type (preprocessed_problems) and names no absorbed row, the owner's object defines the new
    symbol once and no dynamic initializer for it, no rebuilt object names the old symbol or an
    absorbed one, every reference into the extent is its start plus an offset, and data_rows.py
    proves the new row (compiler sizeof, retail bytes, relocations)."""
    sys.path.insert(0, str(ctx.root / "tools"))
    import build
    import data_rows
    import reloc_ledger
    problems, definitions = [], []
    word, old, new = retype["word"], retype["old"], retype["new"]
    for rel in retype["sources"]:                    # every declaration, as the compiler sees it
        if not rel.endswith(SOURCE_SUFFIXES):        # an assembler source: its object is read below
            continue
        text, why = preprocess_unit(ctx, rel)
        if text is None:
            problems.append(f"{rel}: {why}")
            continue
        problems += [f"{rel} {what}" for what in preprocessed_problems(text, word, retype["type"])]
        problems += [f"{rel} still names {gone} after the preprocessor, absorbed into {word}"
                     for gone, _name in retype["absorbed"] if re.search(r"\b" + re.escape(gone) + r"\b", text)]
    for rel in retype["sources"]:
        obj = build.obj_path(ctx.path(rel))
        if not obj.exists():
            problems.append(f"{rel} has no object after the build")
            continue
        data = obj.read_bytes()
        _sections, symbols = reloc_ledger.parse_coff(data)
        names = [s["name"] for s in symbols.values()]
        directives = linker_directives(data)
        problems += [f"{rel}'s linker directives still name {gone}, retired by this retype"
                     for gone in [old] + [word for word, _name in retype["absorbed"]] if gone in directives]
        if old in names:
            problems.append(f"{rel}'s object still names {old} (a second symbol for 0x{retype['row']['address']})")
        problems += [f"{rel}'s object still names {symbol}, absorbed into {word}" for gone, _name in retype["absorbed"]
                     for symbol in names if symbol.startswith(f"?{gone}@@")]
        defined = [s for s in symbols.values() if s["name"] == new and s["storage"] == data_rows.EXTERNAL
                   and (s["section"] > 0 or s["value"] > 0)]
        definitions += [rel] * len(defined)
        if rel == retype["owner"]:
            inits = sorted({n for n in names if n.startswith((f"??__E{word}@@", f"??__F{word}@@"))})
            if inits:
                problems.append(f"{rel}'s object now constructs {word} itself ({', '.join(inits)}); retail's rowed "
                                "initializer already does, so the image would construct and destroy it twice: "
                                "retype to a type without a constructor (its extent) instead")
    if definitions != [retype["owner"]]:
        problems.append(f"{new} is defined {len(definitions)} time(s) across the rebuilt objects "
                        f"({', '.join(sorted(definitions)) or 'nowhere'}); it must be once, in {retype['owner']}")
    if not problems:
        problems += retype_reference_problems(ctx, retype)
    if not problems:
        img, resolve = reloc_ledger.Image(), data_rows.Resolver(data_rows.load())
        ok, message = data_rows.verify_row(retype["row"], img, resolve, compile=False)
        if not ok:
            problems.append(f"data_rows.py refuses the retyped row: {message}")
    return problems


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
HEADER_QUEUE = "reverse/header_queue.tsv"
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


# ---------------------------------------------------------------- registered classes
#
# A class registered in reverse/canonical_classes.csv has a canonical header, a
# contract (reverse/class_contracts/<class>.json, tools/class_contract.py) and
# usually private views in units that have not adopted the header yet
# (reverse/header_queue.tsv). Its placeholder name moves with all of them in one
# commit, or the gates read the result as something else: class_gate sees every
# respelled private view as a new copy of NEW, and repair_queue sees each
# header_queue.tsv row re-keyed to NEW as retired debt. Both credit exactly this
# change (class_views.recorded_class_renames): the commit's name_basis.csv `class`
# record plus the one registry key moved to NEW under the header OLD had. So the
# plan, on top of the token rewrite, re-keys the registry row (and its contract
# note), git-mvs the contract to NEW.json with its spellings respelled, and
# re-keys OLD's header_queue.tsv rows (same source, same RVAs). The header keeps
# its path: the file kind refuses a header others include. After ./build.sh no
# rebuilt unit's object may name a symbol OLD scopes or types.

def class_registration(ctx, old, new, basis=None):
    """What the registry holds for `old` when `old` is registered, else None; refuses a
    registration this rename cannot move: a readable OLD (two real names are a
    reconciliation) unless the basis is `restored` (check_restore then proves the exact
    inverse of an inferred landing), two registry rows, a missing or mismatched contract,
    an orphan contract, or a NEW that is registered or has a contract already."""
    rows = [r for r in ctx.dicts(CANONICAL_CLASSES) if r.get("class") == old]
    contract = f"{CLASS_CONTRACTS}/{old}.json"
    if not rows and ctx.read(contract) is None:
        return None
    if not rows:
        raise Refusal(f"{contract} exists but {CANONICAL_CLASSES} registers no {old}: an orphan contract "
                      "is no registration this rename can move")
    if not is_placeholder(old, "class") and basis != RESTORED:
        raise Refusal(f"{old} is a readable class registered in {CANONICAL_CLASSES}: only a placeholder's key "
                      "moves with a rename (or an inferred one back to its placeholder, by `rename.py revert`); "
                      "choosing between real names is a class reconciliation")
    if len(rows) != 1:
        raise Refusal(f"{CANONICAL_CLASSES} registers {old} {len(rows)} times; one key must move")
    if any(r.get("class") == new for r in ctx.dicts(CANONICAL_CLASSES)) or \
            ctx.read(f"{CLASS_CONTRACTS}/{new}.json") is not None:
        raise Refusal(f"{new} is registered in {CANONICAL_CLASSES} / {CLASS_CONTRACTS} already: two registered "
                      "classes are one only through a reconciliation (or class --fold), not a rename")
    data = ctx.read(contract)
    if data is None:
        raise Refusal(f"{old} is registered in {CANONICAL_CLASSES} but {contract} is missing; write it with "
                      f"tools/class_contract.py --class {old} --write first")
    try:
        frozen = json.loads(data.decode("utf-8"))
    except ValueError as error:
        raise Refusal(f"{contract} is not JSON: {error}") from None
    if not isinstance(frozen, dict) or frozen.get("class") != old:
        raise Refusal(f"{contract} is the contract of {frozen.get('class') if isinstance(frozen, dict) else '?'}, "
                      f"not {old}")
    header = rows[0].get("header") or ""
    refuse_vendored(ctx, {header}, f"renaming the registered class {old}")
    return {"old": old, "new": new, "header": header, "contract": contract, "contract_bytes": data}


def check_registered_basis(ctx, header, basis, evidence, old, new):
    """check_basis for a registered class's rename, plus the exact key: an inferred
    name's agreement must be the one name_lane serves for this class, its canonical
    header's `<header>|class||OLD`, not an agreement reached on another unit's view."""
    which = check_basis(ctx, "class", basis, evidence, old, old, None, new_name=new, new_word=new)
    if which == "inferred":
        rid = re.fullmatch(r"agree:([A-Za-z0-9_.:-]+)", evidence.strip())
        rows = [r for r in ctx.dicts(AGREED) if rid and r.get("id") == rid.group(1)]
        if not rows:
            raise Refusal(f"an inferred registered-class name needs an agreement record in {AGREED}, not {evidence!r}")
        rid, key = rid.group(1), rows[-1].get("key")
        if key != f"{header}|class||{old}":
            raise Refusal(f"agreement record {rid} was reached at {key}, not at {old}'s canonical header "
                          f"({header}|class||{old}; name_lane.py next --registered {old})")
        if isinstance(ctx, RevisionContext) and not rid.startswith("nr-"):
            votes_bound_to_text(ctx, rid, key, new, header)
    return which


# tools/name_lane.py `submit` writes, beside each vote, the fingerprint of the source text
# it served the voter (name_vote_sources.csv, append-only, one row per vote).
VOTE_SOURCES = "reverse/name_vote_sources.csv"


def votes_bound_to_text(ctx, rid, key, new, rel):
    """A gate's credit is bound to the text each vote named. An `nl-` vote's row carries
    no fingerprint (an `nr-` resolution does, and check_agreement checks it), so
    `submit` records one beside it: the sha256 of the source it served (VOTE_SOURCES).
    Every vote counted for `new` at `key` needs such a row in the base, and its
    fingerprint must be the sha256 of base's `rel`, the text the rename is applied to.
    A vote with no fingerprint, or one cast on any other text -- edited before, with,
    or after the votes, in whatever order the commits land -- earns nothing."""
    base = ctx.base or "HEAD"
    data = ctx.read(rel)
    if data is None:
        raise Refusal(f"{rel} is not in {base}")
    applied = hashlib.sha256(data).hexdigest()
    wanted = name_agreement.digest(key, new)
    votes = [v for v in ctx.dicts(name_agreement.VOTES) if v.get("key") == key and v.get("hash") == wanted]
    if not votes:
        raise Refusal(f"no vote for {new} at {key} is in {base}'s {name_agreement.VOTES}")
    sources = collections.defaultdict(list)
    for row in ctx.dicts(VOTE_SOURCES):
        sources[tuple(row.get(c) or "" for c in ("key", "hash", "worker", "session"))].append(row)
    for vote in votes:
        rows = sources.get(tuple(vote.get(c) or "" for c in ("key", "hash", "worker", "session")), [])
        if not rows:
            raise Refusal(f"the vote by {vote.get('worker')} records no fingerprint of the text it was served "
                          f"({VOTE_SOURCES}); serve the key again and vote")
        if {r.get("source_sha") for r in rows} != {applied}:
            raise Refusal(f"the vote by {vote.get('worker')} named another text of {rel} than {base} holds: "
                          "serve the key again and vote")
        for row in rows:
            fingerprint_bound(ctx, row, rel)


VOTE_SOURCE_FIELDS = ("key", "hash", "worker", "session", "source_sha")


def fingerprint_bound(ctx, row, rel):
    """A fingerprint row is a claim until history binds it: the one commit that added its
    exact line (VOTE_SOURCES is append-only, so a line is added once and never edited or
    removed) must hold, in its own tree, `rel` with exactly that sha256. The hook
    (tools/class_gate.py --staged) refuses any other change; this reads history itself, so
    a commit made around the hook gains nothing either."""
    base = ctx.base or "HEAD"
    line = ",".join(row.get(c) or "" for c in VOTE_SOURCE_FIELDS)
    vote = ",".join(row.get(c) or "" for c in VOTE_SOURCE_FIELDS[:4]) + ","
    # every line this vote's fingerprint ever had, added (+) or removed (-), commit by commit
    _code, patches = _git_out(ctx.root, "log", "-p", "--format=COMMIT %H", "--no-renames", "--unified=0", base,
                              "--", VOTE_SOURCES)
    changes, commit = [], None
    for text in patches.decode("utf-8", errors="replace").splitlines():
        if text.startswith("COMMIT "):
            commit = text.split()[1]
        elif text[:1] in "+-" and not text.startswith(("+++", "---")) and text[1:].startswith(vote):
            changes.append((commit, text[:1], text[1:]))
    if changes != [(changes[0][0] if changes else None, "+", line)]:
        raise Refusal(f"the fingerprint of the vote by {row.get('worker')} was not added once and left alone "
                      f"({len(changes)} change(s) in {VOTE_SOURCES}, which is append-only)")
    code, blob = _git_out(ctx.root, "show", f"{changes[0][0]}:{rel}")
    if code or hashlib.sha256(blob).hexdigest() != row.get("source_sha"):
        raise Refusal(f"the commit adding the fingerprint of the vote by {row.get('worker')} ({changes[0][0][:10]}) "
                      f"holds another text of {rel}: a fingerprint is bound when it is added")


# The gates (tools/class_gate.py, tools/repair_queue.py) credit a registered class's
# rename only when its record is an approval this very check accepts, and they run
# it from the BASE revision's tools (`verify-record`), never the commit's own copy,
# against the BASE revision's data: votes, agreements and resolutions land in their
# own name_lane commits before the rename that cites them, so nothing the judged
# commit adds to a vote ledger counts towards its own credit, and a commit cannot
# loosen the check it is judged by. Only the record being judged is read from the
# target (verify_record). A path inside a submodule (a Zero Hour citation under
# reference/open-bfme-1) is read at the commit the base pins for that submodule.


# Trusted history is read as git wrote it, from the checkout's own repository: every git call
# of the registered-class rename, its credit check (verify-record) and its prepared-unit proof
# runs under git_trust.trusted_env (no GIT_DIR/GIT_WORK_TREE/GIT_COMMON_DIR of the caller's,
# no replace objects), behind git_trust.preflight.
def trusted_env(extra=None):
    return git_trust.trusted_env(extra)


class RevisionContext(Context):
    """A Context reading the git revision `base` (gitlinks followed), read-only, with no
    object scan."""

    def __init__(self, root, base):
        super().__init__(root, object_scan=False)
        self.base = base
        self._gitlinks = None

    def gitlinks(self):
        """{submodule path: the commit `base` pins} for every gitlink in base's tree."""
        if self._gitlinks is None:
            listed = subprocess.run(["git", "-C", str(self.root), "ls-tree", "-r", "-z", self.base or "HEAD"],
                                    capture_output=True, env=trusted_env())
            self._gitlinks = {}
            for entry in listed.stdout.decode("utf-8", "surrogateescape").split("\0"):
                meta, _, path = entry.partition("\t")
                parts = meta.split()
                if len(parts) == 3 and parts[0] == "160000":
                    self._gitlinks[path] = parts[2]
        return self._gitlinks

    def read(self, rel):
        for link, commit in self.gitlinks().items():
            if rel.startswith(link + "/"):
                result = subprocess.run(["git", "-C", str(self.root / link), "show",
                                         f"{commit}:{rel[len(link) + 1:]}"], capture_output=True, env=trusted_env())
                return result.stdout if result.returncode == 0 else None
        result = subprocess.run(["git", "-C", str(self.root), "show", f"{self.base}:{rel}"], capture_output=True,
                                env=trusted_env())
        return result.stdout if result.returncode == 0 else None


def verify_record(root, base, target, old, new):
    """Refuse unless the `class,OLD,NEW` name_basis.csv record that target adds over
    base is an approval check_registered_basis accepts for OLD's registration at base."""
    git_trust.preflight(root, "verify-record", Refusal)
    ctx = RevisionContext(root, base)

    def records(ref):
        shown = subprocess.run(["git", "-C", str(root), "show", f"{ref}:{NAME_BASIS}"], capture_output=True,
                               env=trusted_env())
        return list(csv.DictReader(io.StringIO(shown.stdout.decode("utf-8") if shown.returncode == 0 else "")))
    before = {tuple(sorted(r.items())) for r in records(base)}
    added = [r for r in records(target) if r.get("kind") == "class" and r.get("old") == old
             and r.get("new") == new and tuple(sorted(r.items())) not in before]
    if len(added) != 1:
        raise Refusal(f"target adds {len(added)} `class,{old},{new}` record(s) to {NAME_BASIS}, not one")
    rows = [r for r in ctx.dicts(CANONICAL_CLASSES) if r.get("class") == old]
    if len(rows) != 1:
        raise Refusal(f"base registers {old} {len(rows)} time(s) in {CANONICAL_CLASSES}")
    which = check_registered_basis(ctx, rows[0].get("header") or "", added[0].get("basis") or "",
                                   added[0].get("evidence") or "", old, new)
    if which == RESTORED:
        inverse_problems = revert_inverse_problems(root, base, target, added[0])
        if inverse_problems:
            raise Refusal(f"the revert is not the exact inverse of its landing: {inverse_problems[0]}")
    return which


# Below the evidence, a revert's credit also needs its CHANGE to be the landing's
# inverse: the landing commit's diff, reversed and applied to base, must give
# target's tree exactly, outside name_basis.csv and deleted_rows.csv. Those two
# take exactly what a revert writes: name_basis.csv only the one restored record,
# deleted_rows.csv the landing's tombstones lifted and each landed name tombstoned
# `Renamed to <placeholder> by tools/rename.py (restored)`. A revert that edits
# anything else -- a field's type, a view, another row -- or a landing a later
# commit has since touched (the reversed diff no longer applies) gets no credit.
REVERT_FREE = (NAME_BASIS, DELETED)


def _git_out(root, *args, env=None, data=None):
    result = subprocess.run(["git", "-C", str(root), *args], capture_output=True, input=data, env=trusted_env(env))
    return result.returncode, result.stdout


def _tree_of(root, rev):
    """The tree id of `rev` ('' is the index)."""
    if rev:
        return _git_out(root, "rev-parse", f"{rev}^{{tree}}")[1].decode().strip()
    return _git_out(root, "write-tree")[1].decode().strip()


def _rev_lines(root, rev, rel):
    """`rel`'s lines at revision `rev` ('' is the index), [] when absent."""
    shown = subprocess.run(["git", "-C", str(root), "show", f"{rev}:{rel}"], capture_output=True, env=trusted_env())
    return shown.stdout.decode("utf-8", "replace").splitlines() if shown.returncode == 0 else []


def landing_commit(root, rid, base):
    """The one commit in `base`'s history that wrote agree:<rid> into name_basis.csv."""
    code, out = _git_out(root, "log", "--format=%H", f"-Sagree:{rid}", base or "HEAD", "--", NAME_BASIS)
    landings = out.decode().split()
    if code or len(landings) != 1:
        raise Refusal(f"{len(landings)} commit(s) in {base or 'HEAD'}'s history wrote agree:{rid} into "
                      f"{NAME_BASIS}, not one: no landing to reverse")
    return landings[0]


def inverse_tree(root, base, landing):
    """The tree id of `base` with the landing commit's diff, outside REVERT_FREE, reversed;
    Refusal when it no longer applies (a later commit touched the landing's lines)."""
    with tempfile.TemporaryDirectory(prefix="revert-inverse-") as tmp:
        env = {"GIT_INDEX_FILE": str(Path(tmp) / "index")}
        if _git_out(root, "read-tree", base or "HEAD", env=env)[0]:
            raise Refusal(f"cannot read {base or 'HEAD'}'s tree")
        excluded = [f":(exclude){rel}" for rel in REVERT_FREE]
        _code, patch = _git_out(root, "diff", "--binary", "--no-renames", landing, f"{landing}^", "--", ".", *excluded)
        if patch and _git_out(root, "apply", "--cached", "--binary", "-", env=env, data=patch)[0]:
            raise Refusal(f"the landing {landing[:10]}'s diff no longer reverses cleanly over {base or 'HEAD'} "
                          "(a later commit touched its lines); revert it by hand")
        return _git_out(root, "write-tree", env=env)[1].decode().strip()


def landing_tombstones(root, landing):
    """The deleted_rows.csv lines the landing commit added, in its order."""
    left = collections.Counter(_rev_lines(root, f"{landing}^", DELETED))
    added = []
    for line in _rev_lines(root, landing, DELETED):
        if left[line]:
            left[line] -= 1
        else:
            added.append(line)
    return added


def restored_tombstones(landed):
    """The tombstones a revert writes for the landing's: each landed name, `Renamed to
    <placeholder> by tools/rename.py (restored)`, in the landing's order."""
    out = []
    for line in landed:
        row = next(csv.reader([line]), [])
        reason = LANDED_TOMBSTONE.match(row[2]) if len(row) >= 3 else None
        if reason:
            text = tombstone_line(reason.group(1), _rva(row[1]), f"Renamed to {row[0]} by tools/rename.py ({RESTORED})")
            out.append((text.decode("utf-8") if isinstance(text, bytes) else text).rstrip("\r\n"))
    return out


def lifted_in_place(lines, landed):
    """`lines` with each landed line removed once, every other line kept in its place;
    None when one of them is missing."""
    want = collections.Counter(landed)
    out = []
    for line in lines:
        if want[line]:
            want[line] -= 1
        else:
            out.append(line)
    return None if +want else out


def revert_inverse_problems(root, base, target, record):
    """Why target is not exactly the landing's inverse over base, or []. Outside
    REVERT_FREE the trees must be equal; the two ledgers must change by exactly what a
    revert writes, as an ORDERED diff (name protection reads a name's last record, so a
    reordered, repeated or extra line is a change of meaning, not noise):
    name_basis.csv is base's lines unchanged and in place plus the one restored record
    at the end; deleted_rows.csv is base's lines with each of the landing's tombstones
    removed once, every other line in place, plus the restored tombstones at the end."""
    match = REVERT_RE.fullmatch((record.get("evidence") or "").strip())
    try:
        landing = landing_commit(root, match.group(1) if match else "", base)
        expected = inverse_tree(root, base, landing)
    except Refusal as why:
        return [str(why)]
    problems = []
    excluded = [f":(exclude){rel}" for rel in REVERT_FREE]
    code, out = _git_out(root, "diff", "--name-only", "--no-renames", expected, _tree_of(root, target), "--", ".",
                         *excluded)
    if code or out.strip():
        changed = out.decode().split()
        problems.append(f"it changes {', '.join(changed[:3])} beyond the landing's inverse" if changed
                        else "cannot compare its tree with the landing's inverse")
    before, after = _rev_lines(root, base, NAME_BASIS), _rev_lines(root, target, NAME_BASIS)
    if after[:len(before)] != before or len(after) != len(before) + 1:
        problems.append(f"{NAME_BASIS} must be base's lines, unchanged and in place, plus the one restored record")
    landed = landing_tombstones(root, landing)
    kept = lifted_in_place(_rev_lines(root, base, DELETED), landed)
    if kept is None or _rev_lines(root, target, DELETED) != kept + restored_tombstones(landed):
        problems.append(f"{DELETED} must be base's lines with the landing's tombstones lifted (every other line in "
                        "place) plus exactly the restored tombstones")
    return problems


def plan_registered_revert(ctx, old, new, evidence, registration, max_files):
    """The revert of a registered class's rename: the landing commit's diff reversed over
    HEAD (inverse_tree), so every file comes back exactly -- NEW's spellings the landing
    never touched (a --merge-existing landing) stay as they were -- plus the one restored
    name_basis.csv record and the restored tombstones; rename_plan then lifts the
    landing's own. `old` is the landed name, `new` the placeholder it replaced."""
    git_trust.preflight(ctx.root, "rename.py revert of a registered class", Refusal)
    rid = REVERT_RE.fullmatch(evidence.strip()).group(1)
    landing = landing_commit(ctx.root, rid, "HEAD")
    expected = inverse_tree(ctx.root, "HEAD", landing)
    excluded = [f":(exclude){rel}" for rel in REVERT_FREE]
    _code, out = _git_out(ctx.root, "diff", "--name-status", "--no-renames", "HEAD", expected, "--", ".", *excluded)
    status = [line.split("\t", 1) for line in out.decode().splitlines() if "\t" in line]
    plan = Plan("class", old, new, RESTORED, evidence.strip(), registration["header"], None, old_word=old,
                new_word=new)

    def blob(rel):
        return _git_out(ctx.root, "show", f"{expected}:{rel}")[1]
    added = [rel for code, rel in status if code == "A"]
    deleted = [rel for code, rel in status if code == "D"]
    contract_old, contract_new = f"{CLASS_CONTRACTS}/{old}.json", f"{CLASS_CONTRACTS}/{new}.json"
    if sorted(added) != [contract_new] or sorted(deleted) != [contract_old]:
        raise Refusal(f"the reversed landing adds {added or 'nothing'} and deletes {deleted or 'nothing'}, not just "
                      f"the contract move {contract_old} -> {contract_new}; revert it by hand")
    for code, rel in status:
        head = _git_out(ctx.root, "show", f"HEAD:{rel}")[1] if code != "A" else None
        if code != "A" and ctx.read(rel) != head:
            raise Refusal(f"{rel} has edits beyond HEAD; commit or put them aside before reverting")
        if code == "M":
            plan.edit(ctx, rel, blob(rel))
    plan.moves.append((contract_old, contract_new))
    plan.moved_bytes[contract_old] = ctx.read(contract_old)
    plan.edit(ctx, contract_new, blob(contract_new))
    landed = landing_tombstones(ctx.root, landing)
    plan.edit(ctx, DELETED, appended(ctx.read(DELETED), [(line + "\n").encode("utf-8")
                                                         for line in restored_tombstones(landed)],
                                     header="name,target_rva,reason"))
    plan.edit(ctx, NAME_BASIS, appended(ctx.read(NAME_BASIS), [csv_line(
        ["class", old, new, RESTORED, plan.evidence, registration["header"], ""])], header=NAME_BASIS_HEADER))
    for line in landed:
        row = next(csv.reader([line]), [])
        reason = LANDED_TOMBSTONE.match(row[2]) if len(row) >= 3 else None
        if reason:
            plan.renamed_rows.append((reason.group(1), row[0], _rva(row[1])))
    edited = {rel for code, rel in status if code == "M"}
    verify = {rel for rel in edited if rel in ctx.ledger_sources()}
    headers = [rel for rel in edited if rel.startswith(("Code/", "reference/shims/")) and rel not in verify]
    if headers:
        verify |= includers(ctx, headers, max_files)
    plan.verify = sorted(v for v in verify if v and not is_generated(v) and v in ctx.ledger_sources())
    if len(plan.verify) > max_files:
        raise Refusal(f"{len(plan.verify)} sources to verify (over --max-files {max_files})")
    plan.claims = sorted({at for _o, _n, at in plan.renamed_rows if at is not None}) + [f"class:{old}"]
    plan.registered = {"old": old, "new": new, "header": registration["header"], "contract": contract_old,
                       "stale": sorted({n for n, _o, _a in plan.renamed_rows}),
                       "moved": [f"the landing {landing[:10]}'s diff reversed: {len(edited)} file(s), "
                                 f"git mv {contract_old} {contract_new}"]}
    return plan


def _respelled_strings(value, token, new):
    """`value` (parsed JSON) with every string, keys included, token-respelled."""
    if isinstance(value, dict):
        return {token.sub(new, k): _respelled_strings(v, token, new) for k, v in value.items()}
    if isinstance(value, list):
        return [_respelled_strings(v, token, new) for v in value]
    return token.sub(new, value) if isinstance(value, str) else value


def move_registration(ctx, plan, registration):
    """Add the registry key, contract and header_queue.tsv moves to a class plan."""
    old, new = registration["old"], registration["new"]
    token = class_token_re(old)
    moved = []
    raw = ctx.read(CANONICAL_CLASSES).decode("utf-8")
    lines = raw.split("\n")
    at = [i for i, line in enumerate(lines) if line.split(",", 1)[0] == old]
    if len(at) != 1 or lines[at[0]].startswith('"'):
        raise Refusal(f"{CANONICAL_CLASSES}: {old}'s row is not one plain CSV line; re-key it by hand first")
    line = lines[at[0]]
    lines[at[0]] = new + line[len(old):].replace(f"class_contracts/{old}.json", f"class_contracts/{new}.json")
    plan.edit(ctx, CANONICAL_CLASSES, "\n".join(lines).encode("utf-8"))
    moved.append(f"{CANONICAL_CLASSES}: key {old} -> {new}")

    target = f"{CLASS_CONTRACTS}/{new}.json"
    text = registration["contract_bytes"].decode("utf-8")
    respelled = token.sub(new, text)
    try:
        after = json.loads(respelled)
    except ValueError as error:
        raise Refusal(f"respelling {registration['contract']} breaks its JSON ({error})") from None
    if after != _respelled_strings(json.loads(text), token, new) or after.get("class") != new:
        raise Refusal(f"respelling {registration['contract']} changes more than its {old} spellings")
    plan.moves.append((registration["contract"], target))
    plan.moved_bytes[registration["contract"]] = registration["contract_bytes"]
    plan.edit(ctx, target, respelled.encode("utf-8"))
    moved.append(f"git mv {registration['contract']} {target} ({text.count(old)} spelling(s) respelled)")

    queue = ctx.read(HEADER_QUEUE)
    if queue is not None:
        rows = queue.decode("utf-8").split("\n")
        keyed = [i for i, row in enumerate(rows) if row.split("\t", 1)[0] == old]
        clash = {tuple(row.split("\t")[:2]) for row in rows if row.split("\t", 1)[0] == new}
        for i in keyed:
            cells = rows[i].split("\t")
            if (new, cells[1] if len(cells) > 1 else "") in clash:
                raise Refusal(f"{HEADER_QUEUE} already queues {new} for {cells[1]}; the re-keyed row would "
                              "be a second one")
            rows[i] = new + token.sub(new, rows[i][len(old):])
        if keyed:
            plan.edit(ctx, HEADER_QUEUE, "\n".join(rows).encode("utf-8"))
            moved.append(f"{HEADER_QUEUE}: {len(keyed)} row(s) re-keyed to {new} (same sources, same RVAs)")
    registration = {k: v for k, v in registration.items() if k != "contract_bytes"}
    plan.registered = dict(registration, moved=moved)


# A registered placeholder's retail name is often spelled already: other units
# forward-declare `class FXNugget;`, keep views deriving their nuggets from it,
# and take `FXNugget *` parameters, while every row of the class itself sits
# under the placeholder. `--merge-existing` lets the rename take such a NEW:
# NEW may be spelled only as a type -- never as a scope or identifier of a row,
# pin or data row -- and no unit outside the rewrite may define a symbol the
# respelling creates (a second body of one retail function: a duplicate the
# byte gate never sees). Type use is no proof of identity, so every existing
# DEFINITION of NEW the rewrite leaves alone is compiled and must lay out only
# scalar leaves of OLD's contract, by offset, size, kind and name, within its
# sizeof; anything it cannot expand into scalars refuses (merge_definitions);
# its units and the consumers of the respelled symbols are verified with the
# rest. Only declarations and pointer/reference uses stay unexamined. The intended
# path leaves no such definition at all: every private view of NEW is put on the
# canonical header first. An inferred basis is allowed because the revert is
# exact: a registered rename's revert is the landing commit's diff reversed
# (plan_registered_revert), so NEW's pre-existing spellings, which the landing
# never touched, are exactly as they were, and the gates credit a revert only as
# that inverse (revert_inverse_problems).

def merge_problems(ctx, new, names):
    """Why the tree's existing spellings of `new` are more than a type, or []."""
    problems = []
    for symbol in names:
        if not symbol:
            continue
        if leading_identifier(symbol, new):
            problems.append(f"{new} is the identifier of {symbol}")
            continue
        try:
            spans = class_spans(symbol, new)
        except Unparsed:
            problems.append(f"cannot tokenize {symbol}, which spells {new}")
            continue
        for a, _b in spans:
            if symbol[a - 1:a] not in ("V", "U", "T") and symbol[a - 2:a] != "W4":
                problems.append(f"{new} scopes {symbol} (a row, pin or data row of its own): that is a fold, "
                                "not a merge")
                break
    return problems


def existing_definers(ctx, plan, new):
    """Units outside the rewrite that already define a symbol the respelling creates:
    by their cached objects, and by text (`NEW::method(` in a unit that spells NEW)."""
    created = {n for _o, n, _a in plan.renamed_rows + plan.renamed_data} | {n for _o, n, _a in plan.renamed_pins}
    found = []
    outside = lambda rel: rel not in plan.after and not is_generated(rel)  # noqa: E731
    if ctx.object_scan and created:
        sys.path.insert(0, str(ctx.root / "tools"))
        import build
        import reloc_ledger
        for rel in sorted(filter(outside, object_referencers(ctx, created))):
            obj = build.obj_path(ctx.path(rel))
            if not obj.exists():
                continue
            _sections, symbols = reloc_ledger.parse_coff(obj.read_bytes())
            defined = sorted({s["name"] for s in symbols.values() if s["name"] in created
                              and s.get("storage") == 2 and s.get("section", 0) > 0})
            found += [f"{rel} defines {name}" for name in defined]
    methods = {(scope_of(n) or "").split("::")[-1] for n in created} - {""}
    if methods:
        qualified = re.compile(r"\b%s\s*::\s*~?(%s)\s*\(" % (re.escape(new), "|".join(map(re.escape, sorted(methods)))))
        for rel in sorted(filter(outside, ctx.grep_files(new, word=True))):
            code = name_metric.strip((ctx.read(rel) or b"").decode("utf-8", errors="replace"))
            hit = qualified.search(code)
            if hit:
                found.append(f"{rel} spells {new}::{hit.group(1)}( (a second body of a respelled row, or a "
                             "qualified call this rule cannot tell from one)")
    return found


def spells_in_code(ctx, rel, word):
    """`rel` spells the type `word` in code: outside comments, string literals and
    #include paths. Prose ("FXNugget-family base ctor") never collides with a class."""
    text = (ctx.read(rel) or b"").decode("utf-8", errors="replace")
    # translation phase 2 first, as the compiler does: a backslash-newline joins lines before
    # comments and literals are recognised, so `"\<newline>"; class X {...}` is code, not a string
    text = re.sub(r"\\\r?\n", "", text)
    code = name_metric.strip("\n".join(line for line in text.splitlines() if not INCLUDE_LINE.match(line)))
    return re.search(r"(?<![A-Za-z0-9_])%s(?![A-Za-z0-9_])" % re.escape(word), code) is not None


def prepare_merge_sources(ctx, plan, prepared, old, new, registration):
    """Put prepared units into a --merge-existing plan: units whose private NEW view the
    caller already reshaped onto the canonical class, spelled as they read after the
    rename. They become part of the rewrite (merge_definitions and existing_definers skip
    plan.after) and are byte-verified with it; _batch_source_edits admits only tracked,
    clean, matched Code/ C++ sources. Each must name the class only through its canonical
    header: no OLD left, no body of NEW (a derived class is fine), the canonical header
    #included wherever its code spells NEW, and no second body (`NEW::m(`) of a row the
    rename respells. Returns the prepared paths."""
    token = ClassText(old)
    owners = {(r.get("name"), _rva(r.get("target_rva"))): r.get("source") for r in ctx.rows()}
    created = [((scope_of(renamed) or "").split("::")[-1].lstrip("~"), owners.get((before, at)))
               for before, renamed, at in plan.renamed_rows]
    header = posixpath.basename(registration["header"]).lower()
    for rel, data in sorted(prepared.items()):
        text = data.decode("utf-8", errors="surrogateescape")
        own = prepared_text_problems(rel, data)
        if own:
            raise Refusal(f"prepared {own[0]}")
        code = name_metric.strip(text)
        methods = sorted({m for m, source in created if m and source != rel})   # a row's own unit holds its body
        qualified = re.compile(r"\b%s\s*::\s*~?(%s)\s*\(" % (re.escape(new), "|".join(map(re.escape, methods)))) \
            if methods else None
        if token.search("\n".join(line for line in text.splitlines() if not INCLUDE_LINE.match(line))):
            raise Refusal(f"prepared {rel} still spells {old} (outside the kept header's #include path): "
                          "it reads as after the rename")
        if declares_type(code, new):
            raise Refusal(f"prepared {rel} defines its own {new}: a prepared unit includes "
                          f"{registration['header']} instead (a class derived from it is fine)")
        spells = re.search(r"\b%s\b" % re.escape(new), code)
        includes = [m.group(1) for m in re.finditer(r'(?m)^[ \t]*#[ \t]*include[ \t]*[<"]([^>"]+)[>"]', text)]
        if spells and not any(posixpath.basename(i.replace("\\", "/")).lower() == header for i in includes):
            raise Refusal(f"prepared {rel} spells {new} without #including its canonical header {registration['header']}")
        hit = qualified.search(code) if qualified else None
        if hit:
            raise Refusal(f"prepared {rel} spells {new}::{hit.group(1)}(, a second body of a row the rename respells")
    _batch_source_edits(ctx, plan, dict(prepared))
    return set(prepared)


LINE_MARKER = re.compile(r'(?m)^[ \t]*#[ \t]*line[ \t]+\d+[ \t]+"((?:[^"\\]|\\.)*)"')


def _marker_path(raw, root):
    """A `#line` marker's file as a repo-relative path: escapes undone, slashes forward,
    lower case (the preprocessor reports Wine's case-folded absolute path or the
    command line's relative one), `..` resolved, and an absolute path inside `root`
    made relative to it; any other absolute path stays absolute, so it never equals a
    repository file."""
    path = posixpath.normpath(raw.replace("\\\\", "\\").replace("\\", "/").lower())
    for prefix in (str(root), "z:" + str(root)):
        prefix = posixpath.normpath(prefix.replace("\\", "/").lower())
        if path.startswith(prefix + "/"):
            return path[len(prefix) + 1:]
    return path


def class_definitions(text, word, root=ROOT):
    """[(file, offset)] of every definition of class/struct/union `word` in the
    preprocessor's output, each attributed to the repo-relative file its `#line`
    marker names: heads carrying __declspec/__attribute__/alignas, macro expansions
    and anything an #if left in are all already plain text there."""
    head = re.compile(r"\b(?:class|struct|union)\s+(?:(?:__declspec|__attribute__|alignas)\s*\("
                      r"(?:[^()]|\([^()]*\))*\)\s*)*%s\s*(?::[^;{]*)?\{" % re.escape(word))
    markers = [(m.start(), _marker_path(m.group(1), root)) for m in LINE_MARKER.finditer(text)]
    out = []
    for match in head.finditer(text):
        files = [path for at, path in markers if at < match.start()]
        out.append((files[-1] if files else "", match.start()))
    return out


UPSTREAM = "refs/remotes/origin/master"         # never a local branch named origin/master
LINE_DIRECTIVE = re.compile(r"(?m)^[ \t\f\v]*(?:#|\?\?=|%:)[ \t\f\v]*(?:line\b|\d)")
UTF8_BOM = b"\xef\xbb\xbf"


def line_directive(text):
    """True when `text` holds a #line directive (`#line N`, `# N`) in any spelling the
    preprocessor could read as one: after a BOM, across backslash-newline splices, with
    a trigraph or digraph `#`, or a comment between `#` and `line` (a BOM anywhere is
    dropped). A directive inside a comment counts too: refusing it costs nothing."""
    text = text.replace("\ufeff", "").replace("\r\n", "\n").replace("\r", "\n")
    spliced = re.sub(r"\\[ \t]*\n", "", text)
    return any(LINE_DIRECTIVE.search(t) for t in
               (spliced, name_metric.strip(spliced), re.sub(r"/\*.*?\*/", " ", spliced, flags=re.S)))


def source_line_directive(data):
    """line_directive over a file's bytes as the compiler reads them: UTF-8 BOMs dropped
    wherever they sit, then 8-bit text. A UTF-16 or UTF-32 BOM, or any NUL byte, counts as
    a directive: the compiler would decode that file differently from this scan."""
    data = data.replace(UTF8_BOM, b"")
    if data.startswith((b"\xff\xfe", b"\xfe\xff")) or b"\0" in data:
        return True
    return line_directive(data.decode("latin-1"))


def prepared_text_problems(rel, data):
    """A prepared unit's own `#line` directive would make the preprocessor attribute its
    lines to any file it names, so the unit is refused before anything is written."""
    if source_line_directive(data):
        return [f"{rel} carries a #line directive of its own (or is not 8-bit text): its lines could be "
                "attributed to any file"]
    return []


def unit_flags(ctx, rel):
    """The flags the build itself gives `rel`: build.source_extra_flags, which reads the
    `// cl:` directive exactly as a compile does. Never parsed here."""
    sys.path.insert(0, str(ctx.root / "tools"))
    import build
    return list(build.source_extra_flags(ctx.path(rel)))


def prepared_baseline(ctx, registration, prepared):
    """What a prepared unit is proved against, fixed before anything is written: the merge
    base with origin/master. The registry, OLD's contract and every prepared unit must read
    there exactly as in the working tree (one edited in an outgoing commit or in the tree
    proves nothing), and each unit's flags are the build's flags for that copy."""
    git_trust.preflight(ctx.root, "--prepared", Refusal)
    code, out = _git_out(ctx.root, "merge-base", "HEAD", UPSTREAM)
    base = out.decode("ascii", "replace").strip() if not code else ""
    if not base:
        raise Refusal(f"--prepared: no merge base with {UPSTREAM}; a prepared unit is proved against "
                      "master's contract")
    for rel in [CANONICAL_CLASSES, registration["contract"], *prepared]:
        code, blob = _git_out(ctx.root, "show", f"{base}:{rel}")
        if code or blob != ctx.read(rel):
            raise Refusal(f"--prepared: {rel} differs from {UPSTREAM} ({base[:10]}); a prepared unit is proved "
                          "against master's registry, contract and unit, so land that change first")
    try:
        return {"base": base, "flags": {rel: unit_flags(ctx, rel) for rel in prepared}}
    except cl_flags.Refused as refused:
        raise Refusal(f"--prepared: the build refuses a prepared unit's flags on {UPSTREAM}: {refused}") from None


def contract_layout_problems(rel, contract, layout):
    """The compiled class of a prepared unit against the canonical contract, exactly:
    sizeof, bases, every field with its offset, name, size and i4-level kind (the vfptr
    as the contract's VPTR field), and every virtual slot."""
    sys.path.insert(0, str(ROOT / "tools"))
    import class_contract
    if not layout or layout.get("fwd") or layout.get("unparsed") is not None:
        return [f"{rel}'s object holds no single complete record of the class to compare with its contract"]
    want = {(f.get("offset"), f.get("name"), f.get("size"), f.get("kind")) for f in contract.get("fields", [])}
    if any(None in field for field in want):
        return [f"the contract has a field without an offset, name, size or kind: nothing to compare {rel} with"]
    got = {(o, n, s, class_contract.kind(t)) for o, n, t, s in layout.get("fields", [])}
    if layout.get("vfptr"):
        got.add((0, "__vfptr", 4, "VPTR"))
    slots = {str(k): (v.get("member") if isinstance(v, dict) else v) for k, v in (contract.get("vslots") or {}).items()}
    problems = []
    if layout.get("size") != contract.get("size"):
        problems.append(f"sizeof {layout.get('size')}, the contract {contract.get('size')}")
    if [b for b, _o in layout.get("bases", [])] != list(contract.get("bases") or []):
        problems.append(f"bases {[b for b, _o in layout.get('bases', [])]}, the contract {contract.get('bases')}")
    if got != want:
        problems.append(f"fields {sorted(got - want)[:2]} not in the contract, {sorted(want - got)[:2]} missing")
    if dict(layout.get("vslots") or {}) != slots:
        problems.append(f"virtual slots {layout.get('vslots')}, the contract {slots}")
    return [f"{rel}'s class is not its contract: " + "; ".join(problems)] if problems else []


def master_contract(ctx, registered):
    """(contract, problems): OLD's contract as origin/master's merge base holds it, respelled
    to NEW exactly as the rename writes it; the working copy is never read as proof, and the
    NEW.json the transaction wrote must be that respelling byte for byte."""
    old, new = registered["old"], registered["new"]
    base = (registered.get("baseline") or {}).get("base")
    code, data = _git_out(ctx.root, "show", f"{base}:{registered['contract']}") if base else (1, b"")
    try:
        text = class_token_re(old).sub(new, data.decode("utf-8")) if not code else None
        contract = json.loads(text) if text is not None else None
    except ValueError:
        contract = None
    if contract is None:
        return None, [f"{registered['contract']} cannot be read at {UPSTREAM}'s merge base: the prepared units' "
                      f"{new} has no contract to equal"]
    if ctx.read(f"{CLASS_CONTRACTS}/{new}.json") != text.encode("utf-8"):
        return None, [f"{CLASS_CONTRACTS}/{new}.json is not {UPSTREAM}'s {registered['contract']} respelled: "
                      "the contract changed in the transaction"]
    return contract, []


def prepared_attribution_problems(ctx, plan):
    """After ./build.sh, each prepared unit must compile the canonical class and nothing else:
      - its own text has no #line (prepared_text_problems), and the build gives it exactly
        the flags it gave master's copy (unit_flags, frozen by prepared_baseline);
      - the compiler's own include list (/showIncludes) names the canonical header, and no
        file it includes carries a #line directive, so every `#line` marker in the
        preprocessed output is the compiler's own;
      - no definition of NEW comes from any other file than the canonical header, and no
        definition of OLD remains;
      - its compiled type record of NEW (view_layouts, CodeView) equals master's contract
        (master_contract) exactly (contract_layout_problems).
    Anything it cannot read refuses."""
    registered = plan.registered
    old, new, header = registered["old"], registered["new"], registered["header"]
    untrusted = git_trust.untrusted_history(ctx.root)
    if untrusted:
        return [f"local git state rewrites history ({'; '.join(untrusted)}): master's contract cannot be read"]
    contract, problems = master_contract(ctx, registered)
    if contract is None:
        return problems
    frozen = (registered.get("baseline") or {}).get("flags") or {}
    for rel in registered.get("prepared") or ():
        own = ctx.read(rel)
        if own is None:
            problems.append(f"{rel} cannot be read to prove its {new}")
            continue
        problems += prepared_text_problems(rel, own)
        try:
            flags = unit_flags(ctx, rel)
        except cl_flags.Refused as refused:
            problems.append(f"{rel}: the build refuses its flags: {refused}")
            continue
        if rel not in frozen or flags != frozen[rel]:
            problems.append(f"{rel} compiles with {flags}, {UPSTREAM}'s copy with {frozen.get(rel)}: a prepared "
                            "unit keeps master's flags")
            continue
        includes = []
        text, why = preprocess_unit(ctx, rel, includes)
        if text is None:
            problems.append(f"{rel} cannot be preprocessed to prove its {new}: {why}")
            continue
        seen, marked = [], []
        for host in includes:
            path = Path(host)
            included = os.path.relpath(path, ctx.root).replace(os.sep, "/")
            if not path.is_file() or source_line_directive(path.read_bytes()):
                marked.append(included)
            seen.append(included)
        if marked:
            problems.append(f"{rel} includes {marked[0]}, which carries a #line directive (or cannot be read): "
                            "its lines could be attributed to any file")
            continue
        if header not in seen:
            problems.append(f"{rel} never includes {header} (the compiler's /showIncludes list)")
            continue
        if class_definitions(text, old, ctx.root):
            problems.append(f"{rel} still defines {old} once preprocessed")
        others = sorted({f or "<no #line>" for f, _at in class_definitions(text, new, ctx.root)
                         if f != header.lower()})
        if others:
            problems.append(f"{rel} defines its own {new} in {', '.join(others[:2])}, not only through {header}")
            continue
        problems += contract_layout_problems(rel, contract, view_layouts(ctx, rel).get(new))
    return problems


def view_layouts(ctx, unit):
    """{class: layout} the compiler reports for ledger source `unit` (tools/class_layouts.py:
    its own flags plus -Z7, read from CodeView)."""
    sys.path.insert(0, str(ctx.root / "tools"))
    import class_layouts
    return class_layouts.compile_layouts(unit)


class Unknown(Exception):
    """A layout the merge cannot read completely: it refuses rather than guesses."""


def scalar_kinds():
    """The leaf kinds a merge compares: tools/class_contract.py's primitive kinds, a
    pointer and the vfptr. Anything else (an array, an aggregate it cannot expand, an
    unknown kind) is compared by nothing but a type-name string, so it is Unknown."""
    sys.path.insert(0, str(ROOT / "tools"))
    import class_contract
    return set(class_contract.PRIMK.values()) | {"P", "VPTR"}


def contract_leaves(contract):
    """{(offset, size, kind, name)} of a frozen contract's fields, member aggregates
    expanded (`member.field`); Unknown for anything it cannot compare."""
    if contract.get("bases"):
        raise Unknown(f"the contract has bases ({', '.join(contract['bases'])}): base subobject placement is not "
                      "recorded in a contract, so a merge cannot compare it")
    scalars, out = scalar_kinds(), set()
    for f in contract.get("fields", []):
        parts = f.get("members") or [None]
        for m in parts:
            leaf = f if m is None else m
            if any(leaf.get(k) is None for k in ("offset", "size", "kind", "name")):
                raise Unknown(f"the contract's field {f.get('name')!r} lacks an offset, size, kind or name")
            if leaf["kind"] not in scalars:
                raise Unknown(f"the contract's field {f.get('name')!r} is {leaf['kind']}, not a scalar a merge "
                              "can compare (an array, an unexpanded aggregate or a bitfield)")
            out.add((f["offset"] + (m["offset"] if m else 0), leaf["size"], leaf["kind"],
                     f["name"] + ("." + m["name"] if m else "")))
    return out


def view_leaves(layout, every, kind_of, base=0, prefix="", depth=0):
    """[(offset, size, kind, name)] of a compiled view: its vfptr, every named member (none
    is padding), member aggregates expanded the way contracts expand them. Unknown for a
    forward-only or unparsed layout, any base (virtual or not), a bitfield, an array, and a
    member aggregate it cannot expand completely (forward-only, polymorphic, based, of
    another size, or nested too deep): no member is ever compared by its type name."""
    if not layout or layout.get("fwd") or not layout.get("size") or layout.get("unparsed") is not None:
        raise Unknown(f"{prefix or 'the view'} has no complete layout in the compiled type stream")
    if layout.get("bases"):
        raise Unknown(f"{prefix or 'the view'} has bases ({', '.join(b for b, _o in layout['bases'])}): "
                      "a merge does not compare base subobjects")
    scalars = scalar_kinds()
    out = [(base, 4, "VPTR", prefix + "__vfptr")] if layout.get("vfptr") else []
    for offset, name, type_name, size in layout.get("fields", []):
        if type_name == "bitfield" or not size:
            raise Unknown(f"{prefix}{name} is a bitfield or has no size: its bits are not read")
        kind = kind_of(type_name)
        if kind in scalars:
            out.append((base + offset, size, kind, prefix + name))
            continue
        member = every.get(type_name)
        if kind == "A" or member is None or member.get("fwd") or member.get("size") != size \
                or member.get("vfptr") or member.get("bases") or depth >= 6:
            raise Unknown(f"{prefix}{name} ({type_name}) is not a scalar and cannot be expanded into scalars "
                          "from the compiled type stream")
        out += view_leaves(member, every, kind_of, base + offset, prefix + name + ".", depth + 1)
    return out


def merge_definitions(ctx, plan, new, registration, max_files):
    """(problems, units) for the definitions of `new` the rewrite leaves untouched: each is
    compiled (view_layouts) and every leaf it lays out (view_leaves: vfptr, every named
    member, aggregates expanded) must be a leaf of OLD's contract with the same offset,
    size, kind and name; the view has a vfptr exactly when the contract does, and fits its
    sizeof. Anything either side cannot state completely (a forward-only layout, a base,
    a bitfield, a contract field without a kind) refuses. `units` are the ledger sources
    that compile one, which the plan then verifies with the rest."""
    sys.path.insert(0, str(ctx.root / "tools"))
    import class_contract
    contract = json.loads(registration["contract_bytes"].decode("utf-8"))
    try:
        want = contract_leaves(contract)
    except Unknown as why:
        return [f"{registration['contract']}: {why}"], set()
    sizeof = contract.get("size")
    if not isinstance(sizeof, int) or sizeof <= 0:
        return [f"{registration['contract']} records no sizeof to compare"], set()
    has_vptr = any(kind == "VPTR" for _o, _s, kind, _n in want)
    problems, units = [], set()
    for rel in sorted(ctx.grep_files(new, word=True)):
        if rel in plan.after:
            continue
        if not declares_type(name_metric.strip((ctx.read(rel) or b"").decode("utf-8", errors="replace")), new):
            continue
        compiled = [rel] if rel in ctx.ledger_sources() else \
            sorted(includers(ctx, [rel], max_files) & ctx.ledger_sources())
        if not compiled:
            problems.append(f"{rel} defines {new}, and no ledger source compiles it to compare")
            continue
        units |= set(compiled)
        every = view_layouts(ctx, compiled[0])
        layout = every.get(new)
        if layout is None:
            problems.append(f"{rel}: compiling {compiled[0]} reports no layout of {new}")
            continue
        try:
            leaves = view_leaves(layout, every, class_contract.kind)
        except Unknown as why:
            problems.append(f"{rel}: {new}: {why}")
            continue
        by_offset = {o: (s, k, n) for o, s, k, n in want}
        for offset, size, kind, name in leaves:
            if (offset, size, kind, name) in want:
                continue
            if offset not in by_offset:
                problems.append(f"{rel}: {new}::{name} ({size} B {kind}, +0x{offset:X}) is a field "
                                f"{registration['old']}'s contract does not have")
            else:
                s, k, n = by_offset[offset]
                problems.append(f"{rel}: {new}::{name} at +0x{offset:X} is {size} B {kind}; the contract has "
                                f"{n}, {s} B {k}")
        if has_vptr != bool(layout.get("vfptr")):
            problems.append(f"{rel}: its {new} {'lacks' if has_vptr else 'has'} the vfptr the contract "
                            f"{'has' if has_vptr else 'lacks'}")
        if layout.get("size", 0) > sizeof:
            problems.append(f"{rel}: its {new} is {layout.get('size')} B, over the contract's {sizeof}")
    return problems, units


def registered_object_problems(ctx, plan):
    """After ./build.sh: no rebuilt unit's object names a symbol the renamed registered
    class still scopes or types under its old spelling. A revert checks the landed row
    names it took back (`stale`) instead: NEW's spellings the landing never touched may
    rightly stay in objects."""
    sys.path.insert(0, str(ctx.root / "tools"))
    import build
    import reloc_ledger
    frag, problems = type_fragment_re(plan.registered["old"]), []
    stale_names = set(plan.registered.get("stale") or ())
    for rel in plan.verify:
        obj = build.obj_path(ctx.path(rel))
        if not obj.exists():
            problems.append(f"{rel} has no object after the build")
            continue
        _sections, symbols = reloc_ledger.parse_coff(obj.read_bytes())
        stale = sorted({s["name"] for s in symbols.values()
                        if (s["name"] in stale_names if "stale" in plan.registered else frag.search(s["name"]))})
        if stale:
            problems.append(f"{rel}'s object still names {stale[0]}" + (f" (+{len(stale) - 1} more)" if len(stale) > 1 else ""))
    return problems


def plan_class(ctx, name, new, basis=None, evidence="", *, max_files=25, fold=False, prepared=None,
               access=None, merge=False):
    """Plan respelling one class/struct/union/enum type token everywhere: every
    mangled name it scopes or types (functions.csv names and notes, pins, data
    rows), every source, header and shim view that spells it, and the units
    whose objects reference a renamed symbol. The rewrite is the whole token,
    so it refuses when the word also names a function or datum. `fold` folds
    a placeholder into the name its retail vftable already carries
    (plan_fold), with no basis. `merge` lets a registered placeholder take a
    NEW the tree already spells as a type only (merge_problems)."""
    if fold:
        if merge:
            raise Refusal("--merge-existing goes with class --name OLD --new NEW, not --fold")
        if basis is not None:
            raise Refusal("class --fold invents no name and takes no --basis: retail's vftable is the evidence")
        return plan_fold(ctx, name, new, evidence=evidence or "", max_files=max_files, prepared=prepared,
                         access=access)
    if prepared and not merge:
        raise Refusal("--prepared goes with class --fold into a nested class, or with --merge-existing")
    if access is not None:
        raise Refusal("--access goes with class --fold (or function --virtual)")
    if basis is None:
        raise Refusal("--basis is required")
    old = name or ""
    if not IDENT.fullmatch(old):
        raise Refusal(f"{old!r} is not a type identifier")
    check_new_identifier(new or "", "class", basis)
    if new == old:
        raise Refusal("the new name is the old name")
    reason = class_protected(ctx, old)
    if reason:
        raise Refusal(f"canonical name: {reason}")
    registration = class_registration(ctx, old, new, basis)
    if merge and not registration:
        raise Refusal(f"--merge-existing moves a registered class's key; {old} is not registered "
                      f"in {CANONICAL_CLASSES}")
    if registration:
        which = check_registered_basis(ctx, registration["header"], basis, evidence, old, new)
        if which == RESTORED:
            return plan_registered_revert(ctx, old, new, evidence, registration, max_files)
    else:
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
    # source could spell it -- or, merging, spelled only as a type nothing owns.
    # An #include path is a file name, not a spelling of the type (a revert's
    # placeholder still names its kept header), and prose in a comment or string
    # declares nothing: only code can collide.
    taken = [rel for rel in ctx.grep_files(new, word=True) if spells_in_code(ctx, rel, new)]
    new_frag = type_fragment_re(new)
    if merge:
        problems = merge_problems(ctx, new, names)
        if problems:
            raise Refusal(f"--merge-existing: {problems[0]}")
    elif taken:
        raise Refusal(f"{new} already appears in {', '.join(taken[:3])}"
                      + (" (a registered placeholder may take a NEW spelled only as a type: --merge-existing)"
                         if registration else ""))
    else:
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
        if data is not None:
            text = data.decode("utf-8", errors="surrogateescape")
            if token.search(text):
                texts[rel] = text
    # Cheap text/protection failures should not start an object scan.
    refuse_vendored(ctx, set(texts), f"renaming the type {old}")
    if len(texts) > max_files:
        raise Refusal(f"{len(texts)} files spell {old} (over --max-files {max_files}; text scope alone)")
    declarers = sorted(rel for rel, text in texts.items() if declares_type(name_metric.strip(text), old))
    for text in texts.values():
        enclosing |= {outer for name, _s, _e, outer in enclosing_types(name_metric.strip(text)) if name == old}
    if len(enclosing) > 1:
        raise Refusal(f"{old} names types in {len(enclosing)} different scopes "
                      f"({', '.join(sorted(e or '<global>' for e in enclosing))}); a token rewrite would rename "
                      "them all -- phase 1 renames one type only when its spelling is unique")
    if not scoped and not declarers:
        raise Refusal(f"no class, struct, union or enum named {old} (no definition, no ledger name)")
    by_object = object_referencers(ctx, set(scoped), word=old) if ctx.object_scan and scoped else set()
    touched = set(texts) | by_object
    refuse_vendored(ctx, touched | set(declarers), f"renaming the type {old}")
    generated = sorted(p for p in touched if is_generated(p))
    if generated:
        raise Refusal(f"generated source(s) spell {old}: {', '.join(generated[:5])}; "
                      "the rename would leave them stale and they are never edited")
    if len(touched) > max_files:
        print(f"rename: class scope for {old}: {len(texts)} spelling file(s), "
              f"{len(by_object)} object consumer(s), {len(touched)} total; limit {max_files}", flush=True)
        raise Refusal(f"{len(touched)} files spell {old} (over --max-files {max_files}; "
                      f"{len(texts)} text, {len(by_object)} object consumers)")

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
    merge_verify = set()
    if prepared:
        merge_verify |= prepare_merge_sources(ctx, plan, prepared, old, new, registration)
    if merge:
        definers = existing_definers(ctx, plan, new)
        if definers:
            raise Refusal(f"--merge-existing: {definers[0]}" + (f" (+{len(definers) - 1} more)" if len(definers) > 1
                                                                 else "") + "; reconcile that unit first")
        mismatched, merge_verify = merge_definitions(ctx, plan, new, registration, max_files)
        if mismatched:
            raise Refusal(f"--merge-existing: an existing definition of {new} is not {old}'s contract: "
                          + "; ".join(mismatched[:4]) + (f" (+{len(mismatched) - 4} more)" if len(mismatched) > 4
                                                         else ""))
        created = {n for _o, n, _a in plan.renamed_rows + plan.renamed_data}
        merge_verify |= object_referencers(ctx, created) if ctx.object_scan and created else set()
    if registration:
        move_registration(ctx, plan, registration)
        if merge:
            plan.registered["moved"].append(f"merged into {new}'s existing type spellings in "
                                            f"{len(set(taken) - set(plan.after))} untouched file(s)")
    verify = {rel for rel in plan.source_counts if rel in ctx.ledger_sources()}
    renamed = {o for o, _, _ in plan.renamed_rows}
    verify |= {r["source"] for r in ctx.rows() if r["name"] in renamed}
    verify |= {r["source"] for r in ctx.rows() if (r["name"], _rva(r.get("target_rva"))) in set(plan.notes_rows)}
    renamed_data = {o for o, _, _ in plan.renamed_data}
    verify |= {d.get("source", "") for d in ctx.dicts(DATA_ROWS) if d.get("name") in renamed_data}
    if headers:
        verify |= includers(ctx, headers, max_files)
    verify |= merge_verify                       # NEW's existing definers and the consumers of its symbols
    plan.verify = sorted(v for v in verify if v and not is_generated(v) and v in ctx.ledger_sources())
    if len(plan.verify) > max_files:
        raise Refusal(f"{len(plan.verify)} sources to verify (over --max-files {max_files})")
    if prepared:
        # the prepared units' class is proved after the build, against master's contract and flags
        plan.registered["prepared"] = sorted(prepared)
        plan.registered["baseline"] = prepared_baseline(ctx, registration, sorted(prepared))
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
    edited = set(plan.after) | {o for o, _n in plan.moves} | {"reverse/re_attempts.log"}
    plan.mentions = sorted(set(ctx.grep_files(old, word=True, roots=("docs", "reverse"))) - edited)
    stems = sorted(rel for rel in plan.source_counts if old in Path(rel).stem)
    for rel in stems:
        plan.warnings.append(f"{rel}: its file name spells {old} (not renamed; use the file kind)")
    return plan


# ---------------------------------------------------------------- class --fold
#
# One retail class sometimes carries two placeholder names: one seat rowed its
# constructor as `??0BfmeModuleDataSnapshotBase`, another its destructor,
# deleting destructor and vftable as `Rva001164B6`. A TU merge then needs one
# spelling, and `class` cannot give it: the new token already names rows (a
# collision) and is itself a placeholder. `class --fold OLD --into NEW`
# respells the placeholder OLD as NEW everywhere, exactly as `class` would,
# when retail proves the two names are one class:
#
#   * a constructor, destructor or deleting destructor row of OLD installs a
#     retail vftable T as its own: a destructor's or deleting destructor's
#     FIRST +0 store (MSVC stores the class's own table before member and
#     base destructors restore theirs), or a constructor's +0 stores when they
#     all install T (a constructor that also installs a base's or a member's
#     table proves nothing and must merely include T), or a constructor's
#     last +0 store when every vftable store in it is through a register
#     that provably holds this + d (this_stores: inlined base constructors
#     store first, and no store into another object is among them);
#     every other special member row of OLD or NEW agrees (none owns another
#     table); a store's displacement is read from this, not from its
#     instruction (`lea edi,[esi+4]; mov [edi],S` is a +4 store);
#   * T's `??_7X@@6B@` names (data_rows.csv, and the data_ledger.csv names the
#     matched rows' DIR32 relocations bind there) name NEW, and no class but
#     OLD and NEW;
#   * T is no ICF fold of distinct classes' vftables (0x007CEFA0 is one, under
#     three constructors): no special member row of a third class installs T
#     as its own; the slot layout agrees: every deleting destructor of OLD and
#     NEW sits in a slot of T and no slot holds a third class's; and OLD and
#     NEW never both have a row of one special-member kind (one class has one
#     destructor; two constructor rows could be overloads or two classes, so
#     that stays refused in this narrow mode).
#   * a class with several bases has one more table per base subobject, and
#     its deleting destructor reaches the later ones through an adjustor thunk
#     (`??_EX@@WM@AEPAXI@Z`: `this -= 12`, then the deleting destructor). Such
#     a thunk sits in a slot of the class's own table for the subobject at
#     that displacement: the table an own-table special member installs there
#     itself (a destructor's first store at `+disp`, a constructor's last,
#     after any inlined base constructor's), never at `+0` of T. The thunk is
#     a member kind of its own (keyed by its displacement), and the secondary
#     table gets T's ICF and slot checks: no third class installs it as its
#     own, and no slot holds a third class's deleting destructor.
#   * a destructor-only OLD (every row of OLD is a destructor or deleting
#     destructor, and none of them stores any vftable: MSVC drops the vptr
#     store of an empty-bodied destructor) owns no table, so T comes from
#     NEW's rows by the same own-table rules; OLD's deleting destructors must
#     then sit in slots of T (a class's table holds the class's own deleting
#     destructor), and every destructor of OLD must be called by one of them
#     (the deleting destructor calls its class's complete destructor). Each
#     body is then NEW's member: T is NEW's own table. A third class whose
#     row also installs T as its own (overloaded constructors rowed under two
#     placeholders, or an ICF fold of identical tables) does not refuse this
#     route, because the slot's body is NEW's either way (ICF shares it); it
#     is recorded in the evidence and is not folded. A name on T for a class
#     that installs no T of its own still refuses.
#   * whenever only destructors tie OLD to T (this route, the next one, or a
#     destructor's first store, which an inlined base destructor's restore
#     can supply; not when a constructor of OLD installs T as its own), the
#     slot must be T's alone: a deleting destructor of OLD that another
#     retail table also holds (outside T's subobject tables) is one body
#     retail ICF-folded for distinct classes, and refuses. 0x00537E60
#     (??_GRva00535776, whose destructor 0x00535776 stores 0x00C68DD8 first)
#     is slot 0 of the Profile, StrategicStats and RealTimeStats preferences
#     tables; the fold passed into each of the three before this check.
#   * a destructor family whose stores an inlined base destructor explains
#     takes the same route. When the base destructor is inline, the class's
#     destructor stores its own tables and then the base's, and MSVC drops
#     the stores the base's overwrite: the first +0 store is the base's own
#     table, so the own-table rule would name the base. Such an OLD is
#     accepted when every table one of its rows installs at +d is either the
#     table every constructor row of NEW installs last at +d (NEW's own, at a
#     displacement the base does not restore) or the table a base
#     constructor row installs last at +d, where every constructor row of NEW
#     calls (E8) that base constructor; at least one store must be the
#     base's. 0x004B96CC (DamageModule's destructor, placeholder Rva004B96CC):
#     +0x10 0x00BE2B78, then BehaviorModule's 0x00BEEA7C at +0 and 0x00BEE9C0
#     at +0x0C (both installed last by ??0BehaviorModule 0x00253330, which the
#     DamageModule constructor 0x004B9704 calls), then the tail jump.
#   * a NEW rowed only through virtual methods (no constructor, destructor or
#     deleting destructor row, so no object binds T under NEW's name: a
#     multiply-derived OLD's T is `??_7OLD@@6BBase@@@`) is tied to OLD's own
#     table T by its slots instead of a `??_7NEW` name, when nothing but OLD
#     names T, every rowed virtual method of NEW sits in a slot of T and in no
#     other retail table (a base class's own table would hold its virtuals
#     too; an ICF-folded body would sit in both), and no slot of T holds a
#     third class's member (an inherited slot this route does not judge).
#     0x00CF1648: ctor 0x00740FD9 (Rva0074104C) installs it last, its slots
#     are ??_G 0x007410D0, W3DAptComponentColorPicker::Init and ::Render, and
#     the base table 0x00CF1630 holds __purecall there.
#
# T's names come from data_rows.csv, data_ledger.csv and, because the ledger
# is a tool-written cache that lags new rows, the DIR32 bindings of OLD's and
# NEW's own special-member rows read from their compiled objects (the
# derivation tools/data_ledger.py makes for every matched row).
#
# OLD must be a placeholder (tools/name_metric.py): a readable name never
# folds, into a placeholder (docs/naming.md: only a `restored` revert puts a
# placeholder back) or into another readable name (that is a naming decision).
# NEW may be readable; it keeps whatever basis it has. No name is invented,
# so no name_basis.csv record is written (records scoped by OLD are carried,
# as by `class`); each renamed row is tombstoned `Renamed to <new> by
# tools/rename.py (fold: retail vftable 0x...)`. A pin that the respelling
# makes a row's own name at the same address (the redundant alias the second
# name needed) is dropped; one that would give a name a second address is
# refused. The byte gate, pin_admission and pin_consistency --check
# (commit_checks) decide as for every rename.

# A class as MSVC decorates its scope: `Icon@Impl@Page@UI@` (innermost name
# first, each ended by `@`), then the qualified name's own terminating `@`.
CLASS_SCOPE = r"((?:[A-Za-z_]\w*@)+)@"
SPECIAL_MEMBER = re.compile(r"\?\?(0|1|_G|_E)" + CLASS_SCOPE)
SPECIAL_ROLE = {"0": "constructor", "1": "destructor", "_G": "deleting destructor", "_E": "deleting destructor"}
GLOBAL_VTABLE = re.compile(r"\?\?_7" + CLASS_SCOPE + "6B")
# A deleting destructor's this-adjustor thunk: the class scope, then the access
# code of a virtual adjustor thunk (G/H private, O/P protected, W/X public) and
# the encoded displacement (a digit d is d+1; else hex digits A..P ending in `@`).
ADJUSTOR_THUNK = re.compile(r"\?\?(?:_G|_E)(?:[A-Za-z_]\w*@)+@[GHOPWX]([0-9]|[A-P]+@)")


def scope_class(scope):
    """The C++ spelling of a decorated class scope: `Icon@Impl@Page@UI@` is
    `UI::Page::Impl::Icon`."""
    return "::".join(reversed(scope.rstrip("@").split("@")))


def class_scope(cls):
    """The decorated scope fragments of class `cls`, without the terminating
    `@`s: `UI::Page::Impl::Icon` is `Icon@Impl@Page@UI`."""
    return "@".join(reversed(cls.split("::")))


def nested_respelling_check(old, new):
    """check(symbol, respelled) for respelling the global class `old` as the
    nested class `new` (`A::B::C`) in mangled names. MSVC's name table holds
    each name fragment once, in order, and a later repeat is a back-reference
    digit: the nested scope adds len(parts) - 1 names, so this refuses a
    symbol that carries any name back-reference (it would point elsewhere
    after the respelling) and a respelling that spells one of NEW's names
    twice (cl would compress the repeat). Argument-type back-references index
    the argument list, not the name table, and stay valid."""
    parts = new.split("::")

    def check(symbol, respelled):
        refs = []
        try:
            fragments(symbol, refs=refs)
            spans = fragments(respelled)
        except Unparsed as error:
            raise Refusal(f"cannot read {symbol} to respell {old} as the nested {new}: {error}") from None
        if refs:
            raise Refusal(f"{symbol} carries a name back-reference ({', '.join(map(str, refs))}): the nested "
                          f"{new} adds {len(parts) - 1} name(s) to MSVC's name table, so it would no longer "
                          "point at the name it does now")
        names = [respelled[a:b] for a, b in spans]
        for part in parts:
            if names.count(part) > 1:
                raise Refusal(f"{symbol} would become {respelled}, which spells {part} twice: cl encodes the "
                              "repeat as a name back-reference, so that is not the name it emits")
    return check


def adjustor_of(name):
    """The this-displacement a deleting destructor's adjustor thunk subtracts
    (`??_EX@@WM@AEPAXI@Z`: 12), or None for any other name."""
    match = ADJUSTOR_THUNK.match(name or "")
    if not match:
        return None
    code = match.group(1)
    if code[-1] != "@":
        return int(code) + 1
    return int("".join("0123456789ABCDEF"[ord(c) - ord("A")] for c in code[:-1]), 16)


def _all_installs(ctx, tables):
    """sorted [(store rva, table, this offset)] of every retail vftable install."""
    key = "_all_installs"
    if key not in ctx._cache:
        ctx._cache[key] = sorted((store, table, disp) for table, (_slots, installs) in tables.items()
                                 for store, disp in installs.items())
    return ctx._cache[key]


# retail_vtables reads each install's displacement from its own instruction,
# so `lea edi,[esi+4]; mov dword ptr [edi],T` reads as a +0 store of T. A
# class with a second base whose subobject address sits in a register stores
# its secondary table that way (PlanRetreatsPhaseBehavior::Impl, 0x005770F7:
# `lea edi,[esi+4]` ... `mov [esi],0xC6E8F8; mov [edi],0xC6E8EC`). The special
# member's own body is therefore read once more, tracking which registers hold
# `this + d` (ecx at entry; mov and lea copy it, a call clobbers eax/ecx/edx,
# any other write ends it, and a branch join keeps only what every way in
# agrees on): a store through such a register is at `d + k`.
_SUBREGISTER = {}


def _full_register(reg):
    """The 32-bit register a capstone x86 register id is part of."""
    if not _SUBREGISTER:
        from capstone import x86
        for full, parts in (("EAX", "AL AH AX"), ("ECX", "CL CH CX"), ("EDX", "DL DH DX"),
                            ("EBX", "BL BH BX"), ("ESI", "SI SIL"), ("EDI", "DI DIL"), ("EBP", "BP BPL"),
                            ("ESP", "SP SPL")):
            target = getattr(x86, f"X86_REG_{full}")
            _SUBREGISTER[target] = target
            for part in parts.split():
                if hasattr(x86, f"X86_REG_{part}"):
                    _SUBREGISTER[getattr(x86, f"X86_REG_{part}")] = target
    return _SUBREGISTER.get(reg, reg)


def this_displacements(ctx, row):
    """{store rva: displacement from this} for every `mov dword ptr
    [reg+k], imm32` in special member `row`'s retail body whose base register
    provably holds `this + d` there (see above); a store through any other
    register is absent (its install keeps the displacement retail_vtables
    read). Empty for a scratch root, which has no retail image of its own."""
    if ctx.root != ROOT.resolve():
        return {}
    start = _rva(row.get("target_rva"))
    try:
        size = int(row.get("target_size") or 0)
    except (TypeError, ValueError):
        return {}
    key = ("_this_displacements", start, size)
    if key in ctx._cache:
        return ctx._cache[key]
    import build
    image, sections = build.exe_image()
    offset = build.rva_to_file_offset(sections, start)
    # `mov eax,<FuncInfo>; call __EH_prolog` opens an EH frame and clobbers
    # eax only: ecx still holds this after it (the ledger's one row, eh_prolog_rva).
    eh_prolog = eh_prolog_rva(ctx)
    ctx._cache[key] = this_stores(bytes(image[offset:offset + size]), start, () if eh_prolog is None else (eh_prolog,))
    return ctx._cache[key]


def this_stores(body, start, eh_prolog=()):
    """{store address: displacement from this} for every `mov dword ptr
    [reg+k], imm32` in the thiscall body `body` (loaded at `start`) whose base
    register provably holds `this + d` (see above); `eh_prolog` holds the
    addresses of the EH frame helper, whose call clobbers eax only."""
    import capstone
    from capstone import x86
    size = len(body)
    md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
    md.detail = True
    code = list(md.disasm(body, start))
    jumps = {x86.X86_INS_JMP} | {getattr(x86, n) for n in dir(x86) if n.startswith("X86_INS_J") and n != "X86_INS_JMP"}
    incoming = collections.defaultdict(list)          # target -> [forward branch sources]
    loops = set()                                       # targets of backward branches
    for ins in code:
        if ins.id in jumps and ins.operands and ins.operands[0].type == x86.X86_OP_IMM:
            target = ins.operands[0].imm
            if start <= target < start + size:
                (incoming[target].append(ins.address) if target > ins.address else loops.add(target))
    # The null-guarded cast `this ? this + d : 0` reads `mov r,this; neg r;
    # lea s,[this+d]; sbb r,r; and r,s`: neg sets CF when this is nonzero, so
    # sbb leaves a mask (cf_this: the last flag write was that neg; masks:
    # registers holding the mask) and the and leaves this + d.
    out, alias, snapshots, falls = {}, {x86.X86_REG_ECX: 0}, {}, True
    masks, cf_this = set(), False
    for ins in code:
        if ins.address in loops:
            alias, masks, cf_this = {}, set(), False
        elif ins.address in incoming:
            ways = [snapshots.get(src, {}) for src in incoming[ins.address]] + ([alias] if falls else [])
            alias = {r: d for r, d in ways[0].items() if all(w.get(r) == d for w in ways[1:])}
            masks, cf_this = set(), False
        ops = ins.operands
        written = {_full_register(reg) for reg in ins.regs_access()[1]}
        flags = x86.X86_REG_EFLAGS in written
        regs = len(ops) == 2 and ops[0].type == ops[1].type == x86.X86_OP_REG and ops[0].size == 4
        if ins.id == x86.X86_INS_NEG and len(ops) == 1 and ops[0].type == x86.X86_OP_REG and ops[0].size == 4:
            reg = _full_register(ops[0].reg)
            cf_this = alias.get(reg) == 0
            alias.pop(reg, None)
            masks.discard(reg)
            continue
        if ins.id == x86.X86_INS_SBB and regs and _full_register(ops[0].reg) == _full_register(ops[1].reg):
            reg = _full_register(ops[0].reg)
            alias.pop(reg, None)
            (masks.add if cf_this else masks.discard)(reg)
            cf_this = False
            continue
        if ins.id == x86.X86_INS_AND and regs:
            dst, src = _full_register(ops[0].reg), _full_register(ops[1].reg)
            cf_this = False
            if dst in masks and src in alias:
                alias[dst] = alias[src]
                masks.discard(dst)
                continue
            if src in masks and dst in alias:
                continue
        if flags:
            cf_this = False
        masks -= written
        falls = ins.id not in (x86.X86_INS_JMP, x86.X86_INS_RET)
        if ins.id in jumps:
            snapshots[ins.address] = dict(alias)
        if ins.id == x86.X86_INS_MOV and len(ops) == 2 and ops[0].type == x86.X86_OP_MEM:
            mem = ops[0].mem
            if (ops[1].type == x86.X86_OP_IMM and ops[0].size == 4 and not mem.index and not mem.segment
                    and mem.base in alias):
                out[ins.address] = alias[mem.base] + mem.disp
            continue
        if ins.id == x86.X86_INS_MOV and len(ops) == 2 and ops[0].type == ops[1].type == x86.X86_OP_REG:
            dst, src = _full_register(ops[0].reg), _full_register(ops[1].reg)
            if ops[0].size == 4 and src in alias:
                alias[dst] = alias[src]
            else:
                alias.pop(dst, None)
            continue
        if ins.id == x86.X86_INS_LEA and len(ops) == 2:
            dst, mem = _full_register(ops[0].reg), ops[1].mem
            if not mem.index and not mem.segment and mem.base in alias:
                alias[dst] = alias[mem.base] + mem.disp
            else:
                alias.pop(dst, None)
            continue
        if ins.id == x86.X86_INS_CALL:
            helper = ops and ops[0].type == x86.X86_OP_IMM and ops[0].imm in eh_prolog
            for reg in (x86.X86_REG_EAX,) if helper else (x86.X86_REG_EAX, x86.X86_REG_ECX, x86.X86_REG_EDX):
                alias.pop(reg, None)
                masks.discard(reg)
            cf_this = False
            continue
        for reg in ins.regs_access()[1]:
            alias.pop(_full_register(reg), None)
    return out


def row_installs(ctx, row, tables):
    """[(store rva, table, displacement)] of the retail vftable installs in
    special member `row`'s body, in store order; a store through a register
    holding `this + d` reads at its displacement from this
    (this_displacements). Each entry also says whether that displacement is
    proven (True) or only read from the instruction (False)."""
    import bisect
    start = _rva(row.get("target_rva"))
    try:
        end = start + int(row.get("target_size") or 0)
    except (TypeError, ValueError):
        return []
    installs = _all_installs(ctx, tables)
    k = bisect.bisect_left(installs, (start, -1, -1))
    found = []
    while k < len(installs) and installs[k][0] < end:
        found.append(installs[k])
        k += 1
    if not found:
        return []
    resolved = this_displacements(ctx, row)
    return [(store, table, resolved.get(store, disp), store in resolved) for store, table, disp in found]


def own_secondary(ctx, row, tables, disp):
    """The table special member `row`'s retail body installs as its own at
    `+disp` (disp != 0): a destructor's or deleting destructor's first store
    there, a constructor's last (an inlined base constructor stores the base's
    table first); None when the body stores nothing there."""
    stored = [table for _store, table, at, _proven in row_installs(ctx, row, tables) if at == disp]
    if not stored:
        return None
    return stored[-1] if special_member(row["name"])[0] == "0" else stored[0]


def special_member(name):
    """(role code, class) of a constructor, destructor or deleting destructor
    decorated name, or None; a nested class reads `A::B::C`."""
    match = SPECIAL_MEMBER.match(name or "")
    return (match.group(1), scope_class(match.group(2))) if match else None


def own_table(ctx, row, tables):
    """(own table or None, [tables installed at +0, in store order]) of the
    retail body of special member `row`: a destructor's or deleting
    destructor's first +0 store; a constructor's table when all its +0 stores
    install that one table, or, when every store in it is proven relative to
    this (this_displacements), its last +0 store: inlined base constructors
    store their tables there first, and no store through another object's
    pointer is among them. Otherwise None (ambiguous)."""
    installs = row_installs(ctx, row, tables)
    stored = [table for _store, table, at, _proven in installs if at == 0]
    if not stored:
        return None, stored
    if special_member(row["name"])[0] == "0":
        if len(set(stored)) == 1:
            return stored[0], stored
        return (stored[-1] if all(proven for *_rest, proven in installs) else None), stored
    return stored[0], stored


def owner_rows_at(ctx, address):
    """Every functions.csv owner row (no funclet) whose body holds `address`:
    an ICF-folded body carries several."""
    import bisect
    starts, spans = _row_spans(ctx)
    k = bisect.bisect_right(starts, address) - 1
    out = []
    while k >= 0 and address - spans[k][0] < 0x20000:
        if spans[k][0] <= address < spans[k][1]:
            out.append(spans[k][2])
        k -= 1
    return out


def live_vtable_names(ctx, rows, table):
    """{`??_7` symbol: where} that the compiled objects of matched `rows` bind
    at retail address `table` through a DIR32 relocation (the derivation
    tools/data_ledger.py makes for every matched row, for these rows only).
    Empty without an object scan (a scratch root has no objects)."""
    rows = [r for r in rows if r.get("status") == "matched" and (r.get("target_rva") or "").startswith("0x")
            and r.get("source", "").lower().endswith((".c", ".cpp"))]
    if not ctx.object_scan or not rows:
        return {}
    import data_ledger
    found = collections.defaultdict(set)
    for row in rows:
        bind = data_ledger.collect_uncached([row])[0]
        for (symbol, _local), _sites in bind.get(table, {}).items():
            if symbol.startswith("??_7"):
                found[symbol].add(row["source"])
    return {symbol: "a DIR32 binding in " + ", ".join(sorted(sources)) for symbol, sources in sorted(found.items())}


def vtable_names_at(ctx, table, rows=()):
    """{`??_7` symbol: where} bound at retail address `table`: a data_rows.csv
    row, or a data_ledger.csv name/names entry (a matched row's DIR32
    relocation to that symbol reads `table` in retail), or a binding `rows`'
    compiled objects make there now (live_vtable_names: the ledger lags)."""
    out = {}
    for data in ctx.dicts(DATA_ROWS):
        if data_rva(data) == table and data.get("name", "").startswith("??_7"):
            out.setdefault(data["name"], "data_rows.csv")
    for data in ctx.dicts(DATA_LEDGER):
        if _rva(data.get("address")) != table:
            continue
        for symbol in [data.get("name", "")] + (data.get("names") or "").split(";"):
            symbol = re.split(r"@(?=(?:Code|reference)/)", symbol.strip())[0]
            if symbol.startswith("??_7"):
                out.setdefault(symbol, DATA_LEDGER.rsplit("/", 1)[-1])
    for symbol, where in live_vtable_names(ctx, rows, table).items():
        out.setdefault(symbol, where)
    return out


def destructor_only(ctx, old, rows, tables, *, installs_allowed=False):
    """True when placeholder class `old`'s rows are a destructor family that
    stores no vftable: every special member row is a destructor or deleting
    destructor (at least one deleting destructor), none installs any table
    (unless `installs_allowed`: inlined_base_restores judges the stores),
    and no other ledger row is a member of `old` (EH handlers and funclets of
    those rows aside)."""
    if not rows or any(special_member(r["name"])[0] not in ("1", "_G", "_E") for r in rows):
        return False
    if not any(special_member(r["name"])[0] in ("_G", "_E") for r in rows):
        return False
    if not installs_allowed and any(row_installs(ctx, r, tables) for r in rows):
        return False
    family = {r["name"] for r in rows}
    member = re.compile(r"(?:^\?\?_?[0-9A-Z]|@)" + re.escape(old) + "@@")
    for row in ctx.rows():
        name = row["name"]
        for prefix in FUNCLET_PREFIXES:
            if name.startswith(prefix):
                name = name[len(prefix):]
        if name in family or "parent=" in row.get("notes", "") or name.startswith("$L"):
            continue
        if member.search(name):
            return False
    return True


def registered_table_owners(ctx, table, tables, exclude=()):
    """{class: row} of the classes registered in reverse/canonical_classes.csv
    (outside `exclude`) one of whose constructor, destructor or deleting
    destructor rows installs retail table `table` at +0 as its own
    (own_table): the table is that registered class's (several when retail
    ICF-folded identical tables of registered classes)."""
    registered = {row.get("class") for row in ctx.dicts(CANONICAL_CLASSES)} - {"", None} - set(exclude)
    found = {}
    for store, disp in sorted(tables.get(table, ([], {}))[1].items()):
        if disp:
            continue
        for row in owner_rows_at(ctx, store):
            member = special_member(row["name"])
            if member and member[1] in registered and member[1] not in found \
                    and own_table(ctx, row, tables)[0] == table:
                found[member[1]] = row
    return found


def _derives_from(ctx, derived, base, rows):
    """Does a view of class `derived` (its registered header, or the units of
    its special member `rows`) derive from `base`? False when not read."""
    sources = {r.get("source", "") for r in rows}
    sources |= {row.get("header", "") for row in ctx.dicts(CANONICAL_CLASSES) if row.get("class") == derived}
    return any(base in class_chain(class_base_map(ctx, rel), derived)[0] for rel in sorted(sources - {""}))


def inlined_base_restores(ctx, old, new, old_rows, new_rows, tables):
    """[evidence] when placeholder `old` is a destructor family of `new` whose
    own +0 store retail dropped under an inlined base destructor, else None.

    A destructor whose base destructor is inline stores its class's tables,
    then the base's; the optimizer drops the class's stores the base's
    overwrite, so the body's first +0 store is the base's own table and
    own_table names the base, not the class. That is accepted only when
    every table each row of `old` installs at +d is either
      - the table every constructor row of `new` installs last at +d (the
        class's own, at a displacement the base does not restore), or
      - the table a constructor row of a base installs last at +d, where
        every constructor row of `new` calls (E8) that base constructor, or
      - the own table of a class registered in reverse/canonical_classes.csv
        (registered_table_owners: one of its special member rows installs it
        as its own), when that base's constructor is inline too and no
        constructor of `new` calls one (ScriptGroup's 0x003B4100 restores
        Snapshot's 0x00BBB554; neither ScriptGroup constructor stores or calls
        a Snapshot constructor),
    in order at each displacement: the class's own table, then its bases'
    (a base's restore is never followed by the class's own table, and a
    later base is a base of the earlier one), at least one store is of a
    base's kind, and `old` is a destructor family (destructor_only, stores
    allowed). The deleting destructor's slot in `new`'s own table then ties
    `old` to it (the destructor-only route), and only a destructor of `new`
    stores its bases' tables."""
    if not destructor_only(ctx, old, old_rows, tables, installs_allowed=True):
        return None
    ctors = [r for r in new_rows if special_member(r["name"])[0] == "0"]
    if not ctors:
        return None

    def last_at(row):
        out = {}
        for _store, table, at, _proven in row_installs(ctx, row, tables):
            out[at] = table
        return out

    new_last = [last_at(r) for r in ctors]
    called = None
    for row in ctors:
        calls = retail_calls(ctx, _rva(row["target_rva"]), int(row.get("target_size") or 0))
        called = set(calls) if called is None else called & set(calls)
    bases = {}                                      # displacement -> {table: base constructor row}
    for _start, _end, row in _row_spans(ctx)[1]:
        found = special_member(row["name"])
        if not found or found[0] != "0" or found[1] in (old, new) or _rva(row["target_rva"]) not in called:
            continue
        for at, table in last_at(row).items():
            bases.setdefault(at, {}).setdefault(table, row)
    evidence, restored = [], False
    for row in old_rows:
        restoring = {}                              # displacement -> (table, [(class, row)]) last restored there
        for _store, table, at, _proven in row_installs(ctx, row, tables):
            va = f"0x{table + IMAGE_BASE:08X}"
            where = f"{row['name']} at 0x{_rva(row['target_rva']):08X}"
            if all(m.get(at) == table for m in new_last):
                if at in restoring:
                    return None                     # the class's own table after a base's restore
                evidence.append(f"{where} stores {va} at +0x{at:X}, which {new}'s constructor installs there "
                                "last (its own)")
                continue
            base = bases.get(at, {}).get(table)
            if base is not None:
                owners = [(special_member(base["name"])[1], base)]
                why = (f"the table {base['name']} at 0x{_rva(base['target_rva']):08X} installs there, a base "
                       f"constructor every constructor of {new} calls")
            else:
                if at:
                    return None                     # a registered class's own table is its +0 vptr's
                registered = registered_table_owners(ctx, table, tables, exclude=(old, new))
                if not registered:
                    return None
                owners = sorted(registered.items())
                why = (f"the own table of registered {', '.join(c for c, _r in owners)} (" +
                       ", ".join(f"{r['name']} at 0x{_rva(r['target_rva']):08X}" for _c, r in owners) +
                       " installs it as its own), a base whose constructor is inline")
            previous = restoring.get(at)
            if previous is not None and previous[0] != table and not any(
                    _derives_from(ctx, earlier, later, [earlier_row])
                    for earlier, earlier_row in previous[1] for later, _r in owners):
                return None                         # a later restore of no base of the earlier one
            restoring[at] = (table, owners)
            restored = True
            evidence.append(f"{where} stores {va} at +0x{at:X}, {why}: an inlined base destructor's restore")
    return evidence if restored else None


def third_owners(ctx, table, classes, tables):
    """{class: [rows]} of the special member rows of classes outside `classes`
    whose retail body installs `table` at +0 as their own (own_table)."""
    found = collections.defaultdict(list)
    for store, disp in sorted(tables[table][1].items()):
        if disp:
            continue
        for row in owner_rows_at(ctx, store):
            member = special_member(row["name"])
            if member and member[1] not in classes and own_table(ctx, row, tables)[0] == table:
                found[member[1]].append(row)
    return dict(found)


# A virtual method's decorated name: `?Init@W3DAptComponentColorPicker@@UAEX...`
# (access codes E private, M protected, U public virtual near __thiscall).
def virtual_member_re(cls):
    return re.compile(r"\?[A-Za-z_]\w*@" + re.escape(class_scope(cls)) + r"@@[EMU]")


def virtual_slot_tie(ctx, old, new, table, tables, unnamed):
    """[evidence] tying NEW to OLD's own table T through NEW's rowed virtual
    methods (the virtual-slot route of the section comment); raises Refusal
    with `unnamed` plus the reason when the slots do not tie it."""
    slots = tables[table][0]
    va = f"0x{table + IMAGE_BASE:08X}"
    virtuals = [r for _start, _end, r in _row_spans(ctx)[1] if virtual_member_re(new).match(r["name"])]
    if not virtuals:
        raise Refusal(unnamed + f"; and no row is a virtual method of {new}, so no slot of {va} ties it either")
    evidence = []
    for row in virtuals:
        rva = _rva(row["target_rva"])
        at = f"{row['name']} at 0x{rva:08X}"
        if rva not in slots:
            raise Refusal(unnamed + f"; and {at} is on no slot of {va}: {new}'s virtuals live in another table")
        elsewhere = sorted(t for t, (other, _stores) in tables.items() if t != table and rva in other)
        if elsewhere:
            raise Refusal(unnamed + f"; and {at} also sits in retail table " +
                          ", ".join(f"0x{t + IMAGE_BASE:08X}" for t in elsewhere) +
                          f": {new} may be a base with a table of its own, or the body an ICF fold")
        evidence.append(f"{at} is slot {slots.index(rva)} of {va} and of no other retail table")
    starting = collections.defaultdict(list)
    for start, _end, row in _row_spans(ctx)[1]:
        starting[start].append(row)
    scope = re.compile(r"\?(?:\?_?[0-9A-Z]|[A-Za-z_]\w*@)" + CLASS_SCOPE)
    for index, target in enumerate(slots):
        for row in starting.get(target, []):
            found = scope.match(row["name"])
            cls = scope_class(found.group(1)) if found else None
            if cls and cls not in (old, new):
                raise Refusal(unnamed + f"; and {va} slot {index} holds {row['name']} at 0x{target:08X}, a "
                              f"member of {cls}: an inherited or folded slot this route does not judge")
    evidence.append(f"{new} has no constructor, destructor or deleting destructor row and nothing names {va} "
                    f"for it; {old}'s own table holds {new}'s virtual methods, so they are one class")
    return evidence


# The initializer route, the virtual-slot route's sibling: NEW names no vftable and has no
# virtual, but a global rowed as NEW is what retail builds with OLD's constructor. A compiler
# initializer `mov ecx,&G; call ctor` runs the most-derived constructor of G, so G's class is
# that constructor's, unless ctor is a base's and the derived constructor was inlined into the
# initializer. A class derived from a polymorphic OLD has a table of its own and stores it after
# the base constructor returns, which the exact shape refuses; and OLD's constructor storing +0
# once shows OLD is polymorphic and no inlined base of its own class sits in that body. Every
# condition below is read from retail's bytes and refuses when it cannot be read:
#   - exactly one retail initializer calls a constructor of OLD, its bytes are exactly
#     `mov ecx,imm32; call rel32` (or `jmp rel32`) then nothing but `ret` or `push thunk; call
#     _atexit; pop ecx; ret`, and no other code in retail calls or names that constructor (a
#     derived constructor's call would be one);
#   - imm32 is the exact start of one matched data row, whose decorated type is exactly the
#     global class NEW, and the data ledger gives that row the same name and extent;
#   - the tree records NEW as a real class (new_class_provenance): a verified agreement;
#   - an atexit thunk is exactly `mov ecx,&G; jmp dtor` (or `call dtor; ret`), dtor a destructor
#     of OLD;
#   - OLD's constructor makes exactly one +0 store through `this`, of OLD's own table;
#   - retail calls a member of NEW with ecx=&G and no member of another readable class (OLD's
#     own methods and placeholder classes decide nothing: a placeholder method may be a base's);
#   - such a member touches a field OLD's constructor itself sets up, at or past everything its
#     base constructor chain reaches, so NEW's layout is OLD's and NEW is not one of its bases;
#   - no member of NEW touches a field at or past everything OLD's constructor reaches, which
#     would be state a derived NEW adds; no row of either class reaches past G's extent, OLD's
#     destructors read as far as they can be (a tail call into a base ends that walk);
#   - no view derives one of the two from the other;
#   - the fold is pinned in reverse/initializer_fold_census.csv. Retail's bytes never change, so what
#     bounds a false accept is the census over them (initializer_fold_census): a fold not on that
#     list, or with no review, refuses until a reviewer has looked at it by hand and added it, and
#     tests/test_rename_fold_census.py fails if the census and the list differ (fold_census_problems).
# The owner's view comes prepared, and after the build its object must reference the folded
# constructor without defining one, and data_rows must prove G's compiled size (fold_tie_problems).
INIT_THIS_CALL = re.compile(r"\?[A-Za-z_]\w*@((?:[A-Za-z_]\w*@)+)@[ABEFIJMNQRUV]")


class ThisInconclusive(ValueError):
    """this_use could not read what a body does with `this`."""


def retail_initializers(ctx):
    """Function RVAs of retail's `.CRT$XCU` table (image_report's reading of `_initterm`'s)."""
    key = "_retail_initializers"
    if key not in ctx._cache:
        import build
        import image_report
        ctx._cache[key] = image_report.Retail(build.EXE.read_bytes()).initializers()
    return ctx._cache[key]


def retail_text(ctx):
    """(rva, bytes) of retail's .text."""
    key = "_retail_text"
    if key not in ctx._cache:
        import build
        image, sections = build.exe_image()
        text = next(section for section in sections if section["name"] == ".text")
        ctx._cache[key] = (text["rva"], image[text["raw_pointer"]:text["raw_pointer"] + text["raw_size"]])
    return ctx._cache[key]


def rel32_target(rva, code, at):
    """The RVA a `call/jmp rel32` at offset `at` of `code` (read from `rva`) lands on."""
    return (rva + at + 5 + struct.unpack_from("<i", code, at + 1)[0]) & 0xFFFFFFFF


def initializer_shape(code, rva):
    """(G va, ctor rva, atexit thunk va or None, atexit rva or None) when `code` at `rva` is
    exactly the initializer shape, else None."""
    if len(code) < 11 or code[0] != 0xB9 or code[5] not in (0xE8, 0xE9):
        return None
    g, ctor = struct.unpack_from("<I", code, 1)[0], rel32_target(rva, code, 5)
    if code[5] == 0xE9 or code[10] == 0xC3:
        return g, ctor, None, None
    if len(code) >= 22 and code[10] == 0x68 and code[15] == 0xE8 and code[20] == 0x59 and code[21] == 0xC3:
        return g, ctor, struct.unpack_from("<I", code, 11)[0], rel32_target(rva, code, 15)
    return None


def initializer_callees(code, rva):
    """Every direct call or jump target of the function at `rva`, up to its first return."""
    import capstone
    out = set()
    for _address, _size, mnemonic, operands in capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32).disasm_lite(code, rva):
        if mnemonic in ("call", "jmp") and operands.startswith("0x"):
            out.add(int(operands, 16))
        if mnemonic in ("ret", "retn", "jmp"):
            break
    return out


def retail_code_refs(ctx, target):
    """Every .text address that `call`s or `jmp`s `target` by rel32 or spells its VA."""
    base, raw = retail_text(ctx)
    found = set()
    for match in re.finditer(rb"[\xE8\xE9]", raw):
        at = match.start()
        if at + 5 <= len(raw) and (base + at + 5 + struct.unpack_from("<i", raw, at + 1)[0]) & 0xFFFFFFFF == target:
            found.add(base + at)
    needle, at = struct.pack("<I", target + IMAGE_BASE), -1
    while True:
        at = raw.find(needle, at + 1)
        if at < 0:
            return found
        found.add(base + at)


def _thiscall(ctx, target):
    """Is the row at `target` a __thiscall member? None when no decorated name says."""
    row = row_at(ctx, target)
    name = row["name"] if row is not None and _rva(row.get("target_rva")) == target else ""
    return bool(re.search(r"@@[ABEFIJMNQRUV][A-D]?E", name)) if name.startswith("?") else None


def _callee_pops(ctx, target):
    """The bytes `target`'s own `ret` takes off the stack, or None when it cannot be read."""
    import capstone
    import build
    row = row_at(ctx, target)
    if row is None or _rva(row.get("target_rva")) != target:
        return None
    code = build.read_target_bytes(target, int(row.get("target_size") or 0))
    for ins in capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32).disasm(code, target):
        if ins.mnemonic in ("ret", "retn"):
            return int(ins.op_str, 16) if ins.op_str else 0
    return None


def _merge_this(a, b):
    """Two paths' `this` states at one address. Holding `this`, or a stack address, on only one
    path is `maybe`; a saved copy of `this` taints its stack slot on every path after it."""
    regs = a["regs"] & b["regs"]
    maybe = (a["maybe"] | b["maybe"] | a["regs"] | b["regs"]) - regs
    derived, stack = {}, {}
    for name in set(a["derived"]) | set(b["derived"]):
        left, right = a["derived"].get(name), b["derived"].get(name)
        if left is None or right is None:
            maybe |= {name}
        else:
            derived[name] = left if left == right else (min(left[0], right[0]), False)  # a loop's pointer
    for name in set(a["stack"]) | set(b["stack"]):
        if a["stack"].get(name) == b["stack"].get(name):
            stack[name] = a["stack"][name]
        else:
            maybe |= {name}
    return dict(regs=regs, maybe=maybe - set(derived) - set(stack), derived=derived, stack=stack,
                taint=a["taint"] | b["taint"], built=a["built"] & b["built"], sp=a["sp"] if a["sp"] == b["sp"] else None,
                frame=a["frame"] if a["frame"] == b["frame"] else None)


# What this_use reads through `this`. Anything else that reads a register holding it refuses.
THIS_READS = frozenset(("mov", "lea", "push", "cmp", "test", "add", "sub", "and", "or", "inc", "dec", "movzx", "movsx"))


def this_use(ctx, start, seed="ecx", *, follow=False, lenient=False, _seen=None):
    """What the rowed retail body at `start` does with `this`, which arrives in ecx or, with an
    int `seed`, as that stack argument. A dict: `fields` {displacement read, written or taken},
    `setup` {displacement written through `this`, or whose address the body writes through or
    passes on}, `reach` (the largest displacement plus access size, or displacement alone for an
    address), `vptr` [the immediate, or None, of each store at this+0], `chain` [(callee, seed)
    of each call receiving `this` itself: in ecx, unless the callee's decorated name says it is no
    __thiscall member, or pushed as an argument].

    It reads a short list of shapes and raises ThisInconclusive on anything else; a false refusal
    costs nothing here. The body's control flow is followed to a fixed point. A write to a register
    drops `this` from it, and a register holding `this` on only some paths into a join cannot be used.
    Past the ledger's one __EH_prolog row (eh_prolog_rva) ecx stays. Every path must end in a `ret` or
    in a call or tail jump the walk handled; running off the row, a branch it cannot follow, or a
    target inside an instruction refuses.

    The stack holds no live copy of `this`. Pushing a register holding it, or storing it in a frame
    slot, is allowed (an arguments's push, `push ecx` reserving a local, a spill for unwinding), but
    taints that slot for good: nothing may read it or pop it, whatever overwrote it since. Its address
    may not be taken either, with one exception, P36's local temporary: once `lea ecx,[slot]; call ??0X`
    has constructed over the reserved slot, its address may travel, though its bytes are still never
    read. An incoming stack argument holding `this` may only be loaded whole into a register. Copying
    a stack address refuses, and a register holding one cannot be dereferenced, nor passed on if a
    tainted slot lies at or above it. An 8- or 16-bit operation on a register holding `this` refuses.
    A call or tail jump with this+d in ecx refuses, since the callee's reach through the subobject is
    unread. With `follow`, a callee receiving `this` is read the same way and its reach counts; an
    unrowed or indirect callee, a subobject address passed on, or an indexed or loop access refuses,
    since none of those bounds the reach. A pointer to `this` stored outside the stack is not
    followed: that is the other object's use of it, not a field this body's class chain sets up.

    With `lenient` the body is read as far as it can be, and what it cannot read adds nothing instead
    of raising: enough to catch a destructor reaching past a global, which is all it is used for."""
    import capstone
    from capstone import x86
    import build
    seen = {} if _seen is None else _seen
    key = (start, seed)
    if key in seen:
        return seen[key]
    if len(seen) > 32:
        raise ThisInconclusive(f"the chain from 0x{start:08X} goes too deep to read")
    row = row_at(ctx, start)
    if row is None or _rva(row.get("target_rva")) != start:
        raise ThisInconclusive(f"0x{start:08X} has no row, so its body's extent is unknown")
    size = int(row.get("target_size") or 0)
    code = build.read_target_bytes(start, size)
    use = dict(fields=set(), setup=set(), reach=0, vptr=[], chain=[])
    seen[key] = use
    md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
    md.detail = True
    decoded, finish = {}, start
    for ins in md.disasm(code, start):
        decoded[ins.address] = ins
        finish = ins.address + ins.size
    if finish != start + size:
        raise ThisInconclusive(f"0x{start:08X} does not decode to its row's end (stopped at 0x{finish:08X})")
    eh_prolog = eh_prolog_rva(ctx)
    argument = None if seed == "ecx" else 4 + 4 * seed

    def step(ins, state, record):
        """(state after `ins`, the addresses it continues at). Only `record` touches `use` or raises:
        states only ever lose certainty, so the final pass sees each instruction at its least certain."""
        state = dict(state, regs=set(state["regs"]), maybe=set(state["maybe"]), derived=dict(state["derived"]),
                     stack=dict(state["stack"]), taint=set(state["taint"]), built=set(state["built"]))
        regs, maybe, derived, stack, taint, built = (state[n] for n in ("regs", "maybe", "derived", "stack", "taint", "built"))
        ops, mnemonic = ins.operands, ins.mnemonic
        where = f"0x{ins.address:08X} in 0x{start:08X}"
        guarded = bool(taint) or argument is not None

        def unsure(why):
            if record and not lenient:
                raise ThisInconclusive(f"{where} {why}")

        def full(reg):
            return FULL_REG.get(ins.reg_name(reg), ins.reg_name(reg))

        def place(mem, name):
            if mem.index:
                return None
            if name == "esp":
                return None if state["sp"] is None else mem.disp - state["sp"]
            return mem.disp + state["frame"] if name == "ebp" and state["frame"] is not None else None

        def saved(slot, width=4):
            return any(slot < t + 4 and t < slot + width for t in taint)

        def receive(target):
            """`this` reaches `target`: in ecx, and as each stack argument holding it."""
            kind = None if target is None else _thiscall(ctx, target)
            takes_ecx = target is None or kind is not False
            if takes_ecx and "ecx" in maybe:
                unsure("may or may not pass `this` in ecx")
            if takes_ecx and "ecx" in derived:
                unsure(f"passes this+{derived['ecx'][0]:#x} in ecx to a callee the proof does not read")
            if "ecx" in stack and takes_ecx:
                slot = stack["ecx"]
                name = next((r["name"] for r in ctx.rows() if _rva(r.get("target_rva")) == target), "")
                if slot in taint and kind and name.startswith("??0"):
                    built.add(slot)
                if any(t >= slot for t in taint - built):
                    unsure("passes the address of a stack slot holding `this` in ecx")
            given = ["ecx"] if "ecx" in regs and takes_ecx else []
            if taint:
                if state["sp"] is None:
                    unsure("makes a call on a stack it cannot place")
                else:
                    pops = None if target is None else _callee_pops(ctx, target)
                    counted = pops if pops or kind else None
                    given += [(slot + state["sp"]) // 4 for slot in sorted(taint - built) if slot >= -state["sp"]
                              and not (slot + state["sp"]) % 4 and (counted is None or slot + state["sp"] < counted)]
            for how in given:
                if target is None:
                    unsure("passes `this` to an indirect call")
                elif record:
                    if (target, how) not in use["chain"]:
                        use["chain"].append((target, how))
                    if follow:
                        use["reach"] = max(use["reach"], this_use(ctx, target, how, follow=True, _seen=seen)["reach"])

        alias = regs | maybe | set(derived)
        if any(op.type == x86.X86_OP_REG and ins.reg_name(op.reg) != full(op.reg)
               and full(op.reg) in alias | set(stack) for op in ops):
            unsure(f"runs `{mnemonic}` on part of a register holding `this`")
        if {full(reg) for reg in ins.regs_access()[0]} & alias:
            operands = {full(op.reg) for op in ops if op.type == x86.X86_OP_REG}
            control = ins.group(capstone.CS_GRP_CALL) or ins.group(capstone.CS_GRP_JUMP) or ins.group(capstone.CS_GRP_RET)
            if not control and mnemonic not in THIS_READS:
                unsure(f"runs `{mnemonic}` on `this`")
            elif control and operands & alias:
                unsure("branches through a register holding `this`")
            elif mnemonic in ("and", "or", "inc", "dec", "movzx", "movsx") and operands & alias:
                unsure(f"runs `{mnemonic}` on `this`")
            elif mnemonic in ("add", "sub") and operands & alias and (
                    len(ops) != 2 or ops[0].type != x86.X86_OP_REG or ops[1].type != x86.X86_OP_IMM):
                unsure(f"runs `{mnemonic}` on `this`")
        for op in ops:
            if op.type != x86.X86_OP_MEM:
                continue
            base = ins.reg_name(op.mem.base) if op.mem.base else None
            index = ins.reg_name(op.mem.index) if op.mem.index else None
            if index in alias or index in stack:
                unsure("indexes by `this`")
            if base in maybe:
                unsure(f"uses {base}, which may or may not hold `this` here")
            elif base in stack and guarded:
                unsure("reads through a stack address while `this` is on the stack")
            elif base in regs or base in derived:
                at, exact = derived.get(base, (0, True))
                at += op.mem.disp
                if follow and (index or not exact):
                    unsure("reaches an unbounded offset of `this`")
                if record:
                    use["fields"].add(at)
                    use["reach"] = max(use["reach"], at + (0 if mnemonic == "lea" else op.size))
                    if mnemonic != "lea" and op.access & capstone.CS_AC_WRITE:
                        use["setup"].add(at)
                        if not at and not index and exact:
                            use["vptr"].append(ops[1].imm & 0xFFFFFFFF if len(ops) == 2 and mnemonic == "mov"
                                               and ops[1].type == x86.X86_OP_IMM else None)
            elif base in ("esp", "ebp") and mnemonic != "lea":
                slot = place(op.mem, base)
                if slot is None:
                    if guarded:
                        unsure("uses a stack slot it cannot place")
                    continue
                if op.access & capstone.CS_AC_READ and saved(slot, op.size):
                    unsure("reads a stack slot that has held `this`")
                if argument is not None and slot < argument + 4 and argument < slot + op.size:
                    whole = mnemonic == "mov" and op.access == capstone.CS_AC_READ and op.size == 4 \
                        and slot == argument and ops[0].type == x86.X86_OP_REG
                    if not whole:
                        unsure("uses the stack argument holding `this` other than loading it whole")

        if ins.group(capstone.CS_GRP_RET):
            return state, []
        if ins.group(capstone.CS_GRP_INT):
            unsure(f"stops at `{mnemonic}`")
            return state, []
        if ins.group(capstone.CS_GRP_CALL):
            target = ops[0].imm if ops and ops[0].type == x86.X86_OP_IMM else None
            if target is not None and target == eh_prolog:
                # __EH_prolog: ebp is the caller's esp less 4, the frame takes 0x10; ecx stays
                state["frame"] = None if state["sp"] is None else -state["sp"] - 4
                state["sp"] = None if state["sp"] is None else state["sp"] + 0x10
                for name in ("eax", "edx"):
                    regs.discard(name), maybe.discard(name), derived.pop(name, None), stack.pop(name, None)
                return state, [ins.address + ins.size]
            receive(target)
            for name in ("eax", "ecx", "edx"):
                regs.discard(name), maybe.discard(name), derived.pop(name, None), stack.pop(name, None)
            pops = _callee_pops(ctx, target) if target is not None else None
            state["sp"] = None if state["sp"] is None or pops is None else state["sp"] - pops
            return state, [ins.address + ins.size]
        if ins.group(capstone.CS_GRP_JUMP):
            target = ops[0].imm if ops and ops[0].type == x86.X86_OP_IMM else None
            onward = [] if mnemonic == "jmp" else [ins.address + ins.size]
            if target is None:
                unsure("branches where the walk cannot follow")
                return state, onward
            if start <= target < start + size:
                if target not in decoded:
                    unsure(f"branches into an instruction at 0x{target:08X}")
                    return state, onward
                return state, onward + [target]
            found = row_at(ctx, target)
            if found is None or _rva(found.get("target_rva")) != target:
                unsure(f"jumps off its row to 0x{target:08X}, which is no row's start")
            receive(target)
            return state, onward

        src, dst = (ops[1], ops[0]) if len(ops) == 2 else (None, None)
        dst_reg = ins.reg_name(dst.reg) if dst is not None and dst.type == x86.X86_OP_REG else None
        source = ins.reg_name(src.reg) if src is not None and src.type == x86.X86_OP_REG else None
        kept = {}
        if mnemonic == "mov" and dst_reg == "ebp" and source == "esp":
            state["frame"] = None if state["sp"] is None else -state["sp"]
        elif mnemonic == "lea" and dst_reg == "ebp" and src.mem.base and ins.reg_name(src.mem.base) == "esp":
            state["frame"] = None if state["sp"] is None else src.mem.disp - state["sp"]
        elif mnemonic == "mov" and dst_reg and source:
            if source in ("esp", "ebp") or source in stack:
                unsure("copies a stack address")
            elif source in regs:
                kept["regs"] = True
            elif source in maybe:
                kept["maybe"] = True
            elif source in derived:
                kept["derived"] = derived[source]
        elif mnemonic == "mov" and dst_reg and src.type == x86.X86_OP_MEM and src.mem.base \
                and argument is not None and place(src.mem, ins.reg_name(src.mem.base)) == argument:
            kept["regs"] = True
        elif mnemonic == "lea" and dst_reg and src.mem.base:
            name = ins.reg_name(src.mem.base)
            if name in ("esp", "ebp"):
                slot = place(src.mem, name)
                if guarded and (slot is None or src.mem.index or (dst_reg != "ecx" and any(
                        slot < t + 4 and t < slot + 4 for t in taint - built))):
                    unsure("takes the address of a stack slot that has held `this`")
                if slot is not None:
                    kept["stack"] = slot
            elif not src.mem.index:
                if name in regs and not src.mem.disp:
                    kept["regs"] = True
                elif name in regs:
                    kept["derived"] = (src.mem.disp, True)
                elif name in derived:
                    kept["derived"] = (src.mem.disp + derived[name][0], derived[name][1])
                elif name in stack:
                    unsure("offsets a stack address")
        elif mnemonic in ("add", "sub") and dst_reg and src.type == x86.X86_OP_IMM:
            if dst_reg in regs or dst_reg in derived:
                at, exact = derived.get(dst_reg, (0, True))
                kept["derived"] = (at + (src.imm if mnemonic == "add" else -src.imm), exact)
            elif dst_reg in stack:
                unsure("offsets a stack address")
        elif mnemonic == "mov" and dst is not None and dst.type == x86.X86_OP_MEM and source:
            name = ins.reg_name(dst.mem.base) if dst.mem.base else None
            if name in ("esp", "ebp") and not (name == "ebp" and name in regs):
                slot = place(dst.mem, name)
                if source in regs or source in maybe:
                    if source in maybe:
                        unsure("saves a register that may or may not hold `this`")
                    if slot is None:
                        unsure("saves `this` in a stack slot it cannot place")
                    else:
                        taint.add(slot)
                elif source in stack:
                    unsure("saves a stack address")
        if mnemonic in ("add", "sub") and dst_reg == "esp" and state["sp"] is not None:
            state["sp"] = state["sp"] + (src.imm if mnemonic == "sub" else -src.imm) if src.type == x86.X86_OP_IMM else None
        elif dst_reg == "esp" and mnemonic not in ("add", "sub"):
            state["sp"] = None
        if mnemonic == "leave":
            state["sp"] = None if state["frame"] is None else -(state["frame"] + 4)
        if mnemonic == "push":
            state["sp"] = None if state["sp"] is None else state["sp"] + 4
            if ops[0].type == x86.X86_OP_REG:
                name = ins.reg_name(ops[0].reg)
                if name in maybe:
                    unsure("pushes a register that may or may not hold `this`")
                if name in regs:
                    if state["sp"] is None:
                        unsure("pushes `this` on a stack it cannot place")
                    else:
                        taint.add(-state["sp"])
                elif name in derived:
                    if record:
                        use["setup"].add(derived[name][0])
                        use["reach"] = max(use["reach"], derived[name][0])
                    if follow:
                        unsure(f"passes this+{derived[name][0]:#x} on")
                elif name in stack and any(t >= stack[name] for t in taint - built):
                    unsure("passes the address of a stack slot holding `this`")
                elif name == "esp" or (name == "ebp" and state["frame"] is not None):
                    unsure("pushes a stack address")
            return state, [ins.address + ins.size]
        if mnemonic == "pop":
            if guarded and state["sp"] is None:
                unsure("pops a stack it cannot place")
            elif state["sp"] is not None:
                if saved(-state["sp"]):
                    unsure("pops a stack slot that has held `this`")
                if argument == -state["sp"]:
                    unsure("pops the stack argument holding `this`")
                state["sp"] -= 4
            if ops[0].type == x86.X86_OP_REG:
                name = ins.reg_name(ops[0].reg)
                regs.discard(name), maybe.discard(name), derived.pop(name, None), stack.pop(name, None)
            return state, [ins.address + ins.size]
        for reg in ins.regs_access()[1]:
            name = full(reg)
            regs.discard(name), maybe.discard(name), derived.pop(name, None), stack.pop(name, None)
        if dst_reg and dst_reg not in ("esp",) and not (dst_reg == "ebp" and not kept):
            if kept.get("regs"):
                regs.add(dst_reg)
            elif kept.get("maybe"):
                maybe.add(dst_reg)
            elif "derived" in kept:
                derived[dst_reg] = kept["derived"]
            elif "stack" in kept:
                stack[dst_reg] = kept["stack"]
        return state, [ins.address + ins.size]

    states = {start: dict(regs={"ecx"} if seed == "ecx" else set(), maybe=set(), derived={}, stack={}, taint=set(),
                          built=set(), sp=0, frame=None)}
    work = [start]
    visits = 0
    while work:
        address = work.pop()
        visits += 1
        if visits > 64 * len(decoded) + 64:
            raise ThisInconclusive(f"the walk of 0x{start:08X} does not settle")
        after, onward = step(decoded[address], states[address], False)
        for target in onward:
            if target not in decoded:
                if lenient:
                    continue
                raise ThisInconclusive(f"0x{address:08X} in 0x{start:08X} runs off its row's end")
            merged = _merge_this(states[target], after) if target in states else after
            if merged != states.get(target):
                states[target] = merged
                work.append(target)
    for address in sorted(states):
        step(decoded[address], states[address], True)
    return use


def new_class_provenance(ctx, new, owner):
    """How the tree records NEW as a real class, or raises Refusal: spelling alone never qualifies, and
    neither does a label or a registry row nobody can check. The one arm is an inferred name_basis.csv
    record whose agreement check_agreement recomputes here, for this class in the global's owner unit.
    A two-agent agreement is the project's normal standard for a name, not retail evidence: the byte
    conditions are what tie OLD to NEW. The agreement's address is optional, and naming another member of
    the same class still passes: it stays bound to the class and the owner."""
    records = [row for row in name_basis_rows(ctx) if row.get("kind") == "class" and row.get("new") == new]
    if not records:
        raise Refusal(f"{new} has no class record in {NAME_BASIS}: a hand-named class does not qualify")
    record = records[-1]
    basis, evidence = record.get("basis", ""), record.get("evidence", "")
    if basis != "inferred" or not evidence.startswith("agree:"):
        raise Refusal(f"{new}'s {NAME_BASIS} record is {basis or 'no basis'} ({evidence or 'no evidence'}), "
                      "not a verified agreement")
    if record.get("source") != owner:
        raise Refusal(f"{new}'s {NAME_BASIS} record is for {record.get('source') or 'no source'}, not the global's "
                      f"owner {owner}")
    agreed = [row for row in ctx.dicts(AGREED) if row.get("id") == evidence[len("agree:"):]]
    if agreed and agreed[-1].get("key", "").split("|")[0] != owner:
        raise Refusal(f"agreement {evidence} is for {agreed[-1].get('key', '').split('|')[0] or 'no source'}, not the "
                      f"global's owner {owner}")
    address = _rva((record.get("rva") or (agreed[-1].get("rva") if agreed else "")) or None)
    if address is not None and not any(_rva(r.get("target_rva")) == address and INIT_THIS_CALL.match(r["name"])
                                       and INIT_THIS_CALL.match(r["name"]).group(1).rstrip("@") == new
                                       for r in ctx.rows()):
        raise Refusal(f"{new}'s agreement names 0x{address:08X}, which is no member row of {new}")
    check_agreement(ctx, "class", evidence, {record.get("old")}, {new}, address)
    return f"{new} is agreed ({evidence}, verified now), not retail-evidenced"


def initializer_fold_census(ctx):
    """{(old, new, initializer rva)}: every fold initializer_tie admits over retail's whole table."""
    import build
    data = {data_rva(d): d for d in ctx.dicts(DATA_ROWS) if d.get("address")}
    admitted = set()
    for entry in retail_initializers(ctx):
        shape = initializer_shape(build.read_target_bytes(entry, 64), entry)
        if shape is None:
            continue
        row, datum = row_at(ctx, shape[1]), data.get(shape[0] - IMAGE_BASE)
        if row is None or datum is None or _rva(row["target_rva"]) != shape[1]:
            continue
        member = special_member(row["name"])
        if not member or member[0] != "0":
            continue
        try:
            typed = type_tree(datum["name"])[3][2]
        except (ValueError, IndexError, TypeError):
            continue
        if typed[0] != "C" or len(typed[2][1]) != 1 or typed[2][1][0][0] != "N":
            continue
        old, new = member[1], typed[2][1][0][1]
        if old == new or not is_placeholder(old, "class"):
            continue
        tie = {}
        try:
            fold_evidence(ctx, old, new, tie, pinned=False)
        except Refusal:
            continue
        if tie:
            admitted.add((old, new, tie["entry"]))
    return admitted


def fold_census_problems(ctx):
    """[why] the census over retail and the reviewed list differ. Every listed fold is either still
    admitted, or has landed, which takes positive evidence: the constructor retail's initializer calls
    is rowed ??0NEW and no row or pin names OLD. Nothing admitted may be unlisted."""
    import build
    admitted = initializer_fold_census(ctx)
    problems, listed = [], set()
    for row in ctx.dicts(FOLD_CENSUS):
        old, new, entry = row.get("old", ""), row.get("new", ""), _rva(row.get("initializer"))
        fold = (old, new, entry)
        listed.add(fold)
        where = f"{old} into {new} by {row.get('initializer')}"
        if not (row.get("review") or "").strip():
            problems.append(f"{where} has no review")
        if fold in admitted:
            continue
        shape = initializer_shape(build.read_target_bytes(entry, 64), entry) if entry is not None else None
        ctor_named = shape is not None and any(
            _rva(r.get("target_rva")) == shape[1] and r["name"].startswith(f"??0{new}@@") for r in ctx.rows())
        frag = type_fragment_re(old) if old else None
        spells_old = frag is None or any(frag.search(r["name"]) for r in ctx.rows()) or any(
            frag.search(p.get("name", "")) for p in ctx.pins())
        if not ctor_named or spells_old:
            problems.append(f"{where} is neither admitted nor landed (the constructor retail's initializer calls "
                            f"{'is' if ctor_named else 'is not'} rowed ??0{new}; rows or pins "
                            f"{'still name' if spells_old else 'no longer name'} {old})")
    for fold in sorted(admitted - listed, key=str):
        problems.append(f"{fold[0]} into {fold[1]} by 0x{fold[2]:08X} is admitted but not listed: a reviewer must read it")
    return problems


def initializer_tie(ctx, old, new, table, tables, members, unnamed, pinned=True):
    """([evidence], tie) proving G's class NEW and OLD one class (see the comment above);
    raises Refusal with `unnamed` plus the reason. `pinned` also requires the fold to be on the
    reviewed census; only the census itself reads without it."""
    import build

    def no(why):
        return Refusal(unnamed + f"; and no retail initializer ties them: {why}")

    if name_metric.placeholder(new) or not IDENT.fullmatch(new):
        raise no(f"{new} is a placeholder or scoped name, so no real row says what G is")
    ctors = {_rva(r["target_rva"]): r for r in members[old] if special_member(r["name"])[0] == "0"}
    dtors = {_rva(r["target_rva"]): r for r in members[old] if special_member(r["name"])[0] == "1"}
    if not ctors:
        raise no(f"{old} has no constructor row")
    try:
        hits = []
        for entry in retail_initializers(ctx):
            code = build.read_target_bytes(entry, 64)
            if initializer_callees(code, entry) & set(ctors):
                hits.append((entry, code))
        if len(hits) != 1:
            raise no(f"{len(hits)} retail initializers call a constructor of {old} "
                     f"({', '.join(f'0x{e:08X}' for e, _c in hits[:4])}): exactly one must")
        entry, code = hits[0]
        shape = initializer_shape(code, entry)
        if shape is None or shape[1] not in ctors:
            raise no(f"0x{entry:08X} is not exactly `mov ecx,&G; call ctor`, then `ret` or an atexit registration: "
                     "anything more may be a derived class's own construction")
        g_va, ctor, thunk, atexit = shape
        g = g_va - IMAGE_BASE
        for address in sorted(set(ctors)):
            others = retail_code_refs(ctx, address) - {entry + 5}
            if others:
                raise no(f"retail also reaches {ctors[address]['name']} from 0x{min(others):08X}: a derived "
                         "constructor or a second use, so the initializer alone does not say what the class is")
        data = [d for d in ctx.dicts(DATA_ROWS) if d.get("status") == "matched" and d.get("address")
                and data_rva(d) <= g < data_rva(d) + int(d.get("size") or 0)]
        if len(data) != 1 or data_rva(data[0]) != g:
            raise no(f"0x{g_va:08X} is not the exact start of one matched data row ({len(data)} rows hold it)")
        row = data[0]
        try:
            tree = type_tree(row["name"])
            header = tree[3]
            typed = header[2]
        except (Unparsed, IndexError):
            raise no(f"{row['name']}'s type cannot be read") from None
        if not (tree[0] == "SYM" and header[0] == "H" and header[1][:1] in "01234" and typed[0] == "C"
                and typed[2][1] == (("N", new),)):
            raise no(f"{row['name']} at 0x{g_va:08X} is not typed exactly as class {new}")
        try:
            provenance = new_class_provenance(ctx, new, row.get("source", ""))
        except Refusal as error:
            raise no(str(error)) from None
        extent = int(row.get("size") or 0)
        ledger = [d for d in ctx.dicts(DATA_LEDGER) if _rva(d.get("address")) == g]
        if len(ledger) != 1 or ledger[0].get("name") != row["name"] or int(ledger[0].get("size") or 0) != extent \
                or not extent:
            raise no(f"the data ledger does not give {row['name']} that name and the extent {extent} at 0x{g:08X}")
        cleanup = None
        if thunk is not None:
            names = {r["name"] for r in ctx.rows() if _rva(r.get("target_rva")) == atexit}
            if "_atexit" not in names:
                raise no(f"0x{entry:08X} registers its thunk through 0x{atexit:08X} "
                         f"({', '.join(sorted(names)) or 'unrowed'}), not _atexit")
            body = build.read_target_bytes(thunk - IMAGE_BASE, 11)
            exact = len(body) >= 10 and body[0] == 0xB9 and struct.unpack_from("<I", body, 1)[0] == g_va \
                and (body[5] == 0xE9 or (body[5] == 0xE8 and len(body) > 10 and body[10] == 0xC3))
            cleanup = rel32_target(thunk - IMAGE_BASE, body, 5) if exact else None
            if cleanup not in dtors:
                raise no(f"its atexit thunk 0x{thunk:08X} is not exactly `mov ecx,&G; jmp dtor` with a destructor of {old}")

        # OLD's constructor: one +0 store, of its own table; what it sets up past its bases
        own = this_use(ctx, ctor)
        if own["vptr"] != [table + IMAGE_BASE]:
            stored = ", ".join("an unknown value" if v is None else f"0x{v:08X}" for v in own["vptr"]) or "nothing"
            raise no(f"{ctors[ctor]['name']} stores {stored} at +0, not exactly once 0x{table + IMAGE_BASE:08X}: "
                     "an inlined base may sit in its body")
        seen = {}
        base_reach = 0
        for callee, how in own["chain"]:
            base_reach = max(base_reach, this_use(ctx, callee, how, follow=True, _seen=seen)["reach"])
        past_base = {at for at in own["setup"] if at >= max(base_reach, 4)}

        # the row is corroborated by retail's own calls on G
        text_rva, raw = retail_text(ctx)
        needle = b"\xB9" + struct.pack("<I", g_va)
        called, others, at = {}, set(), raw.find(needle)
        while at >= 0:
            if raw[at + 5:at + 6] == b"\xE8":
                target = (text_rva + at + 10 + struct.unpack_from("<i", raw, at + 6)[0]) & 0xFFFFFFFF
                member = row_at(ctx, target)
                match = INIT_THIS_CALL.match(member["name"]) if member and _rva(member["target_rva"]) == target else None
                cls = match.group(1).rstrip("@") if match else None
                if cls == new:
                    called[target] = member
                elif cls and cls != old and not name_metric.placeholder(cls.split("@")[0]):
                    others.add(member["name"])
            at = raw.find(needle, at + 1)
        if others:
            raise no(f"retail also calls {', '.join(sorted(others)[:2])} on it: a member of another real class, so "
                     "G's class is not settled")
        if not called:
            raise no(f"retail calls no rowed member of {new} on it, so nothing corroborates {row['name']}")
        shared = {}
        for target, member in called.items():
            for field in this_use(ctx, target)["fields"] & past_base:
                shared.setdefault(field, member)
        if not shared:
            raise no(f"no member of {new} retail calls on it touches a field {ctors[ctor]['name']} sets up past its "
                     f"base chain's reach (+{base_reach:#x}; it sets up "
                     f"{', '.join(f'+{d:#x}' for d in sorted(past_base)) or 'nothing'}): {new} may be a base")

        # no state a derived NEW adds, and nothing reaches past G
        new_rows = [r for _s, _e, r in _row_spans(ctx)[1] if INIT_THIS_CALL.match(r["name"])
                    and INIT_THIS_CALL.match(r["name"]).group(1).rstrip("@") == new]
        for member in new_rows:
            use = this_use(ctx, _rva(member["target_rva"]))
            beyond = sorted(d for d in use["fields"] if d >= own["reach"])
            if beyond:
                raise no(f"{member['name']} touches +{beyond[0]:#x}, past everything {ctors[ctor]['name']} reaches "
                         f"(+{own['reach']:#x}): {new} may be a class derived from {old}")
        for member in list(ctors.values()) + new_rows + [r for r in members[old] if _rva(r["target_rva"]) not in ctors]:
            reach = this_use(ctx, _rva(member["target_rva"]), lenient=_rva(member["target_rva"]) not in ctors
                             and member in members[old])["reach"]
            if reach > extent:
                raise no(f"{member['name']} reaches this+{reach:#x}, past G's {extent:#x} bytes")
    except ThisInconclusive as error:
        raise no(str(error)) from None
    except (OSError, ValueError, struct.error) as error:
        raise no(f"retail's bytes cannot be read ({error})") from None
    owner = row.get("source", "")
    for rel in sorted({owner, *(r["source"] for r in members[old])}):
        bases = class_base_map(ctx, rel)
        if old in class_chain(bases, new)[0] or new in class_chain(bases, old)[0]:
            raise no(f"{rel} derives one of {old} and {new} from the other, so they are two classes")
    if pinned and not any(r.get("old") == old and r.get("new") == new and _rva(r.get("initializer")) == entry
                          and (r.get("review") or "").strip() for r in ctx.dicts(FOLD_CENSUS)):
        raise no(f"{old} into {new} by 0x{entry:08X} has no row with a review in {FOLD_CENSUS}: a new member of the "
                 "census needs a reviewer's look by hand before it is added")
    evidence = [f"retail initializer 0x{entry:08X} builds {row['name']} at 0x{g_va:08X} ({extent} bytes) with "
                f"{ctors[ctor]['name']}: exactly `mov ecx,&G; call ctor`, its only caller", provenance]
    if thunk is not None:
        evidence.append(f"its atexit thunk 0x{thunk:08X} is `mov ecx,&G; jmp {dtors[cleanup]['name']}`")
    field, member = min(shared.items())
    evidence.append(f"{ctors[ctor]['name']} stores +0 once (0x{table + IMAGE_BASE:08X}) and sets up +{field:#x}, past "
                    f"its base chain's +{base_reach:#x}; {member['name']}, which retail calls on it, touches that field")
    return evidence, dict(row=row, owner=owner, ctor=ctors[ctor]["name"], entry=entry, g=g, extent=extent,
                          thunk=None if thunk is None else thunk - IMAGE_BASE)


def fold_tie_problems(ctx, tie):
    """After ./build.sh: the owner's object references the folded constructor and defines none
    (a local plain-data constructor is the defect this route repairs), and data_rows proves the
    global's compiled size against its row."""
    sys.path.insert(0, str(ctx.root / "tools"))
    import build
    import data_rows
    import reloc_ledger
    obj = build.obj_path(ctx.path(tie["owner"]))
    if not obj.exists():
        return [f"{tie['owner']} has no object after the build"]
    _sections, symbols = reloc_ledger.parse_coff(obj.read_bytes())
    named = [sym for sym in symbols.values() if sym["name"] == tie["ctor_new"]]
    problems = []
    if not named:
        problems.append(f"{tie['owner']}'s object does not reference {tie['ctor_new']}: its initializer does not run it")
    if any(sym["section"] > 0 for sym in named):
        problems.append(f"{tie['owner']}'s object defines its own {tie['ctor_new']}: a local copy, not retail's row")
    if not problems:
        img, resolve = reloc_ledger.Image(), data_rows.Resolver(data_rows.load())
        ok, message = data_rows.verify_row(tie["row"], img, resolve, compile=False)
        if not ok:
            problems.append(f"data_rows does not prove {tie['row']['name']}: {message}")
    return problems


def fold_evidence(ctx, old, new, tie=None, pinned=True):
    """(table rva, [evidence]) proving the class names `old` and `new` one
    retail class (see the section comment); raises Refusal. `tie` (a dict) receives
    what the initializer route must prove after the build, when that route decided."""
    tables = retail_vtables(ctx)
    spans = _row_spans(ctx)[1]
    members = {old: [], new: []}
    for _start, _end, row in spans:
        found = special_member(row["name"])
        if found and found[1] in members:
            members[found[1]].append(row)

    def at(row):
        return f"{row['name']} at 0x{_rva(row['target_rva']):08X}"

    # A destructor family whose stores an inlined base destructor explains
    # (inlined_base_restores) takes the destructor-only route below.
    restores = inlined_base_restores(ctx, old, new, members[old], members[new], tables)
    owns = collections.defaultdict(list)
    for row in members[old] if restores is None else ():
        own, _stored = own_table(ctx, row, tables)
        if own is not None:
            owns[own].append(row)
    table_owner = old
    if not owns:
        no_table = (f"{old} installs no vftable retail shows as its own (through {len(members[old])} "
                    "constructor, destructor or deleting destructor row(s)): nothing in retail ties it to a "
                    "class table")
        if restores is None and not destructor_only(ctx, old, members[old], tables):
            raise Refusal(no_table)
        # A destructor-only OLD: the table is NEW's own (see the section
        # comment); its deleting destructors' slots tie OLD to it below.
        table_owner = new
        for row in members[new]:
            own, _stored = own_table(ctx, row, tables)
            if own is not None:
                owns[own].append(row)
        if not owns:
            raise Refusal(no_table + f"; and {new} installs none either, so no table's slot can tie {old}'s "
                          "deleting destructor to it")
    if len(owns) > 1:
        raise Refusal(f"{table_owner}'s rows install different own vftables (" + "; ".join(
            f"0x{t + IMAGE_BASE:08X} by {', '.join(at(r) for r in rows)}" for t, rows in sorted(owns.items())) +
            f"): {table_owner} names more than one class")
    via_slot = table_owner == new
    table = next(iter(owns))
    va = f"0x{table + IMAGE_BASE:08X}"
    evidence = []
    for row in owns[table]:
        role = special_member(row["name"])[0]
        how = "its first +0 store"
        if role == "0":
            how = ("its only +0 install" if len(set(own_table(ctx, row, tables)[1])) == 1 else
                   "its last +0 store; every vftable store in it is through this")
        evidence.append(f"{at(row)} installs retail vftable {va} as its own ({how})")
    evidence.extend(restores or ())
    for cls in (old, new):
        for row in members[cls]:
            if cls == old and restores is not None:
                continue                            # each store judged by inlined_base_restores
            own, stored = own_table(ctx, row, tables)
            if own is not None and own != table:
                raise Refusal(f"{at(row)} installs 0x{own + IMAGE_BASE:08X} as its own vftable, not {va}: "
                              f"{cls} is not that class")
            if own is None and stored and table not in stored:
                raise Refusal(f"{at(row)} installs " + ", ".join(f"0x{t + IMAGE_BASE:08X}" for t in stored) +
                              f" but never {va}: {cls} is not that class")

    installers = [row for cls in (old, new) for row in members[cls]
                  if table in own_table(ctx, row, tables)[1]]
    names = vtable_names_at(ctx, table, installers)
    classes = collections.defaultdict(list)
    for symbol, where in sorted(names.items()):
        match = GLOBAL_VTABLE.match(symbol)
        classes[scope_class(match.group(1)) if match else symbol].append(f"{symbol} ({where})")
    if new not in classes:
        unnamed = (f"retail vftable {va}, which {table_owner}'s rows install as their own, is named "
                   f"{', '.join(sorted(names)) or 'by nothing'} in data_rows.csv / data_ledger.csv / the "
                   f"installing rows' objects, not ??_7{class_scope(new)}@@6B@: nothing ties {new} to it")
        # NEW rowed only through virtual methods: their slots tie it to T
        # (see the section comment); refused like before when they do not.
        if via_slot or members[new] or set(classes) - {old}:
            raise Refusal(unnamed)
        if tie is None or any(virtual_member_re(new).match(r["name"]) for _s, _e, r in spans):
            evidence.extend(virtual_slot_tie(ctx, old, new, table, tables, unnamed))
        else:
            found, proved = initializer_tie(ctx, old, new, table, tables, members, unnamed + (
                f"; and no row is a virtual method of {new}, so no slot of {va} ties it either"), pinned)
            evidence.extend(found)
            tie.update(proved)
    # The destructor-only route lets a third class that installs T as its own
    # stand (see the section comment); it is named in the evidence, not folded.
    co_owners = third_owners(ctx, table, (old, new), tables) if via_slot else {}
    others = sorted(set(classes) - {old, new} - set(co_owners))
    if others:
        raise Refusal(f"retail vftable {va} is also named for {', '.join(others)} "
                      f"({'; '.join(w for o in others for w in classes[o])}): a third name for the table")
    evidence.append(f"{va} is named " + ", ".join(w for c in [new, old] + sorted(co_owners)
                                                  for w in classes.get(c, [])))

    # A deleting destructor's adjustor thunk sits on the class's own table for
    # the base subobject at its displacement, which the rows owning T install
    # there themselves (own_secondary); every such row must agree on it.
    secondary = {}                                  # displacement -> (table, installing row)
    for cls in (old, new):
        for row in members[cls]:
            disp = adjustor_of(row["name"])
            if disp is None or disp in secondary:
                continue
            seen = {}
            for owner in installers:
                if own_table(ctx, owner, tables)[0] != table:
                    continue
                found = own_secondary(ctx, owner, tables, disp)
                if found is not None:
                    seen.setdefault(found, owner)
            if not seen:
                raise Refusal(f"{at(row)} adjusts this by 0x{disp:X}, but no row owning {va} installs a table "
                              f"at +0x{disp:X}: nothing ties the thunk's table to {va}'s class")
            if len(seen) > 1:
                raise Refusal(f"the rows owning {va} install different tables at +0x{disp:X} (" + "; ".join(
                    f"0x{t + IMAGE_BASE:08X} by {at(r)}" for t, r in sorted(seen.items(), key=lambda x: x[0])) +
                    f"): {at(row)} has no one subobject table")
            secondary[disp] = next(iter(seen.items()))

    def subobject(disp):
        """(table rva, what it is) for this displacement's table of the class."""
        if not disp:
            return table, f"retail vftable {va}"
        other, owner = secondary[disp]
        return other, f"secondary vftable 0x{other + IMAGE_BASE:08X} (installed at +0x{disp:X} by {at(owner)})"

    starting = collections.defaultdict(list)
    for start, _end, row in spans:
        starting[start].append(row)
    for disp in [0] + sorted(secondary):
        checked, what = subobject(disp)
        slots, installs = tables[checked]
        for store, at_disp in sorted(installs.items()):
            for row in owner_rows_at(ctx, store):
                found = special_member(row["name"])
                if not found or found[1] in (old, new):
                    continue
                if disp == 0 and at_disp == 0 and found[1] in co_owners:
                    continue                    # the destructor-only route's co-owner (evidence below)
                if (at_disp == 0 and own_table(ctx, row, tables)[0] == checked) or \
                        (at_disp and own_secondary(ctx, row, tables, at_disp) == checked):
                    raise Refusal(f"{what} is also the own vftable of {found[1]} ({at(row)}): retail "
                                  "ICF-folds identical vftables of distinct classes, so the table proves no single "
                                  "class")
        for index, target in enumerate(slots):
            for row in starting.get(target, []):
                found = special_member(row["name"])
                if found and found[0] in ("_G", "_E") and found[1] not in (old, new):
                    raise Refusal(f"{what} slot {index} holds {found[1]}'s deleting destructor "
                                  f"({at(row)}): the table is not one class's of {old} and {new}")
    for cls in (old, new):
        for row in members[cls]:
            if special_member(row["name"])[0] not in ("_G", "_E"):
                continue
            checked, what = subobject(adjustor_of(row["name"]) or 0)
            slots = tables[checked][0]
            if _rva(row["target_rva"]) not in slots:
                raise Refusal(f"{at(row)} is on no slot of {what}: {cls}'s table is another one")
            evidence.append(f"{at(row)} is slot {slots.index(_rva(row['target_rva']))}" +
                            (f" of {what}" if checked != table else ""))

    # Unless a constructor of OLD installs T as its own, only destructors tie
    # OLD to T: a slot, or a destructor's first store, which an inlined base
    # destructor's restore can supply. Retail ICF-folds identical deleting
    # destructors of distinct classes into one body, which then sits in a slot
    # of each class's table; a deleting destructor of OLD that a table other
    # than the class's own (T and its subobject tables) also holds is such a
    # body, so OLD is no single class and folding it into NEW is a naming claim.
    if not (table_owner == old and any(special_member(r["name"])[0] == "0" for r in owns[table])):
        own = {table} | {other for other, _owner in secondary.values()}
        for row in members[old]:
            if special_member(row["name"])[0] not in ("_G", "_E"):
                continue
            address = _rva(row["target_rva"])
            elsewhere = [(other, slots.index(address)) for other, (slots, _installs) in sorted(tables.items())
                         if other not in own and address in slots]
            if elsewhere:
                raise Refusal(f"{at(row)} is also " + ", ".join(
                    f"slot {index} of retail vftable 0x{other + IMAGE_BASE:08X}" for other, index in elsewhere) +
                    f": an ICF-folded deleting destructor of distinct classes, and no constructor of {old} "
                    f"installs {va}, so {old} is no single class ({new} is one candidate of "
                    f"{len(elsewhere) + 1})")

    if via_slot:
        # The destructor-only route: the slots tie OLD's deleting destructors
        # to T (checked above); each destructor of OLD must be the one a
        # deleting destructor of OLD on T calls.
        deleting = [r for r in members[old] if special_member(r["name"])[0] in ("_G", "_E")]
        for row in members[old]:
            if special_member(row["name"])[0] != "1":
                continue
            target = _rva(row["target_rva"])
            callers = [d for d in deleting if target in retail_calls(ctx, _rva(d["target_rva"]),
                                                                     int(d.get("target_size") or 0))]
            if not callers:
                raise Refusal(f"{at(row)} is called by no deleting destructor of {old} on {va}: nothing ties "
                              f"{old}'s destructor to the table (it may be a base's)")
            evidence.append(f"{at(row)} is called by {at(callers[0])}")
        evidence.append((f"{old} installs no table of its own (its stores are {new}'s own tables and an inlined "
                         "base destructor's restore)" if restores is not None else
                         f"{old} installs no vftable (destructor-only)") +
                        f"; {va} is {new}'s own table, so its slot bodies are {new}'s members")
        for cls, rows in sorted(co_owners.items()):
            evidence.append(f"{va} is also installed as its own by {cls} (" + ", ".join(at(r) for r in rows) +
                            f"): overloaded constructors under two placeholders or an ICF fold; the slot "
                            f"bodies are {new}'s either way, and {cls} is not folded")

    def kind(row):
        return special_member(row["name"])[0], adjustor_of(row["name"]) or 0

    for key in sorted({kind(r) for r in members[old]} & {kind(r) for r in members[new]}):
        mine = [r for r in members[old] if kind(r) == key]
        theirs = [r for r in members[new] if kind(r) == key]
        thunk = f" (adjustor thunk, this -= 0x{key[1]:X})" if key[1] else ""
        raise Refusal(f"both names have a {SPECIAL_ROLE[key[0]]}{thunk} row ({at(mine[0])}; {at(theirs[0])}): one "
                      f"class has one (a folded vftable of two classes, or overloads or an ICF alias pair this mode "
                      "does not merge)")
    return table, evidence


def fold_access_respell(mangled_new, access):
    """`post` for class_sub under `class --fold --access`: a respelled
    destructor, deleting destructor or deleting-destructor adjustor thunk of
    the folded class (`??1NEW@@`, `??_GNEW@@`, `??_ENEW@@`) takes `access`'s
    near virtual code (thunk code for a thunk); every other symbol is kept.
    A destructor family that is not spelled virtual is refused: access is no
    retail fact, and only a virtual family's spelling follows the shared
    header's declaration."""
    code, thunk = VIRTUAL_CODE_OF[access], THUNK_CODE_OF[access]
    family = re.compile(r"(?:%s)?\?\?(1|_G|_E)%s@@" % ("|".join(re.escape(p) for p in FUNCLET_PREFIXES),
                                                    re.escape(mangled_new)))

    def post(symbol):
        match = family.match(symbol)
        if not match:
            return symbol
        at = match.end()
        current = symbol[at:at + 1]
        if current in VIRTUAL_NEAR_CODES:
            wanted = code
        elif current in THUNK_NEAR_CODES and match.group(1) != "1":
            wanted = thunk
        else:
            raise Refusal(f"{symbol}: --access respells a near virtual destructor family only "
                          f"(access code {current!r})")
        return symbol[:at] + wanted + symbol[at + 1:]
    return post


# A prepared fold into an unregistered global NEW. A unit that declares both
# views (OLD's, which its placeholder rows compile against, and NEW's) cannot be
# token-rewritten: it would declare NEW twice. Its caller writes the unit with
# NEW's view alone, and what the token rewrite kept by construction is checked
# instead: the unit spells OLD nowhere and every unit spelling OLD comes
# prepared (plan_fold), it declares no body of a registered class it did not
# declare before (class_gate's private copy), and the compiler's own record of
# the class (view_layouts: sizeof, vfptr, bases with offsets, fields with
# offsets and types, introduced virtual slots) is the same before and after.
# Before, OLD's and NEW's complete records in the unit must agree (OLD spelled
# NEW where it named itself); after, NEW's must equal them. A unit with no
# complete record before may not gain one. The rows' bytes stay the build's.

def fold_layout_shape(layout, old, new):
    """The class shape a prepared fold keeps, with OLD's own spelling read as NEW's;
    None for no complete record (absent, forward-only or unparsed)."""
    if not layout or layout.get("fwd") or layout.get("unparsed") is not None or not layout.get("size"):
        return None
    shape = {"size": layout.get("size"), "vfptr": bool(layout.get("vfptr")),
             "bases": [list(b) for b in layout.get("bases", [])],
             "fields": [list(f) for f in layout.get("fields", [])],
             "vslots": sorted([str(k), v] for k, v in (layout.get("vslots") or {}).items())}
    return word_re(old).sub(new, json.dumps(shape, sort_keys=True))


def fold_layout_baseline(ctx, old, new, prepared, touched, registered):
    """{"old", "new", "units": {rel: shape or None}}: each prepared unit's class shape
    before the fold, read from the unit as committed. Refuses a prepared unit that
    spells no OLD, declares a registered class's body it did not declare before, or
    whose two views already disagree on the layout."""
    units = {}
    for rel, data in sorted(prepared.items()):
        if rel not in touched:
            raise Refusal(f"prepared {rel} spells no {old}: a fold prepares only the units that spell it")
        before = name_metric.strip((ctx.read(rel) or b"").decode("utf-8", errors="surrogateescape"))
        after = name_metric.strip(data.decode("utf-8", errors="surrogateescape"))
        copied = sorted(c for c in registered if c and IDENT.fullmatch(c)
                        and declares_type(after, c) and not declares_type(before, c))
        if copied:
            raise Refusal(f"prepared {rel} declares a body of {copied[0]}, which {CANONICAL_CLASSES} registers: "
                          "a private copy (class_gate); include its shared header instead")
        try:
            layouts = view_layouts(ctx, rel)
        except Exception as error:                       # a compile failure or an unreadable record
            raise Refusal(f"{rel}'s class layouts cannot be read before the fold: {str(error)[:200]}") from None
        shapes = {name: fold_layout_shape(layouts.get(name), old, new) for name in (old, new)}
        complete = {name: shape for name, shape in shapes.items() if shape is not None}
        if len(set(complete.values())) > 1:
            raise Refusal(f"{rel}'s {old} view and its {new} view disagree on the class layout ({shapes[old]} "
                          f"against {shapes[new]}): one class has one layout; reconcile the two views first")
        units[rel] = next(iter(complete.values()), None)
    return {"old": old, "new": new, "units": units}


def fold_layout_problems(ctx, baseline):
    """After ./build.sh, each prepared unit's NEW against its shape before the fold."""
    old, new, problems = baseline["old"], baseline["new"], []
    for rel, want in sorted(baseline["units"].items()):
        try:
            layouts = view_layouts(ctx, rel)
        except Exception as error:
            problems.append(f"{rel}'s class layouts cannot be read after the fold: {str(error)[:200]}")
            continue
        if old in layouts:
            problems.append(f"{rel} still compiles a class {old}")
            continue
        got = fold_layout_shape(layouts.get(new), old, new)
        if got != want:
            problems.append(f"{rel}: the prepared unit changes the class layout: its {new} compiles as {got}, "
                            f"its views before the fold as {want}")
    return problems


def plan_fold(ctx, old, new, *, evidence="", max_files=25, prepared=None, access=None):
    """Plan `class --fold`: respell placeholder class `old` as `new`, the class
    retail's vftable already names (fold_evidence); see the section comment.
    `new` may be a nested class (`A::B::C`); its units then come as
    `prepared` C++. `access` ('public', 'protected' or 'private') gives the
    folded destructor family that access (fold_access_respell): a registered
    NEW's header declares its destructor with an access the placeholder's
    rows need not share, and the prepared units then compile that spelling.
    Raises Refusal; writes nothing."""
    old, new = old or "", new or ""
    parts = new.split("::")
    nested = len(parts) > 1
    for word in [old] + parts:
        if not IDENT.fullmatch(word) or word in name_metric.KEYWORDS:
            raise Refusal(f"{word!r} is not a type identifier" + (f" (in {new})" if nested and word != old else ""))
    if new == old:
        raise Refusal("the new name is the old name")
    if old in parts:
        raise Refusal(f"{old} is one of {new}'s own scope names: the fold would nest the class in itself")
    registered = {row.get("class") for row in ctx.dicts(CANONICAL_CLASSES)}
    registered_new = new in registered or ctx.path(f"{CLASS_CONTRACTS}/{new}.json").exists()
    if access is not None and access not in VIRTUAL_CODE_OF:
        raise Refusal(f"--access {access!r} is not one of {', '.join(sorted(VIRTUAL_CODE_OF))}")
    if access is not None and not prepared:
        raise Refusal("--access goes with prepared units: a token rewrite keeps each view's own access, "
                      "so only units prepared on NEW's header compile the respelled destructor family")
    if not is_placeholder(old, "class"):
        raise Refusal(f"{old} is a readable name: class --fold folds only a placeholder (docs/naming.md: a "
                      "placeholder never replaces a readable name except by a `restored` revert, and choosing "
                      "between two readable names is a naming decision)")
    reason = class_protected(ctx, old)
    if reason:
        raise Refusal(f"canonical name: {reason}")
    if old in registered or ctx.path(f"{CLASS_CONTRACTS}/{old}.json").exists():
        raise Refusal(f"{old} is registered in {CANONICAL_CLASSES} / {CLASS_CONTRACTS}; its key, contract "
                      "and class_gate allowances move in a class-reconciliation commit, not here")
    tie = {}
    table, proof = fold_evidence(ctx, old, new, tie)
    # A registered NEW has one shared header: a token rewrite would turn each
    # unit's OLD view into a private copy of it, so its units come prepared.
    # An unregistered global NEW is a token rewrite, unless its units come
    # prepared: a unit declaring both views cannot be token-rewritten (it would
    # declare NEW twice), so it comes declaring NEW's view alone, and the fold
    # holds it to OLD's compiled layout (fold_layout_baseline).
    by_layout = bool(prepared) and not nested and not registered_new and not tie
    by_hand = nested or (bool(prepared) and registered_new) or by_layout
    if tie and set(prepared or ()) != {tie["owner"]}:
        raise Refusal(f"the initializer route needs exactly the global's owner {tie['owner']} prepared: its view "
                      f"must declare {new}'s retail layout and constructor, so its initializer runs the row")
    va = f"0x{table + IMAGE_BASE:08X}"

    # A nested NEW is respelled in mangled names as its decorated scope
    # (`C@B@A`), and only where MSVC's name table stays put (see
    # nested_respelling_check); NEW is the C++ spelling everywhere else.
    mangled_new = class_scope(new)
    post = fold_access_respell(mangled_new, access) if access is not None else None
    frag = ClassToken(old, nested_respelling_check(old, new) if nested else None, post)
    token = class_token_re(old)
    rows, pins, datas = ctx.rows(), ctx.pins(), ctx.dicts(DATA_ROWS)
    names = [r["name"] for r in rows] + [p.get("name", "") for p in pins] + [d.get("name", "") for d in datas]
    scoped = sorted({n for n in names if n and frag.search(n)})
    for symbol in scoped:
        for a, b in class_spans(symbol, old):
            if symbol[b + 1:b + 2] != "@" or symbol[a - 2:a] == "?$":
                raise Refusal(f"{symbol} spells {old} nested in another scope or as a template: this mode folds "
                              "one global class only")
    for other in names:
        if other and leading_identifier(other, old):
            raise Refusal(f"{old} is also the identifier of {other}; a token rewrite would rename it too")
    for rel in ctx.grep_files(old, roots=FROZEN_KEYED):
        if rel == DATA_LEDGER:
            continue
        if frag.search((ctx.read(rel) or b"").decode("utf-8", errors="replace")):
            raise Refusal(f"{old} scopes a key in {rel} (frozen, shrink-only); renaming it needs a "
                          "Verifier-Change commit")

    texts = {}
    for rel in ctx.grep_files(old):
        data = ctx.read(rel)
        if data is not None:
            text = data.decode("utf-8", errors="surrogateescape")
            if token.search(text):
                texts[rel] = text
    refuse_vendored(ctx, set(texts), f"folding the type {old}")
    if len(texts) > max_files:
        raise Refusal(f"{len(texts)} files spell {old} (over --max-files {max_files}; text scope alone)")
    declarers = sorted(rel for rel, text in texts.items() if declares_type(name_metric.strip(text), old))
    if declarers and registered_new and not prepared:
        raise Refusal(f"{new} is registered in {CANONICAL_CLASSES}: the fold would turn {', '.join(declarers[:3])}'s "
                      f"class {old} into a private copy of {new} (class_gate); adopt {new}'s header there first, "
                      "or pass every unit spelling it as --prepared REL=FILE")
    by_object = object_referencers(ctx, set(scoped), word=old) if ctx.object_scan and scoped else set()
    touched = set(texts) | by_object
    refuse_vendored(ctx, touched, f"folding the type {old}")
    generated = sorted(p for p in touched if is_generated(p))
    if generated:
        raise Refusal(f"generated source(s) spell {old}: {', '.join(generated[:5])}; "
                      "the fold would leave them stale and they are never edited")
    if len(touched) > max_files:
        raise Refusal(f"{len(touched)} files spell {old} (over --max-files {max_files}; "
                      f"{len(texts)} text, {len(by_object)} object consumers)")

    owner = next((d for d in declarers if d in ctx.ledger_sources()), declarers[0] if declarers else "")
    if access is not None:
        proof = list(proof) + [f"the destructor family takes {access} access as requested (NEW's header "
                               "declares it; access is no retail fact)"]
    plan = Plan("class", old, new, "fold", "; ".join(proof) + (f"; {' '.join(evidence.split())}"
                                                                 if evidence.strip() else ""),
                owner, None, old_word=old, new_word=new, fold=table)

    # Ledgers. One name, one address: a respelled row or pin may not take a
    # name another address carries; a pin respelled into the very name of a
    # row (or pin) at its own address is that alias made redundant: dropped.
    renamed_row = {r["name"]: frag.sub(mangled_new, r["name"]) for r in rows if frag.search(r["name"])}
    created = set(renamed_row.values())
    taken = {r["name"] for r in rows}
    for name, respelled in renamed_row.items():
        if respelled in taken:
            raise Refusal(f"{name} would become {respelled}, which already names a row: this mode does not merge "
                          "two rows (an ICF alias pair keeps its two names)")
    rows_after = collections.defaultdict(set)           # row name after the fold -> addresses
    for row in rows:
        rows_after[renamed_row.get(row["name"], row["name"])].add(_rva(row.get("target_rva")))

    def respell_pin(name):
        return frag.sub(mangled_new, name) if frag.search(name) else name
    pins_after = collections.defaultdict(set)           # pin name after the fold -> addresses
    for pin in pins:
        pins_after[respell_pin(pin.get("name", ""))].add(_rva(pin.get("address")))
    for pin in pins:
        name, address = pin.get("name", ""), _rva(pin.get("address"))
        respelled = respell_pin(name)
        if respelled == name and name not in created:
            continue                                     # a pin the fold neither respells nor reaches
        others = (rows_after.get(respelled, set()) | pins_after.get(respelled, set())) - {address}
        if others:
            raise Refusal(f"pin {name} at {pin.get('address')} would read {respelled}, which also names "
                          f"0x{sorted(others)[0]:08X}: one name at two addresses")
    raw = ctx.read(SYMBOLS)
    if raw is not None:
        ledger_io.lf_terminator(raw, "symbols.csv")
        out, kept, first = [], set(), True
        for payload, term in ledger_io.split_records(raw):
            flds = ledger_io.fields(payload)
            if first or len(flds) < 2:
                first = False
                out.append(payload + term)
                continue
            name, address = flds[0], _rva(flds[1])
            respelled = respell_pin(name)
            if respelled != name or name in created:
                if address in rows_after.get(respelled, ()) or (respelled, address) in kept:
                    plan.dropped_pins.append((name, respelled, flds[1]))
                    continue
            kept.add((respelled, address))
            if respelled != name:
                plan.renamed_pins.append((name, respelled, flds[1]))
            text = payload.decode("utf-8")
            changed = frag.sub(mangled_new, text)        # the name and any mangled name in its notes
            out.append((changed.encode("utf-8") if changed != text else payload) + term)
        after = b"".join(out)
        if after != raw:
            plan.edit(ctx, SYMBOLS, after)
    for before, after in rewrite_ledger(ctx, plan, FUNCTIONS, "functions.csv", frag, mangled_new):
        at = _rva(before[2])
        if before[0] != after[0]:
            plan.renamed_rows.append((before[0], after[0], at))
        else:
            plan.notes_rows.append((before[0], at))
    for before, _after in rewrite_ledger(ctx, plan, BODY_OWNERS, "body_owners.csv", frag, mangled_new):
        plan.owner_rows.append((before[1], _rva(before[0])))
    data_index = {d.get("name"): data_rva(d) for d in datas}
    for before, after in rewrite_ledger(ctx, plan, DATA_ROWS, "data_rows.csv", frag, mangled_new):
        if before[0] != after[0]:
            if after[0] in data_index:
                raise Refusal(f"data row {before[0]} would become {after[0]}, which already names a data row")
            plan.renamed_data.append((before[0], after[0], data_index.get(before[0])))
    tombstoned = _tombstones(ctx)
    for _o, n, at in plan.renamed_rows:
        if (n, at) in tombstoned:
            raise Refusal(f"({n}, 0x{at:08X}) is tombstoned in deleted_rows.csv: {tombstoned[(n, at)][:120]}")
    lines = [tombstone_line(o, at, f"Renamed to {n} by tools/rename.py (fold: retail vftable {va})")
             for o, n, at in plan.renamed_rows + plan.renamed_data
             if at is not None and (o, at) not in tombstoned]
    if lines:
        plan.edit(ctx, DELETED, appended(ctx.read(DELETED), lines, header="name,target_rva,reason"))

    def carried(spelling):
        if "@" in spelling or spelling.startswith("?"):
            return frag.sub(mangled_new, spelling)
        names = spelling.split("::")
        return "::".join(new if i < len(names) - 1 and n == old else n for i, n in enumerate(names))
    carry_records(ctx, plan, carried)

    # Sources: OLD's views become NEW's; a unit that would then declare NEW
    # twice, or derive NEW from itself, needs its views reconciled first. A
    # token rewrite cannot declare a nested NEW's enclosing scopes (it cannot
    # tell a namespace from a class, nor how the unit declares them), so each
    # unit spelling OLD comes prepared, spelling OLD nowhere; the build and
    # commit_checks decide on its bytes as for every rename.
    headers = []
    if by_hand:
        prepared = dict(prepared or {})
        missing = sorted(rel for rel in touched if rel not in prepared)
        why = (f"a nested {new} needs its enclosing scopes declared in each unit, which a token rewrite cannot do"
               if nested else
               f"{new} is registered in {CANONICAL_CLASSES}, so each unit adopts its header instead of a "
               "token rewrite" if registered_new else
               f"the fold comes prepared, so each unit spelling {old} declares {new}'s view in place of its "
               f"{old} view (a token rewrite of one unit beside a prepared one is no single route)")
        if missing:
            raise Refusal(f"{', '.join(missing[:5])} spell{'s' if len(missing) == 1 else ''} {old}: {why}; "
                          "pass each as --prepared REL=FILE")
        for rel, data in sorted(prepared.items()):
            if token.search(data.decode("utf-8", errors="surrogateescape")):
                raise Refusal(f"prepared {rel} still spells {old}: the fold leaves no {old} behind")
        if by_layout:
            plan.fold_layouts = fold_layout_baseline(ctx, old, new, prepared, touched, registered)
        _batch_source_edits(ctx, plan, prepared)
    if tie:
        data = prepared[tie["owner"]]
        if token.search(data.decode("utf-8", errors="surrogateescape")) or tie["owner"] in touched:
            raise Refusal(f"{tie['owner']} spells {old}: the fold leaves no {old} behind, and the prepared owner is "
                          "its whole change")
        _batch_source_edits(ctx, plan, prepared)
        tie["ctor_new"] = frag.sub(mangled_new, tie["ctor"])
        plan.fold_tie = tie
    for rel in sorted(touched) if not by_hand else ():
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
        code = name_metric.strip(new_text)
        # A class head may carry `__declspec(novtable)` before the name.
        bodies = re.findall(r"\b(?:class|struct|union)\s+(?:__declspec\s*\(\s*\w+\s*\)\s*)*%s\b([^;{()]*)\{"
                            % re.escape(new), code)
        if len(bodies) > 1:
            raise Refusal(f"{rel} would declare class {new} twice (its {old} view and its {new} view): "
                          "reconcile the two views in that unit first")
        if any(re.search(r":[^{]*\b%s\b" % re.escape(new), clause) for clause in bodies):
            raise Refusal(f"{rel} would derive {new} from itself ({old} derives from {new} there): "
                          f"{old} and {new} are not one class in that view")
        plan.source_counts[rel] = counts
        plan.edit(ctx, rel, new_text.encode("utf-8", errors="surrogateescape"))
        if not rel.endswith(SOURCE_SUFFIXES) or rel not in ctx.ledger_sources():
            headers.append(rel)
    verify = {rel for rel in plan.source_counts if rel in ctx.ledger_sources()}
    if tie:
        verify.add(tie["owner"])
    renamed = {o for o, _, _ in plan.renamed_rows}
    verify |= {r["source"] for r in rows if r["name"] in renamed}
    verify |= {r["source"] for r in rows if (r["name"], _rva(r.get("target_rva"))) in set(plan.notes_rows)}
    renamed_data = {o for o, _, _ in plan.renamed_data}
    verify |= {d.get("source", "") for d in datas if d.get("name") in renamed_data}
    if headers:
        verify |= includers(ctx, headers, max_files)
    plan.verify = sorted(v for v in verify if v and not is_generated(v) and v in ctx.ledger_sources())
    if len(plan.verify) > max_files:
        raise Refusal(f"{len(plan.verify)} sources to verify (over --max-files {max_files})")
    if not plan.verify:
        raise Refusal(f"no ledger source compiles {old}; ./build.sh could not verify the fold")

    prose = len(word_re(old).findall(plan.after.get(FUNCTIONS, b"").decode("utf-8", errors="replace")))
    if prose:
        plan.warnings.append(f"functions.csv notes still spell {old} {prose} time(s) in prose (left as written)")
    dropped = {_rva(address) for _o, _n, address in plan.dropped_pins}
    plan.claims = sorted({at for _, _, at in plan.renamed_rows if at is not None} |
                         {at for _, at in plan.notes_rows if at is not None} |
                         {at for at in dropped if at is not None}) + [f"class:{old}", f"class:{new}"] + \
        sorted(f"file:{rel}" for rel in (prepared or {}))
    ledger_text = (ctx.read(DATA_LEDGER) or b"").decode("utf-8", errors="replace")
    if frag.search(ledger_text):
        plan.warnings.append(f"{DATA_LEDGER} (tool-written, protected) still spells {old} symbols; "
                             "tools/data_ledger.py regenerates it in a Verifier-Change commit")
    edited = set(plan.after) | {"reverse/re_attempts.log"}
    plan.mentions = sorted(set(ctx.grep_files(old, word=True, roots=("docs", "reverse"))) - edited)
    for rel in sorted(rel for rel in plan.source_counts if old in Path(rel).stem):
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


def parameter_parts(params):
    """`params` split on the commas that separate parameters, not every comma.

    A template argument list brings its own commas, so splitting on all of them
    cut `vector<const ModuleData *, allocator<...> > *units` in two and left the
    type's last word, `ModuleData`, looking like a parameter name;
    `prototype_param_spans` below refuses to read such a list positionally for
    the same reason. An arrow in a default argument is not a closing bracket,
    and a list whose brackets do not balance falls back to the plain split, so
    nothing that parsed before parses worse now.
    """
    parts, depth, start = [], 0, 0
    for i, ch in enumerate(params):
        if ch in "<([":
            depth += 1
        elif ch in ">)]":
            if ch == ">" and i and params[i - 1] == "-":
                continue
            depth -= 1
        elif ch == "," and depth == 0:
            parts.append(params[start:i])
            start = i + 1
    if depth != 0:
        return params.split(",")
    return parts + [params[start:]]


def parameters(params):
    """The names a parameter list declares (`int count` counts, unlike
    name_metric.param_names, which wants two non-keyword words)."""
    for part in parameter_parts(params):
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


_INCLUDE_HEADER_NAME = re.compile(r"^[ \t]*#[ \t]*(?:(?:include|include_next|import)[ \t]*<[^>\n]*>"
                                  r"|(?:error|warning)\b[^\n]*)")


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
        # an angle-bracket header name (`#include <stl/_algobase.c>`) is a path and
        # `#error`/`#warning` text is a message, not tokens: neither spells a macro
        # (quoted header names strip() already blanked)
        if pattern.search(_INCLUDE_HEADER_NAME.sub("", line)):
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
        _class_heads(bases, (ctx.read(path) or b"").decode("utf-8", "replace"))
    ctx._cache[key] = bases
    return bases


def _class_heads(bases, text):
    """Add every class head of `text` to `bases` (class_base_map's reading)."""
    code = name_metric.strip(text)
    for match in re.finditer(r"\b(?:class|struct)\s+([A-Za-z_]\w*)\s*(?:<[^{};]*?>\s*)?(?::([^{;]*))?\{", code):
        entry = bases.setdefault(match.group(1), set())
        if match.group(2):
            names = base_clause_names(match.group(2))
            entry.update([UNPARSED_BASE] if names is None else names)


def prepared_base_map(ctx, rel, prepared=None):
    """class_base_map of `rel`, read from its prepared bytes (and the headers
    those include) when `prepared` holds it, else from the tree."""
    data = (prepared or {}).get(rel)
    if data is None:
        return class_base_map(ctx, rel)
    text = data.decode("utf-8", "replace")
    header_closure(ctx, rel)                    # builds the basename index
    index = ctx._cache.get("_by_base", {})
    headers = set()
    for _delimiter, name in re.findall(r'^[ \t]*#[ \t]*include[ \t]*([<"])([^>"]+)[>"]', text, re.M):
        for path in index.get(Path(name).name.lower(), []):
            if path not in headers:
                headers.add(path)
                headers |= header_closure(ctx, path)
    bases = {}
    _class_heads(bases, text)
    for path in sorted(headers - {rel}):
        _class_heads(bases, (ctx.read(path) or b"").decode("utf-8", "replace"))
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


def _names_in(value, word):
    """How many dicts anywhere in `value` (parsed JSON) carry "name": word."""
    if isinstance(value, dict):
        return (value.get("name") == word) + sum(_names_in(v, word) for v in value.values())
    if isinstance(value, list):
        return sum(_names_in(v, word) for v in value)
    return 0


def respell_contract_member(ctx, plan, cls, member, new):
    """A member of a class registered in reverse/canonical_classes.csv is also a field of its
    contract: a top-level `fields` entry named `member` takes `new`. The contract's name for a
    field is the views' majority, decided before; it is left alone when it already says `new`,
    and the rename refuses when it names that field neither way (the contract would then
    disagree with the header it froze) or when `member` is spelled elsewhere in the contract
    (a nested member, a queue candidate) where a text edit cannot tell which it means."""
    if not any(r.get("class") == cls for r in ctx.dicts(CANONICAL_CLASSES)):
        return
    rel = f"{CLASS_CONTRACTS}/{cls}.json"
    data = ctx.read(rel)
    if data is None:
        return
    text = data.decode("utf-8")
    frozen = json.loads(text)
    fields = [f for f in frozen.get("fields", []) if isinstance(f, dict)]
    mine = [f for f in fields if f.get("name") == member]
    if not mine:
        theirs = [f for f in fields if f.get("name") == new]
        spelled_at = re.fullmatch(r"m_(?:field|x|unk)?_?([0-9A-Fa-f]{1,4})", member)
        if theirs and spelled_at and all(f.get("offset") != int(spelled_at.group(1), 16) for f in theirs):
            raise Refusal(f"{rel} names {new} at +0x{theirs[0].get('offset', 0):X}, but {member} spells "
                          f"+0x{int(spelled_at.group(1), 16):X}: another field's name")
        if theirs:
            plan.warnings.append(f"{rel} already names the field {new} (the views' majority); unchanged")
            return
        raise Refusal(f"{rel} names no field {member} or {new}: the contract decided another name for this "
                      f"member; rename it to the contract's name, or re-decide the contract "
                      f"(tools/class_contract.py --class {cls} --write) first")
    spelled = re.compile(r'"name"\s*:\s*"%s"' % re.escape(member))
    if len(spelled.findall(text)) != len(mine) or _names_in(frozen, member) != len(mine) or \
            len(re.findall(r"\b%s\b" % re.escape(member), text)) != len(mine):
        raise Refusal(f"{rel} spells {member} outside its top-level field; respell the contract by hand first")
    respelled = spelled.sub(f'"name": "{new}"', text)
    if any(f.get("name") == new for f in fields):
        raise Refusal(f"{rel} already names another field {new}")
    plan.edit(ctx, rel, respelled.encode("utf-8"))


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
    respell_contract_member(ctx, plan, cls, member, new)
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
                                timeout=GIT_TIMEOUT, env=trusted_env())
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


def pick_function(code, function, *, functions=None):
    """The name_metric.functions_in entry `function` names: its exact scope
    (`Class::method`, `Class::method#2` for the second overload in the file),
    or a bare method name when one function in the file has it."""
    found = name_metric.functions_in(code) if functions is None else functions
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


def _comma_local_declarations(body):
    """Extra declarators in simple primitive comma declarations.

    Deliberately limited to ordinary primitive declarations and simple literal
    initializers. Template/function declarators and comma expressions need a
    fuller C++ parser; this helper never guesses their binding.
    """
    primitive = {"int", "float", "double", "char", "short", "long", "bool", "wchar_t"}
    extra = []
    for first in name_metric.LOCAL.finditer(body):
        if first.group(1) not in primitive:
            continue
        stop = body.find(";", first.end(2))
        if stop < 0:
            continue
        tail = body[first.end(2):stop]
        if "," not in tail or re.search(r"[(){}<>?:]", tail):
            continue
        parts = tail.split(",")
        if not re.fullmatch(r"\s*(?:=\s*(?:[-+]?\d+(?:\.\d+)?[fFuUlL]*|NULL|true|false))?\s*", parts[0]):
            continue
        offset = first.end(2) + len(parts[0]) + 1
        for part in parts[1:]:
            match = re.fullmatch(r"\s*[*&]*\s*([A-Za-z_]\w*)\s*"
                r"(?:=\s*(?:[-+]?\d+(?:\.\d+)?[fFuUlL]*|NULL|true|false))?\s*", part)
            if match is None or match.group(1) in name_metric.KEYWORDS:
                break
            extra.append((match.group(1), offset + match.start(1), first.group(2)))
            offset += len(part) + 1
    return extra


def scoped_local_names(body):
    """Local inventory, including conservative primitive comma declarators."""
    return name_metric.local_names(body) + [name for name, _at, _first in _comma_local_declarations(body)]


def local_scopes(body, name, *, include_comma=True):
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
    for declared, at, first in _comma_local_declarations(body) if include_comma else ():
        if declared != name:
            continue
        first_scopes = local_scopes(body, first, include_comma=False)
        if len(first_scopes) == 1 and first_scopes[0][0] < at <= first_scopes[0][1]:
            scopes.append((at, first_scopes[0][1]))
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
    return any(inferred_record(row.get("record")) == record and row.get("source") == rel
               and row.get("old") == land.target and row.get("new") == land.current
               and row.get("outer_sha256") == current for row in ctx.dicts(NAME_BINDINGS))


def plan_scoped(kind, ctx, source, name, new, basis, evidence, *, function=None, rva=None, max_files=25,
                local_binding=False, expected_source_sha=None):
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
    raw = ctx.read(rel)
    if evidence.strip().startswith("direct:") and (not isinstance(expected_source_sha, str)
            or not re.fullmatch(r"[0-9a-f]{64}", expected_source_sha)):
        raise Refusal("direct scoped plans require the reviewed source SHA-256 fingerprint")
    if expected_source_sha is not None and ctx.resolution_source_sha(rel) != expected_source_sha:
        raise Refusal(f"{rel} changed since the direct naming batch was prepared; serve it again")
    cached = ctx._cache.setdefault("_scoped_sources", {}).get(rel)
    if cached is None or cached[0] != raw:
        text = raw.decode("utf-8", errors="surrogateescape")
        code = name_metric.strip(text)
        cached = (raw, text, code, name_metric.functions_in(code))
        ctx._cache["_scoped_sources"][rel] = cached
    _raw, text, code, functions = cached
    scope, start, end, params = pick_function(code, function, functions=functions)
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
        if evidence.strip().startswith("direct:") and name in scoped_local_names(body):
            raise Refusal(f"{name} is shadowed by a local declaration in {scope}; its bindings need separate proof")
    else:
        if name in set(parameters(params)):
            raise Refusal(f"{name} is a parameter of {scope}, not a local")
        if name not in set(scoped_local_names(body)):
            raise Refusal(f"{name} is not a local of {scope}")
        if evidence.strip().startswith("direct:") and len(local_scopes(body, name)) != 1:
            raise Refusal(f"{name} has ambiguous or unsupported declarations in {scope}")
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


def plan_param(ctx, source, name, new, basis, evidence, *, function=None, rva=None, max_files=25,
               expected_source_sha=None):
    return plan_scoped("param", ctx, source, name, new, basis, evidence,
                       function=function, rva=rva, max_files=max_files, expected_source_sha=expected_source_sha)


def plan_local(ctx, source, name, new, basis, evidence, *, function=None, rva=None, max_files=25, local_binding=False,
               expected_source_sha=None):
    return plan_scoped("local", ctx, source, name, new, basis, evidence,
                       function=function, rva=rva, max_files=max_files, local_binding=local_binding,
                       expected_source_sha=expected_source_sha)


def scoped_entry_key(entry):
    return json.dumps(entry, sort_keys=True, separators=(",", ":"))


def plan_scoped_set(ctx, source, entries, expected_source_sha, basis="inferred", evidence="", prepared=None):
    """Plan reviewed scoped names against one original source, then compose.

    Each entry retains the ordinary scoped planner's binding, protection and
    capture checks. Token-aligned edits are combined simultaneously, never
    progressively changing the context a later entry was reviewed against.
    Entries that cannot be proved safe are reported without discarding peers.
    """
    if basis != "inferred" or not isinstance(entries, list) or not entries:
        raise Refusal("scoped-set needs a nonempty list of direct inferred scoped entries")
    rel = (source or "").replace("\\", "/")
    raw = ctx.read(rel)
    if (not isinstance(expected_source_sha, str)
            or not re.fullmatch(r"[0-9a-f]{64}", expected_source_sha)
            or raw is None or ctx.resolution_source_sha(rel) != expected_source_sha):
        raise Refusal(f"{rel} changed since the direct naming batch was prepared; serve it again")
    text = raw.decode("utf-8", errors="surrogateescape")
    original_tokens = list(name_metric.WORD.finditer(text))
    plan = Plan("scoped-set", "scoped identifiers", "reviewed identifiers", basis, evidence, rel, None)
    plan.scoped_refused = {}
    plan.scoped_plans = []
    edits, seen_bindings, targets = {}, set(), set()
    history = {NAME_BASIS: [], NAME_BINDINGS: []}
    for index, entry in enumerate(entries):
        try:
            if not isinstance(entry, dict) or entry.get("kind") not in ("param", "local"):
                raise Refusal("scoped-set entries may rename only parameters and locals")
            if not isinstance(entry.get("evidence"), str) or not entry["evidence"].startswith("direct:"):
                raise Refusal("scoped-set entries require direct: scoped review evidence")
            if set(entry) - {"kind", "function", "name", "new", "evidence", "local_binding"}:
                raise Refusal("unknown scoped-set entry fields")
            candidate = (prepared or {}).get(scoped_entry_key(entry))
            if isinstance(candidate, str):
                raise Refusal(candidate)
            if candidate is None:
                candidate = plan_scoped(entry["kind"], ctx, rel, entry.get("name"), entry.get("new"),
                    basis, entry["evidence"], function=entry.get("function"),
                    local_binding=entry.get("local_binding", entry["kind"] == "local"),
                    expected_source_sha=expected_source_sha)
            binding = candidate.old
            target = candidate.new
            if binding in seen_bindings or target in targets:
                raise Refusal("duplicate binding or competing final name in scoped-set")
            changed = candidate.after[rel].decode("utf-8", errors="surrogateescape")
            tokens = list(name_metric.WORD.finditer(changed))
            if len(tokens) != len(original_tokens):
                raise Refusal("scoped-set rewrite is not an identifier-only token replacement")
            candidate_edits = {}
            before_at = after_at = 0
            for original, replacement in zip(original_tokens, tokens):
                if text[before_at:original.start()] != changed[after_at:replacement.start()]:
                    raise Refusal("scoped-set rewrite changes non-identifier text")
                if original.group() != replacement.group():
                    if original.group() != entry["name"] or replacement.group() != entry["new"]:
                        raise Refusal("scoped-set rewrite changes an unrelated identifier")
                    span = (original.start(), original.end())
                    if span in edits:
                        raise Refusal("overlapping scoped-set binding edits")
                    candidate_edits[span] = replacement.group()
                before_at, after_at = original.end(), replacement.end()
            if text[before_at:] != changed[after_at:]:
                raise Refusal("scoped-set rewrite changes trailing non-identifier text")
            if not candidate_edits:
                raise Refusal("scoped-set entry has no identifier edits")
            additions = {}
            for ledger in history:
                if ledger not in candidate.after:
                    continue
                old = ctx.read(ledger)
                new = candidate.after[ledger]
                if old is not None:
                    if not new.startswith(old):
                        raise Refusal("scoped-set planner changed existing naming history")
                    additions[ledger] = new[len(old):]
                else:
                    # Ordinary plans create a header; retain it once, not per entry.
                    _header, separator, row = new.partition(b"\n")
                    if not separator:
                        raise Refusal("scoped-set planner did not create a complete history row")
                    additions[ledger] = row
            if set(candidate.after) - {rel, NAME_BASIS, NAME_BINDINGS}:
                raise Refusal("scoped-set planner touched paths outside its source and naming history")
            edits.update(candidate_edits)
            seen_bindings.add(binding)
            targets.add(target)
            for ledger, added in additions.items():
                history[ledger].append(added)
            plan.claims.extend(candidate.claims)
            plan.scoped_plans.append((index, candidate))
        except Refusal as error:
            plan.scoped_refused[index] = str(error)
    if not plan.scoped_plans:
        raise Refusal("no scoped-set entries passed planning: " + "; ".join(plan.scoped_refused.values()))
    for (start, end), replacement in sorted(edits.items(), reverse=True):
        text = text[:start] + replacement + text[end:]
    plan.edit(ctx, rel, text.encode("utf-8", errors="surrogateescape"))
    for ledger, rows in history.items():
        if rows:
            header = NAME_BASIS_HEADER if ledger == NAME_BASIS else NAME_BINDINGS_HEADER
            initial = ctx.read(ledger)
            if initial is None:
                initial = (header + "\n").encode("utf-8")
            plan.edit(ctx, ledger, initial + b"".join(rows))
    plan.verify = [rel]
    plan.claims = claim_keys(plan)
    plan.source_counts[rel] = {"scoped_names": len(plan.scoped_plans), "code": len(edits)}
    plan.scoped_count = len(plan.scoped_plans)
    plan.warnings.extend(f"entry {index}: {reason}" for index, reason in plan.scoped_refused.items())
    return plan


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
            "member": plan_member, "param": plan_param, "local": plan_local, "scoped-set": plan_scoped_set}


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
    ctx._build_diagnostics = ""
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
    # Per-context diagnostics survive wrappers without leaking a previous
    # invocation's output or relying on mutable attributes on a callable.
    ctx._build_diagnostics = output
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
        data = _unb64(record.get("moved_bytes", {}).get(old))
        if ctx.path(new).exists() and not ctx.path(old).exists():
            moved = subprocess.run(["git", "-C", str(ctx.root), "mv", "--", new, old], capture_output=True)
            if moved.returncode == 0:
                if data is not None and ctx.path(old).read_bytes() != data:
                    ctx.path(old).write_bytes(data)          # a moved file the plan also edited
                continue
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
    there, and a failed run undoes it). The copy lives inside the git directory, where
    git_trust accepts an index, and goes with the run."""
    found = subprocess.run(["git", "-C", str(ctx.root), "rev-parse", "--git-path", "index"],
                           capture_output=True, text=True, env=trusted_env())
    git_dir = subprocess.run(["git", "-C", str(ctx.root), "rev-parse", "--absolute-git-dir"],
                             capture_output=True, text=True, env=trusted_env())
    if found.returncode or git_dir.returncode:
        yield None
        return
    source = ctx.root / found.stdout.strip()
    with tempfile.TemporaryDirectory(prefix="rename-index-", dir=git_dir.stdout.strip()) as folder:
        private = Path(folder) / "index"
        if source.exists():
            private.write_bytes(source.read_bytes())
        env = trusted_env({"GIT_INDEX_FILE": str(private), "RENAME_SCRATCH": folder})
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
    if HEADER_QUEUE in paths:
        # the hook's debt check: a header_queue.tsv row may leave only by its verdict or a recorded move
        jobs["header_debt"] = ("repair_queue", ["verify-removed", "--defer-missing"], None)
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
        for rel in plan.removed:
            if ctx.path(rel).exists():
                ctx.path(rel).unlink()
        ctx._build_diagnostics = ""
        if not verify(ctx, plan.verify):
            error = VerifyFailed(f"verification failed for {plan.old} -> {plan.new}; every file restored")
            error.diagnostics = ctx._build_diagnostics
            error.verify_sources = list(plan.verify)
            raise error
        if plan.to_class:
            # The slot the rebuilt installer units' vftable names is the proof
            # a prepared source can change; read it from the fresh objects.
            slot_problems = to_class_slot_problems(ctx, plan.to_class, current=False)
            if slot_problems:
                raise VerifyFailed(f"the rebuilt vftable does not prove {plan.old} -> {plan.new}: "
                                   f"{slot_problems[0][:300]}; every file restored")
            if plan.to_class.get("bases"):
                record_base_reports(ctx, plan)
            static_problems = to_class_static_problems(ctx, plan.to_class)
            if static_problems:
                raise VerifyFailed(f"the rebuilt object does not prove {plan.old} -> {plan.new}: "
                                   f"{static_problems[0][:300]}; every file restored")
        if plan.this_cv:
            # A `this`-cv respell overrides the base virtual only if the rebuilt
            # installers' vftable names the row in its retail slot.
            slot_problems = to_class_slot_problems(ctx, plan.this_cv, current=False)
            if slot_problems:
                raise VerifyFailed(f"the rebuilt vftable does not prove {plan.old} -> {plan.new}: "
                                   f"{slot_problems[0][:300]}; every file restored")
        if plan.identity:
            # The rebuilt objects' bindings are the proof: every reference of a
            # respelled row binds its retail owner, and no touched row gains a
            # wrong binding.
            identity_problems_found = (retail_identity_problems if plan.identity.get("retail") else identity_problems)(
                ctx, plan.identity)
            if identity_problems_found:
                raise VerifyFailed(f"the code-identity check does not prove {plan.old} -> {plan.new}: "
                                   f"{identity_problems_found[0][:300]}; every file restored")
        if plan.fold_tie:
            tie_problems = fold_tie_problems(ctx, plan.fold_tie)
            if tie_problems:
                raise VerifyFailed(f"the rebuilt owner does not prove {plan.old} -> {plan.new}: "
                                   f"{tie_problems[0][:300]}; every file restored")
        if plan.fold_layouts:
            layout_problems = fold_layout_problems(ctx, plan.fold_layouts)
            if layout_problems:
                raise VerifyFailed(f"the rebuilt units do not keep {plan.old}'s layout as {plan.new}: "
                                   f"{layout_problems[0][:300]}; every file restored")
        if plan.retype:
            retype_problems = retype_object_problems(ctx, plan.retype)
            if retype_problems:
                raise VerifyFailed(f"the rebuilt objects do not prove {plan.old} -> {plan.new}: "
                                   f"{retype_problems[0][:300]}; every file restored")
        if plan.registered:
            stale = registered_object_problems(ctx, plan)
            if stale:
                raise VerifyFailed(f"the rebuilt objects do not prove {plan.old} -> {plan.new}: "
                                   f"{stale[0][:300]}; every file restored")
            if plan.registered.get("prepared"):
                copies = prepared_attribution_problems(ctx, plan)
                if copies:
                    raise VerifyFailed(f"a prepared unit keeps its own {plan.new}: {copies[0][:300]}; "
                                       "every file restored")
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
        if not result.returncode and ctx.path(old).read_bytes() != plan.moved_bytes[old]:
            ctx.path(old).write_bytes(plan.moved_bytes[old])     # a moved file the plan also edited
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
            raise ClaimConflict(error.refused)
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
        raise ClaimConflict(others)
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

        def resolution_source_sha(self, rel):
            data = ctx.read(rel)
            return hashlib.sha256(data).hexdigest() if data is not None else ""

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
    class_symbols = ([row["name"] for row in ctx.rows()] +
                     [pin.get("name", "") for pin in ctx.pins()] +
                     [row.get("name", "") for row in ctx.dicts(DATA_ROWS)]) if "class" in kinds else []
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
        elif kind == "class":
            old, new = kwargs.get("name"), kwargs.get("new")
            if isinstance(old, str) and IDENT.fullmatch(old):
                fragment = type_fragment_re(old)
                symbols.update(name for name in class_symbols if name and fragment.search(name))
                terms.add(old)
            if isinstance(new, str):
                terms.add(new)
            # Class member identifiers can be very generic (get, slot4, etc.).
            # Warm their exact object symbols, not broad source-word searches.
            continue
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
        import claims
        # Plans spell scopes as file:PATH/class:NAME; the coordination API
        # returns canonical file/<hash>/class/<name> keys. Journals, retained
        # leases and release decisions must all compare the same representation.
        keys = list(dict.fromkeys(claims.key_of(key) for key in keys))
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

    def keep(self, keys):
        import claims
        self.kept.update(claims.key_of(key) for key in keys)

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
    diagnostics: str = ""                    # captured verifier output, when available
    planning_seconds: float = 0.0
    claims_seconds: float = 0.0
    apply_verify_seconds: float = 0.0


def _batch_source_edits(ctx, plan, edits):
    """Journal owned C++ preparations before name planning, without writing.

    This does not admit new sources or ledger edits. Every prepared source has
    matched rows, is claimed with the union and goes through its normal gates.
    At most ctx.max_prepared sources (PREPARED_DEFAULT unless --max-prepared
    raises it): a respell whose callers cannot be split across commits (a unit
    left behind calls a symbol no row names) stays one transaction, with the
    same per-unit byte gate, rollback and object checks however many it holds.
    """
    if edits is None:
        return False
    limit = getattr(ctx, "max_prepared", PREPARED_DEFAULT)
    if not isinstance(edits, dict) or len(edits) > limit:
        raise Refusal(f"source_edits must map at most {limit} existing Code C++ paths to bytes"
                      + (f" ({len(edits)} given; --max-prepared N raises the limit for one transaction, up to "
                         f"{PREPARED_CEILING} without --beyond-prepared-ceiling)" if isinstance(edits, dict) else ""))
    if not edits:
        return False
    if any(not isinstance(rel, str) or not isinstance(data, bytes) for rel, data in edits.items()):
        raise Refusal("source_edits needs repository-relative string paths and bytes")
    paths = sorted(edits)
    for rel in paths:
        parsed = PurePosixPath(rel)
        if (not rel.startswith("Code/") or not rel.endswith(".cpp") or ".." in parsed.parts
                or parsed.as_posix() != rel or "\\" in rel):
            raise Refusal(f"source preparation must be an existing Code C++ source: {rel}")
        path = ctx.path(rel)
        if (path.is_symlink() or not path.is_file()
                or not path.resolve().is_relative_to((ctx.root / "Code").resolve())):
            raise Refusal(f"source preparation is missing or outside the Code tree: {rel}")
        if is_generated(rel):
            raise Refusal(f"generated source {rel} cannot be prepared by a rename")
        refuse_vendored(ctx, [rel], "preparing a rename source")
        if rel not in ctx.ledger_sources():
            raise Refusal(f"source preparation has no matched rows to verify: {rel}")
    tracked = set(ctx.git("ls-files", "--", *paths).splitlines())
    if set(paths) - tracked:
        raise Refusal("source preparation is untracked: " + ", ".join(sorted(set(paths) - tracked)))
    # A source preparation is supplied in memory, not layered over somebody's
    # existing staged or unstaged edit. New miniature test trees have no HEAD.
    base = ["HEAD"] if ctx.git("rev-parse", "--verify", "--quiet", "HEAD").strip() else []
    dirty = ctx.git("diff", "--name-only", *base, "--", *paths).splitlines()
    if dirty:
        raise Refusal("source preparation requires clean source paths: " + ", ".join(dirty))
    for rel in paths:
        plan.edit(ctx, rel, edits[rel])
        plan.source_counts[rel] = {"prepared": 1}
        plan.claims.append("file:" + rel)
    plan.verify = sorted(set(plan.verify) | set(paths))
    return True


def run_batch(ctx, requests, *, claim=True, verify=build_verify, checks=ledger_checks, session=None,
              source_edits=None, scoped_plans=None):
    """Plan each name normally, then claim/apply/verify the complete union.

    Planning refusals affect only their request. A failed combined transaction
    is restored by apply_rename and returned to the caller for smaller retries.
    Unexpected errors and interrupts propagate after recovery and claim release.
    Source moves are excluded. Optional source_edits puts owned preparatory C++
    changes in the same journal, claims, staging and normal byte verification.
    Such preparations require every coupled request to plan successfully.
    scoped_plans supplies dependency-validated preview candidates only for scoped
    batches; composition, claims, journal, checks and verification are unchanged.
    """
    from portable_lock import lock, unlock

    batch_started = time.perf_counter()
    refuse_pending_journal(ctx)
    requests = list(requests)
    if scoped_plans is not None and any(kind != "scoped-set" for kind, _ in requests):
        raise Refusal("preview candidates require a scoped-set-only batch")
    result = RunBatchResult()
    own_session = session is None
    session = session or RunBatchSession(ctx)
    reads = {}
    searches = {}
    git_searches = {}
    combined = Plan("run-batch", "approved names", "readable names", "inferred", "", None, None)
    prepared_base = {}

    class View(Context):
        def read(self, rel):
            data = combined.after[rel] if rel in combined.after else ctx.read(rel)
            reads[rel] = data
            return data

        def resolution_source_sha(self, rel):
            # Approval fingerprints must cover the proposed starting source,
            # not the older disk bytes, before this batch's identifier edits.
            data = prepared_base[rel] if rel in prepared_base else ctx.read(rel)
            reads[rel] = data
            return hashlib.sha256(data).hexdigest() if data is not None else ""

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
                if scoped_plans is not None:
                    scoped_plans.begin()
                prepared_sources = _batch_source_edits(ctx, combined, source_edits)
                if prepared_sources:
                    prepared_base.update({rel: combined.after[rel] for rel in source_edits})
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
                        # The batch's union carries no plan.identity, so apply_rename would run none of
                        # an identity respell's object checks, and nothing would prove a forced move.
                        if kwargs.get("forced_moves"):
                            raise Refusal("a run batch does not take --forced-move")
                        if kwargs.get("identity"):
                            raise Refusal("a run batch does not take an identity respell: "
                                          "tools/rename.py function --respell --identity, on its own")
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
                                valid = all(object_referencers(view, symbols, word=word) == found
                                            for symbols, found, word in object_queries)
                        if valid:
                            plan = cached[0]
                        else:
                            reads.clear()
                            searches.clear()
                            git_searches.clear()
                            view._cache.clear()
                            view._object_queries = []
                            scoped = scoped_plans.get(view, kwargs) if kind == "scoped-set" and scoped_plans else None
                            plan = plan_rename(kind, ctx=view, **kwargs,
                                **({"prepared": scoped} if scoped is not None else {}))
                            session.prepared[key] = (plan, dict(reads), dict(searches), dict(git_searches),
                                                     list(view._object_queries), session.object_generation)
                            del view._object_queries
                        if plan.moves:
                            raise Refusal("a run batch may not move source files")
                        if plan.to_class:
                            raise Refusal("a run batch does not take function --to-class moves")
                        if plan.identity:
                            raise Refusal("a run batch does not take an identity plan: its object checks would not run")
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
                if prepared_sources and (result.refused or not result.plans):
                    result.failure = Refusal("source preparations require every coupled rename to plan; "
                                             "nothing was applied")
                    result.planning_seconds = time.perf_counter() - batch_started
                    return result
                if not result.plans:
                    result.planning_seconds = time.perf_counter() - batch_started
                    return result
                combined.claims = claim_keys(combined)
                for _, plan in result.plans:
                    print(plan.report())
                name_count = sum(getattr(plan, "scoped_count", 1) for _, plan in result.plans)
                print(f"rename: run batch of {name_count} names; "
                      f"one verification of {len(combined.verify)} source(s).", flush=True)
                result.planning_seconds = time.perf_counter() - batch_started
                claimed = None
                try:
                    problems = pin_preflight(ctx, combined)
                    if problems:
                        message = "pin_admission: " + "; ".join(problems)
                        result.suspects = diagnostic_suspects(result.plans, problems)
                        raise VerifyFailed(message)
                    claim_started = time.perf_counter()
                    claimed = session.acquire(combined.claims, claim)
                    result.claims_seconds = time.perf_counter() - claim_started
                    verify_started = time.perf_counter()
                    try:
                        apply_rename(combined, ctx=ctx, verify=verify, checks=checks, claimed=claimed)
                    finally:
                        result.apply_verify_seconds = time.perf_counter() - verify_started
                except (Refusal, VerifyFailed) as exc:
                    if not result.suspects:
                        result.suspects = diagnostic_suspects(result.plans, getattr(exc, "problems", [str(exc)]))
                    result.failure = exc
                    result.diagnostics = getattr(exc, "diagnostics", "")
                    print("rename: batch timing " + json.dumps(dict(
                        planning=round(result.planning_seconds, 3),
                        claims=round(result.claims_seconds, 3),
                        apply_verify=round(result.apply_verify_seconds, 3))), flush=True)
                    return result
                except BaseException:
                    raise
                session.keep(combined.claims)
                if claimed.new:
                    print("rename: claims kept until the rename is pushed; then run: python3 tools/claims.py release "
                          + " ".join(map(claim_label, claimed.new)))
                print(f"rename: run batch verified OK ({name_count} names, "
                      f"{len(combined.verify)} source(s)).")
                print("rename: batch timing " + json.dumps(dict(
                    planning=round(result.planning_seconds, 3),
                    claims=round(result.claims_seconds, 3),
                    apply_verify=round(result.apply_verify_seconds, 3))), flush=True)
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
    common.add_argument("--max-prepared", type=int, default=PREPARED_DEFAULT, metavar="N",
                        help=f"accept up to N --prepared sources in the one transaction (default "
                             f"{PREPARED_DEFAULT}; above {PREPARED_CEILING} needs --beyond-prepared-ceiling)")
    common.add_argument("--beyond-prepared-ceiling", action="store_true",
                        help=f"with --max-prepared above {PREPARED_CEILING}: the larger transaction is deliberate")
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
    record = kinds.add_parser("verify-record", help="the gates' check: target's class,OLD,NEW name_basis.csv "
                                                    "record is an approval for OLD's registration at base")
    record.add_argument("--root", type=Path, default=ROOT, help="the repository the revisions belong to")
    record.add_argument("--base", required=True, help="the revision the rename was planned on (HEAD)")
    record.add_argument("--target", required=True, help="the revision holding the rename ('' is the index)")
    record.add_argument("--old", required=True)
    record.add_argument("--new", required=True)
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
                          help="new identifier, or the full mangled name (identifier change only, or any "
                               "spelling with --respell); required unless --virtual")
    function.add_argument("--old", help="the current mangled name, when several share the RVA")
    function.add_argument("--virtual", action="store_true",
                          help="respell the row non-virtual -> virtual (QAE->UAE, IAE->MAE, AAE->EAE), keeping "
                               "identifier, parameters and return type; refused unless a retail vtable slot of "
                               "the row's class (or of a class a view derives from it) holds the address")
    function.add_argument("--access", choices=sorted(VIRTUAL_CODE_OF),
                          help="with --virtual: the virtual member's access instead of the row's "
                               "(protected: QAE->MAE); each in-class declaration is put under that label")
    function.add_argument("--to-class", metavar="CLASS",
                          help="move a placeholder-class member into CLASS as its virtual --new (identifier or "
                               "full mangled name); no --basis: refused unless a table CLASS's own constructor "
                               "or destructor rows install holds the address in one slot and CLASS's compiled "
                               "vftable names the new symbol there")
    function.add_argument("--prepared", action="append", default=[], metavar="REL=FILE",
                          help="with --to-class: the proposed bytes of Code source REL, read from FILE "
                               "(repeatable): the definition under CLASS and any caller of the old member; "
                               "with --virtual: a unit whose class view must change shape (not only gain "
                               "`virtual`) for the respelled member to compile to retail's bytes")
    function.add_argument("--respell", action="store_true",
                          help="--new is the row's whole mangled name even where it differs beyond the "
                               "identifier (a changed return type, parameter or template argument); needs "
                               "--prepared for every unit that names it, runs no word rewrite, and is "
                               "refused while an alias pin shares the address")
    function.add_argument("--also", action="append", default=[], metavar="RVA=NEW",
                          help="with --to-class: move another slot of the same retail table in the same plan "
                               "(repeatable); a table whose slots are all still rowed under other placeholders "
                               "is proved only by moving them together; with --respell --identity: respell "
                               "another row in the same plan (NEW is its whole mangled name); with a this-cv "
                               "--respell: another slot of the same retail table, each proved by its base "
                               "virtual and all checked after one build")
    function.add_argument("--identity", action="store_true",
                          help="with --respell: respell a placeholder-typed compiler-spelled row (operator, "
                               "special member, template member) by the naming route, --basis inferred "
                               "--evidence 'agree:<id> ...' (one approval per row), gated by code identity: "
                               "refused unless the check reports a wrong binding before and, after ./build.sh, "
                               "every reference of every respelled row binds its retail owner directly")
    function.add_argument("--move-to", metavar="TU",
                          help="with --respell --identity: also move the respelled rows into their approved "
                               "TU (reverse/tu_map.csv); every row of the owner source must move, its "
                               "path-keyed columns follow and the emptied source is deleted; with --basis "
                               "retail, only the rows --move-rows names move")
    function.add_argument("--move-rows", default="", metavar="RVA[,RVA...]",
                          help="with --basis retail and --move-to: move only these rows of the family, each "
                               "approved for that TU; their owner source stays")
    function.add_argument("--forced-move", action="append", default=[], metavar="RVA:SOURCE",
                          help="with --basis retail: a row the family's reviewed forced_moves names, which this "
                               "respell forces out of a file it rewrites, with no unit in reverse/tu_map.csv, moves "
                               "to SOURCE on the objects' proof and is recorded in reverse/forced_row_moves.csv; "
                               "it approves nothing (docs/consolidation.md)")
    data = kinds.add_parser("global", parents=[common],
                            help="respell one reverse/data_rows.csv global and every consumer")
    data.add_argument("--name", required=True, help="the global's mangled name, or its bare identifier")
    data.add_argument("--new", required=True,
                      help="new identifier, or the full mangled name (identifier change only); with --retype "
                           "the full mangled name of the retyped global (same identifier)")
    data.add_argument("--retype", metavar="TYPE",
                      help="change the global's C++ type (e.g. 'unsigned int [3]') and keep its identifier: every "
                           "declaration, the data row, pins, notes and the data_ledger.csv row follow; takes "
                           "--size and --evidence, no --basis")
    data.add_argument("--size", help="with --retype: the new extent in bytes, proven by the compiler and retail")
    data.add_argument("--initializer", help="with --retype: the definition's initializer when retail's bytes "
                                            "over the new extent are not all zero")
    data.add_argument("--prepared", action="append", default=[], metavar="REL=FILE",
                      help="with --retype: the proposed bytes of a Code source whose uses must change shape for "
                           "the new type (repeatable); every source is still byte-verified")
    data.add_argument("--address", help="with --retype: the new start, an RVA below the row's, over unrowed space, as "
                                        "an entry of tools/retail_identity.py's EXTENTS spells out")
    data.add_argument("--absorb", action="append", default=[], metavar="MANGLED",
                      help="with --retype: a row of the same unit wholly inside the extent, whose readers --prepared "
                           "rewrites as offsets, as an EXTENTS entry spells out (repeatable)")
    data.add_argument("--model", help="with --retype: who lands the data row a global only data_ledger.csv owns gains")
    unit = kinds.add_parser("file", parents=[common],
                            help="git mv one Code/ unit within its directory, with its path-keyed rows")
    unit.add_argument("--source", required=True, help="the unit's repo-relative path")
    unit.add_argument("--new", required=True, help="new file name or stem (same directory), or full path")
    klass = kinds.add_parser("class", parents=[common],
                             help="respell one class/struct/union/enum token in every name and view")
    klass.add_argument("--name", help="the type's current identifier (required unless --fold)")
    klass.add_argument("--new", help="the new identifier (required unless --fold)")
    klass.add_argument("--fold", metavar="OLD",
                       help="fold placeholder class OLD into --into NEW, the class its retail vftable already "
                            "names (no --basis: retail is the evidence; see docs/naming.md)")
    klass.add_argument("--into", metavar="NEW", help="with --fold: the class name OLD folds into (A::B::C for a "
                                                     "nested class)")
    klass.add_argument("--prepared", action="append", default=[], metavar="REL=FILE",
                       help="with --fold into a nested class, or with --merge-existing: the proposed bytes of "
                            "Code source REL, read from FILE (repeatable); with --fold, for every unit spelling OLD")
    klass.add_argument("--access", choices=sorted(VIRTUAL_CODE_OF),
                       help="with --fold and --prepared: the access the folded virtual destructor family takes "
                            "(the registered NEW header's declaration), instead of the placeholder rows'")
    klass.add_argument("--merge-existing", action="store_true",
                       help="with --name on a registered placeholder: NEW is already spelled as a type (forward "
                            "declarations, views, parameter types) and owns no row, pin or definition; a "
                            "canonical basis proves OLD is that class (see docs/naming.md)")
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
    if args.kind == "verify-record":
        try:
            which = verify_record(args.root, args.base, args.target, args.old, args.new)
        except Refusal as why:
            print(f"rename: verify-record: {args.old} -> {args.new}: {why}", file=sys.stderr)
            return 1
        print(f"rename: verify-record: {args.old} -> {args.new}: {which} approval verified")
        return 0
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
    to_class = args.kind == "function" and args.to_class
    fold = args.kind == "class" and (args.fold is not None or args.into is not None)
    respell = args.kind == "function" and getattr(args, "respell", False)
    identity = args.kind == "function" and getattr(args, "identity", False)
    if args.kind == "function" and (identity or args.move_to) and not respell:
        parser.error("--identity and --move-to go with --respell")
    if args.kind == "function" and args.move_to and not identity:
        parser.error("--move-to goes with --respell --identity")
    if args.kind == "function" and args.prepared and not (to_class or args.virtual or respell):
        parser.error("--prepared goes with --to-class, --virtual or --respell")
    if respell and (to_class or args.virtual):
        parser.error("--respell is its own mode: not with --to-class or --virtual")
    if respell and not args.prepared:
        parser.error("--respell needs --prepared sources for every unit that names the row")
    if args.kind == "class" and args.prepared and not (fold or args.merge_existing):
        parser.error("--prepared goes with --fold or --merge-existing")
    if to_class and (args.basis or not args.new):
        parser.error("function --to-class takes --new (the member's identifier in CLASS) and its evidence from "
                     "retail's vftable: pass no --basis")
    also = []
    for item in (args.also if args.kind == "function" else []):
        if not to_class and not identity and not respell:
            parser.error("--also goes with --to-class, --respell --identity or a this-cv --respell")
        at, sep, word = item.partition("=")
        try:
            also.append((int(at, 16), word))
        except ValueError:
            sep = ""
        if not sep or not word:
            parser.error(f"--also {item!r} is not RVA=NEW (hex RVA)")
    retype = args.kind == "global" and args.retype is not None
    if args.kind == "global" and not retype and (args.size or args.initializer or args.prepared or args.address
                                                 or args.absorb or args.model):
        parser.error("--size, --initializer, --prepared, --address, --absorb and --model go with global --retype")
    if retype and (args.basis or args.size is None or not args.evidence):
        parser.error("global --retype keeps the identifier and takes --new (the full mangled name), --size and "
                     "--evidence; pass no --basis")
    prepared = {}
    for item in (args.prepared if to_class or fold or respell or retype or (args.kind == "function" and args.virtual)
                 or (args.kind == "class" and args.merge_existing) else []):
        rel, sep, path = item.partition("=")
        if not sep or not rel or not path:
            parser.error(f"--prepared {item!r} is not REL=FILE")
        try:
            prepared[rel.replace("\\", "/")] = Path(path).read_bytes()
        except OSError as error:
            parser.error(f"--prepared {item!r}: {error}")
    virtual = args.kind == "function" and args.virtual and not to_class
    if args.kind == "function" and args.access and not virtual:
        parser.error("--access goes with --virtual")
    if args.kind == "class" and args.access and not fold:
        parser.error("--access goes with --fold")
    if virtual and (args.new or args.basis):
        parser.error("function --virtual keeps the identifier and takes its evidence from retail: "
                     "pass neither --new nor --basis")
    if fold:
        if args.fold is None or args.into is None:
            parser.error("class --fold OLD takes --into NEW (both)")
        if args.name or args.new or args.basis:
            parser.error("class --fold invents no name and takes its evidence from retail: "
                         "pass neither --name, --new nor --basis")
        if args.merge_existing:
            parser.error("--merge-existing goes with class --name OLD --new NEW, not --fold")
    elif args.kind == "class" and (args.name is None or args.new is None):
        parser.error("the following arguments are required: " +
                     ", ".join(f for f, v in (("--name", args.name), ("--new", args.new)) if v is None))
    if identity and args.new is None:
        parser.error("the following arguments are required: --new")
    if not virtual and not fold and not to_class and not retype and (
            args.basis is None or args.evidence is None or args.new is None):
        parser.error("the following arguments are required: " +
                     ", ".join(f for f, v in (("--new", args.new), ("--basis", args.basis),
                                              ("--evidence", args.evidence)) if v is None))
    max_prepared = getattr(args, "max_prepared", PREPARED_DEFAULT)
    if max_prepared < 1:
        parser.error("--max-prepared must be at least 1")
    if max_prepared > PREPARED_CEILING and not getattr(args, "beyond_prepared_ceiling", False):
        parser.error(f"--max-prepared {max_prepared} is above the {PREPARED_CEILING} ceiling; pass "
                     "--beyond-prepared-ceiling as well if that one transaction is deliberate")
    ctx = Context(args.root, object_scan=not args.no_object_scan, sweep_dirs=args.sweep_dir or ("build",))
    ctx.max_prepared = max_prepared
    kwargs = dict(new=args.new, basis=args.basis, evidence=args.evidence, max_files=args.max_files)
    if respell:
        kwargs["respell"] = True
        kwargs["prepared"] = prepared
    if respell and also:
        kwargs["also"] = also
    if identity:
        kwargs.update(identity=True, move_to=args.move_to,
                      move_rows=[int(x, 16) for x in args.move_rows.split(",") if x.strip()],
                      forced_moves=[(int(at, 16), dest) for at, _colon, dest in
                                    (item.partition(":") for item in args.forced_move)])
    if virtual:
        kwargs = dict(virtual=True, evidence=args.evidence or "", max_files=args.max_files,
                      prepared=prepared or None)
        if args.access:
            kwargs["access"] = args.access
    if to_class:
        kwargs = dict(to_class=args.to_class, new=args.new, prepared=prepared, evidence=args.evidence or "",
                      max_files=args.max_files)
        if also:
            kwargs["also"] = also
    if fold:
        kwargs = dict(name=args.fold, new=args.into, fold=True, evidence=args.evidence or "",
                      max_files=args.max_files, prepared=prepared or None)
        if args.access:
            kwargs["access"] = args.access
    elif args.kind == "function":
        try:
            kwargs.update(rva=int(args.rva, 16), old=args.old)
        except ValueError:
            parser.error(f"--rva {args.rva!r} is not hex")
    elif args.kind in ("global", "class"):
        kwargs.update(name=args.name)
        if args.kind == "class" and args.merge_existing:
            kwargs["merge"] = True
            if prepared:
                kwargs["prepared"] = prepared
        if retype:
            kwargs.update(retype=args.retype, size=args.size, initializer=args.initializer,
                          prepared=prepared or None, address=args.address, absorb=args.absorb, model=args.model)
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
