# AITacticsGenerator consolidation handoff (2026-11-04)

Preparation commit: `0517891752`. Destination:
`Code/GameEngine/Source/GameLogic/SkirmishAI/AITacticalAI/AITacticsGenerator/AITacticsGenerator.cpp`.
Donors: `Code/GameEngine/Source/Common/Rva00505AF1Prune.cpp` and
`Code/GameEngine/Source/Common/Rva00505D91Find.cpp`.

The original merge dry run rejected the prune iterator types and the finder's
raw `m_08` endpoint. `tu_views.py --dry-run` refused overlapping padding/fields.
Both donors now use the destination's existing eight-vector declaration;
opaque element views stay at the accesses. This does not recover element names.

Verification: `./build.sh` matches both donor bodies (201 and 51 bytes),
`find_declared_unmatched.py` is clean, and the current-object link preview says
LINKS for both, preserving 252 linked bytes against the f12552d0a7 census index.
The next merge dry run accepts the destination and both donors, rejects none,
and reports 60 rows in the composition. No census change is claimed.

Application wrote nothing: its scope claim was refused at `0x0007FAB3`, held by
`yasinschroeder-claudeb`. The file claims were released. Retry the ordinary
`tu_skeleton.py --merge` when that claim is free; never use `--no-claim`.
The destination's AITactic/Player/Team header debt is separate and remains queued.
