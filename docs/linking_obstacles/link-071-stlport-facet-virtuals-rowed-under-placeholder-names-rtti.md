### LINK-071: STLport facet virtuals rowed under placeholder names (RTTI vftable slots)

**Status: Open. Updated: 2026-10-26; inspected revision: 13cb4119f9.**

- **Evidence / scope:** `tools/vtable_slots.py _STL` names every STLport vftable by RTTI.
  Slots 4 and 5 of `numpunct<char>` (0x007BBB78) hold 0x00017A40 / 0x00017AA0 and of
  `numpunct<wchar_t>` (0x007BBB94) 0x00017B00 / 0x00017B30: `do_truename` / `do_falsename`.
  They are rowed as `?init@Rva00017A40StringInit@@...` (and siblings) in
  `stlport_narrow_string_range_ctors.cpp` and `Rva00017B00StringInit.cpp`, reading
  address-named 12-byte globals (0x009DEEF0..0x009DEF38, `g_Va00DDEF08` and the like in
  `Rva007AB8D0StringInits.cpp` / `Rva007B6880Thunks.cpp`). `stlport_numpunct_virtuals.cpp`
  (44 B, 4 rows) defines the real `do_truename` / `do_falsename`, unrowed, and does not link:
  its `_M_truename` / `_M_falsename` statics of both specializations are unresolved.
  Same slot test also shows the wide `moneypunct` string getters (0x00019D90, slots 4-6 of
  0x007BC868 / 0x007BC894) rowed as the placeholder `?init@Rva00019D90StringInit@@QAEPAXPAX@Z`
  in `Code/GameEngine/Source/Common/Rva00017B00StringInit.cpp`.
- **Completed:** the same shape for slot 0 of `basic_ios<wchar_t>` (0x007BBCFC):
  437bc30603 repointed 0x00013490 from `??_GRva00013490Element` to
  `??_G?$basic_ios@GV?$char_traits@G@_STL@@@_STL@@UAEPAXI@Z` in `stlport_wide_ios.cpp`
  (link_check 296 -> 326 B) and removed the never-linking split unit.
  ea8aaf453c renamed `collate<char>` slot 2 (0x00017890, vftable 0x007BBB50) from
  `?init@Rva00017890StringInit@@` to `?do_transform@?$collate@D@_STL@@MBE...PBD0@Z` in place in
  `stlport_narrow_string_range_ctors.cpp` and removed the two `/alternatename` hatches that bound
  the real name to the placeholder (`stlport_classic_locale.cpp`,
  `stlport_locale_facet_subclass_dtors.cpp`); 5/5 units still LINK, bytes unchanged.
  cf40575e42 renamed 0x00019D30 (slot 3 of `moneypunct<char,true>` 0x007BC810; the same body
  fills slots 3-6 of both narrow moneypuncts and slot 3 of both wide ones) from
  `?init@Rva00019D30StringInit@@` to `?do_grouping@?$moneypunct@D$00@_STL@@MBE...XZ`; the
  moneypunct ctor/dtor units drop that name's hatch and point the other nine folded names at
  it instead of the placeholder. 5/5 units still LINK, bytes unchanged. Those nine hatches stay
  until the folded aliases get their own rows (one body per name would emit unrowed EH
  handlers/funclets).
- **Remaining / next check:** give the six 12-byte strings their STLport names
  (`?_M_truename@?$numpunct@D@_STL@@1V?$basic_string@...@2@A` etc.) through
  `tools/name_globals.py` / the data lane, then repoint the four slot rows to the real
  `do_truename` / `do_falsename` names and check `stlport_numpunct_virtuals.cpp` against
  them. Needs claims on both placeholder units and the data owners.
- **Census confirmation:** awaiting the next census for 437bc30603.
