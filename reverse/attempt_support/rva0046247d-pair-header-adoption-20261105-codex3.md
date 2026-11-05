# Rva0046247DPair canonical header adoption

Inspected revision: `c1d9595ba93972152654cc482911ad790f75dc4f`. Date: 2026-11-05.
Claim owner: `yasinschroeder-codex3`; scope: `class:Rva0046247DPair` and the
picker-selected 17-consumer cohort.

Replaced all 17 queued private pair declarations with the existing
`Code/GameEngine/Include/GameLogic/Module/Rva0046247DPair.h`.
The header's target evidence fixes the record at eight bytes: the null-preserving
ContainModuleInterface pointer at +0 and the opaque list pointer at +4.
Consumers retain their existing list views through explicit casts. Local field
spellings map by those offsets; no original field or element name is inferred.
The canonical header and public function identities are unchanged.

Verification:

- `find_declared_unmatched.py` succeeds before and after for all 17 sources.
  The pre-existing absent-from-retail anchor in the pair provider is unchanged.
- `./build.sh` verifies 228/228 matched rows across 17 sources, including
  funclet parent evidence and the existing STLport fold.
- `header_adopt_lane.py accept --class Rva0046247DPair` passes all 17 consumers.
  It retired 15 rows in the initial pass and the remaining two after the local
  helper assignments wrote the opaque pointer without a const-qualified list cast.
  Only the owning acceptance tool changed `reverse/header_queue.tsv`.
- `check_csv.py` and `git diff --check` pass.
- Ordinary current-object link previews before and after preserve
  32,489/32,489 census-linked bytes; all 17 units link cleanly. Index:
  2026-11-05 05:17 at `c95fcfcfcd`. This is a scoped preview, not a new census
  or real-game link measurement. Existing unreferenced COMDAT diagnostics remain
  non-blocking. No new link obstacle or changed prerequisite was observed.

## Changed sources

- `Code/GameEngine/Source/Common/Rva0046247DCondPair.cpp`
- `Code/GameEngine/Source/GameLogic/Object/Contain/GarrisonContainOnRemoving.cpp`
- `Code/GameEngine/Source/GameLogic/Object/Contain/HordeContain/HordeTransportContain.cpp`
- `Code/GameEngine/Source/GameLogic/Object/Contain/HordeContain/HordeTransportContainNestedRiders.cpp`
- `Code/GameEngine/Source/GameLogic/Object/Contain/HordeContainApplyUpgradeMask.cpp`
- `Code/GameEngine/Source/GameLogic/Object/Contain/HordeContainAveragePosition.cpp`
- `Code/GameEngine/Source/GameLogic/Object/Contain/HordeContainIface11CSlots.cpp`
- `Code/GameEngine/Source/GameLogic/Object/Contain/HordeContainRva0046A10D.cpp`
- `Code/GameEngine/Source/GameLogic/Object/Contain/HordeContainRva0046C7A4.cpp`
- `Code/GameEngine/Source/GameLogic/Object/Contain/HordeContainRva0046FC1B.cpp`
- `Code/GameEngine/Source/GameLogic/Object/Contain/OpenContain_redeployOccupants.cpp`
- `Code/GameEngine/Source/GameLogic/Object/Contain/Rva0046333BCounts.cpp`
- `Code/GameEngine/Source/GameLogic/Object/Contain/Rva00466C94.cpp`
- `Code/GameEngine/Source/GameLogic/Object/Contain/Rva0046DA6BDraw.cpp`
- `Code/GameEngine/Source/GameLogic/Object/Contain/SlaughterHordeContainRva004642D3.cpp`
- `Code/GameEngine/Source/GameLogic/Object/Contain/TransportContainRiders.cpp`
- `Code/GameEngine/Source/GameLogic/Object/HordeMeleeAmoebaXfer.cpp`

## Byte verification

```text
Source claims: OK (17 sources, scoped byte-verified)
Compile: 3 of 17 TU(s) (deps-cache: 14 current)
Funclet pins: 22 row(s) verified past a renumbered $L label
    $L3706 (Code/GameEngine/Source/GameLogic/Object/Contain/SlaughterHordeContainRva004642D3.cpp): $L3706 was renumbered; verified parent EH data places $L3715 at 0x0078AAB4
    Unwind@00b8b279 (Code/GameEngine/Source/GameLogic/Object/Contain/HordeContainIface11CSlots.cpp): $L39567 was renumbered; verified parent EH data places $L44797 at 0x0078B279
    Unwind@00b8b281 (Code/GameEngine/Source/GameLogic/Object/Contain/HordeContainIface11CSlots.cpp): $L39568 was renumbered; verified parent EH data places $L44798 at 0x0078B281
    Unwind@00b8af11 (Code/GameEngine/Source/GameLogic/Object/Contain/HordeContainIface11CSlots.cpp): $L26105 was renumbered; verified parent EH data places $L30756 at 0x0078AF11
    Unwind@00b8afa8 (Code/GameEngine/Source/GameLogic/Object/Contain/HordeContainIface11CSlots.cpp): $L26146 was renumbered; verified parent EH data places $L30797 at 0x0078AFA8
STLport folds: 1 complete emitted constructor(s) verified against retail owners and resolved callees
Functions: OK 228/228 matched across 17 source file(s)
String-ref verify: OK (17 literals + 4 empty-string refs verified, 0 baselined, 0 unverified/skipped)
Float-ref verify: OK (67 compiler literals verified)
Import-ref verify: OK (0 named imports verified)
```

