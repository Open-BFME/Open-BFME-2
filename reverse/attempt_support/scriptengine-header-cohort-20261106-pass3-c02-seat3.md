# ScriptEngine header cohort: supported adoption boundaries

Base: `f15737ff46b`. Worker: `codex-fleet-20261106-c02-seat3`, shard `5/30`.

The initial default picker served Sphere writer `0x0055D525`; current source,
ledger and commit `795ee3be40a` prove that identity repair had already landed.
Its temporary claims were released; no writer reconstruction was repeated.
The supported ranked shard view then served this first fresh header cohort.

## Command and measured verdict

`header_adopt_lane.py adopt --class ScriptEngine --header
Code/GameEngine/Include/GameLogic/ScriptEngine.h --apply --jobs 1` with the
sixteen sources below, run under the fleet two-slot scheduler. Runtime used
`BFME_VM_WINEPREFIX=/home/bfme/.wine-pdb`, `BUILD_POOL=1` and the dispatch VM wine
wrapper. Original queued process was polled through completion, never duplicated.

**0/16 accepted, exit 1.** Exact scope of each supported refusal follows. These
are supported boundaries, not asserted verifier false rejects.

| Source | Refusal |
| --- | --- |
| `Code/GameEngine/Source/GameLogic/ScriptEngine/ScriptEngine_getObjectCount.cpp` | m_maps (+0x1A164,96 bytes) has no canonical field of that offset and size |
| `Code/GameEngine/Source/GameLogic/ScriptEngine/ScriptEngine_init.cpp` | m_pre (+0x8,107736 bytes) has no canonical field of that offset and size |
| `Code/GameEngine/Source/GameLogic/ScriptEngine/ScriptEngine_initActionTemplates.cpp` | m_pre (+0x0,32 bytes) has no canonical field of that offset and size |
| `Code/GameEngine/Source/GameLogic/ScriptEngine/ScriptEngine_initConditionTemplates.cpp` | m_pre (+0x0,32 bytes) has no canonical field of that offset and size |
| `Code/GameEngine/Source/GameLogic/ScriptEngine/ScriptEngine_initTemplateNameKeys.cpp` | m_pre (+0x0,32 bytes) has no canonical field of that offset and size |
| `Code/GameEngine/Source/GameLogic/ScriptEngine/ScriptEngine_rva00203FA8.cpp` | m_pre (+0x0,106784 bytes) has no canonical field of that offset and size |
| `Code/GameEngine/Source/GameLogic/ScriptEngine/ScriptEngine_rva002047CF.cpp` | m_useLogicDebugFrame (+0x1A4D9,1 byte) has no canonical field of that offset and size |
| `Code/GameEngine/Source/GameLogic/ScriptEngine/ScriptEngine_rva0020A7C9.cpp` | vendor/stlport/pthread.h: unresolved include /usr/include/pthread.h |
| `Code/GameEngine/Source/GameLogic/ScriptEngine/ScriptEngine_rva00357960.cpp` | m_begin (+0x1A120,4 bytes) has no canonical field of that offset and size |
| `Code/GameEngine/Source/GameLogic/ScriptEngine/ScriptEngine_updateClientDebugFrame.cpp` | m_useLogicDebugFrame (+0x1A4D9,1 byte) has no canonical field of that offset and size |
| `Code/GameEngine/Source/GameLogic/System/GameLogicInit.cpp` | SubsystemInterface::m_04 (+0x4,4 bytes) has no canonical field of that offset and size |
| `Code/GameEngineDevice/Source/MilesAudioDevice/MilesAudioManager.cpp` | Data rows: FAIL 1 of 1 |
| `Code/GameEngineDevice/Source/W3DDevice/GameClient/Drawable/Draw/W3DTruckDrawDoDrawModule.cpp` | vs2003 Vc7/include/new(75): error (tool summarized first compiler error only) |
| `Code/GameEngineDevice/Source/W3DDevice/GameClient/W3DDisplayGatherDebugStats.cpp` | m_campaignAI (+0x1A4C4,4 bytes) has no canonical field of that offset and size |
| `Code/GameEngineDevice/Source/W3DDevice/GameClient/W3DTreeBufferUpdate.cpp` | error C2039: getBreezeInfo is not a member of ScriptEngine |
| `Code/Libraries/Source/WWVegas/WWLib/ScriptEngine_setObjectCount.cpp` | m_maps (+0x1A164,12 bytes) has no canonical field of that offset and size |

## Integrity and remaining prerequisites

All sixteen sources were checked with `find_declared_unmatched.py` first.
MilesAudioManager reported 384 matched rows and 3 unclaimed definitions; it
remains frozen. The other fifteen reported all defined functions matched.
The tool left edits in MilesAudioManager, W3DTruckDrawDoDrawModule and
W3DTreeBufferUpdate even though all three printed FAIL. Those three edits were
restored; a final `git status --short` showed no Code changes. No header or queue
row was changed, no debt retired, and no reconstruction was left under Code/.

The offset/size refusals need evidence-backed canonical field contracts before
adoption; this pass did not infer a new layout or change the shared header.
The include/compiler failures need their actual owning SDK/STLport and method
contracts resolved. The Miles data-row failure needs a complete data diagnostic
and the three frozen bodies resolved. No unsupported aliases, stubs, pins or
manual signatures were introduced.

No strict provider receipt, consumer audit, new census, real link, image or smoke
run was obtained for this unsuccessful cohort. The available published index
was copied from the coordinator (47fd56b879, 2026-11-06 05:39 UTC); an index is
not a full-link or runtime result. No link or runtime improvement is claimed.
