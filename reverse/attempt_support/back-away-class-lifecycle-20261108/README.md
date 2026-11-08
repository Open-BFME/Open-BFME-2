# AIBackAwayAndCowerState identity and lifecycle slots

Native table VA 0x00C10EE0, installed by constructor 0x0033F33D and
destructor 0x003401E4, has slot-2 getter 0x0033F35E. That complete
six-byte getter returns the literal AIBackAwayAndCowerState at VA
0x00C10F24. The same table's slots 4/5/6 already have the readable
onEnter/onExit/update rows at 0x00347C38/0x0034025E/0x0034022F.
This is target identity evidence, independent of a donor or masked match.

The four constructor/destructor/deleting-destructor/xfer rows and their
constructor caller now use that existing readable class name. Each old
(name, RVA) has a deleted_rows.csv tombstone and a tools/re_log.py entry.
The automatic class-fold planner cannot express the literal-getter tie
and refuses inherited ICF slots, including the shared Region2D RET.
This follows docs/naming.md's canonical hand-rename route and LINK-618's
eight-state precedent. name_basis.csv is untouched: no evidence-tier
approval is claimed, and the tool's normal naming and commit gates remain.
No data-ledger cache names are edited by hand.

Both lifecycle table views declare the existing onEnter/onExit/update
overrides. Together with the prior xfer declaration, slots 3/4/5/6 now
reference their native bodies. Both tables remain identical at 68 bytes.
The owned +0x20 sub-machine uses the canonical StateMachine pointer in
constructor, destructor and xfer views; the destructor uses ordinary
global-scope C++ deletion. Its former one-slot member proxy disappears.
The native onEnter constructs that sub-machine and update/onExit use its
StateMachine surface. Pointer naming and measured offsets are retained.

Public build.sh passes 85/85 rows across four changed sources, including
the AIStateMachine caller and its 77 funclets. Strict preparation passes
161 rows/three data rows across seven sources, plus 10 rows in the
replacement inherited-default provider. All five EH graphs are exact.
Frozen-source and paired new-variant checks pass. Retained executable
COMDAT bodies, relocation positions, flags and policies are identical
after the class-name normalization. Other data and external bindings
agree, except for the three intended lifecycle table referents and the
removed State::onExit reference. Each removed State::onEnter copy has an
identical, strictly current provider in Rva0049B47CDerived.cpp.
Eight-source preview conserves LINKS/6,021 bytes at index c885072a48
(2026-11-08 19:18).

The slot-2 placeholder getter remains separate and the emitted tables
still need a bridge. Shared-class consolidation, the stale Wind header
queue identity, the earlier broader-audit consumer receipt and next-image
confirmation remain open. This changes no pin, alias, flag, header or
source path and claims no full-table, image or runtime clearance.

Published as bd717ca94a on the first attempt (56.0 seconds: 14.6 rebase,
41.4 hook/push). The commit's name-dependent closure passes 666 rows and
31 data rows across 25 sources, with 70 exact EH graphs. Post-rebase push
verification passes 516 rows/eight data rows across 14 sources, 19 exact
EH graphs, literals/imports and scoped DIR32. The broader audit remains
INCONCLUSIVE: ten source objects lack current receipts, first
Common/ConstIntGetters4.cpp, against index c885072a48 and outgoing base
8e5e79fd2f9bf69aa6f56a5bc985fbacaacb6af0. Carry that larger consumer closure
into the next census/image; no full-link or runtime clearance is claimed.
