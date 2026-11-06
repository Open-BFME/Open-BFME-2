> Recovery publication: historical investigation from 526cdde3c120. Recovered against `8bb483ac9115`; original commands and results below were not rerun during recovery. All original fleet claims were released. These are prerequisites/attempt evidence, not a completed repair or runtime result.

# StateMachine header cohort, fleet chat 03 seat 2

Owner: `codex-fleet-20261106-c03-seat2`; base `f15737ff46b`.

Selection: `next_work.py --claim --shard 7/30` served Cylinder writer
0x0055D815, already landed by 630837598a2. Current source and ledger
provide its virtual writeINI export; both temporary claims were released.
The ranked JSON shard view then served StateMachine header adoption first.

## Supported boundary

`find_declared_unmatched.py Code/GameEngine/Source/Common/AIHarvestPrepareSiteState.cpp`
reported all definitions matched. A scheduler-wrapped supported preview:

```
python3 tools/header_adopt_lane.py adopt --class StateMachine --header Code/GameEngine/Include/Common/StateMachineClass.h Code/GameEngine/Source/Common/AIHarvestPrepareSiteState.cpp
```

refused with `field renames: m_machine occurs in a comma declaration or expression`
and exit 1. No source was modified. This is a supported adoption boundary,
not demonstrated to be a gate defect. No manual rewrite bypass was attempted.

Target facts: the private StateMachine view reads owner at +0x14 and the
coordinate at +0x24, agreeing with the shared header offsets. This alone
does not prove adoption or runtime success.

## Second coherent unit

`find_declared_unmatched.py Code/GameEngine/Source/GameLogic/AI/AIDockStateOnExit.cpp`
reported all definitions matched. The scheduler-wrapped command:

```
python3 tools/header_adopt_lane.py adopt --class StateMachine --header Code/GameEngine/Include/Common/StateMachineClass.h --apply Code/GameEngine/Source/GameLogic/AI/AIDockStateOnExit.cpp
```

refused with `StateMachine::m_machineFields04 (+0x4, 16 bytes) has no canonical field of that offset and size`
and exit 1. The canonical layout splits that opaque private range into
current-state +4 and tree storage +8. No source mutation was retained.
No manual replacement of the private view or shared header edit was attempted.

Two further hypotheses remain untested: the canonical owner getter is const
(the private getter is nonconst), which can affect emitted COMDAT symbols;
and moving the canonical include before the current first Snapshot include
can affect State/AIDockMachine slot selection. Offset agreement is not a
byte or link verdict. Compiler, byte, strict-receipt, affected-consumer and
runtime verification were not reached for either refused candidate.

Both attempts used the shared scheduler, BUILD_POOL=1 and the configured
shared compiler VM paths/prefix. No game/image or runtime improvement was
measured. No debt rows, source rows, names, paths or hatches changed.

Next work must respect the supported header lane boundary and first establish
a permitted structural mapping; neither refusal demonstrates a verifier defect.
The current source remains the verified prior reconstruction.
