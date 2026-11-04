# HordeAIUpdate header adoption

This handoff uses LINK-227. Another worker published LINK-226 concurrently;
the original attempt log's LINK-226 reference is superseded by LINK-227.

2026-11-04, codexb; source base `370febb6d2`, prediction index
`a62ac1c10b` (2026-11-04 07:28).

`header_adopt_lane.py adopt --class HordeAIUpdate --header
Code/GameEngine/Include/GameLogic/Module/HordeAIUpdate.h --apply` tried the
six queued units. Only
`Code/GameEngine/Source/GameLogic/Object/Update/AIUpdate/HordeAIUpdatePrivateCommands.cpp`
passed unchanged byte comparison. Its private HordeAIUpdate declaration is
replaced by the canonical include. `header_adopt_lane.py accept` retired that
unit's HordeAIUpdate row. Explicit `./build.sh` verification passes 8/8 rows;
the declared-unmatched check is clear. Ordinary `link_check.py` predicts LINKS,
1,301 -> 1,301 bytes. These are preserved bytes, not a census gain.

The same unit already includes canonical AIUpdateInterface and
AICommandInterface declarations. Their acceptance checks now pass and retire
two stale queue rows. An explicit BehaviorModule.h include also satisfies the
canonical dependency check for BehaviorModule and BehaviorModuleInterface;
both acceptance checks pass and retire their rows. Five header-queue entries
are retired in total, all through `header_adopt_lane.py accept`. ControlBar's
private unrecovered fields remain a separate adoption prerequisite.

Other automated trials were restored:

- `Common/Rva0026E836Derived.cpp` and `HordeWorkerAIUpdateDtor.cpp`: their
  `m_extra03E4` data word has no corresponding canonical data field. The
  canonical layout represents the interface at +0x3E4 as a base class.
- `Common/Thing/ModuleFactoryInit.cpp`: Module class redefinition.
- `AIUpdate/HordeAIUpdateCtor.cpp`: missing default AIUpdateInterface
  constructor; the source initializer still names its private opaque base.
- `HordeWorkerAIUpdateCtor.cpp`: private `m_vtable` is absent from the
  canonical class.

A manual worker-destructor trial removed its obsolete base hierarchy,
included HordeAIUpdate.h and wrote the secondary table through
`*(const void **)((char *)this + 0x3E4) = g_00C50868`. Both existing rows
byte-match (2/2). An adjusted-base-pointer cast instead emitted a leading LEA
and did not match; the direct byte offset avoided that extra instruction.
However, `accept` refused the direct-offset trial because its generated
vtables introduce these six unresolved names:

```
?GetSnapshotName@HordeAIUpdate@@MBEPBDXZ
?loadPostProcess@HordeAIUpdate@@MAEXXZ
?slot22@HordeAIUpdate@@UAEPAXXZ
?vslot094@AIUpdateInterface@@UBEPAXXZ
?vslot095@AIUpdateInterface@@UBEPAXXZ
?xfer@HordeAIUpdate@@MAEXPAVXfer@@@Z
```

Prediction: worker destructor 77 -> 0 bytes. No exact-name function or symbol
row was found for these six spellings. This establishes a provider-spelling
prerequisite, not that the retail bodies are absent. Recover the existing
owners and their proper identities through the naming lane before retrying
this adoption. The worker source was restored and `./build.sh` again passes
2/2. Its header debt remains. No linker alias was removed or added.
