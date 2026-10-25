# Consolidation: one retail translation unit, one source file

The ledger mostly holds one function per file (about 23,000 units under `Code/`).
Retail was linked from real translation units, and a TU's functions sit next to
each other in `.text` in object order. This lane merges the small files back into
the TU retail built them from, one TU at a time, without losing a matched row.

Four tools support the workflow; a seat does the judgement.

Start a consolidation or subsystem naming pass with the read-only
[evidence catalogue and naming planner](#evidence-catalogue-and-naming-packets).
Its investigation packets support work selection and prerequisite repairs;
merges continue through `tools/tu_skeleton.py` and the normal verification gates.

| Tool | Role |
|---|---|
| `tools/name_lane.py consolidate` | The evidence planner: catalogues original paths and donor structure, identifies candidate groups and flags routing, declaration, include and compiler prerequisites. |
| `tools/tu_map.py` | Which TU each retail function came from: `__FILE__` strings, Zero Hour definitions and class sites, naming inside an anchored address cluster, contiguity. `approved` rows are the only ones a merge moves. |
| `tools/tu_skeleton.py` | The lane: `--queue`, `--plan`, `--merge`. It verifies every merge by compiling and byte-matching, claims its scope, and repoints the ledger. |
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
   another TU), `refused` (deleting the file is not mechanical: vendored, keyed in
   a protected register, `#include`d by another file, or expanding `__FILE__`), or
   a placeholder comment (unmatched; it compiles to nothing and is never credited).
3. **Dry run.** `--merge TU --dry-run` composes and verifies without writing.
   `accepted` donors merge as they are. Each `rejected` donor carries the compile
   error or `bytes` (a row the merged text no longer matches).
4. **Reconcile the rejected donors, one ordinary commit each.** The usual cause is
   a private view of a class or struct that differs from the seed's: a local
   `Coord3D`, an enum declared twice, a member declared `private` in one view and
   reached from another. Make the donor compile against the seed's headers, or
   move both to the canonical header (`tools/class_views.py --class X`,
   `tools/header_adopt_lane.py`). Verify the donor with `./build.sh` and commit it
   before merging. Duplicate *identical* declarations and donor-local copies of a
   type that the seed or an included header defines are removed by the merge
   itself, and the byte check decides whether that was safe.
5. **Merge.** `BFME_CLAIM_OWNER=<seat> python3 tools/tu_skeleton.py --merge TU`
   claims `file:` for the TU and every donor, plus each moved row's RVA. It writes
   nothing when another worker holds one of them. Then it writes the TU, deletes
   the absorbed donors, repoints `functions.csv`, `data_rows.csv`, `tu_map.csv`
   and `body_owners.csv` `source` columns and the `docs/doxygen/sources.cfg`
   inputs, and stages the result. It prints the paths it staged and a commit
   subject.
6. **Verify and commit.** `./build.sh TU`, then
   `python3 tools/find_declared_unmatched.py TU`, then commit with the printed
   subject. The hook byte-verifies the TU again. Follow AGENTS.md's Publication
   rules: a merge recovers no new bytes, so batch merges and push them together. Perform
   the tooling compatibility audit below once over the full outgoing batch
   immediately before pushing.
7. **Name while you are there.** The rows of the TU are a natural naming group:
   rename placeholder rows with `tools/rename.py` (`docs/naming.md`) in separate
   commits. A merged TU path is an approved retail TU, so `rename_files.py` never
   renames it.
8. **Release** the `file:` claims after the push
   (`python3 tools/claims.py release file:<path> ...`) and let
   `python3 tools/claims.py release --landed` settle the RVAs.

## Carving a mixed file (the split lane)

A mixed file holds matched rows of several TUs, and often rows with no approved
TU yet. A merge never splits one. `tools/tu_skeleton.py --split` carves the rows
approved for ONE TU out of it, straight into that TU path, and leaves every other
row where it was:

    python3 tools/tu_skeleton.py --split FILE                 # which TUs the file's rows belong to
    python3 tools/tu_skeleton.py --split FILE --for TU --dry-run
    BFME_CLAIM_OWNER=<seat> python3 tools/tu_skeleton.py --split FILE --for TU

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
   declaration and comment. Definitions are never duplicated: a file-local
   helper function with internal linkage that is not a ledger row travels as a
   copy when a carved body calls it (transitively); one with external linkage
   never does. A file-scope object definition goes where it is used: with the
   carved bodies when only they use it (its data row is repointed), else it
   stays; an external one used on both sides stays and the donor declares it
   `extern`; an internal one used on both sides refuses the carve, as does a
   `namespace {}` / `extern "C" {}` block that defines anything. Quoted includes
   that resolve beside the mixed file are rewritten to resolve beside the TU
   (the compiler searches the including file's directory first).
3. Verifies the residual under its own path and the flags the build will give its
   remaining rows (the region vote can change when rows leave). Any lost row
   blocks the split.
4. Verifies every carved row alone beside the TU under the TU's flags. A row that
   matches only under the mixed file's own flags stays behind (`flag_bound`).
5. Runs the carved bodies through the merge verifier as a donor: into the existing
   TU file as seed, or as a new TU file. The usual merge repairs apply
   (duplicate declarations dropped once, redefinitions repaired); a donor the
   seed's headers cannot host is rejected with the compiler's reason, exactly as
   in `--merge`, and the seat reconciles the seed or the donor first.
6. Claims `file:TU`, `file:FILE` and every moved RVA; writes the TU and the
   residual; repoints only the moved rows in `functions.csv`, `tu_map.csv` and
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

## What the lane does not do yet

- **Mixed files** (a file holding rows of two TUs) are never split inside a
  merge: about as many donor files are mixed as clean. A split is its own
  verified change, `--split FILE --for TU` above, one TU at a time; rows the map
  has not placed stay in the file until it places them.
- **TU paths that hold another TU's rows** are skipped by the queue for the same
  reason (`blocked: ... split it first`).
- **Linking.** `tools/link_check.py` cannot preview a new path before a census
  has seen it; an existing TU path is previewable. A merge that changes which
  COMDAT copy a link keeps shows up in the next census.

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