## Final acceptance

```text
  PASS Code/GameEngine/Source/Common/Rva0046247DCondPair.cpp
  PASS Code/GameEngine/Source/GameLogic/Object/Contain/GarrisonContainOnRemoving.cpp
  PASS Code/GameEngine/Source/GameLogic/Object/Contain/HordeContain/HordeTransportContain.cpp
  PASS Code/GameEngine/Source/GameLogic/Object/Contain/HordeContain/HordeTransportContainNestedRiders.cpp
  PASS Code/GameEngine/Source/GameLogic/Object/Contain/HordeContainApplyUpgradeMask.cpp
  PASS Code/GameEngine/Source/GameLogic/Object/Contain/HordeContainAveragePosition.cpp
  PASS Code/GameEngine/Source/GameLogic/Object/Contain/HordeContainIface11CSlots.cpp
  PASS Code/GameEngine/Source/GameLogic/Object/Contain/HordeContainRva0046A10D.cpp
  PASS Code/GameEngine/Source/GameLogic/Object/Contain/HordeContainRva0046C7A4.cpp
  PASS Code/GameEngine/Source/GameLogic/Object/Contain/HordeContainRva0046FC1B.cpp
  PASS Code/GameEngine/Source/GameLogic/Object/Contain/OpenContain_redeployOccupants.cpp
  PASS Code/GameEngine/Source/GameLogic/Object/Contain/Rva0046333BCounts.cpp
  PASS Code/GameEngine/Source/GameLogic/Object/Contain/Rva00466C94.cpp
  PASS Code/GameEngine/Source/GameLogic/Object/Contain/Rva0046DA6BDraw.cpp
  PASS Code/GameEngine/Source/GameLogic/Object/Contain/SlaughterHordeContainRva004642D3.cpp
  PASS Code/GameEngine/Source/GameLogic/Object/Contain/TransportContainRiders.cpp
  PASS Code/GameEngine/Source/GameLogic/Object/HordeMeleeAmoebaXfer.cpp
  retired 2 row(s) from reverse/header_queue.tsv; commit it with the adoption
```

## Final current-object preview

