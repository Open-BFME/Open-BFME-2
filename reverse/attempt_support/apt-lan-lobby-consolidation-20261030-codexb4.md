# AptLanLobby reset helper composition (2026-10-30, codexb4)

Base: `84887c9bc0`. Scope claimed through the default consolidation picker:
AptLanLobby.cpp, the four adjacent whole-file donors and Common/Rva004442FD.cpp.
The supported naming planner was generated under
`build/consolidation/aptlan-codexb4`; original-path hints do not prove a BFME 2
source path. The supported merge rebuilds current TU approvals in memory.

## Declaration repair

The initial merge dry run rejected all five donors at compilation.
Common/Rva004442FD.cpp needs fields absent from the seed's method-only class
view. Copying its complete class declarations into that seed adds no function
body or binding. Neither class is in the canonical-class register.

`./build.sh` verifies all 47 rows across seed and donor; the seed's eight EH
graphs remain exact. The seed object's 116 normalized COMDAT fingerprints,
225 external bindings and one weak binding equal the saved original object.
`find_declared_unmatched.py` is clean. No debt is retired and no census gain
is claimed.

## Remaining donors

- GetValidSelectedGameInfo uses `m_listboxGames` where the seed uses
  `m_customGamesList` at the same offset; reconcile the views before merging.
- MPOwnerValidatGameInfo disagrees with the seed's first virtual slot.
- GameCreate lacks seed declarations including Cancel and has further class
  conflicts (GameEngine, GameTextInterface, LANAPI and callback return type).
- GamesListTooltip needs GameInfo/GameSlot method and layout reconciliation,
  plus a LANAPI ValidateGameInfo declaration.
- Nine mixed files remain separate; this pass does not move their rows.

These are existing composition prerequisites, not lost matched rows. The
initial trial and tu_views plans are in `build/aptlan-dryrun-codexb4.txt` and
`build/aptlan-views-codexb4.txt` respectively. Carry moved-provider selection
and affected consumers into the next scheduled census.

## Intrinsic declaration ordering

The supported merge after the layout repair compiles the pair but matches only
46/47 rows. The sole miss, 0x004442FD, emits an external `__ReadWriteBarrier`
call: composition hoists the intrinsic pragma before its declaration. This is
not a retail codegen or flag mismatch. The original donor remains exact.

The seed now declares the intrinsic before its last include, an ordering that
the existing composition tool preserves. Its own 46 rows remain exact, and a
bounded `tu_skeleton.Verifier` composition of the pair matches all 47 rows.
The full supported merge and link guard still decide whether to apply the move.

## Applied composition

The runner rebased the prerequisite commits onto `7d15ffa2bd`; the supported
merge then absorbed Common/Rva004442FD.cpp into the approved provisional TU.
It removes one source file and repoints one function row and its existing
`tu_map.csv` source cell. The map was rebuilt in memory for approval, not
regenerated into the commit. Other donors and mixed files remain in place.

The final `./build.sh` verifies all 47 rows, with 25 nonempty string references,
two empty references and one named import. `eh_verify.py` reports eight exact
EH graphs. `find_declared_unmatched.py` and `check_csv.py` pass. The final object
preserves the saved original pair's 117 external definitions, 106 unresolved
names, 117 normalized external COMDAT fingerprints and one weak binding.

The supported link guard admits composition of the census-linked pair. A
strict reusable receipt is prepared for the destination, and ordinary preview
reports LINKS for its 3,804 authored bytes against index `85f6b7f40c` from
2026-10-29 15:08. The original pair previewed 3,758 + 46 = 3,804 bytes: the
file-level increase is a move, not a measured linking gain.

## Tooling and register audit

Audited the complete pending path-change batch from `7d15ffa2bd` to the staged
tree, covering both prerequisite commits and this many-to-one merge. Searched
the removed full path and basename across active tools, hooks, workflows,
source includes, root configuration, ledgers, queues and documentation.
Remaining mentions are the generated TU's donor-provenance comment, this
historical attempt record and the last census's `reverse/link_status.csv`.
No active path consumer needs an update. Keep census history unchanged.

Neither source has keys in the code-identity, data-check, hatch or flag-override
registers. The supported merge refreshed header and Microsoft-header reports;
neither queue needed a transfer or change. No debt retirement is claimed.
The naming planner was regenerated after composition without missing inputs.

Final identity checks report zero data findings, zero converged-data second
names across 11 addresses, and zero new code-identity findings across 47 rows
(mode remains shadow). The staged TU-ownership check succeeds.

## Batch audit limitation and census handoff

`link_batch_audit.py` audited base `7d15ffa2bd` against staged source/ledger tree
`6eb4593f10d8c1fd0c421c0737e8acc55a7f28e9`, with the byte-verified destination
listed explicitly. Exit 2 is INCONCLUSIVE: census index `85f6b7f40c` predates
the outgoing base and affected consumer
`Code/GameEngine/Source/Common/0CreateAHeroManager21FE49.cpp` lacks a current
receipt. This is unverified external consumer selection, not a clean batch
audit. Carry that consumer and selection of the moved reset-helper provider
into the next scheduled census. No direct link cycle or smoke run was started.
