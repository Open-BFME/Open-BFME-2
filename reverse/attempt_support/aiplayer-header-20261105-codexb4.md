# AIPlayer canonical-header adoption, 2026-11-05

Inspected revision: `0d12d0c458` (parent `3510a3e22a`). Claimed class: `AIPlayer`.
The picker served the twelve remaining AIPlayer header-queue consumers.
`find_declared_unmatched.py` passed all twelve before edits. The automatic
`adopt --apply` trial retained no changes: queue pointer conversions, unmatched
padding, constructor head-wrapper types, missing inline iterator/helper methods,
Coord3DBase fields, the AISkirmishPlayer include environment, Snapshot table
redeclaration and the incomplete Player type prevented direct adoption.

Four consumers now include the existing, unchanged `AIPlayerClass.h`:

- `Common/AIPlayer_flip.cpp`: use the existing TeamInQueue layout and its
  ready-list links instead of a private node and private AIPlayer layout.
- `Common/AIPlayer_prependTo_TeamReadyQueue.cpp`: use a typed head pointer.
- `GameLogic/AI/AIPlayer.cpp`: remove the private AIPlayer declaration; its
  implemented methods already use the canonical fields and signatures.
- `GameLogic/AI/Rva004F48D8.cpp`: use canonical fields and slot 26; cast the
  Player pointer to the existing local +0x338 access view, without declaring
  another Player identity or changing the neutral field's meaning.

The fixed header's existing retail-field/slot evidence supplies these identities;
this work adds no donor source-provenance, layout or function-name claim.
No pins, aliases, globals, compiler flags, shared headers, source paths or ledger
rows change. AIPlayer.cpp's two registered data-identity keys remain untouched.

The normal build passes 29/29 code rows across these four consumers plus the
restored destructor control; 16 string references, 19 float references and two
imports pass. All definitions remain rowed. Four header-debt rows are retired
only by `header_adopt_lane.py accept --class AIPlayer` on these consumers.
Their ordinary link preview preserves 4,129/4,129 bytes. This is a preview,
not a new census or real-link measurement.

## Destructor trial: restored

`Rva004F07E6Dtor.cpp` also byte-matches with the canonical header after removing
its explicit Snapshot table declaration and private SnapBase/AIPlayer classes.
Acceptance correctly refuses it: the canonical AIPlayer table introduces eight
unresolved virtual names and conflicts with the first AIPlayer table COMDAT.
The original source was restored and its normal build passed. Its queue row
remains. This refines LINK-484's provider prerequisite; it does not repair the
AISkirmishPlayer lifetime composition. Before retrying either, reconcile the
canonical virtual names and table owner with current providers; do not add
aliases or accept a byte-only destructor result.

The other seven consumers remain unchanged and queued. Their prerequisites
remain the head-wrapper constructor shape, missing iteration/count helpers,
Coord3DBase field reconciliation and AISkirmishPlayer include environment.

## Verification receipts

Index: `c95fcfcfcd`, census 2026-11-05 05:17. Commands use normal scoped builders;
no direct compile API or census/smoke runner was invoked.

### before-build

```text
Source claims: OK (5 sources, scoped byte-verified)
Compile: 1 of 5 TU(s) (deps-cache: 4 current)
Funclet pins: 10 row(s) verified past a renumbered $L label
    Unwind@00b92cee (Code/GameEngine/Source/GameLogic/AI/AIPlayer.cpp): $L4149 was renumbered; verified parent EH data places $L13155 at 0x00792CEE
    Unwind@00b92cf6 (Code/GameEngine/Source/GameLogic/AI/AIPlayer.cpp): $L4150 was renumbered; verified parent EH data places $L13156 at 0x00792CF6
    Unwind@00b92d64 (Code/GameEngine/Source/GameLogic/AI/AIPlayer.cpp): $L3572 was renumbered; verified parent EH data places $L12574 at 0x00792D64
    Unwind@00b92d6c (Code/GameEngine/Source/GameLogic/AI/AIPlayer.cpp): $L3573 was renumbered; verified parent EH data places $L12575 at 0x00792D6C
    Unwind@00b92d74 (Code/GameEngine/Source/GameLogic/AI/AIPlayer.cpp): $L3574 was renumbered; verified parent EH data places $L12576 at 0x00792D74
Functions: OK 29/29 matched across 5 source file(s)
String-ref verify: OK (16 literals + 0 empty-string refs verified, 0 baselined, 0 unverified/skipped)
Float-ref verify: OK (19 compiler literals verified)
Import-ref verify: OK (2 named imports verified)
```

### before-link

```text
Compile: 0 of 1 TU(s) (deps-cache: 1 current)
Compile: 0 of 1 TU(s) (deps-cache: 1 current)
Compile: 0 of 1 TU(s) (deps-cache: 1 current)
Compile: 0 of 1 TU(s) (deps-cache: 1 current)
Compile: 0 of 1 TU(s) (deps-cache: 1 current)
Code/GameEngine/Source/Common/AIPlayer_flip.cpp: LINKS  LINKED 35 -> 35 bytes (census 2026-11-05 05:17 at c95fcfcfcd; file's own bytes 35)
Code/GameEngine/Source/Common/AIPlayer_prependTo_TeamReadyQueue.cpp: LINKS  LINKED 32 -> 32 bytes (census 2026-11-05 05:17 at c95fcfcfcd; file's own bytes 32)
Code/GameEngine/Source/GameLogic/AI/AIPlayer.cpp: LINKS  LINKED 3,983 -> 3,983 bytes (census 2026-11-05 05:17 at c95fcfcfcd; file's own bytes 3,983)
Code/GameEngine/Source/GameLogic/AI/Rva004F48D8.cpp: LINKS  LINKED 79 -> 79 bytes (census 2026-11-05 05:17 at c95fcfcfcd; file's own bytes 79)
Code/GameEngine/Source/GameLogic/AI/Rva004F07E6Dtor.cpp: LINKS  LINKED 79 -> 79 bytes (census 2026-11-05 05:17 at c95fcfcfcd; file's own bytes 79)
link_check: 5 of 5 link cleanly; LINKED 4,208 -> 4,208 bytes (5.9s)
```

