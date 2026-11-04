# MixFileInfoBuffer header adoption, 2026-11-04

Inspected source revision: `8b0291f7968187908f13c1f80dfa13481a9b030b`.

Replaced six private class views with the existing canonical header. The header and its target-layout evidence are unchanged. Typed accesses now use its existing field names: links at +0x34/+0x38, costs at +0x10/+0x12, coordinates at +0/+4 and five pointer slots at +0x14. Other classes' coordinate accesses are unchanged. The unlink definition adopts the header's nonthrowing declaration.

The generic adoption tool refused padding overlays and ambiguous token replacements; the manual edits resolve each receiver explicitly. An obsolete comment claiming a sibling helper was unrowed was removed; that helper already lives in MixFileInfoBuffer.cpp. No code row or alias was removed.

The ordinary link preview is scoped to these units against the published index (8661f15284, 2026-11-03 20:03). Its difference from that census includes intervening work; it is not an attributed linking gain or a new census. No real-link, smoke or ownership measurement was run.

## Byte verification

```text
Source claims: OK (6 sources, scoped byte-verified)
Data rows: OK (6 row(s) byte-verified)
Compile: 2 of 6 TU(s) (deps-cache: 4 current)
Funclet pins: 6 row(s) verified past a renumbered $L label
    uw_007972fc (Code/GameEngine/Source/Common/MixFileInfoBuffer.cpp): $L359 was renumbered; verified parent EH data places $L595 at 0x007972FC
    uw_00778e0a (Code/GameEngine/Source/GameLogic/AI/AIPathfind.cpp): $L4142 was renumbered; verified parent EH data places $L14423 at 0x00778E0A
    uw_00778e1c (Code/GameEngine/Source/GameLogic/AI/AIPathfind.cpp): $L5747 was renumbered; verified parent EH data places $L14436 at 0x00778E1C
    Unwind@00b78d8f (Code/GameEngine/Source/GameLogic/AI/AIPathfind.cpp): $L698 was renumbered; verified parent EH data places $L14627 at 0x00778D8F
    Unwind@00b78d97 (Code/GameEngine/Source/GameLogic/AI/AIPathfind.cpp): $L699 was renumbered; verified parent EH data places $L14628 at 0x00778D97
Functions: OK 114/114 matched across 6 source file(s)
String-ref verify: OK (7 literals + 0 empty-string refs verified, 0 baselined, 0 unverified/skipped)
Float-ref verify: OK (28 compiler literals verified)
Import-ref verify: OK (5 named imports verified)
```

## Header queue acceptance

```text
  PASS Code/GameEngine/Source/Common/MixFileInfoBuffer.cpp
  PASS Code/GameEngine/Source/Common/MixFileInfoBufferUnlink.cpp
  PASS Code/GameEngine/Source/Common/Rva002F5925InfoRva002F5925.cpp
  PASS Code/GameEngine/Source/GameLogic/AI/AIPathfind.cpp
  PASS Code/GameEngine/Source/GameLogic/Object/PathfinderPosGoalManager.cpp
  PASS Code/GameEngine/Source/GameLogic/Pathfinder/PathfinderRva002F83F5Neighbors.cpp
  retired 6 row(s) from reverse/header_queue.tsv; commit it with the adoption
```

## Link preview

```text
Compile: 0 of 1 TU(s) (deps-cache: 1 current)
Compile: 0 of 1 TU(s) (deps-cache: 1 current)
Compile: 0 of 1 TU(s) (deps-cache: 1 current)
Compile: 0 of 1 TU(s) (deps-cache: 1 current)
Compile: 0 of 1 TU(s) (deps-cache: 1 current)
Compile: 0 of 1 TU(s) (deps-cache: 1 current)
Code/GameEngine/Source/Common/MixFileInfoBuffer.cpp: LINKS  LINKED 179 -> 179 bytes (census 2026-11-03 20:03 at 8661f15284; file's own bytes 179)
Code/GameEngine/Source/Common/MixFileInfoBufferUnlink.cpp: LINKS  LINKED 34 -> 34 bytes (census 2026-11-03 20:03 at 8661f15284; file's own bytes 34)
Code/GameEngine/Source/Common/Rva002F5925InfoRva002F5925.cpp: LINKS  LINKED 851 -> 851 bytes (census 2026-11-03 20:03 at 8661f15284; file's own bytes 851)
Code/GameEngine/Source/GameLogic/AI/AIPathfind.cpp: LINKS  LINKED 4,228 -> 5,069 bytes (census 2026-11-03 20:03 at 8661f15284; file's own bytes 5,069)
  diagnostic  ?deallocate@?$allocator@U?$_Rb_tree_node@H@_STL@@@_STL@@QBEXPAU?$_Rb_tree_node@H@2@I@Z  (codegen-like: 21 bytes against the majority copy's 20; unreferenced, not a blocker)
  diagnostic  ?deallocate@?$allocator@U?$_Rb_tree_node@U?$pair@$$CBII@_STL@@@_STL@@@_STL@@QBEXPAU?$_Rb_tree_node@U?$pair@$$CBII@_STL@@@2@I@Z  (codegen-like: 21 bytes against the majority copy's 20; unreferenced, not a blocker)
  diagnostic  ?deallocate@?$_STLP_alloc_proxy@PAU?$_Rb_tree_node@H@_STL@@U12@V?$Rva002F0C32Allocator@H@@@_STL@@QAEXPAU?$_Rb_tree_node@H@2@I@Z  (codegen-like: 21 bytes against the majority copy's 5; unreferenced, not a blocker)
  diagnostic  ?_M_erase@?$_Rb_tree@HHU?$_Identity@H@_STL@@U?$less@H@2@V?$Rva002F0C32Allocator@H@@@_STL@@AAEXPAU?$_Rb_tree_node@H@2@@Z  (codegen-like: 46 bytes against the majority copy's 48; unreferenced, not a blocker)
  diagnostic  ?deallocate@?$_STLP_alloc_proxy@PAU?$_Rb_tree_node@U?$pair@$$CBII@_STL@@@_STL@@U12@V?$allocator@U?$_Rb_tree_node@U?$pair@$$CBII@_STL@@@_STL@@@2@@_STL@@QAEXPAU?$_Rb_tree_node@U?$pair@$$CBII@_STL@@@2@I@Z  (codegen-like: 21 bytes against the majority copy's 20; unreferenced, not a blocker)
  diagnostic  ??1?$_Rb_tree_base@HV?$Rva002F0C32Allocator@H@@@_STL@@QAE@XZ  (codegen-like: 15 bytes against the majority copy's 10; unreferenced, not a blocker)
  diagnostic  ??1?$_Rb_tree@HHU?$_Identity@H@_STL@@U?$less@H@2@V?$Rva002F0C32Allocator@H@@@_STL@@QAE@XZ  (codegen-like: 57 bytes against the majority copy's 54; unreferenced, not a blocker)
Code/GameEngine/Source/GameLogic/Object/PathfinderPosGoalManager.cpp: LINKS  LINKED 669 -> 669 bytes (census 2026-11-03 20:03 at 8661f15284; file's own bytes 669)
Code/GameEngine/Source/GameLogic/Pathfinder/PathfinderRva002F83F5Neighbors.cpp: LINKS  LINKED 1,799 -> 1,799 bytes (census 2026-11-03 20:03 at 8661f15284; file's own bytes 1,799)
link_check: 6 of 6 link cleanly; LINKED 7,760 -> 8,601 bytes (6.3s)
```
