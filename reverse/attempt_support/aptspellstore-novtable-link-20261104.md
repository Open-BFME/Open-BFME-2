# AptSpellStore forwarding-destructor link repair

Inspected revision: `320fac87ed7c0e4575201c4c4617f78176ba7f2d`.
Source: `Code/GameEngine/Source/GameClient/GUI/AptSpellStore.cpp`.

## Target facts and history

Commit `48d25c26438cd7156322c479b2786db12a920d44` removed
`novtable` from this unit's `Rva0043D16F` view while normalizing class
spellings. The view defines a force-inline destructor that delegates to
`Rva0043D193::~Rva0043D193` (retail RVA `0x0043D193`). Its constructor
is only declared here; the row at `0x0043D16F` belongs to
`Code/GameEngine/Source/Common/Rva0043D16FCtor.cpp` and installs the vtable.
The existing handoff at `reverse/re_attempts.log` (the AptSpellStore
consolidation entry beginning `TU consolidation AptSpellStore.cpp: merged 3
donors`) already distinguishes the constructor's vptr store from this
forwarding destructor's lack of a store.

Before the repair, normal byte verification passes 16/16, but
`python3 tools/link_check.py Code/GameEngine/Source/GameClient/GUI/AptSpellStore.cpp`
fails with exactly these two unresolved symbols:

```
?v00@Rva0043D16F@@UAE_NW4ScienceType@@@Z
?v04@Rva0043D16F@@UAEHXZ
```

## Change and verification

Restore `__declspec(novtable)` only on the forwarding view. This suppresses
its incidental vtable and vptr write; the out-of-line constructor and the
rowed destructor remain the existing providers. No donor source was used,
and no class identity, ledger extent, pin or alias changes.

- `./build.sh Code/GameEngine/Source/GameClient/GUI/AptSpellStore.cpp`:
  16/16 matched; nine string literals verified; all ten funclet rows verified
  through their parent's EH mapping despite compiler-label renumbering.
- `python3 tools/find_declared_unmatched.py` for the source:
  all defined functions already matched.
- `python3 tools/eh_verify.py` for the source: EXACT 1, zero not exact.
- `python3 tools/link_check.py` for the source: 1/1 links cleanly, own
  authored scope 1,137 bytes. Before the edit the same preview reports
  1,137 -> 0; after it reports 1,137 -> 1,137 against the census baseline.
- Census index: `2026-11-04 07:28`, revision `a62ac1c10b`; fetching the
  published index retained that same local index.
- Reading the rebuilt object's external symbols with
  `link_census.object_symbols` finds only the constructor and destructor
  names containing `Rva0043D16F`, with neither missing virtual method nor
  its vtable emitted.
- `git diff --check`: clean.

This is a scoped link prediction, not a new census or real-link measurement.
The next real-link run must confirm removal of this unit's two blockers.
