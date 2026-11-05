# SpecialAbilityUpdate.cpp: absorb Rva0044EF5EFinish.cpp (2026-11-05)

`tu_skeleton --merge --dry-run` accepted SpecialAbilityUpdate.cpp plus
Rva0044EF5EFinish.cpp; eight donors stay rejected:
- compile: Rva0044ECCEDtor.cpp (StringBase redefinition),
  SpecialAbilityUpdateModuleData.cpp (C2600 compiler-generated ctor),
  SpecialAbilityUpdateSlot8.cpp and ...IsWithinStartAbilityRange.cpp
  (m_prepSoundLoop undeclared), SpecialAbilityUpdateXfer.cpp (xfer not a
  member), SpecialAbilityUpdateRva0044FEB6.cpp (Thing base undefined),
  SpecialAbilityUpdateInitiateIntent.cpp (m_modelConditionFlags type),
  SpecialAbilityUpdateTriggerAbilityEffect.cpp (Object::position missing)
- bytes: SpecialAbilityUpdateDtor.cpp

Verification after the merge: `./build.sh SpecialAbilityUpdate.cpp` 32/32
matched (EH funclets verified past renumbered labels, 5+1 string and 13
float literals); `find_declared_unmatched` clean; `link_check
--new-variants` clean. The merged cl line carries the donor's include paths.

Path consumers: only `reverse/link_status.csv` (census output), the TU's
provenance comment and historical attempt evidence name the old path; no
tool, hook, include or debt-register key does.
