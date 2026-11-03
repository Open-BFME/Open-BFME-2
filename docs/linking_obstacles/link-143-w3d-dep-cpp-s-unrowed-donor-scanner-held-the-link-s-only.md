### LINK-143: w3d_dep.cpp's unrowed donor scanner held the link's only string-list helpers (2026-10-29, seat yasinschroeder-claudeb2)

Status: repaired, pending census confirmation. The 2026-10-29 census lists
w3d_dep.cpp linked=no. Its one unresolved name, `??0ChunkLoadClass@@QAE@PAVFileClass@@@Z`,
comes from the Generals dependency scanner (Get_W3D_Dependencies and its Scan_*
helpers), which has no row. Retail's constructor takes `BFMEChunkInput *` (0x614EF0).
The scanner also emitted the only copies of `_S_sort`, `_S_merge`, `_S_unique`, the
node proxy `swap`, the `_List_base` constructor and destructor and `_M_create_node`
for `list<basic_string<char>>`, and linked stlport_list_string_erase_00424363.cpp
declares those without a body (the reversed 2026-10-26 trial above). A rebuilt
current-object scan finds no other unit referencing any of the scanner's 20 sole
definitions. Repair:
- stlport_list_string_erase_00424363.cpp drops those seven suppressions, plus
  the list constructor, destructor and splice that its new `_S_sort` and
  `_S_merge` copies call. Its explicit instantiation now emits all of them.
- That unit declares `less<string>::operator()` without a body: it is rowed at
  0x00389117 in stlport_rb_tree_hint_0038d58c.cpp. Otherwise `_S_merge` inlines
  `operator<`, which emits a non-retail `_M_compare` COMDAT that link_check
  rejects.
- w3d_dep.cpp keeps only its `operator==` row.

Results: both units are exact (4/4 and 1/1), and the only externals the new
objects leave without a provider are CRT EH helpers. `link_check.py` on both
current objects predicts LINKS for both (LINKED 96 -> 143 bytes against index
840db2d676).
