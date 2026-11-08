# Names: where they come from and how they change

A byte match proves nothing about names. `m_pitchShift` and `m_priority`
compile to the same bytes, and the byte gate never compares a symbol name: it
finds each body by the row's mangled name and resolves calls through
`functions.csv` and `symbols.csv`. A plausible wrong name misleads every reader,
and no gate catches it. This page says which names count as proven, how a rename
records its basis, and which tools make a rename safe. Open-BFME-1's
`docs/naming_evidence.md` is the model; the tools here are BFME 2's own.

## Whole-function locals and parameters (normal scoped workflow)

Use this path for local/parameter naming instead of isolated voting rounds:

The voting picker `next` serves only functions, classes, members and globals.
`submit` and `validate` reject new local/parameter votes even from old saved
sessions. `--meaning-review-only` and scoped `resolve` requests also direct
workers here. Cached task inventories cannot restore scoped voting tasks.
Start a fresh scoped session and review its current complete functions; old
answers are context, not an approval for the new source snapshot.

```sh
python3 tools/name_lane.py scoped next --session S --model M --under Code/GameEngine/Source/Common/
# A native sub-agent reads build/name_lane/scoped/S.json and fills S.answers.json.
python3 tools/name_lane.py scoped preview --session S --answer build/name_lane/scoped/S.answers.json
# Parent scans the complete mapping and preview diff; investigates only questionable names.
python3 tools/name_lane.py scoped apply --session S --answer build/name_lane/scoped/S.answers.json --review build/name_lane/scoped/S.review.json
```

The picker targets 200 bindings by default (`--target 500` for a larger pass),
selects complete sources/functions, and inventories all recognized scoped names,
including meaningful names and donor spellings. No weak-name filter truncates
the pass. `--files SOURCE...` selects explicit sources. Packet size/file bounds
never truncate a function. Claims held by other workers are skipped.
Fully reviewed sources are remembered locally until their bytes change, so
continuous batches advance rather than repeatedly reviewing completed files;
explicit `--files` revisits a source.

Link and consolidation work also supplies a `scoped_naming` handoff, in both
selected-work JSON and human instructions; a successful TU merge points at its
final TU path, including when applying a saved merge plan. Reuse the analysis and
worker identity from the main task to clarify locals/parameters in the complete
functions you inspected:

```sh
python3 tools/name_lane.py scoped next --session link-names-S --model M --files Code/Game/X.cpp --functions 'Object::update'
```

`--functions` requires explicit files. A bare scope includes all its overloads;
`#1`, `#2`, etc. selects one complete overload. No function's binding inventory
is cut to meet `--target`. A partial-function pass does not mark the whole file
reviewed, so future bulk work still sees its other functions. Without the filter,
the existing whole-file bulk workflow is unchanged. Run with the same claim owner
as the main task and respect other workers' claims. Take the packet after primary
edits; update a function selector if the repair renamed that function. For a merge,
use the destination TU after application, never donors about to disappear.

The handoff does not launch a model, inventory code, claim more files or run another
verifier merely by being served. The worker follows the usual child-proposal,
parent-review and batch-apply path when useful names can be established. Keep
already clear names and uncertain roles; no unrelated files are added to fill a
quota. Complete the primary pass test and publish verified moves promptly before
lengthy naming work. Naming is not a link or consolidation success condition.

Apply the complete reviewed batch and verify its changed sources together;
hundreds of names can share one transaction and one commit. Do not split it
into per-name votes or small application rounds. `--target` counts inventoried
bindings, including names retained as already clear; it is not a rename quota.

Answers are `{"proposed_by":"/root/naming-child","names":{"KEY":{"name":"descriptiveName"}}}`.
For several children, keep their original part files and combine them with:

```sh
python3 tools/name_lane.py scoped merge --session S --parts PART_A.json PART_B.json
```

The combined `S.answers.json` records one `proposed_by` on each binding. A
per-binding identity overrides the single-child default; listing several
children as one identity is refused. Duplicate or missing bindings are refused
before overwriting the output. Preserve the child proposals; make final parent
corrections in the review file rather than rewriting the child's proposed name.
The naming history records the actual proposer and reviewing parent. Parent
decisions also preserve the original proposed name (or keep) and the decision's
reason in the existing evidence field. Routine accepted names need no essay,
new voting round or additional ledger.

Account for every inventoried binding; use `{"keep":"already clear"}` to retain
one. Add `"question":"uncertain units"` to questionable proposals. The parent
quickly scans all mappings and diffs; only questionable entries need deeper
investigation and a decision. In the generated review file set `scan_complete`
to true only after scanning. Preserve the exact proposal SHA. `decisions` maps
exceptional keys to `{"name":"finalName","reason":"source-based determination"}`
or `{"keep":"reason"}`. Every flagged question requires a final decision.
Coverage warnings require `coverage_checked:true` after inspection; regex
inventory is not a complete C++ parser, so unsupported declarations must be
reported rather than described as renamed. Already meaningful names need no
cosmetic replacement.

Preview saves its scoped candidate plans in the session's `.plans.json`; the
review form binds that artifact with `plan_sha256`. Apply validates the source,
read dependencies, tracked searches, header closure, compiler flags and planner
rules before reusing candidates. Parent keeps drop candidates; corrected names
are planned normally without repeating the other names' analysis. Stale, missing
or modified artifacts fall back to normal planning. Older sessions still work.
Keep the generated `plan_sha256` when acknowledging the review form.
Claims, journaling, rollback and combined byte/link/ledger verification remain
on the ordinary transaction path. The result reports `reused_sources` and
`reused_names`; neither is a verification receipt.

For an unclear binding, request a small amount of additional context:

```sh
python3 tools/name_lane.py scoped context --session S --key 'Code/X.cpp|param|functionName|a'
# Optionally add --context-files Code/Game/Relevant.h for a known external declaration.
```

This read-only command shows the binding's uses, relevant call signatures and
member declaration candidates from the source and locally resolvable includes.
It accepts up to four binding keys and eight explicit context files; reads at
most twelve extra files within a byte budget; and reports unresolved or omitted
includes. It does not build a repository-wide declaration index, run a model,
refresh a reference checkout or change the normal packet size. Use it only when
the supplied full source leaves the role unclear. Returned declarations carry
their path, line and content hash. Multiple overloads/owners remain candidates;
inferred, donor and conditionally compiled declarations do not become canonical
proof. The syntax-limited lookup can miss declarations; a missing hint is not
evidence that a declaration does not exist.

The grouped planner reuses the original source analysis and composes independent
binding-proved changes together. One run transaction claims the union, writes
the journal and verifies changed sources together. Only successful inferred-name
history/binding records are appended; scoped votes/approvals and external review
processes are not used. Failed verification restores the transaction. If compiler
diagnostics identify failed source files, unaffected files retry together once;
unknown failures stop with diagnostics rather than repeatedly compiling individual names. Inspect the
per-session `.result.json` for renamed, retained, refused and timing counts.
Review acknowledgement records responsibility; it is not machine proof of a
name's meaning or of agent independence.

Canonical protections, ambiguous binding/capture checks, optimization constraints,
byte/link/ledger verification, and rollback remain enforced. Globals, members,
functions and classes retain their existing workflow. The voting sections below
also describe historical scoped agreements, which remain readable/reversible.

## Three kinds of name

| The name is | What backs it | Where it is recorded |
|---|---|---|
| a **placeholder** (`Rva0026C320Owner`, `?rva0052F63F@...`, `bfmeHit1173`, `m_0C`, `param_1`, `iVar3`, `a1`) | nothing: it admits ignorance | `address` tier, or nothing at all |
| **inferred** (`AwardRecordView`, `m_markerHandle`) | a scoped batch proposal reviewed by its parent; otherwise two agents proposed it blind and agreed; or a file stem was read from the real-named rows the file owns | `reverse/name_basis.csv`, basis `inferred` |
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

