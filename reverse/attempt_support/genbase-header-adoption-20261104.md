# GenBase009EB7D0 header adoption, 2026-11-04

Inspected source revision: `a3368cc7d7ea9e088f947a60cdd530a2d553abbc`. Worker: yasinschroeder-codex4.
Prediction index: `3fbce7bcb2`, 2026-11-04 22:01; fetched through
`link_check.py --fetch-index` (local index retained; published objects imported).
No census or whole-game link was run; preview counts below preserve existing coverage.

## Applied scope

`Rva001517B5Link.cpp` and `Rva00180AB5.cpp` now include the registered
`GenBase009EB7D0.h` instead of declaring private four-byte base views.
Removed each derived class's redundant sixteen-byte `m_pad04`: the shared
base owns that storage, keeping the link/tree pointer at +0x14.
Function bodies, names, flags, ledger rows and aliases are unchanged.
`header_adopt_lane.py accept --class GenBase009EB7D0` passed both files and
retired exactly their two queue rows. Their 41 + 33 authored bytes remain linked
in the current-object preview.

## Reverted constructor cohort / LINK-354

The initial supported adoption trial failed all fifteen queued files. Six
constructor files and the two method files had the same duplicated padding.
After correcting it, the ordinary scoped builder verified all 14 rows across
eight sources, including the existing EH handler/funclet rows.

The six constructor files still failed adoption's link verdict: their expanded
derived vtables reference these canonical base members without providers:

- `?Delete@GenBase009EB7D0@@UAEXXZ`
- `?UnloadNow@GenBase009EB7D0@@UAEXXZ`
- `?vslot10@GenBase009EB7D0@@UAE_NXZ`
- `?vslot11@GenBase009EB7D0@@UAEXXZ`

`Rva00180B94Ctor.cpp` also emits `??_7Rva00180B94_Prototype@@6B@` differing
from the first copy in link order. The trial predicted loss of 634 existing
linked bytes, so all six constructor source edits were restored and rebuilt.
Seven constructor-body verdicts are recorded through `re_log.py`; no failed
source reconstruction remains in Code/.

Target evidence in the canonical header associates the slot bodies with RVAs
0x0061EDA0, 0x00130FCE, 0x0061EE20 and 0x0061EE50. The current ledger rows
use AssetFactoryBase::Delete, BfmeThingURB::bfmeGoURB (int result),
Rva009EB8A0::method and BfmeE1024::UnloadNow respectively. This establishes
the provider identity mismatch; it does not establish an approved class rename
or ABI change. Next work needs the normal identity/naming workflow to reconcile
these providers and the derived vtable copies before retrying the constructors.
Do not introduce alias pragmas to make this adoption pass.

The seven other queued files are unchanged: five fail with abstract derived
classes, texture.cpp has a field-rename collision, and Rva00136794Dtor.cpp needs
its inline base teardown reconciled. Their existing debt stays queued.

## Receipts

### Initial adoption trial (expected refusal)

