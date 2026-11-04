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
after which no row would remain, a TU path holding rows the map places elsewhere
(split that first), and anything another worker holds a claim on.

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
