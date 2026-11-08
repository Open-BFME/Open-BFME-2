# Consolidation: one retail translation unit, one source file

The ledger mostly holds one function per file (about 23,000 units under `Code/`).
Retail was linked from real translation units, and a TU's functions sit next to
each other in `.text` in object order. This lane merges the small files back into
the TU retail built them from, one TU at a time, without losing a matched row.

The retail FESL SDK diagnostics name a separate
`\views\feslbuild_main\jabba\fesl\source\` build root. The TU mapper recognises
that exact root and represents its source-relative paths under
`Code/Libraries/Source/Fesl/`. This repository location does not claim that the
SDK's original path was inside BFME 2's `Code/` tree. Unrecognised external
paths and header paths do not supply TU anchors.

Five tools support the workflow; a seat does the judgement.

Start a consolidation or subsystem naming pass with the read-only
[evidence catalogue and naming planner](#evidence-catalogue-and-naming-packets).
Its investigation packets support work selection and prerequisite repairs;
merges continue through `tools/tu_skeleton.py` and the normal verification gates.

| Tool | Role |
|---|---|
| `tools/name_lane.py consolidate` | The evidence planner: catalogues original paths and donor structure, identifies candidate groups and flags routing, declaration, include and compiler prerequisites. |
| `tools/tu_map.py` | Which TU each retail function came from: `__FILE__` strings, Zero Hour definitions and class sites, whole vendored upstream files (L), WorldBuilder leads that corroborate a hinted path, naming inside an anchored address cluster, contiguity. `approved` rows are the only ones a merge moves; a TU nothing anchors can be approved under a provisional name (below). |
| `tools/tu_skeleton.py` | The lane: `--queue`, `--plan`, `--merge`. It verifies every merge by compiling and byte-matching, claims its scope, and repoints the ledger. |
| `tools/tu_evidence.py` | Retail layout signals (funclet order, vftables, initializers, .rdata order, funclet parentage) for rows nothing else places; proposal-only until a signal passes its 99% precision gate and is promoted. |
| `tools/tu_ownership.py` | The commit hook's invariants (a row moved to a file other than its approved TU, a second body for one address). Shadow mode. |

`tu_skeleton.py` rebuilds the map in memory when the committed `tu_map.csv` is
stale, so a merge commit never carries a regenerated map. Never commit a
regenerated `tu_map.csv` from this lane.

## Workflow per TU

1. **Survey and pick.** Run `python3 tools/name_lane.py consolidate --under Code/<subsystem>/`
   and review its evidence and blockers. An unchanged report can be reused while
   `python3 tools/name_lane.py consolidate --check build/consolidation` passes.
   Then `python3 tools/tu_skeleton.py --queue --limit 20` ranks approved TUs by
   how many files a merge would remove and marks those another worker holds
   (`HELD`). Take an unheld one. `removes` is an upper bound: the merge keeps only
   donors that compile together without losing a row.
2. **Read the plan.** `--plan TU` lists every approved row in retail order and what
   happens to it: `pull` (a clean donor), `mixed` (its file also holds rows of
   another TU, or rows the map leaves without a TU for want of evidence; a row it
   leaves homeless on purpose, `tu_map.homeless`, does not count: a header-inline
   COMDAT (evidence token `inline`), a template instantiation or a
   compiler-generated COMDAT follows its file into the TU, and the byte check
   verifies it there. Being displaced is not enough, and a row whose own F/Z/S/L/W
   names a TU, or a companion the map assigns elsewhere, always blocks), `refused` (it holds a row only proposed for the TU, or a
   p-group funclet of an unapproved parent: only approved rows move; or deleting
   the file is not mechanical: vendored,
   `#include`d by another file, or expanding `__FILE__`, even when it is also
   register-keyed, an approved TU path or recorded canonical), or
   a placeholder comment (unmatched; it compiles to nothing and is never credited).
3. **Dry run.** `--merge TU --dry-run` composes and verifies without writing.
   `accepted` donors merge as they are. Each `rejected` donor carries the compile
   error or `bytes` (a row the merged text no longer matches). A successful dry
   run saves its winning composition under ignored `build/tu_skeleton/plans/`.
   The later `--merge TU` reuses that choice when the worktree and TU inputs are
   unchanged. It recompiles and checks the chosen unit's bytes and current link
   guard once, then recomputes protected-register transfers before writing. A
   changed input or failed check returns to the ordinary merge search.
4. **Reconcile the rejected donors, one ordinary commit each.** The usual cause is
   a private view of a class or struct that differs from the seed's: a local
   `Coord3D`, an enum declared twice, a member declared `private` in one view and
   reached from another. `python3 tools/tu_views.py TU --dry-run` plans the
   mechanical part for every class two of the TU's files declare privately: one
   superset view from the compiler's layouts (seed names, union of methods,
   padding for gaps, forward declarations and enums a file lacks), the donors'
   field references renamed, and a conflict with its evidence wherever the
   views disagree on layout, vtable slots or mangling.
   Without `--dry-run` it writes the classes that verify (layout re-read,
   `./build.sh` exact, nothing newly unmatched) and restores the rest; commit
   that as its own change. Otherwise make the donor compile against the seed's
   headers, or move both to the canonical header (`tools/class_views.py --class X`,
   `tools/header_adopt_lane.py`). Verify the donor with `./build.sh` and commit it
   before merging. Duplicate *identical* declarations and donor-local copies of a
   type that the seed or an included header defines are removed by the merge
   itself, and the byte check decides whether that was safe.
5. **Merge.** `BFME_CLAIM_OWNER=<seat> python3 tools/tu_skeleton.py --merge TU`
   claims `file:` for the TU and every donor, plus each moved row's RVA. It writes
   nothing when another worker holds one of them. Then it writes the TU, deletes
   the absorbed donors, repoints `functions.csv`, `data_rows.csv`, `tu_map.csv`
   and `body_owners.csv` `source` columns, the `fold-proof=<donor>` notes tokens
   in `functions.csv` and `symbols.csv`, and the `docs/doxygen/sources.cfg`
   inputs, carries the donors' protected-register keys to the TU (below), and
   stages the result. It prints the paths it staged and a commit subject.
6. **Verify and commit.** `./build.sh TU`, then
   `python3 tools/find_declared_unmatched.py TU`, then commit with the printed
   subject, plus the printed `trailer:` and any `debt-retired:` lines when the
   merge carried register keys. The hook byte-verifies the TU again. Follow AGENTS.md's Publication
   rules: a merge recovers no new bytes, so batch merges and push them together. Perform
   the tooling compatibility audit below once over the full outgoing batch
   immediately before pushing.
7. **Name while you are there.** The rows of the TU are a natural naming group:
   successful merge reports include a `scoped_naming` handoff for the final TU.
   Reuse the code context and existing claim owner to clarify locals/parameters
   with `name_lane.py scoped next --files TU --functions 'Class::method'`, then
   the usual native-child proposal, parent review and combined application
   (`docs/naming.md`). Take the packet after merging; donor paths are stale.
   Keep clear names and uncertain roles. Publish verified moves promptly rather
   than holding them for an unrelated naming quota. Shared names still require
   their existing evidence/approval path:
   rename placeholder rows with `tools/rename.py` (`docs/naming.md`) in separate
   commits. A merged TU path is an approved retail TU, so `rename_files.py` never
   renames it, unless its name is provisional (see "Provisional names" below): then
   proving the file's real name is part of this step.
8. **Release** the `file:` claims after the push
   (`python3 tools/claims.py release file:<path> ...`) and let
   `python3 tools/claims.py release --landed` settle the RVAs.

## Protected registers travel with the merge

A donor keyed in a protected path-keyed register (`rename.PROTECTED_PATH_KEYED`)
is absorbed, and the merge commit carries its debt to the TU, so no key is left
on a deleted file and no follow-up `Debt-Retired:` cleanup is needed:

| Register | Key layout | What the merge does |
|---|---|---|
| `code_identity_baseline.tsv` | `source<TAB>row<TAB>symbol<TAB>target<TAB>class` | source rewritten to the TU; a key two donors share is kept once |
| `data_check_baseline.txt` | `source<TAB>check<TAB>symbol<TAB>address` | same |
| `hatch_baseline.tsv` | `hatch<TAB>path<TAB>token<TAB>count` | `hatch_counters.py --update` after staging (a total-keeping move); the merged text may not hold more occurrences than its donors; refused on a tree with other modified files |
| `flag_overrides.csv` | `source,flags,rows,default_lost,reason` | the donors' (and TU's) entries become one TU entry with summed counts; the merge is verified under those flags (the TU's own when it has one, else the most rows'), the TU spells them, a donor overridden with other flags is rejected, and a donor that would lose a row its region-default build matches is rejected; when the TU has no override and the carried one would cost it a row, the TU keeps its region default and the overridden donors are rejected |
| `data_ledger.csv` | `source` column; `name@source` in `names` | rewritten to the TU |

The hooks read a re-keyed line as a transfer: a grown key counts as moved only
when the identical key leaves under a source the commit deletes, that source's
ledger rows all move to the new key's source, and that source exists
(`protected_paths.transferred`, used by `protected_paths.py`,
`code_identity_gate.py --staged` and `data_check.py --staged`; each donor
line excuses one grown line). Any other re-keying stays growth. `repair_queue.py
verify-removed` judges every removed line on its own source: it is a transfer only
when that source is gone, or all its rows moved to the new key's source. A donor
sharing the key never excuses removing another source's line; that source still
goes to its owner verdict. The merge refuses, writing nothing, when a register would still name a
deleted donor. It prints:

- `trailer:` the exact `Verifier-Change: tu_skeleton --merge carried the
  protected-register keys of N absorbed donor(s) to TU (transfer; totals kept)`
  line the commit needs (the registers are protected paths);
- `debt-retired:` one `Debt-Retired: <key> <donor> merged into TU, which already
  holds this key` line per donor key the TU already held (no transfer can show
  for it), to add to the same commit message;
- `follow-up:` keys the merged TU may no longer produce leave only on the owning
  tool's fresh verdict, in a later commit: after `./build.sh TU`,
  `repair_queue.py retire identity|data TU`, and `flag_defaults.py propose TU`
  for a carried override. Retiring in the merge commit itself would hide the
  transfer from verify-removed.

## Vendored libraries built from upstream's files (L)

GameSpy, Lua, zlib and LZHL were compiled from upstream's own files, one retail
TU per file, and their vendored copies sit at the official BFME paths. tu_map's
L signal anchors a row to its own file when that file is a whole upstream file
(a ledger row tags it `vendored=<lib>-<ver>`; a carve-out such as
`liolib_bfme1.c` or `peerCallbacksFinished.c` is not one) and is the only whole
file of its library defining the row's name. Header-inline "vendored" code (ATL,
GDI+, strsafe, the CRT splits, STLport) is emitted as COMDATs in whichever object
used it and never names a TU. F/Z/S never reach library code, so L has its own
gate, approved by the owner on 2026-10-28: each L row held out, the nearest
anchored rows on both sides in retail order must name its file, at >= 99% on
>= 100 rows (785/785 when it landed; `tu_map.py --validate` prints it). Below the
gate L anchors nothing.

## Provisional names: grouping proven, file name not

A TU nothing anchors (no `__FILE__` string, Zero Hour definition, whole upstream
file or corroborating WorldBuilder lead) is still approved when grouping alone
holds it together: at least two rows share its naming hint (N/U), no row another
TU could claim sits inside its address span, and its span overlaps no anchored
TU's. Its rows, and the C, funclet and data rows that follow them, carry the
evidence token `provisional` in `tu_map.csv`. `tu_skeleton.py` merges them like
any approved rows (a provisional TU is an approved unit), but the TU path is only
the naming hint: `rename.py` and `rename_files.py` do not take it for a proven
file name, so the merged file can still be renamed once a naming lane proves the
real one, and `progress.py` counts these rows separately under TU-APPROVED.

The owner approved this on 2026-10-28, conditional on 99% precision. Measured by
holding out every anchor of the 601 anchored TUs (five folds, the map rebuilt
each time): all 13,655 rows approved provisionally landed in a group whose other
rows share their TU, 4,627/4,627 among rows with their own F/Z/S, and no group
mixed two TUs. A TU can split into several provisional groups (25 of the 427
recovered did), so merging can leave more than one file for a TU until it is
named, never one file for two TUs.

### Funclet groups (`p-group`, pending owner approval)

