### LINK-171: retiring a link-wide `vectorSmallAllocate` alternatename unresolved two consumers (2026-11-01, seat halilkkaya-lk12)

Status: Cleared (current objects). Base `6b1a8fb85c`; census 12:39 (`39dfbbdb50`).
`d96297b68e` merged stlport_deque_e8_pushback_aux.cpp into SimpleObjectIterator.cpp and dropped its
`/alternatename:?vectorSmallAllocate@_STL@@YAPAXII@Z=?allocate@?$allocator@D@_STL@@SAPADIPBX@Z`
(the merged body now calls `_STL::allocator<char>::allocate` through the bfmealloc shim). The
directive was link-wide (LINK-160 pattern): VP6/DuckMemAlloc.cpp (141 B) and
WWLib/Rva008FB570DequePushBackAux.cpp (123 B), both census-linked, still called the invented
`_STL::vectorSmallAllocate` and became unresolved (index: no definer, two touching objects).
Both now bind the real name of the retail callee, the static
`?allocate@?$allocator@D@_STL@@SAPADIPBX@Z` rowed at 0x000307F0 (GameMemory.cpp), through an
`extern "C" __identifier` declaration (`_STL::allocator` is a registered canonical class, so neither
unit declares a private `allocator<char>`). `./build.sh` 4/4 rows; scoped DIR32 OK (17 symbols, with
GameMemory.cpp); `link_check --refresh` DuckMemAlloc 0 -> 141 B, Rva008FB570DequePushBackAux
0 -> 123 B, GameMemory 316 B unchanged LINKS. Pattern: before retiring any `/alternatename`, list
every object that touches its alias name (index `touches`), not only the directive's own unit.
Census confirmation: awaiting.