When two blind voters choose different names, the configured reviewer can make
one further comparison against the same source. The first proposal is kept in
`build/name_lane/proposals/` locally and is shown to the reviewer only after
both blind votes are recorded. The comparison selects the original name, the
reviewer's name, a replacement, or `skip` with a source-based reason. If the
reviewer selects the original name, its reviewed acceptance completes the two
workers' agreement. If it selects its own name, the original voter can accept
it with `name_lane.py resolve --key KEY --name NAME --reason REASON`. A
replacement needs both original voters to accept it. A substantive disagreement
stays pending. No new blind votes or worker identities are created by this step.

Reviewed acceptances are recorded in `reverse/name_resolutions.csv`; the original
hashed votes remain unchanged. The approval record carries the agreed name and
the source fingerprint. The rename engine recomputes the original voter set,
their accepted spelling, and the source fingerprint before applying an inferred
rename. If the source changes, resolve it again against the changed code.
Verified run-wide rename batches may carry this worker's local plaintext
proposal to the new source hash only when the proposal matches the transaction's
exact old source and the on-disk file matches its exact verified result. This
keeps automatic local/parameter application from stranding shared-name comparisons.
Unrelated edits and failed transactions never refresh the proposal; the original
votes, reviewer independence and resolution fingerprint checks remain unchanged.

`review --no-resolve` disables this comparison for a configured reviewer. The
reviewer runs the comparison only when the original plaintext proposal is
available locally; an old hash without its proposal cannot be reconstructed.
For a manual comparison, both voters can use `resolve` with a selected name and
source-based reason. `next --count N` prepares multiple files from one subsystem
in a single picker call; `apply` verifies eligible approvals as a run-wide batch.
For an explicit set, `next --files Code/.../A.cpp Code/.../B.cpp --session S
--model M` serves them together, using one claim snapshot and one shared brief.
Blind shared-name proposals may include a role sentence in
`{"name":"...","role":"..."}`; the reviewer records its own role description
before seeing the first proposal. The comparison packet carries both roles so
the decision can distinguish different wording from different interpretations.
The role is context, not a canonical naming basis. Picker timing separates
queue, claims, selection and brief generation; reviewer reports blind and
comparison time and each resolution outcome; the run batch reports planning,
claims and apply/verification time. Publication timing remains in `push.py`.

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

Every rename goes through this tool's planner. For a single CLI rename, plan with `--dry-run` first:

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
  bytes), except the one evidence-gated respell below (`function --virtual`);
- a name keyed in a shrink-only baseline or whitelist;
- a file keyed in `flag_overrides.csv`, `hatch_baseline.tsv` or another protected path-keyed register,
  a file that expands `__FILE__`, a file another file `#include`s, and an approved retail
  TU;
- a move across directories;
- a readable class registered in `reverse/canonical_classes.csv` (a registered
  placeholder moves with its key and contract: see
  [`rename.py class` on a registered class](#renamepy-class-on-a-registered-class-key-contract-and-views-together));
- a blast radius over `--max-files` (25).

### `rename.py function --virtual`: a row retail calls through a vtable

A row spelled non-virtual (`?f@C@@QAEXH@Z`, `IAE`, `AAE`) whose address sits
in a retail vtable slot is really virtual (`UAE`, `MAE`, `EAE`). That is a
one-character change of the decoration; the identifier, scope, constness,
calling convention, return type and parameters stay. The plain function kind
refuses it and no hand rename may make it over a real name, so this mode does
exactly that change and nothing else:

    python3 tools/rename.py function --rva 0x00433025 --virtual --dry-run
    python3 tools/rename.py function --rva 0x00433025 --virtual [--evidence 'optional note']

It takes no `--new` and no `--basis`: the evidence is retail's, and the tool
reads it itself. The respell keeps the row's access (`Q` public, `I`
protected, `A` private) unless `--access public|protected|private` names
another: `--access protected` turns `QAE` into `MAE`, for a row that the
callers' views and canonical headers declare a protected virtual (Zero Hour's
module `xfer`/`crc`/`loadPostProcess`). Access is no retail fact, so the plan's
evidence records it as requested. Each in-class declaration the respell makes
virtual is put under that label (`protected: virtual void xfer(Xfer *xfer);`),
and the access it had is restored after it unless nothing or another label
follows it in the class body. A caller outside the class hierarchy that called
the member directly no longer compiles (C2248); prepare it (`--prepared`) with a
qualified call through a derived view. It refuses unless all of these hold:

