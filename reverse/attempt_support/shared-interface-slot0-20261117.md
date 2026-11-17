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
The adjusting thunk is banked separately against its existing owner in
GapForwardersSeat8.cpp. The ordinary build then verifies all seventeen rows;
the callback and its adjustment each have their own commit.

This is source/provider repair, not a published bridge-retirement result.
Only a later published real-link receipt can confirm which bridges leave.

After publishing both bodies, StrategicInGameUI.cpp drops its old slot0-to-step
alternatename. The real shared member now supplies that binding directly.
Its ordinary build verifies all seventy current rows, and a private A/B retains
all eighty-six COMDATs identically. The global hatch register was claimed by
another worker, so this change leaves its old allowance untouched rather than
editing that worker's register scope. The source has one fewer alias.

The second callback, slot1, is now defined beside slot0. The native body at
0x005E415F loads the owned pointer at +0x10 and tail-calls 0x005E4116.
The existing consumer alias independently ties that body to slot1. Reading
child.value from the already-proven shared layout produces the same complete
eight bytes and relocation as the old helper. Its callback result is unused;
the tail call retains the provider's machine return value. add_match admits
the byte-and-relocation twin against the existing owner in
stlport_map_int_sbserver.cpp. All eighteen source rows remain exact.

The consumer then removes the obsolete slot1 alias as its own change. Its
seventy rows and all eighty-six COMDATs again remain identical. Both shared
callbacks now bind directly to real rowed members; the consumer has two fewer
alternatename directives. The held global hatch register remains untouched.