An EH funclet whose parent function the map does not approve is approved anyway
with its parent's TU (`tu_evidence.P_GROUPS`). It carries the evidence token
`p-group`, plus `provisional` when that TU has no anchor. `python3
tools/tu_map.py --holdout p-groups` measures it with the method above, now in
`tools/tu_holdout.py`. Five folds, scoring only rows whose anchored TU was held
out: 5,974/5,981 (99.88%) join a group whose other rows share their TU. The
misses are Apt.cpp/AptLoad.cpp funclets that land on the wrong side of the
boundary. On the live map it approves +4,073 code rows, nearly all in
`gen_small` funclet files, so it frees few authored files directly. The same
harness measures the rules that did not clear: `prov-min-1`, `brackets`,
`interleave` and `k-only`.

## Retail layout evidence (the TU-evidence lane)

About 8,400 sources have no tu_map row with any TU: no `__FILE__` string, no Zero
Hour definition, no usable name and no bracketing anchor. `tools/tu_evidence.py`
reads layouts the linker kept in object order out of the retail image and the
committed xref tables: funclet order in `.text$x` (E, parents from the image's own
EH FuncInfo tables), vftable layout (V), the `.CRT$XCU` initializer table (I),
`.rdata` order (R), `.text` order itself (T: brackets of approved F/Z/L rows, past
other TUs' proposed guesses, vetoed by any row between that names another TU
firmly), and funclet parentage (P: a handler or funclet takes its parent's TU and
confidence). A row is placed only when the nearest anchored entries on both sides
of each of its entries name one TU within the signal's gap, and all signals that
reach it agree. E, P and T are promoted; V, R and I only propose (the docstring
records each measurement).

    python3 tools/tu_evidence.py --validate          # precision/recall per signal, rows a pass would approve
    python3 tools/tu_evidence.py --source FILE       # what reaches one source's rows
    python3 tools/tu_evidence.py --write             # build/tu_evidence.csv, every evidence row
    python3 tools/tu_evidence.py --check             # re-derive it; a row nothing re-derives fails

Every signal starts proposal-only. It counts toward tu_map approval only when
`tu_evidence.PROMOTED` lists it, in a Verifier-Change commit recording
`--validate` at >= 99% precision (leave-one-out over approved F/Z/S rows; P
against the ledger's `parent=` notes) in the tool's docstring, and the hold-out
harness on the signal (`tu_map.py --holdout signal-X`, and `--unit row` for a
signal that anchors only on a TU's own hard rows, which a TU fold strips
entirely) at >= 99%. `--validate` exits 1 when a promoted signal has fallen below
the gate. Even then tu_map computes the
approval: the TU must be anchored and contiguous, the row must not sit inside
another approved TU's span, and a funclet's parent must be approved. Nothing here is
entered by hand, and the lane never commits a regenerated map.

`next_work.py --tier tu-evidence` (`repair_queue.tu_evidence_items`) serves the
unmapped address runs that hold those sources, at most 16 sources per item, runs a
signal reaches first. Each item lists the bracketing rows, the gap and the
re-derived layout evidence, and claims its sources. The seat finds a re-checkable
anchor (a real name with a Zero Hour definition or a `__FILE__` string, often a
mis-named row whose Z fails) or a missing bracket through the naming lanes. It never
asserts a TU. The item passes when the map rebuilt from current inputs gives the
run's rows a TU.

The same tier also serves `wb-path` leads from `tools/wb_source_paths.py`. It
inventories every `.cpp`/`.c` path string in `worldbuilder.exe` and `game.dat`
into `reverse/worldbuilder_source_paths.csv` (`inventory` rewrites it, `check`
compares it with a rebuild). The tool emits one lead for each non-editor
WorldBuilder path that has no TU in the live map. Each lead lists the
`wb_name_leads.csv` game RVAs whose paired WB body pushes that path (every file
the body pushes, not only the first), with their owners and map confidence. It
also lists same-basename TUs already in the map and whether game.dat's own strings
carry the path. WorldBuilder paths are donor facts. A path proves that a file of
that spelling existed in the editor build. It does not prove that a game function
belongs to that file, and the WorldBuilder path count is not a game file count. A
lead approves nothing: tu_map's W route (`wb_name_leads` and its `w_score` gate)
and the F/Z/S anchors stay the only way to approve, and a lead is never a reason to
create an empty TU.

## Carving a mixed file (the split lane)

A mixed file holds matched rows of several TUs, and often rows with no approved
TU yet. A merge never splits one. `tools/tu_skeleton.py --split` carves the rows
approved for ONE TU out of it, straight into that TU path, and leaves every other
row where it was:

    python3 tools/tu_skeleton.py --split FILE                 # which TUs the file's rows belong to
    python3 tools/tu_skeleton.py --split FILE --for TU --dry-run
    BFME_CLAIM_OWNER=<seat> python3 tools/tu_skeleton.py --split FILE --for TU

A successful split dry run saves its composition under ignored
`build/tu_skeleton/split_plans/`. Applying the same split reuses that composition
while the tree and planning inputs are unchanged. Application still claims the
scope, checks the residual and moved rows, verifies the final TU, runs the full
residual/destination link guard, and carries the unit-key registers. A stale or
failing plan falls back to the normal search; `plan_reused: True` identifies a
successful reuse. Plans are separate for each donor and destination pair.

What it does, in order, writing nothing until the last step:

1. Identifies each approved row's definition by the name it spells
   (`Class::method(`, a free function, a destructor, an operator, a template),
   or, in a sweep file that generates one body per macro invocation, the
   invocation naming the row's class among its arguments; a row no definition
   spells, or that two spell, stays behind and is reported, as does a row whose
   one definition (a template, a macro) also produces rows the map places in
   another TU. Rows emitted with a carved body ride with it: EH funclets by name
   (`__ehhandler$X`, ...), generated funclets (`gen-funclet;parent=X`) and the
   deleting destructors of a carved destructor. A body naming a global that
   carries data-identity debt keyed to the file stays behind: retire that key
   first.
2. Carves: the donor text is the file minus the bodies that stay; the residual is
   the file minus the bodies that leave. Both keep every preprocessor line,
   declaration and comment, except that an extern object or a class body the
   side no longer names is dropped from it. A class body with a comment, a
   templated or declarator-bearing body, and every class in a file with
   preprocessor conditionals stay. Definitions are never duplicated: a file-local
   helper function with internal linkage that is not a ledger row travels as a
   copy when a carved body calls it (transitively); one with external linkage
   never does. A file-scope object definition goes where it is used: with the
   carved bodies when only they use it (its data row is repointed), else it
   stays; an external one used on both sides stays and the donor declares it
   `extern`; an internal one used on both sides refuses the carve. Definitions
   inside a `namespace {}` / `extern "C" {}` block follow the same rules one by
   one: both texts keep the block, the TU around the bodies that leave, the
   residual around the rest; a free function there is identified by its
   namespace (`?f@Ns@@`); an unrowed inline body or primary template there stays
   on both sides; an anonymous-namespace helper is internal. A file-scope
   `#pragma comment(linker, "/alternatename:SYMBOL=...")` line naming one
   symbol goes with the side whose bodies use SYMBOL (its name or its class),
   so the hatch moves instead of counting twice; one both sides use stays on
   both (and the hatch check refuses the growth), one neither uses stays in
   the residual. A wrong guess leaves SYMBOL unresolved, which the link guard
   reports. Quoted includes that resolve beside the mixed file are rewritten
   to resolve beside the TU (the compiler searches the including file's
   directory first).
3. Verifies the residual under its own path and the flags the build will give its
   remaining rows (the region vote can change when rows leave). Any lost row
   blocks the split, except an ICF alias: a row sharing its address with the
   row the map identifies that address by (tu_map's first row wins, e.g. the
   folded vector destructor at 0x0007FAB3). The map places no alias, so an
   alias no definition spells (an STLport COMDAT, an inline member) is emitted
   wherever a body uses it; one only the carved bodies emitted rides with them
   (`riders` in the report) and must match beside the TU in step 4. For the
   same reason an alias never makes a file mixed for `--merge`.
4. Verifies every carved row alone beside the TU under the TU's flags. A row that
   matches only under the mixed file's own flags stays behind (`flag_bound`).
5. Runs the carved bodies through the merge verifier as a donor: into the existing
   TU file as seed, or as a new TU file. The usual merge repairs apply
   (duplicate declarations dropped once, redefinitions repaired); a donor the
   seed's headers cannot host is rejected with the compiler's reason, exactly as
   in `--merge`, and the seat reconciles the seed or the donor first.
6. For application, claims `file:TU`, `file:FILE` and every moved RVA. Compares
   linking before and after with `SplitLinkGuard`. It compiles the
   original mixed file and existing destination for a bounded baseline, then
   judges the residual and destination together in their post-split ledger
   order. Both objects' providers, COMMON data, aliases and row ownership join
   the same view. A link-clean original stays link-clean; existing debt remains
   visible and new blockers require repair. Outside consumers retain their
   providers, alias routes and selected implementations, with no new duplicate
   or COMDAT losses. A moved unproven selected copy needs matching raw relocation
   context; a changed measured `/MAP` selection needs measured evidence.
   The census index downloads automatically when absent. Missing or inconclusive
   evidence blocks the split before either source or its ledger is written.
   Other providers remain the last census's evidence, as for merge protection;
   broader changes since that census still need the outgoing audit and census.
7. Writes the TU and residual; repoints only the moved rows in `functions.csv`, `tu_map.csv` and
   `body_owners.csv`; adds the TU to the doxygen list; stages the result and
   prints a commit subject. When a moved body carries an escape hatch the carve
   first proves no per-hatch total grows (rule 3 of `tools/hatch_counters.py`),
   refuses on a tree with other modified files, runs `hatch_counters.py
   --update` after staging and prints the `Verifier-Change:` trailer the
   register's change needs.

Then `./build.sh TU FILE`, `python3 tools/find_declared_unmatched.py TU FILE`, commit
with the printed subject, and publish under the normal batch rules (a split moves
no new bytes; batch splits with the merges they unblock, and run the tooling
compatibility audit once over the batch).

What it refuses: a vendored file, one another file `#include`s, one that
expands `__FILE__` (each checked directly, not only through `rename_files`'
first reason), a file every row of which is this TU's (use `--merge`), a carve
after which no row would remain (unless `--prepared` absorbs the donor, below), a TU path holding rows the map places elsewhere
(split that first), and anything another worker holds a claim on.

### Prepared texts, vtable riders and emission moves

    python3 tools/tu_skeleton.py --split FILE --for TU --prepared TU=TEXT [--dry-run]
    python3 tools/tu_skeleton.py --emit-move FILE[,FILE...] --for TU [--rva 0xRVA,...]
                                 [--prepared PATH=TEXT ...] [--dry-run]
    python3 tools/tu_skeleton.py --recover-emit

- `--prepared TU=TEXT` writes TEXT as the TU's whole final text in the same
  transaction: the carved bodies are not appended, every moved row and every row
  the TU matched before must match in TEXT, and a donor left with no row is
  absorbed as a merge absorbs it (deleted, its path-keyed columns repointed)
  instead of refused. Hatch totals over the TU and the file may not grow.
- A deleting destructor (`??_G`/`??_E`) the map leaves displaced or homeless rides
  with the carved body that emits its class's vtable, when it is the only ledger
  row at its address, the destination's object emits the vtable and the
  residual's does not.
- `--emit-move` repoints a mixed file's deleting-destructor rows to their approved
  TU once the TU's own code emits each byte-exact; no text moves. It moves only
  `??_G`/`??_E`, by the decorated name, and only when no copy looks hand-written:
  `__identifier("??_G...")` can spell the name, so every object defining it must
  select its COMDAT ANY in a code section as the compiler does (a plain
  `__identifier` definition gets NODUPLICATES), and neither unit's preprocessed
  text may define it through `__identifier` (an `inline` one also gets ANY). The
  vtable rider passes the same checks. By name alone, constructors, destructors
  and assignments never move this way: a hand-written one compiles to the implicit
  one's name, bytes and relocations. Nor do template instances: whether an
  instance was instantiated from vendored STLport or written in project code (a
  typedef'd member, a project `#line` naming an STLport header, a reopened
  `namespace _STL`) cannot be proved from text, and `#line` also rewrites the
  debug line info.
- In a prepared transaction a row of a prepared file that no name admits may move
  on the transfer proof, which reads objects and claims nothing about who wrote the
  body. All of it must hold, or the row is refused: the current map approves the
  TU for the row's own address; the file's rebuilt object no longer defines the
  symbol; the TU's defines it byte-exact in a code COMDAT selected ANY; its body
  there is the one the file's object held before the move, compared beyond the
  masked bytes (`section_identity`: exact bytes and flags, each relocation's offset,
  type and target, recursively for associated sections and local targets, with
  anything it cannot compare refused); no other object of the transaction defines
  it, a weak external or `/alternatename` included. That last check covers the
  objects of the transaction only: the whole link is judged by the pre-push batch
  audit and `link_check`, so a move is not cleared until those have run. Under `/Gy` a plain function is a COMDAT section too, but selected
  NODUPLICATES, so a real body still goes through `--split` or `--merge`. Every
  compile runs with the object store off, the real objects are deleted before the
  build, and anything that cannot be read (a failed compile, a missing object, an
  unparseable section) refuses. It is judged at the byte gate, on the final
  compiles and on the rebuilt objects. A row it refuses stays in its file, whose
  prepared text then loses it, so the transaction stops. Without a prepared text
  a template move still needs a provenance proof that does not depend on text.
- `--emit-move` over several files is one transaction: one journal, one build over
  exactly those files and the TU, one claim scope, one undo. `--rva` picks rows
  across them and each file's others stay; every listed file must contribute a
  row. `--prepared PATH=TEXT` is the whole final text of the TU or of a listed
  file, written in the same transaction and judged as given: today's text is
  still the baseline, every remaining row must match in the new text, hatch
  totals may move but not grow, and no strong symbol may vanish from every object
  of the move. A COMDAT a prepared text stops emitting is reported as
  `comdats_dropped` for the pre-push link audit. Like a split, it may not cost the
  map an approval, row by row.
- An emission move journals its before-state under
  `build/tu_skeleton/emit-journal/` before touching the ledger and undoes itself
  on any failure. A killed run leaves the journal; `--recover-emit` undoes it per
  moved row (by numeric RVA), refuses a row edited since, puts a prepared text
  back whole only from its before or after state, and releases only the claims
  the move acquired, each with its fencing token. Neither `rename.py` nor another
  move starts while a journal is pending.

## Bulk merges (`--merge-all`)

`python3 tools/tu_skeleton.py --merge-all` (tools/merge_all.py) runs the same
`--merge` over the whole queue, most donors first. It skips any TU whose scope
another seat claims. TUs with disjoint files run side by side (`--jobs N`), each
in its own worker worktree beside the checkout (`<checkout>-ma<N>`, made by
`worktree_setup.py`) and committed there through the hooks. The commits are
cherry-picked onto the invoking checkout's branch in queue order, and the ledger
is checked after each pick (no matched row lost, every absorbed row names the
TU). A conflict is retried next pass, never resolved by hand. Runs resume from
`build/merge_all/state.json`; `--budget-min` stops starting new waves. Run it
from a clean checkout whose tools are committed, with the push identity in the
environment. After pushing the branch, `--merge-all --release` returns the
merged TUs' scope claims; run the consolidation checks below over the batch as
for any merge.

What it cannot merge goes to a ranked decision queue
(`build/merge_all/decisions.json`, shared through the picker cache), ranked by
the files merging it would remove: blocked by classes (served by the header
tier), split, compile error, link regression, row loss, claimed, refused and
hook refusals, each with its evidence. `next_work.py --tier consolidate`
serves the split, compile-error and link-regression items as decisions. `--dry-run`
compiles but writes nothing, and prints how many TUs and files would merge now
along with the blocker histogram; `--dry-run --static` reads the queue alone.

## Shattering a mixed file into all its TUs

    python3 tools/tu_skeleton.py --shatter FILE --dry-run
    BFME_CLAIM_OWNER=<seat> python3 tools/tu_skeleton.py --shatter FILE

`--shatter` carves FILE into every TU its rows are approved for in one
transaction and deletes FILE, so no intermediate residual has to verify on its
own (a split's commonest refusal is a residual that stops emitting a COMDAT only
a carved body made it emit). It plans every row and definition first:

1. A row goes with the one definition that spells it; one no definition spells
   (an inline member, an STLport COMDAT) only has to be emitted matched by its
   unit; a definition producing rows of two TUs, or a row two definitions
   spell, refuses. An unplaced row rides with the TU owning its definition. One
   with no definition, or a primary template's (an instantiation), rides with
   the first unit that emits it matched. Unplaced rows with a definition of
   their own stay in FILE, which then remains as one more unit (the residual)
   verified and link-judged with the others instead of being deleted.
2. An external helper that is not a row goes to the one unit that calls it,
   else beside the owned definition before it; two calling units refuse.
   Internal helpers are copied as in `--split`; primary templates, and types the
   chunker reads as bodies, stay in every unit.
3. An external object used by several units is defined by the first in file
   order and declared `extern` by the rest; a data row no unit uses refuses.
4. Anything keyed to FILE as a unit (protected registers other than the hatch
   register and `data_ledger.csv`, the header queue, a flag override), and any
   ledger row the shatter does not carry, refuses.

Then each unit is verified alone under its TU's flags (every row must match: there is no residual to
stay in), then through the merge verifier into its TU file or a new one, then all final objects are
judged together by the link guard with FILE gone from the link. A per-hatch total may move, never
grow. Only when every unit passes does it write the TUs, repoint each moved row to its own TU, delete
FILE and stage the result.

