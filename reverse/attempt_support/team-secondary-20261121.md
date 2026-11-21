# Team secondary vtable

The authoritative run at 073c9f4f013 bridges 0x0081AEB8. The native Team
constructor and destructor objects each emit a four-byte table containing
only the matched secondary deleting thunk. The retail secondary table has
17 slots. The primary Snapshot table has four slots.

The existing Team.cpp now supplies exact independently emitted bodies for
slots 2 and 14 through 16. The 180-row scoped build, 16 exact EH graphs
and seven-source link preview passed. The shared Team header now uses
Rva002EE9B7 for its +0x130 ObjectID set. The shared-header gate verified
3,130 function rows in 208 dependents. A temporary substitution in the
queued constructor, using the same typed set, preserved all ten existing
rows and its exact EH graph.

A second diagnostic used the existing physical +0x48 bucket-table member
shape, the typed +0x130 set and the complete secondary base declaration in
TeamCtor.cpp. It again passed 10/10 and exact EH. COFF binds its actual
17-slot table to 0x0081AEB8. Slots 0, 2, 5, 12, 14, 15 and 16 identify
their exact retail rows. Slots 1, 3, 4, 6, 7, 8, 9, 10 and 11 need the
existing matched bodies under the canonical secondary base symbols. Slot
13 reveals a distinct return-type key mismatch: the trial emits
`?getLocation@Team@@UBE?AUCoord3D@@XZ`. The exact 101-byte row at 0x0039D7DB
uses `?getLocation@Team@@UBE?AVCoord3D@@XZ`. See
[LINK-018](../../docs/linking_obstacles/link-018-canonical-coord3d-member-growth-blocks-header-adoption-until.md)
for the shared Coord3D class-key prerequisites.

The supported slot 1 virtual conversion at 0x0055AFA3 passed dry run. Its
prepared owner must leave the deleting destructor at slot 0, and the
qualified base caller and existing AIBuildableUnit binding need verification.
That conversion alone does not resolve the shared header's slot 1 name.

Team+0x48 uses AsciiString keys with a byte-sized mapped value. The same
0x003A393A initializer also serves a differently typed relation-map member.
Team's direct destructor at 0x003A2EBD and the constructor's 0x00781A2A
cleanup via 0x003A354A are distinct from the other member's destructor.
The +0x130 constructor cleanup at 0x00781A43 still uses a separate five-byte
forwarder at 0x002F0F02. That generated 14-byte scaffold stayed in its
existing row. Ordinary EH verification alone does not establish that its
compiler-generated replacement would preserve the immediate callee.

The diagnostic constructor was restored and rebuilt successfully. The
shared +0x44 AsciiString, +0x48 hash table and +0x12C list lifetimes, the
destructor and deleter adoption, and the remaining slot identities still
block retirement. Trial sources and logs are under
`build/root-resume-20261120/team-secondary/` in the isolated r20 worktree.