```text
  FAIL Code/GameEngine/Source/Common/Rva00151632Ctor.cpp: FAIL ??0Rva00151632@@QAE@PBD@Z (Code/GameEngine/Source/Common/Rva00151632Ctor.cpp)
  FAIL Code/GameEngine/Source/Common/Rva001517B5Link.cpp: FAIL ?rva001517B5@Rva00151632@@UAEXXZ (Code/GameEngine/Source/Common/Rva001517B5Link.cpp)
  FAIL Code/GameEngine/Source/Common/Rva0017FB41Ctor.cpp: FAIL ??0Rva0017FB41_Prototype@@QAE@PBDHH@Z (Code/GameEngine/Source/Common/Rva0017FB41Ctor.cpp)
  FAIL Code/GameEngine/Source/Common/Rva001803D3Ctor.cpp: FAIL ??0Rva001803D3@@QAE@PBDHH@Z (Code/GameEngine/Source/Common/Rva001803D3Ctor.cpp)
  FAIL Code/GameEngine/Source/Common/Rva00180847Ctor.cpp: FAIL ??0Rva00180847@@QAE@PBDHH@Z (Code/GameEngine/Source/Common/Rva00180847Ctor.cpp)
  FAIL Code/GameEngine/Source/Common/Rva00180AB5.cpp: FAIL ?rva00180AB5@Rva00180B94_Prototype@@UAEXXZ (Code/GameEngine/Source/Common/Rva00180AB5.cpp)
  FAIL Code/GameEngine/Source/Common/Rva00180B94Ctor.cpp: FAIL ??0Rva00180B94_Prototype@@QAE@PBDPAX@Z (Code/GameEngine/Source/Common/Rva00180B94Ctor.cpp)
  FAIL Code/Libraries/Source/WWVegas/WW3D2/AnimationAsset.cpp: Code\Libraries\Source\WWVegas\WW3D2\AnimationAsset.cpp(249) : error C2259: 'Rva0014CE67_Prototype' : cannot instantiate abstract class
  FAIL Code/Libraries/Source/WWVegas/WW3D2/BfmeResetTextureRef.cpp: Code\Libraries\Source\WWVegas\WW3D2\BfmeResetTextureRef.cpp(266) : error C2259: 'Rva001805E0' : cannot instantiate abstract class
  FAIL Code/Libraries/Source/WWVegas/WW3D2/Rva00131BE5Ctor.cpp: FAIL ??0Rva00131BE5@@QAE@PAX000HH@Z (Code/Libraries/Source/WWVegas/WW3D2/Rva00131BE5Ctor.cpp)
  FAIL Code/Libraries/Source/WWVegas/WW3D2/Rva00131DFC.cpp: Code\Libraries\Source\WWVegas\WW3D2\Rva00131DFC.cpp(65) : error C2259: 'Rva00131BE5' : cannot instantiate abstract class
  FAIL Code/Libraries/Source/WWVegas/WW3D2/Rva00180054Factory.cpp: Code\Libraries\Source\WWVegas\WW3D2\Rva00180054Factory.cpp(81) : error C2259: 'Rva0017FF77' : cannot instantiate abstract class (fields: GenBase009EB7D0::m_flags -> m_04, GenBase009EB7D0::m_zero08 -> m_08, GenBase009EB7D0::m_zero0c -> m_0C, GenBase009EB7D0::m_zero10 -> m_10)
  FAIL Code/Libraries/Source/WWVegas/WW3D2/Rva00972A30AddPrototype.cpp: Code\Libraries\Source\WWVegas\WW3D2\Rva00972A30AddPrototype.cpp(16) : error C2259: 'Rva00972880' : cannot instantiate abstract class
  FAIL Code/Libraries/Source/WWVegas/WW3D2/texture.cpp: field renames: Code/Libraries/Source/WWVegas/WW3D2/texture.cpp: renaming m_flags -> m_04 collides with an existing `m_04` there
  FAIL Code/Libraries/Source/WWVegas/WWLib/Rva00136794Dtor.cpp: FAIL ??1Rva00136794@@UAE@XZ (Code/Libraries/Source/WWVegas/WWLib/Rva00136794Dtor.cpp) (fields: GenBase009EB7D0::m_flags -> m_04, GenBase009EB7D0::m_zero08 -> m_08, GenBase009EB7D0::m_zero0c -> m_0C, GenBase009EB7D0::m_zero10 -> m_10)
```

### Padding-corrected cohort build

```text
Source claims: OK (8 sources, scoped byte-verified)
Funclet pins: 2 row(s) verified past a renumbered $L label
    $L339 (Code/GameEngine/Source/Common/Rva001803D3Ctor.cpp): $L339 was renumbered; verified parent EH data places $L447 at 0x00768249
    $L345 (Code/GameEngine/Source/Common/Rva00180B94Ctor.cpp): $L345 was renumbered; verified parent EH data places $L453 at 0x007683B6
Functions: OK 14/14 matched across 8 source file(s)
String-ref verify: OK (1 literals + 0 empty-string refs verified, 0 baselined, 0 unverified/skipped)
Float-ref verify: OK (0 compiler literals verified)
Import-ref verify: OK (0 named imports verified)
```

### Padding-corrected cohort adoption verdict

