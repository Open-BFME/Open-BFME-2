### LINK-036: StlportVectorEraseRangeDeferred historical blockers resolved by landed providers
Status: Repair verified after later consumer-identity regression; awaiting census. Updated: 2026-11-01; inspected index: 0d24c60eef.
Evidence / affected units: `Code/Libraries/Source/WWVegas/WWLib/StlportVectorEraseRangeDeferred.cpp`,
`reverse/link_status.csv` reported unresolved blockers from census `2026-10-25 13:53 at 51fde01dff`.
Completed: Verified unit against current objects; external callee dependencies have landed on master.
Remaining / next check: None.
Clearance: `tools/link_check.py Code/Libraries/Source/WWVegas/WWLib/StlportVectorEraseRangeDeferred.cpp`
reports: LINKS (0 -> 2,464 bytes). Full 59/59 matched rows verified.
Census confirmation: awaiting the next census.

Later identity-regression repair (2026-11-01): the unit's sole blocker was its stale GameWindow-list copy4703B1 declaration after that false identity was retracted and the pooled Object-list family readmitted. Native4758F4->474125->4703B1->46F0C2 proves the pooled target. Bind its existing global Rva001EB984PoolAllocator<Object*> specialization, retaining the opaque caller element view. All59rows and strict71/71provider rows pass; all80 emitted code definitions retain identical bytes with only the one intended relocation renamed. Preview3/3LINKS restores0->2464B while copy76B and Horde1761B remain linked (1837->4301). No new row/pin/hatch/path move or original allocator-name claim. This is prospective scope, not a new census result. Evidence: reverse/attempt_support/vector-erase-pooled-binding-20261101/readme.md and receipts. Earlier fb1a2e8d59 broad audit remains INCONCLUSIVE on missing0CreateAHeroManager21FE49 receipt; carry affected consumers into the next census.

**Original-family identity follow-up (2026-10-27, inspected `f643d446a0`):**
[The whole-source check](../../reverse/attempt_support/vector-erase-family-identity-20261027.md)
binds the 24-byte `_Destroy<TreeHintRef00217D4C *>` at 0x005F97BC to
the existing `Rva004F72EDDestroy` owner at 0x004F72ED, preserving its native
unused third cdecl argument. All 14 source rows and its EH graph remain
exact. The owning retirement tool removes 22 source keys (21 stale after
earlier row moves, one repaired binding), retaining the two wrong copy-helper
bindings at 0x0007A7AA and 0x003F6975. Inline-forwarding trials for those
two changed the empty-tag stack layout and were reverted and recorded.
Next: reconcile visible helper bodies and owner signatures together before
retrying. The original source and three providers preview LINKS for the
same 800 authored bytes against index `bf3dd31211`; this retires debt with
no new census-linked-byte gain. The moved destinations were not changed
or cleared by this source-scoped retirement.
