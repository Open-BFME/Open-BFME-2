# EmotionTrackerUpdate consolidation, 2026-10-29

Base: `6825bf755c`. The default claimed picker selected the existing
`Code/GameEngine/Source/GameLogic/Object/Update/EmotionTrackerUpdate.cpp` TU
and ten donor files. The supported consolidation planner was run under
`Code/GameEngine/Source/` to include the Common satellites. Its current
assignment is provisional; donor path agreement is not proof of an original
BFME 2 source path or complete class layout. The merger rebuilds stale TU
assignments in memory rather than regenerating the committed map.

## Declaration prerequisites

The seed lacks declarations for the already matched nugget deactivation and
name-key getter. Declare those methods and use the seed's existing
EmotionNugget view in Rva004B0E9CClear.cpp. The clear helper still accesses the
same opaque entry field at +0x4c through its existing local view; this does not
recover an EmotionEntry layout or rename the helper. No canonical class is
copied and no pin or hatch is added.

Both revised sources pass `./build.sh`: 15/15 rows, including the six seed
funclets whose assembler labels were renumbered. Saved pre-edit objects and
current verified objects have identical COMDAT byte/relocation fingerprints,
strong definitions, undefined externals and weak aliases, compared through
`link_census.object_facts` with identity verdicts excluded. Both sources pass
`find_declared_unmatched.py`. Baseline strict preparation also passed the
separate name-key source's three rows and one string literal. Initial link
previews against index `85f6b7f40c` (2026-10-29 15:08) report all three units
LINKS: 933 + 32 + 79 authored bytes. This is preview evidence, not a census
change. The constructor and broader derived-interface reconciliation remain
outside this bounded declaration change.