**Unit keys.** `data_ledger.csv` (`source`, and `name@FILE` statics in `names`) and
`fold-proof=FILE` pins in `symbols.csv` name the unit whose object defines a symbol. After the final
objects pass the link guard, `--shatter` (and `--split`, for its residual and TU) reads their COFF
symbol tables and moves each key to the one unit that defines it: a global or static for the ledger, the
pinned body for a fold proof. The residual counts as one of the final objects: when it is the only definer
it keeps the key. It refuses when two final objects define the symbol (the residual and a destination,
or a static that `carve()` copied to two units), when none does, when a verified `data_rows.csv` owner
disagrees with the object, when a move would merge two `names` keys into one, and when a fold proof's
unrowed callee would end up in a different object from the pinned body (checked for a proof the residual
keeps too). A key the original object did not define either is stale from before the carve: while the
file remains (a residual) it stays as it is, whatever defines the symbol now. A moved ledger key needs the printed `Verifier-Change:`
trailer. Pin admission re-proves a moved fold proof at commit.

## What the lane does not do yet

- **Mixed files** (a file holding rows of two TUs) are never split inside a
  merge: about as many donor files are mixed as clean. A split is its own
  verified change, `--split FILE --for TU` above, one TU at a time; rows the map
  has not placed stay in the file until it places them.
- **TU paths that hold another TU's rows** are skipped by the queue for the same
  reason (`blocked: ... split it first`).
- **Linking.** The pre-push `tools/link_batch_audit.py` compares selected
  providers and changed-unit unresolved symbols once across the outgoing
  batch, using current object receipts. It reports stale inputs as inconclusive
  and leaves consumer byte totals for the next census. Review its shadow
  findings and update the shared linking obstacle register.
  Each run appends one JSON line to `<git common dir>/link_audit_verdicts.jsonl`,
  the before/after measurement for strict receipts. Anything reading that log
  must drop lines with `"base": "a"` and `"tip": "b"`: they are fixtures
  `tools/tests/test_link_batch_audit.py` wrote into real logs (2026-11-07 on), and
  a clone running the suite from before its fix can still add more.
- **A merge that would cost the map an approval is refused, not repaired.** N
  hints follow a file's directory, so moving one file of a provisional group can
  leave a sibling row with no interleaving cluster (2026-11-07:
  `Upgrade/BaseUpgrade.cpp` without `BaseUpgradeUpgradeImplementation.cpp`, row
  0x004B37CA dropped from approved to proposed and its funclets stayed approved
  for the deleted path). `--merge`, a dry run, a reused plan and a prepared
  `--split` that absorbs its whole donor rebuild the map in memory with the
  accepted donors' rows repointed and refuse when any code row's confidence falls
  or a row is placed in a path the move deletes. Move the group's files together.
  A split that leaves its file in place is judged the same way, row by row.
- **A write that fails partway keeps its claims.** A merge, split or shatter has
  no journal. An exception before the first write gives back what the call claimed;
  once the write has started, the tool says so and the claims stay held, so no
  other worker takes the files while the tree is half written. Restore it with
  `git restore --staged --worktree` on the paths `git status` lists, then release
  the scope with `tools/claims.py release`.
- **A header-queue retirement and its source's merge go in separate pushes.**
  If `header_adopt_lane.py accept` retires a donor's header-queue row and a merge
  in the same push deletes that donor, the pre-push debt check sees a retired
  row whose unit vanished and refuses it as a regression. Push the adoption
  first, then the merge (merges alone may use the go-file).

### Measured blockers, 2026-11-03 (ten TUs sampled)

Ten targets were taken end to end on this date, five `--merge` and five `--split`, each with
a freshly fetched census index. None landed, but the lane is not closed: one of the ten,
`GameLogic/Object/PartitionManager.cpp`, composed a **verified seven-donor merge** (23 donors,
7 accepted) and was refused at the write step only because another contributor held the
scope — "blocked: held by another worker: 0x000073E0, 0x00260E01, 0x00322167, 0x00739840,
0x00739870", all held by a concurrent `tu_skeleton` seat on the same TU. So a mid-queue TU can
still merge; the good targets are contested, and the queue's `HELD` marker did not warn before
the dry run spent its compile budget. The other nine refusals cluster into three causes, and
the first two are the same mechanism seen from opposite sides:

- **Carried compiler flags (merges).** `reverse/flag_overrides.csv` holds 699 files, 652 keyed
  "region default loses rows" and 46 "region default does not compile". A merge carries one
  `// cl:` set, so a donor whose rows only match under different flags is rejected: "its flag
  override '-O2 -G6' is not the carried ''", "loses 35 row(s) under the carried flag override
  '-G7 -arch:SSE'". `Geometry.cpp` rejected all 21 donors this way with an empty carried set
  against donors needing `-O2`, `-O2 -G6` and `-Ox -G6`. Only 187 of 17,324 sources under
  `Code/` carry a `// cl:` line with an optimisation flag, so the overrides are the exception
  that blocks the rule. **Corrected below:** queue-wide this stops 14 of 723 items and 14 of
  1,453 file removals, so it is a real mechanism with almost none of the weight this bullet
  implies; see "The whole queue measured".
- **The residual's flag-region vote (splits).** Three of five splits carved their rows cleanly
  and were still refused with "the residual loses matched rows (flag region or a shared
  helper)": removing rows re-votes the region for what stays behind. `MeshLoadContextCtor.cpp`
  carved 2 rows and would have cost the residual 18.
- **Donor-private class views.** `C2011`/`C2953` redefinition where a donor declares its own
  view of a class the destination's headers define: `AsciiString` from
  `reference/shims/bfme2_ascii`, donors' own `namespace _STL` vector/allocator, `GameSlot`,
  `OVERRIDE`, `INI`, `MemoryPoolObject`, `NameKeyGenerator`.

`SubsystemInterface` is the largest single instance of the third cause and worth its own
pass: 8 of `System/Upgrade.cpp`'s 16 donors fail on it, 462 `reverse/header_queue.tsv` rows
name a subsystem header, and nine headers in the tree declare the class. It is already
registered canonical to `Code/Libraries/Source/subsystem/SubsystemInterface.h`, whose note
records only 16 of 206 sampled units adopting, while 15 units include
`reference/shims/subsystem_bfme2/subsystem_interface.h` instead. That is not an include swap:
the shim also declares `SubsystemInterfaceList`, `SubsystemSlotBase`, `SubsystemSlot<T>` and
`initSubsystem<T>`, it declares the fourteen virtual slots unconditionally where the canonical
header guards them behind `BFME_SUBSYSTEM_SLOTS`, and its `setName` is inline where retail's
is the out-of-line 0x0006F3CC. Each unit needs byte verification, and
`header_adopt_lane.py adopt` cannot drive it, reporting "no private view found" because these
units include a header rather than declaring a class.


### Scripts.cpp merged, 2026-11-03 (38 files, 83 rows, landed `e1ffb0b1df6`)

The queue's largest item went through: `tu_skeleton.py --merge-all` composed
`GameLogic/ScriptEngine/Scripts.cpp` from 350 approved rows over roughly three hours and
absorbed 38 of its candidate donors, 83 rows, deleting 38 sources and repointing 69 rows
each in `functions.csv` and `tu_map.csv`. The push hook verified it whole: functions
83/83 matched, EH EXACT on all 10 rows with EH data, string and float refs OK, DIR32
consistent, `data_check` converged over 11 addresses.

