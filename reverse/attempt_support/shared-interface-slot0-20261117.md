# Restore the shared interface callback and its native adjustment

The default picker serves nine bridged tables in Rva005CDVirtualDtors.cpp,
starting at table RVA 0x0087501C. Its first pointer targets native thunk
0x005CDA53, which subtracts eight from this and jumps to callback 0x005E5554.
The matched constructor/destructor hierarchy declares that callback as
Rva005E4F6D::slot0; the missing definition is already linked to the old
Rva005E5554::step spelling by an existing StrategicInGameUI.cpp alternatename.

The real slot0 definition calls the same qualified helper at 0x005E549E
and tail-calls the existing run provider at 0x005F327A through the receiver
eight bytes earlier. Its complete seventeen bytes and both relocations are
identical to the existing rowed step body. add_match admits that twin against
its owner with fold-proof. No new pin, alias, class name or layout is added.

MSVC naturally emits the existing eight-byte secondary-base adjusting thunk
under the proper slot0 decoration when it compiles this complete hierarchy.
A private probe verifies both bodies and all fifteen pre-existing source rows.
The ordinary build after callback admission verifies sixteen rows.
The adjusting thunk is to be banked separately against its existing owner.

This is source/provider repair, not a published bridge-retirement result.
The cohort still has other unresolved virtual surfaces, including slot1.
Only a later published real-link receipt can confirm which bridges leave.
