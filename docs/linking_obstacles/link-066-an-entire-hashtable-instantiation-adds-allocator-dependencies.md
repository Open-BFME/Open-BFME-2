### LINK-066: an entire hashtable instantiation adds allocator dependencies to one row

Status: Cleared in ordinary-preview scope; census confirmation pending. Updated: 2026-10-26; inspected revision: `896af216804e`.
Evidence / affected unit: `Code/GameEngine/Source/Common/System/XferBlockWriter_rva009D86E0_Rva0060CB97.cpp`, the 21-byte `_M_bkt_num_key(key, count)` row. The whole-class hashtable instantiation emits unrowed operations that reference undefined `__node_alloc<false,0>::_M_allocate` and `_M_deallocate`.
Completed: explicitly instantiate only the existing member from the same STLport primary definition. The matched row is unchanged, and the unit now LINKS. The removed selected copies have no external referrers in the index reference graph; the paired 78-unit preview introduces no blocker. Raw proof: `build/link-worker-20261026-w2/xfer-member-build2.log`, `removed-selected-consumers.log`, `paired-comparison.log` and `all-cohort-after.log`.
Remaining / next check: confirm this unit and the removed-provider scope in the next scheduled census. The build, frozen-file, EH and data checks pass; CSV and pin consistency pass. Full local receipt: `build/link-report.md`.
Clearance: cleared in ordinary-preview scope; census confirmation pending. No census headline change is claimed.

#### Assignment-only R3 hashtables, 2026-10-26

Status: the unrelated equality-dependency scope is cleared in ordinary-preview scope; census confirmation pending. Both whole units remain blocked on native helper identities. Inspected revision: `2a45addda1806342ac5c52757f63be902dcd428e`; index `d1f046749a`, `retail-truth-4`.

Evidence / affected units: `StlSweepR3Rva001DE3E3.cpp` and `StlSweepR3Rva001FDEBC.cpp` each instantiated the entire hashtable for one assignment row. Completed: instantiate only the existing `operator=` from the unchanged STLport `_hashtable.h` definition, retaining its required `clear` and `_M_copy_from` bodies. Remove the unused local unsigned-max definition and its optimization pragmas. No replacement helper, renamed class, body-suppression declaration, ledger edit or new hatch is introduced.

Verification: both assignment rows remain exact and their equality-only unresolved names disappear. The expanded paired preview preserves every previously linking unit and adds no blocker. The complete removed-definition/reference audit finds no retained caller without a provider. Raw proof: `build/c136-r3sweep/before-expanded-cohort.log`, `after-expanded-cohort.log`, `expanded-provider-audit.log` and the `final-*` gate logs mapped by `build/link-report.md`. Declaration, EH, shadow-data, CSV and pin checks pass.

Remaining / next check: both units retain unresolved record copy/destructor names and wrong selected `clear`/`_M_copy_from` copies. Native `clear` is 0x003A2A41 in Rva003A2A41Clear.cpp; the copy workers are 0x001DDCC5 in StlSweepR3Rva001DDCC5.cpp and 0x001FDC0F in PlayerTemplate.cpp, under different record names. All three native providers and Eva.cpp are included in the current-object comparison. Reconcile those key/value identities and the duplicate assignment rows (LINK-060) together. Whole-unit clearance remains pending; the ordinary-preview cleanup changes no census headline.

2026-10-30 follow-up: `StlSweepR3Rva001FDEBC.cpp` is retired as a duplicate
under LINK-060. Its complete assignment remains owned by
`Rva000427195Dtor.cpp`; the current clear owner is now in `Common/RTS/Team.cpp`.
No native element name or layout is recovered by removing the sweep. The
`StlSweepR3Rva001DE3E3.cpp` reconciliation remains open.
