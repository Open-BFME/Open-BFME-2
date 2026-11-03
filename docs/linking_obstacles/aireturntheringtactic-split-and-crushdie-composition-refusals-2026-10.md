### AIReturnTheRingTactic split and CrushDie composition refusals (2026-10-30, dd-30)

Two consolidation refusals on current master, both at the link/composition
boundary rather than in the bytes.

`tu_skeleton.py --split Code/GameEngine/Source/Common/Rva005AB309Tactic.cpp --for
Code/GameEngine/Source/Common/AIReturnTheRingTactic.cpp` carves 8 of the file's
10 rows and all 10 carved rows match alone beside the TU under its flags, but
SplitLinkGuard refuses the pair: the residual, link-clean today, would stop
linking, because the carved side takes the AsciiString global
`?AIReturnTheRingTactic_IsRunning@@3VAsciiString@@A` (data_moved g_009BC1B8) with
it, and the moved selected COMDAT `?buildReturnTeam@AIReturnTheRingTactic@@QAE_NXZ`
lacks matching private/weak-free context. Prerequisite: give that global one
owner that survives on the residual side (or move the rows and the datum as one
unit) and record the selected-copy evidence for `buildReturnTeam`; then re-run
the split dry run. Nothing was written.

`tu_skeleton.py --merge Code/GameEngine/Source/GameLogic/Object/Die/CrushDie.cpp`
accepts its one donor and byte-verifies 8/8 rows, but the commit hook refuses the
merged TU: it declares its own `Thing` and `tools/class_gate.py` requires the
shared `Code/GameEngine/Source/Common/Thing/thing.h` view. Prerequisite: reconcile
the donor's `Thing` view to the shared header in its own verified commit first
(as for any canonical-class view), then merge. The merge was reverted; nothing
was committed.
