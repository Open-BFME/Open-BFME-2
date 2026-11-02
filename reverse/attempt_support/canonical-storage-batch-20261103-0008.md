# 8 verified BFME2 declaration cleanup and queue item(s)

Base `c55cddf26377555521449e646a4cc1efb04db6f9`. 2 separately claimed source units replace private
storage definitions with existing registered headers. 4 other source units adopt real standard headers or remove redundant declarations already supplied by existing headers. 2 other
item(s) refresh already-completed queue evidence without changing source.
Normal gates preserve 137 native function/EH rows, 18631 ledger-extent
bytes, 255 retained external code bodies/relocation lists and
11 named TU-local code definitions. No new native rows, names,
pins, aliases, shared headers or baselines are authored. No optimization or ABI switches change.
No native/authored-byte or runtime improvement is claimed.

- [Adopt canonical Coord3D in RebuildHoleBehavior](rebuildholebehavior-coord3d-20261103-0008.md): 7 existing rows, 53 retained external definitions.
- [Adopt canonical ICoord2D in Rva002ECE6AInfoCtor](rva002ece6ainfoctor-icoord2d-20261103-0008.md): 2 existing rows, 8 retained external definitions.
- [Use real Microsoft declarations in EAStringCConcat](eastringcconcat-microsoft-headers-20261103-0008.md): 16 existing rows, 13 retained external definitions.
- [Use real Microsoft declarations in AptMovieFrameControls](aptmovieframecontrols-microsoft-headers-20261103-0008.md): 20 existing rows, 15 retained external definitions.
- [Refresh completed Microsoft-header key for InGameHeroSelectInterface](ingameheroselectinterface-microsoft-headers-20261103-0008.md): 32 existing rows, 78 retained external definitions.
- [Repair PlayerInitFromDict include inventory and refresh its completed Microsoft key](playerinitfromdict-microsoft-headers-20261103-0008.md): 31 existing rows, 46 retained external definitions.
- [Refresh completed Microsoft-header key for PolygonTrigger](polygontrigger-microsoft-headers-20261103-0008.md): 26 existing rows, 38 retained external definitions.
- [Remove redundant scalar-delete declaration in MeshModelReset](meshmodelreset-microsoft-headers-20261103-0008.md): 3 existing rows, 4 retained external definitions.

Each unit has its own before-object and normal/frozen checks. Source changes
also have isolated private compiles and complete non-debug section comparisons.
Storage adoptions use owning header acceptance. Standard declaration cleanup
and already-completed Microsoft-header keys use the native scoped Microsoft
header scan. No external code is added or removed in this batch. Named statics
are compared separately; generated EH labels are covered by runtime sections
and native parent EH checks.

Owning acceptance retires 0 source/class queue row(s); strict preparation and new-variant checks pass.

9 related unclaimed allocation-header candidates are deferred after the shared header probe exposed placement-definition, exception-contract and linker-directive prerequisites. They were not independently attempted and are not counted. No new header guard, library-selection workaround or checker relaxation is landed.

Unsuccessful trial, not counted as completion: [b2-03](b2-03-storage-prerequisite-20261103-0008.md). Original source untouched; claim released.

Unsuccessful trial, not counted as completion: [b2-04](b2-04-storage-prerequisite-20261103-0008.md). Original source untouched; claim released.

Unsuccessful trial, not counted as completion: [b2-10](b2-10-storage-prerequisite-20261103-0008.md). Original source untouched; claim released.

Bounded preview, not a fresh census or complete current selection:

