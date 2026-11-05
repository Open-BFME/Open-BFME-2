### LINK-594: stock-allocator `basic_string<char>::reserve` COMDAT beat retail's copy (boot crash in initializers)
Status: Repair landed / awaiting verification. Updated: 2026-11-05; inspected revision: b93e4864a9.
Evidence / affected units: the diagnostic image from `3973ef8ec5` (queue receipt
`2026-11-05T221341Z-boot_smoke-47417a1af376`) faulted in `GeneralAllocator::rva00033150`+0x55
(retail 0x331a5, code byte-identical to retail) from `free` ← `_String_base::_M_deallocate_block`
← `basic_string<char>::reserve` ← `__copy` ← `_Init_timeinfo` ← `make_classic_locale` ←
`Rva007AB870InitializeClassicLocale`, during the initializer pass. The winning `reserve`
(95 bytes) came from `stlport_narrow_ostringstream_dtor.obj` (real STLport 4.6 headers): it
allocates through stock `__node_alloc<1,0>::allocate` but frees the old block through the
game's `free` (EA allocator), so the allocator read a node-pool block as its own. Retail's
`reserve` (0x0000C390, `stlport_narrow_string_reserve.cpp`, 116 bytes) allocates through
`allocator<char>::allocate` (0x000307F0, game class 3) and frees through `free` (0x00030830).
Only these two objects define the symbol, and the stock copy came first on the command line.
An image scan found no other function mixing stock allocate with game free (111 call stock
allocate, 1,834 call the game's `allocator<char>::allocate`).
Completed: the dtor TU declares `reserve` as an explicit specialization without a body, as it
already does for the proxy `deallocate`, so it emits no copy; none of its four rows calls
`reserve` in retail. `./build.sh` 6/6 exact; the object now leaves `reserve` undefined and
the retail copy is the only definer.
Remaining / next check: a queue receipt for an image from a commit with this change, past
`make_classic_locale`.
Clearance: pending the queue receipt.
Census confirmation: not claimed.

2026-11-05 follow-up: the image from `2b78296450` (receipt
`2026-11-05T232606Z-boot_smoke-ce226891c07e`) faulted at the same place with retail's `reserve`
winning: the block it freed came from the winning `basic_string<char>` default constructor, also
this unit's stock copy (allocates through `bfmeSmallAllocPS`, the node pool). Retail's
(0x00007850, `stlport_narrow_string_default_ctor.cpp`) calls `allocator<char>::allocate`; the two
are the only definers. The constructor is now declared body-less too (6/6 exact; both symbols
undefined in the object). A by-address scan of that image finds no other char-string function
on the stock pool. The unit still wins retail-owned `operator=`, `append(n, c)`,
`_M_append_buffer` and `epptr` copies, none of which call the pool; they are not changed here.