Two things are open and neither is a defect in the merge. The batch link audit came back
INCONCLUSIVE: 38 source objects lack current receipts, which is the unavoidable shape of
the trap recorded in
[the inconclusive-audit note](linking_obstacles/inferred-name-landings-pushed-with-an-inconclusive-link-audit-2026-11-03.md)
— a published index carries receipts for objects as the census found them, so absorbing
38 objects necessarily leaves 38 without one. Carry this TU and its absorbed donors into
the next scheduled census; no linking or census gain is claimed. Second, 42 classes still
hold donor-private views here and the rejected donors need step 4
(`tools/tu_views.py Code/GameEngine/Source/GameLogic/ScriptEngine/Scripts.cpp --dry-run`);
`adopt_first` names `ScriptList` and `Parameter` as the first to resolve.

### Scripts.cpp's 42 private views, reconciled as far as they go (2026-11-03)

`tools/tu_views.py` on the merged TU planned 16 of the 42 classes that two or more of its
files declare privately; 10 verified and were written (`Rva003B3EEAOwner`,
`Rva003B40A1Holder`, `Rva003B44EE`, `Rva003B485AHolder`, `Rva003B48B9Holder`,
`Rva003B48E4`, `Rva003B713ERange`, `Rva003B8802Set`, `BfmeStringRecord003B3F78`,
`KindOfMaskType`), and three (`Rva0034FE00`, `Rva003B40B6Holder`, `Template`) did not
compile with their block and the tool restored them. No donor was unblocked by this: the
rejections that remain are the 26 conflicting views, and they group as follows.

- **10: the rename is token-based and would reach the wrong member.** The superset view
  needs a field renamed, and an identically named field of a *different* struct sits in
  the same file, so the tool refuses: "`m_index` is also a member of `Rva003B3204`; a token
  rename would reach it". This is the largest group and it holds the single biggest blocker
  in the whole class-view category — `Rva003B31DF`, named by 23 queue items. Worth being
  precise about what these are *not*: `Rva003B31DF` and `Rva003B3204` sit in one file with
  identical layouts (`m_next` +0x00, `m_index` +0x04) and a `clear()` each, which looks
  like one retail class split into two placeholders. It is not. Retail's own mangling
  separates them — `?deleteGroupRef@ScriptList@@QAEXPAXPAURva003B31DF@@@Z` against
  `?deleteScriptRef@ScriptList@@QAEXPAXPAURva003B3204@@@Z` — so they are two real types, a
  group-ref node and a script-ref node, that happen to share a shape. The fix is a
  class-scoped rename, not unification, and naming the pair is ordinary name-lane work with
  the evidence already in hand. The others in this group: `BfmeHeadXZ`, `BfmeNodeXZ`,
  `BfmeNodeZ`, `Gen_00350E60`, `Rva003B3204`, `Rva003B3485`, `Rva003B37C8`, `Rva003B448C`,
  `ScriptSubRecord`.
- **7: the views partition the same bytes differently** (`Rva003B2498`, `Rva003B44AB`,
  `Rva003B56A5`, `Rva003B573E`, `Rva003B761E`, `Rva003B770B`, `Rva003B872ASet`). Real
  layout disagreement; each needs evidence, not a tool.
- **4: the view omits its own bases or vfptr**, declaring a field at +0x0 where the
  compiler puts base data (`ActionTemplate` and `ConditionTemplate`, own data at +0x7C;
  `Rva003BRefSubrecord` at +0x10; `BfmeParserBindingBaseVE` under the vfptr at +0x4).
- **5 singletons:** `Rva003B3536` is defined inline in one file and out of line in
  another; `OrCondition`'s base clause differs between views; `Rva003B675BRecord` is typed
  `AsciiString` in one view and `void*` in another at +0x8; `ScriptListBase` names
  `m_firstScript` at both +0x4 and +0x8; and nothing in the tree lays `ScriptListView` out
  at all, so there is no evidence to reconcile.

**The sister TU is someone else's lane.** `Weapon.cpp` carries the other 40 of the 92
class-view items, but 8 of its 9 commonest blockers (`WeaponTemplate`, `Weapon`, `Thing`,
`Drawable`, `ThingTemplate`, `AI`, `TerrainLogic`, `WeaponStore`; only `Object` is not)
are registered in `reverse/canonical_classes.csv`, which makes them
`header_adopt_lane` work rather than `tu_views` work — and a contributor's header fleet
held live `apply AI` and `apply TerrainLogic` claims while this was measured. Do not open a
second front on it; 34 of its 40 diagnostics are plain `C2011` redefinitions that adopting
the canonical header is meant to remove.

**Two follow-ups this pass created or uncovered.** The merge left three new code-identity
findings in shadow mode on the merged TU — two wrong call bindings in `Scripts.cpp`
(`deque<Rva003B5603Element>::back` to `_M_decrement` at 0x003B3EA8,
`deque<Rva00423BD8Element>::push_back` to `_M_push_back_aux_v` at 0x003B7313) and one
divergent definition (`vector<const ModuleData*>::_M_insert_overflow`) — all naming types
that entered the TU with the absorbed donors, none of them touched by the view edits.
They belong in the identity register's reconciliation
(`docs/consolidation.md`, "Consolidation verification checks"), not in a view pass. Second,
`tu_views` appended its offset comment to a comment that already carried the same offset,
emitting `// +0x18 +0x18` and compounding on every rerun; that is fixed at the source and
the four lines this pass wrote are cleaned, but **114 files and 496 lines** across the tree
still carry the doubled form. It is comment text only, byte-neutral, and a tree-wide sweep
would conflict with every contributor's in-flight work, so it is left for whoever is
already editing those files.

### The whole queue measured, 2026-11-03 (723 items; supersedes the flag reading above)

The same run measured every candidate before starting work and wrote
`build/merge_all/decisions.json` (`{kind: [items, files freed]}`, 723 items at master
`2be2d0e6d26`). Ranked by files freed -- the consolidation payoff -- the picture is not the
one the ten-TU sample above suggested:

    kind                items  files freed  rows
    claimed                52         1168  4835
    blocked-by-classes     92           92   314
    split                 477           52  1688
    other                   1           49   404
    baseline               42           42    60
    compile-error          34           34    62
    flags                  14           14   111
    link-regression         5            5     5
    refused                 4            4     0
    row-loss                2            2     5

**Carried flags are not the ceiling.** They stop 14 of 723 items and 14 of the 1,453 file
removals the queue offers, under one percent of both. The bullet above has the mechanism
right and its weight wrong: it generalised from a five-merge sample that happened to draw
`Geometry.cpp`. The ledgers agree independently -- of 2,277 TUs holding assigned rows,
1,854 have no donor in `reverse/flag_overrides.csv` at all and 384 have donors whose
overrides all agree, leaving 39 where overridden donors disagree. Of those 39 exactly one,
`WWVegas/WW3D2/camera.cpp`, is split only by token order: the overrides file records 33
files under both `-G7 -arch:SSE` and `-arch:SSE -G7`, and 9 under both
`-O2 -G7 -arch:SSE` and `-O2 -arch:SSE -G7`, while the merge weights those raw strings
(`weight[e["flags"]]` in `tu_skeleton.py`), so one flag set is counted as two. Folding the
order would recover that one TU and could not admit an unverified merge, since the
composition is still compile- and byte-checked -- but it is one TU, not a lane.

**The ceiling, in order of what it costs:**

- **Contention, 1,168 of 1,453 file removals.** 52 items are refused because another seat
  holds one of their scope keys, and they are the valuable ones: `ScriptActions.cpp` (715
  rows, 317 files freed), `Object.cpp` (540 rows, 222 files). This is the wall
  `PartitionManager.cpp` hit above, now measured instead of inferred: about four fifths of
  the queue's value is held by other contributors at any given moment, so a seat drawing
  from the top of the queue will mostly draw held items. Prefer `--queue` entries without
  `HELD`, and check the claim immediately before spending a compile budget.
- **Donor-private class views, 92 items.** The largest technical cause, one file freed
  each, and the lane with the clearest tool: `tools/tu_views.py TU --dry-run`.
  `SubsystemInterface` (above) is its biggest single instance.
- **A split first, 477 items.** The row sits in a mixed file that has to be carved before a
  merge can take it; these overlap the split refusals above.

Measurement only; nothing was edited to produce the table.

### Spelling conflicts: the mechanical half of `blocked-by-classes` (2026-11-03)

`tu_views.py` refuses a whole class when the TU's views disagree on anything
that could change mangling or codegen, and two of those disagreements are
mechanical enough to fix in bulk: the class key (`struct` against `class`) and
`__declspec(novtable)`. Landed `07bf66e496d`, `40fec3c11e4` and `92b341a9179`:
28 classes in 30 TUs, 40 blocked donors touched, 18 of them left with an empty
blocking set.

**Scope it per TU, never by name.** 882 classes under `Code/` are spelled both
ways somewhere in the tree, but only a disagreement inside one approved TU's
file set blocks that TU's merge, and the same name in two TUs is usually two
unrelated types: `Code/Libraries/Source/Apt/AptAnimationRebase.cpp` declares a
`struct Object` of `int kind,marker` and a union, which has nothing to do with
the game's `Object` (position at `+0x38`, id at `+0x74`). A tree-wide sweep by
name would have unified two different classes' spellings and churned files no
merge is waiting on.

**The class key is forced wherever a mangled name uses the class as a type**,
`U` for `struct` and `V` for `class`. Read that evidence ledger-wide rather
than per TU, because the forcing row usually lives elsewhere: `Rva00087A93`'s
`V` spelling is carried by `MeshClass`'s rows, not by the TU declaring the
private view. A name the ledger spells both ways is two types sharing a name
(`Rva00587375`: `U` eleven times, `V` four) and must be left alone. Where no
row spells it at all, either key byte-matches and the TU's majority is as good
a choice as any; a tie is no evidence.

Match that evidence as a literal `U<name>@@` or `V<name>@@`. The key letter
follows the pointer and reference modifiers, as in `ABU0@`, `PAVRva00587375@@`
and `XURva00087A93@@`, so it is not at a word boundary and a `(?<![\w?])`
lookbehind silently finds almost nothing. A scan with that bug pointed three
classes the wrong way and `./build.sh` refused all three
(`??0BfmeObject544@@QAE@ABU0@@Z` reported `symbol not found`,
`?Render_With_FX_Material@MeshClass@@QAEXURva00087A93@@H@Z` reported an
unresolved call), which is the check working, not a reason to trust the scan.

**A key change must not move any member's effective access**, because MSVC
mangles access into member names. Converting `struct` to `class` therefore
needs an explicit `public:` when the first member region has no specifier, and
`class` to `struct` an explicit `private:`; 20 of the 26 sites in
`40fec3c11e4` needed one. A `friend` declaration first in the region is
unaffected either way.

**For novtable the majority rule is backwards.** It omits the vftable stores in
the class's own constructors and destructor, so it changes generated code, and
the outlier is almost always the `...Ctor.cpp` or `...Dtor.cpp` file where that
matters. The authority is the file owning the class's `??0`/`??1`/`??_G`/`??_E`
rows, so the fix adds novtable to the files that lack it. Two of seven
candidates were real conflicts: novtable on `Rva0074104CBase` broke
`??0Rva0074104C` and on `Rva00740555` broke
`?rva007402C0@W3DAptComponentView3D`, because a base can need it in the file
defining its own constructor and not in a file that builds a derived object.
Those TUs need two spellings and the refusal is correct. Skip a class whose
ctor/dtor owners already disagree.

Both passes are detection-only until `./build.sh` runs; propose, build the
whole edited set, and revert per class on failure, exactly as `tu_views` does.
Neither pass removes a `blocked-by-classes` item on its own when the donor has
other blocking classes, and neither touches a class in
`reverse/canonical_classes.csv`: that is header-lane work.

A caution on reading the queue's own counters while doing this: a `file:` claim
moves its donors from `blocked-by-classes` into `claimed`, so holding the scope
you are working on makes the blocker you are clearing appear to shrink. Release
the scope and re-measure before quoting a figure.

### What the view wall is made of, statically (2026-11-03)

`blocked-by-classes` is one number over a queue of 582 TUs, so it says nothing
about which mechanism to attack. This is a compiler-free census of it: for every
approved TU, every class the TU's files declare at namespace scope more than
once, classified by the first disagreement visible in the text. 4,051 class/TU
pairs, "canonical" being the ones registered in
`reverse/canonical_classes.csv` and therefore `header_adopt_lane.py`'s:

| disagreement | non-canonical | canonical |
| --- | --- | --- |
| field names | 1,751 | 163 |
| nothing visible without a layout | 1,007 | 97 |
| base arity | 367 | 150 |
| two inline bodies of one method | 164 | 62 |
| class key | 100 | 11 |
| declspec | 60 | 8 |
| base names | 50 | 9 |
| inline body against an out-of-line definition | 44 | 6 |
| base access only | 2 | 0 |