- a table that retail code installs (`mov dword ptr [reg], imm32` or
  `[reg+disp]`, the store `tools/vftable_map.py` reads, with the displacement
  forms a multiply-derived class's secondary table takes) has a slot holding the
  row's address;
- that table belongs to the row's class, or to a class that a view derives from
  it: a constructor, destructor or deleting destructor row of that class
  installs it (at a displacement only when the same row also installs a table
  at +0, so a member object's table does not count), or `data_rows.csv` names it
  `??_7Class@@6B..@`; a derived class counts when its installer's unit (or the
  row's own unit), with the headers it includes, declares the derivation;
- the address is not a shared body: no other row or pin there and no fold in
  the notes (`fold-proof=`, `icf-owner=`, `dup-of=`, `ICF`), since a slot on a
  folded body proves only that some folded function is virtual;
- the new decorated name names no row or pin and is not tombstoned at the
  address, no local static embeds the old name, no frozen register keys it, and
  the name is not protected (above; a destructor is judged by its decorated
  name, since its class token is not renamed).

A destructor is virtual exactly when its deleting destructors are, so `??1C`,
`??_GC` and `??_EC` rows spelled non-virtual are respelled together whichever
one is named: a deleting destructor on its own slot, the destructor because a
slotted deleting destructor's retail body calls it.

It rewrites the row, its `__ehhandler$`/`__unwindfunclet$` rows and every notes
token (`parent=`, prose), pins in place, `body_owners.csv`, every spelled
mangled name in comments, linker pragmas and `__identifier` strings (a plain
string literal spelling it is refused), and adds `virtual` to each in-class
declaration of the method (or of `~C`) in every body of the class that declares
it (callers' and includers' views alike; an out-of-line definition is left as
it is; an ordinary overload set, a static or a template member is refused). The
one supported operator family, in a global non-template class, is non-const
thiscall `operator<<(bool)`,
`operator<<(__int64)` and `operator<<(unsigned __int64)`, returning its own
class by reference. Its exact primitive operand selects one declaration;
other overloads, const members and out-of-line definitions remain unchanged.
Typedef operands and other operator signatures are unsupported. All native
installation, identity, protection and byte checks above still apply. A unit
whose current object references the old name but whose text declares nothing
to rewrite (an implicit member, a base's declaration) is refused: reconcile
that view first. A unit that includes, directly or through other headers, a
header this respell makes virtual is not such a unit: its view is that
header's, and it is verified with it. It tombstones each renamed `(name, rva)` with `Renamed to
<new> by tools/rename.py (virtual: retail vtable slot)`. The name's basis does
not change: a `name_basis.csv` record of the old spelling moves to the new one
in a `carry` row whose evidence cites the slot (so an inferred landing stays
revertible), and a name with no record gets none, as for a hand rename.

The byte gates decide, as for any rename: one `./build.sh` over every touched
source, owner and includer, then the commit checks. Declaring a method
`virtual` can change code: a caller whose call now goes through the vtable, or
a view that gains a vptr and shifts every field. Any such byte change fails the
build and every file is restored. Run `tools/link_check.py` over the touched
units before and after: a view that emits the class's vtable now carries the
new slot, and every view emitting that table must agree.

The library API `run_batch(..., source_edits={path: proposed_cpp_bytes})` can
couple source preparations, such as preserving an overload block or removing a
duplicate emitter, to the ordinary rename plans. Supply the bytes in memory;
do not edit the files first. Up to32 tracked, clean, non-generated/non-vendored
`Code/*.cpp` paths with matched rows are supported. The complete source
preparation joins the journal, file claims, normal byte verification and staged
footprint. Every coupled rename must plan successfully; a refusal applies
nothing. Failed verification restores both source preparations and ledgers.
Reviewed name-resolution fingerprints cover the prepared starting source.
The unstaged-dependent guard remains active; adding a file only to the byte
verification list does not put its edits in the transaction.

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

### `rename.py function --to-class`: a slot rowed under a placeholder class

A vftable slot rowed before its class was known carries an address-derived
class (`?rva00550B4C@Rva00550B4C@@QAEXXZ`). Once the slot's class C is known,
`function` cannot respell it (identifier only), `class --fold` needs special
members of the placeholder class, and `class` collides with C. This mode moves
the row into C as its virtual member:

    python3 tools/rename.py function --rva 0x00550B4C --to-class GameSpyBuddyMessageQueue \
        --new endThread --prepared Code/.../BuddyThread.cpp=build/endThread.cpp --dry-run

`--new` is the member's identifier in C (the access code becomes the virtual
form of the old one) or its full mangled name (to choose, say, protected
`MBE`, or a `this` cv other than the placeholder's guess: the class's own
declaration decides, and its compiled vftable must name exactly that
spelling); convention, return type and parameters are kept. It takes no
`--basis`, invents nothing, and refuses unless all of these hold:

- the row's class is a placeholder;
- a table that a constructor, destructor or deleting destructor row of C
  installs holds the address in exactly one slot, and no table of a class
  unrelated to C holds it (a folded body); the address has no second row, pin
  or fold note;
- the vftable C's installer units compile names the new symbol in that slot,
  and every other slot whose symbol the ledger resolves agrees with retail's
  table: C's declared virtual order matches retail's there. A slot also
  agrees when its address and retail's word reach one body through a single
  `jmp rel32` on either side (retail 0x00497805, `jmp 0x0058B03E`, is the
  ICF-folded empty `loadPostProcess` override of the UpdateModule family,
  which a view inheriting UpdateModule's slot calls too); a chain of jumps or
  a jump to another body still refuses. An installer unit that only
  references the class's `??_7` (a constructor storing the table another
  unit emits) compiles no copy and is passed over, and so is a stand-in
  installer: a destructor scaffold whose view keeps placeholder bases, so its
  copies of the class's tables name nothing the ledger resolves (no row, pin
  or moved name in any slot) under `??_7` symbols no judged installer
  compiles (`??_7ObjectWeaponStatusHelper@@6BRva004DF8A9_B2@@@` = [f2] in
  Rva004DF7C2Derived.cpp). One installer must still compile a matching table.
  It is checked on the current objects when planning and on the rebuilt ones
  after ./build.sh.

An int-return placeholder override (`?update@Rva0028F976@@UAEHXZ`, where the
base virtual returns an enum and C++ forbids an int override) may take the
enum: a full mangled `--new` may differ from the row's tail only by the return
type `H` -> `?AW4E@@` (thiscall, a global enum, `E` not spelled again in the
signature), and only when a class registered in `canonical_classes.csv`, among
C and the bases its installer units' views derive from, declares
`virtual E WORD(` in its header (UpdateModuleInterface::update in
UpdateModule.h returns UpdateSleepTime). MSVC returns an int-sized enum in eax
like an int, so the byte gate still proves the body; the declaration is
recorded in the evidence and the tombstone (`; return type: ...`).

A table whose slots are all still rowed under other placeholders (Rva005C44A3's
0x00C745D4) cannot prove its first move: no other slot resolves to agree with.
`--also RVA=NEW` (repeatable) moves further slots of the same table in the same
plan and verification. Every member passes the single-move checks, all sit in
one table at distinct slots, each moved name resolves to its row's address, and
every moved slot must agree with at least one other slot and clash with none:

    python3 tools/rename.py function --rva 0x005C44DF --to-class Rva005C44A3 --new rva005C44DF         --also 0x005C44C3=getName --also 0x005C4352=rva005C4352 --prepared ... --dry-run

A retail table of exactly one slot (SpawnUnitBehavior's +0x20 interface table
0x00C59120) has no other slot at all. Its move proves itself when an
installer's compiled copy is exactly one slot long too and that slot names the
moved symbol; a longer copy, another name in the slot, or a longer retail table
with its other slots unresolved still refuses.

The C++ is the caller's, given as `--prepared REL=FILE` (the definition under
C, a caller that names the old member, a view declaring the override); the
files must be clean, tracked ledger sources. The tool respells rows, funclet
rows, notes tokens, pins, body owners and every spelled mangled name,
tombstones `Renamed to <new> by tools/rename.py (to-class: retail vftable
0x... slot N)`, writes no `name_basis.csv` row (the identifier is the one C's
own declaration gives the slot) and carries an existing record. Run
`link_check` over the installer units before and after.

### `rename.py class --fold`: one retail class under two placeholders

Two seats sometimes row one class independently: its constructor as
`??0BfmeModuleDataSnapshotBase`, its destructor, deleting destructor and
vftable as `Rva001164B6`. A TU merge needs one spelling, and `class` cannot
give it (the new token already names rows, and it is a placeholder). This mode
folds the placeholder into the name the class's vftable already carries:

    python3 tools/rename.py class --fold BfmeModuleDataSnapshotBase --into Rva001164B6 --dry-run

It takes no `--basis`: no name is invented, and retail is the evidence. It
refuses unless all of these hold:

- OLD is a placeholder (`tools/name_metric.py`). A readable name never folds:
  into a placeholder only a `restored` revert may go, and choosing between two
  readable names is a naming decision. NEW may be readable; it keeps its basis.
- A constructor, destructor or deleting destructor row of OLD installs a
  retail vftable T as its own: a destructor's first `+0` store, or a
  constructor whose `+0` stores all install T. Every special-member row of OLD
  and NEW agrees (none owns another table; a constructor that also installs a
  base's table must include T).
- An OLD whose rows are only destructors and deleting destructors may own no
  table: one that stores none (an empty destructor), or one whose stores an
  inlined base destructor explains. When the base destructor is inline, MSVC
  drops the class's own stores that the base's overwrite, so the destructor's
  first `+0` store is the base's table. Each table such an OLD installs at
  `+d` must be the one every constructor of NEW installs last there (NEW's
  own), or the one a base constructor installs last there, where every
  constructor of NEW calls (E8) that base constructor. T is then NEW's own
  table: OLD's deleting destructor must sit in a slot of T, and each
  destructor of OLD must be called by one of them. Examples: DamageModule's
  0x004B96CC and CollideModule's 0x004BB68E (BehaviorModule's tables at `+0`
  and `+0x0C`, the class's own at `+0x10`). When the base's constructor is
  inline too, so no constructor of NEW calls one, a `+0` store may instead be
  the own table of a class registered in `canonical_classes.csv` (one of its
  special-member rows installs it as its own): ScriptGroup's 0x003B4100
  restores Snapshot's 0x00BBB554. At each displacement the stores run in
  order, the class's own table first and then its bases' (a base restore is
  never followed by the class's own table; a later base must be a base of the
  earlier one by its registered header).
- T's `??_7X@@6B@` names (`data_rows.csv`, the `data_ledger.csv` names that
  matched rows' relocations bind at T, and, because that ledger is a cache that
  lags new rows, the DIR32 bindings the installing rows' own objects make at T
  now) include NEW and no class but OLD and NEW.
- A class with several bases reaches its later base subobjects' tables through
  a deleting destructor's adjustor thunk (`??_EX@@WM@AEPAXI@Z`, `this -= 0xC`).
  The thunk must sit in a slot of the class's own table at that displacement:
  the one a row owning T installs there itself (a destructor's first store at
  `+disp`, a constructor's last), and every such row must agree. That secondary
  table gets T's ICF and slot checks, and the thunk counts as a special-member
  kind of its own, so it never collides with the primary deleting destructor.
- T is no ICF fold of distinct classes' tables (retail folds identical
  vftables: `0x007CEFA0` serves three constructors of different classes): no
  third class's special-member row installs T as its own, no slot of T holds a
  third class's deleting destructor, OLD's and NEW's deleting destructors sit
  in T's slots, and OLD and NEW do not both row one special-member kind (one
  class has one destructor; two constructor rows stay refused in this narrow
  mode).
- The usual `class` rules: OLD is not protected or registered in
  `canonical_classes.csv`, is global and no template, is no function's
  identifier, and keys no frozen register; a registered NEW is refused where
  the fold would create a private copy of it, unless every unit that spells
  OLD (text or object) comes `--prepared REL=FILE` on NEW's shared header and
  spells OLD nowhere (class_gate and the byte gate judge those units); no unit
  may end up declaring NEW twice or deriving NEW from itself.
- With prepared units, `--access public|protected|private` respells the folded
  virtual destructor family (`??1`, `??_G`, `??_E` and their adjustor thunks,
  with their `__ehhandler$` rows) to that access, where NEW's shared header
  declares its destructor with another access than the placeholder rows spell
  (CreateModuleClass.h: protected, `??1CreateModule@@MAE@XZ`, the spelling its
  consumers reference; `Rva004B8CDE` rowed it public). Access is no retail fact:
  the header's declaration and the prepared units' bytes decide it. A
  non-virtual family is refused, and without prepared units so is `--access`.

Each renamed row and data row is tombstoned `Renamed to <new> by
tools/rename.py (fold: retail vftable 0x...)`. No `name_basis.csv` row is
written for the fold itself; records scoped by OLD (`OLD::m_x`) are carried. A
respelled pin that becomes a row's own name at its own address (the alias the
second name needed) is dropped; one that would give a name a second address is
refused. The byte gate, `pin_admission` and `pin_consistency --check` decide as
for any rename (commit checks). Because no record is written, `rename.py check`
does not watch the old spelling; the tombstones keep union merges from
reviving its rows.

### `rename.py class` on a registered class: key, contract and views together

A placeholder class registered in `reverse/canonical_classes.csv` has a
canonical header, a contract (`reverse/class_contracts/<class>.json`) and usually
private views in units that have not adopted the header yet
(`reverse/header_queue.tsv`). `class --name OLD --new NEW` renames all of them in
one commit:

    python3 tools/rename.py class --name Rva001DFEAABase --new FXNugget \
        --basis inferred --evidence agree:<id> --max-files 40 --dry-run

On top of the ordinary token rewrite, it:

- re-keys the registry row and the contract note in it;
- moves the contract to `NEW.json` with `git mv` and respells it;
- re-keys OLD's `header_queue.tsv` rows, keeping each row's source and RVAs.

The header keeps its path: the file kind refuses a header other files include,
and an `#include` path is not a spelling of the type. After `./build.sh`, no
rebuilt object may name a symbol of the old spelling.

**Approval.** An inferred name needs the agreement reached at the canonical
header's key (`<header>|class||OLD`): `name_lane.py next --registered OLD`
serves it, two blind votes from distinct workers agree it, and the agreement
must be for this exact key and NEW. An agreement reached at a private view's key
is refused. A canonical basis needs its proof, as for any rename. The same
route serves the class's placeholder members (`--key` serves one alone).
`rename.py member` lands a member on a registered class without renaming the
class; it also respells the contract field of that name, leaves the contract
alone when it already names the field NEW (the views' majority), and refuses
when the contract names that field neither way, names NEW at another offset
than the placeholder spells, or spells OLD outside its top-level field.

**What the gates credit.** `class_gate` credits a unit that declared
`class OLD` at HEAD and now declares `class NEW` (the same private view, not a
new one). `repair_queue verify-removed` treats a re-keyed queue row as carried,
not retired. Both credits need all of the following in the commit:

- a `name_basis.csv` class record;
- the one registry key moved to NEW under the same header;
- `rename.py verify-record` accepting the record.

`verify-record` recomputes an agreement from the votes, re-checks a canonical
citation (a path inside `reference/open-bfme-1` is read at the commit the base
pins), and proves a revert to be the exact inverse. It runs from the base
revision's own tools (HEAD, or the push base) against the base revision's data.
Votes, agreements and resolutions therefore land in their own `name_lane`
commits before the rename that cites them; nothing a commit adds to a vote
ledger counts towards its own credit. A vote's own row names the key and the
spelling but not the text, so `name_lane.py submit` records beside each vote the
sha256 of the source it served the voter (`reverse/name_vote_sources.csv`). Every
vote counted for the name needs that row, and its fingerprint must be the sha256
of the base's canonical header, the text the rename is applied to. A row binds
only when it is added. `class_gate.py --staged` (pre-commit) keeps
`name_vote_sources.csv` append-only (no line of the parent's copy modified or
deleted). It also requires each added row's hash to equal the sha256 of the
header it names in that commit's index. Pre-push applies the same rule to every
commit of the outgoing range against its parent (`--vote-sources-range`), so a
batch can't add a fingerprint and rewrite it in a later commit. A push with no
known remote base reads the file's whole history from the root commit instead.
Every git call of the registered-class rename, its `verify-record` credit check and
prepared-unit proof, `class_gate.py`, `repair_queue.py`'s base `verify-record`, and
both hooks run with `GIT_NO_REPLACE_OBJECTS=1`, so a `git replace` object never
stands in for history they trust. Neither tool sets it on import, so other lanes'
git calls are unaffected.

Every history-dependent path first runs one preflight (`tools/git_trust.py`). The
repository it judges is the tool's own checkout, found from its root with `GIT_DIR`,
`GIT_WORK_TREE`, `GIT_COMMON_DIR` and `GIT_INDEX_FILE` unset. Each of those that is
set must resolve to exactly that repository's paths; `GIT_INDEX_FILE`, which git
exports to hooks, must sit inside its git directory, which is also where rename.py
keeps its private staged index while it runs the gates. Every trusted git call then runs
from the root with the three selection variables dropped, so it cannot read another
repository. The preflight also refuses when local git state could rewrite what git
reports as history: a shallow clone, an `info/grafts` file, any ref under
`refs/replace/`, or `GIT_GRAFT_FILE` or `GIT_REPLACE_REF_BASE` set. A failed `git
diff --cached` in class_gate stops the gate; it never reads as nothing staged.
Alternates and borrowed objects (`objects/info/alternates`, as srv1's worktrees use)
are allowed: they add objects but never change which object a name means. A corrupt
or substituted object store is outside what this guards. It runs at the start of `verify-record`, the revert of a
registered class, `--prepared`'s baseline and proof, `class_gate.py --staged` and
`--vote-sources-range`, and repair_queue's `verify-removed`, `verify-missing`,
`retire`, `retired` and header-queue reads. repair_queue keeps an inline copy (the
hooks run it from stdin), and its census and stub-receipt ancestry checks give no
answer under such state. Both hooks carry the same rule in shell, before any tool
runs. The credit
readers accept a row only if history adds it once and
never touches it again, with the hash of the header as it stood in that adding
commit. A header edited before, with or after the votes earns nothing, in
whatever order the commits land, and so does a vote recorded without a
fingerprint or a fingerprint rewritten later. A commit can't loosen the check
that judges it. The credits apply only to commits made after this landed.

**Refusals.** The rename refuses:

- a readable registered class (two real names are a reconciliation);
- two registry rows for OLD;
- a missing contract, a contract of another class, or an orphan contract;
- a NEW already registered or holding a contract;
- `--fold` of a registered OLD.

**Reverting.** An inferred landing goes back with
`rename.py revert --record <id> --reason TEXT`. For a registered class the revert
*is* the landing commit's diff reversed over HEAD, so every file it touched,
including the key, contract and queue rows, comes back byte for byte. To that the
revert adds the one restored `name_basis.csv` record and the `(restored)`
tombstones, and lifts the landing's own tombstones.

The gates credit a revert only as that exact inverse. The landing's reversed
diff must give the commit's tree exactly. The two ledgers must change by an
ordered diff, because name protection reads a name's last record, so a
reordered, repeated or extra line changes meaning:
- `name_basis.csv` keeps every line in place and gains only the restored record
  at the end;
- `deleted_rows.csv` keeps every line in place except the lifted tombstones, and
  gains only the restored ones at the end.

A revert that also edits anything else gets no credit. A landing that a later
commit has touched doesn't reverse cleanly, so revert it by hand.

**A NEW the tree already spells.** A placeholder's retail name is often spelled
already. Other units forward-declare `class FXNugget;`, keep views deriving their
nuggets from it, and take `FXNugget *` parameters, while every row of the class
sits under the placeholder. `--merge-existing` lets the rename take such a NEW,
on three conditions:

- NEW appears only as a type, never as the scope or identifier of a row, pin or
  data row (one that owns a row is a fold), and is not itself registered.
- No unit outside the rewrite already defines a symbol the respelling creates
  (checked in its objects and in its text, `NEW::method(`).
- Every existing *definition* of NEW is compiled (`tools/class_layouts.py`,
  CodeView). Each leaf it lays out must be one of OLD's contract leaves with the
  same offset, size, kind and name:
  - the vfptr is a leaf, and the view has one exactly when the contract does;
  - every named member is a leaf, never padding;
  - member aggregates are read as their scalars (`member.field`).

  The view must fit within the contract's sizeof. Only scalars compare: a
  primitive, a pointer, or the vfptr. Fail closed: the merge refuses anything it
  cannot reduce to scalars, never guessing from a type name. That covers a
  forward-only or unparsed layout, any base (virtual or not), a bitfield, an
  array, a member aggregate it cannot expand, and a contract field that is not a
  scalar. The definers' units and the consumers of the respelled symbols are
  verified with the rest; only declarations and pointer or reference uses stay
  unexamined.

The intended path leaves nothing for that comparison. Every private view of NEW is
first reshaped onto the canonical class, either in its own commit or passed with
the rename as `--prepared REL=FILE` (repeatable). A prepared unit is part of the
rewrite and is byte-verified with it. It must be a tracked, clean, matched `Code/`
C++ source that reads as after the rename:
- no OLD outside the kept header's `#include` path;
- no body of NEW of its own (a class derived from NEW is fine);
- `#include` of the canonical header wherever its code spells NEW;
- no second body (`NEW::m(`) of a row the rename respells, unless the unit owns
  that row;
- no `#line` directive of its own, in any spelling the preprocessor could read
  as one: `#line N`, `# N`, after a UTF-8 BOM anywhere, across a
  backslash-newline, with `??=` or `%:`, or with a comment between `#` and
  `line`. A file with a UTF-16 or UTF-32 BOM, or any NUL byte, refuses too: the
  compiler would decode it differently from the scan. Such a directive would make
  the preprocessor attribute the unit's own lines to any file it names.

The proof is fixed before anything is written. At the merge base with
`refs/remotes/origin/master` (never a local branch of that name),
`canonical_classes.csv`, OLD's contract and every prepared unit
must read exactly as in the working tree. An edit in an outgoing commit or in
the tree refuses (a contract widened to fit a prepared layout proves nothing), so
land such a change first. The contract the proof compares with is master's,
respelled. The `NEW.json` the transaction writes must be that respelling byte for
byte.

Those text checks are only a fast pre-filter; `#if 0`, `__declspec(...)` or a
macro can hide a private copy from them. After `./build.sh`, the rename refuses,
and every file is restored, unless each prepared unit:
- compiles with exactly the flags the build gave master's copy. They are read by
  `build.source_extra_flags`, the build's own reading of `// cl:`, never parsed
  here. `/Dint=double`, an indented decoy line or a BOM in front of the directive
  all show up there.
- lists the canonical header in the compiler's own include list (`cl -E
  -showIncludes` under its build command; no object is written);
- includes no file that carries a `#line` directive, read by the same byte-level
  scan, so every line marker in the preprocessed output is the compiler's own (no
  header on master carries one);
- defines NEW, once preprocessed, only through the canonical header (markers
  compared as full repo-relative paths), with no definition of OLD left;
- holds one complete CodeView record of NEW equal to master's contract: sizeof,
  base names, every field's offset, name, size and i4-level kind (the vfptr as
  the contract's `VPTR` field), and every virtual slot. An absent, forward-only
  or unparsed record (two complete records of the name that differ in fields or
  virtual slots) refuses.

The 14 units on master that carry retail `#line` markers therefore cannot be
prepared.

A merge may be **inferred**: two blind votes through `name_lane.py next
--registered OLD`, which accepts an answer the tree already spells when it is
such a merge, and lands it with `--merge-existing`. That is safe only because the
revert is exact. A revert is the reversed landing diff, and the landing never
touched NEW's pre-existing spellings, so they come back exactly as they were.

On 2026-11-07, FXNugget would refuse on all three of these:

- `FXList.cpp`'s second `FXNugget::doFXObj` body;
- `EvaEventFXNugget.cpp`'s view, a 324-byte opaque array at `+0x4`;
- the Zero Hour shim `reference/shims/zh_outofline/GameClient/FXList.h`,
  whose includers report no layout to compare.

Its prepared path also refuses until the contract equals the compiled canonical
header. `FXNugget.json` names `m_filter08`/`m_filter0C` as filter structs and
slot 3 `slot3()`. The header compiles `m_08`/`m_0C`, adds `m_10`, `m_5C`,
`m_A8` and `m_F4`, and declares slot 3 as `slot03(AssetList*,int)`. Reconcile the
contract through the class-contract and header-adoption lane
(`class_contract.py --write`, then `header_adopt_lane.py`) as its own verified
change, never by rewriting it to fit a rename.

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

### `rename.py global --retype`: a rowed global's type and extent

A placeholder global can be smaller than the retail object it stands for: `unsigned
g_00DFE1AC;` (4 bytes) where retail's code reads +4 and +8 of a 12-byte vector, which
`tools/image_iso.py` reports as out-of-object pointers. The type is part of the mangled
name, so `global --new` cannot change it. `--retype` changes the type and size and keeps
the identifier:

```sh
python3 tools/rename.py global --name '?g_00DFE1AC@@3IA' --new '?g_00DFE1AC@@3PAIA' \
    --retype 'unsigned int [3]' --size 12 --evidence '<what reads the extent>' \
    [--initializer '<retail bytes>'] [--prepared Code/X.cpp=FILE ...]
```

It respells every declaration, re-keys the data row (name and size), pins, notes and the
`data_ledger.csv` row at the address, tombstones the old name, and removes each
`/alternatename` that named the old symbol and is gone, with its `hatch_baseline.tsv`
occurrence. A consumer whose uses must change shape (a member call through a class-typed
extern) comes as `--prepared` bytes. It refuses an extent that another data row, function
row, converged address or ledger name overlaps, one that leaves its retail section,
non-zero retail bytes without `--initializer`, a second definition, an initializer it
cannot respell, a converged address, and the old symbol surviving anywhere. It verifies
with `./build.sh` (which runs `data_rows.py` on the new row: compiler sizeof, retail
bytes, relocations) and then reads the rebuilt objects: the owner defines the new symbol
once, nothing names the old one, and the owner does not construct the global itself.
Every rebuilt unit is also run through the compiler's preprocessor alone (`cl -E` under its
own flags, writing no object), and every occurrence of the identifier there must be a
declaration of the new type with C++ linkage, outside any `extern "C"` block, or a plain use
(an operand, an initializer, a declared function's argument, a cast's operand); anything it
cannot classify refuses. Whether a statement is a declaration is decided by its shape, not
by knowing its type names: a run of names (qualified, templated or attributes) followed only
by declarator punctuation (`*`, `&`, `(`, cv-qualifiers) must parse as a declaration of the
new type, a function head's parameters included, or it refuses. That covers declarations macros build, including nested arguments, and the units
a computed include, a `/FI` forced include or a `##` paste reaches (the last selected by
the identifier's prefixes and suffixes appearing as tokens next to a paste). The new type
must be arithmetic (an integer or float, or an array of one); an initializer may not spell
a number in retail's address range, and an extent where retail relocates a word refuses.

That last check matters for these placeholders: retail builds them in a rowed initializer
(`Rva007ABB96AllocCtorInits`) and destroys them in a rowed atexit thunk, and the exit link
runs that initializer through its bridge. Retyped to the class (`_STL::vector<void *>`), the
owner's object would register its own `??__E` initializer too, constructing and destroying
the global twice. So a retype gives the extent (`unsigned int [3]`) and consumers view it
through a cast, until real statics replace the bridge.

Known limits, each refused or out of reach rather than passed wrongly:

- A target type spelled through a typedef (`--retype 'UINT [3]'`) is refused: give the
  builtin spelling.
- A `##` paste that splits the identifier below token level (`g_00 ## DFE1AC`) does not
  select the unit; prefixes and suffixes are matched as whole tokens only.
- `decltype(...)` in a declaration and a name that is both a parenthesised typedef and a
  function (`typedef int (T); void T(int); T(g);`) are not modelled; such statements refuse.
- A functional cast in a statement of its own (`unsigned(g) + 1;`) is refused as
  declaration-shaped. A declared function's call passes with the identifier first in its
  arguments, alone or behind `&`, `*` or extra parentheses (`memset(&g, 0, 16)`), unless the
  function's name is also a type.

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

ANSWER.json maps each served source to its answers, and each answer is keyed by
`answer_key()`, **not** by the pipe-separated ledger key:

    {"Code/GameEngine/Source/Common/X.cpp": {
        "SomeClass":              "RealClass",   // class, function, global: bare identifier
        "SomeClass::m_14":        "m_hitPoints", // member: scope::ident  (two colons)
        "SomeClass::method:a":    "angle",       // param/local: scope:ident (one colon)
        "SomeClass::method:b":    "skip"}}       // skip costs nothing; omitted keys are skips too

The brief `next` writes already prints these in its first column, so copy that column
rather than building a key. An answer key the session was not served is a hard error
(`keys not served for <file>`), and the whole submit is refused. When a session served
exactly one file you may drop the outer level and pass the inner map alone; `submit`
wraps it for you. A value may also be an object carrying a meaning/role instead of a
bare string. Submit consumes the session, so run `validate` first — and note `validate`
exits non-zero on an all-skip file, so never chain the two with `&&`.

A skipped key is **never consumed**: it stays in the queue and `next` will serve it again,
to you, under any later session id. A round that returns only keys you already skipped
means the lane has nothing new for you; stop there instead of looping on repeats.

`apply` plans all selected live names in memory, running each proposal's normal
agreement, protection, scope and per-name `--max-files` checks. Planning refusals
stay blocked. Accepted plans share one claim operation, recovery journal, native
verification of every affected source, and set of ledger and consumer checks.
The union may contain more sources than one name's `--max-files` bound; every
selected source is still verified.

When claims are enabled, `apply` first reads one shared claim snapshot and
defers approvals whose known owner file, RVA or class is held by another worker.
The standard claim footprints exclude our own claims and include locks expanded
from other workers' RVA/class claims. Deferred approvals are unchanged, do not
consume `--limit`, and can be retried once available. This happens before file
analysis or rename planning in all apply modes. Ordinary acquisition still
rechecks claims before writing, including consumer scopes discovered by planning.

If a combined build or ledger check fails, the whole transaction is restored.
Static pin admission runs before claims and the native build; proof-dependent
pin decisions remain in the full final gate. Exact pin diagnostics select a
suspect group, expanded to include plans sharing affected sources. Ambiguous
failures fall back to splitting. A retry session keeps fenced claims until the
run ends, releases only unused newly acquired claims, and retains claims needed
by verified changes. Scope keys are normalized across acquisition, recovery
journals and retention, so a file/class lease is not accidentally released after
a successful group. Prepared inferred plans are reused only when their recorded
reads and tracked searches still match. A lightweight object and dependency-file
stamp, including source-file stamps, catches builds and source edits by other workers; object consumer results are rechecked
when that stamp changes. Outcome rows are
flushed when the run exits, including on interruption, so they do not invalidate
otherwise reusable plans. Donor parameter lookups are batched across the selected
files before ownership checks. Each retry verifies
its full source and consumer scope; shared sources are restored exactly and
reverified when edited again. A failed group never removes an earlier successful
group. An interruption follows the ordinary journal recovery path.

Function/global planning shares text and object searches across the selected
names. Candidate text files are found together per search-root group; each
individual query still goes through Git on those candidates to retain exact
word, binary-file and pathspec behavior. Current-object symbol checks and stale
source-text checks are scanned once for all prepared symbols, retaining a separate
consumer set for each name. Both search snapshots are rebuilt for every retry
under the ledger lock; newly introduced scope spellings use the normal searches.
Static pin conflicts are also checked on each prepared pin edit so an invalid
proposal can remain blocked while the valid proposals proceed together. The
combined pin check and full verification still run on the accepted union.
Class symbols also join the shared object scan, retaining a separate exact
consumer set for each class. Cheap name collisions, protected source checks and
text-only scope overflow are refused before starting object lookup.

If claim acquisition races the preflight snapshot, the refused claim keys are
matched back to their plans. Those approvals stay agreed, and the unheld names
are retried together without binary-splitting the claim failure. When the
compiler names a failing translation unit, it narrows the suspect group; a
source location alone does not prove every name touching that source is invalid.
An unchanged direct include with C1083 proves that source cannot build: its
proposals are blocked once and the clean proposals are retried together.
Other compiler errors retain the conservative split fallback within the suspect
group. Diagnostics belong to one verification context and survive timing wrappers.

Only a missing-include failure with sufficient compiler-input evidence is
persistently suppressed. Its fingerprint covers indexed and dirty repository
inputs (including submodules and new headers), compiler commands and executables,
include inventories, available dependency receipts, missing-header search paths,
and the requested scope bound. Missing proof disables suppression. The cache
merges per-key updates under a lock so concurrent workers retain each other's
records. `--retry-blocked --retry-unchanged` forces an attempt despite an unchanged
fingerprint. Transient failures and other unexplained errors are always eligible
for an explicit retry. Class plans report text and object-consumer fan-out before
rewriting sources or ledgers.

Use `apply --per-file` for the previous grouping of same-file members and scoped
names, or `apply --no-batch` for individual verification. Repeat `--key KEY` to
select exact agreements; `--limit` still bounds selected names for the entire run.

`next` serves one matched, non-generated source with the placeholders that
this file alone decides. That covers the functions it owns rows for, the classes only it defines and their
members, and the file globals it owns. Locals and parameters use `scoped next`.
`next` writes a brief to `build/name_lane/briefs/<session>.txt` with the
style rules: types `CamelCase`, members `m_camelCase`, and functions/methods
following the class's convention. Answer each key with a name or `"skip"` in a JSON file written with a
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

**Parameters and locals** use the complete-function scoped batch workflow at
the start of this document: native sub-agent proposals, parent review and one
combined application/verification. They create no new voting or approval rows.

Functions, classes, members and globals still require two independent agents
to propose a name blind and agree. BFME 1 measured the original blanket rule's
reason on 2026-09-29: one model alone named about 60% of
placeholders right and 2-9% of them misleadingly; two agreeing blind proposals were about
80% right and never misleading.

- Each shared-name vote is stored in `reverse/name_votes.csv` only as
  `sha256(key|canon(name))[:24]`. No name text enters the repository until a
  second worker matches it.
- `canon()` folds word order, plurals and common abbreviations, so
  `m_ladderComboBox` and `m_comboBoxLadder` count as one vote.
- Agreement counts distinct **workers**, not session labels. The worker id
  comes from the environment (`BFME_CLAIM_OWNER` or `BFME_RUN_ID`, otherwise the harness
  session, otherwise `tools/claims.py`'s owner), stored hashed. Print yours with
  `python3 tools/name_agreement.py whoami`. An orchestrator running blind seats
  gives each seat its own `BFME_CLAIM_OWNER`, as it already does for claims.
- Shared names need two or more workers and a lead of `--lead` (2) over every
  rival spelling; `--min-models` can require distinct model labels.
- `rename.py` treats `name_agreed.csv` only as an index. It recomputes the
  agreement from the votes, so a hand-written agreement row authorises
  nothing.

Existing votes and approvals are preserved. `apply` may still land already
approved locals/parameters through the existing agreement, collision, byte and
ledger checks, and landed names remain reversible. Historical approval rules
(including single-worker scoped approvals and late-rival checks) remain in the
proof engine solely to read and verify that backlog. Unfinished scoped tasks
need a fresh scoped review; do not add votes, meaning annotations or resolutions
to complete them. Old hashes alone do not recover the proposed spelling.

Do not show your proposal to another seat or read theirs, and do not cast votes for a
second seat yourself.

## Historical scoped voting meanings (ledger reference)

This section documents existing scoped vote records. New scoped names use the
batch workflow above; the voting commands no longer accept these answers.

A historical scoped answer could include a role descriptor instead of just a string:

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

Historical `reverse/name_meanings.csv` rows store only a descriptor hash, bound to the exact
key, spelling vote, worker, model, session and date in `name_votes.csv`. No
role prose was exposed to the next blind worker. The historical submit path
wrote votes and meanings together. A meaning-based
agreement id carries the descriptor hash, and `rename.py` independently checks
its support. The chosen identifier must be one someone actually proposed.
An unbacked metadata/approval row grants no support. Disputing a meaning-based
name also blocks that meaning under alternative spellings.

Existing plain-string and annotated votes remain readable. An old vote may join an
annotated role only for the exact same spelling with one unambiguous meaning;
an old differently spelled vote has no recoverable role and remains a rival.
The first approved spelling can remain while other equivalent proposals add
support. Functions, classes, members and globals retain spelling agreement in
this first version. Meaning agreement is inferred and revocable, not proof of
original naming or semantic correctness. Byte and ledger checks are unchanged.

Historical clarification records bound an annotation to the original vote's
worker/model/session/date, without changing that vote or adding a voter.
Those annotations remain part of the proof for already approved names.
`next --meaning-review-only` now redirects to `scoped next`; unfinished scoped
disagreements are reviewed from current code instead of extending old voting
rounds. The normal voting picker serves shared names only.

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

Renames recover zero bytes. Keep shared-name changes coherent and keep a class
rename in its own commit. Scoped names use one reviewed batch and one combined
verification; a successful batch of hundreds does not need splitting into small
commits. The lander does the following:

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
signature change, a cross-directory move), a hand rename must still (a
non-virtual decoration that retail's vtable contradicts is no hand rename: use
`function --virtual` above):

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

### Existing-type reconciliation packets

`python3 tools/name_lane.py reconcile [--key SOURCE|class||OLD]` prints JSON
packets for pending class names that collide with existing declarations. Quote
the key in a shell. Each packet includes the private declaration, existing
views, content hashes, registered header, available contract and next checks.
The command changes no source, votes or status and does not certify identity.
A reviewer must prove identity from uses and target evidence, reconcile layout
and ABI, then verify the source and affected consumers in a separate commit.
Equal fields alone do not justify replacing a private view with a shared type.

### Larger verified fan-out

`name_lane.py apply --max-files 80` raises the default 25-source planning bound
for a deliberate larger batch, including transitive header consumers. Every
affected source remains in the verification set; claims, ledger checks, byte
checks, failure rollback and publication link audit still apply. The limit
must be positive. Increase it only when prepared to verify that whole fan-out.

Agents applying names: when the source-count limit is the only blocker, inspect
the affected sources and header consumers, choose a bound large enough for that
rename, and retry the specific approval. A large TU assignment is context, not
the affected-source count. Keep the bound finite and all verification enabled;
raising it authorizes more verification work, never fewer checks. For example,
a reviewed rename affecting hundreds of sources can be retried with:

```sh
python3 tools/name_lane.py apply --retry-blocked --key "SOURCE|KIND|SCOPE|OLD" --max-files 400
```

Replace the key and bound with the actual approval and reviewed fan-out. If the
larger run discovers more consumers, inspect that expanded scope before raising
the bound again. Other blockers still require their own repair. This is an
explicit agent decision; the tool does not automatically raise limits or retry.

### Locals that shadow an outer name

The naming lane asks the engine to prove a unique ordinary scalar binding
before rewriting it. Uses before the declaration or after its block stay on
the outer name, as do the outer declaration and other functions. The direct
CLI exposes this as `rename.py local --local-binding`. The proof currently
covers simple built-in scalar declarations in ordinary balanced blocks;
control initializers, arrays, local types, lambdas and ambiguous declarations
retain conservative handling. Macros, member-qualified uses within the binding,
new-name captures, optimization restrictions and canonical-name protections
remain checked. Exact inverse restoration uses the same binding proof.
Precise inferred landings also append `reverse/name_bindings.csv`; stage that
file with the basis and source. It binds the approval and source to a hash of
the outer source context and included headers. Reversal may reuse the proof
only while that context is unchanged; otherwise ordinary conservative checks
apply. Header edits or edits outside the selected function can therefore
require a fresh review. Legacy landings do not gain this exception.

### Apply approved names regularly

An integrator can run `python3 tools/name_lane.py apply --limit 20` after each
integration batch. It attempts at most 20 eligible approvals; the rest keep
waiting, and blocked entries need an explicit `--retry-blocked` to be retried.
Existing key/worker filters and the source fan-out bound still compose.

Normal `submit ANSWER.json --session S --model M` records votes, then claims and
applies every approval created by that submission as one verified run-wide batch.
It never selects unrelated ready backlog or starts an apply when nothing newly
agreed. `--apply-ready 5` explicitly caps that immediate application at five;
without the flag there is no arbitrary name-count cap on this submission's batch.
`--max-files` retains the per-plan affected-source bound and all units are verified.
Failed verification restores source and records blocked outcomes while retaining
the votes. Neither command commits or pushes.

Use `submit --propose-only` only for an explicitly proposal-only/read-only pass:
it records votes without applying source changes or dispatching a reviewer.
`--no-auto-review` retains immediate application but suppresses reviewer dispatch
for that submission. Prefer completing a subsystem batch through application to
accumulating separate blanket voting rounds.

### Automatically dispatch independent second reviews

Normal submission automatically configures a stable reviewer seat when shared
names need an independent second vote and no fleet configuration exists. It
discovers an installed Codex, Claude Code or OpenCode CLI, preferring the
submitting CLI when identifiable. Existing configurations, especially an explicit
`review disable`, are never replaced. The native scoped batch path does not
launch this external reviewer. Historical approved scoped names can still be
applied without dispatching an external reviewer.
Missing runtimes/models are reported explicitly; recorded votes are retained.

Override the discovered runner/model once per local fleet when desired:

```sh
python3 tools/name_lane.py review configure
python3 tools/name_lane.py review configure --provider claude --model sonnet
python3 tools/name_lane.py review configure --provider opencode --model provider/model
python3 tools/name_lane.py review configure --provider t3 --t3-backend codex
```

Codex uses its configured model. Claude uses `ANTHROPIC_MODEL`, its user model
setting, or the CLI's `sonnet` alias. OpenCode uses a configured `provider/model`
from its JSON/JSONC configuration or an explicit `--model`; no paid model is
guessed when it has no configured choice. `--provider t3` supports T3 Code by
launching a fresh underlying Codex/Claude/OpenCode CLI, selected automatically or
with `--t3-backend`. It never starts a T3 server or reuses an existing T3 thread.
The T3 backend can also be selected with `BFME_NAME_REVIEW_T3_BACKEND`.
See the [T3 provider requirements](https://github.com/pingdotgg/t3code#requirements).

Automatic review enables real model execution and uses the chosen account's
credits. Each subsequent submission with new votes
starts a background reviewer that drains eligible work in successive batches.
The submitting worker can continue immediately.
A shared lock permits one AI reviewer at a time, with at most ten keys, six
files, 150,000 packet characters and a 300-second model timeout per batch.
Ten keys is a batch size, not a total review limit. The reviewer reloads the
queue between batches and continues until eligible work is exhausted. Existing
enabled configurations inherit this behavior. `review configure --max-batches N`
sets an optional run budget; reaching it reports `paused` / `batch_limit`.
Busy clients exit while the active reviewer continues draining. A model or
validation error stops the run; it never records a fabricated vote.
Completed skips/rejections are remembered per worker and source hash, so an
unchanged target is not repeatedly sent to the model.
Git worktrees share configuration and the lock through their common repository.
The automatically chosen reviewer identity is stable and account-scoped;
different contributors do not all cast votes as one identically named seat.
Independent clones should set `BFME_NAME_REVIEW_CONFIG` to the same fleet-local
configuration path to share the slot. Keep the reviewer identity stable across
batches; changing it to manufacture additional votes defeats independent review.

The child is a fresh process outside the repository with no inherited agent
session. Codex uses its ephemeral read-only mode; Claude disables tools, MCP,
session persistence and customizations while retaining subscription login;
OpenCode uses a fresh tool-denied session and a private server when supported.
It receives only source and target keys, with no original proposals or vote
hashes. It must use the packet only; tool-using, malformed, incomplete, failed
or timed-out answers contribute no votes. Source hashes and current protections
are rechecked through normal submission after it finishes. Different answers
remain disagreements unless the existing source-based comparison resolves them.

The integrator can run `python3 tools/name_lane.py apply --limit 20` for ready
approvals. A normal foreground or automatically dispatched `review` verifies and
applies each newly agreed review batch under the caller/integrator's identity,
after leaving the independent voter's identity. `review --propose-only` retains
proposal-only operation; `review --apply-ready 10` explicitly bounds application
to ten names across the run. All usual claims, quorum,
byte checks, consumer checks and failure rollback remain in force. Larger source
fan-out still requires an explicit reviewed `--max-files` override on apply.
No reviewer commits or pushes. Inspect `review status` and the local
`build/name_lane/reviewer-last.json` / `review-dispatch.log`; `review disable`
stops automatic launches and the active reviewer before its next batch.
`--apply-ready N` is a total apply bound across the run, not per batch.
An unavailable reviewer does not invent a second vote: another real worker can
use `next --review-only`. Worker and library integrations deliberately recording
proposals only must opt out explicitly at the CLI, or retain the proposal-only
library API. No command commits or pushes automatically.

### Validate proposals before voting

Run `python3 tools/name_lane.py validate ANSWER.json --session S --model M`
after writing proposals. It uses submission's source, eligibility, spelling,
collision and prior-vote checks, writes a local JSON report under
`build/name_lane/validation/`, and leaves votes, approvals and the served session
intact. Revise rejected answers once from their source and rejection reasons;
skip any that remain uncertain, then submit the final answer file normally.
Submission validates again against current inputs.

Member and method collision checks consider their own class and method bodies,
globals and preprocessor directives. An unrelated class may reuse a spelling.
Same-scope collisions and ambiguous ownership remain blocked. These are voting
prechecks: the rename planner still checks captures, inherited declarations,
cross-file consumers, claims and byte verification before applying any name.

The automatic reviewer validates its blind answers before recording its vote.
Invalid answers get one isolated revision containing only its own proposal,
the rejection reason and source. Valid answers are retained. The original
proposer's names remain hidden until the reviewer's final blind vote is fixed.
Revision reports live under the review job's `validation.json` and `revision/`.

Review packets normally fill the configured key and character budgets across
as many eligible files as fit. `review --strict-count` makes `--count` a hard
file limit. Oversized groups are split while selecting, rather than failing
after preparing an oversized packet. `next --max-chars N` exposes the same
packet bound for manual selection.

Repeated picks reuse expensive ownership discovery from a local picker cache
when repository and reference inputs are unchanged. Sources, headers, ledgers,
tooling and reference worktree changes invalidate it; naming votes and reviewed
acceptances are read fresh. Claims are refreshed on every pick. Submission and
application always run their ordinary current-input checks.

## Naming an unrowed data address

An unrowed datum has no C++ placeholder to rename. Register caller evidence
without creating an address-named global:

```sh
python3 tools/name_lane.py register-data --source Code/GameEngine/Source/Common/BigObfFallbacks.cpp --address 0xDC2274 --address-kind va --size 0x38 --type FallbackCtx --users Code/GameEngine/Source/Common/ConstIntGettersAddr.cpp --evidence "Code/GameEngine/Source/Common/ConstIntGettersAddr.cpp:254"
```

This records facts only in `reverse/name_data_requests.csv` and prints a naming
key plus the `next --file ... --key ... --session ... --model ...` command.
It proposes no name, creates no source definition or data row, and adds no hatch.
Stage the request register with the later votes, approval, definition and row.
The register is created on first use; requests must fit unowned, non-executable
retail data and may not overlap a verified data row, a ledger row with a source
owner, or a converged global owner. An unowned ledger row has only a next-address
upper bound: registration reports overlapping bounds as notes and allows them.
After admission, loading or regenerating the ledger inserts the verified extent
and shortens the preceding heuristic bound to the new address; the following
row and verified extents keep their own bounds.
VA inputs are normalized to RVA. Type is a caller-supplied type/struct hint,
not proof of original source identity. The first registrant's worker identity
is recorded in the key and cannot vote on that request. Two other independent
workers must agree. Re-registering identical facts preserves that registrant.
User sources and their hashes travel in the human brief and machine packet.
Free-text evidence prose does not: only validated repository file:line references
are shown, so an evidence sentence cannot plant a proposed name in blind briefs.
Admission recomputes quorum with registrant votes excluded, including forged
historical vote rows. Proposals and competing names remain hidden.
The key binds address, extent, type, users and evidence, so changing those facts
cannot reuse an old agreement.

Registration does not start either voter. An independent first agent uses
`next --file SOURCE --key 'KEY' --session S --model MODEL`, reads the printed
brief, writes its answer JSON, and runs `submit ANSWER.json --session S --model MODEL`.
Normal `submit` records that first vote and can dispatch a fresh independent
reviewer CLI for the second vote, with the same sanitized request facts.
`review status` reports the configured runner; `review configure` discovers an
installed CLI, and `review run --key 'KEY'` retries pending second reviews.
An unavailable or explicitly disabled runner leaves the second vote pending.
Alternatively a second independent agent uses `next --review-only --file SOURCE
--key 'KEY' --session S2 --model MODEL2` and `submit` under its own stable worker
identity. Neither changing a session label nor changing a model label creates
an independent voter; the registrant must not adopt another identity to vote.

Use the ordinary `next` and `submit` flow on two independent seats with their
existing distinct worker identities. The ordinary worker-count, spelling,
source-snapshot, canonical-name and collision protections apply. A single vote,
a disagreement, or a hand-written approval does not authorize admission.
Normal submit/apply leaves an agreed unrowed key waiting and prints an admission
command, since there is no old C++ symbol to rename. No inferred-name basis or
matched-data credit is recorded merely for agreeing on a spelling.

After agreement, claim the data RVA and defining source, check the frozen-file
rule, write a real typed C++ definition with the agreed identifier and retail
initializer, and byte-build that source normally. Then admit its exact external
COFF symbol:

```sh
python3 tools/data_rows.py --admit-agreed APPROVAL_ID --symbol 'EXACT_COFF_SYMBOL' --model MODEL
```

Admission rechecks the registered range and the original blind votes, requires
the exact agreed non-address-derived identifier and a current compiler receipt,
refuses names already used by data rows, functions or pins (including identifier
fragments), and refuses names already present in `data_converged.csv`,
and uses the existing data verifier for compiled sizeof/allocation extent,
retail bytes and all relocations. It never compiles a replacement source into
`build/match`; ordinary sizeof probes remain under `build/data_rows`. Failure
restores the data ledger, basis and agreement status through the rename journal.
The normal `rename.ledger_checks` run before and after the transaction against
its private index, including the caller's unchanged source and naming-input
snapshots. A ledger refusal rolls back the admission too.
Success writes the matched row, a `global` basis record with `inferred` and
`agree:APPROVAL_ID`, and a landed approval. It keeps the source/RVA claims until
publication and prints the explicit paths to stage and claims to release.
Neither command commits, pushes, weakens a gate, or admits a hatch. Hand-added
address-named source/data rows remain subject to the existing hatch gate.

Registered data requests bypass the ordinary 15,000-character picker limit.
Oversized defining/user files are represented by numbered excerpts around the
validated evidence references in manual and automatic review packets. The full
source hashes still protect serving and submission; excerpts do not weaken
staleness checks. Missing references are reported in the packet so the voter
can inspect the file or skip. Picker exclusions report reasons and a bounded
sample of paths instead of silently dropping oversized files.

For reviewed (`nr-`) unrowed data admissions, the tool recovers the exact source
from the commit recording the resolution. Only inserted file-scope definitions
of registered, agreed globals with their exact registered type are allowed;
initializers must be literal aggregates. Comments and whitespace may accompany
these definitions. Removed/replaced lines, extra symbols, directives and runtime
initializer expressions are refused. Every added agreed definition (including
peers awaiting admission) must pass compiled extent, retail-byte and relocation
verification. The ordinary rename source fingerprint rule is unchanged.
