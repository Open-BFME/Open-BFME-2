> Recovery publication: historical investigation from 490e712d03c2. Recovered against `8bb483ac9115`; original commands and results below were not rerun during recovery. All original fleet claims were released. These are prerequisites/attempt evidence, not a completed repair or runtime result.

# LivingWorldLogic header adoption: original-layout preflight blocked

2026-11-06, chat 07 seat 1, source revision `f15737ff46b`.

The shard 18/30 default picker claimed `class:LivingWorldLogic` and served
eleven header-adoption units. Inspected existing coverage and LINK-156; the
selected coherent subset was `Code/GameEngine/Source/GameNetwork/GameSpy/StagingRoomGameInfo.cpp`.
Its private view models only an integer at +0xEC; the canonical header declares
`fieldEC`. This is a potential adoption, not a verified source change.
`find_declared_unmatched.py` reports all defined functions already matched.

Original invocation (with prescribed PATH, Wine prefix, owner, namespace and
BUILD_POOL=1):

```
python3 /Users/mehmet/Projects/Open-BFME-2/build/fleet/20261106-pass3/verification_slot.py python3 tools/header_adopt_lane.py adopt --class LivingWorldLogic --header Code/GameEngine/Include/GameLogic/LivingWorldLogic.h --apply Code/GameEngine/Source/GameNetwork/GameSpy/StagingRoomGameInfo.cpp
```

After waiting for slot 2/2, the invocation reached the original unit's layout
preflight: `prepare_unit -> field_renames -> compile_text(source, None) ->
class_layouts.compile_layouts`. No candidate or ledger changes had been applied;
the byte gate and acceptance were never reached. The layout subprocess at
`tools/class_layouts.py:369` has no timeout. `build._run_compile` documents a
bounded compiler failure path, but this layout reader does not use it.

The preserved stdout ends with fatal C1083 at source line 55: missing
`windows.h`. Stderr contains only D4025 overriding /O2 with /O1. These logs
remained 19,251 and 63 bytes, respectively, while the original guest cl.exe
PID 9113 consumed CPU without further output. At the final preserved snapshot,
elapsed time was 1:14:04, CPU time 1:13:16, CPU 98.9%, state R, RSS 18,120 KiB.
No output object existed. This is post-diagnostic compiler spinning, not useful
compile progress or a false gate refusal. The owning header queue already
records C1083 for this unit.

After preserving the exact logs and process identity, sent SIGTERM only to
guest PID 9113, checking its cmdline still named this worker and source. The
original wrapper and owning adoption tool returned normally with exit 1:

```
FAIL Code/GameEngine/Source/GameNetwork/GameSpy/StagingRoomGameInfo.cpp: field renames: the unit's layout: Code/GameEngine/Source/GameNetwork/GameSpy/StagingRoomGameInfo.cpp: compile failed: C1083
```

No scheduler, parent, other compiler, Wine server or VM was stopped. No full
gate was interrupted. No source, header, ledger, queue or gate was altered.
No byte, strict link, consumer-audit, real-image or runtime result is claimed.

Next step: resolve the original unit's supported Windows SDK include setup
and the layout-preflight compiler timeout boundary, independently of source
adoption. Do not repeat the unchanged preflight. After a baseline layout
compile succeeds, retry supported adoption and acceptance, then verify current
provider/consumer receipts. Logs here establish local compiler diagnostics;
they establish no retail layout or original source names.