```text
  FAIL Code/GameEngine/Source/Common/Rva00151632Ctor.cpp: link_check predicts a loss of census-linked bytes
  PASS Code/GameEngine/Source/Common/Rva001517B5Link.cpp
  FAIL Code/GameEngine/Source/Common/Rva0017FB41Ctor.cpp: link_check predicts a loss of census-linked bytes
  FAIL Code/GameEngine/Source/Common/Rva001803D3Ctor.cpp: link_check predicts a loss of census-linked bytes
  FAIL Code/GameEngine/Source/Common/Rva00180847Ctor.cpp: link_check predicts a loss of census-linked bytes
  PASS Code/GameEngine/Source/Common/Rva00180AB5.cpp
  FAIL Code/GameEngine/Source/Common/Rva00180B94Ctor.cpp: link_check predicts a loss of census-linked bytes
  FAIL Code/Libraries/Source/WWVegas/WW3D2/Rva00131BE5Ctor.cpp: link_check predicts a loss of census-linked bytes
  retired 2 row(s) from reverse/header_queue.tsv; commit it with the adoption
```

### Rejected constructor link preview

```text
Compile: 0 of 1 TU(s) (deps-cache: 1 current)
Compile: 0 of 1 TU(s) (deps-cache: 1 current)
Compile: 0 of 1 TU(s) (deps-cache: 1 current)
Compile: 0 of 1 TU(s) (deps-cache: 1 current)
Compile: 0 of 1 TU(s) (deps-cache: 1 current)
Compile: 0 of 1 TU(s) (deps-cache: 1 current)
Code/GameEngine/Source/Common/Rva00151632Ctor.cpp: does not link  LINKED 98 -> 0 bytes (census 2026-11-04 22:01 at 3fbce7bcb2; file's own bytes 98)
  unresolved  ?Delete@GenBase009EB7D0@@UAEXXZ
  unresolved  ?UnloadNow@GenBase009EB7D0@@UAEXXZ
  unresolved  ?vslot10@GenBase009EB7D0@@UAE_NXZ
  unresolved  ?vslot11@GenBase009EB7D0@@UAEXXZ
Code/GameEngine/Source/Common/Rva0017FB41Ctor.cpp: does not link  LINKED 77 -> 0 bytes (census 2026-11-04 22:01 at 3fbce7bcb2; file's own bytes 77)
  unresolved  ?Delete@GenBase009EB7D0@@UAEXXZ
  unresolved  ?UnloadNow@GenBase009EB7D0@@UAEXXZ
  unresolved  ?vslot10@GenBase009EB7D0@@UAE_NXZ
  unresolved  ?vslot11@GenBase009EB7D0@@UAEXXZ
Code/GameEngine/Source/Common/Rva001803D3Ctor.cpp: does not link  LINKED 77 -> 0 bytes (census 2026-11-04 22:01 at 3fbce7bcb2; file's own bytes 77)
  unresolved  ?Delete@GenBase009EB7D0@@UAEXXZ
  unresolved  ?UnloadNow@GenBase009EB7D0@@UAEXXZ
  unresolved  ?vslot10@GenBase009EB7D0@@UAE_NXZ
  unresolved  ?vslot11@GenBase009EB7D0@@UAEXXZ
Code/GameEngine/Source/Common/Rva00180847Ctor.cpp: does not link  LINKED 77 -> 0 bytes (census 2026-11-04 22:01 at 3fbce7bcb2; file's own bytes 77)
  unresolved  ?Delete@GenBase009EB7D0@@UAEXXZ
  unresolved  ?UnloadNow@GenBase009EB7D0@@UAEXXZ
  unresolved  ?vslot10@GenBase009EB7D0@@UAE_NXZ
  unresolved  ?vslot11@GenBase009EB7D0@@UAEXXZ
Code/GameEngine/Source/Common/Rva00180B94Ctor.cpp: does not link  LINKED 163 -> 0 bytes (census 2026-11-04 22:01 at 3fbce7bcb2; file's own bytes 163)
  unresolved  ?Delete@GenBase009EB7D0@@UAEXXZ
  unresolved  ?UnloadNow@GenBase009EB7D0@@UAEXXZ
  unresolved  ?vslot10@GenBase009EB7D0@@UAE_NXZ
  unresolved  ?vslot11@GenBase009EB7D0@@UAEXXZ
  comdat      ??_7Rva00180B94_Prototype@@6B@  (first: differs from the first copy in link order (no retail address))
Code/Libraries/Source/WWVegas/WW3D2/Rva00131BE5Ctor.cpp: does not link  LINKED 142 -> 0 bytes (census 2026-11-04 22:01 at 3fbce7bcb2; file's own bytes 142)
  unresolved  ?Delete@GenBase009EB7D0@@UAEXXZ
  unresolved  ?UnloadNow@GenBase009EB7D0@@UAEXXZ
  unresolved  ?vslot10@GenBase009EB7D0@@UAE_NXZ
  unresolved  ?vslot11@GenBase009EB7D0@@UAEXXZ
link_check: 0 of 6 link cleanly; LINKED 634 -> 0 bytes (6.3s)
```

