# AptOnlineCustomMatch interface table 0x008713AC

Served 2026-11-16 from `reverse/vtable_bridge_queue.tsv`
(`??_7AptOnlineCustomMatch@@6BRva0059EB41@@@`, 12 bytes, sources
`Code/GameEngine/Source/GameClient/GUI/GUICallbacks/Apt/AptOnlineCustomMatchCtor.cpp` and
`...Dtor.cpp`).

## Verdict

Blocked on the interface class, not a local slot edit.

The ctor's placeholder `Rva0059EB41` (the 4-byte interface at `AptOnlineCustomMatch+0x6C`) declares
two empty three-argument virtuals and a virtual destructor. Its emitted table therefore holds
0x000D1407 (shared empty `ret 12`) in slots 0/1 and a deleting destructor in slot 2. Retail's table
at 0x008713AC holds:

- 0x0059EF57 twice: an 11-byte `this -= 0x6C` forwarder to `AptOnlineCustomMatch::UpdatePings`
  (0x0059ED8B), rowed as `?rva0059EF57@Rva0059EF57@@QAEXHHH@Z` in `GapForwardersSeat8.cpp`;
- 0x005A00DE: the this-adjusting (-0x6C) deleting-destructor thunk of `Rva005A0009`, rowed in
  `OpaqueScalarDeletingDtorsB14.cpp`.

The two callbacks are only reachable as virtual overrides of the interface; a vtable slot cannot
point at another class's non-virtual free/forwarder body without an ICF fold-proof. The placeholder
also spells the parameters `(void *, void *, void *)` while the retail row spells `(int, int, int)`.
The prerequisite is a canonical interface class with the real two virtuals and the outer-class
adjustment (or an accepted fold-proof for 0x59EF57), plus the matching deleting-dtor thunk. None of
that is a change to the placeholder declarations.

No source change was made.