Two of those rows are not blockers and must not be read as a backlog:

- **field names** is what `tu_views` is for. It renames each view's fields to the
  superset's spelling and only refuses when the rename is unsafe, so most of
  the 1,751 are work the tool already does.
- **nothing visible without a layout** means this census found no textual
  disagreement, not that the class is blocked. Offsets, `sizeof`, padding and
  field types need `tools/class_layouts.py` and the compiler. Both of
  `BattlePlanUpdate.cpp`'s classes that `tu_views` reports as *already shared*
  land in this row, which is the proof that it is a residual bucket.

Validated against the recorded `tu_views --dry-run` for
`BattlePlanUpdate.cpp`, the one TU with a verdict on file for every class:
`BattlePlanUpdateModuleData` declspec, `BattlePlanUpdate` base arity, `Object`
field names. All three agree.

Mind the parser when repeating this. A first version matched a class head only
when its opening brace sat on the same line, which is the minority spelling
here; it found 974 pairs where the real figure is 4,051, and it biased the
table toward compact declarations. Match the head and brace as one unit across
newlines, and track brace depth so a nested class is not taken for a
namespace-scope one.

A third row is mostly not a backlog either, and the correction matters because
the line above it first read the other way. **Two inline bodies of one method is
not a `tu_views` refusal when the bodies agree.** `merge_fn` compares them
already and only refuses a genuine difference:

    if ma.body and mb.body and ws(code_text(ma.body)) != ws(code_text(mb.body)):
        raise Refused(f"{cls}::{ma.name}: two different inline bodies ...")

Of the 164 non-canonical pairs in that row, 97 are whitespace-equal and so
already accepted, 62 have genuinely different token streams, and 5 are refused
on spacing alone, because `ws` collapses runs of whitespace but does not
tokenise: `~Foo(){}` against `~Foo() {}`, or
`operator()(unsigned int a,unsigned int b)const{return a<b;}` against the same
body spaced out. A tokenising comparison would accept those 5 and nothing else,
which is not worth changing a verifier for; it is recorded here so the next seat
does not read 164 as work.

Where this leaves the mechanical lanes: the class key is finished at 14
decidable pairs of 100, because 56 are ties with no ledger spelling and 30 are
names the ledger spells both `U` and `V`, which means two types share the name.
`declspec` is nearly finished the same way. What is left that is real and not
already handled is base arity (367, of which 150 are the header lane's and most
of the rest need a complete base type, so they depend on it too), the 62 genuine
inline-body differences, and the 44 pairs where one view defines a method inline
and another defines it out of line. None of those is a spelling fix.

### Bulk merges refuse at the top of the queue on linking, not contention (2026-11-03)

A `--merge-all --jobs 1` run over the highest-value queue entries accepted no
donor at all in eight TUs: `lantheateremulator.cpp`,
`LinearCampaignManager.cpp`, `W3DShrubBuffer.cpp`, `Geometry.cpp`,
`GameWindowManager.cpp`, `BuddyThread.cpp`, `W3DView.cpp` and
`W3DVideoBuffer.cpp`. The refusals are the link audit and the compiler, not
held scope: for `BuddyThread.cpp` the TU's own file is rejected because "the
merged object would not [link]: no longer defines
`?rva00550B4C@Rva00550B4C@@QAEXXZ`, which the census still references", and
`GetNickForMessage.cpp` because three `GameSpyBuddyMessageQueue` virtuals go
unresolved.

That is worth knowing before spending a wave: the top of the queue is where the
mixed files are, so a merge there moves rows out of objects the census still
references and `link_batch_audit` correctly refuses it. The 142 approved rows of
`BuddyThread.cpp` sat behind eleven mixed donors.

**Correcting the advice this section first gave:** it said to carve the mixed
files first instead. You cannot. `split()` ends by calling `_merge()` with its
own applier, so a split IS a merge with the mixed file carved as one of its
donors, and it lands only if the destination verifies. A carve whose destination
is blocked reports the merge's verdict and writes nothing:
`ConstIntGetters4.cpp` into `ElvenWoodSpecialPower.cpp` plans cleanly and even
reports `alone: 7/7 carved rows match beside the TU under its flags`, then stops
at `blocked: no verified merge of two or more donors`, because the destination
does not compile with the carved bodies (`'rva001E42F2' : is not a member of
'Object'`).

So the order runs the other way: whatever blocks the destination has to go
first, and for 231 of the queue's 547 split destinations that includes a
`blocked-by-classes` donor. Note also that the destination's class views are
reconciled by `tu_views` only across the TU's OWN files; a member that only the
carved body needs is not in that set, so a view fix there does not necessarily
clear the carve. 54 destinations have nothing recorded against them but the
split itself, and those are the ones to try.

A practical caution on choosing a target: rank from the decision queue's full
paths, not from basenames. `W3DGhostObjectScene.cpp` lives under
`W3DDevice/GameLogic/`, not beside its TU in `W3DDevice/GameClient/`, and a
reconstructed path earns a flat `no matched rows in that file`.

Four carves tried from the top of that ranking stopped at four different gates,
which is the shape of the lane rather than bad luck:

- `ConstIntGetters4.cpp` into `ElvenWoodSpecialPower.cpp`: the destination's
  merge is blocked, as above.
- `W3DGhostObjectScene.cpp` into `W3DGhostObject.cpp` (26 of 40 rows carvable):
  `an escape-hatch count would grow (hatch_counters rule 3)`. The datum
  `animationDisableOverride` travels with the carved bodies and carries a
  hatch, so that hatch has to be retired before the carve.
- `IngameNoticeDisplay.cpp` into `Common/Bfme/IngameNoticeDisplay.cpp`:
  `the residual loses matched rows (flag region or a shared helper)`, with
  `residual_keeps: 0` against three rows that cannot ride, one of which no
  definition spells.
- the same file's listing shows the fourth: 110 of `ConstIntGetters4.cpp`'s 259
  rows have no approved TU at all, so `--shatter` cannot empty and delete it
  however many destinations verify.

So a seat should not plan a sweep of carves. Each one needs its own prerequisite
retired first - a class view, a hatch, an unrowed body, a TU approval - and the
dry run names which. Budget one carve at a time and read its gate.

## Consolidation verification checks

During the audit before pushing, check the complete consolidation batch:

- Reconcile `reverse/code_identity_baseline.tsv` and
  `reverse/data_check_baseline.txt` with moved rows and current owners. Preserve
  surviving findings and verify retirements through each register's workflow.
- Refresh `reverse/header_queue.tsv` and `reverse/ms_header_queue.tsv` for
  destination TUs and split residuals.
- Compare code/data identity, selected COMDATs and provider/consumer bindings
  before and after composition. Verify changed bindings.
- Confirm active ledgers, registers, queues and fold proofs resolve to current
  owners. Record verification results and remaining prerequisites in the handoff.

## Tooling compatibility audit before pushing

Run this audit once before each push across **all pending path changes**, so a
batch with ten moves pays for one review. Source and ledger consistency is still
verified when each move is applied; the broader consumer audit is batched here.

1. Collect old-to-new paths for moves/renames and destinations for absorbed
   fragments across the complete outgoing range (`origin/master..HEAD` after
   fetching). Use `git diff --name-status --find-renames origin/master..HEAD`
   and the merge plans; a many-to-one consolidation can appear as deletions and
   additions rather than a detected Git rename.
2. Search once with the combined old paths, basenames and moved directory names.
   Review active references in `tools/`, `.githooks/`, `.github/`, source/header
   includes, build/configuration files, source registries and documentation.
   Include relative paths, globs and code that derives paths from a directory.
3. Update affected consumers coherently in the unpublished batch. The merge
   engine already repoints `rename.PATH_COLUMNS` and the doxygen source list;
   it cannot infer every hard-coded path or directory assumption in other tools.
   Extend shared repointing support when another active registry needs it and
   test that behavior. Protected registers retain their normal admission rules.
4. Refresh affected generated reports and caches through their owning tools and
   verify affected consumers at the new paths. Do not treat old compiler receipts
   as proof for a moved source. Preserve original EA path strings and historical
   evidence; classify remaining old-path mentions rather than replacing them all.
5. Finish normal byte, ledger, ownership, include, data, EH and link checks for
   the changes that need them. Record the audited range and any intentional old
   references in the batch's handoff. Re-run the audit only if relevant path
   changes or consumers are added before publishing.

## Evidence catalogue and naming packets

`python3 tools/name_lane.py consolidate` runs BFME 2's own planner in
`tools/source_layout.py`. It inventories original paths and produces work
packets for consolidating fragments while the existing naming lanes recover
identities. It edits no game source, ledger, reference, git index or claims,
and does not commit or push. No output is an admission to merge.

```text
python3 tools/name_lane.py consolidate --out build/consolidation
python3 tools/name_lane.py consolidate --rotwk C:\GitLab-Runner\rotwk-unofficial-202\source
python3 tools/name_lane.py consolidate --check build/consolidation
```

The ROTWK path is optional and machine specific. `--bfme1` accepts another
checkout; both BFME 1 layouts (`game/` and `Code/`) are recognised. `--zh` selects
an explicit `GeneralsMD/Code` tree. `--under Code/GameEngine/.../` narrows the
survey, but a destination outside that ledger scope remains blocked.

### Sharing views does not move the merge: the classes it can write are not the ones blocking (2026-11-04)

Two TUs had their private class views shared and then re-measured with
`tu_skeleton --merge --dry-run`. Both went **0 donors -> 0 donors**:
`TransportContain.cpp` (1 class written) and `SiegeDeploySpecialPower.cpp`
(5 written). The work was real and byte-verified; the merge did not move at all.

The cause is a selection effect inside each TU, and it is worth stating because
the obvious plan - sweep `tu_views` across the `blocked-by-classes` ranking and
expect merges to fall out - does not work. `tu_views` writes the classes whose
views are *compatible*, and refuses as a CONFLICT the ones that are not. The
donors are blocked by the second group. On `SiegeDeploySpecialPower` the two
sets line up one for one; the donors' compiler errors name the conflicts and
nothing else:

| donor error | class | why `tu_views` refused it |
| --- | --- | --- |
| `C2509: 'xfer' : member function not declared in 'SiegeDeploySpecialPower'` | `SiegeDeploySpecialPower` | base clause differs across its 6 files |
| `C2504: 'WeaponModeSpecialPowerUpdateBase' : base class undefined` | `WeaponModeSpecialPowerUpdateBase` | `m_vtable` at +0x0 lies under the bases (own data starts at +0x28) |
| `C2248: 'Object::findModule' : cannot access protected member` | `Object` | written, then reverted: the block does not compile in ComputeApproachPoint.cpp |
| `C2027: use of undefined type 'ModuleData'` | - | an incomplete type, not a shared view at all |

The five that landed - `Rva004598F2Point`, `SiegeDockingIface`,
`SiegeDockingBehavior`, `SiegeDeployModuleDataView`, `DynamicPortalBehaviour` -
were not in any donor's way. `TransportContain` is the same shape: the residual
errors were `OpenContain::onRemoving`, `UpdateModuleInterface` and
`OpenContainModuleData`, all of them types the TU does not share a view of.

So `blocked-by-classes` in `build/merge_all/decisions.json` (685 files over 317
TUs) means "some views in this TU disagree", not "reconciling the agreeable ones
unblocks it". The reason is in the label the tool prints for itself: *header lane
ranking; not compiled*. Rank a merge-unblocking pass by a TU's **CONFLICT** list,
not by its plan list, and expect each conflict to be its own piece of work - a
base clause, a class key, a vtable placement, an access level - with some of them
only retirable through the header lane.

That does not make the plan list worthless: one shared spelling is a prerequisite
that has to be paid once per class either way, and it is cheap and safely
verified. It is just not a merge, and a seat should not report it as progress
toward SOURCE FILES.

### How much of the view lane is real (2026-11-04)

Measured after `tu_views --dry-run` was taught to report `already shared` (it
previously printed a plan for every shared class, and only the apply path tested
whether the files already agreed, so the counts it gave a planner were inflated -
18 plans on `TransportContain.cpp` where 1 class needed writing).

Over the 70 TUs with the most `blocked-by-classes` donors: **87 classes actually
need a write**, spread over 45 of those 70 TUs; the other 25 need none. The best
TU in the sample holds 6. Scaled across all 317 such TUs that is roughly 390
classes, in ones and twos, not the per-TU hauls the old count implied. Budget it
as a long tail of small, cheap, independently verifiable edits, and do not expect
any one of them to land a merge.

### The conflict census, and why none of it is a mechanical lane (2026-11-04)

