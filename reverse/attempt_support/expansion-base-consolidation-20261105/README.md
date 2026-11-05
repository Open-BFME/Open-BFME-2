# Expansion-base declaration reconciliation

Inspected revision: `112a456a2c40d5c7731b1355d11e901090afd702`.
Initial provider-index snapshot: `2026-11-05 05:17`, `c95fcfcfcd`.
The refreshed local index reports underlying census `2026-11-05 03:49`,
`c2a9f8e0d7`; the local refresh is not a new census.

## Evidence and changes

The existing constructor at RVA 0x005730FF declares an eight-byte
`Rva005CB22A` base (vfptr and held pointer), followed by a counter at +0x08.
The method unit instead declared a four-byte base and placed the held pointer
in the derived view. Both views put the counter at +0x08. Reconciliation moves
the method view's pointer declaration into its base, without moving storage,
and gives the constructor the method view's unsigned counter spelling and
existing method declarations.

The rowed `findBestTarget` is virtual (RVA 0x0057327E). Adding that declaration
to the constructor initially exposed a shorter, one-slot vtable emitted by
`Rva005CB23CDerived.cpp`, the first copy in link order. Its expansion-base view
now also declares that existing virtual method. No function identity, body,
pin, alias, data definition, header adoption or protected-register key changes.
The destructor file remains mixed and is not a merge donor.

This is reconciliation of existing target declarations, not new evidence of
the original base-class name. The supported planner records the retail path
under `GameLogic/SkirmishAI/.../AITargetHeuristics/`, while the current approved
TU map groups the rows under `Code/GameEngine/Source/Common/` provisionally.
The consolidation follows the current approved map; its path is not claimed
as the original BFME translation-unit path.

## Verification

- `find_declared_unmatched.py`: clean in all three files, before and after.
- `./build.sh` on constructor and method unit: 12/12 rows exact, including
  compiler-emitted handlers and funclets (renumbered labels resolved from EH).
- `./build.sh Rva005CB23CDerived.cpp`: 12/12 rows exact.
- Combined `link_check.py` on all three files: 3/3 link cleanly; 1,197 -> 1,197
  census bytes (234 destructor-file bytes, 24 constructor bytes, 939 method-unit
  bytes). No headline census or runtime result is claimed.
- Initial merge dry-run: method declarations missing from the seed.
- Reconciled merge dry-run against the original index: the guard still sees
  the old, shorter outside destructor-file table. Refresh the local index with
  `link_check.py --update-index` before checking the merge again.

The method unit's Player, Rva002A8F24, TerrainLogic and Waypoint header queue
items remain adoption work; no debt is retired by this prerequisite repair.

## Composer false reject after local index refresh

The local `link_check.py --update-index` completed, rereading 5,601 objects
and dropping 83 stale entries. The next merge dry-run reaches compilation
but fails at `Rva00261409Filter(Player *player, ...)` (composed line 11).
The seed's `class Player;` enters the late declaration stream; the identical
donor forward declaration, which precedes its last include, is discarded as
already seen. Consequently the earlier include/declaration stream uses
`Player` before either declaration or definition. All four composition
strategies reproduce the missing forward declaration. The original files
remain unchanged and verified; this is a composer failure, not a new source
layout hypothesis. Recorded with `re_log.py` as a `false-reject`.

Next step: preserve forward declarations independently in the two output
streams, with a regression fixture and existing verifier exploit tests;
then retry the approved merge. No merge or source-file reduction yet.
