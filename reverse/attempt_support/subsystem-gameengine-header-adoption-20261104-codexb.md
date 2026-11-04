# GameEngine consumers adopt SubsystemInterfaceList, 2026-11-04

Inspected revision: `3ff6f61ef5c02a4e7a3c443dad30bfb88afa83b3`.
The default picker claimed SubsystemInterfaceList, its existing header and
GameEngineInit.cpp, GameEngineSlots.cpp and System/SubsystemInterface.cpp.

## Completed

GameEngineInit.cpp now includes Common/SubsystemInterfaceList.h instead of
declaring an opaque 0x24-byte prefix and m_xfer. The canonical header's
three vectors occupy that prefix and retain the +0x24 transfer pointer.
Its allocation and field accesses byte-match without changing the header.
The unused rva001B4EAB declaration disappears with the private class; the
actual call already uses the existing Rva001B4EAB receiver view.

GameEngineSlots.cpp uses the same header. Its private inline rva001B5140
wrapper previously forwarded to Rva001B5140::rva001B5140, whose existing
row at 0x001B5140 lives in System/SubsystemInterface.cpp. The caller now
performs that same receiver cast directly. This preserves the rowed helper
identity without adding a method, pin or alias to the canonical class.
No recovered semantic name is asserted for that helper.

## Verification

- ./build.sh on both consumers: 113/113 function rows exact, one data row
  exact; literal, float and import checks pass. Existing funclet labels
  are verified through parent EH data after compiler renumbering.
- find_declared_unmatched.py before and after: all defined functions already
  matched; the existing GameEngineInit.cpp informational note is unchanged.
- header_adopt_lane.py accept --class SubsystemInterfaceList on both files:
  PASS/PASS, exactly two header_queue.tsv entries retired by the owning tool.
- Joint link_check.py preview: GameEngineInit.cpp LINKS 9,424 -> 9,424 bytes;
  GameEngineSlots.cpp LINKS 128 -> 128 bytes. Census index: f12552d0a7,
  2026-11-04 20:47. These are previews, not a new linking census.
- check_csv.py: OK (99,452 function rows, 9,328 symbol rows, 2,268 data rows).
- link_check.py --prepare-current: both explicit safe providers byte-verified
  with strict reusable receipts; no census/index/status changes.

The staged-tree link_batch_audit.py exits 2 after receipt preparation:

    INCONCLUSIVE baseline: index at f12552d0a7, outgoing base HEAD
    INCONCLUSIVE: affected consumer lacks current receipt:
    Code/GameEngine/Source/Common/0CreateAHeroManager21FE49.cpp

This is the same missing consumer receipt recorded by the earlier donor
adoptions. Full provider/consumer preservation remains unverified. Carry
these two consumers and their affected provider/consumer closure into the
next scheduled census/current-receipt audit. No direct census or smoke
runner was invoked and no broader linking clearance is claimed.

## Remaining prerequisite

The automatic adoption trial still refuses System/SubsystemInterface.cpp's
vector<BfmePod8> field versus the canonical pair vector. No seed source,
shared header, function ledger, symbol pin or source path is changed.
Its queue row remains. The seed's previously documented constructor and
destructor helper bindings must be reconciled before retrying that adoption
or the TU merge; no new seed reconstruction was attempted here.
