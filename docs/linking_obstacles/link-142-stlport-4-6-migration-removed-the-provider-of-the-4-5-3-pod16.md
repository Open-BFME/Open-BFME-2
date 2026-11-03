### LINK-142: STLport 4.6 migration removed the provider of the 4.5.3 Pod16 map node allocate (2026-10-29, seat yasinschroeder-claudeb2)

Status: repaired, pending census confirmation. The 2026-10-29 census lists
stlport_map_int_pod16_subscript.cpp linked=no with one unresolved name,
`?allocate@?$allocator@U?$_Rb_tree_node@U?$pair@$$CBHUBfmePod16@@@_STL@@@_STL@@@_STL@@QBEPAU...@IPBX@Z`
(the const 4.5.3 signature, an ICF fold onto 0x005DFB2C in reverse/symbols.csv).
Its own `_M_create_node` copy calls that allocate through the proxy. That copy must
stay visible, because re_log 0x00257252 shows that a declaration-only
`_M_create_node` reorders the parent's rep movsd. The 840db2d676 index's only
provider was Rva0041355DParse.cpp (fold-proof), which emits the non-const 4.6
signature after 9fcc9c90dc. Repair: the unit's body-less allocate declaration
is now a dllimport+forceinline specialization with the vendor body, as the file
already does for `__malloc_alloc` and `less<int>`. The object no longer
references the name. 3/3 rows are exact, and the remaining externals are
`_Rb_global`, `_S_oom_malloc` and `_malloc`. The pin stays consistent
(`pin_consistency.py --symbol`); its fold-proof source still names Parse.cpp.
