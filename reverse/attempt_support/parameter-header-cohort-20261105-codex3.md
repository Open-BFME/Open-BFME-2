# Parameter header cohort, 2026-11-05

Base: `0f487d74bad0`. Worker: `yasinschroeder-codex3`; model: GPT-6.

Six consumers now include the existing `ScriptParameter.h`, replacing private
Parameter declarations without changing that header or any ledger identity:

- Common/Script_objectTypesFromParam.cpp: use the canonical AsciiString field.
- ScriptEngine/ScriptActionParseAction.cpp: initialize the canonical cache words;
  remove the unused empty setter base along with the private declaration.
- ScriptEngine/ScriptActions_buildBaseBuilding.cpp: use the shared getInt getter.
- ScriptEngine/ScriptConditions_evaluateSkirmishSpecialPowerIsReady.cpp: use the
  canonical +0x20 word, documenting this parameter's cached-frame interpretation.
- ScriptEngine/ScriptEngineGetUnitNamed.cpp: read the canonical +0x24 object ID.
- ScriptEngine/ScriptEngine_setFlag.cpp: use the canonical integer field.

Verification:

- Before and after: `./build.sh` over the six sources passes all 12 rows,
  including the two EH funclets. Declared-unmatched checks pass for every source.
- One `header_adopt_lane.py accept --class Parameter` over all six sources
  passes and retires their six header-queue rows.
- Combined ordinary `link_check.py` preview: 6/6 LINKS, 1,584 -> 1,584 bytes,
  against the 2026-11-05 15:19 census index at `f44cbcf5b0`. Individual bytes:
  113, 55, 817, 397, 75 and 127 respectively. No census gain is claimed.
- `class_cleanup.runtime_graph` / `same_runtime`: all non-debug contents,
  relocation bindings, external definitions, COMDAT policies and weak bindings
  are identical for the common helper, constructor, special-power condition and
  flag setter. The base-building object is identical after substituting only
  `?bfme_getInt_d5339@Parameter@@QBEHXZ` with `?getInt@Parameter@@QBEHXZ` in
  its external definition and relocation bindings. The unit-named lookup is
  identical after removing its unreferenced getObjectID COMDAT section and
  renumbering sections.
- A pre-edit scan of all 36,803 `build/**/*.obj` objects (excluding this trial's
  backup directory) parsed COFF external records for both removed helper names.
  Each occurs only as a definition in its original source's object; neither has
  an undefined external consumer. The old getObjectID section has no runtime
  relocation to it within its defining object either. The existing link-wide
  getUnitNamed alternatename remains unchanged.
- No data/identity/gate-baseline keys belong to these six paths; the existing
  alternatename hatch remains. Source paths and row ownership do not move.

Eight Parameter queue rows remain unchanged. Their automatic trial still refuses
padding/status layouts, nested declarations, template/header conflicts or the
unrelated namespaced FXShader::Parameter. Those units were restored unchanged.
Whole-engine linking and census confirmation remain for scheduled measurement.
