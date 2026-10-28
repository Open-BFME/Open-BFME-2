# ScriptEngine debug-wrapper placement, 2026-10-28

Inspected revision: `57c2e30122`. The default picker selected the proposed
ScriptEngine TU placement of `0x000424FF` (32 bytes), currently owned by
`ScriptEngine_rva0020424FF.cpp`. This is an existing matched placeholder,
not missing coverage or a regression.

## Target facts

The complete row `?rva0020424FF@Rva00203B08@@QAE_NXZ` passes `./build.sh`.
Its C++ returns the short-circuit OR of the existing methods at `0x00203AE5`
and `0x00203B08`. Those sibling bodies test the byte at object offset
`0x1A4D9`, the debug-DLL handle and continuation bytes. These observations
support debug-state semantics; they do not establish original identifiers.

The current `name_lane.py consolidate --under
Code/GameEngine/Source/GameLogic/ScriptEngine/` packet has exactly one proposed
destination and only `stale-tu-map: K=Rva00203B08` evidence for the wrapper.
Its strength is `hint`. The fresh in-memory `tu_skeleton.py --plan` does not
approve this address. The wrapper stays in its current source.

## Donor facts and missing proof

The WB/ZH/BFME1 lanes of `name_evidence.py` produce no naming candidate for
the wrapper or either sibling address in the available evidence caches.
Zero Hour's `ScriptEngine::isTimeFrozenDebug` at
`GeneralsMD/Code/GameEngine/Source/GameLogic/ScriptEngine/ScriptEngine.cpp:8429`
has frame tracking and a `GetProcAddress` call; it is not the wrapper or the
two 35-byte sibling bodies. Its name and donor path are not BFME 2 proof.

No name basis, TU-map regeneration, pin, source edit or row move is justified
for this address. A future pass needs a checked same-body naming witness or
independent target placement evidence. Do not retry the same semantic guess.

Local receipts: `build/scriptengine-name-evidence.{tsv,log}`,
`build/scriptengine-tu-plan.txt` and the current consolidation packet. The
blocked verdict is recorded through `tools/re_log.py`.
