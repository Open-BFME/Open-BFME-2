# Script-event record key identity

Inspected base: `cc891735cc`. Scope: `Common/Rva00332F5BCtor.cpp` and
`Common/Rva00332FC1Ctor.cpp`, under `Code/GameEngine/Source/`.

## Target facts

Both 38-byte constructors call retail `0x00326BE6` at instruction offset
`+3` (COFF relocation `+4`). That six-byte body zeroes the dword at `this`.
Their remaining calls copy two 76-byte payloads at `+4` and `+0x50`, or two
16-byte payloads at `+4` and `+0x14`, respectively. Their rowed 64-byte
predicates compare the first dword directly before comparing the payloads.

The two rowed parser consumers, `LuaScriptEngineParseModelConditionEvent.cpp`
and `LuaScriptEngineParseObjectStatusEvent.cpp`, construct these records and
pass their address to `EventFlagEntry::setKeyFromName` (`0x003316BA`). The
setter's native call at `0x003316C7` reaches
`NameKeyGenerator::nameToKey(const char *)` (`0x00148E1A`), then
`0x003316CC` stores EAX at `[ESI]`. The value is a name key, not string storage.
This conclusion uses the rowed caller/setter chain and native stores; the
shared zero-constructor address by itself cannot identify a type.

## Source correction

Replace both private `UnicodeString` bodies with the existing four-byte
`Rva00336BE4Key` view. Its already-rowed constructor in
`GameLogic/ScriptEngine/Rva00336BE4KeyCtor.cpp` owns the same native
`0x00326BE6` body. The view is also used by
`LuaScriptEngine_ProcessScriptedEvent.cpp` before the same name setter.
The address-derived view name is structural; this does not recover retail's
original C++ record name. No external donor name or layout is claimed.

Constructor calls now use that existing provider. The predicates compare
`unsigned key` values. Payload views and their existing names remain outside
this correction. The owning ledger tool updates the two misleading constructor
notes while preserving their names, RVAs, extents and source owners.

## Verification

- Frozen-file checks pass before and after the correction. The existing
  absent-from-retail anchor remains explicit.
- Ordinary build passes all four rows (204 bytes).
- Before/after object comparison preserves all four raw bodies exactly.
  Only the constructors' `+4` relocation changes, from
  `??0UnicodeString@@QAE@XZ` to `??0Rva00336BE4Key@@QAE@XZ`; both resolve to
  retail `0x00326BE6`. Equality relocations and payload-copy relocations are
  unchanged. Local comparison output: `build/script-key-identity/`.
- Before correction, both callers and the existing key provider preview
  LINKS, retaining 102 + 102 + 6 authored bytes against census index
  `6fe1089c24` (2026-10-30 04:25).
- Strict preparation of those three sources and the two parser consumers
  passes 13/13 rows, five string literals, two empty-string references and
  two renamed funclet placements. The ordinary gates reuse all five strict
  objects. Final paired preview reports 5/5 LINKS, retaining 1,295 authored
  bytes (102 + 102 + 6 + 602 + 483). Existing unreferenced `ConditionWords`
  diagnostics in the object-status parser are not blockers; neither parser
  source is edited.
- `check_csv.py` passes with 99,010 function rows, 9,413 symbol rows and 2,235
  data rows.
- Staged-tree `link_batch_audit.py` is INCONCLUSIVE: the census index predates
  the outgoing source base, and affected consumer
  `Code/GameEngine/Source/Common/AIGameTeam.cpp` lacks a current receipt.
  This does not establish full consumer selection or absence of losses.
  Carry both repaired records, their existing constructor provider, both
  parser consumers and the wider affected scope into the next scheduled
  census. No nightly, link cycle or smoke run is started.

No new body, pin, alias, class hatch, source path or unique byte coverage is
introduced. This is an identity correction to existing matched owners.

## Header-queue boundary

`header_adopt_lane.py accept --class UnicodeString` refuses both files solely
because they do not include `reference/shims/bfme2_ascii/unicode_string.h`.
Its `misclassified` exception requires the historically queued source to have
had no namespace-scope body of that name. These files did have such bodies;
correcting their false identity therefore does not satisfy that exception.
The two queue rows remain, and the false rejects are recorded through
`re_log.py`. Acceptance needs a supported identity-correction proof path;
adding an unused string header would conceal the issue. The old notes about
missing buffer-identity accessors are superseded for these two records.
