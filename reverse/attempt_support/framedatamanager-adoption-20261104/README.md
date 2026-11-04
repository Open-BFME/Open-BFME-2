# FrameDataManager adoption, 2026-11-04

Inspected source revision: `372e613e52`. Published census index:
`5a13f2cd61`, 2026-11-04 02:25. This is header-debt cleanup, not a new census.

## Applied reset consumer

`ConnectionManager_reset.cpp` adopts the existing FrameDataManager,
NetCommandList and ConnectionManager headers. No shared header changes.
The canonical ConnectionManager field names replace its private field names.
The already-rowed `Rva004D060B` destructor view remains necessary for connection
elements: deleting the canonical forward-declared Connection directly would
omit the destructor call to RVA 0x004D060B. Its identity remains unresolved.

Target bytes in reset at RVA 0x004D0669 show the frame-data loop loading the
vptr, pushing zero, calling slot zero, pushing EAX and calling global delete.
`::delete m_frameData[i]` emits that exact sequence. Ordinary `delete` instead
passes flag one and omits the global delete call; explicit destruction followed
by global deletion reloads the pointer and changes the body by one byte.
Global delete syntax removes the old fictitious virtual `destroy` method.
The NetCommandList private byte array was used only to establish allocation
size; the canonical 16-byte class preserves that allocation and its call targets.

Verification:

- `./build.sh Code/GameEngine/Source/GameNetwork/ConnectionManager_reset.cpp`:
  all five function/EH rows match. Three renumbered unwind labels are located
  by the exact parent's EH graph, not edited in the ledger.
- `find_declared_unmatched.py` on both inspected sources: all definitions rowed.
- `header_adopt_lane.py accept` separately for FrameDataManager, NetCommandList
  and ConnectionManager: each passes and retires its one reset-source queue row.
- Ordinary two-source `link_check.py`: reset LINKS, 438 -> 438 authored bytes;
  unchanged FrameDataManagerDtor LINKS, 282 -> 282. Combined 720 -> 720.
  These previews preserve existing linking; no headline increase is claimed.

## Blocked lifetime provider

The lane's unchanged header swap in `FrameDataManagerDtor.cpp` fails the complete
destructor at RVA 0x0058B623 (67 bytes) and constructor at 0x0058B567 (113 bytes).
The canonical class derives from MemoryPoolObject, whose inline empty virtual
destructor introduces base cleanup EH state. The destructor starts with an EH
prologue rather than retail's `push esi; push edi; mov esi,ecx; xor edi,edi`.
The constructor acquires an additional saved-this stack slot and EH state.
Adding `/Ob2` leaves both mismatches unchanged. The original source was restored;
no nonmatching body or new compiler override remains under Code/.

The failed candidate was only the lane's unmodified header swap; reproduce with
`header_adopt_lane.py adopt --class FrameDataManager --header
Code/GameEngine/Include/GameNetwork/FrameDataManagerClass.h
Code/GameEngine/Source/Common/FrameDataManagerDtor.cpp` (without `--apply`).
No donor layout or name is inferred from these byte comparisons.

Next: establish the base lifetime/exception contract against retail before a
shared-header change; coordinate with the broader MemoryPoolObject issues in
LINK-188. Then recheck both lifetime bodies, every compiler-emitted companion,
and consumers together. The provider's header-queue row remains registered.
