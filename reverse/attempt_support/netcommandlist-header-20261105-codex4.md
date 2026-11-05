# NetCommandList consumer header adoption

Base: `3f98ce70cbe7c7052f7d4c59fdb16ed90797d804`, 2026-11-05.

Replace three private NetCommandList declarations with the existing canonical
`Code/GameEngine/Include/GameNetwork/NetCommandListClass.h`. The frame-list
consumer's explicit vfptr becomes the header's native virtual destructor.
The resend consumer casts the canonical head to its existing local node view;
its message/next/relay accesses and traversal remain unchanged. No shared
header, function identity, alias, pin, compiler flag or ledger row changes.

| Consumer under Code/GameEngine/Source/GameNetwork/ | Matched rows | Ordinary preview bytes |
| --- | ---: | ---: |
| Connection.cpp | 22 | 1,688 -> 1,688 LINKS |
| ConnectionManagerFrameList.cpp | 1 | 148 -> 148 LINKS |
| ConnectionManager_rva004D00BB.cpp | 2 | 221 -> 221 LINKS |

Verification:

- `find_declared_unmatched.py` before/after: all defined functions matched.
- `./build.sh` on the three consumers: 25/25 function rows and one data row
  pass; three float literals and five named import references pass. Existing
  Connection EH labels are resolved through the verified parent graph.
- Rebuild the original Connection source through `./build.sh` before comparing
  its object: its initial cached object still used the historical unrelated
  NetFrameCommandMsg::getOriginalFrame spelling. Compare the freshly built
  original and adopted objects, never that stale object.
- `link_census.object_facts` and `object_references` compare equal before/after
  for all three objects: all 58 external COMDAT names, body/relocation digests,
  sizes and bindings; exclusive definitions, undefined symbols, weak bindings,
  relocation roots and reference edges are retained. No provider disappears.
  Scratch comparison: `build/netcommandlist-adoption-before/comparison.json`.
- One cohort `header_adopt_lane.py accept --class NetCommandList` passes all
  three and retires exactly their three header-queue rows. A second acceptance
  confirms the final objects after the original/adopted comparison rebuild.
- Ordinary `link_check.py` previews preserve 2,057/2,057 census-linked bytes,
  using the published 2026-11-05 15:19 index at `f44cbcf5b0`. This is not a
  new census, real link or game-run result.

The fourth served consumer, Rva0025E5F4RelayCommands.cpp, remains unchanged
with its queue row. The ordinary adoption trial restores it after C2440:
canonical m_first is NetCommandRef*, while traversal uses a local node view.
It also calls a private `destroy(0)` slot then global delete; the canonical
header exposes protected virtual destruction instead. Reconcile that lifetime
access and traversal together before adopting it; no alias or header access
change is part of this pass. Broader Connection/NetPacket/NetCommandRef
composition prerequisites in the existing obstacle entry remain outside scope.
