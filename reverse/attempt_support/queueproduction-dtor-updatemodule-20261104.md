# QueueProductionExitUpdate destructor: canonical UpdateModule

Inspected revision: `cd25723e65` (2026-11-04, codex3).
Source: `Code/GameEngine/Source/GameLogic/Object/Update/QueueProductionExitUpdateDtor.cpp`.

Target facts: the getter already has the matched owner
`?getDisabledTypesToProcess@UpdateModule@@UBE?AV?$BitFlags@$0L@@@XZ`
at RVA `0x00253376`, in `UpdateModuleSetWakeFrame.cpp`.
The canonical `UpdateModule.h` documents the native four-byte disability mask,
three-slot update interface, and layout through offset `0x1C`.
The destructor's private declaration instead used `BitFlags<13>`, requesting
the absent `$0N` getter. This is an existing declaration mismatch, not a
missing body.

Change: replace the private UpdateModule/UpdateModuleInterface declarations,
empty BitFlags template and unused BehaviorModuleOther with the canonical
UpdateModule header. No shared header, function row, pin or alias changes.
The automatic adoption trial was restored after rejecting the conflicting
local DisabledMaskType typedef (C2371); removing that obsolete typedef with
the private classes makes the direct adoption compile.

Verification:

- Before: `./build.sh` passes both destructor rows; ordinary `link_check.py`
  rejects the unit on the `$0N` getter (0 of its 60 authored bytes).
- After: `./build.sh` passes both rows, including the 32-byte destructor and
  28-byte deleting destructor. `find_declared_unmatched.py` reports all
  defined functions matched.
- `header_adopt_lane.py accept --class UpdateModule` and the corresponding
  `UpdateModuleInterface` acceptance each pass and retire their one queue row.
- `link_check.py --prepare-current` passes all three rows across destructor
  and constructor, producing strict reusable receipts.
- The paired ordinary preview predicts LINKS for the destructor (60 bytes)
  and constructor (106 bytes) against the published 2026-11-04 02:25 index
  at `5a13f2cd61`. This clears the missing-getter prerequisite for this unit;
  it does not claim a new census or real-link result.

Local raw logs: `build/queueexit-dtor-20261104/`. Broader QueueProductionExit
TU composition and the other LINK-004 ABI mismatches remain open.
