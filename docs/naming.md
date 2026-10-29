# Names: where they come from and how they change

A byte match proves nothing about names. `m_pitchShift` and `m_priority`
compile to the same bytes, and the byte gate never compares a symbol name: it
finds each body by the row's mangled name and resolves calls through
`functions.csv` and `symbols.csv`. A plausible wrong name misleads every reader,
and no gate catches it. This page says which names count as proven, how a rename
records its basis, and which tools make a rename safe. Open-BFME-1's
`docs/naming_evidence.md` is the model; the tools here are BFME 2's own.

## Three kinds of name

| The name is | What backs it | Where it is recorded |
|---|---|---|
| a **placeholder** (`Rva0026C320Owner`, `?rva0052F63F@...`, `bfmeHit1173`, `m_0C`, `param_1`, `iVar3`, `a1`) | nothing: it admits ignorance | `address` tier, or nothing at all |
| **inferred** (`AwardRecordView`, `m_markerHandle`) | one uncontested proposal for a parameter/local; otherwise two agents proposed it blind and agreed; or a file stem was read from the real-named rows the file owns | `reverse/name_basis.csv`, basis `inferred` |
| **canonical** (`?ClassifyWall@Pathfinder@@...`) | evidence a tool can check: export, vendored, retail string, Zero Hour or BFME 1 same body, WorldBuilder self-assert, ... | `reverse/name_basis.csv`, basis `canonical:<kind>`, or a fact the tier tool reads directly (exports, `vendored=`, `.lib`) |

A placeholder is acceptable as a starting point but never as a final name. An inferred name is
readable and revocable: the identifier is clean, and the ledger, not the
spelling, says that nobody proved it. A canonical name is permanent. Nothing renames it.

`tools/name_metric.py` decides what counts as a placeholder or weak name: address tokens, any
`bfme` token, 6-8 hex runs, offset names (`m_value84`, `field_1C`), decompiler
locals, and for params and locals single letters and `tmp`/`arg`. `rename.py`,
the lanes and the README's *Readable names* metric all import that one
definition. The metric checks spelling only; it does not prove identity.

### The name tier

`reverse/name_tiers.csv` (`name,target_rva,name_tier,evidence`) is written
only by `python3 tools/allowed_symbols.py --tiers`. Never edit it by hand.
`tools/code_identity_gate.py` compares a staged copy with the tool's output.

| `name_tier` | `evidence` | Meaning |
|---|---|---|
| `address` | `placeholder` | address-derived, generator, scaffold or Ghidra name |
| `evidence` | `vendored`, `lib-member`, `export` | named independently of any agent |
| `evidence` | `wb`, `zh`, `string`, ... | recorded `canonical:<kind>` in `name_basis.csv` |
| `inferred` | `agree`, `mechanical` | recorded `inferred` in `name_basis.csv` |
| `inferred` | `class-agree` | the row's mangled name spells a class token recorded `inferred` |
| *(not listed)* | | unverified: a label an agent chose, with no record |

The facts the tool checks itself come first: placeholder, then vendored, then `.lib`, then
export. A `name_basis.csv` record only decides a row those checks leave
unverified. A carried record keeps its tier, and a `restored` record drops it. The committed file is
far behind the ledger (about 22.8k rows), and regenerating it is a separate
decision, so do not stage a regenerated copy with a rename.

## Canonical evidence

`tools/rename.py` checks every `canonical:<kind>` against the record the
evidence cites. A basis it cannot check is refused.

