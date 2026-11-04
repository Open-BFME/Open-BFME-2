# Rva003ED658 consumer header adoption

Inspected revision: `b412381ec549b59783be9edda159811f649fc8e1`.
Date: 2026-11-04. Claim owner: `yasinschroeder-codex3`.

## Applied scope

- `Code/GameEngine/Source/GameLogic/LargeGroupAudio/LargeGroupAudioInit_Rva0020D86C.cpp`
- `Code/GameEngine/Source/GameLogic/Map/FireLogicSystem.cpp`
- `Code/GameEngine/Source/GameLogic/Map/FireLogicSystemCtorDtor.cpp`

All three now include `GameLogic/Rva003ED658.h` instead of declaring a
private class. The audio consumer casts the returned aggregate to its existing
zero-offset merge-call view explicitly; it no longer asserts an inheritance
relationship. The temporary still lives through the merge call.

Target facts: the existing header documents the twelve-byte, three-pointer
layout and the retail copy/destructor call boundaries. No donor names, layouts,
new pins or aliases were introduced. The header and lifetime providers did not
change.

## Verification

`./build.sh` on the three applied sources: 58/58 matched rows; string, float and
import reference checks pass. Compiler-emitted handlers and rowed funclets remain
verified. `find_declared_unmatched.py` on the same sources passes before and after.

`header_adopt_lane.py accept --class Rva003ED658` on all three applied sources:
PASS for each; the tool retired exactly their three `reverse/header_queue.tsv`
rows. The two provider rows remain queued.

`link_check.py` on the same three current objects: 3/3 link cleanly. Compared with
the 2026-11-04 13:15 census at `f6d845ecd4`, the per-unit previews are audio
143 -> 143, FireLogicSystem 2,521 -> 2,760, and FireLogicSystemCtorDtor
355 -> 355 bytes. These are preservation previews, not a new census or an
attribution of the FireLogicSystem difference to this adoption.

## Remaining provider prerequisites

The supported automatic adopter refuses the remaining two sources:

- `Common/BitRange.cpp`: its twelve-byte `m_vec` has no canonical field with
  that offset and size. The copy constructor initializes a real STLport vector
  member before calling `Rva003ED498Count`.
- `Common/RvaTreeDtorFamily.cpp`: its `RvaTreeFamilyHolder m_header` conflicts
  with the canonical raw pointer at +0. The member destructor conditionally
  frees that pointer after `bfmeClearMembers`, and supplies automatic unwind
  cleanup.

Structural inference: a raw-pointer declaration swap alone cannot preserve
these members' construction/destruction behavior. No manual provider rewrite or
claim of a codegen impossibility was made. The next pass should reconstruct the
member lifetime representation, verify both the normal code and EH graph, then
run the adoption acceptance check for those two sources. Do not delete either
remaining queue row without that check.