### after-build

```text
Source claims: OK (5 sources, scoped byte-verified)
Funclet pins: 10 row(s) verified past a renumbered $L label
    Unwind@00b92cee (Code/GameEngine/Source/GameLogic/AI/AIPlayer.cpp): $L4149 was renumbered; verified parent EH data places $L13263 at 0x00792CEE
    Unwind@00b92cf6 (Code/GameEngine/Source/GameLogic/AI/AIPlayer.cpp): $L4150 was renumbered; verified parent EH data places $L13264 at 0x00792CF6
    Unwind@00b92d64 (Code/GameEngine/Source/GameLogic/AI/AIPlayer.cpp): $L3572 was renumbered; verified parent EH data places $L12682 at 0x00792D64
    Unwind@00b92d6c (Code/GameEngine/Source/GameLogic/AI/AIPlayer.cpp): $L3573 was renumbered; verified parent EH data places $L12683 at 0x00792D6C
    Unwind@00b92d74 (Code/GameEngine/Source/GameLogic/AI/AIPlayer.cpp): $L3574 was renumbered; verified parent EH data places $L12684 at 0x00792D74
Functions: OK 29/29 matched across 5 source file(s)
String-ref verify: OK (16 literals + 0 empty-string refs verified, 0 baselined, 0 unverified/skipped)
Float-ref verify: OK (19 compiler literals verified)
Import-ref verify: OK (2 named imports verified)
```

### accept

```text
  PASS Code/GameEngine/Source/Common/AIPlayer_flip.cpp
  PASS Code/GameEngine/Source/Common/AIPlayer_prependTo_TeamReadyQueue.cpp
  PASS Code/GameEngine/Source/GameLogic/AI/AIPlayer.cpp
  PASS Code/GameEngine/Source/GameLogic/AI/Rva004F48D8.cpp
  FAIL Code/GameEngine/Source/GameLogic/AI/Rva004F07E6Dtor.cpp: link_check predicts a loss of census-linked bytes
  retired 4 row(s) from reverse/header_queue.tsv; commit it with the adoption
```

### after-link

```text
Compile: 0 of 1 TU(s) (deps-cache: 1 current)
Compile: 0 of 1 TU(s) (deps-cache: 1 current)
Compile: 0 of 1 TU(s) (deps-cache: 1 current)
Compile: 0 of 1 TU(s) (deps-cache: 1 current)
Code/GameEngine/Source/Common/AIPlayer_flip.cpp: LINKS  LINKED 35 -> 35 bytes (census 2026-11-05 05:17 at c95fcfcfcd; file's own bytes 35)
Code/GameEngine/Source/Common/AIPlayer_prependTo_TeamReadyQueue.cpp: LINKS  LINKED 32 -> 32 bytes (census 2026-11-05 05:17 at c95fcfcfcd; file's own bytes 32)
Code/GameEngine/Source/GameLogic/AI/AIPlayer.cpp: LINKS  LINKED 3,983 -> 3,983 bytes (census 2026-11-05 05:17 at c95fcfcfcd; file's own bytes 3,983)
Code/GameEngine/Source/GameLogic/AI/Rva004F48D8.cpp: LINKS  LINKED 79 -> 79 bytes (census 2026-11-05 05:17 at c95fcfcfcd; file's own bytes 79)
link_check: 4 of 4 link cleanly; LINKED 4,129 -> 4,129 bytes (4.3s)
```

### dtor-trial-link

```text
Compile: 0 of 1 TU(s) (deps-cache: 1 current)
Code/GameEngine/Source/GameLogic/AI/Rva004F07E6Dtor.cpp: does not link  LINKED 79 -> 0 bytes (census 2026-11-05 05:17 at c95fcfcfcd; file's own bytes 79)
  unresolved  ?GetSnapshotName@AIPlayer@@MBEPBDXZ
  unresolved  ?checkBridges@AIPlayer@@UAE_NPAVObject@@PAVWaypoint@@@Z
  unresolved  ?getAiEnemy@AIPlayer@@UAEPAVPlayer@@XZ
  unresolved  ?isSkirmishAI@AIPlayer@@UAE_NXZ
  unresolved  ?loadPostProcess@AIPlayer@@MAEXXZ
  unresolved  ?newMap@AIPlayer@@UAEXXZ
  unresolved  ?selectSkillset@AIPlayer@@UAEXH@Z
  unresolved  ?vslot26@AIPlayer@@MAEXXZ
  comdat      ??_7AIPlayer@@6B@  (first: differs from the first copy in link order (no retail address))
link_check: 0 of 1 link cleanly; LINKED 79 -> 0 bytes (5.0s)
```

### dtor-restored-build

```text
Source claims: OK (1 sources, scoped byte-verified)
Functions: OK 2/2 matched across 1 source file(s)
String-ref verify: OK (0 literals + 0 empty-string refs verified, 0 baselined, 0 unverified/skipped)
Float-ref verify: OK (0 compiler literals verified)
Import-ref verify: OK (0 named imports verified)
```