Classified from the `evidence` string `tu_views` already writes, over 168 TUs
examined: **273 CONFLICTs across 146 TUs**.

| count | blocker |
| --- | --- |
| 100 | base clause differs |
| 24 | vtable/vfptr placement |
| 23 | unclassified |
| 22 | class declspec differs |
| 18 | class-key differs, ledger silent |
| 18 | virtual slot filled two ways |
| 18 | fields overlap |
| 16 | no layout evidence (**8 of these were false**, see below) |
| 15 | field typed differently |
| 8 | anonymous/nested aggregate |
| 5 | two inline bodies |
| 3 | inline vs out of line |

**Realistically mechanical: about 6 of 273, roughly 2%.** That figure replaces
three earlier estimates of mine, each made from a category label rather than its
evidence, and each wrong: 15 of 94, then 11, then 3. The two categories that look
mechanical are not:

- **class-key differs: 0 decidable.** All 18 carry the marker
  `and no matched name spells it`, which is the tool saying the ledger holds no
  mangled name that settles the key. Not a sample - all 18.
- **class declspec differs: about 1 in 4.** Checking ctor/dtor row ownership for
  eleven cases decided 3, left 7 undecidable because the ctor owner and the dtor
  owner disagree, and 1 unresolvable. A declspec row is a candidate for that
  check, never a decided fix, and the two rows must not be added together.

**One category was partly bogus, and is now fixed.** Of the 16 rows reading
`no file's CodeView lays X out (nothing uses it)`, **8 were not conflicts**: the
two views spell the class identically, so nothing needs writing and the merge
emits it once as it stands. They were refused only because `describe()` called
`plan()`, `plan()` needs a layout, and a class that two files declare identically
but neither file uses concretely has no CodeView record to give it.
`describe()` now asks `spelled_alike()` first (`ad6ec1dc9a`), which compares the
views exactly as `plan()` does and needs no layout. Identical views cannot produce
an edit, so the change can only turn a false CONFLICT into `already shared`.

Verified on the real declarations, not just in tests: `TerrainLighting`,
`W3DDisplay`, `BfmePoolHolder`, `AptPlayerStatusObjectives`, `BehaviorModuleBase`,
`BehaviorModuleOther` and `Rva005AE26AOwner` all report `already shared` when run
with an empty layout provider, with **zero builds invoked** and the worktree
untouched. The other 8 of the 16 genuinely differ and stay CONFLICT, as does a
minified-against-formatted pair: `ws()` collapses whitespace runs but not
whitespace presence, which is why `AptValue.cpp`'s reformat earlier the same day
was a real landed change rather than a false positive.

Measured across every category rather than just that one, `spelled_alike()`
turns **13 of 310 reported conflicts, 4%, into `already shared`**: 8 of the 17
no-layout rows, 2 anonymous/nested, 1 vtable/vfptr and 2 others. So the census's
conflict total is 13 lower than it reads above, and the `blocked-by-classes`
ranking that seats pick work from was pointing at a handful of TUs whose named
class was not blocking anything.

The bound matters as much as the gain: **zero** of the four large categories had
an identical pair - base clause (112), class declspec (30), virtual slot (22) and
fields overlap (20) are genuine disagreements to a case. This fix cleans the
reporting; it does not open the lane.

The reason is structural and worth stating once: these conflicts are **survivors**.
`tu_views` writes every class it can settle and refuses the rest, so the census is
by construction the residue of everything mechanisable. Any subset of it that
looks cheap is selected against being cheap. Price a category by opening its
evidence; a label is not a measurement.

### Audit of the automated view pass (2026-11-04)

The 29 view commits of 2026-11-04, 14 of them written by an unattended driver,
measured through `name_metric.declared()` on every changed file:

- **+77 declared names, +19 weak, net +58 strong.**
- **No commit lost a strong name on balance.** Four individual strong names went
  across all 29 (`before`, `m_movie`, `opaque`, `enabled`) against many gained,
  the largest being `Display.cpp`'s six real members.
- 71% of the names added are non-placeholder, against a 67.69% tree baseline, so
  the pass nudges READABLE NAMES up rather than down.

Two side effects are worth knowing before running the pass again.

**It spreads placeholder field names.** Every weak name it introduced is an
offset-derived member the tool did not invent - `m_260`, `m_438`, `m_str80`,
`m_flag88`, `m_16C` - propagated from the view that had the field into a view that
had nothing at that offset. That is the correct trade (a named field beats a gap),
but it widens the rename surface: a later naming-lane rename of `m_260` now has
more files to touch. Prefer renaming a class before sharing its views, not after.

**It resolves project typedefs.** Three cases in 29 commits: two `UnsignedInt` and
one `Real` came back as `unsigned int` and `float`. Same types here, and the
receiving views already said the resolved form, but `Real` and `UnsignedInt` are
the retail idiom and the block does not preserve them.

Neither is a reason to stop the pass. Both are reasons not to run it over a
subsystem whose names are about to be recovered.

### Two smaller conflict categories, anatomised (2026-11-04)

**`virtual slot filled two ways` (22).** Six pit a named method against
`__vecDelDtor(uint)`, which is one view claiming slot 0 holds the virtual
destructor while the other gives it a method - usually because one view omits the
virtual destructor and its slots shift. The ledger can only settle that where a
destructor row exists, and it does for **2 of the 6** (`Rva009519B`,
`InputChunk`); the other four have no `??1`/`??_G`/`??_E` row at all, so the
`__vecDelDtor` claim is unbacked. Of the remaining 16, seven pit two real names
against each other and seven are placeholder-against-placeholder. So about 2 of 22
are evidence-backed, consistent with the ~2% ceiling above.

**`fields overlap` (20).** Mostly not a contradiction: **16 of 20 are a
granularity difference at the same offset** - one view names a field and another
covers the same bytes with a single wider one, like `x +0x0..0x4` against
`a +0x0..0xC`, or `blendNdx +0x0..0x4` against `m_data +0x0..0x10`. The wider
field is usually opaque and placeholder-named (`a`, `f`, `m_data`, `pair68`,
`unmodelled68`, `presets`), so the finer view is simply more resolved. Only 4
straddle offsets in a way that genuinely conflicts.

That makes the 16 a **candidate** for the same treatment `head_free()` gives a
silent head: a placeholder-named span that another view subdivides is arguably no
evidence about those bytes. It is recorded as a candidate and nothing more. Two
cautions, both earned today: `tu_views` may already handle some of this (its
doctrine does cover padding and unclaimed `sizeof`, and the one relaxation I
proposed from a category shape this session - for base clauses - turned out to be
a bug that `head_free()` already prevented), and a wide field may be a real object
passed by value rather than a gap, in which case subdividing it changes member
access. Anyone picking this up should read `plan()`'s field loop first and expect
the answer to be no.

### A worked base-clause conflict: mapper.cpp's TextureMapperClass family (2026-11-04)

One of the 16 non-canonical base-clause conflicts, written out so the next seat
starts from the real question instead of the diff. Nothing here is resolved; what
follows is the evidence and the one measurement that would settle it.

`mapper.cpp`'s TU holds two incompatible models of the same four classes.

`TextureMapperApply.cpp` carries the hierarchy, and it reads like recovered
source: `TextureMapperClass : public RefCountClass` with a virtual destructor,
then `Mapper_ID`, `Clone`, `Is_Time_Variant`, `Apply`, `Reset`, `Needs_Normals`,
`RetailSlot20`, `Calculate_Texture_Matrix`, and `unsigned int Stage`;
`GridTextureMapperClass` and `ScaleTextureMapperClass` derive from it;
`LinearOffsetTextureMapperClass` derives from `ScaleTextureMapperClass` and adds
the UV offset fields.

`TextureMapperFXShaderConvert.cpp` carries flattened views of the same three
derived classes, each with no base, each naming its virtuals by vftable byte
offset - `slot00`, `slot04`, `Mapper_ID`, `slot0C`, `slot10`, `slot14`, `slot18`,
`slot1C` - then one method of its own (`rva00187AD0`, `rva00187690`,
`rva00187850`), and an inline `Get_Stage()` returning `Stage`.

`TextureMapperSlot8.cpp` carries a third, minimal view: `TextureMapperClass` with
no base and a single virtual `_bfme_mapper_v8(int)`.

**Measured, 2026-11-04.** An earlier version of this section guessed that the two
models disagree about slot positions - that the flattened views put `Mapper_ID`
at +8 where the hierarchy put it at +4 - and said one compiler run would decide
the family. The compiler run happened and **the guess was wrong**: those offsets
were counted off the source text, not read from a layout.
`python3 tools/class_layouts.py` on the three files reports:

- Hierarchy (`TextureMapperApply.cpp`): `TextureMapperClass` is `size=12`,
  `bases=[[RefCountClass, 0]]`, and its vslots run
  `1=__vecDelDtor(uint), 2=Mapper_ID(), 3=Clone(), 4=Is_Time_Variant(),
  5=Apply(int), 6=Reset(), 7=Needs_Normals(), 8=RetailSlot20(),
  9=Calculate_Texture_Matrix(Matrix4*)`, with `Stage` at +8. Slot 0 is
  `RefCountClass`'s own, which is why the list starts at 1.
- Flattened (`TextureMapperFXShaderConvert.cpp`): each derived view is
  `bases=[]`, `vfptr=True`, with vslots
  `0=slot00(), 1=slot04(), 2=Mapper_ID(), ... 8=rva...(Rva00082EB8*)`.

**The slots agree.** `Mapper_ID` is slot 2 in both. The flattened `slot00` is
`RefCountClass`'s slot and `slot04` is the deleting destructor, so the placeholder
names are just unrecovered spellings of the inherited slots, not a competing
claim. The flattened views also name slot 8, which the hierarchy calls
`RetailSlot20`, and they name it **differently per derived class**
(`rva00187AD0`, `rva00187690`, `rva00187850`) - so that slot is an override point,
and those three are its real identities.

The genuine disagreement is **size and fields**, which `tu_views` never reached
because the textual base clause refused first. Flattened `GridTextureMapperClass`
is `size=40` with `NumRefs@4, Stage@8, FPS@12, m_10@16, m_14@20`; the hierarchy's
`GridTextureMapperClass` is `size=12` with no fields of its own. The hierarchy is
the **incomplete** one here: it has the base chain and the real method names, and
the flattened views have the data members it lacks.

**The slot-8 identity, confirmed by the file itself.**
`TextureMapperFXShaderConvert.cpp`'s own header comment opens: "The BFME2 texture
mappers' FXShader conversion virtual (**vtable +0x20**; WB 0x00A33B70 by its
strings)", and says the conversion's original name is not recovered. Slot 8 is
vtable +0x20, which is exactly the slot the hierarchy view calls `RetailSlot20`.
So `RetailSlot20` is not a mystery: it is the FXShader conversion virtual, and
`rva00187690` (Scale), `rva00187850` (LinearOffset) and `rva00187AD0` (Grid) are
its three per-class overrides. That is a naming-lane lead with the evidence
already in the tree.

**The target declarations, from the measured layouts.** Written out so the edit is
mechanical rather than exploratory. Sizes and offsets are `class_layouts.py`
output, not inference:

```
RefCountClass                       vfptr +0x00, NumRefs +0x04, size 8
  slot 0                            its own virtual
TextureMapperClass : RefCountClass  Stage +0x08, size 12
  slot 1 __vecDelDtor   slot 2 Mapper_ID       slot 3 Clone
  slot 4 Is_Time_Variant slot 5 Apply          slot 6 Reset
  slot 7 Needs_Normals   slot 8 RetailSlot20 (+0x20, the FXShader conversion)
  slot 9 Calculate_Texture_Matrix
ScaleTextureMapperClass : TextureMapperClass
  ScaleX +0x0C, ScaleY +0x10, size 20          (hierarchy spells these Vector2 Scale +0x0C)
GridTextureMapperClass : TextureMapperClass
  FPS +0x0C, m_10 +0x10, m_14 +0x14, m_18 +0x18,
  LogGridWidth +0x1C, LastFrame +0x20, FrameOffset +0x24, size 40
LinearOffsetTextureMapperClass : ScaleTextureMapperClass
  CurrentUVOffset{X,Y} +0x14/+0x18, UVOffsetDeltaPerMS{X,Y} +0x1C/+0x20,
  LastUsedSyncTime +0x24, UOffset +0x28, VOffset +0x2C, ClampFix +0x30, size 52
                                               (hierarchy spells +0x28 StartingUVOffset)
```

Both views are consistent with this; each is missing a different part of it. The
hierarchy lacks **all seven of Grid's fields** - it reports `size=12` where the
layout says 40 - and the flattened views lack the base chain.

