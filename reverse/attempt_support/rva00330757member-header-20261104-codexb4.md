# Rva00330757Member header cohort, 2026-11-04

Inspected source revision: `a1ad5f0db7`. Class, header and all 15 queued
consumer files were claimed before trials. The initial 15-unit automatic
adoption retained no changes; four bounded manual adaptations pass below.
The other eleven sources are restored and retain their queue rows.

## Target facts and retained change

The unchanged canonical header records the constructor/destructor retail
accesses, absence of a vptr, and 0x10-byte extent. These are target facts;
the element type, original class name and field meanings remain unknown.
No donor identity is inferred here.

OpaqueScalarDeletingDtorsB18, Rva0053805DBaseDtor and LivingWorldBuildPlot
now include that header and define their existing inline destructor outside
the class body, using canonical field00 at offset zero. The free call's
existing spelling and inline policy are retained in each unit. A direct
header replacement had instead introduced an out-of-line destructor call
and failed byte verification. No shared header or allocator ABI changes.
LivingWorldLogicCtorBfme only replaces its private 16-byte declaration with
the include; its code and EH graph still verify, including the two funclets
whose compiler labels changed.

`header_adopt_lane.py accept --class Rva00330757Member` accepted all four
sources and retired exactly their four rows from `reverse/header_queue.tsv`.
The removed OpaqueScalarDeletingDtorsB18 private-body marker is obsolete:
the existing free-first-pointer destructor still verifies through its rowed
parent. `hatch_counters.py --update` removed its present-unmatched key;
unrelated stale shrinkage from that whole-tree update was excluded.
No new row, pin, alias, source path or invented recovered name is introduced.

## Verification

All four sources pass `find_declared_unmatched.py` before and after editing.
The normal `./build.sh` cohort result is:

```text
Source claims: OK (4 sources, scoped byte-verified)
Funclet pins: 34 row(s) verified past a renumbered $L label
    $L9050 (Code/GameEngine/Source/GameLogic/System/LivingWorld/LivingWorldLogicCtorBfme.cpp): $L9050 was renumbered; verified parent EH data places $L8706 at 0x007764A9
    $L9053 (Code/GameEngine/Source/GameLogic/System/LivingWorld/LivingWorldLogicCtorBfme.cpp): $L9053 was renumbered; verified parent EH data places $L8709 at 0x007764D3
    $L1824 (Code/GameEngine/Source/Common/OpaqueScalarDeletingDtorsB18.cpp): $L1824 was renumbered; verified parent EH data places $L2204 at 0x007A5F58
    $L1864 (Code/GameEngine/Source/Common/OpaqueScalarDeletingDtorsB18.cpp): $L1864 was renumbered; verified parent EH data places $L2239 at 0x007A6160
    $L1933 (Code/GameEngine/Source/Common/OpaqueScalarDeletingDtorsB18.cpp): $L1933 was renumbered; verified parent EH data places $L2309 at 0x007A6144
STLport folds: 1 complete emitted constructor(s) verified against retail owners and resolved callees
Functions: OK 78/78 matched across 4 source file(s)
String-ref verify: OK (2 literals + 0 empty-string refs verified, 0 baselined, 0 unverified/skipped)
Float-ref verify: OK (0 compiler literals verified)
Import-ref verify: OK (0 named imports verified)
```

The fresh published index was fetched through `link_check.py --fetch-index`.
The subsequent ordinary four-unit preview is:

```text
Compile: 0 of 1 TU(s) (deps-cache: 1 current)
Compile: 0 of 1 TU(s) (deps-cache: 1 current)
Compile: 0 of 1 TU(s) (deps-cache: 1 current)
Compile: 0 of 1 TU(s) (deps-cache: 1 current)
Code/GameEngine/Source/Common/Rva0053805DBaseDtor.cpp: LINKS  LINKED 179 -> 179 bytes (census 2026-11-04 05:53 at 5a13f2cd61; file's own bytes 179)
Code/GameEngine/Source/Common/OpaqueScalarDeletingDtorsB18.cpp: LINKS  LINKED 736 -> 736 bytes (census 2026-11-04 05:53 at 5a13f2cd61; file's own bytes 736)
Code/GameEngine/Source/GameLogic/System/LivingWorld/LivingWorldBuildPlot.cpp: LINKS  LINKED 676 -> 676 bytes (census 2026-11-04 05:53 at 5a13f2cd61; file's own bytes 676)
Code/GameEngine/Source/GameLogic/System/LivingWorld/LivingWorldLogicCtorBfme.cpp: LINKS  LINKED 815 -> 815 bytes (census 2026-11-04 05:53 at 5a13f2cd61; file's own bytes 815)
link_check: 4 of 4 link cleanly; LINKED 2,406 -> 2,406 bytes (4.9s)
```

Acceptance was repeated after that index refresh; all four still pass.
This is a local prediction preserving existing linking, not a new census or
a claim of additional linked bytes. Normal commit/push hooks remain required.

