# ConstIntGettersAddr.cpp: last five FieldParse tables typed (blocked by link_debt --staged)

Seat halilkkaya-ad-o1, 2026-11-01, base e57b7de842, census index 987ee56fdc.

## What `typed-tables.patch` does

It turns the last five raw-int tables in `Code/GameEngine/Source/Common/ConstIntGettersAddr.cpp`
into typed `FieldParse` tables:

- s_fxpsSizeAngleTable 0x00C6C4A0
- s_modelDrawFieldTable 0x00BCB3C8
- AODCrushCollideTable 0x00C5A4A8
- s_transportAiFieldTable 0x00BF9378
- s_radiusDecalFieldTable 0x00C0DC20

It uses the method of 62b884e46b. `convert_fp.py` generated the patch:

- Field names come from retail through `build.read_target_bytes`.
- Every parser is the one matched `functions.csv` row at its RVA, declared through `__identifier`.
- Owned userData lists are named: 0xDBC284 `TheWeaponSlotTypeNames` and 0xDBB4F0 `TheLocomotorSetNames`.
- The five consumers declare `extern const FieldParse X[]`.
- Five new data rows check the initializers.

Verified on the patched tree:

- `./build.sh` on the 6 sources: Functions OK 57/57, Data rows OK (39 verified).
- `find_declared_unmatched` is clean on all six sources.
- Scoped DIR32 is OK (28 symbols).
- `link_check`: ConstIntGettersAddr.cpp addresses go from 254 to 24. The five consumers still LINK
  (2,762 B, unchanged). The 14 providers of the newly referenced parsers and lists still LINK
  (15,574 B, unchanged).

## Why it is not committed

Ten userData words point at lists with no external real-named definition, so they stay as
`(const void *)0x...` literals inside the typed entries:

- 0x00C1B6D8 (Rotation) is only defined as address-named `g_00C1B6D8` in
  FXParticleSystemModuleParsers.cpp. exports.csv names it `?RotationTypeNames@FXParticleSystem@@3QBQBDB`.
  The data ledger holds a stale `?g_00C1B6D8@@3PAPBDA` size 560 entry, which earlier blocked a rebind
  (reverse/attempt_support/rotation-table-link-blocked-20261014).
- 0x00DB960C (MinLODRequired) is only defined as `g_00DB960C` in GameLOD.cpp, with no data row and no
  proven name.
- 0x00DCD4D0 and 0x00DCD550 (6 words), 0x00DBB4C4 and 0x00DBE6F0 are per-TU copies of Zero Hour's
  header `static` lists: TheDamageNames, TheDeathNames, TheAutoAcquireEnemiesNames and TheShadowNames.
  Each of those names already belongs to another copy's data row, and data_rows allows one row per name.
  A `static` copy is no fix either: data_rows.verify_row refuses a relocation to a TU-local symbol.

The pre-commit `link_debt.py --staged` refuses the commit (casts 0 -> 10), and it is right to. All
ten counted casts embed an image address (`(const void *)0x00DCD4D0`, ...), so they are real link debt
even though each address was already in the file as a raw word. The symbol-based
`(FieldParseProc)&__identifier(..)` casts are not counted, which is also correct. This was first
logged as a false reject, then retracted (`void` row in reverse/re_attempts.log, followed by a plain
`blocked` row). Do not change link_debt for this case.

## To land

The ten lists need real external names (each with a data row) before the patch can land. Once they
have them, replace each `(const void *)0x...` with the named list, apply the patch with `git apply`,
rebuild the six sources, and run link_check on the consumers and providers.