**Scope warning, which is why this was not attempted in a short window.**
`TextureMapperFXShaderConvert.cpp` declares neither `RefCountClass` nor
`TextureMapperClass`, so the edit introduces two class declarations and rewrites
three, preserving an exact vtable across all five in an `/O2` TU where every body
must still match. Each derived view also declares its own `Mapper_ID`. Budget
several build iterations, and do `GridTextureMapperClass` first: its 28 missing
bytes in the hierarchy view are the one place the two models give different sizes,
so it is the real test of this reading.

So the resolution is not a tool relaxation and not a coin flip. It is: give each
flattened view its real base (`: public TextureMapperClass`, and
`: public ScaleTextureMapperClass` for the linear-offset one), delete the
placeholder slot declarations that belong to the base, keep its own slot-8
override and its fields, and carry those fields into the hierarchy view. Then both
views agree and the byte check arbitrates. That is per-class reverse engineering
with a clear target, which is the honest description of this whole category.

Worth noting for whoever picks it up: `RefCountClass` is not in
`reverse/canonical_classes.csv`, so this family needs no header-lane work. It is
the cheapest shape of base-clause conflict available, which is why it is written
up rather than one of the module-data cases.

### What the base-clause conflicts are made of, and why no tool change clears them (2026-11-04)

`base clause differs` is the largest group in the CONFLICT census by a wide
margin - 100 of 273 over 146 TUs, so a little over a third, not the "half" an
earlier 94-conflict sample here suggested - so it is worth knowing exactly what it
is before anyone tries to automate it. Two things were measured.

**Canonical bases gate two thirds of it, not all of it.** None of the 48
conflicted classes is itself in `reverse/canonical_classes.csv`; they are all
private views. But 32 of the 48 name at least one canonical base (`UpdateModule`,
`DrawModule`, `SubsystemInterface`, `Snapshot`, `ModuleData`, `CreateModule`,
`RefCountClass`), so the header lane gates those. The remaining **16 involve no
canonical class at all** and are reachable from the consolidation lane alone:
`W3DVideoBuffer`, `Rva0043D193`, `AptOnlineLogin`, `AptSkirmish`,
`GameWindowTransitionsHandler`, `GarrisonObjectGroupOrder`, `HordeContain`,
`AODHordeContain`, `HorseHordeContain`, `Rva00596F18`, `Rva007E86B0Base`,
`Rva0014F401`, and the three `*TextureMapperClass` cases in `mapper.cpp`. That
corrects an earlier claim in this file that the group "mostly needs the header
lane": two thirds, not all.

**The conflicts are real, and the tool's refusal is load-bearing.** 26 of the 48
print one variant as `-`, a view declaring no base while the other variants agree,
which looks like a view that is merely silent - and `tu_views` already has the
right doctrine for genuine silence: `head_free()` ignores any view with no base,
no class declspec, no vfptr, no virtual slot and no virtual method, so the
interface-only stubs (`ModuleFactoryInit.cpp` declaring a class solely to call one
static factory) are already excluded and never reach the comparison.

The `-` views that do reach it are a different animal: **30 of those 32 declare
their own virtual functions**, and 11 also flatten the base away into opaque
padding. `FireWeaponUpdate` is the clean illustration. In
`DamageFieldUpdate.cpp` it declares no base, four virtuals of its own
(`~FireWeaponUpdate`, `v01`, `v02`, `xfer`) and `char m_unrecovered04[0x2C-0x04]`.
In `DamageFieldUpdateRva004911AE.cpp` it is `: public UpdateModule` with
`Weapon *m_20; DamageNode *m_24; void *m_28;`. Those are incompatible models of
one class: the first claims the vtable slots are introduced here, the second says
they come from `UpdateModule`. Picking either silently moves the vftable, so
refusing is correct.

So there is no relaxation to be had here. Clearing one of these means recovering
which class really introduces the slots and giving the flattened view its real
base and real fields - reverse engineering per class, with the byte check as the
arbiter. The 16 non-canonical ones are where a seat without header-lane access can
start.

### The declspec conflicts are not a mechanical lane (2026-11-04)

The CONFLICT census groups 9 "class declspec differs" and 1 "member declspec
differs" rows, and they look like the cheapest pile in it: `__declspec(novtable)`
suppresses the vftable stores in a class's own constructor and destructor, so it
changes generated code only in the file holding those bodies, and the
authoritative spelling should simply be whichever file owns the class's
`??0`/`??1`/`??_G`/`??_E` rows. That rule settled four classes earlier the same
day (`5ab85e1f799`). Applied to all eleven, it settles **three**:

| class | spelling | evidence |
| --- | --- | --- |
| `DamageFieldUpdate` | novtable | one file owns both the ctor and the dtor rows |
| `Rva0043D16F` | plain | single ctor owner is plain; the novtable spelling owns nothing |
| `DetachableRiderBody` | novtable | single ctor owner, and no dtor row exists at all |

**Seven are undecidable, and all seven fail the same way: the ctor owner says
plain and the dtor owner says novtable.** Seven out of seven in that direction is
not noise. `GrantUpgradeCreateModuleData`, `InheritUpgradeCreateModuleData`,
`DamageFieldUpdateModuleData`, `PartTheHeavensUpdateModuleData`,
`RespawnUpdateModuleData`, `RousingSpeechUpdateModuleData` and `RankInfo` each
have their constructor in a file spelling the class plain and their destructor in
a file spelling it novtable, and **both files byte-match retail today**.

That is coherent rather than contradictory, and it is a property of the
one-function-per-file tree: a spelling only reaches the bodies in its own file, so
two files can hold incompatible spellings and each still be locally exact. What it
means is that retail's constructor stores the vftable where its destructor does
not, and no ledger row says why. Merging forces one spelling and breaks whichever
body loses. Explaining it is reverse engineering, not a lookup, so none of these
seven should be touched by a mechanical pass.

Three of the seven are not really declspec cases at all: their ctor and dtor files
give the class **different bases** - `CreateModuleData` against `Snapshot` for the
two UpgradeCreate module datas, `SpecialAbilityUpdateModuleData` against
`Rva0044ECCE` for `RousingSpeechUpdateModuleData`. The layouts are compatible
enough that `tu_views` reported the declspec first, but the base clause is the
primary disagreement and has to be settled before the keyword means anything.
`RankInfo` and `RespawnUpdateModuleData` are the pure cases, identical bases and
nothing differing but the keyword.

The eleventh, `EvaMessageInfo`, is a different animal: one file marks its
destructor `__declspec(dllimport)` with an inline body, another only declares it,
and **no file under `Code/` defines it**. There is no `functions.csv` row for
`??1EvaMessageInfo@@`; the single `symbols.csv` row is recorded in
`reverse/re_attempts.log` as really being
`??1BfmeStringRecord00111ACF@@`, a placeholder shared by other 28-byte record
views, and already blocked there as a class-identity question for the naming lane.
So the dllimport is an identity claim the ledger does not support. Leave it to
that lane.

**The general lesson, which cost three wrong estimates today.** The conflicts that
reach this census are survivors: `tu_views` already wrote everything it could
settle, so what remains is selected for being hard. Every subset of it that looks
mechanical has shrunk on inspection - "ledger-decidable" went 15 of 94, then 11,
then 3. Price a conflict category only after opening its evidence, never from its
label.

### Eleven TUs worked: what the plan count is worth (2026-11-04)

Eleven TUs were claimed, reconciled and landed in one pass, which is enough to
price the lane properly rather than from the dry run's plan count.

| | classes |
| --- | --- |
| applied and byte-verified | 20 |
| tried and reverted by the byte check | 16 |
| refused as CONFLICT | 26 |
| already shared, nothing to write | 27 |

Of the 36 classes `tu_views` actually attempted, **20 landed - 56%**. That is the
figure to plan with, not the plan count: a dry run that promises six classes is
promising about three. The sweep's 87 plan classes over the 70 worst TUs are
therefore worth roughly 49 landed classes, with the other 38 failing the byte
check, and a separate population of 26-per-11-TUs conflicts that needs its own
work.

Reverts are not distributed evenly, and the ranking is close to useless for
picking a target. `LinearCampaignManager.cpp`, which the sweep ranked **first**
on plan count, landed **1 of 6**: five reverted and six more were CONFLICT.
`SiegeDeploySpecialPower.cpp` landed 5 of 6. `Display.cpp` landed both of its
two and produced the pass's largest name gain. So plan count predicts neither
landed classes nor value, and a seat is better off taking any free TU with a
plan of two or three than queueing for the top of the list.

All eleven measured 0 donors before and after, as the section above predicts.

### What sharing a view does to declared names (2026-11-04)

Worth measuring, because the superset block rewrites every method declaration in
the classes it touches and normalises their parameter spellings, so it can hand a
name back weaker than it found it. A raw diff shows exactly that:
`void rva00167EF8(const Rva00167EF8Rec &src)` came back as
`(const Rva00167EF8Rec &)`, and in a TU left unlanded here, `void m( int value )`
came back as `void m(int a)` - `value` is a strong name by
`tools/name_metric.py`'s own predicate and `a` is weak.

Measured through `name_metric.declared()` rather than off the diff, the lane is
**net positive**: across the four TUs landed today it is +15 declared names with
+3 weak, so +12 strong. The gains are real member names propagated into views
that had none (`m_delay`, `m_searchRadius`, `m_pushDistance`,
`m_disabledDuration`, `m_evacuate`, `m_exit`, `config`, `owner`, `begin`, `end`,
`m_refCount`), plus one parameter improved from `o` to `other`. One strong name
was lost in all four commits put together (`enabled`, in AIUpgradeScienceBuilder).

The reason the diff reads worse than the metric: `declared()` counts a class
member's own name through `members()`, and counts parameter names only through
`param_names()` on function *definitions*. Parameter names inside a member
*declaration* are outside the metric entirely, so neither the dropped `src` nor
`value` -> `a` moves READABLE NAMES at all. Do not reach for the metric to justify
or to refuse one of these edits; it cannot see that part of the change.

The human-readability point still stands on its own, and it is small: where the
views disagree on a parameter name, the block takes the seed's, which may be the
poorer one, and the authoritative name is usually the one on the out-of-line
definition (`Gen_00489270::m` is defined with `val` in
`InGameNotificationType.cpp`, while the views carry `a`, `value` and no name at
all). Improving that is a naming-lane rename with its own approvals, not
something to slip into a view commit.

### Evidence, without upgrading a hint into proof

The baseline `game.dat` SHA-256 is
`f008b587570bad693981dc7218588c81d192a1e064b0f7f861539c51156a7640`.
It contains **173 distinct original `.cpp` paths and 10 header paths**. The
173 count describes surviving assertions, not the size of the original tree.
The planner extracts every occurrence, retaining its raw EA spelling, image,
file offset, string RVA and encoding. Headers are catalogued but cannot become
translation-unit destinations.

WorldBuilder has considerably more surviving paths, including editor-only
files. Its path inventory establishes that a file existed in that build; a
callgraph pairing in `wb_name_leads.csv` supplies a file hint for a BFME 2
function. Neither fact proves that the retail function belonged in that TU.
`tools/tu_map.py` uses a pairing (W) only as corroboration: it anchors a TU
when it names exactly the path a row's own naming hint already gives, and only
while `tu_map.py --validate` shows W agreeing with the game's own `__FILE__`
strings at 99% or better (170/170 when it landed). W never names a TU itself.

Zero Hour supplies actual source/header structure and out-of-line definitions.
The planner reuses `tu_map.zh_definitions`, rather than matching filenames or
every occurrence of `Class::method`. Its same-name definitions remain donor
hints. BFME 1 supplies its EA `ea_evidence.csv` and the existence of reconstructed
counterparts. Its name/file pairs join **inside BFME 1 first**, then join BFME 2
by spelling. BFME 1 addresses never become BFME 2 addresses. `wb1-run`,
`retail-run` and similar propagated routes are preserved in the catalogue but
cannot nominate a BFME 1 donor home.

Current retail string references are stronger: the referenced path must exist
in the current image, and the instruction at the xref must be an executable
`push imm32` or `mov r32,imm32` whose operand points at that exact string.
This repository's `string_xrefs.tsv` records the owning function's entry; the
planner uses the existing Capstone dependency to find instruction boundaries
inside that row's own extent. A short folded twin cannot borrow an instruction
from a longer row at the same address. Without Capstone, owner-level references
remain unverified. Unsupported instructions remain unrouted. Header references do not route TUs.
Several target paths for one body are a conflict, not a vote.

