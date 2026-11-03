### LINK-167: RebuildHoleExposeDie.cpp canonical adoption blocked on the building-destructor scaffold holding its primary vtable name (2026-10-31, seat nleigh-codex)

The RC row's straight canonical swap (include GameLogic/Module/DieModule.h,
delete the TU-local fake DieModule/BehaviorModuleInterface/DieModuleInterface)
keeps all 9 rows byte-matched (layout stays 0x14: three vfptr stores at
+0/+0x0C/+0x10 via pinned constants, no row changes) but MSVC then names the
1-slot die-interface table [onDie] under the primary name
`??_7RebuildHoleExposeDie@@6B@` with digest adf9e406890f, refusing
against the census's sole first-copy holder DieModuleDeletingDtors.obj
(f35a4af100fd, the 2-slot EmitVtableTag scaffold artifact — not retail's
48B/12-slot primary at 0x00C4AE54). The same byte-set was census-safe as
`@@6BDieModuleInterface@@@` in the fake shape (RC.obj-sole, self-refresh
exempt). Renaming away from the primary in DFCOD's style needs an own
polymorphic secondary base: an empty non-virtual dummy does not rename, and
`__declspec(novtable)` did not suppress the derived-side store (`cl` still
emits a 4th vfptr store at +0x14, breaking the 42B row ctor 0x00486768).
DFCOD's landed rename worked because its TU defines no ctor row. Per-unit
link_check behavior confirmed again: only that single name is refused; all
other canonical emissions are either byte-identical to census copies (inline
BehaviorModule bodies, 188B 7e0850252d95) or RC.obj-sole. Working state
reverted to the fake-shape baseline (9/9, LINKS 670->670). Evidence and open
paths: reverse/attempt_support/rebuild_hole_expose_die_canonical_shape.md.
The open path is restructuring the RebuildHoleExposeDie branch of
DieModuleDeletingDtors.cpp (rows ??_GRebuildHoleExposeDie @0x004867DD and its
??1 0x004867F9 audited wrappers) so its class-copy stops emitting the primary
name; that tu is deleting-dtor family-wide, so it waits for the merge lane's
consolidation pass. The DamageFilteredCreateObjectDieCtor header row stays
census-gated on the next nightly index absorbing the landed DFCOD dtor
digests (name-held-solely-by-another-object refusals, resolved by refresh).
