# AnimationSoundClientBehavior consolidation, 2026-10-28

Seat: yasinschroeder-codexb4. Inspected base: `17e504a240`.
Destination: `Code/GameEngine/Source/GameClient/Drawable/Update/AnimationSoundClientBehavior.cpp`.

## Routing and prerequisite

The default picker claimed the destination and ten clean donors. The scoped
`name_lane.py consolidate` packet was reviewed, including original paths,
alternatives and declaration, layout, include and compiler-setting blockers.
The packet's Behavior path is a donor lead, not approval to move the current
Update destination. The committed TU map is stale; the supported
`tu_skeleton.py` plan rebuilds assignments in memory and approves 49 rows for
the Update TU. Seven mixed files remain outside this merge.

All eleven original files pass `./build.sh`: 36/36 function rows, two data
rows, eleven string references plus one empty-string reference, one floating
literal and one import. All pass the frozen-file check. Original objects are
saved under `build/animation-sound-before` for subsequent comparisons.

The first supported merge dry run accepts no donor. Its diagnostics include
missing manager and client declarations, incompatible tree/entry views, a
duplicate STL node definition and a missing module-data parser declaration.
`tu_views.py --dry-run` independently reports the conflicting base, layout
and virtual-interface views. These fragments require separate reconciliation;
their successful standalone byte checks do not prove they compile together.

The smallest prerequisite adds the existing nonvirtual
`AnimationSoundModuleManager::rva00432E5D(Rva00432F23Node*)` declaration to the
destination's private view. Its signature comes from the matched manager
provider at 0x00432E5D and the existing assignment caller, not a donor-name
inference. No implementation or binding changes.

Before the edit, strict receipt preparation succeeds for the destination and
`Common/U4GlobalGuardedNotifies_Rva004ca223.cpp`: 18/18 rows. An earlier receipt
attempt overlapped the merge trial's temporary Code files and was invalidated
by the changing source inventory; the successful repeat follows trial cleanup.

After the declaration, the destination passes 17/17 rows, ten strings plus
one empty-string reference, its named import and both EXACT EH graphs. Its
43 external definitions, 43 external COMDAT byte-and-symbolic-relocation
fingerprints, 42 unresolved external names and both weak aliases equal the
original object. The frozen-file check passes. The ordinary two-input preview
preserves LINKS for 1,882 destination bytes and 51 assignment bytes, 1,933
authored bytes total, against index `d92e7e6635` (2026-10-28 15:58).

Next: retry the supported merge after committing this prerequisite. Preserve
the remaining fragments until their private views reconcile. No census,
smoke or ownership measurement is run, and no new linked bytes are claimed.
