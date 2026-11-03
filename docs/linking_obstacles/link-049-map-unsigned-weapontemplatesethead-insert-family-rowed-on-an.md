### LINK-049: map<unsigned, WeaponTemplateSetHead> insert family rowed on an int-key placeholder and a private tree view
Status: Repair landed, awaiting census. Updated: 2026-10-26; inspected revision: a8fa0b2df4.
Evidence / affected units: `StlSweepW4Rva00464431.cpp` (0x00464431, 29 B) was rowed as
`map<int, Rva00464431Element>::insert` and failed on an unresolved element copy ctor and a
non-retail local `insert_unique` COMDAT. Target facts: its only caller 0x00464923 compares the key
with jae and memsets a 0x4C-byte value (already spelled `map<unsigned, WeaponTemplateSetHead>`
there and pinned in symbols.csv); 0x00464431 calls 0x00463E4D, whose chain 0x0046383F and
0x004637B7 was rowed as `Rva00463782::rva*` view members.
Completed: the four bodies are now the `_Rb_tree<unsigned, pair<const unsigned,
WeaponTemplateSetHead> >` members they are: `map::insert` and both `insert_unique`s from the
template, `_M_insert` as an explicit specialization keeping the rowed create provider; the caller
takes `map::insert` decl-only. Two dead pins retracted. A pointer-to-member cast in place of a direct
call changed MSVC's tail merging in the 294-byte hinted insert (300 B), so convert by renaming the
callee rather than casting to it.
Remaining / next check: 0x004634BA (`Rva004634BACreate`) and 0x00462D83 (`_Construct<Rva0046267A>`)
are still the placeholder spelling of this tree's `_M_create_node` and element construct.
Clearance: `tools/link_check.py` on the five units: LINKS (661 -> 690 bytes), 5/5 rows exact.
Census confirmation: awaiting the next census.
