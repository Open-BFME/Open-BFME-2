# Volumetric-shadow TU approval: four shared cache bodies

Inspected `bb9a7d13ca`, 2026-11-04. Scope claim:
`file:Code/GameEngineDevice/Source/W3DDevice/GameClient/Shadow/W3DVolumetricShadow.cpp`.

The current map rebuilt in memory by `tu_skeleton.map_rows()` assigns this TU
87 proposed ordinary code rows (53 Z, 2 S, 32 C) in 46 source files, spanning
RVA `0x000EFB99..0x000F4AB7`, plus 64 approved P funclets. The picker reports
45 files; the current-map source count above includes generated/mixed sources.
The only other TU's F/Z/S/L/N/U/C assignments inside that ordinary-code span
are these four approved Z rows of `Code/Libraries/Source/WWVegas/WW3D2/hanimmgr.cpp`:

| RVA | Bytes | Current owner |
| --- | ---: | --- |
| 0x000F0B81 | 23 | HAnimManagerClass::Peek_Anim |
| 0x000F0B98 | 19 | HAnimManagerClass::Get_Anim |
| 0x000F0BAB | 23 | HAnimManagerClass::Add_Anim |
| 0x000F0BC2 | 21 | HAnimManagerClass::Is_Missing |

## Target facts

`functions.csv` owns each address once. The first, third and fourth bodies are
in `hanimmgr.cpp`; the second is in `hanimmgr_GetAnim.cpp`. Their placement notes
cite masked compiled-body matches, not a retail source-name assertion.
`symbols.csv` already pins W3DShadowGeometryManager::Peek_Geom and Add_Geom to
the first and third addresses. Shadow `Load_Geom` and `addShadow` reconstruct
calls through HAnimManagerClass casts at those same addresses. These existing
casts and pins alone do not prove which retail object supplied the kept body.
No WorldBuilder lead for any of the four RVAs was found in `wb_name_leads.csv`.

## Donor facts

The pinned Zero Hour tree's `W3DVolumetricShadow.cpp:3986..4044` defines
W3DShadowGeometryManager::Peek_Geom, Get_Geom, Add_Geom and Is_Missing with
hash-table lookup, reference increment/insertion, and missing-table lookup
shapes corresponding to the animation methods. The BFME 1 game source has
these geometry methods at lines 4103..4161 too. These are donor facts, not
BFME 2 source-ownership proof or independent exact-byte comparison receipts.

## Boundary and next step

The map treats the four animation names' ZH definition sites as hard anchors;
`tu_map.build()` consequently marks the surrounding shadow span noncontiguous.
Shared/folded cache bodies are a plausible explanation. A routine rename would
replace real names with other real names without evidence identifying the
retail owner, and would not establish that the animation identities are wrong.
No row, pin, name, map or source was changed. Resolve the shared-body ownership
with independent target evidence, or a separately validated mapper treatment
of bodies with multiple supported TU identities, before merging these 87 rows.
Do not infer approval merely from placement between shadow functions.

## Verification

- `python3 tools/check_csv.py`: passed, 99,450 function rows.
- `python3 tools/find_declared_unmatched.py .../W3DVolumetricShadow.cpp`:
  all defined functions already matched.
- `./build.sh .../W3DVolumetricShadow.cpp`: 4/4 exact; string, float and import
  checks passed.
- `tu_skeleton.py --plan .../W3DVolumetricShadow.cpp`: 64 approved funclet rows,
  1 donor, 1 mixed file, 7 refused files; the 87 ordinary rows remain proposed.

No merge trial, linking census, smoke run or TU-approval gain is claimed.