```text
Compile: 0 of 1 TU(s) (deps-cache: 1 current)
Compile: 0 of 1 TU(s) (deps-cache: 1 current)
Compile: 0 of 1 TU(s) (deps-cache: 1 current)
Compile: 0 of 1 TU(s) (deps-cache: 1 current)
Compile: 0 of 1 TU(s) (deps-cache: 1 current)
Compile: 0 of 1 TU(s) (deps-cache: 1 current)
Compile: 0 of 1 TU(s) (deps-cache: 1 current)
Compile: 0 of 1 TU(s) (deps-cache: 1 current)
Compile: 0 of 1 TU(s) (deps-cache: 1 current)
Compile: 0 of 1 TU(s) (deps-cache: 1 current)
Compile: 0 of 1 TU(s) (deps-cache: 1 current)
Compile: 0 of 1 TU(s) (deps-cache: 1 current)
Compile: 0 of 1 TU(s) (deps-cache: 1 current)
Compile: 0 of 1 TU(s) (deps-cache: 1 current)
Compile: 0 of 1 TU(s) (deps-cache: 1 current)
Compile: 0 of 1 TU(s) (deps-cache: 1 current)
Compile: 0 of 1 TU(s) (deps-cache: 1 current)
Code/GameEngine/Source/Common/Rva0046247DCondPair.cpp: LINKS  LINKED 26 -> 26 bytes (census 2026-11-05 05:17 at c95fcfcfcd; file's own bytes 26)
Code/GameEngine/Source/GameLogic/Object/Contain/GarrisonContainOnRemoving.cpp: LINKS  LINKED 717 -> 717 bytes (census 2026-11-05 05:17 at c95fcfcfcd; file's own bytes 717)
Code/GameEngine/Source/GameLogic/Object/Contain/HordeContain/HordeTransportContain.cpp: LINKS  LINKED 2,362 -> 2,362 bytes (census 2026-11-05 05:17 at c95fcfcfcd; file's own bytes 2,362)
  diagnostic  ??XVector3@@QAEAAV0@M@Z  (codegen-like: 40 of 51 bytes differ from the majority copy; unreferenced, not a blocker)
  diagnostic  ?deallocate@?$_STLP_alloc_proxy@PAU?$_List_node@H@_STL@@U12@V?$allocator@U?$_List_node@H@_STL@@@2@@_STL@@QAEXPAU?$_List_node@H@2@I@Z  (codegen-like: 5 bytes against the majority copy's 20; unreferenced, not a blocker)
Code/GameEngine/Source/GameLogic/Object/Contain/HordeContain/HordeTransportContainNestedRiders.cpp: LINKS  LINKED 133 -> 133 bytes (census 2026-11-05 05:17 at c95fcfcfcd; file's own bytes 133)
Code/GameEngine/Source/GameLogic/Object/Contain/HordeContainApplyUpgradeMask.cpp: LINKS  LINKED 471 -> 471 bytes (census 2026-11-05 05:17 at c95fcfcfcd; file's own bytes 471)
Code/GameEngine/Source/GameLogic/Object/Contain/HordeContainAveragePosition.cpp: LINKS  LINKED 628 -> 628 bytes (census 2026-11-05 05:17 at c95fcfcfcd; file's own bytes 628)
Code/GameEngine/Source/GameLogic/Object/Contain/HordeContainIface11CSlots.cpp: LINKS  LINKED 23,871 -> 23,871 bytes (census 2026-11-05 05:17 at c95fcfcfcd; file's own bytes 23,871)
Code/GameEngine/Source/GameLogic/Object/Contain/HordeContainRva0046A10D.cpp: LINKS  LINKED 409 -> 409 bytes (census 2026-11-05 05:17 at c95fcfcfcd; file's own bytes 409)
Code/GameEngine/Source/GameLogic/Object/Contain/HordeContainRva0046C7A4.cpp: LINKS  LINKED 904 -> 904 bytes (census 2026-11-05 05:17 at c95fcfcfcd; file's own bytes 904)
Code/GameEngine/Source/GameLogic/Object/Contain/HordeContainRva0046FC1B.cpp: LINKS  LINKED 638 -> 638 bytes (census 2026-11-05 05:17 at c95fcfcfcd; file's own bytes 638)
  diagnostic  ??0Rva002ED236Pos@@QAE@ABUCoord3D@@@Z  (codegen-like: 28 bytes against the majority copy's 25; unreferenced, not a blocker)
  diagnostic  ??A?$vector@MV?$allocator@M@_STL@@@_STL@@QAEAAMI@Z  (codegen-like: 15 bytes against the majority copy's 12; unreferenced, not a blocker)
Code/GameEngine/Source/GameLogic/Object/Contain/OpenContain_redeployOccupants.cpp: LINKS  LINKED 77 -> 77 bytes (census 2026-11-05 05:17 at c95fcfcfcd; file's own bytes 77)
Code/GameEngine/Source/GameLogic/Object/Contain/Rva0046333BCounts.cpp: LINKS  LINKED 151 -> 151 bytes (census 2026-11-05 05:17 at c95fcfcfcd; file's own bytes 151)
Code/GameEngine/Source/GameLogic/Object/Contain/Rva00466C94.cpp: LINKS  LINKED 173 -> 173 bytes (census 2026-11-05 05:17 at c95fcfcfcd; file's own bytes 173)
Code/GameEngine/Source/GameLogic/Object/Contain/Rva0046DA6BDraw.cpp: LINKS  LINKED 258 -> 258 bytes (census 2026-11-05 05:17 at c95fcfcfcd; file's own bytes 258)
Code/GameEngine/Source/GameLogic/Object/Contain/SlaughterHordeContainRva004642D3.cpp: LINKS  LINKED 200 -> 200 bytes (census 2026-11-05 05:17 at c95fcfcfcd; file's own bytes 200)
Code/GameEngine/Source/GameLogic/Object/Contain/TransportContainRiders.cpp: LINKS  LINKED 809 -> 809 bytes (census 2026-11-05 05:17 at c95fcfcfcd; file's own bytes 809)
Code/GameEngine/Source/GameLogic/Object/HordeMeleeAmoebaXfer.cpp: LINKS  LINKED 662 -> 662 bytes (census 2026-11-05 05:17 at c95fcfcfcd; file's own bytes 662)
link_check: 17 of 17 link cleanly; LINKED 32,489 -> 32,489 bytes (5.7s)
```
