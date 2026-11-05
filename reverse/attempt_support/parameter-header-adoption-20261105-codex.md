# Parameter header adoption, 2026-11-05

Inspected revision: `0011654fe5`. Adopted the existing
`Code/GameEngine/Include/GameLogic/ScriptParameter.h` without changing it.

| Source under `Code/GameEngine/Source/GameLogic/ScriptEngine/` | Change |
| --- | --- |
| `ScriptActionParseAction.cpp` | Replace the private Parameter and unused empty setter base; initialize the canonical cached-player-mask and object-ID fields. |
| `ParameterReadParameter.cpp` | Replace the private Parameter; use the canonical signed BitFlags template parameter and read the parameter type directly to preserve the original emitted providers. |
| `ScriptActions_livingWorldRegion.cpp` | Replace the private Parameter with the existing header. |
| `ScriptEngine_setFlag.cpp` | Replace the partial Parameter; read the canonical integer field. |
| `ScriptEngineGetUnitNamed.cpp` | Replace the private Parameter; read the canonical object-ID field with the existing ObjectID cast. |

Verification:

- `./build.sh` over all five sources: **30/30 matched**, string/float/import checks pass. Post-edit declared-unmatched checks pass.
- `header_adopt_lane.py accept --class Parameter` over the five-source cohort: **five PASS**, retires **five rows** through the owning tool. The other nine Parameter queue rows remain.
- `class_cleanup.runtime_graph` / `same_runtime`: all non-debug sections, relocations, external definitions, weak bindings and COMDAT policies are identical for four units, allowing section renumbering.
- `ScriptEngineGetUnitNamed.cpp` differs only by removal of the unused four-byte `Parameter::getObjectID` COMDAT. Dropping that section from the saved original graph makes its runtime graph identical too. No aliases were removed. A literal symbol scan of **39,120 objects under build/** finds `?getObjectID@Parameter@@QBE?AW4ObjectID@@XZ` only in the saved original object; no current object references it.
- Downloaded the published index/object store with `link_check.py --fetch-index`. The retained index is **2026-11-05 15:19, f44cbcf5b0**. Ordinary five-source preview: **5/5 LINKS**, **23,753 -> 23,753 authored bytes**. This is a preview, not a census or real-link measurement.

No source paths, ledger rows, pins, shared headers or hatch counts changed.
