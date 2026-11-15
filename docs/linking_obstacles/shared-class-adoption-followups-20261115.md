# SubsystemInterface and GameLogic adoption follow-ups (2026-11-15)

Completed: `Code/Libraries/Source/subsystem/SubsystemInterfaceCopy.cpp` now includes its registered canonical header through `header_adopt_lane.py adopt --apply`. The existing header declares the copy constructor and assignment, clearing the queue's old C2600 failure. The unit enables the existing `BFME_SUBSYSTEM_SLOTS` compiler option because its private view had fourteen virtual slots. The canonical header and all shared headers remain unchanged.

Verification: 2/2 functions byte-match. The emitted SubsystemInterface vtable remains 56 bytes / fourteen relocations, with the same ordered target symbols as before. The header lane's `vt_undefined.py` reports zero newly undefined references, repeated over the captured before/after COFF on srv1. `link_check`'s own verdict is LINKS, 68 -> 68 bytes. `header_adopt_lane.py accept` retires exactly the SubsystemInterfaceCopy queue row; its other rows are untouched.

The full seven-unit trial cohort was rebuilt and refreshed after every exclusion. All seven own LINKS verdicts pass using the once-fetched published index (2026-11-15 20:31 / 9bbbf6b768). These are scoped row, vtable and link-prediction results, not whole-object equality, a fresh global census or real-image/runtime proof.

GameLogic: all six originals are restored byte-for-byte and their queue rows remain. The local enum collision can be removed without shared-header edits: use an ObjectID forward declaration and the equivalent typed zero during the supported original-layout preflight; the canonical header supplies the definition after adoption. An initial trial inserted the whole canonical header too early and correctly failed on duplicate GameLogic definitions; those setup diagnostics are superseded by this valid baseline trial. No guard, tool or gate was changed.

The corrected trial finds these actual next blockers:

- FAIL Code/GameEngine/Source/GameLogic/AI/AIStatesBfmeComputePath.cpp: field renames: GameLogic::m_bfmeDebugLevel (+0x1B4, 4 bytes) has no canonical field of that offset and size
- FAIL Code/GameEngine/Source/GameLogic/AI/Squad.cpp: field renames: GameLogic::m_objHash (+0xB0, 20 bytes) has no canonical field of that offset and size
- FAIL Code/GameEngine/Source/GameLogic/Object/Behavior/SlowDeathBehaviorUpdate.cpp: field renames: GameLogic::m_hulkMaxLifetimeOverride (+0xA0, 4 bytes) has no canonical field of that offset and size
- FAIL Code/GameEngine/Source/GameLogic/Object/Body/ActiveBody.cpp: field renames: GameLogic::m_objHash (+0xB4, 20 bytes) has no canonical field of that offset and size
- FAIL Code/GameEngine/Source/GameLogic/Object/Object_setID.cpp: field renames: GameLogic::m_lookup (+0xB4) is ObjectLookupMap; the canonical GameLogic::m_map is ObjectIdMap
- FAIL Code/GameEngine/Source/GameLogic/ScriptEngine/ScriptEngineRva00358752.cpp: FAIL ?lookupUnitByValue@Rva00358752Opaque@@QAEPAVObject@@VAsciiString@@@Z (Code/GameEngine/Source/GameLogic/ScriptEngine/ScriptEngineRva00358752.cpp)

The first five require canonical field/layout or map-type reconciliation, outside this unit-local enum batch. ScriptEngineRva00358752 instead reaches a row byte mismatch; investigate the recorded lookupUnitByValue row before another adoption. Do not widen the shared accessed-prefix header or substitute another map type merely to pass compilation. No failed GameLogic source is landed.

Evidence: slotnames scratch `followup-results` (first SubsystemInterface pass), `followup-game-results` (corrected six-unit trial), `followup-final-results` (combined restored-cohort rows/link, exact source/dependency fingerprints and before/after COFF). StringBase is separate: its two landed batches remove 43 of the assigned 60 declaration facades, with 17 unchanged trial exclusions.
