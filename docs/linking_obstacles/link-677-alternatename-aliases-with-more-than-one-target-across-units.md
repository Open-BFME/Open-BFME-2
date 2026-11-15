### LINK-677: /alternatename aliases with more than one target across units

Status: Open. Updated: 2026-11-15 (ancalgonn-swarm-waste); inspected revision: `3e6d60a0651`.

**The defect.** A private class view that declares a placeholder virtual (`?slot02@State@@UAEXXZ`, `?b0@B0@@UAEXXZ`,
...) binds it to a rowed body with `#pragma comment(linker, "/alternatename:ALIAS=TARGET")`, a counted hatch
(`reverse/hatch_baseline.tsv`). When several units alias the same phantom name to *different* targets, the link
can keep only one, and every object that references the name gets that one. Each such alias is an identity defect
of the same kind as `State::slot02` (LINK-514) and `State::slot03` (fixed in `0b6fe9514d9`).

**Current list.** Tool lane 2's `sweeps/toollane2/multi-target-aliases.tsv` (2026-11-14 19:34) listed 48 aliases.
That list had gone stale. A scan of every `/alternatename` pragma under `Code/` at `3e6d60a0651` finds 2,223 aliases
in 942 files, and 17 of them have more than one target: 56 definitions in 23 units. All 23 units build, 181/181
matched. For each definition, the defining unit's own object was checked for a reference to the alias (`nm`, `U`).
Other objects that reference the name are listed from the census index's `touches` (metadata: 2026-11-14 23:54
UTC at `565145b59d`); absence from that snapshot does not establish absence at `3e6d60a0651`.

| Alias | Units | Unused in its own unit | Other objects that reference it | Verdict |
|---|---|---|---|---|
| `AIInternalMoveToState` onEnter/onExit/update/xfer | 5 | `onEnter` in Rva0036804FCtor.cpp | AIStateMoveTightenCtors, Rva003429B9Ctor, AIStateEvacLeafCtors (define no alias) | split; Rva0036804FCtor's `onEnter` alias kept (below) |
| `B0` `b0`, `B5` `b5`, `B7` `b7`, `B2` `b2` | 4 | `b2` in GarrisonContain.cpp | cave, transport, horde, horse-horde contain objects | split; GarrisonContain's `b2` removed (its target is ProductionQueueHordeContain's too) |
| `BehaviorModuleBase::unused`, `UpdateModule::update` | 3 | both in AIGateUpdate.cpp and DestroyEnvironmentUpdate.cpp | only MineshaftPortalBehaviourCtor.obj, which keeps its alias | removed; one target left |
| `Iface10::f10`, `Iface28::f28` | 2 | none | AODHordeContain, SiegeEngineContain, HordeSiegeEngineContain objects | split |
| `Rva0024A797_B2::f2` | 2 | LargeGroupAudioUpdateDtor.cpp | only CastleBehaviorDtor.obj | removed; one target left |
| `State::slot02` | 2 | none | AIInternalMoveToState ctor objects and others | split (LINK-514) |
| `Rva009EB810TailBase::slot18` | 2 | none | none beyond the two | split |
| `Visitor005CCCD0::visit` | 2 | none | HasListenersVisitor.obj | split |
| `Rva0053F1ECSub::note` | 1 | none | GameLogicInit.obj | one unit (RvaCountNoteRunFamily.cpp) aliases it twice, to two targets |

**Removed, by the hatch route.** Every removed alias is unreferenced by its own unit's object. Where a removal
eliminates a distinct target mapping (`BehaviorModuleBase::unused`, `UpdateModule::update`,
`Rva0024A797_B2::f2`), every consumer found in the census index retains its own alias: the coordinator-approved
case. GarrisonContain.cpp's `b2` mapping is preserved through ProductionQueueHordeContain.cpp's identical
remaining alias.
- AIGateUpdate.cpp and DestroyEnvironmentUpdate.cpp: `BehaviorModuleBase::unused` and `UpdateModule::update`
  (alternatename -4).
- LargeGroupAudioUpdateDtor.cpp: `Rva0024A797_B2::f2` (alternatename -1).
- GarrisonContain.cpp: `B2::b2` (alternatename -1); ProductionQueueHordeContain.cpp keeps the same target.

**Kept: Rva0036804FCtor.cpp's `AIInternalMoveToState::onEnter` alias** (target `?onEnter@Rva0036804F@@UAEHXZ`). Its
own object does not reference it, but its target is unique among the five. Three objects that define no alias
(AIStateMoveTightenCtors, Rva003429B9Ctor, AIStateEvacLeafCtors) reference the name and resolve through whichever
alias the link keeps. So it is not dead for the image, and removing it could change what they bind to. It stays
until that family's identities are recovered.

**Splits: what is left.** The remaining families contain conflicting target mappings for a shared phantom name.
Most definitions are referenced by their own objects; the unused definitions and their dispositions are listed
above. The lasting fix is identity, not hatch removal: adopt the
canonical class with each derived class's real override bound to its row (header adoption), or rename through
the identity tools. Each removed alias lowers its hatch count; each split stays counted until its family is
adopted.
