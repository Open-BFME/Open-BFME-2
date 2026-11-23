### LINK-604: MilesAudioManager header adoption in three audio consumers
Status: Cleared for the three consumers below by byte and link-preview checks, 2026-11-05; inspected revision `d7dd0eadbe`.
Scope / completed: `MilesAudioManagerScaledValue.cpp`, `MilesAudioManager_getGlobalReverbMultiplier.cpp` and `MilesAudioManager_isPlayingLowerPriority.cpp` now use the canonical manager header; its opaque fields retain local typed access views. The owning acceptance tool retired all three queue rows together.
Evidence: [source changes, object-provider audit and verification](../../reverse/attempt_support/link_604_miles_audio_manager_header_adoptions.md).
Remaining / next check: other MilesAudioManager queue rows retain their existing prerequisites; no shared header or member provider was changed. Census confirmation and real-image validation are not claimed.


2026-11-13 (merge-climb, source consolidation at `1b7a6e99402b`):
The official TU merge absorbs 3 approved satellites into
`Code/GameEngineDevice/Source/MilesAudioDevice/MilesAudioManager.cpp`. `./build.sh` verifies
415/415 matched rows with zero row identities lost; CSV and frozen-source
checks pass. Fresh index SHA-256 `0d99f769fe7bb4a4c08d24769264a6f025abce03d648a0496abfe3915e757e70`
(meta `ec61e5dbe7`, underlying census `cbed44f606`)
admits the applied composition through LinkGuard and ProviderGuard. The
header queue's current source/acceptance commands follow the absorbed donor.
This is a partial source merge; it does not retire further header-adoption debt
or establish census, real-link, or runtime closure for the manager. The
three-consumer clearance and other remaining prerequisites above are retained.


2026-11-13 landing follow-up: source merge `ba4944ecca395cb95659ab0764ca58290c4b518d`
and log-only record `bc02ffea95e476c3235551c5af8540dccb257b5f` landed together.
Post-landing checks retain 415/415 rows and the approved object unchanged. The
manager's own scoped preview is LINKS. The broader pre-push link audit is
INCONCLUSIVE: index `ec61e5dbe7` predates outgoing base `2decb620eba`, and
19 affected source objects lack current receipts (first: Common/BuildingNuggetParse.cpp).
Carry that wider consumer/provider scope into the next scheduled census;
the scoped checks do not establish a full-image link or runtime result.

2026-11-23 (MilesAudioManager consolidation)
The canonical AudioFileCache declaration retired one header-queue entry at
2f583e2b903. The 421 function rows, one data row and 80 EH records verified.
Comparing the exact parent and candidate receipts preserved all 1,589 external
definition payloads and relocations after normalizing compiler-local labels.

The official TU tool moved the 41-byte deque range teardown at 0x00056DEB from
StlSweepW5Rva00056DEB.cpp into its approved MilesAudioManager.cpp. The combined
build verified 422 functions, one data row and 80 EXACT EH rows. The outgoing
AudioFileCache and deque-move batch has one retired path. The source marker
retains its provenance, the census retains its snapshot, and the row and name
provenance moved to the destination. The path audit found no active include,
build or tooling consumer. The merge link guard used an older index. A fresh
whole-image link and runtime measurement are pending.

2026-11-23 (device cleanup move)
The TU tool moved the 26-byte device cleanup at 0x00053D89 into
MilesAudioManager.cpp after matching the receiver declaration to the donor.
The merged body keeps the destructor call at +13 (0x000A897D) and operator
delete at +19 (0x0002FD60). The scoped build verified all 502 function rows
across MilesAudioManager.cpp and OwnedPointerResets.cpp, one data row, and
80 EXACT EH records.

The compatibility audit covers the declaration and move after 24f26796c32.
OwnedPointerResets now refers to the cleanup by RVA. The source marker and
link census retain the retired path for provenance. The fresh in-memory TU
plan supplied the move approval, and the committed map was only repointed.
The merge link guard used the older census index.

2026-11-23 (LatchRestore consolidation)
The official TU tool moved the LatchRestore<bool> constructor and both
destructors from LatchRestoreCtor.cpp into MilesAudioManager.cpp. The native
bodies and the four-byte vtable preserve all payload bytes and relocations.
The destination passed 426 function rows, one data row and 80 EXACT EH
records. Approval came from the fresh in-memory plan.

The outgoing audit after 63fa17fe899 covers the template alignment and move.
The tool repointed the single Doxygen source entry. The source marker and
old census record retain the original path. No live include, build or tooling
consumer references the retired file. The link guard used the older census
index.

2026-11-23 (compiler-owned reset guard)
The reset's exact EH graph places its compiler-emitted rollback at
`0x0075E42F`. The obsolete standalone spelling and duplicate external guard
are retired. The update rollback at `0x0075E4D4` has equivalent placement
evidence and retains its matched data row while the data verifier refuses its
compiler-local symbol. [Guard ownership and verifier evidence](../../reverse/attempt_support/miles-static-guard-ownership-20261123.md)

2026-11-23 (room-type multiplier move)
The approved device TU, `MilesAudioManager.cpp`, now owns the multiplier at
`0x00052F4C`. The original header-adoption entry above records the retired
donor. The destination uses the 26-float table at offset `0xC4` established
by the native settings constructor at `0x00041589`.

The native build verified 432 functions and one data row. The moved function
preserved all 84 bytes and all three relocations, including the Miles import
and both float constants. The path audit found no active source, build, or
tooling consumer of the retired file.

2026-11-23 (priority comparison move)
`MilesAudioManager.cpp` now owns `isPlayingLowerPriority` at `0x0005BDD2`.
The earlier header-adoption entry identifies the retired donor. The
destination reuses its existing playing-audio list types and preserves all
135 bytes, including the four call relocations.
