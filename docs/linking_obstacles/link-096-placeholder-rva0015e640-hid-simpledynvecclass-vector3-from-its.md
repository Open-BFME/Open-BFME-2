### LINK-096: placeholder `Rva0015E640` hid `SimpleDynVecClass<Vector3>` from its copy-ctor consumers
Status: Repair landed / awaiting verification for the WW3D2 subset; Blocked for
`V3PolyDeferredCopyCtors2.cpp`. Updated: 2026-10-26; inspected revision: `7e7a10015d`
(index 2026-10-26 19:02 at `5ce093a71a`).
Evidence / affected units: the copy ctor 0x0015E640 and implicit assignment
0x0015E670 were rowed as `Rva0015E640`, whose private vptr classes left
`??1Rva0015E640Base`/`??1Rva0015E640` unresolved in
`V3PolyDeferredCopyCtors2.cpp`, `Rva001684D6Copy.cpp` and `Rva001684D6Assign.cpp`.
The body installs vtables 0x007C6F44/0x007C6F50, whose slots are the rowed
`SimpleVecClass<Vector3>`/`SimpleDynVecClass<Vector3>` deleting dtors and `Resize`
(target fact). The 39-byte copy ctor at 0x00741BF0, formerly rowed as the Vector3
instance, installs 0x007D71C8/0x007D71D4, the Vector4 vtables (slots 0x1A7FF0,
0x1AC6C0). It is `SimpleDynVecClass<Vector4>`'s and is emitted by `streak.cpp`.
Completed: the consumers use the real `SimpleDynVecClass<Vector3>`. segline.cpp owns
0x0015E640/0x0015E670 under the real names; the placeholder rows have tombstones.
0x00741BF0 is rowed as the Vector4 copy ctor. All 30 sources using the template
pass (675/675 rows). Without the `SimpleVecClass<Vector3>`/`SimpleDynVecClass<Vector3>`
lines, the DIR32 consistency check passes over the same rows, so the whitelist
drops both. Preview: `Rva001684D6Copy.cpp`, `Rva001684D6Assign.cpp`, `segline.cpp`
and `streak.cpp` link (LINKED 9,905 -> 9,944).
Update 2026-10-27: `V3PolyDeferredCopyCtors2.cpp` no longer lacks
`??1Rva0028C62B`/`??1Rva0028F68F`. Its copy-ctor classes are the default-ctor
classes `Rva00263653` and `Rva00263895Member`, which store the same one-slot
vftables. The slots (0x004D6FC4/0x004D6F86) are their virtuals, and neither class
has a virtual dtor. link_check: the unit goes 0 -> 216 B LINKS, and the seven
provider/consumer units still link (LINKED 2,282 -> 2,498 at index `bf3dd31211`).
The real DamageInfo names are still open (LINK-004). `reverse/data_ledger.csv` still lists the old vtable
alias names until it is next regenerated.
Clearance: pending.
Census confirmation: awaiting the next census.
