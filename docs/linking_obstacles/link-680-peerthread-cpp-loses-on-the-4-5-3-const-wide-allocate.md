### LINK-680: `PeerThread.cpp` loses on the 4.5.3 const wide allocate once its row moved to 4.6's name

Status: Repair landed / awaiting census. Updated: 2026-11-15; inspected revision: `bb93a2a56e`.
Evidence / affected units: `Code/GameEngine/Source/GameNetwork/GameSpy/Thread/PeerThread.cpp`
(18,622 authored bytes, 174 rows) left the census at 2026-11-05 04:07 (`c2a9f8e0d7`) and is still
out at 2026-11-15 08:36 (`331df3e3ff`) on one name, `?allocate@?$allocator@G@_STL@@QBEPAGIPBX@Z`.
Retail's wide allocate is one 29-byte /O2 body at 0x00017710. `126057036b` (2026-11-04) moved
`stlport_wide_string.cpp` to STLport 4.6 and tombstoned the const (QBE) row in favour of 4.6's
non-const `?allocate@?$allocator@G@_STL@@QAEPAGIPBX@Z` in `_STL.cpp`. The const name then had no
retail address, so the `first` rule replaced the retail rule: of the two 4.5.3 units still emitting
it, `Render2DSentenceBuildThaiBFME2.cpp` (first in link order, /O2, bytes equal to 0x00017710) kept
its copy and `PeerThread.cpp`'s /O1 copy (415222b68de7) lost. Under the retail rule the same /O1
copy had not lost, because the kept first copy was proven retail's.
Completed: `Render2DSentenceBuildThaiBFME2.cpp` moved to STLport 4.6 (`// stlport46`, const dropped
from its one `allocator<unsigned short>::deallocate` declaration). 5/5 rows exact and re-admitted
through `add_match.py` with `migrated=stlport-4.6`. Its object now emits the non-const name (digest
97338804e347, equal to retail outside the one relocation field) and no longer emits the const
name, `__stl_alloc_rebind<G,G>` or the two `_STLP_alloc_proxy<G*>` helpers. `PeerThread.cpp` is
unchanged and is now the const name's only copy. Preview against index `bb93a2a56e`:
`PeerThread.cpp` LINKS 0 -> 18,622; the Thai unit keeps 2,191; all 13 other census objects touching
a changed name keep linking, among them `stlport_wide_money_get_string.cpp`,
`stlport_wide_money_put_string.cpp` and `stlport_wide_num_put_bool.cpp`, which declare the const
allocate declaration-only and now resolve it to `PeerThread.cpp`'s copy.
Rejected on the way: an inline-only (`dllimport __forceinline`) const allocate in `PeerThread.cpp`
changes `PeerThreadClass::Thread_Function`'s bytes; a direct 4.6 move of `PeerThread.cpp` stops at
`_string.h(552)`, where 4.6's range append calls `allocate(n)` and the 4.6 `bfmealloc` port's static
`allocator<char>::allocate(n, hint)` has no default hint.
Remaining / next check: `PeerThread.cpp` is the last provider of the const name. Whoever moves it
to 4.6 must first move the three declaration-only users above (their calls then name the rowed
non-const body), or they become unresolved (the LINK-140 pattern).
Clearance: preview only, scope the 15 objects checked (the Thai unit and the 14 census objects touching a changed name).
Census confirmation: awaiting.