```text
Compile: 0 of 1 TU(s) (deps-cache: 1 current)

Compile: 0 of 1 TU(s) (deps-cache: 1 current)

Compile: 0 of 1 TU(s) (deps-cache: 1 current)

Compile: 0 of 1 TU(s) (deps-cache: 1 current)

Compile: 0 of 1 TU(s) (deps-cache: 1 current)

Compile: 0 of 1 TU(s) (deps-cache: 1 current)

Compile: 0 of 1 TU(s) (deps-cache: 1 current)

Compile: 0 of 1 TU(s) (deps-cache: 1 current)

Code/GameEngine/Source/GameLogic/Object/Behavior/RebuildHoleBehavior.cpp: LINKS  LINKED 1,198 -> 1,198 bytes (census 2026-11-02 08:35 at 984a4cdc4d; file's own bytes 1,198)

Code/GameEngine/Source/GameLogic/Pathfinder/Rva002ECE6AInfoCtor.cpp: LINKS  LINKED 699 -> 699 bytes (census 2026-11-02 08:35 at 984a4cdc4d; file's own bytes 699)

Code/Libraries/Source/EA/Apt/AptString/EAStringCConcat.cpp: LINKS  LINKED 1,790 -> 1,790 bytes (census 2026-11-02 08:35 at 984a4cdc4d; file's own bytes 1,790)

Code/Libraries/Source/Apt/AptMovieFrameControls.cpp: LINKS  LINKED 3,546 -> 3,546 bytes (census 2026-11-02 08:35 at 984a4cdc4d; file's own bytes 3,546)

Code/GameEngine/Source/GameClient/GUI/InGame/Tactical/InGameHeroSelectInterface.cpp: LINKS  LINKED 4,890 -> 4,890 bytes (census 2026-11-02 08:35 at 984a4cdc4d; file's own bytes 4,890)

Code/GameEngine/Source/Common/RTS/PlayerInitFromDict.cpp: LINKS  LINKED 4,707 -> 4,707 bytes (census 2026-11-02 08:35 at 984a4cdc4d; file's own bytes 4,707)

Code/GameEngine/Source/GameLogic/Map/PolygonTrigger.cpp: LINKS  LINKED 999 -> 999 bytes (census 2026-11-02 08:35 at 984a4cdc4d; file's own bytes 999)

Code/Libraries/Source/WWVegas/WW3D2/MeshModelReset.cpp: LINKS  LINKED 214 -> 214 bytes (census 2026-11-02 08:35 at 984a4cdc4d; file's own bytes 214)

link_check: 8 of 8 link cleanly; LINKED 18,043 -> 18,043 bytes (2.9s)
```

## Parallel and sequential execution

The two independent repositories use separate source trees, object caches,
ledgers and claim namespaces; their working processes can run concurrently.
BUILD_POOL=14 per repository, aggregate28 build workers on28 logical CPUs.
Within one repository, source installation, normal verification, queue/log
writes, staging and commits are serialized. Private compilations are safe to
parallelize only with distinct objects and stable shared inputs; they do not
authorize simultaneous shared-cache or ledger writes. Dependent canonical-header
changes precede consumers and require their own wider gate. Publications follow
each repository's native workflow and account clock. No local inference or GPU
job is needed. No serial-vs-parallel speedup benchmark is claimed.

Full engine link, gameplay and RAM/leak/crash/FPS gains remain unproven.

Immutable outgoing audit at `c55cddf26377555521449e646a4cc1efb04db6f9` -> `d5b1e0e5cdf53bb9d1bd4957668476cf03a82440` before this documentation-only amendment, exit2:

```text
link batch audit: INCONCLUSIVE baseline: index at 984a4cdc4d, outgoing base c55cddf26377555521449e646a4cc1efb04db6f9; findings below are provisional since-index changes
link batch audit: INCONCLUSIVE: 1 source object(s) lack current receipts; first: Code/GameEngine/Source/Common/RTS/PlayerInitFromDict.cpp
```

## Include-inventory follow-up

The initial audit's own-source missing receipt for PlayerInitFromDict is
explained by its whole-checkout include root. The bounded repair removes that
redundant root, anchors the same header, and preserves every native row and
complete non-debug section. The eight tasks now comprise two canonical-storage
adoptions, three standard-declaration cleanups, one include-inventory repair
and two maintenance-only queue refreshes. The initial audit above is retained
as history; the follow-up audit below supersedes its own-source finding.

Follow-up audit at `f9d80791fbee55243090c30df3e52da0ea323503`, exit 2:

```text
link batch audit: INCONCLUSIVE baseline: index at 984a4cdc4d, outgoing base c55cddf26377555521449e646a4cc1efb04db6f9; findings below are provisional since-index changes
link batch audit: INCONCLUSIVE: affected consumer lacks current receipt: Code/GameEngine/Source/Common/0CreateAHeroManager21FE49.cpp
```