## Remaining cohort

The eleven remaining queue entries require member/cleanup reconciliation,
not another identical automatic swap. Constructor-emitting views use a
12-byte vector or Header base instead of the canonical three scalar slots;
SecondaryBase uses a private release helper; Rva0053947DDtor obtains forEach
through its private base; Rva005D4C61Dtor and Rva005A71B1Dtor couple explicit
freeing with containing-member teardown. BuildPlot's ambiguity is resolved
only for the retained unit by qualifying the canonical destructor field;
the similarly named fields elsewhere must be treated at their own bindings.

Initial automatic-trial diagnostics (all failed candidates restored):

```text
  FAIL Code/GameEngine/Source/Common/OpaqueScalarDeletingDtorsB18.cpp: FAIL ??1Rva005FCF0E@@UAE@XZ (Code/GameEngine/Source/Common/OpaqueScalarDeletingDtorsB18.cpp) (fields: Rva00330757Member::begin -> field00)
  FAIL Code/GameEngine/Source/Common/Rva0053805DBaseDtor.cpp: FAIL ??1Rva0053805DBase@@UAE@XZ (Code/GameEngine/Source/Common/Rva0053805DBaseDtor.cpp) (fields: Rva00330757Member::m_begin -> field00, Rva00330757Member::m_capacity -> field08, Rva00330757Member::m_end -> field04, Rva00330757Member::m_index -> field0C)
  FAIL Code/GameEngine/Source/Common/Rva0053947DDtor.cpp: Code\GameEngine\Source\Common\Rva0053947DDtor.cpp(76) : error C3861: 'forEach': identifier not found, even with argument-dependent lookup
  FAIL Code/GameEngine/Source/Common/Rva00578AC1.cpp: field renames: Rva00330757Member::m_items (+0x0, 12 bytes) has no canonical field of that offset and size
  FAIL Code/GameEngine/Source/Common/Rva005D4C61Dtor.cpp: field renames: m_begin at line 35 is not proven a member of Rva00330757Member; refusing rather than guessing
  FAIL Code/GameEngine/Source/Common/System/Rva005A71B1Dtor.cpp: FAIL ??1Rva005A71B1@@UAE@XZ (Code/GameEngine/Source/Common/System/Rva005A71B1Dtor.cpp) (fields: Rva00330757Member::m_begin -> field00, Rva00330757Member::m_capacity -> field08, Rva00330757Member::m_end -> field04, Rva00330757Member::m_flags -> field0C)
  FAIL Code/GameEngine/Source/GameLogic/Map/SidesListCtor.cpp: field renames: Rva00330757Member::m_items (+0x0, 12 bytes) has no canonical field of that offset and size
  FAIL Code/GameEngine/Source/GameLogic/Object/Behavior/Rva00330757Member.cpp: field renames: Rva00330757Member::m_items (+0x0, 12 bytes) has no canonical field of that offset and size
  FAIL Code/GameEngine/Source/GameLogic/Object/Behavior/SecondaryBase.cpp: Code\GameEngine\Source\GameLogic\Object\Behavior\SecondaryBase.cpp(14) : error C2039: 'release' : is not a member of 'Rva00330757Member' (fields: Rva00330757Member::buffer -> field00)
  FAIL Code/GameEngine/Source/GameLogic/System/ArmySummaryCopyBFME2.cpp: field renames: Rva00330757Member::m_items (+0x0, 12 bytes) has no canonical field of that offset and size
  FAIL Code/GameEngine/Source/GameLogic/System/LivingWorld/LivingWorldBuildPlot.cpp: field renames: Code/GameEngine/Source/GameLogic/System/LivingWorld/LivingWorldBuildPlot.cpp: m_begin is also a member of Rva004FC320List; a token rename would reach it
  FAIL Code/GameEngine/Source/GameLogic/System/LivingWorld/LivingWorldBuilding.cpp: field renames: /work4/Open-BFME-2/vendor/stlport/config/stl_dec_vms.h:50: trigraph or continued line comment in include input
  FAIL Code/GameEngine/Source/GameLogic/System/LivingWorld/LivingWorldLogicCtorBfme.cpp: field renames: Rva00330757Member::storage (+0x0, 16 bytes) has no canonical field of that offset and size
  FAIL Code/GameEngine/Source/GameLogic/System/LivingWorld/LivingWorldPlayer.cpp: field renames: Code/GameEngine/Source/GameLogic/System/LivingWorld/LivingWorldPlayer.cpp: flag is also a member of Rva002BA8F1Input; a token rename would reach it
  FAIL Code/GameEngine/Source/GameLogic/System/LivingWorld/LivingWorldRegionConstructor.cpp: field renames: /work4/Open-BFME-2/vendor/stlport/config/stl_dec_vms.h:50: trigraph or continued line comment in include input
```