An approved `tu_map.csv` assignment counts as target routing only if
`tu_map.check_fresh` passes and `approved_tu` finds no contradictory F/Z/S or
bracketing anchor. A stale map is useful context but has hint strength. Even
current map approval remains a reconstruction judgement: the packet preserves
its evidence and requires review before execution.

ROTWK INI module tokens are vocabulary hints, with example file/line citations.
They never create a C++ path or prove a class, member, ABI or layout. Actual
source paths are catalogued only when a C/C++ file under a recognisable `Code/`
path exists. Game `.map`, `.apt`, model and art files are not C++ source evidence.

### Reviewable artifacts

| Artifact | Purpose |
|---|---|
| `paths.csv` | Union of retail, WorldBuilder, Zero Hour and BFME 1 EA paths; origins, citations, case variants and current counterparts |
| `image_paths.jsonl` | Every original image-path occurrence, including all 173 retail `.cpp` paths and the ten headers |
| `retail_paths.csv` | Compact retail-only occurrence list with exact image hash; suitable for a checked-in evidence snapshot |
| `queue.csv` | Every selected active source; whole-file, mixed or unresolved routing and static hazards |
| `groups.json` | Destination groups, source packet keys/hashes, prerequisites and proposed checks |
| `files.jsonl` | One packet per active source: row names/RVAs/extents, routing evidence, data rows, includers and compile lines |
| `data_hints.csv` | Optional ROTWK vocabulary, explicitly graded as data only |
| `report.md` | Counts and the first investigation packets |
| `inputs.json` | Input and output hashes, reference revisions, gitlink, selection and map freshness |

Default outputs stay under ignored `build/consolidation/`. A review snapshot
may be written under `reverse/consolidation/`; other output roots are refused.
The snapshot records the locally selected BFME 1 revision separately from the
superproject gitlink, preserving an already advanced reference checkout.

The snapshot fingerprints the actual source trees, ZH source contents, images, ledgers,
flag regions, path-keyed registers and tool versions. Adding a new source or
header invalidates it. Inputs are checked again before publication to reject a
scan made during concurrent edits. `--check` checks input and output currency;
it does not run a compiler, certify evidence or prove merge safety. Regenerate
after any naming, header adoption, source, ledger or reference change.
BFME 1's reconstructed tree contributes path existence only, so its inventory
is fingerprinted; its EA evidence is fingerprinted by content. ROTWK fingerprints
the inventory and the source/INI text used for hints; unused art payloads are not read.

### Working a packet while naming

1. Recheck the snapshot and run `tools/check_csv.py`. Review every destination
   alternative and source row, including attached EH funclets. Resolve mixed or
   incomplete ownership before moving a whole file. Never drop unresolved rows.
2. Obtain names through `name_evidence.py` and `rename.py`, or the existing blind
   agreement lane for inferred names. The planner cannot grant `canonical:file`,
   `canonical:zh`, `canonical:bfme1` or any other canonical basis. Renaming a
   placeholder can unlock donor evidence on the next scan.
3. Reconcile duplicate class views through `class_views.py`, `class_contract.py`
   and `header_adopt_lane.py`. Check real BFME 2 ABI evidence; do not copy BFME 1
   or ZH offsets. BFME 1's `name_oracle.py` is a reference for building checked
   witnesses, not an oracle for BFME 2 offsets.
4. Reconcile compile environments: `// cl:` include paths, macros, runtime/EH
   flags, current region defaults, per-file overrides and compiler profiles.
   Equal `// cl:` lines alone are insufficient. Inspect static names, macros,
   pragmas, relative/quoted includes, source inclusions, `__FILE__`, `__LINE__`
   and case-sensitive directory spelling. Avoid changing a protected register
   to make a merge appear admissible.
5. For an approved TU, run `tools/tu_skeleton.py --merge TU --dry-run`,
   retain exact source provenance, and compare
   every affected whole body and relocation against retail. Check EH ownership,
   data definitions/references, internal symbol collisions and providers and
   consumers together. A move with different include resolution can compile and
   still use the wrong declarations.
6. Only after a successful trial, apply through `tools/tu_skeleton.py --merge TU`
   under the execution workflow above. Repoint function and data rows and ownership/source
   registers together; retain names, signatures, pins, parent notes and ICF proof.
   Drain a fragment completely before deleting it. Run the ordinary byte,
   declaration, identity, ownership, data, case, EH and local link checks. The
   maintainer-only runners in `AGENTS.md` still require their normal permission.

`potential_file_reduction` is an unverified upper bound per packet. Mixed files
may appear in several packets, so those numbers cannot be added. No packet is
called mergeable; even one with no static blockers requires a compiler trial.
Changing file count is not recovered-byte progress.

### BFME 1 tooling reviewed

The local reference's `ea_evidence.py`, `ea_queue.py`, `name_oracle.py`,
`name_lane.py`, `placement_queue.py`, `mergeable_groups.py` and
`docs/placement_lane.md` informed this design. In particular, BFME 1 found that
concatenation failed even in groups passing its static checks. Its placement
lane therefore moves fragments and preserves per-file environments; it does not
solve consolidation by itself. BFME 2 keeps that distinction and uses its own
existing guarded naming, TU, class and verification machinery.

### FXParticleSystem: approved units are single files, approval is the wall (2026-11-04)

`name_lane.py consolidate --under Code/GameEngine/Source/GameClient/System/FXParticleSystem/`
surveyed 294 files in 10 groups, none statically clear. `tu_skeleton.py --list` on the directory
names nine approved TUs, and none of them has anything to merge:

- The seven `fxps*module.cpp` TUs each hold one approved row, their `__FILE__` anchor, already in
  a file of that name. `DefaultModuleHeadBase.cpp` (three provisional N rows) is one file too.
- `T1Base_005F3750.cpp` holds only four `p-group provisional` funclets of 0x0055C903, whose own
  row is only proposed (N). A carve cannot move funclets without their parent. The parent's
  WorldBuilder pairing names `fxpsdefaultdrawmodule.cpp`, so the provisional name is probably not
  its unit. Its unresolved `??1T1Base_005F3750` is the `Rva003ABA36` class-identity fold recorded
  in LINK-181, not a TU question.

**Why the rest has no TU (1,199 of the 1,318 tu_map rows of the directory's files).** Each `fxps`
unit has one F anchor, so C brackets nothing. Retail's file names (`fxpsemitterboxvolumemodule.cpp`)
do not follow `<dir>/<Class>.cpp`, and `tu_map.demangle` reads no class from a namespaced name
(`?getPosition@SphereEmissionVolumeModule@FXParticleSystem@@...`), so N, U and W have nothing to
work with. The code is new in BFME 2, so Z and S cannot reach it.

**Missed F evidence (target facts).** F reads only `reverse/string_xrefs.tsv`, the Ghidra export,
which lists the references Ghidra created. A scan of retail `.text` for imm32 operands equal to one
of the 173 retail `.cpp` path strings, decoded with capstone inside the owning row, finds 301
`push`/`mov` references in 213 functions that the export lacks:

| owner's current map row | functions |
| --- | ---: |
| approved for the same TU (agreement) | 139 |
| no TU | 21 |
| proposed for the same TU | 10 |
| proposed or displaced to another TU | 23 |
| approved for another TU | 20 |

Most of the 20 are provisional names that retail's own path corrects. For example,
`AINavyUnitBattleShip` is approved under `Common/` while retail names
`GameLogic/SkirmishAI/AITacticalAI/AITacticalNavy/`, and `HordeContain.cpp` sits one directory above
retail's `Contain/HordeContain/`. One is a real conflict: the function at 0x00216332, approved for
`BannerUI.cpp` by C, pushes `LivingWorldAIArmyMover.cpp`.

In this directory the missed references are:
- `fxpswindmodule.cpp` at 0x003A5926 (`mov ebx`) in 0x003A58A6 and at 0x003A59FB in 0x003A59C3,
  three anchors over 0x003A5572..0x003A5A42;
- `fxpsstoragemodule.cpp`, which has no F row at all, at 0x003B066A in 0x003B0578 and at
  0x003B096E/0x003B0ABD in 0x003B0869;
- `W3DFXParticleSystem.cpp` at 0x0004D229/0x0004D26A in 0x0004CF9A.

Every reference is listed in `reverse/attempt_support/tu-evidence-missed-file-xrefs-20261104.tsv`.

**What approval needs (maintainer action, stopped here).** Two routes: re-export
`string_xrefs.tsv` with the references Ghidra missed, or let F take capstone-verified imm32
operands from retail, as `source_layout.py` already does for routing. Either route then needs
`tu_map.py --validate` and the hold-out over the approvals it changes. A seat must not hand-edit a
generated input to move approvals.

WorldBuilder pairings also name six draw-module units for constructors and draw bodies:
- `fxpsdefaultdrawmodule` at 0x0055C478, 0x0055C8BC and 0x0055C903;
- `fxpsstreakdrawmodule` at 0x00560135;
- `fxpsquaddrawmodule` at 0x00560A58;
- `fxpsbutterflydrawmodule` at 0x005613B2;
- `fxpslightningdrawmodule` at 0x00561D3D;
- `fxpsgpudrawmodule` at 0x005639A4.

These are donor facts. W anchors only where a row's N gives the same path, which the naming above
rules out.

**Initializers.** The 52 "registered twice" from `FXParticleSystemFactories.obj` were a counting
error (LINK-236, `b4d81c1215`). Merging these files would retire emission scaffolding (146
unidentified registrations), not double construction.

### The view lane's unit of work was the TU, and that is what capped it (2026-11-04)

The whole-TU sweep in `driver_log.tsv` looks as though contention stopped it: 513 of its
1074 rows say "another seat holds one of its files", against 105 landings. Both readings of
that are wrong, and the second one matters.

**The 513 are 92 TUs, not 513 refusals.** A contended verdict is not terminal, so the driver
retried it on each of its eight passes; 36 of those TUs contributed exactly 8 rows each. A
snapshot of the live claim table taken after the sweep blocks 26 of the 268 TUs that have
anything to share, which is the real rate.

**But 46 TUs were refused on every pass and never attempted once**, and they are not a random
46. The 523 TUs that ran have a median of 3 files and a maximum of 73. The 46 have a median of
8, a mean of 31 and a maximum of 318, and every one of the ten largest candidates is among
them: `ScriptActions.cpp` (318 files), `Object.cpp` (223), `Player.cpp` (159),
`InGameUI.cpp` (121), `Scripts.cpp` (70), `Drawable.cpp` (60), `ScriptEngine.cpp` and
`Team.cpp` (50), `Locomotor.cpp` (38), `OpenContain.cpp` (36). Between them they hold 272 of
the 640 shareable classes still on offer, including all 44 of `Object.cpp`'s.

The cause was in `tu_views` itself, not in the fleet. `--class` narrowed which classes were
written but nothing else: the claim, the CodeView layout read and the unmatched audit all ran
over the TU's whole file list. Across those 268 TUs the full lists name 2661 distinct files
while the classes being written live in 1008, so 1653 files - 62% - were claimed and compiled
for runs that could not touch them. `Object.cpp` is the extreme: 223 files to write a view of
`Energy`, which lives in 2.

A large footprint does not need any particular file to be held. It needs *some* file to be
held each time it is tried, and with a few hundred file claims live across the fleet that is
close to certain for a 223-file list and close to impossible for a 2-file one. That is why the
sweep harvested the small TUs and could never reach the large ones, however many passes it
made.

**Fixed in `b415326627`.** A `--class` run now works on the union of the selected classes' own
files and reports it as `files`, so a caller claims that set and nothing more; `touched` says
the same whether or not `--class` was given. Without `--class` the whole TU is still the unit,
and a test holds that. `--class Energy` on `Object.cpp` now plans in 4 seconds.

**What this does and does not buy.** It makes the remaining 272 classes reachable, which eight
passes of the TU driver could not do. It does not change any verdict: a class that conflicts
still conflicts, and the lane still moves 0 merge donors (see "Sharing views does not move the
merge"). The unit being wrong capped how much of the lane could be *attempted*, not how much of
it was real.

A cached plan row from a TU that did run is spent, and this was worth checking rather than
assuming. `tu_views` can refuse a class because an earlier sibling's renames changed a block it
already wrote ("its renames would change the shared view of ..."), which cannot happen to a
class run on its own, so re-running the spent TUs class by class might have recovered some. It
would not: across the sweep's 222 apply reports, 372 conflicts and 198 reverts, **not one**
carries that reason. The interference is real in the code and absent from the data.

So the reachable work is the 272 classes in the 46 TUs the sweep never ran, and nothing else.
The 365 plan rows cached against TUs that did run are already settled - applied, reverted or
refused on their own merits - and re-reading them buys only the two cheap screens' worth of
confirmation.
