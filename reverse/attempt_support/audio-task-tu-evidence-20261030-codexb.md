# Audio parser and living-world task TU evidence

Inspected base: `e969e5b869`, 2026-10-30. The default picker claimed
`0x0056A83B..0x0056AFCF`, 46 rows in 16 sources. No source, name, row or
TU assignment was changed.

The selected parser is
`Code/GameEngine/Source/GameLogic/LargeGroupAudio/Rva0056A83BParseAudioMap.cpp`.
Its complete 328-byte body consumes `AudioMap`, `Sound` and `Multiplier`
tokens. The existing source and recovery log distinguish that target protocol
from the related BFME 1 parser; neither establishes an original function name.
The other inspected sources are already living-world code: the `0x0056A989`
predicate calls LivingWorldBattle, and the `0x0056AD80` constructor and
`0x0056AEC6` constructor use an opaque registry owner and pending-battle visitor.
The picker's unmapped address run is therefore not evidence for one TU.

Rechecked evidence:

- `tu_evidence.py --source` finds only the proposal R signal for
  `Common/INI/INIAudioEventInfo.cpp`, bracketed at `0x007DA25C..0x007DA268`
  by the same `0x001D9E91` owner. The two EH rows inherit that proposal as
  gated P evidence. It does not approve a destination.
- `name_lane.py consolidate --under Code/GameEngine/Source/GameLogic/LargeGroupAudio/`
  surveys 12 active sources and finds no verified retail path reference in
  the selected rows. Its parser packet has three unresolved rows, no target
  or alternative, and an include-resolution review. The six broader groups
  have static blockers; they do not authorize moving this parser.
- `name_lane.py consolidate --check build/consolidation` passes for that
  report. The committed TU map is stale; a fresh in-memory
  `tu_map.py --dir` check for this exact source still reports three code rows
  with no TU, zero approved TUs.
- The WB leads for the registry destructor, base initializer and SpawnArmy
  probe remain address placeholders/PIN_ONLY. The registry owner's
  `notifyTaskCreated` name is recorded as inferred, not canonical evidence
  for an original translation unit.
- BFME 1 EA evidence names its LargeGroupAudio.cpp and related parser sites;
  these are donor facts. The reviewed BFME 1 `LargeGroupAudioMap::parseSound`
  allocates a SoundKeyPair and parses a sub-block, unlike the selected target's
  stack record and keyword triplet. No same-body target identity is established.
- `./build.sh` on the unchanged parser verifies all 3 rows, five string
  literals, its float literal and named import. The declared-unmatched check
  reports all definitions matched.

Next useful work is an independently checkable original parser or registry-task
identity/path anchor, followed by a current in-memory map rebuild. Do not move
the parser to INIAudioEventInfo.cpp from its proposal-only R signal, or group
the adjacent living-world task implementations under an audio filename.
No TU approval, source-file reduction, debt retirement or linking gain is claimed.