### Final build after restoring constructor trials

```text
Source claims: OK (8 sources, scoped byte-verified)
Compile: 6 of 8 TU(s) (deps-cache: 2 current)
Funclet pins: 2 row(s) verified past a renumbered $L label
    $L339 (Code/GameEngine/Source/Common/Rva001803D3Ctor.cpp): $L339 was renumbered; verified parent EH data places $L423 at 0x00768249
    $L345 (Code/GameEngine/Source/Common/Rva00180B94Ctor.cpp): $L345 was renumbered; verified parent EH data places $L429 at 0x007683B6
Functions: OK 14/14 matched across 8 source file(s)
String-ref verify: OK (1 literals + 0 empty-string refs verified, 0 baselined, 0 unverified/skipped)
Float-ref verify: OK (0 compiler literals verified)
Import-ref verify: OK (0 named imports verified)
```

### Final accepted method-only cohort

```text
  PASS Code/GameEngine/Source/Common/Rva001517B5Link.cpp
  PASS Code/GameEngine/Source/Common/Rva00180AB5.cpp
```

### Final preview, including restored constructors

```text
Compile: 0 of 1 TU(s) (deps-cache: 1 current)
Compile: 0 of 1 TU(s) (deps-cache: 1 current)
Compile: 0 of 1 TU(s) (deps-cache: 1 current)
Compile: 0 of 1 TU(s) (deps-cache: 1 current)
Compile: 0 of 1 TU(s) (deps-cache: 1 current)
Compile: 0 of 1 TU(s) (deps-cache: 1 current)
Compile: 0 of 1 TU(s) (deps-cache: 1 current)
Compile: 0 of 1 TU(s) (deps-cache: 1 current)
Code/GameEngine/Source/Common/Rva00151632Ctor.cpp: LINKS  LINKED 98 -> 98 bytes (census 2026-11-04 22:01 at 3fbce7bcb2; file's own bytes 98)
Code/GameEngine/Source/Common/Rva001517B5Link.cpp: LINKS  LINKED 41 -> 41 bytes (census 2026-11-04 22:01 at 3fbce7bcb2; file's own bytes 41)
Code/GameEngine/Source/Common/Rva0017FB41Ctor.cpp: LINKS  LINKED 77 -> 77 bytes (census 2026-11-04 22:01 at 3fbce7bcb2; file's own bytes 77)
Code/GameEngine/Source/Common/Rva001803D3Ctor.cpp: LINKS  LINKED 77 -> 77 bytes (census 2026-11-04 22:01 at 3fbce7bcb2; file's own bytes 77)
Code/GameEngine/Source/Common/Rva00180847Ctor.cpp: LINKS  LINKED 77 -> 77 bytes (census 2026-11-04 22:01 at 3fbce7bcb2; file's own bytes 77)
Code/GameEngine/Source/Common/Rva00180AB5.cpp: LINKS  LINKED 33 -> 33 bytes (census 2026-11-04 22:01 at 3fbce7bcb2; file's own bytes 33)
Code/GameEngine/Source/Common/Rva00180B94Ctor.cpp: LINKS  LINKED 163 -> 163 bytes (census 2026-11-04 22:01 at 3fbce7bcb2; file's own bytes 163)
Code/Libraries/Source/WWVegas/WW3D2/Rva00131BE5Ctor.cpp: LINKS  LINKED 142 -> 142 bytes (census 2026-11-04 22:01 at 3fbce7bcb2; file's own bytes 142)
link_check: 8 of 8 link cleanly; LINKED 708 -> 708 bytes (7.6s)
```
