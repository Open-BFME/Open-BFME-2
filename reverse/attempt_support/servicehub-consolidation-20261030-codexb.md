# FESL servicehub consolidation

Inspected base: `e37b19e3ab`, 2026-10-30. The supported picker selected
`Code/Libraries/Source/Fesl/servicehub.cpp` and claimed its three whole-file
donors. `tu_skeleton.py --merge` absorbed:

- `Code/GameEngine/Source/GameNetwork/Y2FeslServiceList.cpp`
- `Code/GameEngine/Source/GameNetwork/Rva00657590Finish.cpp`
- `Code/GameEngine/Source/GameNetwork/Rva007EA5E0Forwarder.cpp`

This removes two source files while preserving four matched rows (227 bytes).
Only source columns change in the function ledger and committed TU map; no
whole-map regeneration, new row or recovered name is claimed.

## Placement and remaining scope

The pre-edit `name_lane.py consolidate` surveys covered both the Fesl and
GameNetwork roots. The GameNetwork report classifies these donors as unresolved,
with no alternative destination; it flags pragma context and the protected
flag/hatch registers. That report supplies no merge approval. The supported
merger rebuilds the current TU map in memory and approves all four rows for
the FESL servicehub TU. Retail's assertion string names
`\views\feslbuild_main\jabba\fesl\source\servicehub.cpp`; this is an external
FESL SDK path represented under the repository's Fesl library root, not an EA
game-source path or a claim that a donor source tree is BFME 2's source.

Both dry run and application accept all three donors. The link guard accepts
the three census-linked inputs against index `85f6b7f40c` (2026-10-29 15:08).
Eight other approved rows remain in five mixed files: Disp8LeaFieldGetters,
DispDwordLeaFieldGetters, InlineDtorDeletingDtors2, S3SmallAccessorFamilies and
ServiceHubImpl. They were neither split nor claimed by this merge.

## Verification and ownership

- Before the move, `./build.sh` and strict `link_check.py --prepare-current`
  pass all three donors. After the move, both pass the new TU: four exact
  function rows and four exact string-literal references.
- Declared-unmatched checks pass before and after. `check_csv.py` passes
  99,009 function rows, 9,415 symbol rows and 2,235 data rows.
- `tu_ownership.py --staged` passes. `data_check.py --converged` passes for
  the destination: 11 addresses, zero second names and zero unjudged rows.
- The Microsoft-header auditor reports the destination clean. The merger's
  scoped header-debt transfer and Microsoft-header queue refresh leave both
  queues unchanged; none of the donors has an entry in either queue.
- No donor owns a code-identity or data-check baseline finding. The merger
  transfers the two existing linker aliases without changing their targets or
  total hatch count. The two flag-register records become the destination's
  `/O2` record, preserving the three affected rows. No debt key is retired.
- The merged object's six normalized COMDAT fingerprints (bytes and relocation
  targets), four strong definitions, three external dependencies after removing
  internal definitions, weak records and two linker aliases equal the union of
  the original objects. No COMDAT or dependency is added or removed.

The unchanged fingerprint prefixes are: add `b3ff2db7bc1c`, remove
`7ec209ccb45e`, notify `b1afc6e70d8f`, forwarder `2c510e7b1bd1`, assertion
literal `7c3144eeff7c`, and source-path literal `62fd88163179`. These are bounded
object comparisons; they do not establish a new census result.

## Tooling compatibility audit

The audit covers the complete outgoing source-path batch at base `e37b19e3ab`:
the three paths above become the single servicehub TU. Other already-pending
commits have no source-path moves. The combined search covers old paths,
basenames and the GameNetwork directory in tools, hooks, workflows, game
sources/includes, documentation, ledgers and build/configuration consumers.

Remaining old-basename references are the destination's provenance comments and
the historical census entries in `reverse/link_status.csv`. Active path-keyed
ledgers/registers resolve to the new owner. No source include, fold proof,
doxygen entry, hook or workflow needs an old-path replacement. GameSpy-specific
directory rules in rename/progress, the readability display ordering, and
synthetic GameNetwork tests continue to apply at their existing scopes. No
active tooling change is required. New compiler receipts were prepared at the
destination rather than reusing a donor's path-bound receipt.

Publication rebase onto `6fe1089c24`: repeated the donor-path search and reviewed
the intervening consolidation/map, rename and consumer-tool changes. No active
consumer needs a path update. A fresh `tu_skeleton.py --plan` still approves
these four rows and the eight rows in five mixed files; no map regeneration
is committed. `./build.sh` again verifies all four moved rows and four literals.
Before that rebase, the full gate passed all 99,009 functions, 2,235 data rows,
reference checks and the no-op patch; the tree-wide converged-data check passed.

## Link boundary

Ordinary preview reports that the new TU is absent from index `85f6b7f40c` and
must be measured by the next census; it supplies no LINKS verdict for this path.
The initial staged-tree batch audit is INCONCLUSIVE because the index predates
the outgoing base and three affected sources lack current receipts:
GameSpy/Thread/BuddyThreadClassThreadFunction.cpp, ServiceHubImpl.cpp and
Y2FeslGameBrowserPinger.cpp, all under GameNetwork. Strict preparation now passes
those three sources: 32 function rows, their EH data, one data row, 44 string
literals plus an empty-string reference, and five named imports.

The follow-up staged-tree audit remains INCONCLUSIVE on the older index and a
missing current receipt for affected consumer
`Code/GameEngine/Source/Common/0CreateAHeroManager21FE49.cpp`. This is the wider
consumer boundary, not a demonstrated regression in the four merged rows.
Carry that consumer, the three prepared GameNetwork sources and the new
servicehub provider into the next scheduled census. Full consumer closure and
census confirmation remain unverified; no census gain is claimed.