| `--basis` | What `rename.py` checks |
|---|---|
| `canonical:export` | `reverse/exports.csv` spells the new name |
| `canonical:vendored`, `canonical:lib` | a `vendored=` or `.lib` row spells it, or a cited `<path>:<line>` does |
| `canonical:module` | a retail module class in `reverse/module_factory_registrations.csv` |
| `canonical:rtti` | one of the retail RTTI exception classes (retail is `/GR-`; no other game class has RTTI) |
| `canonical:string`, `canonical:assert` | a retail string in `reverse/string_xrefs.tsv`, referenced by the renamed function's own address (`0x<rva>` in the evidence), spells the word as a whole word |
| `canonical:file` | an approved `reverse/tu_map.csv` TU, or a retail `__FILE__` path ending in the new file name |
| `canonical:wb` | a `reverse/wb_name_leads.csv` row at the address naming it, **and** `tools/name_evidence.py`'s `proof()` grades it canonical: the paired WorldBuilder body asserts the name itself, the pairing scores, and the pairing is unique |
| `canonical:zh` | a cited Zero Hour `<path>:<line>` spelling it, and `proof()` grades a specific (non-trivial), unique same-body Zero Hour placement at this address |
| `canonical:bfme1` | a cited line under `reference/open-bfme-1/` (never its `targets/*/reverse/` ledgers, whose names agents chose; its `ea_evidence.csv` is EA's), and `proof()` grades a specific BFME 1 same-body placement backed by EA or Zero Hour |

The following are **hints, never a basis**. They go into the inferred lane's brief as context:
a WorldBuilder lead that does not self-assert (`wb-lead`, `wb-name-unverified`
notes), a trivial Zero Hour or BFME 1 body that places anywhere, a BFME 1 ledger
name, a Zero Hour line that only shows the name exists, vtable slot or
declaration order (`vtable-slot`, `vtable-order`), a pool-name getter
(`poolkey`), an identifier-like retail string referenced by one placeholder
(`string-hint`), a harvested pin, a caller's spelling, and decompiled C.

## Protected names

These names are never renamed, by any lane or by hand:

- retail exports (`reverse/exports.csv`), `vendored=` rows and `.lib` members
  (upstream's own names), and evidence-tier names in `reverse/name_tiers.csv`;
- retail module class names (`reverse/module_factory_registrations.csv`) and
  the retail RTTI exception classes (`INIException`, `XferException`,
  `FunctorNotSet`, `DllHandle`, ...);
- converged globals (`reverse/data_converged.csv`): `tools/data_check.py
  --converged` refuses a second or a changed name at those addresses;
- anything spelled inside a string literal (`verify_string_refs` checks every
  literal against `game.dat`): assert text, pool names, `__FILE__` paths;
- any name `reverse/name_basis.csv` already records as canonical.

An **inferred** name may replace only a placeholder or weak name, never a real
one. It may not override a real-named pin, a WorldBuilder lead or an
evidence-tier name at the address. A **canonical** name may replace a
placeholder or an inferred name. Vendored and SDK sources (library
directories, gamespy and Platform SDK shims) and generated sources
(`Code/gen_asm/`, `Code/gen_small/`) are never touched. A game unit that
hosts nothing of upstream's except STLport template instantiations over its own
types (`vendored=stlport-*` rows whose own qualified names are `?$` template instances in `_STL`, not merely signatures that spell one, in a
file that also owns rows of its own and is not an `stlport*` unit) is game
source: the instantiation rows keep their names, and a word they spell is still
shared and refused.

## The engine: `tools/rename.py`

### Naming within a subsystem

The default picker first targets shared names with exactly one independent
voter. It serves only those pending shared keys in a second-review batch,
without exposing the first worker's spelling. `next --review-only` restricts
the pass to this queue and never fills it with fresh naming tasks. Previously
visiting the same file for another identifier does not prevent a worker from
reviewing a different key; each worker still votes only once per key.
Pending second reviews take precedence over affinity for fresh work in another
subsystem. Explicit `--file` remains a general file request unless combined
with `--review-only`. Claimed/stale/ineligible keys are still excluded.

`name_lane.py next --count N` serves up to N files from one subsystem, rather
than filling the batch with unrelated files. A worker stays in that subsystem
on subsequent calls until it has no eligible unvoted files there. Within the
group the queue keeps its existing preference for another worker's/model's
votes; an initial group is selected from that same priority order.

The shared brief inventories existing type/function vocabulary across the
selected files and up to three read-only related sources, followed by each
target's source and evidence. Read the related files together before proposing
names. Unlanded proposals and votes are never used as shared vocabulary.
This provides context, not proof that two private class views are the same type.

When the TU map is current, a fragmented file can be grouped by its approved
TU directory only when every owned row has an approved, non-provisional
assignment in that directory. Otherwise the packet explicitly labels the
group as its actual source directory. Stale/provisional assignments do not
become naming evidence. Grouping grants neither canonical names nor approval
to merge files.

Use `next --subsystem Code/GameEngine/Source/GameLogic/AI --count 6 ...` to
restrict a pass to a source or approved-TU directory prefix. `--file` still
selects exactly that file; a conflicting subsystem restriction is refused.
`--list-only` previews the group without writing sessions or worker affinity.
`--mixed` retains the old shuffled multi-subsystem batches for comparison.
Apply, review thresholds, claims and verification are unchanged.

Before choosing a subsystem or scanning source bodies, `next` reads one shared
claim snapshot and skips files locked by other workers. The standard claim
footprint includes file locks and files covered by RVA/class claims, persisted
locks and configured read-only mirrors. This worker's own claims remain
eligible; foreign namespaces do not grant ownership just because their owner
label matches. The picker reports skipped files on stderr, keeping
`--list-only` JSON clean. An explicitly requested busy `--file` yields no task.

This check does not acquire claims or reserve a file. A new claim can arrive
after serving, so apply still takes claims normally and refuses conflicts.
When origin is unreachable, the existing claim helper warns and retains known
cached peer locks; the picker does not invent a claim-free snapshot.

Before renaming a fragmented subsystem, `python3 tools/name_lane.py consolidate`
builds original-path and donor evidence packets alongside the naming work.
It catalogues every retail path, WorldBuilder paths, ZH structure and BFME 1 EA
file evidence, and flags consolidation prerequisites without editing source or
granting a name basis. See [the consolidation workflow](consolidation.md).
Before pushing accumulated file renames or merges, audit affected tooling once
across the entire outgoing batch using that workflow's path-consumer checklist.

Every rename goes through one tool, one rename per invocation. Always plan with `--dry-run` first:

    python3 tools/rename.py function --rva 0x0052F63F --new ClassifyWall \
        --basis canonical:wb --evidence '<what the WB body asserts>' --dry-run
    python3 tools/rename.py global --name '?g_00DFE9E0@@3UDisplayCriticalSection@@A' \
        --new g_displayCriticalSection --basis inferred --evidence agree:<id> --dry-run
    python3 tools/rename.py file --source Code/.../DrawableRva00278644.cpp \
        --new Drawable_setAudible --basis inferred --evidence 'mechanical:<row>' --dry-run
    python3 tools/rename.py class --name Rva0040ADDD --new AwardRecordView \
        --basis inferred --evidence agree:<id> --dry-run
    python3 tools/rename.py member --class Rva00362EC7 --member m_0C --new m_markerHandle \
        --basis inferred --evidence agree:<id> --dry-run
    python3 tools/rename.py param --source Code/.../X.cpp --function Class::method \
        --name a1 --new key --basis inferred --evidence agree:<id> --dry-run
    python3 tools/rename.py local ...        # as param; refused where the unit compiles /Od

Each renamed name and every reference to it change together:

- the `functions.csv` row, the `__ehhandler$`/`__unwindfunclet$` funclet rows,
  the `parent=`, `object-symbol=`, `dup-of=` and `fold-proof=` notes tokens;
- `symbols.csv` pins (renamed in place at the address, alias pins with them);
- `data_rows.csv` rows (globals, `??_7X@@6B@` for a class);
- `/alternatename` pragmas, `__identifier("?...")` strings and
  `present-unmatched` markers;
- every caller's or includer's private declaration and use, found by text and
  by cached object symbol tables (`tools/name_dependents.py`);
- for a file, a same-directory `git mv` plus the `source` columns of
  `functions.csv`, `data_rows.csv`, `tu_map.csv` and `body_owners.csv` and the
  `docs/doxygen/sources.cfg` line.

The rename then runs one `./build.sh` over every touched ledger source, followed by `check_csv` and
`find_declared_unmatched`, and the pre-commit hook's path-sensitive checks on what the commit will contain:
`class_gate`, `ledger_guard`, `code_identity_gate`, `link_debt`, `check_case_collisions`, `hatch_counters`
and `data_check --staged` always run. Which file a rename writes switches on three more, and the two file
sets differ (`COMMIT_LEDGER_FILES` and `NAME_LEDGER_FILES` in `tools/rename.py`): `pin_admission` and
`pin_consistency` (`--check`) run when the rename writes `reverse/functions.csv`, `reverse/symbols.csv`,
`reverse/deleted_rows.csv` or `reverse/re_attempts.log`; `name_dependents` runs when it writes
`reverse/functions.csv`, `reverse/symbols.csv` or `reverse/data_rows.csv`. So a rename that writes only
`data_rows.csv` runs `name_dependents` but not the two pin checks, and one that writes only
`deleted_rows.csv` runs the pin checks but not `name_dependents`. The first set is the hook's own
`ledger_changed` condition (a test compares them); the hook runs `name_dependents` on every commit, and the
second set is rename.py's choice: the three ledgers that tool reads for a name a rename takes away.
`data_check --converged` and `eh_verify` run over the units the rename builds that own a matched row, and
not at all when it builds none. All run with the hook's own arguments against a private copy of the index in
which exactly the files the rename wrote, and those earlier renames of the same run (a `rename_files.py` batch run) left in the tree, are staged (the checks never write the real index; a file rename's
`git mv` has already staged its move there, and a failed run undoes it). Any unit `name_dependents` lists
that the rename does not already verify is built too. It stands only if all of them pass, and the refusal
names the check (`[pin_admission]`). The hook's `conversion_gate`, `tu_ownership`, `invented_names`,
`header_dependents` and baseline shrink-only assertions are not run: a rename cannot change what they judge,
and they still run at commit. A check whose tool is missing from this repository is itself a refusal (a
fixture tree is exempt). A signal cancels the checks, wherever the main thread is waiting (`check_csv` or
the hook tools): the running tool and, in its own session, the `./build.sh` of a `name_dependents` unit are
killed, so the restore does not wait for them. This costs about 13 s per apply (or batch) on a cold object
cache, mostly `name_dependents`' and `code_identity_gate`'s scans, run beside `check_csv`. On any failure,
exception or SIGTERM every file is restored byte for byte. A run that is killed outright leaves a journal in
`build/rename-journal/`. Run `python3 tools/rename.py recover` to restore it; no other run starts while a
journal is pending. On success the tool appends a `deleted_rows.csv` tombstone
`Renamed to <new> by tools/rename.py (<basis>)` for every renamed `(name, rva)`, so a union merge cannot
resurrect the old row. It also appends one `name_basis.csv` row. It claims every affected RVA plus
`file:`/`class:` scopes, keeps those claims for the lander, and prints the paths to stage and a subject
(`Rename <old> to <new> (<basis>)`). It never commits.

It refuses, among other things, the following:

- a protected name, as listed above;
- a new name that collides with an existing one or is itself a placeholder;
- a mangled-name change beyond the identifier (signature changes such as `int` to `bool` cost
  bytes);
- a name keyed in a shrink-only baseline or whitelist;
- a file keyed in `flag_overrides.csv`, `hatch_baseline.tsv` or another protected path-keyed register,
  a file that expands `__FILE__`, a file another file `#include`s, and an approved retail
  TU;
- a move across directories;
- a class registered in `reverse/canonical_classes.csv`. Rename that class in a
  class-reconciliation commit instead;
- a blast radius over `--max-files` (25).

A function rename also respells a base class's declaration of the same virtual
function, but only when the unit itself proves the pair: the renamed class
derives from that base through classes the unit declares, the base declares the
function `virtual`, and both declare it with the same parameter types and
constness (an override takes the base's name in C++). The reverse holds for
overrides of a renamed base declaration. A base declared elsewhere, another
signature, an overload set, a non-virtual base declaration, or a unit that
shows only one side stays refused: a word rewrite would name a method of
another class.

A canonical function rename (never reverted, so the revert's whole-word match
has nothing to keep exact) may take a word that the touched text already
spells, but only where every such spelling is provably another scope that the
rewrite can neither capture nor make ambiguous: a member of, or `Other::word`
through, a class `Other` that the unit declares with all its bases, that is not
a renamed class or a base of one, is not derived from one, and has no
descendant that is also derived from a renamed class (the renamed classes are
the row's class and every base or descendant of it that spells the old word in
its body, read across the file and the headers it includes, since a unit often
declares its classes in a header and defines them out of line: the rewrite
respells those declarations with it, so a sibling that derives from the
respelled base, or a second base of a respelled overrider, is refused wherever
the classes are declared; an unqualified spelling of the old word inside
`Other`'s body or methods is refused, since the rewrite would land in `Other`'s
scope). That holds for a file the rewrite never touches, too, because it does
not spell the old word: every other file that spells the new word is read from
each unit that sees the renamed class (a touched unit, or one that includes a
touched header), over the unit's text and its headers, and a class there that
declares or qualifies the word must be shown unrelated in the same way, else
the rename is refused ("already a name outside the files this rename
rewrites"). Three more spellings in those files are read: a preprocessor line
that spells the word is refused (a macro can declare it inside any class, as in a
touched file; a define continued over a blank after the backslash is read both
ways, as the macro screen reads it); an unqualified spelling inside a method of the renamed class, or
of a class derived from it, is refused unless it is a parameter of the method or
every use lies in the scope of a local of that name (after the rename it would
bind to the renamed member); and an unrelated class's out-of-line methods are
checked for the old word in the unit and in every header it includes. The scope
is read from the class body around the spelling and from the class a qualified
declarator names, so an out-of-line member of a class template, an operator, a
constructor's member-initializer list, a default argument and a static member's
initializer count as much as a plain method (a local never excuses a spelling in
the declarator itself). A method of a class whose bases are not all declared is
refused when it spells the word unqualified. Spellings through `.` or `->`, and a local or file-scope name in a
free function or an unrelated class's method, are not read. A word an unreverted
inferred landing holds is refused as soon as any other file spells it (see
below). The other permitted spellings are a local or parameter of a
function whose parameters, member-initializer list and body never spell the old
word (a function that calls itself is refused) with every unqualified spelling
inside a declaration's scope; or a prototype's parameter name (a parameter list that a
`;` follows, never an inline definition). A base clause is read at top-level
commas only and a template's arguments are not bases (`Pair<A, B>` and
`Wrapper<Mid<A> >` derive from `Pair` and `Wrapper`, whose own definitions say
the rest); a dependent base (`typename T::X`, a bare template parameter, a
nested `Outer<T>::Inner`) or unbalanced brackets leave the chain unknown, so
the class counts as having an undeclared base. A macro whose body (in the file
or a header it includes) spells the old word, directly or through another such
macro, is respelled too, so a function with a local or parameter of the new
word, or an `Other` with a member of it, that invokes that macro is refused
(object-like or function-like; a continued `#define` is joined over backslash-LF
and backslash-CR-LF, and, since cl may or may not continue over a blank between the
backslash and the line end, a define is read both with and without that join, so a
`#define` on the line after a blank-continued one stays a macro of its own). A spelling at file scope, in a
macro, in a `friend` or `using` declaration, after `.` or `->` (the object's
type is not known), in a free function's rename, or beside an undeclared base
stays refused. An inferred name keeps the plain refusal for the files it
rewrites: `revert` and `check` match the word whole. It reads no file outside
that rewrite, a deliberate limit: a later `revert` would rewrite an unrelated
class's spelling of the word too, and `foreign_declarations` refuses that, so the
landing is left unrevertable rather than wrong, and refusing every outside
spelling would turn away most inferred names. For the same reason a canonical rename does not take a
word that an unreverted inferred landing in name_basis.csv (`agree:<id>`)
holds: sharing it would make that landing's `revert` refuse for good, so
restore the landing first.

A `param` or `local` rename is confined to one function's text, so it asks only
what the new spelling could capture and what the old one could mean there. The
function's own text must not spell the new name; the unit must not spell it at
file scope, as a member or in a macro (a parameter or local of another function
may). An included header counts only through a macro, or a member of the
function's class or a base (an initializer list names a member beside the
parameter of that name): a header's own parameters, locals, file-scope names
and unrelated classes do not. A base the headers never declare means any
class's member counts. A macro formal parameter binds only inside its macro.
For the old word in the unit, a named member of an unrelated class does not
count when the function's class and every base are declared; a free function
cannot mean such a member either. Own/base members, globals and macros still
count. Unknown bases and nested class owners keep the conservative refusal.
An ordinary new word keeps the all-member collision check. A verified exact
inverse may restore the original word beside the same unrelated member.
A unit or header that spells either name and whose parentheses or braces do not
balance (an `#if`/`#else` split signature, a stray closer) cannot be classified
and refuses the rename, naming the file.
A local is renamed only where every spelling of its word lies inside the scope of
one of its declarations (the declaring block, or a `for`/`while`/`if`/`switch`/`catch`
statement for a declaration in its header). A spelling before the declaration, after
its block closed or in a sibling block may mean a global or a header's declaration,
so the rename is refused.

A global's consumers are invisible to the byte gate, because DIR32 is masked. For that reason
`rename.py` refuses a global rename when it cannot find and rewrite every consumer. It reports
`data_ledger.csv` as stale instead of editing it.

### `rename.py carry`: notes added after a rename

A seat working on a tree older than a rename can add a `gen-funclet` row whose
`parent=` still spells the parent's old name; the union merge keeps it, and
`rename.py check` reports `reverse/functions.csv still spells <old>`. No rename
can repair that (the owner row already has the new name). Worse, build.py finds
a funclet from `__ehhandler$<parent>` and the parent's exact EH graph, so a
stale `parent=` leaves the row riding on its `object-symbol=$L` pin alone, with
the byte gate still green.

    python3 tools/rename.py carry --all --dry-run     # the plan and the refusals
    python3 tools/rename.py carry --all               # apply, verify, print the paths to stage
    python3 tools/rename.py carry --range origin/master..HEAD

`check` prints this command when its problem is a stale notes token carry can
cover. `carry` replays every `function`, `global`, `class` and mangled `carry`
record of `name_basis.csv` in order over the tokens of each functions.csv notes
field (`parent=`, `parents=`, `icf-owner=`, `dup-of=`, `object-symbol=` and free
prose), so a chain `A -> B -> C`, a function rename followed by a class rename
and the reverse order all end at the live spelling. A record that a later
record restores or whose old spelling a later rename reuses is skipped, as in
`check`. It rewrites only the notes field of each row (the planner asserts the
other six fields are byte-identical), writes no tombstone and no
`name_basis.csv` row (it is not the `carry` basis kind), and goes through the
same journal, `./build.sh`, `check_csv` and restore path as a rename, so
`rename.py recover` restores a killed run. After `parent=` is fixed the build
locates each funclet from its parent's EH graph, which is the byte check this
needs.

A record is carried only when the live ledger proves each respelling:

- the old spelling names no row, pin or data row;
- the new spelling names exactly one matched functions.csv row (or one data
  row), and for a function chain that row is at the renamed RVA (a funclet-name
  token is checked through its parent);
- for a `gen-funclet` row's `parent=`, the parent is a row of the funclet's own
  source and so is `__ehhandler$<parent>`;
- the token is one of the symbol-valued keys above or prose; `import=`,
  `target=` and any other `key=` are refused;
- no old spelling is left outside the notes (a row name, a pin, a data row, a
  body owner or a source), and the row is not in generated source.

A record is all or nothing. Anything it cannot prove is listed as `carry
refused: <record>: <reason>` and the exit status is 2 (0 when everything was
carried or there was nothing to do, 1 when verification failed and everything
was restored); the other records still land. A plan over `--max-files` sources
is refused as a whole: carry fewer renames (`--range`). Commit the printed paths
(functions.csv only) with the suggested subject, then run `check` again.

### `reverse/name_basis.csv`

Append-only and union-merged, one row per rename:
`kind,old,new,basis,evidence,source,rva`.

- `kind` is one of `function`, `global`, `file`, `class`, `member`, `param`,
  `local`, `carry`. A `carry` row moves an existing record when its spelling
  changes (for example, a method of a renamed class), so that the record's protection
  does not lapse.
- `basis` is `inferred`, `canonical:<kind>` or `restored`. `restored` marks the
  exact inverse of a reverted inferred landing.
- `evidence` is `agree:<id>` (a row of `reverse/name_agreed.csv`),
  `mechanical:<row>`, or the canonical citation.

`tools/rename.py` is the only writer. Members, params and locals are recorded qualified
(`Class::m_x`, `Scope::fn::a`), so a record for one does not protect an
unrelated name with the same spelling.
For overloaded functions, parameter and local records retain the selected
scope (`Scope::fn#2::a`, or explicit `#1` for the first overload).
`check` examines that overload and reports a missing selection; `revert`
uses the recorded selection, including after a class or function scope rename
or a recorded source-file move.
Older records without a selector retain the conservative check across all
overloads and may need `revert --function Scope::fn#N` to select their inverse.

## The lanes

The daily renaming pass drives three lanes. Agents can run them by hand.
Run all of them after `git pull --rebase origin master` and the usual
`tools/check_csv.py`.

**1. Mechanical files: `tools/rename_files.py`.** This lane renames address-named units
(`Rva002A9DACGet.cpp`) whose rows already have real names, to `Class_method.cpp`
(one row) or `Class.cpp` (one class). It involves no naming judgement, and the stem lands as
`inferred` with `mechanical:<row>`. It is a port of BFME 1's
`rename_addressed_sources.py`, with the same refusals.

    python3 tools/rename_files.py [--under DIR] [--show N] [--show-refusals] [--check]
    python3 tools/rename_files.py --apply --limit 20 [--batch 10] [--json build/rename_files.json]

A batch shares one journal and one `./build.sh`. If a batch fails, it is restored and its
members are retried one at a time. The renames stay staged for the lander.

**2. Evidence: `tools/name_evidence.py`.** This lane finds names that the target or a reference
already gives, and grades each one `canonical` or `hint`.

    python3 tools/name_evidence.py [--sweep-dir build] [--kinds wb,zh,bfme1,string,poolkey,vtable]

It writes `build/name_evidence.tsv`
(`kind key rva current candidate evidence_kind strength detail`). A
`canonical` line carries `basis=canonical:<k>` and an `evidence=` string that
`rename.py` accepts. Review a WorldBuilder pairing with `python3 tools/wb_show.py <rva>`, then
land it with `rename.py function|class ... --basis canonical:<k>`. Hints go
no further than the inferred lane's brief. The tool runs no sweep itself: it reads
the `zh_sweep`/`bfme1_sweep` caches that already exist.

**3. Inferred: `tools/name_lane.py`.** This lane covers everything nobody can prove.

    python3 tools/name_lane.py next --session S --model M [--count N] [--file F] [--list-only]
    python3 tools/name_lane.py submit ANSWER.json --session S --model M
    python3 tools/name_lane.py apply [--retry-blocked] [--lead 2] [--min-models 1] [--only-labels L,L]
    python3 tools/name_lane.py dispute KEY... --reason TEXT
    python3 tools/name_lane.py status [--metric] [--only-labels L,L]

Parameter and local renames within one file share a transaction and verification;
each proposal still passes its normal agreement and scope checks. On failure the
whole batch is restored, then names are retried individually. Use `apply --no-batch`
to retain per-name verification, or repeat `--key KEY` to select exact agreements.

`next` serves one matched, non-generated source with the placeholders that
this file alone decides. That covers the functions it owns rows for, the classes only it defines and their
members, its params, its locals (only where the unit compiles optimised) and the file
globals it owns. `next` writes a brief to `build/name_lane/briefs/<session>.txt` with the
style rules: types `CamelCase`, members `m_camelCase`, params and locals
`camelCase`. Answer each key with a name or `"skip"` in a JSON file written with a
file-writing tool, never inline in a shell command. A skip costs nothing; a
wrong name misleads. If a stand-in type *is* a class that a game or Zero Hour
header declares, answer that class's name. `apply` lands each agreed key
through `rename.py` with `--basis inferred --evidence agree:<id>`, and appends
`landed`, `blocked` or `stale` to `reverse/name_agreed.csv`.

`apply` lands every agreed key, including agreements that only other
contributors' voters reached. A pass that should land only its own seats'
agreements runs `apply --only-labels seat-a,seat-b` (the `--model` labels the seats
voted under). A key is then applied only when every worker that voted its winning
spelling carries one of those labels. A key whose winning spelling has any other
voter, or whose lead over a rival rests on one, is left untouched. It stays
`waiting` for whoever applies it, is neither blocked nor stale, and gets no row in
`name_agreed.csv`. Rivals count against the lead whoever cast them, and
`--retry-blocked` works with the filter. `status --only-labels seat-a,seat-b` prints how many
waiting keys the filter would select (pass the same `--lead` and `--min-models`;
it does not read the source, so `apply` may still find a selected key stale).
Without the option `apply` behaves as before.

## Review by naming scope

An uncontested inferred **parameter or local** name may land from one worker's
proposal. It is scoped to one function, remains inferred and revocable, and
still goes through `rename.py`'s scope/collision checks, byte verification and
ledger checks. A competing non-disputed proposal restores the existing
two-worker requirement and voting lead; `apply` and the engine recheck votes,
so a late rival stops a single-proposal approval before it lands.

Functions, classes, members and globals still require two independent agents
to propose a name blind and agree. BFME 1 measured the original blanket rule's
reason on 2026-09-29: one model alone named about 60% of
placeholders right and 2-9% of them misleadingly; two agreeing blind proposals were about
80% right and never misleading.

- Each vote is stored in `reverse/name_votes.csv` only as
  `sha256(key|canon(name))[:24]`. No name text enters the repository until a
  second worker matches it for names requiring blind agreement. An uncontested
  parameter/local proposal writes its name to the approval record immediately.
- `canon()` folds word order, plurals and common abbreviations, so
  `m_ladderComboBox` and `m_comboBoxLadder` count as one vote.
- Agreement counts distinct **workers**, not session labels. The worker id
  comes from the environment (`BFME_CLAIM_OWNER` or `BFME_RUN_ID`, otherwise the harness
  session, otherwise `tools/claims.py`'s owner), stored hashed. Print yours with
  `python3 tools/name_agreement.py whoami`. An orchestrator running blind seats
  gives each seat its own `BFME_CLAIM_OWNER`, as it already does for claims.
- An uncontested parameter/local wins with one worker. Other names need two
  or more workers and a lead of `--lead` (2) over every rival spelling.
  `--min-models` applies to both paths: requiring two models also requires
  a second proposal for an otherwise uncontested parameter/local.
- `rename.py` treats `name_agreed.csv` only as an index. It recomputes the
  agreement from the votes, so a hand-written agreement row authorises
  nothing.

Old single votes contain hashes, not recoverable name text. This policy does
not automatically turn that backlog into approved names; an existing proposal
must be recovered from its original answer or independently proposed again.
The lighter path changes review cost, not evidence: it does not make a name
canonical or prove its meaning correct.

Do not show your proposal to another seat or read theirs, and do not cast votes for a
second seat yourself.

## Meaning before spelling for parameters and locals

A scoped answer may include a role descriptor instead of just a string:

```json
{
  "copyBuffer:param_1": {
    "name": "destination",
    "meaning": {
      "role": "destination",
      "entity": "buffer",
      "units": "bytes",
      "ownership": "borrowed"
    }
  }
}
```

The worker classifies the role independently from the code. All four fields
must match exactly before different spellings share support. There is no
global `target = destination` synonym rule. A source/destination, byte/element,
radius/diameter or borrowed/owned disagreement stays a rival even when both
workers chose the same identifier. Ordinary vote leads and model requirements
still apply to those rivals.

`role` is one of `source`, `destination`, `input`, `output`, `inout`, `index`,
`count`, `length`, `size`, `flag`, `callback`, `handle`, `owner`, `result`,
`radius`, `diameter`, `angle`, `position`, `duration`, `deadline`. `entity` is a
specific lowercase snake_case concept (not `unknown`, `thing`, `value`, `data`,
`parameter` or `local`). Units are `none`, `bytes`, `elements`, `pixels`,
`radians`, `degrees`, `frames`, `seconds`, `milliseconds`, `world_units`,
`boolean`, `identifier` or `unspecified`. Ownership is `borrowed`, `owned`,
`shared`, `value` or `unspecified`. Different qualifiers stay distinct.

`reverse/name_meanings.csv` stores only a descriptor hash, bound to the exact
key, spelling vote, worker, model, session and date in `name_votes.csv`. No
role prose is exposed to the next blind worker. Submit writes both records;
stage the votes, meanings and agreement records together. A meaning-based
agreement id carries the descriptor hash, and `rename.py` independently checks
its support. The chosen identifier must be one someone actually proposed.
An unbacked metadata/approval row grants no support. Disputing a meaning-based
name also blocks that meaning under alternative spellings.

Plain string answers and old votes remain supported. An old vote may join an
annotated role only for the exact same spelling with one unambiguous meaning;
an old differently spelled vote has no recoverable role and remains a rival.
The first approved spelling can remain while other equivalent proposals add
support. Functions, classes, members and globals retain spelling agreement in
this first version. Meaning agreement is inferred and revocable, not proof of
original naming or semantic correctness. Byte and ledger checks are unchanged.

For an unresolved scoped disagreement, the original worker can use
`next --meaning-review-only` to revisit its own unannotated vote. Resubmit the
same normalized original spelling with a structured meaning. This appends an
annotation bound to the original vote's worker/model/session/date; it never
adds a spelling vote, increases voter count, changes the original choice or
replaces an existing descriptor. Another worker cannot annotate your vote.
Once both original meanings agree, an old pending approval is promoted to a
meaning-bound record. Conflicting meanings remain rivals. The normal picker
routes these clarifications ahead of fresh work after independent shared-name
second reviews; `--review-only` and `--meaning-review-only` are separate queues.

## Disputes

A landed inferred name that the code contradicts goes back through the lane:

    python3 tools/name_lane.py dispute 'Code/X.cpp|class|...|Rva0040ADDD' --reason 'what the code shows'

The lane calls `rename.py revert`, which is the exact inverse of the recorded landing: same
kind and address, from the current spelling (carry rows followed) back to the
placeholder. The revert is byte-gated and recorded as basis `restored`, and the lane refuses that spelling for
the key from then on. `python3 tools/rename.py revert --record <id> --reason TEXT`
does the same directly. A canonical name is not disputed this way. If retail
evidence refutes one, that is an identity correction with its own evidence
(`tools/add_match.py --replace-rva`), not a naming vote.

## Landing a rename

Renames recover zero bytes. Batch them like other trivial work (roughly 5-20
per commit, one coherent kind) and keep a class rename in its own commit. The
lander does the following:

1. Stages exactly the paths `rename.py` or the lane printed, including
   `reverse/name_basis.csv` and `reverse/deleted_rows.csv`, and commits with the
   suggested subject.
2. Runs `git pull --rebase origin master`, then
   `python3 tools/rename.py check --range origin/master..HEAD`. A seat that
   added a pin, a caller or an extern with the old spelling while the rename was in
   flight passes every gate and breaks only the link; `check` catches it. When
   the old spelling is a functions.csv notes token (a funclet's `parent=`),
   `python3 tools/rename.py carry --range origin/master..HEAD` repairs it.
3. Pushes, then runs the `python3 tools/claims.py release ...` command that the tool printed.

## Renaming by hand

Hundreds of `Name ...`/`Rename ...` commits came before these tools, each
citing ZH, vtable-slot, WorldBuilder or caller evidence. Prefer `rename.py`
now, because it writes the tombstone and the record that most hand renames forgot. Only 9 of 240 such commits
tombstoned the old row. When `rename.py` cannot express a rename (an operator, a
signature change, a cross-directory move), a hand rename must still:

- replace only a placeholder, and only with a name whose evidence would pass the
  canonical table above. Never hand-land an inferred name, because those need the
  scope-dependent review rule;
- cite the evidence in the commit message and record it with `tools/re_log.py`;
- rename pins in place, update every caller's view, and append a
  `deleted_rows.csv` tombstone `Renamed to <new>: <evidence>` for each old
  `(name, rva)`;
- leave `name_basis.csv` alone. A hand rename has no record, so its name stays
  *unverified* in the tier, which is accurate.

## Traps

- A rename counts only if it makes the name clearer: `Q2Vt0110F978` to
  `PolymorphicVptrBase0110F978` is longer, not clearer.
- A type can appear only inside decorated names (`??1Sub005C6A40@@QAE@XZ`).
  Search decorated forms before calling a word free.
- A stale old-name pin keeps the old name resolving: every gate stays green and
  the link breaks. `rename.py` renames pins with the row, and `check` looks for
  pins that reappear.
- A file using bare `__FILE__` embeds its repo path in retail-compared bytes.
  A file using `__LINE__` or `#line N` changes bytes if the rename adds or removes
  lines.
- Private class views: most units declare their own view of a class, so a class
  or member rename touches many files. `tools/class_views.py --class X` lists
  them before you plan.

### Early eligibility

The picker excludes function addresses with a different real-named pin, using
rename.py's pin predicate. Placeholder pins and the owner's own symbol do not
exclude a candidate. Submission rechecks inferred-name protections before
recording a vote, including pins added since serving and reference spellings.
Class proposals whose new token already occurs in source are refused before
voting: reconcile declarations instead of accumulating an unapplicable agreement.
These checks do not replace the planner or byte/link verification at apply.
